#include "basebutton.h"
#include "global.h"

BaseButton::BaseButton(QWidget *parent) : QWidget(parent)
{
    m_nIconSize = 70;
    m_iconCode = 0xe864;
    m_nTextSize = 25;

    m_bEnter = false;
    m_bPress = false;
    m_bShowShadow = false;
}

void BaseButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, true); // 抗锯齿和使用平滑转换算法

    QColor colorBg("#24272C");

    if (m_bEnter)
        colorBg = QColor("#2B2E33");

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

    QFont ftIcon = IconHelper::GetFont();

    painter.save();

    if (m_bShowShadow)
    {
        painter.save();
        QRect rcShadow(rect());
        rcShadow.setTop(rcShadow.center().y() + (m_nIconSize / 2 - 15));
        rcShadow.setBottom(rcShadow.top() + 20);

        QRect rcShadowPic(rcShadow.center().x() - 25, rcShadow.center().y() - 8, 50, 16);
        QPixmap backPixmap = QPixmap(":/img/shadow.png");
        painter.drawPixmap(rcShadowPic, backPixmap.scaled(rcShadowPic.size()));

        painter.restore();
    }

    painter.save();
    QRect rcIcon(rect());
    rcIcon.setBottom(rcIcon.bottom() - (height() / 3 ));
    QFont font1 = ftIcon;
    font1.setBold(true);
    font1.setPixelSize(m_nIconSize);
    painter.setFont(font1);
    painter.setPen(QColor("#D7D7D7"));
    painter.drawText(rcIcon, Qt::AlignHCenter | Qt::AlignBottom, m_iconCode);
    painter.restore();

    painter.save();
    QRect rcText(rect());
    rcText.setBottom(rcText.bottom() - (height() / 7));
    QFont font2 = painter.font();
    font2.setBold(true);
    font2.setPixelSize(m_nTextSize);
    painter.setFont(font2);
    painter.setPen(QColor("#D7D7D7"));
    painter.drawText(rcText, Qt::AlignHCenter | Qt::AlignBottom, m_strText);
    painter.restore();

    painter.restore();
}

void BaseButton::enterEvent(QEvent *event)
{
    m_bEnter = true;
    update();
}

void BaseButton::leaveEvent(QEvent *event)
{
    m_bEnter = false;
    update();
}

void BaseButton::mousePressEvent(QMouseEvent *event)
{
    m_bPress = false;
    update();

    QWidget::mousePressEvent(event);
}

void BaseButton::mouseReleaseEvent(QMouseEvent *event)
{
    m_bPress = false;
    update();

    QWidget::mouseReleaseEvent(event);
}
