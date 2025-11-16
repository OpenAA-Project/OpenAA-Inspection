/********************************************************************************
** Form generated from reading UI file 'ShowMarkListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWMARKLISTFORM_H
#define UI_SHOWMARKLISTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowMarkListForm
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonClose;

    void setupUi(QWidget *ShowMarkListForm)
    {
        if (ShowMarkListForm->objectName().isEmpty())
            ShowMarkListForm->setObjectName("ShowMarkListForm");
        ShowMarkListForm->resize(279, 453);
        tableWidget = new QTableWidget(ShowMarkListForm);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 281, 421));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonClose = new QPushButton(ShowMarkListForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(80, 420, 112, 34));

        retranslateUi(ShowMarkListForm);

        QMetaObject::connectSlotsByName(ShowMarkListForm);
    } // setupUi

    void retranslateUi(QWidget *ShowMarkListForm)
    {
        ShowMarkListForm->setWindowTitle(QCoreApplication::translate("ShowMarkListForm", "Show mark list", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowMarkListForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowMarkListForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowMarkListForm", "Position", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ShowMarkListForm", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowMarkListForm: public Ui_ShowMarkListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWMARKLISTFORM_H
