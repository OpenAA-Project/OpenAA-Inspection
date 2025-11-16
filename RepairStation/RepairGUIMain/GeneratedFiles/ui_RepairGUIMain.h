/********************************************************************************
** Form generated from reading UI file 'RepairGUIMain.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPAIRGUIMAIN_H
#define UI_REPAIRGUIMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RepairGUIMainClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RepairGUIMainClass)
    {
        if (RepairGUIMainClass->objectName().isEmpty())
            RepairGUIMainClass->setObjectName(QString::fromUtf8("RepairGUIMainClass"));
        RepairGUIMainClass->resize(600, 400);
        menuBar = new QMenuBar(RepairGUIMainClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        RepairGUIMainClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RepairGUIMainClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        RepairGUIMainClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(RepairGUIMainClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        RepairGUIMainClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(RepairGUIMainClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        RepairGUIMainClass->setStatusBar(statusBar);

        retranslateUi(RepairGUIMainClass);

        QMetaObject::connectSlotsByName(RepairGUIMainClass);
    } // setupUi

    void retranslateUi(QMainWindow *RepairGUIMainClass)
    {
        RepairGUIMainClass->setWindowTitle(QCoreApplication::translate("RepairGUIMainClass", "RepairGUIMain", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RepairGUIMainClass: public Ui_RepairGUIMainClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPAIRGUIMAIN_H
