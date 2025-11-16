/********************************************************************************
** Form generated from reading UI file 'SelectShareNoDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTSHARENODIALOG_H
#define UI_SELECTSHARENODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SelectShareNoDialog
{
public:
    QLabel *label;
    QSpinBox *spinBoxShareNo;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectShareNoDialog)
    {
        if (SelectShareNoDialog->objectName().isEmpty())
            SelectShareNoDialog->setObjectName("SelectShareNoDialog");
        SelectShareNoDialog->resize(228, 91);
        label = new QLabel(SelectShareNoDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 71, 16));
        spinBoxShareNo = new QSpinBox(SelectShareNoDialog);
        spinBoxShareNo->setObjectName("spinBoxShareNo");
        spinBoxShareNo->setGeometry(QRect(90, 10, 61, 22));
        pushButtonOK = new QPushButton(SelectShareNoDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 50, 93, 28));
        pushButtonCancel = new QPushButton(SelectShareNoDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 50, 93, 28));

        retranslateUi(SelectShareNoDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SelectShareNoDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectShareNoDialog)
    {
        SelectShareNoDialog->setWindowTitle(QCoreApplication::translate("SelectShareNoDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SelectShareNoDialog", "Share No", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectShareNoDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectShareNoDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectShareNoDialog: public Ui_SelectShareNoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTSHARENODIALOG_H
