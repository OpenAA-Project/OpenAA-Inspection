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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QSpinBox *spinBoxBrightness;
    QToolButton *toolButtonOnOff;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(115, 138);
        spinBoxBrightness = new QSpinBox(SettingDialog);
        spinBoxBrightness->setObjectName("spinBoxBrightness");
        spinBoxBrightness->setGeometry(QRect(10, 20, 91, 22));
        spinBoxBrightness->setMaximum(255);
        toolButtonOnOff = new QToolButton(SettingDialog);
        toolButtonOnOff->setObjectName("toolButtonOnOff");
        toolButtonOnOff->setGeometry(QRect(10, 50, 91, 31));
        toolButtonOnOff->setCheckable(true);
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 92, 75, 31));

        retranslateUi(SettingDialog);

        pushButtonOK->setDefault(false);


        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Dialog", nullptr));
        toolButtonOnOff->setText(QCoreApplication::translate("SettingDialog", "ON/OFF", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
