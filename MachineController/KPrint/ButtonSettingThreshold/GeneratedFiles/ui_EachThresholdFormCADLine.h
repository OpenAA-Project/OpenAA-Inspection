/********************************************************************************
** Form generated from reading UI file 'EachThresholdFormCADLine.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EACHTHRESHOLDFORMCADLINE_H
#define UI_EACHTHRESHOLDFORMCADLINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EachThresholdFormCADLine
{
public:
    QTableWidget *tableWidget;
    QToolButton *toolButtonOK;
    QToolButton *toolButtonOKSize;
    QToolButton *toolButtonCancel;
    QFrame *frameThresholdLevel;
    QLabel *labelK_8;
    QFrame *frame;
    QToolButton *toolButtonNarrow;
    QToolButton *toolButtonBroad;
    QStackedWidget *stackedWidget;
    QWidget *Broad;
    QFrame *frame_4;
    QLabel *labelK_6;
    QLabel *labelK_9;
    QSpinBox *spinBoxBCL;
    QLabel *labelK_7;
    QSpinBox *spinBoxBYH;
    QSpinBox *spinBoxBCH;
    QSpinBox *spinBoxBMH;
    QSlider *horizontalSliderBYH;
    QSlider *horizontalSliderBCH;
    QSlider *horizontalSliderBMH;
    QSlider *horizontalSliderBML;
    QSlider *horizontalSliderBYL;
    QLabel *labelK_2;
    QSpinBox *spinBoxBYL;
    QSlider *horizontalSliderBCL;
    QSpinBox *spinBoxBML;
    QLabel *labelK_10;
    QLabel *labelK_11;
    QFrame *frame_3;
    QLabel *labelK_5;
    QSlider *horizontalSliderSizeB;
    QDoubleSpinBox *doubleSpinBoxSizeBMM;
    QLabel *labelK_4;
    QLabel *labelK_3;
    QSpinBox *spinBoxSizeB;
    QSpinBox *spinBoxLengthB;
    QDoubleSpinBox *doubleSpinBoxLengthBMM;
    QLabel *labelK_12;
    QLabel *labelK_13;
    QSlider *horizontalSliderLengthB;
    QLabel *labelK_14;
    QWidget *Narrow;
    QFrame *frame_5;
    QLabel *labelK_15;
    QLabel *labelK_16;
    QSpinBox *spinBoxNCL;
    QLabel *labelK_17;
    QSpinBox *spinBoxNYH;
    QSpinBox *spinBoxNCH;
    QSpinBox *spinBoxNMH;
    QSlider *horizontalSliderNYH;
    QSlider *horizontalSliderNCH;
    QSlider *horizontalSliderNMH;
    QSlider *horizontalSliderNML;
    QSlider *horizontalSliderNYL;
    QLabel *labelK_18;
    QSpinBox *spinBoxNYL;
    QSlider *horizontalSliderNCL;
    QSpinBox *spinBoxNML;
    QLabel *labelK_19;
    QLabel *labelK_20;
    QFrame *frame_6;
    QLabel *labelK_21;
    QSlider *horizontalSliderSizeN;
    QDoubleSpinBox *doubleSpinBoxSizeNMM;
    QLabel *labelK_22;
    QLabel *labelK_23;
    QSpinBox *spinBoxSizeN;
    QSpinBox *spinBoxLengthN;
    QDoubleSpinBox *doubleSpinBoxLengthNMM;
    QLabel *labelK_24;
    QLabel *labelK_25;
    QSlider *horizontalSliderLengthN;
    QLabel *labelK_26;

    void setupUi(QWidget *EachThresholdFormCADLine)
    {
        if (EachThresholdFormCADLine->objectName().isEmpty())
            EachThresholdFormCADLine->setObjectName("EachThresholdFormCADLine");
        EachThresholdFormCADLine->resize(1101, 974);
        tableWidget = new QTableWidget(EachThresholdFormCADLine);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 200, 381, 741));
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->verticalHeader()->setMinimumSectionSize(30);
        tableWidget->verticalHeader()->setDefaultSectionSize(30);
        toolButtonOK = new QToolButton(EachThresholdFormCADLine);
        toolButtonOK->setObjectName("toolButtonOK");
        toolButtonOK->setGeometry(QRect(410, 770, 501, 81));
        QFont font;
        font.setPointSize(16);
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
        toolButtonOKSize = new QToolButton(EachThresholdFormCADLine);
        toolButtonOKSize->setObjectName("toolButtonOKSize");
        toolButtonOKSize->setGeometry(QRect(410, 860, 501, 81));
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
        toolButtonCancel = new QToolButton(EachThresholdFormCADLine);
        toolButtonCancel->setObjectName("toolButtonCancel");
        toolButtonCancel->setGeometry(QRect(930, 860, 161, 81));
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
        frameThresholdLevel = new QFrame(EachThresholdFormCADLine);
        frameThresholdLevel->setObjectName("frameThresholdLevel");
        frameThresholdLevel->setGeometry(QRect(10, 10, 551, 181));
        frameThresholdLevel->setFrameShape(QFrame::Panel);
        frameThresholdLevel->setFrameShadow(QFrame::Sunken);
        labelK_8 = new QLabel(frameThresholdLevel);
        labelK_8->setObjectName("labelK_8");
        labelK_8->setGeometry(QRect(0, 0, 551, 31));
        QFont font1;
        font1.setPointSize(14);
        labelK_8->setFont(font1);
        labelK_8->setAlignment(Qt::AlignCenter);
        frame = new QFrame(EachThresholdFormCADLine);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(570, 120, 401, 71));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonNarrow = new QToolButton(frame);
        toolButtonNarrow->setObjectName("toolButtonNarrow");
        toolButtonNarrow->setGeometry(QRect(210, 0, 181, 61));
        toolButtonNarrow->setFont(font);
        toolButtonNarrow->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonNarrow->setCheckable(true);
        toolButtonNarrow->setAutoExclusive(true);
        toolButtonBroad = new QToolButton(frame);
        toolButtonBroad->setObjectName("toolButtonBroad");
        toolButtonBroad->setGeometry(QRect(10, 0, 191, 61));
        toolButtonBroad->setFont(font);
        toolButtonBroad->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonBroad->setCheckable(true);
        toolButtonBroad->setChecked(true);
        toolButtonBroad->setAutoExclusive(true);
        stackedWidget = new QStackedWidget(EachThresholdFormCADLine);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(390, 190, 701, 571));
        Broad = new QWidget();
        Broad->setObjectName("Broad");
        frame_4 = new QFrame(Broad);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 10, 531, 361));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        labelK_6 = new QLabel(frame_4);
        labelK_6->setObjectName("labelK_6");
        labelK_6->setGeometry(QRect(0, 0, 441, 51));
        QFont font2;
        font2.setPointSize(18);
        labelK_6->setFont(font2);
        labelK_6->setAlignment(Qt::AlignCenter);
        labelK_9 = new QLabel(frame_4);
        labelK_9->setObjectName("labelK_9");
        labelK_9->setGeometry(QRect(0, 280, 131, 41));
        QPalette palette;
        QBrush brush(QColor(255, 170, 127, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        labelK_9->setPalette(palette);
        QFont font3;
        font3.setPointSize(12);
        labelK_9->setFont(font3);
        labelK_9->setAlignment(Qt::AlignCenter);
        spinBoxBCL = new QSpinBox(frame_4);
        spinBoxBCL->setObjectName("spinBoxBCL");
        spinBoxBCL->setGeometry(QRect(190, 130, 81, 31));
        QPalette palette1;
        QBrush brush2(QColor(0, 255, 255, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        QBrush brush3(QColor(240, 240, 240, 255));
        brush3.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxBCL->setPalette(palette1);
        spinBoxBCL->setFont(font3);
        spinBoxBCL->setAutoFillBackground(true);
        spinBoxBCL->setMaximum(360);
        spinBoxBCL->setValue(10);
        labelK_7 = new QLabel(frame_4);
        labelK_7->setObjectName("labelK_7");
        labelK_7->setGeometry(QRect(0, 190, 131, 41));
        QPalette palette2;
        QBrush brush4(QColor(255, 0, 255, 255));
        brush4.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush4);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush4);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        labelK_7->setPalette(palette2);
        labelK_7->setFont(font3);
        labelK_7->setAlignment(Qt::AlignCenter);
        spinBoxBYH = new QSpinBox(frame_4);
        spinBoxBYH->setObjectName("spinBoxBYH");
        spinBoxBYH->setGeometry(QRect(360, 310, 81, 31));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxBYH->setPalette(palette3);
        spinBoxBYH->setFont(font3);
        spinBoxBYH->setAutoFillBackground(true);
        spinBoxBYH->setMaximum(255);
        spinBoxBYH->setValue(10);
        spinBoxBCH = new QSpinBox(frame_4);
        spinBoxBCH->setObjectName("spinBoxBCH");
        spinBoxBCH->setGeometry(QRect(360, 130, 81, 31));
        QPalette palette4;
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxBCH->setPalette(palette4);
        spinBoxBCH->setFont(font3);
        spinBoxBCH->setAutoFillBackground(true);
        spinBoxBCH->setMaximum(360);
        spinBoxBCH->setValue(10);
        spinBoxBMH = new QSpinBox(frame_4);
        spinBoxBMH->setObjectName("spinBoxBMH");
        spinBoxBMH->setGeometry(QRect(360, 220, 81, 31));
        QPalette palette5;
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette5.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxBMH->setPalette(palette5);
        spinBoxBMH->setFont(font3);
        spinBoxBMH->setAutoFillBackground(true);
        spinBoxBMH->setMaximum(255);
        spinBoxBMH->setValue(10);
        horizontalSliderBYH = new QSlider(frame_4);
        horizontalSliderBYH->setObjectName("horizontalSliderBYH");
        horizontalSliderBYH->setGeometry(QRect(330, 270, 181, 41));
        horizontalSliderBYH->setMaximum(255);
        horizontalSliderBYH->setOrientation(Qt::Horizontal);
        horizontalSliderBCH = new QSlider(frame_4);
        horizontalSliderBCH->setObjectName("horizontalSliderBCH");
        horizontalSliderBCH->setGeometry(QRect(330, 90, 181, 41));
        horizontalSliderBCH->setMaximum(360);
        horizontalSliderBCH->setOrientation(Qt::Horizontal);
        horizontalSliderBMH = new QSlider(frame_4);
        horizontalSliderBMH->setObjectName("horizontalSliderBMH");
        horizontalSliderBMH->setGeometry(QRect(330, 180, 181, 41));
        horizontalSliderBMH->setMaximum(255);
        horizontalSliderBMH->setOrientation(Qt::Horizontal);
        horizontalSliderBML = new QSlider(frame_4);
        horizontalSliderBML->setObjectName("horizontalSliderBML");
        horizontalSliderBML->setGeometry(QRect(140, 180, 181, 41));
        horizontalSliderBML->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderBML->setMaximum(255);
        horizontalSliderBML->setOrientation(Qt::Horizontal);
        horizontalSliderBYL = new QSlider(frame_4);
        horizontalSliderBYL->setObjectName("horizontalSliderBYL");
        horizontalSliderBYL->setGeometry(QRect(140, 270, 181, 41));
        horizontalSliderBYL->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderBYL->setMaximum(255);
        horizontalSliderBYL->setOrientation(Qt::Horizontal);
        labelK_2 = new QLabel(frame_4);
        labelK_2->setObjectName("labelK_2");
        labelK_2->setGeometry(QRect(0, 100, 131, 41));
        QPalette palette6;
        QBrush brush5(QColor(85, 255, 255, 255));
        brush5.setStyle(Qt::BrushStyle::SolidPattern);
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush5);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush5);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        labelK_2->setPalette(palette6);
        labelK_2->setFont(font3);
        labelK_2->setAlignment(Qt::AlignCenter);
        spinBoxBYL = new QSpinBox(frame_4);
        spinBoxBYL->setObjectName("spinBoxBYL");
        spinBoxBYL->setGeometry(QRect(190, 310, 81, 31));
        QPalette palette7;
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxBYL->setPalette(palette7);
        spinBoxBYL->setFont(font3);
        spinBoxBYL->setAutoFillBackground(true);
        spinBoxBYL->setMaximum(255);
        spinBoxBYL->setValue(10);
        horizontalSliderBCL = new QSlider(frame_4);
        horizontalSliderBCL->setObjectName("horizontalSliderBCL");
        horizontalSliderBCL->setGeometry(QRect(140, 90, 181, 41));
        horizontalSliderBCL->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderBCL->setMaximum(360);
        horizontalSliderBCL->setOrientation(Qt::Horizontal);
        spinBoxBML = new QSpinBox(frame_4);
        spinBoxBML->setObjectName("spinBoxBML");
        spinBoxBML->setGeometry(QRect(190, 220, 81, 31));
        QPalette palette8;
        palette8.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette8.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette8.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxBML->setPalette(palette8);
        spinBoxBML->setFont(font3);
        spinBoxBML->setAutoFillBackground(true);
        spinBoxBML->setMaximum(255);
        spinBoxBML->setValue(10);
        labelK_10 = new QLabel(frame_4);
        labelK_10->setObjectName("labelK_10");
        labelK_10->setGeometry(QRect(150, 50, 151, 31));
        labelK_10->setFont(font1);
        labelK_10->setAlignment(Qt::AlignCenter);
        labelK_11 = new QLabel(frame_4);
        labelK_11->setObjectName("labelK_11");
        labelK_11->setGeometry(QRect(350, 50, 151, 31));
        labelK_11->setFont(font1);
        labelK_11->setAlignment(Qt::AlignCenter);
        frame_3 = new QFrame(Broad);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 380, 681, 181));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        labelK_5 = new QLabel(frame_3);
        labelK_5->setObjectName("labelK_5");
        labelK_5->setGeometry(QRect(600, 50, 81, 36));
        QFont font4;
        font4.setPointSize(11);
        labelK_5->setFont(font4);
        labelK_5->setAlignment(Qt::AlignCenter);
        horizontalSliderSizeB = new QSlider(frame_3);
        horizontalSliderSizeB->setObjectName("horizontalSliderSizeB");
        horizontalSliderSizeB->setGeometry(QRect(200, 20, 241, 51));
        horizontalSliderSizeB->setMaximum(10000);
        horizontalSliderSizeB->setOrientation(Qt::Horizontal);
        doubleSpinBoxSizeBMM = new QDoubleSpinBox(frame_3);
        doubleSpinBoxSizeBMM->setObjectName("doubleSpinBoxSizeBMM");
        doubleSpinBoxSizeBMM->setGeometry(QRect(480, 10, 111, 36));
        doubleSpinBoxSizeBMM->setFont(font);
        doubleSpinBoxSizeBMM->setMaximum(10000.000000000000000);
        doubleSpinBoxSizeBMM->setValue(0.500000000000000);
        labelK_4 = new QLabel(frame_3);
        labelK_4->setObjectName("labelK_4");
        labelK_4->setGeometry(QRect(600, 10, 61, 36));
        labelK_4->setFont(font1);
        labelK_4->setAlignment(Qt::AlignCenter);
        labelK_3 = new QLabel(frame_3);
        labelK_3->setObjectName("labelK_3");
        labelK_3->setGeometry(QRect(10, 20, 181, 51));
        labelK_3->setFont(font2);
        labelK_3->setAlignment(Qt::AlignCenter);
        spinBoxSizeB = new QSpinBox(frame_3);
        spinBoxSizeB->setObjectName("spinBoxSizeB");
        spinBoxSizeB->setGeometry(QRect(480, 50, 111, 36));
        spinBoxSizeB->setFont(font);
        spinBoxSizeB->setMaximum(99999999);
        spinBoxSizeB->setValue(2000);
        spinBoxLengthB = new QSpinBox(frame_3);
        spinBoxLengthB->setObjectName("spinBoxLengthB");
        spinBoxLengthB->setGeometry(QRect(480, 130, 111, 36));
        spinBoxLengthB->setFont(font);
        spinBoxLengthB->setMaximum(99999999);
        spinBoxLengthB->setValue(2000);
        doubleSpinBoxLengthBMM = new QDoubleSpinBox(frame_3);
        doubleSpinBoxLengthBMM->setObjectName("doubleSpinBoxLengthBMM");
        doubleSpinBoxLengthBMM->setGeometry(QRect(480, 90, 111, 36));
        doubleSpinBoxLengthBMM->setFont(font);
        doubleSpinBoxLengthBMM->setMaximum(10000.000000000000000);
        doubleSpinBoxLengthBMM->setValue(0.500000000000000);
        labelK_12 = new QLabel(frame_3);
        labelK_12->setObjectName("labelK_12");
        labelK_12->setGeometry(QRect(600, 130, 81, 36));
        labelK_12->setFont(font4);
        labelK_12->setAlignment(Qt::AlignCenter);
        labelK_13 = new QLabel(frame_3);
        labelK_13->setObjectName("labelK_13");
        labelK_13->setGeometry(QRect(600, 90, 61, 36));
        labelK_13->setFont(font1);
        labelK_13->setAlignment(Qt::AlignCenter);
        horizontalSliderLengthB = new QSlider(frame_3);
        horizontalSliderLengthB->setObjectName("horizontalSliderLengthB");
        horizontalSliderLengthB->setGeometry(QRect(200, 100, 241, 51));
        horizontalSliderLengthB->setMaximum(10000);
        horizontalSliderLengthB->setOrientation(Qt::Horizontal);
        labelK_14 = new QLabel(frame_3);
        labelK_14->setObjectName("labelK_14");
        labelK_14->setGeometry(QRect(10, 100, 181, 51));
        labelK_14->setFont(font2);
        labelK_14->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(Broad);
        Narrow = new QWidget();
        Narrow->setObjectName("Narrow");
        frame_5 = new QFrame(Narrow);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 10, 531, 361));
        frame_5->setFrameShape(QFrame::Panel);
        frame_5->setFrameShadow(QFrame::Sunken);
        labelK_15 = new QLabel(frame_5);
        labelK_15->setObjectName("labelK_15");
        labelK_15->setGeometry(QRect(0, 0, 441, 51));
        labelK_15->setFont(font2);
        labelK_15->setAlignment(Qt::AlignCenter);
        labelK_16 = new QLabel(frame_5);
        labelK_16->setObjectName("labelK_16");
        labelK_16->setGeometry(QRect(0, 280, 131, 41));
        QPalette palette9;
        palette9.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette9.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette9.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        labelK_16->setPalette(palette9);
        labelK_16->setFont(font3);
        labelK_16->setAlignment(Qt::AlignCenter);
        spinBoxNCL = new QSpinBox(frame_5);
        spinBoxNCL->setObjectName("spinBoxNCL");
        spinBoxNCL->setGeometry(QRect(190, 130, 81, 31));
        QPalette palette10;
        palette10.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette10.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette10.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxNCL->setPalette(palette10);
        spinBoxNCL->setFont(font3);
        spinBoxNCL->setAutoFillBackground(true);
        spinBoxNCL->setMaximum(360);
        spinBoxNCL->setValue(10);
        labelK_17 = new QLabel(frame_5);
        labelK_17->setObjectName("labelK_17");
        labelK_17->setGeometry(QRect(0, 190, 131, 41));
        QPalette palette11;
        palette11.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush4);
        palette11.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush4);
        palette11.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        labelK_17->setPalette(palette11);
        labelK_17->setFont(font3);
        labelK_17->setAlignment(Qt::AlignCenter);
        spinBoxNYH = new QSpinBox(frame_5);
        spinBoxNYH->setObjectName("spinBoxNYH");
        spinBoxNYH->setGeometry(QRect(360, 310, 81, 31));
        QPalette palette12;
        palette12.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette12.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette12.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxNYH->setPalette(palette12);
        spinBoxNYH->setFont(font3);
        spinBoxNYH->setAutoFillBackground(true);
        spinBoxNYH->setMaximum(255);
        spinBoxNYH->setValue(10);
        spinBoxNCH = new QSpinBox(frame_5);
        spinBoxNCH->setObjectName("spinBoxNCH");
        spinBoxNCH->setGeometry(QRect(360, 130, 81, 31));
        QPalette palette13;
        palette13.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette13.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette13.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxNCH->setPalette(palette13);
        spinBoxNCH->setFont(font3);
        spinBoxNCH->setAutoFillBackground(true);
        spinBoxNCH->setMaximum(360);
        spinBoxNCH->setValue(10);
        spinBoxNMH = new QSpinBox(frame_5);
        spinBoxNMH->setObjectName("spinBoxNMH");
        spinBoxNMH->setGeometry(QRect(360, 220, 81, 31));
        QPalette palette14;
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette14.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxNMH->setPalette(palette14);
        spinBoxNMH->setFont(font3);
        spinBoxNMH->setAutoFillBackground(true);
        spinBoxNMH->setMaximum(255);
        spinBoxNMH->setValue(10);
        horizontalSliderNYH = new QSlider(frame_5);
        horizontalSliderNYH->setObjectName("horizontalSliderNYH");
        horizontalSliderNYH->setGeometry(QRect(330, 270, 181, 41));
        horizontalSliderNYH->setMaximum(255);
        horizontalSliderNYH->setOrientation(Qt::Horizontal);
        horizontalSliderNCH = new QSlider(frame_5);
        horizontalSliderNCH->setObjectName("horizontalSliderNCH");
        horizontalSliderNCH->setGeometry(QRect(330, 90, 181, 41));
        horizontalSliderNCH->setMaximum(360);
        horizontalSliderNCH->setOrientation(Qt::Horizontal);
        horizontalSliderNMH = new QSlider(frame_5);
        horizontalSliderNMH->setObjectName("horizontalSliderNMH");
        horizontalSliderNMH->setGeometry(QRect(330, 180, 181, 41));
        horizontalSliderNMH->setMaximum(255);
        horizontalSliderNMH->setOrientation(Qt::Horizontal);
        horizontalSliderNML = new QSlider(frame_5);
        horizontalSliderNML->setObjectName("horizontalSliderNML");
        horizontalSliderNML->setGeometry(QRect(140, 180, 181, 41));
        horizontalSliderNML->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderNML->setMaximum(255);
        horizontalSliderNML->setOrientation(Qt::Horizontal);
        horizontalSliderNYL = new QSlider(frame_5);
        horizontalSliderNYL->setObjectName("horizontalSliderNYL");
        horizontalSliderNYL->setGeometry(QRect(140, 270, 181, 41));
        horizontalSliderNYL->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderNYL->setMaximum(255);
        horizontalSliderNYL->setOrientation(Qt::Horizontal);
        labelK_18 = new QLabel(frame_5);
        labelK_18->setObjectName("labelK_18");
        labelK_18->setGeometry(QRect(0, 100, 131, 41));
        QPalette palette15;
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush5);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush5);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        labelK_18->setPalette(palette15);
        labelK_18->setFont(font3);
        labelK_18->setAlignment(Qt::AlignCenter);
        spinBoxNYL = new QSpinBox(frame_5);
        spinBoxNYL->setObjectName("spinBoxNYL");
        spinBoxNYL->setGeometry(QRect(190, 310, 81, 31));
        QPalette palette16;
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxNYL->setPalette(palette16);
        spinBoxNYL->setFont(font3);
        spinBoxNYL->setAutoFillBackground(true);
        spinBoxNYL->setMaximum(255);
        spinBoxNYL->setValue(10);
        horizontalSliderNCL = new QSlider(frame_5);
        horizontalSliderNCL->setObjectName("horizontalSliderNCL");
        horizontalSliderNCL->setGeometry(QRect(140, 90, 181, 41));
        horizontalSliderNCL->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderNCL->setMaximum(360);
        horizontalSliderNCL->setOrientation(Qt::Horizontal);
        spinBoxNML = new QSpinBox(frame_5);
        spinBoxNML->setObjectName("spinBoxNML");
        spinBoxNML->setGeometry(QRect(190, 220, 81, 31));
        QPalette palette17;
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxNML->setPalette(palette17);
        spinBoxNML->setFont(font3);
        spinBoxNML->setAutoFillBackground(true);
        spinBoxNML->setMaximum(255);
        spinBoxNML->setValue(10);
        labelK_19 = new QLabel(frame_5);
        labelK_19->setObjectName("labelK_19");
        labelK_19->setGeometry(QRect(150, 50, 151, 31));
        labelK_19->setFont(font1);
        labelK_19->setAlignment(Qt::AlignCenter);
        labelK_20 = new QLabel(frame_5);
        labelK_20->setObjectName("labelK_20");
        labelK_20->setGeometry(QRect(350, 50, 151, 31));
        labelK_20->setFont(font1);
        labelK_20->setAlignment(Qt::AlignCenter);
        frame_6 = new QFrame(Narrow);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(10, 380, 681, 181));
        frame_6->setFrameShape(QFrame::Panel);
        frame_6->setFrameShadow(QFrame::Sunken);
        labelK_21 = new QLabel(frame_6);
        labelK_21->setObjectName("labelK_21");
        labelK_21->setGeometry(QRect(600, 50, 81, 36));
        labelK_21->setFont(font4);
        labelK_21->setAlignment(Qt::AlignCenter);
        horizontalSliderSizeN = new QSlider(frame_6);
        horizontalSliderSizeN->setObjectName("horizontalSliderSizeN");
        horizontalSliderSizeN->setGeometry(QRect(200, 20, 241, 51));
        horizontalSliderSizeN->setMaximum(10000);
        horizontalSliderSizeN->setOrientation(Qt::Horizontal);
        doubleSpinBoxSizeNMM = new QDoubleSpinBox(frame_6);
        doubleSpinBoxSizeNMM->setObjectName("doubleSpinBoxSizeNMM");
        doubleSpinBoxSizeNMM->setGeometry(QRect(480, 10, 111, 36));
        doubleSpinBoxSizeNMM->setFont(font);
        doubleSpinBoxSizeNMM->setMaximum(10000.000000000000000);
        doubleSpinBoxSizeNMM->setValue(0.500000000000000);
        labelK_22 = new QLabel(frame_6);
        labelK_22->setObjectName("labelK_22");
        labelK_22->setGeometry(QRect(600, 10, 61, 36));
        labelK_22->setFont(font1);
        labelK_22->setAlignment(Qt::AlignCenter);
        labelK_23 = new QLabel(frame_6);
        labelK_23->setObjectName("labelK_23");
        labelK_23->setGeometry(QRect(10, 20, 181, 51));
        labelK_23->setFont(font2);
        labelK_23->setAlignment(Qt::AlignCenter);
        spinBoxSizeN = new QSpinBox(frame_6);
        spinBoxSizeN->setObjectName("spinBoxSizeN");
        spinBoxSizeN->setGeometry(QRect(480, 50, 111, 36));
        spinBoxSizeN->setFont(font);
        spinBoxSizeN->setMaximum(99999999);
        spinBoxSizeN->setValue(2000);
        spinBoxLengthN = new QSpinBox(frame_6);
        spinBoxLengthN->setObjectName("spinBoxLengthN");
        spinBoxLengthN->setGeometry(QRect(480, 130, 111, 36));
        spinBoxLengthN->setFont(font);
        spinBoxLengthN->setMaximum(99999999);
        spinBoxLengthN->setValue(2000);
        doubleSpinBoxLengthNMM = new QDoubleSpinBox(frame_6);
        doubleSpinBoxLengthNMM->setObjectName("doubleSpinBoxLengthNMM");
        doubleSpinBoxLengthNMM->setGeometry(QRect(480, 90, 111, 36));
        doubleSpinBoxLengthNMM->setFont(font);
        doubleSpinBoxLengthNMM->setMaximum(10000.000000000000000);
        doubleSpinBoxLengthNMM->setValue(0.500000000000000);
        labelK_24 = new QLabel(frame_6);
        labelK_24->setObjectName("labelK_24");
        labelK_24->setGeometry(QRect(600, 130, 81, 36));
        labelK_24->setFont(font4);
        labelK_24->setAlignment(Qt::AlignCenter);
        labelK_25 = new QLabel(frame_6);
        labelK_25->setObjectName("labelK_25");
        labelK_25->setGeometry(QRect(600, 90, 61, 36));
        labelK_25->setFont(font1);
        labelK_25->setAlignment(Qt::AlignCenter);
        horizontalSliderLengthN = new QSlider(frame_6);
        horizontalSliderLengthN->setObjectName("horizontalSliderLengthN");
        horizontalSliderLengthN->setGeometry(QRect(200, 100, 241, 51));
        horizontalSliderLengthN->setMaximum(10000);
        horizontalSliderLengthN->setOrientation(Qt::Horizontal);
        labelK_26 = new QLabel(frame_6);
        labelK_26->setObjectName("labelK_26");
        labelK_26->setGeometry(QRect(10, 100, 181, 51));
        labelK_26->setFont(font2);
        labelK_26->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(Narrow);

        retranslateUi(EachThresholdFormCADLine);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EachThresholdFormCADLine);
    } // setupUi

    void retranslateUi(QWidget *EachThresholdFormCADLine)
    {
        EachThresholdFormCADLine->setWindowTitle(QCoreApplication::translate("EachThresholdFormCADLine", "Setting", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\350\211\262", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\345\211\262\343\202\212\345\275\223\343\201\246", nullptr));
        toolButtonOK->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\343\201\223\343\201\256\350\274\235\345\272\246\345\244\211\345\214\226\343\201\250\346\244\234\345\207\272\343\202\265\343\202\244\343\202\272\343\202\222\350\250\255\345\256\232", nullptr));
        toolButtonOKSize->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\343\202\265\343\202\244\343\202\272\343\201\256\343\201\277\343\202\222\350\250\255\345\256\232", nullptr));
        toolButtonCancel->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        labelK_8->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\343\203\254\343\203\231\343\203\253\347\242\272\350\252\215\357\274\217\350\250\255\345\256\232", nullptr));
        toolButtonNarrow->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\347\213\255\345\237\237", nullptr));
        toolButtonBroad->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\345\272\203\345\237\237\357\274\217\344\270\200\350\210\254", nullptr));
        labelK_6->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\350\274\235\345\272\246\345\244\211\345\214\226\343\201\256\346\244\234\345\207\272", nullptr));
        labelK_9->setText(QCoreApplication::translate("EachThresholdFormCADLine", "V\343\200\200\357\274\210\346\230\216\345\272\246\357\274\211", nullptr));
        labelK_7->setText(QCoreApplication::translate("EachThresholdFormCADLine", "S\343\200\200\357\274\210\345\275\251\345\272\246\357\274\211", nullptr));
        labelK_2->setText(QCoreApplication::translate("EachThresholdFormCADLine", "H\343\200\200\357\274\210\350\211\262\347\233\270\357\274\211", nullptr));
        labelK_10->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\346\232\227\345\201\264", nullptr));
        labelK_11->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\346\230\216\345\201\264", nullptr));
        labelK_5->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_4->setText(QCoreApplication::translate("EachThresholdFormCADLine", "mm2", nullptr));
        labelK_3->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\346\244\234\345\207\272\351\235\242\347\251\215", nullptr));
        labelK_12->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_13->setText(QCoreApplication::translate("EachThresholdFormCADLine", "mm", nullptr));
        labelK_14->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\346\244\234\345\207\272\351\225\267\343\201\225", nullptr));
        labelK_15->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\350\274\235\345\272\246\345\244\211\345\214\226\343\201\256\346\244\234\345\207\272", nullptr));
        labelK_16->setText(QCoreApplication::translate("EachThresholdFormCADLine", "V\343\200\200\357\274\210\346\230\216\345\272\246\357\274\211", nullptr));
        labelK_17->setText(QCoreApplication::translate("EachThresholdFormCADLine", "S\343\200\200\357\274\210\345\275\251\345\272\246\357\274\211", nullptr));
        labelK_18->setText(QCoreApplication::translate("EachThresholdFormCADLine", "H\343\200\200\357\274\210\350\211\262\347\233\270\357\274\211", nullptr));
        labelK_19->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\346\232\227\345\201\264", nullptr));
        labelK_20->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\346\230\216\345\201\264", nullptr));
        labelK_21->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_22->setText(QCoreApplication::translate("EachThresholdFormCADLine", "mm2", nullptr));
        labelK_23->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\346\244\234\345\207\272\351\235\242\347\251\215", nullptr));
        labelK_24->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_25->setText(QCoreApplication::translate("EachThresholdFormCADLine", "mm", nullptr));
        labelK_26->setText(QCoreApplication::translate("EachThresholdFormCADLine", "\346\244\234\345\207\272\351\225\267\343\201\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EachThresholdFormCADLine: public Ui_EachThresholdFormCADLine {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EACHTHRESHOLDFORMCADLINE_H
