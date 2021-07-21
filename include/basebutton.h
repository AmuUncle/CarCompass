#ifndef BASEBUTTON_H
#define BASEBUTTON_H

#include <QPushButton>

class BaseButton : public QWidget
{
    Q_OBJECT

public:
    explicit BaseButton(QWidget *parent = 0);

public:
    void SetIcon(QChar iconCode) { m_iconCode = iconCode; }
    void SetIconSize(int nSize) { m_nIconSize = nSize; }
    void setText(QString strText) { m_strText = strText; }
    void SetTextSize(int nSize) { m_nTextSize = nSize; }
    void ShowShadow(bool bShow) { m_bShowShadow = bShow; }

private:
    void paintEvent(QPaintEvent* event);//重写绘画事件
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void SignalClicked();

private:
    QChar m_iconCode;
    int m_nIconSize;
    QString m_strText;
    int m_nTextSize;
    bool m_bShowShadow;

    bool m_bEnter;
    bool m_bPress;
};

#endif // BASEBUTTON_H
