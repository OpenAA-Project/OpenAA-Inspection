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
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QFrame *frameSetting;
    QPushButton *pushButtonOK;
    QFrame *frame_3;
    QPushButton *pushButtonTransfer;
    QProgressBar *progressBar;
    QSpinBox *spinBoxBrightness;
    QLabel *label_2;
    QPushButton *pushButtonSetAll;
    QToolButton *toolButtonON;
    QPushButton *pushButtonShowIO;
    QLineEdit *lineEditVersion;
    QComboBox *comboBoxPatternNo;
    QLabel *label_3;
    QLineEdit *lineEditPatternComment;
    QLabel *label_4;
    QLabel *label_5;
    QCheckBox *checkBoxManual;
    QLabel *label_6;
    QLabel *label_7;
    QComboBox *comboBoxPatternNoOperation;
    QLabel *label_8;
    QComboBox *comboBoxLightNo;
    QLineEdit *lineEditLightComment;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(604, 831);
        frameSetting = new QFrame(SettingDialog);
        frameSetting->setObjectName("frameSetting");
        frameSetting->setGeometry(QRect(10, 190, 361, 571));
        frameSetting->setFrameShape(QFrame::Panel);
        frameSetting->setFrameShadow(QFrame::Sunken);
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(270, 770, 101, 41));
        frame_3 = new QFrame(SettingDialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(380, 190, 201, 571));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        pushButtonTransfer = new QPushButton(frame_3);
        pushButtonTransfer->setObjectName("pushButtonTransfer");
        pushButtonTransfer->setGeometry(QRect(10, 180, 181, 41));
        progressBar = new QProgressBar(frame_3);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(10, 230, 171, 23));
        progressBar->setValue(24);
        spinBoxBrightness = new QSpinBox(frame_3);
        spinBoxBrightness->setObjectName("spinBoxBrightness");
        spinBoxBrightness->setGeometry(QRect(70, 20, 71, 22));
        spinBoxBrightness->setMaximum(1023);
        spinBoxBrightness->setValue(1000);
        label_2 = new QLabel(frame_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 20, 51, 21));
        pushButtonSetAll = new QPushButton(frame_3);
        pushButtonSetAll->setObjectName("pushButtonSetAll");
        pushButtonSetAll->setGeometry(QRect(10, 60, 181, 41));
        toolButtonON = new QToolButton(frame_3);
        toolButtonON->setObjectName("toolButtonON");
        toolButtonON->setGeometry(QRect(10, 280, 181, 61));
        toolButtonON->setCheckable(true);
        toolButtonON->setChecked(true);
        pushButtonShowIO = new QPushButton(frame_3);
        pushButtonShowIO->setObjectName("pushButtonShowIO");
        pushButtonShowIO->setGeometry(QRect(30, 530, 141, 28));
        lineEditVersion = new QLineEdit(SettingDialog);
        lineEditVersion->setObjectName("lineEditVersion");
        lineEditVersion->setGeometry(QRect(10, 10, 581, 21));
        comboBoxPatternNo = new QComboBox(SettingDialog);
        comboBoxPatternNo->addItem(QString());
        comboBoxPatternNo->addItem(QString());
        comboBoxPatternNo->addItem(QString());
        comboBoxPatternNo->addItem(QString());
        comboBoxPatternNo->addItem(QString());
        comboBoxPatternNo->addItem(QString());
        comboBoxPatternNo->addItem(QString());
        comboBoxPatternNo->addItem(QString());
        comboBoxPatternNo->setObjectName("comboBoxPatternNo");
        comboBoxPatternNo->setGeometry(QRect(110, 140, 81, 31));
        label_3 = new QLabel(SettingDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 140, 81, 21));
        lineEditPatternComment = new QLineEdit(SettingDialog);
        lineEditPatternComment->setObjectName("lineEditPatternComment");
        lineEditPatternComment->setGeometry(QRect(200, 150, 161, 21));
        label_4 = new QLabel(SettingDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(250, 80, 71, 21));
        label_5 = new QLabel(SettingDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 40, 361, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        checkBoxManual = new QCheckBox(SettingDialog);
        checkBoxManual->setObjectName("checkBoxManual");
        checkBoxManual->setGeometry(QRect(430, 70, 131, 19));
        label_6 = new QLabel(SettingDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(380, 40, 201, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(SettingDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(420, 100, 81, 21));
        comboBoxPatternNoOperation = new QComboBox(SettingDialog);
        comboBoxPatternNoOperation->addItem(QString());
        comboBoxPatternNoOperation->addItem(QString());
        comboBoxPatternNoOperation->addItem(QString());
        comboBoxPatternNoOperation->addItem(QString());
        comboBoxPatternNoOperation->addItem(QString());
        comboBoxPatternNoOperation->addItem(QString());
        comboBoxPatternNoOperation->addItem(QString());
        comboBoxPatternNoOperation->addItem(QString());
        comboBoxPatternNoOperation->setObjectName("comboBoxPatternNoOperation");
        comboBoxPatternNoOperation->setGeometry(QRect(510, 100, 61, 31));
        label_8 = new QLabel(SettingDialog);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 100, 81, 21));
        comboBoxLightNo = new QComboBox(SettingDialog);
        comboBoxLightNo->addItem(QString());
        comboBoxLightNo->addItem(QString());
        comboBoxLightNo->addItem(QString());
        comboBoxLightNo->addItem(QString());
        comboBoxLightNo->setObjectName("comboBoxLightNo");
        comboBoxLightNo->setGeometry(QRect(110, 100, 81, 31));
        lineEditLightComment = new QLineEdit(SettingDialog);
        lineEditLightComment->setObjectName("lineEditLightComment");
        lineEditLightComment->setGeometry(QRect(200, 110, 161, 21));

        retranslateUi(SettingDialog);

        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        pushButtonTransfer->setText(QCoreApplication::translate("SettingDialog", "Transfer", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "Value", nullptr));
        pushButtonSetAll->setText(QCoreApplication::translate("SettingDialog", "Set all in this pattern", nullptr));
        toolButtonON->setText(QCoreApplication::translate("SettingDialog", "ON", nullptr));
        pushButtonShowIO->setText(QCoreApplication::translate("SettingDialog", "Show I/O", nullptr));
        comboBoxPatternNo->setItemText(0, QCoreApplication::translate("SettingDialog", "No 0", nullptr));
        comboBoxPatternNo->setItemText(1, QCoreApplication::translate("SettingDialog", "No 1", nullptr));
        comboBoxPatternNo->setItemText(2, QCoreApplication::translate("SettingDialog", "No 2", nullptr));
        comboBoxPatternNo->setItemText(3, QCoreApplication::translate("SettingDialog", "No 3", nullptr));
        comboBoxPatternNo->setItemText(4, QCoreApplication::translate("SettingDialog", "No 4", nullptr));
        comboBoxPatternNo->setItemText(5, QCoreApplication::translate("SettingDialog", "No 5", nullptr));
        comboBoxPatternNo->setItemText(6, QCoreApplication::translate("SettingDialog", "No 6", nullptr));
        comboBoxPatternNo->setItemText(7, QCoreApplication::translate("SettingDialog", "No 7", nullptr));

        label_3->setText(QCoreApplication::translate("SettingDialog", "Pattern No", nullptr));
        label_4->setText(QCoreApplication::translate("SettingDialog", "Comment", nullptr));
        label_5->setText(QCoreApplication::translate("SettingDialog", "Registration", nullptr));
        checkBoxManual->setText(QCoreApplication::translate("SettingDialog", "Manual control", nullptr));
        label_6->setText(QCoreApplication::translate("SettingDialog", "Operation", nullptr));
        label_7->setText(QCoreApplication::translate("SettingDialog", "Pattern No", nullptr));
        comboBoxPatternNoOperation->setItemText(0, QCoreApplication::translate("SettingDialog", "No 0", nullptr));
        comboBoxPatternNoOperation->setItemText(1, QCoreApplication::translate("SettingDialog", "No 1", nullptr));
        comboBoxPatternNoOperation->setItemText(2, QCoreApplication::translate("SettingDialog", "No 2", nullptr));
        comboBoxPatternNoOperation->setItemText(3, QCoreApplication::translate("SettingDialog", "No 3", nullptr));
        comboBoxPatternNoOperation->setItemText(4, QCoreApplication::translate("SettingDialog", "No 4", nullptr));
        comboBoxPatternNoOperation->setItemText(5, QCoreApplication::translate("SettingDialog", "No 5", nullptr));
        comboBoxPatternNoOperation->setItemText(6, QCoreApplication::translate("SettingDialog", "No 6", nullptr));
        comboBoxPatternNoOperation->setItemText(7, QCoreApplication::translate("SettingDialog", "No 7", nullptr));

        label_8->setText(QCoreApplication::translate("SettingDialog", "Light No", nullptr));
        comboBoxLightNo->setItemText(0, QCoreApplication::translate("SettingDialog", "Light 1", nullptr));
        comboBoxLightNo->setItemText(1, QCoreApplication::translate("SettingDialog", "Light 2", nullptr));
        comboBoxLightNo->setItemText(2, QCoreApplication::translate("SettingDialog", "Light 3", nullptr));
        comboBoxLightNo->setItemText(3, QCoreApplication::translate("SettingDialog", "Light 4", nullptr));

    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
