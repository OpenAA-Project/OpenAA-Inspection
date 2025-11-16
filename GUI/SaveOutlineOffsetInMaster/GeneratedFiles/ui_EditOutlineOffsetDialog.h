/********************************************************************************
** Form generated from reading UI file 'EditOutlineOffsetDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOUTLINEOFFSETDIALOG_H
#define UI_EDITOUTLINEOFFSETDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditOutlineOffsetDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *EditOutlineOffsetDialog)
    {
        if (EditOutlineOffsetDialog->objectName().isEmpty())
            EditOutlineOffsetDialog->setObjectName("EditOutlineOffsetDialog");
        EditOutlineOffsetDialog->resize(302, 304);
        tableWidget = new QTableWidget(EditOutlineOffsetDialog);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 281, 231));
        pushButtonOK = new QPushButton(EditOutlineOffsetDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 250, 91, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(EditOutlineOffsetDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(170, 250, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(EditOutlineOffsetDialog);

        QMetaObject::connectSlotsByName(EditOutlineOffsetDialog);
    } // setupUi

    void retranslateUi(QDialog *EditOutlineOffsetDialog)
    {
        EditOutlineOffsetDialog->setWindowTitle(QCoreApplication::translate("EditOutlineOffsetDialog", "Edit OutlineOffset", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditOutlineOffsetDialog", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditOutlineOffsetDialog", "Y", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditOutlineOffsetDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditOutlineOffsetDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditOutlineOffsetDialog: public Ui_EditOutlineOffsetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOUTLINEOFFSETDIALOG_H
