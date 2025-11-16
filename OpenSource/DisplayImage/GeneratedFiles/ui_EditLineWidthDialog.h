/********************************************************************************
** Form generated from reading UI file 'EditLineWidthDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLINEWIDTHDIALOG_H
#define UI_EDITLINEWIDTHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EditLineWidthDialog
{
public:
    QSpinBox *spinBoxLineWidth;
    QLabel *label;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *EditLineWidthDialog)
    {
        if (EditLineWidthDialog->objectName().isEmpty())
            EditLineWidthDialog->setObjectName("EditLineWidthDialog");
        EditLineWidthDialog->resize(206, 92);
        spinBoxLineWidth = new QSpinBox(EditLineWidthDialog);
        spinBoxLineWidth->setObjectName("spinBoxLineWidth");
        spinBoxLineWidth->setGeometry(QRect(80, 10, 71, 31));
        label = new QLabel(EditLineWidthDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 61, 31));
        pushButtonOK = new QPushButton(EditLineWidthDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(50, 50, 101, 31));

        retranslateUi(EditLineWidthDialog);

        QMetaObject::connectSlotsByName(EditLineWidthDialog);
    } // setupUi

    void retranslateUi(QDialog *EditLineWidthDialog)
    {
        EditLineWidthDialog->setWindowTitle(QCoreApplication::translate("EditLineWidthDialog", "Line width", nullptr));
        label->setText(QCoreApplication::translate("EditLineWidthDialog", "Line width", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditLineWidthDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLineWidthDialog: public Ui_EditLineWidthDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLINEWIDTHDIALOG_H
