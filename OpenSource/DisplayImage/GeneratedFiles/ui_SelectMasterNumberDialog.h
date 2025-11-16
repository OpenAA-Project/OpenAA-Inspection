/********************************************************************************
** Form generated from reading UI file 'SelectMasterNumberDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTMASTERNUMBERDIALOG_H
#define UI_SELECTMASTERNUMBERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectMasterNumberDialog
{
public:
    QComboBox *comboBox;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectMasterNumberDialog)
    {
        if (SelectMasterNumberDialog->objectName().isEmpty())
            SelectMasterNumberDialog->setObjectName("SelectMasterNumberDialog");
        SelectMasterNumberDialog->resize(240, 97);
        comboBox = new QComboBox(SelectMasterNumberDialog);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(10, 10, 211, 24));
        pushButtonOK = new QPushButton(SelectMasterNumberDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 50, 91, 34));
        pushButtonCancel = new QPushButton(SelectMasterNumberDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(130, 50, 91, 34));

        retranslateUi(SelectMasterNumberDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SelectMasterNumberDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectMasterNumberDialog)
    {
        SelectMasterNumberDialog->setWindowTitle(QCoreApplication::translate("SelectMasterNumberDialog", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectMasterNumberDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectMasterNumberDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectMasterNumberDialog: public Ui_SelectMasterNumberDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTMASTERNUMBERDIALOG_H
