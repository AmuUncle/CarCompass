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
#include "moviepicwidget.h"
#include "systemcfg.h"

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
    m_pMoviePicWidget = NULL;
    m_pAnimationOpacity = NULL;
    m_pSystemCfg = NULL;

    m_eMainTabTitle = TABTITLE_MAIN;

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    setFixedSize(800, 480);
    setProperty("canMove", "true");
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "mainwnd");

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();
    ChangePage();
    RunLoading();
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
    NEW_OBJECT(m_pMoviePicWidget, MoviePicWidget);
    NEW_OBJECT(m_pSystemCfg, SystemCfg);
}

void CarCompass::InitCtrl()
{
    m_pStackedWidget->hide();
    m_pLiquidPlot->SetWaterColor(QColor("#24272C"));
    m_pLiquidPlot->SetPlotType(LiquidPlot::PLOTTYPE_RECTANGLE);
    m_pLiquidPlot->SetSpeed(50);
    m_pLiquidPlot->SetPercent(0);
    m_pLiquidPlot->hide();

    m_pStackedWidget->insertWidget(TABTITLE_MAIN, m_pMainWnd);
    m_pStackedWidget->insertWidget(TABTITLE_DROPBOX, m_pDropdownBox);
    m_pStackedWidget->insertWidget(TABTITLE_CALL, m_pIncomingCall);
    m_pStackedWidget->insertWidget(TABTITLE_MUSIC, m_pMusicPane);
    m_pStackedWidget->insertWidget(TABTITLE_COMPASS, m_pCompassPane);
    m_pStackedWidget->insertWidget(TABTITLE_STANDBY, m_pStandbyPane);
    m_pStackedWidget->insertWidget(TABTITLE_SYSCFG, m_pSystemCfg);
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

    connect(m_pSystemCfg, &SystemCfg::SignalClose, [=]()
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
    layoutMain->addWidget(m_pMoviePicWidget);
    layoutMain->addWidget(m_pStackedWidget);
    layoutMain->setMargin(0);

    setLayout(layoutMain);
}

void CarCompass::ChangePage()
{
    m_pStackedWidget->setCurrentIndex(m_eMainTabTitle);
}

//排列判断
bool compareFileName(const QString &file1, const QString &file2)
{
    int nIndex1 = 0;
    int nIndex2 = 0;

    if (file1.split("(").size() > 1)
    {
        QString name = file1.split("(").at(1);
        nIndex1 = atoi(name.toStdString().c_str());
    }

    if (file2.split("(").size() > 1)
    {
        QString name = file2.split("(").at(1);
        nIndex2 = atoi(name.toStdString().c_str());
    }

    if (nIndex1 < nIndex2)
        return true;

    return false;
}

void CarCompass::RunLoading()
{
    QString strRoot = QCoreApplication::applicationDirPath();
    QList<QPixmap> picList;

    QDir dir(QString("%1\\screen").arg(strRoot));
    QStringList nameFilters;
    nameFilters  << "*.png";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);

    qSort(files.begin(), files.end(), compareFileName);

    foreach (QString file, files)
    {
       picList << QPixmap(QString("%1\\screen\\%2").arg(strRoot).arg(file));
    }

    m_pMoviePicWidget->SetPicList(picList);
    m_pMoviePicWidget->Start(50);
    m_pMoviePicWidget->show();

    QTimer::singleShot(50 * picList.size(), [=]()
    {
        this->setProperty("transparency", 0.0);
        m_pAnimationOpacity = new QPropertyAnimation(this, "transparency");
        m_pAnimationOpacity->setDuration(800);
        m_pAnimationOpacity->setEasingCurve(QEasingCurve::InQuart);
        m_pAnimationOpacity->setStartValue(0);
        m_pAnimationOpacity->setEndValue(m_pMoviePicWidget->height());

        connect(m_pAnimationOpacity, &QPropertyAnimation::valueChanged, [=](const QVariant &value)
        {
            int fTransparencye = value.toInt();
            m_pMoviePicWidget->setFixedHeight(m_pAnimationOpacity->endValue().toInt() - fTransparencye);
            m_pStackedWidget->show();
        });

        connect(m_pAnimationOpacity, &QPropertyAnimation::finished, [=]()
        {
            m_pMoviePicWidget->Stop();
            m_pMoviePicWidget->hide();
            m_pStackedWidget->show();
            m_eMainTabTitle = TABTITLE_MAIN;
            ChangePage();
            AppInit::Instance()->StartWatchMouse();
        });

        m_pAnimationOpacity->start();
    });
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

