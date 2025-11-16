/********************************************************************************
** Form generated from reading UI file 'EachSettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EACHSETTINGDIALOG_H
#define UI_EACHSETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EachSettingDialog
{
public:
    QPushButton *PushButtonAutoGenerate;
    QPushButton *PushButtonInspection;
    QPushButton *PushButtonBlade;
    QPushButton *PushButtonSwitchPhase;
    QPushButton *PushButtonMask;
    QPushButton *PushButtonAlignment;
    QPushButton *PushButtonSettingThresholdTop;
    QPushButton *PushButtonBladeSettingThresholdBottom;
    QPushButton *PushButtonClose;
    QPushButton *PushButtonColorDifference;
    QPushButton *PushButtonMakeAverageImage;
    QPushButton *PushButtonSettingExpose;
    QPushButton *PushButtonBCode;
    QPushButton *PushButtonMeasure;
    QPushButton *PushButtonSettingThresholdMono;
    QPushButton *PushButtonCalcFinalize;
    QPushButton *PushButtonResetSlaves;

    void setupUi(QDialog *EachSettingDialog)
    {
        if (EachSettingDialog->objectName().isEmpty())
            EachSettingDialog->setObjectName("EachSettingDialog");
        EachSettingDialog->resize(232, 937);
        PushButtonAutoGenerate = new QPushButton(EachSettingDialog);
        PushButtonAutoGenerate->setObjectName("PushButtonAutoGenerate");
        PushButtonAutoGenerate->setGeometry(QRect(10, 590, 199, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font.setPointSize(24);
        PushButtonAutoGenerate->setFont(font);
        PushButtonAutoGenerate->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(120, 254, 180, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonAutoGenerate->setCheckable(true);
        PushButtonAutoGenerate->setAutoDefault(false);
        PushButtonAutoGenerate->setFlat(false);
        PushButtonInspection = new QPushButton(EachSettingDialog);
        PushButtonInspection->setObjectName("PushButtonInspection");
        PushButtonInspection->setGeometry(QRect(10, 170, 211, 61));
        PushButtonInspection->setFont(font);
        PushButtonInspection->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonInspection->setCheckable(true);
        PushButtonInspection->setAutoExclusive(true);
        PushButtonInspection->setAutoDefault(false);
        PushButtonInspection->setFlat(false);
        PushButtonBlade = new QPushButton(EachSettingDialog);
        PushButtonBlade->setObjectName("PushButtonBlade");
        PushButtonBlade->setGeometry(QRect(10, 230, 211, 61));
        PushButtonBlade->setFont(font);
        PushButtonBlade->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonBlade->setCheckable(true);
        PushButtonBlade->setAutoExclusive(true);
        PushButtonBlade->setAutoDefault(false);
        PushButtonBlade->setFlat(false);
        PushButtonSwitchPhase = new QPushButton(EachSettingDialog);
        PushButtonSwitchPhase->setObjectName("PushButtonSwitchPhase");
        PushButtonSwitchPhase->setGeometry(QRect(10, 310, 211, 61));
        PushButtonSwitchPhase->setFont(font);
        PushButtonSwitchPhase->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSwitchPhase->setCheckable(true);
        PushButtonSwitchPhase->setAutoExclusive(true);
        PushButtonSwitchPhase->setAutoDefault(false);
        PushButtonSwitchPhase->setFlat(false);
        PushButtonMask = new QPushButton(EachSettingDialog);
        PushButtonMask->setObjectName("PushButtonMask");
        PushButtonMask->setGeometry(QRect(10, 50, 211, 61));
        PushButtonMask->setFont(font);
        PushButtonMask->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonMask->setCheckable(true);
        PushButtonMask->setAutoExclusive(true);
        PushButtonMask->setAutoDefault(false);
        PushButtonMask->setFlat(false);
        PushButtonAlignment = new QPushButton(EachSettingDialog);
        PushButtonAlignment->setObjectName("PushButtonAlignment");
        PushButtonAlignment->setGeometry(QRect(10, 110, 211, 61));
        PushButtonAlignment->setFont(font);
        PushButtonAlignment->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonAlignment->setCheckable(true);
        PushButtonAlignment->setAutoExclusive(true);
        PushButtonAlignment->setAutoDefault(false);
        PushButtonAlignment->setFlat(false);
        PushButtonSettingThresholdTop = new QPushButton(EachSettingDialog);
        PushButtonSettingThresholdTop->setObjectName("PushButtonSettingThresholdTop");
        PushButtonSettingThresholdTop->setGeometry(QRect(10, 720, 211, 51));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font1.setPointSize(20);
        PushButtonSettingThresholdTop->setFont(font1);
        PushButtonSettingThresholdTop->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSettingThresholdTop->setCheckable(true);
        PushButtonSettingThresholdTop->setAutoExclusive(true);
        PushButtonSettingThresholdTop->setAutoDefault(false);
        PushButtonSettingThresholdTop->setFlat(false);
        PushButtonBladeSettingThresholdBottom = new QPushButton(EachSettingDialog);
        PushButtonBladeSettingThresholdBottom->setObjectName("PushButtonBladeSettingThresholdBottom");
        PushButtonBladeSettingThresholdBottom->setGeometry(QRect(10, 770, 211, 51));
        PushButtonBladeSettingThresholdBottom->setFont(font1);
        PushButtonBladeSettingThresholdBottom->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonBladeSettingThresholdBottom->setCheckable(true);
        PushButtonBladeSettingThresholdBottom->setAutoExclusive(true);
        PushButtonBladeSettingThresholdBottom->setAutoDefault(false);
        PushButtonBladeSettingThresholdBottom->setFlat(false);
        PushButtonClose = new QPushButton(EachSettingDialog);
        PushButtonClose->setObjectName("PushButtonClose");
        PushButtonClose->setGeometry(QRect(10, 870, 211, 61));
        PushButtonClose->setFont(font);
        PushButtonClose->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 10px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 220, 160, 255), stop:1 rgba(165, 140, 100, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(255, 100, 100, 255), stop:1 rgba(141, 60, 60, 255));\n"
"}"));
        PushButtonClose->setCheckable(true);
        PushButtonClose->setAutoExclusive(true);
        PushButtonClose->setAutoDefault(false);
        PushButtonClose->setFlat(false);
        PushButtonColorDifference = new QPushButton(EachSettingDialog);
        PushButtonColorDifference->setObjectName("PushButtonColorDifference");
        PushButtonColorDifference->setGeometry(QRect(10, 380, 211, 61));
        PushButtonColorDifference->setFont(font);
        PushButtonColorDifference->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonColorDifference->setCheckable(true);
        PushButtonColorDifference->setAutoExclusive(true);
        PushButtonColorDifference->setAutoDefault(false);
        PushButtonColorDifference->setFlat(false);
        PushButtonMakeAverageImage = new QPushButton(EachSettingDialog);
        PushButtonMakeAverageImage->setObjectName("PushButtonMakeAverageImage");
        PushButtonMakeAverageImage->setGeometry(QRect(10, 460, 211, 61));
        PushButtonMakeAverageImage->setFont(font);
        PushButtonMakeAverageImage->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonMakeAverageImage->setCheckable(true);
        PushButtonMakeAverageImage->setAutoExclusive(true);
        PushButtonMakeAverageImage->setAutoDefault(false);
        PushButtonMakeAverageImage->setFlat(false);
        PushButtonSettingExpose = new QPushButton(EachSettingDialog);
        PushButtonSettingExpose->setObjectName("PushButtonSettingExpose");
        PushButtonSettingExpose->setGeometry(QRect(10, 10, 211, 31));
        PushButtonSettingExpose->setFont(font);
        PushButtonSettingExpose->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSettingExpose->setCheckable(true);
        PushButtonSettingExpose->setAutoExclusive(true);
        PushButtonSettingExpose->setAutoDefault(false);
        PushButtonSettingExpose->setFlat(false);
        PushButtonBCode = new QPushButton(EachSettingDialog);
        PushButtonBCode->setObjectName("PushButtonBCode");
        PushButtonBCode->setGeometry(QRect(10, 520, 211, 61));
        PushButtonBCode->setFont(font);
        PushButtonBCode->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonBCode->setCheckable(true);
        PushButtonBCode->setAutoExclusive(true);
        PushButtonBCode->setAutoDefault(false);
        PushButtonBCode->setFlat(false);
        PushButtonMeasure = new QPushButton(EachSettingDialog);
        PushButtonMeasure->setObjectName("PushButtonMeasure");
        PushButtonMeasure->setGeometry(QRect(10, 230, 211, 61));
        PushButtonMeasure->setFont(font);
        PushButtonMeasure->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonMeasure->setCheckable(true);
        PushButtonMeasure->setAutoExclusive(true);
        PushButtonMeasure->setAutoDefault(false);
        PushButtonMeasure->setFlat(false);
        PushButtonSettingThresholdMono = new QPushButton(EachSettingDialog);
        PushButtonSettingThresholdMono->setObjectName("PushButtonSettingThresholdMono");
        PushButtonSettingThresholdMono->setGeometry(QRect(10, 820, 211, 51));
        PushButtonSettingThresholdMono->setFont(font1);
        PushButtonSettingThresholdMono->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSettingThresholdMono->setCheckable(true);
        PushButtonSettingThresholdMono->setAutoExclusive(true);
        PushButtonSettingThresholdMono->setAutoDefault(false);
        PushButtonSettingThresholdMono->setFlat(false);
        PushButtonCalcFinalize = new QPushButton(EachSettingDialog);
        PushButtonCalcFinalize->setObjectName("PushButtonCalcFinalize");
        PushButtonCalcFinalize->setGeometry(QRect(10, 590, 211, 71));
        PushButtonCalcFinalize->setFont(font);
        PushButtonCalcFinalize->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 120, 180, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonCalcFinalize->setCheckable(true);
        PushButtonCalcFinalize->setAutoDefault(false);
        PushButtonCalcFinalize->setFlat(false);
        PushButtonResetSlaves = new QPushButton(EachSettingDialog);
        PushButtonResetSlaves->setObjectName("PushButtonResetSlaves");
        PushButtonResetSlaves->setGeometry(QRect(10, 660, 211, 61));
        PushButtonResetSlaves->setFont(font);
        PushButtonResetSlaves->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(120, 255, 180, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonResetSlaves->setCheckable(true);
        PushButtonResetSlaves->setAutoDefault(false);
        PushButtonResetSlaves->setFlat(false);

        retranslateUi(EachSettingDialog);

        PushButtonAutoGenerate->setDefault(false);
        PushButtonInspection->setDefault(false);
        PushButtonBlade->setDefault(false);
        PushButtonSwitchPhase->setDefault(false);
        PushButtonMask->setDefault(false);
        PushButtonAlignment->setDefault(false);
        PushButtonSettingThresholdTop->setDefault(false);
        PushButtonBladeSettingThresholdBottom->setDefault(false);
        PushButtonClose->setDefault(false);
        PushButtonColorDifference->setDefault(false);
        PushButtonMakeAverageImage->setDefault(false);
        PushButtonSettingExpose->setDefault(false);
        PushButtonBCode->setDefault(false);
        PushButtonMeasure->setDefault(false);
        PushButtonSettingThresholdMono->setDefault(false);
        PushButtonCalcFinalize->setDefault(false);
        PushButtonResetSlaves->setDefault(false);


        QMetaObject::connectSlotsByName(EachSettingDialog);
    } // setupUi

    void retranslateUi(QDialog *EachSettingDialog)
    {
        EachSettingDialog->setWindowTitle(QCoreApplication::translate("EachSettingDialog", "\345\200\213\345\210\245\350\250\255\345\256\232", nullptr));
        PushButtonAutoGenerate->setText(QCoreApplication::translate("EachSettingDialog", "\350\207\252\345\213\225\347\224\237\346\210\220", nullptr));
        PushButtonInspection->setText(QCoreApplication::translate("EachSettingDialog", "\346\244\234\346\237\273\351\240\230\345\237\237", nullptr));
        PushButtonBlade->setText(QCoreApplication::translate("EachSettingDialog", "\345\210\203", nullptr));
        PushButtonSwitchPhase->setText(QCoreApplication::translate("EachSettingDialog", "\344\270\201\347\225\252\347\231\273\351\214\262", nullptr));
        PushButtonMask->setText(QCoreApplication::translate("EachSettingDialog", "\343\203\236\343\202\271\343\202\257/CAD", nullptr));
        PushButtonAlignment->setText(QCoreApplication::translate("EachSettingDialog", "\344\275\215\347\275\256\343\201\202\343\202\217\343\201\233", nullptr));
        PushButtonSettingThresholdTop->setText(QCoreApplication::translate("EachSettingDialog", "\345\211\215\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        PushButtonBladeSettingThresholdBottom->setText(QCoreApplication::translate("EachSettingDialog", "\345\276\214\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        PushButtonClose->setText(QCoreApplication::translate("EachSettingDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        PushButtonColorDifference->setText(QCoreApplication::translate("EachSettingDialog", "\350\211\262\345\267\256", nullptr));
        PushButtonMakeAverageImage->setText(QCoreApplication::translate("EachSettingDialog", "\345\271\263\345\235\207\347\224\273\345\203\217", nullptr));
        PushButtonSettingExpose->setText(QCoreApplication::translate("EachSettingDialog", "\351\234\262\345\205\211\346\231\202\351\226\223", nullptr));
        PushButtonBCode->setText(QCoreApplication::translate("EachSettingDialog", "\343\203\220\343\203\274\343\202\263\343\203\274\343\203\211", nullptr));
        PushButtonMeasure->setText(QCoreApplication::translate("EachSettingDialog", "\350\250\210\346\270\254", nullptr));
        PushButtonSettingThresholdMono->setText(QCoreApplication::translate("EachSettingDialog", "\343\203\242\343\203\216\343\202\257\343\203\255\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        PushButtonCalcFinalize->setText(QCoreApplication::translate("EachSettingDialog", "\347\267\250\351\233\206\347\242\272\345\256\232", nullptr));
        PushButtonResetSlaves->setText(QCoreApplication::translate("EachSettingDialog", "\343\203\252\343\202\273\343\203\203\343\203\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EachSettingDialog: public Ui_EachSettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EACHSETTINGDIALOG_H
