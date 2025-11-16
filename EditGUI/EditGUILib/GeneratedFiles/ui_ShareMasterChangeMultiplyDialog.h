/********************************************************************************
** Form generated from reading UI file 'ShareMasterChangeMultiplyDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHAREMASTERCHANGEMULTIPLYDIALOG_H
#define UI_SHAREMASTERCHANGEMULTIPLYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_ShareMasterChangeMultiplyDialog
{
public:
    QDialogButtonBox *buttonBox;
    QListWidget *listWidgetMultiply;

    void setupUi(QDialog *ShareMasterChangeMultiplyDialog)
    {
        if (ShareMasterChangeMultiplyDialog->objectName().isEmpty())
            ShareMasterChangeMultiplyDialog->setObjectName("ShareMasterChangeMultiplyDialog");
        ShareMasterChangeMultiplyDialog->resize(193, 239);
        buttonBox = new QDialogButtonBox(ShareMasterChangeMultiplyDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(10, 200, 171, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        listWidgetMultiply = new QListWidget(ShareMasterChangeMultiplyDialog);
        listWidgetMultiply->setObjectName("listWidgetMultiply");
        listWidgetMultiply->setGeometry(QRect(0, 0, 191, 192));

        retranslateUi(ShareMasterChangeMultiplyDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ShareMasterChangeMultiplyDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ShareMasterChangeMultiplyDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ShareMasterChangeMultiplyDialog);
    } // setupUi

    void retranslateUi(QDialog *ShareMasterChangeMultiplyDialog)
    {
        ShareMasterChangeMultiplyDialog->setWindowTitle(QCoreApplication::translate("ShareMasterChangeMultiplyDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShareMasterChangeMultiplyDialog: public Ui_ShareMasterChangeMultiplyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHAREMASTERCHANGEMULTIPLYDIALOG_H
