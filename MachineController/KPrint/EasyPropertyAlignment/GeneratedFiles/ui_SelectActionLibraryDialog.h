/********************************************************************************
** Form generated from reading UI file 'SelectActionLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTACTIONLIBRARYDIALOG_H
#define UI_SELECTACTIONLIBRARYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SelectActionLibraryDialog
{
public:
    QToolButton *toolButtonAddLibrary;
    QToolButton *toolButtonRemoveLibrary;
    QListWidget *listWidgetLibType;
    QTableWidget *tableWidgetLibrary;

    void setupUi(QDialog *SelectActionLibraryDialog)
    {
        if (SelectActionLibraryDialog->objectName().isEmpty())
            SelectActionLibraryDialog->setObjectName("SelectActionLibraryDialog");
        SelectActionLibraryDialog->resize(622, 432);
        toolButtonAddLibrary = new QToolButton(SelectActionLibraryDialog);
        toolButtonAddLibrary->setObjectName("toolButtonAddLibrary");
        toolButtonAddLibrary->setGeometry(QRect(20, 320, 221, 91));
        QFont font;
        font.setPointSize(26);
        toolButtonAddLibrary->setFont(font);
        toolButtonAddLibrary->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(100, 254, 120, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(255, 180, 0, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonAddLibrary->setCheckable(false);
        toolButtonAddLibrary->setChecked(false);
        toolButtonRemoveLibrary = new QToolButton(SelectActionLibraryDialog);
        toolButtonRemoveLibrary->setObjectName("toolButtonRemoveLibrary");
        toolButtonRemoveLibrary->setGeometry(QRect(390, 320, 211, 91));
        toolButtonRemoveLibrary->setFont(font);
        toolButtonRemoveLibrary->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254,100 , 120, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(255, 180, 0, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonRemoveLibrary->setCheckable(false);
        toolButtonRemoveLibrary->setChecked(false);
        listWidgetLibType = new QListWidget(SelectActionLibraryDialog);
        listWidgetLibType->setObjectName("listWidgetLibType");
        listWidgetLibType->setGeometry(QRect(10, 10, 181, 301));
        tableWidgetLibrary = new QTableWidget(SelectActionLibraryDialog);
        if (tableWidgetLibrary->columnCount() < 2)
            tableWidgetLibrary->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibrary->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibrary->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibrary->setObjectName("tableWidgetLibrary");
        tableWidgetLibrary->setGeometry(QRect(200, 10, 411, 301));
        tableWidgetLibrary->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibrary->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(SelectActionLibraryDialog);

        QMetaObject::connectSlotsByName(SelectActionLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectActionLibraryDialog)
    {
        SelectActionLibraryDialog->setWindowTitle(QCoreApplication::translate("SelectActionLibraryDialog", "Dialog", nullptr));
        toolButtonAddLibrary->setText(QCoreApplication::translate("SelectActionLibraryDialog", "\350\277\275\345\212\240", nullptr));
        toolButtonRemoveLibrary->setText(QCoreApplication::translate("SelectActionLibraryDialog", "\345\211\212\351\231\244", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibrary->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectActionLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibrary->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectActionLibraryDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectActionLibraryDialog: public Ui_SelectActionLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTACTIONLIBRARYDIALOG_H
