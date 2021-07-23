#include "standbypane.h"
#include "perfectclock.h"


StandbyPane::StandbyPane(QWidget *parent) : BaseWidget(parent)
{
    m_pPerfectClock = NULL;

    GLOBAL_FUNC_RUN
}

void StandbyPane::mousePressEvent(QMouseEvent *event)
{
    emit SignalClose();
}

void StandbyPane::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_pPerfectClock, PerfectClock);
}

void StandbyPane::InitCtrl()
{

}

void StandbyPane::InitSolts()
{

}

void StandbyPane::Relayout()
{
    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(m_pPerfectClock);
    layoutMain->setMargin(8);

    setLayout(layoutMain);
}
