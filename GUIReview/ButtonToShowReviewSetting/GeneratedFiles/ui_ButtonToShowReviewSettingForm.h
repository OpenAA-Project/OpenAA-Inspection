/********************************************************************************
** Form generated from reading UI file 'ButtonToShowReviewSettingForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONTOSHOWREVIEWSETTINGFORM_H
#define UI_BUTTONTOSHOWREVIEWSETTINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ButtonToShowReviewSettingClass
{
public:
    QGridLayout *gridLayout;
    QPushButton *pbShowSetting;

    void setupUi(QWidget *ButtonToShowReviewSettingClass)
    {
        if (ButtonToShowReviewSettingClass->objectName().isEmpty())
            ButtonToShowReviewSettingClass->setObjectName(QString::fromUtf8("ButtonToShowReviewSettingClass"));
        ButtonToShowReviewSettingClass->resize(105, 28);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ButtonToShowReviewSettingClass->sizePolicy().hasHeightForWidth());
        ButtonToShowReviewSettingClass->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(ButtonToShowReviewSettingClass);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
        pbShowSetting = new QPushButton(ButtonToShowReviewSettingClass);
        pbShowSetting->setObjectName(QString::fromUtf8("pbShowSetting"));
        sizePolicy.setHeightForWidth(pbShowSetting->sizePolicy().hasHeightForWidth());
        pbShowSetting->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pbShowSetting, 0, 0, 1, 1);


        retranslateUi(ButtonToShowReviewSettingClass);

        QMetaObject::connectSlotsByName(ButtonToShowReviewSettingClass);
    } // setupUi

    void retranslateUi(QWidget *ButtonToShowReviewSettingClass)
    {
        ButtonToShowReviewSettingClass->setWindowTitle(QCoreApplication::translate("ButtonToShowReviewSettingClass", "ButtonToShowReviewSetting", nullptr));
        pbShowSetting->setText(QCoreApplication::translate("ButtonToShowReviewSettingClass", "GeneralSetting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonToShowReviewSettingClass: public Ui_ButtonToShowReviewSettingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONTOSHOWREVIEWSETTINGFORM_H
