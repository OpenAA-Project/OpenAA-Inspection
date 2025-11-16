/********************************************************************************
** Form generated from reading UI file 'CheckEverydayResultHistoryForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKEVERYDAYRESULTHISTORYFORM_H
#define UI_CHECKEVERYDAYRESULTHISTORYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_CheckEverydayResultHistoryForm
{
public:
    QTableWidget *tableWidgetItemList;
    QTableWidget *tableWidgetHistoryList;
    QPushButton *pushButtonSaveButton;

    void setupUi(GUIFormBase *CheckEverydayResultHistoryForm)
    {
        if (CheckEverydayResultHistoryForm->objectName().isEmpty())
            CheckEverydayResultHistoryForm->setObjectName("CheckEverydayResultHistoryForm");
        CheckEverydayResultHistoryForm->resize(696, 250);
        tableWidgetItemList = new QTableWidget(CheckEverydayResultHistoryForm);
        if (tableWidgetItemList->columnCount() < 4)
            tableWidgetItemList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetItemList->setObjectName("tableWidgetItemList");
        tableWidgetItemList->setGeometry(QRect(10, 10, 321, 192));
        tableWidgetItemList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetItemList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetHistoryList = new QTableWidget(CheckEverydayResultHistoryForm);
        if (tableWidgetHistoryList->columnCount() < 2)
            tableWidgetHistoryList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetHistoryList->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetHistoryList->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        tableWidgetHistoryList->setObjectName("tableWidgetHistoryList");
        tableWidgetHistoryList->setGeometry(QRect(350, 10, 331, 192));
        tableWidgetHistoryList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetHistoryList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSaveButton = new QPushButton(CheckEverydayResultHistoryForm);
        pushButtonSaveButton->setObjectName("pushButtonSaveButton");
        pushButtonSaveButton->setGeometry(QRect(350, 210, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSaveButton->setIcon(icon);

        retranslateUi(CheckEverydayResultHistoryForm);

        QMetaObject::connectSlotsByName(CheckEverydayResultHistoryForm);
    } // setupUi

    void retranslateUi(GUIFormBase *CheckEverydayResultHistoryForm)
    {
        CheckEverydayResultHistoryForm->setWindowTitle(QCoreApplication::translate("CheckEverydayResultHistoryForm", "Check Everyday for ResultHistory", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetItemList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CheckEverydayResultHistoryForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetItemList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CheckEverydayResultHistoryForm", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetItemList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CheckEverydayResultHistoryForm", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetItemList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("CheckEverydayResultHistoryForm", "ID/Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetHistoryList->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("CheckEverydayResultHistoryForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetHistoryList->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("CheckEverydayResultHistoryForm", "Result", nullptr));
        pushButtonSaveButton->setText(QCoreApplication::translate("CheckEverydayResultHistoryForm", "Save result", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CheckEverydayResultHistoryForm: public Ui_CheckEverydayResultHistoryForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKEVERYDAYRESULTHISTORYFORM_H
