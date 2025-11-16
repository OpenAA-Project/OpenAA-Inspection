/********************************************************************************
** Form generated from reading UI file 'RemoteLightExecuter.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOTELIGHTEXECUTER_H
#define UI_REMOTELIGHTEXECUTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RemoteLightExecuterClass
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEditFileName;
    QLineEdit *lineEditPortNumber;

    void setupUi(QMainWindow *RemoteLightExecuterClass)
    {
        if (RemoteLightExecuterClass->objectName().isEmpty())
            RemoteLightExecuterClass->setObjectName("RemoteLightExecuterClass");
        RemoteLightExecuterClass->resize(320, 20);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RemoteLightExecuterClass->sizePolicy().hasHeightForWidth());
        RemoteLightExecuterClass->setSizePolicy(sizePolicy);
        RemoteLightExecuterClass->setMinimumSize(QSize(320, 20));
        RemoteLightExecuterClass->setMaximumSize(QSize(320, 20));
        centralWidget = new QWidget(RemoteLightExecuterClass);
        centralWidget->setObjectName("centralWidget");
        lineEditFileName = new QLineEdit(centralWidget);
        lineEditFileName->setObjectName("lineEditFileName");
        lineEditFileName->setGeometry(QRect(60, 0, 261, 20));
        lineEditFileName->setReadOnly(true);
        lineEditPortNumber = new QLineEdit(centralWidget);
        lineEditPortNumber->setObjectName("lineEditPortNumber");
        lineEditPortNumber->setGeometry(QRect(0, 0, 61, 20));
        RemoteLightExecuterClass->setCentralWidget(centralWidget);

        retranslateUi(RemoteLightExecuterClass);

        QMetaObject::connectSlotsByName(RemoteLightExecuterClass);
    } // setupUi

    void retranslateUi(QMainWindow *RemoteLightExecuterClass)
    {
        RemoteLightExecuterClass->setWindowTitle(QCoreApplication::translate("RemoteLightExecuterClass", "RemoteLightExecuter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RemoteLightExecuterClass: public Ui_RemoteLightExecuterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOTELIGHTEXECUTER_H
