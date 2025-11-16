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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QPushButton *pushButtonIPAddress;
    QPushButton *pushButtonSet;
    QSlider *horizontalSliderPower;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label;
    QComboBox *comboBoxMode;
    QSpinBox *spinBoxPower;
    QPushButton *pushButtonCancel;
    QComboBox *comboBoxChannel;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *spinBoxDelay;
    QSpinBox *spinBoxOutputTime;
    QLineEdit *lineEditName;
    QLabel *label_7;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(459, 276);
        pushButtonIPAddress = new QPushButton(SettingDialog);
        pushButtonIPAddress->setObjectName("pushButtonIPAddress");
        pushButtonIPAddress->setGeometry(QRect(350, 10, 91, 34));
        pushButtonSet = new QPushButton(SettingDialog);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(70, 220, 112, 34));
        horizontalSliderPower = new QSlider(SettingDialog);
        horizontalSliderPower->setObjectName("horizontalSliderPower");
        horizontalSliderPower->setGeometry(QRect(100, 120, 255, 22));
        horizontalSliderPower->setMaximum(255);
        horizontalSliderPower->setOrientation(Qt::Horizontal);
        horizontalSliderPower->setTickPosition(QSlider::TicksBelow);
        label_4 = new QLabel(SettingDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 120, 75, 21));
        label_2 = new QLabel(SettingDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 80, 75, 21));
        label = new QLabel(SettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 75, 21));
        comboBoxMode = new QComboBox(SettingDialog);
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->setObjectName("comboBoxMode");
        comboBoxMode->setGeometry(QRect(100, 80, 181, 24));
        spinBoxPower = new QSpinBox(SettingDialog);
        spinBoxPower->setObjectName("spinBoxPower");
        spinBoxPower->setGeometry(QRect(380, 120, 61, 24));
        spinBoxPower->setMaximum(255);
        spinBoxPower->setValue(255);
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(270, 220, 112, 34));
        comboBoxChannel = new QComboBox(SettingDialog);
        comboBoxChannel->addItem(QString());
        comboBoxChannel->addItem(QString());
        comboBoxChannel->addItem(QString());
        comboBoxChannel->addItem(QString());
        comboBoxChannel->addItem(QString());
        comboBoxChannel->addItem(QString());
        comboBoxChannel->addItem(QString());
        comboBoxChannel->addItem(QString());
        comboBoxChannel->setObjectName("comboBoxChannel");
        comboBoxChannel->setGeometry(QRect(100, 10, 61, 24));
        label_5 = new QLabel(SettingDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 150, 91, 21));
        label_6 = new QLabel(SettingDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 180, 101, 21));
        spinBoxDelay = new QSpinBox(SettingDialog);
        spinBoxDelay->setObjectName("spinBoxDelay");
        spinBoxDelay->setGeometry(QRect(140, 150, 71, 24));
        spinBoxDelay->setMaximum(9000);
        spinBoxDelay->setValue(9000);
        spinBoxOutputTime = new QSpinBox(SettingDialog);
        spinBoxOutputTime->setObjectName("spinBoxOutputTime");
        spinBoxOutputTime->setGeometry(QRect(140, 180, 71, 24));
        spinBoxOutputTime->setMinimum(1);
        spinBoxOutputTime->setMaximum(9999);
        spinBoxOutputTime->setValue(9999);
        lineEditName = new QLineEdit(SettingDialog);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(100, 50, 241, 24));
        label_7 = new QLabel(SettingDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 50, 75, 21));

        retranslateUi(SettingDialog);

        pushButtonSet->setDefault(true);


        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Dialog", nullptr));
        pushButtonIPAddress->setText(QCoreApplication::translate("SettingDialog", "IP address", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("SettingDialog", "Set", nullptr));
        label_4->setText(QCoreApplication::translate("SettingDialog", "Power", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "Mode", nullptr));
        label->setText(QCoreApplication::translate("SettingDialog", "Channel", nullptr));
        comboBoxMode->setItemText(0, QCoreApplication::translate("SettingDialog", "0 : Normal", nullptr));
        comboBoxMode->setItemText(1, QCoreApplication::translate("SettingDialog", "1: Repeat", nullptr));
        comboBoxMode->setItemText(2, QCoreApplication::translate("SettingDialog", "2: Single", nullptr));
        comboBoxMode->setItemText(3, QCoreApplication::translate("SettingDialog", "3: Edge", nullptr));

        pushButtonCancel->setText(QCoreApplication::translate("SettingDialog", "Cancel", nullptr));
        comboBoxChannel->setItemText(0, QCoreApplication::translate("SettingDialog", "L1", nullptr));
        comboBoxChannel->setItemText(1, QCoreApplication::translate("SettingDialog", "L2", nullptr));
        comboBoxChannel->setItemText(2, QCoreApplication::translate("SettingDialog", "L3", nullptr));
        comboBoxChannel->setItemText(3, QCoreApplication::translate("SettingDialog", "L4", nullptr));
        comboBoxChannel->setItemText(4, QCoreApplication::translate("SettingDialog", "L5", nullptr));
        comboBoxChannel->setItemText(5, QCoreApplication::translate("SettingDialog", "L6", nullptr));
        comboBoxChannel->setItemText(6, QCoreApplication::translate("SettingDialog", "L7", nullptr));
        comboBoxChannel->setItemText(7, QCoreApplication::translate("SettingDialog", "L8", nullptr));

        label_5->setText(QCoreApplication::translate("SettingDialog", "Delay", nullptr));
        label_6->setText(QCoreApplication::translate("SettingDialog", "Output time", nullptr));
        label_7->setText(QCoreApplication::translate("SettingDialog", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
