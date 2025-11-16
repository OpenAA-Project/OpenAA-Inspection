/********************************************************************************
** Form generated from reading UI file 'EasyPropertyMaskingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EASYPROPERTYMASKINGFORM_H
#define UI_EASYPROPERTYMASKINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include "XGeneralWidget.h"
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_EasyPropertyMaskingForm
{
public:
    QToolButton *toolButtonAutoPickup;
    QFrame *frame;
    QToolButton *toolButtonEffective;
    QTableWidgetWithRightClick *tableWidgetLimited;
    QSlider *horizontalSlider;
    QToolButton *toolButtonMakeEffectiveFromCAD;
    QLabel *label;
    QSpinBox *spinBoxShrinkDotForCAD;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxShrinkDotForCADMM;
    QLabel *label_Unit;
    QToolButton *toolButtonMakeOutlineArea;
    QToolButton *toolButtonSetAllPhases;
    QToolButton *toolButtonMakePatternEdge;
    QToolButton *toolButtonShowOnlyLibID;

    void setupUi(GUIFormBase *EasyPropertyMaskingForm)
    {
        if (EasyPropertyMaskingForm->objectName().isEmpty())
            EasyPropertyMaskingForm->setObjectName("EasyPropertyMaskingForm");
        EasyPropertyMaskingForm->resize(417, 900);
        toolButtonAutoPickup = new QToolButton(EasyPropertyMaskingForm);
        toolButtonAutoPickup->setObjectName("toolButtonAutoPickup");
        toolButtonAutoPickup->setGeometry(QRect(650, 240, 271, 91));
        QFont font;
        font.setPointSize(20);
        toolButtonAutoPickup->setFont(font);
        toolButtonAutoPickup->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        frame = new QFrame(EasyPropertyMaskingForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 401, 111));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonEffective = new QToolButton(frame);
        toolButtonEffective->setObjectName("toolButtonEffective");
        toolButtonEffective->setGeometry(QRect(10, 10, 371, 91));
        toolButtonEffective->setFont(font);
        toolButtonEffective->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 60, 60, 255), stop:1 rgba(130, 0, 0, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 160, 0, 255));\n"
"}"));
        toolButtonEffective->setCheckable(true);
        toolButtonEffective->setChecked(true);
        toolButtonEffective->setAutoExclusive(false);
        tableWidgetLimited = new QTableWidgetWithRightClick(EasyPropertyMaskingForm);
        if (tableWidgetLimited->columnCount() < 3)
            tableWidgetLimited->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLimited->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLimited->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLimited->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetLimited->setObjectName("tableWidgetLimited");
        tableWidgetLimited->setGeometry(QRect(10, 160, 391, 341));
        QFont font1;
        font1.setPointSize(12);
        tableWidgetLimited->setFont(font1);
        tableWidgetLimited->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLimited->setSelectionBehavior(QAbstractItemView::SelectItems);
        tableWidgetLimited->verticalHeader()->setMinimumSectionSize(48);
        tableWidgetLimited->verticalHeader()->setDefaultSectionSize(48);
        horizontalSlider = new QSlider(EasyPropertyMaskingForm);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(180, 110, 201, 41));
        horizontalSlider->setMaximum(255);
        horizontalSlider->setValue(128);
        horizontalSlider->setOrientation(Qt::Horizontal);
        toolButtonMakeEffectiveFromCAD = new QToolButton(EasyPropertyMaskingForm);
        toolButtonMakeEffectiveFromCAD->setObjectName("toolButtonMakeEffectiveFromCAD");
        toolButtonMakeEffectiveFromCAD->setGeometry(QRect(16, 590, 371, 71));
        toolButtonMakeEffectiveFromCAD->setFont(font);
        toolButtonMakeEffectiveFromCAD->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(192, 192, 192, 255), stop:1 rgba(128, 128, 128, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 120, 0, 255), stop:1 rgba(0, 192, 0, 255));\n"
"}"));
        toolButtonMakeEffectiveFromCAD->setCheckable(false);
        toolButtonMakeEffectiveFromCAD->setChecked(false);
        toolButtonMakeEffectiveFromCAD->setAutoExclusive(false);
        label = new QLabel(EasyPropertyMaskingForm);
        label->setObjectName("label");
        label->setGeometry(QRect(16, 670, 151, 31));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxShrinkDotForCAD = new QSpinBox(EasyPropertyMaskingForm);
        spinBoxShrinkDotForCAD->setObjectName("spinBoxShrinkDotForCAD");
        spinBoxShrinkDotForCAD->setGeometry(QRect(176, 670, 81, 31));
        QFont font2;
        font2.setPointSize(11);
        spinBoxShrinkDotForCAD->setFont(font2);
        spinBoxShrinkDotForCAD->setMaximum(100);
        spinBoxShrinkDotForCAD->setValue(20);
        label_2 = new QLabel(EasyPropertyMaskingForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(260, 670, 81, 31));
        doubleSpinBoxShrinkDotForCADMM = new QDoubleSpinBox(EasyPropertyMaskingForm);
        doubleSpinBoxShrinkDotForCADMM->setObjectName("doubleSpinBoxShrinkDotForCADMM");
        doubleSpinBoxShrinkDotForCADMM->setGeometry(QRect(176, 700, 81, 31));
        doubleSpinBoxShrinkDotForCADMM->setFont(font2);
        doubleSpinBoxShrinkDotForCADMM->setMaximum(9999.000000000000000);
        label_Unit = new QLabel(EasyPropertyMaskingForm);
        label_Unit->setObjectName("label_Unit");
        label_Unit->setGeometry(QRect(260, 700, 81, 31));
        toolButtonMakeOutlineArea = new QToolButton(EasyPropertyMaskingForm);
        toolButtonMakeOutlineArea->setObjectName("toolButtonMakeOutlineArea");
        toolButtonMakeOutlineArea->setGeometry(QRect(20, 740, 371, 71));
        toolButtonMakeOutlineArea->setFont(font);
        toolButtonMakeOutlineArea->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(192, 192, 192, 255), stop:1 rgba(128, 128, 128, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 120, 0, 255), stop:1 rgba(0, 192, 0, 255));\n"
"}"));
        toolButtonMakeOutlineArea->setCheckable(false);
        toolButtonMakeOutlineArea->setChecked(false);
        toolButtonMakeOutlineArea->setAutoExclusive(false);
        toolButtonSetAllPhases = new QToolButton(EasyPropertyMaskingForm);
        toolButtonSetAllPhases->setObjectName("toolButtonSetAllPhases");
        toolButtonSetAllPhases->setGeometry(QRect(20, 510, 371, 71));
        toolButtonSetAllPhases->setFont(font);
        toolButtonSetAllPhases->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(192, 192, 192, 255), stop:1 rgba(128, 128, 128, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 120, 0, 255), stop:1 rgba(0, 192, 0, 255));\n"
"}"));
        toolButtonSetAllPhases->setCheckable(true);
        toolButtonSetAllPhases->setChecked(true);
        toolButtonSetAllPhases->setAutoExclusive(false);
        toolButtonMakePatternEdge = new QToolButton(EasyPropertyMaskingForm);
        toolButtonMakePatternEdge->setObjectName("toolButtonMakePatternEdge");
        toolButtonMakePatternEdge->setGeometry(QRect(20, 820, 371, 71));
        toolButtonMakePatternEdge->setFont(font);
        toolButtonMakePatternEdge->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(192, 192, 192, 255), stop:1 rgba(128, 128, 128, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 120, 0, 255), stop:1 rgba(0, 192, 0, 255));\n"
"}"));
        toolButtonMakePatternEdge->setCheckable(false);
        toolButtonMakePatternEdge->setChecked(false);
        toolButtonMakePatternEdge->setAutoExclusive(false);
        toolButtonShowOnlyLibID = new QToolButton(EasyPropertyMaskingForm);
        toolButtonShowOnlyLibID->setObjectName("toolButtonShowOnlyLibID");
        toolButtonShowOnlyLibID->setGeometry(QRect(10, 120, 161, 31));
        toolButtonShowOnlyLibID->setCheckable(true);

        retranslateUi(EasyPropertyMaskingForm);

        QMetaObject::connectSlotsByName(EasyPropertyMaskingForm);
    } // setupUi

    void retranslateUi(GUIFormBase *EasyPropertyMaskingForm)
    {
        EasyPropertyMaskingForm->setWindowTitle(QCoreApplication::translate("EasyPropertyMaskingForm", "Form", nullptr));
        toolButtonAutoPickup->setText(QCoreApplication::translate("EasyPropertyMaskingForm", "\346\234\211\345\212\271\351\240\230\345\237\237\343\201\256\346\212\275\345\207\272", nullptr));
        toolButtonEffective->setText(QCoreApplication::translate("EasyPropertyMaskingForm", "\346\234\211\345\212\271\351\240\230\345\237\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLimited->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EasyPropertyMaskingForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLimited->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EasyPropertyMaskingForm", "\345\220\215\345\211\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLimited->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EasyPropertyMaskingForm", "\344\275\277\347\224\250\346\225\260", nullptr));
        toolButtonMakeEffectiveFromCAD->setText(QCoreApplication::translate("EasyPropertyMaskingForm", "CAD\350\274\252\351\203\255\343\201\213\343\202\211\346\234\211\345\212\271\351\240\230\345\237\237\347\224\237\346\210\220", nullptr));
        label->setText(QCoreApplication::translate("EasyPropertyMaskingForm", "CAD\347\267\232\343\201\213\343\202\211\345\217\216\347\270\256\351\207\217", nullptr));
        label_2->setText(QCoreApplication::translate("EasyPropertyMaskingForm", "Dot", nullptr));
        label_Unit->setText(QCoreApplication::translate("EasyPropertyMaskingForm", "mm", nullptr));
        toolButtonMakeOutlineArea->setText(QCoreApplication::translate("EasyPropertyMaskingForm", "\350\274\252\351\203\255\351\240\230\345\237\237\343\201\256\347\224\237\346\210\220", nullptr));
        toolButtonSetAllPhases->setText(QCoreApplication::translate("EasyPropertyMaskingForm", "\345\205\250\344\270\201\347\225\252\343\202\222\351\200\232\343\201\230\343\201\237\350\250\255\345\256\232", nullptr));
        toolButtonMakePatternEdge->setText(QCoreApplication::translate("EasyPropertyMaskingForm", "\343\203\221\343\202\277\343\203\274\343\203\263\350\274\252\351\203\255\351\240\230\345\237\237\343\201\256\347\224\237\346\210\220", nullptr));
        toolButtonShowOnlyLibID->setText(QCoreApplication::translate("EasyPropertyMaskingForm", "\351\201\270\346\212\236\350\241\214\343\201\256\343\201\277\350\241\250\347\244\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EasyPropertyMaskingForm: public Ui_EasyPropertyMaskingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EASYPROPERTYMASKINGFORM_H
