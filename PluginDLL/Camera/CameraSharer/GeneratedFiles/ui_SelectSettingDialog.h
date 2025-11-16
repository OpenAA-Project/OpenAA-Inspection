/********************************************************************************
** Form generated from reading UI file 'SelectSettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTSETTINGDIALOG_H
#define UI_SELECTSETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SelectSettingDialog
{
public:
    QLabel *label;
    QSpinBox *spinBoxCameraNo;
    QPushButton *pushButtonSetting;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *SelectSettingDialog)
    {
        if (SelectSettingDialog->objectName().isEmpty())
            SelectSettingDialog->setObjectName("SelectSettingDialog");
        SelectSettingDialog->resize(215, 112);
        label = new QLabel(SelectSettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 81, 16));
        spinBoxCameraNo = new QSpinBox(SelectSettingDialog);
        spinBoxCameraNo->setObjectName("spinBoxCameraNo");
        spinBoxCameraNo->setGeometry(QRect(10, 30, 71, 22));
        pushButtonSetting = new QPushButton(SelectSettingDialog);
        pushButtonSetting->setObjectName("pushButtonSetting");
        pushButtonSetting->setGeometry(QRect(110, 20, 91, 31));
        pushButtonClose = new QPushButton(SelectSettingDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(60, 70, 93, 28));

        retranslateUi(SelectSettingDialog);

        QMetaObject::connectSlotsByName(SelectSettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectSettingDialog)
    {
        SelectSettingDialog->setWindowTitle(QCoreApplication::translate("SelectSettingDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SelectSettingDialog", "Camera No", nullptr));
        pushButtonSetting->setText(QCoreApplication::translate("SelectSettingDialog", "Setting", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SelectSettingDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectSettingDialog: public Ui_SelectSettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTSETTINGDIALOG_H
