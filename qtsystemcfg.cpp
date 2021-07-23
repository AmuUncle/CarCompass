#include "qtsystemcfg.h"
#include "ui_qtsystemcfg.h"

QtSystemCfg::QtSystemCfg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtSystemCfg)
{
    ui->setupUi(this);
}

QtSystemCfg::~QtSystemCfg()
{
    delete ui;
}
