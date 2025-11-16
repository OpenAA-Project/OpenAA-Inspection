/********************************************************************************
** Form generated from reading UI file 'SettingHResolutionDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGHRESOLUTIONDIALOG_H
#define UI_SETTINGHRESOLUTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingHResolutionDialog
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QDoubleSpinBox *doubleSpinBoxRate;
    QLabel *label;

    void setupUi(QDialog *SettingHResolutionDialog)
    {
        if (SettingHResolutionDialog->objectName().isEmpty())
            SettingHResolutionDialog->setObjectName("SettingHResolutionDialog");
        SettingHResolutionDialog->resize(189, 150);
        pushButtonOK = new QPushButton(SettingHResolutionDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 90, 71, 41));
        pushButtonCancel = new QPushButton(SettingHResolutionDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(100, 90, 71, 41));
        doubleSpinBoxRate = new QDoubleSpinBox(SettingHResolutionDialog);
        doubleSpinBoxRate->setObjectName("doubleSpinBoxRate");
        doubleSpinBoxRate->setGeometry(QRect(50, 40, 111, 22));
        doubleSpinBoxRate->setDecimals(5);
        doubleSpinBoxRate->setMaximum(99999999.000000000000000);
        doubleSpinBoxRate->setValue(1.000000000000000);
        label = new QLabel(SettingHResolutionDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 171, 21));

        retranslateUi(SettingHResolutionDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SettingHResolutionDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingHResolutionDialog)
    {
        SettingHResolutionDialog->setWindowTitle(QCoreApplication::translate("SettingHResolutionDialog", "Setting", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingHResolutionDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingHResolutionDialog", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("SettingHResolutionDialog", "Extension rate for Horizon", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingHResolutionDialog: public Ui_SettingHResolutionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGHRESOLUTIONDIALOG_H
