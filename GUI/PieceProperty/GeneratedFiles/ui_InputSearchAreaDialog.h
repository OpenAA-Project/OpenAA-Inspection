/********************************************************************************
** Form generated from reading UI file 'InputSearchAreaDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTSEARCHAREADIALOG_H
#define UI_INPUTSEARCHAREADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_InputSearchAreaDialog
{
public:
    QSpinBox *spinBoxSearchDot;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label;

    void setupUi(QDialog *InputSearchAreaDialog)
    {
        if (InputSearchAreaDialog->objectName().isEmpty())
            InputSearchAreaDialog->setObjectName("InputSearchAreaDialog");
        InputSearchAreaDialog->resize(229, 109);
        spinBoxSearchDot = new QSpinBox(InputSearchAreaDialog);
        spinBoxSearchDot->setObjectName("spinBoxSearchDot");
        spinBoxSearchDot->setGeometry(QRect(30, 10, 101, 31));
        spinBoxSearchDot->setMaximum(99999);
        pushButtonOK = new QPushButton(InputSearchAreaDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 60, 91, 34));
        pushButtonCancel = new QPushButton(InputSearchAreaDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 60, 91, 34));
        label = new QLabel(InputSearchAreaDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(140, 20, 61, 18));

        retranslateUi(InputSearchAreaDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(InputSearchAreaDialog);
    } // setupUi

    void retranslateUi(QDialog *InputSearchAreaDialog)
    {
        InputSearchAreaDialog->setWindowTitle(QCoreApplication::translate("InputSearchAreaDialog", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputSearchAreaDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputSearchAreaDialog", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("InputSearchAreaDialog", "Pixels", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputSearchAreaDialog: public Ui_InputSearchAreaDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTSEARCHAREADIALOG_H
