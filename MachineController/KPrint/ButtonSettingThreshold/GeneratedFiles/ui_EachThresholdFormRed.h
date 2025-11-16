/********************************************************************************
** Form generated from reading UI file 'EachThresholdFormRed.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EACHTHRESHOLDFORMRED_H
#define UI_EACHTHRESHOLDFORMRED_H

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

class Ui_EachThresholdFormRed
{
public:
    QToolButton *toolButtonCancel;
    QFrame *frameMarkerImage;
    QLabel *label;
    QFrame *frame_4;
    QLabel *labelK_6;
    QSpinBox *spinBoxRedMinBrightness;
    QSpinBox *spinBoxRedHighRate;
    QSlider *horizontalSliderRedHighRate;
    QSlider *horizontalSliderRedMinBrightness;
    QLabel *labelK_2;
    QLabel *labelK_10;
    QLabel *labelK_11;
    QLabel *labelK_13;
    QLabel *labelK_14;
    QSlider *horizontalSliderRedGBMerginRate;
    QSpinBox *spinBoxRedGBMerginRate;
    QLabel *labelK_15;
    QSlider *horizontalSliderRedGBMerginOffset;
    QSpinBox *spinBoxRedGBMerginOffset;
    QPushButton *PushButtonMarker;
    QPushButton *PushButtonShowWhole;
    QToolButton *toolButtonOK;
    QToolButton *toolButtonOKSize;
    QFrame *frame_3;
    QLabel *labelK_5;
    QSlider *horizontalSliderRedOKDot;
    QDoubleSpinBox *doubleSpinBoxRedOKDotMM;
    QLabel *labelK_4;
    QLabel *labelK_3;
    QSpinBox *spinBoxRedOKDot;
    QFrame *frameRedRange;
    QFrame *frameRedColor;
    QLabel *label_2;
    QLabel *label_3;
    QFrame *frameThresholdLevel;
    QLabel *labelK_8;

    void setupUi(QWidget *EachThresholdFormRed)
    {
        if (EachThresholdFormRed->objectName().isEmpty())
            EachThresholdFormRed->setObjectName("EachThresholdFormRed");
        EachThresholdFormRed->resize(1407, 869);
        toolButtonCancel = new QToolButton(EachThresholdFormRed);
        toolButtonCancel->setObjectName("toolButtonCancel");
        toolButtonCancel->setGeometry(QRect(1220, 750, 161, 81));
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
        frameMarkerImage = new QFrame(EachThresholdFormRed);
        frameMarkerImage->setObjectName("frameMarkerImage");
        frameMarkerImage->setGeometry(QRect(890, 110, 501, 431));
        frameMarkerImage->setFrameShape(QFrame::StyledPanel);
        frameMarkerImage->setFrameShadow(QFrame::Raised);
        label = new QLabel(EachThresholdFormRed);
        label->setObjectName("label");
        label->setGeometry(QRect(890, 77, 501, 31));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        frame_4 = new QFrame(EachThresholdFormRed);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 170, 551, 391));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        labelK_6 = new QLabel(frame_4);
        labelK_6->setObjectName("labelK_6");
        labelK_6->setGeometry(QRect(0, 0, 551, 51));
        QFont font2;
        font2.setPointSize(18);
        labelK_6->setFont(font2);
        labelK_6->setAlignment(Qt::AlignCenter);
        spinBoxRedMinBrightness = new QSpinBox(frame_4);
        spinBoxRedMinBrightness->setObjectName("spinBoxRedMinBrightness");
        spinBoxRedMinBrightness->setGeometry(QRect(110, 160, 81, 31));
        spinBoxRedMinBrightness->setFont(font1);
        spinBoxRedMinBrightness->setMinimum(0);
        spinBoxRedMinBrightness->setMaximum(255);
        spinBoxRedMinBrightness->setValue(10);
        spinBoxRedHighRate = new QSpinBox(frame_4);
        spinBoxRedHighRate->setObjectName("spinBoxRedHighRate");
        spinBoxRedHighRate->setGeometry(QRect(340, 160, 81, 31));
        spinBoxRedHighRate->setFont(font1);
        spinBoxRedHighRate->setMinimum(0);
        spinBoxRedHighRate->setMaximum(1000);
        spinBoxRedHighRate->setValue(10);
        horizontalSliderRedHighRate = new QSlider(frame_4);
        horizontalSliderRedHighRate->setObjectName("horizontalSliderRedHighRate");
        horizontalSliderRedHighRate->setGeometry(QRect(300, 110, 181, 41));
        horizontalSliderRedHighRate->setMinimum(0);
        horizontalSliderRedHighRate->setMaximum(1000);
        horizontalSliderRedHighRate->setValue(500);
        horizontalSliderRedHighRate->setOrientation(Qt::Horizontal);
        horizontalSliderRedMinBrightness = new QSlider(frame_4);
        horizontalSliderRedMinBrightness->setObjectName("horizontalSliderRedMinBrightness");
        horizontalSliderRedMinBrightness->setGeometry(QRect(90, 110, 181, 41));
        horizontalSliderRedMinBrightness->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderRedMinBrightness->setMinimum(0);
        horizontalSliderRedMinBrightness->setMaximum(255);
        horizontalSliderRedMinBrightness->setValue(60);
        horizontalSliderRedMinBrightness->setOrientation(Qt::Horizontal);
        horizontalSliderRedMinBrightness->setInvertedAppearance(true);
        labelK_2 = new QLabel(frame_4);
        labelK_2->setObjectName("labelK_2");
        labelK_2->setGeometry(QRect(10, 110, 61, 41));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        labelK_2->setPalette(palette);
        labelK_2->setFont(font1);
        labelK_2->setAlignment(Qt::AlignCenter);
        labelK_10 = new QLabel(frame_4);
        labelK_10->setObjectName("labelK_10");
        labelK_10->setGeometry(QRect(60, 70, 161, 31));
        labelK_10->setFont(font1);
        labelK_10->setAlignment(Qt::AlignCenter);
        labelK_11 = new QLabel(frame_4);
        labelK_11->setObjectName("labelK_11");
        labelK_11->setGeometry(QRect(260, 70, 271, 31));
        labelK_11->setFont(font1);
        labelK_11->setAlignment(Qt::AlignCenter);
        labelK_13 = new QLabel(frame_4);
        labelK_13->setObjectName("labelK_13");
        labelK_13->setGeometry(QRect(10, 210, 131, 41));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        labelK_13->setPalette(palette1);
        labelK_13->setFont(font1);
        labelK_13->setAlignment(Qt::AlignCenter);
        labelK_14 = new QLabel(frame_4);
        labelK_14->setObjectName("labelK_14");
        labelK_14->setGeometry(QRect(250, 260, 291, 31));
        labelK_14->setFont(font1);
        labelK_14->setAlignment(Qt::AlignCenter);
        horizontalSliderRedGBMerginRate = new QSlider(frame_4);
        horizontalSliderRedGBMerginRate->setObjectName("horizontalSliderRedGBMerginRate");
        horizontalSliderRedGBMerginRate->setGeometry(QRect(320, 300, 181, 41));
        horizontalSliderRedGBMerginRate->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderRedGBMerginRate->setMinimum(0);
        horizontalSliderRedGBMerginRate->setMaximum(100);
        horizontalSliderRedGBMerginRate->setValue(25);
        horizontalSliderRedGBMerginRate->setTracking(true);
        horizontalSliderRedGBMerginRate->setOrientation(Qt::Horizontal);
        horizontalSliderRedGBMerginRate->setInvertedAppearance(true);
        horizontalSliderRedGBMerginRate->setInvertedControls(false);
        spinBoxRedGBMerginRate = new QSpinBox(frame_4);
        spinBoxRedGBMerginRate->setObjectName("spinBoxRedGBMerginRate");
        spinBoxRedGBMerginRate->setGeometry(QRect(340, 350, 81, 31));
        spinBoxRedGBMerginRate->setFont(font1);
        spinBoxRedGBMerginRate->setMinimum(0);
        spinBoxRedGBMerginRate->setMaximum(100);
        spinBoxRedGBMerginRate->setValue(10);
        labelK_15 = new QLabel(frame_4);
        labelK_15->setObjectName("labelK_15");
        labelK_15->setGeometry(QRect(50, 260, 191, 31));
        labelK_15->setFont(font1);
        labelK_15->setAlignment(Qt::AlignCenter);
        horizontalSliderRedGBMerginOffset = new QSlider(frame_4);
        horizontalSliderRedGBMerginOffset->setObjectName("horizontalSliderRedGBMerginOffset");
        horizontalSliderRedGBMerginOffset->setGeometry(QRect(90, 300, 181, 41));
        horizontalSliderRedGBMerginOffset->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderRedGBMerginOffset->setMinimum(0);
        horizontalSliderRedGBMerginOffset->setMaximum(255);
        horizontalSliderRedGBMerginOffset->setValue(60);
        horizontalSliderRedGBMerginOffset->setOrientation(Qt::Horizontal);
        horizontalSliderRedGBMerginOffset->setInvertedAppearance(true);
        spinBoxRedGBMerginOffset = new QSpinBox(frame_4);
        spinBoxRedGBMerginOffset->setObjectName("spinBoxRedGBMerginOffset");
        spinBoxRedGBMerginOffset->setGeometry(QRect(110, 350, 81, 31));
        spinBoxRedGBMerginOffset->setFont(font1);
        spinBoxRedGBMerginOffset->setMinimum(0);
        spinBoxRedGBMerginOffset->setMaximum(255);
        spinBoxRedGBMerginOffset->setValue(10);
        PushButtonMarker = new QPushButton(EachThresholdFormRed);
        PushButtonMarker->setObjectName("PushButtonMarker");
        PushButtonMarker->setGeometry(QRect(890, 10, 241, 51));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font3.setPointSize(24);
        PushButtonMarker->setFont(font3);
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
        PushButtonShowWhole = new QPushButton(EachThresholdFormRed);
        PushButtonShowWhole->setObjectName("PushButtonShowWhole");
        PushButtonShowWhole->setGeometry(QRect(1140, 10, 241, 51));
        PushButtonShowWhole->setFont(font3);
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
        toolButtonOK = new QToolButton(EachThresholdFormRed);
        toolButtonOK->setObjectName("toolButtonOK");
        toolButtonOK->setGeometry(QRect(10, 680, 481, 81));
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
        toolButtonOKSize = new QToolButton(EachThresholdFormRed);
        toolButtonOKSize->setObjectName("toolButtonOKSize");
        toolButtonOKSize->setGeometry(QRect(10, 770, 481, 81));
        toolButtonOKSize->setFont(font);
        toolButtonOKSize->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        frame_3 = new QFrame(EachThresholdFormRed);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 570, 781, 101));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        labelK_5 = new QLabel(frame_3);
        labelK_5->setObjectName("labelK_5");
        labelK_5->setGeometry(QRect(680, 50, 81, 36));
        QFont font4;
        font4.setPointSize(11);
        labelK_5->setFont(font4);
        labelK_5->setAlignment(Qt::AlignCenter);
        horizontalSliderRedOKDot = new QSlider(frame_3);
        horizontalSliderRedOKDot->setObjectName("horizontalSliderRedOKDot");
        horizontalSliderRedOKDot->setGeometry(QRect(280, 20, 241, 51));
        horizontalSliderRedOKDot->setMaximum(10000);
        horizontalSliderRedOKDot->setOrientation(Qt::Horizontal);
        doubleSpinBoxRedOKDotMM = new QDoubleSpinBox(frame_3);
        doubleSpinBoxRedOKDotMM->setObjectName("doubleSpinBoxRedOKDotMM");
        doubleSpinBoxRedOKDotMM->setGeometry(QRect(560, 10, 111, 36));
        doubleSpinBoxRedOKDotMM->setFont(font);
        doubleSpinBoxRedOKDotMM->setMaximum(10000.000000000000000);
        doubleSpinBoxRedOKDotMM->setValue(0.500000000000000);
        labelK_4 = new QLabel(frame_3);
        labelK_4->setObjectName("labelK_4");
        labelK_4->setGeometry(QRect(680, 10, 61, 36));
        QFont font5;
        font5.setPointSize(14);
        labelK_4->setFont(font5);
        labelK_4->setAlignment(Qt::AlignCenter);
        labelK_3 = new QLabel(frame_3);
        labelK_3->setObjectName("labelK_3");
        labelK_3->setGeometry(QRect(10, 20, 261, 51));
        labelK_3->setFont(font2);
        labelK_3->setAlignment(Qt::AlignCenter);
        spinBoxRedOKDot = new QSpinBox(frame_3);
        spinBoxRedOKDot->setObjectName("spinBoxRedOKDot");
        spinBoxRedOKDot->setGeometry(QRect(560, 50, 111, 36));
        spinBoxRedOKDot->setFont(font);
        spinBoxRedOKDot->setMaximum(99999999);
        spinBoxRedOKDot->setValue(2000);
        frameRedRange = new QFrame(EachThresholdFormRed);
        frameRedRange->setObjectName("frameRedRange");
        frameRedRange->setGeometry(QRect(570, 200, 311, 241));
        frameRedRange->setFrameShape(QFrame::StyledPanel);
        frameRedRange->setFrameShadow(QFrame::Raised);
        frameRedColor = new QFrame(EachThresholdFormRed);
        frameRedColor->setObjectName("frameRedColor");
        frameRedColor->setGeometry(QRect(610, 480, 251, 81));
        frameRedColor->setAutoFillBackground(true);
        frameRedColor->setFrameShape(QFrame::StyledPanel);
        frameRedColor->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(EachThresholdFormRed);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(570, 170, 311, 31));
        label_2->setFont(font1);
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(EachThresholdFormRed);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(610, 450, 251, 31));
        label_3->setFont(font1);
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        frameThresholdLevel = new QFrame(EachThresholdFormRed);
        frameThresholdLevel->setObjectName("frameThresholdLevel");
        frameThresholdLevel->setGeometry(QRect(10, 10, 551, 151));
        frameThresholdLevel->setFrameShape(QFrame::Panel);
        frameThresholdLevel->setFrameShadow(QFrame::Sunken);
        labelK_8 = new QLabel(frameThresholdLevel);
        labelK_8->setObjectName("labelK_8");
        labelK_8->setGeometry(QRect(0, 0, 551, 31));
        labelK_8->setFont(font5);
        labelK_8->setAlignment(Qt::AlignCenter);

        retranslateUi(EachThresholdFormRed);

        PushButtonMarker->setDefault(false);
        PushButtonShowWhole->setDefault(false);


        QMetaObject::connectSlotsByName(EachThresholdFormRed);
    } // setupUi

    void retranslateUi(QWidget *EachThresholdFormRed)
    {
        EachThresholdFormRed->setWindowTitle(QCoreApplication::translate("EachThresholdFormRed", "Setting", nullptr));
        toolButtonCancel->setText(QCoreApplication::translate("EachThresholdFormRed", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        label->setText(QCoreApplication::translate("EachThresholdFormRed", "\343\203\236\343\203\274\343\202\253\343\203\274\347\256\207\346\211\200", nullptr));
        labelK_6->setText(QCoreApplication::translate("EachThresholdFormRed", "\350\274\235\345\272\246\345\244\211\345\214\226\343\201\256\346\244\234\345\207\272", nullptr));
        labelK_2->setText(QCoreApplication::translate("EachThresholdFormRed", "\350\265\244\343\201\277", nullptr));
        labelK_10->setText(QCoreApplication::translate("EachThresholdFormRed", "\346\232\227\345\201\264\350\274\235\345\272\246\345\200\244", nullptr));
        labelK_11->setText(QCoreApplication::translate("EachThresholdFormRed", "\346\230\216\345\201\264\357\274\210\347\267\221\343\203\273\351\235\222\346\210\220\345\210\206\343\201\256\345\200\215\347\216\207\357\274\205\357\274\211", nullptr));
        labelK_13->setText(QCoreApplication::translate("EachThresholdFormRed", "\350\265\244\345\244\211\345\214\226\347\257\204\345\233\262", nullptr));
        labelK_14->setText(QCoreApplication::translate("EachThresholdFormRed", "\346\230\216\345\201\264\357\274\210\347\267\221\351\235\222\345\244\211\345\214\226\345\211\262\345\220\210\357\274\205\357\274\211", nullptr));
        labelK_15->setText(QCoreApplication::translate("EachThresholdFormRed", "\346\232\227\345\201\264\343\202\252\343\203\225\343\202\273\343\203\203\343\203\210\345\200\244", nullptr));
        PushButtonMarker->setText(QCoreApplication::translate("EachThresholdFormRed", "\343\203\236\343\203\274\343\202\253\343\203\274", nullptr));
        PushButtonShowWhole->setText(QCoreApplication::translate("EachThresholdFormRed", "\345\205\250\344\275\223\350\241\250\347\244\272", nullptr));
        toolButtonOK->setText(QCoreApplication::translate("EachThresholdFormRed", "\350\211\262\347\257\204\345\233\262\343\200\201\346\244\234\345\207\272\343\202\265\343\202\244\343\202\272\343\202\222\350\250\255\345\256\232", nullptr));
        toolButtonOKSize->setText(QCoreApplication::translate("EachThresholdFormRed", "\343\202\265\343\202\244\343\202\272\343\201\256\343\201\277\343\202\222\350\250\255\345\256\232", nullptr));
        labelK_5->setText(QCoreApplication::translate("EachThresholdFormRed", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_4->setText(QCoreApplication::translate("EachThresholdFormRed", "mm2", nullptr));
        labelK_3->setText(QCoreApplication::translate("EachThresholdFormRed", "\346\244\234\345\207\272\351\235\242\347\251\215", nullptr));
        label_2->setText(QCoreApplication::translate("EachThresholdFormRed", "\350\265\244\347\257\204\345\233\262", nullptr));
        label_3->setText(QCoreApplication::translate("EachThresholdFormRed", "\343\203\236\343\202\246\343\202\271\343\203\235\343\202\244\343\203\263\343\202\277\343\201\256\350\265\244\350\211\262", nullptr));
        labelK_8->setText(QCoreApplication::translate("EachThresholdFormRed", "\343\203\254\343\203\231\343\203\253\347\242\272\350\252\215\357\274\217\350\250\255\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EachThresholdFormRed: public Ui_EachThresholdFormRed {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EACHTHRESHOLDFORMRED_H
