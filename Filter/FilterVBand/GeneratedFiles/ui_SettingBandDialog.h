/********************************************************************************
** Form generated from reading UI file 'SettingBandDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGBANDDIALOG_H
#define UI_SETTINGBANDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingBandDialog
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxX1;
    QSpinBox *spinBoxX2;
    QDoubleSpinBox *doubleSpinBoxGain;
    QSpinBox *spinBoxOffset;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QDialog *SettingBandDialog)
    {
        if (SettingBandDialog->objectName().isEmpty())
            SettingBandDialog->setObjectName("SettingBandDialog");
        SettingBandDialog->resize(253, 230);
        pushButtonOK = new QPushButton(SettingBandDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 180, 91, 31));
        pushButtonCancel = new QPushButton(SettingBandDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 180, 81, 31));
        spinBoxX1 = new QSpinBox(SettingBandDialog);
        spinBoxX1->setObjectName("spinBoxX1");
        spinBoxX1->setGeometry(QRect(30, 40, 91, 22));
        spinBoxX1->setMaximum(99999999);
        spinBoxX1->setValue(100);
        spinBoxX2 = new QSpinBox(SettingBandDialog);
        spinBoxX2->setObjectName("spinBoxX2");
        spinBoxX2->setGeometry(QRect(140, 40, 91, 22));
        spinBoxX2->setMaximum(99999999);
        spinBoxX2->setValue(200);
        doubleSpinBoxGain = new QDoubleSpinBox(SettingBandDialog);
        doubleSpinBoxGain->setObjectName("doubleSpinBoxGain");
        doubleSpinBoxGain->setGeometry(QRect(30, 90, 91, 22));
        doubleSpinBoxGain->setDecimals(5);
        doubleSpinBoxGain->setMinimum(-99.000000000000000);
        spinBoxOffset = new QSpinBox(SettingBandDialog);
        spinBoxOffset->setObjectName("spinBoxOffset");
        spinBoxOffset->setGeometry(QRect(30, 140, 91, 22));
        spinBoxOffset->setMinimum(-99999);
        spinBoxOffset->setMaximum(99999);
        label = new QLabel(SettingBandDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 20, 91, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(SettingBandDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 20, 91, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(SettingBandDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 70, 91, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(SettingBandDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 120, 91, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);

        retranslateUi(SettingBandDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SettingBandDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingBandDialog)
    {
        SettingBandDialog->setWindowTitle(QCoreApplication::translate("SettingBandDialog", "Setting VBand", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingBandDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingBandDialog", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("SettingBandDialog", "Start X", nullptr));
        label_2->setText(QCoreApplication::translate("SettingBandDialog", "End X", nullptr));
        label_3->setText(QCoreApplication::translate("SettingBandDialog", "GAIN", nullptr));
        label_4->setText(QCoreApplication::translate("SettingBandDialog", "Offset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingBandDialog: public Ui_SettingBandDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGBANDDIALOG_H
