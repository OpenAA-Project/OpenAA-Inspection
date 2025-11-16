/********************************************************************************
** Form generated from reading UI file 'SelectLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLIBRARYDIALOG_H
#define UI_SELECTLIBRARYDIALOG_H

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
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectLibraryDialog
{
public:
    QPushButton *pushButtonSelect;
    QFrame *frameLibFolder;
    QLabel *label_4;
    QPushButton *pushButtonCancel;
    QLineEdit *EditLibID;
    QLineEdit *EditLibName;
    QTableWidget *tableWidgetLibList;
    QFrame *frame_9;
    QLabel *label_39;
    QCheckBox *checkBModeAbsoluteBright;
    QCheckBox *checkBModeCenterBrightFromParts;
    QCheckBox *checkBModeEnabled;
    QCheckBox *checkBModeDynamicMask;
    QLabel *label_30;
    QSpinBox *EditTransitDot;
    QFrame *frame_6;
    QLabel *label_35;
    QLabel *label_20;
    QLabel *label_17;
    QSpinBox *EditNGSizeIH;
    QLabel *label_18;
    QSpinBox *EditBrightWidthIL;
    QSpinBox *EditNGSizeIL;
    QSpinBox *EditBrightWidthIH;
    QLabel *label_19;
    QFrame *frame_7;
    QLabel *label_37;
    QLabel *label_22;
    QSpinBox *EditNGSizeOH;
    QLabel *label_21;
    QSpinBox *EditNGSizeOL;
    QSpinBox *EditBrightWidthOL;
    QLabel *label_24;
    QLabel *label_23;
    QSpinBox *EditBrightWidthOH;
    QFrame *frame_11;
    QLabel *label_41;
    QSpinBox *EditAdjustBrightIL;
    QSpinBox *EditAdjustBrightIH;
    QLabel *label_26;
    QLabel *label_25;
    QSpinBox *EditAdjustBrightOH;
    QLabel *label_29;
    QSpinBox *EditAdjustBrightOL;
    QLabel *label_34;
    QFrame *frame_13;
    QLabel *label_43;
    QFrame *frame_14;
    QLabel *label_44;
    QSpinBox *EditSearchDot;
    QLabel *label_27;
    QLabel *label_28;
    QSpinBox *EditGlobalSearchDot;
    QFrame *frame_12;
    QLabel *label_42;
    QCheckBox *checkBModeUseRegularBrightness;
    QLabel *label_33;
    QSpinBox *EditRegulatedColI;
    QSpinBox *EditRegulatedColO;
    QLabel *label_36;

    void setupUi(QDialog *SelectLibraryDialog)
    {
        if (SelectLibraryDialog->objectName().isEmpty())
            SelectLibraryDialog->setObjectName("SelectLibraryDialog");
        SelectLibraryDialog->resize(476, 858);
        pushButtonSelect = new QPushButton(SelectLibraryDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(80, 810, 121, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSelect->setIcon(icon);
        frameLibFolder = new QFrame(SelectLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 221, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(SelectLibraryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 230, 51, 31));
        QFont font;
        font.setPointSize(12);
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonCancel = new QPushButton(SelectLibraryDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(290, 810, 121, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        EditLibID = new QLineEdit(SelectLibraryDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 230, 71, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        EditLibName = new QLineEdit(SelectLibraryDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(130, 230, 331, 31));
        EditLibName->setFont(font);
        tableWidgetLibList = new QTableWidget(SelectLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(240, 10, 221, 201));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame_9 = new QFrame(SelectLibraryDialog);
        frame_9->setObjectName("frame_9");
        frame_9->setGeometry(QRect(40, 440, 396, 91));
        frame_9->setFrameShape(QFrame::StyledPanel);
        frame_9->setFrameShadow(QFrame::Sunken);
        label_39 = new QLabel(frame_9);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(0, 0, 31, 91));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Raised);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_39->setIndent(1);
        checkBModeAbsoluteBright = new QCheckBox(frame_9);
        checkBModeAbsoluteBright->setObjectName("checkBModeAbsoluteBright");
        checkBModeAbsoluteBright->setGeometry(QRect(40, 30, 161, 18));
        checkBModeCenterBrightFromParts = new QCheckBox(frame_9);
        checkBModeCenterBrightFromParts->setObjectName("checkBModeCenterBrightFromParts");
        checkBModeCenterBrightFromParts->setGeometry(QRect(190, 10, 191, 18));
        checkBModeEnabled = new QCheckBox(frame_9);
        checkBModeEnabled->setObjectName("checkBModeEnabled");
        checkBModeEnabled->setGeometry(QRect(40, 10, 161, 18));
        checkBModeDynamicMask = new QCheckBox(frame_9);
        checkBModeDynamicMask->setObjectName("checkBModeDynamicMask");
        checkBModeDynamicMask->setGeometry(QRect(190, 30, 191, 18));
        label_30 = new QLabel(frame_9);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(40, 60, 266, 21));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditTransitDot = new QSpinBox(frame_9);
        EditTransitDot->setObjectName("EditTransitDot");
        EditTransitDot->setGeometry(QRect(310, 60, 81, 22));
        EditTransitDot->setMaximum(255);
        frame_6 = new QFrame(SelectLibraryDialog);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(40, 266, 396, 81));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Sunken);
        label_35 = new QLabel(frame_6);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(0, 0, 31, 81));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Raised);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_35->setIndent(1);
        label_20 = new QLabel(frame_6);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(306, 8, 81, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        label_20->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_17 = new QLabel(frame_6);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(36, 28, 176, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNGSizeIH = new QSpinBox(frame_6);
        EditNGSizeIH->setObjectName("EditNGSizeIH");
        EditNGSizeIH->setGeometry(QRect(306, 48, 81, 22));
        EditNGSizeIH->setMaximum(99999999);
        label_18 = new QLabel(frame_6);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(36, 48, 176, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBrightWidthIL = new QSpinBox(frame_6);
        EditBrightWidthIL->setObjectName("EditBrightWidthIL");
        EditBrightWidthIL->setGeometry(QRect(218, 28, 81, 22));
        EditBrightWidthIL->setMaximum(255);
        EditNGSizeIL = new QSpinBox(frame_6);
        EditNGSizeIL->setObjectName("EditNGSizeIL");
        EditNGSizeIL->setGeometry(QRect(218, 48, 81, 22));
        EditNGSizeIL->setMaximum(99999999);
        EditBrightWidthIH = new QSpinBox(frame_6);
        EditBrightWidthIH->setObjectName("EditBrightWidthIH");
        EditBrightWidthIH->setGeometry(QRect(306, 28, 81, 22));
        EditBrightWidthIH->setMaximum(255);
        label_19 = new QLabel(frame_6);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(218, 8, 81, 21));
        label_19->setFrameShape(QFrame::Panel);
        label_19->setFrameShadow(QFrame::Sunken);
        label_19->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_7 = new QFrame(SelectLibraryDialog);
        frame_7->setObjectName("frame_7");
        frame_7->setGeometry(QRect(40, 348, 396, 81));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Sunken);
        label_37 = new QLabel(frame_7);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(0, 0, 31, 81));
        label_37->setFrameShape(QFrame::Panel);
        label_37->setFrameShadow(QFrame::Raised);
        label_37->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_37->setIndent(1);
        label_22 = new QLabel(frame_7);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(36, 30, 176, 21));
        label_22->setFrameShape(QFrame::Panel);
        label_22->setFrameShadow(QFrame::Sunken);
        label_22->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNGSizeOH = new QSpinBox(frame_7);
        EditNGSizeOH->setObjectName("EditNGSizeOH");
        EditNGSizeOH->setGeometry(QRect(306, 50, 81, 22));
        EditNGSizeOH->setMaximum(99999999);
        label_21 = new QLabel(frame_7);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(306, 10, 81, 21));
        label_21->setFrameShape(QFrame::Panel);
        label_21->setFrameShadow(QFrame::Sunken);
        label_21->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNGSizeOL = new QSpinBox(frame_7);
        EditNGSizeOL->setObjectName("EditNGSizeOL");
        EditNGSizeOL->setGeometry(QRect(218, 50, 81, 22));
        EditNGSizeOL->setMaximum(99999999);
        EditBrightWidthOL = new QSpinBox(frame_7);
        EditBrightWidthOL->setObjectName("EditBrightWidthOL");
        EditBrightWidthOL->setGeometry(QRect(218, 30, 81, 22));
        EditBrightWidthOL->setMaximum(255);
        label_24 = new QLabel(frame_7);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(36, 50, 176, 21));
        label_24->setFrameShape(QFrame::Panel);
        label_24->setFrameShadow(QFrame::Sunken);
        label_24->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_23 = new QLabel(frame_7);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(218, 10, 81, 21));
        label_23->setFrameShape(QFrame::Panel);
        label_23->setFrameShadow(QFrame::Sunken);
        label_23->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBrightWidthOH = new QSpinBox(frame_7);
        EditBrightWidthOH->setObjectName("EditBrightWidthOH");
        EditBrightWidthOH->setGeometry(QRect(306, 30, 81, 22));
        EditBrightWidthOH->setMaximum(255);
        frame_11 = new QFrame(SelectLibraryDialog);
        frame_11->setObjectName("frame_11");
        frame_11->setGeometry(QRect(40, 540, 396, 111));
        frame_11->setFrameShape(QFrame::StyledPanel);
        frame_11->setFrameShadow(QFrame::Sunken);
        label_41 = new QLabel(frame_11);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(0, 0, 31, 111));
        label_41->setFrameShape(QFrame::Panel);
        label_41->setFrameShadow(QFrame::Raised);
        label_41->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_41->setIndent(1);
        EditAdjustBrightIL = new QSpinBox(frame_11);
        EditAdjustBrightIL->setObjectName("EditAdjustBrightIL");
        EditAdjustBrightIL->setGeometry(QRect(310, 10, 81, 22));
        EditAdjustBrightIL->setMaximum(255);
        EditAdjustBrightIH = new QSpinBox(frame_11);
        EditAdjustBrightIH->setObjectName("EditAdjustBrightIH");
        EditAdjustBrightIH->setGeometry(QRect(310, 30, 81, 22));
        EditAdjustBrightIH->setMaximum(255);
        label_26 = new QLabel(frame_11);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(40, 30, 266, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_25 = new QLabel(frame_11);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(40, 10, 266, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditAdjustBrightOH = new QSpinBox(frame_11);
        EditAdjustBrightOH->setObjectName("EditAdjustBrightOH");
        EditAdjustBrightOH->setGeometry(QRect(310, 80, 81, 22));
        EditAdjustBrightOH->setMaximum(255);
        label_29 = new QLabel(frame_11);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(40, 60, 266, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditAdjustBrightOL = new QSpinBox(frame_11);
        EditAdjustBrightOL->setObjectName("EditAdjustBrightOL");
        EditAdjustBrightOL->setGeometry(QRect(310, 60, 81, 22));
        EditAdjustBrightOL->setMaximum(255);
        label_34 = new QLabel(frame_11);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(40, 80, 266, 21));
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Sunken);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_13 = new QFrame(SelectLibraryDialog);
        frame_13->setObjectName("frame_13");
        frame_13->setGeometry(QRect(40, 660, 396, 61));
        frame_13->setFrameShape(QFrame::StyledPanel);
        frame_13->setFrameShadow(QFrame::Sunken);
        label_43 = new QLabel(frame_13);
        label_43->setObjectName("label_43");
        label_43->setGeometry(QRect(0, 0, 31, 61));
        label_43->setFrameShape(QFrame::Panel);
        label_43->setFrameShadow(QFrame::Raised);
        label_43->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_43->setIndent(1);
        frame_14 = new QFrame(frame_13);
        frame_14->setObjectName("frame_14");
        frame_14->setGeometry(QRect(10, 120, 371, 101));
        frame_14->setFrameShape(QFrame::StyledPanel);
        frame_14->setFrameShadow(QFrame::Sunken);
        label_44 = new QLabel(frame_14);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(0, 0, 20, 61));
        label_44->setFrameShape(QFrame::Panel);
        label_44->setFrameShadow(QFrame::Raised);
        label_44->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_44->setIndent(1);
        EditSearchDot = new QSpinBox(frame_13);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(310, 10, 81, 22));
        label_27 = new QLabel(frame_13);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(40, 10, 266, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_28 = new QLabel(frame_13);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(40, 30, 266, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditGlobalSearchDot = new QSpinBox(frame_13);
        EditGlobalSearchDot->setObjectName("EditGlobalSearchDot");
        EditGlobalSearchDot->setGeometry(QRect(310, 30, 81, 22));
        frame_12 = new QFrame(SelectLibraryDialog);
        frame_12->setObjectName("frame_12");
        frame_12->setGeometry(QRect(40, 730, 391, 61));
        frame_12->setFrameShape(QFrame::StyledPanel);
        frame_12->setFrameShadow(QFrame::Sunken);
        label_42 = new QLabel(frame_12);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(0, 0, 31, 61));
        label_42->setFrameShape(QFrame::Panel);
        label_42->setFrameShadow(QFrame::Raised);
        label_42->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_42->setIndent(1);
        checkBModeUseRegularBrightness = new QCheckBox(frame_12);
        checkBModeUseRegularBrightness->setObjectName("checkBModeUseRegularBrightness");
        checkBModeUseRegularBrightness->setGeometry(QRect(40, 4, 341, 18));
        label_33 = new QLabel(frame_12);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(40, 30, 81, 21));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Sunken);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditRegulatedColI = new QSpinBox(frame_12);
        EditRegulatedColI->setObjectName("EditRegulatedColI");
        EditRegulatedColI->setGeometry(QRect(122, 30, 81, 22));
        EditRegulatedColI->setMaximum(255);
        EditRegulatedColO = new QSpinBox(frame_12);
        EditRegulatedColO->setObjectName("EditRegulatedColO");
        EditRegulatedColO->setGeometry(QRect(302, 30, 81, 22));
        EditRegulatedColO->setMaximum(255);
        label_36 = new QLabel(frame_12);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(220, 30, 81, 21));
        label_36->setFrameShape(QFrame::Panel);
        label_36->setFrameShadow(QFrame::Sunken);
        label_36->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(SelectLibraryDialog);

        pushButtonSelect->setDefault(true);


        QMetaObject::connectSlotsByName(SelectLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectLibraryDialog)
    {
        SelectLibraryDialog->setWindowTitle(QCoreApplication::translate("SelectLibraryDialog", "Dialog", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectLibraryDialog", "Select", nullptr));
        label_4->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\220\215\347\247\260", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectLibraryDialog", "Cancel", nullptr));
        EditLibID->setText(QCoreApplication::translate("SelectLibraryDialog", "12345", nullptr));
        EditLibName->setText(QCoreApplication::translate("SelectLibraryDialog", "Library Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectLibraryDialog", "Name", nullptr));
        label_39->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\261\236\n"
"\346\200\247", nullptr));
        checkBModeAbsoluteBright->setText(QCoreApplication::translate("SelectLibraryDialog", "\347\265\266\345\257\276\350\274\235\345\272\246", nullptr));
        checkBModeCenterBrightFromParts->setText(QCoreApplication::translate("SelectLibraryDialog", "\351\203\250\345\223\201\343\201\213\343\202\211\350\274\235\345\272\246\343\202\222\346\212\275\345\207\272\343\201\231\343\202\213", nullptr));
        checkBModeEnabled->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\244\234\346\237\273\346\234\211\345\212\271", nullptr));
        checkBModeDynamicMask->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\256\237\350\241\214\343\203\236\343\202\271\343\202\257", nullptr));
        label_30->setText(QCoreApplication::translate("SelectLibraryDialog", "\350\274\252\351\203\255\351\203\250\345\210\206\343\201\256\347\247\273\350\241\214\345\271\205", nullptr));
        label_35->setText(QCoreApplication::translate("SelectLibraryDialog", "<html><head/><body><p>\345\206\205</p><p>\345\201\264</p></body></html>", nullptr));
        label_20->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\230\216\345\201\264", nullptr));
        label_17->setText(QCoreApplication::translate("SelectLibraryDialog", "OK\350\274\235\345\272\246\347\257\204\345\233\262", nullptr));
        label_18->setText(QCoreApplication::translate("SelectLibraryDialog", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_19->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\232\227\345\201\264", nullptr));
        label_37->setText(QCoreApplication::translate("SelectLibraryDialog", "<html><head/><body><p>\345\244\226</p><p>\345\201\264</p></body></html>", nullptr));
        label_22->setText(QCoreApplication::translate("SelectLibraryDialog", "OK\350\274\235\345\272\246\347\257\204\345\233\262", nullptr));
        label_21->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\230\216\345\201\264", nullptr));
        label_24->setText(QCoreApplication::translate("SelectLibraryDialog", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_23->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\232\227\345\201\264", nullptr));
        label_41->setText(QCoreApplication::translate("SelectLibraryDialog", "\350\243\234\n"
"\346\255\243", nullptr));
        label_26->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\206\205\345\201\264\343\200\200\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_25->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\206\205\345\201\264\343\200\200\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_29->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\244\226\345\201\264\343\200\200\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_34->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\244\226\345\201\264\343\200\200\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_43->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\216\242\n"
"\347\264\242", nullptr));
        label_44->setText(QCoreApplication::translate("SelectLibraryDialog", "\350\274\235\n"
"\345\272\246", nullptr));
        label_27->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\215\230\344\275\223\343\201\247\343\201\256\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_28->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\205\250\344\275\223\343\201\247\343\201\256\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_42->setText(QCoreApplication::translate("SelectLibraryDialog", "\350\274\235\n"
"\345\272\246", nullptr));
        checkBModeUseRegularBrightness->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\237\272\346\272\226\350\274\235\345\272\246\343\202\222\344\275\277\343\201\206", nullptr));
        label_33->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\206\205\345\201\264", nullptr));
        label_36->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\244\226\345\201\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibraryDialog: public Ui_SelectLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBRARYDIALOG_H
