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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBox;
    QToolButton *toolButtonON;
    QComboBox *comboBoxLEDNumber;
    QLabel *label;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(180, 158);
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 110, 75, 31));
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(100, 110, 75, 31));
        spinBox = new QSpinBox(SettingDialog);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(10, 60, 71, 22));
        spinBox->setMaximum(255);
        spinBox->setValue(255);
        toolButtonON = new QToolButton(SettingDialog);
        toolButtonON->setObjectName("toolButtonON");
        toolButtonON->setGeometry(QRect(100, 50, 71, 41));
        toolButtonON->setCheckable(true);
        comboBoxLEDNumber = new QComboBox(SettingDialog);
        comboBoxLEDNumber->addItem(QString());
        comboBoxLEDNumber->addItem(QString());
        comboBoxLEDNumber->addItem(QString());
        comboBoxLEDNumber->addItem(QString());
        comboBoxLEDNumber->addItem(QString());
        comboBoxLEDNumber->addItem(QString());
        comboBoxLEDNumber->addItem(QString());
        comboBoxLEDNumber->addItem(QString());
        comboBoxLEDNumber->addItem(QString());
        comboBoxLEDNumber->addItem(QString());
        comboBoxLEDNumber->addItem(QString());
        comboBoxLEDNumber->addItem(QString());
        comboBoxLEDNumber->addItem(QString());
        comboBoxLEDNumber->addItem(QString());
        comboBoxLEDNumber->addItem(QString());
        comboBoxLEDNumber->addItem(QString());
        comboBoxLEDNumber->setObjectName("comboBoxLEDNumber");
        comboBoxLEDNumber->setGeometry(QRect(100, 10, 74, 22));
        label = new QLabel(SettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 81, 16));

        retranslateUi(SettingDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingDialog", "Cancel", nullptr));
        toolButtonON->setText(QCoreApplication::translate("SettingDialog", "ON", nullptr));
        comboBoxLEDNumber->setItemText(0, QCoreApplication::translate("SettingDialog", "0", nullptr));
        comboBoxLEDNumber->setItemText(1, QCoreApplication::translate("SettingDialog", "1", nullptr));
        comboBoxLEDNumber->setItemText(2, QCoreApplication::translate("SettingDialog", "2", nullptr));
        comboBoxLEDNumber->setItemText(3, QCoreApplication::translate("SettingDialog", "3", nullptr));
        comboBoxLEDNumber->setItemText(4, QCoreApplication::translate("SettingDialog", "4", nullptr));
        comboBoxLEDNumber->setItemText(5, QCoreApplication::translate("SettingDialog", "5", nullptr));
        comboBoxLEDNumber->setItemText(6, QCoreApplication::translate("SettingDialog", "6", nullptr));
        comboBoxLEDNumber->setItemText(7, QCoreApplication::translate("SettingDialog", "7", nullptr));
        comboBoxLEDNumber->setItemText(8, QCoreApplication::translate("SettingDialog", "8", nullptr));
        comboBoxLEDNumber->setItemText(9, QCoreApplication::translate("SettingDialog", "9", nullptr));
        comboBoxLEDNumber->setItemText(10, QCoreApplication::translate("SettingDialog", "10", nullptr));
        comboBoxLEDNumber->setItemText(11, QCoreApplication::translate("SettingDialog", "11", nullptr));
        comboBoxLEDNumber->setItemText(12, QCoreApplication::translate("SettingDialog", "12", nullptr));
        comboBoxLEDNumber->setItemText(13, QCoreApplication::translate("SettingDialog", "13", nullptr));
        comboBoxLEDNumber->setItemText(14, QCoreApplication::translate("SettingDialog", "14", nullptr));
        comboBoxLEDNumber->setItemText(15, QCoreApplication::translate("SettingDialog", "15", nullptr));

        label->setText(QCoreApplication::translate("SettingDialog", "LED number", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
