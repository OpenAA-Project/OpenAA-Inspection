/********************************************************************************
** Form generated from reading UI file 'TunableListDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TUNABLELISTDIALOG_H
#define UI_TUNABLELISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TunableListDialog
{
public:
    QListWidget *listWidgetTunable;
    QPushButton *pushButtonDown;
    QPushButton *pushButtonUp;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *TunableListDialog)
    {
        if (TunableListDialog->objectName().isEmpty())
            TunableListDialog->setObjectName("TunableListDialog");
        TunableListDialog->resize(270, 216);
        listWidgetTunable = new QListWidget(TunableListDialog);
        listWidgetTunable->setObjectName("listWidgetTunable");
        listWidgetTunable->setGeometry(QRect(10, 10, 161, 192));
        pushButtonDown = new QPushButton(TunableListDialog);
        pushButtonDown->setObjectName("pushButtonDown");
        pushButtonDown->setGeometry(QRect(180, 100, 77, 31));
        pushButtonUp = new QPushButton(TunableListDialog);
        pushButtonUp->setObjectName("pushButtonUp");
        pushButtonUp->setGeometry(QRect(180, 50, 77, 31));
        pushButtonClose = new QPushButton(TunableListDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(180, 170, 77, 31));

        retranslateUi(TunableListDialog);

        QMetaObject::connectSlotsByName(TunableListDialog);
    } // setupUi

    void retranslateUi(QDialog *TunableListDialog)
    {
        TunableListDialog->setWindowTitle(QCoreApplication::translate("TunableListDialog", "Dialog", nullptr));
        pushButtonDown->setText(QCoreApplication::translate("TunableListDialog", "Down", nullptr));
        pushButtonUp->setText(QCoreApplication::translate("TunableListDialog", "Up", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("TunableListDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TunableListDialog: public Ui_TunableListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TUNABLELISTDIALOG_H
