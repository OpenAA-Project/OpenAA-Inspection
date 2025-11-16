/********************************************************************************
** Form generated from reading UI file 'DefineShortcutKeyDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEFINESHORTCUTKEYDIALOG_H
#define UI_DEFINESHORTCUTKEYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DefineShortcutKeyDialog
{
public:
    QTableWidget *tableWidget;
    QFrame *frame;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonSaveFile;
    QPushButton *pushButtonLoadFile;

    void setupUi(QDialog *DefineShortcutKeyDialog)
    {
        if (DefineShortcutKeyDialog->objectName().isEmpty())
            DefineShortcutKeyDialog->setObjectName("DefineShortcutKeyDialog");
        DefineShortcutKeyDialog->resize(651, 680);
        tableWidget = new QTableWidget(DefineShortcutKeyDialog);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 651, 631));
        frame = new QFrame(DefineShortcutKeyDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 630, 651, 51));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonOK = new QPushButton(frame);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(270, 10, 112, 34));
        pushButtonSaveFile = new QPushButton(frame);
        pushButtonSaveFile->setObjectName("pushButtonSaveFile");
        pushButtonSaveFile->setGeometry(QRect(400, 10, 112, 34));
        pushButtonLoadFile = new QPushButton(frame);
        pushButtonLoadFile->setObjectName("pushButtonLoadFile");
        pushButtonLoadFile->setGeometry(QRect(520, 10, 112, 34));

        retranslateUi(DefineShortcutKeyDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(DefineShortcutKeyDialog);
    } // setupUi

    void retranslateUi(QDialog *DefineShortcutKeyDialog)
    {
        DefineShortcutKeyDialog->setWindowTitle(QCoreApplication::translate("DefineShortcutKeyDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DefineShortcutKeyDialog", "Shortcut key", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DefineShortcutKeyDialog", "Component-Control", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DefineShortcutKeyDialog", "Action", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("DefineShortcutKeyDialog", "Extra/Number", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("DefineShortcutKeyDialog", "OK", nullptr));
        pushButtonSaveFile->setText(QCoreApplication::translate("DefineShortcutKeyDialog", "Save file", nullptr));
        pushButtonLoadFile->setText(QCoreApplication::translate("DefineShortcutKeyDialog", "Load file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DefineShortcutKeyDialog: public Ui_DefineShortcutKeyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEFINESHORTCUTKEYDIALOG_H
