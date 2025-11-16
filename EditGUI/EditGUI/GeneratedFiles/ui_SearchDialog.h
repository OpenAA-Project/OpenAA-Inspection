/********************************************************************************
** Form generated from reading UI file 'SearchDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHDIALOG_H
#define UI_SEARCHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchDialog
{
public:
    QLabel *label;
    QLineEdit *lineEditSearcgStr;
    QPushButton *pushButtonSearcg;
    QListWidget *listWidgetRootList;
    QLabel *label_2;
    QTableWidget *tableWidgetComponents;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *SearchDialog)
    {
        if (SearchDialog->objectName().isEmpty())
            SearchDialog->setObjectName("SearchDialog");
        SearchDialog->resize(1032, 585);
        label = new QLabel(SearchDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(300, 10, 291, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        lineEditSearcgStr = new QLineEdit(SearchDialog);
        lineEditSearcgStr->setObjectName("lineEditSearcgStr");
        lineEditSearcgStr->setGeometry(QRect(300, 30, 291, 21));
        pushButtonSearcg = new QPushButton(SearchDialog);
        pushButtonSearcg->setObjectName("pushButtonSearcg");
        pushButtonSearcg->setGeometry(QRect(600, 10, 93, 41));
        listWidgetRootList = new QListWidget(SearchDialog);
        listWidgetRootList->setObjectName("listWidgetRootList");
        listWidgetRootList->setGeometry(QRect(10, 40, 256, 451));
        label_2 = new QLabel(SearchDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 251, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        tableWidgetComponents = new QTableWidget(SearchDialog);
        if (tableWidgetComponents->columnCount() < 4)
            tableWidgetComponents->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetComponents->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetComponents->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetComponents->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetComponents->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetComponents->setObjectName("tableWidgetComponents");
        tableWidgetComponents->setGeometry(QRect(300, 60, 721, 431));
        tableWidgetComponents->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetComponents->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelect = new QPushButton(SearchDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(480, 500, 93, 28));
        pushButtonClose = new QPushButton(SearchDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(320, 537, 101, 31));

        retranslateUi(SearchDialog);

        QMetaObject::connectSlotsByName(SearchDialog);
    } // setupUi

    void retranslateUi(QDialog *SearchDialog)
    {
        SearchDialog->setWindowTitle(QCoreApplication::translate("SearchDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SearchDialog", "Ambiguous", nullptr));
        pushButtonSearcg->setText(QCoreApplication::translate("SearchDialog", "Search", nullptr));
        label_2->setText(QCoreApplication::translate("SearchDialog", "Root list", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetComponents->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SearchDialog", "Icon", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetComponents->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SearchDialog", "Root", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetComponents->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SearchDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetComponents->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SearchDialog", "Explain", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SearchDialog", "Select", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SearchDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchDialog: public Ui_SearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHDIALOG_H
