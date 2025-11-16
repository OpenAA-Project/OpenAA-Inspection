/********************************************************************************
** Form generated from reading UI file 'InputEchingFactorDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTECHINGFACTORDIALOG_H
#define UI_INPUTECHINGFACTORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputEchingFactorDialog
{
public:
    QDoubleSpinBox *doubleSpinBoxCornerR;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *InputEchingFactorDialog)
    {
        if (InputEchingFactorDialog->objectName().isEmpty())
            InputEchingFactorDialog->setObjectName("InputEchingFactorDialog");
        InputEchingFactorDialog->resize(220, 127);
        doubleSpinBoxCornerR = new QDoubleSpinBox(InputEchingFactorDialog);
        doubleSpinBoxCornerR->setObjectName("doubleSpinBoxCornerR");
        doubleSpinBoxCornerR->setGeometry(QRect(50, 40, 91, 31));
        doubleSpinBoxCornerR->setMaximum(99999999.000000000000000);
        doubleSpinBoxCornerR->setValue(5.000000000000000);
        label = new QLabel(InputEchingFactorDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 10, 141, 16));
        label_2 = new QLabel(InputEchingFactorDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(150, 50, 62, 15));
        pushButtonOK = new QPushButton(InputEchingFactorDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 90, 93, 28));
        pushButtonCancel = new QPushButton(InputEchingFactorDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 90, 93, 28));

        retranslateUi(InputEchingFactorDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(InputEchingFactorDialog);
    } // setupUi

    void retranslateUi(QDialog *InputEchingFactorDialog)
    {
        InputEchingFactorDialog->setWindowTitle(QCoreApplication::translate("InputEchingFactorDialog", "Input eching factor", nullptr));
        label->setText(QCoreApplication::translate("InputEchingFactorDialog", "Radius in corner", nullptr));
        label_2->setText(QCoreApplication::translate("InputEchingFactorDialog", "Pixels", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputEchingFactorDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputEchingFactorDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputEchingFactorDialog: public Ui_InputEchingFactorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTECHINGFACTORDIALOG_H
