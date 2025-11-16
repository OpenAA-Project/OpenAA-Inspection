/********************************************************************************
** Form generated from reading UI file 'LargeFlatInspectionForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LARGEFLATINSPECTIONFORM_H
#define UI_LARGEFLATINSPECTIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LargeFlatInspectionForm
{
public:
    QLabel *labelResult;
    QFrame *frame;
    QLabel *label_4;
    QLabel *labelLibName;
    QPushButton *PushButtonOKbySizeWhole;
    QLabel *label_3;
    QToolButton *toolButtonShowNGMark;
    QLabel *labelLibID;
    QPushButton *PushButtonOKbyColorWhole;
    QFrame *frameMaster;
    QPushButton *PushButtonOKbyShiftWhole;
    QPushButton *pushButtonClose;
    QLabel *label_2;

    void setupUi(QWidget *LargeFlatInspectionForm)
    {
        if (LargeFlatInspectionForm->objectName().isEmpty())
            LargeFlatInspectionForm->setObjectName("LargeFlatInspectionForm");
        LargeFlatInspectionForm->resize(910, 532);
        labelResult = new QLabel(LargeFlatInspectionForm);
        labelResult->setObjectName("labelResult");
        labelResult->setGeometry(QRect(460, 420, 431, 31));
        QFont font;
        font.setPointSize(12);
        labelResult->setFont(font);
        labelResult->setFrameShape(QFrame::Panel);
        labelResult->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(LargeFlatInspectionForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(460, 30, 441, 381));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_4 = new QLabel(LargeFlatInspectionForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 460, 91, 51));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);
        labelLibName = new QLabel(LargeFlatInspectionForm);
        labelLibName->setObjectName("labelLibName");
        labelLibName->setGeometry(QRect(110, 420, 341, 31));
        labelLibName->setFont(font);
        labelLibName->setFrameShape(QFrame::Panel);
        labelLibName->setFrameShadow(QFrame::Sunken);
        PushButtonOKbySizeWhole = new QPushButton(LargeFlatInspectionForm);
        PushButtonOKbySizeWhole->setObjectName("PushButtonOKbySizeWhole");
        PushButtonOKbySizeWhole->setGeometry(QRect(420, 460, 141, 61));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font1.setPointSize(12);
        PushButtonOKbySizeWhole->setFont(font1);
        PushButtonOKbySizeWhole->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonOKbySizeWhole->setCheckable(false);
        PushButtonOKbySizeWhole->setAutoDefault(false);
        PushButtonOKbySizeWhole->setFlat(false);
        label_3 = new QLabel(LargeFlatInspectionForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(460, 10, 441, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        toolButtonShowNGMark = new QToolButton(LargeFlatInspectionForm);
        toolButtonShowNGMark->setObjectName("toolButtonShowNGMark");
        toolButtonShowNGMark->setGeometry(QRect(580, 460, 151, 61));
        toolButtonShowNGMark->setFont(font);
        toolButtonShowNGMark->setAutoFillBackground(false);
        toolButtonShowNGMark->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        toolButtonShowNGMark->setCheckable(true);
        toolButtonShowNGMark->setChecked(true);
        labelLibID = new QLabel(LargeFlatInspectionForm);
        labelLibID->setObjectName("labelLibID");
        labelLibID->setGeometry(QRect(20, 420, 81, 31));
        labelLibID->setFont(font);
        labelLibID->setFrameShape(QFrame::Panel);
        labelLibID->setFrameShadow(QFrame::Sunken);
        PushButtonOKbyColorWhole = new QPushButton(LargeFlatInspectionForm);
        PushButtonOKbyColorWhole->setObjectName("PushButtonOKbyColorWhole");
        PushButtonOKbyColorWhole->setGeometry(QRect(120, 460, 141, 61));
        PushButtonOKbyColorWhole->setFont(font1);
        PushButtonOKbyColorWhole->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonOKbyColorWhole->setCheckable(false);
        PushButtonOKbyColorWhole->setAutoDefault(false);
        PushButtonOKbyColorWhole->setFlat(false);
        frameMaster = new QFrame(LargeFlatInspectionForm);
        frameMaster->setObjectName("frameMaster");
        frameMaster->setGeometry(QRect(10, 30, 441, 381));
        frameMaster->setFrameShape(QFrame::StyledPanel);
        frameMaster->setFrameShadow(QFrame::Raised);
        PushButtonOKbyShiftWhole = new QPushButton(LargeFlatInspectionForm);
        PushButtonOKbyShiftWhole->setObjectName("PushButtonOKbyShiftWhole");
        PushButtonOKbyShiftWhole->setGeometry(QRect(270, 460, 141, 61));
        PushButtonOKbyShiftWhole->setFont(font1);
        PushButtonOKbyShiftWhole->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonOKbyShiftWhole->setCheckable(false);
        PushButtonOKbyShiftWhole->setAutoDefault(false);
        PushButtonOKbyShiftWhole->setFlat(false);
        pushButtonClose = new QPushButton(LargeFlatInspectionForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(740, 460, 151, 61));
        pushButtonClose->setFont(font);
        pushButtonClose->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(120, 254, 180, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        label_2 = new QLabel(LargeFlatInspectionForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 441, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(LargeFlatInspectionForm);

        PushButtonOKbySizeWhole->setDefault(false);
        PushButtonOKbyColorWhole->setDefault(false);
        PushButtonOKbyShiftWhole->setDefault(false);


        QMetaObject::connectSlotsByName(LargeFlatInspectionForm);
    } // setupUi

    void retranslateUi(QWidget *LargeFlatInspectionForm)
    {
        LargeFlatInspectionForm->setWindowTitle(QCoreApplication::translate("LargeFlatInspectionForm", "Form", nullptr));
        labelResult->setText(QString());
        label_4->setText(QCoreApplication::translate("LargeFlatInspectionForm", "\345\205\250\344\275\223", nullptr));
        labelLibName->setText(QString());
        PushButtonOKbySizeWhole->setText(QCoreApplication::translate("LargeFlatInspectionForm", "\345\244\247\343\201\215\343\201\225\343\201\247OK", nullptr));
        label_3->setText(QCoreApplication::translate("LargeFlatInspectionForm", "NG\351\203\250\345\210\206\343\201\256\347\224\273\345\203\217", nullptr));
        toolButtonShowNGMark->setText(QCoreApplication::translate("LargeFlatInspectionForm", "\350\265\244\344\270\270\350\241\250\347\244\272", nullptr));
        labelLibID->setText(QString());
        PushButtonOKbyColorWhole->setText(QCoreApplication::translate("LargeFlatInspectionForm", "\350\211\262\343\203\273\350\274\235\345\272\246\343\201\214OK", nullptr));
        PushButtonOKbyShiftWhole->setText(QCoreApplication::translate("LargeFlatInspectionForm", "\343\202\272\343\203\254\343\201\247OK", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("LargeFlatInspectionForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_2->setText(QCoreApplication::translate("LargeFlatInspectionForm", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LargeFlatInspectionForm: public Ui_LargeFlatInspectionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LARGEFLATINSPECTIONFORM_H
