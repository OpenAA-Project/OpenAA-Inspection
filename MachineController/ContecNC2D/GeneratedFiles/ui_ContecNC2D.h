/********************************************************************************
** Form generated from reading UI file 'ContecNC2D.ui'
**
** Created: Thu May 14 11:22:55 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTECNC2D_H
#define UI_CONTECNC2D_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QToolButton>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_ContecNC2DClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonGoOrigin;
    QFrame *frame;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBoxStartPosX;
    QSpinBox *spinBoxStartPosY;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *spinBoxStartVelocity;
    QLabel *label_6;
    QSpinBox *spinBoxAccel;
    QLabel *label_7;
    QSpinBox *spinBoxScanPulse;
    QLabel *label_8;
    QSpinBox *spinBoxScanVelocity;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QSpinBox *spinBoxStepPulse;
    QSpinBox *spinBoxStepVelocity;
    QLabel *label_12;
    QSpinBox *spinBoxScanCount;
    QLabel *label_13;
    QSpinBox *spinBoxCurrentScan;
    QLabel *label_14;
    QLabel *label_18;
    QLabel *label_19;
    QSpinBox *spinBoxOriginVelocity;
    QLabel *label_20;
    QSpinBox *spinBoxMaxPulseX;
    QSpinBox *spinBoxMaxPulseY;
    QLabel *label_21;
    QLabel *label_22;
    QPushButton *pushButtonGoStartPos;
    QPushButton *pushButtonStartScan;
    QFrame *frame_2;
    QLabel *label_15;
    QSpinBox *spinBoxBoardSizeX;
    QLabel *label_16;
    QLabel *label_17;
    QSpinBox *spinBoxBoardSizeY;
    QLabel *label_26;
    QSpinBox *spinBoxSpaceY;
    QPushButton *pushButtonConvertToScan;
    QPushButton *pushButtonJogXP;
    QPushButton *pushButtonJogXM;
    QPushButton *pushButtonJogYP;
    QPushButton *pushButtonJogYM;
    QPushButton *pushButtonSave;
    QToolButton *toolButtonVacuum;
    QToolButton *toolButtonPatlightR;
    QToolButton *toolButtonPatlightY;
    QToolButton *toolButtonPatlightG;
    QCheckBox *checkBoxStartButtonL;
    QCheckBox *checkBoxStartButtonR;
    QCheckBox *checkBoxFootSW;
    QCheckBox *checkBoxAreaSensor;
    QPushButton *pushButtonStop;
    QCheckBox *checkBoxEmergency;
    QSpinBox *spinBoxCurrentPulseX;
    QLabel *label_23;
    QLabel *label_24;
    QSpinBox *spinBoxCurrentPulseY;
    QLabel *label_25;

    void setupUi(QMainWindow *ContecNC2DClass)
    {
        if (ContecNC2DClass->objectName().isEmpty())
            ContecNC2DClass->setObjectName(QString::fromUtf8("ContecNC2DClass"));
        ContecNC2DClass->resize(705, 527);
        centralWidget = new QWidget(ContecNC2DClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButtonGoOrigin = new QPushButton(centralWidget);
        pushButtonGoOrigin->setObjectName(QString::fromUtf8("pushButtonGoOrigin"));
        pushButtonGoOrigin->setGeometry(QRect(10, 260, 121, 41));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(330, 150, 361, 361));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 60, 331, 16));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 80, 41, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(210, 80, 41, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        spinBoxStartPosX = new QSpinBox(frame);
        spinBoxStartPosX->setObjectName(QString::fromUtf8("spinBoxStartPosX"));
        spinBoxStartPosX->setGeometry(QRect(110, 80, 81, 22));
        spinBoxStartPosX->setMinimum(-99999999);
        spinBoxStartPosX->setMaximum(99999999);
        spinBoxStartPosY = new QSpinBox(frame);
        spinBoxStartPosY->setObjectName(QString::fromUtf8("spinBoxStartPosY"));
        spinBoxStartPosY->setGeometry(QRect(260, 80, 81, 22));
        spinBoxStartPosY->setMaximum(99999999);
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 150, 331, 16));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(60, 110, 41, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        spinBoxStartVelocity = new QSpinBox(frame);
        spinBoxStartVelocity->setObjectName(QString::fromUtf8("spinBoxStartVelocity"));
        spinBoxStartVelocity->setGeometry(QRect(110, 110, 81, 22));
        spinBoxStartVelocity->setMaximum(99999999);
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(210, 110, 41, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        spinBoxAccel = new QSpinBox(frame);
        spinBoxAccel->setObjectName(QString::fromUtf8("spinBoxAccel"));
        spinBoxAccel->setGeometry(QRect(260, 110, 81, 22));
        spinBoxAccel->setMaximum(99999999);
        label_7 = new QLabel(frame);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(60, 170, 41, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        spinBoxScanPulse = new QSpinBox(frame);
        spinBoxScanPulse->setObjectName(QString::fromUtf8("spinBoxScanPulse"));
        spinBoxScanPulse->setGeometry(QRect(110, 170, 81, 22));
        spinBoxScanPulse->setMaximum(99999999);
        label_8 = new QLabel(frame);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(210, 170, 41, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        spinBoxScanVelocity = new QSpinBox(frame);
        spinBoxScanVelocity->setObjectName(QString::fromUtf8("spinBoxScanVelocity"));
        spinBoxScanVelocity->setGeometry(QRect(260, 170, 81, 22));
        spinBoxScanVelocity->setMaximum(99999999);
        label_9 = new QLabel(frame);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 200, 331, 16));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_10 = new QLabel(frame);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(210, 220, 41, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_11 = new QLabel(frame);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(60, 220, 41, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        spinBoxStepPulse = new QSpinBox(frame);
        spinBoxStepPulse->setObjectName(QString::fromUtf8("spinBoxStepPulse"));
        spinBoxStepPulse->setGeometry(QRect(110, 220, 81, 22));
        spinBoxStepPulse->setMaximum(99999999);
        spinBoxStepVelocity = new QSpinBox(frame);
        spinBoxStepVelocity->setObjectName(QString::fromUtf8("spinBoxStepVelocity"));
        spinBoxStepVelocity->setGeometry(QRect(260, 220, 81, 22));
        spinBoxStepVelocity->setMaximum(99999999);
        label_12 = new QLabel(frame);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 250, 331, 16));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        spinBoxScanCount = new QSpinBox(frame);
        spinBoxScanCount->setObjectName(QString::fromUtf8("spinBoxScanCount"));
        spinBoxScanCount->setGeometry(QRect(140, 270, 51, 22));
        spinBoxScanCount->setMaximum(99999999);
        label_13 = new QLabel(frame);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(60, 270, 71, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        spinBoxCurrentScan = new QSpinBox(frame);
        spinBoxCurrentScan->setObjectName(QString::fromUtf8("spinBoxCurrentScan"));
        spinBoxCurrentScan->setGeometry(QRect(290, 270, 51, 22));
        spinBoxCurrentScan->setMaximum(99999999);
        label_14 = new QLabel(frame);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(210, 270, 81, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_18 = new QLabel(frame);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(60, 320, 41, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_19 = new QLabel(frame);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(10, 300, 331, 16));
        label_19->setFrameShape(QFrame::Panel);
        label_19->setFrameShadow(QFrame::Sunken);
        spinBoxOriginVelocity = new QSpinBox(frame);
        spinBoxOriginVelocity->setObjectName(QString::fromUtf8("spinBoxOriginVelocity"));
        spinBoxOriginVelocity->setGeometry(QRect(110, 320, 81, 22));
        spinBoxOriginVelocity->setMaximum(99999999);
        label_20 = new QLabel(frame);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(60, 30, 41, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        spinBoxMaxPulseX = new QSpinBox(frame);
        spinBoxMaxPulseX->setObjectName(QString::fromUtf8("spinBoxMaxPulseX"));
        spinBoxMaxPulseX->setGeometry(QRect(110, 30, 81, 22));
        spinBoxMaxPulseX->setMaximum(99999999);
        spinBoxMaxPulseY = new QSpinBox(frame);
        spinBoxMaxPulseY->setObjectName(QString::fromUtf8("spinBoxMaxPulseY"));
        spinBoxMaxPulseY->setGeometry(QRect(260, 30, 81, 22));
        spinBoxMaxPulseY->setMaximum(99999999);
        label_21 = new QLabel(frame);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(210, 30, 41, 21));
        label_21->setFrameShape(QFrame::Panel);
        label_21->setFrameShadow(QFrame::Sunken);
        label_22 = new QLabel(frame);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(10, 10, 331, 16));
        label_22->setFrameShape(QFrame::Panel);
        label_22->setFrameShadow(QFrame::Sunken);
        pushButtonGoStartPos = new QPushButton(centralWidget);
        pushButtonGoStartPos->setObjectName(QString::fromUtf8("pushButtonGoStartPos"));
        pushButtonGoStartPos->setGeometry(QRect(10, 10, 121, 51));
        pushButtonStartScan = new QPushButton(centralWidget);
        pushButtonStartScan->setObjectName(QString::fromUtf8("pushButtonStartScan"));
        pushButtonStartScan->setGeometry(QRect(10, 80, 121, 51));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(330, 10, 361, 81));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_15 = new QLabel(frame_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(0, 0, 361, 16));
        label_15->setFrameShape(QFrame::Panel);
        label_15->setFrameShadow(QFrame::Sunken);
        label_15->setAlignment(Qt::AlignCenter);
        spinBoxBoardSizeX = new QSpinBox(frame_2);
        spinBoxBoardSizeX->setObjectName(QString::fromUtf8("spinBoxBoardSizeX"));
        spinBoxBoardSizeX->setGeometry(QRect(80, 20, 81, 22));
        spinBoxBoardSizeX->setMaximum(99999999);
        label_16 = new QLabel(frame_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(30, 20, 41, 21));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_17 = new QLabel(frame_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(180, 20, 41, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        spinBoxBoardSizeY = new QSpinBox(frame_2);
        spinBoxBoardSizeY->setObjectName(QString::fromUtf8("spinBoxBoardSizeY"));
        spinBoxBoardSizeY->setGeometry(QRect(230, 20, 81, 22));
        spinBoxBoardSizeY->setMaximum(99999999);
        label_26 = new QLabel(frame_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(140, 50, 81, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        spinBoxSpaceY = new QSpinBox(frame_2);
        spinBoxSpaceY->setObjectName(QString::fromUtf8("spinBoxSpaceY"));
        spinBoxSpaceY->setGeometry(QRect(230, 50, 81, 22));
        spinBoxSpaceY->setMaximum(99999999);
        pushButtonConvertToScan = new QPushButton(centralWidget);
        pushButtonConvertToScan->setObjectName(QString::fromUtf8("pushButtonConvertToScan"));
        pushButtonConvertToScan->setGeometry(QRect(450, 100, 101, 41));
        pushButtonJogXP = new QPushButton(centralWidget);
        pushButtonJogXP->setObjectName(QString::fromUtf8("pushButtonJogXP"));
        pushButtonJogXP->setGeometry(QRect(20, 190, 41, 23));
        pushButtonJogXM = new QPushButton(centralWidget);
        pushButtonJogXM->setObjectName(QString::fromUtf8("pushButtonJogXM"));
        pushButtonJogXM->setGeometry(QRect(90, 190, 41, 23));
        pushButtonJogYP = new QPushButton(centralWidget);
        pushButtonJogYP->setObjectName(QString::fromUtf8("pushButtonJogYP"));
        pushButtonJogYP->setGeometry(QRect(50, 160, 51, 23));
        pushButtonJogYM = new QPushButton(centralWidget);
        pushButtonJogYM->setObjectName(QString::fromUtf8("pushButtonJogYM"));
        pushButtonJogYM->setGeometry(QRect(50, 220, 51, 23));
        pushButtonSave = new QPushButton(centralWidget);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));
        pushButtonSave->setGeometry(QRect(240, 350, 75, 31));
        toolButtonVacuum = new QToolButton(centralWidget);
        toolButtonVacuum->setObjectName(QString::fromUtf8("toolButtonVacuum"));
        toolButtonVacuum->setGeometry(QRect(180, 10, 71, 31));
        toolButtonVacuum->setCheckable(true);
        toolButtonPatlightR = new QToolButton(centralWidget);
        toolButtonPatlightR->setObjectName(QString::fromUtf8("toolButtonPatlightR"));
        toolButtonPatlightR->setGeometry(QRect(180, 70, 81, 31));
        toolButtonPatlightR->setCheckable(true);
        toolButtonPatlightY = new QToolButton(centralWidget);
        toolButtonPatlightY->setObjectName(QString::fromUtf8("toolButtonPatlightY"));
        toolButtonPatlightY->setGeometry(QRect(180, 100, 81, 31));
        toolButtonPatlightY->setCheckable(true);
        toolButtonPatlightG = new QToolButton(centralWidget);
        toolButtonPatlightG->setObjectName(QString::fromUtf8("toolButtonPatlightG"));
        toolButtonPatlightG->setGeometry(QRect(180, 130, 81, 31));
        toolButtonPatlightG->setCheckable(true);
        checkBoxStartButtonL = new QCheckBox(centralWidget);
        checkBoxStartButtonL->setObjectName(QString::fromUtf8("checkBoxStartButtonL"));
        checkBoxStartButtonL->setGeometry(QRect(170, 220, 76, 17));
        checkBoxStartButtonR = new QCheckBox(centralWidget);
        checkBoxStartButtonR->setObjectName(QString::fromUtf8("checkBoxStartButtonR"));
        checkBoxStartButtonR->setGeometry(QRect(250, 220, 76, 17));
        checkBoxFootSW = new QCheckBox(centralWidget);
        checkBoxFootSW->setObjectName(QString::fromUtf8("checkBoxFootSW"));
        checkBoxFootSW->setGeometry(QRect(170, 250, 131, 17));
        checkBoxAreaSensor = new QCheckBox(centralWidget);
        checkBoxAreaSensor->setObjectName(QString::fromUtf8("checkBoxAreaSensor"));
        checkBoxAreaSensor->setGeometry(QRect(170, 280, 141, 17));
        pushButtonStop = new QPushButton(centralWidget);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));
        pushButtonStop->setGeometry(QRect(10, 310, 121, 41));
        checkBoxEmergency = new QCheckBox(centralWidget);
        checkBoxEmergency->setObjectName(QString::fromUtf8("checkBoxEmergency"));
        checkBoxEmergency->setGeometry(QRect(170, 310, 141, 17));
        spinBoxCurrentPulseX = new QSpinBox(centralWidget);
        spinBoxCurrentPulseX->setObjectName(QString::fromUtf8("spinBoxCurrentPulseX"));
        spinBoxCurrentPulseX->setGeometry(QRect(90, 490, 81, 22));
        spinBoxCurrentPulseX->setReadOnly(true);
        spinBoxCurrentPulseX->setMinimum(-99999999);
        spinBoxCurrentPulseX->setMaximum(99999999);
        label_23 = new QLabel(centralWidget);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(190, 490, 41, 21));
        label_23->setFrameShape(QFrame::Panel);
        label_23->setFrameShadow(QFrame::Sunken);
        label_24 = new QLabel(centralWidget);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(10, 470, 311, 16));
        label_24->setFrameShape(QFrame::Panel);
        label_24->setFrameShadow(QFrame::Sunken);
        label_24->setAlignment(Qt::AlignCenter);
        spinBoxCurrentPulseY = new QSpinBox(centralWidget);
        spinBoxCurrentPulseY->setObjectName(QString::fromUtf8("spinBoxCurrentPulseY"));
        spinBoxCurrentPulseY->setGeometry(QRect(240, 490, 81, 22));
        spinBoxCurrentPulseY->setReadOnly(true);
        spinBoxCurrentPulseY->setMinimum(-99999999);
        spinBoxCurrentPulseY->setMaximum(99999999);
        label_25 = new QLabel(centralWidget);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(40, 490, 41, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        ContecNC2DClass->setCentralWidget(centralWidget);

        retranslateUi(ContecNC2DClass);

        QMetaObject::connectSlotsByName(ContecNC2DClass);
    } // setupUi

    void retranslateUi(QMainWindow *ContecNC2DClass)
    {
        ContecNC2DClass->setWindowTitle(QApplication::translate("ContecNC2DClass", "ContecNC2D", 0, QApplication::UnicodeUTF8));
        pushButtonGoOrigin->setText(QApplication::translate("ContecNC2DClass", "\345\216\237\347\202\271\345\276\251\345\270\260", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ContecNC2DClass", "\351\226\213\345\247\213\344\275\215\347\275\256", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ContecNC2DClass", "X", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ContecNC2DClass", "Y", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ContecNC2DClass", "\343\202\271\343\202\255\343\203\243\343\203\263\344\275\215\347\275\256", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ContecNC2DClass", "\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ContecNC2DClass", "\345\212\240\351\200\237", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ContecNC2DClass", "\347\247\273\345\213\225\351\207\217", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ContecNC2DClass", "\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("ContecNC2DClass", "\346\250\252\343\202\271\343\203\206\343\203\203\343\203\227", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("ContecNC2DClass", "\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("ContecNC2DClass", "\347\247\273\345\213\225\351\207\217", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("ContecNC2DClass", "\343\202\271\343\202\255\343\203\243\343\203\263\346\225\260", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("ContecNC2DClass", "\343\202\271\343\202\255\343\203\243\343\203\263\346\225\260", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("ContecNC2DClass", "\347\217\276\345\234\250\343\202\271\343\202\255\343\203\243\343\203\263\346\225\260", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("ContecNC2DClass", "\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("ContecNC2DClass", "\345\216\237\347\202\271\345\276\251\345\270\260", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("ContecNC2DClass", "\357\274\270", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("ContecNC2DClass", "\357\274\271", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("ContecNC2DClass", "\346\234\200\345\244\247\345\217\257\345\213\225\347\257\204\345\233\262", 0, QApplication::UnicodeUTF8));
        pushButtonGoStartPos->setText(QApplication::translate("ContecNC2DClass", "\351\226\213\345\247\213\344\275\215\347\275\256\343\201\270\347\247\273\345\213\225", 0, QApplication::UnicodeUTF8));
        pushButtonStartScan->setText(QApplication::translate("ContecNC2DClass", "\343\202\271\343\202\255\343\203\243\343\203\263\351\226\213\345\247\213", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("ContecNC2DClass", "\343\203\257\343\203\274\343\202\257\343\202\265\343\202\244\343\202\272", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("ContecNC2DClass", "X", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("ContecNC2DClass", "Y", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("ContecNC2DClass", "\347\251\272\350\265\260\350\267\235\351\233\242Y", 0, QApplication::UnicodeUTF8));
        pushButtonConvertToScan->setText(QApplication::translate("ContecNC2DClass", "\343\202\271\343\202\255\343\203\243\343\203\263\345\244\211\346\217\233\343\200\200\342\206\223", 0, QApplication::UnicodeUTF8));
        pushButtonJogXP->setText(QApplication::translate("ContecNC2DClass", "JOG+", 0, QApplication::UnicodeUTF8));
        pushButtonJogXM->setText(QApplication::translate("ContecNC2DClass", "JOG-", 0, QApplication::UnicodeUTF8));
        pushButtonJogYP->setText(QApplication::translate("ContecNC2DClass", "JOG+", 0, QApplication::UnicodeUTF8));
        pushButtonJogYM->setText(QApplication::translate("ContecNC2DClass", "JOG-", 0, QApplication::UnicodeUTF8));
        pushButtonSave->setText(QApplication::translate("ContecNC2DClass", "Save", 0, QApplication::UnicodeUTF8));
        toolButtonVacuum->setText(QApplication::translate("ContecNC2DClass", "\345\220\270\347\235\200", 0, QApplication::UnicodeUTF8));
        toolButtonPatlightR->setText(QApplication::translate("ContecNC2DClass", "\343\203\221\343\203\210\343\203\251\343\202\244\343\203\210\343\200\200\350\265\244", 0, QApplication::UnicodeUTF8));
        toolButtonPatlightY->setText(QApplication::translate("ContecNC2DClass", "\343\203\221\343\203\210\343\203\251\343\202\244\343\203\210\343\200\200\351\273\204", 0, QApplication::UnicodeUTF8));
        toolButtonPatlightG->setText(QApplication::translate("ContecNC2DClass", "\343\203\221\343\203\210\343\203\251\343\202\244\343\203\210\343\200\200\347\267\221", 0, QApplication::UnicodeUTF8));
        checkBoxStartButtonL->setText(QApplication::translate("ContecNC2DClass", "\350\265\267\345\213\225\343\203\234\343\202\277\343\203\263", 0, QApplication::UnicodeUTF8));
        checkBoxStartButtonR->setText(QApplication::translate("ContecNC2DClass", "\350\265\267\345\213\225\343\203\234\343\202\277\343\203\263", 0, QApplication::UnicodeUTF8));
        checkBoxFootSW->setText(QApplication::translate("ContecNC2DClass", "\343\203\225\343\203\203\343\203\210\343\202\271\343\202\244\343\203\203\343\203\201", 0, QApplication::UnicodeUTF8));
        checkBoxAreaSensor->setText(QApplication::translate("ContecNC2DClass", "\343\202\250\343\203\252\343\202\242\343\202\273\343\203\263\343\202\265\343\203\274", 0, QApplication::UnicodeUTF8));
        pushButtonStop->setText(QApplication::translate("ContecNC2DClass", "\345\201\234\346\255\242", 0, QApplication::UnicodeUTF8));
        checkBoxEmergency->setText(QApplication::translate("ContecNC2DClass", "\351\235\236\345\270\270\345\201\234\346\255\242", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("ContecNC2DClass", "\357\274\271", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("ContecNC2DClass", "\347\217\276\345\234\250\344\275\215\347\275\256", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("ContecNC2DClass", "\357\274\270", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ContecNC2DClass: public Ui_ContecNC2DClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTECNC2D_H
