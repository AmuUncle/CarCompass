#include "liquidplot.h"
#include <QPainter>
#include <QWheelEvent>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QtMath>
#include <QFontDatabase>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

LiquidPlot::LiquidPlot(QWidget *parent)
    : QWidget(parent)
{
    m_fOffset = 350.0;
    m_nPercent = 50;
    m_ePlotType = PLOTTYPE_CIRCULAR;
    m_nSpeed = 10;
    m_colorWater = QColor("#6193F9");
    m_bEnableSpace = false;

    this->setAttribute(Qt::WA_TranslucentBackground, true);

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();
}

LiquidPlot::~LiquidPlot()
{

}

void LiquidPlot::SetPercent(int nPercent)
{
    m_nPercent = nPercent;
    update();
}

void LiquidPlot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);         // 创建画家对象
    QRect rcClient = rect();
    DrawCircularPlot(&painter, rcClient.marginsRemoved(QMargins(0, 0, 0, 0)));

    if (m_nPercent > 60)
    {
        painter.save();

        QFont font1 = QFont("YouYuan", 9);
        font1.setBold(true);
        font1.setPixelSize(80);
        painter.setFont(font1);
        QColor color = QColor("#D7D7D7");
        color.setAlpha(255 * (double)(40 - (100 - m_nPercent))/40.0);

        painter.setPen(color);
        painter.drawText(rect(), Qt::AlignCenter, "汽车导航仪");
        painter.restore();
    }
}

void LiquidPlot::DrawCircularPlot(QPainter *p, QRect rcRect)
{
    p->save();

    p->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform | QPainter::Qt4CompatiblePainting);
    p->translate(rcRect.left(), rcRect.top());

    int side = qMin(rcRect.width(), rcRect.height());
    p->scale(rcRect.width() / 350.0, rcRect.height() / 350.0);

    QRect rcBase(0, 0, 350, 350);
    QColor boderColor(m_colorWater);
    QColor clockDialColor("#FFFFFF");

    // 边框
    if (PLOTTYPE_CIRCULAR == m_ePlotType)
    {
        p->save();
        p->setPen(Qt::NoPen);
        p->setBrush(boderColor);
        p->drawEllipse(rcBase);
        p->setBrush(clockDialColor);
        p->drawEllipse(rcBase.marginsRemoved(QMargins(5, 5, 5, 5)));
        p->restore();
    }
    else if (PLOTTYPE_RECTANGLE == m_ePlotType)
    {
        p->save();
        p->setPen(Qt::NoPen);
        p->setBrush(boderColor);
        p->drawRect(rcBase);
        p->setBrush(clockDialColor);
        p->drawRect(rcBase.marginsRemoved(QMargins(5, 5, 5, 5)));
        p->restore();
    }
    else if (PLOTTYPE_DIAMOND == m_ePlotType)
    {
        QRect rcClip = rcBase;
        QPolygon py;
        py << QPoint(rcClip.center().x(), rcClip.top()) << QPoint(rcClip.right(), rcClip.center().y())
                << QPoint(rcClip.center().x(), rcClip.bottom())
                 << QPoint(rcClip.left(), rcClip.center().y());

        p->save();
        p->setPen(Qt::NoPen);
        p->setBrush(boderColor);
        p->drawPolygon(py);

        {
            QRect rcClip = rcBase.marginsRemoved(QMargins(5, 5, 5, 5));
            QPolygon py;
            py << QPoint(rcClip.center().x(), rcClip.top()) << QPoint(rcClip.right(), rcClip.center().y())
                    << QPoint(rcClip.center().x(), rcClip.bottom())
                     << QPoint(rcClip.left(), rcClip.center().y());

            p->setBrush(clockDialColor);
            p->drawPolygon(py);
        }

        p->restore();
    }

    p->save();

    int nOffset = 2;
    if (m_bEnableSpace)
        nOffset = 10;

    if (PLOTTYPE_CIRCULAR == m_ePlotType)
    {
        p->setClipRegion(QRegion(rcBase.adjusted(nOffset, nOffset, -nOffset, -nOffset), QRegion::Ellipse));
    }
    else if (PLOTTYPE_RECTANGLE == m_ePlotType)
    {
        p->setClipRegion(QRegion(rcBase.adjusted(nOffset, nOffset, -nOffset, -nOffset), QRegion::Rectangle));
    }
    else if (PLOTTYPE_DIAMOND == m_ePlotType)
    {
        QRect rcClip = rcBase.adjusted(nOffset, nOffset, -nOffset, -nOffset);
        QPolygon py;
        py << QPoint(rcClip.center().x(), rcClip.top()) << QPoint(rcClip.right(), rcClip.center().y())
                << QPoint(rcClip.center().x(), rcClip.bottom())
                 << QPoint(rcClip.left(), rcClip.center().y());

        p->setClipRegion(QRegion(py));
    }


    if (m_nPercent < 100)
    {
        //起始点坐标和结束点坐标
        int startX = 0;
        int endX = rcBase.width() - 0;
        int endY = rcBase.height() - 0;

        //第一条波浪路径集合
        QPainterPath waterPath1;
        //第二条波浪路径集合
        QPainterPath waterPath2;
        //第三条波浪路径集合
        QPainterPath waterPath3;
        QPainterPath waterPath4;

        //移动到左上角起始点
        waterPath1.moveTo(startX, endY);
        waterPath2.moveTo(startX, endY);
        waterPath3.moveTo(startX, endY);
        waterPath4.moveTo(startX, endY);

        //正弦曲线公式 y = A * qSin(ωx + φ) + k
        //A表示振幅,可以理解为水波的高度
        //k表示y轴偏移,控制在垂直方向显示的位置
        //φ控制x轴偏移，通过定时器控制实现动画效果
        //w表示周期,可以理解为水波的密度,值越大密度越大(浪越密集 ^_^),取值 密度*M_PI/宽度

        double Density = 5.0;
        double w = Density*M_PI/rcBase.width();

        m_fOffset += 0.6;
        for(int i = 0; i <= rcBase.width(); i++)
        {
            double y1 = (double)(10 * sin(-w * (i - m_fOffset) + 400*w)) + rcBase.height() * (double)(100 - m_nPercent)/100.0;
            double y2 = (double)(10 * sin(-w * (i - m_fOffset * 0.3) + 200*w)) + rcBase.height() * (double)(100 - m_nPercent)/100.0;
            double y3 = (double)(10 * sin(-w * (i - m_fOffset * 0.7) + 200*w)) + rcBase.height() * (double)(100 - m_nPercent)/100.0;

            waterPath1.lineTo(i, y1);
            waterPath2.lineTo(i, y2);
            waterPath3.lineTo(i, y3);
        }

        //形成闭合路径
        waterPath1.lineTo(endX, endY);
        waterPath2.lineTo(endX, endY);
        waterPath3.lineTo(endX, endY);
        waterPath4.lineTo(endX, endY);

        //颜色及透明度设置
        QColor waterColor1 = m_colorWater;
        waterColor1.setAlpha(255);
        QColor waterColor2 = m_colorWater;
        waterColor2.setAlpha(150);
        QColor waterColor3 = m_colorWater;
        waterColor3.setAlpha(100);

        p->setPen(Qt::NoPen);
        //绘制path
        p->setBrush(waterColor2);
        p->drawPath(waterPath2);

        p->setBrush(waterColor3);
        p->drawPath(waterPath3);

        p->setBrush(waterColor1);
        p->drawPath(waterPath1);
    }
    else
    {
        p->setPen(Qt::NoPen);
        p->setBrush(m_colorWater);
        p->drawRect(rcBase);
    }

    p->restore();

    if (m_bEnableSpace)
    {
        if (PLOTTYPE_CIRCULAR == m_ePlotType)
        {
            p->setPen(QPen(Qt::white,nOffset,Qt::SolidLine));
            p->drawEllipse(rcBase.adjusted(nOffset, nOffset, -nOffset, -nOffset));
        }
        else if (PLOTTYPE_RECTANGLE == m_ePlotType)
        {
            p->setPen(QPen(Qt::white,nOffset,Qt::SolidLine));
            p->drawRect(rcBase.adjusted(nOffset, nOffset, -nOffset, -nOffset));

            p->setPen(QPen(Qt::white,1,Qt::SolidLine));
            p->drawRect(rcBase.adjusted(5, 5, -5, -5));
        }
        else if (PLOTTYPE_DIAMOND == m_ePlotType)
        {
            QRect rcClip = rcBase.adjusted(nOffset, nOffset, -nOffset, -nOffset);
            QPolygon py;
            py << QPoint(rcClip.center().x(), rcClip.top()) << QPoint(rcClip.right(), rcClip.center().y())
                    << QPoint(rcClip.center().x(), rcClip.bottom())
                     << QPoint(rcClip.left(), rcClip.center().y());

            p->setPen(QPen(Qt::white,nOffset,Qt::SolidLine));
            p->drawPolygon(py);

            {
                QRect rcClip = rcBase.adjusted(5, 5, -5, -5);
                QPolygon py;
                py << QPoint(rcClip.center().x(), rcClip.top())
                   << QPoint(rcClip.right(), rcClip.center().y())
                        << QPoint(rcClip.center().x(), rcClip.bottom())
                         << QPoint(rcClip.left(), rcClip.center().y());

                p->setPen(QPen(Qt::white,1,Qt::SolidLine));
                p->drawPolygon(py);
            }
        }
    }

//    p->save();
//    QFont font1 = m_iconFont;
//    font1.setBold(true);
//    font1.setPixelSize(40);
//    p->setFont(font1);
//    p->setPen(QColor("#4A535C"));
//    p->drawText(QRect(0, 0, 350, 350), Qt::AlignCenter, QString("%1%").arg(m_nPercent));
//    p->restore();

    p->restore();
}

void LiquidPlot::timerEvent(QTimerEvent *event)
{
    if (m_nPercent < 100)
    {
        m_fOffset += (double)m_nSpeed / 100.0 * 20;
        update();
    }
}

void LiquidPlot::CreateAllChildWnd()
{

}

void LiquidPlot::InitCtrl()
{
    setProperty("LiquidPlot", "true");
    startTimer(60);

    int nFontId = QFontDatabase::addApplicationFont(":/res/ttf/led_board-7.ttf");
    QStringList strlistFontName = QFontDatabase::applicationFontFamilies(nFontId);

    if (strlistFontName.count() > 0)
    {
        m_iconFont = QFont(strlistFontName.at(0));
        m_iconFont.setStyleStrategy(QFont::PreferAntialias);
    }
}

void LiquidPlot::InitSolts()
{

}

void LiquidPlot::Relayout()
{

}
