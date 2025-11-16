/********************************************************************************
** Form generated from reading UI file 'SelectPriorityInAreaDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTPRIORITYINAREADIALOG_H
#define UI_SELECTPRIORITYINAREADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_SelectPriorityInAreaDialog
{
public:
    QGroupBox *groupBox;
    QRadioButton *radioButtonPriorityHigh;
    QRadioButton *radioButtonPriorityMiddle;
    QRadioButton *radioButtonPriorityLow;
    QRadioButton *radioButtonPriorityLGlobal;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectPriorityInAreaDialog)
    {
        if (SelectPriorityInAreaDialog->objectName().isEmpty())
            SelectPriorityInAreaDialog->setObjectName("SelectPriorityInAreaDialog");
        SelectPriorityInAreaDialog->resize(398, 165);
        groupBox = new QGroupBox(SelectPriorityInAreaDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 0, 381, 111));
        radioButtonPriorityHigh = new QRadioButton(groupBox);
        radioButtonPriorityHigh->setObjectName("radioButtonPriorityHigh");
        radioButtonPriorityHigh->setGeometry(QRect(20, 40, 361, 17));
        radioButtonPriorityHigh->setChecked(false);
        radioButtonPriorityMiddle = new QRadioButton(groupBox);
        radioButtonPriorityMiddle->setObjectName("radioButtonPriorityMiddle");
        radioButtonPriorityMiddle->setGeometry(QRect(20, 60, 361, 17));
        radioButtonPriorityMiddle->setChecked(true);
        radioButtonPriorityLow = new QRadioButton(groupBox);
        radioButtonPriorityLow->setObjectName("radioButtonPriorityLow");
        radioButtonPriorityLow->setGeometry(QRect(20, 80, 361, 17));
        radioButtonPriorityLow->setChecked(false);
        radioButtonPriorityLGlobal = new QRadioButton(groupBox);
        radioButtonPriorityLGlobal->setObjectName("radioButtonPriorityLGlobal");
        radioButtonPriorityLGlobal->setGeometry(QRect(20, 20, 361, 17));
        radioButtonPriorityLGlobal->setChecked(false);
        pushButtonOK = new QPushButton(SelectPriorityInAreaDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(50, 120, 101, 31));
        pushButtonCancel = new QPushButton(SelectPriorityInAreaDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(250, 120, 101, 31));

        retranslateUi(SelectPriorityInAreaDialog);

        QMetaObject::connectSlotsByName(SelectPriorityInAreaDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectPriorityInAreaDialog)
    {
        SelectPriorityInAreaDialog->setWindowTitle(QCoreApplication::translate("SelectPriorityInAreaDialog", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SelectPriorityInAreaDialog", "Priority", nullptr));
        radioButtonPriorityHigh->setText(QCoreApplication::translate("SelectPriorityInAreaDialog", "High( Exp. BGA, special part)", nullptr));
        radioButtonPriorityMiddle->setText(QCoreApplication::translate("SelectPriorityInAreaDialog", "Middle (General)", nullptr));
        radioButtonPriorityLow->setText(QCoreApplication::translate("SelectPriorityInAreaDialog", "Low (Only parts fitting)", nullptr));
        radioButtonPriorityLGlobal->setText(QCoreApplication::translate("SelectPriorityInAreaDialog", "Global alignment (Only for other alignment)", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectPriorityInAreaDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectPriorityInAreaDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectPriorityInAreaDialog: public Ui_SelectPriorityInAreaDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTPRIORITYINAREADIALOG_H
