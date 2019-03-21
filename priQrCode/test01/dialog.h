#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "dialogsge.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_btn_sge_clicked();

    void on_btn_dou_clicked();

    void on_btn_mac_sn_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
