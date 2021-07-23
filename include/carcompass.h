#ifndef CARCOMPASS_H
#define CARCOMPASS_H

#include <QWidget>
#include <QPropertyAnimation>
#include "global.h"

class MainWnd;
class DropdownBox;
class IncomingCall;
class MusicPane;
class CompassPane;
class LiquidPlot;
class StandbyPane;
class MoviePicWidget;
class SystemCfg;
class CarCompass : public QWidget
{
    Q_OBJECT

public:
    CarCompass(QWidget *parent = 0);
    ~CarCompass();

private:
    GLOBAL_FUNC
    void ChangePage();
    void RunLoading();

    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    MoviePicWidget *m_pMoviePicWidget;
    LiquidPlot *m_pLiquidPlot;
    QStackedWidget *m_pStackedWidget;
    MainWnd *m_pMainWnd;
    DropdownBox *m_pDropdownBox;
    IncomingCall *m_pIncomingCall;
    MusicPane *m_pMusicPane;
    CompassPane *m_pCompassPane;
    StandbyPane *m_pStandbyPane;
    SystemCfg *m_pSystemCfg;

    EMainTabTitle m_eMainTabTitle;

    QPropertyAnimation* m_pAnimationOpacity;
    QTimer *m_pLodingTimer;
};

#endif // CARCOMPASS_H
