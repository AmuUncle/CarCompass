#include "moviepicwidget.h"
#include <QPainter>

MoviePicWidget::MoviePicWidget(QWidget *parent) : QWidget(parent)
{
    m_nPicIndex = 0;
}

void MoviePicWidget::SetPicList(QList<QPixmap> picList)
{
    m_picList = picList;
}

void MoviePicWidget::Start(int interval)
{
    if (m_picList.size() <= 0)
        return;

    m_nPicIndex = 0;
    m_nTimerId = startTimer(50);
}

void MoviePicWidget::Stop()
{
    killTimer(m_nTimerId);
}

void MoviePicWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);         // 创建画家对象
    QRect rcClient = rect();
    painter.drawPixmap(rcClient, m_curPic);
}

void MoviePicWidget::timerEvent(QTimerEvent *event)
{
    if (m_nPicIndex < 0 || m_nPicIndex >= m_picList.size())
        m_nPicIndex = 0;

    if (m_picList.size() <= 0)
    {
        killTimer(m_nTimerId);
        return;
    }

    m_curPic = m_picList[m_nPicIndex].scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_nPicIndex++;

    update();
}
