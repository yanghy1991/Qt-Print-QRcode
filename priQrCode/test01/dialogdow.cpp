#include "dialogdow.h"
#include "ui_dialogdow.h"
#include <QDebug>
#include <QTextBlock>
#include <QMessageBox>
#include <QThread>

Dialogdow::Dialogdow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogdow)
{
    ui->setupUi(this);
    //mac 数量
    ui->lineEdit->setReadOnly(true);
    //mac edit
    ui->plainTextEdit->setReadOnly(true);\
    // sn edit
    ui->plainTextEdit_SN->setReadOnly(true);
    //sn 数量
    ui->lineEdit_SNsum->setReadOnly(true);
    //箱号
    ui->lineEdit_box->setValidator(new QIntValidator(0, 10000, this));
    //上一次输入的条码
    oldSrt.clear();
}

Dialogdow::~Dialogdow()
{
    delete ui;
}

void Dialogdow::on_priBtn_clicked()
{
    int macLine = ui->lineEdit->text().toInt(0,10);
    int snLine = ui->lineEdit_SNsum->text().toInt(0,10);

    if(ui->lineEdit_name->text().length() == 0){
            QMessageBox::warning(this, tr("警告"), tr("请输入产品名称"));
            return;
    } if(ui->lineEdit_mode->text().length() == 0){
        QMessageBox::warning(this, tr("警告"), tr("请输入型号"));
        return;
    } else if(ui->lineEdit_color->text().length() == 0){
        QMessageBox::warning(this, tr("警告"), tr("请输入颜色"));
        return;
    } else if(ui->lineEdit_box->text().length() == 0){
        QMessageBox::warning(this, tr("警告"), tr("请输入箱号"));
        return;
    } else if(ui->lineEdit_po->text().length() == 0){
        QMessageBox::warning(this, tr("警告"), tr("请输入PO"));
        return;
    } else if(macLine != 20 || snLine != 20){
        QMessageBox::warning(this, tr("警告"), tr("录入的MAC或SN少于20"));
        return;
    }

    //打开文件
    priInfo.clear();
    priInfo_SN_MAC.clear();
    //获取产品名称
    priInfo = "\"" + ui->lineEdit_name->text() + "\",";
    //获取型号
    priInfo += "\"" + ui->lineEdit_mode->text() + "\",";
    //获取颜色
    priInfo += "\"" + ui->lineEdit_color->text() + "\",";
    //获取数量
    priInfo += "\"" + ui->lineEdit->text() + "pcs\",";
    //获取箱号
    priInfo += "\"" + ui->lineEdit_box->text() + "\",";
    //获取PO
    priInfo += "\"" + ui->lineEdit_po->text() + "\",";

    //获取20个MAC
    for(int i = 0;i<macLine;i++){
         priInfo += "\"" + ui->plainTextEdit->document()->findBlockByLineNumber(i).text() + "\",";
    }

    //获取20个SN
    for(int i = 0;i<snLine;i++){
         priInfo += "\"" + ui->plainTextEdit_SN->document()->findBlockByLineNumber(i).text() + "\",";
    }

    //生成二维码信息
    for(int i = 0;i<snLine;i++){
         priInfo_SN_MAC += QString::number(i+1) + " " + ui->plainTextEdit_SN->document()->findBlockByLineNumber(i).text() + ",MAC:" + ui->plainTextEdit->document()->findBlockByLineNumber(i).text() + ";";
    }

    priInfo += "\"" + priInfo_SN_MAC + "\",";

    QFile file("D:/dxmf/批量INFO.txt");
    if(!file.open(QIODevice::WriteOnly |  QFile::Truncate)){
        QMessageBox::warning(this, tr("警告"), tr("写MAC失败,请重新操作"));
    } else {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << priInfo;
        file.close();
        process.start("D:/dxmf/bartenderInfo.bat");
        //qDebug() << "priInfo:" << priInfo  << "打印成功";
        QThread::msleep(200);
    }
}

void Dialogdow::on_clearBtn_clicked()
{
    ui->plainTextEdit->clear();
    ui->lineEdit->clear();
}

void Dialogdow::on_clearBtn_SN_clicked()
{
    ui->plainTextEdit_SN->clear();
    ui->lineEdit_SNsum->clear();
}

