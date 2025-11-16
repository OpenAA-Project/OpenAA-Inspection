/********************************************************************************
** Form generated from reading UI file 'CameraAlignmentSettingForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAALIGNMENTSETTINGFORM_H
#define UI_CAMERAALIGNMENTSETTINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include "InputRectInConstImageLabel.h"
#include "InputRectInMultiImageWidget.h"

QT_BEGIN_NAMESPACE

class Ui_CameraAlignmentSettingClass
{
public:
    QGridLayout *gridLayout;
    InputRectInMultiImageWidget *widWholeImageAlignment;
    InputRectInConstImageLabel *lbCameraAlignment;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *pushButtonMove;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *CameraAlignmentSettingClass)
    {
        if (CameraAlignmentSettingClass->objectName().isEmpty())
            CameraAlignmentSettingClass->setObjectName(QString::fromUtf8("CameraAlignmentSettingClass"));
        CameraAlignmentSettingClass->setWindowModality(Qt::WindowModal);
        CameraAlignmentSettingClass->resize(1119, 580);
        gridLayout = new QGridLayout(CameraAlignmentSettingClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widWholeImageAlignment = new InputRectInMultiImageWidget(CameraAlignmentSettingClass);
        widWholeImageAlignment->setObjectName(QString::fromUtf8("widWholeImageAlignment"));

        gridLayout->addWidget(widWholeImageAlignment, 0, 0, 1, 1);

        lbCameraAlignment = new InputRectInConstImageLabel(CameraAlignmentSettingClass);
        lbCameraAlignment->setObjectName(QString::fromUtf8("lbCameraAlignment"));

        gridLayout->addWidget(lbCameraAlignment, 0, 1, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        pushButtonMove = new QPushButton(CameraAlignmentSettingClass);
        pushButtonMove->setObjectName(QString::fromUtf8("pushButtonMove"));

        hboxLayout->addWidget(pushButtonMove);

        okButton = new QPushButton(CameraAlignmentSettingClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(CameraAlignmentSettingClass);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 2);

        gridLayout->setRowStretch(0, 1);

        retranslateUi(CameraAlignmentSettingClass);
        QObject::connect(okButton, SIGNAL(clicked()), CameraAlignmentSettingClass, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), CameraAlignmentSettingClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(CameraAlignmentSettingClass);
    } // setupUi

    void retranslateUi(QDialog *CameraAlignmentSettingClass)
    {
        CameraAlignmentSettingClass->setWindowTitle(QCoreApplication::translate("CameraAlignmentSettingClass", "CameraAlignmentSettingForm", nullptr));
        lbCameraAlignment->setText(QCoreApplication::translate("CameraAlignmentSettingClass", "TextLabel", nullptr));
        pushButtonMove->setText(QCoreApplication::translate("CameraAlignmentSettingClass", "Move", nullptr));
        okButton->setText(QCoreApplication::translate("CameraAlignmentSettingClass", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("CameraAlignmentSettingClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraAlignmentSettingClass: public Ui_CameraAlignmentSettingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAALIGNMENTSETTINGFORM_H
