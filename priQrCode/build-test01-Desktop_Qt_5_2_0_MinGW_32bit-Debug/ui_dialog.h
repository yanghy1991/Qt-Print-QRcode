/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *btn_sge;
    QPushButton *btn_dou;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(768, 436);
        Dialog->setSizeGripEnabled(false);
        btn_sge = new QPushButton(Dialog);
        btn_sge->setObjectName(QStringLiteral("btn_sge"));
        btn_sge->setGeometry(QRect(230, 60, 211, 61));
        btn_dou = new QPushButton(Dialog);
        btn_dou->setObjectName(QStringLiteral("btn_dou"));
        btn_dou->setGeometry(QRect(230, 180, 211, 61));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        btn_sge->setText(QApplication::translate("Dialog", "\345\215\225\344\270\252\346\211\223\345\215\260", 0));
        btn_dou->setText(QApplication::translate("Dialog", "\346\211\271\351\207\217\346\211\223\345\215\260", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
