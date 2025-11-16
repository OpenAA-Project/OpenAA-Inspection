/********************************************************************************
** Form generated from reading UI file 'NoComponentDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOCOMPONENTDIALOG_H
#define UI_NOCOMPONENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NoComponentDialog
{
public:
    QPushButton *pushButtonOK;
    QListWidget *listWidget;

    void setupUi(QDialog *NoComponentDialog)
    {
        if (NoComponentDialog->objectName().isEmpty())
            NoComponentDialog->setObjectName("NoComponentDialog");
        NoComponentDialog->resize(411, 251);
        pushButtonOK = new QPushButton(NoComponentDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(150, 210, 112, 34));
        listWidget = new QListWidget(NoComponentDialog);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 0, 411, 192));

        retranslateUi(NoComponentDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(NoComponentDialog);
    } // setupUi

    void retranslateUi(QDialog *NoComponentDialog)
    {
        NoComponentDialog->setWindowTitle(QCoreApplication::translate("NoComponentDialog", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("NoComponentDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NoComponentDialog: public Ui_NoComponentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOCOMPONENTDIALOG_H
