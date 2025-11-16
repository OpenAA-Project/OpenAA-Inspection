/********************************************************************************
** Form generated from reading UI file 'SettingFilterHorizontalLinear.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGFILTERHORIZONTALLINEAR_H
#define UI_SETTINGFILTERHORIZONTALLINEAR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingFilterHorizontalLinear
{
public:
    QDoubleSpinBox *doubleSpinBoxStrength;
    QLabel *label_3;
    QCheckBox *checkBoxLeftSide;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QCheckBox *checkBoxRightSide;
    QLabel *label;
    QCheckBox *checkBoxWholeImage;
    QCheckBox *cbLayer2;
    QLabel *label_4;
    QCheckBox *cbLayer0;
    QCheckBox *cbLayer1;
    QDoubleSpinBox *doubleSpinBoxGamma;
    QLabel *label_7;

    void setupUi(QDialog *SettingFilterHorizontalLinear)
    {
        if (SettingFilterHorizontalLinear->objectName().isEmpty())
            SettingFilterHorizontalLinear->setObjectName("SettingFilterHorizontalLinear");
        SettingFilterHorizontalLinear->resize(249, 358);
        doubleSpinBoxStrength = new QDoubleSpinBox(SettingFilterHorizontalLinear);
        doubleSpinBoxStrength->setObjectName("doubleSpinBoxStrength");
        doubleSpinBoxStrength->setGeometry(QRect(120, 117, 91, 22));
        doubleSpinBoxStrength->setDecimals(4);
        doubleSpinBoxStrength->setMinimum(-99.000000000000000);
        label_3 = new QLabel(SettingFilterHorizontalLinear);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 147, 211, 31));
        checkBoxLeftSide = new QCheckBox(SettingFilterHorizontalLinear);
        checkBoxLeftSide->setObjectName("checkBoxLeftSide");
        checkBoxLeftSide->setGeometry(QRect(40, 270, 76, 17));
        pushButtonOK = new QPushButton(SettingFilterHorizontalLinear);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 300, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(SettingFilterHorizontalLinear);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 300, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        checkBoxRightSide = new QCheckBox(SettingFilterHorizontalLinear);
        checkBoxRightSide->setObjectName("checkBoxRightSide");
        checkBoxRightSide->setGeometry(QRect(160, 270, 76, 17));
        label = new QLabel(SettingFilterHorizontalLinear);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 120, 50, 20));
        checkBoxWholeImage = new QCheckBox(SettingFilterHorizontalLinear);
        checkBoxWholeImage->setObjectName("checkBoxWholeImage");
        checkBoxWholeImage->setGeometry(QRect(40, 240, 201, 19));
        cbLayer2 = new QCheckBox(SettingFilterHorizontalLinear);
        cbLayer2->setObjectName("cbLayer2");
        cbLayer2->setGeometry(QRect(100, 70, 94, 20));
        label_4 = new QLabel(SettingFilterHorizontalLinear);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 40, 50, 20));
        cbLayer0 = new QCheckBox(SettingFilterHorizontalLinear);
        cbLayer0->setObjectName("cbLayer0");
        cbLayer0->setGeometry(QRect(100, 10, 94, 20));
        cbLayer1 = new QCheckBox(SettingFilterHorizontalLinear);
        cbLayer1->setObjectName("cbLayer1");
        cbLayer1->setGeometry(QRect(100, 40, 94, 20));
        doubleSpinBoxGamma = new QDoubleSpinBox(SettingFilterHorizontalLinear);
        doubleSpinBoxGamma->setObjectName("doubleSpinBoxGamma");
        doubleSpinBoxGamma->setGeometry(QRect(130, 187, 81, 22));
        doubleSpinBoxGamma->setDecimals(4);
        doubleSpinBoxGamma->setValue(1.000000000000000);
        label_7 = new QLabel(SettingFilterHorizontalLinear);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 190, 101, 20));

        retranslateUi(SettingFilterHorizontalLinear);

        QMetaObject::connectSlotsByName(SettingFilterHorizontalLinear);
    } // setupUi

    void retranslateUi(QDialog *SettingFilterHorizontalLinear)
    {
        SettingFilterHorizontalLinear->setWindowTitle(QCoreApplication::translate("SettingFilterHorizontalLinear", "Setting", nullptr));
        label_3->setText(QCoreApplication::translate("SettingFilterHorizontalLinear", "Gain / (Distance from Center)", nullptr));
        checkBoxLeftSide->setText(QCoreApplication::translate("SettingFilterHorizontalLinear", "Left side", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingFilterHorizontalLinear", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingFilterHorizontalLinear", "Cancel", nullptr));
        checkBoxRightSide->setText(QCoreApplication::translate("SettingFilterHorizontalLinear", "Right side", nullptr));
        label->setText(QCoreApplication::translate("SettingFilterHorizontalLinear", "Strength", nullptr));
        checkBoxWholeImage->setText(QCoreApplication::translate("SettingFilterHorizontalLinear", "Adapt in whole image", nullptr));
        cbLayer2->setText(QCoreApplication::translate("SettingFilterHorizontalLinear", "Layer 2", nullptr));
        label_4->setText(QCoreApplication::translate("SettingFilterHorizontalLinear", "Layer", nullptr));
        cbLayer0->setText(QCoreApplication::translate("SettingFilterHorizontalLinear", "Layer 0", nullptr));
        cbLayer1->setText(QCoreApplication::translate("SettingFilterHorizontalLinear", "Layer 1", nullptr));
        label_7->setText(QCoreApplication::translate("SettingFilterHorizontalLinear", "Pixel Gamma", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingFilterHorizontalLinear: public Ui_SettingFilterHorizontalLinear {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGFILTERHORIZONTALLINEAR_H
