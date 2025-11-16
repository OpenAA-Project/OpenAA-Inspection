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
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QCheckBox *cbLayer0;
    QLabel *label_6;
    QSpinBox *spinBoxLength;
    QCheckBox *cbLayer1;
    QPushButton *pushButtonOK;
    QDoubleSpinBox *doubleSpinBoxGain;
    QCheckBox *cbLayer2;
    QPushButton *pushButtonCancel;
    QLabel *label;
    QCheckBox *cbVertical;
    QLabel *label_3;
    QLabel *label_2;
    QGroupBox *groupBoxBPF;
    QLabel *label_4;
    QSpinBox *spinBoxPassWidth;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(260, 520);
        cbLayer0 = new QCheckBox(SettingDialog);
        cbLayer0->setObjectName("cbLayer0");
        cbLayer0->setGeometry(QRect(110, 10, 94, 20));
        label_6 = new QLabel(SettingDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(50, 40, 50, 20));
        spinBoxLength = new QSpinBox(SettingDialog);
        spinBoxLength->setObjectName("spinBoxLength");
        spinBoxLength->setGeometry(QRect(140, 180, 81, 22));
        spinBoxLength->setMaximum(99999999);
        cbLayer1 = new QCheckBox(SettingDialog);
        cbLayer1->setObjectName("cbLayer1");
        cbLayer1->setGeometry(QRect(110, 40, 94, 20));
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 420, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        doubleSpinBoxGain = new QDoubleSpinBox(SettingDialog);
        doubleSpinBoxGain->setObjectName("doubleSpinBoxGain");
        doubleSpinBoxGain->setGeometry(QRect(140, 110, 81, 22));
        doubleSpinBoxGain->setDecimals(4);
        doubleSpinBoxGain->setMinimum(-10000.000000000000000);
        doubleSpinBoxGain->setMaximum(10000.000000000000000);
        doubleSpinBoxGain->setValue(1.000000000000000);
        cbLayer2 = new QCheckBox(SettingDialog);
        cbLayer2->setObjectName("cbLayer2");
        cbLayer2->setGeometry(QRect(110, 70, 94, 20));
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 420, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        label = new QLabel(SettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 113, 50, 20));
        cbVertical = new QCheckBox(SettingDialog);
        cbVertical->setObjectName("cbVertical");
        cbVertical->setGeometry(QRect(90, 230, 94, 20));
        label_3 = new QLabel(SettingDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(130, 140, 111, 21));
        label_2 = new QLabel(SettingDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 180, 81, 20));
        groupBoxBPF = new QGroupBox(SettingDialog);
        groupBoxBPF->setObjectName("groupBoxBPF");
        groupBoxBPF->setGeometry(QRect(20, 280, 221, 80));
        groupBoxBPF->setCheckable(true);
        label_4 = new QLabel(groupBoxBPF);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 30, 81, 20));
        spinBoxPassWidth = new QSpinBox(groupBoxBPF);
        spinBoxPassWidth->setObjectName("spinBoxPassWidth");
        spinBoxPassWidth->setGeometry(QRect(130, 30, 81, 22));
        spinBoxPassWidth->setMaximum(99999999);

        retranslateUi(SettingDialog);

        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Setting", nullptr));
        cbLayer0->setText(QCoreApplication::translate("SettingDialog", "Layer 0", nullptr));
        label_6->setText(QCoreApplication::translate("SettingDialog", "Layer", nullptr));
        cbLayer1->setText(QCoreApplication::translate("SettingDialog", "Layer 1", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        cbLayer2->setText(QCoreApplication::translate("SettingDialog", "Layer 2", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingDialog", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("SettingDialog", "Gain", nullptr));
        cbVertical->setText(QCoreApplication::translate("SettingDialog", "Vertical", nullptr));
        label_3->setText(QCoreApplication::translate("SettingDialog", "1.0 : not change", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "Length", nullptr));
        groupBoxBPF->setTitle(QCoreApplication::translate("SettingDialog", "BPF", nullptr));
        label_4->setText(QCoreApplication::translate("SettingDialog", "Pass width", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
