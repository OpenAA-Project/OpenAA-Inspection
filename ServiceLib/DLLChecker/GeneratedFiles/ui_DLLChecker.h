/********************************************************************************
** Form generated from reading UI file 'DLLChecker.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLLCHECKER_H
#define UI_DLLCHECKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DLLCheckerClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonEditAlgorithm;
    QPushButton *pushButtonCheckDLL;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonDLLVersionList;

    void setupUi(QMainWindow *DLLCheckerClass)
    {
        if (DLLCheckerClass->objectName().isEmpty())
            DLLCheckerClass->setObjectName("DLLCheckerClass");
        DLLCheckerClass->resize(259, 291);
        centralWidget = new QWidget(DLLCheckerClass);
        centralWidget->setObjectName("centralWidget");
        pushButtonEditAlgorithm = new QPushButton(centralWidget);
        pushButtonEditAlgorithm->setObjectName("pushButtonEditAlgorithm");
        pushButtonEditAlgorithm->setGeometry(QRect(40, 20, 181, 61));
        pushButtonCheckDLL = new QPushButton(centralWidget);
        pushButtonCheckDLL->setObjectName("pushButtonCheckDLL");
        pushButtonCheckDLL->setGeometry(QRect(40, 90, 181, 61));
        pushButtonClose = new QPushButton(centralWidget);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(40, 240, 181, 31));
        pushButtonDLLVersionList = new QPushButton(centralWidget);
        pushButtonDLLVersionList->setObjectName("pushButtonDLLVersionList");
        pushButtonDLLVersionList->setGeometry(QRect(40, 160, 181, 61));
        DLLCheckerClass->setCentralWidget(centralWidget);

        retranslateUi(DLLCheckerClass);

        QMetaObject::connectSlotsByName(DLLCheckerClass);
    } // setupUi

    void retranslateUi(QMainWindow *DLLCheckerClass)
    {
        DLLCheckerClass->setWindowTitle(QCoreApplication::translate("DLLCheckerClass", "DLLChecker", nullptr));
        pushButtonEditAlgorithm->setText(QCoreApplication::translate("DLLCheckerClass", "Edit Algorithm list", nullptr));
        pushButtonCheckDLL->setText(QCoreApplication::translate("DLLCheckerClass", "Check DLL", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("DLLCheckerClass", "Close", nullptr));
        pushButtonDLLVersionList->setText(QCoreApplication::translate("DLLCheckerClass", "DLL Version list", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLLCheckerClass: public Ui_DLLCheckerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLLCHECKER_H
