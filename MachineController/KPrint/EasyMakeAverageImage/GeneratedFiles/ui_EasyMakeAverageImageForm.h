/********************************************************************************
** Form generated from reading UI file 'EasyMakeAverageImageForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EASYMAKEAVERAGEIMAGEFORM_H
#define UI_EASYMAKEAVERAGEIMAGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_EasyMakeAverageImageForm
{
public:
    QToolButton *toolButtonScan;
    QToolButton *toolButtonGenerateImage;
    QTableWidget *tableWidget;
    QLabel *label;
    QFrame *frame;
    QToolButton *toolButtonViewMaster;
    QLabel *label_2;
    QToolButton *toolButtonViewLowSide;
    QToolButton *toolButtonViewHighSide;
    QToolButton *toolButtonViewVariation;
    QToolButton *toolButtonViewAverage;
    QToolButton *toolButtonResetAverage;

    void setupUi(GUIFormBase *EasyMakeAverageImageForm)
    {
        if (EasyMakeAverageImageForm->objectName().isEmpty())
            EasyMakeAverageImageForm->setObjectName("EasyMakeAverageImageForm");
        EasyMakeAverageImageForm->resize(300, 874);
        toolButtonScan = new QToolButton(EasyMakeAverageImageForm);
        toolButtonScan->setObjectName("toolButtonScan");
        toolButtonScan->setGeometry(QRect(10, 10, 281, 111));
        QFont font;
        font.setPointSize(26);
        toolButtonScan->setFont(font);
        toolButtonScan->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 165, 165, 255), stop:1 rgba(141, 100, 100, 255));\n"
"}"));
        toolButtonScan->setCheckable(true);
        toolButtonScan->setChecked(false);
        toolButtonGenerateImage = new QToolButton(EasyMakeAverageImageForm);
        toolButtonGenerateImage->setObjectName("toolButtonGenerateImage");
        toolButtonGenerateImage->setGeometry(QRect(10, 400, 281, 111));
        toolButtonGenerateImage->setFont(font);
        toolButtonGenerateImage->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonGenerateImage->setCheckable(false);
        tableWidget = new QTableWidget(EasyMakeAverageImageForm);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 130, 281, 241));
        QFont font1;
        font1.setPointSize(12);
        tableWidget->setFont(font1);
        label = new QLabel(EasyMakeAverageImageForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 380, 271, 18));
        frame = new QFrame(EasyMakeAverageImageForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 520, 281, 281));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonViewMaster = new QToolButton(frame);
        toolButtonViewMaster->setObjectName("toolButtonViewMaster");
        toolButtonViewMaster->setGeometry(QRect(10, 30, 261, 41));
        toolButtonViewMaster->setFont(font1);
        toolButtonViewMaster->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked{ 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 80, 80, 255), stop:1 rgba(141, 50, 50, 255));\n"
"}"));
        toolButtonViewMaster->setCheckable(true);
        toolButtonViewMaster->setChecked(true);
        toolButtonViewMaster->setAutoExclusive(true);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 281, 20));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        label_2->setFont(font2);
        label_2->setAlignment(Qt::AlignCenter);
        toolButtonViewLowSide = new QToolButton(frame);
        toolButtonViewLowSide->setObjectName("toolButtonViewLowSide");
        toolButtonViewLowSide->setGeometry(QRect(10, 80, 261, 41));
        toolButtonViewLowSide->setFont(font1);
        toolButtonViewLowSide->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 80, 80, 255), stop:1 rgba(141, 50, 50, 255));\n"
"}"));
        toolButtonViewLowSide->setCheckable(true);
        toolButtonViewLowSide->setAutoExclusive(true);
        toolButtonViewHighSide = new QToolButton(frame);
        toolButtonViewHighSide->setObjectName("toolButtonViewHighSide");
        toolButtonViewHighSide->setGeometry(QRect(10, 130, 261, 41));
        toolButtonViewHighSide->setFont(font1);
        toolButtonViewHighSide->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 80, 80, 255), stop:1 rgba(141, 50, 50, 255));\n"
"}"));
        toolButtonViewHighSide->setCheckable(true);
        toolButtonViewHighSide->setAutoExclusive(true);
        toolButtonViewVariation = new QToolButton(frame);
        toolButtonViewVariation->setObjectName("toolButtonViewVariation");
        toolButtonViewVariation->setGeometry(QRect(10, 180, 261, 41));
        toolButtonViewVariation->setFont(font1);
        toolButtonViewVariation->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 80, 80, 255), stop:1 rgba(141, 50, 50, 255));\n"
"}"));
        toolButtonViewVariation->setCheckable(true);
        toolButtonViewVariation->setAutoExclusive(true);
        toolButtonViewAverage = new QToolButton(frame);
        toolButtonViewAverage->setObjectName("toolButtonViewAverage");
        toolButtonViewAverage->setGeometry(QRect(10, 230, 261, 41));
        toolButtonViewAverage->setFont(font1);
        toolButtonViewAverage->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 80, 80, 255), stop:1 rgba(141, 50, 50, 255));\n"
"}"));
        toolButtonViewAverage->setCheckable(true);
        toolButtonViewAverage->setAutoExclusive(true);
        toolButtonResetAverage = new QToolButton(EasyMakeAverageImageForm);
        toolButtonResetAverage->setObjectName("toolButtonResetAverage");
        toolButtonResetAverage->setGeometry(QRect(10, 810, 281, 61));
        toolButtonResetAverage->setFont(font);
        toolButtonResetAverage->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonResetAverage->setCheckable(false);

        retranslateUi(EasyMakeAverageImageForm);

        QMetaObject::connectSlotsByName(EasyMakeAverageImageForm);
    } // setupUi

    void retranslateUi(GUIFormBase *EasyMakeAverageImageForm)
    {
        EasyMakeAverageImageForm->setWindowTitle(QCoreApplication::translate("EasyMakeAverageImageForm", "Form", nullptr));
        toolButtonScan->setText(QCoreApplication::translate("EasyMakeAverageImageForm", "\346\222\256\345\275\261", nullptr));
        toolButtonGenerateImage->setText(QCoreApplication::translate("EasyMakeAverageImageForm", "\345\217\215\346\230\240", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EasyMakeAverageImageForm", "Phase", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EasyMakeAverageImageForm", "Count", nullptr));
        label->setText(QCoreApplication::translate("EasyMakeAverageImageForm", "\343\203\252\343\202\271\343\203\210\343\201\256\343\203\200\343\203\226\343\203\253\343\202\257\343\203\252\343\203\203\343\202\257\343\201\247\343\202\257\343\203\252\343\202\242", nullptr));
        toolButtonViewMaster->setText(QCoreApplication::translate("EasyMakeAverageImageForm", "\343\203\236\343\202\271\343\202\277\343\203\274", nullptr));
        label_2->setText(QCoreApplication::translate("EasyMakeAverageImageForm", "\350\241\250\347\244\272", nullptr));
        toolButtonViewLowSide->setText(QCoreApplication::translate("EasyMakeAverageImageForm", "\346\232\227\345\201\264", nullptr));
        toolButtonViewHighSide->setText(QCoreApplication::translate("EasyMakeAverageImageForm", "\346\230\216\345\201\264", nullptr));
        toolButtonViewVariation->setText(QCoreApplication::translate("EasyMakeAverageImageForm", "\343\203\220\343\203\251\343\203\204\343\202\255", nullptr));
        toolButtonViewAverage->setText(QCoreApplication::translate("EasyMakeAverageImageForm", "\345\271\263\345\235\207\345\214\226", nullptr));
        toolButtonResetAverage->setText(QCoreApplication::translate("EasyMakeAverageImageForm", "\343\203\252\343\202\273\343\203\203\343\203\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EasyMakeAverageImageForm: public Ui_EasyMakeAverageImageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EASYMAKEAVERAGEIMAGEFORM_H
