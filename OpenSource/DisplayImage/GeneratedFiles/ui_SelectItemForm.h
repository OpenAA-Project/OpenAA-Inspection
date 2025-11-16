/********************************************************************************
** Form generated from reading UI file 'SelectItemForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTITEMFORM_H
#define UI_SELECTITEMFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectItemForm
{
public:
    QTableWidget *tableWidgetItem;
    QPushButton *ButtonOK;

    void setupUi(QDialog *SelectItemForm)
    {
        if (SelectItemForm->objectName().isEmpty())
            SelectItemForm->setObjectName("SelectItemForm");
        SelectItemForm->resize(671, 232);
        tableWidgetItem = new QTableWidget(SelectItemForm);
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
        tableWidgetItem->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetItem->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonOK = new QPushButton(SelectItemForm);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(300, 190, 81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);

        retranslateUi(SelectItemForm);

        QMetaObject::connectSlotsByName(SelectItemForm);
    } // setupUi

    void retranslateUi(QDialog *SelectItemForm)
    {
        SelectItemForm->setWindowTitle(QCoreApplication::translate("SelectItemForm", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetItem->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectItemForm", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetItem->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectItemForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetItem->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectItemForm", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetItem->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectItemForm", "Library", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetItem->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SelectItemForm", "Name", nullptr));
        ButtonOK->setText(QCoreApplication::translate("SelectItemForm", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectItemForm: public Ui_SelectItemForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTITEMFORM_H
