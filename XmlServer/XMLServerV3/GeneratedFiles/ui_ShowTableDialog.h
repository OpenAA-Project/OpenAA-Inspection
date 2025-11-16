/********************************************************************************
** Form generated from reading UI file 'ShowTableDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWTABLEDIALOG_H
#define UI_SHOWTABLEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ShowTableDialog
{
public:
    QLineEdit *lineEditTableName;
    QLabel *label;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonRemove;
    QListWidget *listWidgetSharedClients;
    QLabel *label_2;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *ShowTableDialog)
    {
        if (ShowTableDialog->objectName().isEmpty())
            ShowTableDialog->setObjectName(QString::fromUtf8("ShowTableDialog"));
        ShowTableDialog->resize(400, 277);
        lineEditTableName = new QLineEdit(ShowTableDialog);
        lineEditTableName->setObjectName(QString::fromUtf8("lineEditTableName"));
        lineEditTableName->setGeometry(QRect(10, 30, 381, 20));
        label = new QLabel(ShowTableDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 381, 16));
        pushButtonSave = new QPushButton(ShowTableDialog);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));
        pushButtonSave->setGeometry(QRect(10, 230, 91, 31));
        pushButtonRemove = new QPushButton(ShowTableDialog);
        pushButtonRemove->setObjectName(QString::fromUtf8("pushButtonRemove"));
        pushButtonRemove->setGeometry(QRect(130, 230, 161, 31));
        listWidgetSharedClients = new QListWidget(ShowTableDialog);
        listWidgetSharedClients->setObjectName(QString::fromUtf8("listWidgetSharedClients"));
        listWidgetSharedClients->setGeometry(QRect(10, 90, 381, 131));
        label_2 = new QLabel(ShowTableDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 70, 381, 16));
        pushButtonClose = new QPushButton(ShowTableDialog);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(310, 230, 75, 31));

        retranslateUi(ShowTableDialog);

        QMetaObject::connectSlotsByName(ShowTableDialog);
    } // setupUi

    void retranslateUi(QDialog *ShowTableDialog)
    {
        ShowTableDialog->setWindowTitle(QCoreApplication::translate("ShowTableDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ShowTableDialog", "Table name", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("ShowTableDialog", "Save", nullptr));
        pushButtonRemove->setText(QCoreApplication::translate("ShowTableDialog", "Save/Remove from memory", nullptr));
        label_2->setText(QCoreApplication::translate("ShowTableDialog", "Shared clients", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ShowTableDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowTableDialog: public Ui_ShowTableDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWTABLEDIALOG_H
