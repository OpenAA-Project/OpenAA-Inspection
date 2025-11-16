/********************************************************************************
** Form generated from reading UI file 'ShowThinMetalResultListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWTHINMETALRESULTLISTFORM_H
#define UI_SHOWTHINMETALRESULTLISTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowThinMetalResultListForm
{
public:
    QTableWidget *tableWidget;

    void setupUi(GUIFormBase *ShowThinMetalResultListForm)
    {
        if (ShowThinMetalResultListForm->objectName().isEmpty())
            ShowThinMetalResultListForm->setObjectName("ShowThinMetalResultListForm");
        ShowThinMetalResultListForm->resize(291, 391);
        tableWidget = new QTableWidget(ShowThinMetalResultListForm);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 291, 391));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(ShowThinMetalResultListForm);

        QMetaObject::connectSlotsByName(ShowThinMetalResultListForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowThinMetalResultListForm)
    {
        ShowThinMetalResultListForm->setWindowTitle(QCoreApplication::translate("ShowThinMetalResultListForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowThinMetalResultListForm", "File name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowThinMetalResultListForm", "Matching", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowThinMetalResultListForm: public Ui_ShowThinMetalResultListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWTHINMETALRESULTLISTFORM_H
