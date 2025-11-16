/********************************************************************************
** Form generated from reading UI file 'AddSourceItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDSOURCEITEMDIALOG_H
#define UI_ADDSOURCEITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_AddSourceItemDialog
{
public:
    QLabel *label;
    QTableWidget *tableWidgetAlgorithm;
    QLabel *label_2;
    QSpinBox *spinBoxItemID;
    QPushButton *pushButtonSearch;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *AddSourceItemDialog)
    {
        if (AddSourceItemDialog->objectName().isEmpty())
            AddSourceItemDialog->setObjectName("AddSourceItemDialog");
        AddSourceItemDialog->resize(301, 334);
        label = new QLabel(AddSourceItemDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 281, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        tableWidgetAlgorithm = new QTableWidget(AddSourceItemDialog);
        if (tableWidgetAlgorithm->columnCount() < 2)
            tableWidgetAlgorithm->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetAlgorithm->setObjectName("tableWidgetAlgorithm");
        tableWidgetAlgorithm->setGeometry(QRect(10, 30, 281, 192));
        tableWidgetAlgorithm->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAlgorithm->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_2 = new QLabel(AddSourceItemDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 240, 61, 31));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        spinBoxItemID = new QSpinBox(AddSourceItemDialog);
        spinBoxItemID->setObjectName("spinBoxItemID");
        spinBoxItemID->setGeometry(QRect(80, 240, 111, 31));
        spinBoxItemID->setMaximum(999999999);
        pushButtonSearch = new QPushButton(AddSourceItemDialog);
        pushButtonSearch->setObjectName("pushButtonSearch");
        pushButtonSearch->setGeometry(QRect(200, 240, 81, 28));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSearch->setIcon(icon);
        pushButtonOK = new QPushButton(AddSourceItemDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 290, 93, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        pushButtonCancel = new QPushButton(AddSourceItemDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(170, 290, 93, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon2);

        retranslateUi(AddSourceItemDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(AddSourceItemDialog);
    } // setupUi

    void retranslateUi(QDialog *AddSourceItemDialog)
    {
        AddSourceItemDialog->setWindowTitle(QCoreApplication::translate("AddSourceItemDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AddSourceItemDialog", "Algorithm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetAlgorithm->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AddSourceItemDialog", "Root", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetAlgorithm->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AddSourceItemDialog", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("AddSourceItemDialog", "ItemID", nullptr));
        pushButtonSearch->setText(QCoreApplication::translate("AddSourceItemDialog", "Search", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AddSourceItemDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AddSourceItemDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddSourceItemDialog: public Ui_AddSourceItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDSOURCEITEMDIALOG_H
