/********************************************************************************
** Form generated from reading UI file 'SelectListDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLISTDIALOG_H
#define UI_SELECTLISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectListDialog
{
public:
    QTableWidget *tableWidgetLight;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectListDialog)
    {
        if (SelectListDialog->objectName().isEmpty())
            SelectListDialog->setObjectName("SelectListDialog");
        SelectListDialog->resize(470, 340);
        tableWidgetLight = new QTableWidget(SelectListDialog);
        if (tableWidgetLight->columnCount() < 3)
            tableWidgetLight->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLight->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLight->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLight->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetLight->setObjectName("tableWidgetLight");
        tableWidgetLight->setGeometry(QRect(0, 0, 471, 291));
        tableWidgetLight->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLight->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelect = new QPushButton(SelectListDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(90, 300, 111, 31));
        pushButtonCancel = new QPushButton(SelectListDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(290, 300, 111, 31));

        retranslateUi(SelectListDialog);

        pushButtonSelect->setDefault(true);


        QMetaObject::connectSlotsByName(SelectListDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectListDialog)
    {
        SelectListDialog->setWindowTitle(QCoreApplication::translate("SelectListDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLight->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectListDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLight->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectListDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLight->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectListDialog", "Remark", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectListDialog", "Select", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectListDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectListDialog: public Ui_SelectListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLISTDIALOG_H
