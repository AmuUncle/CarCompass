#include "voicecontrolpane.h"

VoiceControlPane::VoiceControlPane(QWidget *parent) : QWidget(parent)
{
    m_nIconSize = 120;
    m_iconCode = 0xe601;
    m_strText = tr("上海市 徐汇区 虹梅路\n阴转多云 30-36℃");

    m_bEnter = false;
    m_bPress = false;

    m_btnCfg = NULL;
    m_nVoiceChaneTimerId = -1;
    m_nVoiceHeight = 50;
    m_pAnimationOpacity = NULL;

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();
}

void VoiceControlPane::paintEvent(QPaintEvent *event)
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

    QFont ftIcon = IconHelper::GetFont();

    painter.save();

    float fRotationAngle = this->property("RotationAngle").toFloat();
    fRotationAngle = qMax(fRotationAngle, (float)0.0);

    if (QPropertyAnimation::Running == m_pAnimationOpacity->state())
    {
        painter.save();
        QRect rcShadow(rect().center().x() - 15, rect().center().y() - 30, 30, 50);
        rcShadow.setTop(rcShadow.top() + rcShadow.height() * (1 - fRotationAngle * 0.6));
        painter.setPen(Qt::NoPen);//设置画笔颜色
        painter.setBrush(QColor("#368B16"));//设置画刷颜色
        painter.drawRect(rcShadow);
        painter.restore();
    }

    painter.save();
    QRect rcIcon(rect());
    QFont font1 = ftIcon;
    font1.setBold(true);
    font1.setPixelSize(m_nIconSize);
    painter.setFont(font1);
    painter.setPen(QColor("#D7D7D7"));
    painter.drawText(rcIcon, Qt::AlignCenter, m_iconCode);
    painter.restore();

    painter.save();
    QRect rcText(rect().marginsRemoved(QMargins(6, 6, 6, 6)));
    rcText.setBottom(rcText.top() + 80);

    font1.setBold(true);
    font1.setPixelSize(25);
    painter.setFont(font1);
    painter.setPen(QColor("#D7D7D7"));
    painter.drawText(rcText, Qt::AlignLeft | Qt::AlignTop, QChar(0xe64c));
    painter.restore();


    painter.save();
    rcText.setTop(rcText.top() + 5);
    rcText.setLeft(rcText.left() + 25);
    QFont font2 = painter.font();
    font2.setBold(true);
    font2.setPixelSize(16);
    painter.setFont(font2);
    painter.setPen(QColor("#D7D7D7"));
    painter.drawText(rcText, Qt::AlignLeft | Qt::AlignTop, m_strText);
    painter.restore();

    if (QPropertyAnimation::Running == m_pAnimationOpacity->state())
    {
        painter.save();
        QFont font2 = painter.font();
        font2.setBold(true);

        font2.setPixelSize(26);
        painter.setFont(font2);
        QColor colorText("#4E555E");
        painter.setPen(colorText);
        painter.drawText(120, 130, tr("去机场"));

        font2.setPixelSize(16);
        painter.setFont(font2);
        colorText.setAlpha(100);
        painter.setPen(colorText);
        painter.drawText(20, 135, tr("打开空调"));

        font2.setPixelSize(36);
        painter.setFont(font2);
        colorText.setAlpha(200);
        painter.setPen(colorText);
        painter.drawText(30, 100, tr("来点音乐"));

        font2.setPixelSize(26);
        painter.setFont(font2);
        colorText.setAlpha(200);
        painter.setPen(colorText);
        painter.drawText(5, 300, tr("今天天气怎么样?"));

        font2.setPixelSize(10);
        painter.setFont(font2);
        colorText.setAlpha(100);
        painter.setPen(colorText);
        painter.drawText(110, 280, tr("启动辅助驾驶"));

        painter.restore();

        painter.save();
        painter.setBrush(Qt::NoBrush);//设置画刷颜色

        int nOffset1 = 10 * fRotationAngle;

        QPoint ptCenter = rect().center();
        QColor colorEllipse("#3B4345");

        painter.setPen(colorEllipse);//设置画笔颜色
        painter.drawEllipse(QPoint(ptCenter.x() + 1, ptCenter.y() + 2), 58 + nOffset1, 58 + nOffset1);

        colorEllipse.setAlpha(200);
        painter.setPen(colorEllipse);//设置画笔颜色
        painter.drawEllipse(QPoint(ptCenter.x() + 1, ptCenter.y() + 2), 68 + nOffset1, 68 + nOffset1);

        colorEllipse.setAlpha(100);
        painter.setPen(colorEllipse);//设置画笔颜色
        painter.drawEllipse(QPoint(ptCenter.x() + 1, ptCenter.y() + 2), 78 + nOffset1, 78 + nOffset1);

        painter.restore();
    }

    painter.restore();
}

void VoiceControlPane::enterEvent(QEvent *event)
{
    m_bEnter = true;
    update();
}

void VoiceControlPane::leaveEvent(QEvent *event)
{
    m_bEnter = false;
    update();
}

void VoiceControlPane::mousePressEvent(QMouseEvent *event)
{
    m_bPress = false;
    update();

    if (m_regVoice.contains(event->pos()))
    {
        m_pAnimationOpacity->start();
    }

    QWidget::mousePressEvent(event);
}

void VoiceControlPane::mouseReleaseEvent(QMouseEvent *event)
{
    m_bPress = false;
    update();

    QWidget::mouseReleaseEvent(event);
}

void VoiceControlPane::timerEvent(QTimerEvent *event)
{
    if (m_nVoiceChaneTimerId == event->timerId())
    {
        qsrand(QDateTime::currentMSecsSinceEpoch());
        m_nVoiceHeight = qrand() % 100;
        update();
    }
}

void VoiceControlPane::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_btnCfg, QPushButton);
}

void VoiceControlPane::InitCtrl()
{
    setMaximumWidth(240);
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    IconHelper::SetIcon(m_btnCfg, QChar(0xe606));

    m_regVoice = QRegion(118 - 55, 200 - 55, 110, 110, QRegion::Ellipse);


    this->setProperty("RotationAngle", 1.0);
    m_pAnimationOpacity = new QPropertyAnimation(this, "RotationAngle");
    m_pAnimationOpacity->setDuration(500);
    m_pAnimationOpacity->setEasingCurve(QEasingCurve::Linear);
    m_pAnimationOpacity->setStartValue(0.0);
    m_pAnimationOpacity->setEndValue(1.0);
    m_pAnimationOpacity->setLoopCount(15);
    connect(m_pAnimationOpacity, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
    connect(m_pAnimationOpacity, SIGNAL(finished()), this, SLOT(update()));
}

void VoiceControlPane::InitSolts()
{

}

void VoiceControlPane::Relayout()
{
    QHBoxLayout *layouBottom = new QHBoxLayout();
    layouBottom->addWidget(m_btnCfg);
    layouBottom->addStretch();
    layouBottom->setMargin(0);

    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->addStretch();
    layoutMain->addLayout(layouBottom);
    layoutMain->setMargin(8);

    setLayout(layoutMain);
}
