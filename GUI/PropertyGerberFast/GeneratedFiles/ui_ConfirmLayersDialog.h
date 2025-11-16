/********************************************************************************
** Form generated from reading UI file 'ConfirmLayersDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIRMLAYERSDIALOG_H
#define UI_CONFIRMLAYERSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfirmLayersDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonClearAll;

    void setupUi(QDialog *ConfirmLayersDialog)
    {
        if (ConfirmLayersDialog->objectName().isEmpty())
            ConfirmLayersDialog->setObjectName("ConfirmLayersDialog");
        ConfirmLayersDialog->resize(1111, 626);
        tableWidget = new QTableWidget(ConfirmLayersDialog);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 1111, 571));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonOK = new QPushButton(ConfirmLayersDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(450, 580, 161, 31));
        pushButtonCancel = new QPushButton(ConfirmLayersDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(1010, 580, 93, 31));
        pushButtonClearAll = new QPushButton(ConfirmLayersDialog);
        pushButtonClearAll->setObjectName("pushButtonClearAll");
        pushButtonClearAll->setGeometry(QRect(10, 580, 93, 31));

        retranslateUi(ConfirmLayersDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(ConfirmLayersDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfirmLayersDialog)
    {
        ConfirmLayersDialog->setWindowTitle(QCoreApplication::translate("ConfirmLayersDialog", "Confirm layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ConfirmLayersDialog", "Chk", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ConfirmLayersDialog", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ConfirmLayersDialog", "File name", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("ConfirmLayersDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("ConfirmLayersDialog", "Cancel", nullptr));
        pushButtonClearAll->setText(QCoreApplication::translate("ConfirmLayersDialog", "Clear all", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfirmLayersDialog: public Ui_ConfirmLayersDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIRMLAYERSDIALOG_H
