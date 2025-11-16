/********************************************************************************
** Form generated from reading UI file 'SettingDialog.ui'
**
** Created: Tue May 19 09:24:45 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QFrame *frame;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxAccel1;
    QSpinBox *spinBoxPulsePerRot1;
    QLabel *label_3;
    QSpinBox *spinBoxPitch1;
    QLabel *label_4;
    QSpinBox *spinBoxMaxVerocity1;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QSpinBox *spinBoxJogVerocity1;
    QLabel *label_8;
    QSpinBox *spinBoxOriginVelocity1;
    QLabel *label_9;
    QLabel *label_10;
    QSpinBox *spinBoxMaxPulse1;
    QLabel *label_31;
    QLabel *label_34;
    QSpinBox *spinBoxJogPulse1;
    QLabel *label_37;
    QFrame *frame_2;
    QLabel *label_11;
    QLabel *label_12;
    QSpinBox *spinBoxAccel2;
    QSpinBox *spinBoxPulsePerRot2;
    QLabel *label_13;
    QSpinBox *spinBoxPitch2;
    QLabel *label_14;
    QSpinBox *spinBoxMaxVerocity2;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QSpinBox *spinBoxJogVerocity2;
    QLabel *label_18;
    QSpinBox *spinBoxOriginVelocity2;
    QLabel *label_19;
    QLabel *label_20;
    QSpinBox *spinBoxMaxPulse2;
    QSpinBox *spinBoxJogPulse2;
    QLabel *label_35;
    QLabel *label_32;
    QLabel *label_38;
    QFrame *frame_3;
    QLabel *label_21;
    QLabel *label_22;
    QSpinBox *spinBoxAccel3;
    QSpinBox *spinBoxPulsePerRot3;
    QLabel *label_23;
    QSpinBox *spinBoxPitch3;
    QLabel *label_24;
    QSpinBox *spinBoxMaxVerocity3;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QSpinBox *spinBoxJogVerocity3;
    QLabel *label_28;
    QSpinBox *spinBoxOriginVelocity3;
    QLabel *label_29;
    QLabel *label_30;
    QSpinBox *spinBoxMaxPulse3;
    QSpinBox *spinBoxJogPulse3;
    QLabel *label_36;
    QLabel *label_33;
    QLabel *label_39;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName(QString::fromUtf8("SettingDialog"));
        SettingDialog->resize(451, 661);
        frame = new QFrame(SettingDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 431, 191));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 431, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 30, 61, 21));
        spinBoxAccel1 = new QSpinBox(frame);
        spinBoxAccel1->setObjectName(QString::fromUtf8("spinBoxAccel1"));
        spinBoxAccel1->setGeometry(QRect(80, 30, 71, 22));
        spinBoxAccel1->setMaximum(99999999);
        spinBoxPulsePerRot1 = new QSpinBox(frame);
        spinBoxPulsePerRot1->setObjectName(QString::fromUtf8("spinBoxPulsePerRot1"));
        spinBoxPulsePerRot1->setGeometry(QRect(110, 60, 71, 22));
        spinBoxPulsePerRot1->setMaximum(99999999);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 60, 91, 21));
        spinBoxPitch1 = new QSpinBox(frame);
        spinBoxPitch1->setObjectName(QString::fromUtf8("spinBoxPitch1"));
        spinBoxPitch1->setGeometry(QRect(350, 60, 71, 22));
        spinBoxPitch1->setMaximum(99999999);
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(250, 60, 91, 21));
        spinBoxMaxVerocity1 = new QSpinBox(frame);
        spinBoxMaxVerocity1->setObjectName(QString::fromUtf8("spinBoxMaxVerocity1"));
        spinBoxMaxVerocity1->setGeometry(QRect(110, 90, 71, 22));
        spinBoxMaxVerocity1->setMaximum(99999999);
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 90, 71, 21));
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(190, 90, 71, 21));
        label_7 = new QLabel(frame);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 110, 71, 21));
        spinBoxJogVerocity1 = new QSpinBox(frame);
        spinBoxJogVerocity1->setObjectName(QString::fromUtf8("spinBoxJogVerocity1"));
        spinBoxJogVerocity1->setGeometry(QRect(110, 110, 71, 22));
        spinBoxJogVerocity1->setMaximum(99999999);
        label_8 = new QLabel(frame);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(190, 110, 71, 21));
        spinBoxOriginVelocity1 = new QSpinBox(frame);
        spinBoxOriginVelocity1->setObjectName(QString::fromUtf8("spinBoxOriginVelocity1"));
        spinBoxOriginVelocity1->setGeometry(QRect(110, 130, 71, 22));
        spinBoxOriginVelocity1->setMaximum(99999999);
        label_9 = new QLabel(frame);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 130, 81, 21));
        label_10 = new QLabel(frame);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(190, 130, 71, 21));
        spinBoxMaxPulse1 = new QSpinBox(frame);
        spinBoxMaxPulse1->setObjectName(QString::fromUtf8("spinBoxMaxPulse1"));
        spinBoxMaxPulse1->setGeometry(QRect(110, 160, 81, 22));
        spinBoxMaxPulse1->setMaximum(99999999);
        label_31 = new QLabel(frame);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(40, 160, 61, 21));
        label_34 = new QLabel(frame);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(270, 110, 71, 21));
        spinBoxJogPulse1 = new QSpinBox(frame);
        spinBoxJogPulse1->setObjectName(QString::fromUtf8("spinBoxJogPulse1"));
        spinBoxJogPulse1->setGeometry(QRect(350, 110, 71, 22));
        spinBoxJogPulse1->setMaximum(99999999);
        label_37 = new QLabel(frame);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setGeometry(QRect(200, 160, 71, 21));
        frame_2 = new QFrame(SettingDialog);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(10, 210, 431, 191));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_11 = new QLabel(frame_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(0, 0, 431, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_12 = new QLabel(frame_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 30, 61, 21));
        spinBoxAccel2 = new QSpinBox(frame_2);
        spinBoxAccel2->setObjectName(QString::fromUtf8("spinBoxAccel2"));
        spinBoxAccel2->setGeometry(QRect(80, 30, 71, 22));
        spinBoxAccel2->setMaximum(99999999);
        spinBoxPulsePerRot2 = new QSpinBox(frame_2);
        spinBoxPulsePerRot2->setObjectName(QString::fromUtf8("spinBoxPulsePerRot2"));
        spinBoxPulsePerRot2->setGeometry(QRect(110, 60, 71, 22));
        spinBoxPulsePerRot2->setMaximum(99999999);
        label_13 = new QLabel(frame_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 60, 91, 21));
        spinBoxPitch2 = new QSpinBox(frame_2);
        spinBoxPitch2->setObjectName(QString::fromUtf8("spinBoxPitch2"));
        spinBoxPitch2->setGeometry(QRect(350, 60, 71, 22));
        spinBoxPitch2->setMaximum(99999999);
        label_14 = new QLabel(frame_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(250, 60, 91, 21));
        spinBoxMaxVerocity2 = new QSpinBox(frame_2);
        spinBoxMaxVerocity2->setObjectName(QString::fromUtf8("spinBoxMaxVerocity2"));
        spinBoxMaxVerocity2->setGeometry(QRect(110, 90, 71, 22));
        spinBoxMaxVerocity2->setMaximum(99999999);
        label_15 = new QLabel(frame_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(30, 90, 71, 21));
        label_16 = new QLabel(frame_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(190, 90, 71, 21));
        label_17 = new QLabel(frame_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(30, 110, 71, 21));
        spinBoxJogVerocity2 = new QSpinBox(frame_2);
        spinBoxJogVerocity2->setObjectName(QString::fromUtf8("spinBoxJogVerocity2"));
        spinBoxJogVerocity2->setGeometry(QRect(110, 110, 71, 22));
        spinBoxJogVerocity2->setMaximum(99999999);
        label_18 = new QLabel(frame_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(190, 110, 71, 21));
        spinBoxOriginVelocity2 = new QSpinBox(frame_2);
        spinBoxOriginVelocity2->setObjectName(QString::fromUtf8("spinBoxOriginVelocity2"));
        spinBoxOriginVelocity2->setGeometry(QRect(110, 130, 71, 22));
        spinBoxOriginVelocity2->setMaximum(99999999);
        label_19 = new QLabel(frame_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(30, 130, 81, 21));
        label_20 = new QLabel(frame_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(190, 130, 71, 21));
        spinBoxMaxPulse2 = new QSpinBox(frame_2);
        spinBoxMaxPulse2->setObjectName(QString::fromUtf8("spinBoxMaxPulse2"));
        spinBoxMaxPulse2->setGeometry(QRect(110, 160, 81, 22));
        spinBoxMaxPulse2->setMaximum(99999999);
        spinBoxJogPulse2 = new QSpinBox(frame_2);
        spinBoxJogPulse2->setObjectName(QString::fromUtf8("spinBoxJogPulse2"));
        spinBoxJogPulse2->setGeometry(QRect(350, 110, 71, 22));
        spinBoxJogPulse2->setMaximum(99999999);
        label_35 = new QLabel(frame_2);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setGeometry(QRect(270, 110, 71, 21));
        label_32 = new QLabel(frame_2);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(40, 160, 61, 21));
        label_38 = new QLabel(frame_2);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setGeometry(QRect(200, 160, 71, 21));
        frame_3 = new QFrame(SettingDialog);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(10, 410, 431, 191));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_21 = new QLabel(frame_3);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(0, 0, 431, 21));
        label_21->setFrameShape(QFrame::Panel);
        label_21->setFrameShadow(QFrame::Sunken);
        label_22 = new QLabel(frame_3);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(10, 30, 61, 21));
        spinBoxAccel3 = new QSpinBox(frame_3);
        spinBoxAccel3->setObjectName(QString::fromUtf8("spinBoxAccel3"));
        spinBoxAccel3->setGeometry(QRect(80, 30, 71, 22));
        spinBoxAccel3->setMaximum(99999999);
        spinBoxPulsePerRot3 = new QSpinBox(frame_3);
        spinBoxPulsePerRot3->setObjectName(QString::fromUtf8("spinBoxPulsePerRot3"));
        spinBoxPulsePerRot3->setGeometry(QRect(110, 60, 71, 22));
        spinBoxPulsePerRot3->setMaximum(99999999);
        label_23 = new QLabel(frame_3);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(10, 60, 91, 21));
        spinBoxPitch3 = new QSpinBox(frame_3);
        spinBoxPitch3->setObjectName(QString::fromUtf8("spinBoxPitch3"));
        spinBoxPitch3->setGeometry(QRect(350, 60, 71, 22));
        spinBoxPitch3->setMaximum(99999999);
        label_24 = new QLabel(frame_3);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(250, 60, 91, 21));
        spinBoxMaxVerocity3 = new QSpinBox(frame_3);
        spinBoxMaxVerocity3->setObjectName(QString::fromUtf8("spinBoxMaxVerocity3"));
        spinBoxMaxVerocity3->setGeometry(QRect(110, 90, 71, 22));
        spinBoxMaxVerocity3->setMaximum(99999999);
        label_25 = new QLabel(frame_3);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(30, 90, 71, 21));
        label_26 = new QLabel(frame_3);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(190, 90, 71, 21));
        label_27 = new QLabel(frame_3);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(30, 110, 71, 21));
        spinBoxJogVerocity3 = new QSpinBox(frame_3);
        spinBoxJogVerocity3->setObjectName(QString::fromUtf8("spinBoxJogVerocity3"));
        spinBoxJogVerocity3->setGeometry(QRect(110, 110, 71, 22));
        spinBoxJogVerocity3->setMaximum(99999999);
        label_28 = new QLabel(frame_3);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(190, 110, 71, 21));
        spinBoxOriginVelocity3 = new QSpinBox(frame_3);
        spinBoxOriginVelocity3->setObjectName(QString::fromUtf8("spinBoxOriginVelocity3"));
        spinBoxOriginVelocity3->setGeometry(QRect(110, 130, 71, 22));
        spinBoxOriginVelocity3->setMaximum(99999999);
        label_29 = new QLabel(frame_3);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(30, 130, 81, 21));
        label_30 = new QLabel(frame_3);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(190, 130, 71, 21));
        spinBoxMaxPulse3 = new QSpinBox(frame_3);
        spinBoxMaxPulse3->setObjectName(QString::fromUtf8("spinBoxMaxPulse3"));
        spinBoxMaxPulse3->setGeometry(QRect(110, 160, 81, 22));
        spinBoxMaxPulse3->setMaximum(99999999);
        spinBoxJogPulse3 = new QSpinBox(frame_3);
        spinBoxJogPulse3->setObjectName(QString::fromUtf8("spinBoxJogPulse3"));
        spinBoxJogPulse3->setGeometry(QRect(350, 110, 71, 22));
        spinBoxJogPulse3->setMaximum(99999999);
        label_36 = new QLabel(frame_3);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setGeometry(QRect(270, 110, 71, 21));
        label_33 = new QLabel(frame_3);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(40, 160, 61, 21));
        label_39 = new QLabel(frame_3);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setGeometry(QRect(200, 160, 71, 21));
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(140, 620, 75, 31));
        pushButtonOK->setDefault(true);
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(240, 620, 75, 31));

        retranslateUi(SettingDialog);

        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QApplication::translate("SettingDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SettingDialog", "Axis - 1", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SettingDialog", "Accelrate", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SettingDialog", "Pulse/Rotation", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SettingDialog", "Pitch (mm/Rot)", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SettingDialog", "Max velocity", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("SettingDialog", "mm/sec", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("SettingDialog", "JOG velocity", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("SettingDialog", "mm/sec", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("SettingDialog", "Origin velocity", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("SettingDialog", "mm/sec", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("SettingDialog", "MaxLength", 0, QApplication::UnicodeUTF8));
        label_34->setText(QApplication::translate("SettingDialog", "JOG Pulse", 0, QApplication::UnicodeUTF8));
        label_37->setText(QApplication::translate("SettingDialog", "mm", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("SettingDialog", "Axis - 2", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("SettingDialog", "Accelrate", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("SettingDialog", "Pulse/Rotation", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("SettingDialog", "Pitch (mm/Rot)", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("SettingDialog", "Max velocity", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("SettingDialog", "mm/sec", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("SettingDialog", "JOG velocity", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("SettingDialog", "mm/sec", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("SettingDialog", "Origin velocity", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("SettingDialog", "mm/sec", 0, QApplication::UnicodeUTF8));
        label_35->setText(QApplication::translate("SettingDialog", "JOG Pulse", 0, QApplication::UnicodeUTF8));
        label_32->setText(QApplication::translate("SettingDialog", "MaxLength", 0, QApplication::UnicodeUTF8));
        label_38->setText(QApplication::translate("SettingDialog", "mm", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("SettingDialog", "Axis - 3", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("SettingDialog", "Accelrate", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("SettingDialog", "Pulse/Rotation", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("SettingDialog", "Pitch (mm/Rot)", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("SettingDialog", "Max velocity", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("SettingDialog", "mm/sec", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("SettingDialog", "JOG velocity", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("SettingDialog", "mm/sec", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("SettingDialog", "Origin velocity", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("SettingDialog", "mm/sec", 0, QApplication::UnicodeUTF8));
        label_36->setText(QApplication::translate("SettingDialog", "JOG Pulse", 0, QApplication::UnicodeUTF8));
        label_33->setText(QApplication::translate("SettingDialog", "MaxLength", 0, QApplication::UnicodeUTF8));
        label_39->setText(QApplication::translate("SettingDialog", "mm", 0, QApplication::UnicodeUTF8));
        pushButtonOK->setText(QApplication::translate("SettingDialog", "OK", 0, QApplication::UnicodeUTF8));
        pushButtonCancel->setText(QApplication::translate("SettingDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
