/********************************************************************************
** Form generated from reading UI file 'PropertyAlignmentFlexAreaForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYALIGNMENTFLEXAREAFORM_H
#define UI_PROPERTYALIGNMENTFLEXAREAFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyAlignmentFlexAreaForm
{
public:
    QFrame *frame;
    QToolButton *toolButtonGenerate;
    QLabel *label_32;
    QToolButton *toolButtonOutline;
    QToolButton *toolButtonMark;
    QFrame *frame_8;
    QToolButton *toolButtonAlignmrntFlexAreaArea;
    QStackedWidget *stackedWidgetMatchingType;
    QWidget *WholeMatch;
    QToolButton *toolButtonWholeMatch;
    QWidget *BaseMatch;
    QToolButton *toolButtonBaseMatch;
    QStackedWidget *stackedWidgetArea;
    QWidget *page;
    QFrame *frame_5;
    QLabel *label_6;
    QTableWidget *tableWidgetArea;
    QWidget *page_2;
    QFrame *frame_9;
    QLabel *label_8;
    QTableWidget *tableWidgetWholeMatch;
    QWidget *page_3;
    QLabel *label;
    QTableWidget *tableWidgetBaseMatch;
    QPushButton *pushButtonGenerateBaseMatch;
    QPushButton *pushButtonExecuteBaseMatch;
    QTabWidget *tabWidgetPoint;
    QWidget *tab;
    QFrame *frame_7;
    QLabel *label_7;
    QPushButton *pushButtonClearPickup;
    QPushButton *pushButtonPickupTest;
    QFrame *frame_3;
    QPushButton *ButtonLibSave;
    QLabel *label_3;
    QLineEdit *EditLibName;
    QLabel *label_4;
    QLineEdit *EditLibID;
    QFrame *frame_15;
    QSpinBox *EditExpansionDot;
    QLabel *label_58;
    QSpinBox *EditLimitSize;
    QLabel *label_59;
    QLabel *label_63;
    QFrame *frame_6;
    QSpinBox *EditMinAreaSize;
    QLabel *label_11;
    QSpinBox *EditMaxAreaSize;
    QLabel *label_12;
    QSpinBox *EditMinAreaDots;
    QLabel *label_13;
    QSpinBox *EditMaxAreaDots;
    QLabel *label_14;
    QLabel *label_34;
    QPushButton *pushButtonGenerate;
    QFrame *frame_2;
    QLabel *label_31;
    QPushButton *pushButtonSetFromAll;
    QTableWidget *tableWidgetGeneratedLibList;
    QPushButton *pushButtonGetBackAll;
    QPushButton *pushButtonGetBack;
    QLabel *labelLibFolderName;
    QTableWidget *tableWidgetLibList;
    QPushButton *pushButtonEditLibFolder;
    QLabel *label_30;
    QPushButton *pushButtonSetFrom;
    QPushButton *pushButtonEditLibrary;
    QWidget *tab_2;
    QFrame *frame_4;
    QLabel *label_5;
    QTableWidget *tableWidgetAlignmentFlexAreaInfo;
    QFrame *frame_10;
    QLabel *label_9;
    QTableWidget *tableWidgetMarkList;

    void setupUi(GUIFormBase *PropertyAlignmentFlexAreaForm)
    {
        if (PropertyAlignmentFlexAreaForm->objectName().isEmpty())
            PropertyAlignmentFlexAreaForm->setObjectName("PropertyAlignmentFlexAreaForm");
        PropertyAlignmentFlexAreaForm->resize(400, 968);
        frame = new QFrame(PropertyAlignmentFlexAreaForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 0, 381, 56));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        toolButtonGenerate = new QToolButton(frame);
        toolButtonGenerate->setObjectName("toolButtonGenerate");
        toolButtonGenerate->setGeometry(QRect(440, 20, 121, 31));
        toolButtonGenerate->setCheckable(true);
        toolButtonGenerate->setChecked(false);
        toolButtonGenerate->setAutoExclusive(false);
        label_32 = new QLabel(frame);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(0, 0, 381, 20));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        toolButtonOutline = new QToolButton(frame);
        toolButtonOutline->setObjectName("toolButtonOutline");
        toolButtonOutline->setGeometry(QRect(290, 20, 81, 31));
        toolButtonOutline->setCheckable(true);
        toolButtonOutline->setChecked(false);
        toolButtonOutline->setAutoExclusive(true);
        toolButtonMark = new QToolButton(frame);
        toolButtonMark->setObjectName("toolButtonMark");
        toolButtonMark->setGeometry(QRect(680, 20, 81, 31));
        toolButtonMark->setCheckable(true);
        toolButtonMark->setChecked(false);
        toolButtonMark->setAutoExclusive(false);
        frame_8 = new QFrame(frame);
        frame_8->setObjectName("frame_8");
        frame_8->setGeometry(QRect(10, 20, 271, 31));
        frame_8->setFrameShape(QFrame::StyledPanel);
        frame_8->setFrameShadow(QFrame::Raised);
        toolButtonAlignmrntFlexAreaArea = new QToolButton(frame_8);
        toolButtonAlignmrntFlexAreaArea->setObjectName("toolButtonAlignmrntFlexAreaArea");
        toolButtonAlignmrntFlexAreaArea->setGeometry(QRect(0, 0, 141, 31));
        toolButtonAlignmrntFlexAreaArea->setCheckable(true);
        toolButtonAlignmrntFlexAreaArea->setChecked(false);
        toolButtonAlignmrntFlexAreaArea->setAutoExclusive(true);
        stackedWidgetMatchingType = new QStackedWidget(frame_8);
        stackedWidgetMatchingType->setObjectName("stackedWidgetMatchingType");
        stackedWidgetMatchingType->setGeometry(QRect(140, 0, 131, 31));
        WholeMatch = new QWidget();
        WholeMatch->setObjectName("WholeMatch");
        toolButtonWholeMatch = new QToolButton(WholeMatch);
        toolButtonWholeMatch->setObjectName("toolButtonWholeMatch");
        toolButtonWholeMatch->setGeometry(QRect(10, 0, 121, 31));
        toolButtonWholeMatch->setCheckable(true);
        toolButtonWholeMatch->setChecked(false);
        toolButtonWholeMatch->setAutoExclusive(true);
        stackedWidgetMatchingType->addWidget(WholeMatch);
        BaseMatch = new QWidget();
        BaseMatch->setObjectName("BaseMatch");
        toolButtonBaseMatch = new QToolButton(BaseMatch);
        toolButtonBaseMatch->setObjectName("toolButtonBaseMatch");
        toolButtonBaseMatch->setGeometry(QRect(10, 0, 121, 31));
        toolButtonBaseMatch->setCheckable(true);
        toolButtonBaseMatch->setChecked(false);
        toolButtonBaseMatch->setAutoExclusive(true);
        stackedWidgetMatchingType->addWidget(BaseMatch);
        stackedWidgetArea = new QStackedWidget(PropertyAlignmentFlexAreaForm);
        stackedWidgetArea->setObjectName("stackedWidgetArea");
        stackedWidgetArea->setGeometry(QRect(10, 60, 391, 241));
        page = new QWidget();
        page->setObjectName("page");
        frame_5 = new QFrame(page);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(0, 0, 381, 241));
        frame_5->setFrameShape(QFrame::Panel);
        frame_5->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(frame_5);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 0, 381, 21));
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetArea = new QTableWidget(frame_5);
        if (tableWidgetArea->columnCount() < 4)
            tableWidgetArea->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetArea->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetArea->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetArea->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetArea->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetArea->setObjectName("tableWidgetArea");
        tableWidgetArea->setGeometry(QRect(10, 20, 361, 211));
        tableWidgetArea->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetArea->setSelectionBehavior(QAbstractItemView::SelectRows);
        stackedWidgetArea->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        frame_9 = new QFrame(page_2);
        frame_9->setObjectName("frame_9");
        frame_9->setGeometry(QRect(0, 0, 381, 241));
        frame_9->setFrameShape(QFrame::Panel);
        frame_9->setFrameShadow(QFrame::Sunken);
        label_8 = new QLabel(frame_9);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 0, 381, 21));
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetWholeMatch = new QTableWidget(frame_9);
        if (tableWidgetWholeMatch->columnCount() < 3)
            tableWidgetWholeMatch->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetWholeMatch->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetWholeMatch->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetWholeMatch->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        tableWidgetWholeMatch->setObjectName("tableWidgetWholeMatch");
        tableWidgetWholeMatch->setGeometry(QRect(10, 20, 361, 211));
        tableWidgetWholeMatch->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetWholeMatch->setSelectionBehavior(QAbstractItemView::SelectRows);
        stackedWidgetArea->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        label = new QLabel(page_3);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 0, 271, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        tableWidgetBaseMatch = new QTableWidget(page_3);
        if (tableWidgetBaseMatch->columnCount() < 3)
            tableWidgetBaseMatch->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetBaseMatch->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetBaseMatch->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetBaseMatch->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        tableWidgetBaseMatch->setObjectName("tableWidgetBaseMatch");
        tableWidgetBaseMatch->setGeometry(QRect(100, 20, 271, 221));
        tableWidgetBaseMatch->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetBaseMatch->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonGenerateBaseMatch = new QPushButton(page_3);
        pushButtonGenerateBaseMatch->setObjectName("pushButtonGenerateBaseMatch");
        pushButtonGenerateBaseMatch->setGeometry(QRect(0, 20, 91, 34));
        pushButtonExecuteBaseMatch = new QPushButton(page_3);
        pushButtonExecuteBaseMatch->setObjectName("pushButtonExecuteBaseMatch");
        pushButtonExecuteBaseMatch->setGeometry(QRect(0, 70, 91, 34));
        stackedWidgetArea->addWidget(page_3);
        tabWidgetPoint = new QTabWidget(PropertyAlignmentFlexAreaForm);
        tabWidgetPoint->setObjectName("tabWidgetPoint");
        tabWidgetPoint->setGeometry(QRect(10, 310, 381, 621));
        tab = new QWidget();
        tab->setObjectName("tab");
        frame_7 = new QFrame(tab);
        frame_7->setObjectName("frame_7");
        frame_7->setGeometry(QRect(0, 0, 381, 591));
        frame_7->setFrameShape(QFrame::Panel);
        frame_7->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frame_7);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 0, 381, 21));
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonClearPickup = new QPushButton(frame_7);
        pushButtonClearPickup->setObjectName("pushButtonClearPickup");
        pushButtonClearPickup->setGeometry(QRect(10, 550, 181, 31));
        pushButtonPickupTest = new QPushButton(frame_7);
        pushButtonPickupTest->setObjectName("pushButtonPickupTest");
        pushButtonPickupTest->setGeometry(QRect(10, 510, 181, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonPickupTest->setIcon(icon);
        frame_3 = new QFrame(frame_7);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 256, 361, 251));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        ButtonLibSave = new QPushButton(frame_3);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(10, 214, 341, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon1);
        label_3 = new QLabel(frame_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 371, 21));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibName = new QLineEdit(frame_3);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 20, 211, 21));
        QFont font;
        font.setPointSize(12);
        EditLibName->setFont(font);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 20, 51, 21));
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(frame_3);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 20, 81, 21));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        frame_15 = new QFrame(frame_3);
        frame_15->setObjectName("frame_15");
        frame_15->setGeometry(QRect(10, 150, 341, 61));
        frame_15->setFrameShape(QFrame::StyledPanel);
        frame_15->setFrameShadow(QFrame::Sunken);
        EditExpansionDot = new QSpinBox(frame_15);
        EditExpansionDot->setObjectName("EditExpansionDot");
        EditExpansionDot->setGeometry(QRect(230, 4, 81, 22));
        EditExpansionDot->setMaximum(1000000);
        label_58 = new QLabel(frame_15);
        label_58->setObjectName("label_58");
        label_58->setGeometry(QRect(40, 30, 191, 21));
        label_58->setFrameShape(QFrame::Panel);
        label_58->setFrameShadow(QFrame::Sunken);
        label_58->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLimitSize = new QSpinBox(frame_15);
        EditLimitSize->setObjectName("EditLimitSize");
        EditLimitSize->setGeometry(QRect(230, 30, 81, 22));
        EditLimitSize->setMaximum(1000000);
        label_59 = new QLabel(frame_15);
        label_59->setObjectName("label_59");
        label_59->setGeometry(QRect(40, 4, 191, 21));
        label_59->setFrameShape(QFrame::Panel);
        label_59->setFrameShadow(QFrame::Sunken);
        label_59->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_63 = new QLabel(frame_15);
        label_63->setObjectName("label_63");
        label_63->setGeometry(QRect(0, 0, 31, 61));
        label_63->setFrameShape(QFrame::Panel);
        label_63->setFrameShadow(QFrame::Raised);
        label_63->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_63->setIndent(1);
        frame_6 = new QFrame(frame_3);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(10, 50, 341, 101));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Sunken);
        EditMinAreaSize = new QSpinBox(frame_6);
        EditMinAreaSize->setObjectName("EditMinAreaSize");
        EditMinAreaSize->setGeometry(QRect(230, 4, 81, 22));
        EditMinAreaSize->setMaximum(1000000);
        label_11 = new QLabel(frame_6);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(42, 26, 191, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxAreaSize = new QSpinBox(frame_6);
        EditMaxAreaSize->setObjectName("EditMaxAreaSize");
        EditMaxAreaSize->setGeometry(QRect(230, 26, 81, 22));
        EditMaxAreaSize->setMaximum(1000000);
        label_12 = new QLabel(frame_6);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(42, 4, 191, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinAreaDots = new QSpinBox(frame_6);
        EditMinAreaDots->setObjectName("EditMinAreaDots");
        EditMinAreaDots->setGeometry(QRect(230, 50, 101, 22));
        EditMinAreaDots->setMaximum(2000000000);
        label_13 = new QLabel(frame_6);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(42, 50, 191, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxAreaDots = new QSpinBox(frame_6);
        EditMaxAreaDots->setObjectName("EditMaxAreaDots");
        EditMaxAreaDots->setGeometry(QRect(230, 70, 101, 22));
        EditMaxAreaDots->setMinimum(-1);
        EditMaxAreaDots->setMaximum(2000000000);
        EditMaxAreaDots->setValue(2000000000);
        label_14 = new QLabel(frame_6);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(42, 70, 191, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_34 = new QLabel(frame_6);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(0, 0, 31, 101));
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Raised);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_34->setIndent(1);
        pushButtonGenerate = new QPushButton(frame_7);
        pushButtonGenerate->setObjectName("pushButtonGenerate");
        pushButtonGenerate->setGeometry(QRect(210, 510, 161, 71));
        pushButtonGenerate->setIcon(icon);
        frame_2 = new QFrame(frame_7);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 20, 361, 231));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_31 = new QLabel(frame_2);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(200, 40, 151, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSetFromAll = new QPushButton(frame_2);
        pushButtonSetFromAll->setObjectName("pushButtonSetFromAll");
        pushButtonSetFromAll->setGeometry(QRect(160, 160, 39, 23));
        tableWidgetGeneratedLibList = new QTableWidget(frame_2);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem11);
        tableWidgetGeneratedLibList->setObjectName("tableWidgetGeneratedLibList");
        tableWidgetGeneratedLibList->setGeometry(QRect(200, 60, 151, 121));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonGetBackAll = new QPushButton(frame_2);
        pushButtonGetBackAll->setObjectName("pushButtonGetBackAll");
        pushButtonGetBackAll->setGeometry(QRect(160, 190, 39, 23));
        pushButtonGetBack = new QPushButton(frame_2);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(160, 110, 39, 23));
        labelLibFolderName = new QLabel(frame_2);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(120, 4, 241, 31));
        QFont font1;
        font1.setPointSize(16);
        labelLibFolderName->setFont(font1);
        tableWidgetLibList = new QTableWidget(frame_2);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem13);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 60, 147, 161));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonEditLibFolder = new QPushButton(frame_2);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(10, 4, 101, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon2);
        label_30 = new QLabel(frame_2);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 40, 151, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSetFrom = new QPushButton(frame_2);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(160, 80, 39, 23));
        pushButtonEditLibrary = new QPushButton(frame_2);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(200, 190, 151, 31));
        tabWidgetPoint->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        frame_4 = new QFrame(tab_2);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(0, 10, 371, 191));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(frame_4);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 0, 371, 21));
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetAlignmentFlexAreaInfo = new QTableWidget(frame_4);
        if (tableWidgetAlignmentFlexAreaInfo->columnCount() < 1)
            tableWidgetAlignmentFlexAreaInfo->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidgetAlignmentFlexAreaInfo->setHorizontalHeaderItem(0, __qtablewidgetitem14);
        tableWidgetAlignmentFlexAreaInfo->setObjectName("tableWidgetAlignmentFlexAreaInfo");
        tableWidgetAlignmentFlexAreaInfo->setGeometry(QRect(10, 20, 351, 161));
        tableWidgetAlignmentFlexAreaInfo->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAlignmentFlexAreaInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame_10 = new QFrame(tab_2);
        frame_10->setObjectName("frame_10");
        frame_10->setGeometry(QRect(0, 210, 371, 371));
        frame_10->setFrameShape(QFrame::StyledPanel);
        frame_10->setFrameShadow(QFrame::Sunken);
        label_9 = new QLabel(frame_10);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(0, 0, 371, 21));
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetMarkList = new QTableWidget(frame_10);
        if (tableWidgetMarkList->columnCount() < 3)
            tableWidgetMarkList->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidgetMarkList->setHorizontalHeaderItem(0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidgetMarkList->setHorizontalHeaderItem(1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidgetMarkList->setHorizontalHeaderItem(2, __qtablewidgetitem17);
        tableWidgetMarkList->setObjectName("tableWidgetMarkList");
        tableWidgetMarkList->setGeometry(QRect(10, 20, 351, 341));
        tableWidgetMarkList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetMarkList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tabWidgetPoint->addTab(tab_2, QString());

        retranslateUi(PropertyAlignmentFlexAreaForm);

        stackedWidgetMatchingType->setCurrentIndex(1);
        stackedWidgetArea->setCurrentIndex(0);
        tabWidgetPoint->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PropertyAlignmentFlexAreaForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyAlignmentFlexAreaForm)
    {
        PropertyAlignmentFlexAreaForm->setWindowTitle(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Form", nullptr));
        toolButtonGenerate->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\343\203\235\343\202\244\343\203\263\343\203\210\347\224\237\346\210\220", nullptr));
        label_32->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\346\217\217\347\224\273", nullptr));
        toolButtonOutline->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\350\274\252\351\203\255\351\240\230\345\237\237", nullptr));
        toolButtonMark->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\343\203\236\343\203\274\343\202\257", nullptr));
        toolButtonAlignmrntFlexAreaArea->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\343\202\242\343\203\251\343\202\244\343\203\263\343\203\241\343\203\263\343\203\210\351\240\230\345\237\237", nullptr));
        toolButtonWholeMatch->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\345\244\247\345\237\237\346\216\242\347\264\242\351\240\230\345\237\237", nullptr));
        toolButtonBaseMatch->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\343\203\231\343\203\274\343\202\271\343\203\236\343\203\203\343\203\201", nullptr));
        label_6->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\343\202\242\343\203\251\343\202\244\343\203\263\343\203\241\343\203\263\343\203\210\351\240\230\345\237\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetArea->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetArea->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "AreaID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetArea->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Name/Pos", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetArea->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Type", nullptr));
        label_8->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\345\205\250\344\275\223\343\203\236\343\203\203\343\203\201\343\203\263\343\202\260\351\240\230\345\237\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetWholeMatch->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetWholeMatch->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetWholeMatch->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Division", nullptr));
        label->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\350\247\222\345\272\246\343\203\236\343\203\203\343\203\201\343\203\263\343\202\260\346\203\205\345\240\261", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetBaseMatch->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "No", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetBaseMatch->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Angle", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetBaseMatch->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Matching", nullptr));
        pushButtonGenerateBaseMatch->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\347\224\237\346\210\220", nullptr));
        pushButtonExecuteBaseMatch->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\343\203\236\343\203\203\343\203\201\343\203\263\343\202\260", nullptr));
        label_7->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\343\203\235\343\202\244\343\203\263\343\203\210\351\240\230\345\237\237", nullptr));
        pushButtonClearPickup->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Clear", nullptr));
        pushButtonPickupTest->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\346\212\275\345\207\272\343\203\206\343\202\271\343\203\210", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\343\203\207\343\203\274\343\202\277\343\203\231\343\203\274\343\202\271\343\201\270\343\201\256\346\233\264\346\226\260", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\227\343\203\255\343\203\221\343\203\206\343\202\243", nullptr));
        EditLibName->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Library Name", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "12345", nullptr));
        label_58->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\351\231\220\347\225\214\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_59->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210", nullptr));
        label_63->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "<html><head/><body><p>\347\224\237</p><p>\346\210\220</p></body></html>", nullptr));
        label_11->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\351\240\230\345\237\237\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_12->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\351\240\230\345\237\237\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_13->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\351\240\230\345\237\237\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_14->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\351\240\230\345\237\237\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_34->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\343\202\265\n"
"\343\202\244\n"
"\343\202\272", nullptr));
        pushButtonGenerate->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\347\224\237\346\210\220", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "=>>", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Name", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "<<=", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "<=", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\357\274\270\357\274\270\357\274\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Name", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "=>", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Edit library", nullptr));
        tabWidgetPoint->setTabText(tabWidgetPoint->indexOf(tab), QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Point generation", nullptr));
        label_5->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "\347\224\237\346\210\220\343\201\225\343\202\214\343\201\237\351\240\230\345\237\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidgetAlignmentFlexAreaInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "LibID", nullptr));
        label_9->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Point list", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidgetMarkList->horizontalHeaderItem(0);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidgetMarkList->horizontalHeaderItem(1);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidgetMarkList->horizontalHeaderItem(2);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Search", nullptr));
        tabWidgetPoint->setTabText(tabWidgetPoint->indexOf(tab_2), QCoreApplication::translate("PropertyAlignmentFlexAreaForm", "Point", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyAlignmentFlexAreaForm: public Ui_PropertyAlignmentFlexAreaForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYALIGNMENTFLEXAREAFORM_H
