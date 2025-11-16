/********************************************************************************
** Form generated from reading UI file 'SettingKoreaST8ChDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGKOREAST8CHDIALOG_H
#define UI_SETTINGKOREAST8CHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SettingKoreaST8ChDialog
{
public:
    QListWidget *listWidgetCH;
    QToolButton *toolButtonLightON;
    QSpinBox *spinBoxLightValue;
    QPushButton *pushButtonTransmit;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *SettingKoreaST8ChDialog)
    {
        if (SettingKoreaST8ChDialog->objectName().isEmpty())
            SettingKoreaST8ChDialog->setObjectName("SettingKoreaST8ChDialog");
        SettingKoreaST8ChDialog->resize(244, 243);
        listWidgetCH = new QListWidget(SettingKoreaST8ChDialog);
        listWidgetCH->setObjectName("listWidgetCH");
        listWidgetCH->setGeometry(QRect(10, 10, 91, 151));
        toolButtonLightON = new QToolButton(SettingKoreaST8ChDialog);
        toolButtonLightON->setObjectName("toolButtonLightON");
        toolButtonLightON->setGeometry(QRect(110, 20, 121, 41));
        toolButtonLightON->setCheckable(true);
        spinBoxLightValue = new QSpinBox(SettingKoreaST8ChDialog);
        spinBoxLightValue->setObjectName("spinBoxLightValue");
        spinBoxLightValue->setGeometry(QRect(110, 70, 121, 31));
        spinBoxLightValue->setMaximum(255);
        pushButtonTransmit = new QPushButton(SettingKoreaST8ChDialog);
        pushButtonTransmit->setObjectName("pushButtonTransmit");
        pushButtonTransmit->setGeometry(QRect(110, 120, 121, 41));
        pushButtonClose = new QPushButton(SettingKoreaST8ChDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(70, 190, 101, 41));

        retranslateUi(SettingKoreaST8ChDialog);

        QMetaObject::connectSlotsByName(SettingKoreaST8ChDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingKoreaST8ChDialog)
    {
        SettingKoreaST8ChDialog->setWindowTitle(QCoreApplication::translate("SettingKoreaST8ChDialog", "Dialog", nullptr));
        toolButtonLightON->setText(QCoreApplication::translate("SettingKoreaST8ChDialog", "ON", nullptr));
        pushButtonTransmit->setText(QCoreApplication::translate("SettingKoreaST8ChDialog", "Transmit", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SettingKoreaST8ChDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingKoreaST8ChDialog: public Ui_SettingKoreaST8ChDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGKOREAST8CHDIALOG_H
