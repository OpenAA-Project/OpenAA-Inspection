/********************************************************************************
** Form generated from reading UI file 'AddItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDITEMDIALOG_H
#define UI_ADDITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_AddItemDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBoxPeakCount;
    QDoubleSpinBox *doubleSpinBoxAngle;
    QSpinBox *spinBoxUsageLayer;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label_4;
    QLineEdit *lineEditItemName;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBoxAbandonRateL;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBoxAbandonRateH;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBoxPeakIsolation;

    void setupUi(QDialog *AddItemDialog)
    {
        if (AddItemDialog->objectName().isEmpty())
            AddItemDialog->setObjectName("AddItemDialog");
        AddItemDialog->resize(329, 284);
        label = new QLabel(AddItemDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 50, 101, 18));
        label_2 = new QLabel(AddItemDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 80, 101, 18));
        label_3 = new QLabel(AddItemDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 140, 111, 18));
        spinBoxPeakCount = new QSpinBox(AddItemDialog);
        spinBoxPeakCount->setObjectName("spinBoxPeakCount");
        spinBoxPeakCount->setGeometry(QRect(150, 50, 111, 24));
        doubleSpinBoxAngle = new QDoubleSpinBox(AddItemDialog);
        doubleSpinBoxAngle->setObjectName("doubleSpinBoxAngle");
        doubleSpinBoxAngle->setGeometry(QRect(150, 80, 111, 24));
        doubleSpinBoxAngle->setMaximum(360.000000000000000);
        spinBoxUsageLayer = new QSpinBox(AddItemDialog);
        spinBoxUsageLayer->setObjectName("spinBoxUsageLayer");
        spinBoxUsageLayer->setGeometry(QRect(150, 140, 111, 24));
        pushButtonOK = new QPushButton(AddItemDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 240, 112, 34));
        pushButtonCancel = new QPushButton(AddItemDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(190, 240, 112, 34));
        label_4 = new QLabel(AddItemDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 10, 101, 21));
        lineEditItemName = new QLineEdit(AddItemDialog);
        lineEditItemName->setObjectName("lineEditItemName");
        lineEditItemName->setGeometry(QRect(110, 10, 151, 24));
        label_5 = new QLabel(AddItemDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 170, 181, 18));
        doubleSpinBoxAbandonRateL = new QDoubleSpinBox(AddItemDialog);
        doubleSpinBoxAbandonRateL->setObjectName("doubleSpinBoxAbandonRateL");
        doubleSpinBoxAbandonRateL->setGeometry(QRect(200, 170, 111, 24));
        doubleSpinBoxAbandonRateL->setDecimals(3);
        doubleSpinBoxAbandonRateL->setMaximum(1.000000000000000);
        label_6 = new QLabel(AddItemDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 200, 181, 18));
        doubleSpinBoxAbandonRateH = new QDoubleSpinBox(AddItemDialog);
        doubleSpinBoxAbandonRateH->setObjectName("doubleSpinBoxAbandonRateH");
        doubleSpinBoxAbandonRateH->setGeometry(QRect(200, 200, 111, 24));
        doubleSpinBoxAbandonRateH->setDecimals(3);
        doubleSpinBoxAbandonRateH->setMaximum(1.000000000000000);
        label_7 = new QLabel(AddItemDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 110, 101, 18));
        doubleSpinBoxPeakIsolation = new QDoubleSpinBox(AddItemDialog);
        doubleSpinBoxPeakIsolation->setObjectName("doubleSpinBoxPeakIsolation");
        doubleSpinBoxPeakIsolation->setGeometry(QRect(150, 110, 111, 24));
        doubleSpinBoxPeakIsolation->setMaximum(360.000000000000000);

        retranslateUi(AddItemDialog);

        QMetaObject::connectSlotsByName(AddItemDialog);
    } // setupUi

    void retranslateUi(QDialog *AddItemDialog)
    {
        AddItemDialog->setWindowTitle(QCoreApplication::translate("AddItemDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AddItemDialog", "Peak count", nullptr));
        label_2->setText(QCoreApplication::translate("AddItemDialog", "Angle", nullptr));
        label_3->setText(QCoreApplication::translate("AddItemDialog", "Usage layer", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AddItemDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AddItemDialog", "Cancel", nullptr));
        label_4->setText(QCoreApplication::translate("AddItemDialog", "ItemName", nullptr));
        label_5->setText(QCoreApplication::translate("AddItemDialog", "Abandon rate Low", nullptr));
        label_6->setText(QCoreApplication::translate("AddItemDialog", "Abandon rate High", nullptr));
        label_7->setText(QCoreApplication::translate("AddItemDialog", "Peak Isolation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddItemDialog: public Ui_AddItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDITEMDIALOG_H
