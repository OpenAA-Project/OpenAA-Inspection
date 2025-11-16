/********************************************************************************
** Form generated from reading UI file 'SelectDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTDIALOG_H
#define UI_SELECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SelectDialog
{
public:
    QToolButton *toolButtonDelete;
    QToolButton *toolButtonLoad;
    QToolButton *toolButtonCancel;

    void setupUi(QDialog *SelectDialog)
    {
        if (SelectDialog->objectName().isEmpty())
            SelectDialog->setObjectName("SelectDialog");
        SelectDialog->resize(238, 58);
        toolButtonDelete = new QToolButton(SelectDialog);
        toolButtonDelete->setObjectName("toolButtonDelete");
        toolButtonDelete->setGeometry(QRect(10, 10, 51, 41));
        toolButtonLoad = new QToolButton(SelectDialog);
        toolButtonLoad->setObjectName("toolButtonLoad");
        toolButtonLoad->setGeometry(QRect(70, 10, 81, 41));
        toolButtonCancel = new QToolButton(SelectDialog);
        toolButtonCancel->setObjectName("toolButtonCancel");
        toolButtonCancel->setGeometry(QRect(170, 10, 61, 41));

        retranslateUi(SelectDialog);

        QMetaObject::connectSlotsByName(SelectDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectDialog)
    {
        SelectDialog->setWindowTitle(QCoreApplication::translate("SelectDialog", "Dialog", nullptr));
        toolButtonDelete->setText(QCoreApplication::translate("SelectDialog", "\345\211\212\351\231\244", nullptr));
        toolButtonLoad->setText(QCoreApplication::translate("SelectDialog", "\343\203\236\343\202\271\343\202\277\343\203\274\343\201\270\350\252\255\350\276\274", nullptr));
        toolButtonCancel->setText(QCoreApplication::translate("SelectDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectDialog: public Ui_SelectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTDIALOG_H
