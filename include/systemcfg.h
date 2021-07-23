#ifndef QTSYSTEMCFG_H
#define QTSYSTEMCFG_H

#include <QWidget>
#include "basewidget.h"
#include "global.h"

namespace Ui {
class QtSystemCfg;
}

class SystemCfg : public QWidget
{
    Q_OBJECT

public:
    explicit SystemCfg(QWidget *parent = 0);
    ~SystemCfg();

    struct CfgItem
    {
        QChar icon;
        QString strName;

        CfgItem(QChar _icon, QString _strName)
        {
            icon = _icon;
            strName = _strName;
        }
    };

private slots:
    void on_pushButton_clicked();

private:
    GLOBAL_FUNC

signals:
    void SignalClose();

private:
    Ui::QtSystemCfg *ui;

    QList<CfgItem> m_listCfg;
};

#endif // QTSYSTEMCFG_H
