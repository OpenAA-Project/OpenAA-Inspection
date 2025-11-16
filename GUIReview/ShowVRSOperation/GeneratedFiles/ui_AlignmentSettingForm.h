/********************************************************************************
** Form generated from reading UI file 'AlignmentSettingForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALIGNMENTSETTINGFORM_H
#define UI_ALIGNMENTSETTINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include "ExpandImageDisplay.h"

QT_BEGIN_NAMESPACE

class Ui_AlignmentSettingClass
{
public:
    QGridLayout *gridLayout;
    ExpandImageDisplay *ewidWholeImage;
    ExpandImageDisplay *ewidCameraImage;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *AlignmentSettingClass)
    {
        if (AlignmentSettingClass->objectName().isEmpty())
            AlignmentSettingClass->setObjectName(QString::fromUtf8("AlignmentSettingClass"));
        AlignmentSettingClass->resize(944, 584);
        gridLayout = new QGridLayout(AlignmentSettingClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ewidWholeImage = new ExpandImageDisplay(AlignmentSettingClass);
        ewidWholeImage->setObjectName(QString::fromUtf8("ewidWholeImage"));

        gridLayout->addWidget(ewidWholeImage, 0, 0, 1, 1);

        ewidCameraImage = new ExpandImageDisplay(AlignmentSettingClass);
        ewidCameraImage->setObjectName(QString::fromUtf8("ewidCameraImage"));

        gridLayout->addWidget(ewidCameraImage, 0, 1, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(AlignmentSettingClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(AlignmentSettingClass);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 2);

        gridLayout->setRowStretch(0, 1);

        retranslateUi(AlignmentSettingClass);
        QObject::connect(okButton, SIGNAL(clicked()), AlignmentSettingClass, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), AlignmentSettingClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(AlignmentSettingClass);
    } // setupUi

    void retranslateUi(QDialog *AlignmentSettingClass)
    {
        AlignmentSettingClass->setWindowTitle(QCoreApplication::translate("AlignmentSettingClass", "AlignmentSettingForm", nullptr));
        okButton->setText(QCoreApplication::translate("AlignmentSettingClass", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("AlignmentSettingClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AlignmentSettingClass: public Ui_AlignmentSettingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALIGNMENTSETTINGFORM_H
