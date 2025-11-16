/********************************************************************************
** Form generated from reading UI file 'AddNewPhaseDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNEWPHASEDIALOG_H
#define UI_ADDNEWPHASEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddNewPhaseDialog
{
public:
    QLineEdit *lineEditPhaseName;
    QLabel *label;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *AddNewPhaseDialog)
    {
        if (AddNewPhaseDialog->objectName().isEmpty())
            AddNewPhaseDialog->setObjectName("AddNewPhaseDialog");
        AddNewPhaseDialog->resize(365, 107);
        lineEditPhaseName = new QLineEdit(AddNewPhaseDialog);
        lineEditPhaseName->setObjectName("lineEditPhaseName");
        lineEditPhaseName->setGeometry(QRect(10, 20, 341, 24));
        label = new QLabel(AddNewPhaseDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 341, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        pushButtonOK = new QPushButton(AddNewPhaseDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(40, 60, 112, 34));
        pushButtonCancel = new QPushButton(AddNewPhaseDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(200, 60, 112, 34));

        retranslateUi(AddNewPhaseDialog);

        QMetaObject::connectSlotsByName(AddNewPhaseDialog);
    } // setupUi

    void retranslateUi(QDialog *AddNewPhaseDialog)
    {
        AddNewPhaseDialog->setWindowTitle(QCoreApplication::translate("AddNewPhaseDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AddNewPhaseDialog", "\345\220\215\347\247\260", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AddNewPhaseDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AddNewPhaseDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddNewPhaseDialog: public Ui_AddNewPhaseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNEWPHASEDIALOG_H
