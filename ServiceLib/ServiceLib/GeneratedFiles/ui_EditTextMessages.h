/********************************************************************************
** Form generated from reading UI file 'EditTextMessages.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITTEXTMESSAGES_H
#define UI_EDITTEXTMESSAGES_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditTextMessages
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonLoad;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *EditTextMessages)
    {
        if (EditTextMessages->objectName().isEmpty())
            EditTextMessages->setObjectName("EditTextMessages");
        EditTextMessages->resize(481, 284);
        tableWidget = new QTableWidget(EditTextMessages);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 461, 192));
        pushButtonSave = new QPushButton(EditTextMessages);
        pushButtonSave->setObjectName("pushButtonSave");
        pushButtonSave->setGeometry(QRect(350, 220, 111, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSave->setIcon(icon);
        pushButtonLoad = new QPushButton(EditTextMessages);
        pushButtonLoad->setObjectName("pushButtonLoad");
        pushButtonLoad->setGeometry(QRect(350, 250, 111, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Load.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonLoad->setIcon(icon1);
        pushButtonOK = new QPushButton(EditTextMessages);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 220, 111, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon2);
        pushButtonCancel = new QPushButton(EditTextMessages);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(190, 220, 111, 41));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon3);

        retranslateUi(EditTextMessages);

        QMetaObject::connectSlotsByName(EditTextMessages);
    } // setupUi

    void retranslateUi(QDialog *EditTextMessages)
    {
        EditTextMessages->setWindowTitle(QCoreApplication::translate("EditTextMessages", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditTextMessages", "Text", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("EditTextMessages", "Save", nullptr));
        pushButtonLoad->setText(QCoreApplication::translate("EditTextMessages", "Load", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditTextMessages", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditTextMessages", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditTextMessages: public Ui_EditTextMessages {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITTEXTMESSAGES_H
