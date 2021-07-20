#ifndef BODERPANE_H
#define BODERPANE_H

#include <QWidget>
#include <QtWidgets>

class BoderPane : public QWidget
{
    Q_OBJECT
public:
    explicit BoderPane(QWidget *parent = nullptr);

public:
    void SetMainLayout(QLayout *layout);

protected:
    QWidget *centralWidget() const;

private:
    void InitMainCtrl();

private:
    QWidget *m_widgetMain;
};

#endif // BODERPANE_H
