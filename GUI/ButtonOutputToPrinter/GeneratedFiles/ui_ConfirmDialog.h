/********************************************************************************
** Form generated from reading UI file 'ConfirmDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIRMDIALOG_H
#define UI_CONFIRMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ConfirmDialog
{
public:
    QPlainTextEdit *plainTextEdit;
    QFrame *frame;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *ConfirmDialog)
    {
        if (ConfirmDialog->objectName().isEmpty())
            ConfirmDialog->setObjectName("ConfirmDialog");
        ConfirmDialog->resize(413, 369);
        plainTextEdit = new QPlainTextEdit(ConfirmDialog);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(0, 10, 411, 301));
        frame = new QFrame(ConfirmDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 310, 411, 61));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonClose = new QPushButton(frame);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(150, 10, 112, 41));

        retranslateUi(ConfirmDialog);

        QMetaObject::connectSlotsByName(ConfirmDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfirmDialog)
    {
        ConfirmDialog->setWindowTitle(QCoreApplication::translate("ConfirmDialog", "Dialog", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ConfirmDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfirmDialog: public Ui_ConfirmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIRMDIALOG_H
