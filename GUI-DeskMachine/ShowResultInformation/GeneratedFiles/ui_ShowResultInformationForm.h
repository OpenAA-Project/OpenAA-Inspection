/********************************************************************************
** Form generated from reading UI file 'ShowResultInformationForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWRESULTINFORMATIONFORM_H
#define UI_SHOWRESULTINFORMATIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowResultInformationFormClass
{
public:
    QGridLayout *gridLayout;
    QLabel *labelHeadInspectCount;
    QLabel *labelInspectCount;
    QLabel *labelHeadOKCount;
    QLabel *labelOKCount;
    QLabel *labelHeadNGCount;
    QLabel *labelNGCount;
    QLabel *labelHeadReInspectCount;
    QLabel *labelReInspectCount;

    void setupUi(GUIFormBase *ShowResultInformationFormClass)
    {
        if (ShowResultInformationFormClass->objectName().isEmpty())
            ShowResultInformationFormClass->setObjectName(QString::fromUtf8("ShowResultInformationFormClass"));
        ShowResultInformationFormClass->resize(303, 110);
        gridLayout = new QGridLayout(ShowResultInformationFormClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelHeadInspectCount = new QLabel(ShowResultInformationFormClass);
        labelHeadInspectCount->setObjectName(QString::fromUtf8("labelHeadInspectCount"));
        labelHeadInspectCount->setFrameShape(QFrame::Panel);
        labelHeadInspectCount->setFrameShadow(QFrame::Sunken);
        labelHeadInspectCount->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelHeadInspectCount, 0, 0, 1, 1);

        labelInspectCount = new QLabel(ShowResultInformationFormClass);
        labelInspectCount->setObjectName(QString::fromUtf8("labelInspectCount"));
        labelInspectCount->setFrameShape(QFrame::Panel);
        labelInspectCount->setFrameShadow(QFrame::Sunken);
        labelInspectCount->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelInspectCount, 0, 1, 1, 1);

        labelHeadOKCount = new QLabel(ShowResultInformationFormClass);
        labelHeadOKCount->setObjectName(QString::fromUtf8("labelHeadOKCount"));
        labelHeadOKCount->setFrameShape(QFrame::Panel);
        labelHeadOKCount->setFrameShadow(QFrame::Sunken);
        labelHeadOKCount->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelHeadOKCount, 1, 0, 1, 1);

        labelOKCount = new QLabel(ShowResultInformationFormClass);
        labelOKCount->setObjectName(QString::fromUtf8("labelOKCount"));
        labelOKCount->setFrameShape(QFrame::Panel);
        labelOKCount->setFrameShadow(QFrame::Sunken);
        labelOKCount->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelOKCount, 1, 1, 1, 1);

        labelHeadNGCount = new QLabel(ShowResultInformationFormClass);
        labelHeadNGCount->setObjectName(QString::fromUtf8("labelHeadNGCount"));
        labelHeadNGCount->setFrameShape(QFrame::Panel);
        labelHeadNGCount->setFrameShadow(QFrame::Sunken);
        labelHeadNGCount->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelHeadNGCount, 2, 0, 1, 1);

        labelNGCount = new QLabel(ShowResultInformationFormClass);
        labelNGCount->setObjectName(QString::fromUtf8("labelNGCount"));
        labelNGCount->setFrameShape(QFrame::Panel);
        labelNGCount->setFrameShadow(QFrame::Sunken);
        labelNGCount->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelNGCount, 2, 1, 1, 1);

        labelHeadReInspectCount = new QLabel(ShowResultInformationFormClass);
        labelHeadReInspectCount->setObjectName(QString::fromUtf8("labelHeadReInspectCount"));
        labelHeadReInspectCount->setFrameShape(QFrame::Panel);
        labelHeadReInspectCount->setFrameShadow(QFrame::Sunken);
        labelHeadReInspectCount->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelHeadReInspectCount, 3, 0, 1, 1);

        labelReInspectCount = new QLabel(ShowResultInformationFormClass);
        labelReInspectCount->setObjectName(QString::fromUtf8("labelReInspectCount"));
        labelReInspectCount->setFrameShape(QFrame::Panel);
        labelReInspectCount->setFrameShadow(QFrame::Sunken);
        labelReInspectCount->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelReInspectCount, 3, 1, 1, 1);


        retranslateUi(ShowResultInformationFormClass);

        QMetaObject::connectSlotsByName(ShowResultInformationFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowResultInformationFormClass)
    {
        ShowResultInformationFormClass->setWindowTitle(QCoreApplication::translate("ShowResultInformationFormClass", "ShowResultInformationForm", nullptr));
        labelHeadInspectCount->setText(QCoreApplication::translate("ShowResultInformationFormClass", "Inspect Count", nullptr));
        labelHeadOKCount->setText(QCoreApplication::translate("ShowResultInformationFormClass", "OK Count", nullptr));
        labelHeadNGCount->setText(QCoreApplication::translate("ShowResultInformationFormClass", "NG Count", nullptr));
        labelHeadReInspectCount->setText(QCoreApplication::translate("ShowResultInformationFormClass", "ReInspect Count", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowResultInformationFormClass: public Ui_ShowResultInformationFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWRESULTINFORMATIONFORM_H
