/********************************************************************************
** Form generated from reading UI file 'LargeWindowForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LARGEWINDOWFORM_H
#define UI_LARGEWINDOWFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LargeWindowForm
{
public:
    QFrame *frame;
    QToolButton *toolButtonShowNGMark;
    QPushButton *pushButtonClose;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *PushButtonOKbyColor;
    QPushButton *PushButtonOKbyShift;
    QPushButton *PushButtonOKbySize;
    QPushButton *PushButtonOKbyColorWhole;
    QPushButton *PushButtonOKbySizeWhole;
    QPushButton *PushButtonOKbyShiftWhole;
    QLabel *label;
    QLabel *label_4;
    QPushButton *pushButtonDetail;
    QFrame *frameMaster;
    QLabel *labelLibName;
    QLabel *labelResult;
    QLabel *labelLibID;
    QTextEdit *textEditBrightness;
    QTextEdit *textEditSearch;
    QTextEdit *textEditSizeLen;
    QLabel *label_5;

    void setupUi(QWidget *LargeWindowForm)
    {
        if (LargeWindowForm->objectName().isEmpty())
            LargeWindowForm->setObjectName("LargeWindowForm");
        LargeWindowForm->resize(891, 654);
        frame = new QFrame(LargeWindowForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(450, 20, 441, 381));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonShowNGMark = new QToolButton(LargeWindowForm);
        toolButtonShowNGMark->setObjectName("toolButtonShowNGMark");
        toolButtonShowNGMark->setGeometry(QRect(570, 450, 151, 61));
        QFont font;
        font.setPointSize(12);
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
        pushButtonClose = new QPushButton(LargeWindowForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(730, 520, 141, 61));
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
        label_2 = new QLabel(LargeWindowForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 441, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(LargeWindowForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(450, 0, 441, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        PushButtonOKbyColor = new QPushButton(LargeWindowForm);
        PushButtonOKbyColor->setObjectName("PushButtonOKbyColor");
        PushButtonOKbyColor->setGeometry(QRect(110, 450, 141, 61));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font1.setPointSize(12);
        PushButtonOKbyColor->setFont(font1);
        PushButtonOKbyColor->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonOKbyColor->setCheckable(false);
        PushButtonOKbyColor->setAutoDefault(false);
        PushButtonOKbyColor->setFlat(false);
        PushButtonOKbyShift = new QPushButton(LargeWindowForm);
        PushButtonOKbyShift->setObjectName("PushButtonOKbyShift");
        PushButtonOKbyShift->setGeometry(QRect(260, 450, 141, 61));
        PushButtonOKbyShift->setFont(font1);
        PushButtonOKbyShift->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonOKbyShift->setCheckable(false);
        PushButtonOKbyShift->setAutoDefault(false);
        PushButtonOKbyShift->setFlat(false);
        PushButtonOKbySize = new QPushButton(LargeWindowForm);
        PushButtonOKbySize->setObjectName("PushButtonOKbySize");
        PushButtonOKbySize->setGeometry(QRect(410, 450, 141, 61));
        PushButtonOKbySize->setFont(font1);
        PushButtonOKbySize->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonOKbySize->setCheckable(false);
        PushButtonOKbySize->setAutoDefault(false);
        PushButtonOKbySize->setFlat(false);
        PushButtonOKbyColorWhole = new QPushButton(LargeWindowForm);
        PushButtonOKbyColorWhole->setObjectName("PushButtonOKbyColorWhole");
        PushButtonOKbyColorWhole->setGeometry(QRect(110, 520, 141, 61));
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
        PushButtonOKbySizeWhole = new QPushButton(LargeWindowForm);
        PushButtonOKbySizeWhole->setObjectName("PushButtonOKbySizeWhole");
        PushButtonOKbySizeWhole->setGeometry(QRect(410, 520, 141, 61));
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
        PushButtonOKbyShiftWhole = new QPushButton(LargeWindowForm);
        PushButtonOKbyShiftWhole->setObjectName("PushButtonOKbyShiftWhole");
        PushButtonOKbyShiftWhole->setGeometry(QRect(260, 520, 141, 61));
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
        label = new QLabel(LargeWindowForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 460, 91, 51));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(LargeWindowForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 520, 91, 51));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);
        pushButtonDetail = new QPushButton(LargeWindowForm);
        pushButtonDetail->setObjectName("pushButtonDetail");
        pushButtonDetail->setGeometry(QRect(570, 520, 151, 61));
        pushButtonDetail->setFont(font);
        pushButtonDetail->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 234, 120, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        frameMaster = new QFrame(LargeWindowForm);
        frameMaster->setObjectName("frameMaster");
        frameMaster->setGeometry(QRect(0, 20, 441, 381));
        frameMaster->setFrameShape(QFrame::StyledPanel);
        frameMaster->setFrameShadow(QFrame::Raised);
        labelLibName = new QLabel(LargeWindowForm);
        labelLibName->setObjectName("labelLibName");
        labelLibName->setGeometry(QRect(100, 410, 341, 31));
        labelLibName->setFont(font);
        labelLibName->setFrameShape(QFrame::Panel);
        labelLibName->setFrameShadow(QFrame::Sunken);
        labelResult = new QLabel(LargeWindowForm);
        labelResult->setObjectName("labelResult");
        labelResult->setGeometry(QRect(450, 410, 431, 31));
        labelResult->setFont(font);
        labelResult->setFrameShape(QFrame::Panel);
        labelResult->setFrameShadow(QFrame::Sunken);
        labelLibID = new QLabel(LargeWindowForm);
        labelLibID->setObjectName("labelLibID");
        labelLibID->setGeometry(QRect(10, 410, 81, 31));
        labelLibID->setFont(font);
        labelLibID->setFrameShape(QFrame::Panel);
        labelLibID->setFrameShadow(QFrame::Sunken);
        textEditBrightness = new QTextEdit(LargeWindowForm);
        textEditBrightness->setObjectName("textEditBrightness");
        textEditBrightness->setGeometry(QRect(110, 590, 141, 61));
        textEditBrightness->setFont(font);
        textEditBrightness->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditBrightness->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditBrightness->setReadOnly(true);
        textEditSearch = new QTextEdit(LargeWindowForm);
        textEditSearch->setObjectName("textEditSearch");
        textEditSearch->setGeometry(QRect(270, 590, 121, 51));
        textEditSearch->setFont(font);
        textEditSearch->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditSearch->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditSearch->setReadOnly(true);
        textEditSizeLen = new QTextEdit(LargeWindowForm);
        textEditSizeLen->setObjectName("textEditSizeLen");
        textEditSizeLen->setGeometry(QRect(420, 590, 121, 51));
        textEditSizeLen->setFont(font);
        textEditSizeLen->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditSizeLen->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditSizeLen->setReadOnly(true);
        label_5 = new QLabel(LargeWindowForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 590, 91, 51));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);
        label_5->setWordWrap(true);

        retranslateUi(LargeWindowForm);

        PushButtonOKbyColor->setDefault(false);
        PushButtonOKbyShift->setDefault(false);
        PushButtonOKbySize->setDefault(false);
        PushButtonOKbyColorWhole->setDefault(false);
        PushButtonOKbySizeWhole->setDefault(false);
        PushButtonOKbyShiftWhole->setDefault(false);


        QMetaObject::connectSlotsByName(LargeWindowForm);
    } // setupUi

    void retranslateUi(QWidget *LargeWindowForm)
    {
        LargeWindowForm->setWindowTitle(QCoreApplication::translate("LargeWindowForm", "\346\213\241\345\244\247\350\241\250\347\244\272", nullptr));
        toolButtonShowNGMark->setText(QCoreApplication::translate("LargeWindowForm", "\350\265\244\344\270\270\350\241\250\347\244\272", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("LargeWindowForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_2->setText(QCoreApplication::translate("LargeWindowForm", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217", nullptr));
        label_3->setText(QCoreApplication::translate("LargeWindowForm", "NG\351\203\250\345\210\206\343\201\256\347\224\273\345\203\217", nullptr));
        PushButtonOKbyColor->setText(QCoreApplication::translate("LargeWindowForm", "\350\211\262\343\203\273\350\274\235\345\272\246\343\201\214OK", nullptr));
        PushButtonOKbyShift->setText(QCoreApplication::translate("LargeWindowForm", "\343\202\272\343\203\254\343\201\247OK", nullptr));
        PushButtonOKbySize->setText(QCoreApplication::translate("LargeWindowForm", "\345\244\247\343\201\215\343\201\225\343\201\247OK", nullptr));
        PushButtonOKbyColorWhole->setText(QCoreApplication::translate("LargeWindowForm", "\350\211\262\343\203\273\350\274\235\345\272\246\343\201\214OK", nullptr));
        PushButtonOKbySizeWhole->setText(QCoreApplication::translate("LargeWindowForm", "\345\244\247\343\201\215\343\201\225\343\201\247OK", nullptr));
        PushButtonOKbyShiftWhole->setText(QCoreApplication::translate("LargeWindowForm", "\343\202\272\343\203\254\343\201\247OK", nullptr));
        label->setText(QCoreApplication::translate("LargeWindowForm", "\343\201\223\343\201\256\345\240\264\346\211\200", nullptr));
        label_4->setText(QCoreApplication::translate("LargeWindowForm", "\345\205\250\344\275\223", nullptr));
        pushButtonDetail->setText(QCoreApplication::translate("LargeWindowForm", "\350\251\263\347\264\260\350\250\255\345\256\232", nullptr));
        labelLibName->setText(QString());
        labelResult->setText(QString());
        labelLibID->setText(QString());
        label_5->setText(QCoreApplication::translate("LargeWindowForm", "\344\273\243\350\241\250\343\203\226\343\203\255\343\203\203\343\202\257\n"
"\347\217\276\345\234\250\345\200\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LargeWindowForm: public Ui_LargeWindowForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LARGEWINDOWFORM_H
