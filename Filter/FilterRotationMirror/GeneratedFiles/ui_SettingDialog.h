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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QToolButton *toolButtonMirrorUpDown;
    QToolButton *toolButtonMirrorLeftRight;
    QGroupBox *groupBox;
    QRadioButton *radioButtonRot0;
    QRadioButton *radioButtonRot90;
    QRadioButton *radioButtonRot180;
    QRadioButton *radioButtonRot270;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(187, 300);
        toolButtonMirrorUpDown = new QToolButton(SettingDialog);
        toolButtonMirrorUpDown->setObjectName("toolButtonMirrorUpDown");
        toolButtonMirrorUpDown->setGeometry(QRect(10, 20, 171, 31));
        toolButtonMirrorUpDown->setCheckable(true);
        toolButtonMirrorLeftRight = new QToolButton(SettingDialog);
        toolButtonMirrorLeftRight->setObjectName("toolButtonMirrorLeftRight");
        toolButtonMirrorLeftRight->setGeometry(QRect(10, 60, 171, 31));
        toolButtonMirrorLeftRight->setCheckable(true);
        groupBox = new QGroupBox(SettingDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 100, 151, 121));
        radioButtonRot0 = new QRadioButton(groupBox);
        radioButtonRot0->setObjectName("radioButtonRot0");
        radioButtonRot0->setGeometry(QRect(20, 20, 86, 17));
        radioButtonRot0->setChecked(true);
        radioButtonRot90 = new QRadioButton(groupBox);
        radioButtonRot90->setObjectName("radioButtonRot90");
        radioButtonRot90->setGeometry(QRect(20, 40, 86, 17));
        radioButtonRot180 = new QRadioButton(groupBox);
        radioButtonRot180->setObjectName("radioButtonRot180");
        radioButtonRot180->setGeometry(QRect(20, 60, 86, 17));
        radioButtonRot270 = new QRadioButton(groupBox);
        radioButtonRot270->setObjectName("radioButtonRot270");
        radioButtonRot270->setGeometry(QRect(20, 80, 86, 17));
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 250, 75, 31));
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(100, 250, 75, 31));

        retranslateUi(SettingDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Setting RotationMirror", nullptr));
        toolButtonMirrorUpDown->setText(QCoreApplication::translate("SettingDialog", "Upside Down", nullptr));
        toolButtonMirrorLeftRight->setText(QCoreApplication::translate("SettingDialog", "Left-Right", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SettingDialog", "RotationAngle", nullptr));
        radioButtonRot0->setText(QCoreApplication::translate("SettingDialog", "0 Degree", nullptr));
        radioButtonRot90->setText(QCoreApplication::translate("SettingDialog", "90 Degree", nullptr));
        radioButtonRot180->setText(QCoreApplication::translate("SettingDialog", "180 Degree", nullptr));
        radioButtonRot270->setText(QCoreApplication::translate("SettingDialog", "270 Degree", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
