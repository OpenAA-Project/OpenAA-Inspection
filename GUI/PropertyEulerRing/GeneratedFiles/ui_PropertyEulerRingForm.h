/********************************************************************************
** Form generated from reading UI file 'PropertyEulerRingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYEULERRINGFORM_H
#define UI_PROPERTYEULERRINGFORM_H

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

class Ui_PropertyEulerRingFormClass
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
    QFrame *frameGenerateH;
    QLineEdit *EditLibID;
    QPushButton *ButtonLibSave;
    QLabel *label_45;
    QPushButton *pushButtonGColor;
    QSpinBox *EditNoiseSize;
    QFrame *frameGenerateC;
    QPushButton *pushButtonCColor;
    QToolButton *toolButtonHole;
    QToolButton *toolButtonCupper;
    QPushButton *pushButtonGetBackAll;
    QPushButton *pushButtonSetFromAll;
    QWidget *page_2;
    QLabel *label_32;
    QFrame *frameBlockInfoOnMouse;
    QLabel *label_33;
    QFrame *frame;
    QFrame *frame_15;
    QLabel *label_47;
    QFrame *frame_16;
    QLabel *label_48;
    QSpinBox *EditAdjustBlack;
    QSpinBox *EditAdjustWhite;
    QLabel *label_49;
    QLabel *label_50;
    QLineEdit *EditLibNameInBlock;
    QLineEdit *EditLibIDInBlock;
    QLabel *label_34;
    QSpinBox *EditMergin;
    QSpinBox *EditExpandedDot;
    QFrame *frameInspectionPanel;
    QLabel *label_66;
    QLabel *label_51;
    QTableWidget *tableWidgetBlockInfo;
    QFrame *frame_2;
    QToolButton *toolButtonLibrary;
    QToolButton *toolButtonCreateBlock;

    void setupUi(GUIFormBase *PropertyEulerRingFormClass)
    {
        if (PropertyEulerRingFormClass->objectName().isEmpty())
            PropertyEulerRingFormClass->setObjectName("PropertyEulerRingFormClass");
        PropertyEulerRingFormClass->resize(400, 700);
        stackedWidget = new QStackedWidget(PropertyEulerRingFormClass);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 50, 396, 651));
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
        frame_4->setGeometry(QRect(10, 320, 391, 321));
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
        frameGenerateH = new QFrame(frame_4);
        frameGenerateH->setObjectName("frameGenerateH");
        frameGenerateH->setGeometry(QRect(10, 110, 181, 121));
        frameGenerateH->setFrameShape(QFrame::NoFrame);
        frameGenerateH->setFrameShadow(QFrame::Raised);
        EditLibID = new QLineEdit(frame_4);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(80, 10, 61, 31));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        ButtonLibSave = new QPushButton(frame_4);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(10, 280, 371, 31));
        ButtonLibSave->setFont(font1);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon5);
        label_45 = new QLabel(frame_4);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(20, 240, 121, 31));
        label_45->setFont(font1);
        label_45->setFrameShape(QFrame::Panel);
        label_45->setFrameShadow(QFrame::Sunken);
        label_45->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonGColor = new QPushButton(frame_4);
        pushButtonGColor->setObjectName("pushButtonGColor");
        pushButtonGColor->setGeometry(QRect(30, 80, 75, 23));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Qtres/Color.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonGColor->setIcon(icon6);
        EditNoiseSize = new QSpinBox(frame_4);
        EditNoiseSize->setObjectName("EditNoiseSize");
        EditNoiseSize->setGeometry(QRect(140, 240, 61, 31));
        EditNoiseSize->setFont(font1);
        frameGenerateC = new QFrame(frame_4);
        frameGenerateC->setObjectName("frameGenerateC");
        frameGenerateC->setGeometry(QRect(200, 110, 181, 121));
        frameGenerateC->setFrameShape(QFrame::NoFrame);
        frameGenerateC->setFrameShadow(QFrame::Raised);
        pushButtonCColor = new QPushButton(frame_4);
        pushButtonCColor->setObjectName("pushButtonCColor");
        pushButtonCColor->setGeometry(QRect(220, 80, 75, 23));
        pushButtonCColor->setIcon(icon6);
        toolButtonHole = new QToolButton(frame_4);
        toolButtonHole->setObjectName("toolButtonHole");
        toolButtonHole->setGeometry(QRect(20, 50, 161, 21));
        toolButtonHole->setCheckable(true);
        toolButtonHole->setChecked(true);
        toolButtonHole->setAutoExclusive(true);
        toolButtonCupper = new QToolButton(frame_4);
        toolButtonCupper->setObjectName("toolButtonCupper");
        toolButtonCupper->setGeometry(QRect(210, 50, 161, 21));
        toolButtonCupper->setCheckable(true);
        toolButtonCupper->setChecked(false);
        toolButtonCupper->setAutoExclusive(true);
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
        frame->setGeometry(QRect(10, 70, 361, 371));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_15 = new QFrame(frame);
        frame_15->setObjectName("frame_15");
        frame_15->setGeometry(QRect(10, 280, 341, 71));
        frame_15->setFrameShape(QFrame::StyledPanel);
        frame_15->setFrameShadow(QFrame::Sunken);
        label_47 = new QLabel(frame_15);
        label_47->setObjectName("label_47");
        label_47->setGeometry(QRect(0, 0, 20, 71));
        label_47->setFrameShape(QFrame::Panel);
        label_47->setFrameShadow(QFrame::Raised);
        label_47->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_47->setIndent(1);
        frame_16 = new QFrame(frame_15);
        frame_16->setObjectName("frame_16");
        frame_16->setGeometry(QRect(10, 120, 371, 101));
        frame_16->setFrameShape(QFrame::StyledPanel);
        frame_16->setFrameShadow(QFrame::Sunken);
        label_48 = new QLabel(frame_16);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(0, 0, 20, 61));
        label_48->setFrameShape(QFrame::Panel);
        label_48->setFrameShadow(QFrame::Raised);
        label_48->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_48->setIndent(1);
        EditAdjustBlack = new QSpinBox(frame_15);
        EditAdjustBlack->setObjectName("EditAdjustBlack");
        EditAdjustBlack->setGeometry(QRect(230, 10, 81, 22));
        EditAdjustBlack->setMaximum(255);
        EditAdjustWhite = new QSpinBox(frame_15);
        EditAdjustWhite->setObjectName("EditAdjustWhite");
        EditAdjustWhite->setGeometry(QRect(230, 40, 81, 22));
        EditAdjustWhite->setMaximum(255);
        label_49 = new QLabel(frame_15);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(30, 40, 191, 21));
        label_49->setFrameShape(QFrame::Panel);
        label_49->setFrameShadow(QFrame::Sunken);
        label_49->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_50 = new QLabel(frame_15);
        label_50->setObjectName("label_50");
        label_50->setGeometry(QRect(30, 10, 191, 21));
        label_50->setFrameShape(QFrame::Panel);
        label_50->setFrameShadow(QFrame::Sunken);
        label_50->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
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
        EditMergin = new QSpinBox(frame);
        EditMergin->setObjectName("EditMergin");
        EditMergin->setGeometry(QRect(20, 70, 61, 22));
        EditMergin->setMaximum(99999999);
        EditExpandedDot = new QSpinBox(frame);
        EditExpandedDot->setObjectName("EditExpandedDot");
        EditExpandedDot->setGeometry(QRect(20, 120, 61, 22));
        EditExpandedDot->setMaximum(99999999);
        frameInspectionPanel = new QFrame(frame);
        frameInspectionPanel->setObjectName("frameInspectionPanel");
        frameInspectionPanel->setGeometry(QRect(90, 50, 261, 211));
        frameInspectionPanel->setFrameShape(QFrame::NoFrame);
        frameInspectionPanel->setFrameShadow(QFrame::Raised);
        label_66 = new QLabel(frame);
        label_66->setObjectName("label_66");
        label_66->setGeometry(QRect(10, 50, 70, 21));
        label_66->setFrameShape(QFrame::Panel);
        label_66->setFrameShadow(QFrame::Sunken);
        label_66->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_51 = new QLabel(frame);
        label_51->setObjectName("label_51");
        label_51->setGeometry(QRect(10, 100, 71, 21));
        label_51->setFrameShape(QFrame::Panel);
        label_51->setFrameShadow(QFrame::Sunken);
        label_51->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
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
        tableWidgetBlockInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
        stackedWidget->addWidget(page_2);
        frame_2 = new QFrame(PropertyEulerRingFormClass);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 0, 291, 41));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Plain);
        toolButtonLibrary = new QToolButton(frame_2);
        toolButtonLibrary->setObjectName("toolButtonLibrary");
        toolButtonLibrary->setGeometry(QRect(0, 10, 111, 31));
        toolButtonLibrary->setFont(font1);
        toolButtonLibrary->setCheckable(true);
        toolButtonLibrary->setChecked(true);
        toolButtonLibrary->setAutoExclusive(true);
        toolButtonCreateBlock = new QToolButton(frame_2);
        toolButtonCreateBlock->setObjectName("toolButtonCreateBlock");
        toolButtonCreateBlock->setGeometry(QRect(170, 10, 111, 31));
        toolButtonCreateBlock->setFont(font1);
        toolButtonCreateBlock->setCheckable(true);
        toolButtonCreateBlock->setAutoExclusive(true);

        retranslateUi(PropertyEulerRingFormClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PropertyEulerRingFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyEulerRingFormClass)
    {
        PropertyEulerRingFormClass->setWindowTitle(QCoreApplication::translate("PropertyEulerRingFormClass", "PropertyEulerRingForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "Name", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\357\274\270\357\274\270\357\274\270", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "=>", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "<=", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        ButtonPickupTest->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\345\215\230\344\270\200\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\343\201\256\346\212\275\345\207\272", nullptr));
        ButtonPickupClearTest->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\346\212\275\345\207\272\343\201\256\343\202\257\343\203\252\343\202\242", nullptr));
        ButtonGenerateLibs->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\345\217\263\343\201\256\345\205\250\343\201\246\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\347\224\237\346\210\220", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        EditLibName->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "Library Name", nullptr));
        label_18->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "12345", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\343\203\207\343\203\274\343\202\277\343\203\231\343\203\274\343\202\271\343\201\270\343\201\256\346\233\264\346\226\260", nullptr));
        label_45->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272", nullptr));
        pushButtonGColor->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\347\251\264Color", nullptr));
        pushButtonCColor->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\351\212\205Color", nullptr));
        toolButtonHole->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\347\251\264\350\211\262\350\250\255\345\256\232", nullptr));
        toolButtonCupper->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\351\212\205(\345\221\250\350\276\272\357\274\211\350\211\262\350\250\255\345\256\232", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "<<=", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "=>>", nullptr));
        label_32->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\344\275\277\347\224\250\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\226\343\203\255\343\203\203\343\202\257\346\203\205\345\240\261", nullptr));
        label_33->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\343\203\236\343\202\246\343\202\271\343\202\253\343\203\274\343\202\275\343\203\253\344\275\215\347\275\256\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\346\203\205\345\240\261", nullptr));
        label_47->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\350\243\234\n"
"\346\255\243", nullptr));
        label_48->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\350\274\235\n"
"\345\272\246", nullptr));
        label_49->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_50->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        EditLibNameInBlock->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "Library Name", nullptr));
        EditLibIDInBlock->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "12345", nullptr));
        label_34->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\345\220\215\347\247\260", nullptr));
        label_66->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\350\274\235\345\272\246\343\203\236\343\203\274\343\202\270\343\203\263", nullptr));
        label_51->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetBlockInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetBlockInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetBlockInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\343\203\226\343\203\255\343\203\203\343\202\257\347\267\217\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetBlockInfo->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\343\203\254\343\202\244\343\203\244\343\203\274\357\274\221", nullptr));
        toolButtonLibrary->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\346\212\275\345\207\272", nullptr));
        toolButtonCreateBlock->setText(QCoreApplication::translate("PropertyEulerRingFormClass", "\343\203\226\343\203\255\343\203\203\343\202\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyEulerRingFormClass: public Ui_PropertyEulerRingFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYEULERRINGFORM_H
