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
#include <QtWidgets/QCheckBox>
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
    QComboBox *comboBoxChannel;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBoxMode;
    QLabel *label_3;
    QCheckBox *checkBoxON;
    QLabel *label_4;
    QSlider *horizontalSliderPower;
    QSpinBox *spinBoxPower;
    QPushButton *pushButtonSet;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonIPAddress;
    QLabel *label_5;
    QLineEdit *lineEditName;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(461, 234);
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
        label = new QLabel(SettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 75, 21));
        label_2 = new QLabel(SettingDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 80, 75, 21));
        comboBoxMode = new QComboBox(SettingDialog);
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->setObjectName("comboBoxMode");
        comboBoxMode->setGeometry(QRect(100, 80, 211, 24));
        label_3 = new QLabel(SettingDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 110, 75, 21));
        checkBoxON = new QCheckBox(SettingDialog);
        checkBoxON->setObjectName("checkBoxON");
        checkBoxON->setGeometry(QRect(100, 110, 108, 22));
        label_4 = new QLabel(SettingDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 140, 75, 21));
        horizontalSliderPower = new QSlider(SettingDialog);
        horizontalSliderPower->setObjectName("horizontalSliderPower");
        horizontalSliderPower->setGeometry(QRect(100, 140, 255, 22));
        horizontalSliderPower->setMaximum(255);
        horizontalSliderPower->setOrientation(Qt::Horizontal);
        horizontalSliderPower->setTickPosition(QSlider::TicksBelow);
        spinBoxPower = new QSpinBox(SettingDialog);
        spinBoxPower->setObjectName("spinBoxPower");
        spinBoxPower->setGeometry(QRect(380, 140, 61, 24));
        spinBoxPower->setMaximum(255);
        spinBoxPower->setValue(255);
        pushButtonSet = new QPushButton(SettingDialog);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(80, 180, 112, 34));
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(280, 180, 112, 34));
        pushButtonIPAddress = new QPushButton(SettingDialog);
        pushButtonIPAddress->setObjectName("pushButtonIPAddress");
        pushButtonIPAddress->setGeometry(QRect(350, 10, 91, 34));
        label_5 = new QLabel(SettingDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 50, 75, 21));
        lineEditName = new QLineEdit(SettingDialog);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(100, 50, 241, 24));

        retranslateUi(SettingDialog);

        pushButtonSet->setDefault(true);


        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Dialog", nullptr));
        comboBoxChannel->setItemText(0, QCoreApplication::translate("SettingDialog", "L1", nullptr));
        comboBoxChannel->setItemText(1, QCoreApplication::translate("SettingDialog", "L2", nullptr));
        comboBoxChannel->setItemText(2, QCoreApplication::translate("SettingDialog", "L3", nullptr));
        comboBoxChannel->setItemText(3, QCoreApplication::translate("SettingDialog", "L4", nullptr));
        comboBoxChannel->setItemText(4, QCoreApplication::translate("SettingDialog", "L5", nullptr));
        comboBoxChannel->setItemText(5, QCoreApplication::translate("SettingDialog", "L6", nullptr));
        comboBoxChannel->setItemText(6, QCoreApplication::translate("SettingDialog", "L7", nullptr));
        comboBoxChannel->setItemText(7, QCoreApplication::translate("SettingDialog", "L8", nullptr));

        label->setText(QCoreApplication::translate("SettingDialog", "Channel", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "Mode", nullptr));
        comboBoxMode->setItemText(0, QCoreApplication::translate("SettingDialog", "0 : continuously ON/OFF", nullptr));
        comboBoxMode->setItemText(1, QCoreApplication::translate("SettingDialog", "1: 40 us", nullptr));
        comboBoxMode->setItemText(2, QCoreApplication::translate("SettingDialog", "2: 80 us", nullptr));
        comboBoxMode->setItemText(3, QCoreApplication::translate("SettingDialog", "3: 120 us", nullptr));
        comboBoxMode->setItemText(4, QCoreApplication::translate("SettingDialog", "4: 200 us", nullptr));
        comboBoxMode->setItemText(5, QCoreApplication::translate("SettingDialog", "5: 600 us", nullptr));
        comboBoxMode->setItemText(6, QCoreApplication::translate("SettingDialog", "6: 1 ms", nullptr));
        comboBoxMode->setItemText(7, QCoreApplication::translate("SettingDialog", "7: 4 ms", nullptr));
        comboBoxMode->setItemText(8, QCoreApplication::translate("SettingDialog", "8: 10 ms", nullptr));
        comboBoxMode->setItemText(9, QCoreApplication::translate("SettingDialog", "9: 20 ms", nullptr));
        comboBoxMode->setItemText(10, QCoreApplication::translate("SettingDialog", "10: 40 ms", nullptr));

        label_3->setText(QCoreApplication::translate("SettingDialog", "ON/OFF", nullptr));
        checkBoxON->setText(QCoreApplication::translate("SettingDialog", "ON", nullptr));
        label_4->setText(QCoreApplication::translate("SettingDialog", "Power", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("SettingDialog", "Set", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingDialog", "Cancel", nullptr));
        pushButtonIPAddress->setText(QCoreApplication::translate("SettingDialog", "IP address", nullptr));
        label_5->setText(QCoreApplication::translate("SettingDialog", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
