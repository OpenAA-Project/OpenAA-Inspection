/********************************************************************************
** Form generated from reading UI file 'ParameterHelpDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERHELPDIALOG_H
#define UI_PARAMETERHELPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_ParameterHelpDialog
{
public:
    QPlainTextEdit *plainTextEdit;

    void setupUi(QDialog *ParameterHelpDialog)
    {
        if (ParameterHelpDialog->objectName().isEmpty())
            ParameterHelpDialog->setObjectName("ParameterHelpDialog");
        ParameterHelpDialog->resize(442, 448);
        plainTextEdit = new QPlainTextEdit(ParameterHelpDialog);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(0, 0, 441, 441));
        plainTextEdit->setReadOnly(true);

        retranslateUi(ParameterHelpDialog);

        QMetaObject::connectSlotsByName(ParameterHelpDialog);
    } // setupUi

    void retranslateUi(QDialog *ParameterHelpDialog)
    {
        ParameterHelpDialog->setWindowTitle(QCoreApplication::translate("ParameterHelpDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParameterHelpDialog: public Ui_ParameterHelpDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERHELPDIALOG_H
