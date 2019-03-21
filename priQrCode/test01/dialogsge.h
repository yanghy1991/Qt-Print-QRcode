#ifndef DIALOGSGE_H
#define DIALOGSGE_H

#include <QDialog>
#include <QProcess>
#include <QString>
#include <QFileDevice>
#include <QFile>

namespace Ui {
class DialogSge;
}

class DialogSge : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSge(QWidget *parent = 0);
    ~DialogSge();

private slots:

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::DialogSge *ui;
    QProcess process;
    QString  oldSrt;

};

#endif // DIALOGSGE_H
