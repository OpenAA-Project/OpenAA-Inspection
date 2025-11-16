/********************************************************************************
** Form generated from reading UI file 'SelectOneItemForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTONEITEMFORM_H
#define UI_SELECTONEITEMFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectOneItemForm
{
public:
    QTableWidget *tableWidgetItem;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *SelectOneItemForm)
    {
        if (SelectOneItemForm->objectName().isEmpty())
            SelectOneItemForm->setObjectName("SelectOneItemForm");
        SelectOneItemForm->resize(670, 226);
        tableWidgetItem = new QTableWidget(SelectOneItemForm);
        if (tableWidgetItem->columnCount() < 5)
            tableWidgetItem->setColumnCount(5);
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
        tableWidgetItem->setObjectName("tableWidgetItem");
        tableWidgetItem->setGeometry(QRect(10, 10, 651, 171));
        tableWidgetItem->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetItem->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonOK = new QPushButton(SelectOneItemForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(290, 190, 81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);

        retranslateUi(SelectOneItemForm);

        QMetaObject::connectSlotsByName(SelectOneItemForm);
    } // setupUi

    void retranslateUi(QDialog *SelectOneItemForm)
    {
        SelectOneItemForm->setWindowTitle(QCoreApplication::translate("SelectOneItemForm", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetItem->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectOneItemForm", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetItem->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectOneItemForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetItem->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectOneItemForm", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetItem->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectOneItemForm", "Library", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetItem->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SelectOneItemForm", "Name", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectOneItemForm", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectOneItemForm: public Ui_SelectOneItemForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTONEITEMFORM_H
