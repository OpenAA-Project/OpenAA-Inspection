/********************************************************************************
** Form generated from reading UI file 'SelectItemIndependent.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTITEMINDEPENDENT_H
#define UI_SELECTITEMINDEPENDENT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectItemIndependentClass
{
public:
    QLabel *label;
    QPushButton *pushButtonOK;
    QTableWidget *tableWidgetItems;
    QLabel *label_3;
    QTableWidget *tableWidgetAlgorithm;
    QLabel *label_2;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectItemIndependentClass)
    {
        if (SelectItemIndependentClass->objectName().isEmpty())
            SelectItemIndependentClass->setObjectName("SelectItemIndependentClass");
        SelectItemIndependentClass->resize(639, 286);
        label = new QLabel(SelectItemIndependentClass);
        label->setObjectName("label");
        label->setGeometry(QRect(180, 220, 181, 16));
        pushButtonOK = new QPushButton(SelectItemIndependentClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(60, 240, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        tableWidgetItems = new QTableWidget(SelectItemIndependentClass);
        if (tableWidgetItems->columnCount() < 5)
            tableWidgetItems->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetItems->setObjectName("tableWidgetItems");
        tableWidgetItems->setGeometry(QRect(190, 30, 441, 181));
        tableWidgetItems->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetItems->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_3 = new QLabel(SelectItemIndependentClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(190, 10, 441, 16));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetAlgorithm = new QTableWidget(SelectItemIndependentClass);
        if (tableWidgetAlgorithm->columnCount() < 2)
            tableWidgetAlgorithm->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        tableWidgetAlgorithm->setObjectName("tableWidgetAlgorithm");
        tableWidgetAlgorithm->setGeometry(QRect(10, 30, 171, 181));
        tableWidgetAlgorithm->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAlgorithm->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_2 = new QLabel(SelectItemIndependentClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 171, 16));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonCancel = new QPushButton(SelectItemIndependentClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(480, 240, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(SelectItemIndependentClass);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SelectItemIndependentClass);
    } // setupUi

    void retranslateUi(QDialog *SelectItemIndependentClass)
    {
        SelectItemIndependentClass->setWindowTitle(QCoreApplication::translate("SelectItemIndependentClass", "Select Items", nullptr));
        label->setText(QCoreApplication::translate("SelectItemIndependentClass", "\343\203\254\343\202\244\343\203\244\343\203\274\343\201\253\343\201\257\357\274\221\350\246\201\347\264\240\343\201\240\343\201\221\343\202\222\351\201\270\346\212\236", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectItemIndependentClass", "OK", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetItems->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectItemIndependentClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetItems->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectItemIndependentClass", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetItems->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectItemIndependentClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetItems->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectItemIndependentClass", "Library", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetItems->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SelectItemIndependentClass", "RA", nullptr));
        label_3->setText(QCoreApplication::translate("SelectItemIndependentClass", "Items", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetAlgorithm->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SelectItemIndependentClass", "Root", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetAlgorithm->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("SelectItemIndependentClass", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("SelectItemIndependentClass", "Algorithm", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectItemIndependentClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectItemIndependentClass: public Ui_SelectItemIndependentClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTITEMINDEPENDENT_H
