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
    QFrame *frame;
    QToolButton *toolButtonRed;
    QToolButton *toolButtonGreen;
    QToolButton *toolButtonBlue;
    QFrame *frameSetting;
    QPushButton *pushButtonOK;
    QFrame *frame_3;
    QPushButton *pushButtonTransfer;
    QProgressBar *progressBar;
    QSpinBox *spinBoxBrightness;
    QLabel *label_2;
    QPushButton *pushButtonSetAll;
    QToolButton *toolButtonON;
    QPushButton *pushButtonWriteEPROM;
    QPushButton *pushButtonShowIO;
    QPushButton *pushButtonTemporaryON;
    QLineEdit *lineEditVersion;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(604, 758);
        frame = new QFrame(SettingDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 50, 571, 51));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        toolButtonRed = new QToolButton(frame);
        toolButtonRed->setObjectName("toolButtonRed");
        toolButtonRed->setGeometry(QRect(10, 10, 101, 31));
        toolButtonRed->setCheckable(true);
        toolButtonRed->setChecked(true);
        toolButtonRed->setAutoExclusive(true);
        toolButtonGreen = new QToolButton(frame);
        toolButtonGreen->setObjectName("toolButtonGreen");
        toolButtonGreen->setGeometry(QRect(120, 10, 101, 31));
        toolButtonGreen->setCheckable(true);
        toolButtonGreen->setAutoExclusive(true);
        toolButtonBlue = new QToolButton(frame);
        toolButtonBlue->setObjectName("toolButtonBlue");
        toolButtonBlue->setGeometry(QRect(230, 10, 111, 31));
        toolButtonBlue->setCheckable(true);
        toolButtonBlue->setAutoExclusive(true);
        frameSetting = new QFrame(SettingDialog);
        frameSetting->setObjectName("frameSetting");
        frameSetting->setGeometry(QRect(10, 110, 361, 571));
        frameSetting->setFrameShape(QFrame::Panel);
        frameSetting->setFrameShadow(QFrame::Sunken);
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(240, 690, 101, 41));
        frame_3 = new QFrame(SettingDialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(380, 110, 201, 571));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        pushButtonTransfer = new QPushButton(frame_3);
        pushButtonTransfer->setObjectName("pushButtonTransfer");
        pushButtonTransfer->setGeometry(QRect(10, 180, 93, 41));
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
        pushButtonSetAll->setGeometry(QRect(30, 60, 141, 41));
        toolButtonON = new QToolButton(frame_3);
        toolButtonON->setObjectName("toolButtonON");
        toolButtonON->setGeometry(QRect(10, 280, 181, 61));
        toolButtonON->setCheckable(true);
        toolButtonON->setChecked(true);
        pushButtonWriteEPROM = new QPushButton(frame_3);
        pushButtonWriteEPROM->setObjectName("pushButtonWriteEPROM");
        pushButtonWriteEPROM->setGeometry(QRect(30, 500, 141, 28));
        pushButtonShowIO = new QPushButton(frame_3);
        pushButtonShowIO->setObjectName("pushButtonShowIO");
        pushButtonShowIO->setGeometry(QRect(30, 530, 141, 28));
        pushButtonTemporaryON = new QPushButton(frame_3);
        pushButtonTemporaryON->setObjectName("pushButtonTemporaryON");
        pushButtonTemporaryON->setGeometry(QRect(10, 370, 181, 51));
        lineEditVersion = new QLineEdit(SettingDialog);
        lineEditVersion->setObjectName("lineEditVersion");
        lineEditVersion->setGeometry(QRect(10, 10, 581, 21));

        retranslateUi(SettingDialog);

        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Dialog", nullptr));
        toolButtonRed->setText(QCoreApplication::translate("SettingDialog", "Red", nullptr));
        toolButtonGreen->setText(QCoreApplication::translate("SettingDialog", "Green", nullptr));
        toolButtonBlue->setText(QCoreApplication::translate("SettingDialog", "Blue", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        pushButtonTransfer->setText(QCoreApplication::translate("SettingDialog", "Transfer", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "Value", nullptr));
        pushButtonSetAll->setText(QCoreApplication::translate("SettingDialog", "Set all", nullptr));
        toolButtonON->setText(QCoreApplication::translate("SettingDialog", "ON", nullptr));
        pushButtonWriteEPROM->setText(QCoreApplication::translate("SettingDialog", "Write EPROM", nullptr));
        pushButtonShowIO->setText(QCoreApplication::translate("SettingDialog", "Show I/O", nullptr));
        pushButtonTemporaryON->setText(QCoreApplication::translate("SettingDialog", "Temporary ON", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
