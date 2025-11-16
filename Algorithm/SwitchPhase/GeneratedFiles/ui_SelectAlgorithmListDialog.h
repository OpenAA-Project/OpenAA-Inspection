/********************************************************************************
** Form generated from reading UI file 'SelectAlgorithmListDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTALGORITHMLISTDIALOG_H
#define UI_SELECTALGORITHMLISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectAlgorithmListDialog
{
public:
    QTableWidget *tableWidgetAlgorithmList;
    QTableWidget *tableWidgetOperationList;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonGet;
    QPushButton *pushButtonReturn;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *SelectAlgorithmListDialog)
    {
        if (SelectAlgorithmListDialog->objectName().isEmpty())
            SelectAlgorithmListDialog->setObjectName("SelectAlgorithmListDialog");
        SelectAlgorithmListDialog->resize(688, 335);
        tableWidgetAlgorithmList = new QTableWidget(SelectAlgorithmListDialog);
        if (tableWidgetAlgorithmList->columnCount() < 2)
            tableWidgetAlgorithmList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetAlgorithmList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetAlgorithmList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetAlgorithmList->setObjectName("tableWidgetAlgorithmList");
        tableWidgetAlgorithmList->setGeometry(QRect(10, 40, 301, 241));
        tableWidgetAlgorithmList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAlgorithmList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetOperationList = new QTableWidget(SelectAlgorithmListDialog);
        if (tableWidgetOperationList->columnCount() < 2)
            tableWidgetOperationList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetOperationList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetOperationList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetOperationList->setObjectName("tableWidgetOperationList");
        tableWidgetOperationList->setGeometry(QRect(380, 40, 301, 241));
        tableWidgetOperationList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetOperationList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonOK = new QPushButton(SelectAlgorithmListDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(220, 290, 112, 34));
        pushButtonCancel = new QPushButton(SelectAlgorithmListDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(350, 290, 112, 34));
        pushButtonGet = new QPushButton(SelectAlgorithmListDialog);
        pushButtonGet->setObjectName("pushButtonGet");
        pushButtonGet->setGeometry(QRect(320, 100, 51, 34));
        pushButtonReturn = new QPushButton(SelectAlgorithmListDialog);
        pushButtonReturn->setObjectName("pushButtonReturn");
        pushButtonReturn->setGeometry(QRect(320, 170, 51, 34));
        label = new QLabel(SelectAlgorithmListDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 301, 31));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(SelectAlgorithmListDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(380, 10, 301, 31));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(SelectAlgorithmListDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SelectAlgorithmListDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectAlgorithmListDialog)
    {
        SelectAlgorithmListDialog->setWindowTitle(QCoreApplication::translate("SelectAlgorithmListDialog", "\343\202\263\343\203\224\343\203\274\343\201\231\343\202\213\343\202\242\343\203\253\343\202\264\343\203\252\343\202\272\343\203\240\351\201\270\346\212\236", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetAlgorithmList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectAlgorithmListDialog", "Root", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetAlgorithmList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectAlgorithmListDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetOperationList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectAlgorithmListDialog", "Root", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetOperationList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectAlgorithmListDialog", "Name", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectAlgorithmListDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectAlgorithmListDialog", "Cancel", nullptr));
        pushButtonGet->setText(QCoreApplication::translate("SelectAlgorithmListDialog", ">", nullptr));
        pushButtonReturn->setText(QCoreApplication::translate("SelectAlgorithmListDialog", "<", nullptr));
        label->setText(QCoreApplication::translate("SelectAlgorithmListDialog", "\343\202\242\343\203\253\343\202\264\343\203\252\343\202\272\343\203\240\343\203\252\343\202\271\343\203\210", nullptr));
        label_2->setText(QCoreApplication::translate("SelectAlgorithmListDialog", "\346\223\215\344\275\234\345\257\276\350\261\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectAlgorithmListDialog: public Ui_SelectAlgorithmListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTALGORITHMLISTDIALOG_H
