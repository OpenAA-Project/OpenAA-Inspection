/********************************************************************************
** Form generated from reading UI file 'SelectLibraryOneDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLIBRARYONEDIALOG_H
#define UI_SELECTLIBRARYONEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectLibraryOneDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectLibraryOneDialog)
    {
        if (SelectLibraryOneDialog->objectName().isEmpty())
            SelectLibraryOneDialog->setObjectName("SelectLibraryOneDialog");
        SelectLibraryOneDialog->resize(422, 300);
        tableWidget = new QTableWidget(SelectLibraryOneDialog);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 401, 241));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelect = new QPushButton(SelectLibraryOneDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(50, 260, 112, 34));
        pushButtonCancel = new QPushButton(SelectLibraryOneDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(260, 260, 112, 34));

        retranslateUi(SelectLibraryOneDialog);

        pushButtonSelect->setDefault(true);


        QMetaObject::connectSlotsByName(SelectLibraryOneDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectLibraryOneDialog)
    {
        SelectLibraryOneDialog->setWindowTitle(QCoreApplication::translate("SelectLibraryOneDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectLibraryOneDialog", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectLibraryOneDialog", "Lib Name", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectLibraryOneDialog", "Select", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectLibraryOneDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibraryOneDialog: public Ui_SelectLibraryOneDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBRARYONEDIALOG_H
