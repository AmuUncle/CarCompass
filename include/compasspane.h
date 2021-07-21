#ifndef COMPASSPANE_H
#define COMPASSPANE_H

#include <QWidget>
#include "basewidget.h"

namespace Ui {
class CompassPane;
}

class CompassPane : public BaseWidget
{
    Q_OBJECT

public:
    explicit CompassPane(QWidget *parent = 0);
    ~CompassPane();

private:
    GLOBAL_FUNC

    void resizeEvent(QResizeEvent *event);

signals:
    void SignalClose();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CompassPane *ui;
};

#endif // COMPASSPANE_H
