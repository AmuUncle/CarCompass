#include "systemcfg.h"
#include "ui_qtsystemcfg.h"
#include "standbypane.h"

SystemCfg::SystemCfg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtSystemCfg)
{
    ui->setupUi(this);

    GLOBAL_FUNC_RUN
}

SystemCfg::~SystemCfg()
{
    delete ui;
}

void SystemCfg::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }
}

void SystemCfg::InitCtrl()
{
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "SystemCfg");

    ui->pushButton->setProperty("return", "true");

    ui->widget_2->setFixedWidth(250);

    m_listCfg << CfgItem(QChar(0xe60d), tr("WLAN设置"))
                 << CfgItem(QChar(0xe74a), tr("蓝牙设置"))
                    << CfgItem(QChar(0xe61f), tr("FM设置"))
                       << CfgItem(QChar(0xe60b), tr("流量使用情况"))
                          << CfgItem(QChar(0xe6c6), tr("屏幕保护"))
                             << CfgItem(QChar(0xe6d9), tr("时间日期"))
                                //<< CfgItem(QChar(0xe6ca), tr("系统升级"))
                                   << CfgItem(QChar(0xe607), tr("关于设备"));

    foreach (CfgItem var, m_listCfg)
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(10, 50));
        ui->listWidget->addItem(item);

        QWidget *pItemWidget = new QWidget(ui->listWidget);
        QLabel *pLabelIcon = new QLabel(pItemWidget);
        QLabel *pLabelName = new QLabel(var.strName, pItemWidget);
        pLabelIcon->setProperty("cfgicon", "true");
        pLabelName->setProperty("cfgname", "true");

        IconHelper::SetIcon(pLabelIcon, var.icon, 20);

        QHBoxLayout *layoutMain = new QHBoxLayout(pItemWidget);
        layoutMain->addWidget(pLabelIcon);
        layoutMain->addWidget(pLabelName);
        layoutMain->addStretch();
        layoutMain->setContentsMargins(15, 0, 0, 0);
        ui->listWidget->setItemWidget(item, pItemWidget);
    }

    for(int i = ui->stackedWidget->count(); i >= 0; i--)
    {
         QWidget *widget = ui->stackedWidget->widget(i);
         ui->stackedWidget->removeWidget(widget);
         widget->deleteLater();
    }

    ui->stackedWidget->insertWidget(0, new StandbyPane(this));
    ui->stackedWidget->setCurrentIndex(0);

    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏横向滚动条
    ui->scrollArea->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setStyleSheet(".QScrollArea{border-style:none;background:none}");
}

void SystemCfg::InitSolts()
{

}

void SystemCfg::Relayout()
{

}

void SystemCfg::on_pushButton_clicked()
{
    emit SignalClose();
}
