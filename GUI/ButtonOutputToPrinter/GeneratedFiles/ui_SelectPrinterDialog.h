/********************************************************************************
** Form generated from reading UI file 'SelectPrinterDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTPRINTERDIALOG_H
#define UI_SELECTPRINTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectPrinterDialog
{
public:
    QPushButton *pushButtonPrinter1;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectPrinterDialog)
    {
        if (SelectPrinterDialog->objectName().isEmpty())
            SelectPrinterDialog->setObjectName("SelectPrinterDialog");
        SelectPrinterDialog->resize(211, 119);
        pushButtonPrinter1 = new QPushButton(SelectPrinterDialog);
        pushButtonPrinter1->setObjectName("pushButtonPrinter1");
        pushButtonPrinter1->setGeometry(QRect(10, 10, 191, 41));
        pushButtonCancel = new QPushButton(SelectPrinterDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(50, 70, 112, 34));

        retranslateUi(SelectPrinterDialog);

        QMetaObject::connectSlotsByName(SelectPrinterDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectPrinterDialog)
    {
        SelectPrinterDialog->setWindowTitle(QCoreApplication::translate("SelectPrinterDialog", "Select printer", nullptr));
        pushButtonPrinter1->setText(QCoreApplication::translate("SelectPrinterDialog", "Printer 1", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectPrinterDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectPrinterDialog: public Ui_SelectPrinterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTPRINTERDIALOG_H
