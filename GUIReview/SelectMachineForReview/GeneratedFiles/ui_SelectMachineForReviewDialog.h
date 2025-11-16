/********************************************************************************
** Form generated from reading UI file 'SelectMachineForReviewDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTMACHINEFORREVIEWDIALOG_H
#define UI_SELECTMACHINEFORREVIEWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectMachineForReviewDialog
{
public:
    QLabel *label;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QTableWidget *tableWidgetFrontSide;
    QTableWidget *tableWidgetBackSide;
    QLabel *label_2;

    void setupUi(QDialog *SelectMachineForReviewDialog)
    {
        if (SelectMachineForReviewDialog->objectName().isEmpty())
            SelectMachineForReviewDialog->setObjectName(QString::fromUtf8("SelectMachineForReviewDialog"));
        SelectMachineForReviewDialog->resize(530, 293);
        label = new QLabel(SelectMachineForReviewDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 251, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(SelectMachineForReviewDialog);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(150, 240, 111, 41));
        pushButtonCancel = new QPushButton(SelectMachineForReviewDialog);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(270, 240, 111, 41));
        tableWidgetFrontSide = new QTableWidget(SelectMachineForReviewDialog);
        if (tableWidgetFrontSide->columnCount() < 2)
            tableWidgetFrontSide->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetFrontSide->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetFrontSide->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetFrontSide->setObjectName(QString::fromUtf8("tableWidgetFrontSide"));
        tableWidgetFrontSide->setGeometry(QRect(10, 30, 251, 192));
        tableWidgetFrontSide->setContextMenuPolicy(Qt::ActionsContextMenu);
        tableWidgetFrontSide->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetFrontSide->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetBackSide = new QTableWidget(SelectMachineForReviewDialog);
        if (tableWidgetBackSide->columnCount() < 2)
            tableWidgetBackSide->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetBackSide->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetBackSide->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetBackSide->setObjectName(QString::fromUtf8("tableWidgetBackSide"));
        tableWidgetBackSide->setGeometry(QRect(270, 30, 251, 192));
        tableWidgetBackSide->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetBackSide->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_2 = new QLabel(SelectMachineForReviewDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(270, 10, 251, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(SelectMachineForReviewDialog);

        QMetaObject::connectSlotsByName(SelectMachineForReviewDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectMachineForReviewDialog)
    {
        SelectMachineForReviewDialog->setWindowTitle(QCoreApplication::translate("SelectMachineForReviewDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SelectMachineForReviewDialog", "Front side", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectMachineForReviewDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectMachineForReviewDialog", "Cancel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetFrontSide->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectMachineForReviewDialog", "Code", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetFrontSide->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectMachineForReviewDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetBackSide->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectMachineForReviewDialog", "Code", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetBackSide->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectMachineForReviewDialog", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("SelectMachineForReviewDialog", "Back side", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectMachineForReviewDialog: public Ui_SelectMachineForReviewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTMACHINEFORREVIEWDIALOG_H
