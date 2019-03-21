#include "dialogsge.h"
#include "ui_dialogsge.h"
#include <QDebug>
#include <QProcess>
#include <QMessageBox>
#include <QTextBlock>
#include <QThread>

DialogSge::DialogSge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSge)
{
    ui->setupUi(this);
    ui->lineEdit->setMaxLength(19);
    ui->plainTextEdit->setReadOnly(true);
    oldSrt.clear();
}

DialogSge::~DialogSge()
{
    delete ui;
}

void DialogSge::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1.length() == 18 && arg1.mid(0,3).compare("SN:") == 0){
        if(arg1.compare(oldSrt) == 0){
            QMessageBox::warning(this, tr("警告"), tr("与上一次输入相同"));
        } else {
            oldSrt.clear();
            oldSrt = arg1;
            //qDebug() << "oldSrt:" << oldSrt;
            ui->plainTextEdit->appendPlainText(arg1);

            //打开文件
            QString mac = "\"" + arg1 + "\"";
            //qDebug() << "条码:" << mac;

            QFile file("D:/dxmf/条码.txt");
            if(!file.open(QIODevice::WriteOnly |  QFile::Truncate)){
                QMessageBox::warning(this, tr("警告"), tr("写MAC失败,请重新操作"));
            } else {

                QTextStream out(&file);
                out << mac;
                file.close();
                process.start("D:/dxmf/bartender.bat");
                qDebug() << "条码:" << mac  << "打印成功";
                QThread::msleep(200);
            }
        }
    } else if(arg1.length() == 19 && arg1.mid(0,3).compare("SN:") == 0){
         ui->lineEdit->setText(arg1.right(1));
    } else if(arg1.length() > 13 && arg1.mid(0,3).contains("SN:") == false ){
        ui->lineEdit->setText("");
        QMessageBox::warning(this, tr("警告"), tr("格式无效"));
    } else if(arg1.length() == 12 && arg1.mid(0,3).contains("SN:") == false){

        if(arg1.compare(oldSrt) == 0){
            QMessageBox::warning(this, tr("警告"), tr("与上一次输入相同"));
        } else {
            oldSrt.clear();
            oldSrt = arg1;
            //qDebug() << "oldSrt:" << oldSrt;
            ui->plainTextEdit->appendPlainText(arg1);

            //打开文件
            QString mac = "\"" + arg1 + "\"";
            //qDebug() << "条码:" << mac;

            QFile file("D:/dxmf/条码.txt");
            if(!file.open(QIODevice::WriteOnly |  QFile::Truncate)){
                QMessageBox::warning(this, tr("警告"), tr("写MAC失败,请重新操作"));
            } else {
                QTextStream out(&file);
                out << mac;
                file.close();
                process.start("D:/dxmf/bartender.bat");
                qDebug() << "条码:" << mac  << "打印成功";
                QThread::msleep(200);
            }
        }

     } else if(arg1.length() == 13 && arg1.mid(0,3).contains("SN:") == false ){
        ui->lineEdit->setText(arg1.right(1));
     } else if(arg1.length() == 0 ){
        oldSrt.clear();
     }

}
