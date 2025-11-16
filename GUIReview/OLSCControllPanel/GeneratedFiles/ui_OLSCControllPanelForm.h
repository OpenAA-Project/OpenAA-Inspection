/********************************************************************************
** Form generated from reading UI file 'OLSCControllPanelForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OLSCCONTROLLPANELFORM_H
#define UI_OLSCCONTROLLPANELFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OLSCControllPanelClass
{
public:
    QGridLayout *gridLayout_10;
    QFrame *frmCOMInfo;
    QGridLayout *gridLayout_5;
    QLabel *label;
    QLineEdit *leCOMName;
    QPushButton *pbCOMOpen;
    QSpacerItem *horizontalSpacer;
    QFrame *frmGetState;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout;
    QPushButton *pbSensorStatus;
    QLabel *lbSensorStatus;
    QHBoxLayout *hlGetMotorState;
    QPushButton *pbMotorStatus;
    QGridLayout *gridLayout_3;
    QLabel *label_2;
    QLabel *lbCurrentPosition;
    QLabel *label_3;
    QLabel *lbCurrentMotorState;
    QFrame *frmStopAndPulseMove;
    QGridLayout *gridLayout_7;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pbMotorStop;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pbMoveToPulse;
    QSpinBox *sbMoveToPulse;
    QFrame *frmJogMove;
    QGridLayout *gridLayout_8;
    QPushButton *pbJog;
    QGroupBox *gbJogSpeed;
    QGridLayout *gridLayout;
    QRadioButton *rbJogFast;
    QRadioButton *rbJogSlow;
    QRadioButton *rbJogOnePulse;
    QGroupBox *gbJogWay;
    QGridLayout *gridLayout_2;
    QRadioButton *rbJogToMinus;
    QRadioButton *rbJogToPlus;
    QFrame *frmHomeAndPortMove;
    QGridLayout *gridLayout_9;
    QPushButton *pbHome;
    QGroupBox *gbMoveToPort;
    QGridLayout *gridLayout_4;
    QPushButton *pbMoveToPort1;
    QPushButton *pbMoveToPort2;
    QPushButton *pbMoveToPort3;
    QPushButton *pbMoveToPort4;

    void setupUi(QWidget *OLSCControllPanelClass)
    {
        if (OLSCControllPanelClass->objectName().isEmpty())
            OLSCControllPanelClass->setObjectName(QString::fromUtf8("OLSCControllPanelClass"));
        OLSCControllPanelClass->resize(541, 394);
        gridLayout_10 = new QGridLayout(OLSCControllPanelClass);
        gridLayout_10->setSpacing(0);
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        frmCOMInfo = new QFrame(OLSCControllPanelClass);
        frmCOMInfo->setObjectName(QString::fromUtf8("frmCOMInfo"));
        frmCOMInfo->setFrameShape(QFrame::StyledPanel);
        frmCOMInfo->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frmCOMInfo);
        gridLayout_5->setSpacing(7);
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label = new QLabel(frmCOMInfo);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_5->addWidget(label, 0, 0, 1, 1);

        leCOMName = new QLineEdit(frmCOMInfo);
        leCOMName->setObjectName(QString::fromUtf8("leCOMName"));

        gridLayout_5->addWidget(leCOMName, 0, 1, 1, 1);

        pbCOMOpen = new QPushButton(frmCOMInfo);
        pbCOMOpen->setObjectName(QString::fromUtf8("pbCOMOpen"));

        gridLayout_5->addWidget(pbCOMOpen, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(162, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 0, 3, 1, 1);


        gridLayout_10->addWidget(frmCOMInfo, 0, 0, 1, 1);

        frmGetState = new QFrame(OLSCControllPanelClass);
        frmGetState->setObjectName(QString::fromUtf8("frmGetState"));
        frmGetState->setFrameShape(QFrame::StyledPanel);
        frmGetState->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frmGetState);
        gridLayout_6->setSpacing(7);
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pbSensorStatus = new QPushButton(frmGetState);
        pbSensorStatus->setObjectName(QString::fromUtf8("pbSensorStatus"));

        horizontalLayout->addWidget(pbSensorStatus);

        lbSensorStatus = new QLabel(frmGetState);
        lbSensorStatus->setObjectName(QString::fromUtf8("lbSensorStatus"));

        horizontalLayout->addWidget(lbSensorStatus);


        gridLayout_6->addLayout(horizontalLayout, 0, 0, 1, 1);

        hlGetMotorState = new QHBoxLayout();
        hlGetMotorState->setObjectName(QString::fromUtf8("hlGetMotorState"));
        pbMotorStatus = new QPushButton(frmGetState);
        pbMotorStatus->setObjectName(QString::fromUtf8("pbMotorStatus"));

        hlGetMotorState->addWidget(pbMotorStatus);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_2 = new QLabel(frmGetState);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

        lbCurrentPosition = new QLabel(frmGetState);
        lbCurrentPosition->setObjectName(QString::fromUtf8("lbCurrentPosition"));

        gridLayout_3->addWidget(lbCurrentPosition, 0, 1, 1, 1);

        label_3 = new QLabel(frmGetState);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 1, 0, 1, 1);

        lbCurrentMotorState = new QLabel(frmGetState);
        lbCurrentMotorState->setObjectName(QString::fromUtf8("lbCurrentMotorState"));

        gridLayout_3->addWidget(lbCurrentMotorState, 1, 1, 1, 1);


        hlGetMotorState->addLayout(gridLayout_3);


        gridLayout_6->addLayout(hlGetMotorState, 0, 1, 1, 1);


        gridLayout_10->addWidget(frmGetState, 1, 0, 1, 1);

        frmStopAndPulseMove = new QFrame(OLSCControllPanelClass);
        frmStopAndPulseMove->setObjectName(QString::fromUtf8("frmStopAndPulseMove"));
        frmStopAndPulseMove->setFrameShape(QFrame::StyledPanel);
        frmStopAndPulseMove->setFrameShadow(QFrame::Raised);
        gridLayout_7 = new QGridLayout(frmStopAndPulseMove);
        gridLayout_7->setSpacing(7);
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        pbMotorStop = new QPushButton(frmStopAndPulseMove);
        pbMotorStop->setObjectName(QString::fromUtf8("pbMotorStop"));

        gridLayout_7->addWidget(pbMotorStop, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        pbMoveToPulse = new QPushButton(frmStopAndPulseMove);
        pbMoveToPulse->setObjectName(QString::fromUtf8("pbMoveToPulse"));

        gridLayout_7->addWidget(pbMoveToPulse, 0, 3, 1, 1);

        sbMoveToPulse = new QSpinBox(frmStopAndPulseMove);
        sbMoveToPulse->setObjectName(QString::fromUtf8("sbMoveToPulse"));
        sbMoveToPulse->setMinimum(-16777215);
        sbMoveToPulse->setMaximum(16777215);

        gridLayout_7->addWidget(sbMoveToPulse, 0, 4, 1, 1);


        gridLayout_10->addWidget(frmStopAndPulseMove, 2, 0, 1, 1);

        frmJogMove = new QFrame(OLSCControllPanelClass);
        frmJogMove->setObjectName(QString::fromUtf8("frmJogMove"));
        frmJogMove->setFrameShape(QFrame::StyledPanel);
        frmJogMove->setFrameShadow(QFrame::Raised);
        gridLayout_8 = new QGridLayout(frmJogMove);
        gridLayout_8->setSpacing(7);
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        pbJog = new QPushButton(frmJogMove);
        pbJog->setObjectName(QString::fromUtf8("pbJog"));

        gridLayout_8->addWidget(pbJog, 0, 0, 1, 1);

        gbJogSpeed = new QGroupBox(frmJogMove);
        gbJogSpeed->setObjectName(QString::fromUtf8("gbJogSpeed"));
        gridLayout = new QGridLayout(gbJogSpeed);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        rbJogFast = new QRadioButton(gbJogSpeed);
        rbJogFast->setObjectName(QString::fromUtf8("rbJogFast"));

        gridLayout->addWidget(rbJogFast, 1, 0, 1, 1);

        rbJogSlow = new QRadioButton(gbJogSpeed);
        rbJogSlow->setObjectName(QString::fromUtf8("rbJogSlow"));
        rbJogSlow->setChecked(true);

        gridLayout->addWidget(rbJogSlow, 0, 0, 1, 1);

        rbJogOnePulse = new QRadioButton(gbJogSpeed);
        rbJogOnePulse->setObjectName(QString::fromUtf8("rbJogOnePulse"));

        gridLayout->addWidget(rbJogOnePulse, 2, 0, 1, 1);


        gridLayout_8->addWidget(gbJogSpeed, 0, 1, 1, 1);

        gbJogWay = new QGroupBox(frmJogMove);
        gbJogWay->setObjectName(QString::fromUtf8("gbJogWay"));
        gridLayout_2 = new QGridLayout(gbJogWay);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        rbJogToMinus = new QRadioButton(gbJogWay);
        rbJogToMinus->setObjectName(QString::fromUtf8("rbJogToMinus"));

        gridLayout_2->addWidget(rbJogToMinus, 1, 0, 1, 1);

        rbJogToPlus = new QRadioButton(gbJogWay);
        rbJogToPlus->setObjectName(QString::fromUtf8("rbJogToPlus"));
        rbJogToPlus->setChecked(true);

        gridLayout_2->addWidget(rbJogToPlus, 0, 0, 1, 1);


        gridLayout_8->addWidget(gbJogWay, 0, 2, 1, 1);


        gridLayout_10->addWidget(frmJogMove, 3, 0, 1, 1);

        frmHomeAndPortMove = new QFrame(OLSCControllPanelClass);
        frmHomeAndPortMove->setObjectName(QString::fromUtf8("frmHomeAndPortMove"));
        frmHomeAndPortMove->setFrameShape(QFrame::StyledPanel);
        frmHomeAndPortMove->setFrameShadow(QFrame::Raised);
        gridLayout_9 = new QGridLayout(frmHomeAndPortMove);
        gridLayout_9->setSpacing(7);
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        pbHome = new QPushButton(frmHomeAndPortMove);
        pbHome->setObjectName(QString::fromUtf8("pbHome"));

        gridLayout_9->addWidget(pbHome, 0, 0, 1, 1);

        gbMoveToPort = new QGroupBox(frmHomeAndPortMove);
        gbMoveToPort->setObjectName(QString::fromUtf8("gbMoveToPort"));
        gridLayout_4 = new QGridLayout(gbMoveToPort);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pbMoveToPort1 = new QPushButton(gbMoveToPort);
        pbMoveToPort1->setObjectName(QString::fromUtf8("pbMoveToPort1"));

        gridLayout_4->addWidget(pbMoveToPort1, 0, 0, 1, 1);

        pbMoveToPort2 = new QPushButton(gbMoveToPort);
        pbMoveToPort2->setObjectName(QString::fromUtf8("pbMoveToPort2"));

        gridLayout_4->addWidget(pbMoveToPort2, 0, 1, 1, 1);

        pbMoveToPort3 = new QPushButton(gbMoveToPort);
        pbMoveToPort3->setObjectName(QString::fromUtf8("pbMoveToPort3"));

        gridLayout_4->addWidget(pbMoveToPort3, 0, 2, 1, 1);

        pbMoveToPort4 = new QPushButton(gbMoveToPort);
        pbMoveToPort4->setObjectName(QString::fromUtf8("pbMoveToPort4"));

        gridLayout_4->addWidget(pbMoveToPort4, 0, 3, 1, 1);


        gridLayout_9->addWidget(gbMoveToPort, 0, 1, 1, 1);


        gridLayout_10->addWidget(frmHomeAndPortMove, 4, 0, 1, 1);


        retranslateUi(OLSCControllPanelClass);

        QMetaObject::connectSlotsByName(OLSCControllPanelClass);
    } // setupUi

    void retranslateUi(QWidget *OLSCControllPanelClass)
    {
        OLSCControllPanelClass->setWindowTitle(QCoreApplication::translate("OLSCControllPanelClass", "OLSCControllPanel", nullptr));
        label->setText(QCoreApplication::translate("OLSCControllPanelClass", "COM Name", nullptr));
        pbCOMOpen->setText(QCoreApplication::translate("OLSCControllPanelClass", "Open", nullptr));
        pbSensorStatus->setText(QCoreApplication::translate("OLSCControllPanelClass", "\343\202\273\343\203\263\343\202\265\347\212\266\346\205\213\347\242\272\350\252\215", nullptr));
        lbSensorStatus->setText(QCoreApplication::translate("OLSCControllPanelClass", "state", nullptr));
        pbMotorStatus->setText(QCoreApplication::translate("OLSCControllPanelClass", "\343\203\242\343\203\274\343\202\277\347\212\266\346\205\213\345\217\226\345\276\227", nullptr));
        label_2->setText(QCoreApplication::translate("OLSCControllPanelClass", "\347\217\276\345\234\250\344\275\215\347\275\256\357\274\232", nullptr));
        lbCurrentPosition->setText(QCoreApplication::translate("OLSCControllPanelClass", "None", nullptr));
        label_3->setText(QCoreApplication::translate("OLSCControllPanelClass", "\343\203\242\343\203\274\343\202\277\343\203\274\347\212\266\346\205\213\357\274\232", nullptr));
        lbCurrentMotorState->setText(QCoreApplication::translate("OLSCControllPanelClass", "None", nullptr));
        pbMotorStop->setText(QCoreApplication::translate("OLSCControllPanelClass", "\343\203\242\343\203\274\343\202\277\345\213\225\344\275\234\345\201\234\346\255\242", nullptr));
        pbMoveToPulse->setText(QCoreApplication::translate("OLSCControllPanelClass", "\346\214\207\345\256\232\343\203\221\343\203\253\343\202\271\346\225\260\347\247\273\345\213\225", nullptr));
        pbJog->setText(QCoreApplication::translate("OLSCControllPanelClass", "Jog\347\247\273\345\213\225", nullptr));
        gbJogSpeed->setTitle(QCoreApplication::translate("OLSCControllPanelClass", "Jog\351\200\237\345\272\246\343\202\277\343\202\244\343\203\227", nullptr));
        rbJogFast->setText(QCoreApplication::translate("OLSCControllPanelClass", "\351\253\230\351\200\237", nullptr));
        rbJogSlow->setText(QCoreApplication::translate("OLSCControllPanelClass", "\344\275\216\351\200\237", nullptr));
        rbJogOnePulse->setText(QCoreApplication::translate("OLSCControllPanelClass", "1\343\203\221\343\203\253\343\202\271\347\247\273\345\213\225", nullptr));
        gbJogWay->setTitle(QCoreApplication::translate("OLSCControllPanelClass", "Jog\346\226\271\345\220\221", nullptr));
        rbJogToMinus->setText(QCoreApplication::translate("OLSCControllPanelClass", "-\346\226\271\345\220\221", nullptr));
        rbJogToPlus->setText(QCoreApplication::translate("OLSCControllPanelClass", "+\346\226\271\345\220\221", nullptr));
        pbHome->setText(QCoreApplication::translate("OLSCControllPanelClass", "\345\216\237\347\202\271\345\276\251\345\270\260", nullptr));
        gbMoveToPort->setTitle(QCoreApplication::translate("OLSCControllPanelClass", "\343\203\235\343\203\274\343\203\210\347\247\273\345\213\225", nullptr));
        pbMoveToPort1->setText(QCoreApplication::translate("OLSCControllPanelClass", "Port 1", nullptr));
        pbMoveToPort2->setText(QCoreApplication::translate("OLSCControllPanelClass", "Port 2", nullptr));
        pbMoveToPort3->setText(QCoreApplication::translate("OLSCControllPanelClass", "Port 3", nullptr));
        pbMoveToPort4->setText(QCoreApplication::translate("OLSCControllPanelClass", "Port 4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OLSCControllPanelClass: public Ui_OLSCControllPanelClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OLSCCONTROLLPANELFORM_H
