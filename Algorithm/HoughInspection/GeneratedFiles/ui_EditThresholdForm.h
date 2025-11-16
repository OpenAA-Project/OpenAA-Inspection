/********************************************************************************
** Form generated from reading UI file 'EditThresholdForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITTHRESHOLDFORM_H
#define UI_EDITTHRESHOLDFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditThresholdForm
{
public:
    QFrame *frame_SimImage;
    QLabel *label_4;
    QLineEdit *EditItemName;
    QLineEdit *EditLibName;
    QLineEdit *EditLibID;
    QLabel *label_9;
    QLabel *label_5;
    QPushButton *pushButtonChangeLib;
    QPushButton *pushButtonTransmitItemNameAll;
    QFrame *frame;
    QLabel *label_6;
    QSpinBox *EditZoneWidth;
    QLabel *label_10;
    QLabel *label_12;
    QSpinBox *EditPickupL;
    QLabel *label_13;
    QSpinBox *EditPickupH;
    QLabel *label_14;
    QSpinBox *EditBinarizedLength;
    QSpinBox *EditMaxIsolation;
    QLabel *label_15;
    QCheckBox *checkBoxRemoveDynamicMask;
    QSpinBox *EditReducedSize;
    QLabel *label_29;
    QLabel *label_18;
    QLineEdit *EditZoneWidthMM;
    QLabel *label_19;
    QLineEdit *EditMaxIsolationMM;
    QCheckBox *checkBoxDynamicBinarize;
    QPushButton *ButtonReflectAllBlocks;
    QStackedWidget *stackedWidgetParts;
    QWidget *page;
    QPushButton *ButtonRelrectOnlyBlock;
    QWidget *page_3;
    QPushButton *ButtonRelrectSaveParts;
    QWidget *page_2;
    QPushButton *ButtonClose;
    QPushButton *ButtonLoadFromLibrary;
    QPushButton *ButtonSaveToLibrary;
    QPushButton *pushButtonSimShowCenterPos;
    QToolButton *toolButtonSimShowBright;
    QFrame *frame_2;
    QLabel *label_44;
    QLineEdit *EditMaxNGWidthMM;
    QSpinBox *EditNGLength;
    QLineEdit *EditMinPixelsMM;
    QLabel *label_2;
    QLabel *label_7;
    QLabel *label_17;
    QSpinBox *EditMaxLineCount;
    QLineEdit *EditMinNGWidthMM;
    QDoubleSpinBox *EditMaxNGWidth;
    QSpinBox *EditMinPixels;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_11;
    QLabel *label_45;
    QDoubleSpinBox *EditMinNGWidth;
    QLabel *label_16;
    QLabel *label_8;
    QLineEdit *EditNGLengthMM;
    QLabel *label_20;
    QLabel *label_46;
    QLineEdit *EditMinAverageContinuousMM;
    QSpinBox *EditMinAverageContinuous;

    void setupUi(QWidget *EditThresholdForm)
    {
        if (EditThresholdForm->objectName().isEmpty())
            EditThresholdForm->setObjectName("EditThresholdForm");
        EditThresholdForm->resize(402, 717);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EditThresholdForm->sizePolicy().hasHeightForWidth());
        EditThresholdForm->setSizePolicy(sizePolicy);
        EditThresholdForm->setMinimumSize(QSize(402, 717));
        EditThresholdForm->setMaximumSize(QSize(402, 717));
        frame_SimImage = new QFrame(EditThresholdForm);
        frame_SimImage->setObjectName("frame_SimImage");
        frame_SimImage->setGeometry(QRect(410, 60, 461, 641));
        frame_SimImage->setFrameShape(QFrame::StyledPanel);
        frame_SimImage->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(EditThresholdForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 70, 62, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditItemName = new QLineEdit(EditThresholdForm);
        EditItemName->setObjectName("EditItemName");
        EditItemName->setGeometry(QRect(20, 40, 141, 21));
        EditItemName->setReadOnly(false);
        EditLibName = new QLineEdit(EditThresholdForm);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(80, 90, 101, 21));
        EditLibName->setReadOnly(true);
        EditLibID = new QLineEdit(EditThresholdForm);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(20, 90, 61, 21));
        EditLibID->setReadOnly(true);
        label_9 = new QLabel(EditThresholdForm);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 20, 191, 20));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(EditThresholdForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(80, 70, 101, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonChangeLib = new QPushButton(EditThresholdForm);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(180, 90, 31, 23));
        pushButtonTransmitItemNameAll = new QPushButton(EditThresholdForm);
        pushButtonTransmitItemNameAll->setObjectName("pushButtonTransmitItemNameAll");
        pushButtonTransmitItemNameAll->setGeometry(QRect(160, 40, 51, 23));
        frame = new QFrame(EditThresholdForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 130, 381, 201));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 20, 101, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditZoneWidth = new QSpinBox(frame);
        EditZoneWidth->setObjectName("EditZoneWidth");
        EditZoneWidth->setGeometry(QRect(10, 40, 101, 22));
        EditZoneWidth->setMaximum(99999999);
        label_10 = new QLabel(frame);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(0, 0, 381, 20));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_12 = new QLabel(frame);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 100, 101, 20));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupL = new QSpinBox(frame);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(10, 120, 101, 22));
        EditPickupL->setMaximum(1000000);
        label_13 = new QLabel(frame);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(120, 100, 101, 20));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupH = new QSpinBox(frame);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(120, 120, 101, 22));
        EditPickupH->setMaximum(1000000);
        label_14 = new QLabel(frame);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(230, 20, 101, 20));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBinarizedLength = new QSpinBox(frame);
        EditBinarizedLength->setObjectName("EditBinarizedLength");
        EditBinarizedLength->setGeometry(QRect(230, 40, 101, 22));
        EditBinarizedLength->setMaximum(99999999);
        EditMaxIsolation = new QSpinBox(frame);
        EditMaxIsolation->setObjectName("EditMaxIsolation");
        EditMaxIsolation->setGeometry(QRect(120, 40, 101, 22));
        EditMaxIsolation->setMaximum(99999999);
        label_15 = new QLabel(frame);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(120, 20, 101, 20));
        label_15->setFrameShape(QFrame::Panel);
        label_15->setFrameShadow(QFrame::Sunken);
        label_15->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxRemoveDynamicMask = new QCheckBox(frame);
        checkBoxRemoveDynamicMask->setObjectName("checkBoxRemoveDynamicMask");
        checkBoxRemoveDynamicMask->setGeometry(QRect(210, 170, 161, 22));
        EditReducedSize = new QSpinBox(frame);
        EditReducedSize->setObjectName("EditReducedSize");
        EditReducedSize->setGeometry(QRect(130, 170, 71, 22));
        EditReducedSize->setMaximum(999999);
        label_29 = new QLabel(frame);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(10, 150, 191, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_18 = new QLabel(frame);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(90, 60, 31, 21));
        EditZoneWidthMM = new QLineEdit(frame);
        EditZoneWidthMM->setObjectName("EditZoneWidthMM");
        EditZoneWidthMM->setGeometry(QRect(10, 62, 81, 21));
        QPalette palette;
        QBrush brush(QColor(255, 255, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        EditZoneWidthMM->setPalette(palette);
        EditZoneWidthMM->setReadOnly(true);
        label_19 = new QLabel(frame);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(200, 60, 31, 21));
        EditMaxIsolationMM = new QLineEdit(frame);
        EditMaxIsolationMM->setObjectName("EditMaxIsolationMM");
        EditMaxIsolationMM->setGeometry(QRect(120, 62, 81, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        EditMaxIsolationMM->setPalette(palette1);
        EditMaxIsolationMM->setReadOnly(true);
        checkBoxDynamicBinarize = new QCheckBox(frame);
        checkBoxDynamicBinarize->setObjectName("checkBoxDynamicBinarize");
        checkBoxDynamicBinarize->setGeometry(QRect(230, 120, 151, 22));
        ButtonReflectAllBlocks = new QPushButton(EditThresholdForm);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(210, 560, 171, 41));
        ButtonReflectAllBlocks->setAcceptDrops(true);
        stackedWidgetParts = new QStackedWidget(EditThresholdForm);
        stackedWidgetParts->setObjectName("stackedWidgetParts");
        stackedWidgetParts->setGeometry(QRect(30, 560, 181, 41));
        page = new QWidget();
        page->setObjectName("page");
        ButtonRelrectOnlyBlock = new QPushButton(page);
        ButtonRelrectOnlyBlock->setObjectName("ButtonRelrectOnlyBlock");
        ButtonRelrectOnlyBlock->setGeometry(QRect(0, 0, 171, 41));
        ButtonRelrectOnlyBlock->setAcceptDrops(true);
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
        ButtonClose = new QPushButton(EditThresholdForm);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(120, 670, 171, 41));
        ButtonLoadFromLibrary = new QPushButton(EditThresholdForm);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(210, 610, 171, 41));
        ButtonLoadFromLibrary->setAcceptDrops(true);
        ButtonSaveToLibrary = new QPushButton(EditThresholdForm);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(30, 610, 171, 41));
        ButtonSaveToLibrary->setAcceptDrops(true);
        pushButtonSimShowCenterPos = new QPushButton(EditThresholdForm);
        pushButtonSimShowCenterPos->setObjectName("pushButtonSimShowCenterPos");
        pushButtonSimShowCenterPos->setGeometry(QRect(760, 10, 111, 41));
        toolButtonSimShowBright = new QToolButton(EditThresholdForm);
        toolButtonSimShowBright->setObjectName("toolButtonSimShowBright");
        toolButtonSimShowBright->setGeometry(QRect(580, 10, 141, 41));
        toolButtonSimShowBright->setCheckable(true);
        toolButtonSimShowBright->setChecked(true);
        frame_2 = new QFrame(EditThresholdForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 350, 381, 171));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_44 = new QLabel(frame_2);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(10, 100, 101, 21));
        label_44->setFrameShape(QFrame::Panel);
        label_44->setFrameShadow(QFrame::Sunken);
        label_44->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxNGWidthMM = new QLineEdit(frame_2);
        EditMaxNGWidthMM->setObjectName("EditMaxNGWidthMM");
        EditMaxNGWidthMM->setGeometry(QRect(130, 142, 81, 21));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        EditMaxNGWidthMM->setPalette(palette2);
        EditMaxNGWidthMM->setReadOnly(true);
        EditNGLength = new QSpinBox(frame_2);
        EditNGLength->setObjectName("EditNGLength");
        EditNGLength->setGeometry(QRect(10, 50, 101, 22));
        EditNGLength->setMaximum(99999999);
        EditMinPixelsMM = new QLineEdit(frame_2);
        EditMinPixelsMM->setObjectName("EditMinPixelsMM");
        EditMinPixelsMM->setGeometry(QRect(130, 72, 81, 21));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        EditMinPixelsMM->setPalette(palette3);
        EditMinPixelsMM->setReadOnly(true);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(210, 70, 41, 21));
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(130, 30, 101, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_17 = new QLabel(frame_2);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(210, 140, 31, 21));
        EditMaxLineCount = new QSpinBox(frame_2);
        EditMaxLineCount->setObjectName("EditMaxLineCount");
        EditMaxLineCount->setGeometry(QRect(270, 50, 101, 22));
        EditMaxLineCount->setMaximum(999999999);
        EditMinNGWidthMM = new QLineEdit(frame_2);
        EditMinNGWidthMM->setObjectName("EditMinNGWidthMM");
        EditMinNGWidthMM->setGeometry(QRect(10, 142, 81, 21));
        QPalette palette4;
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        EditMinNGWidthMM->setPalette(palette4);
        EditMinNGWidthMM->setReadOnly(true);
        EditMaxNGWidth = new QDoubleSpinBox(frame_2);
        EditMaxNGWidth->setObjectName("EditMaxNGWidth");
        EditMaxNGWidth->setGeometry(QRect(130, 120, 101, 22));
        EditMaxNGWidth->setMaximum(99999999.000000000000000);
        EditMinPixels = new QSpinBox(frame_2);
        EditMinPixels->setObjectName("EditMinPixels");
        EditMinPixels->setGeometry(QRect(130, 50, 101, 22));
        EditMinPixels->setMaximum(999999999);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(90, 140, 31, 21));
        label = new QLabel(frame_2);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 70, 31, 21));
        label_11 = new QLabel(frame_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(0, 0, 381, 20));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_45 = new QLabel(frame_2);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(130, 100, 101, 21));
        label_45->setFrameShape(QFrame::Panel);
        label_45->setFrameShadow(QFrame::Sunken);
        label_45->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinNGWidth = new QDoubleSpinBox(frame_2);
        EditMinNGWidth->setObjectName("EditMinNGWidth");
        EditMinNGWidth->setGeometry(QRect(10, 120, 101, 22));
        EditMinNGWidth->setMaximum(99999999.000000000000000);
        label_16 = new QLabel(frame_2);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(270, 30, 101, 20));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 30, 101, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNGLengthMM = new QLineEdit(frame_2);
        EditNGLengthMM->setObjectName("EditNGLengthMM");
        EditNGLengthMM->setGeometry(QRect(10, 72, 81, 21));
        QPalette palette5;
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette5.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        EditNGLengthMM->setPalette(palette5);
        EditNGLengthMM->setReadOnly(true);
        label_20 = new QLabel(frame_2);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(330, 138, 31, 21));
        label_46 = new QLabel(frame_2);
        label_46->setObjectName("label_46");
        label_46->setGeometry(QRect(250, 98, 121, 21));
        label_46->setFrameShape(QFrame::Panel);
        label_46->setFrameShadow(QFrame::Sunken);
        label_46->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinAverageContinuousMM = new QLineEdit(frame_2);
        EditMinAverageContinuousMM->setObjectName("EditMinAverageContinuousMM");
        EditMinAverageContinuousMM->setGeometry(QRect(250, 140, 81, 21));
        QPalette palette6;
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        EditMinAverageContinuousMM->setPalette(palette6);
        EditMinAverageContinuousMM->setReadOnly(true);
        EditMinAverageContinuous = new QSpinBox(frame_2);
        EditMinAverageContinuous->setObjectName("EditMinAverageContinuous");
        EditMinAverageContinuous->setGeometry(QRect(250, 120, 121, 22));
        EditMinAverageContinuous->setMaximum(999999999);

        retranslateUi(EditThresholdForm);

        stackedWidgetParts->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditThresholdForm);
    } // setupUi

    void retranslateUi(QWidget *EditThresholdForm)
    {
        EditThresholdForm->setWindowTitle(QCoreApplication::translate("EditThresholdForm", "Threshold HoughInspection", nullptr));
        label_4->setText(QCoreApplication::translate("EditThresholdForm", "Lib ID", nullptr));
        EditItemName->setText(QCoreApplication::translate("EditThresholdForm", "XXX", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditThresholdForm", "XXX", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditThresholdForm", "12345", nullptr));
        label_9->setText(QCoreApplication::translate("EditThresholdForm", "Item name", nullptr));
        label_5->setText(QCoreApplication::translate("EditThresholdForm", "Library name", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("EditThresholdForm", "...", nullptr));
        pushButtonTransmitItemNameAll->setText(QCoreApplication::translate("EditThresholdForm", "To all", nullptr));
        label_6->setText(QCoreApplication::translate("EditThresholdForm", "Line width", nullptr));
        label_10->setText(QCoreApplication::translate("EditThresholdForm", "Pickup", nullptr));
        label_12->setText(QCoreApplication::translate("EditThresholdForm", "Pickup Low", nullptr));
        label_13->setText(QCoreApplication::translate("EditThresholdForm", "Pickup high", nullptr));
        label_14->setText(QCoreApplication::translate("EditThresholdForm", "Binarized size", nullptr));
        label_15->setText(QCoreApplication::translate("EditThresholdForm", "Max isolation", nullptr));
        checkBoxRemoveDynamicMask->setText(QCoreApplication::translate("EditThresholdForm", "DynamicMask", nullptr));
        label_29->setText(QCoreApplication::translate("EditThresholdForm", "Reduced noise pixel area", nullptr));
        label_18->setText(QCoreApplication::translate("EditThresholdForm", "mm", nullptr));
        label_19->setText(QCoreApplication::translate("EditThresholdForm", "mm", nullptr));
        checkBoxDynamicBinarize->setText(QCoreApplication::translate("EditThresholdForm", "DynamicBinarize", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("EditThresholdForm", "Reflect all items", nullptr));
        ButtonRelrectOnlyBlock->setText(QCoreApplication::translate("EditThresholdForm", "Reflect only this", nullptr));
        ButtonRelrectSaveParts->setText(QCoreApplication::translate("EditThresholdForm", "\351\203\250\345\223\201\344\277\235\345\255\230", nullptr));
        ButtonClose->setText(QCoreApplication::translate("EditThresholdForm", "Close", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("EditThresholdForm", "Load from Library", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("EditThresholdForm", "Save to Library", nullptr));
        pushButtonSimShowCenterPos->setText(QCoreApplication::translate("EditThresholdForm", "\345\276\251\345\270\260", nullptr));
        toolButtonSimShowBright->setText(QCoreApplication::translate("EditThresholdForm", "\350\274\235\345\272\246NG", nullptr));
        label_44->setText(QCoreApplication::translate("EditThresholdForm", "Min NG width", nullptr));
        label_2->setText(QCoreApplication::translate("EditThresholdForm", "mm2", nullptr));
        label_7->setText(QCoreApplication::translate("EditThresholdForm", "NG pixels", nullptr));
        label_17->setText(QCoreApplication::translate("EditThresholdForm", "mm", nullptr));
        label_3->setText(QCoreApplication::translate("EditThresholdForm", "mm", nullptr));
        label->setText(QCoreApplication::translate("EditThresholdForm", "mm", nullptr));
        label_11->setText(QCoreApplication::translate("EditThresholdForm", "Judge", nullptr));
        label_45->setText(QCoreApplication::translate("EditThresholdForm", "Max NG width", nullptr));
        label_16->setText(QCoreApplication::translate("EditThresholdForm", "Max line count", nullptr));
        label_8->setText(QCoreApplication::translate("EditThresholdForm", "NG length", nullptr));
        label_20->setText(QCoreApplication::translate("EditThresholdForm", "mm", nullptr));
        label_46->setText(QCoreApplication::translate("EditThresholdForm", "Continuous dots", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditThresholdForm: public Ui_EditThresholdForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITTHRESHOLDFORM_H
