#include "mainwnd.h"
#include "voicecontrolpane.h"
#include "basebutton.h"

MainWnd::MainWnd(QWidget *parent) : QWidget(parent)
{
    m_pVoiceControlPane = NULL;
    m_btn1 = NULL;
    m_btn2 = NULL;
    m_btn3 = NULL;
    m_btn4 = NULL;

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();
}

void MainWnd::CreateAllChildWnd()
{
    NEW_OBJECT(m_pVoiceControlPane, VoiceControlPane);
    NEW_OBJECT(m_btn1, BaseButton);
    NEW_OBJECT(m_btn2, BaseButton);
    NEW_OBJECT(m_btn3, BaseButton);
    NEW_OBJECT(m_btn4, BaseButton);
}

void MainWnd::InitCtrl()
{
    m_btn1->ShowShadow(true);
    m_btn2->ShowShadow(true);
    m_btn3->ShowShadow(true);
    m_btn4->ShowShadow(true);

    m_btn1->setText(tr("电话"));
    m_btn2->setText(tr("音乐"));
    m_btn3->setText(tr("导航"));
    m_btn4->setText(tr("附近"));

    m_btn1->SetIcon(QChar(0xe864));
    m_btn2->SetIcon(QChar(0xe600));
    m_btn3->SetIcon(QChar(0xe794));
    m_btn4->SetIcon(QChar(0xe64c));
}

void MainWnd::InitSolts()
{
    QSignalMapper *pSignalMapperPushed = new QSignalMapper(this);
    pSignalMapperPushed->setMapping(m_btn1, TABTITLE_CALL);
    pSignalMapperPushed->setMapping(m_btn2, TABTITLE_MUSIC);
    pSignalMapperPushed->setMapping(m_btn3, TABTITLE_COMPASS);
    pSignalMapperPushed->setMapping(m_btn4, TABTITLE_MEETING);

    QList<BaseButton *> listBtns = findChildren<BaseButton *>();
    foreach (BaseButton *btn, listBtns)
    {
        connect(btn, SIGNAL(SignalClicked()), pSignalMapperPushed, SLOT(map()));
    }

    connect(pSignalMapperPushed, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped), [=](int value)
    {
        emit SignalPageChange((EMainTabTitle)value);
    });

    connect(m_pVoiceControlPane, &VoiceControlPane::SignalSysCfg, [=]()
    {
        emit SignalPageChange(TABTITLE_SYSCFG);
    });
}

void MainWnd::Relayout()
{
    QGridLayout *layoutRught = new QGridLayout();
    layoutRught->addWidget(m_btn1, 0, 0, 1, 1);
    layoutRught->addWidget(m_btn2, 0, 1, 1, 1);
    layoutRught->addWidget(m_btn3, 1, 0, 1, 1);
    layoutRught->addWidget(m_btn4, 1, 1, 1, 1);

    layoutRught->setMargin(0);
    layoutRught->setSpacing(2);

    QHBoxLayout *layoutMain = new QHBoxLayout();
    layoutMain->addWidget(m_pVoiceControlPane);
    layoutMain->addLayout(layoutRught);
    layoutMain->setMargin(0);
    layoutMain->setSpacing(2);

    setLayout(layoutMain);
}
