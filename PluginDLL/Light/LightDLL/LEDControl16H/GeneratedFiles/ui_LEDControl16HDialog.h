/********************************************************************************
** Form generated from reading UI file 'LEDControl16HDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEDCONTROL16HDIALOG_H
#define UI_LEDCONTROL16HDIALOG_H

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

class Ui_LEDControl16HDialog
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
    QPushButton *pushButtonSetTestLED;
    QPushButton *pushButtonOK;
    QFrame *frame;
    QToolButton *toolButtonRed;

    void setupUi(QDialog *LEDControl16HDialog)
    {
        if (LEDControl16HDialog->objectName().isEmpty())
            LEDControl16HDialog->setObjectName(QString::fromUtf8("LEDControl16HDialog"));
        LEDControl16HDialog->resize(654, 756);
        stackedWidgetSetting = new QStackedWidget(LEDControl16HDialog);
        stackedWidgetSetting->setObjectName(QString::fromUtf8("stackedWidgetSetting"));
        stackedWidgetSetting->setGeometry(QRect(10, 110, 421, 571));
        stackedWidgetSetting->setFrameShape(QFrame::Panel);
        stackedWidgetSetting->setFrameShadow(QFrame::Sunken);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidgetSetting->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        stackedWidgetSetting->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        stackedWidgetSetting->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        stackedWidgetSetting->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        stackedWidgetSetting->addWidget(page_6);
        page_7 = new QWidget();
        page_7->setObjectName(QString::fromUtf8("page_7"));
        stackedWidgetSetting->addWidget(page_7);
        page_8 = new QWidget();
        page_8->setObjectName(QString::fromUtf8("page_8"));
        stackedWidgetSetting->addWidget(page_8);
        page_9 = new QWidget();
        page_9->setObjectName(QString::fromUtf8("page_9"));
        stackedWidgetSetting->addWidget(page_9);
        page_10 = new QWidget();
        page_10->setObjectName(QString::fromUtf8("page_10"));
        stackedWidgetSetting->addWidget(page_10);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidgetSetting->addWidget(page_2);
        page_11 = new QWidget();
        page_11->setObjectName(QString::fromUtf8("page_11"));
        stackedWidgetSetting->addWidget(page_11);
        page_12 = new QWidget();
        page_12->setObjectName(QString::fromUtf8("page_12"));
        stackedWidgetSetting->addWidget(page_12);
        page_13 = new QWidget();
        page_13->setObjectName(QString::fromUtf8("page_13"));
        stackedWidgetSetting->addWidget(page_13);
        page_14 = new QWidget();
        page_14->setObjectName(QString::fromUtf8("page_14"));
        stackedWidgetSetting->addWidget(page_14);
        page_15 = new QWidget();
        page_15->setObjectName(QString::fromUtf8("page_15"));
        stackedWidgetSetting->addWidget(page_15);
        page_16 = new QWidget();
        page_16->setObjectName(QString::fromUtf8("page_16"));
        stackedWidgetSetting->addWidget(page_16);
        lineEditVersion = new QLineEdit(LEDControl16HDialog);
        lineEditVersion->setObjectName(QString::fromUtf8("lineEditVersion"));
        lineEditVersion->setGeometry(QRect(10, 10, 631, 21));
        frame_3 = new QFrame(LEDControl16HDialog);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(440, 110, 201, 571));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        pushButtonTransfer = new QPushButton(frame_3);
        pushButtonTransfer->setObjectName(QString::fromUtf8("pushButtonTransfer"));
        pushButtonTransfer->setGeometry(QRect(10, 120, 93, 41));
        progressBar = new QProgressBar(frame_3);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 170, 171, 23));
        progressBar->setValue(24);
        spinBoxBrightness = new QSpinBox(frame_3);
        spinBoxBrightness->setObjectName(QString::fromUtf8("spinBoxBrightness"));
        spinBoxBrightness->setGeometry(QRect(70, 20, 91, 22));
        spinBoxBrightness->setMaximum(1000000);
        spinBoxBrightness->setValue(15000);
        label_2 = new QLabel(frame_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 20, 51, 21));
        pushButtonSetAll = new QPushButton(frame_3);
        pushButtonSetAll->setObjectName(QString::fromUtf8("pushButtonSetAll"));
        pushButtonSetAll->setGeometry(QRect(30, 60, 141, 41));
        toolButtonON = new QToolButton(frame_3);
        toolButtonON->setObjectName(QString::fromUtf8("toolButtonON"));
        toolButtonON->setGeometry(QRect(10, 220, 181, 61));
        toolButtonON->setCheckable(true);
        toolButtonON->setChecked(true);
        pushButtonShowIO = new QPushButton(frame_3);
        pushButtonShowIO->setObjectName(QString::fromUtf8("pushButtonShowIO"));
        pushButtonShowIO->setGeometry(QRect(10, 420, 181, 41));
        pushButtonDefinition = new QPushButton(frame_3);
        pushButtonDefinition->setObjectName(QString::fromUtf8("pushButtonDefinition"));
        pushButtonDefinition->setGeometry(QRect(10, 370, 181, 41));
        frameManual = new QFrame(frame_3);
        frameManual->setObjectName(QString::fromUtf8("frameManual"));
        frameManual->setGeometry(QRect(10, 290, 181, 71));
        frameManual->setFrameShape(QFrame::StyledPanel);
        frameManual->setFrameShadow(QFrame::Raised);
        pushButtonSetTestLED = new QPushButton(frame_3);
        pushButtonSetTestLED->setObjectName(QString::fromUtf8("pushButtonSetTestLED"));
        pushButtonSetTestLED->setGeometry(QRect(30, 500, 141, 41));
        pushButtonSetTestLED->setCheckable(true);
        pushButtonSetTestLED->setChecked(false);
        pushButtonOK = new QPushButton(LEDControl16HDialog);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(270, 700, 101, 41));
        frame = new QFrame(LEDControl16HDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 50, 631, 51));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        toolButtonRed = new QToolButton(frame);
        toolButtonRed->setObjectName(QString::fromUtf8("toolButtonRed"));
        toolButtonRed->setGeometry(QRect(10, 10, 101, 31));
        toolButtonRed->setCheckable(true);
        toolButtonRed->setChecked(true);
        toolButtonRed->setAutoExclusive(true);

        retranslateUi(LEDControl16HDialog);

        stackedWidgetSetting->setCurrentIndex(15);


        QMetaObject::connectSlotsByName(LEDControl16HDialog);
    } // setupUi

    void retranslateUi(QDialog *LEDControl16HDialog)
    {
        LEDControl16HDialog->setWindowTitle(QCoreApplication::translate("LEDControl16HDialog", "Dialog", nullptr));
        pushButtonTransfer->setText(QCoreApplication::translate("LEDControl16HDialog", "Transfer", nullptr));
        label_2->setText(QCoreApplication::translate("LEDControl16HDialog", "Value", nullptr));
        pushButtonSetAll->setText(QCoreApplication::translate("LEDControl16HDialog", "Set all", nullptr));
        toolButtonON->setText(QCoreApplication::translate("LEDControl16HDialog", "ON", nullptr));
        pushButtonShowIO->setText(QCoreApplication::translate("LEDControl16HDialog", "Show  I/O", nullptr));
        pushButtonDefinition->setText(QCoreApplication::translate("LEDControl16HDialog", "Set definition", nullptr));
        pushButtonSetTestLED->setText(QCoreApplication::translate("LEDControl16HDialog", "TestLED", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("LEDControl16HDialog", "OK", nullptr));
        toolButtonRed->setText(QCoreApplication::translate("LEDControl16HDialog", "Red", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LEDControl16HDialog: public Ui_LEDControl16HDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEDCONTROL16HDIALOG_H
