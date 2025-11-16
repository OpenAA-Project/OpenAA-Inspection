/********************************************************************************
** Form generated from reading UI file 'TreeMasterShowResultForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TREEMASTERSHOWRESULTFORM_H
#define UI_TREEMASTERSHOWRESULTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_TreeMasterShowResultForm
{
public:
    QTableWidget *tableWidget;

    void setupUi(GUIFormBase *TreeMasterShowResultForm)
    {
        if (TreeMasterShowResultForm->objectName().isEmpty())
            TreeMasterShowResultForm->setObjectName("TreeMasterShowResultForm");
        TreeMasterShowResultForm->resize(414, 473);
        tableWidget = new QTableWidget(TreeMasterShowResultForm);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 411, 471));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(TreeMasterShowResultForm);

        QMetaObject::connectSlotsByName(TreeMasterShowResultForm);
    } // setupUi

    void retranslateUi(GUIFormBase *TreeMasterShowResultForm)
    {
        TreeMasterShowResultForm->setWindowTitle(QCoreApplication::translate("TreeMasterShowResultForm", "TreeMaster show Result", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TreeMasterShowResultForm", "CatID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TreeMasterShowResultForm", "CatName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("TreeMasterShowResultForm", "MasterID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("TreeMasterShowResultForm", "MatchColor", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("TreeMasterShowResultForm", "MatchShape", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TreeMasterShowResultForm: public Ui_TreeMasterShowResultForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TREEMASTERSHOWRESULTFORM_H
