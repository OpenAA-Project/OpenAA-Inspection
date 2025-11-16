/********************************************************************************
** Form generated from reading UI file 'SelectImagePathDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTIMAGEPATHDIALOG_H
#define UI_SELECTIMAGEPATHDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectImagePathDialog
{
public:
    QListWidget *listWidgetPath;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectImagePathDialog)
    {
        if (SelectImagePathDialog->objectName().isEmpty())
            SelectImagePathDialog->setObjectName("SelectImagePathDialog");
        SelectImagePathDialog->resize(311, 175);
        listWidgetPath = new QListWidget(SelectImagePathDialog);
        listWidgetPath->setObjectName("listWidgetPath");
        listWidgetPath->setGeometry(QRect(0, 0, 311, 131));
        listWidgetPath->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonOK = new QPushButton(SelectImagePathDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 140, 131, 31));
        pushButtonCancel = new QPushButton(SelectImagePathDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(170, 140, 131, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);

        retranslateUi(SelectImagePathDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SelectImagePathDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectImagePathDialog)
    {
        SelectImagePathDialog->setWindowTitle(QCoreApplication::translate("SelectImagePathDialog", "Select image path", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectImagePathDialog", "Select path", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectImagePathDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectImagePathDialog: public Ui_SelectImagePathDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTIMAGEPATHDIALOG_H
