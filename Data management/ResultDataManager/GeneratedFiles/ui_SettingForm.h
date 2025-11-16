/********************************************************************************
** Form generated from reading UI file 'SettingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGFORM_H
#define UI_SETTINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingForm
{
public:
    QPushButton *pushButtonOk;
    QFrame *frame;

    void setupUi(QDialog *SettingForm)
    {
        if (SettingForm->objectName().isEmpty())
            SettingForm->setObjectName("SettingForm");
        SettingForm->resize(580, 230);
        pushButtonOk = new QPushButton(SettingForm);
        pushButtonOk->setObjectName("pushButtonOk");
        pushButtonOk->setGeometry(QRect(190, 200, 191, 23));
        frame = new QFrame(SettingForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 581, 191));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        retranslateUi(SettingForm);

        QMetaObject::connectSlotsByName(SettingForm);
    } // setupUi

    void retranslateUi(QDialog *SettingForm)
    {
        SettingForm->setWindowTitle(QCoreApplication::translate("SettingForm", "Setting Form", nullptr));
        pushButtonOk->setText(QCoreApplication::translate("SettingForm", "OK & Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingForm: public Ui_SettingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGFORM_H
