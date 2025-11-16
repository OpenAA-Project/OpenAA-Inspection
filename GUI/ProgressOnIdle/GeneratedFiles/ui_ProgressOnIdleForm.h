/********************************************************************************
** Form generated from reading UI file 'ProgressOnIdleForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESSONIDLEFORM_H
#define UI_PROGRESSONIDLEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QProgressBar>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ProgressOnIdleFormClass
{
public:
    QProgressBar *progressBar;

    void setupUi(GUIFormBase *ProgressOnIdleFormClass)
    {
        if (ProgressOnIdleFormClass->objectName().isEmpty())
            ProgressOnIdleFormClass->setObjectName("ProgressOnIdleFormClass");
        ProgressOnIdleFormClass->resize(377, 21);
        progressBar = new QProgressBar(ProgressOnIdleFormClass);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(0, 0, 381, 21));
        progressBar->setMaximum(200);

        retranslateUi(ProgressOnIdleFormClass);

        QMetaObject::connectSlotsByName(ProgressOnIdleFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ProgressOnIdleFormClass)
    {
        ProgressOnIdleFormClass->setWindowTitle(QCoreApplication::translate("ProgressOnIdleFormClass", "ProgressOnIdleForm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProgressOnIdleFormClass: public Ui_ProgressOnIdleFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESSONIDLEFORM_H
