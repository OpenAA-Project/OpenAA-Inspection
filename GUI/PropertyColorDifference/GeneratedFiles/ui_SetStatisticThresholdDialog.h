/********************************************************************************
** Form generated from reading UI file 'SetStatisticThresholdDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETSTATISTICTHRESHOLDDIALOG_H
#define UI_SETSTATISTICTHRESHOLDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetStatisticThresholdDialog
{
public:
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxSigmaH;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxSigmaS;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBoxSigmaV;
    QPushButton *pushButtonSet;
    QLabel *label_4;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SetStatisticThresholdDialog)
    {
        if (SetStatisticThresholdDialog->objectName().isEmpty())
            SetStatisticThresholdDialog->setObjectName("SetStatisticThresholdDialog");
        SetStatisticThresholdDialog->resize(231, 261);
        label = new QLabel(SetStatisticThresholdDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 75, 31));
        doubleSpinBoxSigmaH = new QDoubleSpinBox(SetStatisticThresholdDialog);
        doubleSpinBoxSigmaH->setObjectName("doubleSpinBoxSigmaH");
        doubleSpinBoxSigmaH->setGeometry(QRect(100, 10, 101, 31));
        doubleSpinBoxSigmaH->setDecimals(4);
        doubleSpinBoxSigmaH->setValue(3.000000000000000);
        label_2 = new QLabel(SetStatisticThresholdDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 50, 75, 31));
        doubleSpinBoxSigmaS = new QDoubleSpinBox(SetStatisticThresholdDialog);
        doubleSpinBoxSigmaS->setObjectName("doubleSpinBoxSigmaS");
        doubleSpinBoxSigmaS->setGeometry(QRect(100, 50, 101, 31));
        doubleSpinBoxSigmaS->setDecimals(4);
        doubleSpinBoxSigmaS->setValue(3.000000000000000);
        label_3 = new QLabel(SetStatisticThresholdDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 90, 75, 31));
        doubleSpinBoxSigmaV = new QDoubleSpinBox(SetStatisticThresholdDialog);
        doubleSpinBoxSigmaV->setObjectName("doubleSpinBoxSigmaV");
        doubleSpinBoxSigmaV->setGeometry(QRect(100, 90, 101, 31));
        doubleSpinBoxSigmaV->setDecimals(4);
        doubleSpinBoxSigmaV->setValue(3.000000000000000);
        pushButtonSet = new QPushButton(SetStatisticThresholdDialog);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(10, 210, 101, 34));
        label_4 = new QLabel(SetStatisticThresholdDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 130, 211, 71));
        label_4->setWordWrap(true);
        pushButtonCancel = new QPushButton(SetStatisticThresholdDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 210, 101, 34));

        retranslateUi(SetStatisticThresholdDialog);

        pushButtonSet->setDefault(true);


        QMetaObject::connectSlotsByName(SetStatisticThresholdDialog);
    } // setupUi

    void retranslateUi(QDialog *SetStatisticThresholdDialog)
    {
        SetStatisticThresholdDialog->setWindowTitle(QCoreApplication::translate("SetStatisticThresholdDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SetStatisticThresholdDialog", "H-\343\202\267\343\202\260\343\203\236", nullptr));
        label_2->setText(QCoreApplication::translate("SetStatisticThresholdDialog", "S-\343\202\267\343\202\260\343\203\236", nullptr));
        label_3->setText(QCoreApplication::translate("SetStatisticThresholdDialog", "V-\343\202\267\343\202\260\343\203\236", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("SetStatisticThresholdDialog", "\350\250\255\345\256\232", nullptr));
        label_4->setText(QCoreApplication::translate("SetStatisticThresholdDialog", "\351\201\270\346\212\236\343\201\227\343\201\237Item\351\240\230\345\237\237\343\201\256\343\201\227\343\201\215\343\201\204\345\200\244\343\202\222\346\265\201\345\213\225\347\231\273\351\214\262\343\203\207\343\203\274\343\202\277\343\201\256\347\265\261\350\250\210\345\200\244\343\201\247\350\207\252\345\213\225\350\250\255\345\256\232\343\201\227\343\201\276\343\201\231", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SetStatisticThresholdDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetStatisticThresholdDialog: public Ui_SetStatisticThresholdDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETSTATISTICTHRESHOLDDIALOG_H
