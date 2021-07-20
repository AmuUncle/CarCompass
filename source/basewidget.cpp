#include "basewidget.h"

BaseWidget::BaseWidget(QWidget *parent) : QWidget(parent)
{

}

void BaseWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, true); // 抗锯齿和使用平滑转换算法

    QColor colorBg("#24272C");

    painter.setPen(Qt::NoPen);//设置画笔颜色
    painter.setBrush(colorBg);//设置画刷颜色
    painter.drawRect(rect());

    const int nOffset = 4;
    for (int i = 0; i < 4; i++)
    {
        QRect rcShadow(rect());

        if (0 == i)
        {
            rcShadow.setRight(rcShadow.left() + nOffset);

            QLinearGradient batteryGradient(rcShadow.topLeft(), rcShadow.topRight());
            batteryGradient.setColorAt(0.0, QColor(QString("#2B2E33")));
            batteryGradient.setColorAt(1.0, colorBg);

            painter.setPen(Qt::NoPen);
            painter.setBrush(batteryGradient);
        }
        else if (1 == i)
        {
            rcShadow.setBottom(rcShadow.top() + nOffset);

            QLinearGradient batteryGradient(rcShadow.topLeft(), rcShadow.bottomLeft());
            batteryGradient.setColorAt(0.0, QColor(QString("#2B2E33")));
            batteryGradient.setColorAt(1.0, colorBg);

            painter.setPen(Qt::NoPen);
            painter.setBrush(batteryGradient);
        }
        else if (2 == i)
        {
            rcShadow.setLeft(rcShadow.right() - nOffset);

            QLinearGradient batteryGradient(rcShadow.topLeft(), rcShadow.topRight());
            batteryGradient.setColorAt(1.0, QColor(QString("#2B2E33")));
            batteryGradient.setColorAt(0.0, colorBg);

            painter.setPen(Qt::NoPen);
            painter.setBrush(batteryGradient);
        }
        else if (3 == i)
        {
            rcShadow.setTop(rcShadow.bottom() - nOffset);

            QLinearGradient batteryGradient(rcShadow.topLeft(), rcShadow.bottomLeft());
            batteryGradient.setColorAt(1.0, QColor(QString("#2B2E33")));
            batteryGradient.setColorAt(0.0, colorBg);

            painter.setPen(Qt::NoPen);
            painter.setBrush(batteryGradient);
        }

        painter.drawRect(rcShadow);
    }
}
