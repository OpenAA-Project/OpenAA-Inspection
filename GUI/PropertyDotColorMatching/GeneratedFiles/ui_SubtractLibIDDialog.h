/********************************************************************************
** Form generated from reading UI file 'SubtractLibIDDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBTRACTLIBIDDIALOG_H
#define UI_SUBTRACTLIBIDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SubtractLibIDDialog
{
public:
    QFrame *frameLibFolder;
    QTableWidget *tableWidgetLibList;
    QTableWidget *tableWidgetSelectedList;
    QPushButton *pushButtonSend;
    QPushButton *pushButtonBack;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label;

    void setupUi(QDialog *SubtractLibIDDialog)
    {
        if (SubtractLibIDDialog->objectName().isEmpty())
            SubtractLibIDDialog->setObjectName("SubtractLibIDDialog");
        SubtractLibIDDialog->resize(705, 454);
        frameLibFolder = new QFrame(SubtractLibIDDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 311, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        tableWidgetLibList = new QTableWidget(SubtractLibIDDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 160, 311, 241));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetSelectedList = new QTableWidget(SubtractLibIDDialog);
        if (tableWidgetSelectedList->columnCount() < 2)
            tableWidgetSelectedList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetSelectedList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetSelectedList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetSelectedList->setObjectName("tableWidgetSelectedList");
        tableWidgetSelectedList->setGeometry(QRect(390, 160, 311, 241));
        tableWidgetSelectedList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSend = new QPushButton(SubtractLibIDDialog);
        pushButtonSend->setObjectName("pushButtonSend");
        pushButtonSend->setGeometry(QRect(330, 180, 51, 41));
        pushButtonBack = new QPushButton(SubtractLibIDDialog);
        pushButtonBack->setObjectName("pushButtonBack");
        pushButtonBack->setGeometry(QRect(330, 280, 51, 41));
        pushButtonOK = new QPushButton(SubtractLibIDDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(430, 410, 101, 31));
        pushButtonCancel = new QPushButton(SubtractLibIDDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(560, 410, 101, 31));
        label = new QLabel(SubtractLibIDDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(390, 130, 311, 29));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);

        retranslateUi(SubtractLibIDDialog);

        QMetaObject::connectSlotsByName(SubtractLibIDDialog);
    } // setupUi

    void retranslateUi(QDialog *SubtractLibIDDialog)
    {
        SubtractLibIDDialog->setWindowTitle(QCoreApplication::translate("SubtractLibIDDialog", "Subtract List", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SubtractLibIDDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SubtractLibIDDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetSelectedList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SubtractLibIDDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetSelectedList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SubtractLibIDDialog", "Name", nullptr));
        pushButtonSend->setText(QCoreApplication::translate("SubtractLibIDDialog", "=>", nullptr));
        pushButtonBack->setText(QCoreApplication::translate("SubtractLibIDDialog", "<=", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SubtractLibIDDialog", "\351\201\270\346\212\236", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SubtractLibIDDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        label->setText(QCoreApplication::translate("SubtractLibIDDialog", "\343\201\223\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\202\222\351\231\244\345\216\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SubtractLibIDDialog: public Ui_SubtractLibIDDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBTRACTLIBIDDIALOG_H
