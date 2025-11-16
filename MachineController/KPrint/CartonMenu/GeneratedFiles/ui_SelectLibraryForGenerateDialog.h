/********************************************************************************
** Form generated from reading UI file 'SelectLibraryForGenerateDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLIBRARYFORGENERATEDIALOG_H
#define UI_SELECTLIBRARYFORGENERATEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectLibraryForGenerateDialog
{
public:
    QGroupBox *groupBox;
    QFrame *frameSelect1;
    QPushButton *PushButtonFlatTop;
    QPushButton *PushButtonPrintPatternTop;
    QPushButton *PushButtonBladeTop;
    QGroupBox *groupBoxBottom;
    QPushButton *PushButtonBladeBottom;
    QFrame *frameSelect2;
    QPushButton *PushButtonFlatBottom;
    QPushButton *PushButtonPrintPatternBottom;
    QGroupBox *groupBoxMono;
    QFrame *frameSelect3;
    QPushButton *PushButtonFlatMono;
    QPushButton *PushButtonPrintPatternMono;
    QFrame *frameTail;
    QPushButton *PushButtonCancel;
    QPushButton *PushButtonStartGenerate;
    QFrame *frameThresholdLevel;

    void setupUi(QDialog *SelectLibraryForGenerateDialog)
    {
        if (SelectLibraryForGenerateDialog->objectName().isEmpty())
            SelectLibraryForGenerateDialog->setObjectName("SelectLibraryForGenerateDialog");
        SelectLibraryForGenerateDialog->resize(927, 459);
        groupBox = new QGroupBox(SelectLibraryForGenerateDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 20, 291, 281));
        QFont font;
        font.setPointSize(14);
        groupBox->setFont(font);
        frameSelect1 = new QFrame(groupBox);
        frameSelect1->setObjectName("frameSelect1");
        frameSelect1->setGeometry(QRect(30, 120, 241, 161));
        frameSelect1->setFrameShape(QFrame::StyledPanel);
        frameSelect1->setFrameShadow(QFrame::Raised);
        PushButtonFlatTop = new QPushButton(frameSelect1);
        PushButtonFlatTop->setObjectName("PushButtonFlatTop");
        PushButtonFlatTop->setGeometry(QRect(0, 80, 241, 68));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font1.setPointSize(24);
        PushButtonFlatTop->setFont(font1);
        PushButtonFlatTop->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonFlatTop->setCheckable(true);
        PushButtonFlatTop->setAutoExclusive(true);
        PushButtonFlatTop->setAutoDefault(false);
        PushButtonFlatTop->setFlat(false);
        PushButtonPrintPatternTop = new QPushButton(frameSelect1);
        PushButtonPrintPatternTop->setObjectName("PushButtonPrintPatternTop");
        PushButtonPrintPatternTop->setGeometry(QRect(0, 0, 241, 68));
        PushButtonPrintPatternTop->setFont(font1);
        PushButtonPrintPatternTop->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonPrintPatternTop->setCheckable(true);
        PushButtonPrintPatternTop->setChecked(true);
        PushButtonPrintPatternTop->setAutoExclusive(true);
        PushButtonPrintPatternTop->setAutoDefault(false);
        PushButtonPrintPatternTop->setFlat(false);
        PushButtonBladeTop = new QPushButton(groupBox);
        PushButtonBladeTop->setObjectName("PushButtonBladeTop");
        PushButtonBladeTop->setGeometry(QRect(30, 40, 241, 68));
        PushButtonBladeTop->setFont(font1);
        PushButtonBladeTop->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 168, 128, 255), stop:1 rgba(141, 120, 96, 255));\n"
"}"));
        PushButtonBladeTop->setCheckable(true);
        PushButtonBladeTop->setChecked(false);
        PushButtonBladeTop->setAutoExclusive(false);
        PushButtonBladeTop->setAutoDefault(false);
        PushButtonBladeTop->setFlat(false);
        groupBoxBottom = new QGroupBox(SelectLibraryForGenerateDialog);
        groupBoxBottom->setObjectName("groupBoxBottom");
        groupBoxBottom->setGeometry(QRect(330, 20, 291, 281));
        groupBoxBottom->setFont(font);
        PushButtonBladeBottom = new QPushButton(groupBoxBottom);
        PushButtonBladeBottom->setObjectName("PushButtonBladeBottom");
        PushButtonBladeBottom->setGeometry(QRect(30, 40, 241, 68));
        PushButtonBladeBottom->setFont(font1);
        PushButtonBladeBottom->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 168, 128, 255), stop:1 rgba(141, 120, 96, 255));\n"
"}"));
        PushButtonBladeBottom->setCheckable(true);
        PushButtonBladeBottom->setChecked(true);
        PushButtonBladeBottom->setAutoExclusive(false);
        PushButtonBladeBottom->setAutoDefault(false);
        PushButtonBladeBottom->setFlat(false);
        frameSelect2 = new QFrame(groupBoxBottom);
        frameSelect2->setObjectName("frameSelect2");
        frameSelect2->setGeometry(QRect(30, 120, 241, 151));
        frameSelect2->setFrameShape(QFrame::StyledPanel);
        frameSelect2->setFrameShadow(QFrame::Raised);
        PushButtonFlatBottom = new QPushButton(frameSelect2);
        PushButtonFlatBottom->setObjectName("PushButtonFlatBottom");
        PushButtonFlatBottom->setGeometry(QRect(0, 80, 241, 68));
        PushButtonFlatBottom->setFont(font1);
        PushButtonFlatBottom->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonFlatBottom->setCheckable(true);
        PushButtonFlatBottom->setChecked(true);
        PushButtonFlatBottom->setAutoExclusive(true);
        PushButtonFlatBottom->setAutoDefault(false);
        PushButtonFlatBottom->setFlat(false);
        PushButtonPrintPatternBottom = new QPushButton(frameSelect2);
        PushButtonPrintPatternBottom->setObjectName("PushButtonPrintPatternBottom");
        PushButtonPrintPatternBottom->setGeometry(QRect(0, 0, 241, 68));
        PushButtonPrintPatternBottom->setFont(font1);
        PushButtonPrintPatternBottom->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonPrintPatternBottom->setCheckable(true);
        PushButtonPrintPatternBottom->setChecked(false);
        PushButtonPrintPatternBottom->setAutoExclusive(true);
        PushButtonPrintPatternBottom->setAutoDefault(false);
        PushButtonPrintPatternBottom->setFlat(false);
        groupBoxMono = new QGroupBox(SelectLibraryForGenerateDialog);
        groupBoxMono->setObjectName("groupBoxMono");
        groupBoxMono->setGeometry(QRect(640, 20, 291, 281));
        groupBoxMono->setFont(font);
        frameSelect3 = new QFrame(groupBoxMono);
        frameSelect3->setObjectName("frameSelect3");
        frameSelect3->setGeometry(QRect(20, 40, 241, 151));
        frameSelect3->setFrameShape(QFrame::StyledPanel);
        frameSelect3->setFrameShadow(QFrame::Raised);
        PushButtonFlatMono = new QPushButton(frameSelect3);
        PushButtonFlatMono->setObjectName("PushButtonFlatMono");
        PushButtonFlatMono->setGeometry(QRect(0, 80, 241, 68));
        PushButtonFlatMono->setFont(font1);
        PushButtonFlatMono->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonFlatMono->setCheckable(true);
        PushButtonFlatMono->setChecked(false);
        PushButtonFlatMono->setAutoExclusive(true);
        PushButtonFlatMono->setAutoDefault(false);
        PushButtonFlatMono->setFlat(false);
        PushButtonPrintPatternMono = new QPushButton(frameSelect3);
        PushButtonPrintPatternMono->setObjectName("PushButtonPrintPatternMono");
        PushButtonPrintPatternMono->setGeometry(QRect(0, 0, 241, 68));
        PushButtonPrintPatternMono->setFont(font1);
        PushButtonPrintPatternMono->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonPrintPatternMono->setCheckable(true);
        PushButtonPrintPatternMono->setChecked(true);
        PushButtonPrintPatternMono->setAutoExclusive(true);
        PushButtonPrintPatternMono->setAutoDefault(false);
        PushButtonPrintPatternMono->setFlat(false);
        frameTail = new QFrame(SelectLibraryForGenerateDialog);
        frameTail->setObjectName("frameTail");
        frameTail->setGeometry(QRect(0, 300, 921, 161));
        frameTail->setFrameShape(QFrame::StyledPanel);
        frameTail->setFrameShadow(QFrame::Raised);
        PushButtonCancel = new QPushButton(frameTail);
        PushButtonCancel->setObjectName("PushButtonCancel");
        PushButtonCancel->setGeometry(QRect(470, 90, 181, 61));
        PushButtonCancel->setFont(font1);
        PushButtonCancel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonCancel->setCheckable(false);
        PushButtonCancel->setAutoDefault(false);
        PushButtonCancel->setFlat(false);
        PushButtonStartGenerate = new QPushButton(frameTail);
        PushButtonStartGenerate->setObjectName("PushButtonStartGenerate");
        PushButtonStartGenerate->setGeometry(QRect(210, 90, 241, 61));
        PushButtonStartGenerate->setFont(font1);
        PushButtonStartGenerate->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(180, 254, 180, 255), stop:1 rgba(120, 165, 120, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(255, 0, 0, 255), stop:1 rgba(120, 0, 0, 255));\n"
"}"));
        PushButtonStartGenerate->setCheckable(false);
        PushButtonStartGenerate->setAutoDefault(false);
        PushButtonStartGenerate->setFlat(false);
        frameThresholdLevel = new QFrame(frameTail);
        frameThresholdLevel->setObjectName("frameThresholdLevel");
        frameThresholdLevel->setGeometry(QRect(0, 0, 331, 80));
        frameThresholdLevel->setFrameShape(QFrame::NoFrame);
        frameThresholdLevel->setFrameShadow(QFrame::Plain);

        retranslateUi(SelectLibraryForGenerateDialog);

        PushButtonFlatTop->setDefault(false);
        PushButtonPrintPatternTop->setDefault(false);
        PushButtonBladeTop->setDefault(false);
        PushButtonBladeBottom->setDefault(false);
        PushButtonFlatBottom->setDefault(false);
        PushButtonPrintPatternBottom->setDefault(false);
        PushButtonFlatMono->setDefault(false);
        PushButtonPrintPatternMono->setDefault(false);
        PushButtonCancel->setDefault(false);
        PushButtonStartGenerate->setDefault(false);


        QMetaObject::connectSlotsByName(SelectLibraryForGenerateDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectLibraryForGenerateDialog)
    {
        SelectLibraryForGenerateDialog->setWindowTitle(QCoreApplication::translate("SelectLibraryForGenerateDialog", "\350\207\252\345\213\225\347\224\237\346\210\220\343\201\256\350\250\255\345\256\232", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SelectLibraryForGenerateDialog", "\344\270\212\346\265\201\357\274\210\350\243\217\351\235\242\343\201\213\343\202\211\343\201\256\346\222\256\345\275\261\357\274\211", nullptr));
        PushButtonFlatTop->setText(QCoreApplication::translate("SelectLibraryForGenerateDialog", "\347\204\241\345\234\260", nullptr));
        PushButtonPrintPatternTop->setText(QCoreApplication::translate("SelectLibraryForGenerateDialog", "\345\215\260\345\210\267\343\203\221\343\202\277\343\203\274\343\203\263", nullptr));
        PushButtonBladeTop->setText(QCoreApplication::translate("SelectLibraryForGenerateDialog", "\350\250\210\346\270\254", nullptr));
        groupBoxBottom->setTitle(QCoreApplication::translate("SelectLibraryForGenerateDialog", "\344\270\213\346\265\201", nullptr));
        PushButtonBladeBottom->setText(QCoreApplication::translate("SelectLibraryForGenerateDialog", "\350\250\210\346\270\254", nullptr));
        PushButtonFlatBottom->setText(QCoreApplication::translate("SelectLibraryForGenerateDialog", "\347\204\241\345\234\260", nullptr));
        PushButtonPrintPatternBottom->setText(QCoreApplication::translate("SelectLibraryForGenerateDialog", "\345\215\260\345\210\267\343\203\221\343\202\277\343\203\274\343\203\263", nullptr));
        groupBoxMono->setTitle(QCoreApplication::translate("SelectLibraryForGenerateDialog", "\357\274\223\345\217\260\347\233\256", nullptr));
        PushButtonFlatMono->setText(QCoreApplication::translate("SelectLibraryForGenerateDialog", "\347\204\241\345\234\260", nullptr));
        PushButtonPrintPatternMono->setText(QCoreApplication::translate("SelectLibraryForGenerateDialog", "\345\215\260\345\210\267\343\203\221\343\202\277\343\203\274\343\203\263", nullptr));
        PushButtonCancel->setText(QCoreApplication::translate("SelectLibraryForGenerateDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        PushButtonStartGenerate->setText(QCoreApplication::translate("SelectLibraryForGenerateDialog", "\347\224\237\346\210\220\351\226\213\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibraryForGenerateDialog: public Ui_SelectLibraryForGenerateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBRARYFORGENERATEDIALOG_H
