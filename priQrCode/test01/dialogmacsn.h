#ifndef DIALOGMACSN_H
#define DIALOGMACSN_H

#include <QDialog>
#include <QString>
#include <QProcess>

namespace Ui {
class DialogMacSn;
}

class DialogMacSn : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMacSn(QWidget *parent = 0);
    ~DialogMacSn();

private slots:
    void on_sigradioButton_clicked();

    void on_autoradioButton_clicked();

    void on_maclineEdit_textChanged(const QString &arg1);

    void on_snNumlineEdit_textChanged(const QString &arg1);

private:
    Ui::DialogMacSn *ui;
    QString priInfo;
    QString  oldSrt;
    QProcess process;
    int snNum;
};

#endif // DIALOGMACSN_H
