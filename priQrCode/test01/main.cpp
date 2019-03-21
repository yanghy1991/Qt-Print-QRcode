#include "dialog.h"
#include <QApplication>
#include "connection.h"
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle(QStyleFactory::create("fusion"));

    //QProcess process;
    //process.start("D:/dxmf/bartender.bat");

    Dialog w;
    w.setWindowTitle("自动打印程序");
    w.show();
    return a.exec();
}
