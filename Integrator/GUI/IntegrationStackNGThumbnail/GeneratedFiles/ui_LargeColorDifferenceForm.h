/********************************************************************************
** Form generated from reading UI file 'LargeColorDifferenceForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LARGECOLORDIFFERENCEFORM_H
#define UI_LARGECOLORDIFFERENCEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LargeColorDifferenceForm
{
public:
    QLabel *label;
    QToolButton *toolButtonShowNGMark;
    QPushButton *pushButtonClose;
    QLabel *label_2;
    QPushButton *PushButtonOKbyDeltaE;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButtonDetail;
    QPushButton *PushButtonOKbyDeltaEWhole;
    QFrame *frame;
    QFrame *frameMaster;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBoxThresholdDeltaE;
    QDoubleSpinBox *doubleSpinBoxResultDeltaE;
    QLabel *label_6;
    QLabel *label_10;

    void setupUi(QWidget *LargeColorDifferenceForm)
    {
        if (LargeColorDifferenceForm->objectName().isEmpty())
            LargeColorDifferenceForm->setObjectName("LargeColorDifferenceForm");
        LargeColorDifferenceForm->resize(910, 561);
        label = new QLabel(LargeColorDifferenceForm);
        label->setObjectName("label");
        label->setGeometry(QRect(320, 430, 91, 51));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        toolButtonShowNGMark = new QToolButton(LargeColorDifferenceForm);
        toolButtonShowNGMark->setObjectName("toolButtonShowNGMark");
        toolButtonShowNGMark->setGeometry(QRect(580, 420, 151, 61));
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
        pushButtonClose = new QPushButton(LargeColorDifferenceForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(740, 490, 141, 61));
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
        label_2 = new QLabel(LargeColorDifferenceForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 441, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        PushButtonOKbyDeltaE = new QPushButton(LargeColorDifferenceForm);
        PushButtonOKbyDeltaE->setObjectName("PushButtonOKbyDeltaE");
        PushButtonOKbyDeltaE->setGeometry(QRect(420, 420, 141, 61));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font1.setPointSize(12);
        PushButtonOKbyDeltaE->setFont(font1);
        PushButtonOKbyDeltaE->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonOKbyDeltaE->setCheckable(false);
        PushButtonOKbyDeltaE->setAutoDefault(false);
        PushButtonOKbyDeltaE->setFlat(false);
        label_3 = new QLabel(LargeColorDifferenceForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(460, 10, 441, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(LargeColorDifferenceForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(320, 490, 91, 51));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);
        pushButtonDetail = new QPushButton(LargeColorDifferenceForm);
        pushButtonDetail->setObjectName("pushButtonDetail");
        pushButtonDetail->setGeometry(QRect(580, 490, 151, 61));
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
        PushButtonOKbyDeltaEWhole = new QPushButton(LargeColorDifferenceForm);
        PushButtonOKbyDeltaEWhole->setObjectName("PushButtonOKbyDeltaEWhole");
        PushButtonOKbyDeltaEWhole->setGeometry(QRect(420, 490, 141, 61));
        PushButtonOKbyDeltaEWhole->setFont(font1);
        PushButtonOKbyDeltaEWhole->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonOKbyDeltaEWhole->setCheckable(false);
        PushButtonOKbyDeltaEWhole->setAutoDefault(false);
        PushButtonOKbyDeltaEWhole->setFlat(false);
        frame = new QFrame(LargeColorDifferenceForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(460, 30, 441, 381));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frameMaster = new QFrame(LargeColorDifferenceForm);
        frameMaster->setObjectName("frameMaster");
        frameMaster->setGeometry(QRect(10, 30, 441, 381));
        frameMaster->setFrameShape(QFrame::StyledPanel);
        frameMaster->setFrameShadow(QFrame::Raised);
        label_5 = new QLabel(LargeColorDifferenceForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(200, 460, 61, 31));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxThresholdDeltaE = new QDoubleSpinBox(LargeColorDifferenceForm);
        doubleSpinBoxThresholdDeltaE->setObjectName("doubleSpinBoxThresholdDeltaE");
        doubleSpinBoxThresholdDeltaE->setGeometry(QRect(20, 460, 81, 31));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        QBrush brush2(QColor(240, 240, 240, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush2);
        doubleSpinBoxThresholdDeltaE->setPalette(palette);
        QFont font2;
        font2.setPointSize(14);
        doubleSpinBoxThresholdDeltaE->setFont(font2);
        doubleSpinBoxThresholdDeltaE->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxThresholdDeltaE->setReadOnly(true);
        doubleSpinBoxThresholdDeltaE->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxThresholdDeltaE->setMaximum(999999999.000000000000000);
        doubleSpinBoxResultDeltaE = new QDoubleSpinBox(LargeColorDifferenceForm);
        doubleSpinBoxResultDeltaE->setObjectName("doubleSpinBoxResultDeltaE");
        doubleSpinBoxResultDeltaE->setGeometry(QRect(110, 460, 81, 31));
        doubleSpinBoxResultDeltaE->setFont(font2);
        doubleSpinBoxResultDeltaE->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxResultDeltaE->setReadOnly(true);
        doubleSpinBoxResultDeltaE->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxResultDeltaE->setMaximum(999999999.000000000000000);
        label_6 = new QLabel(LargeColorDifferenceForm);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(110, 430, 81, 31));
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(LargeColorDifferenceForm);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(20, 430, 81, 31));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignCenter);

        retranslateUi(LargeColorDifferenceForm);

        PushButtonOKbyDeltaE->setDefault(false);
        PushButtonOKbyDeltaEWhole->setDefault(false);


        QMetaObject::connectSlotsByName(LargeColorDifferenceForm);
    } // setupUi

    void retranslateUi(QWidget *LargeColorDifferenceForm)
    {
        LargeColorDifferenceForm->setWindowTitle(QCoreApplication::translate("LargeColorDifferenceForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("LargeColorDifferenceForm", "\343\201\223\343\201\256\345\240\264\346\211\200", nullptr));
        toolButtonShowNGMark->setText(QCoreApplication::translate("LargeColorDifferenceForm", "\350\265\244\344\270\270\350\241\250\347\244\272", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("LargeColorDifferenceForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_2->setText(QCoreApplication::translate("LargeColorDifferenceForm", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217", nullptr));
        PushButtonOKbyDeltaE->setText(QCoreApplication::translate("LargeColorDifferenceForm", "\350\274\235\345\272\246\345\267\256OK", nullptr));
        label_3->setText(QCoreApplication::translate("LargeColorDifferenceForm", "NG\351\203\250\345\210\206\343\201\256\347\224\273\345\203\217", nullptr));
        label_4->setText(QCoreApplication::translate("LargeColorDifferenceForm", "\345\205\250\344\275\223", nullptr));
        pushButtonDetail->setText(QCoreApplication::translate("LargeColorDifferenceForm", "\350\251\263\347\264\260\350\250\255\345\256\232", nullptr));
        PushButtonOKbyDeltaEWhole->setText(QCoreApplication::translate("LargeColorDifferenceForm", "\350\274\235\345\272\246\345\267\256OK", nullptr));
        label_5->setText(QCoreApplication::translate("LargeColorDifferenceForm", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        label_6->setText(QCoreApplication::translate("LargeColorDifferenceForm", "\316\224E", nullptr));
        label_10->setText(QCoreApplication::translate("LargeColorDifferenceForm", "\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LargeColorDifferenceForm: public Ui_LargeColorDifferenceForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LARGECOLORDIFFERENCEFORM_H
