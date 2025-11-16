/********************************************************************************
** Form generated from reading UI file 'SettingColorDifferenceDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGCOLORDIFFERENCEDIALOG_H
#define UI_SETTINGCOLORDIFFERENCEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SettingColorDifferenceDialog
{
public:
    QFrame *frame;
    QLabel *label_49;
    QToolButton *toolButtonDelNGColor;
    QFrame *frameResult;
    QLabel *label_50;
    QTableWidget *tableWidgetResult;
    QLabel *label_51;
    QLineEdit *lineEditDeltaE;
    QLabel *label_53;
    QLineEdit *lineEditLenOK;
    QLabel *label_54;
    QLineEdit *lineEditLenNG;
    QTableWidget *tableWidgetHSVInfo;
    QLabel *label_52;
    QLabel *labelK_8;
    QToolButton *toolButtonCurrentColor;
    QListWidget *listWidgetOKBrightness;
    QFrame *frame_2;
    QLabel *labelK;
    QSlider *verticalSliderY;
    QFrame *frameMapK;
    QFrame *frameMap;
    QSpinBox *spinBoxK;
    QToolButton *toolButtonAddOKColor;
    QToolButton *toolButtonAddNGColor;
    QDoubleSpinBox *doubleSpinBoxAdoptedRate;
    QDoubleSpinBox *doubleSpinBoxTHDeltaE;
    QListWidget *listWidgetNGBrightness;
    QLabel *labelK_7;
    QToolButton *toolButtonDelOKColor;
    QLabel *label;
    QComboBox *comboBoxJudgeMethod;
    QLabel *label_60;
    QFrame *frame_5;
    QLabel *label_34;
    QLabel *label_59;
    QDoubleSpinBox *doubleSpinBoxdH;
    QDoubleSpinBox *doubleSpinBoxdSL;
    QLabel *label_61;
    QDoubleSpinBox *doubleSpinBoxdSH;
    QLabel *label_62;
    QDoubleSpinBox *doubleSpinBoxdVL;
    QLabel *label_63;
    QDoubleSpinBox *doubleSpinBoxdVH;
    QLabel *label_64;
    QPushButton *ButtonRelrectOnlyBlock;
    QPushButton *ButtonClose;
    QTableWidget *tableWidgetItemList;
    QLabel *label_2;
    QPushButton *ButtonReflectAllBlocks;
    QFrame *frameImage;

    void setupUi(QDialog *SettingColorDifferenceDialog)
    {
        if (SettingColorDifferenceDialog->objectName().isEmpty())
            SettingColorDifferenceDialog->setObjectName("SettingColorDifferenceDialog");
        SettingColorDifferenceDialog->resize(1485, 914);
        frame = new QFrame(SettingColorDifferenceDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(350, 0, 1131, 831));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_49 = new QLabel(frame);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(20, 530, 261, 31));
        QFont font;
        font.setPointSize(12);
        label_49->setFont(font);
        label_49->setFrameShape(QFrame::Panel);
        label_49->setFrameShadow(QFrame::Sunken);
        label_49->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        toolButtonDelNGColor = new QToolButton(frame);
        toolButtonDelNGColor->setObjectName("toolButtonDelNGColor");
        toolButtonDelNGColor->setGeometry(QRect(680, 210, 101, 61));
        toolButtonDelNGColor->setFont(font);
        toolButtonDelNGColor->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 230, 230, 255), stop:1 rgba(165, 130, 130, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 180, 180, 255), stop:1 rgba(141, 120, 120, 255));\n"
"}"));
        toolButtonDelNGColor->setCheckable(true);
        toolButtonDelNGColor->setAutoExclusive(true);
        frameResult = new QFrame(frame);
        frameResult->setObjectName("frameResult");
        frameResult->setGeometry(QRect(570, 280, 551, 461));
        frameResult->setFrameShape(QFrame::Panel);
        frameResult->setFrameShadow(QFrame::Sunken);
        label_50 = new QLabel(frameResult);
        label_50->setObjectName("label_50");
        label_50->setGeometry(QRect(0, 0, 551, 31));
        label_50->setFont(font);
        label_50->setFrameShape(QFrame::Panel);
        label_50->setFrameShadow(QFrame::Sunken);
        label_50->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetResult = new QTableWidget(frameResult);
        if (tableWidgetResult->columnCount() < 3)
            tableWidgetResult->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidgetResult->rowCount() < 4)
            tableWidgetResult->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetResult->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetResult->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetResult->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetResult->setVerticalHeaderItem(3, __qtablewidgetitem6);
        tableWidgetResult->setObjectName("tableWidgetResult");
        tableWidgetResult->setGeometry(QRect(10, 40, 531, 131));
        tableWidgetResult->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetResult->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        label_51 = new QLabel(frameResult);
        label_51->setObjectName("label_51");
        label_51->setGeometry(QRect(10, 250, 231, 31));
        label_51->setFont(font);
        label_51->setFrameShape(QFrame::Panel);
        label_51->setFrameShadow(QFrame::Sunken);
        label_51->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditDeltaE = new QLineEdit(frameResult);
        lineEditDeltaE->setObjectName("lineEditDeltaE");
        lineEditDeltaE->setGeometry(QRect(260, 250, 121, 31));
        lineEditDeltaE->setFont(font);
        lineEditDeltaE->setReadOnly(true);
        label_53 = new QLabel(frameResult);
        label_53->setObjectName("label_53");
        label_53->setGeometry(QRect(10, 180, 231, 31));
        label_53->setFont(font);
        label_53->setFrameShape(QFrame::Panel);
        label_53->setFrameShadow(QFrame::Sunken);
        label_53->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditLenOK = new QLineEdit(frameResult);
        lineEditLenOK->setObjectName("lineEditLenOK");
        lineEditLenOK->setGeometry(QRect(260, 180, 121, 31));
        lineEditLenOK->setFont(font);
        lineEditLenOK->setReadOnly(true);
        label_54 = new QLabel(frameResult);
        label_54->setObjectName("label_54");
        label_54->setGeometry(QRect(10, 210, 231, 31));
        label_54->setFont(font);
        label_54->setFrameShape(QFrame::Panel);
        label_54->setFrameShadow(QFrame::Sunken);
        label_54->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditLenNG = new QLineEdit(frameResult);
        lineEditLenNG->setObjectName("lineEditLenNG");
        lineEditLenNG->setGeometry(QRect(260, 210, 121, 31));
        lineEditLenNG->setFont(font);
        lineEditLenNG->setReadOnly(true);
        tableWidgetHSVInfo = new QTableWidget(frameResult);
        if (tableWidgetHSVInfo->columnCount() < 3)
            tableWidgetHSVInfo->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetHSVInfo->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetHSVInfo->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetHSVInfo->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        if (tableWidgetHSVInfo->rowCount() < 3)
            tableWidgetHSVInfo->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetHSVInfo->setVerticalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetHSVInfo->setVerticalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidgetHSVInfo->setVerticalHeaderItem(2, __qtablewidgetitem12);
        tableWidgetHSVInfo->setObjectName("tableWidgetHSVInfo");
        tableWidgetHSVInfo->setGeometry(QRect(10, 310, 531, 141));
        QFont font1;
        font1.setPointSize(10);
        tableWidgetHSVInfo->setFont(font1);
        tableWidgetHSVInfo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetHSVInfo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetHSVInfo->verticalHeader()->setMinimumSectionSize(36);
        tableWidgetHSVInfo->verticalHeader()->setDefaultSectionSize(36);
        label_52 = new QLabel(frame);
        label_52->setObjectName("label_52");
        label_52->setGeometry(QRect(20, 610, 261, 31));
        label_52->setFont(font);
        label_52->setFrameShape(QFrame::Panel);
        label_52->setFrameShadow(QFrame::Sunken);
        label_52->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelK_8 = new QLabel(frame);
        labelK_8->setObjectName("labelK_8");
        labelK_8->setGeometry(QRect(680, 40, 81, 31));
        labelK_8->setFont(font);
        labelK_8->setAlignment(Qt::AlignCenter);
        toolButtonCurrentColor = new QToolButton(frame);
        toolButtonCurrentColor->setObjectName("toolButtonCurrentColor");
        toolButtonCurrentColor->setGeometry(QRect(800, 80, 151, 71));
        toolButtonCurrentColor->setFont(font);
        toolButtonCurrentColor->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 254, 230, 255), stop:1 rgba(130, 165, 130, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonCurrentColor->setCheckable(false);
        toolButtonCurrentColor->setChecked(false);
        toolButtonCurrentColor->setAutoExclusive(false);
        listWidgetOKBrightness = new QListWidget(frame);
        listWidgetOKBrightness->setObjectName("listWidgetOKBrightness");
        listWidgetOKBrightness->setGeometry(QRect(570, 80, 101, 121));
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 40, 551, 481));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        labelK = new QLabel(frame_2);
        labelK->setObjectName("labelK");
        labelK->setGeometry(QRect(450, 3, 61, 20));
        labelK->setFont(font);
        labelK->setAlignment(Qt::AlignCenter);
        verticalSliderY = new QSlider(frame_2);
        verticalSliderY->setObjectName("verticalSliderY");
        verticalSliderY->setGeometry(QRect(461, 33, 41, 331));
        verticalSliderY->setMaximum(255);
        verticalSliderY->setValue(128);
        verticalSliderY->setOrientation(Qt::Vertical);
        frameMapK = new QFrame(frame_2);
        frameMapK->setObjectName("frameMapK");
        frameMapK->setGeometry(QRect(510, 33, 31, 331));
        frameMapK->setFrameShape(QFrame::StyledPanel);
        frameMapK->setFrameShadow(QFrame::Raised);
        frameMap = new QFrame(frame_2);
        frameMap->setObjectName("frameMap");
        frameMap->setGeometry(QRect(10, 10, 441, 401));
        frameMap->setFrameShape(QFrame::StyledPanel);
        frameMap->setFrameShadow(QFrame::Raised);
        spinBoxK = new QSpinBox(frame_2);
        spinBoxK->setObjectName("spinBoxK");
        spinBoxK->setGeometry(QRect(460, 370, 81, 41));
        QFont font2;
        font2.setPointSize(16);
        spinBoxK->setFont(font2);
        spinBoxK->setMaximum(255);
        spinBoxK->setValue(128);
        toolButtonAddOKColor = new QToolButton(frame_2);
        toolButtonAddOKColor->setObjectName("toolButtonAddOKColor");
        toolButtonAddOKColor->setGeometry(QRect(20, 420, 211, 61));
        toolButtonAddOKColor->setFont(font);
        toolButtonAddOKColor->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 254, 230, 255), stop:1 rgba(130, 165, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonAddOKColor->setCheckable(true);
        toolButtonAddOKColor->setChecked(false);
        toolButtonAddOKColor->setAutoExclusive(true);
        toolButtonAddNGColor = new QToolButton(frame_2);
        toolButtonAddNGColor->setObjectName("toolButtonAddNGColor");
        toolButtonAddNGColor->setGeometry(QRect(250, 420, 211, 61));
        toolButtonAddNGColor->setFont(font);
        toolButtonAddNGColor->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 230, 230, 255), stop:1 rgba(165, 130, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 0, 0, 255), stop:1 rgba(141,0, 0, 255));\n"
"}"));
        toolButtonAddNGColor->setCheckable(true);
        toolButtonAddNGColor->setChecked(false);
        toolButtonAddNGColor->setAutoExclusive(true);
        doubleSpinBoxAdoptedRate = new QDoubleSpinBox(frame);
        doubleSpinBoxAdoptedRate->setObjectName("doubleSpinBoxAdoptedRate");
        doubleSpinBoxAdoptedRate->setGeometry(QRect(290, 530, 101, 31));
        doubleSpinBoxAdoptedRate->setFont(font);
        doubleSpinBoxAdoptedRate->setMaximum(100.000000000000000);
        doubleSpinBoxTHDeltaE = new QDoubleSpinBox(frame);
        doubleSpinBoxTHDeltaE->setObjectName("doubleSpinBoxTHDeltaE");
        doubleSpinBoxTHDeltaE->setGeometry(QRect(290, 610, 101, 31));
        doubleSpinBoxTHDeltaE->setFont(font);
        doubleSpinBoxTHDeltaE->setDecimals(3);
        doubleSpinBoxTHDeltaE->setMaximum(100.000000000000000);
        listWidgetNGBrightness = new QListWidget(frame);
        listWidgetNGBrightness->setObjectName("listWidgetNGBrightness");
        listWidgetNGBrightness->setGeometry(QRect(680, 80, 101, 121));
        labelK_7 = new QLabel(frame);
        labelK_7->setObjectName("labelK_7");
        labelK_7->setGeometry(QRect(570, 40, 81, 31));
        labelK_7->setFont(font);
        labelK_7->setAlignment(Qt::AlignCenter);
        toolButtonDelOKColor = new QToolButton(frame);
        toolButtonDelOKColor->setObjectName("toolButtonDelOKColor");
        toolButtonDelOKColor->setGeometry(QRect(570, 210, 101, 61));
        toolButtonDelOKColor->setFont(font);
        toolButtonDelOKColor->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 230, 230, 255), stop:1 rgba(165, 130, 130, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 180, 180, 255), stop:1 rgba(141, 120, 120, 255));\n"
"}"));
        toolButtonDelOKColor->setCheckable(true);
        toolButtonDelOKColor->setAutoExclusive(true);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 971, 31));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        comboBoxJudgeMethod = new QComboBox(frame);
        comboBoxJudgeMethod->addItem(QString());
        comboBoxJudgeMethod->addItem(QString());
        comboBoxJudgeMethod->addItem(QString());
        comboBoxJudgeMethod->setObjectName("comboBoxJudgeMethod");
        comboBoxJudgeMethod->setGeometry(QRect(290, 570, 241, 31));
        comboBoxJudgeMethod->setFont(font);
        label_60 = new QLabel(frame);
        label_60->setObjectName("label_60");
        label_60->setGeometry(QRect(20, 570, 261, 31));
        QFont font3;
        font3.setPointSize(14);
        label_60->setFont(font3);
        label_60->setFrameShape(QFrame::Panel);
        label_60->setFrameShadow(QFrame::Sunken);
        label_60->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_5 = new QFrame(frame);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 650, 551, 171));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Sunken);
        label_34 = new QLabel(frame_5);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(0, 0, 31, 171));
        label_34->setFont(font);
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Raised);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_34->setIndent(1);
        label_59 = new QLabel(frame_5);
        label_59->setObjectName("label_59");
        label_59->setGeometry(QRect(50, 10, 380, 28));
        label_59->setFont(font);
        label_59->setFrameShape(QFrame::Panel);
        label_59->setFrameShadow(QFrame::Sunken);
        label_59->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxdH = new QDoubleSpinBox(frame_5);
        doubleSpinBoxdH->setObjectName("doubleSpinBoxdH");
        doubleSpinBoxdH->setGeometry(QRect(440, 10, 101, 28));
        doubleSpinBoxdH->setFont(font);
        doubleSpinBoxdH->setMaximum(100.000000000000000);
        doubleSpinBoxdSL = new QDoubleSpinBox(frame_5);
        doubleSpinBoxdSL->setObjectName("doubleSpinBoxdSL");
        doubleSpinBoxdSL->setGeometry(QRect(440, 40, 101, 28));
        doubleSpinBoxdSL->setFont(font);
        doubleSpinBoxdSL->setMaximum(100.000000000000000);
        label_61 = new QLabel(frame_5);
        label_61->setObjectName("label_61");
        label_61->setGeometry(QRect(50, 40, 380, 28));
        label_61->setFont(font);
        label_61->setFrameShape(QFrame::Panel);
        label_61->setFrameShadow(QFrame::Sunken);
        label_61->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxdSH = new QDoubleSpinBox(frame_5);
        doubleSpinBoxdSH->setObjectName("doubleSpinBoxdSH");
        doubleSpinBoxdSH->setGeometry(QRect(440, 70, 101, 28));
        doubleSpinBoxdSH->setFont(font);
        doubleSpinBoxdSH->setMaximum(100.000000000000000);
        label_62 = new QLabel(frame_5);
        label_62->setObjectName("label_62");
        label_62->setGeometry(QRect(50, 70, 380, 28));
        label_62->setFont(font);
        label_62->setFrameShape(QFrame::Panel);
        label_62->setFrameShadow(QFrame::Sunken);
        label_62->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxdVL = new QDoubleSpinBox(frame_5);
        doubleSpinBoxdVL->setObjectName("doubleSpinBoxdVL");
        doubleSpinBoxdVL->setGeometry(QRect(440, 100, 101, 28));
        doubleSpinBoxdVL->setFont(font);
        doubleSpinBoxdVL->setMaximum(100.000000000000000);
        label_63 = new QLabel(frame_5);
        label_63->setObjectName("label_63");
        label_63->setGeometry(QRect(50, 100, 380, 28));
        label_63->setFont(font);
        label_63->setFrameShape(QFrame::Panel);
        label_63->setFrameShadow(QFrame::Sunken);
        label_63->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxdVH = new QDoubleSpinBox(frame_5);
        doubleSpinBoxdVH->setObjectName("doubleSpinBoxdVH");
        doubleSpinBoxdVH->setGeometry(QRect(440, 130, 101, 28));
        doubleSpinBoxdVH->setFont(font);
        doubleSpinBoxdVH->setMaximum(100.000000000000000);
        label_64 = new QLabel(frame_5);
        label_64->setObjectName("label_64");
        label_64->setGeometry(QRect(50, 130, 380, 28));
        label_64->setFont(font);
        label_64->setFrameShape(QFrame::Panel);
        label_64->setFrameShadow(QFrame::Sunken);
        label_64->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonRelrectOnlyBlock = new QPushButton(SettingColorDifferenceDialog);
        ButtonRelrectOnlyBlock->setObjectName("ButtonRelrectOnlyBlock");
        ButtonRelrectOnlyBlock->setGeometry(QRect(370, 840, 251, 61));
        ButtonRelrectOnlyBlock->setFont(font);
        ButtonRelrectOnlyBlock->setAcceptDrops(true);
        ButtonRelrectOnlyBlock->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 254, 230, 255), stop:1 rgba(130, 165, 130, 255));\n"
"}\n"
"QPushButton:Pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        ButtonClose = new QPushButton(SettingColorDifferenceDialog);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(1330, 840, 151, 61));
        ButtonClose->setFont(font);
        tableWidgetItemList = new QTableWidget(SettingColorDifferenceDialog);
        if (tableWidgetItemList->columnCount() < 4)
            tableWidgetItemList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(2, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(3, __qtablewidgetitem16);
        tableWidgetItemList->setObjectName("tableWidgetItemList");
        tableWidgetItemList->setGeometry(QRect(10, 30, 331, 441));
        tableWidgetItemList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetItemList->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_2 = new QLabel(SettingColorDifferenceDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 0, 331, 31));
        label_2->setFont(font);
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        ButtonReflectAllBlocks = new QPushButton(SettingColorDifferenceDialog);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(660, 840, 251, 61));
        ButtonReflectAllBlocks->setFont(font);
        ButtonReflectAllBlocks->setAcceptDrops(true);
        ButtonReflectAllBlocks->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 254, 230, 255), stop:1 rgba(130, 165, 130, 255));\n"
"}\n"
"QPushButton:Pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        frameImage = new QFrame(SettingColorDifferenceDialog);
        frameImage->setObjectName("frameImage");
        frameImage->setGeometry(QRect(10, 480, 331, 421));
        frameImage->setFrameShape(QFrame::Panel);
        frameImage->setFrameShadow(QFrame::Sunken);

        retranslateUi(SettingColorDifferenceDialog);

        comboBoxJudgeMethod->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SettingColorDifferenceDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingColorDifferenceDialog)
    {
        SettingColorDifferenceDialog->setWindowTitle(QCoreApplication::translate("SettingColorDifferenceDialog", "\350\211\262\345\267\256\350\250\255\345\256\232", nullptr));
        label_49->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\346\216\241\347\224\250\347\216\207 (%)", nullptr));
        toolButtonDelNGColor->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\345\211\212\351\231\244", nullptr));
        label_50->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\345\210\244\345\256\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetResult->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "RGB", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetResult->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "HSV", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetResult->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "LAB", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetResult->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\345\217\202\347\205\247\347\202\2711", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetResult->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\345\217\202\347\205\247\347\202\2712", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetResult->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\343\203\236\343\202\271\343\202\277\343\203\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetResult->verticalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\346\244\234\346\237\273", nullptr));
        label_51->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\316\224E", nullptr));
        label_53->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "OK\350\211\262\343\201\250\343\201\256\350\267\235\351\233\242", nullptr));
        label_54->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "NG\350\211\262\343\201\250\343\201\256\350\267\235\351\233\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetHSVInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "H", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetHSVInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "S", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetHSVInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "V", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetHSVInfo->verticalHeaderItem(0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\346\265\201\345\213\225\344\270\255\345\277\203", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetHSVInfo->verticalHeaderItem(1);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\346\244\234\346\237\273\345\267\256\347\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetHSVInfo->verticalHeaderItem(2);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\343\202\267\343\202\260\343\203\236", nullptr));
        label_52->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\316\224E\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        labelK_8->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "NG", nullptr));
        toolButtonCurrentColor->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\347\217\276\345\234\250\350\211\262", nullptr));
        labelK->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "V", nullptr));
        toolButtonAddOKColor->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "OK\350\211\262\350\277\275\345\212\240", nullptr));
        toolButtonAddNGColor->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "NG\350\211\262\350\277\275\345\212\240", nullptr));
        labelK_7->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "OK", nullptr));
        toolButtonDelOKColor->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\345\211\212\351\231\244", nullptr));
        label->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\351\201\270\346\212\236\343\201\225\343\202\214\343\201\237\346\244\234\346\237\273\351\240\230\345\237\237\343\201\256\346\203\205\345\240\261", nullptr));
        comboBoxJudgeMethod->setItemText(0, QCoreApplication::translate("SettingColorDifferenceDialog", "OK/NG\343\202\222\344\275\277\343\201\206", nullptr));
        comboBoxJudgeMethod->setItemText(1, QCoreApplication::translate("SettingColorDifferenceDialog", "\316\224E\343\201\247\345\210\244\345\256\232", nullptr));
        comboBoxJudgeMethod->setItemText(2, QCoreApplication::translate("SettingColorDifferenceDialog", "\346\265\201\345\213\225\343\202\265\343\203\263\343\203\227\343\203\253\343\201\247HSV\345\210\244\345\256\232", nullptr));

        label_60->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\345\210\244\345\256\232\346\226\271\346\263\225", nullptr));
        label_34->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "<html><head/><body><p>H</p><p>S</p><p>V</p></body></html>", nullptr));
        label_59->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "H\343\201\256\350\250\261\345\256\271\345\267\256\347\225\260", nullptr));
        label_61->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "S\343\201\256\344\270\255\345\277\203\345\201\264\343\201\256\350\250\261\345\256\271\345\267\256\347\225\260", nullptr));
        label_62->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "S\343\201\256\345\244\226\345\201\264\343\201\256\350\250\261\345\256\271\345\267\256\347\225\260", nullptr));
        label_63->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "V\343\201\256\346\232\227\345\201\264\343\201\256\350\250\261\345\256\271\345\267\256\347\225\260", nullptr));
        label_64->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "V\343\201\256\346\230\216\345\201\264\343\201\256\350\250\261\345\256\271\345\267\256\347\225\260", nullptr));
        ButtonRelrectOnlyBlock->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\343\201\223\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonClose->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidgetItemList->horizontalHeaderItem(0);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "Phase", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidgetItemList->horizontalHeaderItem(1);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidgetItemList->horizontalHeaderItem(2);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidgetItemList->horizontalHeaderItem(3);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "Position", nullptr));
        label_2->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\346\244\234\346\237\273\351\240\230\345\237\237", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("SettingColorDifferenceDialog", "\343\201\231\343\201\271\343\201\246\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\253\345\217\215\346\230\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingColorDifferenceDialog: public Ui_SettingColorDifferenceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGCOLORDIFFERENCEDIALOG_H
