#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include "global.h"

class BaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent* event);//重写绘画事件
};

#endif // BASEWIDGET_H