void Dialogdow::on_plainTextEdit_textChanged()
{
    //获取行号
    lineCnt = ui->plainTextEdit->document()->lineCount();

    if(lineCnt > 20){
        ui->lineEdit->setText(QString::number(lineCnt-1));
        QMessageBox::warning(this, tr("警告"), tr("已输入20行，请打印"));
        return ;
    }

    //获取最后一行
    plnStr = ui->plainTextEdit->document()->findBlockByLineNumber(lineCnt-1).text();
    qDebug() << "plainTextEdit: " << plnStr << "plnLen: " << plnStr.length() << "lineCnt: " << lineCnt;

    if(lineCnt > 0 && plnStr.length() == 12){
         //判断新输入的mac是否重复 录入
        if(lineCnt > 1){
            QString checkMac;
            for(int i = 0;i<= lineCnt-2;i++){
               checkMac  = ui->plainTextEdit->document()->findBlockByLineNumber(i).text();
               if(checkMac.compare(plnStr) == 0){
                   QMessageBox::warning(this, tr("警告"), tr("请不要重复录入MAC"));
                   tc = ui->plainTextEdit->textCursor();
                   tc.select(QTextCursor::BlockUnderCursor);
                   tc.removeSelectedText();
                   return;
               }
            }
        }

         ui->lineEdit->setText(QString::number(lineCnt));
    } else if(plnStr.length() > 12){
        tc = ui->plainTextEdit->textCursor();
        tc.select(QTextCursor::BlockUnderCursor);
        tc.removeSelectedText();
        QMessageBox::warning(this, tr("警告"), tr("MAC格式无效"));
   }
}

void Dialogdow::on_plainTextEdit_SN_textChanged()
{
    //获取行号
    lineCnt = ui->plainTextEdit_SN->document()->lineCount();

    if(lineCnt > 20){
        ui->lineEdit_SNsum->setText(QString::number(lineCnt-1));
        QMessageBox::warning(this, tr("警告"), tr("已输入20行，请打印"));
        return ;
    }
    //获取最后一行
    plnStr = ui->plainTextEdit_SN->document()->findBlockByLineNumber(lineCnt-1).text();
    qDebug() << "plainTextEdit: " << plnStr << "plnLen: " << plnStr.length() << "lineCnt: " << lineCnt;

    if(lineCnt > 0 && plnStr.length() == 18 && plnStr.mid(0,3).compare("SN:") == 0){
       //判断新输入的mac是否重复 录入
       if(lineCnt > 1){
           QString checkMac;
           for(int i = 0;i<= lineCnt-2;i++){
              checkMac  = ui->plainTextEdit_SN->document()->findBlockByLineNumber(i).text();
              if(checkMac.compare(plnStr) == 0){
                  QMessageBox::warning(this, tr("警告"), tr("请不要重复录入MAC"));
                  tc = ui->plainTextEdit_SN->textCursor();
                  tc.select(QTextCursor::BlockUnderCursor);
                  tc.removeSelectedText();
                  return;
              }
           }
       }

        ui->lineEdit_SNsum->setText(QString::number(lineCnt));
   } else if(plnStr.length() > 4 && plnStr.mid(0,3).contains("SN:") == false){
        tc = ui->plainTextEdit_SN->textCursor();
        tc.select(QTextCursor::BlockUnderCursor);
        tc.removeSelectedText();
        QMessageBox::warning(this, tr("警告"), tr("SN格式无效"));
   }
}

void Dialogdow::on_lineEdit_input_textChanged(const QString &arg1)
{
    if(arg1.length() == 18 && arg1.mid(0,3).compare("SN:") == 0){
        oldSrt = arg1;
        if(ui->plainTextEdit_SN->document()->lineCount() < 20){
            ui->plainTextEdit_SN->appendPlainText(arg1);
        } else {
            QMessageBox::warning(this, tr("警告"), tr("录入的SN码已达到20个"));
        }

    } else if(arg1.length() == 19 && arg1.mid(0,3).compare("SN:") == 0){
         ui->lineEdit_input->setText(arg1.right(1));
    } else if(arg1.length() > 13 && arg1.mid(0,3).contains("SN:") == false ){
        ui->lineEdit_input->setText("");
        QMessageBox::warning(this, tr("警告"), tr("格式无效"));
    } else if(arg1.length() == 12 && arg1.mid(0,3).contains("SN:") == false){

        oldSrt = arg1;
        if(ui->plainTextEdit->document()->lineCount() < 20){
             ui->plainTextEdit->appendPlainText(arg1);
        } else {
            QMessageBox::warning(this, tr("警告"), tr("录入的MAC码已达到20个"));
        }

     } else if(arg1.length() == 13 && arg1.mid(0,3).contains("SN:") == false ){
        ui->lineEdit_input->setText(arg1.right(1));
     } else if(arg1.length() == 0 ){
        oldSrt.clear();
     }
}
