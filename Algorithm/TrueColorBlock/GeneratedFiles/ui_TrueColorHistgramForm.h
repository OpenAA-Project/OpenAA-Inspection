/********************************************************************************
** Form generated from reading UI file 'TrueColorHistgramForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRUECOLORHISTGRAMFORM_H
#define UI_TRUECOLORHISTGRAMFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrueColorHistgramFormClass
{
public:
    QTabWidget *tabWidgetInspect;
    QWidget *tab_5;
    QLabel *label_61;
    QSpinBox *EditNMergin;
    QLabel *label_48;
    QSpinBox *EditNOKDot;
    QLabel *label_38;
    QSpinBox *EditNMinNGCount;
    QSpinBox *EditNOKLength;
    QLabel *label_40;
    QWidget *tab_6;
    QSpinBox *EditBMergin;
    QLabel *label_53;
    QSpinBox *EditBOKDot;
    QLabel *label_54;
    QSpinBox *EditBMinNGCount;
    QLabel *label_39;
    QSpinBox *EditBOKLength;
    QLabel *label_41;
    QWidget *tab_7;
    QCheckBox *checkBModeEnabled;
    QCheckBox *checkBModeNGCluster;
    QCheckBox *checkBModeOnlyMatching;
    QCheckBox *checkBModeCenterBrightFromParts;
    QCheckBox *checkBModeInvertLogic;
    QWidget *tab_8;
    QLabel *label_26;
    QLabel *label_25;
    QSpinBox *EditAdjustWhite;
    QCheckBox *checkBModeAdjustable;
    QSpinBox *EditAdjustBlack;
    QWidget *tab_9;
    QLabel *label_27;
    QLabel *label_28;
    QCheckBox *checkBModeCommonMovable;
    QSpinBox *EditSelfSearch;
    QSpinBox *EditCommonMoveDot;
    QLabel *label_4;
    QLineEdit *EditLibID;
    QLabel *label_6;
    QLabel *label_5;
    QPushButton *ButtonClose;
    QFrame *frame;
    QLabel *label_31;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_30;
    QLabel *labelResultBDark;
    QLabel *labelResultNDark;
    QPushButton *ButtonCalc;
    QLineEdit *EditLibName;
    QPushButton *ButtonReflectAllBlocks;
    QStackedWidget *stackedWidgetParts;
    QWidget *page;
    QPushButton *ButtonRefrectOnlyBlock;
    QWidget *page_3;
    QPushButton *ButtonRelrectSaveParts;
    QWidget *page_2;
    QFrame *frameCurrentItem;
    QLabel *label_32;
    QFrame *frameColorSample;
    QPushButton *pushButtonEliminateColor;
    QPushButton *pushButtonAddColor;
    QFrame *frameCurrentPos;
    QPushButton *pushButtonSub;
    QPushButton *pushButtonAdd;
    QSpinBox *spinBoxMerginSub;
    QLabel *label_34;
    QSpinBox *spinBoxMerginAdd;
    QLabel *label_3;
    QLabel *label_35;
    QFrame *framePicked;
    QLabel *label_36;
    QPushButton *pushButtonSubPickupColor;
    QPushButton *pushButtonAddPickupColor;
    QSpinBox *spinBoxMerginAddPickupColor;
    QSpinBox *spinBoxMerginSubPickupColor;
    QLabel *label_37;
    QFrame *framePickupColor;
    QPushButton *ButtonLoadFromLibrary;
    QPushButton *ButtonSaveToLibrary;
    QPushButton *pushButtonChangeLib;
    QFrame *frameTarget;
    QFrame *frameThreshold;
    QLabel *label_33;
    QLabel *label_8;
    QListWidget *listWidgetBaseColor;
    QLabel *label_7;
    QListWidget *listWidgetEliminatedColor;
    QFrame *frameCurrentPos_2;
    QPushButton *pushButtonAdd_2;
    QLabel *label_42;
    QSpinBox *spinBoxMerginAdd_2;
    QLabel *label_9;
    QLabel *label_43;

    void setupUi(QWidget *TrueColorHistgramFormClass)
    {
        if (TrueColorHistgramFormClass->objectName().isEmpty())
            TrueColorHistgramFormClass->setObjectName("TrueColorHistgramFormClass");
        TrueColorHistgramFormClass->resize(824, 621);
        tabWidgetInspect = new QTabWidget(TrueColorHistgramFormClass);
        tabWidgetInspect->setObjectName("tabWidgetInspect");
        tabWidgetInspect->setGeometry(QRect(30, 420, 321, 111));
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        label_61 = new QLabel(tab_5);
        label_61->setObjectName("label_61");
        label_61->setGeometry(QRect(9, 10, 91, 21));
        label_61->setFrameShape(QFrame::Panel);
        label_61->setFrameShadow(QFrame::Sunken);
        label_61->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNMergin = new QSpinBox(tab_5);
        EditNMergin->setObjectName("EditNMergin");
        EditNMergin->setGeometry(QRect(40, 30, 61, 22));
        EditNMergin->setMaximum(99999999);
        label_48 = new QLabel(tab_5);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(110, 10, 91, 21));
        label_48->setFrameShape(QFrame::Panel);
        label_48->setFrameShadow(QFrame::Sunken);
        label_48->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNOKDot = new QSpinBox(tab_5);
        EditNOKDot->setObjectName("EditNOKDot");
        EditNOKDot->setGeometry(QRect(140, 30, 61, 22));
        EditNOKDot->setMaximum(99999999);
        label_38 = new QLabel(tab_5);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(210, 10, 81, 21));
        label_38->setFrameShape(QFrame::Panel);
        label_38->setFrameShadow(QFrame::Sunken);
        label_38->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNMinNGCount = new QSpinBox(tab_5);
        EditNMinNGCount->setObjectName("EditNMinNGCount");
        EditNMinNGCount->setGeometry(QRect(210, 30, 81, 22));
        EditNMinNGCount->setMaximum(99999999);
        EditNOKLength = new QSpinBox(tab_5);
        EditNOKLength->setObjectName("EditNOKLength");
        EditNOKLength->setGeometry(QRect(210, 60, 81, 22));
        EditNOKLength->setMaximum(99999999);
        label_40 = new QLabel(tab_5);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(80, 60, 121, 21));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setFrameShadow(QFrame::Sunken);
        label_40->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidgetInspect->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        EditBMergin = new QSpinBox(tab_6);
        EditBMergin->setObjectName("EditBMergin");
        EditBMergin->setGeometry(QRect(40, 30, 61, 22));
        EditBMergin->setMaximum(99999999);
        label_53 = new QLabel(tab_6);
        label_53->setObjectName("label_53");
        label_53->setGeometry(QRect(110, 10, 91, 21));
        label_53->setFrameShape(QFrame::Panel);
        label_53->setFrameShadow(QFrame::Sunken);
        label_53->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBOKDot = new QSpinBox(tab_6);
        EditBOKDot->setObjectName("EditBOKDot");
        EditBOKDot->setGeometry(QRect(140, 30, 61, 22));
        EditBOKDot->setMaximum(99999999);
        label_54 = new QLabel(tab_6);
        label_54->setObjectName("label_54");
        label_54->setGeometry(QRect(9, 10, 91, 21));
        label_54->setFrameShape(QFrame::Panel);
        label_54->setFrameShadow(QFrame::Sunken);
        label_54->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBMinNGCount = new QSpinBox(tab_6);
        EditBMinNGCount->setObjectName("EditBMinNGCount");
        EditBMinNGCount->setGeometry(QRect(210, 30, 81, 22));
        EditBMinNGCount->setMaximum(99999999);
        label_39 = new QLabel(tab_6);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(210, 10, 81, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBOKLength = new QSpinBox(tab_6);
        EditBOKLength->setObjectName("EditBOKLength");
        EditBOKLength->setGeometry(QRect(210, 60, 81, 22));
        EditBOKLength->setMaximum(99999999);
        label_41 = new QLabel(tab_6);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(80, 60, 121, 21));
        label_41->setFrameShape(QFrame::Panel);
        label_41->setFrameShadow(QFrame::Sunken);
        label_41->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidgetInspect->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        checkBModeEnabled = new QCheckBox(tab_7);
        checkBModeEnabled->setObjectName("checkBModeEnabled");
        checkBModeEnabled->setGeometry(QRect(10, 10, 141, 18));
        checkBModeNGCluster = new QCheckBox(tab_7);
        checkBModeNGCluster->setObjectName("checkBModeNGCluster");
        checkBModeNGCluster->setGeometry(QRect(10, 30, 141, 18));
        checkBModeOnlyMatching = new QCheckBox(tab_7);
        checkBModeOnlyMatching->setObjectName("checkBModeOnlyMatching");
        checkBModeOnlyMatching->setGeometry(QRect(160, 10, 141, 18));
        checkBModeCenterBrightFromParts = new QCheckBox(tab_7);
        checkBModeCenterBrightFromParts->setObjectName("checkBModeCenterBrightFromParts");
        checkBModeCenterBrightFromParts->setGeometry(QRect(160, 30, 141, 18));
        checkBModeInvertLogic = new QCheckBox(tab_7);
        checkBModeInvertLogic->setObjectName("checkBModeInvertLogic");
        checkBModeInvertLogic->setGeometry(QRect(160, 50, 141, 18));
        tabWidgetInspect->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        label_26 = new QLabel(tab_8);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(10, 60, 201, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_25 = new QLabel(tab_8);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(10, 30, 201, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditAdjustWhite = new QSpinBox(tab_8);
        EditAdjustWhite->setObjectName("EditAdjustWhite");
        EditAdjustWhite->setGeometry(QRect(220, 60, 81, 22));
        EditAdjustWhite->setMaximum(255);
        checkBModeAdjustable = new QCheckBox(tab_8);
        checkBModeAdjustable->setObjectName("checkBModeAdjustable");
        checkBModeAdjustable->setGeometry(QRect(30, 10, 241, 18));
        EditAdjustBlack = new QSpinBox(tab_8);
        EditAdjustBlack->setObjectName("EditAdjustBlack");
        EditAdjustBlack->setGeometry(QRect(220, 30, 81, 22));
        EditAdjustBlack->setMaximum(255);
        tabWidgetInspect->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName("tab_9");
        label_27 = new QLabel(tab_9);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(10, 30, 201, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_28 = new QLabel(tab_9);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(10, 60, 201, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBModeCommonMovable = new QCheckBox(tab_9);
        checkBModeCommonMovable->setObjectName("checkBModeCommonMovable");
        checkBModeCommonMovable->setGeometry(QRect(40, 10, 231, 18));
        EditSelfSearch = new QSpinBox(tab_9);
        EditSelfSearch->setObjectName("EditSelfSearch");
        EditSelfSearch->setGeometry(QRect(220, 30, 81, 22));
        EditCommonMoveDot = new QSpinBox(tab_9);
        EditCommonMoveDot->setObjectName("EditCommonMoveDot");
        EditCommonMoveDot->setGeometry(QRect(220, 60, 81, 22));
        tabWidgetInspect->addTab(tab_9, QString());
        label_4 = new QLabel(TrueColorHistgramFormClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 10, 61, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(TrueColorHistgramFormClass);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(70, 10, 61, 21));
        EditLibID->setReadOnly(true);
        label_6 = new QLabel(TrueColorHistgramFormClass);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 420, 20, 111));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Raised);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6->setIndent(1);
        label_5 = new QLabel(TrueColorHistgramFormClass);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(150, 10, 121, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonClose = new QPushButton(TrueColorHistgramFormClass);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(620, 530, 161, 31));
        frame = new QFrame(TrueColorHistgramFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(380, 420, 131, 151));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_31 = new QLabel(frame);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(0, 0, 131, 21));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 60, 61, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 90, 61, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_30 = new QLabel(frame);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(20, 30, 101, 21));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelResultBDark = new QLabel(frame);
        labelResultBDark->setObjectName("labelResultBDark");
        labelResultBDark->setGeometry(QRect(70, 90, 51, 21));
        labelResultBDark->setFrameShape(QFrame::Panel);
        labelResultBDark->setFrameShadow(QFrame::Sunken);
        labelResultBDark->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelResultNDark = new QLabel(frame);
        labelResultNDark->setObjectName("labelResultNDark");
        labelResultNDark->setGeometry(QRect(70, 60, 51, 21));
        labelResultNDark->setFrameShape(QFrame::Panel);
        labelResultNDark->setFrameShadow(QFrame::Sunken);
        labelResultNDark->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonCalc = new QPushButton(frame);
        ButtonCalc->setObjectName("ButtonCalc");
        ButtonCalc->setGeometry(QRect(10, 120, 111, 31));
        EditLibName = new QLineEdit(TrueColorHistgramFormClass);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(270, 10, 141, 21));
        EditLibName->setReadOnly(true);
        ButtonReflectAllBlocks = new QPushButton(TrueColorHistgramFormClass);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(190, 540, 171, 31));
        stackedWidgetParts = new QStackedWidget(TrueColorHistgramFormClass);
        stackedWidgetParts->setObjectName("stackedWidgetParts");
        stackedWidgetParts->setGeometry(QRect(10, 540, 181, 31));
        page = new QWidget();
        page->setObjectName("page");
        ButtonRefrectOnlyBlock = new QPushButton(page);
        ButtonRefrectOnlyBlock->setObjectName("ButtonRefrectOnlyBlock");
        ButtonRefrectOnlyBlock->setGeometry(QRect(0, 0, 171, 31));
        stackedWidgetParts->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        ButtonRelrectSaveParts = new QPushButton(page_3);
        ButtonRelrectSaveParts->setObjectName("ButtonRelrectSaveParts");
        ButtonRelrectSaveParts->setGeometry(QRect(0, 0, 171, 31));
        stackedWidgetParts->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidgetParts->addWidget(page_2);
        frameCurrentItem = new QFrame(TrueColorHistgramFormClass);
        frameCurrentItem->setObjectName("frameCurrentItem");
        frameCurrentItem->setGeometry(QRect(10, 60, 251, 181));
        frameCurrentItem->setFrameShape(QFrame::StyledPanel);
        frameCurrentItem->setFrameShadow(QFrame::Sunken);
        label_32 = new QLabel(TrueColorHistgramFormClass);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(10, 40, 251, 21));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameColorSample = new QFrame(TrueColorHistgramFormClass);
        frameColorSample->setObjectName("frameColorSample");
        frameColorSample->setGeometry(QRect(600, 10, 205, 511));
        frameColorSample->setFrameShape(QFrame::StyledPanel);
        frameColorSample->setFrameShadow(QFrame::Sunken);
        pushButtonEliminateColor = new QPushButton(frameColorSample);
        pushButtonEliminateColor->setObjectName("pushButtonEliminateColor");
        pushButtonEliminateColor->setGeometry(QRect(20, 480, 161, 25));
        pushButtonAddColor = new QPushButton(frameColorSample);
        pushButtonAddColor->setObjectName("pushButtonAddColor");
        pushButtonAddColor->setGeometry(QRect(20, 450, 161, 25));
        frameCurrentPos = new QFrame(TrueColorHistgramFormClass);
        frameCurrentPos->setObjectName("frameCurrentPos");
        frameCurrentPos->setGeometry(QRect(10, 250, 381, 91));
        frameCurrentPos->setFrameShape(QFrame::StyledPanel);
        frameCurrentPos->setFrameShadow(QFrame::Sunken);
        pushButtonSub = new QPushButton(frameCurrentPos);
        pushButtonSub->setObjectName("pushButtonSub");
        pushButtonSub->setGeometry(QRect(80, 60, 75, 23));
        pushButtonAdd = new QPushButton(frameCurrentPos);
        pushButtonAdd->setObjectName("pushButtonAdd");
        pushButtonAdd->setGeometry(QRect(80, 30, 75, 23));
        spinBoxMerginSub = new QSpinBox(frameCurrentPos);
        spinBoxMerginSub->setObjectName("spinBoxMerginSub");
        spinBoxMerginSub->setGeometry(QRect(160, 60, 61, 22));
        label_34 = new QLabel(frameCurrentPos);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(160, 10, 64, 21));
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Sunken);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxMerginAdd = new QSpinBox(frameCurrentPos);
        spinBoxMerginAdd->setObjectName("spinBoxMerginAdd");
        spinBoxMerginAdd->setGeometry(QRect(160, 30, 61, 22));
        label_3 = new QLabel(frameCurrentPos);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(230, 30, 141, 52));
        label_35 = new QLabel(frameCurrentPos);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(0, 0, 71, 91));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Sunken);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_35->setWordWrap(true);
        framePicked = new QFrame(TrueColorHistgramFormClass);
        framePicked->setObjectName("framePicked");
        framePicked->setGeometry(QRect(400, 250, 191, 111));
        framePicked->setFrameShape(QFrame::StyledPanel);
        framePicked->setFrameShadow(QFrame::Sunken);
        label_36 = new QLabel(framePicked);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(0, 0, 191, 21));
        label_36->setFrameShape(QFrame::Panel);
        label_36->setFrameShadow(QFrame::Sunken);
        label_36->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSubPickupColor = new QPushButton(framePicked);
        pushButtonSubPickupColor->setObjectName("pushButtonSubPickupColor");
        pushButtonSubPickupColor->setGeometry(QRect(40, 80, 75, 23));
        pushButtonAddPickupColor = new QPushButton(framePicked);
        pushButtonAddPickupColor->setObjectName("pushButtonAddPickupColor");
        pushButtonAddPickupColor->setGeometry(QRect(40, 50, 75, 23));
        spinBoxMerginAddPickupColor = new QSpinBox(framePicked);
        spinBoxMerginAddPickupColor->setObjectName("spinBoxMerginAddPickupColor");
        spinBoxMerginAddPickupColor->setGeometry(QRect(120, 50, 61, 22));
        spinBoxMerginAddPickupColor->setValue(10);
        spinBoxMerginSubPickupColor = new QSpinBox(framePicked);
        spinBoxMerginSubPickupColor->setObjectName("spinBoxMerginSubPickupColor");
        spinBoxMerginSubPickupColor->setGeometry(QRect(120, 80, 61, 22));
        spinBoxMerginSubPickupColor->setValue(10);
        label_37 = new QLabel(framePicked);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(120, 30, 64, 21));
        label_37->setFrameShape(QFrame::Panel);
        label_37->setFrameShadow(QFrame::Sunken);
        label_37->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        framePickupColor = new QFrame(framePicked);
        framePickupColor->setObjectName("framePickupColor");
        framePickupColor->setGeometry(QRect(10, 30, 21, 71));
        framePickupColor->setFrameShape(QFrame::NoFrame);
        framePickupColor->setFrameShadow(QFrame::Plain);
        ButtonLoadFromLibrary = new QPushButton(TrueColorHistgramFormClass);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(190, 580, 171, 31));
        ButtonSaveToLibrary = new QPushButton(TrueColorHistgramFormClass);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(10, 580, 171, 31));
        pushButtonChangeLib = new QPushButton(TrueColorHistgramFormClass);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(420, 10, 75, 23));
        frameTarget = new QFrame(TrueColorHistgramFormClass);
        frameTarget->setObjectName("frameTarget");
        frameTarget->setGeometry(QRect(270, 40, 331, 211));
        frameTarget->setFrameShape(QFrame::NoFrame);
        frameTarget->setFrameShadow(QFrame::Plain);
        frameThreshold = new QFrame(frameTarget);
        frameThreshold->setObjectName("frameThreshold");
        frameThreshold->setGeometry(QRect(0, 20, 251, 181));
        frameThreshold->setFrameShape(QFrame::StyledPanel);
        frameThreshold->setFrameShadow(QFrame::Sunken);
        label_33 = new QLabel(frameTarget);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(0, 0, 251, 21));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Sunken);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_8 = new QLabel(frameTarget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(260, 120, 61, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetBaseColor = new QListWidget(frameTarget);
        listWidgetBaseColor->setObjectName("listWidgetBaseColor");
        listWidgetBaseColor->setGeometry(QRect(260, 20, 61, 61));
        label_7 = new QLabel(frameTarget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(260, 0, 61, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetEliminatedColor = new QListWidget(frameTarget);
        listWidgetEliminatedColor->setObjectName("listWidgetEliminatedColor");
        listWidgetEliminatedColor->setGeometry(QRect(260, 140, 61, 61));
        frameCurrentPos_2 = new QFrame(TrueColorHistgramFormClass);
        frameCurrentPos_2->setObjectName("frameCurrentPos_2");
        frameCurrentPos_2->setGeometry(QRect(10, 350, 381, 61));
        frameCurrentPos_2->setFrameShape(QFrame::StyledPanel);
        frameCurrentPos_2->setFrameShadow(QFrame::Sunken);
        pushButtonAdd_2 = new QPushButton(frameCurrentPos_2);
        pushButtonAdd_2->setObjectName("pushButtonAdd_2");
        pushButtonAdd_2->setGeometry(QRect(80, 10, 75, 41));
        label_42 = new QLabel(frameCurrentPos_2);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(160, 10, 64, 21));
        label_42->setFrameShape(QFrame::Panel);
        label_42->setFrameShadow(QFrame::Sunken);
        label_42->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxMerginAdd_2 = new QSpinBox(frameCurrentPos_2);
        spinBoxMerginAdd_2->setObjectName("spinBoxMerginAdd_2");
        spinBoxMerginAdd_2->setGeometry(QRect(160, 30, 61, 22));
        label_9 = new QLabel(frameCurrentPos_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(250, 20, 101, 41));
        label_9->setWordWrap(true);
        label_43 = new QLabel(frameCurrentPos_2);
        label_43->setObjectName("label_43");
        label_43->setGeometry(QRect(0, 0, 71, 61));
        label_43->setFrameShape(QFrame::Panel);
        label_43->setFrameShadow(QFrame::Sunken);
        label_43->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_43->setWordWrap(true);

        retranslateUi(TrueColorHistgramFormClass);

        tabWidgetInspect->setCurrentIndex(0);
        stackedWidgetParts->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TrueColorHistgramFormClass);
    } // setupUi

    void retranslateUi(QWidget *TrueColorHistgramFormClass)
    {
        TrueColorHistgramFormClass->setWindowTitle(QCoreApplication::translate("TrueColorHistgramFormClass", "Color Map", nullptr));
        label_61->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\350\274\235\345\272\246\343\203\236\343\203\274\343\202\270\343\203\263", nullptr));
        label_48->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_38->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "NG\345\241\212\345\200\213\346\225\260", nullptr));
        label_40->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\343\201\223\343\202\214\344\273\245\344\270\212\343\201\256\351\225\267\343\201\225\343\201\247\357\274\256\357\274\247", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_5), QCoreApplication::translate("TrueColorHistgramFormClass", "\347\213\255\345\237\237", nullptr));
        label_53->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_54->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\350\274\235\345\272\246\343\203\236\343\203\274\343\202\270\343\203\263", nullptr));
        label_39->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "NG\345\241\212\345\200\213\346\225\260", nullptr));
        label_41->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\343\201\223\343\202\214\344\273\245\344\270\212\343\201\256\351\225\267\343\201\225\343\201\247\357\274\256\357\274\247", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_6), QCoreApplication::translate("TrueColorHistgramFormClass", "\345\272\203\345\237\237", nullptr));
        checkBModeEnabled->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\346\244\234\346\237\273\346\234\211\345\212\271", nullptr));
        checkBModeNGCluster->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\345\241\212\346\244\234\346\237\273", nullptr));
        checkBModeOnlyMatching->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\347\265\220\346\236\234\345\207\272\345\212\233\343\201\227\343\201\252\343\201\204", nullptr));
        checkBModeCenterBrightFromParts->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\351\203\250\345\223\201\343\201\213\343\202\211\350\274\235\345\272\246\343\202\222\346\212\275\345\207\272\343\201\231\343\202\213", nullptr));
        checkBModeInvertLogic->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\350\253\226\347\220\206\345\217\215\350\273\242", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_7), QCoreApplication::translate("TrueColorHistgramFormClass", "\345\261\236\346\200\247", nullptr));
        label_26->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_25->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        checkBModeAdjustable->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\344\270\255\345\277\203\350\274\235\345\272\246\350\243\234\346\255\243\343\202\222\346\234\211\345\212\271\343\201\253\343\201\231\343\202\213", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_8), QCoreApplication::translate("TrueColorHistgramFormClass", "\350\243\234\346\255\243", nullptr));
        label_27->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\343\203\226\343\203\255\343\203\203\343\202\257\345\215\230\344\275\223\343\201\247\343\201\256\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_28->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\345\205\250\344\275\223\343\201\247\343\201\256\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        checkBModeCommonMovable->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\345\205\250\344\275\223\343\201\247\343\201\256\346\216\242\347\264\242\343\202\222\346\234\211\345\212\271\343\201\253\343\201\231\343\202\213", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_9), QCoreApplication::translate("TrueColorHistgramFormClass", "\346\216\242\347\264\242", nullptr));
        label_4->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        EditLibID->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "12345", nullptr));
        label_6->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\346\244\234\n"
"\346\237\273", nullptr));
        label_5->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        ButtonClose->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_31->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\345\210\244\345\256\232\347\265\220\346\236\234", nullptr));
        label->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\347\213\255\345\237\237\345\210\244\345\256\232", nullptr));
        label_2->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\345\272\203\345\237\237\345\210\244\345\256\232", nullptr));
        label_30->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\347\257\204\345\233\262\345\244\226\343\203\211\343\203\203\343\203\210", nullptr));
        labelResultBDark->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "123", nullptr));
        labelResultNDark->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "123", nullptr));
        ButtonCalc->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\350\250\210\347\256\227", nullptr));
        EditLibName->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "XXX", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonRefrectOnlyBlock->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\343\201\223\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonRelrectSaveParts->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\351\203\250\345\223\201\344\277\235\345\255\230", nullptr));
        label_32->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\343\202\253\343\203\251\343\203\274\343\203\236\343\203\203\343\203\227", nullptr));
        pushButtonEliminateColor->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "Eliminate color", nullptr));
        pushButtonAddColor->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "Add Color", nullptr));
        pushButtonSub->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "Sub =>", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "Add =>", nullptr));
        label_34->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\343\203\236\343\203\274\343\202\270\343\203\263\350\274\235\345\272\246", nullptr));
        label_3->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "Add : \343\201\223\343\201\256\343\203\236\343\203\274\343\202\270\343\203\263\345\210\206\343\201\240\343\201\221\350\274\235\345\272\246\343\202\222\n"
"        \346\213\241\345\274\265\343\201\227\343\201\246\350\277\275\345\212\240\n"
"Sub : \343\201\223\343\201\256\343\203\236\343\203\274\343\202\270\343\203\263\345\210\206\343\201\240\343\201\221\350\274\235\345\272\246\343\202\222\n"
"        \346\213\241\345\274\265\343\201\227\343\201\246\351\231\244\345\244\226\350\274\235\345\272\246\343\201\253\350\277\275\345\212\240", nullptr));
        label_35->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\350\211\262\343\201\256\350\277\275\345\212\240\343\203\273\351\231\244\345\244\226", nullptr));
        label_36->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\343\203\224\343\203\203\343\202\257\343\202\242\343\203\203\343\203\227\350\211\262\343\201\256\350\277\275\345\212\240\343\203\273\351\231\244\345\244\226", nullptr));
        pushButtonSubPickupColor->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "Sub =>", nullptr));
        pushButtonAddPickupColor->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "Add =>", nullptr));
        label_37->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\343\203\236\343\203\274\343\202\270\343\203\263\350\274\235\345\272\246", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "...", nullptr));
        label_33->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\346\244\234\346\237\273\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        label_8->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\351\231\244\345\244\226\350\211\262", nullptr));
        label_7->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\350\277\275\345\212\240\350\211\262", nullptr));
        pushButtonAdd_2->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\350\211\262\350\277\275\345\212\240", nullptr));
        label_42->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "\343\203\236\343\203\274\343\202\270\343\203\263\350\274\235\345\272\246", nullptr));
        label_9->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS UI Gothic'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">\343\201\223\343\201\256\343\203\236\343\203\274\343\202\270\343\203\263\345\210\206\343\201\240\343\201\221\350\274\235\345\272\246\343\202\222\346\213\241\345\274\265\343\201\227\343\201\246\350\277\275\345\212\240</p></body></html>", nullptr));
        label_43->setText(QCoreApplication::translate("TrueColorHistgramFormClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS UI Gothic'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">\344\275\234\346\210\220\343\201\227\343\201\237\343\203\226\343\203\255\343\203\203</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">\343\202\257\347\256\207\346\211\200\343\201\256\343\203\236\343\202\271\343\202\277</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">\343\203\274\347\224\273\345\203\217\343\201\256OK\350\211\262</p>\n"
"<p style=\" margin-to"
                        "p:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">\350\277\275\345\212\240</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrueColorHistgramFormClass: public Ui_TrueColorHistgramFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRUECOLORHISTGRAMFORM_H
