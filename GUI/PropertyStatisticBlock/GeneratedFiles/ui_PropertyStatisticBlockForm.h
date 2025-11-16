/********************************************************************************
** Form generated from reading UI file 'PropertyStatisticBlockForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYSTATISTICBLOCKFORM_H
#define UI_PROPERTYSTATISTICBLOCKFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
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
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyStatisticBlockFormClass
{
public:
    QToolButton *toolButtonCreateBlock;
    QFrame *frame_3;
    QToolButton *toolButtonEdge;
    QToolButton *toolButtonArea;
    QToolButton *toolButtonInside;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *pushButtonEditLibFolder;
    QLabel *labelLibFolderName;
    QTableWidget *tableWidgetLibList;
    QTableWidget *tableWidgetGeneratedLibList;
    QPushButton *pushButtonSetFrom;
    QPushButton *pushButtonGetBack;
    QPushButton *pushButtonEditLibrary;
    QPushButton *ButtonPickupClearTest;
    QPushButton *ButtonPickupTest;
    QPushButton *ButtonGenerateLibs;
    QFrame *frame_4;
    QLineEdit *EditLibName;
    QLabel *label_3;
    QLineEdit *EditLibID;
    QLabel *label_4;
    QSpinBox *EditNoiseSize;
    QSpinBox *EditSpaceToOutline;
    QLabel *label_16;
    QSpinBox *EditPriority;
    QLabel *label_14;
    QLabel *label_15;
    QPushButton *ButtonLibSave;
    QLabel *label_30;
    QLabel *label_31;
    QWidget *page_2;
    QTableWidget *tableWidgetBlockInfo;
    QLabel *label_32;
    QFrame *frameBlockInfoOnMouse;
    QLabel *label_33;
    QFrame *frame;
    QFrame *frame_15;
    QLabel *label_46;
    QFrame *frame_16;
    QLabel *label_47;
    QSpinBox *EditAdjustBlack;
    QSpinBox *EditAdjustWhite;
    QLabel *label_48;
    QLabel *label_49;
    QCheckBox *checkBModeWhiteMask;
    QFrame *frame_7;
    QLabel *label_35;
    QLabel *label_36;
    QSpinBox *EditOKDotH;
    QLabel *label_38;
    QSpinBox *EditOKDotL;
    QLabel *label_39;
    QSpinBox *EditOKLengthH;
    QSpinBox *EditOKLengthL;
    QLabel *label_29;
    QLabel *label_17;
    QLineEdit *EditBrightWidthH;
    QLineEdit *EditBrightWidthL;
    QCheckBox *checkBModeBlackMask;
    QLineEdit *EditLibNameInBlock;
    QLineEdit *EditLibIDnBlock;
    QLabel *label_34;
    QToolButton *toolButtonLibrary;

    void setupUi(GUIFormBase *PropertyStatisticBlockFormClass)
    {
        if (PropertyStatisticBlockFormClass->objectName().isEmpty())
            PropertyStatisticBlockFormClass->setObjectName("PropertyStatisticBlockFormClass");
        PropertyStatisticBlockFormClass->resize(400, 700);
        toolButtonCreateBlock = new QToolButton(PropertyStatisticBlockFormClass);
        toolButtonCreateBlock->setObjectName("toolButtonCreateBlock");
        toolButtonCreateBlock->setGeometry(QRect(180, 10, 121, 31));
        toolButtonCreateBlock->setCheckable(true);
        toolButtonCreateBlock->setAutoExclusive(true);
        frame_3 = new QFrame(PropertyStatisticBlockFormClass);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(320, 10, 71, 21));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Plain);
        toolButtonEdge = new QToolButton(frame_3);
        toolButtonEdge->setObjectName("toolButtonEdge");
        toolButtonEdge->setGeometry(QRect(20, 0, 19, 18));
        toolButtonEdge->setCheckable(true);
        toolButtonEdge->setChecked(false);
        toolButtonEdge->setAutoExclusive(true);
        toolButtonArea = new QToolButton(frame_3);
        toolButtonArea->setObjectName("toolButtonArea");
        toolButtonArea->setGeometry(QRect(0, 0, 19, 18));
        toolButtonArea->setCheckable(true);
        toolButtonArea->setChecked(true);
        toolButtonArea->setAutoExclusive(true);
        toolButtonInside = new QToolButton(frame_3);
        toolButtonInside->setObjectName("toolButtonInside");
        toolButtonInside->setGeometry(QRect(40, 0, 19, 18));
        toolButtonInside->setCheckable(true);
        toolButtonInside->setChecked(false);
        toolButtonInside->setAutoExclusive(true);
        stackedWidget = new QStackedWidget(PropertyStatisticBlockFormClass);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 50, 401, 651));
        page = new QWidget();
        page->setObjectName("page");
        pushButtonEditLibFolder = new QPushButton(page);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(20, 10, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon);
        labelLibFolderName = new QLabel(page);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(140, 10, 241, 31));
        QFont font;
        font.setPointSize(16);
        labelLibFolderName->setFont(font);
        tableWidgetLibList = new QTableWidget(page);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 70, 161, 161));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetGeneratedLibList = new QTableWidget(page);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetGeneratedLibList->setObjectName("tableWidgetGeneratedLibList");
        tableWidgetGeneratedLibList->setGeometry(QRect(230, 70, 161, 161));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSetFrom = new QPushButton(page);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(180, 110, 39, 23));
        pushButtonGetBack = new QPushButton(page);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(180, 150, 39, 23));
        pushButtonEditLibrary = new QPushButton(page);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(80, 240, 211, 41));
        QFont font1;
        font1.setPointSize(12);
        pushButtonEditLibrary->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon1);
        ButtonPickupClearTest = new QPushButton(page);
        ButtonPickupClearTest->setObjectName("ButtonPickupClearTest");
        ButtonPickupClearTest->setGeometry(QRect(10, 350, 181, 31));
        QFont font2;
        font2.setPointSize(11);
        ButtonPickupClearTest->setFont(font2);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupClearTest->setIcon(icon2);
        ButtonPickupTest = new QPushButton(page);
        ButtonPickupTest->setObjectName("ButtonPickupTest");
        ButtonPickupTest->setGeometry(QRect(10, 294, 181, 51));
        ButtonPickupTest->setFont(font2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Extract.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupTest->setIcon(icon3);
        ButtonGenerateLibs = new QPushButton(page);
        ButtonGenerateLibs->setObjectName("ButtonGenerateLibs");
        ButtonGenerateLibs->setGeometry(QRect(200, 290, 191, 91));
        ButtonGenerateLibs->setFont(font2);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonGenerateLibs->setIcon(icon4);
        frame_4 = new QFrame(page);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 390, 381, 251));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Sunken);
        EditLibName = new QLineEdit(frame_4);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 20, 211, 31));
        EditLibName->setFont(font1);
        label_3 = new QLabel(frame_4);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 381, 21));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(frame_4);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 20, 81, 31));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        label_4 = new QLabel(frame_4);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 20, 51, 31));
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNoiseSize = new QSpinBox(frame_4);
        EditNoiseSize->setObjectName("EditNoiseSize");
        EditNoiseSize->setGeometry(QRect(280, 110, 61, 31));
        EditNoiseSize->setFont(font1);
        EditSpaceToOutline = new QSpinBox(frame_4);
        EditSpaceToOutline->setObjectName("EditSpaceToOutline");
        EditSpaceToOutline->setGeometry(QRect(280, 70, 61, 31));
        EditSpaceToOutline->setFont(font1);
        label_16 = new QLabel(frame_4);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(20, 150, 251, 31));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPriority = new QSpinBox(frame_4);
        EditPriority->setObjectName("EditPriority");
        EditPriority->setGeometry(QRect(280, 150, 61, 31));
        EditPriority->setFont(font1);
        label_14 = new QLabel(frame_4);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(20, 70, 251, 31));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_15 = new QLabel(frame_4);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(20, 110, 251, 31));
        label_15->setFrameShape(QFrame::Panel);
        label_15->setFrameShadow(QFrame::Sunken);
        label_15->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibSave = new QPushButton(frame_4);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(10, 200, 341, 41));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon5);
        label_30 = new QLabel(page);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 50, 161, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_31 = new QLabel(page);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(230, 50, 161, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        tableWidgetBlockInfo = new QTableWidget(page_2);
        if (tableWidgetBlockInfo->columnCount() < 4)
            tableWidgetBlockInfo->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetBlockInfo->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetBlockInfo->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetBlockInfo->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetBlockInfo->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        tableWidgetBlockInfo->setObjectName("tableWidgetBlockInfo");
        tableWidgetBlockInfo->setGeometry(QRect(10, 20, 381, 161));
        tableWidgetBlockInfo->setSelectionMode(QAbstractItemView::MultiSelection);
        label_32 = new QLabel(page_2);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(10, 0, 381, 21));
        label_32->setFont(font1);
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameBlockInfoOnMouse = new QFrame(page_2);
        frameBlockInfoOnMouse->setObjectName("frameBlockInfoOnMouse");
        frameBlockInfoOnMouse->setGeometry(QRect(10, 190, 381, 451));
        frameBlockInfoOnMouse->setFrameShape(QFrame::StyledPanel);
        frameBlockInfoOnMouse->setFrameShadow(QFrame::Sunken);
        label_33 = new QLabel(frameBlockInfoOnMouse);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(0, 0, 381, 31));
        label_33->setFont(font1);
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Sunken);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame = new QFrame(frameBlockInfoOnMouse);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 70, 361, 371));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_15 = new QFrame(frame);
        frame_15->setObjectName("frame_15");
        frame_15->setGeometry(QRect(10, 170, 341, 81));
        frame_15->setFrameShape(QFrame::StyledPanel);
        frame_15->setFrameShadow(QFrame::Sunken);
        label_46 = new QLabel(frame_15);
        label_46->setObjectName("label_46");
        label_46->setGeometry(QRect(0, 0, 20, 81));
        label_46->setFrameShape(QFrame::Panel);
        label_46->setFrameShadow(QFrame::Raised);
        label_46->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_46->setIndent(1);
        frame_16 = new QFrame(frame_15);
        frame_16->setObjectName("frame_16");
        frame_16->setGeometry(QRect(10, 120, 371, 101));
        frame_16->setFrameShape(QFrame::StyledPanel);
        frame_16->setFrameShadow(QFrame::Sunken);
        label_47 = new QLabel(frame_16);
        label_47->setObjectName("label_47");
        label_47->setGeometry(QRect(0, 0, 20, 61));
        label_47->setFrameShape(QFrame::Panel);
        label_47->setFrameShadow(QFrame::Raised);
        label_47->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_47->setIndent(1);
        EditAdjustBlack = new QSpinBox(frame_15);
        EditAdjustBlack->setObjectName("EditAdjustBlack");
        EditAdjustBlack->setGeometry(QRect(230, 30, 81, 22));
        EditAdjustBlack->setMaximum(255);
        EditAdjustWhite = new QSpinBox(frame_15);
        EditAdjustWhite->setObjectName("EditAdjustWhite");
        EditAdjustWhite->setGeometry(QRect(230, 50, 81, 22));
        EditAdjustWhite->setMaximum(255);
        label_48 = new QLabel(frame_15);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(30, 50, 191, 21));
        label_48->setFrameShape(QFrame::Panel);
        label_48->setFrameShadow(QFrame::Sunken);
        label_48->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_49 = new QLabel(frame_15);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(30, 30, 191, 21));
        label_49->setFrameShape(QFrame::Panel);
        label_49->setFrameShadow(QFrame::Sunken);
        label_49->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBModeWhiteMask = new QCheckBox(frame);
        checkBModeWhiteMask->setObjectName("checkBModeWhiteMask");
        checkBModeWhiteMask->setGeometry(QRect(30, 270, 141, 18));
        frame_7 = new QFrame(frame);
        frame_7->setObjectName("frame_7");
        frame_7->setGeometry(QRect(10, 50, 341, 101));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Sunken);
        label_35 = new QLabel(frame_7);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(0, 0, 20, 101));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Raised);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_35->setIndent(1);
        label_36 = new QLabel(frame_7);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(250, 10, 81, 21));
        label_36->setFrameShape(QFrame::Panel);
        label_36->setFrameShadow(QFrame::Sunken);
        label_36->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKDotH = new QSpinBox(frame_7);
        EditOKDotH->setObjectName("EditOKDotH");
        EditOKDotH->setGeometry(QRect(250, 50, 81, 22));
        EditOKDotH->setMaximum(99999999);
        label_38 = new QLabel(frame_7);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(30, 50, 121, 21));
        label_38->setFrameShape(QFrame::Panel);
        label_38->setFrameShadow(QFrame::Sunken);
        label_38->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKDotL = new QSpinBox(frame_7);
        EditOKDotL->setObjectName("EditOKDotL");
        EditOKDotL->setGeometry(QRect(160, 50, 81, 22));
        EditOKDotL->setMaximum(99999999);
        label_39 = new QLabel(frame_7);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(160, 10, 81, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKLengthH = new QSpinBox(frame_7);
        EditOKLengthH->setObjectName("EditOKLengthH");
        EditOKLengthH->setGeometry(QRect(250, 70, 81, 22));
        EditOKLengthH->setMaximum(99999999);
        EditOKLengthL = new QSpinBox(frame_7);
        EditOKLengthL->setObjectName("EditOKLengthL");
        EditOKLengthL->setGeometry(QRect(160, 70, 81, 22));
        EditOKLengthL->setMaximum(99999999);
        label_29 = new QLabel(frame_7);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(30, 70, 121, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_17 = new QLabel(frame_7);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(30, 30, 121, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBrightWidthH = new QLineEdit(frame_7);
        EditBrightWidthH->setObjectName("EditBrightWidthH");
        EditBrightWidthH->setGeometry(QRect(250, 30, 81, 20));
        EditBrightWidthL = new QLineEdit(frame_7);
        EditBrightWidthL->setObjectName("EditBrightWidthL");
        EditBrightWidthL->setGeometry(QRect(160, 30, 81, 20));
        checkBModeBlackMask = new QCheckBox(frame);
        checkBModeBlackMask->setObjectName("checkBModeBlackMask");
        checkBModeBlackMask->setGeometry(QRect(190, 270, 141, 18));
        EditLibNameInBlock = new QLineEdit(frame);
        EditLibNameInBlock->setObjectName("EditLibNameInBlock");
        EditLibNameInBlock->setGeometry(QRect(120, 10, 231, 31));
        EditLibNameInBlock->setFont(font1);
        EditLibIDnBlock = new QLineEdit(frame);
        EditLibIDnBlock->setObjectName("EditLibIDnBlock");
        EditLibIDnBlock->setGeometry(QRect(60, 10, 61, 31));
        EditLibIDnBlock->setFont(font1);
        EditLibIDnBlock->setReadOnly(true);
        label_34 = new QLabel(frame);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(10, 10, 51, 31));
        label_34->setFont(font1);
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Sunken);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        stackedWidget->addWidget(page_2);
        toolButtonLibrary = new QToolButton(PropertyStatisticBlockFormClass);
        toolButtonLibrary->setObjectName("toolButtonLibrary");
        toolButtonLibrary->setGeometry(QRect(20, 10, 121, 31));
        toolButtonLibrary->setCheckable(true);
        toolButtonLibrary->setChecked(true);
        toolButtonLibrary->setAutoExclusive(true);

        retranslateUi(PropertyStatisticBlockFormClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PropertyStatisticBlockFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyStatisticBlockFormClass)
    {
        PropertyStatisticBlockFormClass->setWindowTitle(QCoreApplication::translate("PropertyStatisticBlockFormClass", "PropertyStatisticBlockForm", nullptr));
        toolButtonCreateBlock->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "Create Block", nullptr));
        toolButtonEdge->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "E", nullptr));
        toolButtonArea->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "A", nullptr));
        toolButtonInside->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "I", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\357\274\270\357\274\270\357\274\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "Name", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "=>", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "<=", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        ButtonPickupClearTest->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\346\212\275\345\207\272\343\201\256\343\202\257\343\203\252\343\202\242", nullptr));
        ButtonPickupTest->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\345\215\230\344\270\200\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\343\201\256\346\212\275\345\207\272", nullptr));
        ButtonGenerateLibs->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\344\270\212\343\201\256\345\205\250\343\201\246\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\347\224\237\346\210\220", nullptr));
        EditLibName->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "Library Name", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\227\343\203\255\343\203\221\343\203\206\343\202\243", nullptr));
        EditLibID->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "12345", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\345\220\215\347\247\260", nullptr));
        label_16->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\345\204\252\345\205\210\345\272\246", nullptr));
        label_14->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\350\274\252\351\203\255\343\201\213\343\202\211\343\201\256\351\226\223\351\232\224", nullptr));
        label_15->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\343\203\207\343\203\274\343\202\277\343\203\231\343\203\274\343\202\271\343\201\270\343\201\256\346\233\264\346\226\260", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetBlockInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetBlockInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetBlockInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\343\203\226\343\203\255\343\203\203\343\202\257\347\267\217\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetBlockInfo->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\343\203\254\343\202\244\343\203\244\343\203\274\357\274\221", nullptr));
        label_32->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\344\275\277\347\224\250\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\226\343\203\255\343\203\203\343\202\257\346\203\205\345\240\261", nullptr));
        label_33->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\343\203\236\343\202\246\343\202\271\343\202\253\343\203\274\343\202\275\343\203\253\344\275\215\347\275\256\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\346\203\205\345\240\261", nullptr));
        label_46->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\350\243\234\n"
"\346\255\243", nullptr));
        label_47->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\350\274\235\n"
"\345\272\246", nullptr));
        label_48->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_49->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        checkBModeWhiteMask->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\347\231\275\343\203\236\343\202\271\343\202\257", nullptr));
        label_35->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\343\203\241\n"
"\343\202\244\n"
"\343\203\263", nullptr));
        label_36->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\346\230\216\345\201\264", nullptr));
        label_38->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_39->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\346\232\227\345\201\264", nullptr));
        label_29->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\343\201\223\343\202\214\344\273\245\344\270\212\343\201\256\351\225\267\343\201\225\343\201\247\357\274\256\357\274\247", nullptr));
        label_17->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "OK\343\201\256\346\250\231\346\272\226\345\201\217\345\267\256\345\200\215\347\216\207", nullptr));
        checkBModeBlackMask->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\351\273\222\343\203\236\343\202\271\343\202\257", nullptr));
        EditLibNameInBlock->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "Library Name", nullptr));
        EditLibIDnBlock->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "12345", nullptr));
        label_34->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "\345\220\215\347\247\260", nullptr));
        toolButtonLibrary->setText(QCoreApplication::translate("PropertyStatisticBlockFormClass", "Library Test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyStatisticBlockFormClass: public Ui_PropertyStatisticBlockFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYSTATISTICBLOCKFORM_H
