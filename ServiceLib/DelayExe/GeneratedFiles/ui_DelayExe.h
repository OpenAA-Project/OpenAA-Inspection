/********************************************************************************
** Form generated from reading UI file 'DelayExe.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELAYEXE_H
#define UI_DELAYEXE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DelayExeClass
{
public:
    QWidget *centralWidget;
    QLabel *labelCounter;
    QLabel *labelFileName;

    void setupUi(QMainWindow *DelayExeClass)
    {
        if (DelayExeClass->objectName().isEmpty())
            DelayExeClass->setObjectName("DelayExeClass");
        DelayExeClass->resize(357, 21);
        centralWidget = new QWidget(DelayExeClass);
        centralWidget->setObjectName("centralWidget");
        labelCounter = new QLabel(centralWidget);
        labelCounter->setObjectName("labelCounter");
        labelCounter->setGeometry(QRect(0, 0, 46, 21));
        labelCounter->setFrameShape(QFrame::Panel);
        labelCounter->setFrameShadow(QFrame::Sunken);
        labelCounter->setAlignment(Qt::AlignCenter);
        labelFileName = new QLabel(centralWidget);
        labelFileName->setObjectName("labelFileName");
        labelFileName->setGeometry(QRect(50, 0, 301, 21));
        labelFileName->setFrameShape(QFrame::Panel);
        labelFileName->setFrameShadow(QFrame::Sunken);
        DelayExeClass->setCentralWidget(centralWidget);

        retranslateUi(DelayExeClass);

        QMetaObject::connectSlotsByName(DelayExeClass);
    } // setupUi

    void retranslateUi(QMainWindow *DelayExeClass)
    {
        DelayExeClass->setWindowTitle(QCoreApplication::translate("DelayExeClass", "DelayExe", nullptr));
        labelCounter->setText(QCoreApplication::translate("DelayExeClass", "1234", nullptr));
        labelFileName->setText(QCoreApplication::translate("DelayExeClass", "XXX", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DelayExeClass: public Ui_DelayExeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELAYEXE_H
