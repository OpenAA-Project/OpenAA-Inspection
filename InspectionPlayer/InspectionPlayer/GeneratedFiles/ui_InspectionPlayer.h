/********************************************************************************
** Form generated from reading UI file 'InspectionPlayer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSPECTIONPLAYER_H
#define UI_INSPECTIONPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InspectionPlayerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *InspectionPlayerClass)
    {
        if (InspectionPlayerClass->objectName().isEmpty())
            InspectionPlayerClass->setObjectName("InspectionPlayerClass");
        InspectionPlayerClass->setObjectName("InspectionPlayerClass");
        InspectionPlayerClass->resize(600, 400);
        menuBar = new QMenuBar(InspectionPlayerClass);
        menuBar->setObjectName("menuBar");
        InspectionPlayerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(InspectionPlayerClass);
        mainToolBar->setObjectName("mainToolBar");
        InspectionPlayerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(InspectionPlayerClass);
        centralWidget->setObjectName("centralWidget");
        InspectionPlayerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(InspectionPlayerClass);
        statusBar->setObjectName("statusBar");
        InspectionPlayerClass->setStatusBar(statusBar);

        retranslateUi(InspectionPlayerClass);

        QMetaObject::connectSlotsByName(InspectionPlayerClass);
    } // setupUi

    void retranslateUi(QMainWindow *InspectionPlayerClass)
    {
        InspectionPlayerClass->setWindowTitle(QCoreApplication::translate("InspectionPlayerClass", "InspectionPlayer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InspectionPlayerClass: public Ui_InspectionPlayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSPECTIONPLAYER_H
