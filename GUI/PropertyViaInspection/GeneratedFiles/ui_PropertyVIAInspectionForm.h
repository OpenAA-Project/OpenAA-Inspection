/********************************************************************************
** Form generated from reading UI file 'PropertyVIAInspectionForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYVIAINSPECTIONFORM_H
#define UI_PROPERTYVIAINSPECTIONFORM_H

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

class Ui_PropertyVIAInspectionForm
{
public:
    QToolButton *toolButtonLibrary;
    QToolButton *toolButtonCreateVIA;
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
    QPushButton *ButtonLibSave;
    QFrame *frame_5;
    QLabel *label_14;
    QSpinBox *EditSpaceToOutline;
    QLabel *label_15;
    QSpinBox *EditNoiseSize;
    QLabel *label_16;
    QSpinBox *EditPriority;
    QLabel *label_53;
    QLabel *label_17;
    QSpinBox *EditNoiseSizePinHole;
    QSpinBox *EditOutlineGeneration;
    QLabel *label_55;
    QFrame *frame_6;
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
    QLabel *label_54;
    QLabel *label_30;
    QLabel *label_31;
    QPushButton *pushButtonGetBackAll;
    QPushButton *pushButtonSetFromAll;
    QWidget *page_2;
    QTableWidget *tableWidgetVIAInfo;
    QLabel *label_32;

    void setupUi(GUIFormBase *PropertyVIAInspectionForm)
    {
        if (PropertyVIAInspectionForm->objectName().isEmpty())
            PropertyVIAInspectionForm->setObjectName("PropertyVIAInspectionForm");
        PropertyVIAInspectionForm->resize(400, 716);
        toolButtonLibrary = new QToolButton(PropertyVIAInspectionForm);
        toolButtonLibrary->setObjectName("toolButtonLibrary");
        toolButtonLibrary->setGeometry(QRect(20, 10, 121, 31));
        toolButtonLibrary->setCheckable(true);
        toolButtonLibrary->setChecked(true);
        toolButtonLibrary->setAutoExclusive(true);
        toolButtonCreateVIA = new QToolButton(PropertyVIAInspectionForm);
        toolButtonCreateVIA->setObjectName("toolButtonCreateVIA");
        toolButtonCreateVIA->setGeometry(QRect(180, 10, 121, 31));
        toolButtonCreateVIA->setCheckable(true);
        toolButtonCreateVIA->setAutoExclusive(true);
        stackedWidget = new QStackedWidget(PropertyVIAInspectionForm);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 50, 401, 661));
        page = new QWidget();
        page->setObjectName("page");
        pushButtonEditLibFolder = new QPushButton(page);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(20, 0, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon);
        labelLibFolderName = new QLabel(page);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(140, 0, 241, 31));
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
        tableWidgetLibList->setGeometry(QRect(10, 60, 161, 161));
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
        tableWidgetGeneratedLibList->setGeometry(QRect(230, 60, 161, 161));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSetFrom = new QPushButton(page);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(180, 90, 39, 23));
        pushButtonGetBack = new QPushButton(page);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(180, 120, 39, 23));
        pushButtonEditLibrary = new QPushButton(page);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(210, 230, 181, 31));
        QFont font1;
        font1.setPointSize(12);
        pushButtonEditLibrary->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon1);
        ButtonPickupClearTest = new QPushButton(page);
        ButtonPickupClearTest->setObjectName("ButtonPickupClearTest");
        ButtonPickupClearTest->setGeometry(QRect(10, 310, 181, 31));
        QFont font2;
        font2.setPointSize(11);
        ButtonPickupClearTest->setFont(font2);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupClearTest->setIcon(icon2);
        ButtonPickupTest = new QPushButton(page);
        ButtonPickupTest->setObjectName("ButtonPickupTest");
        ButtonPickupTest->setGeometry(QRect(10, 254, 181, 51));
        ButtonPickupTest->setFont(font2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Extract.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupTest->setIcon(icon3);
        ButtonGenerateLibs = new QPushButton(page);
        ButtonGenerateLibs->setObjectName("ButtonGenerateLibs");
        ButtonGenerateLibs->setGeometry(QRect(200, 270, 191, 71));
        ButtonGenerateLibs->setFont(font2);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonGenerateLibs->setIcon(icon4);
        frame_4 = new QFrame(page);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 350, 381, 311));
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
        ButtonLibSave->setGeometry(QRect(10, 270, 361, 31));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon5);
        frame_5 = new QFrame(frame_4);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 160, 361, 101));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Sunken);
        label_14 = new QLabel(frame_5);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(40, 10, 171, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSpaceToOutline = new QSpinBox(frame_5);
        EditSpaceToOutline->setObjectName("EditSpaceToOutline");
        EditSpaceToOutline->setGeometry(QRect(210, 10, 61, 23));
        EditSpaceToOutline->setMinimum(-999);
        EditSpaceToOutline->setMaximum(999);
        label_15 = new QLabel(frame_5);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(40, 30, 171, 21));
        label_15->setFrameShape(QFrame::Panel);
        label_15->setFrameShadow(QFrame::Sunken);
        label_15->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNoiseSize = new QSpinBox(frame_5);
        EditNoiseSize->setObjectName("EditNoiseSize");
        EditNoiseSize->setGeometry(QRect(210, 30, 61, 23));
        QFont font3;
        font3.setPointSize(9);
        EditNoiseSize->setFont(font3);
        label_16 = new QLabel(frame_5);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(280, 50, 71, 21));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPriority = new QSpinBox(frame_5);
        EditPriority->setObjectName("EditPriority");
        EditPriority->setGeometry(QRect(280, 70, 61, 23));
        EditPriority->setFont(font3);
        label_53 = new QLabel(frame_5);
        label_53->setObjectName("label_53");
        label_53->setGeometry(QRect(0, 0, 31, 101));
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
        EditNoiseSizePinHole = new QSpinBox(frame_5);
        EditNoiseSizePinHole->setObjectName("EditNoiseSizePinHole");
        EditNoiseSizePinHole->setGeometry(QRect(210, 50, 61, 23));
        EditNoiseSizePinHole->setFont(font3);
        EditOutlineGeneration = new QSpinBox(frame_5);
        EditOutlineGeneration->setObjectName("EditOutlineGeneration");
        EditOutlineGeneration->setGeometry(QRect(210, 70, 61, 23));
        EditOutlineGeneration->setFont(font3);
        EditOutlineGeneration->setMaximum(1000);
        label_55 = new QLabel(frame_5);
        label_55->setObjectName("label_55");
        label_55->setGeometry(QRect(40, 70, 171, 21));
        label_55->setFrameShape(QFrame::Panel);
        label_55->setFrameShadow(QFrame::Sunken);
        label_55->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_6 = new QFrame(frame_4);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(10, 50, 361, 111));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Sunken);
        EditMinVIASize = new QSpinBox(frame_6);
        EditMinVIASize->setObjectName("EditMinVIASize");
        EditMinVIASize->setGeometry(QRect(160, 10, 81, 22));
        EditMinVIASize->setMaximum(1000000);
        label_9 = new QLabel(frame_6);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(40, 30, 111, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxVIASize = new QSpinBox(frame_6);
        EditMaxVIASize->setObjectName("EditMaxVIASize");
        EditMaxVIASize->setGeometry(QRect(160, 30, 81, 22));
        EditMaxVIASize->setMaximum(1000000);
        label_10 = new QLabel(frame_6);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(40, 10, 111, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinVIADots = new QSpinBox(frame_6);
        EditMinVIADots->setObjectName("EditMinVIADots");
        EditMinVIADots->setGeometry(QRect(160, 60, 81, 22));
        EditMinVIADots->setMaximum(2000000000);
        label_12 = new QLabel(frame_6);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(40, 60, 111, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxVIADots = new QSpinBox(frame_6);
        EditMaxVIADots->setObjectName("EditMaxVIADots");
        EditMaxVIADots->setGeometry(QRect(160, 80, 81, 22));
        EditMaxVIADots->setMaximum(2000000000);
        EditMaxVIADots->setValue(2000000000);
        label_11 = new QLabel(frame_6);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(40, 80, 111, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_13 = new QLabel(frame_6);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(250, 60, 101, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLimitVIASize = new QSpinBox(frame_6);
        EditLimitVIASize->setObjectName("EditLimitVIASize");
        EditLimitVIASize->setGeometry(QRect(280, 80, 61, 22));
        EditLimitVIASize->setMaximum(99999);
        label_54 = new QLabel(frame_6);
        label_54->setObjectName("label_54");
        label_54->setGeometry(QRect(0, 0, 31, 111));
        label_54->setFrameShape(QFrame::Panel);
        label_54->setFrameShadow(QFrame::Raised);
        label_54->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_54->setIndent(1);
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
        pushButtonGetBackAll = new QPushButton(page);
        pushButtonGetBackAll->setObjectName("pushButtonGetBackAll");
        pushButtonGetBackAll->setGeometry(QRect(180, 200, 39, 23));
        pushButtonSetFromAll = new QPushButton(page);
        pushButtonSetFromAll->setObjectName("pushButtonSetFromAll");
        pushButtonSetFromAll->setGeometry(QRect(180, 170, 39, 23));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        tableWidgetVIAInfo = new QTableWidget(page_2);
        if (tableWidgetVIAInfo->columnCount() < 4)
            tableWidgetVIAInfo->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetVIAInfo->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetVIAInfo->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetVIAInfo->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetVIAInfo->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        tableWidgetVIAInfo->setObjectName("tableWidgetVIAInfo");
        tableWidgetVIAInfo->setGeometry(QRect(10, 20, 381, 181));
        tableWidgetVIAInfo->setSelectionMode(QAbstractItemView::MultiSelection);
        label_32 = new QLabel(page_2);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(10, 0, 381, 21));
        label_32->setFont(font1);
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        stackedWidget->addWidget(page_2);

        retranslateUi(PropertyVIAInspectionForm);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PropertyVIAInspectionForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyVIAInspectionForm)
    {
        PropertyVIAInspectionForm->setWindowTitle(QCoreApplication::translate("PropertyVIAInspectionForm", "Property VIAInspection", nullptr));
        toolButtonLibrary->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "Library Test", nullptr));
        toolButtonCreateVIA->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "Create Block", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\357\274\270\357\274\270\357\274\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "Name", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "=>", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "<=", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        ButtonPickupClearTest->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\346\212\275\345\207\272\343\201\256\343\202\257\343\203\252\343\202\242", nullptr));
        ButtonPickupTest->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\345\215\230\344\270\200\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\343\201\256\346\212\275\345\207\272", nullptr));
        ButtonGenerateLibs->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\344\270\212\343\201\256\345\205\250\343\201\246\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\347\224\237\346\210\220", nullptr));
        EditLibName->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "Library Name", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\227\343\203\255\343\203\221\343\203\206\343\202\243", nullptr));
        EditLibID->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "12345", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\345\220\215\347\247\260", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\343\203\207\343\203\274\343\202\277\343\203\231\343\203\274\343\202\271\343\201\270\343\201\256\346\233\264\346\226\260", nullptr));
        label_14->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\350\274\252\351\203\255\343\201\213\343\202\211\343\201\256\351\226\223\351\232\224", nullptr));
        label_15->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272 \345\255\244\347\253\213\347\202\271\345\211\212\351\231\244", nullptr));
        label_16->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\345\204\252\345\205\210\345\272\246", nullptr));
        label_53->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\347\224\237\n"
"\346\210\220", nullptr));
        label_17->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272\343\200\200\343\203\224\343\203\263\343\203\233\343\203\274\343\203\253\345\211\212\351\231\244", nullptr));
        label_55->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\350\274\252\351\203\255\344\273\230\350\277\221\343\201\253\347\224\237\346\210\220(Max1000)", nullptr));
        label_9->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_10->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_12->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_11->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_13->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\351\231\220\347\225\214\343\202\265\343\202\244\343\202\272", nullptr));
        label_54->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\343\202\265\n"
"\343\202\244\n"
"\343\202\272", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "<<=", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "=>>", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetVIAInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetVIAInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetVIAInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\343\203\226\343\203\255\343\203\203\343\202\257\347\267\217\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetVIAInfo->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\343\203\254\343\202\244\343\203\244\343\203\274\357\274\221", nullptr));
        label_32->setText(QCoreApplication::translate("PropertyVIAInspectionForm", "\344\275\277\347\224\250\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\226\343\203\255\343\203\203\343\202\257\346\203\205\345\240\261", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyVIAInspectionForm: public Ui_PropertyVIAInspectionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYVIAINSPECTIONFORM_H
