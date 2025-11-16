/********************************************************************************
** Form generated from reading UI file 'IntegrationShowRelationInfoForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONSHOWRELATIONINFOFORM_H
#define UI_INTEGRATIONSHOWRELATIONINFOFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_IntegrationShowRelationInfoForm
{
public:
    QLabel *labelWorkerID;
    QLabel *labelHeadWorkerID;
    QLabel *labelHeadMasterID;
    QLabel *labelMasterID;
    QLabel *labelLotName;
    QLabel *labelHeadMasterName;
    QLabel *labelWorkerName;
    QLabel *labelHeadLotName;
    QLabel *labelHeadWorkerName;
    QLabel *labelMasterName;

    void setupUi(GUIFormBase *IntegrationShowRelationInfoForm)
    {
        if (IntegrationShowRelationInfoForm->objectName().isEmpty())
            IntegrationShowRelationInfoForm->setObjectName("IntegrationShowRelationInfoForm");
        IntegrationShowRelationInfoForm->resize(284, 98);
        labelWorkerID = new QLabel(IntegrationShowRelationInfoForm);
        labelWorkerID->setObjectName("labelWorkerID");
        labelWorkerID->setGeometry(QRect(90, 60, 191, 16));
        labelWorkerID->setFrameShape(QFrame::Panel);
        labelWorkerID->setFrameShadow(QFrame::Sunken);
        labelWorkerID->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelHeadWorkerID = new QLabel(IntegrationShowRelationInfoForm);
        labelHeadWorkerID->setObjectName("labelHeadWorkerID");
        labelHeadWorkerID->setGeometry(QRect(0, 60, 91, 16));
        labelHeadWorkerID->setFrameShape(QFrame::Panel);
        labelHeadWorkerID->setFrameShadow(QFrame::Sunken);
        labelHeadWorkerID->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelHeadMasterID = new QLabel(IntegrationShowRelationInfoForm);
        labelHeadMasterID->setObjectName("labelHeadMasterID");
        labelHeadMasterID->setGeometry(QRect(0, 0, 91, 16));
        labelHeadMasterID->setFrameShape(QFrame::Panel);
        labelHeadMasterID->setFrameShadow(QFrame::Sunken);
        labelHeadMasterID->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelMasterID = new QLabel(IntegrationShowRelationInfoForm);
        labelMasterID->setObjectName("labelMasterID");
        labelMasterID->setGeometry(QRect(90, 0, 191, 16));
        labelMasterID->setFrameShape(QFrame::Panel);
        labelMasterID->setFrameShadow(QFrame::Sunken);
        labelMasterID->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelLotName = new QLabel(IntegrationShowRelationInfoForm);
        labelLotName->setObjectName("labelLotName");
        labelLotName->setGeometry(QRect(90, 40, 191, 16));
        labelLotName->setFrameShape(QFrame::Panel);
        labelLotName->setFrameShadow(QFrame::Sunken);
        labelLotName->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelHeadMasterName = new QLabel(IntegrationShowRelationInfoForm);
        labelHeadMasterName->setObjectName("labelHeadMasterName");
        labelHeadMasterName->setGeometry(QRect(0, 20, 91, 16));
        labelHeadMasterName->setFrameShape(QFrame::Panel);
        labelHeadMasterName->setFrameShadow(QFrame::Sunken);
        labelHeadMasterName->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelWorkerName = new QLabel(IntegrationShowRelationInfoForm);
        labelWorkerName->setObjectName("labelWorkerName");
        labelWorkerName->setGeometry(QRect(90, 80, 191, 16));
        labelWorkerName->setFrameShape(QFrame::Panel);
        labelWorkerName->setFrameShadow(QFrame::Sunken);
        labelWorkerName->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelHeadLotName = new QLabel(IntegrationShowRelationInfoForm);
        labelHeadLotName->setObjectName("labelHeadLotName");
        labelHeadLotName->setGeometry(QRect(0, 40, 91, 16));
        labelHeadLotName->setFrameShape(QFrame::Panel);
        labelHeadLotName->setFrameShadow(QFrame::Sunken);
        labelHeadLotName->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelHeadWorkerName = new QLabel(IntegrationShowRelationInfoForm);
        labelHeadWorkerName->setObjectName("labelHeadWorkerName");
        labelHeadWorkerName->setGeometry(QRect(0, 80, 91, 16));
        labelHeadWorkerName->setFrameShape(QFrame::Panel);
        labelHeadWorkerName->setFrameShadow(QFrame::Sunken);
        labelHeadWorkerName->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelMasterName = new QLabel(IntegrationShowRelationInfoForm);
        labelMasterName->setObjectName("labelMasterName");
        labelMasterName->setGeometry(QRect(90, 20, 191, 16));
        labelMasterName->setFrameShape(QFrame::Panel);
        labelMasterName->setFrameShadow(QFrame::Sunken);
        labelMasterName->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(IntegrationShowRelationInfoForm);

        QMetaObject::connectSlotsByName(IntegrationShowRelationInfoForm);
    } // setupUi

    void retranslateUi(GUIFormBase *IntegrationShowRelationInfoForm)
    {
        IntegrationShowRelationInfoForm->setWindowTitle(QCoreApplication::translate("IntegrationShowRelationInfoForm", "Form", nullptr));
        labelHeadWorkerID->setText(QCoreApplication::translate("IntegrationShowRelationInfoForm", "Worker ID", nullptr));
        labelHeadMasterID->setText(QCoreApplication::translate("IntegrationShowRelationInfoForm", "Master ID", nullptr));
        labelHeadMasterName->setText(QCoreApplication::translate("IntegrationShowRelationInfoForm", "Master Name", nullptr));
        labelHeadLotName->setText(QCoreApplication::translate("IntegrationShowRelationInfoForm", "Lot Name", nullptr));
        labelHeadWorkerName->setText(QCoreApplication::translate("IntegrationShowRelationInfoForm", "Worker Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationShowRelationInfoForm: public Ui_IntegrationShowRelationInfoForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONSHOWRELATIONINFOFORM_H
