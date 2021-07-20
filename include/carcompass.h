#ifndef CARCOMPASS_H
#define CARCOMPASS_H

#include <QWidget>
#include "global.h"

class MainWnd;
class DropdownBox;
class CarCompass : public QWidget
{
    Q_OBJECT

public:
    CarCompass(QWidget *parent = 0);
    ~CarCompass();

private:
    GLOBAL_FUNC
    void ChangePage();

    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    QStackedWidget *m_pStackedWidget;
    MainWnd *m_pMainWnd;
    DropdownBox *m_pDropdownBox;
    EMainTabTitle m_eMainTabTitle;
};

#endif // CARCOMPASS_H
