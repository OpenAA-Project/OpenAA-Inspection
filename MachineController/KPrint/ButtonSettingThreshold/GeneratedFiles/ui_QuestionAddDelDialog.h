/********************************************************************************
** Form generated from reading UI file 'QuestionAddDelDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUESTIONADDDELDIALOG_H
#define UI_QUESTIONADDDELDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_QuestionAddDelDialog
{
public:
    QToolButton *toolButtonOK;
    QToolButton *toolButtonNG;
    QToolButton *toolButtonCancel;

    void setupUi(QDialog *QuestionAddDelDialog)
    {
        if (QuestionAddDelDialog->objectName().isEmpty())
            QuestionAddDelDialog->setObjectName("QuestionAddDelDialog");
        QuestionAddDelDialog->resize(554, 106);
        toolButtonOK = new QToolButton(QuestionAddDelDialog);
        toolButtonOK->setObjectName("toolButtonOK");
        toolButtonOK->setGeometry(QRect(20, 10, 161, 81));
        QFont font;
        font.setPointSize(16);
        toolButtonOK->setFont(font);
        toolButtonOK->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonNG = new QToolButton(QuestionAddDelDialog);
        toolButtonNG->setObjectName("toolButtonNG");
        toolButtonNG->setGeometry(QRect(200, 10, 161, 81));
        toolButtonNG->setFont(font);
        toolButtonNG->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonCancel = new QToolButton(QuestionAddDelDialog);
        toolButtonCancel->setObjectName("toolButtonCancel");
        toolButtonCancel->setGeometry(QRect(380, 10, 161, 81));
        toolButtonCancel->setFont(font);
        toolButtonCancel->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));

        retranslateUi(QuestionAddDelDialog);

        QMetaObject::connectSlotsByName(QuestionAddDelDialog);
    } // setupUi

    void retranslateUi(QDialog *QuestionAddDelDialog)
    {
        QuestionAddDelDialog->setWindowTitle(QCoreApplication::translate("QuestionAddDelDialog", "Select", nullptr));
        toolButtonOK->setText(QCoreApplication::translate("QuestionAddDelDialog", "OK\347\231\273\351\214\262", nullptr));
        toolButtonNG->setText(QCoreApplication::translate("QuestionAddDelDialog", "NG\347\231\273\351\214\262", nullptr));
        toolButtonCancel->setText(QCoreApplication::translate("QuestionAddDelDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QuestionAddDelDialog: public Ui_QuestionAddDelDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUESTIONADDDELDIALOG_H
