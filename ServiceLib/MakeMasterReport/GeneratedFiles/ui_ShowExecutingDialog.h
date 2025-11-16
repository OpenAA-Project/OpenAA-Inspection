/********************************************************************************
** Form generated from reading UI file 'ShowExecutingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWEXECUTINGDIALOG_H
#define UI_SHOWEXECUTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ShowExecutingDialog
{
public:
    QListWidget *listWidget;
    QProgressBar *progressBar;
    QFrame *frameOperation;
    QPushButton *pushButtonSaveEXCEL;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *ShowExecutingDialog)
    {
        if (ShowExecutingDialog->objectName().isEmpty())
            ShowExecutingDialog->setObjectName("ShowExecutingDialog");
        ShowExecutingDialog->resize(392, 591);
        listWidget = new QListWidget(ShowExecutingDialog);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 0, 391, 521));
        progressBar = new QProgressBar(ShowExecutingDialog);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(0, 520, 391, 23));
        progressBar->setValue(24);
        frameOperation = new QFrame(ShowExecutingDialog);
        frameOperation->setObjectName("frameOperation");
        frameOperation->setEnabled(false);
        frameOperation->setGeometry(QRect(0, 540, 391, 51));
        frameOperation->setFrameShape(QFrame::StyledPanel);
        frameOperation->setFrameShadow(QFrame::Sunken);
        pushButtonSaveEXCEL = new QPushButton(frameOperation);
        pushButtonSaveEXCEL->setObjectName("pushButtonSaveEXCEL");
        pushButtonSaveEXCEL->setGeometry(QRect(30, 10, 141, 31));
        pushButtonClose = new QPushButton(frameOperation);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(260, 10, 121, 31));

        retranslateUi(ShowExecutingDialog);

        QMetaObject::connectSlotsByName(ShowExecutingDialog);
    } // setupUi

    void retranslateUi(QDialog *ShowExecutingDialog)
    {
        ShowExecutingDialog->setWindowTitle(QCoreApplication::translate("ShowExecutingDialog", "Dialog", nullptr));
        pushButtonSaveEXCEL->setText(QCoreApplication::translate("ShowExecutingDialog", "Save EXCEL", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ShowExecutingDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowExecutingDialog: public Ui_ShowExecutingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWEXECUTINGDIALOG_H
