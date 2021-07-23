#ifndef APPINIT_H
#define APPINIT_H

#include <QObject>
#include <QTime>

class QTimer;
class AppInit : public QObject
{
    Q_OBJECT
public:
    static AppInit *Instance();
    explicit AppInit(QObject *parent = 0);    

    void start();
    void StartWatchMouse();
    void StopWatchMouse();

protected:
    bool eventFilter(QObject *obj, QEvent *evt);

private:
    static AppInit *self;

    QTimer *m_pMouseWatcher;
    QTime m_timeMouseTrigger;

signals:
    void SignalNoUserOperation();

public slots:
};

#endif // APPINIT_H
