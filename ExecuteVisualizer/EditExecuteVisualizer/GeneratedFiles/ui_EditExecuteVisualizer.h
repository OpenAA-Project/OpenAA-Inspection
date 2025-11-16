/********************************************************************************
** Form generated from reading UI file 'EditExecuteVisualizer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITEXECUTEVISUALIZER_H
#define UI_EDITEXECUTEVISUALIZER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditExecuteVisualizerClass
{
public:
    QAction *actionLoad_EV_File;
    QAction *actionSave_EV_File;
    QAction *actionExfit;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EditExecuteVisualizerClass)
    {
        if (EditExecuteVisualizerClass->objectName().isEmpty())
            EditExecuteVisualizerClass->setObjectName("EditExecuteVisualizerClass");
        EditExecuteVisualizerClass->resize(199, 65);
        actionLoad_EV_File = new QAction(EditExecuteVisualizerClass);
        actionLoad_EV_File->setObjectName("actionLoad_EV_File");
        actionSave_EV_File = new QAction(EditExecuteVisualizerClass);
        actionSave_EV_File->setObjectName("actionSave_EV_File");
        actionExfit = new QAction(EditExecuteVisualizerClass);
        actionExfit->setObjectName("actionExfit");
        centralWidget = new QWidget(EditExecuteVisualizerClass);
        centralWidget->setObjectName("centralWidget");
        EditExecuteVisualizerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EditExecuteVisualizerClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 199, 17));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        EditExecuteVisualizerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EditExecuteVisualizerClass);
        mainToolBar->setObjectName("mainToolBar");
        EditExecuteVisualizerClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(EditExecuteVisualizerClass);
        statusBar->setObjectName("statusBar");
        EditExecuteVisualizerClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLoad_EV_File);
        menuFile->addAction(actionSave_EV_File);
        menuFile->addSeparator();
        menuFile->addAction(actionExfit);

        retranslateUi(EditExecuteVisualizerClass);

        QMetaObject::connectSlotsByName(EditExecuteVisualizerClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditExecuteVisualizerClass)
    {
        EditExecuteVisualizerClass->setWindowTitle(QCoreApplication::translate("EditExecuteVisualizerClass", "EditExecuteVisualizer", nullptr));
        actionLoad_EV_File->setText(QCoreApplication::translate("EditExecuteVisualizerClass", "Load EV File", nullptr));
        actionSave_EV_File->setText(QCoreApplication::translate("EditExecuteVisualizerClass", "Save EV File", nullptr));
        actionExfit->setText(QCoreApplication::translate("EditExecuteVisualizerClass", "Exfit", nullptr));
        menuFile->setTitle(QCoreApplication::translate("EditExecuteVisualizerClass", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditExecuteVisualizerClass: public Ui_EditExecuteVisualizerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITEXECUTEVISUALIZER_H
