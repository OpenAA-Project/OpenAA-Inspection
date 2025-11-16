/********************************************************************************
** Form generated from reading UI file 'AllocateMenuDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALLOCATEMENUDIALOG_H
#define UI_ALLOCATEMENUDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_AllocateMenuDialog
{
public:
    QTableWidget *tableWidget;
    QFrame *frame;
    QPushButton *pushButtonAddLine;
    QPushButton *pushButtonDelLine;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *AllocateMenuDialog)
    {
        if (AllocateMenuDialog->objectName().isEmpty())
            AllocateMenuDialog->setObjectName("AllocateMenuDialog");
        AllocateMenuDialog->resize(500, 300);
        tableWidget = new QTableWidget(AllocateMenuDialog);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 501, 251));
        frame = new QFrame(AllocateMenuDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 250, 501, 51));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonAddLine = new QPushButton(frame);
        pushButtonAddLine->setObjectName("pushButtonAddLine");
        pushButtonAddLine->setGeometry(QRect(10, 10, 51, 34));
        pushButtonDelLine = new QPushButton(frame);
        pushButtonDelLine->setObjectName("pushButtonDelLine");
        pushButtonDelLine->setGeometry(QRect(70, 10, 51, 34));
        pushButtonOK = new QPushButton(frame);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(210, 10, 112, 34));
        pushButtonCancel = new QPushButton(frame);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(380, 10, 112, 34));

        retranslateUi(AllocateMenuDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(AllocateMenuDialog);
    } // setupUi

    void retranslateUi(QDialog *AllocateMenuDialog)
    {
        AllocateMenuDialog->setWindowTitle(QCoreApplication::translate("AllocateMenuDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AllocateMenuDialog", "Button message", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AllocateMenuDialog", "Instance name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("AllocateMenuDialog", "Page name", nullptr));
        pushButtonAddLine->setText(QCoreApplication::translate("AllocateMenuDialog", "+", nullptr));
        pushButtonDelLine->setText(QCoreApplication::translate("AllocateMenuDialog", "-", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AllocateMenuDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AllocateMenuDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AllocateMenuDialog: public Ui_AllocateMenuDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALLOCATEMENUDIALOG_H
