/********************************************************************************
** Form generated from reading UI file 'SettingReverseLens.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGREVERSELENS_H
#define UI_SETTINGREVERSELENS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingReverseLensClass
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QDoubleSpinBox *doubleSpinBoxStrength;
    QDoubleSpinBox *doubleSpinBoxWidth;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *spinBoxStartX;
    QSpinBox *spinBoxEndX;
    QLabel *label_5;

    void setupUi(QDialog *SettingReverseLensClass)
    {
        if (SettingReverseLensClass->objectName().isEmpty())
            SettingReverseLensClass->setObjectName("SettingReverseLensClass");
        SettingReverseLensClass->resize(250, 231);
        pushButtonOK = new QPushButton(SettingReverseLensClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 180, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(SettingReverseLensClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 180, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        doubleSpinBoxStrength = new QDoubleSpinBox(SettingReverseLensClass);
        doubleSpinBoxStrength->setObjectName("doubleSpinBoxStrength");
        doubleSpinBoxStrength->setGeometry(QRect(120, 20, 91, 22));
        doubleSpinBoxStrength->setDecimals(4);
        doubleSpinBoxWidth = new QDoubleSpinBox(SettingReverseLensClass);
        doubleSpinBoxWidth->setObjectName("doubleSpinBoxWidth");
        doubleSpinBoxWidth->setGeometry(QRect(120, 50, 91, 22));
        doubleSpinBoxWidth->setDecimals(4);
        doubleSpinBoxWidth->setMinimum(-0.500000000000000);
        doubleSpinBoxWidth->setMaximum(0.500000000000000);
        doubleSpinBoxWidth->setSingleStep(0.100000000000000);
        doubleSpinBoxWidth->setValue(0.160000000000000);
        label = new QLabel(SettingReverseLensClass);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 23, 50, 20));
        label_2 = new QLabel(SettingReverseLensClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 50, 50, 20));
        label_3 = new QLabel(SettingReverseLensClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 80, 211, 41));
        label_4 = new QLabel(SettingReverseLensClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 120, 61, 20));
        spinBoxStartX = new QSpinBox(SettingReverseLensClass);
        spinBoxStartX->setObjectName("spinBoxStartX");
        spinBoxStartX->setGeometry(QRect(10, 140, 71, 31));
        spinBoxStartX->setMaximum(999999999);
        spinBoxEndX = new QSpinBox(SettingReverseLensClass);
        spinBoxEndX->setObjectName("spinBoxEndX");
        spinBoxEndX->setGeometry(QRect(120, 140, 71, 31));
        spinBoxEndX->setMaximum(99999999);
        label_5 = new QLabel(SettingReverseLensClass);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(130, 120, 61, 20));

        retranslateUi(SettingReverseLensClass);

        QMetaObject::connectSlotsByName(SettingReverseLensClass);
    } // setupUi

    void retranslateUi(QDialog *SettingReverseLensClass)
    {
        SettingReverseLensClass->setWindowTitle(QCoreApplication::translate("SettingReverseLensClass", "SettingReverseLens", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingReverseLensClass", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingReverseLensClass", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("SettingReverseLensClass", "Strength", nullptr));
        label_2->setText(QCoreApplication::translate("SettingReverseLensClass", "Width", nullptr));
        label_3->setText(QCoreApplication::translate("SettingReverseLensClass", "Width:0-0.5   Normally 0.16", nullptr));
        label_4->setText(QCoreApplication::translate("SettingReverseLensClass", "Start X", nullptr));
        label_5->setText(QCoreApplication::translate("SettingReverseLensClass", "End X", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingReverseLensClass: public Ui_SettingReverseLensClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGREVERSELENS_H
