/********************************************************************************
** Form generated from reading UI file 'ShowLoadingDLLForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWLOADINGDLLFORM_H
#define UI_SHOWLOADINGDLLFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowLoadingDLLForm
{
public:
    QListWidget *listWidget;

    void setupUi(QWidget *ShowLoadingDLLForm)
    {
        if (ShowLoadingDLLForm->objectName().isEmpty())
            ShowLoadingDLLForm->setObjectName("ShowLoadingDLLForm");
        ShowLoadingDLLForm->resize(412, 372);
        listWidget = new QListWidget(ShowLoadingDLLForm);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 0, 411, 371));

        retranslateUi(ShowLoadingDLLForm);

        QMetaObject::connectSlotsByName(ShowLoadingDLLForm);
    } // setupUi

    void retranslateUi(QWidget *ShowLoadingDLLForm)
    {
        ShowLoadingDLLForm->setWindowTitle(QCoreApplication::translate("ShowLoadingDLLForm", "Loading...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowLoadingDLLForm: public Ui_ShowLoadingDLLForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWLOADINGDLLFORM_H
