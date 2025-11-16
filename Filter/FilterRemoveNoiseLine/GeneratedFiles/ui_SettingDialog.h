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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QComboBox *comboBoxNoiseLineH;
    QLabel *label;
    QSpinBox *spinBoxNoiseLineWidth;
    QSpinBox *spinBoxThresholdL;
    QLabel *label_2;
    QSpinBox *spinBoxThresholdH;
    QLabel *label_3;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(234, 230);
        comboBoxNoiseLineH = new QComboBox(SettingDialog);
        comboBoxNoiseLineH->addItem(QString());
        comboBoxNoiseLineH->addItem(QString());
        comboBoxNoiseLineH->setObjectName("comboBoxNoiseLineH");
        comboBoxNoiseLineH->setGeometry(QRect(10, 10, 161, 24));
        label = new QLabel(SettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 60, 131, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        spinBoxNoiseLineWidth = new QSpinBox(SettingDialog);
        spinBoxNoiseLineWidth->setObjectName("spinBoxNoiseLineWidth");
        spinBoxNoiseLineWidth->setGeometry(QRect(150, 60, 71, 24));
        spinBoxThresholdL = new QSpinBox(SettingDialog);
        spinBoxThresholdL->setObjectName("spinBoxThresholdL");
        spinBoxThresholdL->setGeometry(QRect(150, 100, 71, 24));
        spinBoxThresholdL->setMaximum(255);
        label_2 = new QLabel(SettingDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 100, 131, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        spinBoxThresholdH = new QSpinBox(SettingDialog);
        spinBoxThresholdH->setObjectName("spinBoxThresholdH");
        spinBoxThresholdH->setGeometry(QRect(150, 130, 71, 24));
        spinBoxThresholdH->setMaximum(255);
        label_3 = new QLabel(SettingDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 130, 131, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 180, 91, 34));
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(130, 180, 91, 34));

        retranslateUi(SettingDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Dialog", nullptr));
        comboBoxNoiseLineH->setItemText(0, QCoreApplication::translate("SettingDialog", "HorizontalNoise", nullptr));
        comboBoxNoiseLineH->setItemText(1, QCoreApplication::translate("SettingDialog", "VerticalNoise", nullptr));

        label->setText(QCoreApplication::translate("SettingDialog", "Noise line width", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "Threshold Low", nullptr));
        label_3->setText(QCoreApplication::translate("SettingDialog", "Threshold High", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
