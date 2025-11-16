/********************************************************************************
** Form generated from reading UI file 'SettingParamForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGPARAMFORM_H
#define UI_SETTINGPARAMFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingParamForm
{
public:
    QFrame *frame;
    QPushButton *pushButtonOk;

    void setupUi(QWidget *SettingParamForm)
    {
        if (SettingParamForm->objectName().isEmpty())
            SettingParamForm->setObjectName(QString::fromUtf8("SettingParamForm"));
        SettingParamForm->resize(666, 529);
        frame = new QFrame(SettingParamForm);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 671, 491));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonOk = new QPushButton(SettingParamForm);
        pushButtonOk->setObjectName(QString::fromUtf8("pushButtonOk"));
        pushButtonOk->setGeometry(QRect(240, 500, 191, 23));

        retranslateUi(SettingParamForm);
        QObject::connect(pushButtonOk, SIGNAL(clicked()), SettingParamForm, SLOT(slotOkSave()));

        QMetaObject::connectSlotsByName(SettingParamForm);
    } // setupUi

    void retranslateUi(QWidget *SettingParamForm)
    {
        SettingParamForm->setWindowTitle(QCoreApplication::translate("SettingParamForm", "Form", nullptr));
        pushButtonOk->setText(QCoreApplication::translate("SettingParamForm", "OK & Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingParamForm: public Ui_SettingParamForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGPARAMFORM_H
