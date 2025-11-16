/********************************************************************************
** Form generated from reading UI file 'InfoDynamicClassifyForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFODYNAMICCLASSIFYFORM_H
#define UI_INFODYNAMICCLASSIFYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InfoDynamicClassifyFormClass
{
public:
    QSpinBox *EditNoiseDot;
    QLabel *label_59;
    QLabel *label_60;
    QSpinBox *EditShrinkDot;
    QLabel *label_61;
    QSpinBox *EditPriority;
    QLabel *label_62;
    QSpinBox *EditVariableWidth;
    QLabel *label_63;
    QSpinBox *EditOutlineTWidth;
    QLabel *label_64;
    QSpinBox *EditOverlapInEachArea;
    QSpinBox *EditOutlineIWidth;
    QLabel *label_65;
    QLabel *label_66;
    QSpinBox *EditOutlineOWidth;
    QLabel *label_7;
    QListWidget *listWidgetBaseColor;
    QLabel *label_8;
    QFrame *frameThreshold;
    QListWidget *listWidgetEliminatedColor;
    QPushButton *pushButtonChangeLib;
    QLineEdit *EditLibName;
    QLabel *label_4;
    QLineEdit *EditLibID;
    QLabel *label_5;
    QTabWidget *tabWidget;
    QWidget *tab_7;
    QFrame *frameColorSample;
    QPushButton *pushButtonEliminateColor;
    QPushButton *pushButtonAddColor;
    QWidget *tab_8;
    QFrame *framePicked_3;
    QLabel *label_44;
    QPushButton *pushButtonSubPickupColor;
    QPushButton *pushButtonAddPickupColor;
    QSpinBox *spinBoxMerginAddPickupColor;
    QSpinBox *spinBoxMerginSubPickupColor;
    QLabel *label_45;
    QFrame *framePickupColor;
    QWidget *tab_9;
    QFrame *frameShowColorSmples;
    QPushButton *pushButtonAddColorArea;
    QPushButton *pushButtonEliminateColorArea;
    QPushButton *ButtonLoadFromLibrary;
    QPushButton *ButtonSaveToLibrary;
    QPushButton *ButtonReflectAllBlocks;
    QStackedWidget *stackedWidgetParts;
    QWidget *page;
    QPushButton *ButtonRelrectOnlyBlock;
    QWidget *page_3;
    QPushButton *ButtonRelrectSaveParts;
    QWidget *page_2;
    QPushButton *ButtonClose;
    QFrame *frame_25;
    QLabel *label_86;
    QSpinBox *EditAdjustBlack;
    QSpinBox *EditAdjustWhite;
    QLabel *label_88;
    QLabel *label_89;
    QFrame *frame;
    QToolButton *toolButtonCoreArea;
    QToolButton *toolButtonMaxZone;
    QToolButton *toolButtonOutlineIArea;
    QToolButton *toolButtonOutlineTArea;
    QToolButton *toolButtonOutlineOArea;
    QPushButton *pushButtonReCalc;
    QToolButton *toolButtonBareArea;
    QToolButton *toolButtonInside;

    void setupUi(QWidget *InfoDynamicClassifyFormClass)
    {
        if (InfoDynamicClassifyFormClass->objectName().isEmpty())
            InfoDynamicClassifyFormClass->setObjectName("InfoDynamicClassifyFormClass");
        InfoDynamicClassifyFormClass->resize(834, 629);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InfoDynamicClassifyFormClass->sizePolicy().hasHeightForWidth());
        InfoDynamicClassifyFormClass->setSizePolicy(sizePolicy);
        EditNoiseDot = new QSpinBox(InfoDynamicClassifyFormClass);
        EditNoiseDot->setObjectName("EditNoiseDot");
        EditNoiseDot->setGeometry(QRect(120, 60, 61, 22));
        EditNoiseDot->setMaximum(1000000);
        label_59 = new QLabel(InfoDynamicClassifyFormClass);
        label_59->setObjectName("label_59");
        label_59->setGeometry(QRect(10, 60, 111, 21));
        label_59->setFrameShape(QFrame::Panel);
        label_59->setFrameShadow(QFrame::Sunken);
        label_59->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_60 = new QLabel(InfoDynamicClassifyFormClass);
        label_60->setObjectName("label_60");
        label_60->setGeometry(QRect(10, 90, 111, 21));
        label_60->setFrameShape(QFrame::Panel);
        label_60->setFrameShadow(QFrame::Sunken);
        label_60->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditShrinkDot = new QSpinBox(InfoDynamicClassifyFormClass);
        EditShrinkDot->setObjectName("EditShrinkDot");
        EditShrinkDot->setGeometry(QRect(120, 90, 61, 22));
        EditShrinkDot->setMaximum(1000000);
        label_61 = new QLabel(InfoDynamicClassifyFormClass);
        label_61->setObjectName("label_61");
        label_61->setGeometry(QRect(10, 120, 111, 21));
        label_61->setFrameShape(QFrame::Panel);
        label_61->setFrameShadow(QFrame::Sunken);
        label_61->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPriority = new QSpinBox(InfoDynamicClassifyFormClass);
        EditPriority->setObjectName("EditPriority");
        EditPriority->setGeometry(QRect(120, 120, 61, 22));
        EditPriority->setMaximum(1000000);
        label_62 = new QLabel(InfoDynamicClassifyFormClass);
        label_62->setObjectName("label_62");
        label_62->setGeometry(QRect(10, 150, 111, 21));
        label_62->setFrameShape(QFrame::Panel);
        label_62->setFrameShadow(QFrame::Sunken);
        label_62->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditVariableWidth = new QSpinBox(InfoDynamicClassifyFormClass);
        EditVariableWidth->setObjectName("EditVariableWidth");
        EditVariableWidth->setGeometry(QRect(120, 150, 61, 22));
        EditVariableWidth->setMaximum(1000000);
        label_63 = new QLabel(InfoDynamicClassifyFormClass);
        label_63->setObjectName("label_63");
        label_63->setGeometry(QRect(190, 150, 111, 21));
        label_63->setFrameShape(QFrame::Panel);
        label_63->setFrameShadow(QFrame::Sunken);
        label_63->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOutlineTWidth = new QSpinBox(InfoDynamicClassifyFormClass);
        EditOutlineTWidth->setObjectName("EditOutlineTWidth");
        EditOutlineTWidth->setGeometry(QRect(300, 90, 61, 22));
        EditOutlineTWidth->setMaximum(1000000);
        label_64 = new QLabel(InfoDynamicClassifyFormClass);
        label_64->setObjectName("label_64");
        label_64->setGeometry(QRect(190, 60, 111, 21));
        label_64->setFrameShape(QFrame::Panel);
        label_64->setFrameShadow(QFrame::Sunken);
        label_64->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOverlapInEachArea = new QSpinBox(InfoDynamicClassifyFormClass);
        EditOverlapInEachArea->setObjectName("EditOverlapInEachArea");
        EditOverlapInEachArea->setGeometry(QRect(300, 150, 61, 22));
        EditOverlapInEachArea->setMaximum(1000000);
        EditOutlineIWidth = new QSpinBox(InfoDynamicClassifyFormClass);
        EditOutlineIWidth->setObjectName("EditOutlineIWidth");
        EditOutlineIWidth->setGeometry(QRect(300, 60, 61, 22));
        EditOutlineIWidth->setMaximum(1000000);
        label_65 = new QLabel(InfoDynamicClassifyFormClass);
        label_65->setObjectName("label_65");
        label_65->setGeometry(QRect(190, 90, 111, 21));
        label_65->setFrameShape(QFrame::Panel);
        label_65->setFrameShadow(QFrame::Sunken);
        label_65->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_66 = new QLabel(InfoDynamicClassifyFormClass);
        label_66->setObjectName("label_66");
        label_66->setGeometry(QRect(190, 120, 111, 21));
        label_66->setFrameShape(QFrame::Panel);
        label_66->setFrameShadow(QFrame::Sunken);
        label_66->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOutlineOWidth = new QSpinBox(InfoDynamicClassifyFormClass);
        EditOutlineOWidth->setObjectName("EditOutlineOWidth");
        EditOutlineOWidth->setGeometry(QRect(300, 120, 61, 22));
        EditOutlineOWidth->setMaximum(1000000);
        label_7 = new QLabel(InfoDynamicClassifyFormClass);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(300, 250, 61, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetBaseColor = new QListWidget(InfoDynamicClassifyFormClass);
        listWidgetBaseColor->setObjectName("listWidgetBaseColor");
        listWidgetBaseColor->setGeometry(QRect(300, 270, 61, 61));
        label_8 = new QLabel(InfoDynamicClassifyFormClass);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(300, 410, 61, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameThreshold = new QFrame(InfoDynamicClassifyFormClass);
        frameThreshold->setObjectName("frameThreshold");
        frameThreshold->setGeometry(QRect(20, 250, 271, 251));
        frameThreshold->setFrameShape(QFrame::StyledPanel);
        frameThreshold->setFrameShadow(QFrame::Raised);
        listWidgetEliminatedColor = new QListWidget(InfoDynamicClassifyFormClass);
        listWidgetEliminatedColor->setObjectName("listWidgetEliminatedColor");
        listWidgetEliminatedColor->setGeometry(QRect(300, 430, 61, 61));
        pushButtonChangeLib = new QPushButton(InfoDynamicClassifyFormClass);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(230, 30, 31, 23));
        EditLibName = new QLineEdit(InfoDynamicClassifyFormClass);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(70, 30, 161, 21));
        EditLibName->setReadOnly(true);
        label_4 = new QLabel(InfoDynamicClassifyFormClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 10, 62, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(InfoDynamicClassifyFormClass);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(10, 30, 61, 21));
        EditLibID->setReadOnly(true);
        label_5 = new QLabel(InfoDynamicClassifyFormClass);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(70, 10, 161, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidget = new QTabWidget(InfoDynamicClassifyFormClass);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(380, 10, 441, 551));
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        frameColorSample = new QFrame(tab_7);
        frameColorSample->setObjectName("frameColorSample");
        frameColorSample->setGeometry(QRect(10, 10, 205, 511));
        frameColorSample->setFrameShape(QFrame::StyledPanel);
        frameColorSample->setFrameShadow(QFrame::Sunken);
        pushButtonEliminateColor = new QPushButton(frameColorSample);
        pushButtonEliminateColor->setObjectName("pushButtonEliminateColor");
        pushButtonEliminateColor->setGeometry(QRect(20, 480, 161, 25));
        pushButtonAddColor = new QPushButton(frameColorSample);
        pushButtonAddColor->setObjectName("pushButtonAddColor");
        pushButtonAddColor->setGeometry(QRect(20, 450, 161, 25));
        tabWidget->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        framePicked_3 = new QFrame(tab_8);
        framePicked_3->setObjectName("framePicked_3");
        framePicked_3->setGeometry(QRect(10, 10, 191, 111));
        framePicked_3->setFrameShape(QFrame::StyledPanel);
        framePicked_3->setFrameShadow(QFrame::Sunken);
        label_44 = new QLabel(framePicked_3);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(0, 0, 191, 21));
        label_44->setFrameShape(QFrame::Panel);
        label_44->setFrameShadow(QFrame::Sunken);
        label_44->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSubPickupColor = new QPushButton(framePicked_3);
        pushButtonSubPickupColor->setObjectName("pushButtonSubPickupColor");
        pushButtonSubPickupColor->setGeometry(QRect(40, 80, 75, 23));
        pushButtonAddPickupColor = new QPushButton(framePicked_3);
        pushButtonAddPickupColor->setObjectName("pushButtonAddPickupColor");
        pushButtonAddPickupColor->setGeometry(QRect(40, 50, 75, 23));
        spinBoxMerginAddPickupColor = new QSpinBox(framePicked_3);
        spinBoxMerginAddPickupColor->setObjectName("spinBoxMerginAddPickupColor");
        spinBoxMerginAddPickupColor->setGeometry(QRect(120, 50, 61, 22));
        spinBoxMerginAddPickupColor->setValue(10);
        spinBoxMerginSubPickupColor = new QSpinBox(framePicked_3);
        spinBoxMerginSubPickupColor->setObjectName("spinBoxMerginSubPickupColor");
        spinBoxMerginSubPickupColor->setGeometry(QRect(120, 80, 61, 22));
        spinBoxMerginSubPickupColor->setValue(10);
        label_45 = new QLabel(framePicked_3);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(120, 30, 64, 21));
        label_45->setFrameShape(QFrame::Panel);
        label_45->setFrameShadow(QFrame::Sunken);
        label_45->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        framePickupColor = new QFrame(framePicked_3);
        framePickupColor->setObjectName("framePickupColor");
        framePickupColor->setGeometry(QRect(10, 30, 21, 71));
        framePickupColor->setFrameShape(QFrame::NoFrame);
        framePickupColor->setFrameShadow(QFrame::Plain);
        tabWidget->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName("tab_9");
        frameShowColorSmples = new QFrame(tab_9);
        frameShowColorSmples->setObjectName("frameShowColorSmples");
        frameShowColorSmples->setGeometry(QRect(10, 10, 415, 355));
        frameShowColorSmples->setFrameShape(QFrame::NoFrame);
        frameShowColorSmples->setFrameShadow(QFrame::Plain);
        pushButtonAddColorArea = new QPushButton(tab_9);
        pushButtonAddColorArea->setObjectName("pushButtonAddColorArea");
        pushButtonAddColorArea->setGeometry(QRect(60, 370, 161, 25));
        pushButtonEliminateColorArea = new QPushButton(tab_9);
        pushButtonEliminateColorArea->setObjectName("pushButtonEliminateColorArea");
        pushButtonEliminateColorArea->setGeometry(QRect(60, 400, 161, 25));
        tabWidget->addTab(tab_9, QString());
        ButtonLoadFromLibrary = new QPushButton(InfoDynamicClassifyFormClass);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(200, 550, 171, 31));
        ButtonSaveToLibrary = new QPushButton(InfoDynamicClassifyFormClass);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(20, 550, 171, 31));
        ButtonReflectAllBlocks = new QPushButton(InfoDynamicClassifyFormClass);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(200, 510, 171, 31));
        stackedWidgetParts = new QStackedWidget(InfoDynamicClassifyFormClass);
        stackedWidgetParts->setObjectName("stackedWidgetParts");
        stackedWidgetParts->setGeometry(QRect(20, 510, 181, 31));
        page = new QWidget();
        page->setObjectName("page");
        ButtonRelrectOnlyBlock = new QPushButton(page);
        ButtonRelrectOnlyBlock->setObjectName("ButtonRelrectOnlyBlock");
        ButtonRelrectOnlyBlock->setGeometry(QRect(0, 0, 171, 31));
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
        ButtonClose = new QPushButton(InfoDynamicClassifyFormClass);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(200, 590, 171, 31));
        frame_25 = new QFrame(InfoDynamicClassifyFormClass);
        frame_25->setObjectName("frame_25");
        frame_25->setGeometry(QRect(10, 180, 291, 61));
        frame_25->setFrameShape(QFrame::StyledPanel);
        frame_25->setFrameShadow(QFrame::Sunken);
        label_86 = new QLabel(frame_25);
        label_86->setObjectName("label_86");
        label_86->setGeometry(QRect(0, 0, 31, 61));
        label_86->setFrameShape(QFrame::Panel);
        label_86->setFrameShadow(QFrame::Raised);
        label_86->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_86->setIndent(1);
        EditAdjustBlack = new QSpinBox(frame_25);
        EditAdjustBlack->setObjectName("EditAdjustBlack");
        EditAdjustBlack->setGeometry(QRect(220, 10, 61, 22));
        EditAdjustBlack->setMaximum(255);
        EditAdjustWhite = new QSpinBox(frame_25);
        EditAdjustWhite->setObjectName("EditAdjustWhite");
        EditAdjustWhite->setGeometry(QRect(220, 30, 61, 22));
        EditAdjustWhite->setMaximum(255);
        label_88 = new QLabel(frame_25);
        label_88->setObjectName("label_88");
        label_88->setGeometry(QRect(40, 30, 181, 21));
        label_88->setFrameShape(QFrame::Panel);
        label_88->setFrameShadow(QFrame::Sunken);
        label_88->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_89 = new QLabel(frame_25);
        label_89->setObjectName("label_89");
        label_89->setGeometry(QRect(40, 10, 181, 21));
        label_89->setFrameShape(QFrame::Panel);
        label_89->setFrameShadow(QFrame::Sunken);
        label_89->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame = new QFrame(InfoDynamicClassifyFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 640, 181, 131));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        toolButtonCoreArea = new QToolButton(frame);
        toolButtonCoreArea->setObjectName("toolButtonCoreArea");
        toolButtonCoreArea->setGeometry(QRect(100, 10, 71, 19));
        toolButtonCoreArea->setCheckable(true);
        toolButtonCoreArea->setChecked(true);
        toolButtonMaxZone = new QToolButton(frame);
        toolButtonMaxZone->setObjectName("toolButtonMaxZone");
        toolButtonMaxZone->setGeometry(QRect(100, 30, 71, 19));
        toolButtonMaxZone->setCheckable(true);
        toolButtonOutlineIArea = new QToolButton(frame);
        toolButtonOutlineIArea->setObjectName("toolButtonOutlineIArea");
        toolButtonOutlineIArea->setGeometry(QRect(10, 50, 71, 19));
        toolButtonOutlineIArea->setCheckable(true);
        toolButtonOutlineTArea = new QToolButton(frame);
        toolButtonOutlineTArea->setObjectName("toolButtonOutlineTArea");
        toolButtonOutlineTArea->setGeometry(QRect(10, 70, 71, 19));
        toolButtonOutlineTArea->setCheckable(true);
        toolButtonOutlineTArea->setChecked(false);
        toolButtonOutlineOArea = new QToolButton(frame);
        toolButtonOutlineOArea->setObjectName("toolButtonOutlineOArea");
        toolButtonOutlineOArea->setGeometry(QRect(10, 90, 71, 19));
        toolButtonOutlineOArea->setCheckable(true);
        pushButtonReCalc = new QPushButton(frame);
        pushButtonReCalc->setObjectName("pushButtonReCalc");
        pushButtonReCalc->setGeometry(QRect(90, 60, 81, 51));
        toolButtonBareArea = new QToolButton(frame);
        toolButtonBareArea->setObjectName("toolButtonBareArea");
        toolButtonBareArea->setGeometry(QRect(10, 10, 71, 19));
        toolButtonBareArea->setCheckable(true);
        toolButtonBareArea->setChecked(true);
        toolButtonInside = new QToolButton(frame);
        toolButtonInside->setObjectName("toolButtonInside");
        toolButtonInside->setGeometry(QRect(10, 30, 71, 19));
        toolButtonInside->setCheckable(true);

        retranslateUi(InfoDynamicClassifyFormClass);

        tabWidget->setCurrentIndex(1);
        stackedWidgetParts->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(InfoDynamicClassifyFormClass);
    } // setupUi

    void retranslateUi(QWidget *InfoDynamicClassifyFormClass)
    {
        InfoDynamicClassifyFormClass->setWindowTitle(QCoreApplication::translate("InfoDynamicClassifyFormClass", "InfoDynamicClassifyForm", nullptr));
        label_59->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272", nullptr));
        label_60->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\345\217\216\347\270\256\343\203\211\343\203\203\343\203\210", nullptr));
        label_61->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\345\207\246\347\220\206\345\204\252\345\205\210\345\272\246", nullptr));
        label_62->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\345\244\211\345\213\225\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_63->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\351\240\230\345\237\237\351\207\215\350\244\207\343\203\211\343\203\203\343\203\210", nullptr));
        label_64->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\350\274\252\351\203\255\357\274\215\345\206\205\345\201\264", nullptr));
        label_65->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\350\274\252\351\203\255\357\274\215\351\201\267\347\247\273", nullptr));
        label_66->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\350\274\252\351\203\255\357\274\215\345\244\226\345\201\264", nullptr));
        label_7->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\350\277\275\345\212\240\350\211\262", nullptr));
        label_8->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\351\231\244\345\244\226\350\211\262", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "...", nullptr));
        EditLibName->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "XXX", nullptr));
        label_4->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        EditLibID->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "12345", nullptr));
        label_5->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        pushButtonEliminateColor->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "Eliminate color", nullptr));
        pushButtonAddColor->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "Add Color", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QCoreApplication::translate("InfoDynamicClassifyFormClass", "\350\211\262\347\231\273\351\214\262\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        label_44->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\343\203\224\343\203\203\343\202\257\343\202\242\343\203\203\343\203\227\350\211\262\343\201\256\350\277\275\345\212\240\343\203\273\351\231\244\345\244\226", nullptr));
        pushButtonSubPickupColor->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "Sub =>", nullptr));
        pushButtonAddPickupColor->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "Add =>", nullptr));
        label_45->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\343\203\236\343\203\274\343\202\270\343\203\263\350\274\235\345\272\246", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_8), QCoreApplication::translate("InfoDynamicClassifyFormClass", "\343\203\224\343\202\257\343\202\273\343\203\253\346\212\275\345\207\272\350\211\262", nullptr));
        pushButtonAddColorArea->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "Add Color", nullptr));
        pushButtonEliminateColorArea->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "Eliminate color", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_9), QCoreApplication::translate("InfoDynamicClassifyFormClass", "\351\240\230\345\237\237\346\212\275\345\207\272\350\211\262", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonRelrectOnlyBlock->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\343\201\223\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonRelrectSaveParts->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\351\203\250\345\223\201\344\277\235\345\255\230", nullptr));
        ButtonClose->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_86->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\350\243\234\n"
"\346\255\243", nullptr));
        label_88->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_89->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        toolButtonCoreArea->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "Core", nullptr));
        toolButtonMaxZone->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "Max Zone", nullptr));
        toolButtonOutlineIArea->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "Outline-I", nullptr));
        toolButtonOutlineTArea->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "Outline-T", nullptr));
        toolButtonOutlineOArea->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "Outline-O", nullptr));
        pushButtonReCalc->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "\345\206\215\350\250\210\347\256\227", nullptr));
        toolButtonBareArea->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "Bare", nullptr));
        toolButtonInside->setText(QCoreApplication::translate("InfoDynamicClassifyFormClass", "Inside", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InfoDynamicClassifyFormClass: public Ui_InfoDynamicClassifyFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFODYNAMICCLASSIFYFORM_H
