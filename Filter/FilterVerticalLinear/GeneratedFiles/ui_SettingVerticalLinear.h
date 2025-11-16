/********************************************************************************
** Form generated from reading UI file 'SettingVerticalLinear.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGVERTICALLINEAR_H
#define UI_SETTINGVERTICALLINEAR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingVerticalLinear
{
public:
    QCheckBox *checkBoxTopSide;
    QDoubleSpinBox *doubleSpinBoxStrength;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QCheckBox *checkBoxBottomSide;
    QLabel *label;
    QLabel *label_3;
    QCheckBox *checkBoxWholeImage;
    QCheckBox *cbLayer2;
    QLabel *label_4;
    QCheckBox *cbLayer0;
    QCheckBox *cbLayer1;
    QDoubleSpinBox *doubleSpinBoxGamma;
    QLabel *label_7;

    void setupUi(QDialog *SettingVerticalLinear)
    {
        if (SettingVerticalLinear->objectName().isEmpty())
            SettingVerticalLinear->setObjectName("SettingVerticalLinear");
        SettingVerticalLinear->resize(254, 368);
        checkBoxTopSide = new QCheckBox(SettingVerticalLinear);
        checkBoxTopSide->setObjectName("checkBoxTopSide");
        checkBoxTopSide->setGeometry(QRect(40, 270, 91, 17));
        doubleSpinBoxStrength = new QDoubleSpinBox(SettingVerticalLinear);
        doubleSpinBoxStrength->setObjectName("doubleSpinBoxStrength");
        doubleSpinBoxStrength->setGeometry(QRect(120, 117, 91, 22));
        doubleSpinBoxStrength->setDecimals(4);
        doubleSpinBoxStrength->setMinimum(-99.000000000000000);
        pushButtonOK = new QPushButton(SettingVerticalLinear);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 300, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(SettingVerticalLinear);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 300, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        checkBoxBottomSide = new QCheckBox(SettingVerticalLinear);
        checkBoxBottomSide->setObjectName("checkBoxBottomSide");
        checkBoxBottomSide->setGeometry(QRect(140, 270, 101, 17));
        label = new QLabel(SettingVerticalLinear);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 120, 50, 20));
        label_3 = new QLabel(SettingVerticalLinear);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 147, 211, 31));
        checkBoxWholeImage = new QCheckBox(SettingVerticalLinear);
        checkBoxWholeImage->setObjectName("checkBoxWholeImage");
        checkBoxWholeImage->setGeometry(QRect(40, 240, 201, 19));
        cbLayer2 = new QCheckBox(SettingVerticalLinear);
        cbLayer2->setObjectName("cbLayer2");
        cbLayer2->setGeometry(QRect(110, 70, 94, 20));
        label_4 = new QLabel(SettingVerticalLinear);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 40, 50, 20));
        cbLayer0 = new QCheckBox(SettingVerticalLinear);
        cbLayer0->setObjectName("cbLayer0");
        cbLayer0->setGeometry(QRect(110, 10, 94, 20));
        cbLayer1 = new QCheckBox(SettingVerticalLinear);
        cbLayer1->setObjectName("cbLayer1");
        cbLayer1->setGeometry(QRect(110, 40, 94, 20));
        doubleSpinBoxGamma = new QDoubleSpinBox(SettingVerticalLinear);
        doubleSpinBoxGamma->setObjectName("doubleSpinBoxGamma");
        doubleSpinBoxGamma->setGeometry(QRect(140, 187, 81, 22));
        doubleSpinBoxGamma->setDecimals(4);
        doubleSpinBoxGamma->setValue(1.000000000000000);
        label_7 = new QLabel(SettingVerticalLinear);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(30, 190, 101, 20));

        retranslateUi(SettingVerticalLinear);

        QMetaObject::connectSlotsByName(SettingVerticalLinear);
    } // setupUi

    void retranslateUi(QDialog *SettingVerticalLinear)
    {
        SettingVerticalLinear->setWindowTitle(QCoreApplication::translate("SettingVerticalLinear", "Setting VerticalLinear", nullptr));
        checkBoxTopSide->setText(QCoreApplication::translate("SettingVerticalLinear", "Top side", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingVerticalLinear", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingVerticalLinear", "Cancel", nullptr));
        checkBoxBottomSide->setText(QCoreApplication::translate("SettingVerticalLinear", "Bottom side", nullptr));
        label->setText(QCoreApplication::translate("SettingVerticalLinear", "Strength", nullptr));
        label_3->setText(QCoreApplication::translate("SettingVerticalLinear", "Gain / (Distance from Center)", nullptr));
        checkBoxWholeImage->setText(QCoreApplication::translate("SettingVerticalLinear", "Adapt in whole image", nullptr));
        cbLayer2->setText(QCoreApplication::translate("SettingVerticalLinear", "Layer 2", nullptr));
        label_4->setText(QCoreApplication::translate("SettingVerticalLinear", "Layer", nullptr));
        cbLayer0->setText(QCoreApplication::translate("SettingVerticalLinear", "Layer 0", nullptr));
        cbLayer1->setText(QCoreApplication::translate("SettingVerticalLinear", "Layer 1", nullptr));
        label_7->setText(QCoreApplication::translate("SettingVerticalLinear", "Pixel Gamma", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingVerticalLinear: public Ui_SettingVerticalLinear {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGVERTICALLINEAR_H
