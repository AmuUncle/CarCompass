#include "perfectclock.h"
#include <QPainter>
#include <QWheelEvent>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>


PerfectClock::PerfectClock(QWidget *parent)
    : QWidget(parent)
{
    m_bDarkMode = false;
    m_curTime = QTime::currentTime();

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();
}

PerfectClock::~PerfectClock()
{

}

void PerfectClock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);         // 创建画家对象
    QRect rcClient = rect();
    paintClock(&painter, rcClient.marginsRemoved(QMargins(10, 10, 10, 10)));
}

QRectF textRectF(double radius, int pointSize, double angle)
{
    QRectF rectF;
    rectF.setX(radius*qCos(angle*M_PI/180.0) - pointSize*2);
    rectF.setY(radius*qSin(angle*M_PI/180.0) - pointSize/2.0);
    rectF.setWidth(pointSize*4);
    rectF.setHeight(pointSize);
    return rectF;
}

void PerfectClock::paintClock(QPainter *p, QRect rcClock)
{
    p->save();

    p->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform | QPainter::Qt4CompatiblePainting);
    p->translate(rcClock.left() + rcClock.width() / 2, rcClock.top() + rcClock.height() / 2);

    int side = qMin(rcClock.width(), rcClock.height());
    p->scale(side / 600.0, side / 600.0);

    QRect rcBase(-300, -300, 600, 600);
    QFont font = p->font();

    QColor hourScaleColor("#63677A");
    QColor minuteScaleColor("#64687B");

    QColor hourColor("#A97F1C");
    QColor minuteColor("#C0911F");
    QColor secondColor("#7C5E14");

    QColor hourTextColor("#464646");

    QColor boderColor("#3A3A3A");
    QColor clockDialColor("#FFFFFF");
    QColor brandColor("#707177");

    QString strBrand = "H&Y";

    if (m_bDarkMode)
    {
        hourScaleColor = QColor("#63677A");
        minuteScaleColor = QColor("#616579");

        hourTextColor = QColor("#B9B8CE");

        boderColor = QColor("#04030A");
        clockDialColor = QColor("#100C2A");
        brandColor = QColor("#707177");
    }

    // 边框
    p->save();
    p->setPen(Qt::NoPen);
    p->setBrush(boderColor);
    p->drawEllipse(rcBase);
    p->setBrush(clockDialColor);
    p->drawEllipse(rcBase.marginsRemoved(QMargins(20, 20, 20, 20)));
    p->restore();

    // 品牌文字
    p->save();
    QFont font1 = m_iconFont;
    font1.setBold(true);
    font1.setPointSize(25);
    p->setFont(font1);
    p->setPen(brandColor);
    p->drawText(QRect(-300, -150, 600, 80), Qt::AlignCenter, strBrand);
    p->restore();

    // led时间
    p->save();
    font1 = m_iconFont;
    font1.setBold(true);
    font1.setPointSize(20);
    p->setFont(font1);
    p->setPen(brandColor);
    p->drawText(QRect(-300, 120, 600, 50), Qt::AlignCenter, m_curTime.toString("hh:mm:ss"));
    p->restore();

    // 秒-刻度
    p->save();
    p->setPen(minuteScaleColor);

    for (int i = 0; i < 60; ++i)
    {
        if ((i % 5) != 0)
            p->drawLine(270, 0, 275, 0);

        p->rotate(6.0);
    }
    p->restore();

    // 小时-刻度
    p->save();
    p->setPen(QPen(QBrush(hourScaleColor), 3, Qt::SolidLine));

    for (int i = 0; i < 12; ++i)
    {
        p->drawLine(265, 0, 275, 0);
        p->rotate(30.0);
    }
    p->restore();

    p->save();
    font.setBold(true);
    font.setPointSize(35);
    p->setFont(font);
    p->setPen(hourTextColor);

    // 绘制小时文本
    int nHour = 0;
    for (int i = 0; i < 12; ++i)
    {
        nHour = i + 3;
        if (nHour > 12)
            nHour -= 12;

        p->drawText(textRectF(290 * 0.8, font.pointSize() + 5, i * 30), Qt::AlignCenter, QString::number(nHour));
    }
    p->restore();

    // 时针
    p->save();
    p->setPen(Qt::NoPen);
    p->setBrush(hourColor);
    p->rotate(-90);
    p->rotate(30.0 * ((m_curTime.hour() + m_curTime.minute() / 60.0)));
    p->drawRoundRect(-30, -7, 160, 14, 6, 80);
    p->restore();

    // 时针-圆盘
    p->save();
    p->setPen(Qt::NoPen);
    p->setBrush(hourColor);
    p->drawEllipse(QPoint(0, 0), 20, 20);
    p->restore();

    // 分针
    p->save();
    p->setPen(Qt::NoPen);
    p->setBrush(minuteColor);
    p->rotate(-90);
    p->rotate(6.0 * (m_curTime.minute() + m_curTime.second() / 60.0));
    p->drawRoundRect(-30, -4, 200, 8, 3, 80);
    p->restore();

    // 秒针
    p->save();
    p->setPen(Qt::NoPen);
    p->setBrush(secondColor);
    p->rotate(-90);

    float fRotationAngle = this->property("RotationAngle").toFloat();
    fRotationAngle = qMax(fRotationAngle, (float)0.0);

    p->rotate((6.0 * (m_curTime.second() - 1)) + (6.0 * fRotationAngle));
    p->drawRoundRect(-30, -2, 240, 4, 40, 40);
    p->restore();

    // 秒针-圆盘
    p->save();
    p->setPen(Qt::NoPen);
    p->setBrush(secondColor);
    p->drawEllipse(QPoint(0, 0), 8, 8);
    p->restore();

    p->restore();

    return;
}

