#ifndef DROPDOWNBOX_H
#define DROPDOWNBOX_H

#include <QWidget>

namespace Ui {
class DropdownBox;
}

class DropdownBox : public QWidget
{
    Q_OBJECT

public:
    explicit DropdownBox(QWidget *parent = 0);
    ~DropdownBox();

signals:
    void SignalClose();

private slots:
    void on_m_btnClose_clicked();

private:
    Ui::DropdownBox *ui;
};

#endif // DROPDOWNBOX_H
