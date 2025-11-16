/********************************************************************************
** Form generated from reading UI file 'SelectPageItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTPAGEITEMDIALOG_H
#define UI_SELECTPAGEITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectPageItemDialog
{
public:
    QPushButton *ButtonOK;
    QTableWidget *tableWidgetItem;

    void setupUi(QDialog *SelectPageItemDialog)
    {
        if (SelectPageItemDialog->objectName().isEmpty())
            SelectPageItemDialog->setObjectName("SelectPageItemDialog");
        SelectPageItemDialog->resize(758, 241);
        ButtonOK = new QPushButton(SelectPageItemDialog);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(330, 190, 81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        tableWidgetItem = new QTableWidget(SelectPageItemDialog);
        if (tableWidgetItem->columnCount() < 6)
            tableWidgetItem->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetItem->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetItem->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetItem->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetItem->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetItem->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetItem->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidgetItem->setObjectName("tableWidgetItem");
        tableWidgetItem->setGeometry(QRect(10, 10, 731, 171));
        tableWidgetItem->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetItem->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(SelectPageItemDialog);

        QMetaObject::connectSlotsByName(SelectPageItemDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectPageItemDialog)
    {
        SelectPageItemDialog->setWindowTitle(QCoreApplication::translate("SelectPageItemDialog", "Select items", nullptr));
        ButtonOK->setText(QCoreApplication::translate("SelectPageItemDialog", "OK", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetItem->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectPageItemDialog", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetItem->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectPageItemDialog", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetItem->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectPageItemDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetItem->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectPageItemDialog", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetItem->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SelectPageItemDialog", "Library", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetItem->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SelectPageItemDialog", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectPageItemDialog: public Ui_SelectPageItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTPAGEITEMDIALOG_H
