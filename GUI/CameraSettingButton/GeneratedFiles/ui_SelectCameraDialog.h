/********************************************************************************
** Form generated from reading UI file 'SelectCameraDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTCAMERADIALOG_H
#define UI_SELECTCAMERADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectCameraDialogClass
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QDialog *SelectCameraDialogClass)
    {
        if (SelectCameraDialogClass->objectName().isEmpty())
            SelectCameraDialogClass->setObjectName("SelectCameraDialogClass");
        SelectCameraDialogClass->resize(160, 182);
        scrollArea = new QScrollArea(SelectCameraDialogClass);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(9, 10, 141, 161));
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 137, 157));
        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(SelectCameraDialogClass);

        QMetaObject::connectSlotsByName(SelectCameraDialogClass);
    } // setupUi

    void retranslateUi(QDialog *SelectCameraDialogClass)
    {
        (void)SelectCameraDialogClass;
    } // retranslateUi

};

namespace Ui {
    class SelectCameraDialogClass: public Ui_SelectCameraDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTCAMERADIALOG_H
