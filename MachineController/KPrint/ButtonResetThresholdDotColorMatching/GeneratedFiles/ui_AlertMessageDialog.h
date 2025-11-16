/********************************************************************************
** Form generated from reading UI file 'AlertMessageDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALERTMESSAGEDIALOG_H
#define UI_ALERTMESSAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_AlertMessageDialog
{
public:
    QLabel *label;
    QToolButton *toolButtonNo;
    QToolButton *toolButtonYes;

    void setupUi(QDialog *AlertMessageDialog)
    {
        if (AlertMessageDialog->objectName().isEmpty())
            AlertMessageDialog->setObjectName(QString::fromUtf8("AlertMessageDialog"));
        AlertMessageDialog->resize(546, 149);
        label = new QLabel(AlertMessageDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 521, 31));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        toolButtonNo = new QToolButton(AlertMessageDialog);
        toolButtonNo->setObjectName(QString::fromUtf8("toolButtonNo"));
        toolButtonNo->setGeometry(QRect(280, 70, 191, 51));
        QFont font1;
        font1.setPointSize(20);
        toolButtonNo->setFont(font1);
        toolButtonNo->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 230, 230, 255), stop:1 rgba(165, 130, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonNo->setCheckable(true);
        toolButtonNo->setAutoExclusive(true);
        toolButtonYes = new QToolButton(AlertMessageDialog);
        toolButtonYes->setObjectName(QString::fromUtf8("toolButtonYes"));
        toolButtonYes->setGeometry(QRect(70, 70, 191, 51));
        toolButtonYes->setFont(font1);
        toolButtonYes->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 254, 230, 255), stop:1 rgba(130, 165, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonYes->setCheckable(true);
        toolButtonYes->setChecked(false);
        toolButtonYes->setAutoExclusive(true);

        retranslateUi(AlertMessageDialog);

        QMetaObject::connectSlotsByName(AlertMessageDialog);
    } // setupUi

    void retranslateUi(QDialog *AlertMessageDialog)
    {
        AlertMessageDialog->setWindowTitle(QCoreApplication::translate("AlertMessageDialog", "\347\242\272\350\252\215", nullptr));
        label->setText(QCoreApplication::translate("AlertMessageDialog", "\345\255\246\347\277\222\343\201\247\350\277\275\345\212\240\343\201\227\343\201\237\343\201\227\343\201\215\343\201\204\345\200\244\343\202\222\345\210\235\346\234\237\347\212\266\346\205\213\343\201\253\346\210\273\343\201\227\343\201\276\343\201\231", nullptr));
        toolButtonNo->setText(QCoreApplication::translate("AlertMessageDialog", "\343\201\204\343\201\204\343\201\210/No", nullptr));
        toolButtonYes->setText(QCoreApplication::translate("AlertMessageDialog", "\343\201\257\343\201\204/Yes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AlertMessageDialog: public Ui_AlertMessageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALERTMESSAGEDIALOG_H
