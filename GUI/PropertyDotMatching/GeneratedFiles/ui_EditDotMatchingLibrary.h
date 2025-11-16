/********************************************************************************
** Form generated from reading UI file 'EditDotMatchingLibrary.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITDOTMATCHINGLIBRARY_H
#define UI_EDITDOTMATCHINGLIBRARY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditDotMatchingLibrary
{
public:
    QLineEdit *EditLibID;
    QPushButton *ButtonLibSave;
    QPushButton *ButtonLibSaveNew;
    QToolButton *toolButtonInspect;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QFrame *frame_3;
    QSpinBox *EditMinDotMatchingSize;
    QLabel *label_9;
    QSpinBox *EditMaxDotMatchingSize;
    QLabel *label_10;
    QSpinBox *EditMinDotMatchingDots;
    QLabel *label_12;
    QSpinBox *EditMaxDotMatchingDots;
    QLabel *label_11;
    QLabel *label_13;
    QSpinBox *EditLimitDotMatchingSize;
    QLabel *label_32;
    QFrame *frame_2;
    QLabel *label_7;
    QSpinBox *EditPickupL;
    QLabel *label_8;
    QSpinBox *EditPickupH;
    QLabel *label_30;
    QFrame *frame_4;
    QLabel *label_14;
    QSpinBox *EditSpaceToOutline;
    QSpinBox *EditNoiseSize;
    QLabel *label_16;
    QSpinBox *EditPriority;
    QLabel *label_33;
    QLabel *label_48;
    QLabel *label_49;
    QSpinBox *EditNoiseSizePinHole;
    QFrame *framePickLayer;
    QLabel *label;
    QFrame *frameGenLayer;
    QLabel *label_2;
    QWidget *page_3;
    QFrame *frame_6;
    QLabel *label_35;
    QLabel *label_20;
    QLabel *label_17;
    QSpinBox *EditOKDot;
    QLabel *label_18;
    QSpinBox *EditBrightWidthL;
    QSpinBox *EditBrightWidthH;
    QLabel *label_19;
    QFrame *frame_11;
    QLabel *label_41;
    QFrame *frame_12;
    QLabel *label_42;
    QSpinBox *EditAdjustBlack;
    QSpinBox *EditAdjustWhite;
    QLabel *label_26;
    QLabel *label_25;
    QFrame *frame_13;
    QLabel *label_43;
    QFrame *frame_14;
    QLabel *label_44;
    QSpinBox *EditSelfSearch;
    QLabel *label_27;
    QSpinBox *EditAreaSearch;
    QLabel *label_28;
    QFrame *frame_15;
    QLabel *label_45;
    QFrame *frame_16;
    QLabel *label_46;
    QCheckBox *checkBoxClusterize;
    QWidget *page_2;
    QLabel *label_4;
    QFrame *frameLibFolder;
    QPushButton *ButtonLibNew;
    QLineEdit *EditLibName;
    QPushButton *pushButton;
    QToolButton *toolButtonPickup;
    QPushButton *ButtonLibDelete;
    QTableWidget *tableWidgetLibList;

    void setupUi(QDialog *EditDotMatchingLibrary)
    {
        if (EditDotMatchingLibrary->objectName().isEmpty())
            EditDotMatchingLibrary->setObjectName("EditDotMatchingLibrary");
        EditDotMatchingLibrary->resize(703, 611);
        EditLibID = new QLineEdit(EditDotMatchingLibrary);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(300, 50, 81, 31));
        QFont font;
        font.setPointSize(12);
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        ButtonLibSave = new QPushButton(EditDotMatchingLibrary);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(570, 530, 91, 31));
        QFont font1;
        font1.setPointSize(11);
        ButtonLibSave->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon);
        ButtonLibSaveNew = new QPushButton(EditDotMatchingLibrary);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(460, 530, 101, 31));
        ButtonLibSaveNew->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon1);
        toolButtonInspect = new QToolButton(EditDotMatchingLibrary);
        toolButtonInspect->setObjectName("toolButtonInspect");
        toolButtonInspect->setGeometry(QRect(470, 10, 141, 31));
        toolButtonInspect->setCheckable(true);
        toolButtonInspect->setAutoExclusive(true);
        stackedWidget = new QStackedWidget(EditDotMatchingLibrary);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(250, 90, 411, 431));
        page = new QWidget();
        page->setObjectName("page");
        frame_3 = new QFrame(page);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(0, 170, 411, 141));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        EditMinDotMatchingSize = new QSpinBox(frame_3);
        EditMinDotMatchingSize->setObjectName("EditMinDotMatchingSize");
        EditMinDotMatchingSize->setGeometry(QRect(290, 10, 81, 22));
        EditMinDotMatchingSize->setMaximum(1000000);
        label_9 = new QLabel(frame_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(60, 30, 221, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxDotMatchingSize = new QSpinBox(frame_3);
        EditMaxDotMatchingSize->setObjectName("EditMaxDotMatchingSize");
        EditMaxDotMatchingSize->setGeometry(QRect(290, 30, 81, 22));
        EditMaxDotMatchingSize->setMaximum(1000000);
        label_10 = new QLabel(frame_3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(60, 10, 221, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinDotMatchingDots = new QSpinBox(frame_3);
        EditMinDotMatchingDots->setObjectName("EditMinDotMatchingDots");
        EditMinDotMatchingDots->setGeometry(QRect(290, 60, 101, 22));
        EditMinDotMatchingDots->setMaximum(2000000000);
        label_12 = new QLabel(frame_3);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(60, 60, 221, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxDotMatchingDots = new QSpinBox(frame_3);
        EditMaxDotMatchingDots->setObjectName("EditMaxDotMatchingDots");
        EditMaxDotMatchingDots->setGeometry(QRect(290, 80, 101, 22));
        EditMaxDotMatchingDots->setMaximum(2000000000);
        EditMaxDotMatchingDots->setValue(2000000000);
        label_11 = new QLabel(frame_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(60, 80, 221, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_13 = new QLabel(frame_3);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(60, 110, 221, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLimitDotMatchingSize = new QSpinBox(frame_3);
        EditLimitDotMatchingSize->setObjectName("EditLimitDotMatchingSize");
        EditLimitDotMatchingSize->setGeometry(QRect(290, 110, 61, 22));
        EditLimitDotMatchingSize->setMaximum(99999);
        label_32 = new QLabel(frame_3);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(0, 0, 31, 141));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Raised);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_32->setIndent(1);
        frame_2 = new QFrame(page);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(0, 100, 411, 61));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(60, 10, 261, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupL = new QSpinBox(frame_2);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(330, 10, 61, 22));
        EditPickupL->setMaximum(255);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(60, 30, 261, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupH = new QSpinBox(frame_2);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(330, 30, 61, 22));
        EditPickupH->setMaximum(255);
        label_30 = new QLabel(frame_2);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(0, 0, 31, 61));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Raised);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_30->setIndent(1);
        frame_4 = new QFrame(page);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(0, 320, 411, 101));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Sunken);
        label_14 = new QLabel(frame_4);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(60, 10, 261, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSpaceToOutline = new QSpinBox(frame_4);
        EditSpaceToOutline->setObjectName("EditSpaceToOutline");
        EditSpaceToOutline->setGeometry(QRect(330, 10, 61, 23));
        EditNoiseSize = new QSpinBox(frame_4);
        EditNoiseSize->setObjectName("EditNoiseSize");
        EditNoiseSize->setGeometry(QRect(330, 30, 61, 23));
        QFont font2;
        font2.setPointSize(9);
        EditNoiseSize->setFont(font2);
        label_16 = new QLabel(frame_4);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(60, 70, 261, 21));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPriority = new QSpinBox(frame_4);
        EditPriority->setObjectName("EditPriority");
        EditPriority->setGeometry(QRect(330, 70, 61, 23));
        EditPriority->setFont(font2);
        label_33 = new QLabel(frame_4);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(0, 0, 31, 101));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Raised);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_33->setIndent(1);
        label_48 = new QLabel(frame_4);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(60, 50, 261, 21));
        label_48->setFrameShape(QFrame::Panel);
        label_48->setFrameShadow(QFrame::Sunken);
        label_48->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_49 = new QLabel(frame_4);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(60, 30, 261, 21));
        label_49->setFrameShape(QFrame::Panel);
        label_49->setFrameShadow(QFrame::Sunken);
        label_49->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNoiseSizePinHole = new QSpinBox(frame_4);
        EditNoiseSizePinHole->setObjectName("EditNoiseSizePinHole");
        EditNoiseSizePinHole->setGeometry(QRect(330, 50, 61, 23));
        EditNoiseSizePinHole->setFont(font2);
        framePickLayer = new QFrame(page);
        framePickLayer->setObjectName("framePickLayer");
        framePickLayer->setGeometry(QRect(0, 20, 411, 28));
        framePickLayer->setFrameShape(QFrame::NoFrame);
        framePickLayer->setFrameShadow(QFrame::Plain);
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 411, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignCenter);
        frameGenLayer = new QFrame(page);
        frameGenLayer->setObjectName("frameGenLayer");
        frameGenLayer->setGeometry(QRect(0, 70, 411, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 50, 411, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setTextFormat(Qt::AutoText);
        label_2->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        frame_6 = new QFrame(page_3);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(0, 0, 411, 91));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Sunken);
        label_35 = new QLabel(frame_6);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(0, 0, 31, 91));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Raised);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_35->setIndent(1);
        label_20 = new QLabel(frame_6);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(320, 10, 81, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        label_20->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_17 = new QLabel(frame_6);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(40, 28, 181, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKDot = new QSpinBox(frame_6);
        EditOKDot->setObjectName("EditOKDot");
        EditOKDot->setGeometry(QRect(270, 52, 81, 22));
        EditOKDot->setMaximum(99999999);
        label_18 = new QLabel(frame_6);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(40, 48, 181, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBrightWidthL = new QSpinBox(frame_6);
        EditBrightWidthL->setObjectName("EditBrightWidthL");
        EditBrightWidthL->setGeometry(QRect(230, 30, 81, 22));
        EditBrightWidthL->setMaximum(255);
        EditBrightWidthH = new QSpinBox(frame_6);
        EditBrightWidthH->setObjectName("EditBrightWidthH");
        EditBrightWidthH->setGeometry(QRect(320, 30, 81, 22));
        EditBrightWidthH->setMaximum(255);
        label_19 = new QLabel(frame_6);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(230, 10, 81, 21));
        label_19->setFrameShape(QFrame::Panel);
        label_19->setFrameShadow(QFrame::Sunken);
        label_19->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_11 = new QFrame(page_3);
        frame_11->setObjectName("frame_11");
        frame_11->setGeometry(QRect(0, 100, 411, 61));
        frame_11->setFrameShape(QFrame::StyledPanel);
        frame_11->setFrameShadow(QFrame::Sunken);
        label_41 = new QLabel(frame_11);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(0, 0, 31, 61));
        label_41->setFrameShape(QFrame::Panel);
        label_41->setFrameShadow(QFrame::Raised);
        label_41->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_41->setIndent(1);
        frame_12 = new QFrame(frame_11);
        frame_12->setObjectName("frame_12");
        frame_12->setGeometry(QRect(10, 120, 371, 101));
        frame_12->setFrameShape(QFrame::StyledPanel);
        frame_12->setFrameShadow(QFrame::Sunken);
        label_42 = new QLabel(frame_12);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(0, 0, 20, 61));
        label_42->setFrameShape(QFrame::Panel);
        label_42->setFrameShadow(QFrame::Raised);
        label_42->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_42->setIndent(1);
        EditAdjustBlack = new QSpinBox(frame_11);
        EditAdjustBlack->setObjectName("EditAdjustBlack");
        EditAdjustBlack->setGeometry(QRect(310, 10, 81, 22));
        EditAdjustBlack->setMaximum(255);
        EditAdjustWhite = new QSpinBox(frame_11);
        EditAdjustWhite->setObjectName("EditAdjustWhite");
        EditAdjustWhite->setGeometry(QRect(310, 30, 81, 22));
        EditAdjustWhite->setMaximum(255);
        label_26 = new QLabel(frame_11);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(40, 30, 261, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_25 = new QLabel(frame_11);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(40, 10, 261, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_13 = new QFrame(page_3);
        frame_13->setObjectName("frame_13");
        frame_13->setGeometry(QRect(0, 170, 411, 61));
        frame_13->setFrameShape(QFrame::StyledPanel);
        frame_13->setFrameShadow(QFrame::Sunken);
        label_43 = new QLabel(frame_13);
        label_43->setObjectName("label_43");
        label_43->setGeometry(QRect(0, 0, 31, 61));
        label_43->setFrameShape(QFrame::Panel);
        label_43->setFrameShadow(QFrame::Raised);
        label_43->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_43->setIndent(1);
        frame_14 = new QFrame(frame_13);
        frame_14->setObjectName("frame_14");
        frame_14->setGeometry(QRect(10, 120, 371, 101));
        frame_14->setFrameShape(QFrame::StyledPanel);
        frame_14->setFrameShadow(QFrame::Sunken);
        label_44 = new QLabel(frame_14);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(0, 0, 20, 61));
        label_44->setFrameShape(QFrame::Panel);
        label_44->setFrameShadow(QFrame::Raised);
        label_44->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_44->setIndent(1);
        EditSelfSearch = new QSpinBox(frame_13);
        EditSelfSearch->setObjectName("EditSelfSearch");
        EditSelfSearch->setGeometry(QRect(310, 30, 81, 22));
        label_27 = new QLabel(frame_13);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(40, 30, 261, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditAreaSearch = new QSpinBox(frame_13);
        EditAreaSearch->setObjectName("EditAreaSearch");
        EditAreaSearch->setGeometry(QRect(310, 10, 81, 22));
        label_28 = new QLabel(frame_13);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(40, 10, 261, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_15 = new QFrame(page_3);
        frame_15->setObjectName("frame_15");
        frame_15->setGeometry(QRect(0, 240, 411, 41));
        frame_15->setFrameShape(QFrame::StyledPanel);
        frame_15->setFrameShadow(QFrame::Sunken);
        label_45 = new QLabel(frame_15);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(0, 0, 31, 41));
        label_45->setFrameShape(QFrame::Panel);
        label_45->setFrameShadow(QFrame::Raised);
        label_45->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_45->setIndent(1);
        frame_16 = new QFrame(frame_15);
        frame_16->setObjectName("frame_16");
        frame_16->setGeometry(QRect(10, 120, 371, 101));
        frame_16->setFrameShape(QFrame::StyledPanel);
        frame_16->setFrameShadow(QFrame::Sunken);
        label_46 = new QLabel(frame_16);
        label_46->setObjectName("label_46");
        label_46->setGeometry(QRect(0, 0, 20, 61));
        label_46->setFrameShape(QFrame::Panel);
        label_46->setFrameShadow(QFrame::Raised);
        label_46->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_46->setIndent(1);
        checkBoxClusterize = new QCheckBox(frame_15);
        checkBoxClusterize->setObjectName("checkBoxClusterize");
        checkBoxClusterize->setGeometry(QRect(60, 10, 108, 22));
        stackedWidget->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        label_4 = new QLabel(EditDotMatchingLibrary);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(250, 50, 51, 31));
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameLibFolder = new QFrame(EditDotMatchingLibrary);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 50, 221, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonLibNew = new QPushButton(EditDotMatchingLibrary);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(250, 530, 101, 31));
        ButtonLibNew->setFont(font1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon2);
        EditLibName = new QLineEdit(EditDotMatchingLibrary);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(380, 50, 281, 31));
        EditLibName->setFont(font);
        pushButton = new QPushButton(EditDotMatchingLibrary);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(570, 570, 91, 31));
        pushButton->setFont(font1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon3);
        toolButtonPickup = new QToolButton(EditDotMatchingLibrary);
        toolButtonPickup->setObjectName("toolButtonPickup");
        toolButtonPickup->setGeometry(QRect(250, 10, 141, 31));
        toolButtonPickup->setCheckable(true);
        toolButtonPickup->setChecked(true);
        toolButtonPickup->setAutoExclusive(true);
        ButtonLibDelete = new QPushButton(EditDotMatchingLibrary);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(360, 530, 91, 31));
        ButtonLibDelete->setFont(font1);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon4);
        tableWidgetLibList = new QTableWidget(EditDotMatchingLibrary);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 260, 221, 341));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(EditDotMatchingLibrary);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditDotMatchingLibrary);
    } // setupUi

    void retranslateUi(QDialog *EditDotMatchingLibrary)
    {
        EditDotMatchingLibrary->setWindowTitle(QCoreApplication::translate("EditDotMatchingLibrary", "Edit DotMatching Library", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditDotMatchingLibrary", "12345", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditDotMatchingLibrary", "Update", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditDotMatchingLibrary", "Save New", nullptr));
        toolButtonInspect->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\346\244\234\346\237\273", nullptr));
        label_9->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_10->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_12->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_11->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_13->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\351\231\220\347\225\214\343\202\265\343\202\244\343\202\272", nullptr));
        label_32->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\343\202\265\n"
"\343\202\244\n"
"\343\202\272", nullptr));
        label_7->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
        label_8->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
        label_30->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\350\274\235\n"
"\345\272\246", nullptr));
        label_14->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\350\274\252\351\203\255\343\201\213\343\202\211\343\201\256\351\226\223\351\232\224", nullptr));
        label_16->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\345\204\252\345\205\210\345\272\246", nullptr));
        label_33->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\347\224\237\n"
"\346\210\220", nullptr));
        label_48->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272\343\200\200\343\203\224\343\203\263\343\203\233\343\203\274\343\203\253\345\211\212\351\231\244", nullptr));
        label_49->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272 \345\255\244\347\253\213\347\202\271\345\211\212\351\231\244", nullptr));
        label->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\346\212\275\345\207\272\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        label_2->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        label_35->setText(QCoreApplication::translate("EditDotMatchingLibrary", "<html><head/><body><p>\346\244\234</p><p>\345\207\272</p></body></html>", nullptr));
        label_20->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\346\230\216\345\201\264", nullptr));
        label_17->setText(QCoreApplication::translate("EditDotMatchingLibrary", "OK\350\274\235\345\272\246\347\257\204\345\233\262(%)", nullptr));
        label_18->setText(QCoreApplication::translate("EditDotMatchingLibrary", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_19->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\346\232\227\345\201\264", nullptr));
        label_41->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\350\243\234\n"
"\346\255\243", nullptr));
        label_42->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\350\274\235\n"
"\345\272\246", nullptr));
        label_26->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_25->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_43->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\346\216\242\n"
"\347\264\242", nullptr));
        label_44->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\350\274\235\n"
"\345\272\246", nullptr));
        label_27->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\343\203\224\343\202\257\343\202\273\343\203\253\345\215\230\344\275\215\343\201\247\343\201\256\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_28->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\351\240\230\345\237\237\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_45->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\345\261\236\n"
"\346\200\247", nullptr));
        label_46->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\350\274\235\n"
"\345\272\246", nullptr));
        checkBoxClusterize->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\345\241\212\345\210\244\345\256\232", nullptr));
        label_4->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\345\220\215\347\247\260", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditDotMatchingLibrary", "Clear new", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditDotMatchingLibrary", "Library Name", nullptr));
        pushButton->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\351\226\211\343\201\230\343\202\213", nullptr));
        toolButtonPickup->setText(QCoreApplication::translate("EditDotMatchingLibrary", "\347\224\237\346\210\220", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditDotMatchingLibrary", "Delete", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditDotMatchingLibrary", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditDotMatchingLibrary", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditDotMatchingLibrary: public Ui_EditDotMatchingLibrary {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITDOTMATCHINGLIBRARY_H
