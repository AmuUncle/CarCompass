#include "musicpane.h"
#include "ui_musicpane.h"

MusicPane::MusicPane(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::MusicPane)
{
    ui->setupUi(this);

    GLOBAL_FUNC_RUN
}

MusicPane::~MusicPane()
{
    delete ui;
}

void MusicPane::paintEvent(QPaintEvent *event)
{
    BaseWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, true); // 抗锯齿和使用平滑转换算法

    QRect rcImg(ui->label->rect());
    rcImg.setTopLeft(mapToParent(ui->label->pos()));
    rcImg.setHeight(ui->label->height());
    rcImg.setWidth(ui->label->width());

    QImage img(":/img/cd.png");
    img = img.mirrored();
    QImage p = img.scaled(rcImg.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    rcImg.setTop(rcImg.top() + 2 + rcImg.height());
    rcImg.setBottom(rcImg.top() + 25);

    painter.setOpacity(0.2);
    painter.drawImage(rcImg, p);

}

void MusicPane::on_pushButton_3_clicked()
{
    emit SignalClose();
}

void MusicPane::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }
}

void MusicPane::InitCtrl()
{
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "mainwnd");

    ui->pushButton_3->setProperty("return", "true");

    QImage* img = new QImage;
    img->load(QString(":/img/cd.png"));
    QImage scaledimg;
    scaledimg = img->scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(QPixmap::fromImage(scaledimg));

    ui->horizontalSlider->setValue(30);

    IconHelper::SetIcon(ui->pushButton, QChar(0xe677), 50);
    IconHelper::SetIcon(ui->pushButton_2, QChar(0xe612), 50);
    IconHelper::SetIcon(ui->pushButton_4, QChar(0xe678), 50);
}

void MusicPane::InitSolts()
{

}

void MusicPane::Relayout()
{

}
