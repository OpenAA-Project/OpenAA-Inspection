/********************************************************************************
** Form generated from reading UI file 'ShowCountFromPIForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWCOUNTFROMPIFORM_H
#define UI_SHOWCOUNTFROMPIFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ShowCountFromPIForm
{
public:
    QTableWidget *tableWidget;

    void setupUi(GUIFormBase *ShowCountFromPIForm)
    {
        if (ShowCountFromPIForm->objectName().isEmpty())
            ShowCountFromPIForm->setObjectName("ShowCountFromPIForm");
        ShowCountFromPIForm->resize(291, 153);
        tableWidget = new QTableWidget(ShowCountFromPIForm);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 4)
            tableWidget->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem4);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 291, 151));
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

        retranslateUi(ShowCountFromPIForm);

        QMetaObject::connectSlotsByName(ShowCountFromPIForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowCountFromPIForm)
    {
        ShowCountFromPIForm->setWindowTitle(QCoreApplication::translate("ShowCountFromPIForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowCountFromPIForm", "\346\225\260\351\207\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowCountFromPIForm", "\347\267\217\346\244\234\346\237\273\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowCountFromPIForm", "\347\267\217OK\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowCountFromPIForm", "\347\267\217NG\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ShowCountFromPIForm", "\347\267\217TM\346\225\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowCountFromPIForm: public Ui_ShowCountFromPIForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWCOUNTFROMPIFORM_H
