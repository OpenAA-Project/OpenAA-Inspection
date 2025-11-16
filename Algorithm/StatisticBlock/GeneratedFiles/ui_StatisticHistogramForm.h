/********************************************************************************
** Form generated from reading UI file 'StatisticHistogramForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTICHISTOGRAMFORM_H
#define UI_STATISTICHISTOGRAMFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatisticHistogramFormClass
{
public:
    QTabWidget *tabWidgetInspect;
    QWidget *tab_5;
    QSpinBox *EditOKDotL;
    QSpinBox *EditOKDotH;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QSpinBox *EditOKLengthL;
    QLabel *label_32;
    QSpinBox *EditOKLengthH;
    QLineEdit *EditBrightWidthL;
    QLineEdit *EditBrightWidthH;
    QWidget *tab;
    QLabel *label_28;
    QCheckBox *checkEliminateAcnode;
    QSpinBox *EditErosionDotCount;
    QLabel *label_27;
    QCheckBox *checkUseMorphology;
    QSpinBox *EditDilationDotCount;
    QComboBox *comboBoxMorphologyApplyTo;
    QWidget *tab_7;
    QCheckBox *checkBModeEnabled;
    QCheckBox *checkBModeAbsoluteBright;
    QCheckBox *checkBModeNGCluster;
    QCheckBox *checkBModeWhiteMask;
    QCheckBox *checkBModeBlackMask;
    QWidget *tab_8;
    QLabel *label_26;
    QLabel *label_25;
    QSpinBox *EditAdjustWhite;
    QSpinBox *EditAdjustBlack;
    QLabel *label_5;
    QLabel *label_4;
    QGroupBox *groupBox;
    QRadioButton *radioButtonDarkSide1;
    QRadioButton *radioButtonLightSide1;
    QLineEdit *EditLibID;
    QLabel *label_3;
    QFrame *frame;
    QLabel *label_31;
    QLabel *label_29;
    QLabel *label;
    QLabel *label_30;
    QLabel *labelResultLight;
    QLabel *labelResultDark;
    QPushButton *ButtonCalc;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *pushButtonChangeLib;
    QFrame *frameLineGraph;
    QFrame *frameLayer;
    QLineEdit *EditLibName;
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
    QFrame *frameTarget;
    QFrame *frameThreshold;
    QFrame *frameMaster;
    QLineEdit *EditAvr;
    QLineEdit *EditSigma;
    QLabel *label_21;
    QLabel *label_22;

    void setupUi(QWidget *StatisticHistogramFormClass)
    {
        if (StatisticHistogramFormClass->objectName().isEmpty())
            StatisticHistogramFormClass->setObjectName("StatisticHistogramFormClass");
        StatisticHistogramFormClass->resize(768, 623);
        tabWidgetInspect = new QTabWidget(StatisticHistogramFormClass);
        tabWidgetInspect->setObjectName("tabWidgetInspect");
        tabWidgetInspect->setGeometry(QRect(240, 410, 321, 121));
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        EditOKDotL = new QSpinBox(tab_5);
        EditOKDotL->setObjectName("EditOKDotL");
        EditOKDotL->setGeometry(QRect(140, 50, 81, 22));
        EditOKDotL->setMaximum(99999999);
        EditOKDotH = new QSpinBox(tab_5);
        EditOKDotH->setObjectName("EditOKDotH");
        EditOKDotH->setGeometry(QRect(230, 50, 81, 22));
        EditOKDotH->setMaximum(99999999);
        label_17 = new QLabel(tab_5);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(10, 30, 121, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_18 = new QLabel(tab_5);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(10, 50, 121, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_19 = new QLabel(tab_5);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(140, 10, 81, 21));
        label_19->setFrameShape(QFrame::Panel);
        label_19->setFrameShadow(QFrame::Sunken);
        label_19->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_20 = new QLabel(tab_5);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(230, 10, 81, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        label_20->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKLengthL = new QSpinBox(tab_5);
        EditOKLengthL->setObjectName("EditOKLengthL");
        EditOKLengthL->setGeometry(QRect(140, 70, 81, 22));
        EditOKLengthL->setMaximum(99999999);
        label_32 = new QLabel(tab_5);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(10, 70, 121, 21));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKLengthH = new QSpinBox(tab_5);
        EditOKLengthH->setObjectName("EditOKLengthH");
        EditOKLengthH->setGeometry(QRect(230, 70, 81, 22));
        EditOKLengthH->setMaximum(99999999);
        EditBrightWidthL = new QLineEdit(tab_5);
        EditBrightWidthL->setObjectName("EditBrightWidthL");
        EditBrightWidthL->setGeometry(QRect(140, 30, 81, 20));
        EditBrightWidthH = new QLineEdit(tab_5);
        EditBrightWidthH->setObjectName("EditBrightWidthH");
        EditBrightWidthH->setGeometry(QRect(230, 30, 81, 20));
        tabWidgetInspect->addTab(tab_5, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        label_28 = new QLabel(tab);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(30, 70, 211, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkEliminateAcnode = new QCheckBox(tab);
        checkEliminateAcnode->setObjectName("checkEliminateAcnode");
        checkEliminateAcnode->setEnabled(false);
        checkEliminateAcnode->setGeometry(QRect(30, 30, 121, 18));
        EditErosionDotCount = new QSpinBox(tab);
        EditErosionDotCount->setObjectName("EditErosionDotCount");
        EditErosionDotCount->setEnabled(false);
        EditErosionDotCount->setGeometry(QRect(250, 70, 61, 22));
        EditErosionDotCount->setMaximum(255);
        label_27 = new QLabel(tab);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(30, 50, 211, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkUseMorphology = new QCheckBox(tab);
        checkUseMorphology->setObjectName("checkUseMorphology");
        checkUseMorphology->setGeometry(QRect(10, 10, 141, 20));
        EditDilationDotCount = new QSpinBox(tab);
        EditDilationDotCount->setObjectName("EditDilationDotCount");
        EditDilationDotCount->setEnabled(false);
        EditDilationDotCount->setGeometry(QRect(250, 50, 61, 22));
        EditDilationDotCount->setMaximum(255);
        comboBoxMorphologyApplyTo = new QComboBox(tab);
        comboBoxMorphologyApplyTo->addItem(QString());
        comboBoxMorphologyApplyTo->addItem(QString());
        comboBoxMorphologyApplyTo->addItem(QString());
        comboBoxMorphologyApplyTo->setObjectName("comboBoxMorphologyApplyTo");
        comboBoxMorphologyApplyTo->setEnabled(false);
        comboBoxMorphologyApplyTo->setGeometry(QRect(170, 10, 141, 22));
        tabWidgetInspect->addTab(tab, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        checkBModeEnabled = new QCheckBox(tab_7);
        checkBModeEnabled->setObjectName("checkBModeEnabled");
        checkBModeEnabled->setGeometry(QRect(10, 10, 141, 18));
        checkBModeAbsoluteBright = new QCheckBox(tab_7);
        checkBModeAbsoluteBright->setObjectName("checkBModeAbsoluteBright");
        checkBModeAbsoluteBright->setGeometry(QRect(10, 30, 141, 18));
        checkBModeNGCluster = new QCheckBox(tab_7);
        checkBModeNGCluster->setObjectName("checkBModeNGCluster");
        checkBModeNGCluster->setGeometry(QRect(10, 50, 141, 18));
        checkBModeWhiteMask = new QCheckBox(tab_7);
        checkBModeWhiteMask->setObjectName("checkBModeWhiteMask");
        checkBModeWhiteMask->setGeometry(QRect(160, 30, 141, 18));
        checkBModeBlackMask = new QCheckBox(tab_7);
        checkBModeBlackMask->setObjectName("checkBModeBlackMask");
        checkBModeBlackMask->setGeometry(QRect(160, 50, 141, 18));
        tabWidgetInspect->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        label_26 = new QLabel(tab_8);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(10, 70, 201, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_25 = new QLabel(tab_8);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(10, 40, 201, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditAdjustWhite = new QSpinBox(tab_8);
        EditAdjustWhite->setObjectName("EditAdjustWhite");
        EditAdjustWhite->setGeometry(QRect(220, 70, 81, 22));
        EditAdjustWhite->setMaximum(255);
        EditAdjustBlack = new QSpinBox(tab_8);
        EditAdjustBlack->setObjectName("EditAdjustBlack");
        EditAdjustBlack->setGeometry(QRect(220, 40, 81, 22));
        EditAdjustBlack->setMaximum(255);
        tabWidgetInspect->addTab(tab_8, QString());
        label_5 = new QLabel(StatisticHistogramFormClass);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(80, 450, 101, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(StatisticHistogramFormClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 450, 62, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox = new QGroupBox(StatisticHistogramFormClass);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 500, 181, 31));
        radioButtonDarkSide1 = new QRadioButton(groupBox);
        radioButtonDarkSide1->setObjectName("radioButtonDarkSide1");
        radioButtonDarkSide1->setGeometry(QRect(20, 4, 51, 18));
        radioButtonDarkSide1->setChecked(true);
        radioButtonLightSide1 = new QRadioButton(groupBox);
        radioButtonLightSide1->setObjectName("radioButtonLightSide1");
        radioButtonLightSide1->setGeometry(QRect(100, 4, 51, 18));
        radioButtonLightSide1->setChecked(false);
        EditLibID = new QLineEdit(StatisticHistogramFormClass);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setEnabled(false);
        EditLibID->setGeometry(QRect(20, 470, 61, 21));
        EditLibID->setReadOnly(true);
        label_3 = new QLabel(StatisticHistogramFormClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(180, 10, 131, 21));
        frame = new QFrame(StatisticHistogramFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(570, 410, 181, 161));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_31 = new QLabel(frame);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(0, 0, 181, 21));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_29 = new QLabel(frame);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(120, 30, 51, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 60, 61, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_30 = new QLabel(frame);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(70, 30, 51, 21));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelResultLight = new QLabel(frame);
        labelResultLight->setObjectName("labelResultLight");
        labelResultLight->setGeometry(QRect(120, 60, 51, 21));
        labelResultLight->setFrameShape(QFrame::Panel);
        labelResultLight->setFrameShadow(QFrame::Sunken);
        labelResultLight->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelResultDark = new QLabel(frame);
        labelResultDark->setObjectName("labelResultDark");
        labelResultDark->setGeometry(QRect(70, 60, 51, 21));
        labelResultDark->setFrameShape(QFrame::Panel);
        labelResultDark->setFrameShadow(QFrame::Sunken);
        labelResultDark->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonCalc = new QPushButton(frame);
        ButtonCalc->setObjectName("ButtonCalc");
        ButtonCalc->setGeometry(QRect(10, 130, 161, 31));
        label_7 = new QLabel(StatisticHistogramFormClass);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(350, 10, 131, 21));
        label_8 = new QLabel(StatisticHistogramFormClass);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(510, 10, 131, 21));
        pushButtonChangeLib = new QPushButton(StatisticHistogramFormClass);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(180, 470, 31, 23));
        frameLineGraph = new QFrame(StatisticHistogramFormClass);
        frameLineGraph->setObjectName("frameLineGraph");
        frameLineGraph->setGeometry(QRect(20, 40, 731, 321));
        frameLineGraph->setFrameShape(QFrame::NoFrame);
        frameLineGraph->setFrameShadow(QFrame::Plain);
        frameLayer = new QFrame(StatisticHistogramFormClass);
        frameLayer->setObjectName("frameLayer");
        frameLayer->setGeometry(QRect(30, 410, 171, 41));
        frameLayer->setFrameShape(QFrame::NoFrame);
        frameLayer->setFrameShadow(QFrame::Plain);
        EditLibName = new QLineEdit(StatisticHistogramFormClass);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setEnabled(false);
        EditLibName->setGeometry(QRect(80, 470, 101, 21));
        EditLibName->setReadOnly(true);
        ButtonLoadFromLibrary = new QPushButton(StatisticHistogramFormClass);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(200, 580, 171, 31));
        ButtonSaveToLibrary = new QPushButton(StatisticHistogramFormClass);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(20, 580, 171, 31));
        ButtonReflectAllBlocks = new QPushButton(StatisticHistogramFormClass);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(200, 540, 171, 31));
        stackedWidgetParts = new QStackedWidget(StatisticHistogramFormClass);
        stackedWidgetParts->setObjectName("stackedWidgetParts");
        stackedWidgetParts->setGeometry(QRect(20, 540, 181, 31));
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
        ButtonClose = new QPushButton(StatisticHistogramFormClass);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(380, 540, 171, 31));
        frameTarget = new QFrame(StatisticHistogramFormClass);
        frameTarget->setObjectName("frameTarget");
        frameTarget->setGeometry(QRect(320, 10, 21, 21));
        frameTarget->setFrameShape(QFrame::NoFrame);
        frameTarget->setFrameShadow(QFrame::Plain);
        frameThreshold = new QFrame(StatisticHistogramFormClass);
        frameThreshold->setObjectName("frameThreshold");
        frameThreshold->setGeometry(QRect(480, 10, 21, 21));
        frameThreshold->setFrameShape(QFrame::NoFrame);
        frameThreshold->setFrameShadow(QFrame::Plain);
        frameMaster = new QFrame(StatisticHistogramFormClass);
        frameMaster->setObjectName("frameMaster");
        frameMaster->setGeometry(QRect(150, 10, 21, 21));
        frameMaster->setFrameShape(QFrame::NoFrame);
        frameMaster->setFrameShadow(QFrame::Plain);
        EditAvr = new QLineEdit(StatisticHistogramFormClass);
        EditAvr->setObjectName("EditAvr");
        EditAvr->setEnabled(false);
        EditAvr->setGeometry(QRect(380, 390, 81, 20));
        EditAvr->setReadOnly(true);
        EditSigma = new QLineEdit(StatisticHistogramFormClass);
        EditSigma->setObjectName("EditSigma");
        EditSigma->setEnabled(false);
        EditSigma->setGeometry(QRect(470, 390, 81, 20));
        EditSigma->setReadOnly(true);
        label_21 = new QLabel(StatisticHistogramFormClass);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(380, 370, 81, 21));
        label_21->setFrameShape(QFrame::Panel);
        label_21->setFrameShadow(QFrame::Sunken);
        label_21->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_22 = new QLabel(StatisticHistogramFormClass);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(470, 370, 81, 21));
        label_22->setFrameShape(QFrame::Panel);
        label_22->setFrameShadow(QFrame::Sunken);
        label_22->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(StatisticHistogramFormClass);

        tabWidgetInspect->setCurrentIndex(0);
        stackedWidgetParts->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(StatisticHistogramFormClass);
    } // setupUi

    void retranslateUi(QWidget *StatisticHistogramFormClass)
    {
        StatisticHistogramFormClass->setWindowTitle(QCoreApplication::translate("StatisticHistogramFormClass", "StatisticHistogramForm", nullptr));
        label_17->setText(QCoreApplication::translate("StatisticHistogramFormClass", "OK\350\274\235\345\272\246\347\257\204\345\233\262", nullptr));
        label_18->setText(QCoreApplication::translate("StatisticHistogramFormClass", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_19->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\346\232\227\345\201\264", nullptr));
        label_20->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\346\230\216\345\201\264", nullptr));
        label_32->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\343\201\223\343\202\214\344\273\245\344\270\212\343\201\256\351\225\267\343\201\225\343\201\247\357\274\256\357\274\247", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_5), QCoreApplication::translate("StatisticHistogramFormClass", "\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        label_28->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\345\217\216\347\270\256\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        checkEliminateAcnode->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\345\255\244\347\253\213\347\202\271\343\201\256\351\231\244\345\216\273", nullptr));
        label_27->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        checkUseMorphology->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\350\206\250\345\274\265\343\203\273\345\217\216\347\270\256\343\202\222\343\201\231\343\202\213", nullptr));
        comboBoxMorphologyApplyTo->setItemText(0, QCoreApplication::translate("StatisticHistogramFormClass", "\346\232\227\345\201\264\343\203\273\346\230\216\345\201\264\344\270\241\346\226\271", nullptr));
        comboBoxMorphologyApplyTo->setItemText(1, QCoreApplication::translate("StatisticHistogramFormClass", "\346\232\227\345\201\264\343\201\256\343\201\277", nullptr));
        comboBoxMorphologyApplyTo->setItemText(2, QCoreApplication::translate("StatisticHistogramFormClass", "\346\230\216\345\201\264\343\201\256\343\201\277", nullptr));

        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab), QCoreApplication::translate("StatisticHistogramFormClass", "\350\206\250\345\274\265\343\203\273\345\217\216\347\270\256", nullptr));
        checkBModeEnabled->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\346\244\234\346\237\273\346\234\211\345\212\271", nullptr));
        checkBModeAbsoluteBright->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\347\265\266\345\257\276\350\274\235\345\272\246", nullptr));
        checkBModeNGCluster->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\345\241\212\346\244\234\346\237\273", nullptr));
        checkBModeWhiteMask->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\347\231\275\343\203\236\343\202\271\343\202\257", nullptr));
        checkBModeBlackMask->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\351\273\222\343\203\236\343\202\271\343\202\257", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_7), QCoreApplication::translate("StatisticHistogramFormClass", "\345\261\236\346\200\247", nullptr));
        label_26->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_25->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_8), QCoreApplication::translate("StatisticHistogramFormClass", "\350\243\234\346\255\243", nullptr));
        label_5->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        label_4->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        radioButtonDarkSide1->setText(QCoreApplication::translate("StatisticHistogramFormClass", "Dark", nullptr));
        radioButtonLightSide1->setText(QCoreApplication::translate("StatisticHistogramFormClass", "Light", nullptr));
        EditLibID->setText(QCoreApplication::translate("StatisticHistogramFormClass", "12345", nullptr));
        label_3->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217", nullptr));
        label_31->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\351\201\270\346\212\236\343\203\226\343\203\255\343\203\203\343\202\257\343\201\256\344\272\214\345\200\244\345\214\226\345\276\214\346\203\205\345\240\261", nullptr));
        label_29->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\346\230\216\345\201\264", nullptr));
        label->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_30->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\346\232\227\345\201\264", nullptr));
        labelResultLight->setText(QCoreApplication::translate("StatisticHistogramFormClass", "123", nullptr));
        labelResultDark->setText(QCoreApplication::translate("StatisticHistogramFormClass", "123", nullptr));
        ButtonCalc->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\350\250\210\347\256\227", nullptr));
        label_7->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\346\244\234\346\237\273\347\224\273\345\203\217", nullptr));
        label_8->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("StatisticHistogramFormClass", "...", nullptr));
        EditLibName->setText(QCoreApplication::translate("StatisticHistogramFormClass", "XXX", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonRelrectOnlyBlock->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\343\201\223\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonRelrectSaveParts->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\351\203\250\345\223\201\344\277\235\345\255\230", nullptr));
        ButtonClose->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_21->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\345\271\263\345\235\207\345\200\244", nullptr));
        label_22->setText(QCoreApplication::translate("StatisticHistogramFormClass", "\346\250\231\346\272\226\345\201\217\345\267\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatisticHistogramFormClass: public Ui_StatisticHistogramFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTICHISTOGRAMFORM_H
