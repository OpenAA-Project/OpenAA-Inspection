/********************************************************************************
** Form generated from reading UI file 'AddExcludedFileDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDEXCLUDEDFILEDIALOG_H
#define UI_ADDEXCLUDEDFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddExcludedFileDialog
{
public:
    QPushButton *pushButtonCancel;
    QLabel *label;
    QLineEdit *lineEditFileName;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *AddExcludedFileDialog)
    {
        if (AddExcludedFileDialog->objectName().isEmpty())
            AddExcludedFileDialog->setObjectName("AddExcludedFileDialog");
        AddExcludedFileDialog->resize(288, 102);
        pushButtonCancel = new QPushButton(AddExcludedFileDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(180, 60, 81, 31));
        label = new QLabel(AddExcludedFileDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 271, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        lineEditFileName = new QLineEdit(AddExcludedFileDialog);
        lineEditFileName->setObjectName("lineEditFileName");
        lineEditFileName->setGeometry(QRect(10, 30, 271, 20));
        pushButtonOK = new QPushButton(AddExcludedFileDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 60, 81, 31));

        retranslateUi(AddExcludedFileDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(AddExcludedFileDialog);
    } // setupUi

    void retranslateUi(QDialog *AddExcludedFileDialog)
    {
        AddExcludedFileDialog->setWindowTitle(QCoreApplication::translate("AddExcludedFileDialog", "Add excluded file", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AddExcludedFileDialog", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("AddExcludedFileDialog", "Table name", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AddExcludedFileDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddExcludedFileDialog: public Ui_AddExcludedFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDEXCLUDEDFILEDIALOG_H
