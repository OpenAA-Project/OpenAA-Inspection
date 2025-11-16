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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxStrength;
    QDoubleSpinBox *doubleSpinBoxWidth;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(291, 191);
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 130, 91, 31));
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(180, 130, 91, 31));
        label_3 = new QLabel(SettingDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 70, 211, 41));
        label_2 = new QLabel(SettingDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 40, 50, 20));
        label = new QLabel(SettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 13, 50, 20));
        doubleSpinBoxStrength = new QDoubleSpinBox(SettingDialog);
        doubleSpinBoxStrength->setObjectName("doubleSpinBoxStrength");
        doubleSpinBoxStrength->setGeometry(QRect(110, 10, 91, 22));
        doubleSpinBoxStrength->setDecimals(4);
        doubleSpinBoxWidth = new QDoubleSpinBox(SettingDialog);
        doubleSpinBoxWidth->setObjectName("doubleSpinBoxWidth");
        doubleSpinBoxWidth->setGeometry(QRect(110, 40, 91, 22));
        doubleSpinBoxWidth->setDecimals(4);
        doubleSpinBoxWidth->setMinimum(-0.500000000000000);
        doubleSpinBoxWidth->setMaximum(0.500000000000000);
        doubleSpinBoxWidth->setSingleStep(0.100000000000000);
        doubleSpinBoxWidth->setValue(0.160000000000000);

        retranslateUi(SettingDialog);

        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Setting", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingDialog", "Cancel", nullptr));
        label_3->setText(QCoreApplication::translate("SettingDialog", "Width:0-0.25   Normally 0.16", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "Width", nullptr));
        label->setText(QCoreApplication::translate("SettingDialog", "Strength", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
