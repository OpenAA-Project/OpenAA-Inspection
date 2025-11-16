/********************************************************************************
** Form generated from reading UI file 'IntegrationShowTotalForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONSHOWTOTALFORM_H
#define UI_INTEGRATIONSHOWTOTALFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_IntegrationShowTotalForm
{
public:
    QTableWidget *tableWidget;
    QFrame *frame;
    QPushButton *PushButtonReset;
    QPushButton *pushButtonExcelSave;

    void setupUi(GUIFormBase *IntegrationShowTotalForm)
    {
        if (IntegrationShowTotalForm->objectName().isEmpty())
            IntegrationShowTotalForm->setObjectName("IntegrationShowTotalForm");
        IntegrationShowTotalForm->resize(290, 343);
        tableWidget = new QTableWidget(IntegrationShowTotalForm);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 7)
            tableWidget->setRowCount(7);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem7);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 291, 271));
        QFont font;
        font.setPointSize(14);
        tableWidget->setFont(font);
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setAutoScroll(false);
        tableWidget->setTabKeyNavigation(false);
        tableWidget->setProperty("showDropIndicator", QVariant(false));
        tableWidget->setDragDropOverwriteMode(false);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setMinimumSectionSize(36);
        tableWidget->verticalHeader()->setDefaultSectionSize(36);
        frame = new QFrame(IntegrationShowTotalForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 270, 281, 71));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        PushButtonReset = new QPushButton(frame);
        PushButtonReset->setObjectName("PushButtonReset");
        PushButtonReset->setGeometry(QRect(10, 10, 101, 51));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font1.setPointSize(14);
        PushButtonReset->setFont(font1);
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
        pushButtonExcelSave = new QPushButton(frame);
        pushButtonExcelSave->setObjectName("pushButtonExcelSave");
        pushButtonExcelSave->setGeometry(QRect(120, 10, 91, 51));
        pushButtonExcelSave->setFont(font);
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

        retranslateUi(IntegrationShowTotalForm);

        PushButtonReset->setDefault(false);


        QMetaObject::connectSlotsByName(IntegrationShowTotalForm);
    } // setupUi

    void retranslateUi(GUIFormBase *IntegrationShowTotalForm)
    {
        IntegrationShowTotalForm->setWindowTitle(QCoreApplication::translate("IntegrationShowTotalForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("IntegrationShowTotalForm", "\346\225\260\351\207\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("IntegrationShowTotalForm", "\347\267\217\346\244\234\346\237\273\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("IntegrationShowTotalForm", "\347\267\217OK\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("IntegrationShowTotalForm", "\347\267\217NG\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("IntegrationShowTotalForm", "\345\211\215OK", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("IntegrationShowTotalForm", "\345\276\214OK", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("IntegrationShowTotalForm", "\345\211\215NG", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("IntegrationShowTotalForm", "\345\276\214NG", nullptr));
        PushButtonReset->setText(QCoreApplication::translate("IntegrationShowTotalForm", "\343\203\252\343\202\273\343\203\203\343\203\210", nullptr));
        pushButtonExcelSave->setText(QCoreApplication::translate("IntegrationShowTotalForm", "EXCEL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationShowTotalForm: public Ui_IntegrationShowTotalForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONSHOWTOTALFORM_H
