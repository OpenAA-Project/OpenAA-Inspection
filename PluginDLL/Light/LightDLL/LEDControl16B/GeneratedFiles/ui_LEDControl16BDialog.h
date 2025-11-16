/********************************************************************************
** Form generated from reading UI file 'LEDControl16BDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEDCONTROL16BDIALOG_H
#define UI_LEDCONTROL16BDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LEDControl16BDialog
{
public:
    QFrame *frame;
    QToolButton *toolButtonRed;
    QFrame *frame_3;
    QPushButton *pushButtonTransfer;
    QProgressBar *progressBar;
    QSpinBox *spinBoxBrightness;
    QLabel *label_2;
    QPushButton *pushButtonSetAll;
    QToolButton *toolButtonON;
    QPushButton *pushButtonWriteEPROM;
    QPushButton *pushButtonShowIO;
    QPushButton *pushButtonDefinition;
    QPushButton *pushButtonShowAD;
    QFrame *frameManual;
    QToolButton *toolButtonManual;
    QSpinBox *spinBoxVolume;
    QPushButton *pushButtonReqVolume;
    QPushButton *pushButtonShowSpecial;
    QLineEdit *lineEditVersion;
    QPushButton *pushButtonOK;
    QStackedWidget *stackedWidgetSetting;
    QWidget *page;
    QWidget *page_3;
    QWidget *page_4;
    QWidget *page_5;
    QWidget *page_6;
    QWidget *page_7;
    QWidget *page_8;
    QWidget *page_9;
    QWidget *page_10;
    QWidget *page_2;
    QWidget *page_11;
    QWidget *page_12;
    QWidget *page_13;
    QWidget *page_14;
    QWidget *page_15;
    QWidget *page_16;

    void setupUi(QDialog *LEDControl16BDialog)
    {
        if (LEDControl16BDialog->objectName().isEmpty())
            LEDControl16BDialog->setObjectName("LEDControl16BDialog");
        LEDControl16BDialog->resize(657, 757);
        frame = new QFrame(LEDControl16BDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 40, 631, 51));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        toolButtonRed = new QToolButton(frame);
        toolButtonRed->setObjectName("toolButtonRed");
        toolButtonRed->setGeometry(QRect(10, 10, 101, 31));
        toolButtonRed->setCheckable(true);
        toolButtonRed->setChecked(true);
        toolButtonRed->setAutoExclusive(true);
        frame_3 = new QFrame(LEDControl16BDialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(440, 100, 201, 571));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        pushButtonTransfer = new QPushButton(frame_3);
        pushButtonTransfer->setObjectName("pushButtonTransfer");
        pushButtonTransfer->setGeometry(QRect(10, 120, 93, 41));
        progressBar = new QProgressBar(frame_3);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(10, 170, 171, 23));
        progressBar->setValue(24);
        spinBoxBrightness = new QSpinBox(frame_3);
        spinBoxBrightness->setObjectName("spinBoxBrightness");
        spinBoxBrightness->setGeometry(QRect(70, 20, 71, 22));
        spinBoxBrightness->setMaximum(1023);
        spinBoxBrightness->setValue(1000);
        label_2 = new QLabel(frame_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 20, 51, 21));
        pushButtonSetAll = new QPushButton(frame_3);
        pushButtonSetAll->setObjectName("pushButtonSetAll");
        pushButtonSetAll->setGeometry(QRect(30, 60, 141, 41));
        toolButtonON = new QToolButton(frame_3);
        toolButtonON->setObjectName("toolButtonON");
        toolButtonON->setGeometry(QRect(10, 220, 181, 61));
        toolButtonON->setCheckable(true);
        toolButtonON->setChecked(true);
        pushButtonWriteEPROM = new QPushButton(frame_3);
        pushButtonWriteEPROM->setObjectName("pushButtonWriteEPROM");
        pushButtonWriteEPROM->setGeometry(QRect(10, 410, 181, 28));
        pushButtonShowIO = new QPushButton(frame_3);
        pushButtonShowIO->setObjectName("pushButtonShowIO");
        pushButtonShowIO->setGeometry(QRect(10, 440, 181, 28));
        pushButtonDefinition = new QPushButton(frame_3);
        pushButtonDefinition->setObjectName("pushButtonDefinition");
        pushButtonDefinition->setGeometry(QRect(10, 370, 181, 28));
        pushButtonShowAD = new QPushButton(frame_3);
        pushButtonShowAD->setObjectName("pushButtonShowAD");
        pushButtonShowAD->setGeometry(QRect(10, 470, 181, 28));
        frameManual = new QFrame(frame_3);
        frameManual->setObjectName("frameManual");
        frameManual->setGeometry(QRect(10, 290, 181, 71));
        frameManual->setFrameShape(QFrame::StyledPanel);
        frameManual->setFrameShadow(QFrame::Raised);
        toolButtonManual = new QToolButton(frameManual);
        toolButtonManual->setObjectName("toolButtonManual");
        toolButtonManual->setGeometry(QRect(0, 3, 181, 31));
        toolButtonManual->setCheckable(true);
        spinBoxVolume = new QSpinBox(frameManual);
        spinBoxVolume->setObjectName("spinBoxVolume");
        spinBoxVolume->setGeometry(QRect(10, 40, 61, 31));
        spinBoxVolume->setMaximum(999999);
        pushButtonReqVolume = new QPushButton(frameManual);
        pushButtonReqVolume->setObjectName("pushButtonReqVolume");
        pushButtonReqVolume->setGeometry(QRect(80, 40, 81, 31));
        pushButtonShowSpecial = new QPushButton(frame_3);
        pushButtonShowSpecial->setObjectName("pushButtonShowSpecial");
        pushButtonShowSpecial->setGeometry(QRect(10, 530, 181, 28));
        lineEditVersion = new QLineEdit(LEDControl16BDialog);
        lineEditVersion->setObjectName("lineEditVersion");
        lineEditVersion->setGeometry(QRect(10, 0, 631, 21));
        pushButtonOK = new QPushButton(LEDControl16BDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(270, 690, 101, 41));
        stackedWidgetSetting = new QStackedWidget(LEDControl16BDialog);
        stackedWidgetSetting->setObjectName("stackedWidgetSetting");
        stackedWidgetSetting->setGeometry(QRect(10, 100, 421, 571));
        stackedWidgetSetting->setFrameShape(QFrame::Panel);
        stackedWidgetSetting->setFrameShadow(QFrame::Sunken);
        page = new QWidget();
        page->setObjectName("page");
        stackedWidgetSetting->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        stackedWidgetSetting->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        stackedWidgetSetting->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        stackedWidgetSetting->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        stackedWidgetSetting->addWidget(page_6);
        page_7 = new QWidget();
        page_7->setObjectName("page_7");
        stackedWidgetSetting->addWidget(page_7);
        page_8 = new QWidget();
        page_8->setObjectName("page_8");
        stackedWidgetSetting->addWidget(page_8);
        page_9 = new QWidget();
        page_9->setObjectName("page_9");
        stackedWidgetSetting->addWidget(page_9);
        page_10 = new QWidget();
        page_10->setObjectName("page_10");
        stackedWidgetSetting->addWidget(page_10);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidgetSetting->addWidget(page_2);
        page_11 = new QWidget();
        page_11->setObjectName("page_11");
        stackedWidgetSetting->addWidget(page_11);
        page_12 = new QWidget();
        page_12->setObjectName("page_12");
        stackedWidgetSetting->addWidget(page_12);
        page_13 = new QWidget();
        page_13->setObjectName("page_13");
        stackedWidgetSetting->addWidget(page_13);
        page_14 = new QWidget();
        page_14->setObjectName("page_14");
        stackedWidgetSetting->addWidget(page_14);
        page_15 = new QWidget();
        page_15->setObjectName("page_15");
        stackedWidgetSetting->addWidget(page_15);
        page_16 = new QWidget();
        page_16->setObjectName("page_16");
        stackedWidgetSetting->addWidget(page_16);

        retranslateUi(LEDControl16BDialog);

        stackedWidgetSetting->setCurrentIndex(15);


        QMetaObject::connectSlotsByName(LEDControl16BDialog);
    } // setupUi

    void retranslateUi(QDialog *LEDControl16BDialog)
    {
        LEDControl16BDialog->setWindowTitle(QCoreApplication::translate("LEDControl16BDialog", "Dialog", nullptr));
        toolButtonRed->setText(QCoreApplication::translate("LEDControl16BDialog", "Red", nullptr));
        pushButtonTransfer->setText(QCoreApplication::translate("LEDControl16BDialog", "Transfer", nullptr));
        label_2->setText(QCoreApplication::translate("LEDControl16BDialog", "Value", nullptr));
        pushButtonSetAll->setText(QCoreApplication::translate("LEDControl16BDialog", "Set all", nullptr));
        toolButtonON->setText(QCoreApplication::translate("LEDControl16BDialog", "ON", nullptr));
        pushButtonWriteEPROM->setText(QCoreApplication::translate("LEDControl16BDialog", "Write EPROM", nullptr));
        pushButtonShowIO->setText(QCoreApplication::translate("LEDControl16BDialog", "Show  I/O", nullptr));
        pushButtonDefinition->setText(QCoreApplication::translate("LEDControl16BDialog", "Set definition", nullptr));
        pushButtonShowAD->setText(QCoreApplication::translate("LEDControl16BDialog", "Show A/D", nullptr));
        toolButtonManual->setText(QCoreApplication::translate("LEDControl16BDialog", "Manual", nullptr));
        pushButtonReqVolume->setText(QCoreApplication::translate("LEDControl16BDialog", "Req", nullptr));
        pushButtonShowSpecial->setText(QCoreApplication::translate("LEDControl16BDialog", "Show Special", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("LEDControl16BDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LEDControl16BDialog: public Ui_LEDControl16BDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEDCONTROL16BDIALOG_H
