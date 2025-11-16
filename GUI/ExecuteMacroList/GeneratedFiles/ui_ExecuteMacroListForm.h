/********************************************************************************
** Form generated from reading UI file 'ExecuteMacroListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXECUTEMACROLISTFORM_H
#define UI_EXECUTEMACROLISTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ExecuteMacroListFormClass
{
public:
    QListWidget *listWidgetMacro;
    QPushButton *pushButtonLoadMacro;
    QLineEdit *lineEditMacroFile;
    QPushButton *pushButtonStartExecute;
    QPushButton *pushButtonStopExecute;

    void setupUi(GUIFormBase *ExecuteMacroListFormClass)
    {
        if (ExecuteMacroListFormClass->objectName().isEmpty())
            ExecuteMacroListFormClass->setObjectName("ExecuteMacroListFormClass");
        ExecuteMacroListFormClass->resize(292, 278);
        listWidgetMacro = new QListWidget(ExecuteMacroListFormClass);
        listWidgetMacro->setObjectName("listWidgetMacro");
        listWidgetMacro->setGeometry(QRect(0, 0, 291, 171));
        pushButtonLoadMacro = new QPushButton(ExecuteMacroListFormClass);
        pushButtonLoadMacro->setObjectName("pushButtonLoadMacro");
        pushButtonLoadMacro->setGeometry(QRect(10, 200, 151, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Load.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonLoadMacro->setIcon(icon);
        lineEditMacroFile = new QLineEdit(ExecuteMacroListFormClass);
        lineEditMacroFile->setObjectName("lineEditMacroFile");
        lineEditMacroFile->setGeometry(QRect(0, 174, 291, 21));
        pushButtonStartExecute = new QPushButton(ExecuteMacroListFormClass);
        pushButtonStartExecute->setObjectName("pushButtonStartExecute");
        pushButtonStartExecute->setGeometry(QRect(170, 200, 121, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Start.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonStartExecute->setIcon(icon1);
        pushButtonStopExecute = new QPushButton(ExecuteMacroListFormClass);
        pushButtonStopExecute->setObjectName("pushButtonStopExecute");
        pushButtonStopExecute->setGeometry(QRect(170, 240, 121, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Stop.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonStopExecute->setIcon(icon2);

        retranslateUi(ExecuteMacroListFormClass);

        QMetaObject::connectSlotsByName(ExecuteMacroListFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ExecuteMacroListFormClass)
    {
        ExecuteMacroListFormClass->setWindowTitle(QCoreApplication::translate("ExecuteMacroListFormClass", "ExecuteMacroListForm", nullptr));
        pushButtonLoadMacro->setText(QCoreApplication::translate("ExecuteMacroListFormClass", "Load Macro file", nullptr));
        pushButtonStartExecute->setText(QCoreApplication::translate("ExecuteMacroListFormClass", "Start macro", nullptr));
        pushButtonStopExecute->setText(QCoreApplication::translate("ExecuteMacroListFormClass", "Stop macro", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExecuteMacroListFormClass: public Ui_ExecuteMacroListFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXECUTEMACROLISTFORM_H
