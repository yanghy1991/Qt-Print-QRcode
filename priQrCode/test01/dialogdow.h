#ifndef DIALOGDOW_H
#define DIALOGDOW_H

#include <QDialog>
#include <QString>
#include <QTextCursor>
#include <QProcess>

namespace Ui {
class Dialogdow;
}

class Dialogdow : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogdow(QWidget *parent = 0);
    ~Dialogdow();

private slots:
    void on_priBtn_clicked();

    void on_clearBtn_clicked();

    void on_plainTextEdit_textChanged();

    void on_plainTextEdit_SN_textChanged();

    void on_clearBtn_SN_clicked();

    void on_lineEdit_input_textChanged(const QString &arg1);

private:
    Ui::Dialogdow *ui;
    QString plnStr;
    int lineCnt;
    QTextCursor tc;
    QString priInfo;
    QString priInfo_SN_MAC;
    QProcess process;
    QString  oldSrt;
};

#endif // DIALOGDOW_H
