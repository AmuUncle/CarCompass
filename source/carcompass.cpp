#include "carcompass.h"
#include "basebutton.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "global.h"
#include "voicecontrolpane.h"
#include "dropdownbox.h"
#include "mainwnd.h"


CarCompass::CarCompass(QWidget *parent)
    : QWidget(parent)
{
    m_pStackedWidget = NULL;
    m_pMainWnd = NULL;
    m_pDropdownBox = NULL;
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
}

void CarCompass::InitCtrl()
{
    m_pStackedWidget->insertWidget(TABTITLE_MAIN, m_pMainWnd);
    m_pStackedWidget->insertWidget(TABTITLE_DROPBOX, m_pDropdownBox);
}

void CarCompass::InitSolts()
{
    connect(m_pDropdownBox, &DropdownBox::SignalClose, [=]()
    {
        m_eMainTabTitle = TABTITLE_MAIN;
        ChangePage();
    });
}

void CarCompass::Relayout()
{
    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(m_pStackedWidget);
    layoutMain->setMargin(0);

    setLayout(layoutMain);
}

void CarCompass::ChangePage()
{
    m_pStackedWidget->setCurrentIndex(m_eMainTabTitle);
}

void CarCompass::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_eMainTabTitle = TABTITLE_DROPBOX;
    ChangePage();
}
