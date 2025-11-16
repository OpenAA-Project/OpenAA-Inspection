/********************************************************************************
** Form generated from reading UI file 'SelectDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTDIALOG_H
#define UI_SELECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectDialog
{
public:
    QListWidget *listWidget;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonSaveAll;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonLoadAppend;
    QPushButton *pushButtonClear;

    void setupUi(QDialog *SelectDialog)
    {
        if (SelectDialog->objectName().isEmpty())
            SelectDialog->setObjectName("SelectDialog");
        SelectDialog->resize(171, 590);
        listWidget = new QListWidget(SelectDialog);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 0, 91, 591));
        pushButtonSave = new QPushButton(SelectDialog);
        pushButtonSave->setObjectName("pushButtonSave");
        pushButtonSave->setGeometry(QRect(100, 190, 61, 23));
        pushButtonSaveAll = new QPushButton(SelectDialog);
        pushButtonSaveAll->setObjectName("pushButtonSaveAll");
        pushButtonSaveAll->setGeometry(QRect(100, 220, 61, 23));
        pushButtonSelect = new QPushButton(SelectDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(100, 100, 61, 23));
        pushButtonLoadAppend = new QPushButton(SelectDialog);
        pushButtonLoadAppend->setObjectName("pushButtonLoadAppend");
        pushButtonLoadAppend->setGeometry(QRect(100, 280, 61, 23));
        pushButtonClear = new QPushButton(SelectDialog);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(100, 380, 61, 23));

        retranslateUi(SelectDialog);

        QMetaObject::connectSlotsByName(SelectDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectDialog)
    {
        SelectDialog->setWindowTitle(QCoreApplication::translate("SelectDialog", "Dialog", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("SelectDialog", "Save", nullptr));
        pushButtonSaveAll->setText(QCoreApplication::translate("SelectDialog", "Save all", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectDialog", "Select", nullptr));
        pushButtonLoadAppend->setText(QCoreApplication::translate("SelectDialog", "Append", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("SelectDialog", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectDialog: public Ui_SelectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTDIALOG_H
