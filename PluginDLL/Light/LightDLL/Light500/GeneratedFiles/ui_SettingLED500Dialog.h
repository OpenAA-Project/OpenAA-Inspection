/********************************************************************************
** Form generated from reading UI file 'SettingLED500Dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGLED500DIALOG_H
#define UI_SETTINGLED500DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SettingLED500Dialog
{
public:
    QComboBox *comboBoxComm;
    QLabel *label_4;
    QFrame *frame;
    QComboBox *comboBoxLeft;
    QSpinBox *spinBoxLBar2;
    QSpinBox *spinBoxLBar4;
    QSpinBox *spinBoxLBar5;
    QSpinBox *spinBoxLBar3;
    QSpinBox *spinBoxLBar0;
    QSpinBox *spinBoxLBar6;
    QSpinBox *spinBoxLBar1;
    QLabel *label_5;
    QFrame *frame_2;
    QComboBox *comboBoxRight;
    QLabel *label_6;
    QSpinBox *spinBoxRBar6;
    QSpinBox *spinBoxRBar0;
    QSpinBox *spinBoxRBar2;
    QSpinBox *spinBoxRBar4;
    QSpinBox *spinBoxRBar1;
    QSpinBox *spinBoxRBar3;
    QSpinBox *spinBoxRBar5;
    QFrame *frame_3;
    QCheckBox *checkBoxSyncMode;
    QLabel *label;
    QSpinBox *spinBoxSyncForward;
    QSpinBox *spinBoxSyncPulsePerBar;
    QLabel *label_2;
    QSpinBox *spinBoxSyncBackward;
    QLabel *label_3;
    QPushButton *pushButtonSetAll;
    QSpinBox *spinBoxAll;
    QPushButton *pushButtonClose;
    QToolButton *toolButtonOnOff;
    QPushButton *pushButtonTransfer;
    QProgressBar *progressBar;
    QPushButton *pushButtonSetLeft;
    QPushButton *pushButtonSetRight;
    QSpinBox *spinBoxLeft;
    QSpinBox *spinBoxRight;
    QLabel *label_7;
    QDoubleSpinBox *dsbGradValue;

    void setupUi(QDialog *SettingLED500Dialog)
    {
        if (SettingLED500Dialog->objectName().isEmpty())
            SettingLED500Dialog->setObjectName("SettingLED500Dialog");
        SettingLED500Dialog->resize(512, 424);
        comboBoxComm = new QComboBox(SettingLED500Dialog);
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->addItem(QString());
        comboBoxComm->setObjectName("comboBoxComm");
        comboBoxComm->setGeometry(QRect(20, 140, 74, 22));
        label_4 = new QLabel(SettingLED500Dialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 120, 81, 16));
        frame = new QFrame(SettingLED500Dialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(140, 120, 111, 281));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        comboBoxLeft = new QComboBox(frame);
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->setObjectName("comboBoxLeft");
        comboBoxLeft->setGeometry(QRect(20, 30, 74, 22));
        spinBoxLBar2 = new QSpinBox(frame);
        spinBoxLBar2->setObjectName("spinBoxLBar2");
        spinBoxLBar2->setGeometry(QRect(20, 120, 71, 21));
        spinBoxLBar2->setMaximum(4095);
        spinBoxLBar4 = new QSpinBox(frame);
        spinBoxLBar4->setObjectName("spinBoxLBar4");
        spinBoxLBar4->setGeometry(QRect(20, 180, 71, 21));
        spinBoxLBar4->setMaximum(4095);
        spinBoxLBar5 = new QSpinBox(frame);
        spinBoxLBar5->setObjectName("spinBoxLBar5");
        spinBoxLBar5->setGeometry(QRect(20, 210, 71, 21));
        spinBoxLBar5->setMaximum(4095);
        spinBoxLBar3 = new QSpinBox(frame);
        spinBoxLBar3->setObjectName("spinBoxLBar3");
        spinBoxLBar3->setGeometry(QRect(20, 150, 71, 21));
        spinBoxLBar3->setMaximum(4095);
        spinBoxLBar0 = new QSpinBox(frame);
        spinBoxLBar0->setObjectName("spinBoxLBar0");
        spinBoxLBar0->setGeometry(QRect(20, 60, 71, 21));
        spinBoxLBar0->setMaximum(4095);
        spinBoxLBar6 = new QSpinBox(frame);
        spinBoxLBar6->setObjectName("spinBoxLBar6");
        spinBoxLBar6->setGeometry(QRect(20, 240, 71, 21));
        spinBoxLBar6->setMaximum(4095);
        spinBoxLBar1 = new QSpinBox(frame);
        spinBoxLBar1->setObjectName("spinBoxLBar1");
        spinBoxLBar1->setGeometry(QRect(20, 90, 71, 21));
        spinBoxLBar1->setMaximum(4095);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 0, 111, 16));
        label_5->setAlignment(Qt::AlignCenter);
        frame_2 = new QFrame(SettingLED500Dialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(270, 120, 111, 281));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        comboBoxRight = new QComboBox(frame_2);
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->setObjectName("comboBoxRight");
        comboBoxRight->setGeometry(QRect(20, 30, 74, 22));
        label_6 = new QLabel(frame_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 0, 111, 16));
        label_6->setAlignment(Qt::AlignCenter);
        spinBoxRBar6 = new QSpinBox(frame_2);
        spinBoxRBar6->setObjectName("spinBoxRBar6");
        spinBoxRBar6->setGeometry(QRect(20, 240, 71, 21));
        spinBoxRBar6->setMaximum(4095);
        spinBoxRBar0 = new QSpinBox(frame_2);
        spinBoxRBar0->setObjectName("spinBoxRBar0");
        spinBoxRBar0->setGeometry(QRect(20, 60, 71, 21));
        spinBoxRBar0->setMaximum(4095);
        spinBoxRBar2 = new QSpinBox(frame_2);
        spinBoxRBar2->setObjectName("spinBoxRBar2");
        spinBoxRBar2->setGeometry(QRect(20, 120, 71, 21));
        spinBoxRBar2->setMaximum(4095);
        spinBoxRBar4 = new QSpinBox(frame_2);
        spinBoxRBar4->setObjectName("spinBoxRBar4");
        spinBoxRBar4->setGeometry(QRect(20, 180, 71, 21));
        spinBoxRBar4->setMaximum(4095);
        spinBoxRBar1 = new QSpinBox(frame_2);
        spinBoxRBar1->setObjectName("spinBoxRBar1");
        spinBoxRBar1->setGeometry(QRect(20, 90, 71, 21));
        spinBoxRBar1->setMaximum(4095);
        spinBoxRBar3 = new QSpinBox(frame_2);
        spinBoxRBar3->setObjectName("spinBoxRBar3");
        spinBoxRBar3->setGeometry(QRect(20, 150, 71, 21));
        spinBoxRBar3->setMaximum(4095);
        spinBoxRBar5 = new QSpinBox(frame_2);
        spinBoxRBar5->setObjectName("spinBoxRBar5");
        spinBoxRBar5->setGeometry(QRect(20, 210, 71, 21));
        spinBoxRBar5->setMaximum(4095);
        frame_3 = new QFrame(SettingLED500Dialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 10, 371, 91));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        checkBoxSyncMode = new QCheckBox(frame_3);
        checkBoxSyncMode->setObjectName("checkBoxSyncMode");
        checkBoxSyncMode->setGeometry(QRect(10, 10, 141, 17));
        label = new QLabel(frame_3);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 40, 121, 16));
        spinBoxSyncForward = new QSpinBox(frame_3);
        spinBoxSyncForward->setObjectName("spinBoxSyncForward");
        spinBoxSyncForward->setGeometry(QRect(10, 60, 111, 22));
        spinBoxSyncForward->setMaximum(99999999);
        spinBoxSyncPulsePerBar = new QSpinBox(frame_3);
        spinBoxSyncPulsePerBar->setObjectName("spinBoxSyncPulsePerBar");
        spinBoxSyncPulsePerBar->setGeometry(QRect(130, 60, 111, 22));
        spinBoxSyncPulsePerBar->setMaximum(99999999);
        label_2 = new QLabel(frame_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 40, 111, 16));
        spinBoxSyncBackward = new QSpinBox(frame_3);
        spinBoxSyncBackward->setObjectName("spinBoxSyncBackward");
        spinBoxSyncBackward->setGeometry(QRect(250, 60, 111, 22));
        spinBoxSyncBackward->setMaximum(99999999);
        label_3 = new QLabel(frame_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(250, 40, 111, 16));
        pushButtonSetAll = new QPushButton(SettingLED500Dialog);
        pushButtonSetAll->setObjectName("pushButtonSetAll");
        pushButtonSetAll->setGeometry(QRect(400, 140, 91, 31));
        spinBoxAll = new QSpinBox(SettingLED500Dialog);
        spinBoxAll->setObjectName("spinBoxAll");
        spinBoxAll->setGeometry(QRect(400, 170, 91, 21));
        spinBoxAll->setMaximum(4095);
        pushButtonClose = new QPushButton(SettingLED500Dialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(400, 350, 91, 51));
        toolButtonOnOff = new QToolButton(SettingLED500Dialog);
        toolButtonOnOff->setObjectName("toolButtonOnOff");
        toolButtonOnOff->setGeometry(QRect(400, 270, 91, 41));
        toolButtonOnOff->setCheckable(true);
        toolButtonOnOff->setChecked(false);
        pushButtonTransfer = new QPushButton(SettingLED500Dialog);
        pushButtonTransfer->setObjectName("pushButtonTransfer");
        pushButtonTransfer->setGeometry(QRect(400, 200, 91, 31));
        progressBar = new QProgressBar(SettingLED500Dialog);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(400, 230, 101, 23));
        progressBar->setValue(24);
        pushButtonSetLeft = new QPushButton(SettingLED500Dialog);
        pushButtonSetLeft->setObjectName("pushButtonSetLeft");
        pushButtonSetLeft->setGeometry(QRect(400, 20, 93, 28));
        pushButtonSetRight = new QPushButton(SettingLED500Dialog);
        pushButtonSetRight->setObjectName("pushButtonSetRight");
        pushButtonSetRight->setGeometry(QRect(400, 80, 93, 28));
        spinBoxLeft = new QSpinBox(SettingLED500Dialog);
        spinBoxLeft->setObjectName("spinBoxLeft");
        spinBoxLeft->setGeometry(QRect(400, 50, 91, 22));
        spinBoxLeft->setMaximum(4095);
        spinBoxRight = new QSpinBox(SettingLED500Dialog);
        spinBoxRight->setObjectName("spinBoxRight");
        spinBoxRight->setGeometry(QRect(400, 110, 91, 22));
        spinBoxRight->setMaximum(4095);
        label_7 = new QLabel(SettingLED500Dialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 210, 71, 16));
        dsbGradValue = new QDoubleSpinBox(SettingLED500Dialog);
        dsbGradValue->setObjectName("dsbGradValue");
        dsbGradValue->setGeometry(QRect(30, 240, 62, 22));
        dsbGradValue->setValue(1.000000000000000);

        retranslateUi(SettingLED500Dialog);

        QMetaObject::connectSlotsByName(SettingLED500Dialog);
    } // setupUi

    void retranslateUi(QDialog *SettingLED500Dialog)
    {
        SettingLED500Dialog->setWindowTitle(QCoreApplication::translate("SettingLED500Dialog", "Dialog", nullptr));
        comboBoxComm->setItemText(0, QCoreApplication::translate("SettingLED500Dialog", "COM1", nullptr));
        comboBoxComm->setItemText(1, QCoreApplication::translate("SettingLED500Dialog", "COM2", nullptr));
        comboBoxComm->setItemText(2, QCoreApplication::translate("SettingLED500Dialog", "COM3", nullptr));
        comboBoxComm->setItemText(3, QCoreApplication::translate("SettingLED500Dialog", "COM4", nullptr));
        comboBoxComm->setItemText(4, QCoreApplication::translate("SettingLED500Dialog", "COM5", nullptr));
        comboBoxComm->setItemText(5, QCoreApplication::translate("SettingLED500Dialog", "COM6", nullptr));
        comboBoxComm->setItemText(6, QCoreApplication::translate("SettingLED500Dialog", "COM7", nullptr));
        comboBoxComm->setItemText(7, QCoreApplication::translate("SettingLED500Dialog", "COM8", nullptr));
        comboBoxComm->setItemText(8, QCoreApplication::translate("SettingLED500Dialog", "COM9", nullptr));
        comboBoxComm->setItemText(9, QCoreApplication::translate("SettingLED500Dialog", "COM10", nullptr));
        comboBoxComm->setItemText(10, QCoreApplication::translate("SettingLED500Dialog", "COM11", nullptr));
        comboBoxComm->setItemText(11, QCoreApplication::translate("SettingLED500Dialog", "COM12", nullptr));
        comboBoxComm->setItemText(12, QCoreApplication::translate("SettingLED500Dialog", "COM13", nullptr));
        comboBoxComm->setItemText(13, QCoreApplication::translate("SettingLED500Dialog", "COM14", nullptr));
        comboBoxComm->setItemText(14, QCoreApplication::translate("SettingLED500Dialog", "COM15", nullptr));
        comboBoxComm->setItemText(15, QCoreApplication::translate("SettingLED500Dialog", "COM16", nullptr));
        comboBoxComm->setItemText(16, QCoreApplication::translate("SettingLED500Dialog", "COM17", nullptr));
        comboBoxComm->setItemText(17, QCoreApplication::translate("SettingLED500Dialog", "COM18", nullptr));
        comboBoxComm->setItemText(18, QCoreApplication::translate("SettingLED500Dialog", "COM19", nullptr));
        comboBoxComm->setItemText(19, QCoreApplication::translate("SettingLED500Dialog", "COM20", nullptr));

        label_4->setText(QCoreApplication::translate("SettingLED500Dialog", "\351\200\232\344\277\241\343\203\235\343\203\274\343\203\210", nullptr));
        comboBoxLeft->setItemText(0, QCoreApplication::translate("SettingLED500Dialog", "Bar-0", nullptr));
        comboBoxLeft->setItemText(1, QCoreApplication::translate("SettingLED500Dialog", "Bar-1", nullptr));
        comboBoxLeft->setItemText(2, QCoreApplication::translate("SettingLED500Dialog", "Bar-2", nullptr));
        comboBoxLeft->setItemText(3, QCoreApplication::translate("SettingLED500Dialog", "Bar-3", nullptr));
        comboBoxLeft->setItemText(4, QCoreApplication::translate("SettingLED500Dialog", "Bar-4", nullptr));
        comboBoxLeft->setItemText(5, QCoreApplication::translate("SettingLED500Dialog", "Bar-5", nullptr));
        comboBoxLeft->setItemText(6, QCoreApplication::translate("SettingLED500Dialog", "Bar-6", nullptr));
        comboBoxLeft->setItemText(7, QCoreApplication::translate("SettingLED500Dialog", "Bar-7", nullptr));
        comboBoxLeft->setItemText(8, QCoreApplication::translate("SettingLED500Dialog", "Bar-8", nullptr));
        comboBoxLeft->setItemText(9, QCoreApplication::translate("SettingLED500Dialog", "Bar-9", nullptr));
        comboBoxLeft->setItemText(10, QCoreApplication::translate("SettingLED500Dialog", "Bar-10", nullptr));
        comboBoxLeft->setItemText(11, QCoreApplication::translate("SettingLED500Dialog", "Bar-11", nullptr));
        comboBoxLeft->setItemText(12, QCoreApplication::translate("SettingLED500Dialog", "Bar-12", nullptr));
        comboBoxLeft->setItemText(13, QCoreApplication::translate("SettingLED500Dialog", "Bar-13", nullptr));
        comboBoxLeft->setItemText(14, QCoreApplication::translate("SettingLED500Dialog", "Bar-14", nullptr));

        label_5->setText(QCoreApplication::translate("SettingLED500Dialog", "Left", nullptr));
        comboBoxRight->setItemText(0, QCoreApplication::translate("SettingLED500Dialog", "Bar-15", nullptr));
        comboBoxRight->setItemText(1, QCoreApplication::translate("SettingLED500Dialog", "Bar-16", nullptr));
        comboBoxRight->setItemText(2, QCoreApplication::translate("SettingLED500Dialog", "Bar-17", nullptr));
        comboBoxRight->setItemText(3, QCoreApplication::translate("SettingLED500Dialog", "Bar-18", nullptr));
        comboBoxRight->setItemText(4, QCoreApplication::translate("SettingLED500Dialog", "Bar-19", nullptr));
        comboBoxRight->setItemText(5, QCoreApplication::translate("SettingLED500Dialog", "Bar-20", nullptr));
        comboBoxRight->setItemText(6, QCoreApplication::translate("SettingLED500Dialog", "Bar-21", nullptr));
        comboBoxRight->setItemText(7, QCoreApplication::translate("SettingLED500Dialog", "Bar-22", nullptr));
        comboBoxRight->setItemText(8, QCoreApplication::translate("SettingLED500Dialog", "Bar-23", nullptr));
        comboBoxRight->setItemText(9, QCoreApplication::translate("SettingLED500Dialog", "Bar-24", nullptr));
        comboBoxRight->setItemText(10, QCoreApplication::translate("SettingLED500Dialog", "Bar-25", nullptr));
        comboBoxRight->setItemText(11, QCoreApplication::translate("SettingLED500Dialog", "Bar-26", nullptr));
        comboBoxRight->setItemText(12, QCoreApplication::translate("SettingLED500Dialog", "Bar-27", nullptr));
        comboBoxRight->setItemText(13, QCoreApplication::translate("SettingLED500Dialog", "Bar-28", nullptr));
        comboBoxRight->setItemText(14, QCoreApplication::translate("SettingLED500Dialog", "Bar-29", nullptr));

        label_6->setText(QCoreApplication::translate("SettingLED500Dialog", "Right", nullptr));
        checkBoxSyncMode->setText(QCoreApplication::translate("SettingLED500Dialog", "\345\205\245\345\212\233\345\220\214\346\234\237\347\202\271\347\201\257", nullptr));
        label->setText(QCoreApplication::translate("SettingLED500Dialog", "\345\211\215\346\226\271\347\204\241\345\212\271\345\214\272\351\226\223\343\203\221\343\203\253\343\202\271", nullptr));
        label_2->setText(QCoreApplication::translate("SettingLED500Dialog", "LED\351\200\201\343\202\212\343\203\221\343\203\253\343\202\271", nullptr));
        label_3->setText(QCoreApplication::translate("SettingLED500Dialog", "\345\276\214\346\226\271\347\204\241\345\212\271\343\203\221\343\203\253\343\202\271", nullptr));
        pushButtonSetAll->setText(QCoreApplication::translate("SettingLED500Dialog", "Set all", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SettingLED500Dialog", "Close", nullptr));
        toolButtonOnOff->setText(QCoreApplication::translate("SettingLED500Dialog", "ON/OFF", nullptr));
        pushButtonTransfer->setText(QCoreApplication::translate("SettingLED500Dialog", "Transfer", nullptr));
        pushButtonSetLeft->setText(QCoreApplication::translate("SettingLED500Dialog", "Set Left", nullptr));
        pushButtonSetRight->setText(QCoreApplication::translate("SettingLED500Dialog", "Set Right", nullptr));
        label_7->setText(QCoreApplication::translate("SettingLED500Dialog", "Grad value", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingLED500Dialog: public Ui_SettingLED500Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGLED500DIALOG_H
