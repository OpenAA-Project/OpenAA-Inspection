/********************************************************************************
** Form generated from reading UI file 'FormCommSetting.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCOMMSETTING_H
#define UI_FORMCOMMSETTING_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormCommSetting
{
public:
    QFrame *frame;
    QFrame *frame_3;
    QLabel *label_5;
    QFrame *frameAccessInfo;
    QFrame *frame_4;
    QFrame *frameCameraMap;
    QLabel *labelForPC;
    QLabel *label_4;
    QSpinBox *SpinBoxSlaveID;
    QLabel *label_3;
    QSpinBox *SpinBoxMaxSlaveNumb;
    QFrame *frameForSlave;
    QLabel *label_6;
    QSpinBox *SpinBoxThisCamCount;
    QCheckBox *CheckBoxMastered;
    QPushButton *OKButton;
    QPushButton *CancelButton;
    QPushButton *pushButtonShowCommError;

    void setupUi(QWidget *FormCommSetting)
    {
        if (FormCommSetting->objectName().isEmpty())
            FormCommSetting->setObjectName("FormCommSetting");
        FormCommSetting->resize(479, 474);
        frame = new QFrame(FormCommSetting);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 461, 401));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        frame_3 = new QFrame(frame);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 130, 291, 261));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 0, 291, 22));
        label_5->setFrameShape(QFrame::StyledPanel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameAccessInfo = new QFrame(frame_3);
        frameAccessInfo->setObjectName("frameAccessInfo");
        frameAccessInfo->setGeometry(QRect(0, 20, 291, 241));
        frameAccessInfo->setFrameShape(QFrame::NoFrame);
        frameAccessInfo->setFrameShadow(QFrame::Raised);
        frame_4 = new QFrame(frame);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(310, 130, 141, 261));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Sunken);
        frameCameraMap = new QFrame(frame_4);
        frameCameraMap->setObjectName("frameCameraMap");
        frameCameraMap->setGeometry(QRect(0, 20, 141, 241));
        frameCameraMap->setFrameShape(QFrame::NoFrame);
        frameCameraMap->setFrameShadow(QFrame::Raised);
        labelForPC = new QLabel(frame_4);
        labelForPC->setObjectName("labelForPC");
        labelForPC->setGeometry(QRect(0, 0, 141, 22));
        labelForPC->setFrameShape(QFrame::StyledPanel);
        labelForPC->setFrameShadow(QFrame::Sunken);
        labelForPC->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 70, 141, 22));
        label_4->setFrameShape(QFrame::StyledPanel);
        label_4->setFrameShadow(QFrame::Sunken);
        SpinBoxSlaveID = new QSpinBox(frame);
        SpinBoxSlaveID->setObjectName("SpinBoxSlaveID");
        SpinBoxSlaveID->setGeometry(QRect(170, 70, 46, 22));
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 40, 141, 22));
        label_3->setFrameShape(QFrame::StyledPanel);
        label_3->setFrameShadow(QFrame::Sunken);
        SpinBoxMaxSlaveNumb = new QSpinBox(frame);
        SpinBoxMaxSlaveNumb->setObjectName("SpinBoxMaxSlaveNumb");
        SpinBoxMaxSlaveNumb->setGeometry(QRect(170, 40, 46, 22));
        frameForSlave = new QFrame(frame);
        frameForSlave->setObjectName("frameForSlave");
        frameForSlave->setGeometry(QRect(220, 10, 201, 91));
        frameForSlave->setFrameShape(QFrame::StyledPanel);
        frameForSlave->setFrameShadow(QFrame::Raised);
        label_6 = new QLabel(frameForSlave);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 30, 181, 22));
        label_6->setFrameShape(QFrame::StyledPanel);
        label_6->setFrameShadow(QFrame::Sunken);
        SpinBoxThisCamCount = new QSpinBox(frameForSlave);
        SpinBoxThisCamCount->setObjectName("SpinBoxThisCamCount");
        SpinBoxThisCamCount->setGeometry(QRect(90, 60, 51, 22));
        CheckBoxMastered = new QCheckBox(frame);
        CheckBoxMastered->setObjectName("CheckBoxMastered");
        CheckBoxMastered->setGeometry(QRect(20, 10, 191, 18));
        CheckBoxMastered->setChecked(true);
        OKButton = new QPushButton(FormCommSetting);
        OKButton->setObjectName("OKButton");
        OKButton->setGeometry(QRect(20, 420, 111, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        OKButton->setIcon(icon);
        CancelButton = new QPushButton(FormCommSetting);
        CancelButton->setObjectName("CancelButton");
        CancelButton->setGeometry(QRect(340, 420, 111, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        CancelButton->setIcon(icon1);
        pushButtonShowCommError = new QPushButton(FormCommSetting);
        pushButtonShowCommError->setObjectName("pushButtonShowCommError");
        pushButtonShowCommError->setGeometry(QRect(170, 420, 151, 41));

        retranslateUi(FormCommSetting);

        QMetaObject::connectSlotsByName(FormCommSetting);
    } // setupUi

    void retranslateUi(QWidget *FormCommSetting)
    {
        FormCommSetting->setWindowTitle(QCoreApplication::translate("FormCommSetting", "Form", nullptr));
        label_5->setText(QCoreApplication::translate("FormCommSetting", "Access Information", nullptr));
        labelForPC->setText(QCoreApplication::translate("FormCommSetting", "Camera map", nullptr));
        label_4->setText(QCoreApplication::translate("FormCommSetting", "This computer ID (0-XX)", nullptr));
        label_3->setText(QCoreApplication::translate("FormCommSetting", "Connected computers", nullptr));
        label_6->setText(QCoreApplication::translate("FormCommSetting", "Camera counts in this SlavePC", nullptr));
        CheckBoxMastered->setText(QCoreApplication::translate("FormCommSetting", "This is Master Computer", nullptr));
        OKButton->setText(QCoreApplication::translate("FormCommSetting", "OK", nullptr));
        CancelButton->setText(QCoreApplication::translate("FormCommSetting", "Cancel", nullptr));
        pushButtonShowCommError->setText(QCoreApplication::translate("FormCommSetting", "Show comm error", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormCommSetting: public Ui_FormCommSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCOMMSETTING_H
