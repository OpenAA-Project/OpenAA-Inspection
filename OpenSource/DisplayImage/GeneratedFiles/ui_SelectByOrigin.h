/********************************************************************************
** Form generated from reading UI file 'SelectByOrigin.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTBYORIGIN_H
#define UI_SELECTBYORIGIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectByOrigin
{
public:
    QPushButton *pushButtonSelect;
    QTableWidget *tableWidget;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectByOrigin)
    {
        if (SelectByOrigin->objectName().isEmpty())
            SelectByOrigin->setObjectName("SelectByOrigin");
        SelectByOrigin->resize(338, 251);
        pushButtonSelect = new QPushButton(SelectByOrigin);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(20, 210, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSelect->setIcon(icon);
        tableWidget = new QTableWidget(SelectByOrigin);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 321, 192));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonCancel = new QPushButton(SelectByOrigin);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(230, 210, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(SelectByOrigin);

        QMetaObject::connectSlotsByName(SelectByOrigin);
    } // setupUi

    void retranslateUi(QDialog *SelectByOrigin)
    {
        SelectByOrigin->setWindowTitle(QCoreApplication::translate("SelectByOrigin", "Dialog", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectByOrigin", "Select", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectByOrigin", "Root", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectByOrigin", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectByOrigin", "Num", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectByOrigin", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectByOrigin: public Ui_SelectByOrigin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTBYORIGIN_H
