/********************************************************************************
** Form generated from reading UI file 'IntegrationPlayer.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONPLAYER_H
#define UI_INTEGRATIONPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IntegrationPlayerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *IntegrationPlayerClass)
    {
        if (IntegrationPlayerClass->objectName().isEmpty())
            IntegrationPlayerClass->setObjectName("IntegrationPlayerClass");
        IntegrationPlayerClass->resize(600, 400);
        menuBar = new QMenuBar(IntegrationPlayerClass);
        menuBar->setObjectName("menuBar");
        IntegrationPlayerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(IntegrationPlayerClass);
        mainToolBar->setObjectName("mainToolBar");
        IntegrationPlayerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(IntegrationPlayerClass);
        centralWidget->setObjectName("centralWidget");
        IntegrationPlayerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(IntegrationPlayerClass);
        statusBar->setObjectName("statusBar");
        IntegrationPlayerClass->setStatusBar(statusBar);

        retranslateUi(IntegrationPlayerClass);

        QMetaObject::connectSlotsByName(IntegrationPlayerClass);
    } // setupUi

    void retranslateUi(QMainWindow *IntegrationPlayerClass)
    {
        IntegrationPlayerClass->setWindowTitle(QCoreApplication::translate("IntegrationPlayerClass", "IntegrationPlayer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationPlayerClass: public Ui_IntegrationPlayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONPLAYER_H
