#include "dialogmacsn.h"
#include "ui_dialogmacsn.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QThread>
#include <QDateTime>

DialogMacSn::DialogMacSn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMacSn)
{
    ui->setupUi(this);
    ui->maclineEdit->setMaxLength(13);
    ui->snlineEdit->setMaxLength(19);
    ui->snNumlineEdit->setFocus();
    ui->snNumlineEdit->setValidator(new QIntValidator(0, 100, this));
    snNum = 0;
}

DialogMacSn::~DialogMacSn()
{
    delete ui;
}

void DialogMacSn::on_sigradioButton_clicked()
{
    if(ui->snNumlineEdit->text().length() == 0){
            QMessageBox::warning(this, tr("警告"), tr("请输入产品SN长度"));
            return;

    } else if(ui->maclineEdit->text().length() != 12){
            QMessageBox::warning(this, tr("警告"), tr("请输入产品MAC"));
            ui->sigradioButton->setCheckable(false);
            ui->sigradioButton->setChecked(false);
            ui->sigradioButton->setCheckable(true);
            return;
    } else if(ui->snlineEdit->text().length() != snNum || ui->snlineEdit->text().contains("SN:") == false){
            QMessageBox::warning(this, tr("警告"), tr("请输入产品SN"));
            ui->sigradioButton->setCheckable(false);
            ui->sigradioButton->setChecked(false);
            ui->sigradioButton->setCheckable(true);
            return;
    }

    //打开文件
    priInfo.clear();
    //获取mac
    priInfo = "\"" + ui->maclineEdit->text() + "\",";
    //获取sn
    priInfo += "\"" + ui->snlineEdit->text() + "\",";
    //获取时间
    QDateTime current_time = QDateTime::currentDateTime();
    QString StrCurrentTime = current_time.toString("yyyy-MM-dd");
    priInfo += "\"" + StrCurrentTime + "\"";

    qDebug() << "mac和sn:" << priInfo;

    QFile file("D:/dxmf/MAC和SN.txt");
    if(!file.open(QIODevice::WriteOnly |  QFile::Truncate)){
        QMessageBox::warning(this, tr("警告"), tr("打开文件失败,请重新操作"));
    } else {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << priInfo;
        file.close();
        process.start("D:/dxmf/bartenderMacSn.bat");
        qDebug() << "priInfo:" << priInfo  << "打印成功";
        QThread::msleep(200);
    }
    ui->plainTextEdit->appendPlainText(priInfo);

    ui->sigradioButton->setCheckable(false);
    ui->sigradioButton->setChecked(false);
    ui->sigradioButton->setCheckable(true);
}

void DialogMacSn::on_autoradioButton_clicked()
{
#if 1
    if(ui->snNumlineEdit->text().length() == 0){
            QMessageBox::warning(this, tr("警告"), tr("请输入产品SN长度"));
            ui->autoradioButton->setCheckable(false);
            ui->autoradioButton->setChecked(false);
            ui->autoradioButton->setCheckable(true);
            return;

    } else if(ui->snlineEdit->text().length() != snNum || ui->snlineEdit->text().contains("SN:") == false){
            QMessageBox::warning(this, tr("警告"), tr("产品SN格式无效"));
            ui->autoradioButton->setCheckable(false);
            ui->autoradioButton->setChecked(false);
            ui->autoradioButton->setCheckable(true);
            return;
    }
#endif
}

void DialogMacSn::on_maclineEdit_textChanged(const QString &arg1)
{
    if(arg1.length() > 13 || arg1.contains("SN:") == true){
        ui->maclineEdit->setText("");
        QMessageBox::warning(this, tr("警告"), tr("MAC格式无效"));
    } else if(arg1.length() == 12){

        if(arg1.compare(oldSrt) == 0){
            QMessageBox::warning(this, tr("警告"), tr("与上一次输入相同"));
        } else {
            if(ui->autoradioButton->isChecked()){

                if(ui->snlineEdit->text().length() != snNum || ui->snlineEdit->text().contains("SN:") == false){
                        QMessageBox::warning(this, tr("警告"), tr("产品SN格式无效"));
                        ui->autoradioButton->setCheckable(false);
                        ui->autoradioButton->setChecked(false);
                        ui->autoradioButton->setCheckable(true);
                    return;
                }

                oldSrt.clear();
                oldSrt = arg1;
                //qDebug() << "oldSrt:" << oldSrt;
                //ui->plainTextEdit->appendPlainText(arg1);

                //打开文件
                priInfo.clear();
                //获取mac
                priInfo = "\"" + ui->maclineEdit->text() + "\",";
                //获取sn
                priInfo += "\"" + ui->snlineEdit->text() + "\",";
                //获取时间
                QDateTime current_time = QDateTime::currentDateTime();
                QString StrCurrentTime = current_time.toString("yyyy-MM-dd");
                priInfo += "\"" + StrCurrentTime + "\"";

                qDebug() << "mac和sn:" << priInfo;

                QFile file("D:/dxmf/MAC和SN.txt");
                if(!file.open(QIODevice::WriteOnly |  QFile::Truncate)){
                    QMessageBox::warning(this, tr("警告"), tr("打开文件失败,请重新操作"));
                } else {
                    QTextStream out(&file);
                    out.setCodec("UTF-8");
                    out << priInfo;
                    file.close();
                    process.start("D:/dxmf/bartenderMacSn.bat");
                    qDebug() << "priInfo:" << priInfo  << "打印成功";
                    QThread::msleep(200);
                }

                ui->plainTextEdit->appendPlainText(priInfo);
                //sn码自动累加
                QString snStr = "";
                int snNum = ui->snlineEdit->text().right(5).toInt();

                snStr  = ui->snlineEdit->text().left(14);
                snStr += QString("%1").arg(snNum+1, 5, 10, QLatin1Char('0'));
                ui->snlineEdit->setText(snStr);
            }

        }

     } else if(arg1.length() == 13 ){
        ui->maclineEdit->setText(arg1.right(1));
     } else if(arg1.length() == 0 ){
        oldSrt.clear();
     }
}

void DialogMacSn::on_snNumlineEdit_textChanged(const QString &arg1)
{

    snNum = arg1.toInt();
}
