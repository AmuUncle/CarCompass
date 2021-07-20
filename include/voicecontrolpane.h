#ifndef VOICECONTROLPANE_H
#define VOICECONTROLPANE_H

#include <QWidget>
#include "global.h"

class VoiceControlPane : public QWidget
{
    Q_OBJECT
public:
    explicit VoiceControlPane(QWidget *parent = 0);

private:
    void paintEvent(QPaintEvent* event);//重写绘画事件
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event);

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitSolts();
    void Relayout();

private slots:


private:
    QChar m_iconCode;
    int m_nIconSize;
    QString m_strText;

    bool m_bEnter;
    bool m_bPress;

    QRegion m_regVoice;
    int m_nVoiceChaneTimerId;
    int m_nVoiceHeight;

    QPropertyAnimation *m_pAnimationOpacity;
    QPushButton *m_btnCfg;
};

#endif // VOICECONTROLPANE_H
