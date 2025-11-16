/********************************************************************************
** Form generated from reading UI file 'SettingLogDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGLOGDIALOG_H
#define UI_SETTINGLOGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingLogDialog
{
public:
    QLabel *label;
    QLineEdit *lineEditLogFileName;
    QPushButton *pushButtonSelectFile;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SettingLogDialog)
    {
        if (SettingLogDialog->objectName().isEmpty())
            SettingLogDialog->setObjectName("SettingLogDialog");
        SettingLogDialog->resize(598, 124);
        label = new QLabel(SettingLogDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 161, 18));
        lineEditLogFileName = new QLineEdit(SettingLogDialog);
        lineEditLogFileName->setObjectName("lineEditLogFileName");
        lineEditLogFileName->setGeometry(QRect(10, 30, 521, 34));
        pushButtonSelectFile = new QPushButton(SettingLogDialog);
        pushButtonSelectFile->setObjectName("pushButtonSelectFile");
        pushButtonSelectFile->setGeometry(QRect(540, 30, 41, 34));
        pushButtonOK = new QPushButton(SettingLogDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(130, 80, 112, 34));
        pushButtonCancel = new QPushButton(SettingLogDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(350, 80, 112, 34));

        retranslateUi(SettingLogDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SettingLogDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingLogDialog)
    {
        SettingLogDialog->setWindowTitle(QCoreApplication::translate("SettingLogDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SettingLogDialog", "Operational log file", nullptr));
        pushButtonSelectFile->setText(QCoreApplication::translate("SettingLogDialog", "...", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingLogDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingLogDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingLogDialog: public Ui_SettingLogDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGLOGDIALOG_H
