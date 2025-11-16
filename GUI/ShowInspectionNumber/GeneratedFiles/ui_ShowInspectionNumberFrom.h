/********************************************************************************
** Form generated from reading UI file 'ShowInspectionNumberFrom.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWINSPECTIONNUMBERFROM_H
#define UI_SHOWINSPECTIONNUMBERFROM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowInspectionNumberFromClass
{
public:
    QLabel *label;
    QLineEdit *lineEditInspectionNumber;

    void setupUi(GUIFormBase *ShowInspectionNumberFromClass)
    {
        if (ShowInspectionNumberFromClass->objectName().isEmpty())
            ShowInspectionNumberFromClass->setObjectName("ShowInspectionNumberFromClass");
        ShowInspectionNumberFromClass->resize(151, 21);
        label = new QLabel(ShowInspectionNumberFromClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 61, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditInspectionNumber = new QLineEdit(ShowInspectionNumberFromClass);
        lineEditInspectionNumber->setObjectName("lineEditInspectionNumber");
        lineEditInspectionNumber->setGeometry(QRect(80, 0, 61, 20));

        retranslateUi(ShowInspectionNumberFromClass);

        QMetaObject::connectSlotsByName(ShowInspectionNumberFromClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowInspectionNumberFromClass)
    {
        ShowInspectionNumberFromClass->setWindowTitle(QCoreApplication::translate("ShowInspectionNumberFromClass", "ShowInspectionNumberFrom", nullptr));
        label->setText(QCoreApplication::translate("ShowInspectionNumberFromClass", "\346\244\234\346\237\273\347\225\252\345\217\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowInspectionNumberFromClass: public Ui_ShowInspectionNumberFromClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWINSPECTIONNUMBERFROM_H
