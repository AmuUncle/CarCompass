#include "carcompass.h"
#include "basebutton.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "global.h"
#include "voicecontrolpane.h"
#include "dropdownbox.h"

CarCompass::CarCompass(QWidget *parent)
    : QWidget(parent)
{
    m_pStackedWidget = NULL;
    m_pWidgetMain = NULL;
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
    NEW_OBJECT(m_pWidgetMain, QWidget);
    NEW_OBJECT(m_pDropdownBox, DropdownBox);
}

void CarCompass::InitCtrl()
{

    VoiceControlPane *btn1 = new VoiceControlPane(m_pWidgetMain);
    BaseButton *btn2 = new BaseButton(m_pWidgetMain);
    BaseButton *btn3 = new BaseButton(m_pWidgetMain);
    BaseButton *btn4 = new BaseButton(m_pWidgetMain);
    BaseButton *btn5 = new BaseButton(m_pWidgetMain);

    btn2->ShowShadow(true);
    btn3->ShowShadow(true);
    btn4->ShowShadow(true);
    btn5->ShowShadow(true);

    btn2->setText(tr("电话"));
    btn3->setText(tr("音乐"));
    btn4->setText(tr("导航"));
    btn5->setText(tr("附近"));

    btn2->SetIcon(QChar(0xe864));
    btn3->SetIcon(QChar(0xe600));
    btn4->SetIcon(QChar(0xe794));
    btn5->SetIcon(QChar(0xe64c));

    QGridLayout *layoutMain = new QGridLayout();
    layoutMain->addWidget(btn1, 0, 0, 2, 1);
    layoutMain->addWidget(btn2, 0, 1, 1, 1);
    layoutMain->addWidget(btn3, 0, 2, 1, 1);
    layoutMain->addWidget(btn4, 1, 1, 1, 1);
    layoutMain->addWidget(btn5, 1, 2, 1, 1);

    layoutMain->setMargin(1);
    layoutMain->setSpacing(2);
    m_pWidgetMain->setLayout(layoutMain);

    m_pStackedWidget->insertWidget(TABTITLE_MAIN, m_pWidgetMain);
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
