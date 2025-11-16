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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QSpinBox *spinBoxCameraNo;
    QLabel *label;
    QPushButton *pushButtonSetting;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(185, 96);
        spinBoxCameraNo = new QSpinBox(SettingDialog);
        spinBoxCameraNo->setObjectName("spinBoxCameraNo");
        spinBoxCameraNo->setGeometry(QRect(90, 10, 81, 22));
        label = new QLabel(SettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 81, 21));
        pushButtonSetting = new QPushButton(SettingDialog);
        pushButtonSetting->setObjectName("pushButtonSetting");
        pushButtonSetting->setGeometry(QRect(10, 50, 81, 28));
        pushButtonClose = new QPushButton(SettingDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(102, 50, 71, 28));

        retranslateUi(SettingDialog);

        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SettingDialog", "Camera No", nullptr));
        pushButtonSetting->setText(QCoreApplication::translate("SettingDialog", "Setting", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SettingDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
