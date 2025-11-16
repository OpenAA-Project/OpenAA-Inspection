/********************************************************************************
** Form generated from reading UI file 'LightCCSControl2GUIForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIGHTCCSCONTROL2GUIFORM_H
#define UI_LIGHTCCSCONTROL2GUIFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_LightCCSControl2GUIForm
{
public:
    QFrame *frame;
    QDial *dialBrightness1;
    QSpinBox *spinBoxBrightness1;
    QToolButton *toolButtonON1;
    QLabel *label;
    QFrame *frame_2;
    QDial *dialBrightness2;
    QSpinBox *spinBoxBrightness2;
    QToolButton *toolButtonON2;
    QLabel *label_2;

    void setupUi(GUIFormBase *LightCCSControl2GUIForm)
    {
        if (LightCCSControl2GUIForm->objectName().isEmpty())
            LightCCSControl2GUIForm->setObjectName("LightCCSControl2GUIForm");
        LightCCSControl2GUIForm->resize(151, 182);
        frame = new QFrame(LightCCSControl2GUIForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 71, 181));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        dialBrightness1 = new QDial(frame);
        dialBrightness1->setObjectName("dialBrightness1");
        dialBrightness1->setGeometry(QRect(0, 30, 71, 71));
        dialBrightness1->setMaximum(255);
        dialBrightness1->setValue(255);
        dialBrightness1->setInvertedControls(false);
        spinBoxBrightness1 = new QSpinBox(frame);
        spinBoxBrightness1->setObjectName("spinBoxBrightness1");
        spinBoxBrightness1->setGeometry(QRect(10, 110, 51, 22));
        spinBoxBrightness1->setMaximum(255);
        spinBoxBrightness1->setValue(255);
        toolButtonON1 = new QToolButton(frame);
        toolButtonON1->setObjectName("toolButtonON1");
        toolButtonON1->setGeometry(QRect(10, 140, 51, 31));
        toolButtonON1->setCheckable(true);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 2, 71, 20));
        label->setAlignment(Qt::AlignCenter);
        frame_2 = new QFrame(LightCCSControl2GUIForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(80, 0, 71, 181));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        dialBrightness2 = new QDial(frame_2);
        dialBrightness2->setObjectName("dialBrightness2");
        dialBrightness2->setGeometry(QRect(0, 30, 71, 71));
        dialBrightness2->setMaximum(255);
        dialBrightness2->setValue(255);
        dialBrightness2->setInvertedControls(false);
        spinBoxBrightness2 = new QSpinBox(frame_2);
        spinBoxBrightness2->setObjectName("spinBoxBrightness2");
        spinBoxBrightness2->setGeometry(QRect(10, 110, 51, 22));
        spinBoxBrightness2->setMaximum(255);
        spinBoxBrightness2->setValue(255);
        toolButtonON2 = new QToolButton(frame_2);
        toolButtonON2->setObjectName("toolButtonON2");
        toolButtonON2->setGeometry(QRect(10, 140, 51, 31));
        toolButtonON2->setCheckable(true);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 2, 71, 20));
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(LightCCSControl2GUIForm);

        QMetaObject::connectSlotsByName(LightCCSControl2GUIForm);
    } // setupUi

    void retranslateUi(GUIFormBase *LightCCSControl2GUIForm)
    {
        LightCCSControl2GUIForm->setWindowTitle(QCoreApplication::translate("LightCCSControl2GUIForm", "Light CCS Control to GUI", nullptr));
        toolButtonON1->setText(QCoreApplication::translate("LightCCSControl2GUIForm", "ON", nullptr));
        label->setText(QCoreApplication::translate("LightCCSControl2GUIForm", "CH1", nullptr));
        toolButtonON2->setText(QCoreApplication::translate("LightCCSControl2GUIForm", "ON", nullptr));
        label_2->setText(QCoreApplication::translate("LightCCSControl2GUIForm", "CH2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LightCCSControl2GUIForm: public Ui_LightCCSControl2GUIForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIGHTCCSCONTROL2GUIFORM_H
