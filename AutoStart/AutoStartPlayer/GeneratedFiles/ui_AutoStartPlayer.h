/********************************************************************************
** Form generated from reading UI file 'AutoStartPlayer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOSTARTPLAYER_H
#define UI_AUTOSTARTPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoStartPlayerClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonStart;
    QDial *dialLoop;
    QLabel *labelArguments;
    QPushButton *pushButtonParam;
    QToolButton *toolButtonStop;

    void setupUi(QMainWindow *AutoStartPlayerClass)
    {
        if (AutoStartPlayerClass->objectName().isEmpty())
            AutoStartPlayerClass->setObjectName("AutoStartPlayerClass");
        AutoStartPlayerClass->resize(131, 264);
        centralWidget = new QWidget(AutoStartPlayerClass);
        centralWidget->setObjectName("centralWidget");
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
        labelArguments = new QLabel(centralWidget);
        labelArguments->setObjectName("labelArguments");
        labelArguments->setGeometry(QRect(10, 180, 111, 41));
        labelArguments->setFrameShape(QFrame::Panel);
        labelArguments->setFrameShadow(QFrame::Sunken);
        labelArguments->setWordWrap(true);
        pushButtonParam = new QPushButton(centralWidget);
        pushButtonParam->setObjectName("pushButtonParam");
        pushButtonParam->setGeometry(QRect(30, 230, 75, 23));
        toolButtonStop = new QToolButton(centralWidget);
        toolButtonStop->setObjectName("toolButtonStop");
        toolButtonStop->setGeometry(QRect(20, 50, 91, 21));
        toolButtonStop->setCheckable(true);
        AutoStartPlayerClass->setCentralWidget(centralWidget);

        retranslateUi(AutoStartPlayerClass);

        QMetaObject::connectSlotsByName(AutoStartPlayerClass);
    } // setupUi

    void retranslateUi(QMainWindow *AutoStartPlayerClass)
    {
        AutoStartPlayerClass->setWindowTitle(QCoreApplication::translate("AutoStartPlayerClass", "AutoStartPlayer", nullptr));
        pushButtonStart->setText(QCoreApplication::translate("AutoStartPlayerClass", "Start", nullptr));
        pushButtonParam->setText(QCoreApplication::translate("AutoStartPlayerClass", "Param", nullptr));
        toolButtonStop->setText(QCoreApplication::translate("AutoStartPlayerClass", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoStartPlayerClass: public Ui_AutoStartPlayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOSTARTPLAYER_H
