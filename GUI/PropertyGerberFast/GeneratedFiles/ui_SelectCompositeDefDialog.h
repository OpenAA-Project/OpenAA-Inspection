/********************************************************************************
** Form generated from reading UI file 'SelectCompositeDefDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTCOMPOSITEDEFDIALOG_H
#define UI_SELECTCOMPOSITEDEFDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectCompositeDefDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonCancel;
    QFrame *frameLibFolder;

    void setupUi(QDialog *SelectCompositeDefDialog)
    {
        if (SelectCompositeDefDialog->objectName().isEmpty())
            SelectCompositeDefDialog->setObjectName("SelectCompositeDefDialog");
        SelectCompositeDefDialog->resize(421, 650);
        tableWidget = new QTableWidget(SelectCompositeDefDialog);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 290, 401, 301));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelect = new QPushButton(SelectCompositeDefDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(60, 600, 112, 34));
        pushButtonCancel = new QPushButton(SelectCompositeDefDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(250, 600, 112, 34));
        frameLibFolder = new QFrame(SelectCompositeDefDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 401, 271));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);

        retranslateUi(SelectCompositeDefDialog);

        QMetaObject::connectSlotsByName(SelectCompositeDefDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectCompositeDefDialog)
    {
        SelectCompositeDefDialog->setWindowTitle(QCoreApplication::translate("SelectCompositeDefDialog", "Select composite definition", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectCompositeDefDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectCompositeDefDialog", "Composite name", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectCompositeDefDialog", "Select", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectCompositeDefDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectCompositeDefDialog: public Ui_SelectCompositeDefDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTCOMPOSITEDEFDIALOG_H
