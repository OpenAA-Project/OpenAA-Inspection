/********************************************************************************
** Form generated from reading UI file 'AutoStartList.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOSTARTLIST_H
#define UI_AUTOSTARTLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoStartListClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonParam;
    QToolButton *toolButtonStop;
    QPushButton *pushButtonStart;
    QDial *dialLoop;
    QToolButton *toolButtonOperation;

    void setupUi(QMainWindow *AutoStartListClass)
    {
        if (AutoStartListClass->objectName().isEmpty())
            AutoStartListClass->setObjectName("AutoStartListClass");
        AutoStartListClass->resize(134, 236);
        centralWidget = new QWidget(AutoStartListClass);
        centralWidget->setObjectName("centralWidget");
        pushButtonParam = new QPushButton(centralWidget);
        pushButtonParam->setObjectName("pushButtonParam");
        pushButtonParam->setGeometry(QRect(30, 180, 71, 23));
        toolButtonStop = new QToolButton(centralWidget);
        toolButtonStop->setObjectName("toolButtonStop");
        toolButtonStop->setGeometry(QRect(20, 50, 91, 21));
        toolButtonStop->setCheckable(true);
        pushButtonStart = new QPushButton(centralWidget);
        pushButtonStart->setObjectName("pushButtonStart");
        pushButtonStart->setGeometry(QRect(20, 10, 91, 31));
        dialLoop = new QDial(centralWidget);
        dialLoop->setObjectName("dialLoop");
        dialLoop->setGeometry(QRect(20, 80, 91, 91));
        dialLoop->setMaximum(20);
        dialLoop->setPageStep(1);
        dialLoop->setValue(5);
        dialLoop->setTracking(false);
        dialLoop->setOrientation(Qt::Horizontal);
        dialLoop->setNotchesVisible(true);
        toolButtonOperation = new QToolButton(centralWidget);
        toolButtonOperation->setObjectName("toolButtonOperation");
        toolButtonOperation->setGeometry(QRect(30, 210, 71, 21));
        toolButtonOperation->setCheckable(true);
        AutoStartListClass->setCentralWidget(centralWidget);

        retranslateUi(AutoStartListClass);

        QMetaObject::connectSlotsByName(AutoStartListClass);
    } // setupUi

    void retranslateUi(QMainWindow *AutoStartListClass)
    {
        AutoStartListClass->setWindowTitle(QCoreApplication::translate("AutoStartListClass", "Auto Start", nullptr));
        pushButtonParam->setText(QCoreApplication::translate("AutoStartListClass", "Param", nullptr));
        toolButtonStop->setText(QCoreApplication::translate("AutoStartListClass", "Stop", nullptr));
        pushButtonStart->setText(QCoreApplication::translate("AutoStartListClass", "Start", nullptr));
        toolButtonOperation->setText(QCoreApplication::translate("AutoStartListClass", "Operation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoStartListClass: public Ui_AutoStartListClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOSTARTLIST_H
