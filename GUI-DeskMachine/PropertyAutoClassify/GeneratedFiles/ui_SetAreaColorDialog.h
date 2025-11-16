/********************************************************************************
** Form generated from reading UI file 'SetAreaColorDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETAREACOLORDIALOG_H
#define UI_SETAREACOLORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetAreaColorDialogClass
{
public:
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonReplace;
    QPushButton *pushButtonCancel;
    QTabWidget *tabWidget;
    QWidget *OnlyThis;
    QWidget *All;

    void setupUi(QDialog *SetAreaColorDialogClass)
    {
        if (SetAreaColorDialogClass->objectName().isEmpty())
            SetAreaColorDialogClass->setObjectName(QString::fromUtf8("SetAreaColorDialogClass"));
        SetAreaColorDialogClass->resize(413, 473);
        pushButtonAdd = new QPushButton(SetAreaColorDialogClass);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));
        pushButtonAdd->setGeometry(QRect(120, 430, 91, 31));
        pushButtonReplace = new QPushButton(SetAreaColorDialogClass);
        pushButtonReplace->setObjectName(QString::fromUtf8("pushButtonReplace"));
        pushButtonReplace->setGeometry(QRect(20, 430, 91, 31));
        pushButtonCancel = new QPushButton(SetAreaColorDialogClass);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(290, 430, 111, 31));
        tabWidget = new QTabWidget(SetAreaColorDialogClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 391, 411));
        OnlyThis = new QWidget();
        OnlyThis->setObjectName(QString::fromUtf8("OnlyThis"));
        tabWidget->addTab(OnlyThis, QString());
        All = new QWidget();
        All->setObjectName(QString::fromUtf8("All"));
        tabWidget->addTab(All, QString());

        retranslateUi(SetAreaColorDialogClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SetAreaColorDialogClass);
    } // setupUi

    void retranslateUi(QDialog *SetAreaColorDialogClass)
    {
        SetAreaColorDialogClass->setWindowTitle(QCoreApplication::translate("SetAreaColorDialogClass", "SetAreaColorDialog", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("SetAreaColorDialogClass", "\350\277\275\345\212\240", nullptr));
        pushButtonReplace->setText(QCoreApplication::translate("SetAreaColorDialogClass", "\347\275\256\346\217\233", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SetAreaColorDialogClass", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(OnlyThis), QCoreApplication::translate("SetAreaColorDialogClass", "\343\201\223\343\201\256\351\240\230\345\237\237\343\201\256\343\201\277", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(All), QCoreApplication::translate("SetAreaColorDialogClass", "\350\277\275\345\212\240\343\201\227\343\200\201\345\205\250\350\211\262\350\241\250\347\244\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetAreaColorDialogClass: public Ui_SetAreaColorDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETAREACOLORDIALOG_H
