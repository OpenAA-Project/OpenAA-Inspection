/********************************************************************************
** Form generated from reading UI file 'ListPieceForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTPIECEFORM_H
#define UI_LISTPIECEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ListPieceForm
{
public:
    QTableWidget *tableWidgetPiece;

    void setupUi(GUIFormBase *ListPieceForm)
    {
        if (ListPieceForm->objectName().isEmpty())
            ListPieceForm->setObjectName(QString::fromUtf8("ListPieceForm"));
        ListPieceForm->resize(283, 548);
        tableWidgetPiece = new QTableWidget(ListPieceForm);
        if (tableWidgetPiece->columnCount() < 4)
            tableWidgetPiece->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetPiece->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetPiece->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetPiece->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetPiece->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetPiece->setObjectName(QString::fromUtf8("tableWidgetPiece"));
        tableWidgetPiece->setGeometry(QRect(0, 0, 281, 541));
        tableWidgetPiece->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetPiece->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(ListPieceForm);

        QMetaObject::connectSlotsByName(ListPieceForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ListPieceForm)
    {
        ListPieceForm->setWindowTitle(QCoreApplication::translate("ListPieceForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetPiece->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ListPieceForm", "F/B", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetPiece->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ListPieceForm", "Col", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetPiece->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ListPieceForm", "Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetPiece->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ListPieceForm", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListPieceForm: public Ui_ListPieceForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTPIECEFORM_H
