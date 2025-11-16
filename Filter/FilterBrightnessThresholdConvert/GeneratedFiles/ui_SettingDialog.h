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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxThresholdBrightness;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxThresholdWidth;
    QFrame *frameLineGraph;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(429, 337);
        label = new QLabel(SettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 131, 18));
        doubleSpinBoxThresholdBrightness = new QDoubleSpinBox(SettingDialog);
        doubleSpinBoxThresholdBrightness->setObjectName("doubleSpinBoxThresholdBrightness");
        doubleSpinBoxThresholdBrightness->setGeometry(QRect(40, 40, 81, 24));
        doubleSpinBoxThresholdBrightness->setMaximum(255.000000000000000);
        label_2 = new QLabel(SettingDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 100, 131, 18));
        doubleSpinBoxThresholdWidth = new QDoubleSpinBox(SettingDialog);
        doubleSpinBoxThresholdWidth->setObjectName("doubleSpinBoxThresholdWidth");
        doubleSpinBoxThresholdWidth->setGeometry(QRect(36, 130, 91, 24));
        doubleSpinBoxThresholdWidth->setMaximum(255.000000000000000);
        frameLineGraph = new QFrame(SettingDialog);
        frameLineGraph->setObjectName("frameLineGraph");
        frameLineGraph->setGeometry(QRect(160, 10, 256, 256));
        frameLineGraph->setFrameShape(QFrame::StyledPanel);
        frameLineGraph->setFrameShadow(QFrame::Raised);
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 280, 112, 34));
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(280, 280, 112, 34));

        retranslateUi(SettingDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SettingDialog", "\350\274\235\345\272\246\343\201\256\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "\350\274\235\345\272\246\343\201\256\343\201\227\343\201\215\343\201\204\345\271\205", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
