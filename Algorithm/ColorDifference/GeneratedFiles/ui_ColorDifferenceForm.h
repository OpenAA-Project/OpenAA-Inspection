/********************************************************************************
** Form generated from reading UI file 'ColorDifferenceForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORDIFFERENCEFORM_H
#define UI_COLORDIFFERENCEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ColorDifferenceForm
{
public:
    QFrame *frame;
    QLabel *labelK;
    QSlider *verticalSliderY;
    QFrame *frameMapK;
    QFrame *frameMap;
    QSpinBox *spinBoxK;
    QToolButton *toolButtonAddOKColor;
    QToolButton *toolButtonAddNGColor;
    QListWidget *listWidgetOKBrightness;
    QLabel *labelK_7;
    QListWidget *listWidgetNGBrightness;
    QLabel *labelK_8;
    QToolButton *toolButtonDelOKColor;
    QToolButton *toolButtonDelNGColor;
    QLabel *label_49;
    QDoubleSpinBox *doubleSpinBoxAdoptedRate;
    QPushButton *ButtonReflectAllBlocks;
    QPushButton *ButtonClose;
    QPushButton *ButtonLoadFromLibrary;
    QPushButton *ButtonRelrectOnlyBlock;
    QPushButton *ButtonSaveToLibrary;
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
    QPushButton *pushButtonOutputFlowList;
    QLabel *label_52;
    QDoubleSpinBox *doubleSpinBoxTHDeltaE;
    QToolButton *toolButtonCurrentColor;
    QFrame *frameThreshold;
    QLabel *label_34;
    QLabel *label_55;
    QDoubleSpinBox *doubleSpinBoxdH;
    QDoubleSpinBox *doubleSpinBoxdSL;
    QLabel *label_56;
    QDoubleSpinBox *doubleSpinBoxdSH;
    QLabel *label_57;
    QDoubleSpinBox *doubleSpinBoxdVL;
    QLabel *label_58;
    QDoubleSpinBox *doubleSpinBoxdVH;
    QLabel *label_59;
    QComboBox *comboBoxJudgeMethod;
    QLabel *label_60;
    QLabel *label_61;
    QLineEdit *lineEditItemName;
    QPushButton *pushButtonSetItemName;
    QCheckBox *checkBoxOutputConstantly;
    QCheckBox *checkBoxAdaptAlignment;
    QLabel *label_62;

    void setupUi(QWidget *ColorDifferenceForm)
    {
        if (ColorDifferenceForm->objectName().isEmpty())
            ColorDifferenceForm->setObjectName("ColorDifferenceForm");
        ColorDifferenceForm->resize(1023, 981);
        frame = new QFrame(ColorDifferenceForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 50, 551, 481));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        labelK = new QLabel(frame);
        labelK->setObjectName("labelK");
        labelK->setGeometry(QRect(450, 3, 61, 20));
        QFont font;
        font.setPointSize(12);
        labelK->setFont(font);
        labelK->setAlignment(Qt::AlignCenter);
        verticalSliderY = new QSlider(frame);
        verticalSliderY->setObjectName("verticalSliderY");
        verticalSliderY->setGeometry(QRect(461, 33, 41, 331));
        verticalSliderY->setMaximum(255);
        verticalSliderY->setValue(128);
        verticalSliderY->setOrientation(Qt::Vertical);
        frameMapK = new QFrame(frame);
        frameMapK->setObjectName("frameMapK");
        frameMapK->setGeometry(QRect(510, 33, 31, 331));
        frameMapK->setFrameShape(QFrame::StyledPanel);
        frameMapK->setFrameShadow(QFrame::Raised);
        frameMap = new QFrame(frame);
        frameMap->setObjectName("frameMap");
        frameMap->setGeometry(QRect(10, 10, 441, 401));
        frameMap->setFrameShape(QFrame::StyledPanel);
        frameMap->setFrameShadow(QFrame::Raised);
        spinBoxK = new QSpinBox(frame);
        spinBoxK->setObjectName("spinBoxK");
        spinBoxK->setGeometry(QRect(460, 370, 81, 41));
        QFont font1;
        font1.setPointSize(16);
        spinBoxK->setFont(font1);
        spinBoxK->setMaximum(255);
        spinBoxK->setValue(128);
        toolButtonAddOKColor = new QToolButton(frame);
        toolButtonAddOKColor->setObjectName("toolButtonAddOKColor");
        toolButtonAddOKColor->setGeometry(QRect(20, 420, 211, 51));
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
        toolButtonAddOKColor->setChecked(true);
        toolButtonAddOKColor->setAutoExclusive(true);
        toolButtonAddNGColor = new QToolButton(frame);
        toolButtonAddNGColor->setObjectName("toolButtonAddNGColor");
        toolButtonAddNGColor->setGeometry(QRect(250, 420, 211, 51));
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
        listWidgetOKBrightness = new QListWidget(ColorDifferenceForm);
        listWidgetOKBrightness->setObjectName("listWidgetOKBrightness");
        listWidgetOKBrightness->setGeometry(QRect(570, 90, 71, 201));
        labelK_7 = new QLabel(ColorDifferenceForm);
        labelK_7->setObjectName("labelK_7");
        labelK_7->setGeometry(QRect(570, 50, 61, 31));
        labelK_7->setFont(font);
        labelK_7->setAlignment(Qt::AlignCenter);
        listWidgetNGBrightness = new QListWidget(ColorDifferenceForm);
        listWidgetNGBrightness->setObjectName("listWidgetNGBrightness");
        listWidgetNGBrightness->setGeometry(QRect(650, 90, 71, 201));
        labelK_8 = new QLabel(ColorDifferenceForm);
        labelK_8->setObjectName("labelK_8");
        labelK_8->setGeometry(QRect(650, 50, 61, 31));
        labelK_8->setFont(font);
        labelK_8->setAlignment(Qt::AlignCenter);
        toolButtonDelOKColor = new QToolButton(ColorDifferenceForm);
        toolButtonDelOKColor->setObjectName("toolButtonDelOKColor");
        toolButtonDelOKColor->setGeometry(QRect(570, 300, 71, 51));
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
        toolButtonDelOKColor->setCheckable(false);
        toolButtonDelOKColor->setAutoExclusive(false);
        toolButtonDelNGColor = new QToolButton(ColorDifferenceForm);
        toolButtonDelNGColor->setObjectName("toolButtonDelNGColor");
        toolButtonDelNGColor->setGeometry(QRect(650, 300, 71, 51));
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
        toolButtonDelNGColor->setCheckable(false);
        toolButtonDelNGColor->setAutoExclusive(false);
        label_49 = new QLabel(ColorDifferenceForm);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(50, 540, 391, 31));
        label_49->setFont(font);
        label_49->setFrameShape(QFrame::Panel);
        label_49->setFrameShadow(QFrame::Sunken);
        label_49->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxAdoptedRate = new QDoubleSpinBox(ColorDifferenceForm);
        doubleSpinBoxAdoptedRate->setObjectName("doubleSpinBoxAdoptedRate");
        doubleSpinBoxAdoptedRate->setGeometry(QRect(450, 540, 101, 31));
        doubleSpinBoxAdoptedRate->setFont(font);
        doubleSpinBoxAdoptedRate->setMaximum(100.000000000000000);
        ButtonReflectAllBlocks = new QPushButton(ColorDifferenceForm);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(210, 880, 191, 41));
        ButtonReflectAllBlocks->setAcceptDrops(true);
        ButtonClose = new QPushButton(ColorDifferenceForm);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(420, 930, 131, 41));
        ButtonLoadFromLibrary = new QPushButton(ColorDifferenceForm);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(210, 930, 191, 41));
        ButtonLoadFromLibrary->setAcceptDrops(true);
        ButtonRelrectOnlyBlock = new QPushButton(ColorDifferenceForm);
        ButtonRelrectOnlyBlock->setObjectName("ButtonRelrectOnlyBlock");
        ButtonRelrectOnlyBlock->setGeometry(QRect(10, 880, 191, 41));
        ButtonRelrectOnlyBlock->setAcceptDrops(true);
        ButtonSaveToLibrary = new QPushButton(ColorDifferenceForm);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(10, 930, 191, 41));
        ButtonSaveToLibrary->setAcceptDrops(true);
        frameResult = new QFrame(ColorDifferenceForm);
        frameResult->setObjectName("frameResult");
        frameResult->setGeometry(QRect(570, 360, 451, 561));
        frameResult->setFrameShape(QFrame::Panel);
        frameResult->setFrameShadow(QFrame::Sunken);
        label_50 = new QLabel(frameResult);
        label_50->setObjectName("label_50");
        label_50->setGeometry(QRect(0, 0, 291, 31));
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
        tableWidgetResult->setGeometry(QRect(10, 36, 431, 181));
        tableWidgetResult->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetResult->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        label_51 = new QLabel(frameResult);
        label_51->setObjectName("label_51");
        label_51->setGeometry(QRect(10, 290, 231, 31));
        label_51->setFont(font);
        label_51->setFrameShape(QFrame::Panel);
        label_51->setFrameShadow(QFrame::Sunken);
        label_51->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditDeltaE = new QLineEdit(frameResult);
        lineEditDeltaE->setObjectName("lineEditDeltaE");
        lineEditDeltaE->setGeometry(QRect(260, 290, 121, 31));
        lineEditDeltaE->setFont(font);
        lineEditDeltaE->setReadOnly(true);
        label_53 = new QLabel(frameResult);
        label_53->setObjectName("label_53");
        label_53->setGeometry(QRect(10, 220, 231, 31));
        label_53->setFont(font);
        label_53->setFrameShape(QFrame::Panel);
        label_53->setFrameShadow(QFrame::Sunken);
        label_53->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditLenOK = new QLineEdit(frameResult);
        lineEditLenOK->setObjectName("lineEditLenOK");
        lineEditLenOK->setGeometry(QRect(260, 220, 121, 31));
        lineEditLenOK->setFont(font);
        lineEditLenOK->setReadOnly(true);
        label_54 = new QLabel(frameResult);
        label_54->setObjectName("label_54");
        label_54->setGeometry(QRect(10, 250, 231, 31));
        label_54->setFont(font);
        label_54->setFrameShape(QFrame::Panel);
        label_54->setFrameShadow(QFrame::Sunken);
        label_54->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditLenNG = new QLineEdit(frameResult);
        lineEditLenNG->setObjectName("lineEditLenNG");
        lineEditLenNG->setGeometry(QRect(260, 250, 121, 31));
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
        tableWidgetHSVInfo->setGeometry(QRect(10, 350, 371, 141));
        QFont font2;
        font2.setPointSize(10);
        tableWidgetHSVInfo->setFont(font2);
        tableWidgetHSVInfo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetHSVInfo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetHSVInfo->verticalHeader()->setMinimumSectionSize(36);
        tableWidgetHSVInfo->verticalHeader()->setDefaultSectionSize(36);
        pushButtonOutputFlowList = new QPushButton(frameResult);
        pushButtonOutputFlowList->setObjectName("pushButtonOutputFlowList");
        pushButtonOutputFlowList->setGeometry(QRect(110, 503, 191, 41));
        label_52 = new QLabel(ColorDifferenceForm);
        label_52->setObjectName("label_52");
        label_52->setGeometry(QRect(50, 660, 391, 31));
        label_52->setFont(font);
        label_52->setFrameShape(QFrame::Panel);
        label_52->setFrameShadow(QFrame::Sunken);
        label_52->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxTHDeltaE = new QDoubleSpinBox(ColorDifferenceForm);
        doubleSpinBoxTHDeltaE->setObjectName("doubleSpinBoxTHDeltaE");
        doubleSpinBoxTHDeltaE->setGeometry(QRect(450, 660, 101, 31));
        doubleSpinBoxTHDeltaE->setFont(font);
        doubleSpinBoxTHDeltaE->setMaximum(100.000000000000000);
        toolButtonCurrentColor = new QToolButton(ColorDifferenceForm);
        toolButtonCurrentColor->setObjectName("toolButtonCurrentColor");
        toolButtonCurrentColor->setGeometry(QRect(730, 90, 131, 51));
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
        frameThreshold = new QFrame(ColorDifferenceForm);
        frameThreshold->setObjectName("frameThreshold");
        frameThreshold->setGeometry(QRect(10, 700, 551, 171));
        frameThreshold->setFrameShape(QFrame::StyledPanel);
        frameThreshold->setFrameShadow(QFrame::Sunken);
        label_34 = new QLabel(frameThreshold);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(0, 0, 31, 171));
        label_34->setFont(font);
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Raised);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_34->setIndent(1);
        label_55 = new QLabel(frameThreshold);
        label_55->setObjectName("label_55");
        label_55->setGeometry(QRect(50, 10, 380, 28));
        label_55->setFont(font);
        label_55->setFrameShape(QFrame::Panel);
        label_55->setFrameShadow(QFrame::Sunken);
        label_55->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxdH = new QDoubleSpinBox(frameThreshold);
        doubleSpinBoxdH->setObjectName("doubleSpinBoxdH");
        doubleSpinBoxdH->setGeometry(QRect(440, 10, 101, 28));
        doubleSpinBoxdH->setFont(font);
        doubleSpinBoxdH->setMaximum(100.000000000000000);
        doubleSpinBoxdSL = new QDoubleSpinBox(frameThreshold);
        doubleSpinBoxdSL->setObjectName("doubleSpinBoxdSL");
        doubleSpinBoxdSL->setGeometry(QRect(440, 40, 101, 28));
        doubleSpinBoxdSL->setFont(font);
        doubleSpinBoxdSL->setMaximum(100.000000000000000);
        label_56 = new QLabel(frameThreshold);
        label_56->setObjectName("label_56");
        label_56->setGeometry(QRect(50, 40, 380, 28));
        label_56->setFont(font);
        label_56->setFrameShape(QFrame::Panel);
        label_56->setFrameShadow(QFrame::Sunken);
        label_56->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxdSH = new QDoubleSpinBox(frameThreshold);
        doubleSpinBoxdSH->setObjectName("doubleSpinBoxdSH");
        doubleSpinBoxdSH->setGeometry(QRect(440, 70, 101, 28));
        doubleSpinBoxdSH->setFont(font);
        doubleSpinBoxdSH->setMaximum(100.000000000000000);
        label_57 = new QLabel(frameThreshold);
        label_57->setObjectName("label_57");
        label_57->setGeometry(QRect(50, 70, 380, 28));
        label_57->setFont(font);
        label_57->setFrameShape(QFrame::Panel);
        label_57->setFrameShadow(QFrame::Sunken);
        label_57->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxdVL = new QDoubleSpinBox(frameThreshold);
        doubleSpinBoxdVL->setObjectName("doubleSpinBoxdVL");
        doubleSpinBoxdVL->setGeometry(QRect(440, 100, 101, 28));
        doubleSpinBoxdVL->setFont(font);
        doubleSpinBoxdVL->setMaximum(100.000000000000000);
        label_58 = new QLabel(frameThreshold);
        label_58->setObjectName("label_58");
        label_58->setGeometry(QRect(50, 100, 380, 28));
        label_58->setFont(font);
        label_58->setFrameShape(QFrame::Panel);
        label_58->setFrameShadow(QFrame::Sunken);
        label_58->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxdVH = new QDoubleSpinBox(frameThreshold);
        doubleSpinBoxdVH->setObjectName("doubleSpinBoxdVH");
        doubleSpinBoxdVH->setGeometry(QRect(440, 130, 101, 28));
        doubleSpinBoxdVH->setFont(font);
        doubleSpinBoxdVH->setMaximum(100.000000000000000);
        label_59 = new QLabel(frameThreshold);
        label_59->setObjectName("label_59");
        label_59->setGeometry(QRect(50, 130, 380, 28));
        label_59->setFont(font);
        label_59->setFrameShape(QFrame::Panel);
        label_59->setFrameShadow(QFrame::Sunken);
        label_59->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        comboBoxJudgeMethod = new QComboBox(ColorDifferenceForm);
        comboBoxJudgeMethod->addItem(QString());
        comboBoxJudgeMethod->addItem(QString());
        comboBoxJudgeMethod->addItem(QString());
        comboBoxJudgeMethod->setObjectName("comboBoxJudgeMethod");
        comboBoxJudgeMethod->setGeometry(QRect(310, 620, 241, 31));
        comboBoxJudgeMethod->setFont(font);
        label_60 = new QLabel(ColorDifferenceForm);
        label_60->setObjectName("label_60");
        label_60->setGeometry(QRect(50, 620, 251, 31));
        QFont font3;
        font3.setPointSize(14);
        label_60->setFont(font3);
        label_60->setFrameShape(QFrame::Panel);
        label_60->setFrameShadow(QFrame::Sunken);
        label_60->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_61 = new QLabel(ColorDifferenceForm);
        label_61->setObjectName("label_61");
        label_61->setGeometry(QRect(10, 10, 131, 31));
        label_61->setFont(font3);
        label_61->setFrameShape(QFrame::Panel);
        label_61->setFrameShadow(QFrame::Sunken);
        label_61->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditItemName = new QLineEdit(ColorDifferenceForm);
        lineEditItemName->setObjectName("lineEditItemName");
        lineEditItemName->setGeometry(QRect(140, 10, 421, 31));
        lineEditItemName->setFont(font);
        pushButtonSetItemName = new QPushButton(ColorDifferenceForm);
        pushButtonSetItemName->setObjectName("pushButtonSetItemName");
        pushButtonSetItemName->setGeometry(QRect(570, 10, 112, 34));
        pushButtonSetItemName->setFont(font);
        checkBoxOutputConstantly = new QCheckBox(ColorDifferenceForm);
        checkBoxOutputConstantly->setObjectName("checkBoxOutputConstantly");
        checkBoxOutputConstantly->setGeometry(QRect(50, 580, 401, 22));
        checkBoxOutputConstantly->setFont(font);
        checkBoxAdaptAlignment = new QCheckBox(ColorDifferenceForm);
        checkBoxAdaptAlignment->setObjectName("checkBoxAdaptAlignment");
        checkBoxAdaptAlignment->setGeometry(QRect(820, 940, 71, 21));
        label_62 = new QLabel(ColorDifferenceForm);
        label_62->setObjectName("label_62");
        label_62->setGeometry(QRect(570, 940, 241, 24));
        QFont font4;
        font4.setPointSize(9);
        label_62->setFont(font4);
        label_62->setFrameShape(QFrame::Panel);
        label_62->setFrameShadow(QFrame::Sunken);
        label_62->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(ColorDifferenceForm);

        QMetaObject::connectSlotsByName(ColorDifferenceForm);
    } // setupUi

    void retranslateUi(QWidget *ColorDifferenceForm)
    {
        ColorDifferenceForm->setWindowTitle(QCoreApplication::translate("ColorDifferenceForm", "Form", nullptr));
        labelK->setText(QCoreApplication::translate("ColorDifferenceForm", "Y", nullptr));
        toolButtonAddOKColor->setText(QCoreApplication::translate("ColorDifferenceForm", "OK\350\211\262\350\277\275\345\212\240", nullptr));
        toolButtonAddNGColor->setText(QCoreApplication::translate("ColorDifferenceForm", "NG\350\211\262\350\277\275\345\212\240", nullptr));
        labelK_7->setText(QCoreApplication::translate("ColorDifferenceForm", "OK", nullptr));
        labelK_8->setText(QCoreApplication::translate("ColorDifferenceForm", "NG", nullptr));
        toolButtonDelOKColor->setText(QCoreApplication::translate("ColorDifferenceForm", "\345\211\212\351\231\244", nullptr));
        toolButtonDelNGColor->setText(QCoreApplication::translate("ColorDifferenceForm", "\345\211\212\351\231\244", nullptr));
        label_49->setText(QCoreApplication::translate("ColorDifferenceForm", "\346\216\241\347\224\250\347\216\207 (%)", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("ColorDifferenceForm", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonClose->setText(QCoreApplication::translate("ColorDifferenceForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("ColorDifferenceForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        ButtonRelrectOnlyBlock->setText(QCoreApplication::translate("ColorDifferenceForm", "\343\201\223\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("ColorDifferenceForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        label_50->setText(QCoreApplication::translate("ColorDifferenceForm", "\345\210\244\345\256\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetResult->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ColorDifferenceForm", "RGB", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetResult->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ColorDifferenceForm", "HSV", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetResult->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ColorDifferenceForm", "LAB", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetResult->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ColorDifferenceForm", "\345\217\202\347\205\247\347\202\2711", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetResult->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ColorDifferenceForm", "\345\217\202\347\205\247\347\202\2712", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetResult->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ColorDifferenceForm", "\343\203\236\343\202\271\343\202\277\343\203\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetResult->verticalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ColorDifferenceForm", "\346\244\234\346\237\273", nullptr));
        label_51->setText(QCoreApplication::translate("ColorDifferenceForm", "\316\224E", nullptr));
        label_53->setText(QCoreApplication::translate("ColorDifferenceForm", "OK\350\211\262\343\201\250\343\201\256\350\267\235\351\233\242", nullptr));
        label_54->setText(QCoreApplication::translate("ColorDifferenceForm", "NG\350\211\262\343\201\250\343\201\256\350\267\235\351\233\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetHSVInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("ColorDifferenceForm", "H", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetHSVInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("ColorDifferenceForm", "S", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetHSVInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("ColorDifferenceForm", "V", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetHSVInfo->verticalHeaderItem(0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("ColorDifferenceForm", "\346\265\201\345\213\225\344\270\255\345\277\203", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetHSVInfo->verticalHeaderItem(1);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("ColorDifferenceForm", "\346\244\234\346\237\273\345\267\256\347\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetHSVInfo->verticalHeaderItem(2);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("ColorDifferenceForm", "\343\202\267\343\202\260\343\203\236", nullptr));
        pushButtonOutputFlowList->setText(QCoreApplication::translate("ColorDifferenceForm", "\346\265\201\345\213\225\343\203\252\343\202\271\343\203\210\345\207\272\345\212\233", nullptr));
        label_52->setText(QCoreApplication::translate("ColorDifferenceForm", "\316\224E\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        toolButtonCurrentColor->setText(QCoreApplication::translate("ColorDifferenceForm", "\347\217\276\345\234\250\350\211\262", nullptr));
        label_34->setText(QCoreApplication::translate("ColorDifferenceForm", "<html><head/><body><p>H</p><p>S</p><p>V</p></body></html>", nullptr));
        label_55->setText(QCoreApplication::translate("ColorDifferenceForm", "H\343\201\256\350\250\261\345\256\271\345\267\256\347\225\260", nullptr));
        label_56->setText(QCoreApplication::translate("ColorDifferenceForm", "S\343\201\256\344\270\255\345\277\203\345\201\264\343\201\256\350\250\261\345\256\271\345\267\256\347\225\260", nullptr));
        label_57->setText(QCoreApplication::translate("ColorDifferenceForm", "S\343\201\256\345\244\226\345\201\264\343\201\256\350\250\261\345\256\271\345\267\256\347\225\260", nullptr));
        label_58->setText(QCoreApplication::translate("ColorDifferenceForm", "V\343\201\256\346\232\227\345\201\264\343\201\256\350\250\261\345\256\271\345\267\256\347\225\260", nullptr));
        label_59->setText(QCoreApplication::translate("ColorDifferenceForm", "V\343\201\256\346\230\216\345\201\264\343\201\256\350\250\261\345\256\271\345\267\256\347\225\260", nullptr));
        comboBoxJudgeMethod->setItemText(0, QCoreApplication::translate("ColorDifferenceForm", "OK/NG\343\202\222\344\275\277\343\201\206", nullptr));
        comboBoxJudgeMethod->setItemText(1, QCoreApplication::translate("ColorDifferenceForm", "DeltaE\343\201\247\345\210\244\345\256\232", nullptr));
        comboBoxJudgeMethod->setItemText(2, QCoreApplication::translate("ColorDifferenceForm", "\346\265\201\345\213\225\343\202\265\343\203\263\343\203\227\343\203\253\343\201\247HSV\345\210\244\345\256\232", nullptr));

        label_60->setText(QCoreApplication::translate("ColorDifferenceForm", "\345\210\244\345\256\232\346\226\271\346\263\225", nullptr));
        label_61->setText(QCoreApplication::translate("ColorDifferenceForm", "\351\240\230\345\237\237\345\220\215\347\247\260", nullptr));
        pushButtonSetItemName->setText(QCoreApplication::translate("ColorDifferenceForm", "\345\220\215\347\247\260\350\250\255\345\256\232", nullptr));
        checkBoxOutputConstantly->setText(QCoreApplication::translate("ColorDifferenceForm", "\345\270\270\343\201\253\347\265\220\346\236\234\345\207\272\345\212\233\357\274\210\343\203\210\343\203\254\343\203\263\343\203\211\347\256\241\347\220\206\357\274\211", nullptr));
        checkBoxAdaptAlignment->setText(QString());
        label_62->setText(QCoreApplication::translate("ColorDifferenceForm", "\344\275\215\347\275\256\345\220\210\343\202\217\343\201\233\343\201\247\347\247\273\345\213\225\343\201\231\343\202\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ColorDifferenceForm: public Ui_ColorDifferenceForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORDIFFERENCEFORM_H
