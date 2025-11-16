/********************************************************************************
** Form generated from reading UI file 'ShowResultMultiDeliveryForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWRESULTMULTIDELIVERYFORM_H
#define UI_SHOWRESULTMULTIDELIVERYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowResultMultiDeliveryForm
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonSet;

    void setupUi(GUIFormBase *ShowResultMultiDeliveryForm)
    {
        if (ShowResultMultiDeliveryForm->objectName().isEmpty())
            ShowResultMultiDeliveryForm->setObjectName("ShowResultMultiDeliveryForm");
        ShowResultMultiDeliveryForm->resize(556, 229);
        tableWidget = new QTableWidget(ShowResultMultiDeliveryForm);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 4)
            tableWidget->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem6);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 551, 181));
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pushButtonSet = new QPushButton(ShowResultMultiDeliveryForm);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(200, 190, 151, 28));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSet->setIcon(icon);

        retranslateUi(ShowResultMultiDeliveryForm);

        QMetaObject::connectSlotsByName(ShowResultMultiDeliveryForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowResultMultiDeliveryForm)
    {
        ShowResultMultiDeliveryForm->setWindowTitle(QCoreApplication::translate("ShowResultMultiDeliveryForm", "Show Result MultiDelivery", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowResultMultiDeliveryForm", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowResultMultiDeliveryForm", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowResultMultiDeliveryForm", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowResultMultiDeliveryForm", "Sub Lot number", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ShowResultMultiDeliveryForm", "Lot ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ShowResultMultiDeliveryForm", "Lot Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ShowResultMultiDeliveryForm", "Stack count", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("ShowResultMultiDeliveryForm", "Set", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowResultMultiDeliveryForm: public Ui_ShowResultMultiDeliveryForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWRESULTMULTIDELIVERYFORM_H
