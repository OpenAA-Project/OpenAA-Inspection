/********************************************************************************
** Form generated from reading UI file 'SettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.11
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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QComboBox *comboBoxType;
    QLabel *label;
    QSpinBox *spinBoxBoardCount;
    QFrame *frame;
    QLabel *label_3;
    QLineEdit *lineEditConfigFileName;
    QPushButton *pushButtonConfigFileName;
    QLabel *label_4;
    QSpinBox *spinBoxBoardLineClock;
    QFrame *frame_2;
    QLabel *label_6;
    QComboBox *comboBoxResolution;
    QLabel *label_5;
    QCheckBox *checkBoxOuterTriggerMode;
    QLabel *label_7;
    QComboBox *comboBoxLEDControl;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinBoxLEDDutyFull;
    QDoubleSpinBox *doubleSpinBoxLEDDutyA;
    QDoubleSpinBox *doubleSpinBoxLEDDutyB;
    QLabel *label_11;
    QComboBox *comboBoxLEDDivide;
    QCheckBox *checkBoxGainMode;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QDoubleSpinBox *doubleSpinBoxGainRed;
    QDoubleSpinBox *doubleSpinBoxGainGreen;
    QDoubleSpinBox *doubleSpinBoxGainBlue;
    QCheckBox *checkBoxScanDirection;
    QCheckBox *checkBoxGamma;
    QSpinBox *spinBoxEvenOffsetY;
    QLabel *label_15;
    QLabel *label_16;
    QSpinBox *spinBoxOddOffsetY;
    QPushButton *pushButtonAdjustWhite;
    QPushButton *pushButtonAdjustBlack;
    QCheckBox *checkBoxModeAdjustWhite;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName(QString::fromUtf8("SettingDialog"));
        SettingDialog->resize(400, 799);
        comboBoxType = new QComboBox(SettingDialog);
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->setObjectName(QString::fromUtf8("comboBoxType"));
        comboBoxType->setGeometry(QRect(10, 10, 141, 24));
        label = new QLabel(SettingDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(190, 10, 75, 21));
        spinBoxBoardCount = new QSpinBox(SettingDialog);
        spinBoxBoardCount->setObjectName(QString::fromUtf8("spinBoxBoardCount"));
        spinBoxBoardCount->setGeometry(QRect(270, 10, 54, 24));
        spinBoxBoardCount->setReadOnly(true);
        frame = new QFrame(SettingDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 50, 381, 71));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 0, 141, 21));
        lineEditConfigFileName = new QLineEdit(frame);
        lineEditConfigFileName->setObjectName(QString::fromUtf8("lineEditConfigFileName"));
        lineEditConfigFileName->setGeometry(QRect(10, 23, 311, 31));
        pushButtonConfigFileName = new QPushButton(frame);
        pushButtonConfigFileName->setObjectName(QString::fromUtf8("pushButtonConfigFileName"));
        pushButtonConfigFileName->setGeometry(QRect(330, 20, 41, 34));
        label_4 = new QLabel(SettingDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 130, 161, 21));
        spinBoxBoardLineClock = new QSpinBox(SettingDialog);
        spinBoxBoardLineClock->setObjectName(QString::fromUtf8("spinBoxBoardLineClock"));
        spinBoxBoardLineClock->setGeometry(QRect(200, 130, 121, 24));
        spinBoxBoardLineClock->setMaximum(99999999);
        frame_2 = new QFrame(SettingDialog);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(10, 180, 381, 561));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 0, 141, 21));
        comboBoxResolution = new QComboBox(frame_2);
        comboBoxResolution->addItem(QString());
        comboBoxResolution->addItem(QString());
        comboBoxResolution->addItem(QString());
        comboBoxResolution->setObjectName(QString::fromUtf8("comboBoxResolution"));
        comboBoxResolution->setGeometry(QRect(200, 30, 121, 24));
        label_5 = new QLabel(frame_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 30, 161, 21));
        checkBoxOuterTriggerMode = new QCheckBox(frame_2);
        checkBoxOuterTriggerMode->setObjectName(QString::fromUtf8("checkBoxOuterTriggerMode"));
        checkBoxOuterTriggerMode->setGeometry(QRect(30, 60, 211, 22));
        checkBoxOuterTriggerMode->setIconSize(QSize(24, 24));
        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 100, 91, 21));
        comboBoxLEDControl = new QComboBox(frame_2);
        comboBoxLEDControl->addItem(QString());
        comboBoxLEDControl->addItem(QString());
        comboBoxLEDControl->addItem(QString());
        comboBoxLEDControl->addItem(QString());
        comboBoxLEDControl->setObjectName(QString::fromUtf8("comboBoxLEDControl"));
        comboBoxLEDControl->setGeometry(QRect(200, 100, 121, 24));
        label_8 = new QLabel(frame_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 130, 231, 21));
        label_9 = new QLabel(frame_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 160, 231, 21));
        label_10 = new QLabel(frame_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 190, 231, 21));
        doubleSpinBoxLEDDutyFull = new QDoubleSpinBox(frame_2);
        doubleSpinBoxLEDDutyFull->setObjectName(QString::fromUtf8("doubleSpinBoxLEDDutyFull"));
        doubleSpinBoxLEDDutyFull->setGeometry(QRect(270, 130, 91, 24));
        doubleSpinBoxLEDDutyFull->setDecimals(1);
        doubleSpinBoxLEDDutyFull->setMaximum(65535.000000000000000);
        doubleSpinBoxLEDDutyFull->setValue(1000.000000000000000);
        doubleSpinBoxLEDDutyA = new QDoubleSpinBox(frame_2);
        doubleSpinBoxLEDDutyA->setObjectName(QString::fromUtf8("doubleSpinBoxLEDDutyA"));
        doubleSpinBoxLEDDutyA->setGeometry(QRect(270, 160, 91, 24));
        doubleSpinBoxLEDDutyA->setDecimals(1);
        doubleSpinBoxLEDDutyA->setMaximum(65535.000000000000000);
        doubleSpinBoxLEDDutyA->setValue(500.000000000000000);
        doubleSpinBoxLEDDutyB = new QDoubleSpinBox(frame_2);
        doubleSpinBoxLEDDutyB->setObjectName(QString::fromUtf8("doubleSpinBoxLEDDutyB"));
        doubleSpinBoxLEDDutyB->setGeometry(QRect(270, 190, 91, 24));
        doubleSpinBoxLEDDutyB->setDecimals(1);
        doubleSpinBoxLEDDutyB->setMaximum(65535.000000000000000);
        doubleSpinBoxLEDDutyB->setValue(500.000000000000000);
        label_11 = new QLabel(frame_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(30, 220, 171, 21));
        comboBoxLEDDivide = new QComboBox(frame_2);
        comboBoxLEDDivide->addItem(QString());
        comboBoxLEDDivide->addItem(QString());
        comboBoxLEDDivide->addItem(QString());
        comboBoxLEDDivide->addItem(QString());
        comboBoxLEDDivide->setObjectName(QString::fromUtf8("comboBoxLEDDivide"));
        comboBoxLEDDivide->setGeometry(QRect(200, 220, 121, 24));
        checkBoxGainMode = new QCheckBox(frame_2);
        checkBoxGainMode->setObjectName(QString::fromUtf8("checkBoxGainMode"));
        checkBoxGainMode->setGeometry(QRect(30, 260, 171, 22));
        checkBoxGainMode->setIconSize(QSize(24, 24));
        label_12 = new QLabel(frame_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(60, 290, 41, 21));
        label_13 = new QLabel(frame_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(60, 320, 41, 21));
        label_14 = new QLabel(frame_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(60, 350, 41, 21));
        doubleSpinBoxGainRed = new QDoubleSpinBox(frame_2);
        doubleSpinBoxGainRed->setObjectName(QString::fromUtf8("doubleSpinBoxGainRed"));
        doubleSpinBoxGainRed->setGeometry(QRect(90, 290, 71, 24));
        doubleSpinBoxGainRed->setDecimals(2);
        doubleSpinBoxGainRed->setMaximum(4.000000000000000);
        doubleSpinBoxGainRed->setValue(1.000000000000000);
        doubleSpinBoxGainGreen = new QDoubleSpinBox(frame_2);
        doubleSpinBoxGainGreen->setObjectName(QString::fromUtf8("doubleSpinBoxGainGreen"));
        doubleSpinBoxGainGreen->setGeometry(QRect(90, 320, 71, 24));
        doubleSpinBoxGainGreen->setDecimals(2);
        doubleSpinBoxGainGreen->setMaximum(4.000000000000000);
        doubleSpinBoxGainGreen->setValue(1.000000000000000);
        doubleSpinBoxGainBlue = new QDoubleSpinBox(frame_2);
        doubleSpinBoxGainBlue->setObjectName(QString::fromUtf8("doubleSpinBoxGainBlue"));
        doubleSpinBoxGainBlue->setGeometry(QRect(90, 350, 71, 24));
        doubleSpinBoxGainBlue->setDecimals(2);
        doubleSpinBoxGainBlue->setMaximum(4.000000000000000);
        doubleSpinBoxGainBlue->setValue(1.000000000000000);
        checkBoxScanDirection = new QCheckBox(frame_2);
        checkBoxScanDirection->setObjectName(QString::fromUtf8("checkBoxScanDirection"));
        checkBoxScanDirection->setGeometry(QRect(30, 390, 171, 22));
        checkBoxScanDirection->setIconSize(QSize(24, 24));
        checkBoxGamma = new QCheckBox(frame_2);
        checkBoxGamma->setObjectName(QString::fromUtf8("checkBoxGamma"));
        checkBoxGamma->setGeometry(QRect(30, 420, 171, 22));
        checkBoxGamma->setIconSize(QSize(24, 24));
        spinBoxEvenOffsetY = new QSpinBox(frame_2);
        spinBoxEvenOffsetY->setObjectName(QString::fromUtf8("spinBoxEvenOffsetY"));
        spinBoxEvenOffsetY->setGeometry(QRect(220, 460, 61, 24));
        spinBoxEvenOffsetY->setMaximum(999);
        label_15 = new QLabel(frame_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(30, 460, 181, 21));
        label_16 = new QLabel(frame_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(30, 490, 181, 21));
        spinBoxOddOffsetY = new QSpinBox(frame_2);
        spinBoxOddOffsetY->setObjectName(QString::fromUtf8("spinBoxOddOffsetY"));
        spinBoxOddOffsetY->setGeometry(QRect(220, 490, 61, 24));
        spinBoxOddOffsetY->setMaximum(999);
        pushButtonAdjustWhite = new QPushButton(frame_2);
        pushButtonAdjustWhite->setObjectName(QString::fromUtf8("pushButtonAdjustWhite"));
        pushButtonAdjustWhite->setGeometry(QRect(240, 310, 112, 34));
        pushButtonAdjustBlack = new QPushButton(frame_2);
        pushButtonAdjustBlack->setObjectName(QString::fromUtf8("pushButtonAdjustBlack"));
        pushButtonAdjustBlack->setGeometry(QRect(240, 270, 112, 34));
        checkBoxModeAdjustWhite = new QCheckBox(frame_2);
        checkBoxModeAdjustWhite->setObjectName(QString::fromUtf8("checkBoxModeAdjustWhite"));
        checkBoxModeAdjustWhite->setGeometry(QRect(240, 360, 121, 22));
        checkBoxModeAdjustWhite->setIconSize(QSize(24, 24));
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(40, 750, 112, 34));
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(270, 750, 112, 34));

        retranslateUi(SettingDialog);

        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Dialog", nullptr));
        comboBoxType->setItemText(0, QCoreApplication::translate("SettingDialog", "KD6R309AX3", nullptr));
        comboBoxType->setItemText(1, QCoreApplication::translate("SettingDialog", "KD6R617AX3", nullptr));
        comboBoxType->setItemText(2, QCoreApplication::translate("SettingDialog", "KD6R926AX3", nullptr));

        label->setText(QCoreApplication::translate("SettingDialog", "\343\203\234\343\203\274\343\203\211\346\225\260", nullptr));
        label_3->setText(QCoreApplication::translate("SettingDialog", "\343\202\263\343\203\263\343\203\225\343\202\243\343\202\260\343\203\225\343\202\241\343\202\244\343\203\253\345\220\215", nullptr));
        pushButtonConfigFileName->setText(QCoreApplication::translate("SettingDialog", "...", nullptr));
        label_4->setText(QCoreApplication::translate("SettingDialog", "\343\203\234\343\203\274\343\203\211\345\201\264\343\203\251\343\202\244\343\203\263\343\202\257\343\203\255\343\203\203\343\202\257", nullptr));
        label_6->setText(QCoreApplication::translate("SettingDialog", "CIS\343\202\253\343\203\241\343\203\251\350\250\255\345\256\232", nullptr));
        comboBoxResolution->setItemText(0, QCoreApplication::translate("SettingDialog", "600 DPI", nullptr));
        comboBoxResolution->setItemText(1, QCoreApplication::translate("SettingDialog", "300 DPI", nullptr));
        comboBoxResolution->setItemText(2, QCoreApplication::translate("SettingDialog", "150 DPI", nullptr));

        label_5->setText(QCoreApplication::translate("SettingDialog", "\344\270\273\350\265\260\346\237\273\350\247\243\345\203\217\345\272\246", nullptr));
        checkBoxOuterTriggerMode->setText(QCoreApplication::translate("SettingDialog", "\345\244\226\351\203\250\343\203\251\343\202\244\343\203\263\343\203\210\343\203\252\343\202\254\343\203\274\345\220\214\346\234\237", nullptr));
        label_7->setText(QCoreApplication::translate("SettingDialog", "LED\345\210\266\345\276\241", nullptr));
        comboBoxLEDControl->setItemText(0, QCoreApplication::translate("SettingDialog", "\345\205\250\347\202\271\347\201\257", nullptr));
        comboBoxLEDControl->setItemText(1, QCoreApplication::translate("SettingDialog", "\347\211\207\345\201\264\357\274\210A)\347\202\271\347\201\257", nullptr));
        comboBoxLEDControl->setItemText(2, QCoreApplication::translate("SettingDialog", "\347\211\207\345\201\264\357\274\210B)\347\202\271\347\201\257", nullptr));
        comboBoxLEDControl->setItemText(3, QCoreApplication::translate("SettingDialog", "\346\266\210\347\201\257", nullptr));

        label_8->setText(QCoreApplication::translate("SettingDialog", "\347\202\271\347\201\257Duty\346\257\224\343\200\200\345\205\250\345\214\272\351\226\223\343\203\221\343\203\253\343\202\271\346\225\260", nullptr));
        label_9->setText(QCoreApplication::translate("SettingDialog", "\347\202\271\347\201\257Duty\346\257\224\343\200\200\347\211\207\345\201\264\357\274\210A\357\274\211\343\203\221\343\203\253\343\202\271\346\225\260", nullptr));
        label_10->setText(QCoreApplication::translate("SettingDialog", "\347\202\271\347\201\257Duty\346\257\224\343\200\200\347\211\207\345\201\264\357\274\210B)\343\203\221\343\203\253\343\202\271\346\225\260", nullptr));
        label_11->setText(QCoreApplication::translate("SettingDialog", "\347\205\247\346\230\216\345\210\206\345\211\262\347\202\271\347\201\257", nullptr));
        comboBoxLEDDivide->setItemText(0, QCoreApplication::translate("SettingDialog", "\345\210\206\345\211\262\347\204\241\343\201\227", nullptr));
        comboBoxLEDDivide->setItemText(1, QCoreApplication::translate("SettingDialog", "2\345\210\206\345\211\262", nullptr));
        comboBoxLEDDivide->setItemText(2, QCoreApplication::translate("SettingDialog", "4\345\210\206\345\211\262", nullptr));
        comboBoxLEDDivide->setItemText(3, QCoreApplication::translate("SettingDialog", "8\345\210\206\345\211\262", nullptr));

        checkBoxGainMode->setText(QCoreApplication::translate("SettingDialog", "\343\202\262\343\202\244\343\203\263", nullptr));
        label_12->setText(QCoreApplication::translate("SettingDialog", "\350\265\244", nullptr));
        label_13->setText(QCoreApplication::translate("SettingDialog", "\347\267\221", nullptr));
        label_14->setText(QCoreApplication::translate("SettingDialog", "\351\235\222", nullptr));
        checkBoxScanDirection->setText(QCoreApplication::translate("SettingDialog", "\343\203\251\343\202\244\343\203\263\346\220\254\351\200\201\346\226\271\345\220\221", nullptr));
        checkBoxGamma->setText(QCoreApplication::translate("SettingDialog", "\343\202\254\343\203\263\343\203\236\350\243\234\346\255\243", nullptr));
        label_15->setText(QCoreApplication::translate("SettingDialog", "\345\201\266\346\225\260\343\203\224\343\202\257\343\202\273\343\203\253\343\200\200Y\343\202\252\343\203\225\343\202\273\343\203\203\343\203\210", nullptr));
        label_16->setText(QCoreApplication::translate("SettingDialog", "\345\245\207\346\225\260\343\203\224\343\202\257\343\202\273\343\203\253\343\200\200Y\343\202\252\343\203\225\343\202\273\343\203\203\343\203\210", nullptr));
        pushButtonAdjustWhite->setText(QCoreApplication::translate("SettingDialog", "\347\231\275\350\243\234\346\255\243", nullptr));
        pushButtonAdjustBlack->setText(QCoreApplication::translate("SettingDialog", "\351\273\222\350\243\234\346\255\243", nullptr));
        checkBoxModeAdjustWhite->setText(QCoreApplication::translate("SettingDialog", "\347\231\275\350\243\234\346\255\243", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
