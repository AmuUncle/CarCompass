#include "carcompass.h"
#include "basebutton.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "global.h"
#include "voicecontrolpane.h"
#include "dropdownbox.h"
#include "mainwnd.h"
#include "incomingcall.h"
#include "musicpane.h"
#include "compasspane.h"
#include "liquidplot.h"
#include "appinit.h"
#include "standbypane.h"


CarCompass::CarCompass(QWidget *parent)
    : QWidget(parent)
{
    m_pLodingTimer = NULL;
    m_pLiquidPlot = NULL;
    m_pStackedWidget = NULL;
    m_pMainWnd = NULL;
    m_pDropdownBox = NULL;
    m_pIncomingCall = NULL;
    m_pMusicPane = NULL;
    m_pCompassPane = NULL;
    m_pStandbyPane = NULL;

    m_eMainTabTitle = TABTITLE_MAIN;

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    setFixedSize(720, 400);
    setProperty("canMove", "true");
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "mainwnd");

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();
    ChangePage();
}

CarCompass::~CarCompass()
{

}

void CarCompass::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_pStackedWidget, QStackedWidget);
    NEW_OBJECT(m_pMainWnd, MainWnd);
    NEW_OBJECT(m_pDropdownBox, DropdownBox);
    NEW_OBJECT(m_pIncomingCall, IncomingCall);
    NEW_OBJECT(m_pMusicPane, MusicPane);
    NEW_OBJECT(m_pCompassPane, CompassPane);
    NEW_OBJECT(m_pLiquidPlot, LiquidPlot);
    NEW_OBJECT(m_pLodingTimer, QTimer);
    NEW_OBJECT(m_pStandbyPane, StandbyPane);
}

void CarCompass::InitCtrl()
{
    m_pStackedWidget->hide();
    m_pLiquidPlot->SetWaterColor(QColor("#24272C"));
    m_pLiquidPlot->SetPlotType(LiquidPlot::PLOTTYPE_RECTANGLE);
    m_pLiquidPlot->SetSpeed(50);
    m_pLiquidPlot->SetPercent(0);
    m_pLodingTimer->start(20);

    m_pStackedWidget->insertWidget(TABTITLE_MAIN, m_pMainWnd);
    m_pStackedWidget->insertWidget(TABTITLE_DROPBOX, m_pDropdownBox);
    m_pStackedWidget->insertWidget(TABTITLE_CALL, m_pIncomingCall);
    m_pStackedWidget->insertWidget(TABTITLE_MUSIC, m_pMusicPane);
    m_pStackedWidget->insertWidget(TABTITLE_COMPASS, m_pCompassPane);
    m_pStackedWidget->insertWidget(TABTITLE_STANDBY, m_pStandbyPane);
}

void CarCompass::InitSolts()
{
    connect(m_pLodingTimer, &QTimer::timeout, [=]()
    {
        if (m_pLiquidPlot->GetPercent() < 100)
            m_pLiquidPlot->SetPercent(m_pLiquidPlot->GetPercent() + 1);
        else
        {
            m_pLiquidPlot->hide();
            m_pStackedWidget->show();
            m_pLodingTimer->stop();
        }
    });

    connect(m_pDropdownBox, &DropdownBox::SignalClose, [=]()
    {
        m_eMainTabTitle = TABTITLE_MAIN;
        ChangePage();
    });

    connect(m_pMainWnd, &MainWnd::SignalPageChange, [=](EMainTabTitle eMainTabTitle)
    {
        m_eMainTabTitle = eMainTabTitle;
        ChangePage();
    });

    connect(m_pIncomingCall, &IncomingCall::SignalClose, [=]()
    {
        m_eMainTabTitle = TABTITLE_MAIN;
        ChangePage();
    });

    connect(m_pMusicPane, &MusicPane::SignalClose, [=]()
    {
        m_eMainTabTitle = TABTITLE_MAIN;
        ChangePage();
    });

    connect(m_pCompassPane, &CompassPane::SignalClose, [=]()
    {
        m_eMainTabTitle = TABTITLE_MAIN;
        ChangePage();
    });

    connect(m_pStandbyPane, &StandbyPane::SignalClose, [=]()
    {
        m_eMainTabTitle = TABTITLE_MAIN;
        ChangePage();
    });

    connect(AppInit::Instance(), &AppInit::SignalNoUserOperation, [=]()
    {
        if (TABTITLE_STANDBY == m_eMainTabTitle)
            return;

        m_eMainTabTitle = TABTITLE_STANDBY;
        ChangePage();
    });
}

void CarCompass::Relayout()
{
    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(m_pLiquidPlot);
    layoutMain->addWidget(m_pStackedWidget);
    layoutMain->setMargin(0);

    setLayout(layoutMain);
}

void CarCompass::ChangePage()
{
    m_pStackedWidget->setCurrentIndex(m_eMainTabTitle);
}

void CarCompass::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        m_eMainTabTitle = TABTITLE_DROPBOX;
        ChangePage();
    }
}

void CarCompass::mouseDoubleClickEvent(QMouseEvent *event)
{
}