void PerfectClock::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    if (event->timerId() == m_nTimerId)
    {
        m_curTime = QTime::currentTime();
        m_pAnimationOpacity->stop();
        m_pAnimationOpacity->start();
        update();
    }
}

void PerfectClock::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }
}

void PerfectClock::InitCtrl()
{
    int nFontId = QFontDatabase::addApplicationFont(":/ttf/ttf/led_board-7.ttf");
    QStringList strlistFontName = QFontDatabase::applicationFontFamilies(nFontId);

    if (strlistFontName.count() > 0)
    {
        m_iconFont = QFont(strlistFontName.at(0));
        m_iconFont.setStyleStrategy(QFont::PreferAntialias);
    }

    // 添加ImageOpacity属性;
    this->setProperty("RotationAngle", 1.0);
    m_pAnimationOpacity = new QPropertyAnimation(this, "RotationAngle");
    m_pAnimationOpacity->setDuration(500);
    m_pAnimationOpacity->setEasingCurve(QEasingCurve::OutBack);  // 缓和曲线风格
    m_pAnimationOpacity->setStartValue(0.0);
    m_pAnimationOpacity->setEndValue(1.0);
    connect(m_pAnimationOpacity, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));

    m_nTimerId = startTimer(1000);
}

void PerfectClock::InitSolts()
{

}

void PerfectClock::Relayout()
{
}


////////////////////////
Clock::Clock(QWidget *parent)
{
    m_pPerfectClock = NULL;

    setProperty("canMove", "true");
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();
}

void Clock::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_pPerfectClock, PerfectClock);
}

void Clock::InitCtrl()
{
    setMouseTracking(true); // 设置窗体追踪鼠标
    setFixedSize(400, 400);

    // 设置边框阴影
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    // 设置具体阴影
    QGraphicsDropShadowEffect *shadowBorder = new QGraphicsDropShadowEffect(this);
    shadowBorder->setOffset(0, 0);
    // 阴影颜色
    shadowBorder->setColor(QColor(0x44, 0x44, 0x44, 127));
    // 阴影半径
    shadowBorder->setBlurRadius(30);
    setGraphicsEffect(shadowBorder);
}

void Clock::InitSolts()
{

}

void Clock::Relayout()
{
    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(m_pPerfectClock);
    layoutMain->setMargin(8);

    setLayout(layoutMain);
}

void Clock::mousePressEvent(QMouseEvent *event)
{
    m_pPerfectClock->EnableDrakMode(!m_pPerfectClock->IsDrakMode());
    update();
}

void Clock::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (windowFlags() & Qt::WindowStaysOnTopHint)
        setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
    else
        setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

    show();
}

void Clock::wheelEvent(QWheelEvent *event)
{
    int nSize = width();
    if(event->delta() > 0)
    {
        nSize += 100;
    }
    else
    {
        nSize -= 100;
    }

    nSize = qMin(nSize, 1080);
    nSize = qMax(nSize, 100);

    setFixedSize(nSize, nSize);
    move(event->globalPos().x() - nSize / 2, event->globalPos().y() - nSize / 2);

    update();
}
