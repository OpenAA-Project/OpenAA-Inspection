/********************************************************************************
** Form generated from reading UI file 'ListboxUncoveredAreaForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTBOXUNCOVEREDAREAFORM_H
#define UI_LISTBOXUNCOVEREDAREAFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ListboxUncoveredAreaFormClass
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonUpdate;

    void setupUi(GUIFormBase *ListboxUncoveredAreaFormClass)
    {
        if (ListboxUncoveredAreaFormClass->objectName().isEmpty())
            ListboxUncoveredAreaFormClass->setObjectName("ListboxUncoveredAreaFormClass");
        ListboxUncoveredAreaFormClass->resize(221, 355);
        tableWidget = new QTableWidget(ListboxUncoveredAreaFormClass);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 221, 311));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonUpdate = new QPushButton(ListboxUncoveredAreaFormClass);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(0, 310, 221, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon);

        retranslateUi(ListboxUncoveredAreaFormClass);

        QMetaObject::connectSlotsByName(ListboxUncoveredAreaFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ListboxUncoveredAreaFormClass)
    {
        ListboxUncoveredAreaFormClass->setWindowTitle(QCoreApplication::translate("ListboxUncoveredAreaFormClass", "ListboxUncoveredAreaForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ListboxUncoveredAreaFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ListboxUncoveredAreaFormClass", "Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ListboxUncoveredAreaFormClass", "Dots", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("ListboxUncoveredAreaFormClass", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListboxUncoveredAreaFormClass: public Ui_ListboxUncoveredAreaFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTBOXUNCOVEREDAREAFORM_H
