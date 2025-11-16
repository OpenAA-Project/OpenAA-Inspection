/********************************************************************************
** Form generated from reading UI file 'ShowListDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWLISTDIALOG_H
#define UI_SHOWLISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowListDialog
{
public:
    QTableWidget *tableWidgetShotList;
    QFrame *frame;
    QTableWidget *tableListInOneShot;

    void setupUi(QDialog *ShowListDialog)
    {
        if (ShowListDialog->objectName().isEmpty())
            ShowListDialog->setObjectName("ShowListDialog");
        ShowListDialog->resize(1167, 632);
        tableWidgetShotList = new QTableWidget(ShowListDialog);
        if (tableWidgetShotList->columnCount() < 4)
            tableWidgetShotList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetShotList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetShotList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetShotList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetShotList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetShotList->setObjectName("tableWidgetShotList");
        tableWidgetShotList->setGeometry(QRect(0, 0, 361, 631));
        tableWidgetShotList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetShotList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(ShowListDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(570, 0, 591, 631));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        tableListInOneShot = new QTableWidget(ShowListDialog);
        if (tableListInOneShot->columnCount() < 3)
            tableListInOneShot->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableListInOneShot->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableListInOneShot->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableListInOneShot->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        tableListInOneShot->setObjectName("tableListInOneShot");
        tableListInOneShot->setGeometry(QRect(370, 0, 191, 631));
        tableListInOneShot->setSelectionMode(QAbstractItemView::SingleSelection);
        tableListInOneShot->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(ShowListDialog);

        QMetaObject::connectSlotsByName(ShowListDialog);
    } // setupUi

    void retranslateUi(QDialog *ShowListDialog)
    {
        ShowListDialog->setWindowTitle(QCoreApplication::translate("ShowListDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetShotList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowListDialog", "\346\231\202\351\226\223", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetShotList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowListDialog", "Phase", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetShotList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowListDialog", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetShotList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowListDialog", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableListInOneShot->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ShowListDialog", "Phase", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableListInOneShot->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ShowListDialog", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableListInOneShot->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ShowListDialog", "Layer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowListDialog: public Ui_ShowListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWLISTDIALOG_H
