/********************************************************************************
** Form generated from reading UI file 'EditDCodeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITDCODEDIALOG_H
#define UI_EDITDCODEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditDCodeDialog
{
public:
    QTableWidget *tableWidgetDCode;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCreateDCode;

    void setupUi(QDialog *EditDCodeDialog)
    {
        if (EditDCodeDialog->objectName().isEmpty())
            EditDCodeDialog->setObjectName("EditDCodeDialog");
        EditDCodeDialog->resize(552, 409);
        tableWidgetDCode = new QTableWidget(EditDCodeDialog);
        if (tableWidgetDCode->columnCount() < 5)
            tableWidgetDCode->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetDCode->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetDCode->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetDCode->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetDCode->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetDCode->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetDCode->setObjectName("tableWidgetDCode");
        tableWidgetDCode->setGeometry(QRect(0, 0, 551, 341));
        pushButtonCancel = new QPushButton(EditDCodeDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(220, 350, 141, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonOK = new QPushButton(EditDCodeDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 350, 141, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        pushButtonCreateDCode = new QPushButton(EditDCodeDialog);
        pushButtonCreateDCode->setObjectName("pushButtonCreateDCode");
        pushButtonCreateDCode->setGeometry(QRect(390, 350, 141, 41));

        retranslateUi(EditDCodeDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(EditDCodeDialog);
    } // setupUi

    void retranslateUi(QDialog *EditDCodeDialog)
    {
        EditDCodeDialog->setWindowTitle(QCoreApplication::translate("EditDCodeDialog", "Edit DCode", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetDCode->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditDCodeDialog", "DCode", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetDCode->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditDCodeDialog", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetDCode->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EditDCodeDialog", "Width", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetDCode->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("EditDCodeDialog", "Height", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetDCode->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("EditDCodeDialog", "Select", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditDCodeDialog", "Cancel", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditDCodeDialog", "OK", nullptr));
        pushButtonCreateDCode->setText(QCoreApplication::translate("EditDCodeDialog", "Create DCode", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditDCodeDialog: public Ui_EditDCodeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITDCODEDIALOG_H
