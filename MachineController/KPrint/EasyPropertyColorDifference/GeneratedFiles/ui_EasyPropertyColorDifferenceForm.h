/********************************************************************************
** Form generated from reading UI file 'EasyPropertyColorDifferenceForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EASYPROPERTYCOLORDIFFERENCEFORM_H
#define UI_EASYPROPERTYCOLORDIFFERENCEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_EasyPropertyColorDifferenceForm
{
public:
    QFrame *frame;
    QToolButton *toolButtonReference;
    QToolButton *toolButtonItem;
    QTableWidget *tableWidgetLibList;
    QToolButton *toolButtonRegisterNG;
    QToolButton *toolButtonRegisterOK;
    QLabel *label;
    QToolButton *toolButtonRegistInFlow;
    QLabel *label_2;
    QLineEdit *lineEditCurrentFlowCount;
    QToolButton *toolButtonSetThresholdByFlow;
    QToolButton *toolButtonClearFlow;
    QToolButton *toolButtonAutoGenerate;

    void setupUi(GUIFormBase *EasyPropertyColorDifferenceForm)
    {
        if (EasyPropertyColorDifferenceForm->objectName().isEmpty())
            EasyPropertyColorDifferenceForm->setObjectName("EasyPropertyColorDifferenceForm");
        EasyPropertyColorDifferenceForm->resize(309, 907);
        frame = new QFrame(EasyPropertyColorDifferenceForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 301, 211));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonReference = new QToolButton(frame);
        toolButtonReference->setObjectName("toolButtonReference");
        toolButtonReference->setGeometry(QRect(10, 110, 271, 91));
        QFont font;
        font.setPointSize(20);
        toolButtonReference->setFont(font);
        toolButtonReference->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 230, 230, 255), stop:1 rgba(165, 130, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonReference->setCheckable(true);
        toolButtonReference->setAutoExclusive(true);
        toolButtonItem = new QToolButton(frame);
        toolButtonItem->setObjectName("toolButtonItem");
        toolButtonItem->setGeometry(QRect(10, 10, 271, 91));
        toolButtonItem->setFont(font);
        toolButtonItem->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 254, 230, 255), stop:1 rgba(130, 165, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonItem->setCheckable(true);
        toolButtonItem->setChecked(true);
        toolButtonItem->setAutoExclusive(true);
        tableWidgetLibList = new QTableWidget(EasyPropertyColorDifferenceForm);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 210, 281, 181));
        QFont font1;
        font1.setPointSize(12);
        tableWidgetLibList->setFont(font1);
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetLibList->verticalHeader()->setMinimumSectionSize(48);
        tableWidgetLibList->verticalHeader()->setDefaultSectionSize(48);
        toolButtonRegisterNG = new QToolButton(EasyPropertyColorDifferenceForm);
        toolButtonRegisterNG->setObjectName("toolButtonRegisterNG");
        toolButtonRegisterNG->setGeometry(QRect(20, 833, 241, 61));
        toolButtonRegisterNG->setFont(font);
        toolButtonRegisterNG->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 230, 230, 255), stop:1 rgba(165, 130, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonRegisterNG->setCheckable(false);
        toolButtonRegisterNG->setAutoExclusive(false);
        toolButtonRegisterOK = new QToolButton(EasyPropertyColorDifferenceForm);
        toolButtonRegisterOK->setObjectName("toolButtonRegisterOK");
        toolButtonRegisterOK->setGeometry(QRect(20, 763, 241, 61));
        toolButtonRegisterOK->setFont(font);
        toolButtonRegisterOK->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 254, 230, 255), stop:1 rgba(130, 165, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonRegisterOK->setCheckable(false);
        toolButtonRegisterOK->setChecked(false);
        toolButtonRegisterOK->setAutoExclusive(false);
        label = new QLabel(EasyPropertyColorDifferenceForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 730, 271, 21));
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        toolButtonRegistInFlow = new QToolButton(EasyPropertyColorDifferenceForm);
        toolButtonRegistInFlow->setObjectName("toolButtonRegistInFlow");
        toolButtonRegistInFlow->setGeometry(QRect(10, 480, 281, 71));
        toolButtonRegistInFlow->setFont(font);
        toolButtonRegistInFlow->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 254, 230, 255), stop:1 rgba(130, 165, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonRegistInFlow->setCheckable(true);
        toolButtonRegistInFlow->setChecked(false);
        toolButtonRegistInFlow->setAutoExclusive(false);
        label_2 = new QLabel(EasyPropertyColorDifferenceForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 570, 61, 21));
        lineEditCurrentFlowCount = new QLineEdit(EasyPropertyColorDifferenceForm);
        lineEditCurrentFlowCount->setObjectName("lineEditCurrentFlowCount");
        lineEditCurrentFlowCount->setGeometry(QRect(90, 570, 91, 24));
        toolButtonSetThresholdByFlow = new QToolButton(EasyPropertyColorDifferenceForm);
        toolButtonSetThresholdByFlow->setObjectName("toolButtonSetThresholdByFlow");
        toolButtonSetThresholdByFlow->setGeometry(QRect(10, 630, 291, 61));
        QFont font2;
        font2.setPointSize(14);
        toolButtonSetThresholdByFlow->setFont(font2);
        toolButtonSetThresholdByFlow->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 254, 230, 255), stop:1 rgba(130, 165, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonSetThresholdByFlow->setCheckable(false);
        toolButtonSetThresholdByFlow->setChecked(false);
        toolButtonSetThresholdByFlow->setAutoExclusive(false);
        toolButtonClearFlow = new QToolButton(EasyPropertyColorDifferenceForm);
        toolButtonClearFlow->setObjectName("toolButtonClearFlow");
        toolButtonClearFlow->setGeometry(QRect(190, 560, 101, 51));
        toolButtonClearFlow->setFont(font);
        toolButtonClearFlow->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 230, 230, 255), stop:1 rgba(165, 130, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonClearFlow->setCheckable(false);
        toolButtonClearFlow->setAutoExclusive(false);
        toolButtonAutoGenerate = new QToolButton(EasyPropertyColorDifferenceForm);
        toolButtonAutoGenerate->setObjectName("toolButtonAutoGenerate");
        toolButtonAutoGenerate->setGeometry(QRect(10, 400, 281, 71));
        toolButtonAutoGenerate->setFont(font);
        toolButtonAutoGenerate->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(240, 200, 120, 255), stop:1 rgba(165, 130, 80, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonAutoGenerate->setCheckable(false);
        toolButtonAutoGenerate->setChecked(false);
        toolButtonAutoGenerate->setAutoExclusive(false);

        retranslateUi(EasyPropertyColorDifferenceForm);

        QMetaObject::connectSlotsByName(EasyPropertyColorDifferenceForm);
    } // setupUi

    void retranslateUi(GUIFormBase *EasyPropertyColorDifferenceForm)
    {
        EasyPropertyColorDifferenceForm->setWindowTitle(QCoreApplication::translate("EasyPropertyColorDifferenceForm", "Form", nullptr));
        toolButtonReference->setText(QCoreApplication::translate("EasyPropertyColorDifferenceForm", "\345\217\202\347\205\247\351\240\230\345\237\237", nullptr));
        toolButtonItem->setText(QCoreApplication::translate("EasyPropertyColorDifferenceForm", "\350\211\262\345\267\256\346\244\234\346\237\273\351\240\230\345\237\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EasyPropertyColorDifferenceForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EasyPropertyColorDifferenceForm", "\345\220\215\345\211\215", nullptr));
        toolButtonRegisterNG->setText(QCoreApplication::translate("EasyPropertyColorDifferenceForm", "NG\350\211\262\347\231\273\351\214\262", nullptr));
        toolButtonRegisterOK->setText(QCoreApplication::translate("EasyPropertyColorDifferenceForm", "OK\350\211\262\347\231\273\351\214\262", nullptr));
        label->setText(QCoreApplication::translate("EasyPropertyColorDifferenceForm", "\347\217\276\345\234\250\343\201\256\346\244\234\346\237\273\347\224\273\345\203\217\343\202\222\347\231\273\351\214\262", nullptr));
        toolButtonRegistInFlow->setText(QCoreApplication::translate("EasyPropertyColorDifferenceForm", "OK\346\265\201\345\213\225\347\231\273\351\214\262", nullptr));
        label_2->setText(QCoreApplication::translate("EasyPropertyColorDifferenceForm", "\347\217\276\345\234\250\346\225\260", nullptr));
        toolButtonSetThresholdByFlow->setText(QCoreApplication::translate("EasyPropertyColorDifferenceForm", "OK\346\265\201\345\213\225\343\201\247\343\201\256\343\201\227\343\201\215\343\201\204\345\200\244\347\231\273\351\214\262", nullptr));
        toolButtonClearFlow->setText(QCoreApplication::translate("EasyPropertyColorDifferenceForm", "\343\202\257\343\203\252\343\202\242", nullptr));
        toolButtonAutoGenerate->setText(QCoreApplication::translate("EasyPropertyColorDifferenceForm", "\350\207\252\345\213\225\347\224\237\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EasyPropertyColorDifferenceForm: public Ui_EasyPropertyColorDifferenceForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EASYPROPERTYCOLORDIFFERENCEFORM_H
