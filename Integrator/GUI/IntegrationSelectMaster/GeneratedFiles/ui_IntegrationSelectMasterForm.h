/********************************************************************************
** Form generated from reading UI file 'IntegrationSelectMasterForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONSELECTMASTERFORM_H
#define UI_INTEGRATIONSELECTMASTERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_IntegrationSelectMasterForm
{
public:
    QFrame *frame;
    QPushButton *pushButtonSelect;
    QFrame *frameGrid;

    void setupUi(GUIFormBase *IntegrationSelectMasterForm)
    {
        if (IntegrationSelectMasterForm->objectName().isEmpty())
            IntegrationSelectMasterForm->setObjectName("IntegrationSelectMasterForm");
        IntegrationSelectMasterForm->resize(542, 372);
        frame = new QFrame(IntegrationSelectMasterForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 300, 541, 71));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonSelect = new QPushButton(frame);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(200, 10, 141, 51));
        frameGrid = new QFrame(IntegrationSelectMasterForm);
        frameGrid->setObjectName("frameGrid");
        frameGrid->setGeometry(QRect(0, 0, 541, 301));
        frameGrid->setFrameShape(QFrame::StyledPanel);
        frameGrid->setFrameShadow(QFrame::Sunken);

        retranslateUi(IntegrationSelectMasterForm);

        QMetaObject::connectSlotsByName(IntegrationSelectMasterForm);
    } // setupUi

    void retranslateUi(GUIFormBase *IntegrationSelectMasterForm)
    {
        IntegrationSelectMasterForm->setWindowTitle(QCoreApplication::translate("IntegrationSelectMasterForm", "Form", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("IntegrationSelectMasterForm", "\351\201\270\346\212\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationSelectMasterForm: public Ui_IntegrationSelectMasterForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONSELECTMASTERFORM_H
