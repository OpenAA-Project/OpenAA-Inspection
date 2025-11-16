/********************************************************************************
** Form generated from reading UI file 'SelectDLLDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTDLLDIALOG_H
#define UI_SELECTDLLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectDLLDialog
{
public:
    QCheckBox *checkBoxCameraDLL;
    QCheckBox *checkBoxPIODLL;
    QCheckBox *checkBoxLightDLL;
    QCheckBox *checkBoxSequenceDLL;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *SelectDLLDialog)
    {
        if (SelectDLLDialog->objectName().isEmpty())
            SelectDLLDialog->setObjectName("SelectDLLDialog");
        SelectDLLDialog->resize(272, 209);
        checkBoxCameraDLL = new QCheckBox(SelectDLLDialog);
        checkBoxCameraDLL->setObjectName("checkBoxCameraDLL");
        checkBoxCameraDLL->setGeometry(QRect(40, 20, 131, 21));
        checkBoxPIODLL = new QCheckBox(SelectDLLDialog);
        checkBoxPIODLL->setObjectName("checkBoxPIODLL");
        checkBoxPIODLL->setGeometry(QRect(40, 50, 141, 21));
        checkBoxLightDLL = new QCheckBox(SelectDLLDialog);
        checkBoxLightDLL->setObjectName("checkBoxLightDLL");
        checkBoxLightDLL->setGeometry(QRect(40, 80, 141, 21));
        checkBoxSequenceDLL = new QCheckBox(SelectDLLDialog);
        checkBoxSequenceDLL->setObjectName("checkBoxSequenceDLL");
        checkBoxSequenceDLL->setGeometry(QRect(40, 110, 141, 21));
        pushButtonOK = new QPushButton(SelectDLLDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(90, 160, 93, 28));

        retranslateUi(SelectDLLDialog);

        QMetaObject::connectSlotsByName(SelectDLLDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectDLLDialog)
    {
        SelectDLLDialog->setWindowTitle(QCoreApplication::translate("SelectDLLDialog", "Select DLL", nullptr));
        checkBoxCameraDLL->setText(QCoreApplication::translate("SelectDLLDialog", "CameraDLL", nullptr));
        checkBoxPIODLL->setText(QCoreApplication::translate("SelectDLLDialog", "PIO", nullptr));
        checkBoxLightDLL->setText(QCoreApplication::translate("SelectDLLDialog", "Light DLL", nullptr));
        checkBoxSequenceDLL->setText(QCoreApplication::translate("SelectDLLDialog", "Sequence DLL", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectDLLDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectDLLDialog: public Ui_SelectDLLDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTDLLDIALOG_H
