/********************************************************************************
** Form generated from reading UI file 'ShowCurrentLightNameForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWCURRENTLIGHTNAMEFORM_H
#define UI_SHOWCURRENTLIGHTNAMEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ShowCurrentLightNameForm
{
public:
    QLabel *labelLightName;
    QLabel *labelID;

    void setupUi(GUIFormBase *ShowCurrentLightNameForm)
    {
        if (ShowCurrentLightNameForm->objectName().isEmpty())
            ShowCurrentLightNameForm->setObjectName("ShowCurrentLightNameForm");
        ShowCurrentLightNameForm->resize(385, 21);
        labelLightName = new QLabel(ShowCurrentLightNameForm);
        labelLightName->setObjectName("labelLightName");
        labelLightName->setGeometry(QRect(50, 0, 331, 21));
        labelLightName->setFrameShape(QFrame::Panel);
        labelLightName->setFrameShadow(QFrame::Sunken);
        labelID = new QLabel(ShowCurrentLightNameForm);
        labelID->setObjectName("labelID");
        labelID->setGeometry(QRect(0, 0, 51, 21));
        labelID->setFrameShape(QFrame::Panel);
        labelID->setFrameShadow(QFrame::Sunken);

        retranslateUi(ShowCurrentLightNameForm);

        QMetaObject::connectSlotsByName(ShowCurrentLightNameForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowCurrentLightNameForm)
    {
        ShowCurrentLightNameForm->setWindowTitle(QCoreApplication::translate("ShowCurrentLightNameForm", "Form", nullptr));
        labelLightName->setText(QCoreApplication::translate("ShowCurrentLightNameForm", "Light name", nullptr));
        labelID->setText(QCoreApplication::translate("ShowCurrentLightNameForm", "ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowCurrentLightNameForm: public Ui_ShowCurrentLightNameForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWCURRENTLIGHTNAMEFORM_H
