/********************************************************************************
** Form generated from reading UI file 'AddFileDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFILEDIALOG_H
#define UI_ADDFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_AddFileDialogClass
{
public:
    QComboBox *comboBoxPage;
    QTableWidget *tableWidget;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *AddFileDialogClass)
    {
        if (AddFileDialogClass->objectName().isEmpty())
            AddFileDialogClass->setObjectName("AddFileDialogClass");
        AddFileDialogClass->resize(487, 339);
        comboBoxPage = new QComboBox(AddFileDialogClass);
        comboBoxPage->addItem(QString());
        comboBoxPage->setObjectName("comboBoxPage");
        comboBoxPage->setGeometry(QRect(10, 10, 111, 22));
        tableWidget = new QTableWidget(AddFileDialogClass);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 40, 461, 241));
        tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonAdd = new QPushButton(AddFileDialogClass);
        pushButtonAdd->setObjectName("pushButtonAdd");
        pushButtonAdd->setGeometry(QRect(90, 290, 111, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAdd->setIcon(icon);
        pushButtonCancel = new QPushButton(AddFileDialogClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(280, 290, 111, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(AddFileDialogClass);

        QMetaObject::connectSlotsByName(AddFileDialogClass);
    } // setupUi

    void retranslateUi(QDialog *AddFileDialogClass)
    {
        AddFileDialogClass->setWindowTitle(QCoreApplication::translate("AddFileDialogClass", "AddFileDialog", nullptr));
        comboBoxPage->setItemText(0, QCoreApplication::translate("AddFileDialogClass", "Page 0", nullptr));

        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AddFileDialogClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AddFileDialogClass", "File Name", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("AddFileDialogClass", "Add", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AddFileDialogClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddFileDialogClass: public Ui_AddFileDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFILEDIALOG_H
