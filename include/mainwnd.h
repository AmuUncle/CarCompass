#ifndef MAINWND_H
#define MAINWND_H

#include <QWidget>
#include "global.h"

class BaseButton;
class VoiceControlPane;
class MainWnd : public QWidget
{
    Q_OBJECT
public:
    explicit MainWnd(QWidget *parent = 0);

private:
    GLOBAL_FUNC

private slots:


signals:
    void SignalPageChange(EMainTabTitle eMainTabTitle);

private:
    VoiceControlPane *m_pVoiceControlPane;
    BaseButton *m_btn1;
    BaseButton *m_btn2;
    BaseButton *m_btn3;
    BaseButton *m_btn4;
};

#endif // MAINWND_H
