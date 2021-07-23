#ifndef QTSYSTEMCFG_H
#define QTSYSTEMCFG_H

#include <QWidget>

namespace Ui {
class QtSystemCfg;
}

class QtSystemCfg : public QWidget
{
    Q_OBJECT

public:
    explicit QtSystemCfg(QWidget *parent = 0);
    ~QtSystemCfg();

private:
    Ui::QtSystemCfg *ui;
};

#endif // QTSYSTEMCFG_H
