/********************************************************************************
** Form generated from reading UI file 'EditTransferHostDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITTRANSFERHOSTDIALOG_H
#define UI_EDITTRANSFERHOSTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditTransferHostDialog
{
public:
    QPushButton *pushButtonOverWriteFileTransfer;
    QPushButton *pushButtonTransferMinus;
    QTableWidget *tableWidgetTransfer;
    QPushButton *pushButtonTransferPlus;

    void setupUi(QDialog *EditTransferHostDialog)
    {
        if (EditTransferHostDialog->objectName().isEmpty())
            EditTransferHostDialog->setObjectName("EditTransferHostDialog");
        EditTransferHostDialog->resize(621, 446);
        pushButtonOverWriteFileTransfer = new QPushButton(EditTransferHostDialog);
        pushButtonOverWriteFileTransfer->setObjectName("pushButtonOverWriteFileTransfer");
        pushButtonOverWriteFileTransfer->setGeometry(QRect(260, 400, 101, 31));
        pushButtonTransferMinus = new QPushButton(EditTransferHostDialog);
        pushButtonTransferMinus->setObjectName("pushButtonTransferMinus");
        pushButtonTransferMinus->setGeometry(QRect(60, 400, 41, 34));
        QFont font;
        font.setPointSize(14);
        pushButtonTransferMinus->setFont(font);
        tableWidgetTransfer = new QTableWidget(EditTransferHostDialog);
        if (tableWidgetTransfer->columnCount() < 3)
            tableWidgetTransfer->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetTransfer->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetTransfer->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetTransfer->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetTransfer->setObjectName("tableWidgetTransfer");
        tableWidgetTransfer->setGeometry(QRect(10, 10, 601, 381));
        pushButtonTransferPlus = new QPushButton(EditTransferHostDialog);
        pushButtonTransferPlus->setObjectName("pushButtonTransferPlus");
        pushButtonTransferPlus->setGeometry(QRect(10, 400, 41, 34));
        pushButtonTransferPlus->setFont(font);

        retranslateUi(EditTransferHostDialog);

        QMetaObject::connectSlotsByName(EditTransferHostDialog);
    } // setupUi

    void retranslateUi(QDialog *EditTransferHostDialog)
    {
        EditTransferHostDialog->setWindowTitle(QCoreApplication::translate("EditTransferHostDialog", "Edit transfer-host", nullptr));
        pushButtonOverWriteFileTransfer->setText(QCoreApplication::translate("EditTransferHostDialog", "OverWrite", nullptr));
        pushButtonTransferMinus->setText(QCoreApplication::translate("EditTransferHostDialog", "-", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetTransfer->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditTransferHostDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetTransfer->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditTransferHostDialog", "Host/IP address", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetTransfer->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EditTransferHostDialog", "Port", nullptr));
        pushButtonTransferPlus->setText(QCoreApplication::translate("EditTransferHostDialog", "+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditTransferHostDialog: public Ui_EditTransferHostDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITTRANSFERHOSTDIALOG_H
