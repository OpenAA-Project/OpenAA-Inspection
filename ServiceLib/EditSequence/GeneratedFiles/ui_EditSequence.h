/********************************************************************************
** Form generated from reading UI file 'EditSequence.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITSEQUENCE_H
#define UI_EDITSEQUENCE_H

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

class Ui_EditSequenceClass
{
public:
    QAction *actionStart;
    QAction *actionShow;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuControl;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EditSequenceClass)
    {
        if (EditSequenceClass->objectName().isEmpty())
            EditSequenceClass->setObjectName("EditSequenceClass");
        EditSequenceClass->resize(170, 56);
        actionStart = new QAction(EditSequenceClass);
        actionStart->setObjectName("actionStart");
        actionShow = new QAction(EditSequenceClass);
        actionShow->setObjectName("actionShow");
        centralWidget = new QWidget(EditSequenceClass);
        centralWidget->setObjectName("centralWidget");
        EditSequenceClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EditSequenceClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 170, 18));
        menuControl = new QMenu(menuBar);
        menuControl->setObjectName("menuControl");
        EditSequenceClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EditSequenceClass);
        mainToolBar->setObjectName("mainToolBar");
        EditSequenceClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(EditSequenceClass);
        statusBar->setObjectName("statusBar");
        EditSequenceClass->setStatusBar(statusBar);

        menuBar->addAction(menuControl->menuAction());
        menuControl->addAction(actionStart);
        menuControl->addAction(actionShow);

        retranslateUi(EditSequenceClass);

        QMetaObject::connectSlotsByName(EditSequenceClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditSequenceClass)
    {
        EditSequenceClass->setWindowTitle(QCoreApplication::translate("EditSequenceClass", "EditSequence", nullptr));
        actionStart->setText(QCoreApplication::translate("EditSequenceClass", "Start", nullptr));
        actionShow->setText(QCoreApplication::translate("EditSequenceClass", "Show", nullptr));
        menuControl->setTitle(QCoreApplication::translate("EditSequenceClass", "Control", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditSequenceClass: public Ui_EditSequenceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITSEQUENCE_H
