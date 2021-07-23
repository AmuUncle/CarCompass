#ifndef MOVIEPICWIDGET_H
#define MOVIEPICWIDGET_H

#include <QWidget>
#include <QList>
#include <QPixmap>

class MoviePicWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MoviePicWidget(QWidget *parent = 0);

public:
    void SetPicList(QList<QPixmap> picList);
    void Start(int interval);
    void Stop();

private:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);

private:
    QList<QPixmap> m_picList;
    int m_nPicIndex;
    QPixmap m_curPic;
    int m_nTimerId;
};

#endif // MOVIEPICWIDGET_H
