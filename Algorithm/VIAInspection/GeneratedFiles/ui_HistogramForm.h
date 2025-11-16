/********************************************************************************
** Form generated from reading UI file 'HistogramForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTOGRAMFORM_H
#define UI_HISTOGRAMFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HistogramForm
{
public:
    QPushButton *pushButtonChangeLib;
    QPushButton *pushButtonSimShowCenterPos;
    QFrame *frameLayer;
    QGroupBox *groupBox;
    QRadioButton *radioButtonDarkSide1;
    QRadioButton *radioButtonLightSide1;
    QLabel *label_4;
    QStackedWidget *stackedWidgetParts;
    QWidget *page;
    QPushButton *ButtonRelrectOnlyVIA;
    QWidget *page_3;
    QPushButton *ButtonRelrectSaveParts;
    QWidget *page_2;
    QLabel *label_39;
    QLineEdit *EditCenterBrightTarget;
    QFrame *frameLineGraph;
    QLabel *label_8;
    QPushButton *ButtonReflectAllVIAs;
    QListWidget *listWidgetHistList;
    QPushButton *ButtonSaveToLibrary;
    QLabel *label_38;
    QLabel *label_40;
    QFrame *frame_SimImage;
    QToolButton *toolButtonSimShowVIA;
    QPushButton *ButtonClose;
    QToolButton *toolButtonSimShowBright;
    QFrame *frameTarget;
    QLineEdit *EditLibName;
    QFrame *frameThreshold;
    QFrame *frame;
    QLabel *label_31;
    QLabel *label_29;
    QLabel *label;
    QLabel *label_30;
    QLabel *labelResultLight;
    QLabel *labelResultDark;
    QPushButton *ButtonCalc;
    QLabel *label_7;
    QLabel *label_5;
    QPushButton *ButtonLoadFromLibrary;
    QLineEdit *EditLibID;
    QLineEdit *EditCenterBrightMaster;
    QFrame *frame_6;
    QLabel *label_35;
    QLabel *label_20;
    QLabel *label_17;
    QSpinBox *EditOKDotH;
    QLabel *label_18;
    QSpinBox *EditBrightWidthL;
    QSpinBox *EditOKDotL;
    QSpinBox *EditBrightWidthH;
    QLabel *label_19;
    QLabel *label_32;
    QSpinBox *EditOKLengthL;
    QSpinBox *EditOKLengthH;
    QSpinBox *EditShrinkDot;
    QLabel *label_41;
    QLabel *label_51;
    QSpinBox *EditMaxNGDotL;
    QSpinBox *EditMaxNGDotH;
    QLabel *label_42;
    QSpinBox *EditEnlargeDot;

    void setupUi(QWidget *HistogramForm)
    {
        if (HistogramForm->objectName().isEmpty())
            HistogramForm->setObjectName("HistogramForm");
        HistogramForm->resize(1237, 722);
        pushButtonChangeLib = new QPushButton(HistogramForm);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(170, 460, 31, 23));
        pushButtonSimShowCenterPos = new QPushButton(HistogramForm);
        pushButtonSimShowCenterPos->setObjectName("pushButtonSimShowCenterPos");
        pushButtonSimShowCenterPos->setGeometry(QRect(1100, 20, 111, 41));
        frameLayer = new QFrame(HistogramForm);
        frameLayer->setObjectName("frameLayer");
        frameLayer->setGeometry(QRect(20, 400, 171, 41));
        frameLayer->setFrameShape(QFrame::NoFrame);
        frameLayer->setFrameShadow(QFrame::Plain);
        groupBox = new QGroupBox(HistogramForm);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 490, 181, 27));
        radioButtonDarkSide1 = new QRadioButton(groupBox);
        radioButtonDarkSide1->setObjectName("radioButtonDarkSide1");
        radioButtonDarkSide1->setGeometry(QRect(20, 4, 51, 18));
        radioButtonDarkSide1->setChecked(true);
        radioButtonLightSide1 = new QRadioButton(groupBox);
        radioButtonLightSide1->setObjectName("radioButtonLightSide1");
        radioButtonLightSide1->setGeometry(QRect(100, 4, 51, 18));
        radioButtonLightSide1->setChecked(false);
        label_4 = new QLabel(HistogramForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 440, 62, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        stackedWidgetParts = new QStackedWidget(HistogramForm);
        stackedWidgetParts->setObjectName("stackedWidgetParts");
        stackedWidgetParts->setGeometry(QRect(20, 600, 181, 41));
        page = new QWidget();
        page->setObjectName("page");
        ButtonRelrectOnlyVIA = new QPushButton(page);
        ButtonRelrectOnlyVIA->setObjectName("ButtonRelrectOnlyVIA");
        ButtonRelrectOnlyVIA->setGeometry(QRect(0, 0, 171, 41));
        ButtonRelrectOnlyVIA->setAcceptDrops(true);
        stackedWidgetParts->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        ButtonRelrectSaveParts = new QPushButton(page_3);
        ButtonRelrectSaveParts->setObjectName("ButtonRelrectSaveParts");
        ButtonRelrectSaveParts->setGeometry(QRect(0, 0, 171, 41));
        stackedWidgetParts->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidgetParts->addWidget(page_2);
        label_39 = new QLabel(HistogramForm);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(10, 540, 101, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditCenterBrightTarget = new QLineEdit(HistogramForm);
        EditCenterBrightTarget->setObjectName("EditCenterBrightTarget");
        EditCenterBrightTarget->setGeometry(QRect(120, 540, 61, 21));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(192, 192, 192, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        EditCenterBrightTarget->setPalette(palette);
        EditCenterBrightTarget->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        frameLineGraph = new QFrame(HistogramForm);
        frameLineGraph->setObjectName("frameLineGraph");
        frameLineGraph->setGeometry(QRect(0, 40, 731, 351));
        frameLineGraph->setFrameShape(QFrame::NoFrame);
        frameLineGraph->setFrameShadow(QFrame::Plain);
        label_8 = new QLabel(HistogramForm);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(510, 10, 131, 21));
        ButtonReflectAllVIAs = new QPushButton(HistogramForm);
        ButtonReflectAllVIAs->setObjectName("ButtonReflectAllVIAs");
        ButtonReflectAllVIAs->setGeometry(QRect(200, 600, 171, 41));
        ButtonReflectAllVIAs->setAcceptDrops(true);
        listWidgetHistList = new QListWidget(HistogramForm);
        listWidgetHistList->setObjectName("listWidgetHistList");
        listWidgetHistList->setGeometry(QRect(570, 610, 181, 91));
        ButtonSaveToLibrary = new QPushButton(HistogramForm);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(20, 650, 171, 41));
        ButtonSaveToLibrary->setAcceptDrops(true);
        label_38 = new QLabel(HistogramForm);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(10, 520, 101, 21));
        label_38->setFrameShape(QFrame::Panel);
        label_38->setFrameShadow(QFrame::Sunken);
        label_38->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_40 = new QLabel(HistogramForm);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(570, 590, 181, 21));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setFrameShadow(QFrame::Sunken);
        label_40->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_SimImage = new QFrame(HistogramForm);
        frame_SimImage->setObjectName("frame_SimImage");
        frame_SimImage->setGeometry(QRect(760, 60, 461, 641));
        frame_SimImage->setFrameShape(QFrame::StyledPanel);
        frame_SimImage->setFrameShadow(QFrame::Sunken);
        toolButtonSimShowVIA = new QToolButton(HistogramForm);
        toolButtonSimShowVIA->setObjectName("toolButtonSimShowVIA");
        toolButtonSimShowVIA->setGeometry(QRect(760, 20, 141, 41));
        toolButtonSimShowVIA->setCheckable(true);
        toolButtonSimShowVIA->setChecked(true);
        ButtonClose = new QPushButton(HistogramForm);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(380, 600, 171, 41));
        toolButtonSimShowBright = new QToolButton(HistogramForm);
        toolButtonSimShowBright->setObjectName("toolButtonSimShowBright");
        toolButtonSimShowBright->setGeometry(QRect(920, 20, 141, 41));
        toolButtonSimShowBright->setCheckable(true);
        toolButtonSimShowBright->setChecked(true);
        frameTarget = new QFrame(HistogramForm);
        frameTarget->setObjectName("frameTarget");
        frameTarget->setGeometry(QRect(320, 10, 21, 21));
        frameTarget->setFrameShape(QFrame::NoFrame);
        frameTarget->setFrameShadow(QFrame::Plain);
        EditLibName = new QLineEdit(HistogramForm);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(70, 460, 101, 21));
        EditLibName->setReadOnly(true);
        frameThreshold = new QFrame(HistogramForm);
        frameThreshold->setObjectName("frameThreshold");
        frameThreshold->setGeometry(QRect(480, 10, 21, 21));
        frameThreshold->setFrameShape(QFrame::NoFrame);
        frameThreshold->setFrameShadow(QFrame::Plain);
        frame = new QFrame(HistogramForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(560, 400, 181, 171));
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
        ButtonCalc->setAcceptDrops(true);
        label_7 = new QLabel(HistogramForm);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(350, 10, 131, 21));
        label_5 = new QLabel(HistogramForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(70, 440, 101, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLoadFromLibrary = new QPushButton(HistogramForm);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(200, 650, 171, 41));
        ButtonLoadFromLibrary->setAcceptDrops(true);
        EditLibID = new QLineEdit(HistogramForm);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(10, 460, 61, 21));
        EditLibID->setReadOnly(true);
        EditCenterBrightMaster = new QLineEdit(HistogramForm);
        EditCenterBrightMaster->setObjectName("EditCenterBrightMaster");
        EditCenterBrightMaster->setGeometry(QRect(120, 520, 61, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        EditCenterBrightMaster->setPalette(palette1);
        EditCenterBrightMaster->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        frame_6 = new QFrame(HistogramForm);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(200, 400, 351, 181));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Sunken);
        label_35 = new QLabel(frame_6);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(0, 0, 31, 181));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Raised);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_35->setIndent(1);
        label_20 = new QLabel(frame_6);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(260, 10, 81, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        label_20->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_17 = new QLabel(frame_6);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(40, 30, 121, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKDotH = new QSpinBox(frame_6);
        EditOKDotH->setObjectName("EditOKDotH");
        EditOKDotH->setGeometry(QRect(260, 50, 81, 22));
        EditOKDotH->setMaximum(99999999);
        label_18 = new QLabel(frame_6);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(40, 50, 121, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBrightWidthL = new QSpinBox(frame_6);
        EditBrightWidthL->setObjectName("EditBrightWidthL");
        EditBrightWidthL->setGeometry(QRect(170, 30, 81, 22));
        EditBrightWidthL->setMaximum(255);
        EditOKDotL = new QSpinBox(frame_6);
        EditOKDotL->setObjectName("EditOKDotL");
        EditOKDotL->setGeometry(QRect(170, 50, 81, 22));
        EditOKDotL->setMaximum(99999999);
        EditBrightWidthH = new QSpinBox(frame_6);
        EditBrightWidthH->setObjectName("EditBrightWidthH");
        EditBrightWidthH->setGeometry(QRect(260, 30, 81, 22));
        EditBrightWidthH->setMaximum(255);
        label_19 = new QLabel(frame_6);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(170, 10, 81, 21));
        label_19->setFrameShape(QFrame::Panel);
        label_19->setFrameShadow(QFrame::Sunken);
        label_19->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_32 = new QLabel(frame_6);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(40, 70, 121, 21));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKLengthL = new QSpinBox(frame_6);
        EditOKLengthL->setObjectName("EditOKLengthL");
        EditOKLengthL->setGeometry(QRect(170, 70, 81, 22));
        EditOKLengthL->setMaximum(99999999);
        EditOKLengthH = new QSpinBox(frame_6);
        EditOKLengthH->setObjectName("EditOKLengthH");
        EditOKLengthH->setGeometry(QRect(260, 70, 81, 22));
        EditOKLengthH->setMaximum(99999999);
        EditShrinkDot = new QSpinBox(frame_6);
        EditShrinkDot->setObjectName("EditShrinkDot");
        EditShrinkDot->setGeometry(QRect(210, 132, 81, 22));
        EditShrinkDot->setMaximum(99999999);
        label_41 = new QLabel(frame_6);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(40, 130, 121, 21));
        label_41->setFrameShape(QFrame::Panel);
        label_41->setFrameShadow(QFrame::Sunken);
        label_41->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_51 = new QLabel(frame_6);
        label_51->setObjectName("label_51");
        label_51->setGeometry(QRect(40, 92, 121, 21));
        label_51->setFrameShape(QFrame::Panel);
        label_51->setFrameShadow(QFrame::Sunken);
        label_51->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxNGDotL = new QSpinBox(frame_6);
        EditMaxNGDotL->setObjectName("EditMaxNGDotL");
        EditMaxNGDotL->setGeometry(QRect(170, 92, 81, 22));
        EditMaxNGDotL->setMaximum(99999999);
        EditMaxNGDotH = new QSpinBox(frame_6);
        EditMaxNGDotH->setObjectName("EditMaxNGDotH");
        EditMaxNGDotH->setGeometry(QRect(260, 92, 81, 22));
        EditMaxNGDotH->setMaximum(99999999);
        label_42 = new QLabel(frame_6);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(40, 152, 121, 21));
        label_42->setFrameShape(QFrame::Panel);
        label_42->setFrameShadow(QFrame::Sunken);
        label_42->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditEnlargeDot = new QSpinBox(frame_6);
        EditEnlargeDot->setObjectName("EditEnlargeDot");
        EditEnlargeDot->setGeometry(QRect(210, 152, 81, 22));
        EditEnlargeDot->setMaximum(99999999);

        retranslateUi(HistogramForm);

        stackedWidgetParts->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(HistogramForm);
    } // setupUi

    void retranslateUi(QWidget *HistogramForm)
    {
        HistogramForm->setWindowTitle(QCoreApplication::translate("HistogramForm", "Threshold VIAInspection", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("HistogramForm", "...", nullptr));
        pushButtonSimShowCenterPos->setText(QCoreApplication::translate("HistogramForm", "\345\276\251\345\270\260", nullptr));
        radioButtonDarkSide1->setText(QCoreApplication::translate("HistogramForm", "Dark", nullptr));
        radioButtonLightSide1->setText(QCoreApplication::translate("HistogramForm", "Light", nullptr));
        label_4->setText(QCoreApplication::translate("HistogramForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        ButtonRelrectOnlyVIA->setText(QCoreApplication::translate("HistogramForm", "\343\201\223\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonRelrectSaveParts->setText(QCoreApplication::translate("HistogramForm", "\351\203\250\345\223\201\344\277\235\345\255\230", nullptr));
        label_39->setText(QCoreApplication::translate("HistogramForm", "Target\344\270\255\345\277\203\350\274\235\345\272\246", nullptr));
        label_8->setText(QCoreApplication::translate("HistogramForm", "\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        ButtonReflectAllVIAs->setText(QCoreApplication::translate("HistogramForm", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("HistogramForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        label_38->setText(QCoreApplication::translate("HistogramForm", "\343\203\236\343\202\271\343\202\277\343\203\274\344\270\255\345\277\203\350\274\235\345\272\246", nullptr));
        label_40->setText(QCoreApplication::translate("HistogramForm", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\343\203\220\343\203\251\343\201\244\343\201\215\343\202\260\343\203\251\343\203\225", nullptr));
        toolButtonSimShowVIA->setText(QCoreApplication::translate("HistogramForm", "Block", nullptr));
        ButtonClose->setText(QCoreApplication::translate("HistogramForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        toolButtonSimShowBright->setText(QCoreApplication::translate("HistogramForm", "\350\274\235\345\272\246NG", nullptr));
        EditLibName->setText(QCoreApplication::translate("HistogramForm", "XXX", nullptr));
        label_31->setText(QCoreApplication::translate("HistogramForm", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\345\210\244\345\256\232\347\265\220\346\236\234", nullptr));
        label_29->setText(QCoreApplication::translate("HistogramForm", "\346\230\216\345\201\264", nullptr));
        label->setText(QCoreApplication::translate("HistogramForm", "\345\210\244\345\256\232", nullptr));
        label_30->setText(QCoreApplication::translate("HistogramForm", "\346\232\227\345\201\264", nullptr));
        labelResultLight->setText(QCoreApplication::translate("HistogramForm", "123", nullptr));
        labelResultDark->setText(QCoreApplication::translate("HistogramForm", "123", nullptr));
        ButtonCalc->setText(QCoreApplication::translate("HistogramForm", "\350\250\210\347\256\227", nullptr));
        label_7->setText(QCoreApplication::translate("HistogramForm", "\346\244\234\346\237\273\347\224\273\345\203\217", nullptr));
        label_5->setText(QCoreApplication::translate("HistogramForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("HistogramForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        EditLibID->setText(QCoreApplication::translate("HistogramForm", "12345", nullptr));
        label_35->setText(QCoreApplication::translate("HistogramForm", "\346\244\234\346\237\273", nullptr));
        label_20->setText(QCoreApplication::translate("HistogramForm", "\346\230\216\345\201\264", nullptr));
        label_17->setText(QCoreApplication::translate("HistogramForm", "OK\350\274\235\345\272\246\347\257\204\345\233\262", nullptr));
        label_18->setText(QCoreApplication::translate("HistogramForm", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_19->setText(QCoreApplication::translate("HistogramForm", "\346\232\227\345\201\264", nullptr));
        label_32->setText(QCoreApplication::translate("HistogramForm", "\343\201\223\343\202\214\344\273\245\344\270\212\343\201\256\351\225\267\343\201\225\343\201\247\357\274\256\357\274\247", nullptr));
        label_41->setText(QCoreApplication::translate("HistogramForm", "\345\217\216\347\270\256\343\203\211\343\203\203\343\203\210", nullptr));
        label_51->setText(QCoreApplication::translate("HistogramForm", "\346\234\200\345\244\247NG\351\235\242\347\251\215", nullptr));
        label_42->setText(QCoreApplication::translate("HistogramForm", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HistogramForm: public Ui_HistogramForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTOGRAMFORM_H
