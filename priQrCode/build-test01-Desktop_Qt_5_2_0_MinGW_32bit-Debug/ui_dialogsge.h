/********************************************************************************
** Form generated from reading UI file 'dialogsge.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSGE_H
#define UI_DIALOGSGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_DialogSge
{
public:
    QLineEdit *lineEdit;
    QLabel *label;
    QPlainTextEdit *plainTextEdit;
    QLabel *label_2;

    void setupUi(QDialog *DialogSge)
    {
        if (DialogSge->objectName().isEmpty())
            DialogSge->setObjectName(QStringLiteral("DialogSge"));
        DialogSge->resize(751, 433);
        lineEdit = new QLineEdit(DialogSge);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(190, 40, 371, 41));
        label = new QLabel(DialogSge);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 30, 51, 61));
        QFont font;
        font.setFamily(QStringLiteral("Aharoni"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        plainTextEdit = new QPlainTextEdit(DialogSge);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(190, 120, 371, 201));
        label_2 = new QLabel(DialogSge);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(70, 100, 111, 61));
        QFont font1;
        font1.setFamily(QStringLiteral("Aharoni"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);

        retranslateUi(DialogSge);

        QMetaObject::connectSlotsByName(DialogSge);
    } // setupUi

    void retranslateUi(QDialog *DialogSge)
    {
        DialogSge->setWindowTitle(QApplication::translate("DialogSge", "Dialog", 0));
        label->setText(QApplication::translate("DialogSge", "\346\240\207\347\255\276\357\274\232", 0));
        label_2->setText(QApplication::translate("DialogSge", "\347\255\211\345\276\205\346\211\223\345\215\260\345\210\227\350\241\250\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogSge: public Ui_DialogSge {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSGE_H
