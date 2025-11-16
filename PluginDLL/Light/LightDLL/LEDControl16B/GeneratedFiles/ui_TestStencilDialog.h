/********************************************************************************
** Form generated from reading UI file 'TestStencilDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTSTENCILDIALOG_H
#define UI_TESTSTENCILDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_TestStencilDialog
{
public:
    QPushButton *pushButtonSetCameraResolution;
    QPushButton *pushButtonReqCameraResolution;
    QLabel *labelCameraResolution;
    QSpinBox *spinBoxCameraResolution;
    QFrame *frame;
    QLabel *labelCameraResolution_2;
    QSpinBox *spinBoxBoardNo;
    QLabel *labelCameraResolution_3;
    QPushButton *pushButtonReqMotorCounter;
    QSpinBox *spinBoxMotorCounter;
    QTableWidget *tableWidgetEnableComparator;
    QLabel *labelCameraResolution_4;
    QPushButton *pushButtonSetEnableComparator;
    QPushButton *pushButtonReqEnableComparator;
    QLabel *labelCameraResolution_5;
    QSpinBox *spinBoxUnitNo;
    QPushButton *pushButtonAllOff;
    QPushButton *pushButtonCalc;
    QSpinBox *spinBoxCalcA;
    QSpinBox *spinBoxCalcB;
    QPushButton *pushButtonSetMotorCounter;
    QPushButton *pushButtonOK;
    QToolButton *toolButtonRelay;

    void setupUi(QDialog *TestStencilDialog)
    {
        if (TestStencilDialog->objectName().isEmpty())
            TestStencilDialog->setObjectName("TestStencilDialog");
        TestStencilDialog->resize(627, 776);
        pushButtonSetCameraResolution = new QPushButton(TestStencilDialog);
        pushButtonSetCameraResolution->setObjectName("pushButtonSetCameraResolution");
        pushButtonSetCameraResolution->setGeometry(QRect(520, 20, 81, 34));
        pushButtonReqCameraResolution = new QPushButton(TestStencilDialog);
        pushButtonReqCameraResolution->setObjectName("pushButtonReqCameraResolution");
        pushButtonReqCameraResolution->setGeometry(QRect(430, 20, 81, 34));
        labelCameraResolution = new QLabel(TestStencilDialog);
        labelCameraResolution->setObjectName("labelCameraResolution");
        labelCameraResolution->setGeometry(QRect(20, 20, 271, 31));
        labelCameraResolution->setFrameShape(QFrame::Panel);
        labelCameraResolution->setFrameShadow(QFrame::Sunken);
        spinBoxCameraResolution = new QSpinBox(TestStencilDialog);
        spinBoxCameraResolution->setObjectName("spinBoxCameraResolution");
        spinBoxCameraResolution->setGeometry(QRect(300, 20, 111, 31));
        spinBoxCameraResolution->setMaximum(99999999);
        frame = new QFrame(TestStencilDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 80, 601, 631));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        labelCameraResolution_2 = new QLabel(frame);
        labelCameraResolution_2->setObjectName("labelCameraResolution_2");
        labelCameraResolution_2->setGeometry(QRect(10, 50, 81, 31));
        labelCameraResolution_2->setFrameShape(QFrame::Panel);
        labelCameraResolution_2->setFrameShadow(QFrame::Sunken);
        spinBoxBoardNo = new QSpinBox(frame);
        spinBoxBoardNo->setObjectName("spinBoxBoardNo");
        spinBoxBoardNo->setGeometry(QRect(100, 50, 61, 31));
        labelCameraResolution_3 = new QLabel(frame);
        labelCameraResolution_3->setObjectName("labelCameraResolution_3");
        labelCameraResolution_3->setGeometry(QRect(10, 100, 271, 31));
        labelCameraResolution_3->setFrameShape(QFrame::Panel);
        labelCameraResolution_3->setFrameShadow(QFrame::Sunken);
        pushButtonReqMotorCounter = new QPushButton(frame);
        pushButtonReqMotorCounter->setObjectName("pushButtonReqMotorCounter");
        pushButtonReqMotorCounter->setGeometry(QRect(420, 100, 81, 34));
        spinBoxMotorCounter = new QSpinBox(frame);
        spinBoxMotorCounter->setObjectName("spinBoxMotorCounter");
        spinBoxMotorCounter->setGeometry(QRect(290, 100, 111, 31));
        spinBoxMotorCounter->setMaximum(99999999);
        tableWidgetEnableComparator = new QTableWidget(frame);
        if (tableWidgetEnableComparator->columnCount() < 3)
            tableWidgetEnableComparator->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetEnableComparator->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetEnableComparator->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetEnableComparator->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetEnableComparator->setObjectName("tableWidgetEnableComparator");
        tableWidgetEnableComparator->setGeometry(QRect(10, 180, 491, 431));
        labelCameraResolution_4 = new QLabel(frame);
        labelCameraResolution_4->setObjectName("labelCameraResolution_4");
        labelCameraResolution_4->setGeometry(QRect(10, 150, 491, 28));
        labelCameraResolution_4->setFrameShape(QFrame::Panel);
        labelCameraResolution_4->setFrameShadow(QFrame::Sunken);
        pushButtonSetEnableComparator = new QPushButton(frame);
        pushButtonSetEnableComparator->setObjectName("pushButtonSetEnableComparator");
        pushButtonSetEnableComparator->setGeometry(QRect(510, 330, 81, 34));
        pushButtonReqEnableComparator = new QPushButton(frame);
        pushButtonReqEnableComparator->setObjectName("pushButtonReqEnableComparator");
        pushButtonReqEnableComparator->setGeometry(QRect(510, 260, 81, 34));
        labelCameraResolution_5 = new QLabel(frame);
        labelCameraResolution_5->setObjectName("labelCameraResolution_5");
        labelCameraResolution_5->setGeometry(QRect(10, 10, 81, 31));
        labelCameraResolution_5->setFrameShape(QFrame::Panel);
        labelCameraResolution_5->setFrameShadow(QFrame::Sunken);
        spinBoxUnitNo = new QSpinBox(frame);
        spinBoxUnitNo->setObjectName("spinBoxUnitNo");
        spinBoxUnitNo->setGeometry(QRect(100, 10, 61, 31));
        pushButtonAllOff = new QPushButton(frame);
        pushButtonAllOff->setObjectName("pushButtonAllOff");
        pushButtonAllOff->setGeometry(QRect(511, 570, 81, 34));
        pushButtonCalc = new QPushButton(frame);
        pushButtonCalc->setObjectName("pushButtonCalc");
        pushButtonCalc->setGeometry(QRect(510, 500, 81, 34));
        spinBoxCalcA = new QSpinBox(frame);
        spinBoxCalcA->setObjectName("spinBoxCalcA");
        spinBoxCalcA->setGeometry(QRect(510, 430, 61, 24));
        spinBoxCalcA->setMaximum(9999);
        spinBoxCalcA->setValue(32);
        spinBoxCalcB = new QSpinBox(frame);
        spinBoxCalcB->setObjectName("spinBoxCalcB");
        spinBoxCalcB->setGeometry(QRect(510, 460, 61, 24));
        spinBoxCalcB->setMaximum(99999999);
        spinBoxCalcB->setValue(10);
        pushButtonSetMotorCounter = new QPushButton(frame);
        pushButtonSetMotorCounter->setObjectName("pushButtonSetMotorCounter");
        pushButtonSetMotorCounter->setGeometry(QRect(510, 100, 81, 34));
        pushButtonOK = new QPushButton(TestStencilDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(460, 720, 151, 41));
        toolButtonRelay = new QToolButton(TestStencilDialog);
        toolButtonRelay->setObjectName("toolButtonRelay");
        toolButtonRelay->setGeometry(QRect(30, 720, 181, 41));
        toolButtonRelay->setCheckable(true);

        retranslateUi(TestStencilDialog);

        QMetaObject::connectSlotsByName(TestStencilDialog);
    } // setupUi

    void retranslateUi(QDialog *TestStencilDialog)
    {
        TestStencilDialog->setWindowTitle(QCoreApplication::translate("TestStencilDialog", "Dialog", nullptr));
        pushButtonSetCameraResolution->setText(QCoreApplication::translate("TestStencilDialog", "Send", nullptr));
        pushButtonReqCameraResolution->setText(QCoreApplication::translate("TestStencilDialog", "Req", nullptr));
        labelCameraResolution->setText(QCoreApplication::translate("TestStencilDialog", "Camera resolution", nullptr));
        labelCameraResolution_2->setText(QCoreApplication::translate("TestStencilDialog", "Board", nullptr));
        labelCameraResolution_3->setText(QCoreApplication::translate("TestStencilDialog", "MotorCounter", nullptr));
        pushButtonReqMotorCounter->setText(QCoreApplication::translate("TestStencilDialog", "Req", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetEnableComparator->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TestStencilDialog", "EnableComparatorL", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetEnableComparator->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TestStencilDialog", "EnableComparatorH", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetEnableComparator->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("TestStencilDialog", "ForceON", nullptr));
        labelCameraResolution_4->setText(QCoreApplication::translate("TestStencilDialog", "Light Term", nullptr));
        pushButtonSetEnableComparator->setText(QCoreApplication::translate("TestStencilDialog", "Send", nullptr));
        pushButtonReqEnableComparator->setText(QCoreApplication::translate("TestStencilDialog", "Req", nullptr));
        labelCameraResolution_5->setText(QCoreApplication::translate("TestStencilDialog", "Unit", nullptr));
        pushButtonAllOff->setText(QCoreApplication::translate("TestStencilDialog", "All off", nullptr));
        pushButtonCalc->setText(QCoreApplication::translate("TestStencilDialog", "Calc", nullptr));
        pushButtonSetMotorCounter->setText(QCoreApplication::translate("TestStencilDialog", "Send", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("TestStencilDialog", "OK", nullptr));
        toolButtonRelay->setText(QCoreApplication::translate("TestStencilDialog", "Relay", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestStencilDialog: public Ui_TestStencilDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTSTENCILDIALOG_H
