/********************************************************************************
** Form generated from reading UI file 'SettingReverseLensOneside.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGREVERSELENSONESIDE_H
#define UI_SETTINGREVERSELENSONESIDE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingReverseLensOneside
{
public:
    QPushButton *pushButtonOK;
    QDoubleSpinBox *doubleSpinBoxWidth;
    QLabel *label;
    QLabel *label_3;
    QPushButton *pushButtonCancel;
    QDoubleSpinBox *doubleSpinBoxStrength;
    QLabel *label_2;
    QCheckBox *checkBoxLeftSide;
    QCheckBox *checkBoxRightSide;

    void setupUi(QDialog *SettingReverseLensOneside)
    {
        if (SettingReverseLensOneside->objectName().isEmpty())
            SettingReverseLensOneside->setObjectName("SettingReverseLensOneside");
        SettingReverseLensOneside->resize(249, 197);
        pushButtonOK = new QPushButton(SettingReverseLensOneside);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 140, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        doubleSpinBoxWidth = new QDoubleSpinBox(SettingReverseLensOneside);
        doubleSpinBoxWidth->setObjectName("doubleSpinBoxWidth");
        doubleSpinBoxWidth->setGeometry(QRect(120, 40, 91, 22));
        doubleSpinBoxWidth->setDecimals(4);
        doubleSpinBoxWidth->setMinimum(-0.500000000000000);
        doubleSpinBoxWidth->setMaximum(0.500000000000000);
        doubleSpinBoxWidth->setSingleStep(0.100000000000000);
        doubleSpinBoxWidth->setValue(0.160000000000000);
        label = new QLabel(SettingReverseLensOneside);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 13, 50, 20));
        label_3 = new QLabel(SettingReverseLensOneside);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 70, 211, 41));
        pushButtonCancel = new QPushButton(SettingReverseLensOneside);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 140, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        doubleSpinBoxStrength = new QDoubleSpinBox(SettingReverseLensOneside);
        doubleSpinBoxStrength->setObjectName("doubleSpinBoxStrength");
        doubleSpinBoxStrength->setGeometry(QRect(120, 10, 91, 22));
        doubleSpinBoxStrength->setDecimals(4);
        label_2 = new QLabel(SettingReverseLensOneside);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 40, 50, 20));
        checkBoxLeftSide = new QCheckBox(SettingReverseLensOneside);
        checkBoxLeftSide->setObjectName("checkBoxLeftSide");
        checkBoxLeftSide->setGeometry(QRect(40, 110, 76, 17));
        checkBoxRightSide = new QCheckBox(SettingReverseLensOneside);
        checkBoxRightSide->setObjectName("checkBoxRightSide");
        checkBoxRightSide->setGeometry(QRect(160, 110, 76, 17));

        retranslateUi(SettingReverseLensOneside);

        QMetaObject::connectSlotsByName(SettingReverseLensOneside);
    } // setupUi

    void retranslateUi(QDialog *SettingReverseLensOneside)
    {
        SettingReverseLensOneside->setWindowTitle(QCoreApplication::translate("SettingReverseLensOneside", "Setting ReverseLens OneSide", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingReverseLensOneside", "OK", nullptr));
        label->setText(QCoreApplication::translate("SettingReverseLensOneside", "Strength", nullptr));
        label_3->setText(QCoreApplication::translate("SettingReverseLensOneside", "Width:0-0.5   Normally 0.16", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingReverseLensOneside", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("SettingReverseLensOneside", "Width", nullptr));
        checkBoxLeftSide->setText(QCoreApplication::translate("SettingReverseLensOneside", "Left side", nullptr));
        checkBoxRightSide->setText(QCoreApplication::translate("SettingReverseLensOneside", "Right side", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingReverseLensOneside: public Ui_SettingReverseLensOneside {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGREVERSELENSONESIDE_H
