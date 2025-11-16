/********************************************************************************
** Form generated from reading UI file 'IntegrationSelectLotForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONSELECTLOTFORM_H
#define UI_INTEGRATIONSELECTLOTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_IntegrationSelectLotForm
{
public:
    QListWidget *listWidget;
    QFrame *frame;
    QToolButton *toolButtonUpdate;
    QToolButton *toolButtonSelect;
    QToolButton *toolButtonSetFilter;

    void setupUi(GUIFormBase *IntegrationSelectLotForm)
    {
        if (IntegrationSelectLotForm->objectName().isEmpty())
            IntegrationSelectLotForm->setObjectName("IntegrationSelectLotForm");
        IntegrationSelectLotForm->resize(434, 331);
        listWidget = new QListWidget(IntegrationSelectLotForm);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 0, 341, 331));
        frame = new QFrame(IntegrationSelectLotForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(340, 0, 91, 331));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonUpdate = new QToolButton(frame);
        toolButtonUpdate->setObjectName("toolButtonUpdate");
        toolButtonUpdate->setGeometry(QRect(10, 120, 71, 41));
        toolButtonSelect = new QToolButton(frame);
        toolButtonSelect->setObjectName("toolButtonSelect");
        toolButtonSelect->setGeometry(QRect(10, 10, 71, 41));
        toolButtonSetFilter = new QToolButton(frame);
        toolButtonSetFilter->setObjectName("toolButtonSetFilter");
        toolButtonSetFilter->setGeometry(QRect(10, 60, 71, 41));

        retranslateUi(IntegrationSelectLotForm);

        QMetaObject::connectSlotsByName(IntegrationSelectLotForm);
    } // setupUi

    void retranslateUi(GUIFormBase *IntegrationSelectLotForm)
    {
        IntegrationSelectLotForm->setWindowTitle(QCoreApplication::translate("IntegrationSelectLotForm", "Form", nullptr));
        toolButtonUpdate->setText(QCoreApplication::translate("IntegrationSelectLotForm", "\346\233\264\346\226\260", nullptr));
        toolButtonSelect->setText(QCoreApplication::translate("IntegrationSelectLotForm", "\351\201\270\346\212\236", nullptr));
        toolButtonSetFilter->setText(QCoreApplication::translate("IntegrationSelectLotForm", "\343\203\225\343\202\243\343\203\253\343\202\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationSelectLotForm: public Ui_IntegrationSelectLotForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONSELECTLOTFORM_H
