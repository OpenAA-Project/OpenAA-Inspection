/********************************************************************************
** Form generated from reading UI file 'GeneralSettingForm.ui'
**
** Created: Mon Aug 20 16:22:46 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERALSETTINGFORM_H
#define UI_GENERALSETTINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QWidget>
#include "PasswordPushButton.h"

QT_BEGIN_NAMESPACE

class Ui_GeneralSettingClass
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabSetting;
    QWidget *tabDB;
    QGridLayout *gridLayout1;
    QGroupBox *gbLocalDataBase;
    QGridLayout *gridLayout2;
    QVBoxLayout *vboxLayout;
    QLabel *label;
    QLineEdit *leHost;
    QLabel *label_19;
    QSpacerItem *spacerItem;
    QVBoxLayout *vboxLayout1;
    QLabel *label_2;
    QLineEdit *lePath;
    QLabel *label_18;
    QGroupBox *gbXMLDataBase_2;
    QGridLayout *gridLayout3;
    QVBoxLayout *vboxLayout2;
    QLabel *label_3;
    QLineEdit *leXMLHost;
    QLabel *label_17;
    QSpacerItem *spacerItem1;
    QVBoxLayout *vboxLayout3;
    QLabel *label_4;
    QLineEdit *leXMLPath;
    QLabel *label_16;
    QGroupBox *gbXMLDataBase_3;
    QGridLayout *gridLayout4;
    QLabel *label_6;
    QHBoxLayout *hboxLayout;
    QLineEdit *leMasterDir;
    PasswordPushButton *pbMasterDir;
    QLabel *label_13;
    QWidget *tabDisplay;
    QGridLayout *gridLayout5;
    QGroupBox *gbMasterImage;
    QGridLayout *gridLayout6;
    QLabel *label_5;
    QComboBox *cbResolution;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout7;
    QRadioButton *rbVertical;
    QRadioButton *rbHorizontal;
    QGroupBox *gbNGMark;
    QGridLayout *gridLayout8;
    QCheckBox *chNGBlinkEnable;
    QSpinBox *sbNGBlinkTime;
    QLabel *label_7;
    QLabel *label_8;
    QSpinBox *sbNGMarkSize;
    QLabel *label_9;
    PasswordPushButton *pbSetColor;
    QLabel *label_28;
    QSpinBox *sbNGImageOffset;
    QLabel *label_29;
    QGroupBox *gbLayout;
    QGridLayout *gridLayout9;
    QGroupBox *groupBox;
    QGridLayout *gridLayout10;
    PasswordPushButton *pbReturnSetting;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout11;
    PasswordPushButton *pbReturnDefault;
    QWidget *tabOperation;
    QGroupBox *gbNGSort;
    QGridLayout *gridLayout12;
    QRadioButton *rbTopBottom;
    QRadioButton *rbBottomTop;
    QRadioButton *rbLeftRight;
    QRadioButton *rbRightLeft;
    QCheckBox *chEachPieces;
    QLabel *label_11;
    QSpinBox *sbNGWaitTime;
    QLabel *label_10;
    QCheckBox *chShowOK;
    QCheckBox *chEnableNGPieceChange;
    PasswordPushButton *pbMMCSetting;
    QGroupBox *gbXMLDataBase_4;
    QGridLayout *gridLayout13;
    QLabel *label_15;
    QHBoxLayout *hboxLayout1;
    QLineEdit *leSaveDirNGImage;
    PasswordPushButton *pbSaveDirNGImage;
    QGroupBox *gbOutputDebugLog;
    QGridLayout *gridLayout14;
    QCheckBox *chOutputXMLData;
    QCheckBox *chShowInsDataMsg;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout15;
    QCheckBox *chNextCheck;
    QCheckBox *chEnterCheck;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_20;
    QSpinBox *sbListScrollRow;
    QLabel *label_21;
    QWidget *tabColor;
    QGroupBox *groupBox_3;
    QLabel *label_12;
    PasswordPushButton *pbShowSigGraph;
    QLabel *label_25;
    QSpinBox *sbPlusRed;
    QSpinBox *sbPlusGreen;
    QLabel *label_26;
    QSpinBox *sbPlusBlue;
    QLabel *label_27;
    QGroupBox *groupBox_5;
    QLabel *label_14;
    QToolButton *tbPieceColor;
    QGroupBox *groupBox_6;
    QLabel *label_22;
    QToolButton *tbOnlyFColor;
    QLabel *label_23;
    QLabel *label_24;
    QToolButton *tbOnlyBColor;
    QToolButton *tbFBColor;
    PasswordPushButton *pbOK;
    QSpacerItem *spacerItem2;
    PasswordPushButton *pbCancel;

    void setupUi(QDialog *GeneralSettingClass)
    {
        if (GeneralSettingClass->objectName().isEmpty())
            GeneralSettingClass->setObjectName(QString::fromUtf8("GeneralSettingClass"));
        GeneralSettingClass->resize(340, 557);
        gridLayout = new QGridLayout(GeneralSettingClass);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabSetting = new QTabWidget(GeneralSettingClass);
        tabSetting->setObjectName(QString::fromUtf8("tabSetting"));
        tabDB = new QWidget();
        tabDB->setObjectName(QString::fromUtf8("tabDB"));
        gridLayout1 = new QGridLayout(tabDB);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        gbLocalDataBase = new QGroupBox(tabDB);
        gbLocalDataBase->setObjectName(QString::fromUtf8("gbLocalDataBase"));
        gridLayout2 = new QGridLayout(gbLocalDataBase);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        label = new QLabel(gbLocalDataBase);
        label->setObjectName(QString::fromUtf8("label"));

        vboxLayout->addWidget(label);

        leHost = new QLineEdit(gbLocalDataBase);
        leHost->setObjectName(QString::fromUtf8("leHost"));
        leHost->setMinimumSize(QSize(131, 0));

        vboxLayout->addWidget(leHost);

        label_19 = new QLabel(gbLocalDataBase);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        vboxLayout->addWidget(label_19);


        gridLayout2->addLayout(vboxLayout, 0, 0, 1, 1);

        spacerItem = new QSpacerItem(71, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem, 0, 1, 1, 1);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        label_2 = new QLabel(gbLocalDataBase);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        vboxLayout1->addWidget(label_2);

        lePath = new QLineEdit(gbLocalDataBase);
        lePath->setObjectName(QString::fromUtf8("lePath"));

        vboxLayout1->addWidget(lePath);

        label_18 = new QLabel(gbLocalDataBase);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        vboxLayout1->addWidget(label_18);


        gridLayout2->addLayout(vboxLayout1, 1, 0, 1, 2);


        gridLayout1->addWidget(gbLocalDataBase, 0, 0, 1, 1);

        gbXMLDataBase_2 = new QGroupBox(tabDB);
        gbXMLDataBase_2->setObjectName(QString::fromUtf8("gbXMLDataBase_2"));
        gridLayout3 = new QGridLayout(gbXMLDataBase_2);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        label_3 = new QLabel(gbXMLDataBase_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        vboxLayout2->addWidget(label_3);

        leXMLHost = new QLineEdit(gbXMLDataBase_2);
        leXMLHost->setObjectName(QString::fromUtf8("leXMLHost"));
        leXMLHost->setMinimumSize(QSize(131, 0));

        vboxLayout2->addWidget(leXMLHost);

        label_17 = new QLabel(gbXMLDataBase_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        vboxLayout2->addWidget(label_17);


        gridLayout3->addLayout(vboxLayout2, 0, 0, 1, 1);

        spacerItem1 = new QSpacerItem(71, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout3->addItem(spacerItem1, 0, 1, 1, 1);

        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        label_4 = new QLabel(gbXMLDataBase_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        vboxLayout3->addWidget(label_4);

        leXMLPath = new QLineEdit(gbXMLDataBase_2);
        leXMLPath->setObjectName(QString::fromUtf8("leXMLPath"));

        vboxLayout3->addWidget(leXMLPath);

        label_16 = new QLabel(gbXMLDataBase_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        vboxLayout3->addWidget(label_16);


        gridLayout3->addLayout(vboxLayout3, 1, 0, 1, 2);


        gridLayout1->addWidget(gbXMLDataBase_2, 1, 0, 1, 1);

        gbXMLDataBase_3 = new QGroupBox(tabDB);
        gbXMLDataBase_3->setObjectName(QString::fromUtf8("gbXMLDataBase_3"));
        gridLayout4 = new QGridLayout(gbXMLDataBase_3);
        gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
        label_6 = new QLabel(gbXMLDataBase_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout4->addWidget(label_6, 0, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        leMasterDir = new QLineEdit(gbXMLDataBase_3);
        leMasterDir->setObjectName(QString::fromUtf8("leMasterDir"));
        leMasterDir->setMinimumSize(QSize(131, 0));

        hboxLayout->addWidget(leMasterDir);

        pbMasterDir = new PasswordPushButton(gbXMLDataBase_3);
        pbMasterDir->setObjectName(QString::fromUtf8("pbMasterDir"));
        pbMasterDir->setMaximumSize(QSize(23, 23));

        hboxLayout->addWidget(pbMasterDir);


        gridLayout4->addLayout(hboxLayout, 1, 0, 1, 1);

        label_13 = new QLabel(gbXMLDataBase_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout4->addWidget(label_13, 2, 0, 1, 1);


        gridLayout1->addWidget(gbXMLDataBase_3, 2, 0, 1, 1);

        tabSetting->addTab(tabDB, QString());
        tabDisplay = new QWidget();
        tabDisplay->setObjectName(QString::fromUtf8("tabDisplay"));
        gridLayout5 = new QGridLayout(tabDisplay);
        gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
        gbMasterImage = new QGroupBox(tabDisplay);
        gbMasterImage->setObjectName(QString::fromUtf8("gbMasterImage"));
        gridLayout6 = new QGridLayout(gbMasterImage);
        gridLayout6->setObjectName(QString::fromUtf8("gridLayout6"));
        label_5 = new QLabel(gbMasterImage);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout6->addWidget(label_5, 0, 0, 1, 1);

        cbResolution = new QComboBox(gbMasterImage);
        cbResolution->setObjectName(QString::fromUtf8("cbResolution"));

        gridLayout6->addWidget(cbResolution, 0, 1, 1, 1);

        groupBox_4 = new QGroupBox(gbMasterImage);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout7 = new QGridLayout(groupBox_4);
        gridLayout7->setObjectName(QString::fromUtf8("gridLayout7"));
        rbVertical = new QRadioButton(groupBox_4);
        rbVertical->setObjectName(QString::fromUtf8("rbVertical"));

        gridLayout7->addWidget(rbVertical, 0, 0, 1, 1);

        rbHorizontal = new QRadioButton(groupBox_4);
        rbHorizontal->setObjectName(QString::fromUtf8("rbHorizontal"));

        gridLayout7->addWidget(rbHorizontal, 0, 1, 1, 1);


        gridLayout6->addWidget(groupBox_4, 1, 0, 1, 2);


        gridLayout5->addWidget(gbMasterImage, 0, 0, 1, 3);

        gbNGMark = new QGroupBox(tabDisplay);
        gbNGMark->setObjectName(QString::fromUtf8("gbNGMark"));
        gridLayout8 = new QGridLayout(gbNGMark);
        gridLayout8->setObjectName(QString::fromUtf8("gridLayout8"));
        chNGBlinkEnable = new QCheckBox(gbNGMark);
        chNGBlinkEnable->setObjectName(QString::fromUtf8("chNGBlinkEnable"));
        chNGBlinkEnable->setChecked(true);

        gridLayout8->addWidget(chNGBlinkEnable, 0, 0, 1, 1);

        sbNGBlinkTime = new QSpinBox(gbNGMark);
        sbNGBlinkTime->setObjectName(QString::fromUtf8("sbNGBlinkTime"));
        sbNGBlinkTime->setMaximum(9999);
        sbNGBlinkTime->setValue(500);

        gridLayout8->addWidget(sbNGBlinkTime, 0, 1, 1, 1);

        label_7 = new QLabel(gbNGMark);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMaximumSize(QSize(50, 16777215));

        gridLayout8->addWidget(label_7, 0, 2, 1, 1);

        label_8 = new QLabel(gbNGMark);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout8->addWidget(label_8, 1, 0, 1, 1);

        sbNGMarkSize = new QSpinBox(gbNGMark);
        sbNGMarkSize->setObjectName(QString::fromUtf8("sbNGMarkSize"));
        sbNGMarkSize->setMaximum(999);
        sbNGMarkSize->setValue(10);

        gridLayout8->addWidget(sbNGMarkSize, 1, 1, 1, 1);

        label_9 = new QLabel(gbNGMark);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMaximumSize(QSize(50, 16777215));

        gridLayout8->addWidget(label_9, 1, 2, 1, 1);

        pbSetColor = new PasswordPushButton(gbNGMark);
        pbSetColor->setObjectName(QString::fromUtf8("pbSetColor"));

        gridLayout8->addWidget(pbSetColor, 2, 1, 1, 1);


        gridLayout5->addWidget(gbNGMark, 1, 0, 1, 3);

        label_28 = new QLabel(tabDisplay);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout5->addWidget(label_28, 2, 0, 1, 1);

        sbNGImageOffset = new QSpinBox(tabDisplay);
        sbNGImageOffset->setObjectName(QString::fromUtf8("sbNGImageOffset"));
        sbNGImageOffset->setMaximum(999);

        gridLayout5->addWidget(sbNGImageOffset, 2, 1, 1, 1);

        label_29 = new QLabel(tabDisplay);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setMaximumSize(QSize(50, 16777215));

        gridLayout5->addWidget(label_29, 2, 2, 1, 1);

        gbLayout = new QGroupBox(tabDisplay);
        gbLayout->setObjectName(QString::fromUtf8("gbLayout"));
        gridLayout9 = new QGridLayout(gbLayout);
        gridLayout9->setObjectName(QString::fromUtf8("gridLayout9"));
        groupBox = new QGroupBox(gbLayout);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout10 = new QGridLayout(groupBox);
        gridLayout10->setObjectName(QString::fromUtf8("gridLayout10"));
        pbReturnSetting = new PasswordPushButton(groupBox);
        pbReturnSetting->setObjectName(QString::fromUtf8("pbReturnSetting"));

        gridLayout10->addWidget(pbReturnSetting, 0, 0, 1, 1);


        gridLayout9->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(gbLayout);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout11 = new QGridLayout(groupBox_2);
        gridLayout11->setObjectName(QString::fromUtf8("gridLayout11"));
        pbReturnDefault = new PasswordPushButton(groupBox_2);
        pbReturnDefault->setObjectName(QString::fromUtf8("pbReturnDefault"));

        gridLayout11->addWidget(pbReturnDefault, 0, 0, 1, 1);


        gridLayout9->addWidget(groupBox_2, 0, 1, 1, 1);


        gridLayout5->addWidget(gbLayout, 3, 0, 1, 3);

        tabSetting->addTab(tabDisplay, QString());
        tabOperation = new QWidget();
        tabOperation->setObjectName(QString::fromUtf8("tabOperation"));
        gbNGSort = new QGroupBox(tabOperation);
        gbNGSort->setObjectName(QString::fromUtf8("gbNGSort"));
        gbNGSort->setGeometry(QRect(9, 9, 298, 96));
        gridLayout12 = new QGridLayout(gbNGSort);
        gridLayout12->setObjectName(QString::fromUtf8("gridLayout12"));
        rbTopBottom = new QRadioButton(gbNGSort);
        rbTopBottom->setObjectName(QString::fromUtf8("rbTopBottom"));
        rbTopBottom->setChecked(true);

        gridLayout12->addWidget(rbTopBottom, 0, 0, 1, 1);

        rbBottomTop = new QRadioButton(gbNGSort);
        rbBottomTop->setObjectName(QString::fromUtf8("rbBottomTop"));
        rbBottomTop->setChecked(false);

        gridLayout12->addWidget(rbBottomTop, 0, 1, 1, 1);

        rbLeftRight = new QRadioButton(gbNGSort);
        rbLeftRight->setObjectName(QString::fromUtf8("rbLeftRight"));

        gridLayout12->addWidget(rbLeftRight, 1, 0, 1, 1);

        rbRightLeft = new QRadioButton(gbNGSort);
        rbRightLeft->setObjectName(QString::fromUtf8("rbRightLeft"));

        gridLayout12->addWidget(rbRightLeft, 1, 1, 1, 1);

        chEachPieces = new QCheckBox(gbNGSort);
        chEachPieces->setObjectName(QString::fromUtf8("chEachPieces"));

        gridLayout12->addWidget(chEachPieces, 2, 0, 1, 1);

        label_11 = new QLabel(tabOperation);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(9, 111, 118, 20));
        label_11->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sbNGWaitTime = new QSpinBox(tabOperation);
        sbNGWaitTime->setObjectName(QString::fromUtf8("sbNGWaitTime"));
        sbNGWaitTime->setGeometry(QRect(133, 111, 118, 20));
        sbNGWaitTime->setMaximum(9999);
        label_10 = new QLabel(tabOperation);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(257, 111, 50, 20));
        label_10->setMaximumSize(QSize(50, 16777215));
        chShowOK = new QCheckBox(tabOperation);
        chShowOK->setObjectName(QString::fromUtf8("chShowOK"));
        chShowOK->setGeometry(QRect(9, 137, 242, 17));
        chEnableNGPieceChange = new QCheckBox(tabOperation);
        chEnableNGPieceChange->setObjectName(QString::fromUtf8("chEnableNGPieceChange"));
        chEnableNGPieceChange->setGeometry(QRect(9, 160, 242, 17));
        pbMMCSetting = new PasswordPushButton(tabOperation);
        pbMMCSetting->setObjectName(QString::fromUtf8("pbMMCSetting"));
        pbMMCSetting->setGeometry(QRect(133, 183, 174, 41));
        pbMMCSetting->setMinimumSize(QSize(0, 41));
        gbXMLDataBase_4 = new QGroupBox(tabOperation);
        gbXMLDataBase_4->setObjectName(QString::fromUtf8("gbXMLDataBase_4"));
        gbXMLDataBase_4->setGeometry(QRect(9, 230, 298, 77));
        gridLayout13 = new QGridLayout(gbXMLDataBase_4);
        gridLayout13->setObjectName(QString::fromUtf8("gridLayout13"));
        label_15 = new QLabel(gbXMLDataBase_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout13->addWidget(label_15, 0, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        leSaveDirNGImage = new QLineEdit(gbXMLDataBase_4);
        leSaveDirNGImage->setObjectName(QString::fromUtf8("leSaveDirNGImage"));
        leSaveDirNGImage->setMinimumSize(QSize(131, 0));

        hboxLayout1->addWidget(leSaveDirNGImage);

        pbSaveDirNGImage = new PasswordPushButton(gbXMLDataBase_4);
        pbSaveDirNGImage->setObjectName(QString::fromUtf8("pbSaveDirNGImage"));
        pbSaveDirNGImage->setMaximumSize(QSize(23, 23));

        hboxLayout1->addWidget(pbSaveDirNGImage);


        gridLayout13->addLayout(hboxLayout1, 1, 0, 1, 1);

        gbOutputDebugLog = new QGroupBox(tabOperation);
        gbOutputDebugLog->setObjectName(QString::fromUtf8("gbOutputDebugLog"));
        gbOutputDebugLog->setGeometry(QRect(9, 313, 298, 50));
        gbOutputDebugLog->setCheckable(true);
        gbOutputDebugLog->setChecked(false);
        gridLayout14 = new QGridLayout(gbOutputDebugLog);
        gridLayout14->setObjectName(QString::fromUtf8("gridLayout14"));
        chOutputXMLData = new QCheckBox(gbOutputDebugLog);
        chOutputXMLData->setObjectName(QString::fromUtf8("chOutputXMLData"));

        gridLayout14->addWidget(chOutputXMLData, 0, 0, 1, 1);

        chShowInsDataMsg = new QCheckBox(tabOperation);
        chShowInsDataMsg->setObjectName(QString::fromUtf8("chShowInsDataMsg"));
        chShowInsDataMsg->setGeometry(QRect(9, 369, 301, 17));
        groupBox_7 = new QGroupBox(tabOperation);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(9, 423, 298, 50));
        gridLayout15 = new QGridLayout(groupBox_7);
        gridLayout15->setObjectName(QString::fromUtf8("gridLayout15"));
        chNextCheck = new QCheckBox(groupBox_7);
        chNextCheck->setObjectName(QString::fromUtf8("chNextCheck"));

        gridLayout15->addWidget(chNextCheck, 0, 0, 1, 1);

        chEnterCheck = new QCheckBox(groupBox_7);
        chEnterCheck->setObjectName(QString::fromUtf8("chEnterCheck"));

        gridLayout15->addWidget(chEnterCheck, 0, 1, 1, 1);

        layoutWidget = new QWidget(tabOperation);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 392, 291, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_20 = new QLabel(layoutWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        horizontalLayout->addWidget(label_20);

        sbListScrollRow = new QSpinBox(layoutWidget);
        sbListScrollRow->setObjectName(QString::fromUtf8("sbListScrollRow"));

        horizontalLayout->addWidget(sbListScrollRow);

        label_21 = new QLabel(layoutWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(label_21);

        tabSetting->addTab(tabOperation, QString());
        tabColor = new QWidget();
        tabColor->setObjectName(QString::fromUtf8("tabColor"));
        groupBox_3 = new QGroupBox(tabColor);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 10, 281, 151));
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 30, 71, 16));
        pbShowSigGraph = new PasswordPushButton(groupBox_3);
        pbShowSigGraph->setObjectName(QString::fromUtf8("pbShowSigGraph"));
        pbShowSigGraph->setGeometry(QRect(160, 20, 101, 31));
        label_25 = new QLabel(groupBox_3);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(20, 63, 31, 16));
        sbPlusRed = new QSpinBox(groupBox_3);
        sbPlusRed->setObjectName(QString::fromUtf8("sbPlusRed"));
        sbPlusRed->setGeometry(QRect(170, 60, 71, 22));
        sbPlusRed->setMinimum(-255);
        sbPlusRed->setMaximum(255);
        sbPlusGreen = new QSpinBox(groupBox_3);
        sbPlusGreen->setObjectName(QString::fromUtf8("sbPlusGreen"));
        sbPlusGreen->setGeometry(QRect(170, 90, 71, 22));
        sbPlusGreen->setMinimum(-255);
        sbPlusGreen->setMaximum(255);
        label_26 = new QLabel(groupBox_3);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(20, 90, 31, 16));
        sbPlusBlue = new QSpinBox(groupBox_3);
        sbPlusBlue->setObjectName(QString::fromUtf8("sbPlusBlue"));
        sbPlusBlue->setGeometry(QRect(170, 120, 71, 22));
        sbPlusBlue->setMinimum(-255);
        sbPlusBlue->setMaximum(255);
        label_27 = new QLabel(groupBox_3);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(20, 120, 31, 16));
        groupBox_5 = new QGroupBox(tabColor);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 170, 281, 61));
        label_14 = new QLabel(groupBox_5);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(20, 30, 95, 16));
        tbPieceColor = new QToolButton(groupBox_5);
        tbPieceColor->setObjectName(QString::fromUtf8("tbPieceColor"));
        tbPieceColor->setGeometry(QRect(160, 20, 101, 31));
        groupBox_6 = new QGroupBox(tabColor);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 240, 281, 137));
        label_22 = new QLabel(groupBox_6);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(10, 22, 174, 31));
        tbOnlyFColor = new QToolButton(groupBox_6);
        tbOnlyFColor->setObjectName(QString::fromUtf8("tbOnlyFColor"));
        tbOnlyFColor->setGeometry(QRect(160, 22, 101, 31));
        label_23 = new QLabel(groupBox_6);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(10, 59, 174, 31));
        label_24 = new QLabel(groupBox_6);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(10, 96, 174, 31));
        tbOnlyBColor = new QToolButton(groupBox_6);
        tbOnlyBColor->setObjectName(QString::fromUtf8("tbOnlyBColor"));
        tbOnlyBColor->setGeometry(QRect(160, 59, 101, 31));
        tbFBColor = new QToolButton(groupBox_6);
        tbFBColor->setObjectName(QString::fromUtf8("tbFBColor"));
        tbFBColor->setGeometry(QRect(160, 96, 101, 31));
        tabSetting->addTab(tabColor, QString());

        gridLayout->addWidget(tabSetting, 0, 0, 1, 3);

        pbOK = new PasswordPushButton(GeneralSettingClass);
        pbOK->setObjectName(QString::fromUtf8("pbOK"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbOK->setIcon(icon);

        gridLayout->addWidget(pbOK, 1, 0, 1, 1);

        spacerItem2 = new QSpacerItem(135, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem2, 1, 1, 1, 1);

        pbCancel = new PasswordPushButton(GeneralSettingClass);
        pbCancel->setObjectName(QString::fromUtf8("pbCancel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbCancel->setIcon(icon1);

        gridLayout->addWidget(pbCancel, 1, 2, 1, 1);


        retranslateUi(GeneralSettingClass);

        tabSetting->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GeneralSettingClass);
    } // setupUi

    void retranslateUi(QDialog *GeneralSettingClass)
    {
        GeneralSettingClass->setWindowTitle(QApplication::translate("GeneralSettingClass", "General Setting", 0, QApplication::UnicodeUTF8));
        gbLocalDataBase->setTitle(QApplication::translate("GeneralSettingClass", "Local DataBase", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GeneralSettingClass", "Host Name (IP Address)", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("GeneralSettingClass", "(ex. Server )", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("GeneralSettingClass", "Local Path", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("GeneralSettingClass", "(ex. D:/Data/Regulus64.fdb )", 0, QApplication::UnicodeUTF8));
        gbXMLDataBase_2->setTitle(QApplication::translate("GeneralSettingClass", "XML DataBase", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("GeneralSettingClass", "Host Name (IP Address)", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("GeneralSettingClass", "(ex. Server )", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("GeneralSettingClass", "Local Path", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("GeneralSettingClass", "(ex. D:/Data )", 0, QApplication::UnicodeUTF8));
        gbXMLDataBase_3->setTitle(QApplication::translate("GeneralSettingClass", "Master Data", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("GeneralSettingClass", "Master Image File Directory", 0, QApplication::UnicodeUTF8));
        pbMasterDir->setText(QApplication::translate("GeneralSettingClass", "...", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("GeneralSettingClass", "(ex. //Server/Data )", 0, QApplication::UnicodeUTF8));
        tabSetting->setTabText(tabSetting->indexOf(tabDB), QApplication::translate("GeneralSettingClass", "DataBase", 0, QApplication::UnicodeUTF8));
        gbMasterImage->setTitle(QApplication::translate("GeneralSettingClass", "Master Image", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("GeneralSettingClass", "Image Resolution", 0, QApplication::UnicodeUTF8));
        cbResolution->clear();
        cbResolution->insertItems(0, QStringList()
         << QApplication::translate("GeneralSettingClass", "1/1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GeneralSettingClass", "1/2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GeneralSettingClass", "1/4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GeneralSettingClass", "1/8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GeneralSettingClass", "1/16", 0, QApplication::UnicodeUTF8)
        );
        groupBox_4->setTitle(QApplication::translate("GeneralSettingClass", "Alignment", 0, QApplication::UnicodeUTF8));
        rbVertical->setText(QApplication::translate("GeneralSettingClass", "Vertical", 0, QApplication::UnicodeUTF8));
        rbHorizontal->setText(QApplication::translate("GeneralSettingClass", "Horizontal", 0, QApplication::UnicodeUTF8));
        gbNGMark->setTitle(QApplication::translate("GeneralSettingClass", "NG Mark", 0, QApplication::UnicodeUTF8));
        chNGBlinkEnable->setText(QApplication::translate("GeneralSettingClass", "NG Blink Enable", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("GeneralSettingClass", "ms", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("GeneralSettingClass", "NG Mark Size", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("GeneralSettingClass", "dot", 0, QApplication::UnicodeUTF8));
        pbSetColor->setText(QApplication::translate("GeneralSettingClass", "ColorSetting", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("GeneralSettingClass", "NG Image Offset", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("GeneralSettingClass", "dot", 0, QApplication::UnicodeUTF8));
        gbLayout->setTitle(QApplication::translate("GeneralSettingClass", "Layout", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("GeneralSettingClass", "Return to setting file", 0, QApplication::UnicodeUTF8));
        pbReturnSetting->setText(QApplication::translate("GeneralSettingClass", "Execute", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("GeneralSettingClass", "Return to default", 0, QApplication::UnicodeUTF8));
        pbReturnDefault->setText(QApplication::translate("GeneralSettingClass", "Execute", 0, QApplication::UnicodeUTF8));
        tabSetting->setTabText(tabSetting->indexOf(tabDisplay), QApplication::translate("GeneralSettingClass", "Display", 0, QApplication::UnicodeUTF8));
        gbNGSort->setTitle(QApplication::translate("GeneralSettingClass", "NG Sort", 0, QApplication::UnicodeUTF8));
        rbTopBottom->setText(QApplication::translate("GeneralSettingClass", "Top to Bottom", 0, QApplication::UnicodeUTF8));
        rbBottomTop->setText(QApplication::translate("GeneralSettingClass", "Bottom to Top", 0, QApplication::UnicodeUTF8));
        rbLeftRight->setText(QApplication::translate("GeneralSettingClass", "Left to Right", 0, QApplication::UnicodeUTF8));
        rbRightLeft->setText(QApplication::translate("GeneralSettingClass", "Right to Left", 0, QApplication::UnicodeUTF8));
        chEachPieces->setText(QApplication::translate("GeneralSettingClass", "Each Pieces", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("GeneralSettingClass", "NG Wait Time", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("GeneralSettingClass", "ms", 0, QApplication::UnicodeUTF8));
        chShowOK->setText(QApplication::translate("GeneralSettingClass", "Show OK Result", 0, QApplication::UnicodeUTF8));
        chEnableNGPieceChange->setText(QApplication::translate("GeneralSettingClass", "Permit change of NG piece number", 0, QApplication::UnicodeUTF8));
        pbMMCSetting->setText(QApplication::translate("GeneralSettingClass", "MMC Setting", 0, QApplication::UnicodeUTF8));
        gbXMLDataBase_4->setTitle(QApplication::translate("GeneralSettingClass", "NG Image", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("GeneralSettingClass", "Save Directory NG Image", 0, QApplication::UnicodeUTF8));
        pbSaveDirNGImage->setText(QApplication::translate("GeneralSettingClass", "...", 0, QApplication::UnicodeUTF8));
        gbOutputDebugLog->setTitle(QApplication::translate("GeneralSettingClass", "Output Debug Log", 0, QApplication::UnicodeUTF8));
        chOutputXMLData->setText(QApplication::translate("GeneralSettingClass", "Output XML Data", 0, QApplication::UnicodeUTF8));
        chShowInsDataMsg->setText(QApplication::translate("GeneralSettingClass", "After read the inspection data, show message", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("GeneralSettingClass", "NG List", 0, QApplication::UnicodeUTF8));
        chNextCheck->setText(QApplication::translate("GeneralSettingClass", "Invalid Right&&Left key", 0, QApplication::UnicodeUTF8));
        chEnterCheck->setText(QApplication::translate("GeneralSettingClass", "Next history at Enter key", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("GeneralSettingClass", "Sending list row line (Disable is 0)", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("GeneralSettingClass", "Row", 0, QApplication::UnicodeUTF8));
        tabSetting->setTabText(tabSetting->indexOf(tabOperation), QApplication::translate("GeneralSettingClass", "Operation", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("GeneralSettingClass", "Image Color", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("GeneralSettingClass", "Color Sigmoid", 0, QApplication::UnicodeUTF8));
        pbShowSigGraph->setText(QApplication::translate("GeneralSettingClass", "Show Graph", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("GeneralSettingClass", "Red", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("GeneralSettingClass", "Green", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("GeneralSettingClass", "Blue", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("GeneralSettingClass", "Piece information", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("GeneralSettingClass", "Text & Piece color", 0, QApplication::UnicodeUTF8));
        tbPieceColor->setText(QApplication::translate("GeneralSettingClass", "...", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("GeneralSettingClass", "Color of history list", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("GeneralSettingClass", "Only Front side", 0, QApplication::UnicodeUTF8));
        tbOnlyFColor->setText(QApplication::translate("GeneralSettingClass", "...", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("GeneralSettingClass", "Only Back side", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("GeneralSettingClass", "Both side", 0, QApplication::UnicodeUTF8));
        tbOnlyBColor->setText(QApplication::translate("GeneralSettingClass", "...", 0, QApplication::UnicodeUTF8));
        tbFBColor->setText(QApplication::translate("GeneralSettingClass", "...", 0, QApplication::UnicodeUTF8));
        tabSetting->setTabText(tabSetting->indexOf(tabColor), QApplication::translate("GeneralSettingClass", "Color", 0, QApplication::UnicodeUTF8));
        pbOK->setText(QApplication::translate("GeneralSettingClass", "OK", 0, QApplication::UnicodeUTF8));
        pbCancel->setText(QApplication::translate("GeneralSettingClass", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GeneralSettingClass: public Ui_GeneralSettingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERALSETTINGFORM_H
