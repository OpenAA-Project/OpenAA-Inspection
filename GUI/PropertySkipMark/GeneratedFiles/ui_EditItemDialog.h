/********************************************************************************
** Form generated from reading UI file 'EditItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITITEMDIALOG_H
#define UI_EDITITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditItemDialog
{
public:
    QComboBox *comboBox;
    QTableWidget *tableWidget;
    QLineEdit *lineEditItemName;
    QLabel *label;
    QPushButton *pushButtonCreateNew;
    QPushButton *pushButtonModify;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *EditItemDialog)
    {
        if (EditItemDialog->objectName().isEmpty())
            EditItemDialog->setObjectName("EditItemDialog");
        EditItemDialog->resize(344, 403);
        comboBox = new QComboBox(EditItemDialog);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(10, 10, 321, 22));
        tableWidget = new QTableWidget(EditItemDialog);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 30, 321, 241));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        lineEditItemName = new QLineEdit(EditItemDialog);
        lineEditItemName->setObjectName("lineEditItemName");
        lineEditItemName->setGeometry(QRect(110, 280, 221, 21));
        label = new QLabel(EditItemDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 280, 91, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        pushButtonCreateNew = new QPushButton(EditItemDialog);
        pushButtonCreateNew->setObjectName("pushButtonCreateNew");
        pushButtonCreateNew->setGeometry(QRect(10, 320, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Make.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCreateNew->setIcon(icon);
        pushButtonModify = new QPushButton(EditItemDialog);
        pushButtonModify->setObjectName("pushButtonModify");
        pushButtonModify->setGeometry(QRect(120, 320, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonModify->setIcon(icon1);
        pushButtonCancel = new QPushButton(EditItemDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 360, 101, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon2);

        retranslateUi(EditItemDialog);

        pushButtonCreateNew->setDefault(true);
        pushButtonModify->setDefault(true);


        QMetaObject::connectSlotsByName(EditItemDialog);
    } // setupUi

    void retranslateUi(QDialog *EditItemDialog)
    {
        EditItemDialog->setWindowTitle(QCoreApplication::translate("EditItemDialog", "Edit Item", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditItemDialog", "ItemName", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditItemDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EditItemDialog", "Position", nullptr));
        label->setText(QCoreApplication::translate("EditItemDialog", "Name", nullptr));
        pushButtonCreateNew->setText(QCoreApplication::translate("EditItemDialog", "Create new", nullptr));
        pushButtonModify->setText(QCoreApplication::translate("EditItemDialog", "Modify", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditItemDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditItemDialog: public Ui_EditItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITITEMDIALOG_H
