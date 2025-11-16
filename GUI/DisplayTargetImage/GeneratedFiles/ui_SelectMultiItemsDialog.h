/********************************************************************************
** Form generated from reading UI file 'SelectMultiItemsDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTMULTIITEMSDIALOG_H
#define UI_SELECTMULTIITEMSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectMultiItemsDialog
{
public:
    QFrame *frame;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonCancel;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTableWidget *tableWidget;
    QWidget *tab_2;
    QTableWidget *tableWidgetBinded;

    void setupUi(QDialog *SelectMultiItemsDialog)
    {
        if (SelectMultiItemsDialog->objectName().isEmpty())
            SelectMultiItemsDialog->setObjectName("SelectMultiItemsDialog");
        SelectMultiItemsDialog->resize(699, 370);
        frame = new QFrame(SelectMultiItemsDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 320, 691, 51));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonSelect = new QPushButton(frame);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(150, 10, 112, 34));
        pushButtonCancel = new QPushButton(frame);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(400, 10, 112, 34));
        tabWidget = new QTabWidget(SelectMultiItemsDialog);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 701, 321));
        tab = new QWidget();
        tab->setObjectName("tab");
        tableWidget = new QTableWidget(tab);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 691, 291));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tableWidgetBinded = new QTableWidget(tab_2);
        if (tableWidgetBinded->columnCount() < 5)
            tableWidgetBinded->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetBinded->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetBinded->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetBinded->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetBinded->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetBinded->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        tableWidgetBinded->setObjectName("tableWidgetBinded");
        tableWidgetBinded->setGeometry(QRect(0, 0, 691, 291));
        tableWidgetBinded->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetBinded->setSelectionBehavior(QAbstractItemView::SelectRows);
        tabWidget->addTab(tab_2, QString());

        retranslateUi(SelectMultiItemsDialog);

        pushButtonSelect->setDefault(true);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SelectMultiItemsDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectMultiItemsDialog)
    {
        SelectMultiItemsDialog->setWindowTitle(QCoreApplication::translate("SelectMultiItemsDialog", "Dialog", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectMultiItemsDialog", "Select", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectMultiItemsDialog", "Cancel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectMultiItemsDialog", "Phase", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectMultiItemsDialog", "Algorithm", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectMultiItemsDialog", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectMultiItemsDialog", "Library", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SelectMultiItemsDialog", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SelectMultiItemsDialog", "Count", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SelectMultiItemsDialog", "Phase\345\210\245", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetBinded->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("SelectMultiItemsDialog", "Algorithm", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetBinded->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("SelectMultiItemsDialog", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetBinded->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("SelectMultiItemsDialog", "Library", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetBinded->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("SelectMultiItemsDialog", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetBinded->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("SelectMultiItemsDialog", "Count", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("SelectMultiItemsDialog", "Phase\345\220\210\344\270\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectMultiItemsDialog: public Ui_SelectMultiItemsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTMULTIITEMSDIALOG_H
