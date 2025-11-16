/********************************************************************************
** Form generated from reading UI file 'EulerRingHistgramForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EULERRINGHISTGRAMFORM_H
#define UI_EULERRINGHISTGRAMFORM_H

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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EulerRingHistgramFormClass
{
public:
    QTabWidget *tabWidgetInspect;
    QWidget *tab_10;
    QLabel *label_62;
    QSpinBox *EditMergin;
    QLabel *label_49;
    QSpinBox *EditExpandedDot;
    QWidget *tab_13;
    QLabel *label_29;
    QLabel *label_32;
    QSpinBox *EditAdjustWhite;
    QSpinBox *EditAdjustBlack;
    QLabel *label_6;
    QFrame *frameCurrentPos;
    QPushButton *pushButtonSub;
    QPushButton *pushButtonAdd;
    QSpinBox *spinBoxMerginSub;
    QLabel *label_39;
    QSpinBox *spinBoxMerginAdd;
    QLabel *label_4;
    QLabel *label_40;
    QPushButton *pushButtonChangeLib;
    QLineEdit *EditLibName;
    QFrame *frame;
    QLabel *label_41;
    QLabel *label_5;
    QLabel *labelResult;
    QPushButton *ButtonCalc;
    QLineEdit *EditLibID;
    QFrame *frameCurrentItem;
    QFrame *frameColorSample;
    QPushButton *pushButtonEliminateColor;
    QPushButton *pushButtonAddColor;
    QPushButton *ButtonLoadFromLibrary;
    QPushButton *ButtonReflectAllBlocks;
    QFrame *framePicked;
    QLabel *label_43;
    QPushButton *pushButtonSubPickupColor;
    QPushButton *pushButtonAddPickupColor;
    QSpinBox *spinBoxMerginAddPickupColor;
    QSpinBox *spinBoxMerginSubPickupColor;
    QLabel *label_44;
    QFrame *framePickupColor;
    QLabel *label_8;
    QPushButton *ButtonClose;
    QFrame *frameTarget;
    QFrame *frameThreshold;
    QLabel *label_45;
    QLabel *label_9;
    QListWidget *listWidgetBaseColor;
    QLabel *label_10;
    QListWidget *listWidgetEliminatedColor;
    QStackedWidget *stackedWidgetParts;
    QWidget *page_4;
    QPushButton *ButtonRefrectOnlyBlock;
    QWidget *page_5;
    QPushButton *ButtonRelrectSaveParts_2;
    QWidget *page_6;
    QLabel *label_46;
    QLabel *label_11;
    QPushButton *ButtonSaveToLibrary;

    void setupUi(QWidget *EulerRingHistgramFormClass)
    {
        if (EulerRingHistgramFormClass->objectName().isEmpty())
            EulerRingHistgramFormClass->setObjectName("EulerRingHistgramFormClass");
        EulerRingHistgramFormClass->resize(819, 585);
        tabWidgetInspect = new QTabWidget(EulerRingHistgramFormClass);
        tabWidgetInspect->setObjectName("tabWidgetInspect");
        tabWidgetInspect->setGeometry(QRect(40, 380, 321, 111));
        tab_10 = new QWidget();
        tab_10->setObjectName("tab_10");
        label_62 = new QLabel(tab_10);
        label_62->setObjectName("label_62");
        label_62->setGeometry(QRect(9, 10, 91, 21));
        label_62->setFrameShape(QFrame::Panel);
        label_62->setFrameShadow(QFrame::Sunken);
        label_62->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMergin = new QSpinBox(tab_10);
        EditMergin->setObjectName("EditMergin");
        EditMergin->setGeometry(QRect(40, 30, 61, 22));
        EditMergin->setMaximum(99999999);
        label_49 = new QLabel(tab_10);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(140, 10, 71, 21));
        label_49->setFrameShape(QFrame::Panel);
        label_49->setFrameShadow(QFrame::Sunken);
        label_49->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditExpandedDot = new QSpinBox(tab_10);
        EditExpandedDot->setObjectName("EditExpandedDot");
        EditExpandedDot->setGeometry(QRect(150, 30, 61, 22));
        EditExpandedDot->setMaximum(99999999);
        tabWidgetInspect->addTab(tab_10, QString());
        tab_13 = new QWidget();
        tab_13->setObjectName("tab_13");
        label_29 = new QLabel(tab_13);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(10, 60, 201, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_32 = new QLabel(tab_13);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(10, 30, 201, 21));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditAdjustWhite = new QSpinBox(tab_13);
        EditAdjustWhite->setObjectName("EditAdjustWhite");
        EditAdjustWhite->setGeometry(QRect(220, 60, 81, 22));
        EditAdjustWhite->setMaximum(255);
        EditAdjustBlack = new QSpinBox(tab_13);
        EditAdjustBlack->setObjectName("EditAdjustBlack");
        EditAdjustBlack->setGeometry(QRect(220, 30, 81, 22));
        EditAdjustBlack->setMaximum(255);
        tabWidgetInspect->addTab(tab_13, QString());
        label_6 = new QLabel(EulerRingHistgramFormClass);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 380, 20, 111));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Raised);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6->setIndent(1);
        frameCurrentPos = new QFrame(EulerRingHistgramFormClass);
        frameCurrentPos->setObjectName("frameCurrentPos");
        frameCurrentPos->setGeometry(QRect(20, 260, 311, 111));
        frameCurrentPos->setFrameShape(QFrame::StyledPanel);
        frameCurrentPos->setFrameShadow(QFrame::Sunken);
        pushButtonSub = new QPushButton(frameCurrentPos);
        pushButtonSub->setObjectName("pushButtonSub");
        pushButtonSub->setGeometry(QRect(10, 80, 75, 23));
        pushButtonAdd = new QPushButton(frameCurrentPos);
        pushButtonAdd->setObjectName("pushButtonAdd");
        pushButtonAdd->setGeometry(QRect(10, 50, 75, 23));
        spinBoxMerginSub = new QSpinBox(frameCurrentPos);
        spinBoxMerginSub->setObjectName("spinBoxMerginSub");
        spinBoxMerginSub->setGeometry(QRect(90, 80, 61, 22));
        label_39 = new QLabel(frameCurrentPos);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(90, 30, 64, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxMerginAdd = new QSpinBox(frameCurrentPos);
        spinBoxMerginAdd->setObjectName("spinBoxMerginAdd");
        spinBoxMerginAdd->setGeometry(QRect(90, 50, 61, 22));
        label_4 = new QLabel(frameCurrentPos);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(160, 50, 141, 52));
        label_40 = new QLabel(frameCurrentPos);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(0, 0, 311, 21));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setFrameShadow(QFrame::Sunken);
        label_40->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonChangeLib = new QPushButton(EulerRingHistgramFormClass);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(430, 20, 75, 23));
        EditLibName = new QLineEdit(EulerRingHistgramFormClass);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(280, 20, 141, 21));
        EditLibName->setReadOnly(true);
        frame = new QFrame(EulerRingHistgramFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(390, 380, 131, 151));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_41 = new QLabel(frame);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(0, 0, 131, 21));
        label_41->setFrameShape(QFrame::Panel);
        label_41->setFrameShadow(QFrame::Sunken);
        label_41->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 60, 61, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelResult = new QLabel(frame);
        labelResult->setObjectName("labelResult");
        labelResult->setGeometry(QRect(70, 60, 51, 21));
        labelResult->setFrameShape(QFrame::Panel);
        labelResult->setFrameShadow(QFrame::Sunken);
        labelResult->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonCalc = new QPushButton(frame);
        ButtonCalc->setObjectName("ButtonCalc");
        ButtonCalc->setGeometry(QRect(10, 120, 111, 31));
        EditLibID = new QLineEdit(EulerRingHistgramFormClass);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(80, 20, 61, 21));
        EditLibID->setReadOnly(true);
        frameCurrentItem = new QFrame(EulerRingHistgramFormClass);
        frameCurrentItem->setObjectName("frameCurrentItem");
        frameCurrentItem->setGeometry(QRect(20, 70, 251, 181));
        frameCurrentItem->setFrameShape(QFrame::StyledPanel);
        frameCurrentItem->setFrameShadow(QFrame::Sunken);
        frameColorSample = new QFrame(EulerRingHistgramFormClass);
        frameColorSample->setObjectName("frameColorSample");
        frameColorSample->setGeometry(QRect(610, 20, 205, 511));
        frameColorSample->setFrameShape(QFrame::StyledPanel);
        frameColorSample->setFrameShadow(QFrame::Sunken);
        pushButtonEliminateColor = new QPushButton(frameColorSample);
        pushButtonEliminateColor->setObjectName("pushButtonEliminateColor");
        pushButtonEliminateColor->setGeometry(QRect(20, 480, 161, 25));
        pushButtonAddColor = new QPushButton(frameColorSample);
        pushButtonAddColor->setObjectName("pushButtonAddColor");
        pushButtonAddColor->setGeometry(QRect(20, 450, 161, 25));
        ButtonLoadFromLibrary = new QPushButton(EulerRingHistgramFormClass);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(200, 540, 171, 31));
        ButtonReflectAllBlocks = new QPushButton(EulerRingHistgramFormClass);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(200, 500, 171, 31));
        framePicked = new QFrame(EulerRingHistgramFormClass);
        framePicked->setObjectName("framePicked");
        framePicked->setGeometry(QRect(340, 260, 191, 111));
        framePicked->setFrameShape(QFrame::StyledPanel);
        framePicked->setFrameShadow(QFrame::Sunken);
        label_43 = new QLabel(framePicked);
        label_43->setObjectName("label_43");
        label_43->setGeometry(QRect(0, 0, 191, 21));
        label_43->setFrameShape(QFrame::Panel);
        label_43->setFrameShadow(QFrame::Sunken);
        label_43->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
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
        label_44 = new QLabel(framePicked);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(120, 30, 64, 21));
        label_44->setFrameShape(QFrame::Panel);
        label_44->setFrameShadow(QFrame::Sunken);
        label_44->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        framePickupColor = new QFrame(framePicked);
        framePickupColor->setObjectName("framePickupColor");
        framePickupColor->setGeometry(QRect(10, 30, 21, 71));
        framePickupColor->setFrameShape(QFrame::NoFrame);
        framePickupColor->setFrameShadow(QFrame::Plain);
        label_8 = new QLabel(EulerRingHistgramFormClass);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(160, 20, 121, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonClose = new QPushButton(EulerRingHistgramFormClass);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(630, 540, 161, 31));
        frameTarget = new QFrame(EulerRingHistgramFormClass);
        frameTarget->setObjectName("frameTarget");
        frameTarget->setGeometry(QRect(280, 50, 331, 211));
        frameTarget->setFrameShape(QFrame::NoFrame);
        frameTarget->setFrameShadow(QFrame::Plain);
        frameThreshold = new QFrame(frameTarget);
        frameThreshold->setObjectName("frameThreshold");
        frameThreshold->setGeometry(QRect(0, 20, 251, 181));
        frameThreshold->setFrameShape(QFrame::StyledPanel);
        frameThreshold->setFrameShadow(QFrame::Sunken);
        label_45 = new QLabel(frameTarget);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(0, 0, 251, 21));
        label_45->setFrameShape(QFrame::Panel);
        label_45->setFrameShadow(QFrame::Sunken);
        label_45->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_9 = new QLabel(frameTarget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(260, 120, 61, 20));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetBaseColor = new QListWidget(frameTarget);
        listWidgetBaseColor->setObjectName("listWidgetBaseColor");
        listWidgetBaseColor->setGeometry(QRect(260, 20, 61, 61));
        label_10 = new QLabel(frameTarget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(260, 0, 61, 20));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetEliminatedColor = new QListWidget(frameTarget);
        listWidgetEliminatedColor->setObjectName("listWidgetEliminatedColor");
        listWidgetEliminatedColor->setGeometry(QRect(260, 140, 61, 61));
        stackedWidgetParts = new QStackedWidget(EulerRingHistgramFormClass);
        stackedWidgetParts->setObjectName("stackedWidgetParts");
        stackedWidgetParts->setGeometry(QRect(20, 500, 181, 31));
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        ButtonRefrectOnlyBlock = new QPushButton(page_4);
        ButtonRefrectOnlyBlock->setObjectName("ButtonRefrectOnlyBlock");
        ButtonRefrectOnlyBlock->setGeometry(QRect(0, 0, 171, 31));
        stackedWidgetParts->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        ButtonRelrectSaveParts_2 = new QPushButton(page_5);
        ButtonRelrectSaveParts_2->setObjectName("ButtonRelrectSaveParts_2");
        ButtonRelrectSaveParts_2->setGeometry(QRect(0, 0, 171, 31));
        stackedWidgetParts->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        stackedWidgetParts->addWidget(page_6);
        label_46 = new QLabel(EulerRingHistgramFormClass);
        label_46->setObjectName("label_46");
        label_46->setGeometry(QRect(20, 50, 251, 21));
        label_46->setFrameShape(QFrame::Panel);
        label_46->setFrameShadow(QFrame::Sunken);
        label_46->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_11 = new QLabel(EulerRingHistgramFormClass);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(20, 20, 61, 20));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonSaveToLibrary = new QPushButton(EulerRingHistgramFormClass);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(20, 540, 171, 31));

        retranslateUi(EulerRingHistgramFormClass);

        tabWidgetInspect->setCurrentIndex(1);
        stackedWidgetParts->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EulerRingHistgramFormClass);
    } // setupUi

    void retranslateUi(QWidget *EulerRingHistgramFormClass)
    {
        EulerRingHistgramFormClass->setWindowTitle(QCoreApplication::translate("EulerRingHistgramFormClass", "EulerRingHistgramForm", nullptr));
        label_62->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\350\274\235\345\272\246\343\203\236\343\203\274\343\202\270\343\203\263", nullptr));
        label_49->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_10), QCoreApplication::translate("EulerRingHistgramFormClass", "\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        label_29->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_32->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_13), QCoreApplication::translate("EulerRingHistgramFormClass", "\350\243\234\346\255\243", nullptr));
        label_6->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\346\244\234\n"
"\346\237\273", nullptr));
        pushButtonSub->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "Sub =>", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "Add =>", nullptr));
        label_39->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\343\203\236\343\203\274\343\202\270\343\203\263\350\274\235\345\272\246", nullptr));
        label_4->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "Add : \343\201\223\343\201\256\343\203\236\343\203\274\343\202\270\343\203\263\345\210\206\343\201\240\343\201\221\350\274\235\345\272\246\343\202\222\n"
"        \346\213\241\345\274\265\343\201\227\343\201\246\350\277\275\345\212\240\n"
"Sub : \343\201\223\343\201\256\343\203\236\343\203\274\343\202\270\343\203\263\345\210\206\343\201\240\343\201\221\350\274\235\345\272\246\343\202\222\n"
"        \346\213\241\345\274\265\343\201\227\343\201\246\351\231\244\345\244\226\350\274\235\345\272\246\343\201\253\350\277\275\345\212\240", nullptr));
        label_40->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\350\211\262\343\201\256\350\277\275\345\212\240\343\203\273\351\231\244\345\244\226", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "...", nullptr));
        EditLibName->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "XXX", nullptr));
        label_41->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\345\210\244\345\256\232\347\265\220\346\236\234", nullptr));
        label_5->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\345\210\244\345\256\232", nullptr));
        labelResult->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "123", nullptr));
        ButtonCalc->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\350\250\210\347\256\227", nullptr));
        EditLibID->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "12345", nullptr));
        pushButtonEliminateColor->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "Eliminate color", nullptr));
        pushButtonAddColor->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "Add Color", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\253\345\217\215\346\230\240", nullptr));
        label_43->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\343\203\224\343\203\203\343\202\257\343\202\242\343\203\203\343\203\227\350\211\262\343\201\256\350\277\275\345\212\240\343\203\273\351\231\244\345\244\226", nullptr));
        pushButtonSubPickupColor->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "Sub =>", nullptr));
        pushButtonAddPickupColor->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "Add =>", nullptr));
        label_44->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\343\203\236\343\203\274\343\202\270\343\203\263\350\274\235\345\272\246", nullptr));
        label_8->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        ButtonClose->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_45->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\346\244\234\346\237\273\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        label_9->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\351\231\244\345\244\226\350\211\262", nullptr));
        label_10->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\350\277\275\345\212\240\350\211\262", nullptr));
        ButtonRefrectOnlyBlock->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\343\201\223\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonRelrectSaveParts_2->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\351\203\250\345\223\201\344\277\235\345\255\230", nullptr));
        label_46->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\343\202\253\343\203\251\343\203\274\343\203\236\343\203\203\343\203\227", nullptr));
        label_11->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("EulerRingHistgramFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EulerRingHistgramFormClass: public Ui_EulerRingHistgramFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EULERRINGHISTGRAMFORM_H
