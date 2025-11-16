/********************************************************************************
** Form generated from reading UI file 'SelectStepInODBDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTSTEPINODBDIALOG_H
#define UI_SELECTSTEPINODBDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectStepInODBDialog
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonClose;
    QTableWidget *tableWidget;

    void setupUi(QDialog *SelectStepInODBDialog)
    {
        if (SelectStepInODBDialog->objectName().isEmpty())
            SelectStepInODBDialog->setObjectName("SelectStepInODBDialog");
        SelectStepInODBDialog->resize(382, 521);
        pushButtonOK = new QPushButton(SelectStepInODBDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(50, 460, 121, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonClose = new QPushButton(SelectStepInODBDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(240, 460, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon1);
        tableWidget = new QTableWidget(SelectStepInODBDialog);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 361, 431));

        retranslateUi(SelectStepInODBDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SelectStepInODBDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectStepInODBDialog)
    {
        SelectStepInODBDialog->setWindowTitle(QCoreApplication::translate("SelectStepInODBDialog", "Select Step in ODB++", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectStepInODBDialog", "Select OK", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SelectStepInODBDialog", "Close", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectStepInODBDialog", "Step name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectStepInODBDialog: public Ui_SelectStepInODBDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTSTEPINODBDIALOG_H
