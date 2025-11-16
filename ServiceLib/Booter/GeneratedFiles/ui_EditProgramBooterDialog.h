/********************************************************************************
** Form generated from reading UI file 'EditProgramBooterDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITPROGRAMBOOTERDIALOG_H
#define UI_EDITPROGRAMBOOTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditProgramBooterDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEditProgram;
    QLineEdit *lineEditParameter;
    QPushButton *pushButtonFile;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonEdit;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *EditProgramBooterDialog)
    {
        if (EditProgramBooterDialog->objectName().isEmpty())
            EditProgramBooterDialog->setObjectName("EditProgramBooterDialog");
        EditProgramBooterDialog->resize(400, 155);
        label = new QLabel(EditProgramBooterDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 331, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(EditProgramBooterDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 60, 381, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        lineEditProgram = new QLineEdit(EditProgramBooterDialog);
        lineEditProgram->setObjectName("lineEditProgram");
        lineEditProgram->setGeometry(QRect(10, 30, 331, 20));
        lineEditParameter = new QLineEdit(EditProgramBooterDialog);
        lineEditParameter->setObjectName("lineEditParameter");
        lineEditParameter->setGeometry(QRect(10, 80, 381, 20));
        pushButtonFile = new QPushButton(EditProgramBooterDialog);
        pushButtonFile->setObjectName("pushButtonFile");
        pushButtonFile->setGeometry(QRect(350, 20, 41, 31));
        pushButtonAdd = new QPushButton(EditProgramBooterDialog);
        pushButtonAdd->setObjectName("pushButtonAdd");
        pushButtonAdd->setGeometry(QRect(40, 110, 91, 31));
        pushButtonEdit = new QPushButton(EditProgramBooterDialog);
        pushButtonEdit->setObjectName("pushButtonEdit");
        pushButtonEdit->setGeometry(QRect(160, 110, 91, 31));
        pushButtonCancel = new QPushButton(EditProgramBooterDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(270, 110, 91, 31));

        retranslateUi(EditProgramBooterDialog);

        pushButtonAdd->setDefault(true);
        pushButtonEdit->setDefault(true);


        QMetaObject::connectSlotsByName(EditProgramBooterDialog);
    } // setupUi

    void retranslateUi(QDialog *EditProgramBooterDialog)
    {
        EditProgramBooterDialog->setWindowTitle(QCoreApplication::translate("EditProgramBooterDialog", "Edit Program Booter", nullptr));
        label->setText(QCoreApplication::translate("EditProgramBooterDialog", "Program", nullptr));
        label_2->setText(QCoreApplication::translate("EditProgramBooterDialog", "Parameter", nullptr));
        pushButtonFile->setText(QCoreApplication::translate("EditProgramBooterDialog", "...", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("EditProgramBooterDialog", "Add", nullptr));
        pushButtonEdit->setText(QCoreApplication::translate("EditProgramBooterDialog", "Edit", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditProgramBooterDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditProgramBooterDialog: public Ui_EditProgramBooterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITPROGRAMBOOTERDIALOG_H
