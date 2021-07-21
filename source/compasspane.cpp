#include "compasspane.h"
#include "ui_compasspane.h"

CompassPane::CompassPane(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::CompassPane)
{
    ui->setupUi(this);

    GLOBAL_FUNC_RUN
}

CompassPane::~CompassPane()
{
    delete ui;
}

void CompassPane::resizeEvent(QResizeEvent *event)
{
    QImage* img = new QImage;
    img->load(QString(":/img/compass.png"));
    QImage scaledimg;
    scaledimg = img->scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    ui->label->setPixmap(QPixmap::fromImage(scaledimg));
}

void CompassPane::on_pushButton_clicked()
{
    emit SignalClose();
}

void CompassPane::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }
}

void CompassPane::InitCtrl()
{
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式

    ui->pushButton->setProperty("return", "true");
}

void CompassPane::InitSolts()
{

}

void CompassPane::Relayout()
{

}
