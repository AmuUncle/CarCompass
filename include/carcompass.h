#ifndef CARCOMPASS_H
#define CARCOMPASS_H

#include <QWidget>
#include "global.h"

class DropdownBox;
class CarCompass : public QWidget
{
    Q_OBJECT

public:
    CarCompass(QWidget *parent = 0);
    ~CarCompass();

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitSolts();
    void Relayout();
    void ChangePage();

    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    QStackedWidget *m_pStackedWidget;

    QWidget *m_pWidgetMain;
    DropdownBox *m_pDropdownBox;
    EMainTabTitle m_eMainTabTitle;
};

#endif // CARCOMPASS_H
