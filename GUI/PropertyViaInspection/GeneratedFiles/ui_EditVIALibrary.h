/********************************************************************************
** Form generated from reading UI file 'EditVIALibrary.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITVIALIBRARY_H
#define UI_EDITVIALIBRARY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
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

class Ui_EditVIALibrary
{
public:
    QLineEdit *EditLibID;
    QPushButton *pushButton;
    QToolButton *toolButtonInspect;
    QToolButton *toolButtonPickup;
    QPushButton *ButtonLibSaveNew;
    QLineEdit *EditLibName;
    QPushButton *ButtonLibDelete;
    QLabel *label_4;
    QFrame *frameLibFolder;
    QPushButton *ButtonLibNew;
    QPushButton *ButtonLibSave;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QFrame *frame_3;
    QSpinBox *EditMinVIASize;
    QLabel *label_9;
    QSpinBox *EditMaxVIASize;
    QLabel *label_10;
    QSpinBox *EditMinVIADots;
    QLabel *label_12;
    QSpinBox *EditMaxVIADots;
    QLabel *label_11;
    QLabel *label_13;
    QSpinBox *EditLimitVIASize;
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
    QSpinBox *EditOKDotH;
    QLabel *label_18;
    QSpinBox *EditBrightWidthL;
    QSpinBox *EditOKDotL;
    QSpinBox *EditBrightWidthH;
    QLabel *label_19;
    QLabel *label_29;
    QSpinBox *EditOKLengthL;
    QSpinBox *EditOKLengthH;
    QSpinBox *EditShrinkDot;
    QLabel *label_38;
    QLabel *label_51;
    QSpinBox *EditMaxNGDotL;
    QSpinBox *EditMaxNGDotH;
    QLabel *label_39;
    QSpinBox *EditEnlargeDot;
    QWidget *page_2;
    QTableWidget *tableWidgetLibList;

    void setupUi(QDialog *EditVIALibrary)
    {
        if (EditVIALibrary->objectName().isEmpty())
            EditVIALibrary->setObjectName("EditVIALibrary");
        EditVIALibrary->resize(638, 626);
        EditLibID = new QLineEdit(EditVIALibrary);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(300, 50, 81, 31));
        QFont font;
        font.setPointSize(12);
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        pushButton = new QPushButton(EditVIALibrary);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(540, 580, 81, 31));
        QFont font1;
        font1.setPointSize(11);
        pushButton->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon);
        toolButtonInspect = new QToolButton(EditVIALibrary);
        toolButtonInspect->setObjectName("toolButtonInspect");
        toolButtonInspect->setGeometry(QRect(470, 10, 141, 31));
        toolButtonInspect->setCheckable(true);
        toolButtonInspect->setAutoExclusive(true);
        toolButtonPickup = new QToolButton(EditVIALibrary);
        toolButtonPickup->setObjectName("toolButtonPickup");
        toolButtonPickup->setGeometry(QRect(250, 10, 141, 31));
        toolButtonPickup->setCheckable(true);
        toolButtonPickup->setChecked(true);
        toolButtonPickup->setAutoExclusive(true);
        ButtonLibSaveNew = new QPushButton(EditVIALibrary);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(440, 540, 91, 31));
        ButtonLibSaveNew->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon1);
        EditLibName = new QLineEdit(EditVIALibrary);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(380, 50, 211, 31));
        EditLibName->setFont(font);
        ButtonLibDelete = new QPushButton(EditVIALibrary);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(350, 540, 81, 31));
        ButtonLibDelete->setFont(font1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon2);
        label_4 = new QLabel(EditVIALibrary);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(250, 50, 51, 31));
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameLibFolder = new QFrame(EditVIALibrary);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 50, 221, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonLibNew = new QPushButton(EditVIALibrary);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(250, 540, 91, 31));
        ButtonLibNew->setFont(font1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon3);
        ButtonLibSave = new QPushButton(EditVIALibrary);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(540, 540, 81, 31));
        ButtonLibSave->setFont(font1);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon4);
        stackedWidget = new QStackedWidget(EditVIALibrary);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(250, 90, 381, 441));
        page = new QWidget();
        page->setObjectName("page");
        frame_3 = new QFrame(page);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(0, 170, 371, 141));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        EditMinVIASize = new QSpinBox(frame_3);
        EditMinVIASize->setObjectName("EditMinVIASize");
        EditMinVIASize->setGeometry(QRect(190, 10, 81, 22));
        EditMinVIASize->setMaximum(1000000);
        label_9 = new QLabel(frame_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(60, 30, 111, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxVIASize = new QSpinBox(frame_3);
        EditMaxVIASize->setObjectName("EditMaxVIASize");
        EditMaxVIASize->setGeometry(QRect(190, 30, 81, 22));
        EditMaxVIASize->setMaximum(1000000);
        label_10 = new QLabel(frame_3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(60, 10, 111, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinVIADots = new QSpinBox(frame_3);
        EditMinVIADots->setObjectName("EditMinVIADots");
        EditMinVIADots->setGeometry(QRect(190, 60, 101, 22));
        EditMinVIADots->setMaximum(2000000000);
        label_12 = new QLabel(frame_3);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(60, 60, 111, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxVIADots = new QSpinBox(frame_3);
        EditMaxVIADots->setObjectName("EditMaxVIADots");
        EditMaxVIADots->setGeometry(QRect(190, 80, 101, 22));
        EditMaxVIADots->setMaximum(2000000000);
        EditMaxVIADots->setValue(2000000000);
        label_11 = new QLabel(frame_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(60, 80, 111, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_13 = new QLabel(frame_3);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(60, 110, 111, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLimitVIASize = new QSpinBox(frame_3);
        EditLimitVIASize->setObjectName("EditLimitVIASize");
        EditLimitVIASize->setGeometry(QRect(190, 110, 61, 22));
        EditLimitVIASize->setMaximum(99999);
        label_32 = new QLabel(frame_3);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(0, 0, 31, 141));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Raised);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_32->setIndent(1);
        frame_2 = new QFrame(page);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(0, 110, 371, 61));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(60, 10, 111, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupL = new QSpinBox(frame_2);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(190, 10, 61, 22));
        EditPickupL->setMaximum(255);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(60, 30, 111, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupH = new QSpinBox(frame_2);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(190, 30, 61, 22));
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
        frame_4->setGeometry(QRect(0, 310, 371, 121));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Sunken);
        label_14 = new QLabel(frame_4);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(40, 10, 171, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSpaceToOutline = new QSpinBox(frame_4);
        EditSpaceToOutline->setObjectName("EditSpaceToOutline");
        EditSpaceToOutline->setGeometry(QRect(220, 10, 61, 23));
        EditSpaceToOutline->setMinimum(-999);
        EditSpaceToOutline->setMaximum(999);
        EditNoiseSize = new QSpinBox(frame_4);
        EditNoiseSize->setObjectName("EditNoiseSize");
        EditNoiseSize->setGeometry(QRect(220, 30, 61, 23));
        QFont font2;
        font2.setPointSize(9);
        EditNoiseSize->setFont(font2);
        label_16 = new QLabel(frame_4);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(40, 70, 171, 21));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPriority = new QSpinBox(frame_4);
        EditPriority->setObjectName("EditPriority");
        EditPriority->setGeometry(QRect(220, 70, 61, 23));
        EditPriority->setFont(font2);
        label_33 = new QLabel(frame_4);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(0, 0, 31, 121));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Raised);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_33->setIndent(1);
        label_48 = new QLabel(frame_4);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(40, 50, 171, 21));
        label_48->setFrameShape(QFrame::Panel);
        label_48->setFrameShadow(QFrame::Sunken);
        label_48->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_49 = new QLabel(frame_4);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(40, 30, 171, 21));
        label_49->setFrameShape(QFrame::Panel);
        label_49->setFrameShadow(QFrame::Sunken);
        label_49->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNoiseSizePinHole = new QSpinBox(frame_4);
        EditNoiseSizePinHole->setObjectName("EditNoiseSizePinHole");
        EditNoiseSizePinHole->setGeometry(QRect(220, 50, 61, 23));
        EditNoiseSizePinHole->setFont(font2);
        framePickLayer = new QFrame(page);
        framePickLayer->setObjectName("framePickLayer");
        framePickLayer->setGeometry(QRect(0, 20, 371, 28));
        framePickLayer->setFrameShape(QFrame::NoFrame);
        framePickLayer->setFrameShadow(QFrame::Plain);
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 371, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignCenter);
        frameGenLayer = new QFrame(page);
        frameGenLayer->setObjectName("frameGenLayer");
        frameGenLayer->setGeometry(QRect(0, 70, 371, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 50, 371, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setTextFormat(Qt::AutoText);
        label_2->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        frame_6 = new QFrame(page_3);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(0, 0, 371, 181));
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
        label_20->setGeometry(QRect(280, 8, 81, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        label_20->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_17 = new QLabel(frame_6);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(60, 28, 121, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKDotH = new QSpinBox(frame_6);
        EditOKDotH->setObjectName("EditOKDotH");
        EditOKDotH->setGeometry(QRect(280, 48, 81, 22));
        EditOKDotH->setMaximum(99999999);
        label_18 = new QLabel(frame_6);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(60, 48, 121, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBrightWidthL = new QSpinBox(frame_6);
        EditBrightWidthL->setObjectName("EditBrightWidthL");
        EditBrightWidthL->setGeometry(QRect(190, 28, 81, 22));
        EditBrightWidthL->setMaximum(255);
        EditOKDotL = new QSpinBox(frame_6);
        EditOKDotL->setObjectName("EditOKDotL");
        EditOKDotL->setGeometry(QRect(190, 48, 81, 22));
        EditOKDotL->setMaximum(99999999);
        EditBrightWidthH = new QSpinBox(frame_6);
        EditBrightWidthH->setObjectName("EditBrightWidthH");
        EditBrightWidthH->setGeometry(QRect(280, 28, 81, 22));
        EditBrightWidthH->setMaximum(255);
        label_19 = new QLabel(frame_6);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(190, 8, 81, 21));
        label_19->setFrameShape(QFrame::Panel);
        label_19->setFrameShadow(QFrame::Sunken);
        label_19->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_29 = new QLabel(frame_6);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(60, 68, 121, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKLengthL = new QSpinBox(frame_6);
        EditOKLengthL->setObjectName("EditOKLengthL");
        EditOKLengthL->setGeometry(QRect(190, 68, 81, 22));
        EditOKLengthL->setMaximum(99999999);
        EditOKLengthH = new QSpinBox(frame_6);
        EditOKLengthH->setObjectName("EditOKLengthH");
        EditOKLengthH->setGeometry(QRect(280, 68, 81, 22));
        EditOKLengthH->setMaximum(99999999);
        EditShrinkDot = new QSpinBox(frame_6);
        EditShrinkDot->setObjectName("EditShrinkDot");
        EditShrinkDot->setGeometry(QRect(230, 130, 81, 22));
        EditShrinkDot->setMaximum(99999999);
        label_38 = new QLabel(frame_6);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(60, 128, 121, 21));
        label_38->setFrameShape(QFrame::Panel);
        label_38->setFrameShadow(QFrame::Sunken);
        label_38->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_51 = new QLabel(frame_6);
        label_51->setObjectName("label_51");
        label_51->setGeometry(QRect(60, 90, 121, 21));
        label_51->setFrameShape(QFrame::Panel);
        label_51->setFrameShadow(QFrame::Sunken);
        label_51->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxNGDotL = new QSpinBox(frame_6);
        EditMaxNGDotL->setObjectName("EditMaxNGDotL");
        EditMaxNGDotL->setGeometry(QRect(190, 90, 81, 22));
        EditMaxNGDotL->setMaximum(99999999);
        EditMaxNGDotH = new QSpinBox(frame_6);
        EditMaxNGDotH->setObjectName("EditMaxNGDotH");
        EditMaxNGDotH->setGeometry(QRect(280, 90, 81, 22));
        EditMaxNGDotH->setMaximum(99999999);
        label_39 = new QLabel(frame_6);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(60, 150, 121, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditEnlargeDot = new QSpinBox(frame_6);
        EditEnlargeDot->setObjectName("EditEnlargeDot");
        EditEnlargeDot->setGeometry(QRect(230, 150, 81, 22));
        EditEnlargeDot->setMaximum(99999999);
        stackedWidget->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        tableWidgetLibList = new QTableWidget(EditVIALibrary);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 270, 221, 271));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(EditVIALibrary);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditVIALibrary);
    } // setupUi

    void retranslateUi(QDialog *EditVIALibrary)
    {
        EditVIALibrary->setWindowTitle(QCoreApplication::translate("EditVIALibrary", "Edit VIA Library", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditVIALibrary", "12345", nullptr));
        pushButton->setText(QCoreApplication::translate("EditVIALibrary", "\351\226\211\343\201\230\343\202\213", nullptr));
        toolButtonInspect->setText(QCoreApplication::translate("EditVIALibrary", "\346\244\234\346\237\273", nullptr));
        toolButtonPickup->setText(QCoreApplication::translate("EditVIALibrary", "\347\224\237\346\210\220", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditVIALibrary", "Save New", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditVIALibrary", "Library Name", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditVIALibrary", "Delete", nullptr));
        label_4->setText(QCoreApplication::translate("EditVIALibrary", "\345\220\215\347\247\260", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditVIALibrary", "Clear new", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditVIALibrary", "Update", nullptr));
        label_9->setText(QCoreApplication::translate("EditVIALibrary", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_10->setText(QCoreApplication::translate("EditVIALibrary", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_12->setText(QCoreApplication::translate("EditVIALibrary", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_11->setText(QCoreApplication::translate("EditVIALibrary", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_13->setText(QCoreApplication::translate("EditVIALibrary", "\351\231\220\347\225\214\343\202\265\343\202\244\343\202\272", nullptr));
        label_32->setText(QCoreApplication::translate("EditVIALibrary", "\343\202\265\n"
"\343\202\244\n"
"\343\202\272", nullptr));
        label_7->setText(QCoreApplication::translate("EditVIALibrary", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
        label_8->setText(QCoreApplication::translate("EditVIALibrary", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
        label_30->setText(QCoreApplication::translate("EditVIALibrary", "\350\274\235\n"
"\345\272\246", nullptr));
        label_14->setText(QCoreApplication::translate("EditVIALibrary", "\350\274\252\351\203\255\343\201\213\343\202\211\343\201\256\351\226\223\351\232\224", nullptr));
        label_16->setText(QCoreApplication::translate("EditVIALibrary", "\345\204\252\345\205\210\345\272\246", nullptr));
        label_33->setText(QCoreApplication::translate("EditVIALibrary", "\347\224\237\n"
"\346\210\220", nullptr));
        label_48->setText(QCoreApplication::translate("EditVIALibrary", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272\343\200\200\343\203\224\343\203\263\343\203\233\343\203\274\343\203\253\345\211\212\351\231\244", nullptr));
        label_49->setText(QCoreApplication::translate("EditVIALibrary", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272 \345\255\244\347\253\213\347\202\271\345\211\212\351\231\244", nullptr));
        label->setText(QCoreApplication::translate("EditVIALibrary", "\346\212\275\345\207\272\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        label_2->setText(QCoreApplication::translate("EditVIALibrary", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        label_35->setText(QCoreApplication::translate("EditVIALibrary", "\346\244\234\346\237\273", nullptr));
        label_20->setText(QCoreApplication::translate("EditVIALibrary", "\346\230\216\345\201\264", nullptr));
        label_17->setText(QCoreApplication::translate("EditVIALibrary", "OK\350\274\235\345\272\246\347\257\204\345\233\262", nullptr));
        label_18->setText(QCoreApplication::translate("EditVIALibrary", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_19->setText(QCoreApplication::translate("EditVIALibrary", "\346\232\227\345\201\264", nullptr));
        label_29->setText(QCoreApplication::translate("EditVIALibrary", "\343\201\223\343\202\214\344\273\245\344\270\212\343\201\256\351\225\267\343\201\225\343\201\247\357\274\256\357\274\247", nullptr));
        label_38->setText(QCoreApplication::translate("EditVIALibrary", "\345\217\216\347\270\256\343\203\211\343\203\203\343\203\210", nullptr));
        label_51->setText(QCoreApplication::translate("EditVIALibrary", "\346\234\200\345\244\247NG\351\235\242\347\251\215", nullptr));
        label_39->setText(QCoreApplication::translate("EditVIALibrary", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditVIALibrary", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditVIALibrary", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditVIALibrary: public Ui_EditVIALibrary {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITVIALIBRARY_H
