/********************************************************************************
** Form generated from reading UI file 'InputPathListDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTPATHLISTDIALOG_H
#define UI_INPUTPATHLISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_InputPathListDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonPlus;
    QPushButton *pushButtonMinus;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *InputPathListDialog)
    {
        if (InputPathListDialog->objectName().isEmpty())
            InputPathListDialog->setObjectName("InputPathListDialog");
        InputPathListDialog->resize(373, 544);
        tableWidget = new QTableWidget(InputPathListDialog);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 351, 421));
        pushButtonPlus = new QPushButton(InputPathListDialog);
        pushButtonPlus->setObjectName("pushButtonPlus");
        pushButtonPlus->setGeometry(QRect(20, 440, 41, 34));
        pushButtonMinus = new QPushButton(InputPathListDialog);
        pushButtonMinus->setObjectName("pushButtonMinus");
        pushButtonMinus->setGeometry(QRect(70, 440, 41, 34));
        pushButtonOK = new QPushButton(InputPathListDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(60, 480, 112, 34));
        pushButtonCancel = new QPushButton(InputPathListDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(200, 480, 112, 34));

        retranslateUi(InputPathListDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(InputPathListDialog);
    } // setupUi

    void retranslateUi(QDialog *InputPathListDialog)
    {
        InputPathListDialog->setWindowTitle(QCoreApplication::translate("InputPathListDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("InputPathListDialog", "Path", nullptr));
        pushButtonPlus->setText(QCoreApplication::translate("InputPathListDialog", "+", nullptr));
        pushButtonMinus->setText(QCoreApplication::translate("InputPathListDialog", "-", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputPathListDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputPathListDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputPathListDialog: public Ui_InputPathListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTPATHLISTDIALOG_H
