/********************************************************************************
** Form generated from reading UI file 'EachThresholdFormOozing.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EACHTHRESHOLDFORMOOZING_H
#define UI_EACHTHRESHOLDFORMOOZING_H

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

class Ui_EachThresholdFormOozing
{
public:
    QFrame *frameMarkerImage;
    QPushButton *PushButtonMarker;
    QToolButton *toolButtonCancel;
    QLabel *label;
    QToolButton *toolButtonOK;
    QFrame *frame_3;
    QLabel *labelK_5;
    QSlider *horizontalSliderOozing;
    QDoubleSpinBox *doubleSpinBoxOozingMM;
    QLabel *labelK_4;
    QLabel *labelK_3;
    QSpinBox *spinBoxOozing;
    QPushButton *PushButtonShowWhole;
    QFrame *frameThresholdLevel;
    QLabel *labelK_8;

    void setupUi(QWidget *EachThresholdFormOozing)
    {
        if (EachThresholdFormOozing->objectName().isEmpty())
            EachThresholdFormOozing->setObjectName("EachThresholdFormOozing");
        EachThresholdFormOozing->resize(1165, 840);
        frameMarkerImage = new QFrame(EachThresholdFormOozing);
        frameMarkerImage->setObjectName("frameMarkerImage");
        frameMarkerImage->setGeometry(QRect(580, 113, 571, 611));
        frameMarkerImage->setFrameShape(QFrame::StyledPanel);
        frameMarkerImage->setFrameShadow(QFrame::Raised);
        PushButtonMarker = new QPushButton(EachThresholdFormOozing);
        PushButtonMarker->setObjectName("PushButtonMarker");
        PushButtonMarker->setGeometry(QRect(590, 10, 261, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font.setPointSize(24);
        PushButtonMarker->setFont(font);
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
        toolButtonCancel = new QToolButton(EachThresholdFormOozing);
        toolButtonCancel->setObjectName("toolButtonCancel");
        toolButtonCancel->setGeometry(QRect(880, 740, 161, 81));
        QFont font1;
        font1.setPointSize(16);
        toolButtonCancel->setFont(font1);
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
        label = new QLabel(EachThresholdFormOozing);
        label->setObjectName("label");
        label->setGeometry(QRect(580, 80, 571, 31));
        QFont font2;
        font2.setPointSize(12);
        label->setFont(font2);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        toolButtonOK = new QToolButton(EachThresholdFormOozing);
        toolButtonOK->setObjectName("toolButtonOK");
        toolButtonOK->setGeometry(QRect(710, 740, 161, 81));
        toolButtonOK->setFont(font1);
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
        frame_3 = new QFrame(EachThresholdFormOozing);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 220, 551, 131));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        labelK_5 = new QLabel(frame_3);
        labelK_5->setObjectName("labelK_5");
        labelK_5->setGeometry(QRect(450, 80, 81, 36));
        QFont font3;
        font3.setPointSize(11);
        labelK_5->setFont(font3);
        labelK_5->setAlignment(Qt::AlignCenter);
        horizontalSliderOozing = new QSlider(frame_3);
        horizontalSliderOozing->setObjectName("horizontalSliderOozing");
        horizontalSliderOozing->setGeometry(QRect(10, 50, 311, 51));
        horizontalSliderOozing->setOrientation(Qt::Horizontal);
        doubleSpinBoxOozingMM = new QDoubleSpinBox(frame_3);
        doubleSpinBoxOozingMM->setObjectName("doubleSpinBoxOozingMM");
        doubleSpinBoxOozingMM->setGeometry(QRect(330, 40, 111, 36));
        doubleSpinBoxOozingMM->setFont(font1);
        doubleSpinBoxOozingMM->setMaximum(10000.000000000000000);
        doubleSpinBoxOozingMM->setValue(0.500000000000000);
        labelK_4 = new QLabel(frame_3);
        labelK_4->setObjectName("labelK_4");
        labelK_4->setGeometry(QRect(450, 40, 61, 36));
        QFont font4;
        font4.setPointSize(14);
        labelK_4->setFont(font4);
        labelK_4->setAlignment(Qt::AlignCenter);
        labelK_3 = new QLabel(frame_3);
        labelK_3->setObjectName("labelK_3");
        labelK_3->setGeometry(QRect(10, 0, 301, 51));
        QFont font5;
        font5.setPointSize(18);
        labelK_3->setFont(font5);
        labelK_3->setAlignment(Qt::AlignCenter);
        spinBoxOozing = new QSpinBox(frame_3);
        spinBoxOozing->setObjectName("spinBoxOozing");
        spinBoxOozing->setGeometry(QRect(330, 80, 111, 36));
        spinBoxOozing->setFont(font1);
        spinBoxOozing->setMaximum(99999999);
        spinBoxOozing->setValue(2000);
        PushButtonShowWhole = new QPushButton(EachThresholdFormOozing);
        PushButtonShowWhole->setObjectName("PushButtonShowWhole");
        PushButtonShowWhole->setGeometry(QRect(860, 10, 261, 51));
        PushButtonShowWhole->setFont(font);
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
        frameThresholdLevel = new QFrame(EachThresholdFormOozing);
        frameThresholdLevel->setObjectName("frameThresholdLevel");
        frameThresholdLevel->setGeometry(QRect(10, 10, 551, 201));
        frameThresholdLevel->setFrameShape(QFrame::Panel);
        frameThresholdLevel->setFrameShadow(QFrame::Sunken);
        labelK_8 = new QLabel(frameThresholdLevel);
        labelK_8->setObjectName("labelK_8");
        labelK_8->setGeometry(QRect(0, 0, 551, 31));
        labelK_8->setFont(font4);
        labelK_8->setAlignment(Qt::AlignCenter);

        retranslateUi(EachThresholdFormOozing);

        PushButtonMarker->setDefault(false);
        PushButtonShowWhole->setDefault(false);


        QMetaObject::connectSlotsByName(EachThresholdFormOozing);
    } // setupUi

    void retranslateUi(QWidget *EachThresholdFormOozing)
    {
        EachThresholdFormOozing->setWindowTitle(QCoreApplication::translate("EachThresholdFormOozing", "Setting", nullptr));
        PushButtonMarker->setText(QCoreApplication::translate("EachThresholdFormOozing", "\343\203\236\343\203\274\343\202\253\343\203\274", nullptr));
        toolButtonCancel->setText(QCoreApplication::translate("EachThresholdFormOozing", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        label->setText(QCoreApplication::translate("EachThresholdFormOozing", "\346\244\234\346\237\273\347\224\273\345\203\217", nullptr));
        toolButtonOK->setText(QCoreApplication::translate("EachThresholdFormOozing", "\350\250\255\345\256\232", nullptr));
        labelK_5->setText(QCoreApplication::translate("EachThresholdFormOozing", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_4->setText(QCoreApplication::translate("EachThresholdFormOozing", "mm", nullptr));
        labelK_3->setText(QCoreApplication::translate("EachThresholdFormOozing", "\343\201\253\343\201\230\343\201\277\351\207\217", nullptr));
        PushButtonShowWhole->setText(QCoreApplication::translate("EachThresholdFormOozing", "\345\205\250\344\275\223\350\241\250\347\244\272", nullptr));
        labelK_8->setText(QCoreApplication::translate("EachThresholdFormOozing", "\343\203\254\343\203\231\343\203\253\347\242\272\350\252\215\357\274\217\350\250\255\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EachThresholdFormOozing: public Ui_EachThresholdFormOozing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EACHTHRESHOLDFORMOOZING_H
