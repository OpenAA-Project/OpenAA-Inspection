/********************************************************************************
** Form generated from reading UI file 'SettingParameterForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGPARAMETERFORM_H
#define UI_SETTINGPARAMETERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingParameterForm
{
public:
    QFrame *frame;
    QPushButton *pushButtonOk;

    void setupUi(QDialog *SettingParameterForm)
    {
        if (SettingParameterForm->objectName().isEmpty())
            SettingParameterForm->setObjectName("SettingParameterForm");
        SettingParameterForm->resize(671, 536);
        frame = new QFrame(SettingParameterForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 671, 491));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonOk = new QPushButton(SettingParameterForm);
        pushButtonOk->setObjectName("pushButtonOk");
        pushButtonOk->setGeometry(QRect(240, 500, 191, 23));

        retranslateUi(SettingParameterForm);

        QMetaObject::connectSlotsByName(SettingParameterForm);
    } // setupUi

    void retranslateUi(QDialog *SettingParameterForm)
    {
        SettingParameterForm->setWindowTitle(QCoreApplication::translate("SettingParameterForm", "Dialog", nullptr));
        pushButtonOk->setText(QCoreApplication::translate("SettingParameterForm", "OK & Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingParameterForm: public Ui_SettingParameterForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGPARAMETERFORM_H
