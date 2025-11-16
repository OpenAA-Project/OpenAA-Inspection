/********************************************************************************
** Form generated from reading UI file 'TrueColorChangeCreateBlockForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRUECOLORCHANGECREATEBLOCKFORM_H
#define UI_TRUECOLORCHANGECREATEBLOCKFORM_H

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

class Ui_TrueColorChangeCreateBlockFormClass
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
    QLabel *label_61;
    QSpinBox *EditNMergin;
    QLabel *label_48;
    QPushButton *pushButtonNColor;
    QSpinBox *EditNOKDot;
    QFrame *frameNarrow;
    QSpinBox *EditNMinNGCount;
    QLabel *label_30;
    QSpinBox *EditNOKLength;
    QLabel *label_34;
    QWidget *tab_6;
    QPushButton *pushButtonBColor;
    QSpinBox *EditBMergin;
    QLabel *label_53;
    QSpinBox *EditBOKDot;
    QFrame *frameBroad;
    QLabel *label_54;
    QLabel *label_31;
    QSpinBox *EditBMinNGCount;
    QSpinBox *EditBOKLength;
    QLabel *label_35;
    QWidget *tab_7;
    QCheckBox *checkBModeEnabled;
    QCheckBox *checkBModeNGCluster;
    QCheckBox *checkBModeOnlyMatching;
    QCheckBox *checkBModeCenterBrightFromParts;
    QCheckBox *checkBModeInvertLogic;
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

    void setupUi(QDialog *TrueColorChangeCreateBlockFormClass)
    {
        if (TrueColorChangeCreateBlockFormClass->objectName().isEmpty())
            TrueColorChangeCreateBlockFormClass->setObjectName("TrueColorChangeCreateBlockFormClass");
        TrueColorChangeCreateBlockFormClass->resize(402, 564);
        frame = new QFrame(TrueColorChangeCreateBlockFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 381, 551));
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
        frame_5->setGeometry(QRect(10, 170, 361, 371));
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
        tabWidgetInspect->setGeometry(QRect(30, 50, 321, 271));
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        label_61 = new QLabel(tab_5);
        label_61->setObjectName("label_61");
        label_61->setGeometry(QRect(10, 10, 70, 21));
        label_61->setFrameShape(QFrame::Panel);
        label_61->setFrameShadow(QFrame::Sunken);
        label_61->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNMergin = new QSpinBox(tab_5);
        EditNMergin->setObjectName("EditNMergin");
        EditNMergin->setGeometry(QRect(20, 30, 61, 22));
        EditNMergin->setMaximum(99999999);
        label_48 = new QLabel(tab_5);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(10, 60, 71, 21));
        label_48->setFrameShape(QFrame::Panel);
        label_48->setFrameShadow(QFrame::Sunken);
        label_48->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonNColor = new QPushButton(tab_5);
        pushButtonNColor->setObjectName("pushButtonNColor");
        pushButtonNColor->setGeometry(QRect(20, 110, 50, 40));
        EditNOKDot = new QSpinBox(tab_5);
        EditNOKDot->setObjectName("EditNOKDot");
        EditNOKDot->setGeometry(QRect(20, 80, 61, 22));
        EditNOKDot->setMaximum(99999999);
        frameNarrow = new QFrame(tab_5);
        frameNarrow->setObjectName("frameNarrow");
        frameNarrow->setGeometry(QRect(90, 10, 221, 161));
        frameNarrow->setFrameShape(QFrame::NoFrame);
        frameNarrow->setFrameShadow(QFrame::Raised);
        EditNMinNGCount = new QSpinBox(tab_5);
        EditNMinNGCount->setObjectName("EditNMinNGCount");
        EditNMinNGCount->setGeometry(QRect(10, 170, 81, 22));
        EditNMinNGCount->setMaximum(99999999);
        label_30 = new QLabel(tab_5);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 150, 81, 21));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNOKLength = new QSpinBox(tab_5);
        EditNOKLength->setObjectName("EditNOKLength");
        EditNOKLength->setGeometry(QRect(10, 220, 81, 22));
        EditNOKLength->setMaximum(99999999);
        label_34 = new QLabel(tab_5);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(10, 200, 121, 21));
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Sunken);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidgetInspect->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        pushButtonBColor = new QPushButton(tab_6);
        pushButtonBColor->setObjectName("pushButtonBColor");
        pushButtonBColor->setGeometry(QRect(20, 110, 50, 40));
        EditBMergin = new QSpinBox(tab_6);
        EditBMergin->setObjectName("EditBMergin");
        EditBMergin->setGeometry(QRect(20, 30, 61, 22));
        EditBMergin->setMaximum(99999999);
        label_53 = new QLabel(tab_6);
        label_53->setObjectName("label_53");
        label_53->setGeometry(QRect(10, 60, 71, 21));
        label_53->setFrameShape(QFrame::Panel);
        label_53->setFrameShadow(QFrame::Sunken);
        label_53->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBOKDot = new QSpinBox(tab_6);
        EditBOKDot->setObjectName("EditBOKDot");
        EditBOKDot->setGeometry(QRect(20, 80, 61, 22));
        EditBOKDot->setMaximum(99999999);
        frameBroad = new QFrame(tab_6);
        frameBroad->setObjectName("frameBroad");
        frameBroad->setGeometry(QRect(90, 10, 221, 161));
        frameBroad->setFrameShape(QFrame::NoFrame);
        frameBroad->setFrameShadow(QFrame::Raised);
        label_54 = new QLabel(tab_6);
        label_54->setObjectName("label_54");
        label_54->setGeometry(QRect(10, 10, 70, 21));
        label_54->setFrameShape(QFrame::Panel);
        label_54->setFrameShadow(QFrame::Sunken);
        label_54->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_31 = new QLabel(tab_6);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(10, 150, 81, 21));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBMinNGCount = new QSpinBox(tab_6);
        EditBMinNGCount->setObjectName("EditBMinNGCount");
        EditBMinNGCount->setGeometry(QRect(10, 170, 81, 22));
        EditBMinNGCount->setMaximum(99999999);
        EditBOKLength = new QSpinBox(tab_6);
        EditBOKLength->setObjectName("EditBOKLength");
        EditBOKLength->setGeometry(QRect(10, 220, 81, 22));
        EditBOKLength->setMaximum(99999999);
        label_35 = new QLabel(tab_6);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(10, 200, 121, 21));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Sunken);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidgetInspect->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        checkBModeEnabled = new QCheckBox(tab_7);
        checkBModeEnabled->setObjectName("checkBModeEnabled");
        checkBModeEnabled->setGeometry(QRect(10, 10, 141, 18));
        checkBModeNGCluster = new QCheckBox(tab_7);
        checkBModeNGCluster->setObjectName("checkBModeNGCluster");
        checkBModeNGCluster->setGeometry(QRect(10, 50, 141, 18));
        checkBModeOnlyMatching = new QCheckBox(tab_7);
        checkBModeOnlyMatching->setObjectName("checkBModeOnlyMatching");
        checkBModeOnlyMatching->setGeometry(QRect(160, 10, 141, 18));
        checkBModeCenterBrightFromParts = new QCheckBox(tab_7);
        checkBModeCenterBrightFromParts->setObjectName("checkBModeCenterBrightFromParts");
        checkBModeCenterBrightFromParts->setGeometry(QRect(160, 50, 141, 18));
        checkBModeInvertLogic = new QCheckBox(tab_7);
        checkBModeInvertLogic->setObjectName("checkBModeInvertLogic");
        checkBModeInvertLogic->setGeometry(QRect(160, 110, 141, 18));
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
        label_6->setGeometry(QRect(10, 50, 20, 271));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Raised);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6->setIndent(1);
        ButtonOK = new QPushButton(frame_5);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(10, 330, 75, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        ButtonCancel = new QPushButton(frame_5);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(270, 330, 81, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/fireworks_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);

        retranslateUi(TrueColorChangeCreateBlockFormClass);

        tabWidgetInspect->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(TrueColorChangeCreateBlockFormClass);
    } // setupUi

    void retranslateUi(QDialog *TrueColorChangeCreateBlockFormClass)
    {
        TrueColorChangeCreateBlockFormClass->setWindowTitle(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "TrueColorChangeCreateBlockForm", nullptr));
        label->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "Name", nullptr));
        label_4->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "12345", nullptr));
        EditLibName->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "Library Name", nullptr));
        label_3->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\227\343\203\255\343\203\221\343\203\206\343\202\243", nullptr));
        label_61->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\350\274\235\345\272\246\343\203\236\343\203\274\343\202\270\343\203\263", nullptr));
        label_48->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        pushButtonNColor->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "Color", nullptr));
        label_30->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "NG\345\241\212\345\200\213\346\225\260", nullptr));
        label_34->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\343\201\223\343\202\214\344\273\245\344\270\212\343\201\256\351\225\267\343\201\225\343\201\247\357\274\256\357\274\247", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_5), QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\347\213\255\345\237\237", nullptr));
        pushButtonBColor->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "Color", nullptr));
        label_53->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_54->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\350\274\235\345\272\246\343\203\236\343\203\274\343\202\270\343\203\263", nullptr));
        label_31->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "NG\345\241\212\345\200\213\346\225\260", nullptr));
        label_35->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\343\201\223\343\202\214\344\273\245\344\270\212\343\201\256\351\225\267\343\201\225\343\201\247\357\274\256\357\274\247", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_6), QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\345\272\203\345\237\237", nullptr));
        checkBModeEnabled->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\346\244\234\346\237\273\346\234\211\345\212\271", nullptr));
        checkBModeNGCluster->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\345\241\212\346\244\234\346\237\273", nullptr));
        checkBModeOnlyMatching->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\347\265\220\346\236\234\345\207\272\345\212\233\343\201\227\343\201\252\343\201\204", nullptr));
        checkBModeCenterBrightFromParts->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\351\203\250\345\223\201\343\201\213\343\202\211\350\274\235\345\272\246\343\202\222\346\212\275\345\207\272\343\201\231\343\202\213", nullptr));
        checkBModeInvertLogic->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\350\253\226\347\220\206\345\217\215\350\273\242", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_7), QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\345\261\236\346\200\247", nullptr));
        label_26->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_25->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        checkBModeAdjustable->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\344\270\255\345\277\203\350\274\235\345\272\246\350\243\234\346\255\243\343\202\222\346\234\211\345\212\271\343\201\253\343\201\231\343\202\213", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_8), QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\350\243\234\346\255\243", nullptr));
        label_27->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\343\203\226\343\203\255\343\203\203\343\202\257\345\215\230\344\275\223\343\201\247\343\201\256\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_28->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\345\205\250\344\275\223\343\201\247\343\201\256\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        checkBModeCommonMovable->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\345\205\250\344\275\223\343\201\247\343\201\256\346\216\242\347\264\242\343\202\222\346\234\211\345\212\271\343\201\253\343\201\231\343\202\213", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_9), QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\346\216\242\347\264\242", nullptr));
        label_6->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "\346\244\234\n"
"\346\237\273", nullptr));
        ButtonOK->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "OK", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("TrueColorChangeCreateBlockFormClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrueColorChangeCreateBlockFormClass: public Ui_TrueColorChangeCreateBlockFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRUECOLORCHANGECREATEBLOCKFORM_H
