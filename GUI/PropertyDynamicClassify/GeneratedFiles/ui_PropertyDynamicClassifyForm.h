/********************************************************************************
** Form generated from reading UI file 'PropertyDynamicClassifyForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYDYNAMICCLASSIFYFORM_H
#define UI_PROPERTYDYNAMICCLASSIFYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyDynamicClassifyFormClass
{
public:
    QPushButton *ButtonPickupClearTest;
    QLabel *label_31;
    QTableWidget *tableWidgetLibList;
    QTableWidget *tableWidgetGeneratedLibList;
    QPushButton *pushButtonSetFrom;
    QPushButton *pushButtonGetBack;
    QPushButton *pushButtonEditLibrary;
    QLabel *label_30;
    QFrame *frame_4;
    QLineEdit *EditLibName;
    QLabel *label_3;
    QLineEdit *EditLibID;
    QLabel *label_4;
    QPushButton *ButtonLibSave;
    QFrame *frame_5;
    QLabel *label_14;
    QSpinBox *EditVariableWidth;
    QLabel *label_15;
    QSpinBox *EditNoiseSize;
    QLabel *label_16;
    QSpinBox *EditPriority;
    QLabel *label_53;
    QLabel *label_17;
    QSpinBox *EditShrinkDot;
    QFrame *frame_6;
    QSpinBox *EditMinBlockSize;
    QLabel *label_9;
    QSpinBox *EditMaxBlockSize;
    QLabel *label_10;
    QSpinBox *EditMinBlockDots;
    QLabel *label_12;
    QSpinBox *EditMaxBlockDots;
    QLabel *label_11;
    QLabel *label_54;
    QPushButton *pushButtonSetFromAll;
    QPushButton *pushButtonGetBackAll;
    QPushButton *pushButtonEditLibFolder;
    QLabel *labelLibFolderName;
    QPushButton *ButtonGenerateLibs;
    QPushButton *ButtonPickupTest;
    QFrame *frame;
    QLabel *label;
    QToolButton *toolButtonCoreArea;
    QToolButton *toolButtonMaxZone;
    QToolButton *toolButtonOutlineIArea;
    QToolButton *toolButtonOutlineTArea;
    QToolButton *toolButtonOutlineOArea;
    QToolButton *toolButtonBareArea;
    QToolButton *toolButtonInsideArea;
    QLabel *label_2;
    QLabel *label_5;
    QToolButton *toolButtonMinZone;
    QFrame *frame_2;
    QLabel *label_6;
    QTableWidget *tableWidgetAreaList;

    void setupUi(GUIFormBase *PropertyDynamicClassifyFormClass)
    {
        if (PropertyDynamicClassifyFormClass->objectName().isEmpty())
            PropertyDynamicClassifyFormClass->setObjectName("PropertyDynamicClassifyFormClass");
        PropertyDynamicClassifyFormClass->resize(400, 869);
        ButtonPickupClearTest = new QPushButton(PropertyDynamicClassifyFormClass);
        ButtonPickupClearTest->setObjectName("ButtonPickupClearTest");
        ButtonPickupClearTest->setGeometry(QRect(10, 350, 181, 31));
        QFont font;
        font.setPointSize(11);
        ButtonPickupClearTest->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupClearTest->setIcon(icon);
        label_31 = new QLabel(PropertyDynamicClassifyFormClass);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(230, 136, 161, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetLibList = new QTableWidget(PropertyDynamicClassifyFormClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 156, 161, 141));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetGeneratedLibList = new QTableWidget(PropertyDynamicClassifyFormClass);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetGeneratedLibList->setObjectName("tableWidgetGeneratedLibList");
        tableWidgetGeneratedLibList->setGeometry(QRect(230, 156, 161, 111));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSetFrom = new QPushButton(PropertyDynamicClassifyFormClass);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(180, 160, 39, 23));
        pushButtonGetBack = new QPushButton(PropertyDynamicClassifyFormClass);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(180, 190, 39, 23));
        pushButtonEditLibrary = new QPushButton(PropertyDynamicClassifyFormClass);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(230, 270, 161, 31));
        QFont font1;
        font1.setPointSize(12);
        pushButtonEditLibrary->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon1);
        label_30 = new QLabel(PropertyDynamicClassifyFormClass);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 136, 161, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_4 = new QFrame(PropertyDynamicClassifyFormClass);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 390, 381, 301));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Sunken);
        EditLibName = new QLineEdit(frame_4);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 20, 231, 21));
        EditLibName->setFont(font1);
        label_3 = new QLabel(frame_4);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 381, 21));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(frame_4);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 20, 81, 21));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        label_4 = new QLabel(frame_4);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 20, 51, 21));
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibSave = new QPushButton(frame_4);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(10, 250, 361, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon2);
        frame_5 = new QFrame(frame_4);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 160, 361, 81));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Sunken);
        label_14 = new QLabel(frame_5);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(40, 10, 171, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditVariableWidth = new QSpinBox(frame_5);
        EditVariableWidth->setObjectName("EditVariableWidth");
        EditVariableWidth->setGeometry(QRect(210, 10, 61, 23));
        label_15 = new QLabel(frame_5);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(40, 30, 171, 21));
        label_15->setFrameShape(QFrame::Panel);
        label_15->setFrameShadow(QFrame::Sunken);
        label_15->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNoiseSize = new QSpinBox(frame_5);
        EditNoiseSize->setObjectName("EditNoiseSize");
        EditNoiseSize->setGeometry(QRect(210, 30, 61, 23));
        QFont font2;
        font2.setPointSize(9);
        EditNoiseSize->setFont(font2);
        label_16 = new QLabel(frame_5);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(280, 10, 71, 21));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPriority = new QSpinBox(frame_5);
        EditPriority->setObjectName("EditPriority");
        EditPriority->setGeometry(QRect(280, 30, 61, 23));
        EditPriority->setFont(font2);
        label_53 = new QLabel(frame_5);
        label_53->setObjectName("label_53");
        label_53->setGeometry(QRect(0, 0, 31, 81));
        label_53->setFrameShape(QFrame::Panel);
        label_53->setFrameShadow(QFrame::Raised);
        label_53->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_53->setIndent(1);
        label_17 = new QLabel(frame_5);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(40, 50, 171, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditShrinkDot = new QSpinBox(frame_5);
        EditShrinkDot->setObjectName("EditShrinkDot");
        EditShrinkDot->setGeometry(QRect(210, 50, 61, 23));
        EditShrinkDot->setFont(font2);
        EditShrinkDot->setMinimum(-99);
        frame_6 = new QFrame(frame_4);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(10, 50, 361, 111));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Sunken);
        EditMinBlockSize = new QSpinBox(frame_6);
        EditMinBlockSize->setObjectName("EditMinBlockSize");
        EditMinBlockSize->setGeometry(QRect(160, 10, 81, 22));
        EditMinBlockSize->setMaximum(1000000);
        label_9 = new QLabel(frame_6);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(40, 30, 111, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxBlockSize = new QSpinBox(frame_6);
        EditMaxBlockSize->setObjectName("EditMaxBlockSize");
        EditMaxBlockSize->setGeometry(QRect(160, 30, 81, 22));
        EditMaxBlockSize->setMaximum(1000000);
        label_10 = new QLabel(frame_6);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(40, 10, 111, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinBlockDots = new QSpinBox(frame_6);
        EditMinBlockDots->setObjectName("EditMinBlockDots");
        EditMinBlockDots->setGeometry(QRect(160, 60, 81, 22));
        EditMinBlockDots->setMaximum(2000000000);
        label_12 = new QLabel(frame_6);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(40, 60, 111, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxBlockDots = new QSpinBox(frame_6);
        EditMaxBlockDots->setObjectName("EditMaxBlockDots");
        EditMaxBlockDots->setGeometry(QRect(160, 80, 81, 22));
        EditMaxBlockDots->setMaximum(2000000000);
        EditMaxBlockDots->setValue(2000000000);
        label_11 = new QLabel(frame_6);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(40, 80, 111, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_54 = new QLabel(frame_6);
        label_54->setObjectName("label_54");
        label_54->setGeometry(QRect(0, 0, 31, 111));
        label_54->setFrameShape(QFrame::Panel);
        label_54->setFrameShadow(QFrame::Raised);
        label_54->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_54->setIndent(1);
        pushButtonSetFromAll = new QPushButton(PropertyDynamicClassifyFormClass);
        pushButtonSetFromAll->setObjectName("pushButtonSetFromAll");
        pushButtonSetFromAll->setGeometry(QRect(180, 240, 39, 23));
        pushButtonGetBackAll = new QPushButton(PropertyDynamicClassifyFormClass);
        pushButtonGetBackAll->setObjectName("pushButtonGetBackAll");
        pushButtonGetBackAll->setGeometry(QRect(180, 270, 39, 23));
        pushButtonEditLibFolder = new QPushButton(PropertyDynamicClassifyFormClass);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(20, 96, 101, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon3);
        labelLibFolderName = new QLabel(PropertyDynamicClassifyFormClass);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(140, 96, 241, 31));
        QFont font3;
        font3.setPointSize(16);
        labelLibFolderName->setFont(font3);
        ButtonGenerateLibs = new QPushButton(PropertyDynamicClassifyFormClass);
        ButtonGenerateLibs->setObjectName("ButtonGenerateLibs");
        ButtonGenerateLibs->setGeometry(QRect(200, 310, 191, 71));
        ButtonGenerateLibs->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonGenerateLibs->setIcon(icon4);
        ButtonPickupTest = new QPushButton(PropertyDynamicClassifyFormClass);
        ButtonPickupTest->setObjectName("ButtonPickupTest");
        ButtonPickupTest->setGeometry(QRect(10, 304, 181, 41));
        ButtonPickupTest->setFont(font);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Extract.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupTest->setIcon(icon5);
        frame = new QFrame(PropertyDynamicClassifyFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 381, 81));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 381, 16));
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        toolButtonCoreArea = new QToolButton(frame);
        toolButtonCoreArea->setObjectName("toolButtonCoreArea");
        toolButtonCoreArea->setGeometry(QRect(10, 40, 121, 19));
        toolButtonCoreArea->setCheckable(true);
        toolButtonCoreArea->setChecked(true);
        toolButtonMaxZone = new QToolButton(frame);
        toolButtonMaxZone->setObjectName("toolButtonMaxZone");
        toolButtonMaxZone->setGeometry(QRect(10, 60, 61, 19));
        toolButtonMaxZone->setCheckable(true);
        toolButtonOutlineIArea = new QToolButton(frame);
        toolButtonOutlineIArea->setObjectName("toolButtonOutlineIArea");
        toolButtonOutlineIArea->setGeometry(QRect(150, 60, 71, 19));
        toolButtonOutlineIArea->setCheckable(true);
        toolButtonOutlineTArea = new QToolButton(frame);
        toolButtonOutlineTArea->setObjectName("toolButtonOutlineTArea");
        toolButtonOutlineTArea->setGeometry(QRect(220, 60, 71, 19));
        toolButtonOutlineTArea->setCheckable(true);
        toolButtonOutlineOArea = new QToolButton(frame);
        toolButtonOutlineOArea->setObjectName("toolButtonOutlineOArea");
        toolButtonOutlineOArea->setGeometry(QRect(290, 60, 71, 19));
        toolButtonOutlineOArea->setCheckable(true);
        toolButtonBareArea = new QToolButton(frame);
        toolButtonBareArea->setObjectName("toolButtonBareArea");
        toolButtonBareArea->setGeometry(QRect(150, 40, 71, 19));
        toolButtonBareArea->setCheckable(true);
        toolButtonInsideArea = new QToolButton(frame);
        toolButtonInsideArea->setObjectName("toolButtonInsideArea");
        toolButtonInsideArea->setGeometry(QRect(220, 40, 71, 19));
        toolButtonInsideArea->setCheckable(true);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 20, 121, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(150, 20, 221, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        toolButtonMinZone = new QToolButton(frame);
        toolButtonMinZone->setObjectName("toolButtonMinZone");
        toolButtonMinZone->setGeometry(QRect(70, 60, 61, 19));
        toolButtonMinZone->setCheckable(true);
        frame_2 = new QFrame(PropertyDynamicClassifyFormClass);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 700, 381, 161));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(frame_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 0, 381, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetAreaList = new QTableWidget(frame_2);
        if (tableWidgetAreaList->columnCount() < 2)
            tableWidgetAreaList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        tableWidgetAreaList->setObjectName("tableWidgetAreaList");
        tableWidgetAreaList->setGeometry(QRect(10, 30, 361, 121));
        tableWidgetAreaList->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetAreaList->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(PropertyDynamicClassifyFormClass);

        QMetaObject::connectSlotsByName(PropertyDynamicClassifyFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyDynamicClassifyFormClass)
    {
        PropertyDynamicClassifyFormClass->setWindowTitle(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "PropertyDynamicClassifyForm", nullptr));
        ButtonPickupClearTest->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\346\212\275\345\207\272\343\201\256\343\202\257\343\203\252\343\202\242", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "Name", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "=>", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "<=", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        EditLibName->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "Library Name", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\227\343\203\255\343\203\221\343\203\206\343\202\243", nullptr));
        EditLibID->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "12345", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\345\220\215\347\247\260", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\343\203\207\343\203\274\343\202\277\343\203\231\343\203\274\343\202\271\343\201\270\343\201\256\346\233\264\346\226\260", nullptr));
        label_14->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\345\244\211\345\213\225\345\271\205", nullptr));
        label_15->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272", nullptr));
        label_16->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\345\204\252\345\205\210\345\272\246", nullptr));
        label_53->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\347\224\237\n"
"\346\210\220", nullptr));
        label_17->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\347\270\256\345\260\217\351\207\217", nullptr));
        label_9->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_10->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_12->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_11->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_54->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\343\202\265\n"
"\343\202\244\n"
"\343\202\272", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "=>>", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "<<=", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\357\274\270\357\274\270\357\274\270", nullptr));
        ButtonGenerateLibs->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\344\270\212\343\201\256\345\205\250\343\201\246\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\347\224\237\346\210\220", nullptr));
        ButtonPickupTest->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\345\215\230\344\270\200\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\343\201\256\346\212\275\345\207\272", nullptr));
        label->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "\350\241\250\347\244\272", nullptr));
        toolButtonCoreArea->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "Core", nullptr));
        toolButtonMaxZone->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "Max Zone", nullptr));
        toolButtonOutlineIArea->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "Outline-I", nullptr));
        toolButtonOutlineTArea->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "Outline-T", nullptr));
        toolButtonOutlineOArea->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "Outline-O", nullptr));
        toolButtonBareArea->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "Bare", nullptr));
        toolButtonInsideArea->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "Inside", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "From master image", nullptr));
        label_5->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "From target image", nullptr));
        toolButtonMinZone->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "Min Zone", nullptr));
        label_6->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "Sheet\351\240\230\345\237\237\343\203\252\343\202\271\343\203\210", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetAreaList->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetAreaList->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyDynamicClassifyFormClass", "LibName", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyDynamicClassifyFormClass: public Ui_PropertyDynamicClassifyFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYDYNAMICCLASSIFYFORM_H
