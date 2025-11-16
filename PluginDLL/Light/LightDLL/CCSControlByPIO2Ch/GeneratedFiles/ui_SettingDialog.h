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
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QSpinBox *spinBoxBrightness1;
    QToolButton *toolButtonOnOff1;
    QPushButton *pushButtonOK;
    QSpinBox *spinBoxBrightness2;
    QToolButton *toolButtonOnOff2;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(223, 143);
        spinBoxBrightness1 = new QSpinBox(SettingDialog);
        spinBoxBrightness1->setObjectName("spinBoxBrightness1");
        spinBoxBrightness1->setGeometry(QRect(10, 28, 91, 22));
        spinBoxBrightness1->setMaximum(255);
        toolButtonOnOff1 = new QToolButton(SettingDialog);
        toolButtonOnOff1->setObjectName("toolButtonOnOff1");
        toolButtonOnOff1->setGeometry(QRect(10, 58, 91, 31));
        toolButtonOnOff1->setCheckable(true);
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 98, 75, 31));
        spinBoxBrightness2 = new QSpinBox(SettingDialog);
        spinBoxBrightness2->setObjectName("spinBoxBrightness2");
        spinBoxBrightness2->setGeometry(QRect(120, 28, 91, 22));
        spinBoxBrightness2->setMaximum(255);
        toolButtonOnOff2 = new QToolButton(SettingDialog);
        toolButtonOnOff2->setObjectName("toolButtonOnOff2");
        toolButtonOnOff2->setGeometry(QRect(120, 58, 91, 31));
        toolButtonOnOff2->setCheckable(true);
        label = new QLabel(SettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 91, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(SettingDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(120, 10, 91, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(SettingDialog);

        pushButtonOK->setDefault(false);


        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Dialog", nullptr));
        toolButtonOnOff1->setText(QCoreApplication::translate("SettingDialog", "ON/OFF", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        toolButtonOnOff2->setText(QCoreApplication::translate("SettingDialog", "ON/OFF", nullptr));
        label->setText(QCoreApplication::translate("SettingDialog", "Ch1", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "Ch2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
