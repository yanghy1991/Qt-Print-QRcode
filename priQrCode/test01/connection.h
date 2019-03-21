#ifndef CONNECTION_H
#define CONNECTION_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection()
{
    qDebug("#####################");

	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setDatabaseName("bngomac");       //这里输入你的数据库名
	db.setUserName("root");
	db.setPassword("");   //这里输入你的密码
	if (!db.open()) {
        qDebug("Failed to connect to root mysql root");
		return false;
    } else {
         qDebug("open success!");
    }

	//下面来创建表
	// 如果 MySQL 数据库中已经存在同名的表， 那么下面的代码不会执行
	QSqlQuery query(db);


	// 创建 bngoMac 表
    query.exec("insert into bngomac.mac values('MAC:80CF2D5758F')");
   // query.exec("insert into bngoMac values('MAC:80CF2D5758F')");
   // query.exec("insert into bngoMac values('MAC:80CF2D5758F')");
    db.close();//关闭数据库
    qDebug("insert success!");
	return true;
} 
#endif // CONNECTION_H
