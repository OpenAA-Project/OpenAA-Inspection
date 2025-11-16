/********************************************************************************
** Form generated from reading UI file 'AddItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDITEMDIALOG_H
#define UI_ADDITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddItemDialog
{
public:
    QLineEdit *lineEditAreaName;
    QLabel *label;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *AddItemDialog)
    {
        if (AddItemDialog->objectName().isEmpty())
            AddItemDialog->setObjectName(QString::fromUtf8("AddItemDialog"));
        AddItemDialog->resize(229, 116);
        lineEditAreaName = new QLineEdit(AddItemDialog);
        lineEditAreaName->setObjectName(QString::fromUtf8("lineEditAreaName"));
        lineEditAreaName->setGeometry(QRect(10, 30, 201, 20));
        label = new QLabel(AddItemDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 191, 16));
        pushButtonOK = new QPushButton(AddItemDialog);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(20, 70, 91, 31));
        pushButtonCancel = new QPushButton(AddItemDialog);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(120, 70, 91, 31));

        retranslateUi(AddItemDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(AddItemDialog);
    } // setupUi

    void retranslateUi(QDialog *AddItemDialog)
    {
        AddItemDialog->setWindowTitle(QCoreApplication::translate("AddItemDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AddItemDialog", "Area name", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AddItemDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AddItemDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddItemDialog: public Ui_AddItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDITEMDIALOG_H
