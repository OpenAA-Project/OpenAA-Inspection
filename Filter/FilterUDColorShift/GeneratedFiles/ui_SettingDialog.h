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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBoxShiftR;
    QSpinBox *spinBoxShiftG;
    QSpinBox *spinBoxShiftB;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxTimeRange;
    QLabel *label_4;
    QCheckBox *checkBoxCheckTime;
    QSpinBox *spinBoxShiftOffset;
    QLabel *label_5;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(162, 252);
        label = new QLabel(SettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 50, 21));
        label_2 = new QLabel(SettingDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 50, 50, 21));
        label_3 = new QLabel(SettingDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 80, 50, 21));
        spinBoxShiftR = new QSpinBox(SettingDialog);
        spinBoxShiftR->setObjectName("spinBoxShiftR");
        spinBoxShiftR->setGeometry(QRect(80, 20, 61, 22));
        spinBoxShiftR->setMinimum(-2000);
        spinBoxShiftR->setMaximum(2000);
        spinBoxShiftG = new QSpinBox(SettingDialog);
        spinBoxShiftG->setObjectName("spinBoxShiftG");
        spinBoxShiftG->setGeometry(QRect(80, 50, 61, 22));
        spinBoxShiftG->setMinimum(-2000);
        spinBoxShiftG->setMaximum(2000);
        spinBoxShiftB = new QSpinBox(SettingDialog);
        spinBoxShiftB->setObjectName("spinBoxShiftB");
        spinBoxShiftB->setGeometry(QRect(80, 80, 61, 22));
        spinBoxShiftB->setMinimum(-2000);
        spinBoxShiftB->setMaximum(2000);
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 210, 61, 31));
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(80, 210, 61, 31));
        spinBoxTimeRange = new QSpinBox(SettingDialog);
        spinBoxTimeRange->setObjectName("spinBoxTimeRange");
        spinBoxTimeRange->setGeometry(QRect(90, 130, 61, 22));
        spinBoxTimeRange->setMinimum(0);
        spinBoxTimeRange->setMaximum(10000);
        label_4 = new QLabel(SettingDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 130, 81, 21));
        checkBoxCheckTime = new QCheckBox(SettingDialog);
        checkBoxCheckTime->setObjectName("checkBoxCheckTime");
        checkBoxCheckTime->setGeometry(QRect(10, 110, 81, 18));
        spinBoxShiftOffset = new QSpinBox(SettingDialog);
        spinBoxShiftOffset->setObjectName("spinBoxShiftOffset");
        spinBoxShiftOffset->setGeometry(QRect(90, 160, 61, 22));
        spinBoxShiftOffset->setMinimum(-10000);
        spinBoxShiftOffset->setMaximum(10000);
        label_5 = new QLabel(SettingDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 160, 61, 21));

        retranslateUi(SettingDialog);

        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Setting UDColor shift", nullptr));
        label->setText(QCoreApplication::translate("SettingDialog", "Shift-R", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "Shift-G", nullptr));
        label_3->setText(QCoreApplication::translate("SettingDialog", "Shift-B", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingDialog", "Cancel", nullptr));
        label_4->setText(QCoreApplication::translate("SettingDialog", "TimeRange Sec", nullptr));
        checkBoxCheckTime->setText(QCoreApplication::translate("SettingDialog", "CheckTime", nullptr));
        label_5->setText(QCoreApplication::translate("SettingDialog", "Shift offset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
