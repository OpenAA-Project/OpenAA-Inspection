/********************************************************************************
** Form generated from reading UI file 'ListMaster.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTMASTER_H
#define UI_LISTMASTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ListMasterFormClass
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tbDataTable;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonOpneInDetail;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbSelect;

    void setupUi(GUIFormBase *ListMasterFormClass)
    {
        if (ListMasterFormClass->objectName().isEmpty())
            ListMasterFormClass->setObjectName(QString::fromUtf8("ListMasterFormClass"));
        ListMasterFormClass->resize(337, 334);
        gridLayout = new QGridLayout(ListMasterFormClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tbDataTable = new QTableWidget(ListMasterFormClass);
        if (tbDataTable->columnCount() < 3)
            tbDataTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbDataTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbDataTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tbDataTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tbDataTable->setObjectName(QString::fromUtf8("tbDataTable"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tbDataTable->sizePolicy().hasHeightForWidth());
        tbDataTable->setSizePolicy(sizePolicy);
        tbDataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbDataTable->setProperty("showDropIndicator", QVariant(false));
        tbDataTable->setDragDropOverwriteMode(false);
        tbDataTable->setDragDropMode(QAbstractItemView::DropOnly);
        tbDataTable->setAlternatingRowColors(true);
        tbDataTable->setSelectionMode(QAbstractItemView::SingleSelection);
        tbDataTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbDataTable->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        tbDataTable->setSortingEnabled(true);
        tbDataTable->horizontalHeader()->setVisible(true);
        tbDataTable->horizontalHeader()->setStretchLastSection(true);
        tbDataTable->verticalHeader()->setCascadingSectionResizes(false);
        tbDataTable->verticalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(tbDataTable, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonOpneInDetail = new QPushButton(ListMasterFormClass);
        pushButtonOpneInDetail->setObjectName(QString::fromUtf8("pushButtonOpneInDetail"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonOpneInDetail->sizePolicy().hasHeightForWidth());
        pushButtonOpneInDetail->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(pushButtonOpneInDetail);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbSelect = new QPushButton(ListMasterFormClass);
        pbSelect->setObjectName(QString::fromUtf8("pbSelect"));

        horizontalLayout->addWidget(pbSelect);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);


        retranslateUi(ListMasterFormClass);

        QMetaObject::connectSlotsByName(ListMasterFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ListMasterFormClass)
    {
        ListMasterFormClass->setWindowTitle(QCoreApplication::translate("ListMasterFormClass", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tbDataTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ListMasterFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tbDataTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ListMasterFormClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tbDataTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ListMasterFormClass", "LastestEdition", nullptr));
        pushButtonOpneInDetail->setText(QCoreApplication::translate("ListMasterFormClass", "Detail Select", nullptr));
        pbSelect->setText(QCoreApplication::translate("ListMasterFormClass", "Select", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListMasterFormClass: public Ui_ListMasterFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTMASTER_H
