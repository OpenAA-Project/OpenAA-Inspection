/********************************************************************************
** Form generated from reading UI file 'ChangeServerForMasterDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGESERVERFORMASTERDIALOG_H
#define UI_CHANGESERVERFORMASTERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChangeServerForMasterDialog
{
public:
    QListWidget *listWidgetServer;
    QPushButton *pushButtonChange;
    QPushButton *pushButtonCancel;
    QLabel *label;
    QPushButton *pushButtonEdit;

    void setupUi(QDialog *ChangeServerForMasterDialog)
    {
        if (ChangeServerForMasterDialog->objectName().isEmpty())
            ChangeServerForMasterDialog->setObjectName("ChangeServerForMasterDialog");
        ChangeServerForMasterDialog->resize(197, 270);
        listWidgetServer = new QListWidget(ChangeServerForMasterDialog);
        new QListWidgetItem(listWidgetServer);
        new QListWidgetItem(listWidgetServer);
        new QListWidgetItem(listWidgetServer);
        new QListWidgetItem(listWidgetServer);
        new QListWidgetItem(listWidgetServer);
        new QListWidgetItem(listWidgetServer);
        new QListWidgetItem(listWidgetServer);
        listWidgetServer->setObjectName("listWidgetServer");
        listWidgetServer->setGeometry(QRect(10, 10, 171, 141));
        listWidgetServer->setAlternatingRowColors(true);
        pushButtonChange = new QPushButton(ChangeServerForMasterDialog);
        pushButtonChange->setObjectName("pushButtonChange");
        pushButtonChange->setGeometry(QRect(10, 160, 81, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Change.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonChange->setIcon(icon);
        pushButtonCancel = new QPushButton(ChangeServerForMasterDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(100, 160, 81, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        label = new QLabel(ChangeServerForMasterDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 240, 171, 21));
        pushButtonEdit = new QPushButton(ChangeServerForMasterDialog);
        pushButtonEdit->setObjectName("pushButtonEdit");
        pushButtonEdit->setGeometry(QRect(10, 210, 81, 23));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEdit->setIcon(icon2);

        retranslateUi(ChangeServerForMasterDialog);

        pushButtonChange->setDefault(true);


        QMetaObject::connectSlotsByName(ChangeServerForMasterDialog);
    } // setupUi

    void retranslateUi(QDialog *ChangeServerForMasterDialog)
    {
        ChangeServerForMasterDialog->setWindowTitle(QCoreApplication::translate("ChangeServerForMasterDialog", "Change server for Master", nullptr));

        const bool __sortingEnabled = listWidgetServer->isSortingEnabled();
        listWidgetServer->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidgetServer->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("ChangeServerForMasterDialog", "Server1", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidgetServer->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("ChangeServerForMasterDialog", "Server2", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidgetServer->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("ChangeServerForMasterDialog", "Server3", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidgetServer->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("ChangeServerForMasterDialog", "Server4", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidgetServer->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("ChangeServerForMasterDialog", "Server5", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = listWidgetServer->item(5);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("ChangeServerForMasterDialog", "Server6", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = listWidgetServer->item(6);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("ChangeServerForMasterDialog", "Server7", nullptr));
        listWidgetServer->setSortingEnabled(__sortingEnabled);

        pushButtonChange->setText(QCoreApplication::translate("ChangeServerForMasterDialog", "Change", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("ChangeServerForMasterDialog", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("ChangeServerForMasterDialog", "Booting is necesary after changing", nullptr));
        pushButtonEdit->setText(QCoreApplication::translate("ChangeServerForMasterDialog", "Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeServerForMasterDialog: public Ui_ChangeServerForMasterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGESERVERFORMASTERDIALOG_H
