/********************************************************************************
** Form generated from reading UI file 'EachThresholdFormMultiSpot.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EACHTHRESHOLDFORMMULTISPOT_H
#define UI_EACHTHRESHOLDFORMMULTISPOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EachThresholdFormMultiSpot
{
public:
    QToolButton *toolButtonCancel;
    QFrame *frame_3;
    QLabel *labelK_5;
    QSlider *horizontalSliderSIze;
    QDoubleSpinBox *doubleSpinBoxSizeMM;
    QLabel *labelK_4;
    QLabel *labelK_3;
    QSpinBox *spinBoxSize;
    QSlider *horizontalSliderNGCount;
    QLabel *labelK_6;
    QSpinBox *spinBoxNGCount;
    QLabel *labelK_7;
    QLabel *labelK_8;
    QLabel *label;
    QToolButton *toolButtonOK;
    QFrame *frameMarkerImage;
    QPushButton *PushButtonMarker;
    QPushButton *PushButtonShowWhole;
    QFrame *frameThresholdLevel;
    QLabel *labelK_9;

    void setupUi(QWidget *EachThresholdFormMultiSpot)
    {
        if (EachThresholdFormMultiSpot->objectName().isEmpty())
            EachThresholdFormMultiSpot->setObjectName("EachThresholdFormMultiSpot");
        EachThresholdFormMultiSpot->resize(1187, 766);
        toolButtonCancel = new QToolButton(EachThresholdFormMultiSpot);
        toolButtonCancel->setObjectName("toolButtonCancel");
        toolButtonCancel->setGeometry(QRect(890, 680, 161, 81));
        QFont font;
        font.setPointSize(16);
        toolButtonCancel->setFont(font);
        toolButtonCancel->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        frame_3 = new QFrame(EachThresholdFormMultiSpot);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 200, 551, 401));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        labelK_5 = new QLabel(frame_3);
        labelK_5->setObjectName("labelK_5");
        labelK_5->setGeometry(QRect(460, 180, 81, 36));
        QFont font1;
        font1.setPointSize(11);
        labelK_5->setFont(font1);
        labelK_5->setAlignment(Qt::AlignCenter);
        horizontalSliderSIze = new QSlider(frame_3);
        horizontalSliderSIze->setObjectName("horizontalSliderSIze");
        horizontalSliderSIze->setGeometry(QRect(20, 150, 311, 51));
        horizontalSliderSIze->setOrientation(Qt::Horizontal);
        doubleSpinBoxSizeMM = new QDoubleSpinBox(frame_3);
        doubleSpinBoxSizeMM->setObjectName("doubleSpinBoxSizeMM");
        doubleSpinBoxSizeMM->setGeometry(QRect(340, 140, 111, 36));
        doubleSpinBoxSizeMM->setFont(font);
        doubleSpinBoxSizeMM->setMaximum(10000.000000000000000);
        doubleSpinBoxSizeMM->setValue(0.500000000000000);
        labelK_4 = new QLabel(frame_3);
        labelK_4->setObjectName("labelK_4");
        labelK_4->setGeometry(QRect(460, 140, 71, 36));
        QFont font2;
        font2.setPointSize(14);
        labelK_4->setFont(font2);
        labelK_4->setAlignment(Qt::AlignCenter);
        labelK_3 = new QLabel(frame_3);
        labelK_3->setObjectName("labelK_3");
        labelK_3->setGeometry(QRect(10, 0, 421, 51));
        QFont font3;
        font3.setPointSize(18);
        labelK_3->setFont(font3);
        labelK_3->setAlignment(Qt::AlignCenter);
        spinBoxSize = new QSpinBox(frame_3);
        spinBoxSize->setObjectName("spinBoxSize");
        spinBoxSize->setGeometry(QRect(340, 180, 111, 36));
        spinBoxSize->setFont(font);
        spinBoxSize->setMaximum(99999999);
        spinBoxSize->setValue(2000);
        horizontalSliderNGCount = new QSlider(frame_3);
        horizontalSliderNGCount->setObjectName("horizontalSliderNGCount");
        horizontalSliderNGCount->setGeometry(QRect(20, 290, 311, 51));
        horizontalSliderNGCount->setOrientation(Qt::Horizontal);
        labelK_6 = new QLabel(frame_3);
        labelK_6->setObjectName("labelK_6");
        labelK_6->setGeometry(QRect(460, 290, 41, 41));
        labelK_6->setFont(font1);
        labelK_6->setAlignment(Qt::AlignCenter);
        spinBoxNGCount = new QSpinBox(frame_3);
        spinBoxNGCount->setObjectName("spinBoxNGCount");
        spinBoxNGCount->setGeometry(QRect(340, 290, 111, 41));
        spinBoxNGCount->setFont(font);
        spinBoxNGCount->setMaximum(99999999);
        spinBoxNGCount->setValue(2000);
        labelK_7 = new QLabel(frame_3);
        labelK_7->setObjectName("labelK_7");
        labelK_7->setGeometry(QRect(10, 90, 511, 41));
        labelK_7->setFont(font2);
        labelK_7->setFrameShape(QFrame::Panel);
        labelK_7->setFrameShadow(QFrame::Sunken);
        labelK_7->setAlignment(Qt::AlignCenter);
        labelK_8 = new QLabel(frame_3);
        labelK_8->setObjectName("labelK_8");
        labelK_8->setGeometry(QRect(10, 240, 511, 41));
        labelK_8->setFont(font2);
        labelK_8->setFrameShape(QFrame::Panel);
        labelK_8->setFrameShadow(QFrame::Sunken);
        labelK_8->setAlignment(Qt::AlignCenter);
        label = new QLabel(EachThresholdFormMultiSpot);
        label->setObjectName("label");
        label->setGeometry(QRect(580, 80, 591, 31));
        QFont font4;
        font4.setPointSize(12);
        label->setFont(font4);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        toolButtonOK = new QToolButton(EachThresholdFormMultiSpot);
        toolButtonOK->setObjectName("toolButtonOK");
        toolButtonOK->setGeometry(QRect(720, 680, 161, 81));
        toolButtonOK->setFont(font);
        toolButtonOK->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        frameMarkerImage = new QFrame(EachThresholdFormMultiSpot);
        frameMarkerImage->setObjectName("frameMarkerImage");
        frameMarkerImage->setGeometry(QRect(580, 113, 591, 551));
        frameMarkerImage->setFrameShape(QFrame::StyledPanel);
        frameMarkerImage->setFrameShadow(QFrame::Raised);
        PushButtonMarker = new QPushButton(EachThresholdFormMultiSpot);
        PushButtonMarker->setObjectName("PushButtonMarker");
        PushButtonMarker->setGeometry(QRect(590, 10, 271, 51));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font5.setPointSize(24);
        PushButtonMarker->setFont(font5);
        PushButtonMarker->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed{ 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(160, 225, 160, 255), stop:1 rgba(80, 141, 80, 255));\n"
"}"));
        PushButtonMarker->setCheckable(false);
        PushButtonMarker->setChecked(false);
        PushButtonMarker->setAutoDefault(false);
        PushButtonMarker->setFlat(false);
        PushButtonShowWhole = new QPushButton(EachThresholdFormMultiSpot);
        PushButtonShowWhole->setObjectName("PushButtonShowWhole");
        PushButtonShowWhole->setGeometry(QRect(880, 10, 261, 51));
        PushButtonShowWhole->setFont(font5);
        PushButtonShowWhole->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed{ 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(160, 225, 160, 255), stop:1 rgba(80, 141, 80, 255));\n"
"}"));
        PushButtonShowWhole->setCheckable(false);
        PushButtonShowWhole->setChecked(false);
        PushButtonShowWhole->setAutoDefault(false);
        PushButtonShowWhole->setFlat(false);
        frameThresholdLevel = new QFrame(EachThresholdFormMultiSpot);
        frameThresholdLevel->setObjectName("frameThresholdLevel");
        frameThresholdLevel->setGeometry(QRect(10, 10, 551, 181));
        frameThresholdLevel->setFrameShape(QFrame::Panel);
        frameThresholdLevel->setFrameShadow(QFrame::Sunken);
        labelK_9 = new QLabel(frameThresholdLevel);
        labelK_9->setObjectName("labelK_9");
        labelK_9->setGeometry(QRect(0, 0, 551, 31));
        labelK_9->setFont(font2);
        labelK_9->setAlignment(Qt::AlignCenter);

        retranslateUi(EachThresholdFormMultiSpot);

        PushButtonMarker->setDefault(false);
        PushButtonShowWhole->setDefault(false);


        QMetaObject::connectSlotsByName(EachThresholdFormMultiSpot);
    } // setupUi

    void retranslateUi(QWidget *EachThresholdFormMultiSpot)
    {
        EachThresholdFormMultiSpot->setWindowTitle(QCoreApplication::translate("EachThresholdFormMultiSpot", "\345\244\232\347\202\271\346\244\234\346\237\273", nullptr));
        toolButtonCancel->setText(QCoreApplication::translate("EachThresholdFormMultiSpot", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        labelK_5->setText(QCoreApplication::translate("EachThresholdFormMultiSpot", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_4->setText(QCoreApplication::translate("EachThresholdFormMultiSpot", "mm2", nullptr));
        labelK_3->setText(QCoreApplication::translate("EachThresholdFormMultiSpot", "NG\343\201\253\343\201\231\343\202\213\345\260\217\343\201\225\343\201\252\347\202\271", nullptr));
        labelK_6->setText(QCoreApplication::translate("EachThresholdFormMultiSpot", "\345\200\213", nullptr));
        labelK_7->setText(QCoreApplication::translate("EachThresholdFormMultiSpot", "\345\260\217\343\201\225\343\201\252\347\202\271\343\201\256\351\235\242\347\251\215", nullptr));
        labelK_8->setText(QCoreApplication::translate("EachThresholdFormMultiSpot", "NG\345\210\244\345\256\232\343\201\231\343\202\213\345\200\213\346\225\260", nullptr));
        label->setText(QCoreApplication::translate("EachThresholdFormMultiSpot", "\346\244\234\346\237\273\347\224\273\345\203\217", nullptr));
        toolButtonOK->setText(QCoreApplication::translate("EachThresholdFormMultiSpot", "\350\250\255\345\256\232", nullptr));
        PushButtonMarker->setText(QCoreApplication::translate("EachThresholdFormMultiSpot", "\343\203\236\343\203\274\343\202\253\343\203\274", nullptr));
        PushButtonShowWhole->setText(QCoreApplication::translate("EachThresholdFormMultiSpot", "\345\205\250\344\275\223\350\241\250\347\244\272", nullptr));
        labelK_9->setText(QCoreApplication::translate("EachThresholdFormMultiSpot", "\343\203\254\343\203\231\343\203\253\347\242\272\350\252\215\357\274\217\350\250\255\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EachThresholdFormMultiSpot: public Ui_EachThresholdFormMultiSpot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EACHTHRESHOLDFORMMULTISPOT_H
