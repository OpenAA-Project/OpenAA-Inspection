/********************************************************************************
** Form generated from reading UI file 'RunnerObjSettingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUNNEROBJSETTINGFORM_H
#define UI_RUNNEROBJSETTINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_RunnerObjSettingForm
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEditUniqueName;
    QLineEdit *lineEditRemark;
    QPushButton *pushButtonSetting;
    QFrame *frame;
    QToolButton *toolButtonPosInputTop;
    QToolButton *toolButtonPosInputLeft;
    QToolButton *toolButtonPosInputRight;
    QToolButton *toolButtonPosInputBottom;
    QLabel *label_3;
    QFrame *frame_2;
    QToolButton *toolButtonPosOutputTop;
    QToolButton *toolButtonPosOutputLeft;
    QToolButton *toolButtonPosOutputRight;
    QToolButton *toolButtonPosOutputBottom;
    QLabel *label_4;
    QLineEdit *lineEditDLLRoot;
    QLabel *label_5;
    QLineEdit *lineEditDLLName;
    QLabel *label_6;
    QPushButton *pushButtonDelete;

    void setupUi(QDialog *RunnerObjSettingForm)
    {
        if (RunnerObjSettingForm->objectName().isEmpty())
            RunnerObjSettingForm->setObjectName("RunnerObjSettingForm");
        RunnerObjSettingForm->resize(352, 320);
        pushButtonOK = new QPushButton(RunnerObjSettingForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(140, 240, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(RunnerObjSettingForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(250, 240, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        label = new QLabel(RunnerObjSettingForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 50, 71, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(RunnerObjSettingForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 80, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        lineEditUniqueName = new QLineEdit(RunnerObjSettingForm);
        lineEditUniqueName->setObjectName("lineEditUniqueName");
        lineEditUniqueName->setGeometry(QRect(80, 50, 261, 20));
        lineEditRemark = new QLineEdit(RunnerObjSettingForm);
        lineEditRemark->setObjectName("lineEditRemark");
        lineEditRemark->setGeometry(QRect(80, 80, 261, 20));
        pushButtonSetting = new QPushButton(RunnerObjSettingForm);
        pushButtonSetting->setObjectName("pushButtonSetting");
        pushButtonSetting->setGeometry(QRect(10, 240, 101, 31));
        frame = new QFrame(RunnerObjSettingForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 110, 161, 111));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        toolButtonPosInputTop = new QToolButton(frame);
        toolButtonPosInputTop->setObjectName("toolButtonPosInputTop");
        toolButtonPosInputTop->setGeometry(QRect(60, 30, 41, 31));
        toolButtonPosInputTop->setCheckable(true);
        toolButtonPosInputTop->setAutoExclusive(true);
        toolButtonPosInputTop->setAutoRaise(false);
        toolButtonPosInputLeft = new QToolButton(frame);
        toolButtonPosInputLeft->setObjectName("toolButtonPosInputLeft");
        toolButtonPosInputLeft->setGeometry(QRect(10, 50, 41, 31));
        toolButtonPosInputLeft->setCheckable(true);
        toolButtonPosInputLeft->setChecked(true);
        toolButtonPosInputLeft->setAutoExclusive(true);
        toolButtonPosInputLeft->setAutoRaise(false);
        toolButtonPosInputRight = new QToolButton(frame);
        toolButtonPosInputRight->setObjectName("toolButtonPosInputRight");
        toolButtonPosInputRight->setGeometry(QRect(110, 50, 41, 31));
        toolButtonPosInputRight->setCheckable(true);
        toolButtonPosInputRight->setChecked(false);
        toolButtonPosInputRight->setAutoExclusive(true);
        toolButtonPosInputRight->setAutoRaise(false);
        toolButtonPosInputBottom = new QToolButton(frame);
        toolButtonPosInputBottom->setObjectName("toolButtonPosInputBottom");
        toolButtonPosInputBottom->setGeometry(QRect(60, 70, 41, 31));
        toolButtonPosInputBottom->setCheckable(true);
        toolButtonPosInputBottom->setAutoExclusive(true);
        toolButtonPosInputBottom->setAutoRaise(false);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 161, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        frame_2 = new QFrame(RunnerObjSettingForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(180, 110, 161, 111));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        toolButtonPosOutputTop = new QToolButton(frame_2);
        toolButtonPosOutputTop->setObjectName("toolButtonPosOutputTop");
        toolButtonPosOutputTop->setGeometry(QRect(60, 30, 41, 31));
        toolButtonPosOutputTop->setCheckable(true);
        toolButtonPosOutputTop->setAutoExclusive(true);
        toolButtonPosOutputTop->setAutoRaise(false);
        toolButtonPosOutputLeft = new QToolButton(frame_2);
        toolButtonPosOutputLeft->setObjectName("toolButtonPosOutputLeft");
        toolButtonPosOutputLeft->setGeometry(QRect(10, 50, 41, 31));
        toolButtonPosOutputLeft->setCheckable(true);
        toolButtonPosOutputLeft->setChecked(false);
        toolButtonPosOutputLeft->setAutoExclusive(true);
        toolButtonPosOutputLeft->setAutoRaise(false);
        toolButtonPosOutputRight = new QToolButton(frame_2);
        toolButtonPosOutputRight->setObjectName("toolButtonPosOutputRight");
        toolButtonPosOutputRight->setGeometry(QRect(110, 50, 41, 31));
        toolButtonPosOutputRight->setCheckable(true);
        toolButtonPosOutputRight->setChecked(true);
        toolButtonPosOutputRight->setAutoExclusive(true);
        toolButtonPosOutputRight->setAutoRaise(false);
        toolButtonPosOutputBottom = new QToolButton(frame_2);
        toolButtonPosOutputBottom->setObjectName("toolButtonPosOutputBottom");
        toolButtonPosOutputBottom->setGeometry(QRect(60, 70, 41, 31));
        toolButtonPosOutputBottom->setCheckable(true);
        toolButtonPosOutputBottom->setAutoExclusive(true);
        toolButtonPosOutputBottom->setAutoRaise(false);
        label_4 = new QLabel(frame_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 0, 161, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        lineEditDLLRoot = new QLineEdit(RunnerObjSettingForm);
        lineEditDLLRoot->setObjectName("lineEditDLLRoot");
        lineEditDLLRoot->setGeometry(QRect(80, 0, 201, 20));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(212, 208, 200, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditDLLRoot->setPalette(palette);
        lineEditDLLRoot->setReadOnly(true);
        label_5 = new QLabel(RunnerObjSettingForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 0, 71, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        lineEditDLLName = new QLineEdit(RunnerObjSettingForm);
        lineEditDLLName->setObjectName("lineEditDLLName");
        lineEditDLLName->setGeometry(QRect(80, 20, 201, 20));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditDLLName->setPalette(palette1);
        lineEditDLLName->setReadOnly(true);
        label_6 = new QLabel(RunnerObjSettingForm);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 20, 71, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        pushButtonDelete = new QPushButton(RunnerObjSettingForm);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(250, 280, 91, 31));

        retranslateUi(RunnerObjSettingForm);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(RunnerObjSettingForm);
    } // setupUi

    void retranslateUi(QDialog *RunnerObjSettingForm)
    {
        RunnerObjSettingForm->setWindowTitle(QCoreApplication::translate("RunnerObjSettingForm", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("RunnerObjSettingForm", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("RunnerObjSettingForm", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("RunnerObjSettingForm", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("RunnerObjSettingForm", "Remark", nullptr));
        pushButtonSetting->setText(QCoreApplication::translate("RunnerObjSettingForm", "Setting", nullptr));
        toolButtonPosInputTop->setText(QCoreApplication::translate("RunnerObjSettingForm", "Top", nullptr));
        toolButtonPosInputLeft->setText(QCoreApplication::translate("RunnerObjSettingForm", "Left", nullptr));
        toolButtonPosInputRight->setText(QCoreApplication::translate("RunnerObjSettingForm", "Right", nullptr));
        toolButtonPosInputBottom->setText(QCoreApplication::translate("RunnerObjSettingForm", "Bottom", nullptr));
        label_3->setText(QCoreApplication::translate("RunnerObjSettingForm", "Input position", nullptr));
        toolButtonPosOutputTop->setText(QCoreApplication::translate("RunnerObjSettingForm", "Top", nullptr));
        toolButtonPosOutputLeft->setText(QCoreApplication::translate("RunnerObjSettingForm", "Left", nullptr));
        toolButtonPosOutputRight->setText(QCoreApplication::translate("RunnerObjSettingForm", "Right", nullptr));
        toolButtonPosOutputBottom->setText(QCoreApplication::translate("RunnerObjSettingForm", "Bottom", nullptr));
        label_4->setText(QCoreApplication::translate("RunnerObjSettingForm", "Output position", nullptr));
        label_5->setText(QCoreApplication::translate("RunnerObjSettingForm", "DLL Root", nullptr));
        label_6->setText(QCoreApplication::translate("RunnerObjSettingForm", "DLL Name", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("RunnerObjSettingForm", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RunnerObjSettingForm: public Ui_RunnerObjSettingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUNNEROBJSETTINGFORM_H
