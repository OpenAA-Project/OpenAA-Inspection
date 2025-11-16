/********************************************************************************
** Form generated from reading UI file 'SelectCodecForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTCODECFORM_H
#define UI_SELECTCODECFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectCodecFormClass
{
public:
    QListWidget *listWidgetCodec;
    QPushButton *pushButtonSelect;

    void setupUi(QDialog *SelectCodecFormClass)
    {
        if (SelectCodecFormClass->objectName().isEmpty())
            SelectCodecFormClass->setObjectName("SelectCodecFormClass");
        SelectCodecFormClass->resize(219, 455);
        listWidgetCodec = new QListWidget(SelectCodecFormClass);
        listWidgetCodec->setObjectName("listWidgetCodec");
        listWidgetCodec->setGeometry(QRect(10, 20, 201, 381));
        pushButtonSelect = new QPushButton(SelectCodecFormClass);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(70, 412, 81, 31));

        retranslateUi(SelectCodecFormClass);

        QMetaObject::connectSlotsByName(SelectCodecFormClass);
    } // setupUi

    void retranslateUi(QDialog *SelectCodecFormClass)
    {
        SelectCodecFormClass->setWindowTitle(QCoreApplication::translate("SelectCodecFormClass", "SelectCodecForm", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectCodecFormClass", "Select", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectCodecFormClass: public Ui_SelectCodecFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTCODECFORM_H
