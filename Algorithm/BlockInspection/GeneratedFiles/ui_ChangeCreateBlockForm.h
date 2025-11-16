/********************************************************************************
** Form generated from reading UI file 'ChangeCreateBlockForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGECREATEBLOCKFORM_H
#define UI_CHANGECREATEBLOCKFORM_H

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
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangeCreateBlockFormClass
{
public:
    QFrame *frame;
    QLabel *label;
    QFrame *frameLibFolder;
    QTableWidget *tableWidgetLibList;
    QFrame *frame_5;
    QLabel *label_4;
    QLineEdit *EditLibID;
    QLineEdit *EditLibName;
    QLabel *label_3;
    QTabWidget *tabWidgetInspect;
    QWidget *tab_5;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QSpinBox *EditNBrightWidthH;
    QSpinBox *EditNOKDotH;
    QSpinBox *EditNBrightWidthL;
    QSpinBox *EditNOKDotL;
    QSpinBox *EditNOKLengthL;
    QSpinBox *EditNOKLengthH;
    QLabel *label_29;
    QSpinBox *EditNMinNGCountL;
    QLabel *label_30;
    QSpinBox *EditNMinNGCountH;
    QSpinBox *EditNConnectLen;
    QLabel *label_32;
    QWidget *tab_6;
    QLabel *label_23;
    QLabel *label_22;
    QLabel *label_24;
    QLabel *label_21;
    QSpinBox *EditBBrightWidthL;
    QSpinBox *EditBBrightWidthH;
    QSpinBox *EditBOKDotL;
    QSpinBox *EditBOKDotH;
    QSpinBox *EditBOKLengthH;
    QLabel *label_34;
    QSpinBox *EditBOKLengthL;
    QSpinBox *EditBMinNGCountL;
    QLabel *label_31;
    QSpinBox *EditBMinNGCountH;
    QSpinBox *EditBConnectLen;
    QLabel *label_33;
    QWidget *tab_7;
    QCheckBox *checkBModeEnabled;
    QCheckBox *checkBModeAbsoluteBright;
    QCheckBox *checkBModeNGCluster;
    QCheckBox *checkBModeDiffer;
    QCheckBox *checkBModeOnlyMatching;
    QCheckBox *checkBModeWhiteMask;
    QCheckBox *checkBModeBlackMask;
    QCheckBox *checkBModeCenterBrightFromParts;
    QCheckBox *checkBModeOppositeRange;
    QWidget *tab_8;
    QLabel *label_26;
    QLabel *label_25;
    QSpinBox *EditAdjustWhite;
    QCheckBox *checkBModeAdjustable;
    QSpinBox *EditAdjustBlack;
    QWidget *tab_9;
    QLabel *label_27;
    QLabel *label_28;
    QCheckBox *checkBModeCommonMovable;
    QSpinBox *EditSelfSearch;
    QSpinBox *EditCommonMoveDot;
    QLabel *label_6;
    QPushButton *ButtonOK;
    QPushButton *ButtonCancel;

    void setupUi(QDialog *ChangeCreateBlockFormClass)
    {
        if (ChangeCreateBlockFormClass->objectName().isEmpty())
            ChangeCreateBlockFormClass->setObjectName("ChangeCreateBlockFormClass");
        ChangeCreateBlockFormClass->resize(386, 485);
        frame = new QFrame(ChangeCreateBlockFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 381, 461));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 381, 21));
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameLibFolder = new QFrame(frame);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 20, 191, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        tableWidgetLibList = new QTableWidget(frame);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 20, 161, 141));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame_5 = new QFrame(frame);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 170, 361, 281));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame_5);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 20, 51, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(frame_5);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 20, 81, 21));
        EditLibID->setReadOnly(true);
        EditLibName = new QLineEdit(frame_5);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 20, 211, 21));
        label_3 = new QLabel(frame_5);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 351, 21));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidgetInspect = new QTabWidget(frame_5);
        tabWidgetInspect->setObjectName("tabWidgetInspect");
        tabWidgetInspect->setGeometry(QRect(30, 50, 321, 181));
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        label_17 = new QLabel(tab_5);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(10, 40, 121, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_18 = new QLabel(tab_5);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(10, 60, 121, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_19 = new QLabel(tab_5);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(140, 10, 81, 21));
        label_19->setFrameShape(QFrame::Panel);
        label_19->setFrameShadow(QFrame::Sunken);
        label_19->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_20 = new QLabel(tab_5);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(230, 10, 81, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        label_20->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNBrightWidthH = new QSpinBox(tab_5);
        EditNBrightWidthH->setObjectName("EditNBrightWidthH");
        EditNBrightWidthH->setGeometry(QRect(230, 40, 81, 22));
        EditNBrightWidthH->setMaximum(255);
        EditNOKDotH = new QSpinBox(tab_5);
        EditNOKDotH->setObjectName("EditNOKDotH");
        EditNOKDotH->setGeometry(QRect(230, 60, 81, 22));
        EditNOKDotH->setMaximum(99999999);
        EditNBrightWidthL = new QSpinBox(tab_5);
        EditNBrightWidthL->setObjectName("EditNBrightWidthL");
        EditNBrightWidthL->setGeometry(QRect(140, 40, 81, 22));
        EditNBrightWidthL->setMaximum(255);
        EditNOKDotL = new QSpinBox(tab_5);
        EditNOKDotL->setObjectName("EditNOKDotL");
        EditNOKDotL->setGeometry(QRect(140, 60, 81, 22));
        EditNOKDotL->setMaximum(99999999);
        EditNOKLengthL = new QSpinBox(tab_5);
        EditNOKLengthL->setObjectName("EditNOKLengthL");
        EditNOKLengthL->setGeometry(QRect(140, 80, 81, 22));
        EditNOKLengthL->setMaximum(99999999);
        EditNOKLengthH = new QSpinBox(tab_5);
        EditNOKLengthH->setObjectName("EditNOKLengthH");
        EditNOKLengthH->setGeometry(QRect(230, 80, 81, 22));
        EditNOKLengthH->setMaximum(99999999);
        label_29 = new QLabel(tab_5);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(10, 80, 121, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNMinNGCountL = new QSpinBox(tab_5);
        EditNMinNGCountL->setObjectName("EditNMinNGCountL");
        EditNMinNGCountL->setGeometry(QRect(140, 100, 81, 22));
        EditNMinNGCountL->setMaximum(99999999);
        label_30 = new QLabel(tab_5);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 100, 121, 21));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNMinNGCountH = new QSpinBox(tab_5);
        EditNMinNGCountH->setObjectName("EditNMinNGCountH");
        EditNMinNGCountH->setGeometry(QRect(230, 100, 81, 22));
        EditNMinNGCountH->setMaximum(99999999);
        EditNConnectLen = new QSpinBox(tab_5);
        EditNConnectLen->setObjectName("EditNConnectLen");
        EditNConnectLen->setGeometry(QRect(140, 130, 81, 22));
        EditNConnectLen->setMaximum(99999999);
        label_32 = new QLabel(tab_5);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(10, 130, 121, 21));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidgetInspect->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        label_23 = new QLabel(tab_6);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(140, 10, 81, 21));
        label_23->setFrameShape(QFrame::Panel);
        label_23->setFrameShadow(QFrame::Sunken);
        label_23->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_22 = new QLabel(tab_6);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(10, 40, 121, 21));
        label_22->setFrameShape(QFrame::Panel);
        label_22->setFrameShadow(QFrame::Sunken);
        label_22->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_24 = new QLabel(tab_6);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(10, 60, 121, 21));
        label_24->setFrameShape(QFrame::Panel);
        label_24->setFrameShadow(QFrame::Sunken);
        label_24->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_21 = new QLabel(tab_6);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(230, 10, 81, 21));
        label_21->setFrameShape(QFrame::Panel);
        label_21->setFrameShadow(QFrame::Sunken);
        label_21->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBBrightWidthL = new QSpinBox(tab_6);
        EditBBrightWidthL->setObjectName("EditBBrightWidthL");
        EditBBrightWidthL->setGeometry(QRect(140, 40, 81, 22));
        EditBBrightWidthL->setMaximum(255);
        EditBBrightWidthH = new QSpinBox(tab_6);
        EditBBrightWidthH->setObjectName("EditBBrightWidthH");
        EditBBrightWidthH->setGeometry(QRect(230, 40, 81, 22));
        EditBBrightWidthH->setMaximum(255);
        EditBOKDotL = new QSpinBox(tab_6);
        EditBOKDotL->setObjectName("EditBOKDotL");
        EditBOKDotL->setGeometry(QRect(140, 60, 81, 22));
        EditBOKDotL->setMaximum(99999999);
        EditBOKDotH = new QSpinBox(tab_6);
        EditBOKDotH->setObjectName("EditBOKDotH");
        EditBOKDotH->setGeometry(QRect(230, 60, 81, 22));
        EditBOKDotH->setMaximum(99999999);
        EditBOKLengthH = new QSpinBox(tab_6);
        EditBOKLengthH->setObjectName("EditBOKLengthH");
        EditBOKLengthH->setGeometry(QRect(230, 80, 81, 22));
        EditBOKLengthH->setMaximum(99999999);
        label_34 = new QLabel(tab_6);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(10, 80, 121, 21));
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Sunken);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBOKLengthL = new QSpinBox(tab_6);
        EditBOKLengthL->setObjectName("EditBOKLengthL");
        EditBOKLengthL->setGeometry(QRect(140, 80, 81, 22));
        EditBOKLengthL->setMaximum(99999999);
        EditBMinNGCountL = new QSpinBox(tab_6);
        EditBMinNGCountL->setObjectName("EditBMinNGCountL");
        EditBMinNGCountL->setGeometry(QRect(140, 100, 81, 22));
        EditBMinNGCountL->setMaximum(99999999);
        label_31 = new QLabel(tab_6);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(10, 100, 121, 21));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBMinNGCountH = new QSpinBox(tab_6);
        EditBMinNGCountH->setObjectName("EditBMinNGCountH");
        EditBMinNGCountH->setGeometry(QRect(230, 100, 81, 22));
        EditBMinNGCountH->setMaximum(99999999);
        EditBConnectLen = new QSpinBox(tab_6);
        EditBConnectLen->setObjectName("EditBConnectLen");
        EditBConnectLen->setGeometry(QRect(140, 130, 81, 22));
        EditBConnectLen->setMaximum(99999999);
        label_33 = new QLabel(tab_6);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(10, 130, 121, 21));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Sunken);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidgetInspect->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        checkBModeEnabled = new QCheckBox(tab_7);
        checkBModeEnabled->setObjectName("checkBModeEnabled");
        checkBModeEnabled->setGeometry(QRect(10, 10, 141, 18));
        checkBModeAbsoluteBright = new QCheckBox(tab_7);
        checkBModeAbsoluteBright->setObjectName("checkBModeAbsoluteBright");
        checkBModeAbsoluteBright->setGeometry(QRect(10, 30, 141, 18));
        checkBModeNGCluster = new QCheckBox(tab_7);
        checkBModeNGCluster->setObjectName("checkBModeNGCluster");
        checkBModeNGCluster->setGeometry(QRect(10, 50, 141, 18));
        checkBModeDiffer = new QCheckBox(tab_7);
        checkBModeDiffer->setObjectName("checkBModeDiffer");
        checkBModeDiffer->setGeometry(QRect(10, 70, 141, 18));
        checkBModeOnlyMatching = new QCheckBox(tab_7);
        checkBModeOnlyMatching->setObjectName("checkBModeOnlyMatching");
        checkBModeOnlyMatching->setGeometry(QRect(160, 10, 141, 18));
        checkBModeWhiteMask = new QCheckBox(tab_7);
        checkBModeWhiteMask->setObjectName("checkBModeWhiteMask");
        checkBModeWhiteMask->setGeometry(QRect(160, 30, 141, 18));
        checkBModeBlackMask = new QCheckBox(tab_7);
        checkBModeBlackMask->setObjectName("checkBModeBlackMask");
        checkBModeBlackMask->setGeometry(QRect(160, 50, 141, 18));
        checkBModeCenterBrightFromParts = new QCheckBox(tab_7);
        checkBModeCenterBrightFromParts->setObjectName("checkBModeCenterBrightFromParts");
        checkBModeCenterBrightFromParts->setGeometry(QRect(160, 70, 141, 18));
        checkBModeOppositeRange = new QCheckBox(tab_7);
        checkBModeOppositeRange->setObjectName("checkBModeOppositeRange");
        checkBModeOppositeRange->setGeometry(QRect(160, 90, 161, 18));
        tabWidgetInspect->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        label_26 = new QLabel(tab_8);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(10, 70, 201, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_25 = new QLabel(tab_8);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(10, 40, 201, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditAdjustWhite = new QSpinBox(tab_8);
        EditAdjustWhite->setObjectName("EditAdjustWhite");
        EditAdjustWhite->setGeometry(QRect(220, 70, 81, 22));
        EditAdjustWhite->setMaximum(255);
        checkBModeAdjustable = new QCheckBox(tab_8);
        checkBModeAdjustable->setObjectName("checkBModeAdjustable");
        checkBModeAdjustable->setGeometry(QRect(30, 10, 241, 18));
        EditAdjustBlack = new QSpinBox(tab_8);
        EditAdjustBlack->setObjectName("EditAdjustBlack");
        EditAdjustBlack->setGeometry(QRect(220, 40, 81, 22));
        EditAdjustBlack->setMaximum(255);
        tabWidgetInspect->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName("tab_9");
        label_27 = new QLabel(tab_9);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(10, 40, 201, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_28 = new QLabel(tab_9);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(10, 70, 201, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBModeCommonMovable = new QCheckBox(tab_9);
        checkBModeCommonMovable->setObjectName("checkBModeCommonMovable");
        checkBModeCommonMovable->setGeometry(QRect(40, 10, 231, 18));
        EditSelfSearch = new QSpinBox(tab_9);
        EditSelfSearch->setObjectName("EditSelfSearch");
        EditSelfSearch->setGeometry(QRect(220, 40, 81, 22));
        EditCommonMoveDot = new QSpinBox(tab_9);
        EditCommonMoveDot->setObjectName("EditCommonMoveDot");
        EditCommonMoveDot->setGeometry(QRect(220, 70, 81, 22));
        tabWidgetInspect->addTab(tab_9, QString());
        label_6 = new QLabel(frame_5);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 50, 20, 181));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Raised);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6->setIndent(1);
        ButtonOK = new QPushButton(frame_5);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(10, 240, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        ButtonCancel = new QPushButton(frame_5);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(250, 240, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);

        retranslateUi(ChangeCreateBlockFormClass);

        tabWidgetInspect->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(ChangeCreateBlockFormClass);
    } // setupUi

    void retranslateUi(QDialog *ChangeCreateBlockFormClass)
    {
        ChangeCreateBlockFormClass->setWindowTitle(QCoreApplication::translate("ChangeCreateBlockFormClass", "ChangeCreateBlockForm", nullptr));
        label->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "Name", nullptr));
        label_4->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "12345", nullptr));
        EditLibName->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "Library Name", nullptr));
        label_3->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\227\343\203\255\343\203\221\343\203\206\343\202\243", nullptr));
        label_17->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "OK\350\274\235\345\272\246\347\257\204\345\233\262", nullptr));
        label_18->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_19->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\346\232\227\345\201\264", nullptr));
        label_20->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\346\230\216\345\201\264", nullptr));
        label_29->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\343\201\223\343\202\214\344\273\245\344\270\212\343\201\256\351\225\267\343\201\225\343\201\247\357\274\256\357\274\247", nullptr));
        label_30->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "NG\345\241\212\345\200\213\346\225\260", nullptr));
        label_32->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "NG\346\216\245\347\266\232\350\267\235\351\233\242(\345\205\261\351\200\232\357\274\211", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_5), QCoreApplication::translate("ChangeCreateBlockFormClass", "\347\213\255\345\237\237", nullptr));
        label_23->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\346\232\227\345\201\264", nullptr));
        label_22->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "OK\350\274\235\345\272\246\347\257\204\345\233\262", nullptr));
        label_24->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_21->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\346\230\216\345\201\264", nullptr));
        label_34->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\343\201\223\343\202\214\344\273\245\344\270\212\343\201\256\351\225\267\343\201\225\343\201\247\357\274\256\357\274\247", nullptr));
        label_31->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\357\274\256\357\274\247\345\241\212\345\200\213\346\225\260", nullptr));
        label_33->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "NG\346\216\245\347\266\232\350\267\235\351\233\242(\345\205\261\351\200\232\357\274\211", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_6), QCoreApplication::translate("ChangeCreateBlockFormClass", "\345\272\203\345\237\237", nullptr));
        checkBModeEnabled->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\346\244\234\346\237\273\346\234\211\345\212\271", nullptr));
        checkBModeAbsoluteBright->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\347\265\266\345\257\276\350\274\235\345\272\246", nullptr));
        checkBModeNGCluster->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\345\241\212\346\244\234\346\237\273", nullptr));
        checkBModeDiffer->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\345\267\256\345\210\206\346\244\234\346\237\273", nullptr));
        checkBModeOnlyMatching->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\347\265\220\346\236\234\345\207\272\345\212\233\343\201\227\343\201\252\343\201\204", nullptr));
        checkBModeWhiteMask->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\347\231\275\343\203\236\343\202\271\343\202\257", nullptr));
        checkBModeBlackMask->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\351\273\222\343\203\236\343\202\271\343\202\257", nullptr));
        checkBModeCenterBrightFromParts->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\351\203\250\345\223\201\343\201\213\343\202\211\350\274\235\345\272\246\343\202\222\346\212\275\345\207\272\343\201\231\343\202\213", nullptr));
        checkBModeOppositeRange->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "Opposite range", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_7), QCoreApplication::translate("ChangeCreateBlockFormClass", "\345\261\236\346\200\247", nullptr));
        label_26->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_25->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        checkBModeAdjustable->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\344\270\255\345\277\203\350\274\235\345\272\246\350\243\234\346\255\243\343\202\222\346\234\211\345\212\271\343\201\253\343\201\231\343\202\213", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_8), QCoreApplication::translate("ChangeCreateBlockFormClass", "\350\243\234\346\255\243", nullptr));
        label_27->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\343\203\226\343\203\255\343\203\203\343\202\257\345\215\230\344\275\223\343\201\247\343\201\256\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_28->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\345\205\250\344\275\223\343\201\247\343\201\256\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        checkBModeCommonMovable->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\345\205\250\344\275\223\343\201\247\343\201\256\346\216\242\347\264\242\343\202\222\346\234\211\345\212\271\343\201\253\343\201\231\343\202\213", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_9), QCoreApplication::translate("ChangeCreateBlockFormClass", "\346\216\242\347\264\242", nullptr));
        label_6->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "\346\244\234\n"
"\346\237\273", nullptr));
        ButtonOK->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "OK", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("ChangeCreateBlockFormClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeCreateBlockFormClass: public Ui_ChangeCreateBlockFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGECREATEBLOCKFORM_H
