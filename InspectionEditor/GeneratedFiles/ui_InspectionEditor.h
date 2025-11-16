/********************************************************************************
** Form generated from reading UI file 'InspectionEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSPECTIONEDITOR_H
#define UI_INSPECTIONEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InspectionEditorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *InspectionEditorClass)
    {
        if (InspectionEditorClass->objectName().isEmpty())
            InspectionEditorClass->setObjectName("InspectionEditorClass");
        InspectionEditorClass->setObjectName("InspectionEditorClass");
        InspectionEditorClass->resize(600, 400);
        menuBar = new QMenuBar(InspectionEditorClass);
        menuBar->setObjectName("menuBar");
        InspectionEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(InspectionEditorClass);
        mainToolBar->setObjectName("mainToolBar");
        InspectionEditorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(InspectionEditorClass);
        centralWidget->setObjectName("centralWidget");
        InspectionEditorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(InspectionEditorClass);
        statusBar->setObjectName("statusBar");
        InspectionEditorClass->setStatusBar(statusBar);

        retranslateUi(InspectionEditorClass);

        QMetaObject::connectSlotsByName(InspectionEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *InspectionEditorClass)
    {
        InspectionEditorClass->setWindowTitle(QCoreApplication::translate("InspectionEditorClass", "InspectionEditor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InspectionEditorClass: public Ui_InspectionEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSPECTIONEDITOR_H
