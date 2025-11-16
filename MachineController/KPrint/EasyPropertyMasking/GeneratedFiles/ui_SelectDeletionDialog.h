/********************************************************************************
** Form generated from reading UI file 'SelectDeletionDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTDELETIONDIALOG_H
#define UI_SELECTDELETIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SelectDeletionDialog
{
public:
    QToolButton *toolButtonDeleteManualItems;
    QToolButton *toolButtonDeleteCADItems;
    QToolButton *toolButtonCancel;
    QToolButton *toolButtonOK;

    void setupUi(QDialog *SelectDeletionDialog)
    {
        if (SelectDeletionDialog->objectName().isEmpty())
            SelectDeletionDialog->setObjectName("SelectDeletionDialog");
        SelectDeletionDialog->resize(375, 266);
        toolButtonDeleteManualItems = new QToolButton(SelectDeletionDialog);
        toolButtonDeleteManualItems->setObjectName("toolButtonDeleteManualItems");
        toolButtonDeleteManualItems->setGeometry(QRect(10, 10, 361, 61));
        QFont font;
        font.setPointSize(20);
        toolButtonDeleteManualItems->setFont(font);
        toolButtonDeleteManualItems->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 234, 230, 255), stop:1 rgba(130, 135, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonDeleteManualItems->setCheckable(true);
        toolButtonDeleteManualItems->setChecked(false);
        toolButtonDeleteManualItems->setAutoExclusive(false);
        toolButtonDeleteCADItems = new QToolButton(SelectDeletionDialog);
        toolButtonDeleteCADItems->setObjectName("toolButtonDeleteCADItems");
        toolButtonDeleteCADItems->setGeometry(QRect(10, 80, 361, 61));
        toolButtonDeleteCADItems->setFont(font);
        toolButtonDeleteCADItems->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 234, 230, 255), stop:1 rgba(130, 135, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonDeleteCADItems->setCheckable(true);
        toolButtonDeleteCADItems->setChecked(false);
        toolButtonDeleteCADItems->setAutoExclusive(false);
        toolButtonCancel = new QToolButton(SelectDeletionDialog);
        toolButtonCancel->setObjectName("toolButtonCancel");
        toolButtonCancel->setGeometry(QRect(200, 160, 171, 91));
        toolButtonCancel->setFont(font);
        toolButtonCancel->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 160, 160, 255), stop:1 rgba(130, 100, 100, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(255, 0, 0, 255), stop:1 rgba(141, 0, 0, 255));\n"
"}"));
        toolButtonCancel->setCheckable(false);
        toolButtonCancel->setChecked(false);
        toolButtonCancel->setAutoExclusive(false);
        toolButtonOK = new QToolButton(SelectDeletionDialog);
        toolButtonOK->setObjectName("toolButtonOK");
        toolButtonOK->setGeometry(QRect(10, 160, 181, 91));
        toolButtonOK->setFont(font);
        toolButtonOK->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(160, 230, 160, 255), stop:1 rgba(100, 130, 100, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonOK->setCheckable(false);
        toolButtonOK->setChecked(false);
        toolButtonOK->setAutoExclusive(false);

        retranslateUi(SelectDeletionDialog);

        QMetaObject::connectSlotsByName(SelectDeletionDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectDeletionDialog)
    {
        SelectDeletionDialog->setWindowTitle(QCoreApplication::translate("SelectDeletionDialog", "Select", nullptr));
        toolButtonDeleteManualItems->setText(QCoreApplication::translate("SelectDeletionDialog", "\346\211\213\345\213\225\344\275\234\346\210\220\351\240\230\345\237\237\343\201\256\345\211\212\351\231\244", nullptr));
        toolButtonDeleteCADItems->setText(QCoreApplication::translate("SelectDeletionDialog", "CAD\351\240\230\345\237\237\343\201\256\345\211\212\351\231\244", nullptr));
        toolButtonCancel->setText(QCoreApplication::translate("SelectDeletionDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        toolButtonOK->setText(QCoreApplication::translate("SelectDeletionDialog", "\347\224\237\346\210\220\351\226\213\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectDeletionDialog: public Ui_SelectDeletionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTDELETIONDIALOG_H
