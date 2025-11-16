/********************************************************************************
** Form generated from reading UI file 'PieceListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIECELISTFORM_H
#define UI_PIECELISTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_PieceListForm
{
public:
    QTableWidget *tableWidget;

    void setupUi(GUIFormBase *PieceListForm)
    {
        if (PieceListForm->objectName().isEmpty())
            PieceListForm->setObjectName("PieceListForm");
        PieceListForm->resize(281, 210);
        tableWidget = new QTableWidget(PieceListForm);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 261, 191));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(PieceListForm);

        QMetaObject::connectSlotsByName(PieceListForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PieceListForm)
    {
        PieceListForm->setWindowTitle(QCoreApplication::translate("PieceListForm", "Piece List", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PieceListForm", "Number", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PieceListForm", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PieceListForm: public Ui_PieceListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIECELISTFORM_H
