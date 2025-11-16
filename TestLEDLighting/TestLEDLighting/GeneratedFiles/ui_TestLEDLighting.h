/********************************************************************************
** Form generated from reading UI file 'TestLEDLighting.ui'
**
** Created: Mon Sep 8 18:42:44 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTLEDLIGHTING_H
#define UI_TESTLEDLIGHTING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestLEDLightingClass
{
public:
    QPushButton *pbClose;
    QDockWidget *dwTestInput;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    QFrame *fmTestInput;
    QFrame *fmBar;
    QTableWidget *twBar;
    QLineEdit *leBar;
    QPushButton *pbOneOn;
    QPushButton *pbAllOff;
    QLineEdit *lbBar;
    QPushButton *pbAllOn;
    QPushButton *pbDetails;
    QFrame *fmBrightness;
    QTableWidget *twBrightness;
    QSpinBox *sbBrightness;
    QCheckBox *chkMultiple;
    QLineEdit *lbLED;
    QLineEdit *lbBrightness;
    QFrame *fmLED;
    QTableWidget *twLED;
    QLineEdit *leLED;
    QPushButton *pbNextOn;
    QDockWidget *dwContinueTest;
    QWidget *dockWidgetContents_2;
    QGridLayout *gridLayout1;
    QFrame *fmContinueTest;
    QLineEdit *leSwitchTime;
    QSpinBox *sbSwitchTime;
    QPushButton *pbStartPosClear;
    QPushButton *pbStart;
    QProgressBar *pgbLight;

    void setupUi(QWidget *TestLEDLightingClass)
    {
        if (TestLEDLightingClass->objectName().isEmpty())
            TestLEDLightingClass->setObjectName(QString::fromUtf8("TestLEDLightingClass"));
        TestLEDLightingClass->resize(575, 558);
        pbClose = new QPushButton(TestLEDLightingClass);
        pbClose->setObjectName(QString::fromUtf8("pbClose"));
        pbClose->setGeometry(QRect(470, 500, 91, 41));
        dwTestInput = new QDockWidget(TestLEDLightingClass);
        dwTestInput->setObjectName(QString::fromUtf8("dwTestInput"));
        dwTestInput->setGeometry(QRect(10, 10, 321, 541));
        dwTestInput->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        fmTestInput = new QFrame(dockWidgetContents);
        fmTestInput->setObjectName(QString::fromUtf8("fmTestInput"));
        fmTestInput->setFrameShape(QFrame::Panel);
        fmTestInput->setFrameShadow(QFrame::Raised);
        fmBar = new QFrame(fmTestInput);
        fmBar->setObjectName(QString::fromUtf8("fmBar"));
        fmBar->setGeometry(QRect(110, 30, 51, 461));
        fmBar->setAutoFillBackground(true);
        fmBar->setFrameShape(QFrame::Panel);
        fmBar->setFrameShadow(QFrame::Raised);
        twBar = new QTableWidget(fmBar);
        twBar->setObjectName(QString::fromUtf8("twBar"));
        twBar->setGeometry(QRect(10, 10, 25, 265));
        leBar = new QLineEdit(fmBar);
        leBar->setObjectName(QString::fromUtf8("leBar"));
        leBar->setGeometry(QRect(10, 280, 25, 20));
        pbOneOn = new QPushButton(fmTestInput);
        pbOneOn->setObjectName(QString::fromUtf8("pbOneOn"));
        pbOneOn->setGeometry(QRect(230, 260, 60, 61));
        pbAllOff = new QPushButton(fmTestInput);
        pbAllOff->setObjectName(QString::fromUtf8("pbAllOff"));
        pbAllOff->setGeometry(QRect(10, 150, 91, 41));
        lbBar = new QLineEdit(fmTestInput);
        lbBar->setObjectName(QString::fromUtf8("lbBar"));
        lbBar->setGeometry(QRect(110, 10, 51, 20));
        lbBar->setAlignment(Qt::AlignCenter);
        lbBar->setReadOnly(true);
        pbAllOn = new QPushButton(fmTestInput);
        pbAllOn->setObjectName(QString::fromUtf8("pbAllOn"));
        pbAllOn->setGeometry(QRect(10, 70, 91, 41));
        pbDetails = new QPushButton(fmTestInput);
        pbDetails->setObjectName(QString::fromUtf8("pbDetails"));
        pbDetails->setGeometry(QRect(10, 450, 91, 41));
        fmBrightness = new QFrame(fmTestInput);
        fmBrightness->setObjectName(QString::fromUtf8("fmBrightness"));
        fmBrightness->setGeometry(QRect(230, 30, 51, 211));
        fmBrightness->setAutoFillBackground(true);
        fmBrightness->setFrameShape(QFrame::Panel);
        fmBrightness->setFrameShadow(QFrame::Raised);
        twBrightness = new QTableWidget(fmBrightness);
        twBrightness->setObjectName(QString::fromUtf8("twBrightness"));
        twBrightness->setGeometry(QRect(10, 10, 25, 150));
        sbBrightness = new QSpinBox(fmBrightness);
        sbBrightness->setObjectName(QString::fromUtf8("sbBrightness"));
        sbBrightness->setGeometry(QRect(4, 170, 42, 22));
        sbBrightness->setMaximum(40);
        chkMultiple = new QCheckBox(fmTestInput);
        chkMultiple->setObjectName(QString::fromUtf8("chkMultiple"));
        chkMultiple->setGeometry(QRect(230, 460, 61, 17));
        lbLED = new QLineEdit(fmTestInput);
        lbLED->setObjectName(QString::fromUtf8("lbLED"));
        lbLED->setGeometry(QRect(170, 10, 51, 20));
        lbLED->setAlignment(Qt::AlignCenter);
        lbLED->setReadOnly(true);
        lbBrightness = new QLineEdit(fmTestInput);
        lbBrightness->setObjectName(QString::fromUtf8("lbBrightness"));
        lbBrightness->setGeometry(QRect(230, 10, 51, 20));
        lbBrightness->setAlignment(Qt::AlignCenter);
        lbBrightness->setReadOnly(true);
        fmLED = new QFrame(fmTestInput);
        fmLED->setObjectName(QString::fromUtf8("fmLED"));
        fmLED->setGeometry(QRect(170, 30, 51, 461));
        fmLED->setAutoFillBackground(true);
        fmLED->setFrameShape(QFrame::Panel);
        fmLED->setFrameShadow(QFrame::Raised);
        twLED = new QTableWidget(fmLED);
        twLED->setObjectName(QString::fromUtf8("twLED"));
        twLED->setGeometry(QRect(10, 10, 25, 420));
        leLED = new QLineEdit(fmLED);
        leLED->setObjectName(QString::fromUtf8("leLED"));
        leLED->setGeometry(QRect(10, 435, 25, 20));
        pbNextOn = new QPushButton(fmTestInput);
        pbNextOn->setObjectName(QString::fromUtf8("pbNextOn"));
        pbNextOn->setGeometry(QRect(230, 330, 60, 61));

        gridLayout->addWidget(fmTestInput, 0, 0, 1, 1);

        dwTestInput->setWidget(dockWidgetContents);
        dwContinueTest = new QDockWidget(TestLEDLightingClass);
        dwContinueTest->setObjectName(QString::fromUtf8("dwContinueTest"));
        dwContinueTest->setGeometry(QRect(330, 10, 241, 271));
        dwContinueTest->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        gridLayout1 = new QGridLayout(dockWidgetContents_2);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        fmContinueTest = new QFrame(dockWidgetContents_2);
        fmContinueTest->setObjectName(QString::fromUtf8("fmContinueTest"));
        fmContinueTest->setFrameShape(QFrame::Panel);
        fmContinueTest->setFrameShadow(QFrame::Raised);
        leSwitchTime = new QLineEdit(fmContinueTest);
        leSwitchTime->setObjectName(QString::fromUtf8("leSwitchTime"));
        leSwitchTime->setGeometry(QRect(70, 40, 71, 20));
        leSwitchTime->setAlignment(Qt::AlignCenter);
        leSwitchTime->setReadOnly(true);
        sbSwitchTime = new QSpinBox(fmContinueTest);
        sbSwitchTime->setObjectName(QString::fromUtf8("sbSwitchTime"));
        sbSwitchTime->setGeometry(QRect(70, 60, 71, 22));
        sbSwitchTime->setMaximum(99999);
        pbStartPosClear = new QPushButton(fmContinueTest);
        pbStartPosClear->setObjectName(QString::fromUtf8("pbStartPosClear"));
        pbStartPosClear->setGeometry(QRect(10, 110, 111, 41));
        pbStart = new QPushButton(fmContinueTest);
        pbStart->setObjectName(QString::fromUtf8("pbStart"));
        pbStart->setGeometry(QRect(10, 170, 201, 51));

        gridLayout1->addWidget(fmContinueTest, 0, 0, 1, 1);

        dwContinueTest->setWidget(dockWidgetContents_2);
        pgbLight = new QProgressBar(TestLEDLightingClass);
        pgbLight->setObjectName(QString::fromUtf8("pgbLight"));
        pgbLight->setGeometry(QRect(340, 290, 221, 23));
        pgbLight->setValue(0);

        retranslateUi(TestLEDLightingClass);

        QMetaObject::connectSlotsByName(TestLEDLightingClass);
    } // setupUi

    void retranslateUi(QWidget *TestLEDLightingClass)
    {
        TestLEDLightingClass->setWindowTitle(QApplication::translate("TestLEDLightingClass", "TestLEDLighting", 0, QApplication::UnicodeUTF8));
        pbClose->setText(QApplication::translate("TestLEDLightingClass", "Close", 0, QApplication::UnicodeUTF8));
        pbOneOn->setText(QApplication::translate("TestLEDLightingClass", "One On", 0, QApplication::UnicodeUTF8));
        pbAllOff->setText(QApplication::translate("TestLEDLightingClass", "All Off", 0, QApplication::UnicodeUTF8));
        lbBar->setText(QApplication::translate("TestLEDLightingClass", "Bar", 0, QApplication::UnicodeUTF8));
        pbAllOn->setText(QApplication::translate("TestLEDLightingClass", "All On", 0, QApplication::UnicodeUTF8));
        pbDetails->setText(QApplication::translate("TestLEDLightingClass", "Details", 0, QApplication::UnicodeUTF8));
        chkMultiple->setText(QApplication::translate("TestLEDLightingClass", "Multiple", 0, QApplication::UnicodeUTF8));
        lbLED->setText(QApplication::translate("TestLEDLightingClass", "LED", 0, QApplication::UnicodeUTF8));
        lbBrightness->setText(QApplication::translate("TestLEDLightingClass", "Bright", 0, QApplication::UnicodeUTF8));
        pbNextOn->setText(QApplication::translate("TestLEDLightingClass", "Next On", 0, QApplication::UnicodeUTF8));
        leSwitchTime->setText(QApplication::translate("TestLEDLightingClass", "Switch Time", 0, QApplication::UnicodeUTF8));
        pbStartPosClear->setText(QApplication::translate("TestLEDLightingClass", "Start position clear", 0, QApplication::UnicodeUTF8));
        pbStart->setText(QApplication::translate("TestLEDLightingClass", "Start", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TestLEDLightingClass: public Ui_TestLEDLightingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTLEDLIGHTING_H
