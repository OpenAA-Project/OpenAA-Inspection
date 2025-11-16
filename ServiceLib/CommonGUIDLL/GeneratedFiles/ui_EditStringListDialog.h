/********************************************************************************
** Form generated from reading UI file 'EditStringListDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITSTRINGLISTDIALOG_H
#define UI_EDITSTRINGLISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditStringListDialog
{
public:
    QDialogButtonBox *buttonBox;
    QListWidget *listWidget;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonSub;

    void setupUi(QDialog *EditStringListDialog)
    {
        if (EditStringListDialog->objectName().isEmpty())
            EditStringListDialog->setObjectName("EditStringListDialog");
        EditStringListDialog->resize(301, 510);
        buttonBox = new QDialogButtonBox(EditStringListDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(0, 460, 291, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        listWidget = new QListWidget(EditStringListDialog);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(10, 10, 281, 431));
        pushButtonAdd = new QPushButton(EditStringListDialog);
        pushButtonAdd->setObjectName("pushButtonAdd");
        pushButtonAdd->setGeometry(QRect(10, 450, 31, 28));
        pushButtonSub = new QPushButton(EditStringListDialog);
        pushButtonSub->setObjectName("pushButtonSub");
        pushButtonSub->setGeometry(QRect(50, 450, 31, 28));

        retranslateUi(EditStringListDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, EditStringListDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, EditStringListDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(EditStringListDialog);
    } // setupUi

    void retranslateUi(QDialog *EditStringListDialog)
    {
        EditStringListDialog->setWindowTitle(QCoreApplication::translate("EditStringListDialog", "Setting EditString list", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("EditStringListDialog", "+", nullptr));
        pushButtonSub->setText(QCoreApplication::translate("EditStringListDialog", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditStringListDialog: public Ui_EditStringListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITSTRINGLISTDIALOG_H
