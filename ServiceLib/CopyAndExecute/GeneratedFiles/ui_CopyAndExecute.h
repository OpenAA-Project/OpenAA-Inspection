/********************************************************************************
** Form generated from reading UI file 'CopyAndExecute.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYANDEXECUTE_H
#define UI_COPYANDEXECUTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CopyAndExecuteClass
{
public:
    QWidget *centralWidget;
    QListWidget *listWidget;

    void setupUi(QMainWindow *CopyAndExecuteClass)
    {
        if (CopyAndExecuteClass->objectName().isEmpty())
            CopyAndExecuteClass->setObjectName("CopyAndExecuteClass");
        CopyAndExecuteClass->resize(600, 400);
        centralWidget = new QWidget(CopyAndExecuteClass);
        centralWidget->setObjectName("centralWidget");
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(-60, 0, 601, 401));
        CopyAndExecuteClass->setCentralWidget(centralWidget);

        retranslateUi(CopyAndExecuteClass);

        QMetaObject::connectSlotsByName(CopyAndExecuteClass);
    } // setupUi

    void retranslateUi(QMainWindow *CopyAndExecuteClass)
    {
        CopyAndExecuteClass->setWindowTitle(QCoreApplication::translate("CopyAndExecuteClass", "CopyAndExecute", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CopyAndExecuteClass: public Ui_CopyAndExecuteClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYANDEXECUTE_H
