#include "incomingcall.h"
#include "ui_incomingcall.h"

IncomingCall::IncomingCall(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::IncomingCall)
{
    ui->setupUi(this);

    GLOBAL_FUNC_RUN
}

IncomingCall::~IncomingCall()
{
    delete ui;
}

void IncomingCall::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }
}

void IncomingCall::InitCtrl()
{
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "mainwnd");

    ui->pushButton_3->setProperty("return", "true");
    ui->pushButton->setProperty("HangUp", "true");
    ui->pushButton_2->setProperty("Answer", "true");

    ui->pushButton->setFixedSize(80, 80);
    ui->pushButton_2->setFixedSize(80, 80);
    IconHelper::SetIcon(ui->pushButton, QChar(0xe66c), 80);
    IconHelper::SetIcon(ui->pushButton_2, QChar(0xe63d), 80);
}

void IncomingCall::InitSolts()
{

}

void IncomingCall::Relayout()
{

}

void IncomingCall::on_pushButton_clicked()
{
    emit SignalClose();
}

void IncomingCall::on_pushButton_3_clicked()
{
    emit SignalClose();
}
