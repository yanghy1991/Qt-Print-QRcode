#include "dialog.h"
#include "ui_dialog.h"
#include "dialogsge.h"
#include "dialogdow.h"
#include "dialogmacsn.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_btn_sge_clicked()
{
    DialogSge sge;
    sge.setWindowTitle("单个打印");
    sge.exec();
}

void Dialog::on_btn_dou_clicked()
{
    Dialogdow dow;
    dow.setWindowTitle("批量打印");
    dow.exec();
}

void Dialog::on_btn_mac_sn_clicked()
{
    DialogMacSn  dlogMacSn;
    dlogMacSn.setWindowTitle("打印MAC和SN");
    dlogMacSn.exec();
}
