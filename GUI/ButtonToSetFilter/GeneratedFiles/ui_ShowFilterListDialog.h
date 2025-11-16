/********************************************************************************
** Form generated from reading UI file 'ShowFilterListDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWFILTERLISTDIALOG_H
#define UI_SHOWFILTERLISTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ShowFilterListDialog
{
public:
    QListWidget *listWidget;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *ShowFilterListDialog)
    {
        if (ShowFilterListDialog->objectName().isEmpty())
            ShowFilterListDialog->setObjectName("ShowFilterListDialog");
        ShowFilterListDialog->resize(194, 250);
        listWidget = new QListWidget(ShowFilterListDialog);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(10, 10, 171, 192));
        pushButtonClose = new QPushButton(ShowFilterListDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(50, 210, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon);

        retranslateUi(ShowFilterListDialog);

        QMetaObject::connectSlotsByName(ShowFilterListDialog);
    } // setupUi

    void retranslateUi(QDialog *ShowFilterListDialog)
    {
        ShowFilterListDialog->setWindowTitle(QCoreApplication::translate("ShowFilterListDialog", "Show filter list", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ShowFilterListDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowFilterListDialog: public Ui_ShowFilterListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWFILTERLISTDIALOG_H
