#ifndef INCOMINGCALL_H
#define INCOMINGCALL_H

#include <QWidget>
#include "basewidget.h"
#include "global.h"

namespace Ui {
class IncomingCall;
}

class IncomingCall : public BaseWidget
{
    Q_OBJECT

public:
    explicit IncomingCall(QWidget *parent = 0);
    ~IncomingCall();

private:
    GLOBAL_FUNC

signals:
    void SignalClose();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::IncomingCall *ui;
};

#endif // INCOMINGCALL_H
