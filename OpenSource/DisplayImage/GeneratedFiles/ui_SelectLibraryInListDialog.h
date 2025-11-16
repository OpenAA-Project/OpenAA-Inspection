/********************************************************************************
** Form generated from reading UI file 'SelectLibraryInListDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLIBRARYINLISTDIALOG_H
#define UI_SELECTLIBRARYINLISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectLibraryInListDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectLibraryInListDialog)
    {
        if (SelectLibraryInListDialog->objectName().isEmpty())
            SelectLibraryInListDialog->setObjectName("SelectLibraryInListDialog");
        SelectLibraryInListDialog->resize(410, 433);
        tableWidget = new QTableWidget(SelectLibraryInListDialog);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 411, 381));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelect = new QPushButton(SelectLibraryInListDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(60, 390, 101, 31));
        pushButtonCancel = new QPushButton(SelectLibraryInListDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(240, 390, 101, 31));

        retranslateUi(SelectLibraryInListDialog);

        pushButtonSelect->setDefault(true);


        QMetaObject::connectSlotsByName(SelectLibraryInListDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectLibraryInListDialog)
    {
        SelectLibraryInListDialog->setWindowTitle(QCoreApplication::translate("SelectLibraryInListDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectLibraryInListDialog", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectLibraryInListDialog", "LibName", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectLibraryInListDialog", "Select", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectLibraryInListDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibraryInListDialog: public Ui_SelectLibraryInListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBRARYINLISTDIALOG_H
