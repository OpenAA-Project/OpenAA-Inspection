/********************************************************************************
** Form generated from reading UI file 'SelectByBindedLimitedDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTBYBINDEDLIMITEDDIALOG_H
#define UI_SELECTBYBINDEDLIMITEDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SelectByBindedLimitedDialog
{
public:
    QTableWidget *tableWidgetBinded;
    QTableWidget *tableWidgetLibList;
    QToolButton *toolButtonPage;
    QToolButton *toolButtonLayer;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonEdit;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *SelectByBindedLimitedDialog)
    {
        if (SelectByBindedLimitedDialog->objectName().isEmpty())
            SelectByBindedLimitedDialog->setObjectName("SelectByBindedLimitedDialog");
        SelectByBindedLimitedDialog->resize(836, 399);
        tableWidgetBinded = new QTableWidget(SelectByBindedLimitedDialog);
        if (tableWidgetBinded->columnCount() < 4)
            tableWidgetBinded->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetBinded->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetBinded->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetBinded->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetBinded->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetBinded->setObjectName("tableWidgetBinded");
        tableWidgetBinded->setGeometry(QRect(10, 50, 351, 291));
        tableWidgetBinded->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetBinded->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetLibList = new QTableWidget(SelectByBindedLimitedDialog);
        if (tableWidgetLibList->columnCount() < 3)
            tableWidgetLibList->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(370, 50, 451, 291));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        toolButtonPage = new QToolButton(SelectByBindedLimitedDialog);
        toolButtonPage->setObjectName("toolButtonPage");
        toolButtonPage->setGeometry(QRect(20, 10, 81, 31));
        toolButtonPage->setCheckable(true);
        toolButtonLayer = new QToolButton(SelectByBindedLimitedDialog);
        toolButtonLayer->setObjectName("toolButtonLayer");
        toolButtonLayer->setGeometry(QRect(110, 10, 81, 31));
        toolButtonLayer->setCheckable(true);
        pushButtonSelect = new QPushButton(SelectByBindedLimitedDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(60, 350, 112, 34));
        pushButtonEdit = new QPushButton(SelectByBindedLimitedDialog);
        pushButtonEdit->setObjectName("pushButtonEdit");
        pushButtonEdit->setGeometry(QRect(230, 350, 112, 34));
        pushButtonClose = new QPushButton(SelectByBindedLimitedDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(710, 350, 112, 34));

        retranslateUi(SelectByBindedLimitedDialog);

        QMetaObject::connectSlotsByName(SelectByBindedLimitedDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectByBindedLimitedDialog)
    {
        SelectByBindedLimitedDialog->setWindowTitle(QCoreApplication::translate("SelectByBindedLimitedDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetBinded->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectByBindedLimitedDialog", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetBinded->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectByBindedLimitedDialog", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetBinded->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectByBindedLimitedDialog", "Count", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetBinded->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectByBindedLimitedDialog", "Limit", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SelectByBindedLimitedDialog", "Algorithm", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SelectByBindedLimitedDialog", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetLibList->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("SelectByBindedLimitedDialog", "Name", nullptr));
        toolButtonPage->setText(QCoreApplication::translate("SelectByBindedLimitedDialog", "Page", nullptr));
        toolButtonLayer->setText(QCoreApplication::translate("SelectByBindedLimitedDialog", "Layer", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectByBindedLimitedDialog", "Select", nullptr));
        pushButtonEdit->setText(QCoreApplication::translate("SelectByBindedLimitedDialog", "Edit", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SelectByBindedLimitedDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectByBindedLimitedDialog: public Ui_SelectByBindedLimitedDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTBYBINDEDLIMITEDDIALOG_H
