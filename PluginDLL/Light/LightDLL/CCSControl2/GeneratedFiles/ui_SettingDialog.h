/********************************************************************************
** Form generated from reading UI file 'SettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QFrame *frame;
    QSpinBox *spinBoxBrightness1;
    QToolButton *toolButtonOnOff1;
    QLabel *label;
    QFrame *frame_2;
    QSpinBox *spinBoxBrightness2;
    QToolButton *toolButtonOnOff2;
    QLabel *label_2;
    QPushButton *pushButton;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(234, 153);
        frame = new QFrame(SettingDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 111, 101));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        spinBoxBrightness1 = new QSpinBox(frame);
        spinBoxBrightness1->setObjectName("spinBoxBrightness1");
        spinBoxBrightness1->setGeometry(QRect(10, 30, 91, 22));
        spinBoxBrightness1->setMaximum(255);
        toolButtonOnOff1 = new QToolButton(frame);
        toolButtonOnOff1->setObjectName("toolButtonOnOff1");
        toolButtonOnOff1->setGeometry(QRect(10, 60, 91, 31));
        toolButtonOnOff1->setCheckable(true);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(-1, 2, 111, 20));
        label->setAlignment(Qt::AlignCenter);
        frame_2 = new QFrame(SettingDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(120, 0, 111, 101));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        spinBoxBrightness2 = new QSpinBox(frame_2);
        spinBoxBrightness2->setObjectName("spinBoxBrightness2");
        spinBoxBrightness2->setGeometry(QRect(10, 30, 91, 22));
        spinBoxBrightness2->setMaximum(255);
        toolButtonOnOff2 = new QToolButton(frame_2);
        toolButtonOnOff2->setObjectName("toolButtonOnOff2");
        toolButtonOnOff2->setGeometry(QRect(10, 60, 91, 31));
        toolButtonOnOff2->setCheckable(true);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(-1, 2, 111, 20));
        label_2->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(SettingDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(60, 110, 121, 31));

        retranslateUi(SettingDialog);

        pushButton->setDefault(false);


        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Setting", nullptr));
        toolButtonOnOff1->setText(QCoreApplication::translate("SettingDialog", "ON/OFF", nullptr));
        label->setText(QCoreApplication::translate("SettingDialog", "Ch1", nullptr));
        toolButtonOnOff2->setText(QCoreApplication::translate("SettingDialog", "ON/OFF", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "Ch2", nullptr));
        pushButton->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
