/********************************************************************************
** Form generated from reading UI file 'ShowPrintTotalBladeForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWPRINTTOTALBLADEFORM_H
#define UI_SHOWPRINTTOTALBLADEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowPrintTotalBladeForm
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_TotalCount;
    QLabel *label_BladeOKCount;
    QLabel *label_BladeNG;
    QLabel *label_TopNGCount;
    QLabel *label_TopCount;
    QLabel *label_BottomNGCount;
    QLabel *label_BottomCount;
    QPushButton *pushButtonExcelSave;
    QPushButton *PushButtonReset;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_8;
    QLabel *label_MonoOKCount;
    QLabel *label_6;
    QLabel *label_9;
    QLabel *label_MonoNGCount;

    void setupUi(GUIFormBase *ShowPrintTotalBladeForm)
    {
        if (ShowPrintTotalBladeForm->objectName().isEmpty())
            ShowPrintTotalBladeForm->setObjectName("ShowPrintTotalBladeForm");
        ShowPrintTotalBladeForm->resize(298, 294);
        label = new QLabel(ShowPrintTotalBladeForm);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 171, 24));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(ShowPrintTotalBladeForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 26, 171, 24));
        label_2->setFont(font);
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(ShowPrintTotalBladeForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 78, 171, 24));
        label_3->setFont(font);
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        label_TotalCount = new QLabel(ShowPrintTotalBladeForm);
        label_TotalCount->setObjectName("label_TotalCount");
        label_TotalCount->setGeometry(QRect(180, 0, 111, 24));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(0, 255, 255, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_TotalCount->setPalette(palette);
        QFont font1;
        font1.setPointSize(14);
        label_TotalCount->setFont(font1);
        label_TotalCount->setAutoFillBackground(true);
        label_TotalCount->setFrameShape(QFrame::Panel);
        label_TotalCount->setFrameShadow(QFrame::Sunken);
        label_TotalCount->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_BladeOKCount = new QLabel(ShowPrintTotalBladeForm);
        label_BladeOKCount->setObjectName("label_BladeOKCount");
        label_BladeOKCount->setGeometry(QRect(180, 78, 111, 24));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_BladeOKCount->setPalette(palette1);
        label_BladeOKCount->setFont(font1);
        label_BladeOKCount->setAutoFillBackground(true);
        label_BladeOKCount->setFrameShape(QFrame::Panel);
        label_BladeOKCount->setFrameShadow(QFrame::Sunken);
        label_BladeOKCount->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_BladeNG = new QLabel(ShowPrintTotalBladeForm);
        label_BladeNG->setObjectName("label_BladeNG");
        label_BladeNG->setGeometry(QRect(180, 190, 111, 24));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_BladeNG->setPalette(palette2);
        label_BladeNG->setFont(font1);
        label_BladeNG->setAutoFillBackground(true);
        label_BladeNG->setFrameShape(QFrame::Panel);
        label_BladeNG->setFrameShadow(QFrame::Sunken);
        label_BladeNG->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_TopNGCount = new QLabel(ShowPrintTotalBladeForm);
        label_TopNGCount->setObjectName("label_TopNGCount");
        label_TopNGCount->setGeometry(QRect(180, 140, 111, 24));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_TopNGCount->setPalette(palette3);
        label_TopNGCount->setFont(font1);
        label_TopNGCount->setAutoFillBackground(true);
        label_TopNGCount->setFrameShape(QFrame::Panel);
        label_TopNGCount->setFrameShadow(QFrame::Sunken);
        label_TopNGCount->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_TopCount = new QLabel(ShowPrintTotalBladeForm);
        label_TopCount->setObjectName("label_TopCount");
        label_TopCount->setGeometry(QRect(180, 26, 111, 24));
        QPalette palette4;
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_TopCount->setPalette(palette4);
        label_TopCount->setFont(font1);
        label_TopCount->setAutoFillBackground(true);
        label_TopCount->setFrameShape(QFrame::Panel);
        label_TopCount->setFrameShadow(QFrame::Sunken);
        label_TopCount->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_BottomNGCount = new QLabel(ShowPrintTotalBladeForm);
        label_BottomNGCount->setObjectName("label_BottomNGCount");
        label_BottomNGCount->setGeometry(QRect(180, 164, 111, 24));
        QPalette palette5;
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette5.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette5.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_BottomNGCount->setPalette(palette5);
        label_BottomNGCount->setFont(font1);
        label_BottomNGCount->setAutoFillBackground(true);
        label_BottomNGCount->setFrameShape(QFrame::Panel);
        label_BottomNGCount->setFrameShadow(QFrame::Sunken);
        label_BottomNGCount->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_BottomCount = new QLabel(ShowPrintTotalBladeForm);
        label_BottomCount->setObjectName("label_BottomCount");
        label_BottomCount->setGeometry(QRect(180, 52, 111, 24));
        QPalette palette6;
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_BottomCount->setPalette(palette6);
        label_BottomCount->setFont(font1);
        label_BottomCount->setAutoFillBackground(true);
        label_BottomCount->setFrameShape(QFrame::Panel);
        label_BottomCount->setFrameShadow(QFrame::Sunken);
        label_BottomCount->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonExcelSave = new QPushButton(ShowPrintTotalBladeForm);
        pushButtonExcelSave->setObjectName("pushButtonExcelSave");
        pushButtonExcelSave->setGeometry(QRect(190, 240, 91, 51));
        pushButtonExcelSave->setFont(font1);
        pushButtonExcelSave->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonReset = new QPushButton(ShowPrintTotalBladeForm);
        PushButtonReset->setObjectName("PushButtonReset");
        PushButtonReset->setGeometry(QRect(0, 240, 101, 51));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font2.setPointSize(14);
        PushButtonReset->setFont(font2);
        PushButtonReset->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonReset->setCheckable(false);
        PushButtonReset->setAutoExclusive(false);
        PushButtonReset->setAutoDefault(false);
        PushButtonReset->setFlat(false);
        label_7 = new QLabel(ShowPrintTotalBladeForm);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 52, 171, 24));
        label_7->setFont(font);
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(ShowPrintTotalBladeForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 190, 171, 24));
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(ShowPrintTotalBladeForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 140, 171, 24));
        label_5->setFont(font);
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(ShowPrintTotalBladeForm);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 164, 171, 24));
        label_8->setFont(font);
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter);
        label_MonoOKCount = new QLabel(ShowPrintTotalBladeForm);
        label_MonoOKCount->setObjectName("label_MonoOKCount");
        label_MonoOKCount->setGeometry(QRect(180, 104, 111, 24));
        QPalette palette7;
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_MonoOKCount->setPalette(palette7);
        label_MonoOKCount->setFont(font1);
        label_MonoOKCount->setAutoFillBackground(true);
        label_MonoOKCount->setFrameShape(QFrame::Panel);
        label_MonoOKCount->setFrameShadow(QFrame::Sunken);
        label_MonoOKCount->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(ShowPrintTotalBladeForm);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 104, 171, 24));
        label_6->setFont(font);
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(ShowPrintTotalBladeForm);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(0, 216, 171, 24));
        label_9->setFont(font);
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter);
        label_MonoNGCount = new QLabel(ShowPrintTotalBladeForm);
        label_MonoNGCount->setObjectName("label_MonoNGCount");
        label_MonoNGCount->setGeometry(QRect(180, 216, 111, 24));
        QPalette palette8;
        palette8.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette8.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette8.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette8.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette8.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette8.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_MonoNGCount->setPalette(palette8);
        label_MonoNGCount->setFont(font1);
        label_MonoNGCount->setAutoFillBackground(true);
        label_MonoNGCount->setFrameShape(QFrame::Panel);
        label_MonoNGCount->setFrameShadow(QFrame::Sunken);
        label_MonoNGCount->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(ShowPrintTotalBladeForm);

        PushButtonReset->setDefault(false);


        QMetaObject::connectSlotsByName(ShowPrintTotalBladeForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowPrintTotalBladeForm)
    {
        ShowPrintTotalBladeForm->setWindowTitle(QCoreApplication::translate("ShowPrintTotalBladeForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "\347\267\217\346\244\234\346\237\273\346\225\260", nullptr));
        label_2->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "\345\211\215OK", nullptr));
        label_3->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "\345\210\203OK", nullptr));
        label_TotalCount->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "7654321", nullptr));
        label_BladeOKCount->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "7654321", nullptr));
        label_BladeNG->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "7654321", nullptr));
        label_TopNGCount->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "7654321", nullptr));
        label_TopCount->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "7654321", nullptr));
        label_BottomNGCount->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "7654321", nullptr));
        label_BottomCount->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "7654321", nullptr));
        pushButtonExcelSave->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "EXCEL", nullptr));
        PushButtonReset->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "\343\203\252\343\202\273\343\203\203\343\203\210", nullptr));
        label_7->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "\345\276\214OK", nullptr));
        label_4->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "\345\210\203NG", nullptr));
        label_5->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "\345\211\215NG", nullptr));
        label_8->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "\345\276\214NG", nullptr));
        label_MonoOKCount->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "7654321", nullptr));
        label_6->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "\343\203\242\343\203\216\343\202\257\343\203\255OK", nullptr));
        label_9->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "\343\203\242\343\203\216\343\202\257\343\203\255NG", nullptr));
        label_MonoNGCount->setText(QCoreApplication::translate("ShowPrintTotalBladeForm", "7654321", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowPrintTotalBladeForm: public Ui_ShowPrintTotalBladeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWPRINTTOTALBLADEFORM_H
