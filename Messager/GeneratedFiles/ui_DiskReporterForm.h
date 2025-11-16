/********************************************************************************
** Form generated from reading UI file 'DiskReporterForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISKREPORTERFORM_H
#define UI_DISKREPORTERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DiskReporterFormClass
{
public:
    QListWidget *listWidget;

    void setupUi(QWidget *DiskReporterFormClass)
    {
        if (DiskReporterFormClass->objectName().isEmpty())
            DiskReporterFormClass->setObjectName("DiskReporterFormClass");
        DiskReporterFormClass->resize(257, 123);
        listWidget = new QListWidget(DiskReporterFormClass);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 0, 256, 121));

        retranslateUi(DiskReporterFormClass);

        QMetaObject::connectSlotsByName(DiskReporterFormClass);
    } // setupUi

    void retranslateUi(QWidget *DiskReporterFormClass)
    {
        DiskReporterFormClass->setWindowTitle(QCoreApplication::translate("DiskReporterFormClass", "DiskReporterForm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DiskReporterFormClass: public Ui_DiskReporterFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISKREPORTERFORM_H
