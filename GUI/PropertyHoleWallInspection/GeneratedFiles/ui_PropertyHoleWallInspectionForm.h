/********************************************************************************
** Form generated from reading UI file 'PropertyHoleWallInspectionForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYHOLEWALLINSPECTIONFORM_H
#define UI_PROPERTYHOLEWALLINSPECTIONFORM_H

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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyHoleWallInspectionForm
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QTableWidget *tableWidgetLibList;
    QTableWidget *tableWidgetGeneratedLibList;
    QLabel *labelLibFolderName;
    QPushButton *pushButtonEditLibFolder;
    QPushButton *pushButtonSetFrom;
    QPushButton *pushButtonGetBack;
    QPushButton *pushButtonEditLibrary;
    QPushButton *ButtonPickupTest;
    QPushButton *ButtonPickupClearTest;
    QPushButton *ButtonGenerateLibs;
    QLabel *label_30;
    QLabel *label_31;
    QFrame *frame_4;
    QLineEdit *EditLibName;
    QLabel *label_18;
    QLineEdit *EditLibID;
    QPushButton *ButtonLibSave;
    QFrame *frame_6;
    QSpinBox *EditNoiseSizePinHole;
    QLabel *label_15;
    QSpinBox *EditNoiseSize;
    QLabel *label_17;
    QLabel *label_14;
    QSpinBox *EditSpaceToOutline;
    QFrame *frame_7;
    QSpinBox *EditMinBlockSize;
    QLabel *label_9;
    QSpinBox *EditMaxBlockSize;
    QLabel *label_10;
    QSpinBox *EditMinBlockDots;
    QLabel *label_12;
    QSpinBox *EditMaxBlockDots;
    QLabel *label_11;
    QLabel *label_54;
    QPushButton *pushButtonGetBackAll;
    QPushButton *pushButtonSetFromAll;
    QWidget *page_2;
    QLabel *label_32;
    QFrame *frameBlockInfoOnMouse;
    QLabel *label_33;
    QFrame *frame;
    QLineEdit *EditLibNameInBlock;
    QLineEdit *EditLibIDInBlock;
    QLabel *label_34;
    QLabel *label_27;
    QLabel *label_37;
    QSpinBox *EditSearchDot;
    QSpinBox *EditNGSize;
    QTableWidget *tableWidgetBlockInfo;
    QFrame *frame_2;
    QToolButton *toolButtonLibrary;
    QToolButton *toolButtonCreateBlock;
    QPushButton *pushButtonMakeBitBuff;

    void setupUi(GUIFormBase *PropertyHoleWallInspectionForm)
    {
        if (PropertyHoleWallInspectionForm->objectName().isEmpty())
            PropertyHoleWallInspectionForm->setObjectName("PropertyHoleWallInspectionForm");
        PropertyHoleWallInspectionForm->resize(400, 740);
        stackedWidget = new QStackedWidget(PropertyHoleWallInspectionForm);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 40, 396, 650));
        page = new QWidget();
        page->setObjectName("page");
        tableWidgetLibList = new QTableWidget(page);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 60, 161, 131));
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
        tableWidgetGeneratedLibList->setGeometry(QRect(230, 60, 161, 131));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        labelLibFolderName = new QLabel(page);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(130, 0, 241, 31));
        QFont font;
        font.setPointSize(16);
        labelLibFolderName->setFont(font);
        pushButtonEditLibFolder = new QPushButton(page);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(20, 0, 101, 31));
        QFont font1;
        font1.setPointSize(12);
        pushButtonEditLibFolder->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon);
        pushButtonSetFrom = new QPushButton(page);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(180, 70, 39, 23));
        pushButtonGetBack = new QPushButton(page);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(180, 100, 39, 23));
        pushButtonEditLibrary = new QPushButton(page);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(90, 200, 211, 31));
        pushButtonEditLibrary->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon1);
        ButtonPickupTest = new QPushButton(page);
        ButtonPickupTest->setObjectName("ButtonPickupTest");
        ButtonPickupTest->setGeometry(QRect(10, 240, 171, 31));
        ButtonPickupTest->setFont(font1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Extract.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupTest->setIcon(icon2);
        ButtonPickupClearTest = new QPushButton(page);
        ButtonPickupClearTest->setObjectName("ButtonPickupClearTest");
        ButtonPickupClearTest->setGeometry(QRect(10, 280, 171, 31));
        ButtonPickupClearTest->setFont(font1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupClearTest->setIcon(icon3);
        ButtonGenerateLibs = new QPushButton(page);
        ButtonGenerateLibs->setObjectName("ButtonGenerateLibs");
        ButtonGenerateLibs->setGeometry(QRect(190, 240, 201, 71));
        ButtonGenerateLibs->setFont(font1);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonGenerateLibs->setIcon(icon4);
        label_30 = new QLabel(page);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 40, 161, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_31 = new QLabel(page);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(230, 40, 161, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_4 = new QFrame(page);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 320, 391, 329));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Sunken);
        EditLibName = new QLineEdit(frame_4);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 10, 231, 31));
        EditLibName->setFont(font1);
        label_18 = new QLabel(frame_4);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(20, 10, 61, 31));
        label_18->setFont(font1);
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(frame_4);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(80, 10, 61, 31));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        ButtonLibSave = new QPushButton(frame_4);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(10, 294, 371, 31));
        ButtonLibSave->setFont(font1);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon5);
        frame_6 = new QFrame(frame_4);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(10, 170, 361, 111));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Sunken);
        EditNoiseSizePinHole = new QSpinBox(frame_6);
        EditNoiseSizePinHole->setObjectName("EditNoiseSizePinHole");
        EditNoiseSizePinHole->setGeometry(QRect(290, 30, 61, 23));
        QFont font2;
        font2.setPointSize(9);
        EditNoiseSizePinHole->setFont(font2);
        label_15 = new QLabel(frame_6);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 10, 271, 21));
        label_15->setFrameShape(QFrame::Panel);
        label_15->setFrameShadow(QFrame::Sunken);
        label_15->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNoiseSize = new QSpinBox(frame_6);
        EditNoiseSize->setObjectName("EditNoiseSize");
        EditNoiseSize->setGeometry(QRect(290, 10, 61, 23));
        EditNoiseSize->setFont(font2);
        label_17 = new QLabel(frame_6);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(10, 30, 271, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_14 = new QLabel(frame_6);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 60, 271, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSpaceToOutline = new QSpinBox(frame_6);
        EditSpaceToOutline->setObjectName("EditSpaceToOutline");
        EditSpaceToOutline->setGeometry(QRect(290, 60, 61, 23));
        frame_7 = new QFrame(frame_4);
        frame_7->setObjectName("frame_7");
        frame_7->setGeometry(QRect(10, 50, 361, 111));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Sunken);
        EditMinBlockSize = new QSpinBox(frame_7);
        EditMinBlockSize->setObjectName("EditMinBlockSize");
        EditMinBlockSize->setGeometry(QRect(270, 10, 81, 22));
        EditMinBlockSize->setMaximum(1000000);
        label_9 = new QLabel(frame_7);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(40, 30, 221, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxBlockSize = new QSpinBox(frame_7);
        EditMaxBlockSize->setObjectName("EditMaxBlockSize");
        EditMaxBlockSize->setGeometry(QRect(270, 30, 81, 22));
        EditMaxBlockSize->setMaximum(1000000);
        label_10 = new QLabel(frame_7);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(40, 10, 221, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinBlockDots = new QSpinBox(frame_7);
        EditMinBlockDots->setObjectName("EditMinBlockDots");
        EditMinBlockDots->setGeometry(QRect(240, 60, 111, 22));
        EditMinBlockDots->setMaximum(2000000000);
        label_12 = new QLabel(frame_7);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(40, 60, 191, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxBlockDots = new QSpinBox(frame_7);
        EditMaxBlockDots->setObjectName("EditMaxBlockDots");
        EditMaxBlockDots->setGeometry(QRect(240, 80, 111, 22));
        EditMaxBlockDots->setMaximum(2000000000);
        EditMaxBlockDots->setValue(2000000000);
        label_11 = new QLabel(frame_7);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(40, 80, 191, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_54 = new QLabel(frame_7);
        label_54->setObjectName("label_54");
        label_54->setGeometry(QRect(0, 0, 31, 111));
        label_54->setFrameShape(QFrame::Panel);
        label_54->setFrameShadow(QFrame::Raised);
        label_54->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_54->setIndent(1);
        pushButtonGetBackAll = new QPushButton(page);
        pushButtonGetBackAll->setObjectName("pushButtonGetBackAll");
        pushButtonGetBackAll->setGeometry(QRect(180, 170, 39, 23));
        pushButtonSetFromAll = new QPushButton(page);
        pushButtonSetFromAll->setObjectName("pushButtonSetFromAll");
        pushButtonSetFromAll->setGeometry(QRect(180, 140, 39, 23));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
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
        frame->setGeometry(QRect(10, 80, 361, 371));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        EditLibNameInBlock = new QLineEdit(frame);
        EditLibNameInBlock->setObjectName("EditLibNameInBlock");
        EditLibNameInBlock->setGeometry(QRect(120, 10, 231, 31));
        EditLibNameInBlock->setFont(font1);
        EditLibIDInBlock = new QLineEdit(frame);
        EditLibIDInBlock->setObjectName("EditLibIDInBlock");
        EditLibIDInBlock->setGeometry(QRect(60, 10, 61, 31));
        EditLibIDInBlock->setFont(font1);
        EditLibIDInBlock->setReadOnly(true);
        label_34 = new QLabel(frame);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(10, 10, 51, 31));
        label_34->setFont(font1);
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Sunken);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_27 = new QLabel(frame);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(10, 70, 291, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_37 = new QLabel(frame);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(10, 140, 121, 21));
        label_37->setFrameShape(QFrame::Panel);
        label_37->setFrameShadow(QFrame::Sunken);
        label_37->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSearchDot = new QSpinBox(frame);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(20, 100, 81, 22));
        EditSearchDot->setMaximum(255);
        EditNGSize = new QSpinBox(frame);
        EditNGSize->setObjectName("EditNGSize");
        EditNGSize->setGeometry(QRect(140, 140, 91, 22));
        EditNGSize->setMinimum(-9999);
        EditNGSize->setMaximum(99999999);
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
        tableWidgetBlockInfo->setGeometry(QRect(10, 20, 381, 131));
        tableWidgetBlockInfo->setSelectionMode(QAbstractItemView::MultiSelection);
        stackedWidget->addWidget(page_2);
        frame_2 = new QFrame(PropertyHoleWallInspectionForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 0, 371, 41));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Plain);
        toolButtonLibrary = new QToolButton(frame_2);
        toolButtonLibrary->setObjectName("toolButtonLibrary");
        toolButtonLibrary->setGeometry(QRect(0, 0, 141, 31));
        toolButtonLibrary->setFont(font1);
        toolButtonLibrary->setCheckable(true);
        toolButtonLibrary->setChecked(true);
        toolButtonLibrary->setAutoExclusive(true);
        toolButtonCreateBlock = new QToolButton(frame_2);
        toolButtonCreateBlock->setObjectName("toolButtonCreateBlock");
        toolButtonCreateBlock->setGeometry(QRect(170, 0, 141, 31));
        toolButtonCreateBlock->setFont(font1);
        toolButtonCreateBlock->setCheckable(true);
        toolButtonCreateBlock->setAutoExclusive(true);
        pushButtonMakeBitBuff = new QPushButton(PropertyHoleWallInspectionForm);
        pushButtonMakeBitBuff->setObjectName("pushButtonMakeBitBuff");
        pushButtonMakeBitBuff->setGeometry(QRect(140, 700, 112, 34));

        retranslateUi(PropertyHoleWallInspectionForm);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PropertyHoleWallInspectionForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyHoleWallInspectionForm)
    {
        PropertyHoleWallInspectionForm->setWindowTitle(QCoreApplication::translate("PropertyHoleWallInspectionForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "Name", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\357\274\270\357\274\270\357\274\270", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "=>", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "<=", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        ButtonPickupTest->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\345\215\230\344\270\200\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\343\201\256\346\212\275\345\207\272", nullptr));
        ButtonPickupClearTest->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\346\212\275\345\207\272\343\201\256\343\202\257\343\203\252\343\202\242", nullptr));
        ButtonGenerateLibs->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\345\217\263\343\201\256\345\205\250\343\201\246\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\347\224\237\346\210\220", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        EditLibName->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "Library Name", nullptr));
        label_18->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "12345", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\343\203\207\343\203\274\343\202\277\343\203\231\343\203\274\343\202\271\343\201\270\343\201\256\346\233\264\346\226\260", nullptr));
        label_15->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272 \345\255\244\347\253\213\347\202\271\345\211\212\351\231\244", nullptr));
        label_17->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272\343\200\200\343\203\224\343\203\263\343\203\233\343\203\274\343\203\253\345\211\212\351\231\244", nullptr));
        label_14->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\350\274\252\351\203\255\343\201\213\343\202\211\343\201\256\351\226\223\351\232\224", nullptr));
        label_9->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_10->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_12->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_11->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_54->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\343\202\265\n"
"\343\202\244\n"
"\343\202\272", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "<<=", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "=>>", nullptr));
        label_32->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\344\275\277\347\224\250\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\226\343\203\255\343\203\203\343\202\257\346\203\205\345\240\261", nullptr));
        label_33->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\343\203\236\343\202\246\343\202\271\343\202\253\343\203\274\343\202\275\343\203\253\344\275\215\347\275\256\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\346\203\205\345\240\261", nullptr));
        EditLibNameInBlock->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "Library Name", nullptr));
        EditLibIDInBlock->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "12345", nullptr));
        label_34->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\345\220\215\347\247\260", nullptr));
        label_27->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "Search area (Pixel)", nullptr));
        label_37->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "NG size", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetBlockInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetBlockInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetBlockInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\343\203\226\343\203\255\343\203\203\343\202\257\347\267\217\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetBlockInfo->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\343\203\254\343\202\244\343\203\244\343\203\274\357\274\221", nullptr));
        toolButtonLibrary->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\346\212\275\345\207\272", nullptr));
        toolButtonCreateBlock->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "\343\203\226\343\203\255\343\203\203\343\202\257", nullptr));
        pushButtonMakeBitBuff->setText(QCoreApplication::translate("PropertyHoleWallInspectionForm", "Make BitBuff", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyHoleWallInspectionForm: public Ui_PropertyHoleWallInspectionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYHOLEWALLINSPECTIONFORM_H
