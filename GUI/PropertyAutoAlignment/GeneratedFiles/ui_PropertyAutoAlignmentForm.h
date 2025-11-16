/********************************************************************************
** Form generated from reading UI file 'PropertyAutoAlignmentForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYAUTOALIGNMENTFORM_H
#define UI_PROPERTYAUTOALIGNMENTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyAutoAlignmentFormClass
{
public:
    QLabel *labelLibFolderName;
    QLabel *label_30;
    QTableWidget *tableWidgetLibList;
    QPushButton *pushButtonGetBack;
    QPushButton *pushButtonSetFrom;
    QLabel *label_31;
    QTableWidget *tableWidgetGeneratedLibList;
    QPushButton *pushButtonEditLibFolder;
    QPushButton *ButtonGenerateLibs;
    QFrame *frame;
    QLabel *label;
    QGroupBox *groupBox;
    QRadioButton *radioButtonSheetNone;
    QRadioButton *radioButtonSheetArea;
    QRadioButton *radioButtonSheetPickup;
    QRadioButton *radioButtonSheetPickupTest;
    QGroupBox *groupBox_2;
    QCheckBox *checkBoxMonoView;
    QComboBox *comboBoxMonoLevel;
    QLabel *label_2;
    QGroupBox *groupBox_3;
    QCheckBox *checkBoxPicoTransView;
    QCheckBox *checkBoxPicoPickupView;
    QCheckBox *checkBoxPicoOtherView;
    QCheckBox *checkBoxPicoInfo;
    QCheckBox *checkBoxFringeArea;
    QPushButton *ButtonPickupTest;
    QFrame *frame_2;
    QLabel *label_3;
    QTableWidget *tableWidgetAreaList;
    QFrame *frame_3;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_5;
    QLineEdit *lineEditXFromMaster;
    QLineEdit *lineEditYFromMaster;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *lineEditXFromTarget;
    QLabel *label_10;
    QLineEdit *lineEditYFromTarget;
    QLineEdit *lineEditRelativeXFromMaster;
    QLineEdit *lineEditRelativeYFromMaster;
    QLineEdit *lineEditRelativeYFromTarget;
    QLineEdit *lineEditRelativeXFromTarget;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QPushButton *pushButtonUpdateView;
    QPushButton *pushButtonEditLibrary;
    QPushButton *pushButtonGetBackAll;
    QPushButton *pushButtonSetFromAll;

    void setupUi(GUIFormBase *PropertyAutoAlignmentFormClass)
    {
        if (PropertyAutoAlignmentFormClass->objectName().isEmpty())
            PropertyAutoAlignmentFormClass->setObjectName("PropertyAutoAlignmentFormClass");
        PropertyAutoAlignmentFormClass->resize(400, 750);
        labelLibFolderName = new QLabel(PropertyAutoAlignmentFormClass);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(150, 4, 241, 31));
        QFont font;
        font.setPointSize(16);
        labelLibFolderName->setFont(font);
        label_30 = new QLabel(PropertyAutoAlignmentFormClass);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 40, 161, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetLibList = new QTableWidget(PropertyAutoAlignmentFormClass);
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
        pushButtonGetBack = new QPushButton(PropertyAutoAlignmentFormClass);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(180, 100, 39, 23));
        pushButtonSetFrom = new QPushButton(PropertyAutoAlignmentFormClass);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(180, 70, 39, 23));
        label_31 = new QLabel(PropertyAutoAlignmentFormClass);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(230, 40, 161, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetGeneratedLibList = new QTableWidget(PropertyAutoAlignmentFormClass);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetGeneratedLibList->setObjectName("tableWidgetGeneratedLibList");
        tableWidgetGeneratedLibList->setGeometry(QRect(230, 60, 161, 131));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonEditLibFolder = new QPushButton(PropertyAutoAlignmentFormClass);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(10, 4, 141, 31));
        QFont font1;
        font1.setPointSize(12);
        pushButtonEditLibFolder->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon);
        ButtonGenerateLibs = new QPushButton(PropertyAutoAlignmentFormClass);
        ButtonGenerateLibs->setObjectName("ButtonGenerateLibs");
        ButtonGenerateLibs->setGeometry(QRect(10, 200, 381, 36));
        ButtonGenerateLibs->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonGenerateLibs->setIcon(icon1);
        frame = new QFrame(PropertyAutoAlignmentFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 280, 397, 181));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 397, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(3, 20, 171, 121));
        radioButtonSheetNone = new QRadioButton(groupBox);
        radioButtonSheetNone->setObjectName("radioButtonSheetNone");
        radioButtonSheetNone->setGeometry(QRect(3, 20, 141, 20));
        radioButtonSheetArea = new QRadioButton(groupBox);
        radioButtonSheetArea->setObjectName("radioButtonSheetArea");
        radioButtonSheetArea->setGeometry(QRect(3, 42, 161, 20));
        radioButtonSheetArea->setChecked(true);
        radioButtonSheetPickup = new QRadioButton(groupBox);
        radioButtonSheetPickup->setObjectName("radioButtonSheetPickup");
        radioButtonSheetPickup->setGeometry(QRect(3, 64, 171, 20));
        radioButtonSheetPickup->setChecked(false);
        radioButtonSheetPickupTest = new QRadioButton(groupBox);
        radioButtonSheetPickupTest->setObjectName("radioButtonSheetPickupTest");
        radioButtonSheetPickupTest->setGeometry(QRect(3, 86, 171, 20));
        radioButtonSheetPickupTest->setChecked(false);
        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(180, 20, 91, 121));
        checkBoxMonoView = new QCheckBox(groupBox_2);
        checkBoxMonoView->setObjectName("checkBoxMonoView");
        checkBoxMonoView->setGeometry(QRect(3, 20, 81, 21));
        comboBoxMonoLevel = new QComboBox(groupBox_2);
        comboBoxMonoLevel->setObjectName("comboBoxMonoLevel");
        comboBoxMonoLevel->setGeometry(QRect(3, 70, 81, 22));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(3, 50, 85, 16));
        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(275, 20, 116, 131));
        checkBoxPicoTransView = new QCheckBox(groupBox_3);
        checkBoxPicoTransView->setObjectName("checkBoxPicoTransView");
        checkBoxPicoTransView->setGeometry(QRect(3, 20, 111, 20));
        checkBoxPicoPickupView = new QCheckBox(groupBox_3);
        checkBoxPicoPickupView->setObjectName("checkBoxPicoPickupView");
        checkBoxPicoPickupView->setGeometry(QRect(3, 42, 111, 20));
        checkBoxPicoOtherView = new QCheckBox(groupBox_3);
        checkBoxPicoOtherView->setObjectName("checkBoxPicoOtherView");
        checkBoxPicoOtherView->setGeometry(QRect(3, 64, 111, 20));
        checkBoxPicoInfo = new QCheckBox(groupBox_3);
        checkBoxPicoInfo->setObjectName("checkBoxPicoInfo");
        checkBoxPicoInfo->setGeometry(QRect(3, 108, 111, 20));
        checkBoxFringeArea = new QCheckBox(groupBox_3);
        checkBoxFringeArea->setObjectName("checkBoxFringeArea");
        checkBoxFringeArea->setGeometry(QRect(3, 86, 111, 20));
        ButtonPickupTest = new QPushButton(frame);
        ButtonPickupTest->setObjectName("ButtonPickupTest");
        ButtonPickupTest->setGeometry(QRect(10, 150, 161, 28));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Extract.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupTest->setIcon(icon2);
        frame_2 = new QFrame(PropertyAutoAlignmentFormClass);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 470, 381, 151));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 381, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetAreaList = new QTableWidget(frame_2);
        if (tableWidgetAreaList->columnCount() < 4)
            tableWidgetAreaList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        tableWidgetAreaList->setObjectName("tableWidgetAreaList");
        tableWidgetAreaList->setGeometry(QRect(10, 26, 361, 121));
        tableWidgetAreaList->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetAreaList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame_3 = new QFrame(PropertyAutoAlignmentFormClass);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 630, 381, 115));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frame_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 0, 381, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 30, 181, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(frame_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(200, 30, 171, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 70, 21, 16));
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditXFromMaster = new QLineEdit(frame_3);
        lineEditXFromMaster->setObjectName("lineEditXFromMaster");
        lineEditXFromMaster->setGeometry(QRect(40, 70, 71, 20));
        lineEditYFromMaster = new QLineEdit(frame_3);
        lineEditYFromMaster->setObjectName("lineEditYFromMaster");
        lineEditYFromMaster->setGeometry(QRect(40, 90, 71, 20));
        label_8 = new QLabel(frame_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 90, 21, 16));
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_9 = new QLabel(frame_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(190, 90, 21, 16));
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditXFromTarget = new QLineEdit(frame_3);
        lineEditXFromTarget->setObjectName("lineEditXFromTarget");
        lineEditXFromTarget->setGeometry(QRect(220, 70, 71, 20));
        label_10 = new QLabel(frame_3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(190, 70, 21, 16));
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditYFromTarget = new QLineEdit(frame_3);
        lineEditYFromTarget->setObjectName("lineEditYFromTarget");
        lineEditYFromTarget->setGeometry(QRect(220, 90, 71, 20));
        lineEditRelativeXFromMaster = new QLineEdit(frame_3);
        lineEditRelativeXFromMaster->setObjectName("lineEditRelativeXFromMaster");
        lineEditRelativeXFromMaster->setGeometry(QRect(110, 70, 71, 20));
        lineEditRelativeYFromMaster = new QLineEdit(frame_3);
        lineEditRelativeYFromMaster->setObjectName("lineEditRelativeYFromMaster");
        lineEditRelativeYFromMaster->setGeometry(QRect(110, 90, 71, 20));
        lineEditRelativeYFromTarget = new QLineEdit(frame_3);
        lineEditRelativeYFromTarget->setObjectName("lineEditRelativeYFromTarget");
        lineEditRelativeYFromTarget->setGeometry(QRect(290, 90, 71, 20));
        lineEditRelativeXFromTarget = new QLineEdit(frame_3);
        lineEditRelativeXFromTarget->setObjectName("lineEditRelativeXFromTarget");
        lineEditRelativeXFromTarget->setGeometry(QRect(290, 70, 71, 20));
        label_11 = new QLabel(frame_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(40, 50, 71, 20));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_12 = new QLabel(frame_3);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(110, 50, 71, 20));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_13 = new QLabel(frame_3);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(220, 50, 71, 20));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_14 = new QLabel(frame_3);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(290, 50, 71, 20));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonUpdateView = new QPushButton(PropertyAutoAlignmentFormClass);
        pushButtonUpdateView->setObjectName("pushButtonUpdateView");
        pushButtonUpdateView->setGeometry(QRect(270, 240, 121, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Reload.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdateView->setIcon(icon3);
        pushButtonEditLibrary = new QPushButton(PropertyAutoAlignmentFormClass);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(10, 240, 211, 31));
        pushButtonEditLibrary->setFont(font1);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon4);
        pushButtonGetBackAll = new QPushButton(PropertyAutoAlignmentFormClass);
        pushButtonGetBackAll->setObjectName("pushButtonGetBackAll");
        pushButtonGetBackAll->setGeometry(QRect(180, 170, 39, 23));
        pushButtonSetFromAll = new QPushButton(PropertyAutoAlignmentFormClass);
        pushButtonSetFromAll->setObjectName("pushButtonSetFromAll");
        pushButtonSetFromAll->setGeometry(QRect(180, 140, 39, 23));

        retranslateUi(PropertyAutoAlignmentFormClass);

        QMetaObject::connectSlotsByName(PropertyAutoAlignmentFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyAutoAlignmentFormClass)
    {
        PropertyAutoAlignmentFormClass->setWindowTitle(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "PropertyAutoAlignmentForm", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\357\274\270\357\274\270\357\274\270", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "Name", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "<=", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "=>", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "Name", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        ButtonGenerateLibs->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\345\217\263\343\201\256\345\205\250\343\201\246\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\347\224\237\346\210\220", nullptr));
        label->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\350\241\250\347\244\272", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "Sheet", nullptr));
        radioButtonSheetNone->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\350\241\250\347\244\272\343\201\252\343\201\227", nullptr));
        radioButtonSheetArea->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\351\240\230\345\237\237\350\241\250\347\244\272", nullptr));
        radioButtonSheetPickup->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\346\212\275\345\207\272\351\240\230\345\237\237\350\241\250\347\244\272", nullptr));
        radioButtonSheetPickupTest->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\346\212\275\345\207\272\343\203\206\343\202\271\343\203\210\351\240\230\345\237\237\350\241\250\347\244\272", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "Mono", nullptr));
        checkBoxMonoView->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\350\241\250\347\244\272", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\350\241\250\347\244\272\343\203\254\343\203\231\343\203\253", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "Pico", nullptr));
        checkBoxPicoTransView->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\351\201\267\347\247\273\351\240\230\345\237\237", nullptr));
        checkBoxPicoPickupView->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\346\212\275\345\207\272\351\240\230\345\237\237", nullptr));
        checkBoxPicoOtherView->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\344\273\226\351\240\230\345\237\237", nullptr));
        checkBoxPicoInfo->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\346\203\205\345\240\261\350\241\250\347\244\272", nullptr));
        checkBoxFringeArea->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\345\221\250\347\270\201\351\240\230\345\237\237", nullptr));
        ButtonPickupTest->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\346\212\275\345\207\272\343\203\206\343\202\271\343\203\210", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "Sheet\351\240\230\345\237\237\343\203\252\343\202\271\343\203\210", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetAreaList->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetAreaList->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "LibName", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetAreaList->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "Shift", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetAreaList->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "Created", nullptr));
        label_7->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\343\203\236\343\202\246\343\202\271\345\272\247\346\250\231\344\270\212\343\201\256\343\202\242\343\203\251\343\202\244\343\203\263\343\203\241\343\203\263\343\203\210\347\265\220\346\236\234", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\343\203\236\343\202\271\343\202\277\343\203\274\344\270\212\343\201\256\347\247\273\345\213\225\351\207\217", nullptr));
        label_6->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "Target\343\201\213\343\202\211\343\201\256\347\247\273\345\213\225\351\207\217", nullptr));
        label_5->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "X", nullptr));
        label_8->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "Y", nullptr));
        label_9->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "Y", nullptr));
        label_10->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "X", nullptr));
        label_11->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\347\265\266\345\257\276\345\200\244", nullptr));
        label_12->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\347\233\270\345\257\276\345\200\244", nullptr));
        label_13->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\347\265\266\345\257\276\345\200\244", nullptr));
        label_14->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\347\233\270\345\257\276\345\200\244", nullptr));
        pushButtonUpdateView->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\350\241\250\347\244\272\346\233\264\346\226\260", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "<<=", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyAutoAlignmentFormClass", "=>>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyAutoAlignmentFormClass: public Ui_PropertyAutoAlignmentFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYAUTOALIGNMENTFORM_H
