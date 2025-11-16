/********************************************************************************
** Form generated from reading UI file 'SelectArrowForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTARROWFORM_H
#define UI_SELECTARROWFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectArrowFormClass
{
public:
    QListWidget *listWidget;

    void setupUi(QWidget *SelectArrowFormClass)
    {
        if (SelectArrowFormClass->objectName().isEmpty())
            SelectArrowFormClass->setObjectName("SelectArrowFormClass");
        SelectArrowFormClass->resize(120, 121);
        listWidget = new QListWidget(SelectArrowFormClass);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(10, 10, 101, 101));
        listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(SelectArrowFormClass);

        QMetaObject::connectSlotsByName(SelectArrowFormClass);
    } // setupUi

    void retranslateUi(QWidget *SelectArrowFormClass)
    {
        SelectArrowFormClass->setWindowTitle(QCoreApplication::translate("SelectArrowFormClass", "SelectArrowForm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectArrowFormClass: public Ui_SelectArrowFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTARROWFORM_H
