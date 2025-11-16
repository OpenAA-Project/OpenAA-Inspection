/********************************************************************************
** Form generated from reading UI file 'LEDControl16FDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEDCONTROL16FDIALOG_H
#define UI_LEDCONTROL16FDIALOG_H

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

class Ui_LEDControl16FDialog
{
public:
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
    QLineEdit *lineEditVersion;
    QFrame *frame_3;
    QPushButton *pushButtonTransfer;
    QProgressBar *progressBar;
    QSpinBox *spinBoxBrightness;
    QLabel *label_2;
    QPushButton *pushButtonSetAll;
    QToolButton *toolButtonON;
    QPushButton *pushButtonShowIO;
    QPushButton *pushButtonDefinition;
    QFrame *frameManual;
    QPushButton *pushButtonOK;
    QFrame *frame;
    QToolButton *toolButtonRed;

    void setupUi(QDialog *LEDControl16FDialog)
    {
        if (LEDControl16FDialog->objectName().isEmpty())
            LEDControl16FDialog->setObjectName("LEDControl16FDialog");
        LEDControl16FDialog->resize(654, 756);
        stackedWidgetSetting = new QStackedWidget(LEDControl16FDialog);
        stackedWidgetSetting->setObjectName("stackedWidgetSetting");
        stackedWidgetSetting->setGeometry(QRect(10, 110, 421, 571));
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
        lineEditVersion = new QLineEdit(LEDControl16FDialog);
        lineEditVersion->setObjectName("lineEditVersion");
        lineEditVersion->setGeometry(QRect(10, 10, 631, 21));
        frame_3 = new QFrame(LEDControl16FDialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(440, 110, 201, 571));
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
        spinBoxBrightness->setGeometry(QRect(70, 20, 91, 22));
        spinBoxBrightness->setMaximum(1000000);
        spinBoxBrightness->setValue(15000);
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
        pushButtonShowIO = new QPushButton(frame_3);
        pushButtonShowIO->setObjectName("pushButtonShowIO");
        pushButtonShowIO->setGeometry(QRect(10, 420, 181, 41));
        pushButtonDefinition = new QPushButton(frame_3);
        pushButtonDefinition->setObjectName("pushButtonDefinition");
        pushButtonDefinition->setGeometry(QRect(10, 370, 181, 41));
        frameManual = new QFrame(frame_3);
        frameManual->setObjectName("frameManual");
        frameManual->setGeometry(QRect(10, 290, 181, 71));
        frameManual->setFrameShape(QFrame::StyledPanel);
        frameManual->setFrameShadow(QFrame::Raised);
        pushButtonOK = new QPushButton(LEDControl16FDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(270, 700, 101, 41));
        frame = new QFrame(LEDControl16FDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 50, 631, 51));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        toolButtonRed = new QToolButton(frame);
        toolButtonRed->setObjectName("toolButtonRed");
        toolButtonRed->setGeometry(QRect(10, 10, 101, 31));
        toolButtonRed->setCheckable(true);
        toolButtonRed->setChecked(true);
        toolButtonRed->setAutoExclusive(true);

        retranslateUi(LEDControl16FDialog);

        stackedWidgetSetting->setCurrentIndex(15);


        QMetaObject::connectSlotsByName(LEDControl16FDialog);
    } // setupUi

    void retranslateUi(QDialog *LEDControl16FDialog)
    {
        LEDControl16FDialog->setWindowTitle(QCoreApplication::translate("LEDControl16FDialog", "Dialog", nullptr));
        pushButtonTransfer->setText(QCoreApplication::translate("LEDControl16FDialog", "Transfer", nullptr));
        label_2->setText(QCoreApplication::translate("LEDControl16FDialog", "Value", nullptr));
        pushButtonSetAll->setText(QCoreApplication::translate("LEDControl16FDialog", "Set all", nullptr));
        toolButtonON->setText(QCoreApplication::translate("LEDControl16FDialog", "ON", nullptr));
        pushButtonShowIO->setText(QCoreApplication::translate("LEDControl16FDialog", "Show  I/O", nullptr));
        pushButtonDefinition->setText(QCoreApplication::translate("LEDControl16FDialog", "Set definition", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("LEDControl16FDialog", "OK", nullptr));
        toolButtonRed->setText(QCoreApplication::translate("LEDControl16FDialog", "Red", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LEDControl16FDialog: public Ui_LEDControl16FDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEDCONTROL16FDIALOG_H
