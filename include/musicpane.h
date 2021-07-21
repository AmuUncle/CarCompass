#ifndef MUSICPANE_H
#define MUSICPANE_H

#include <QWidget>
#include "basewidget.h"

namespace Ui {
class MusicPane;
}

class MusicPane : public BaseWidget
{
    Q_OBJECT

public:
    explicit MusicPane(QWidget *parent = 0);
    ~MusicPane();

private:
    GLOBAL_FUNC

    void paintEvent(QPaintEvent* event);//重写绘画事件

signals:
    void SignalClose();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::MusicPane *ui;
};

#endif // MUSICPANE_H
