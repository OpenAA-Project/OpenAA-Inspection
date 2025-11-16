/********************************************************************************
** Form generated from reading UI file 'SettingFocusAreaDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGFOCUSAREADIALOG_H
#define UI_SETTINGFOCUSAREADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingFocusAreaDialog
{
public:
    QFrame *frame;
    QFrame *frame_2;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonSetDarkLightSetting;

    void setupUi(QDialog *SettingFocusAreaDialog)
    {
        if (SettingFocusAreaDialog->objectName().isEmpty())
            SettingFocusAreaDialog->setObjectName(QString::fromUtf8("SettingFocusAreaDialog"));
        SettingFocusAreaDialog->resize(569, 522);
        frame = new QFrame(SettingFocusAreaDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 571, 471));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(SettingFocusAreaDialog);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(0, 470, 571, 51));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Raised);
        pushButtonOK = new QPushButton(frame_2);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(320, 10, 101, 31));
        pushButtonCancel = new QPushButton(frame_2);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(460, 10, 91, 31));
        pushButtonSetDarkLightSetting = new QPushButton(frame_2);
        pushButtonSetDarkLightSetting->setObjectName(QString::fromUtf8("pushButtonSetDarkLightSetting"));
        pushButtonSetDarkLightSetting->setGeometry(QRect(10, 10, 161, 31));

        retranslateUi(SettingFocusAreaDialog);

        QMetaObject::connectSlotsByName(SettingFocusAreaDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingFocusAreaDialog)
    {
        SettingFocusAreaDialog->setWindowTitle(QCoreApplication::translate("SettingFocusAreaDialog", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingFocusAreaDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingFocusAreaDialog", "Cancel", nullptr));
        pushButtonSetDarkLightSetting->setText(QCoreApplication::translate("SettingFocusAreaDialog", "Set dark light setting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingFocusAreaDialog: public Ui_SettingFocusAreaDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGFOCUSAREADIALOG_H
