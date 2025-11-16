/********************************************************************************
** Form generated from reading UI file 'LEDControl16GTester.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEDCONTROL16GTESTER_H
#define UI_LEDCONTROL16GTESTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LEDControl16GTesterClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonReqVersion;
    QLineEdit *lineEditVersion;
    QPushButton *pushButtonReqAttr;
    QLineEdit *lineEditDipSW;
    QLabel *label;
    QCheckBox *checkBoxTestLED;
    QCheckBox *checkBoxReset;
    QCheckBox *checkBoxPLSEnable;
    QPushButton *pushButtonSetAttr;
    QSpinBox *spinBoxPatternNo;
    QLabel *label_2;
    QTableWidget *tableWidget;
    QPushButton *pushButtonReqBaseCounter;
    QPushButton *pushButtonSetBaseCounter;
    QPushButton *pushButtonReqHighCounter;
    QPushButton *pushButtonSetHighCounter;
    QPushButton *pushButtonReqAnalog;
    QFrame *frame;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEditI_IN;
    QCheckBox *checkBoxI_iCLK;
    QCheckBox *checkBoxI_iCmdW;
    QCheckBox *checkBoxI_iRESET;
    QCheckBox *checkBoxI_iStrobe;
    QLabel *label_5;
    QLineEdit *lineEditI_FIO;
    QLabel *label_6;
    QPushButton *pushButtonReqBit;
    QLineEdit *lineEditKey;
    QLabel *label_11;
    QFrame *frame_2;
    QLabel *label_7;
    QLabel *label_8;
    QCheckBox *checkBoxO_InRW;
    QCheckBox *checkBoxO_InClk;
    QCheckBox *checkBoxO_InCS;
    QLineEdit *lineEditO_FIO;
    QLabel *label_9;
    QPushButton *pushButtonOutBit;
    QLineEdit *lineEditO_RPOut;
    QLabel *label_10;
    QPushButton *pushButtonOutRPOut;
    QPushButton *pushButtonSetTargetValue;
    QPushButton *pushButtonReqTargetValue;

    void setupUi(QMainWindow *LEDControl16GTesterClass)
    {
        if (LEDControl16GTesterClass->objectName().isEmpty())
            LEDControl16GTesterClass->setObjectName(QString::fromUtf8("LEDControl16GTesterClass"));
        LEDControl16GTesterClass->resize(844, 878);
        centralWidget = new QWidget(LEDControl16GTesterClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButtonReqVersion = new QPushButton(centralWidget);
        pushButtonReqVersion->setObjectName(QString::fromUtf8("pushButtonReqVersion"));
        pushButtonReqVersion->setGeometry(QRect(10, 10, 112, 34));
        lineEditVersion = new QLineEdit(centralWidget);
        lineEditVersion->setObjectName(QString::fromUtf8("lineEditVersion"));
        lineEditVersion->setGeometry(QRect(130, 10, 301, 31));
        pushButtonReqAttr = new QPushButton(centralWidget);
        pushButtonReqAttr->setObjectName(QString::fromUtf8("pushButtonReqAttr"));
        pushButtonReqAttr->setGeometry(QRect(10, 50, 112, 34));
        lineEditDipSW = new QLineEdit(centralWidget);
        lineEditDipSW->setObjectName(QString::fromUtf8("lineEditDipSW"));
        lineEditDipSW->setGeometry(QRect(240, 50, 61, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 57, 75, 21));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        checkBoxTestLED = new QCheckBox(centralWidget);
        checkBoxTestLED->setObjectName(QString::fromUtf8("checkBoxTestLED"));
        checkBoxTestLED->setGeometry(QRect(360, 60, 108, 22));
        checkBoxReset = new QCheckBox(centralWidget);
        checkBoxReset->setObjectName(QString::fromUtf8("checkBoxReset"));
        checkBoxReset->setGeometry(QRect(360, 90, 108, 22));
        checkBoxPLSEnable = new QCheckBox(centralWidget);
        checkBoxPLSEnable->setObjectName(QString::fromUtf8("checkBoxPLSEnable"));
        checkBoxPLSEnable->setGeometry(QRect(360, 120, 108, 22));
        pushButtonSetAttr = new QPushButton(centralWidget);
        pushButtonSetAttr->setObjectName(QString::fromUtf8("pushButtonSetAttr"));
        pushButtonSetAttr->setGeometry(QRect(490, 40, 112, 34));
        spinBoxPatternNo = new QSpinBox(centralWidget);
        spinBoxPatternNo->setObjectName(QString::fromUtf8("spinBoxPatternNo"));
        spinBoxPatternNo->setGeometry(QRect(110, 150, 81, 24));
        spinBoxPatternNo->setMaximum(15);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 150, 75, 21));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (tableWidget->rowCount() < 16)
            tableWidget->setRowCount(16);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(10, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(11, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(12, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(13, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(14, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(15, __qtablewidgetitem19);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(40, 180, 461, 521));
        pushButtonReqBaseCounter = new QPushButton(centralWidget);
        pushButtonReqBaseCounter->setObjectName(QString::fromUtf8("pushButtonReqBaseCounter"));
        pushButtonReqBaseCounter->setGeometry(QRect(50, 710, 151, 34));
        pushButtonSetBaseCounter = new QPushButton(centralWidget);
        pushButtonSetBaseCounter->setObjectName(QString::fromUtf8("pushButtonSetBaseCounter"));
        pushButtonSetBaseCounter->setGeometry(QRect(210, 710, 151, 34));
        pushButtonReqHighCounter = new QPushButton(centralWidget);
        pushButtonReqHighCounter->setObjectName(QString::fromUtf8("pushButtonReqHighCounter"));
        pushButtonReqHighCounter->setGeometry(QRect(50, 750, 151, 34));
        pushButtonSetHighCounter = new QPushButton(centralWidget);
        pushButtonSetHighCounter->setObjectName(QString::fromUtf8("pushButtonSetHighCounter"));
        pushButtonSetHighCounter->setGeometry(QRect(210, 750, 151, 34));
        pushButtonReqAnalog = new QPushButton(centralWidget);
        pushButtonReqAnalog->setObjectName(QString::fromUtf8("pushButtonReqAnalog"));
        pushButtonReqAnalog->setGeometry(QRect(50, 830, 151, 34));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(530, 180, 141, 521));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 0, 141, 31));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 50, 41, 21));
        label_4->setAlignment(Qt::AlignCenter);
        lineEditI_IN = new QLineEdit(frame);
        lineEditI_IN->setObjectName(QString::fromUtf8("lineEditI_IN"));
        lineEditI_IN->setGeometry(QRect(60, 50, 71, 24));
        checkBoxI_iCLK = new QCheckBox(frame);
        checkBoxI_iCLK->setObjectName(QString::fromUtf8("checkBoxI_iCLK"));
        checkBoxI_iCLK->setGeometry(QRect(20, 90, 108, 22));
        checkBoxI_iCmdW = new QCheckBox(frame);
        checkBoxI_iCmdW->setObjectName(QString::fromUtf8("checkBoxI_iCmdW"));
        checkBoxI_iCmdW->setGeometry(QRect(20, 120, 108, 22));
        checkBoxI_iRESET = new QCheckBox(frame);
        checkBoxI_iRESET->setObjectName(QString::fromUtf8("checkBoxI_iRESET"));
        checkBoxI_iRESET->setGeometry(QRect(20, 150, 108, 22));
        checkBoxI_iStrobe = new QCheckBox(frame);
        checkBoxI_iStrobe->setObjectName(QString::fromUtf8("checkBoxI_iStrobe"));
        checkBoxI_iStrobe->setGeometry(QRect(20, 180, 108, 22));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(0, 280, 141, 31));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        lineEditI_FIO = new QLineEdit(frame);
        lineEditI_FIO->setObjectName(QString::fromUtf8("lineEditI_FIO"));
        lineEditI_FIO->setGeometry(QRect(60, 320, 71, 24));
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 320, 41, 21));
        label_6->setAlignment(Qt::AlignCenter);
        pushButtonReqBit = new QPushButton(frame);
        pushButtonReqBit->setObjectName(QString::fromUtf8("pushButtonReqBit"));
        pushButtonReqBit->setGeometry(QRect(20, 380, 101, 34));
        lineEditKey = new QLineEdit(frame);
        lineEditKey->setObjectName(QString::fromUtf8("lineEditKey"));
        lineEditKey->setGeometry(QRect(50, 220, 71, 24));
        label_11 = new QLabel(frame);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(0, 220, 41, 21));
        label_11->setAlignment(Qt::AlignCenter);
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(680, 180, 141, 521));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(0, 0, 141, 31));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(0, 280, 141, 31));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter);
        checkBoxO_InRW = new QCheckBox(frame_2);
        checkBoxO_InRW->setObjectName(QString::fromUtf8("checkBoxO_InRW"));
        checkBoxO_InRW->setGeometry(QRect(10, 420, 108, 22));
        checkBoxO_InClk = new QCheckBox(frame_2);
        checkBoxO_InClk->setObjectName(QString::fromUtf8("checkBoxO_InClk"));
        checkBoxO_InClk->setGeometry(QRect(10, 450, 108, 22));
        checkBoxO_InCS = new QCheckBox(frame_2);
        checkBoxO_InCS->setObjectName(QString::fromUtf8("checkBoxO_InCS"));
        checkBoxO_InCS->setGeometry(QRect(10, 480, 108, 22));
        lineEditO_FIO = new QLineEdit(frame_2);
        lineEditO_FIO->setObjectName(QString::fromUtf8("lineEditO_FIO"));
        lineEditO_FIO->setGeometry(QRect(50, 320, 71, 24));
        label_9 = new QLabel(frame_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(0, 320, 41, 21));
        label_9->setAlignment(Qt::AlignCenter);
        pushButtonOutBit = new QPushButton(frame_2);
        pushButtonOutBit->setObjectName(QString::fromUtf8("pushButtonOutBit"));
        pushButtonOutBit->setGeometry(QRect(20, 350, 101, 34));
        lineEditO_RPOut = new QLineEdit(frame_2);
        lineEditO_RPOut->setObjectName(QString::fromUtf8("lineEditO_RPOut"));
        lineEditO_RPOut->setGeometry(QRect(60, 50, 71, 24));
        label_10 = new QLabel(frame_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 50, 41, 21));
        label_10->setAlignment(Qt::AlignCenter);
        pushButtonOutRPOut = new QPushButton(frame_2);
        pushButtonOutRPOut->setObjectName(QString::fromUtf8("pushButtonOutRPOut"));
        pushButtonOutRPOut->setGeometry(QRect(30, 80, 101, 34));
        pushButtonSetTargetValue = new QPushButton(centralWidget);
        pushButtonSetTargetValue->setObjectName(QString::fromUtf8("pushButtonSetTargetValue"));
        pushButtonSetTargetValue->setGeometry(QRect(210, 790, 151, 34));
        pushButtonReqTargetValue = new QPushButton(centralWidget);
        pushButtonReqTargetValue->setObjectName(QString::fromUtf8("pushButtonReqTargetValue"));
        pushButtonReqTargetValue->setGeometry(QRect(50, 790, 151, 34));
        LEDControl16GTesterClass->setCentralWidget(centralWidget);

        retranslateUi(LEDControl16GTesterClass);

        QMetaObject::connectSlotsByName(LEDControl16GTesterClass);
    } // setupUi

    void retranslateUi(QMainWindow *LEDControl16GTesterClass)
    {
        LEDControl16GTesterClass->setWindowTitle(QCoreApplication::translate("LEDControl16GTesterClass", "LEDControl16GTester", nullptr));
        pushButtonReqVersion->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Req Version", nullptr));
        pushButtonReqAttr->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Req Attr", nullptr));
        label->setText(QCoreApplication::translate("LEDControl16GTesterClass", "DIPSW", nullptr));
        checkBoxTestLED->setText(QCoreApplication::translate("LEDControl16GTesterClass", "TestLED", nullptr));
        checkBoxReset->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Reset", nullptr));
        checkBoxPLSEnable->setText(QCoreApplication::translate("LEDControl16GTesterClass", "PLSEnable", nullptr));
        pushButtonSetAttr->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Output Attr", nullptr));
        label_2->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Pattern", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("LEDControl16GTesterClass", "BaseCounter", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("LEDControl16GTesterClass", "HighCounter", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Target", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Analog", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("LEDControl16GTesterClass", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("LEDControl16GTesterClass", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("LEDControl16GTesterClass", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("LEDControl16GTesterClass", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("LEDControl16GTesterClass", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("LEDControl16GTesterClass", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("LEDControl16GTesterClass", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("LEDControl16GTesterClass", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("LEDControl16GTesterClass", "8", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("LEDControl16GTesterClass", "9", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("LEDControl16GTesterClass", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(11);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("LEDControl16GTesterClass", "11", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->verticalHeaderItem(12);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("LEDControl16GTesterClass", "12", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->verticalHeaderItem(13);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("LEDControl16GTesterClass", "13", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->verticalHeaderItem(14);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("LEDControl16GTesterClass", "14", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->verticalHeaderItem(15);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("LEDControl16GTesterClass", "15", nullptr));
        pushButtonReqBaseCounter->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Req Base counter", nullptr));
        pushButtonSetBaseCounter->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Set Base counter", nullptr));
        pushButtonReqHighCounter->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Req High counter", nullptr));
        pushButtonSetHighCounter->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Set High counter", nullptr));
        pushButtonReqAnalog->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Req Analog", nullptr));
        label_3->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Comm upper", nullptr));
        label_4->setText(QCoreApplication::translate("LEDControl16GTesterClass", "IN", nullptr));
        checkBoxI_iCLK->setText(QCoreApplication::translate("LEDControl16GTesterClass", "I_iCLK", nullptr));
        checkBoxI_iCmdW->setText(QCoreApplication::translate("LEDControl16GTesterClass", "I_iCmdW", nullptr));
        checkBoxI_iRESET->setText(QCoreApplication::translate("LEDControl16GTesterClass", "I_iRESET", nullptr));
        checkBoxI_iStrobe->setText(QCoreApplication::translate("LEDControl16GTesterClass", "I_iStrobe", nullptr));
        label_5->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Comm FPGA", nullptr));
        label_6->setText(QCoreApplication::translate("LEDControl16GTesterClass", "IN", nullptr));
        pushButtonReqBit->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Req Bit", nullptr));
        label_11->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Key", nullptr));
        label_7->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Comm upper", nullptr));
        label_8->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Comm FPGA", nullptr));
        checkBoxO_InRW->setText(QCoreApplication::translate("LEDControl16GTesterClass", "O_InRW", nullptr));
        checkBoxO_InClk->setText(QCoreApplication::translate("LEDControl16GTesterClass", "O_InClk", nullptr));
        checkBoxO_InCS->setText(QCoreApplication::translate("LEDControl16GTesterClass", "O_InCS", nullptr));
        label_9->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Out", nullptr));
        pushButtonOutBit->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Out Bit", nullptr));
        label_10->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Out", nullptr));
        pushButtonOutRPOut->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Out Bit", nullptr));
        pushButtonSetTargetValue->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Set Target", nullptr));
        pushButtonReqTargetValue->setText(QCoreApplication::translate("LEDControl16GTesterClass", "Req Target", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LEDControl16GTesterClass: public Ui_LEDControl16GTesterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEDCONTROL16GTESTER_H
