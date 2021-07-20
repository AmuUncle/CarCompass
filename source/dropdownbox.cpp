#include "dropdownbox.h"
#include "ui_dropdownbox.h"

DropdownBox::DropdownBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DropdownBox)
{
    ui->setupUi(this);

    IconHelper::SetIcon(ui->m_btnClose, QChar(0xe631));
    IconHelper::SetIcon(ui->label, QChar(0xe676), 43);
    IconHelper::SetIcon(ui->label_2, QChar(0xe6cf), 40);
    IconHelper::SetIcon(ui->label_3, QChar(0xe615), 40);
    IconHelper::SetIcon(ui->label_4, QChar(0xe9fa), 40);

    ui->pushButton_2->setText(tr("移动数据"));
    ui->pushButton_3->setText(tr("WLAN"));
    ui->pushButton_4->setText(tr("蓝牙"));
    ui->pushButton_5->setText(tr("FM"));
    ui->pushButton_6->setText(tr("GPS"));
    ui->pushButton_7->setText(tr("雷达"));
    ui->pushButton_9->setText(tr("电子狗"));
    ui->pushButton_8->setText(tr("帮助"));

    ui->pushButton_2->SetIcon(QChar(0xe642));
    ui->pushButton_3->SetIcon(QChar(0xe6d7));
    ui->pushButton_4->SetIcon(QChar(0xe790));
    ui->pushButton_5->SetIcon(QChar(0xe65a));
    ui->pushButton_6->SetIcon(QChar(0xe647));
    ui->pushButton_7->SetIcon(QChar(0xe630));
    ui->pushButton_9->SetIcon(QChar(0xe65d));
    ui->pushButton_8->SetIcon(QChar(0xe6aa));

    ui->pushButton_2->SetIconSize(50);
    ui->pushButton_3->SetIconSize(50);
    ui->pushButton_4->SetIconSize(50);
    ui->pushButton_5->SetIconSize(50);
    ui->pushButton_6->SetIconSize(50);
    ui->pushButton_7->SetIconSize(50);
    ui->pushButton_8->SetIconSize(50);
    ui->pushButton_9->SetIconSize(50);

    ui->pushButton_2->SetTextSize(16);
    ui->pushButton_3->SetTextSize(16);
    ui->pushButton_4->SetTextSize(16);
    ui->pushButton_5->SetTextSize(16);
    ui->pushButton_6->SetTextSize(16);
    ui->pushButton_7->SetTextSize(16);
    ui->pushButton_8->SetTextSize(16);
    ui->pushButton_9->SetTextSize(16);

    ui->horizontalSlider->setValue(50);
    ui->horizontalSlider_2->setValue(80);
}

DropdownBox::~DropdownBox()
{
    delete ui;
}

void DropdownBox::on_m_btnClose_clicked()
{
    emit SignalClose();
}
