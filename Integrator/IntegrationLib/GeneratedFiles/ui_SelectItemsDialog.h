/********************************************************************************
** Form generated from reading UI file 'SelectItemsDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTITEMSDIALOG_H
#define UI_SELECTITEMSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectItemsDialog
{
public:
    QFrame *frame;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonBind;
    QPushButton *pushButtonSelectAll;
    QPushButton *pushButtonCancel;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QTableWidget *tableWidget;
    QWidget *page_2;
    QTableWidget *tableWidgetBinded;

    void setupUi(QDialog *SelectItemsDialog)
    {
        if (SelectItemsDialog->objectName().isEmpty())
            SelectItemsDialog->setObjectName("SelectItemsDialog");
        SelectItemsDialog->resize(850, 271);
        frame = new QFrame(SelectItemsDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 220, 851, 51));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonSelect = new QPushButton(frame);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(580, 10, 112, 34));
        pushButtonBind = new QPushButton(frame);
        pushButtonBind->setObjectName("pushButtonBind");
        pushButtonBind->setGeometry(QRect(10, 10, 112, 34));
        pushButtonBind->setCheckable(true);
        pushButtonBind->setChecked(true);
        pushButtonSelectAll = new QPushButton(frame);
        pushButtonSelectAll->setObjectName("pushButtonSelectAll");
        pushButtonSelectAll->setGeometry(QRect(170, 10, 112, 34));
        pushButtonCancel = new QPushButton(frame);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(710, 10, 112, 34));
        stackedWidget = new QStackedWidget(SelectItemsDialog);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 851, 221));
        page = new QWidget();
        page->setObjectName("page");
        tableWidget = new QTableWidget(page);
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
        tableWidget->setGeometry(QRect(0, 0, 851, 221));
        tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        tableWidgetBinded = new QTableWidget(page_2);
        if (tableWidgetBinded->columnCount() < 2)
            tableWidgetBinded->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetBinded->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetBinded->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        tableWidgetBinded->setObjectName("tableWidgetBinded");
        tableWidgetBinded->setGeometry(QRect(0, 0, 851, 221));
        tableWidgetBinded->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetBinded->setSelectionBehavior(QAbstractItemView::SelectRows);
        stackedWidget->addWidget(page_2);

        retranslateUi(SelectItemsDialog);

        pushButtonSelect->setDefault(true);
        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SelectItemsDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectItemsDialog)
    {
        SelectItemsDialog->setWindowTitle(QCoreApplication::translate("SelectItemsDialog", "Select items", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectItemsDialog", "\351\201\270\346\212\236\346\261\272\345\256\232", nullptr));
        pushButtonBind->setText(QCoreApplication::translate("SelectItemsDialog", "\343\201\276\343\201\250\343\202\201\343\202\213", nullptr));
        pushButtonSelectAll->setText(QCoreApplication::translate("SelectItemsDialog", "\345\205\250\351\201\270\346\212\236", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectItemsDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectItemsDialog", "Phase", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectItemsDialog", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectItemsDialog", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectItemsDialog", "ItemID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SelectItemsDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SelectItemsDialog", "Comment", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetBinded->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("SelectItemsDialog", "Comment", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetBinded->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("SelectItemsDialog", "Count", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectItemsDialog: public Ui_SelectItemsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTITEMSDIALOG_H
