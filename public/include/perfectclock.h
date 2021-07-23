#ifndef PERFECTCLOCK_H
#define PERFECTCLOCK_H

#include <QWidget>
#include "boderpane.h"
#include <QPropertyAnimation>


class PerfectClock : public QWidget
{
    Q_OBJECT

public:
    PerfectClock(QWidget *parent = 0);
    ~PerfectClock();

public:
    void EnableDrakMode(bool bEnable) { m_bDarkMode = bEnable; update(); }
    bool IsDrakMode() { return m_bDarkMode; }

private:
    void paintEvent(QPaintEvent *event);
    void paintClock(QPainter *p, QRect rcClock);
    void timerEvent(QTimerEvent *event);

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitSolts();
    void Relayout();

private:
    bool m_bDarkMode;
    QFont m_iconFont;
    QPropertyAnimation* m_pAnimationOpacity;
    QTime m_curTime;
    int m_nTimerId;
};


class Clock : public QWidget
{
    Q_OBJECT

public:
    Clock(QWidget *parent = 0);

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitSolts();
    void Relayout();

    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    PerfectClock *m_pPerfectClock;
};

#endif // PERFECTCLOCK_H
