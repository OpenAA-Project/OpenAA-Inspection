/********************************************************************************
** Form generated from reading UI file 'ChooseItemTypeForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEITEMTYPEFORM_H
#define UI_CHOOSEITEMTYPEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_ChooseItemTypeFormClass
{
public:
    QToolButton *toolButtonPad;
    QToolButton *toolButtonLine;
    QToolButton *toolButtonMatchingLine;

    void setupUi(QDialog *ChooseItemTypeFormClass)
    {
        if (ChooseItemTypeFormClass->objectName().isEmpty())
            ChooseItemTypeFormClass->setObjectName("ChooseItemTypeFormClass");
        ChooseItemTypeFormClass->resize(245, 171);
        toolButtonPad = new QToolButton(ChooseItemTypeFormClass);
        toolButtonPad->setObjectName("toolButtonPad");
        toolButtonPad->setGeometry(QRect(10, 10, 221, 41));
        toolButtonPad->setChecked(false);
        toolButtonLine = new QToolButton(ChooseItemTypeFormClass);
        toolButtonLine->setObjectName("toolButtonLine");
        toolButtonLine->setGeometry(QRect(10, 60, 221, 41));
        toolButtonMatchingLine = new QToolButton(ChooseItemTypeFormClass);
        toolButtonMatchingLine->setObjectName("toolButtonMatchingLine");
        toolButtonMatchingLine->setGeometry(QRect(10, 110, 221, 41));

        retranslateUi(ChooseItemTypeFormClass);

        QMetaObject::connectSlotsByName(ChooseItemTypeFormClass);
    } // setupUi

    void retranslateUi(QDialog *ChooseItemTypeFormClass)
    {
        ChooseItemTypeFormClass->setWindowTitle(QCoreApplication::translate("ChooseItemTypeFormClass", "ChooseItemTypeForm", nullptr));
        toolButtonPad->setText(QCoreApplication::translate("ChooseItemTypeFormClass", "\343\203\221\343\203\203\343\203\211\345\237\272\346\235\277", nullptr));
        toolButtonLine->setText(QCoreApplication::translate("ChooseItemTypeFormClass", "\347\267\232\347\212\266\345\237\272\346\235\277", nullptr));
        toolButtonMatchingLine->setText(QCoreApplication::translate("ChooseItemTypeFormClass", "\347\267\232\347\224\250\344\275\215\347\275\256\343\201\202\343\202\217\343\201\233", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChooseItemTypeFormClass: public Ui_ChooseItemTypeFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEITEMTYPEFORM_H
