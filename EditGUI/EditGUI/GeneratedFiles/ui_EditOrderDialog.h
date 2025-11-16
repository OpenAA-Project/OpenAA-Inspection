/********************************************************************************
** Form generated from reading UI file 'EditOrderDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORDERDIALOG_H
#define UI_EDITORDERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditOrderDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonUp;
    QPushButton *pushButtonDown;
    QFrame *frame;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *EditOrderDialog)
    {
        if (EditOrderDialog->objectName().isEmpty())
            EditOrderDialog->setObjectName("EditOrderDialog");
        EditOrderDialog->resize(710, 408);
        tableWidget = new QTableWidget(EditOrderDialog);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 621, 361));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonUp = new QPushButton(EditOrderDialog);
        pushButtonUp->setObjectName("pushButtonUp");
        pushButtonUp->setGeometry(QRect(630, 120, 71, 51));
        pushButtonDown = new QPushButton(EditOrderDialog);
        pushButtonDown->setObjectName("pushButtonDown");
        pushButtonDown->setGeometry(QRect(630, 190, 71, 51));
        frame = new QFrame(EditOrderDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 360, 711, 51));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonOK = new QPushButton(frame);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(300, 10, 101, 31));

        retranslateUi(EditOrderDialog);

        QMetaObject::connectSlotsByName(EditOrderDialog);
    } // setupUi

    void retranslateUi(QDialog *EditOrderDialog)
    {
        EditOrderDialog->setWindowTitle(QCoreApplication::translate("EditOrderDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditOrderDialog", "DLLRoot", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditOrderDialog", "DLLName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EditOrderDialog", "InstName", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("EditOrderDialog", "Order", nullptr));
        pushButtonUp->setText(QCoreApplication::translate("EditOrderDialog", "Up", nullptr));
        pushButtonDown->setText(QCoreApplication::translate("EditOrderDialog", "Down", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditOrderDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditOrderDialog: public Ui_EditOrderDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORDERDIALOG_H
