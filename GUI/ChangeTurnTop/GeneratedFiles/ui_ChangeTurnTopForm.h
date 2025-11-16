/********************************************************************************
** Form generated from reading UI file 'ChangeTurnTopForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGETURNTOPFORM_H
#define UI_CHANGETURNTOPFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ChangeTurnTopForm
{
public:
    QListWidget *listWidget;

    void setupUi(GUIFormBase *ChangeTurnTopForm)
    {
        if (ChangeTurnTopForm->objectName().isEmpty())
            ChangeTurnTopForm->setObjectName("ChangeTurnTopForm");
        ChangeTurnTopForm->resize(144, 560);
        listWidget = new QListWidget(ChangeTurnTopForm);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 0, 131, 551));
        listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(ChangeTurnTopForm);

        QMetaObject::connectSlotsByName(ChangeTurnTopForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ChangeTurnTopForm)
    {
        ChangeTurnTopForm->setWindowTitle(QCoreApplication::translate("ChangeTurnTopForm", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeTurnTopForm: public Ui_ChangeTurnTopForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGETURNTOPFORM_H
