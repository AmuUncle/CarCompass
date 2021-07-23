#ifndef STANDBYPANE_H
#define STANDBYPANE_H

#include <QWidget>
#include "basewidget.h"
#include "global.h"

class PerfectClock;
class StandbyPane : public BaseWidget
{
    Q_OBJECT
public:
    explicit StandbyPane(QWidget *parent = 0);

private:
    GLOBAL_FUNC

    void mousePressEvent(QMouseEvent *event);

signals:
    void SignalClose();

private:
    PerfectClock *m_pPerfectClock;
};

#endif // STANDBYPANE_H
