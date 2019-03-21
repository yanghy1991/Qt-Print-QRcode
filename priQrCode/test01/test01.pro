#-------------------------------------------------
#
# Project created by QtCreator 2019-01-15T15:06:07
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test01
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    dialogsge.cpp \
    dialogdow.cpp \
    dialogmacsn.cpp

HEADERS  += dialog.h \
    connection.h \
    dialogsge.h \
    dialogdow.h \
    dialogmacsn.h

FORMS    += dialog.ui \
    dialogsge.ui \
    dialogdow.ui \
    dialogmacsn.ui

#LIBS    += -L D:\QT\yuan\test01\test01\libs\ -l Seagull.BarTender.Print
