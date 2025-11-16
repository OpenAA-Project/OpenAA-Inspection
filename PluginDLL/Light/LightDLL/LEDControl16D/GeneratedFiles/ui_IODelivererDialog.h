/********************************************************************************
** Form generated from reading UI file 'IODelivererDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IODELIVERERDIALOG_H
#define UI_IODELIVERERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_IODelivererDialog
{
public:
    QPushButton *pushButtonStart;

    void setupUi(QDialog *IODelivererDialog)
    {
        if (IODelivererDialog->objectName().isEmpty())
            IODelivererDialog->setObjectName("IODelivererDialog");
        IODelivererDialog->resize(174, 93);
        pushButtonStart = new QPushButton(IODelivererDialog);
        pushButtonStart->setObjectName("pushButtonStart");
        pushButtonStart->setGeometry(QRect(30, 30, 112, 34));
        pushButtonStart->setCheckable(true);
        pushButtonStart->setChecked(false);

        retranslateUi(IODelivererDialog);

        QMetaObject::connectSlotsByName(IODelivererDialog);
    } // setupUi

    void retranslateUi(QDialog *IODelivererDialog)
    {
        IODelivererDialog->setWindowTitle(QCoreApplication::translate("IODelivererDialog", "Dialog", nullptr));
        pushButtonStart->setText(QCoreApplication::translate("IODelivererDialog", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IODelivererDialog: public Ui_IODelivererDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IODELIVERERDIALOG_H
