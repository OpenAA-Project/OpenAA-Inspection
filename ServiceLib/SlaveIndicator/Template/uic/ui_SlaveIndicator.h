/********************************************************************************
** Form generated from reading UI file 'SlaveIndicator.ui'
**
** Created by: Qt User Interface Compiler version 5.15.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLAVEINDICATOR_H
#define UI_SLAVEINDICATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SlaveIndicatorClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *SlaveIndicatorClass)
    {
        if (SlaveIndicatorClass->objectName().isEmpty())
            SlaveIndicatorClass->setObjectName(QString::fromUtf8("SlaveIndicatorClass"));
        SlaveIndicatorClass->resize(57, 59);
        centralWidget = new QWidget(SlaveIndicatorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        SlaveIndicatorClass->setCentralWidget(centralWidget);

        retranslateUi(SlaveIndicatorClass);

        QMetaObject::connectSlotsByName(SlaveIndicatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *SlaveIndicatorClass)
    {
        SlaveIndicatorClass->setWindowTitle(QCoreApplication::translate("SlaveIndicatorClass", "SlaveIndicator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SlaveIndicatorClass: public Ui_SlaveIndicatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLAVEINDICATOR_H
