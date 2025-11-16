/********************************************************************************
** Form generated from reading UI file 'ShowMasterNamesForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWMASTERNAMESFORM_H
#define UI_SHOWMASTERNAMESFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowMasterNamesFormClass
{
public:
    QGridLayout *gridLayout;
    QLabel *labelHeadMasterID;
    QLabel *labelMasterID;
    QLabel *labelHeadMasterName;
    QLabel *labelMasterName;
    QLabel *labelHeadLotID;
    QLabel *labelLotID;
    QLabel *labelHeadLotName;
    QLabel *labelLotName;
    QLabel *labelHeadWorkerID;
    QLabel *labelWorkerID;
    QLabel *labelHeadWorkerName;
    QLabel *labelWorkerName;

    void setupUi(GUIFormBase *ShowMasterNamesFormClass)
    {
        if (ShowMasterNamesFormClass->objectName().isEmpty())
            ShowMasterNamesFormClass->setObjectName(QString::fromUtf8("ShowMasterNamesFormClass"));
        ShowMasterNamesFormClass->resize(292, 145);
        gridLayout = new QGridLayout(ShowMasterNamesFormClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelHeadMasterID = new QLabel(ShowMasterNamesFormClass);
        labelHeadMasterID->setObjectName(QString::fromUtf8("labelHeadMasterID"));
        labelHeadMasterID->setFrameShape(QFrame::Panel);
        labelHeadMasterID->setFrameShadow(QFrame::Sunken);
        labelHeadMasterID->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelHeadMasterID, 0, 0, 1, 1);

        labelMasterID = new QLabel(ShowMasterNamesFormClass);
        labelMasterID->setObjectName(QString::fromUtf8("labelMasterID"));
        labelMasterID->setFrameShape(QFrame::Panel);
        labelMasterID->setFrameShadow(QFrame::Sunken);
        labelMasterID->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelMasterID, 0, 1, 1, 1);

        labelHeadMasterName = new QLabel(ShowMasterNamesFormClass);
        labelHeadMasterName->setObjectName(QString::fromUtf8("labelHeadMasterName"));
        labelHeadMasterName->setFrameShape(QFrame::Panel);
        labelHeadMasterName->setFrameShadow(QFrame::Sunken);
        labelHeadMasterName->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelHeadMasterName, 1, 0, 1, 1);

        labelMasterName = new QLabel(ShowMasterNamesFormClass);
        labelMasterName->setObjectName(QString::fromUtf8("labelMasterName"));
        labelMasterName->setFrameShape(QFrame::Panel);
        labelMasterName->setFrameShadow(QFrame::Sunken);
        labelMasterName->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelMasterName, 1, 1, 1, 1);

        labelHeadLotID = new QLabel(ShowMasterNamesFormClass);
        labelHeadLotID->setObjectName(QString::fromUtf8("labelHeadLotID"));
        labelHeadLotID->setFrameShape(QFrame::Panel);
        labelHeadLotID->setFrameShadow(QFrame::Sunken);
        labelHeadLotID->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelHeadLotID, 2, 0, 1, 1);

        labelLotID = new QLabel(ShowMasterNamesFormClass);
        labelLotID->setObjectName(QString::fromUtf8("labelLotID"));
        labelLotID->setFrameShape(QFrame::Panel);
        labelLotID->setFrameShadow(QFrame::Sunken);
        labelLotID->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelLotID, 2, 1, 1, 1);

        labelHeadLotName = new QLabel(ShowMasterNamesFormClass);
        labelHeadLotName->setObjectName(QString::fromUtf8("labelHeadLotName"));
        labelHeadLotName->setFrameShape(QFrame::Panel);
        labelHeadLotName->setFrameShadow(QFrame::Sunken);
        labelHeadLotName->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelHeadLotName, 3, 0, 1, 1);

        labelLotName = new QLabel(ShowMasterNamesFormClass);
        labelLotName->setObjectName(QString::fromUtf8("labelLotName"));
        labelLotName->setFrameShape(QFrame::Panel);
        labelLotName->setFrameShadow(QFrame::Sunken);
        labelLotName->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelLotName, 3, 1, 1, 1);

        labelHeadWorkerID = new QLabel(ShowMasterNamesFormClass);
        labelHeadWorkerID->setObjectName(QString::fromUtf8("labelHeadWorkerID"));
        labelHeadWorkerID->setFrameShape(QFrame::Panel);
        labelHeadWorkerID->setFrameShadow(QFrame::Sunken);
        labelHeadWorkerID->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelHeadWorkerID, 4, 0, 1, 1);

        labelWorkerID = new QLabel(ShowMasterNamesFormClass);
        labelWorkerID->setObjectName(QString::fromUtf8("labelWorkerID"));
        labelWorkerID->setFrameShape(QFrame::Panel);
        labelWorkerID->setFrameShadow(QFrame::Sunken);
        labelWorkerID->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelWorkerID, 4, 1, 1, 1);

        labelHeadWorkerName = new QLabel(ShowMasterNamesFormClass);
        labelHeadWorkerName->setObjectName(QString::fromUtf8("labelHeadWorkerName"));
        labelHeadWorkerName->setFrameShape(QFrame::Panel);
        labelHeadWorkerName->setFrameShadow(QFrame::Sunken);
        labelHeadWorkerName->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelHeadWorkerName, 5, 0, 1, 1);

        labelWorkerName = new QLabel(ShowMasterNamesFormClass);
        labelWorkerName->setObjectName(QString::fromUtf8("labelWorkerName"));
        labelWorkerName->setFrameShape(QFrame::Panel);
        labelWorkerName->setFrameShadow(QFrame::Sunken);
        labelWorkerName->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelWorkerName, 5, 1, 1, 1);


        retranslateUi(ShowMasterNamesFormClass);

        QMetaObject::connectSlotsByName(ShowMasterNamesFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowMasterNamesFormClass)
    {
        ShowMasterNamesFormClass->setWindowTitle(QCoreApplication::translate("ShowMasterNamesFormClass", "ShowMasterNamesForm", nullptr));
        labelHeadMasterID->setText(QCoreApplication::translate("ShowMasterNamesFormClass", "Master ID", nullptr));
        labelHeadMasterName->setText(QCoreApplication::translate("ShowMasterNamesFormClass", "Master Name", nullptr));
        labelHeadLotID->setText(QCoreApplication::translate("ShowMasterNamesFormClass", "Lot ID", nullptr));
        labelHeadLotName->setText(QCoreApplication::translate("ShowMasterNamesFormClass", "Lot Name", nullptr));
        labelHeadWorkerID->setText(QCoreApplication::translate("ShowMasterNamesFormClass", "Worker ID", nullptr));
        labelHeadWorkerName->setText(QCoreApplication::translate("ShowMasterNamesFormClass", "Worker Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowMasterNamesFormClass: public Ui_ShowMasterNamesFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWMASTERNAMESFORM_H
