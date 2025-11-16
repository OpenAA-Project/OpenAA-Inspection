/********************************************************************************
** Form generated from reading UI file 'SettingFilterHorizontalBand.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGFILTERHORIZONTALBAND_H
#define UI_SETTINGFILTERHORIZONTALBAND_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingFilterHorizontalBand
{
public:
    QDoubleSpinBox *doubleSpinBoxGain;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *spinBoxCenterX;
    QSpinBox *spinBoxBandWidth;
    QSpinBox *spinBoxGradationWidth;
    QLabel *label_3;
    QCheckBox *cbLayer2;
    QLabel *label_6;
    QCheckBox *cbLayer0;
    QCheckBox *cbLayer1;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBoxGamma;

    void setupUi(QDialog *SettingFilterHorizontalBand)
    {
        if (SettingFilterHorizontalBand->objectName().isEmpty())
            SettingFilterHorizontalBand->setObjectName("SettingFilterHorizontalBand");
        SettingFilterHorizontalBand->resize(250, 388);
        doubleSpinBoxGain = new QDoubleSpinBox(SettingFilterHorizontalBand);
        doubleSpinBoxGain->setObjectName("doubleSpinBoxGain");
        doubleSpinBoxGain->setGeometry(QRect(140, 110, 81, 22));
        doubleSpinBoxGain->setDecimals(4);
        doubleSpinBoxGain->setValue(1.000000000000000);
        pushButtonOK = new QPushButton(SettingFilterHorizontalBand);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 330, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(SettingFilterHorizontalBand);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 330, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        label = new QLabel(SettingFilterHorizontalBand);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 113, 50, 20));
        label_2 = new QLabel(SettingFilterHorizontalBand);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 180, 81, 20));
        label_4 = new QLabel(SettingFilterHorizontalBand);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 210, 81, 20));
        label_5 = new QLabel(SettingFilterHorizontalBand);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(30, 240, 101, 20));
        spinBoxCenterX = new QSpinBox(SettingFilterHorizontalBand);
        spinBoxCenterX->setObjectName("spinBoxCenterX");
        spinBoxCenterX->setGeometry(QRect(140, 180, 81, 22));
        spinBoxCenterX->setMaximum(99999999);
        spinBoxBandWidth = new QSpinBox(SettingFilterHorizontalBand);
        spinBoxBandWidth->setObjectName("spinBoxBandWidth");
        spinBoxBandWidth->setGeometry(QRect(140, 210, 81, 22));
        spinBoxBandWidth->setMaximum(99999999);
        spinBoxGradationWidth = new QSpinBox(SettingFilterHorizontalBand);
        spinBoxGradationWidth->setObjectName("spinBoxGradationWidth");
        spinBoxGradationWidth->setGeometry(QRect(140, 240, 81, 22));
        spinBoxGradationWidth->setMaximum(99999999);
        label_3 = new QLabel(SettingFilterHorizontalBand);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(130, 140, 111, 21));
        cbLayer2 = new QCheckBox(SettingFilterHorizontalBand);
        cbLayer2->setObjectName("cbLayer2");
        cbLayer2->setGeometry(QRect(110, 70, 94, 20));
        label_6 = new QLabel(SettingFilterHorizontalBand);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(50, 40, 50, 20));
        cbLayer0 = new QCheckBox(SettingFilterHorizontalBand);
        cbLayer0->setObjectName("cbLayer0");
        cbLayer0->setGeometry(QRect(110, 10, 94, 20));
        cbLayer1 = new QCheckBox(SettingFilterHorizontalBand);
        cbLayer1->setObjectName("cbLayer1");
        cbLayer1->setGeometry(QRect(110, 40, 94, 20));
        label_7 = new QLabel(SettingFilterHorizontalBand);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(30, 283, 101, 20));
        doubleSpinBoxGamma = new QDoubleSpinBox(SettingFilterHorizontalBand);
        doubleSpinBoxGamma->setObjectName("doubleSpinBoxGamma");
        doubleSpinBoxGamma->setGeometry(QRect(140, 280, 81, 22));
        doubleSpinBoxGamma->setDecimals(4);
        doubleSpinBoxGamma->setValue(1.000000000000000);

        retranslateUi(SettingFilterHorizontalBand);

        QMetaObject::connectSlotsByName(SettingFilterHorizontalBand);
    } // setupUi

    void retranslateUi(QDialog *SettingFilterHorizontalBand)
    {
        SettingFilterHorizontalBand->setWindowTitle(QCoreApplication::translate("SettingFilterHorizontalBand", "Setting", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingFilterHorizontalBand", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingFilterHorizontalBand", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("SettingFilterHorizontalBand", "Gain", nullptr));
        label_2->setText(QCoreApplication::translate("SettingFilterHorizontalBand", "Center X", nullptr));
        label_4->setText(QCoreApplication::translate("SettingFilterHorizontalBand", "Band width", nullptr));
        label_5->setText(QCoreApplication::translate("SettingFilterHorizontalBand", "Gradation width", nullptr));
        label_3->setText(QCoreApplication::translate("SettingFilterHorizontalBand", "1.0 : not change", nullptr));
        cbLayer2->setText(QCoreApplication::translate("SettingFilterHorizontalBand", "Layer 2", nullptr));
        label_6->setText(QCoreApplication::translate("SettingFilterHorizontalBand", "Layer", nullptr));
        cbLayer0->setText(QCoreApplication::translate("SettingFilterHorizontalBand", "Layer 0", nullptr));
        cbLayer1->setText(QCoreApplication::translate("SettingFilterHorizontalBand", "Layer 1", nullptr));
        label_7->setText(QCoreApplication::translate("SettingFilterHorizontalBand", "Pixel Gamma", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingFilterHorizontalBand: public Ui_SettingFilterHorizontalBand {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGFILTERHORIZONTALBAND_H
