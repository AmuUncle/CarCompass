#include "boderpane.h"
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>

BoderPane::BoderPane(QWidget *parent) : QWidget(parent)
{
    m_widgetMain = new QWidget(this);


    InitMainCtrl();
}

QWidget *BoderPane::centralWidget() const
{
    Q_ASSERT(NULL != m_widgetMain);

    return m_widgetMain;
}

void BoderPane::InitMainCtrl()
{
    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(m_widgetMain);
    layoutMain->setMargin(8);

    // 设置边框阴影
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    // 设置具体阴影
    QGraphicsDropShadowEffect *shadowBorder = new QGraphicsDropShadowEffect(this);
    shadowBorder->setOffset(0, 0);
    // 阴影颜色
    shadowBorder->setColor(QColor(0x44, 0x44, 0x44, 127));
    // 阴影半径
    shadowBorder->setBlurRadius(8);
    setGraphicsEffect(shadowBorder);

    m_widgetMain->setAttribute(Qt::WA_StyledBackground);              // 禁止父窗口样式影响子控件样式
    m_widgetMain->setProperty("form", "userpane");
}
