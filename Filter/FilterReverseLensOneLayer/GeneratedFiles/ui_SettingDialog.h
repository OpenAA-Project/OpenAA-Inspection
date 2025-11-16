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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QLabel *label;
    QCheckBox *checkBoxLeftSide;
    QLabel *label_2;
    QCheckBox *checkBoxRightSide;
    QDoubleSpinBox *doubleSpinBoxWidth;
    QPushButton *pushButtonOK;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBoxStrength;
    QPushButton *pushButtonCancel;
    QComboBox *comboBoxLayer;
    QLabel *label_4;
    QPushButton *pushButtonTest;
    QLabel *labelTestLeft;
    QLabel *labelTestCenter;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(253, 273);
        label = new QLabel(SettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 43, 50, 20));
        checkBoxLeftSide = new QCheckBox(SettingDialog);
        checkBoxLeftSide->setObjectName("checkBoxLeftSide");
        checkBoxLeftSide->setGeometry(QRect(40, 140, 76, 17));
        label_2 = new QLabel(SettingDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 70, 50, 20));
        checkBoxRightSide = new QCheckBox(SettingDialog);
        checkBoxRightSide->setObjectName("checkBoxRightSide");
        checkBoxRightSide->setGeometry(QRect(160, 140, 76, 17));
        doubleSpinBoxWidth = new QDoubleSpinBox(SettingDialog);
        doubleSpinBoxWidth->setObjectName("doubleSpinBoxWidth");
        doubleSpinBoxWidth->setGeometry(QRect(120, 70, 91, 22));
        doubleSpinBoxWidth->setDecimals(4);
        doubleSpinBoxWidth->setMinimum(-0.500000000000000);
        doubleSpinBoxWidth->setMaximum(0.500000000000000);
        doubleSpinBoxWidth->setSingleStep(0.100000000000000);
        doubleSpinBoxWidth->setValue(0.160000000000000);
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 220, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        label_3 = new QLabel(SettingDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 100, 211, 41));
        doubleSpinBoxStrength = new QDoubleSpinBox(SettingDialog);
        doubleSpinBoxStrength->setObjectName("doubleSpinBoxStrength");
        doubleSpinBoxStrength->setGeometry(QRect(120, 40, 91, 22));
        doubleSpinBoxStrength->setDecimals(4);
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 220, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        comboBoxLayer = new QComboBox(SettingDialog);
        comboBoxLayer->setObjectName("comboBoxLayer");
        comboBoxLayer->setGeometry(QRect(120, 10, 91, 22));
        label_4 = new QLabel(SettingDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 10, 50, 20));
        pushButtonTest = new QPushButton(SettingDialog);
        pushButtonTest->setObjectName("pushButtonTest");
        pushButtonTest->setGeometry(QRect(10, 170, 75, 41));
        labelTestLeft = new QLabel(SettingDialog);
        labelTestLeft->setObjectName("labelTestLeft");
        labelTestLeft->setGeometry(QRect(90, 170, 151, 21));
        labelTestCenter = new QLabel(SettingDialog);
        labelTestCenter->setObjectName("labelTestCenter");
        labelTestCenter->setGeometry(QRect(90, 190, 151, 21));

        retranslateUi(SettingDialog);

        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SettingDialog", "Strength", nullptr));
        checkBoxLeftSide->setText(QCoreApplication::translate("SettingDialog", "Left side", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "Width", nullptr));
        checkBoxRightSide->setText(QCoreApplication::translate("SettingDialog", "Right side", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        label_3->setText(QCoreApplication::translate("SettingDialog", "Width:0-0.5   Normally 0.16", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingDialog", "Cancel", nullptr));
        label_4->setText(QCoreApplication::translate("SettingDialog", "Layer", nullptr));
        pushButtonTest->setText(QCoreApplication::translate("SettingDialog", "Test--->", nullptr));
        labelTestLeft->setText(QCoreApplication::translate("SettingDialog", "Left end", nullptr));
        labelTestCenter->setText(QCoreApplication::translate("SettingDialog", "Center", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
