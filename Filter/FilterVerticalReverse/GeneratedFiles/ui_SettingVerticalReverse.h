/********************************************************************************
** Form generated from reading UI file 'SettingVerticalReverse.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGVERTICALREVERSE_H
#define UI_SETTINGVERTICALREVERSE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingVerticalReverse
{
public:
    QLabel *label;
    QCheckBox *checkBoxTopSide;
    QDoubleSpinBox *doubleSpinBoxStrength;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButtonCancel;
    QDoubleSpinBox *doubleSpinBoxWidth;
    QPushButton *pushButtonOK;
    QCheckBox *checkBoxBottomSide;
    QCheckBox *cbLayer2;
    QLabel *label_4;
    QCheckBox *cbLayer0;
    QCheckBox *cbLayer1;
    QDoubleSpinBox *doubleSpinBoxGamma;
    QLabel *label_7;

    void setupUi(QDialog *SettingVerticalReverse)
    {
        if (SettingVerticalReverse->objectName().isEmpty())
            SettingVerticalReverse->setObjectName("SettingVerticalReverse");
        SettingVerticalReverse->resize(248, 373);
        label = new QLabel(SettingVerticalReverse);
        label->setObjectName("label");
        label->setGeometry(QRect(45, 113, 50, 20));
        checkBoxTopSide = new QCheckBox(SettingVerticalReverse);
        checkBoxTopSide->setObjectName("checkBoxTopSide");
        checkBoxTopSide->setGeometry(QRect(35, 260, 81, 17));
        doubleSpinBoxStrength = new QDoubleSpinBox(SettingVerticalReverse);
        doubleSpinBoxStrength->setObjectName("doubleSpinBoxStrength");
        doubleSpinBoxStrength->setGeometry(QRect(115, 110, 91, 22));
        doubleSpinBoxStrength->setDecimals(4);
        label_2 = new QLabel(SettingVerticalReverse);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(45, 140, 50, 20));
        label_3 = new QLabel(SettingVerticalReverse);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(25, 170, 211, 31));
        pushButtonCancel = new QPushButton(SettingVerticalReverse);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(135, 290, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        doubleSpinBoxWidth = new QDoubleSpinBox(SettingVerticalReverse);
        doubleSpinBoxWidth->setObjectName("doubleSpinBoxWidth");
        doubleSpinBoxWidth->setGeometry(QRect(115, 140, 91, 22));
        doubleSpinBoxWidth->setDecimals(4);
        doubleSpinBoxWidth->setMinimum(-0.500000000000000);
        doubleSpinBoxWidth->setMaximum(0.500000000000000);
        doubleSpinBoxWidth->setSingleStep(0.100000000000000);
        doubleSpinBoxWidth->setValue(0.160000000000000);
        pushButtonOK = new QPushButton(SettingVerticalReverse);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(5, 290, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        checkBoxBottomSide = new QCheckBox(SettingVerticalReverse);
        checkBoxBottomSide->setObjectName("checkBoxBottomSide");
        checkBoxBottomSide->setGeometry(QRect(140, 260, 91, 20));
        cbLayer2 = new QCheckBox(SettingVerticalReverse);
        cbLayer2->setObjectName("cbLayer2");
        cbLayer2->setGeometry(QRect(110, 70, 94, 20));
        label_4 = new QLabel(SettingVerticalReverse);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 40, 50, 20));
        cbLayer0 = new QCheckBox(SettingVerticalReverse);
        cbLayer0->setObjectName("cbLayer0");
        cbLayer0->setGeometry(QRect(110, 10, 94, 20));
        cbLayer1 = new QCheckBox(SettingVerticalReverse);
        cbLayer1->setObjectName("cbLayer1");
        cbLayer1->setGeometry(QRect(110, 40, 94, 20));
        doubleSpinBoxGamma = new QDoubleSpinBox(SettingVerticalReverse);
        doubleSpinBoxGamma->setObjectName("doubleSpinBoxGamma");
        doubleSpinBoxGamma->setGeometry(QRect(130, 217, 81, 22));
        doubleSpinBoxGamma->setDecimals(4);
        doubleSpinBoxGamma->setValue(1.000000000000000);
        label_7 = new QLabel(SettingVerticalReverse);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 220, 101, 20));

        retranslateUi(SettingVerticalReverse);

        QMetaObject::connectSlotsByName(SettingVerticalReverse);
    } // setupUi

    void retranslateUi(QDialog *SettingVerticalReverse)
    {
        SettingVerticalReverse->setWindowTitle(QCoreApplication::translate("SettingVerticalReverse", "Setting VerticalReverse", nullptr));
        label->setText(QCoreApplication::translate("SettingVerticalReverse", "Strength", nullptr));
        checkBoxTopSide->setText(QCoreApplication::translate("SettingVerticalReverse", "Top side", nullptr));
        label_2->setText(QCoreApplication::translate("SettingVerticalReverse", "Width", nullptr));
        label_3->setText(QCoreApplication::translate("SettingVerticalReverse", "Width:0-0.5   Normally 0.16", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingVerticalReverse", "Cancel", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingVerticalReverse", "OK", nullptr));
        checkBoxBottomSide->setText(QCoreApplication::translate("SettingVerticalReverse", "Bottom side", nullptr));
        cbLayer2->setText(QCoreApplication::translate("SettingVerticalReverse", "Layer 2", nullptr));
        label_4->setText(QCoreApplication::translate("SettingVerticalReverse", "Layer", nullptr));
        cbLayer0->setText(QCoreApplication::translate("SettingVerticalReverse", "Layer 0", nullptr));
        cbLayer1->setText(QCoreApplication::translate("SettingVerticalReverse", "Layer 1", nullptr));
        label_7->setText(QCoreApplication::translate("SettingVerticalReverse", "Pixel Gamma", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingVerticalReverse: public Ui_SettingVerticalReverse {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGVERTICALREVERSE_H
