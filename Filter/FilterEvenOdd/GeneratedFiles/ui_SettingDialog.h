/********************************************************************************
** Form generated from reading UI file 'SettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QGroupBox *groupBox;
    QDoubleSpinBox *doubleSpinBoxLeftOdd;
    QDoubleSpinBox *doubleSpinBoxLeftEven;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox_2;
    QDoubleSpinBox *doubleSpinBoxRightOdd;
    QDoubleSpinBox *doubleSpinBoxRightEven;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(287, 163);
        groupBox = new QGroupBox(SettingDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 10, 120, 91));
        doubleSpinBoxLeftOdd = new QDoubleSpinBox(groupBox);
        doubleSpinBoxLeftOdd->setObjectName("doubleSpinBoxLeftOdd");
        doubleSpinBoxLeftOdd->setGeometry(QRect(50, 60, 62, 22));
        doubleSpinBoxLeftOdd->setMaximum(1000.000000000000000);
        doubleSpinBoxLeftOdd->setSingleStep(0.100000000000000);
        doubleSpinBoxLeftOdd->setValue(1.000000000000000);
        doubleSpinBoxLeftEven = new QDoubleSpinBox(groupBox);
        doubleSpinBoxLeftEven->setObjectName("doubleSpinBoxLeftEven");
        doubleSpinBoxLeftEven->setGeometry(QRect(50, 30, 62, 22));
        doubleSpinBoxLeftEven->setMaximum(1000.000000000000000);
        doubleSpinBoxLeftEven->setSingleStep(0.100000000000000);
        doubleSpinBoxLeftEven->setValue(1.000000000000000);
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 31, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 60, 31, 16));
        groupBox_2 = new QGroupBox(SettingDialog);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(150, 10, 120, 91));
        doubleSpinBoxRightOdd = new QDoubleSpinBox(groupBox_2);
        doubleSpinBoxRightOdd->setObjectName("doubleSpinBoxRightOdd");
        doubleSpinBoxRightOdd->setGeometry(QRect(50, 60, 62, 22));
        doubleSpinBoxRightOdd->setMaximum(1000.000000000000000);
        doubleSpinBoxRightOdd->setSingleStep(0.100000000000000);
        doubleSpinBoxRightOdd->setValue(1.000000000000000);
        doubleSpinBoxRightEven = new QDoubleSpinBox(groupBox_2);
        doubleSpinBoxRightEven->setObjectName("doubleSpinBoxRightEven");
        doubleSpinBoxRightEven->setGeometry(QRect(50, 30, 62, 22));
        doubleSpinBoxRightEven->setMaximum(1000.000000000000000);
        doubleSpinBoxRightEven->setSingleStep(0.100000000000000);
        doubleSpinBoxRightEven->setValue(1.000000000000000);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 30, 31, 16));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 60, 31, 16));
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(60, 120, 75, 31));
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(160, 120, 75, 31));

        retranslateUi(SettingDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Setting", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SettingDialog", "Left side", nullptr));
        label->setText(QCoreApplication::translate("SettingDialog", "Even", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "Odd", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SettingDialog", "Right side", nullptr));
        label_3->setText(QCoreApplication::translate("SettingDialog", "Even", nullptr));
        label_4->setText(QCoreApplication::translate("SettingDialog", "Odd", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
