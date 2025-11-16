/********************************************************************************
** Form generated from reading UI file 'SelectAlignmentAreaForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTALIGNMENTAREAFORM_H
#define UI_SELECTALIGNMENTAREAFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectAlignmentAreaForm
{
public:
    QTableWidget *tableWidget;
    QToolButton *toolButtonCancel;
    QToolButton *toolButtonSelect;

    void setupUi(QWidget *SelectAlignmentAreaForm)
    {
        if (SelectAlignmentAreaForm->objectName().isEmpty())
            SelectAlignmentAreaForm->setObjectName("SelectAlignmentAreaForm");
        SelectAlignmentAreaForm->resize(420, 300);
        tableWidget = new QTableWidget(SelectAlignmentAreaForm);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 401, 211));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        toolButtonCancel = new QToolButton(SelectAlignmentAreaForm);
        toolButtonCancel->setObjectName("toolButtonCancel");
        toolButtonCancel->setGeometry(QRect(220, 230, 191, 61));
        QFont font;
        font.setPointSize(24);
        toolButtonCancel->setFont(font);
        toolButtonCancel->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254,100 , 120, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(255, 180, 0, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonCancel->setCheckable(false);
        toolButtonCancel->setChecked(false);
        toolButtonSelect = new QToolButton(SelectAlignmentAreaForm);
        toolButtonSelect->setObjectName("toolButtonSelect");
        toolButtonSelect->setGeometry(QRect(10, 230, 191, 61));
        QFont font1;
        font1.setPointSize(26);
        toolButtonSelect->setFont(font1);
        toolButtonSelect->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(100, 254, 120, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(255, 180, 0, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonSelect->setCheckable(false);
        toolButtonSelect->setChecked(false);

        retranslateUi(SelectAlignmentAreaForm);

        QMetaObject::connectSlotsByName(SelectAlignmentAreaForm);
    } // setupUi

    void retranslateUi(QWidget *SelectAlignmentAreaForm)
    {
        SelectAlignmentAreaForm->setWindowTitle(QCoreApplication::translate("SelectAlignmentAreaForm", "Select area", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectAlignmentAreaForm", "\345\204\252\345\205\210\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectAlignmentAreaForm", "\351\240\230\345\237\237\345\220\215", nullptr));
        toolButtonCancel->setText(QCoreApplication::translate("SelectAlignmentAreaForm", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        toolButtonSelect->setText(QCoreApplication::translate("SelectAlignmentAreaForm", "\351\201\270\346\212\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectAlignmentAreaForm: public Ui_SelectAlignmentAreaForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTALIGNMENTAREAFORM_H
