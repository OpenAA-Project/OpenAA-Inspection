/********************************************************************************
** Form generated from reading UI file 'ColorCreateManualBlockForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORCREATEMANUALBLOCKFORM_H
#define UI_COLORCREATEMANUALBLOCKFORM_H

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
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ColorCreateManualBlockFormClass
{
public:
    QFrame *frameLibFolder;
    QLabel *label_6;
    QTableWidget *tableWidgetLibList;
    QPushButton *ButtonCancel;
    QPushButton *ButtonOK;
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
    QSpinBox *EditNMinNGCountL;
    QSpinBox *EditNMinNGCountH;
    QLabel *label_30;
    QSpinBox *EditNOKLengthH;
    QSpinBox *EditNOKLengthL;
    QLabel *label_29;
    QWidget *tab_6;
    QLabel *label_23;
    QLabel *label_22;
    QLabel *label_24;
    QLabel *label_21;
    QSpinBox *EditBBrightWidthL;
    QSpinBox *EditBBrightWidthH;
    QSpinBox *EditBOKDotL;
    QSpinBox *EditBOKDotH;
    QSpinBox *EditBMinNGCountL;
    QSpinBox *EditBMinNGCountH;
    QLabel *label_31;
    QSpinBox *EditBOKLengthH;
    QLabel *label_34;
    QSpinBox *EditBOKLengthL;
    QWidget *tab_7;
    QCheckBox *checkBModeEnabled;
    QCheckBox *checkBModeAbsoluteBright;
    QCheckBox *checkBModeNGCluster;
    QCheckBox *checkBModeDiffer;
    QCheckBox *checkBModeOnlyMatching;
    QCheckBox *checkBModeWhiteMask;
    QCheckBox *checkBModeBlackMask;
    QCheckBox *checkBModeCenterBrightFromParts;
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
    QLineEdit *EditLibID;
    QLineEdit *EditLibName;
    QToolButton *toolButtonR;
    QToolButton *toolButtonG;
    QToolButton *toolButtonB;

    void setupUi(QDialog *ColorCreateManualBlockFormClass)
    {
        if (ColorCreateManualBlockFormClass->objectName().isEmpty())
            ColorCreateManualBlockFormClass->setObjectName("ColorCreateManualBlockFormClass");
        ColorCreateManualBlockFormClass->resize(419, 431);
        frameLibFolder = new QFrame(ColorCreateManualBlockFormClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(ColorCreateManualBlockFormClass);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(40, 230, 20, 151));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Raised);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6->setIndent(1);
        tableWidgetLibList = new QTableWidget(ColorCreateManualBlockFormClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 201, 141));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonCancel = new QPushButton(ColorCreateManualBlockFormClass);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(280, 390, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon);
        ButtonOK = new QPushButton(ColorCreateManualBlockFormClass);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(40, 390, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon1);
        tabWidgetInspect = new QTabWidget(ColorCreateManualBlockFormClass);
        tabWidgetInspect->setObjectName("tabWidgetInspect");
        tabWidgetInspect->setGeometry(QRect(60, 230, 321, 151));
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        label_17 = new QLabel(tab_5);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(10, 30, 121, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_18 = new QLabel(tab_5);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(10, 50, 121, 21));
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
        EditNBrightWidthH->setGeometry(QRect(230, 30, 81, 22));
        EditNBrightWidthH->setMaximum(255);
        EditNOKDotH = new QSpinBox(tab_5);
        EditNOKDotH->setObjectName("EditNOKDotH");
        EditNOKDotH->setGeometry(QRect(230, 50, 81, 22));
        EditNOKDotH->setMaximum(99999999);
        EditNBrightWidthL = new QSpinBox(tab_5);
        EditNBrightWidthL->setObjectName("EditNBrightWidthL");
        EditNBrightWidthL->setGeometry(QRect(140, 30, 81, 22));
        EditNBrightWidthL->setMaximum(255);
        EditNOKDotL = new QSpinBox(tab_5);
        EditNOKDotL->setObjectName("EditNOKDotL");
        EditNOKDotL->setGeometry(QRect(140, 50, 81, 22));
        EditNOKDotL->setMaximum(99999999);
        EditNMinNGCountL = new QSpinBox(tab_5);
        EditNMinNGCountL->setObjectName("EditNMinNGCountL");
        EditNMinNGCountL->setGeometry(QRect(140, 90, 81, 22));
        EditNMinNGCountL->setMaximum(99999999);
        EditNMinNGCountH = new QSpinBox(tab_5);
        EditNMinNGCountH->setObjectName("EditNMinNGCountH");
        EditNMinNGCountH->setGeometry(QRect(230, 90, 81, 22));
        EditNMinNGCountH->setMaximum(99999999);
        label_30 = new QLabel(tab_5);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 90, 121, 21));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNOKLengthH = new QSpinBox(tab_5);
        EditNOKLengthH->setObjectName("EditNOKLengthH");
        EditNOKLengthH->setGeometry(QRect(230, 70, 81, 22));
        EditNOKLengthH->setMaximum(99999999);
        EditNOKLengthL = new QSpinBox(tab_5);
        EditNOKLengthL->setObjectName("EditNOKLengthL");
        EditNOKLengthL->setGeometry(QRect(140, 70, 81, 22));
        EditNOKLengthL->setMaximum(99999999);
        label_29 = new QLabel(tab_5);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(10, 70, 121, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
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
        label_22->setGeometry(QRect(10, 30, 121, 21));
        label_22->setFrameShape(QFrame::Panel);
        label_22->setFrameShadow(QFrame::Sunken);
        label_22->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_24 = new QLabel(tab_6);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(10, 50, 121, 21));
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
        EditBBrightWidthL->setGeometry(QRect(140, 30, 81, 22));
        EditBBrightWidthL->setMaximum(255);
        EditBBrightWidthH = new QSpinBox(tab_6);
        EditBBrightWidthH->setObjectName("EditBBrightWidthH");
        EditBBrightWidthH->setGeometry(QRect(230, 30, 81, 22));
        EditBBrightWidthH->setMaximum(255);
        EditBOKDotL = new QSpinBox(tab_6);
        EditBOKDotL->setObjectName("EditBOKDotL");
        EditBOKDotL->setGeometry(QRect(140, 50, 81, 22));
        EditBOKDotL->setMaximum(99999999);
        EditBOKDotH = new QSpinBox(tab_6);
        EditBOKDotH->setObjectName("EditBOKDotH");
        EditBOKDotH->setGeometry(QRect(230, 50, 81, 22));
        EditBOKDotH->setMaximum(99999999);
        EditBMinNGCountL = new QSpinBox(tab_6);
        EditBMinNGCountL->setObjectName("EditBMinNGCountL");
        EditBMinNGCountL->setGeometry(QRect(140, 90, 81, 22));
        EditBMinNGCountL->setMaximum(99999999);
        EditBMinNGCountH = new QSpinBox(tab_6);
        EditBMinNGCountH->setObjectName("EditBMinNGCountH");
        EditBMinNGCountH->setGeometry(QRect(230, 90, 81, 22));
        EditBMinNGCountH->setMaximum(99999999);
        label_31 = new QLabel(tab_6);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(10, 90, 121, 21));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBOKLengthH = new QSpinBox(tab_6);
        EditBOKLengthH->setObjectName("EditBOKLengthH");
        EditBOKLengthH->setGeometry(QRect(230, 70, 81, 22));
        EditBOKLengthH->setMaximum(99999999);
        label_34 = new QLabel(tab_6);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(10, 70, 121, 21));
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Sunken);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBOKLengthL = new QSpinBox(tab_6);
        EditBOKLengthL->setObjectName("EditBOKLengthL");
        EditBOKLengthL->setGeometry(QRect(140, 70, 81, 22));
        EditBOKLengthL->setMaximum(99999999);
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
        EditLibID = new QLineEdit(ColorCreateManualBlockFormClass);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(40, 160, 41, 21));
        EditLibID->setReadOnly(true);
        EditLibName = new QLineEdit(ColorCreateManualBlockFormClass);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(80, 160, 251, 21));
        EditLibName->setReadOnly(true);
        toolButtonR = new QToolButton(ColorCreateManualBlockFormClass);
        toolButtonR->setObjectName("toolButtonR");
        toolButtonR->setGeometry(QRect(70, 190, 91, 31));
        toolButtonR->setCheckable(true);
        toolButtonR->setChecked(true);
        toolButtonR->setAutoExclusive(true);
        toolButtonG = new QToolButton(ColorCreateManualBlockFormClass);
        toolButtonG->setObjectName("toolButtonG");
        toolButtonG->setGeometry(QRect(170, 190, 91, 31));
        toolButtonG->setCheckable(true);
        toolButtonG->setAutoExclusive(true);
        toolButtonB = new QToolButton(ColorCreateManualBlockFormClass);
        toolButtonB->setObjectName("toolButtonB");
        toolButtonB->setGeometry(QRect(270, 190, 91, 31));
        toolButtonB->setCheckable(true);
        toolButtonB->setAutoExclusive(true);

        retranslateUi(ColorCreateManualBlockFormClass);

        tabWidgetInspect->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ColorCreateManualBlockFormClass);
    } // setupUi

    void retranslateUi(QDialog *ColorCreateManualBlockFormClass)
    {
        ColorCreateManualBlockFormClass->setWindowTitle(QCoreApplication::translate("ColorCreateManualBlockFormClass", "ColorCreateManualBlockForm", nullptr));
        label_6->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\346\244\234\n"
"\346\237\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "Name", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "Cancel", nullptr));
        ButtonOK->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "OK", nullptr));
        label_17->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "OK\350\274\235\345\272\246\347\257\204\345\233\262", nullptr));
        label_18->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_19->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\346\232\227\345\201\264", nullptr));
        label_20->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\346\230\216\345\201\264", nullptr));
        label_30->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "NG\345\241\212\345\200\213\346\225\260", nullptr));
        label_29->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\343\201\223\343\202\214\344\273\245\344\270\212\343\201\256\351\225\267\343\201\225\343\201\247\357\274\256\357\274\247", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_5), QCoreApplication::translate("ColorCreateManualBlockFormClass", "\347\213\255\345\237\237", nullptr));
        label_23->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\346\232\227\345\201\264", nullptr));
        label_22->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "OK\350\274\235\345\272\246\347\257\204\345\233\262", nullptr));
        label_24->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_21->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\346\230\216\345\201\264", nullptr));
        label_31->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\357\274\256\357\274\247\345\241\212\345\200\213\346\225\260", nullptr));
        label_34->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\343\201\223\343\202\214\344\273\245\344\270\212\343\201\256\351\225\267\343\201\225\343\201\247\357\274\256\357\274\247", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_6), QCoreApplication::translate("ColorCreateManualBlockFormClass", "\345\272\203\345\237\237", nullptr));
        checkBModeEnabled->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\346\244\234\346\237\273\346\234\211\345\212\271", nullptr));
        checkBModeAbsoluteBright->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\347\265\266\345\257\276\350\274\235\345\272\246", nullptr));
        checkBModeNGCluster->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\345\241\212\346\244\234\346\237\273", nullptr));
        checkBModeDiffer->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\345\267\256\345\210\206\346\244\234\346\237\273", nullptr));
        checkBModeOnlyMatching->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\347\265\220\346\236\234\345\207\272\345\212\233\343\201\227\343\201\252\343\201\204", nullptr));
        checkBModeWhiteMask->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\347\231\275\343\203\236\343\202\271\343\202\257", nullptr));
        checkBModeBlackMask->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\351\273\222\343\203\236\343\202\271\343\202\257", nullptr));
        checkBModeCenterBrightFromParts->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\351\203\250\345\223\201\343\201\213\343\202\211\350\274\235\345\272\246\343\202\222\346\212\275\345\207\272\343\201\231\343\202\213", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_7), QCoreApplication::translate("ColorCreateManualBlockFormClass", "\345\261\236\346\200\247", nullptr));
        label_26->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_25->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        checkBModeAdjustable->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\344\270\255\345\277\203\350\274\235\345\272\246\350\243\234\346\255\243\343\202\222\346\234\211\345\212\271\343\201\253\343\201\231\343\202\213", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_8), QCoreApplication::translate("ColorCreateManualBlockFormClass", "\350\243\234\346\255\243", nullptr));
        label_27->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\343\203\226\343\203\255\343\203\203\343\202\257\345\215\230\344\275\223\343\201\247\343\201\256\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_28->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\345\205\250\344\275\223\343\201\247\343\201\256\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        checkBModeCommonMovable->setText(QCoreApplication::translate("ColorCreateManualBlockFormClass", "\345\205\250\344\275\223\343\201\247\343\201\256\346\216\242\347\264\242\343\202\222\346\234\211\345\212\271\343\201\253\343\201\231\343\202\213", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_9), QCoreApplication::translate("ColorCreateManualBlockFormClass", "\346\216\242\347\264\242", nullptr));
        toolButtonG->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ColorCreateManualBlockFormClass: public Ui_ColorCreateManualBlockFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORCREATEMANUALBLOCKFORM_H
