/********************************************************************************
** Form generated from reading UI file 'WizardMenuForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIZARDMENUFORM_H
#define UI_WIZARDMENUFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WizardMenuForm
{
public:
    QStackedWidget *stackedWidget;
    QWidget *CreateNew;
    QStackedWidget *stackedWidgetSenario;
    QWidget *page;
    QTextEdit *textEdit;
    QPushButton *PushButtonCreateNewNext1;
    QPushButton *PushButtonCreateNewPrev1;
    QWidget *page_3;
    QTextEdit *textEdit_2;
    QPushButton *PushButtonCreateNewNext2;
    QPushButton *PushButtonCreateNewPrev2;
    QPushButton *pushButtonSetTriggerPosition;
    QWidget *page_4;
    QPushButton *PushButtonCreateNewSave;
    QPushButton *PushButtonCreateNewAgain;
    QWidget *page_5;
    QTextEdit *textEdit_3;
    QPushButton *PushButtonCreateNewNext4;
    QPushButton *PushButtonCreateNewPrev4;
    QWidget *Edit;
    QStackedWidget *stackedWidgetStory;
    QWidget *page_2;
    QPushButton *PushButtonAutoGenerate;
    QPushButton *PushButtonSwitchPhase;
    QPushButton *PushButtonCopyImage;
    QPushButton *PushButtonEditDetail;
    QWidget *page_6;
    QTextEdit *textEdit_4;
    QPushButton *PushButtonSwitchPhaseNext;
    QPushButton *PushButtonSwitchPhasePrev;
    QWidget *page_14;
    QTextEdit *textEdit_12;
    QPushButton *PushButtonSwitchPhaseNext2;
    QPushButton *PushButtonSwitchPhasePrev2;
    QWidget *page_7;
    QTextEdit *textEdit_5;
    QPushButton *PushButtonReadDXFUpper;
    QPushButton *PushButtonReadDXFLower;
    QPushButton *PushButtonDXFReturn;
    QPushButton *PushButtonDXFPrev;
    QWidget *page_8;
    QTextEdit *textEdit_6;
    QPushButton *DXFNext1;
    QPushButton *DXFPrev1;
    QWidget *page_9;
    QTextEdit *textEdit_7;
    QPushButton *PushButtonDXFNext2;
    QPushButton *PushButtonDXFNext3;
    QPushButton *PushButtonDXFPrev3;
    QTextEdit *textEdit_14;
    QWidget *page_10;
    QTextEdit *textEdit_8;
    QPushButton *PushButtonMaskNext1;
    QPushButton *PushButtonMaskPrev1;
    QWidget *page_12;
    QPushButton *PushButtonAlignmentNext;
    QTextEdit *textEdit_9;
    QPushButton *PushButtonAlignmentPrev;
    QWidget *page_11;
    QPushButton *PushButtonInspectionNext1;
    QTextEdit *textEdit_10;
    QPushButton *PushButtonInspectionPrev1;
    QWidget *page_13;
    QPushButton *PushButtonBladeNext1;
    QTextEdit *textEdit_11;
    QPushButton *PushButtonBladePrev1;
    QTextEdit *textEdit_13;
    QWidget *page_15;
    QPushButton *PushButtonClose;
    QFrame *frame;
    QPushButton *PushButtonLoadMaster;
    QPushButton *PushButtonCreateNew;
    QPushButton *PushButtonEdit;
    QPushButton *PushButtonSetExposure;

    void setupUi(QWidget *WizardMenuForm)
    {
        if (WizardMenuForm->objectName().isEmpty())
            WizardMenuForm->setObjectName("WizardMenuForm");
        WizardMenuForm->resize(231, 950);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WizardMenuForm->sizePolicy().hasHeightForWidth());
        WizardMenuForm->setSizePolicy(sizePolicy);
        WizardMenuForm->setMinimumSize(QSize(231, 950));
        WizardMenuForm->setMaximumSize(QSize(231, 950));
        QPalette palette;
        WizardMenuForm->setPalette(palette);
        WizardMenuForm->setAutoFillBackground(true);
        WizardMenuForm->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        stackedWidget = new QStackedWidget(WizardMenuForm);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 270, 211, 601));
        CreateNew = new QWidget();
        CreateNew->setObjectName("CreateNew");
        stackedWidgetSenario = new QStackedWidget(CreateNew);
        stackedWidgetSenario->setObjectName("stackedWidgetSenario");
        stackedWidgetSenario->setGeometry(QRect(0, 20, 211, 511));
        page = new QWidget();
        page->setObjectName("page");
        textEdit = new QTextEdit(page);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(0, 40, 211, 341));
        textEdit->setReadOnly(true);
        PushButtonCreateNewNext1 = new QPushButton(page);
        PushButtonCreateNewNext1->setObjectName("PushButtonCreateNewNext1");
        PushButtonCreateNewNext1->setGeometry(QRect(30, 390, 151, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(20);
        PushButtonCreateNewNext1->setFont(font);
        PushButtonCreateNewNext1->setStyleSheet(QString::fromUtf8(""));
        PushButtonCreateNewNext1->setCheckable(false);
        PushButtonCreateNewNext1->setChecked(false);
        PushButtonCreateNewNext1->setAutoDefault(false);
        PushButtonCreateNewNext1->setFlat(false);
        PushButtonCreateNewPrev1 = new QPushButton(page);
        PushButtonCreateNewPrev1->setObjectName("PushButtonCreateNewPrev1");
        PushButtonCreateNewPrev1->setGeometry(QRect(30, 450, 151, 61));
        PushButtonCreateNewPrev1->setFont(font);
        PushButtonCreateNewPrev1->setStyleSheet(QString::fromUtf8(""));
        PushButtonCreateNewPrev1->setCheckable(false);
        PushButtonCreateNewPrev1->setChecked(false);
        PushButtonCreateNewPrev1->setAutoDefault(false);
        PushButtonCreateNewPrev1->setFlat(false);
        stackedWidgetSenario->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        textEdit_2 = new QTextEdit(page_3);
        textEdit_2->setObjectName("textEdit_2");
        textEdit_2->setGeometry(QRect(0, 40, 211, 281));
        textEdit_2->setReadOnly(true);
        PushButtonCreateNewNext2 = new QPushButton(page_3);
        PushButtonCreateNewNext2->setObjectName("PushButtonCreateNewNext2");
        PushButtonCreateNewNext2->setGeometry(QRect(20, 350, 171, 61));
        PushButtonCreateNewNext2->setFont(font);
        PushButtonCreateNewNext2->setStyleSheet(QString::fromUtf8(""));
        PushButtonCreateNewNext2->setCheckable(false);
        PushButtonCreateNewNext2->setChecked(false);
        PushButtonCreateNewNext2->setAutoDefault(false);
        PushButtonCreateNewNext2->setFlat(false);
        PushButtonCreateNewPrev2 = new QPushButton(page_3);
        PushButtonCreateNewPrev2->setObjectName("PushButtonCreateNewPrev2");
        PushButtonCreateNewPrev2->setGeometry(QRect(20, 420, 171, 61));
        PushButtonCreateNewPrev2->setFont(font);
        PushButtonCreateNewPrev2->setStyleSheet(QString::fromUtf8(""));
        PushButtonCreateNewPrev2->setCheckable(false);
        PushButtonCreateNewPrev2->setChecked(false);
        PushButtonCreateNewPrev2->setAutoDefault(false);
        PushButtonCreateNewPrev2->setFlat(false);
        pushButtonSetTriggerPosition = new QPushButton(page_3);
        pushButtonSetTriggerPosition->setObjectName("pushButtonSetTriggerPosition");
        pushButtonSetTriggerPosition->setGeometry(QRect(20, 250, 171, 61));
        QFont font1;
        font1.setPointSize(12);
        pushButtonSetTriggerPosition->setFont(font1);
        stackedWidgetSenario->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        PushButtonCreateNewSave = new QPushButton(page_4);
        PushButtonCreateNewSave->setObjectName("PushButtonCreateNewSave");
        PushButtonCreateNewSave->setGeometry(QRect(30, 30, 151, 61));
        PushButtonCreateNewSave->setFont(font);
        PushButtonCreateNewSave->setStyleSheet(QString::fromUtf8(""));
        PushButtonCreateNewSave->setCheckable(false);
        PushButtonCreateNewSave->setChecked(false);
        PushButtonCreateNewSave->setAutoDefault(false);
        PushButtonCreateNewSave->setFlat(false);
        PushButtonCreateNewAgain = new QPushButton(page_4);
        PushButtonCreateNewAgain->setObjectName("PushButtonCreateNewAgain");
        PushButtonCreateNewAgain->setGeometry(QRect(30, 110, 151, 61));
        PushButtonCreateNewAgain->setFont(font);
        PushButtonCreateNewAgain->setStyleSheet(QString::fromUtf8(""));
        PushButtonCreateNewAgain->setCheckable(false);
        PushButtonCreateNewAgain->setChecked(false);
        PushButtonCreateNewAgain->setAutoDefault(false);
        PushButtonCreateNewAgain->setFlat(false);
        stackedWidgetSenario->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        textEdit_3 = new QTextEdit(page_5);
        textEdit_3->setObjectName("textEdit_3");
        textEdit_3->setGeometry(QRect(0, 10, 211, 341));
        textEdit_3->setReadOnly(true);
        PushButtonCreateNewNext4 = new QPushButton(page_5);
        PushButtonCreateNewNext4->setObjectName("PushButtonCreateNewNext4");
        PushButtonCreateNewNext4->setGeometry(QRect(30, 370, 151, 61));
        PushButtonCreateNewNext4->setFont(font);
        PushButtonCreateNewNext4->setStyleSheet(QString::fromUtf8(""));
        PushButtonCreateNewNext4->setCheckable(false);
        PushButtonCreateNewNext4->setChecked(false);
        PushButtonCreateNewNext4->setAutoDefault(false);
        PushButtonCreateNewNext4->setFlat(false);
        PushButtonCreateNewPrev4 = new QPushButton(page_5);
        PushButtonCreateNewPrev4->setObjectName("PushButtonCreateNewPrev4");
        PushButtonCreateNewPrev4->setGeometry(QRect(30, 440, 151, 61));
        PushButtonCreateNewPrev4->setFont(font);
        PushButtonCreateNewPrev4->setStyleSheet(QString::fromUtf8(""));
        PushButtonCreateNewPrev4->setCheckable(false);
        PushButtonCreateNewPrev4->setChecked(false);
        PushButtonCreateNewPrev4->setAutoDefault(false);
        PushButtonCreateNewPrev4->setFlat(false);
        stackedWidgetSenario->addWidget(page_5);
        stackedWidget->addWidget(CreateNew);
        Edit = new QWidget();
        Edit->setObjectName("Edit");
        stackedWidgetStory = new QStackedWidget(Edit);
        stackedWidgetStory->setObjectName("stackedWidgetStory");
        stackedWidgetStory->setGeometry(QRect(0, 20, 211, 571));
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        PushButtonAutoGenerate = new QPushButton(page_2);
        PushButtonAutoGenerate->setObjectName("PushButtonAutoGenerate");
        PushButtonAutoGenerate->setGeometry(QRect(0, 30, 211, 71));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font2.setPointSize(24);
        PushButtonAutoGenerate->setFont(font2);
        PushButtonAutoGenerate->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(120, 254, 180, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonAutoGenerate->setCheckable(true);
        PushButtonAutoGenerate->setAutoDefault(false);
        PushButtonAutoGenerate->setFlat(false);
        PushButtonSwitchPhase = new QPushButton(page_2);
        PushButtonSwitchPhase->setObjectName("PushButtonSwitchPhase");
        PushButtonSwitchPhase->setGeometry(QRect(0, 120, 211, 61));
        PushButtonSwitchPhase->setFont(font);
        PushButtonSwitchPhase->setStyleSheet(QString::fromUtf8(""));
        PushButtonSwitchPhase->setCheckable(false);
        PushButtonSwitchPhase->setChecked(false);
        PushButtonSwitchPhase->setAutoDefault(false);
        PushButtonSwitchPhase->setFlat(false);
        PushButtonCopyImage = new QPushButton(page_2);
        PushButtonCopyImage->setObjectName("PushButtonCopyImage");
        PushButtonCopyImage->setGeometry(QRect(0, 200, 211, 61));
        PushButtonCopyImage->setFont(font);
        PushButtonCopyImage->setStyleSheet(QString::fromUtf8(""));
        PushButtonCopyImage->setCheckable(false);
        PushButtonCopyImage->setChecked(false);
        PushButtonCopyImage->setAutoDefault(false);
        PushButtonCopyImage->setFlat(false);
        PushButtonEditDetail = new QPushButton(page_2);
        PushButtonEditDetail->setObjectName("PushButtonEditDetail");
        PushButtonEditDetail->setGeometry(QRect(0, 280, 211, 61));
        PushButtonEditDetail->setFont(font);
        PushButtonEditDetail->setStyleSheet(QString::fromUtf8(""));
        PushButtonEditDetail->setCheckable(false);
        PushButtonEditDetail->setChecked(false);
        PushButtonEditDetail->setAutoDefault(false);
        PushButtonEditDetail->setFlat(false);
        stackedWidgetStory->addWidget(page_2);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        textEdit_4 = new QTextEdit(page_6);
        textEdit_4->setObjectName("textEdit_4");
        textEdit_4->setGeometry(QRect(0, 10, 211, 361));
        textEdit_4->setReadOnly(true);
        PushButtonSwitchPhaseNext = new QPushButton(page_6);
        PushButtonSwitchPhaseNext->setObjectName("PushButtonSwitchPhaseNext");
        PushButtonSwitchPhaseNext->setGeometry(QRect(10, 390, 181, 61));
        PushButtonSwitchPhaseNext->setFont(font);
        PushButtonSwitchPhaseNext->setStyleSheet(QString::fromUtf8(""));
        PushButtonSwitchPhaseNext->setCheckable(false);
        PushButtonSwitchPhaseNext->setChecked(false);
        PushButtonSwitchPhaseNext->setAutoDefault(false);
        PushButtonSwitchPhaseNext->setFlat(false);
        PushButtonSwitchPhasePrev = new QPushButton(page_6);
        PushButtonSwitchPhasePrev->setObjectName("PushButtonSwitchPhasePrev");
        PushButtonSwitchPhasePrev->setGeometry(QRect(10, 450, 181, 61));
        PushButtonSwitchPhasePrev->setFont(font);
        PushButtonSwitchPhasePrev->setStyleSheet(QString::fromUtf8(""));
        PushButtonSwitchPhasePrev->setCheckable(false);
        PushButtonSwitchPhasePrev->setChecked(false);
        PushButtonSwitchPhasePrev->setAutoDefault(false);
        PushButtonSwitchPhasePrev->setFlat(false);
        stackedWidgetStory->addWidget(page_6);
        page_14 = new QWidget();
        page_14->setObjectName("page_14");
        textEdit_12 = new QTextEdit(page_14);
        textEdit_12->setObjectName("textEdit_12");
        textEdit_12->setGeometry(QRect(0, 20, 211, 361));
        textEdit_12->setReadOnly(true);
        PushButtonSwitchPhaseNext2 = new QPushButton(page_14);
        PushButtonSwitchPhaseNext2->setObjectName("PushButtonSwitchPhaseNext2");
        PushButtonSwitchPhaseNext2->setGeometry(QRect(0, 390, 211, 71));
        PushButtonSwitchPhaseNext2->setFont(font);
        PushButtonSwitchPhaseNext2->setStyleSheet(QString::fromUtf8(""));
        PushButtonSwitchPhaseNext2->setCheckable(false);
        PushButtonSwitchPhaseNext2->setChecked(false);
        PushButtonSwitchPhaseNext2->setAutoDefault(false);
        PushButtonSwitchPhaseNext2->setFlat(false);
        PushButtonSwitchPhasePrev2 = new QPushButton(page_14);
        PushButtonSwitchPhasePrev2->setObjectName("PushButtonSwitchPhasePrev2");
        PushButtonSwitchPhasePrev2->setGeometry(QRect(0, 460, 211, 61));
        PushButtonSwitchPhasePrev2->setFont(font);
        PushButtonSwitchPhasePrev2->setStyleSheet(QString::fromUtf8(""));
        PushButtonSwitchPhasePrev2->setCheckable(false);
        PushButtonSwitchPhasePrev2->setChecked(false);
        PushButtonSwitchPhasePrev2->setAutoDefault(false);
        PushButtonSwitchPhasePrev2->setFlat(false);
        stackedWidgetStory->addWidget(page_14);
        page_7 = new QWidget();
        page_7->setObjectName("page_7");
        textEdit_5 = new QTextEdit(page_7);
        textEdit_5->setObjectName("textEdit_5");
        textEdit_5->setGeometry(QRect(0, 20, 211, 101));
        textEdit_5->setReadOnly(true);
        PushButtonReadDXFUpper = new QPushButton(page_7);
        PushButtonReadDXFUpper->setObjectName("PushButtonReadDXFUpper");
        PushButtonReadDXFUpper->setGeometry(QRect(0, 150, 211, 61));
        PushButtonReadDXFUpper->setFont(font);
        PushButtonReadDXFUpper->setStyleSheet(QString::fromUtf8(""));
        PushButtonReadDXFUpper->setCheckable(false);
        PushButtonReadDXFUpper->setChecked(false);
        PushButtonReadDXFUpper->setAutoDefault(false);
        PushButtonReadDXFUpper->setFlat(false);
        PushButtonReadDXFLower = new QPushButton(page_7);
        PushButtonReadDXFLower->setObjectName("PushButtonReadDXFLower");
        PushButtonReadDXFLower->setGeometry(QRect(0, 220, 211, 61));
        PushButtonReadDXFLower->setFont(font);
        PushButtonReadDXFLower->setStyleSheet(QString::fromUtf8(""));
        PushButtonReadDXFLower->setCheckable(false);
        PushButtonReadDXFLower->setChecked(false);
        PushButtonReadDXFLower->setAutoDefault(false);
        PushButtonReadDXFLower->setFlat(false);
        PushButtonDXFReturn = new QPushButton(page_7);
        PushButtonDXFReturn->setObjectName("PushButtonDXFReturn");
        PushButtonDXFReturn->setGeometry(QRect(0, 340, 211, 61));
        PushButtonDXFReturn->setFont(font);
        PushButtonDXFReturn->setStyleSheet(QString::fromUtf8(""));
        PushButtonDXFReturn->setCheckable(false);
        PushButtonDXFReturn->setChecked(false);
        PushButtonDXFReturn->setAutoDefault(false);
        PushButtonDXFReturn->setFlat(false);
        PushButtonDXFPrev = new QPushButton(page_7);
        PushButtonDXFPrev->setObjectName("PushButtonDXFPrev");
        PushButtonDXFPrev->setGeometry(QRect(0, 400, 211, 61));
        PushButtonDXFPrev->setFont(font);
        PushButtonDXFPrev->setStyleSheet(QString::fromUtf8(""));
        PushButtonDXFPrev->setCheckable(false);
        PushButtonDXFPrev->setChecked(false);
        PushButtonDXFPrev->setAutoDefault(false);
        PushButtonDXFPrev->setFlat(false);
        stackedWidgetStory->addWidget(page_7);
        page_8 = new QWidget();
        page_8->setObjectName("page_8");
        textEdit_6 = new QTextEdit(page_8);
        textEdit_6->setObjectName("textEdit_6");
        textEdit_6->setGeometry(QRect(0, 0, 211, 451));
        textEdit_6->setReadOnly(true);
        DXFNext1 = new QPushButton(page_8);
        DXFNext1->setObjectName("DXFNext1");
        DXFNext1->setGeometry(QRect(0, 450, 211, 61));
        DXFNext1->setFont(font);
        DXFNext1->setStyleSheet(QString::fromUtf8(""));
        DXFNext1->setCheckable(false);
        DXFNext1->setChecked(false);
        DXFNext1->setAutoDefault(false);
        DXFNext1->setFlat(false);
        DXFPrev1 = new QPushButton(page_8);
        DXFPrev1->setObjectName("DXFPrev1");
        DXFPrev1->setGeometry(QRect(0, 510, 211, 61));
        DXFPrev1->setFont(font);
        DXFPrev1->setStyleSheet(QString::fromUtf8(""));
        DXFPrev1->setCheckable(false);
        DXFPrev1->setChecked(false);
        DXFPrev1->setAutoDefault(false);
        DXFPrev1->setFlat(false);
        stackedWidgetStory->addWidget(page_8);
        page_9 = new QWidget();
        page_9->setObjectName("page_9");
        textEdit_7 = new QTextEdit(page_9);
        textEdit_7->setObjectName("textEdit_7");
        textEdit_7->setGeometry(QRect(0, 20, 221, 271));
        PushButtonDXFNext2 = new QPushButton(page_9);
        PushButtonDXFNext2->setObjectName("PushButtonDXFNext2");
        PushButtonDXFNext2->setGeometry(QRect(0, 450, 211, 61));
        PushButtonDXFNext2->setFont(font);
        PushButtonDXFNext2->setStyleSheet(QString::fromUtf8(""));
        PushButtonDXFNext2->setCheckable(false);
        PushButtonDXFNext2->setChecked(false);
        PushButtonDXFNext2->setAutoDefault(false);
        PushButtonDXFNext2->setFlat(false);
        PushButtonDXFNext3 = new QPushButton(page_9);
        PushButtonDXFNext3->setObjectName("PushButtonDXFNext3");
        PushButtonDXFNext3->setGeometry(QRect(0, 450, 211, 61));
        PushButtonDXFNext3->setFont(font);
        PushButtonDXFNext3->setStyleSheet(QString::fromUtf8(""));
        PushButtonDXFNext3->setCheckable(false);
        PushButtonDXFNext3->setChecked(false);
        PushButtonDXFNext3->setAutoDefault(false);
        PushButtonDXFNext3->setFlat(false);
        PushButtonDXFPrev3 = new QPushButton(page_9);
        PushButtonDXFPrev3->setObjectName("PushButtonDXFPrev3");
        PushButtonDXFPrev3->setGeometry(QRect(0, 510, 211, 61));
        PushButtonDXFPrev3->setFont(font);
        PushButtonDXFPrev3->setStyleSheet(QString::fromUtf8(""));
        PushButtonDXFPrev3->setCheckable(false);
        PushButtonDXFPrev3->setChecked(false);
        PushButtonDXFPrev3->setAutoDefault(false);
        PushButtonDXFPrev3->setFlat(false);
        textEdit_14 = new QTextEdit(page_9);
        textEdit_14->setObjectName("textEdit_14");
        textEdit_14->setGeometry(QRect(0, 20, 211, 271));
        textEdit_14->setReadOnly(true);
        stackedWidgetStory->addWidget(page_9);
        PushButtonDXFNext2->raise();
        textEdit_7->raise();
        PushButtonDXFNext3->raise();
        PushButtonDXFPrev3->raise();
        textEdit_14->raise();
        page_10 = new QWidget();
        page_10->setObjectName("page_10");
        textEdit_8 = new QTextEdit(page_10);
        textEdit_8->setObjectName("textEdit_8");
        textEdit_8->setGeometry(QRect(0, 20, 211, 341));
        textEdit_8->setReadOnly(true);
        PushButtonMaskNext1 = new QPushButton(page_10);
        PushButtonMaskNext1->setObjectName("PushButtonMaskNext1");
        PushButtonMaskNext1->setGeometry(QRect(0, 400, 211, 61));
        PushButtonMaskNext1->setFont(font);
        PushButtonMaskNext1->setStyleSheet(QString::fromUtf8(""));
        PushButtonMaskNext1->setCheckable(false);
        PushButtonMaskNext1->setChecked(false);
        PushButtonMaskNext1->setAutoDefault(false);
        PushButtonMaskNext1->setFlat(false);
        PushButtonMaskPrev1 = new QPushButton(page_10);
        PushButtonMaskPrev1->setObjectName("PushButtonMaskPrev1");
        PushButtonMaskPrev1->setGeometry(QRect(0, 460, 211, 61));
        PushButtonMaskPrev1->setFont(font);
        PushButtonMaskPrev1->setStyleSheet(QString::fromUtf8(""));
        PushButtonMaskPrev1->setCheckable(false);
        PushButtonMaskPrev1->setChecked(false);
        PushButtonMaskPrev1->setAutoDefault(false);
        PushButtonMaskPrev1->setFlat(false);
        stackedWidgetStory->addWidget(page_10);
        page_12 = new QWidget();
        page_12->setObjectName("page_12");
        PushButtonAlignmentNext = new QPushButton(page_12);
        PushButtonAlignmentNext->setObjectName("PushButtonAlignmentNext");
        PushButtonAlignmentNext->setGeometry(QRect(0, 400, 211, 61));
        PushButtonAlignmentNext->setFont(font);
        PushButtonAlignmentNext->setStyleSheet(QString::fromUtf8(""));
        PushButtonAlignmentNext->setCheckable(false);
        PushButtonAlignmentNext->setChecked(false);
        PushButtonAlignmentNext->setAutoDefault(false);
        PushButtonAlignmentNext->setFlat(false);
        textEdit_9 = new QTextEdit(page_12);
        textEdit_9->setObjectName("textEdit_9");
        textEdit_9->setGeometry(QRect(0, 20, 211, 311));
        textEdit_9->setReadOnly(true);
        PushButtonAlignmentPrev = new QPushButton(page_12);
        PushButtonAlignmentPrev->setObjectName("PushButtonAlignmentPrev");
        PushButtonAlignmentPrev->setGeometry(QRect(0, 460, 211, 61));
        PushButtonAlignmentPrev->setFont(font);
        PushButtonAlignmentPrev->setStyleSheet(QString::fromUtf8(""));
        PushButtonAlignmentPrev->setCheckable(false);
        PushButtonAlignmentPrev->setChecked(false);
        PushButtonAlignmentPrev->setAutoDefault(false);
        PushButtonAlignmentPrev->setFlat(false);
        stackedWidgetStory->addWidget(page_12);
        page_11 = new QWidget();
        page_11->setObjectName("page_11");
        PushButtonInspectionNext1 = new QPushButton(page_11);
        PushButtonInspectionNext1->setObjectName("PushButtonInspectionNext1");
        PushButtonInspectionNext1->setGeometry(QRect(0, 410, 211, 61));
        PushButtonInspectionNext1->setFont(font);
        PushButtonInspectionNext1->setStyleSheet(QString::fromUtf8(""));
        PushButtonInspectionNext1->setCheckable(false);
        PushButtonInspectionNext1->setChecked(false);
        PushButtonInspectionNext1->setAutoDefault(false);
        PushButtonInspectionNext1->setFlat(false);
        textEdit_10 = new QTextEdit(page_11);
        textEdit_10->setObjectName("textEdit_10");
        textEdit_10->setGeometry(QRect(0, 30, 211, 311));
        textEdit_10->setReadOnly(true);
        PushButtonInspectionPrev1 = new QPushButton(page_11);
        PushButtonInspectionPrev1->setObjectName("PushButtonInspectionPrev1");
        PushButtonInspectionPrev1->setGeometry(QRect(0, 470, 211, 61));
        PushButtonInspectionPrev1->setFont(font);
        PushButtonInspectionPrev1->setStyleSheet(QString::fromUtf8(""));
        PushButtonInspectionPrev1->setCheckable(false);
        PushButtonInspectionPrev1->setChecked(false);
        PushButtonInspectionPrev1->setAutoDefault(false);
        PushButtonInspectionPrev1->setFlat(false);
        stackedWidgetStory->addWidget(page_11);
        page_13 = new QWidget();
        page_13->setObjectName("page_13");
        PushButtonBladeNext1 = new QPushButton(page_13);
        PushButtonBladeNext1->setObjectName("PushButtonBladeNext1");
        PushButtonBladeNext1->setGeometry(QRect(0, 430, 211, 61));
        PushButtonBladeNext1->setFont(font);
        PushButtonBladeNext1->setStyleSheet(QString::fromUtf8(""));
        PushButtonBladeNext1->setCheckable(false);
        PushButtonBladeNext1->setChecked(false);
        PushButtonBladeNext1->setAutoDefault(false);
        PushButtonBladeNext1->setFlat(false);
        textEdit_11 = new QTextEdit(page_13);
        textEdit_11->setObjectName("textEdit_11");
        textEdit_11->setGeometry(QRect(0, 10, 221, 371));
        PushButtonBladePrev1 = new QPushButton(page_13);
        PushButtonBladePrev1->setObjectName("PushButtonBladePrev1");
        PushButtonBladePrev1->setGeometry(QRect(0, 500, 211, 61));
        PushButtonBladePrev1->setFont(font);
        PushButtonBladePrev1->setStyleSheet(QString::fromUtf8(""));
        PushButtonBladePrev1->setCheckable(false);
        PushButtonBladePrev1->setChecked(false);
        PushButtonBladePrev1->setAutoDefault(false);
        PushButtonBladePrev1->setFlat(false);
        textEdit_13 = new QTextEdit(page_13);
        textEdit_13->setObjectName("textEdit_13");
        textEdit_13->setGeometry(QRect(0, 10, 211, 371));
        QFont font3;
        font3.setPointSize(9);
        textEdit_13->setFont(font3);
        textEdit_13->setReadOnly(true);
        stackedWidgetStory->addWidget(page_13);
        stackedWidget->addWidget(Edit);
        page_15 = new QWidget();
        page_15->setObjectName("page_15");
        stackedWidget->addWidget(page_15);
        PushButtonClose = new QPushButton(WizardMenuForm);
        PushButtonClose->setObjectName("PushButtonClose");
        PushButtonClose->setGeometry(QRect(10, 880, 211, 61));
        PushButtonClose->setFont(font);
        PushButtonClose->setStyleSheet(QString::fromUtf8(""));
        PushButtonClose->setCheckable(false);
        PushButtonClose->setChecked(false);
        PushButtonClose->setAutoDefault(false);
        PushButtonClose->setFlat(false);
        frame = new QFrame(WizardMenuForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 241, 271));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Plain);
        PushButtonLoadMaster = new QPushButton(frame);
        PushButtonLoadMaster->setObjectName("PushButtonLoadMaster");
        PushButtonLoadMaster->setGeometry(QRect(10, 196, 211, 61));
        PushButtonLoadMaster->setFont(font);
        PushButtonLoadMaster->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 180, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 180, 180, 255), stop:1 rgba(141, 100, 100, 255));\n"
"}"));
        PushButtonLoadMaster->setCheckable(true);
        PushButtonLoadMaster->setChecked(false);
        PushButtonLoadMaster->setAutoExclusive(true);
        PushButtonLoadMaster->setAutoDefault(false);
        PushButtonLoadMaster->setFlat(false);
        PushButtonCreateNew = new QPushButton(frame);
        PushButtonCreateNew->setObjectName("PushButtonCreateNew");
        PushButtonCreateNew->setGeometry(QRect(10, 64, 211, 61));
        PushButtonCreateNew->setFont(font);
        PushButtonCreateNew->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 180, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 180, 180, 255), stop:1 rgba(141, 100, 100, 255));\n"
"}"));
        PushButtonCreateNew->setCheckable(true);
        PushButtonCreateNew->setChecked(false);
        PushButtonCreateNew->setAutoExclusive(true);
        PushButtonCreateNew->setAutoDefault(false);
        PushButtonCreateNew->setFlat(false);
        PushButtonEdit = new QPushButton(frame);
        PushButtonEdit->setObjectName("PushButtonEdit");
        PushButtonEdit->setGeometry(QRect(10, 130, 211, 61));
        PushButtonEdit->setFont(font);
        PushButtonEdit->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 180, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 180, 180, 255), stop:1 rgba(141, 100, 100, 255));\n"
"}"));
        PushButtonEdit->setCheckable(true);
        PushButtonEdit->setChecked(false);
        PushButtonEdit->setAutoExclusive(true);
        PushButtonEdit->setAutoDefault(false);
        PushButtonEdit->setFlat(false);
        PushButtonSetExposure = new QPushButton(frame);
        PushButtonSetExposure->setObjectName("PushButtonSetExposure");
        PushButtonSetExposure->setGeometry(QRect(10, 0, 211, 61));
        PushButtonSetExposure->setFont(font);
        PushButtonSetExposure->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 180, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 180, 180, 255), stop:1 rgba(141, 100, 100, 255));\n"
"}"));
        PushButtonSetExposure->setCheckable(true);
        PushButtonSetExposure->setChecked(false);
        PushButtonSetExposure->setAutoExclusive(true);
        PushButtonSetExposure->setAutoDefault(false);
        PushButtonSetExposure->setFlat(false);

        retranslateUi(WizardMenuForm);

        stackedWidget->setCurrentIndex(0);
        stackedWidgetSenario->setCurrentIndex(1);
        PushButtonCreateNewNext1->setDefault(false);
        PushButtonCreateNewPrev1->setDefault(false);
        PushButtonCreateNewNext2->setDefault(false);
        PushButtonCreateNewPrev2->setDefault(false);
        PushButtonCreateNewSave->setDefault(false);
        PushButtonCreateNewAgain->setDefault(false);
        PushButtonCreateNewNext4->setDefault(false);
        PushButtonCreateNewPrev4->setDefault(false);
        stackedWidgetStory->setCurrentIndex(9);
        PushButtonAutoGenerate->setDefault(false);
        PushButtonSwitchPhase->setDefault(false);
        PushButtonCopyImage->setDefault(false);
        PushButtonEditDetail->setDefault(false);
        PushButtonSwitchPhaseNext->setDefault(false);
        PushButtonSwitchPhasePrev->setDefault(false);
        PushButtonSwitchPhaseNext2->setDefault(false);
        PushButtonSwitchPhasePrev2->setDefault(false);
        PushButtonReadDXFUpper->setDefault(false);
        PushButtonReadDXFLower->setDefault(false);
        PushButtonDXFReturn->setDefault(false);
        PushButtonDXFPrev->setDefault(false);
        DXFNext1->setDefault(false);
        DXFPrev1->setDefault(false);
        PushButtonDXFNext2->setDefault(false);
        PushButtonDXFNext3->setDefault(false);
        PushButtonDXFPrev3->setDefault(false);
        PushButtonMaskNext1->setDefault(false);
        PushButtonMaskPrev1->setDefault(false);
        PushButtonAlignmentNext->setDefault(false);
        PushButtonAlignmentPrev->setDefault(false);
        PushButtonInspectionNext1->setDefault(false);
        PushButtonInspectionPrev1->setDefault(false);
        PushButtonBladeNext1->setDefault(false);
        PushButtonBladePrev1->setDefault(false);
        PushButtonClose->setDefault(false);
        PushButtonLoadMaster->setDefault(false);
        PushButtonCreateNew->setDefault(false);
        PushButtonEdit->setDefault(false);
        PushButtonSetExposure->setDefault(false);


        QMetaObject::connectSlotsByName(WizardMenuForm);
    } // setupUi

    void retranslateUi(QWidget *WizardMenuForm)
    {
        WizardMenuForm->setWindowTitle(QCoreApplication::translate("WizardMenuForm", "\347\267\250\351\233\206\343\203\212\343\203\223\343\202\262\343\203\274\343\202\267\343\203\247\343\203\263", nullptr));
        textEdit->setHtml(QCoreApplication::translate("WizardMenuForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Yu Gothic UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\345\223\201\347\225\252\343\200\201</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\345\223\201\345\220\215\343\200\201</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin"
                        "-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\345\202\231\350\200\203\343\200\201</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\357\274\255\357\274\263 \357\274\260\346\230\216\346\234\235,serif'; font-size:14pt;\">\343\203\257\343\203\274\343\202\257\343\202\265\343\202\244\343\202\272</span><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\343\202\222</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\345\205\245\345\212\233\343\201\227\343\201\246\343\201\217\343\201\240\343\201\225\343\201\204\343\200\202</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-i"
                        "ndent:0px; font-family:'MS UI Gothic'; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\345\205\245\345\212\233\343\201\214\347\265\202\343\202\217\343\201\243\343\201\237\343\202\211\343\200\214\346\226\260\350\246\217\344\277\235\345\255\230\343\200\215\343\203\234\343\202\277\343\203\263\343\202\222\346\212\274\343\201\227\343\201\246\343\201\217\343\201\240\343\201\225\343\201\204\343\200\202</span></p></body></html>", nullptr));
        PushButtonCreateNewNext1->setText(QCoreApplication::translate("WizardMenuForm", "\346\254\241\343\201\253", nullptr));
        PushButtonCreateNewPrev1->setText(QCoreApplication::translate("WizardMenuForm", "\346\210\273\343\202\213", nullptr));
        textEdit_2->setHtml(QCoreApplication::translate("WizardMenuForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Yu Gothic UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\343\203\257\343\203\274\343\202\257\343\202\222\357\274\221\346\236\232\346\265\201\343\201\227\343\201\246\343\201\217\343\201\240\343\201\225\343\201\204\343\200\202</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family"
                        ":'MS UI Gothic'; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\346\222\256\345\275\261\345\256\214\344\272\206\343\201\247\350\207\252\345\213\225\347\224\237\346\210\220\343\201\227\343\201\276\343\201\231\343\200\202</span></p></body></html>", nullptr));
        PushButtonCreateNewNext2->setText(QCoreApplication::translate("WizardMenuForm", "\346\222\256\345\275\261\345\256\214\344\272\206", nullptr));
        PushButtonCreateNewPrev2->setText(QCoreApplication::translate("WizardMenuForm", "\346\210\273\343\202\213", nullptr));
        pushButtonSetTriggerPosition->setText(QCoreApplication::translate("WizardMenuForm", "\343\203\210\343\203\252\343\202\254\343\203\274\344\275\215\347\275\256\343\201\256\350\250\255\345\256\232", nullptr));
        PushButtonCreateNewSave->setText(QCoreApplication::translate("WizardMenuForm", "\344\277\235\345\255\230", nullptr));
        PushButtonCreateNewAgain->setText(QCoreApplication::translate("WizardMenuForm", "\345\206\215\346\222\256\345\275\261", nullptr));
        textEdit_3->setHtml(QCoreApplication::translate("WizardMenuForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Yu Gothic UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\343\201\223\343\201\256\345\220\215\347\247\260\343\201\247\344\277\235\345\255\230\343\201\227\343\201\276\343\201\231\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\344\277\235"
                        "\345\255\230\343\201\231\343\202\213\345\240\264\345\220\210\343\200\201\343\200\214\346\226\260\350\246\217\344\277\235\345\255\230\343\200\215\343\203\234\343\202\277\343\203\263\343\202\222\346\212\274\343\201\227\343\201\246\343\201\217\343\201\240\343\201\225\343\201\204\343\200\202</span></p></body></html>", nullptr));
        PushButtonCreateNewNext4->setText(QCoreApplication::translate("WizardMenuForm", "\346\254\241\343\201\253", nullptr));
        PushButtonCreateNewPrev4->setText(QCoreApplication::translate("WizardMenuForm", "\346\210\273\343\202\213", nullptr));
        PushButtonAutoGenerate->setText(QCoreApplication::translate("WizardMenuForm", "\350\207\252\345\213\225\347\224\237\346\210\220", nullptr));
        PushButtonSwitchPhase->setText(QCoreApplication::translate("WizardMenuForm", "\344\270\201\347\225\252\347\231\273\351\214\262", nullptr));
        PushButtonCopyImage->setText(QCoreApplication::translate("WizardMenuForm", "\347\224\273\345\203\217\345\205\245\346\233\277", nullptr));
        PushButtonEditDetail->setText(QCoreApplication::translate("WizardMenuForm", "\350\251\263\347\264\260\350\250\255\345\256\232", nullptr));
        textEdit_4->setHtml(QCoreApplication::translate("WizardMenuForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Yu Gothic UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\344\270\201\347\225\252\347\225\252\345\217\267\343\201\256\347\250\256\351\241\236\346\225\260\343\201\256\350\250\255\345\256\232\343\202\222\343\201\231\343\202\213\345\240\264\345\220\210\343\200\214\345\210\207\343\202\212\346\233\277\343\201\210\346\225\260\346\214\207\345\256\232\343\200\215\343\201\247\343\200\201\350\277\275\345"
                        "\212\240\346\225\260\343\202\222\345\205\245\345\212\233\343\201\227\343\201\246\343\201\217\343\201\240\343\201\225\343\201\204\343\200\202</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI Gothic'; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\343\201\202\343\202\213\343\201\204\343\201\257</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI Gothic'; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\346\222\256\345\275\261\343\202"
                        "\222\351\226\213\345\247\213\343\201\231\343\202\213\347\225\252\345\217\267\343\202\222\346\212\274\343\201\227\343\201\246\343\200\201\343\203\257\343\203\274\343\202\257\343\202\222\346\222\256\345\275\261\357\274\210\346\265\201\357\274\211\343\201\227\343\201\246\343\201\217\343\201\240\343\201\225\343\201\204\343\200\202</span></p></body></html>", nullptr));
        PushButtonSwitchPhaseNext->setText(QCoreApplication::translate("WizardMenuForm", "\346\254\241\343\201\253", nullptr));
        PushButtonSwitchPhasePrev->setText(QCoreApplication::translate("WizardMenuForm", "\346\210\273\343\202\213", nullptr));
        textEdit_12->setHtml(QCoreApplication::translate("WizardMenuForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Yu Gothic UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\344\270\201\347\225\252\347\225\252\345\217\267\351\203\250\345\210\206\343\202\222\343\200\201\345\220\204\351\235\242\343\201\224\343\201\250\343\201\256\347\224\273\345\203\217\343\201\253\343\203\236\343\203\274\343\202\257\351\240\230\345\237\237\343\202\222\350\250\255\345\256\232\343\201\227\343\201\246\343\201\217\343\201\240\343"
                        "\201\225\343\201\204\343\200\202</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI Gothic'; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\350\250\255\345\256\232\343\201\214\345\256\214\344\272\206\343\201\231\343\202\214\343\201\260\343\200\201\344\270\213\343\201\256\343\200\214\344\270\201\347\225\252\347\231\273\351\214\262\347\242\272\345\256\232\343\200\215\343\203\234\343\202\277\343\203\263\343\202\222\346\212\274\343\201\227\343\201\246\343\201\217\343\201\240\343\201\225\343\201\204\343\200\202</span></p></body></html>", nullptr));
        PushButtonSwitchPhaseNext2->setText(QCoreApplication::translate("WizardMenuForm", "\344\270\201\347\225\252\347\231\273\351\214\262\347\242\272\345\256\232", nullptr));
        PushButtonSwitchPhasePrev2->setText(QCoreApplication::translate("WizardMenuForm", "\346\210\273\343\202\213", nullptr));
        textEdit_5->setHtml(QCoreApplication::translate("WizardMenuForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Yu Gothic UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">CAD\343\203\207\343\203\274\343\202\277\343\202\222\350\252\255\343\201\277\350\276\274\343\201\277\343\201\276\343\201\231\343\200\202</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI Gothic'; font-size:14pt;\""
                        "><br /></p></body></html>", nullptr));
        PushButtonReadDXFUpper->setText(QCoreApplication::translate("WizardMenuForm", "\350\243\217\351\235\242DXF\350\252\255\350\276\274", nullptr));
        PushButtonReadDXFLower->setText(QCoreApplication::translate("WizardMenuForm", "\350\241\250\351\235\242DXF\350\252\255\350\276\274", nullptr));
        PushButtonDXFReturn->setText(QCoreApplication::translate("WizardMenuForm", "CAD\345\256\214\344\272\206", nullptr));
        PushButtonDXFPrev->setText(QCoreApplication::translate("WizardMenuForm", "\346\210\273\343\202\213", nullptr));
        textEdit_6->setHtml(QCoreApplication::translate("WizardMenuForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Yu Gothic UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:12pt;\">CAD\343\203\207\343\203\274\343\202\277\343\202\222\347\224\273\345\203\217\343\201\253\345\220\210\343\202\217\343\201\233\343\201\276\343\201\231\343\200\202</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI G"
                        "othic'; font-size:8pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic';\">\357\274\221\357\274\232\345\233\236\350\273\242\343\201\250\345\217\215\350\273\242\343\201\247\343\201\247\343\201\212\343\202\210\343\201\235\343\201\256\345\220\221\343\201\215\343\202\222\345\220\210\343\202\217\343\201\233\343\202\213</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI Gothic';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic';\">\357\274\222\357\274\232\347\270\246\343\203\273\346\250\252\345\217\215\350\273\242\343\201\247\350\241\250\350\243\217\343\202\222\345\220\210\343\202\217\343\201\233\343\201\276\343\201\231\343\200\201</sp"
                        "an></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI Gothic';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic';\">\357\274\223\357\274\232\344\274\270\347\270\256\343\201\247\343\200\201\347\270\246\344\274\270\347\270\256\343\203\234\343\202\277\343\203\263\343\202\222\357\274\221\345\233\236\346\212\274\343\201\231</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI Gothic';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic';\">\357\274\224\357\274\232\347\247\273\345\213\225\343\201\247\343\200\201\350\277\221"
                        "\343\201\204\344\275\215\347\275\256\343\201\253\347\247\273\345\213\225</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI Gothic';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic';\">\357\274\225\357\274\232\345\276\256\345\260\217\345\233\236\350\273\242\343\201\247\345\233\236\350\273\242\343\202\272\343\203\254\343\202\222\350\243\234\346\255\243</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI Gothic';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic';\">\357\274\226\357\274\232\346\234\200\347\265"
                        "\202\343\201\256\347\247\273\345\213\225\343\201\247\343\201\247\343\201\215\343\202\213\343\201\240\343\201\221\350\277\221\343\201\204\344\275\215\347\275\256\343\201\253\345\220\210\343\202\217\343\201\233\343\202\213</span></p></body></html>", nullptr));
        DXFNext1->setText(QCoreApplication::translate("WizardMenuForm", "\346\254\241", nullptr));
        DXFPrev1->setText(QCoreApplication::translate("WizardMenuForm", "\346\210\273\343\202\213", nullptr));
        textEdit_7->setHtml(QCoreApplication::translate("WizardMenuForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Yu Gothic UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\347\267\232\351\203\250\345\210\206\343\202\222\345\244\252\343\201\217\343\201\231\343\202\213\345\240\264\345\220\210\343\200\201\343\200\214\347\267\232\350\206\250\345\274\265\343\200\215</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text"
                        "-indent:0px; font-family:'MS UI Gothic'; font-size:14pt;\"><br /></p></body></html>", nullptr));
        PushButtonDXFNext2->setText(QCoreApplication::translate("WizardMenuForm", "\343\203\236\343\202\271\343\202\257\343\201\253\345\217\215\346\230\240", nullptr));
        PushButtonDXFNext3->setText(QCoreApplication::translate("WizardMenuForm", "\346\254\241", nullptr));
        PushButtonDXFPrev3->setText(QCoreApplication::translate("WizardMenuForm", "\346\210\273\343\202\213", nullptr));
        textEdit_14->setHtml(QCoreApplication::translate("WizardMenuForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Yu Gothic UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\347\267\232\351\203\250\345\210\206\343\202\222\345\244\252\343\201\217\343\201\231\343\202\213\345\240\264\345\220\210\343\200\201\343\200\214\347\267\232\350\206\250\345\274\265\343\200\215</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text"
                        "-indent:0px; font-family:'MS UI Gothic'; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\345\210\203\343\202\222\345\211\212\351\231\244\343\201\231\343\202\213\345\240\264\345\220\210\343\200\214\345\210\203\345\211\212\351\231\244\343\200\215</span></p></body></html>", nullptr));
        textEdit_8->setHtml(QCoreApplication::translate("WizardMenuForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Yu Gothic UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\343\203\236\343\202\271\343\202\257\347\224\237\346\210\220</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI Gothic'; font-size:14pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left"
                        ":0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:12pt;\">\346\234\211\345\212\271\351\240\230\345\237\237\343\201\256\346\212\275\345\207\272</span><span style=\" font-family:'MS UI Gothic'; font-size:11pt;\">\357\274\232\350\207\252\345\213\225\347\224\237\346\210\220</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI Gothic'; font-size:11pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:12pt;\">\346\234\211\345\212\271\351\240\230\345\237\237</span><span style=\" font-family:'MS UI Gothic'; font-size:11pt;\">\357\274\232\346\244\234\346\237\273\343\201\231\343\202\213\351\240\230\345\237\237</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin"
                        "-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:12pt;\">\347\204\241\345\212\271\351\240\230\345\237\237</span><span style=\" font-family:'MS UI Gothic'; font-size:11pt;\">\357\274\232\346\244\234\346\237\273\343\201\227\343\201\252\343\201\204</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI Gothic'; font-size:11pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:12pt;\">\351\231\220\345\256\232\351\240\230\345\237\237</span><span style=\" font-family:'MS UI Gothic'; font-size:11pt;\">\357\274\232\351\240\230\345\237\237\343\201\224\343\201\250\343\201\253\346\244\234\346\237\273\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\202\222\346\214\207\345\256\232</span></p>\n"
""
                        "<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI Gothic';\"><br /></p></body></html>", nullptr));
        PushButtonMaskNext1->setText(QCoreApplication::translate("WizardMenuForm", "\346\254\241", nullptr));
        PushButtonMaskPrev1->setText(QCoreApplication::translate("WizardMenuForm", "\346\210\273\343\202\213", nullptr));
        PushButtonAlignmentNext->setText(QCoreApplication::translate("WizardMenuForm", "\346\254\241", nullptr));
        textEdit_9->setHtml(QCoreApplication::translate("WizardMenuForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Yu Gothic UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\344\275\215\347\275\256\345\220\210\343\202\217\343\201\233\343\203\236\343\203\274\343\202\257\343\201\256\347\242\272\350\252\215</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI Gothic'; font-size:14pt;\"><"
                        "br /></p></body></html>", nullptr));
        PushButtonAlignmentPrev->setText(QCoreApplication::translate("WizardMenuForm", "\346\210\273\343\202\213", nullptr));
        PushButtonInspectionNext1->setText(QCoreApplication::translate("WizardMenuForm", "\346\254\241", nullptr));
        textEdit_10->setHtml(QCoreApplication::translate("WizardMenuForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Yu Gothic UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\346\244\234\346\237\273\351\240\230\345\237\237\343\201\256\347\242\272\350\252\215</span></p></body></html>", nullptr));
        PushButtonInspectionPrev1->setText(QCoreApplication::translate("WizardMenuForm", "\346\210\273\343\202\213", nullptr));
        PushButtonBladeNext1->setText(QCoreApplication::translate("WizardMenuForm", "\345\256\214\344\272\206/\344\277\235\345\255\230", nullptr));
        textEdit_11->setHtml(QCoreApplication::translate("WizardMenuForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Yu Gothic UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:14pt;\">\350\250\210\346\270\254\343\201\256\346\244\234\346\237\273</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI Gothic'; font-size:11pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left"
                        ":0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:11pt;\">\357\274\221\357\274\232\350\250\210\346\270\254\343\201\256\350\250\255\345\256\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:11pt;\">\343\200\200\343\200\200\350\250\255\345\256\232\345\276\214\343\201\253\343\200\214\350\207\252\345\213\225\347\224\237\346\210\220\343\200\215\343\203\234\343\202\277\343\203\263</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:11pt;\">\357\274\222\357\274\232\350\250\210\346\270\254\343\203\235\343\202\244\343\203\263\343\203\210\343\201\256\345\244\211\346\233\264</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-i"
                        "ndent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:11pt;\">\343\200\200\343\200\200\343\203\235\343\202\244\343\203\263\343\203\210\357\274\221\357\274\217\357\274\222\343\202\222\346\212\274\343\201\227\343\201\246\347\224\273\351\235\242\344\270\212\343\201\247\343\202\257\343\203\252\343\203\203\343\202\257</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:11pt;\">\357\274\223\357\274\232OK\345\237\272\346\272\226\345\200\244\343\201\256\350\250\255\345\256\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:11pt;\">\357\274\224\357\274\232\350\250\210\346\270\254\351\240\230\345\237\237\343\202\222\346\217\217\347\224\273</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; ma"
                        "rgin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:11pt;\">\343\200\200\343\200\200\343\200\200\350\250\210\346\270\254\351\235\242\343\201\253\345\215\260\345\210\267\343\201\214\343\201\202\343\202\213\345\240\264\345\220\210</span></p></body></html>", nullptr));
        PushButtonBladePrev1->setText(QCoreApplication::translate("WizardMenuForm", "\346\210\273\343\202\213", nullptr));
        textEdit_13->setHtml(QCoreApplication::translate("WizardMenuForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Yu Gothic UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:12pt;\">\350\250\210\346\270\254\343\201\256\346\244\234\346\237\273</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS UI Gothic'; font-size:10pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left"
                        ":0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:10pt;\">\357\274\221\357\274\232\343\200\214\357\274\213\343\200\215\343\201\256\347\267\250\351\233\206\343\203\234\343\202\277\343\203\263\343\201\256\346\231\202\343\200\201</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:10pt;\">\343\200\200\343\200\200\343\200\214\346\226\260\350\246\217\350\250\210\346\270\254\357\274\215\351\226\213\345\247\213\343\200\215\343\203\234\343\202\277\343\203\263\343\202\222</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:10pt;\">\343\200\200\343\200\200\346\212\274\343\201\227\343\201\246\343\200\201\350\250\210\346\270\254\343\201\256\345\247\213\347\202\271\343\201\250\347\265\202\347"
                        "\202\271</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:10pt;\">\343\200\200\343\200\200\343\202\222\343\202\257\343\203\252\343\203\203\343\202\257\343\201\227\343\201\276\343\201\231\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:10pt;\">\357\274\222\357\274\232\350\250\210\346\270\254\343\203\235\343\202\244\343\203\263\343\203\210\343\201\256\345\244\211\346\233\264</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:10pt;\">\343\200\200\343\200\200\343\203\235\343\202\244\343\203\263\343\203\210\357\274\221\357\274\217\357\274\222\343\202\222\346\212\274\343\201\227\343\201\246\347"
                        "\224\273\351\235\242\344\270\212</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:10pt;\">\343\200\200\343\200\200\343\201\247\343\202\257\343\203\252\343\203\203\343\202\257</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:10pt;\">\357\274\223\357\274\232OK\345\237\272\346\272\226\345\200\244\343\201\256\350\250\255\345\256\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:10pt;\">\343\200\200\343\200\200\344\270\212\351\231\220\345\200\244\343\200\201\344\270\213\351\231\220\345\200\244\343\202\222\350\250\255\345\256\232\343\201\227\343\201\246</span></p>\n"
"<p style=\" margin-top:0px; margi"
                        "n-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:10pt;\">\343\200\200\343\200\200\343\200\214\345\237\272\346\272\226\345\200\244\343\201\256\345\217\215\346\230\240\343\200\215\343\203\234\343\202\277\343\203\263\343\202\222\346\212\274\343\201\227</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:10pt;\">\343\200\200\343\200\200\343\201\276\343\201\231\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:10pt;\">\357\274\224\357\274\232\347\217\276\345\234\250\345\200\244\343\202\222\345\217\226\345\276\227</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0p"
                        "x;\"><span style=\" font-family:'MS UI Gothic'; font-size:10pt;\">\343\200\200\343\200\200\343\200\214\347\217\276\345\234\250\346\244\234\346\237\273\347\224\273\345\203\217\343\201\256\350\250\210\346\270\254\345\200\244\343\200\215</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS UI Gothic'; font-size:10pt;\">\343\200\200\343\200\200\343\203\234\343\202\277\343\203\263\343\202\222\346\212\274\343\201\227\343\201\276\343\201\231\343\200\202</span></p></body></html>", nullptr));
        PushButtonClose->setText(QCoreApplication::translate("WizardMenuForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        PushButtonLoadMaster->setText(QCoreApplication::translate("WizardMenuForm", "\343\203\207\343\203\274\343\202\277\350\252\255\350\276\274", nullptr));
        PushButtonCreateNew->setText(QCoreApplication::translate("WizardMenuForm", "\346\226\260\350\246\217\344\275\234\346\210\220", nullptr));
        PushButtonEdit->setText(QCoreApplication::translate("WizardMenuForm", "\343\203\207\343\203\274\343\202\277\347\267\250\351\233\206", nullptr));
        PushButtonSetExposure->setText(QCoreApplication::translate("WizardMenuForm", "\351\234\262\345\205\211\346\231\202\351\226\223", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WizardMenuForm: public Ui_WizardMenuForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIZARDMENUFORM_H
