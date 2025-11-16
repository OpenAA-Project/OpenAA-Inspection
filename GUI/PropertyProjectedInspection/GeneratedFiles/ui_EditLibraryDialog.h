/********************************************************************************
** Form generated from reading UI file 'EditLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLIBRARYDIALOG_H
#define UI_EDITLIBRARYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditLibraryDialog
{
public:
    QLabel *label_4;
    QPushButton *ButtonLibSave;
    QLineEdit *EditLibName;
    QFrame *frame_2;
    QLabel *label_30;
    QDoubleSpinBox *doubleSpinBoxAngle;
    QLabel *label_33;
    QSpinBox *EditTransitWidth;
    QLabel *label_38;
    QCheckBox *checkBoxExcludeDynamicMask;
    QLabel *label_35;
    QLabel *label_39;
    QCheckBox *checkBoxCircleMode;
    QCheckBox *checkBoxUseAbsolute;
    QLabel *label_37;
    QSpinBox *EditEvenLength;
    QLabel *label_40;
    QDoubleSpinBox *doubleSpinBoxPartialSwingAngle;
    QDoubleSpinBox *EditOKWidthDiffereceH;
    QDoubleSpinBox *EditOKWidthDiffereceL;
    QPushButton *pushButton;
    QPushButton *ButtonLibDelete;
    QPushButton *ButtonLibSaveNew;
    QFrame *framePickLayer;
    QTableWidget *tableWidgetLibList;
    QLabel *label_8;
    QFrame *frameGenLayer;
    QLineEdit *EditLibID;
    QPushButton *ButtonLibNew;
    QFrame *frameLibFolder;
    QLabel *label_9;
    QFrame *frame;
    QFrame *frame_4;
    QSpinBox *EditMinBlockSize;
    QLabel *label_11;
    QSpinBox *EditMaxBlockSize;
    QLabel *label_12;
    QSpinBox *EditMinBlockDots;
    QLabel *label_13;
    QSpinBox *EditMaxBlockDots;
    QLabel *label_14;
    QLabel *label_15;
    QSpinBox *EditLimitBlockSize;
    QLabel *label_32;
    QFrame *frame_3;
    QLabel *label_7;
    QSpinBox *EditPickupL;
    QLabel *label_10;
    QSpinBox *EditPickupH;
    QLabel *label_31;
    QLabel *label_34;
    QFrame *frame_5;
    QSpinBox *EditNoiseSize;
    QLabel *label_17;
    QSpinBox *EditPriority;
    QLabel *label_36;
    QLabel *label_48;
    QLabel *label_49;
    QSpinBox *EditNoiseSizePinHole;

    void setupUi(QDialog *EditLibraryDialog)
    {
        if (EditLibraryDialog->objectName().isEmpty())
            EditLibraryDialog->setObjectName("EditLibraryDialog");
        EditLibraryDialog->resize(723, 848);
        label_4 = new QLabel(EditLibraryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(280, 10, 51, 31));
        QFont font;
        font.setPointSize(12);
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibSave = new QPushButton(EditLibraryDialog);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(600, 770, 101, 31));
        QFont font1;
        font1.setPointSize(11);
        ButtonLibSave->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon);
        EditLibName = new QLineEdit(EditLibraryDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(410, 10, 251, 31));
        EditLibName->setFont(font);
        frame_2 = new QFrame(EditLibraryDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(280, 460, 431, 301));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_30 = new QLabel(frame_2);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 40, 271, 21));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxAngle = new QDoubleSpinBox(frame_2);
        doubleSpinBoxAngle->setObjectName("doubleSpinBoxAngle");
        doubleSpinBoxAngle->setGeometry(QRect(291, 40, 81, 22));
        doubleSpinBoxAngle->setDecimals(4);
        doubleSpinBoxAngle->setMinimum(-99.989999999999995);
        label_33 = new QLabel(frame_2);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(10, 70, 271, 21));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Sunken);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditTransitWidth = new QSpinBox(frame_2);
        EditTransitWidth->setObjectName("EditTransitWidth");
        EditTransitWidth->setGeometry(QRect(290, 70, 81, 22));
        EditTransitWidth->setMaximum(255);
        label_38 = new QLabel(frame_2);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(10, 160, 271, 21));
        label_38->setFrameShape(QFrame::Panel);
        label_38->setFrameShadow(QFrame::Sunken);
        label_38->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxExcludeDynamicMask = new QCheckBox(frame_2);
        checkBoxExcludeDynamicMask->setObjectName("checkBoxExcludeDynamicMask");
        checkBoxExcludeDynamicMask->setGeometry(QRect(20, 100, 341, 21));
        label_35 = new QLabel(frame_2);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(0, 0, 381, 21));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Sunken);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_39 = new QLabel(frame_2);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(10, 180, 271, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxCircleMode = new QCheckBox(frame_2);
        checkBoxCircleMode->setObjectName("checkBoxCircleMode");
        checkBoxCircleMode->setGeometry(QRect(20, 210, 341, 21));
        checkBoxUseAbsolute = new QCheckBox(frame_2);
        checkBoxUseAbsolute->setObjectName("checkBoxUseAbsolute");
        checkBoxUseAbsolute->setGeometry(QRect(20, 130, 271, 22));
        label_37 = new QLabel(frame_2);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(10, 240, 271, 21));
        label_37->setFrameShape(QFrame::Panel);
        label_37->setFrameShadow(QFrame::Sunken);
        label_37->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditEvenLength = new QSpinBox(frame_2);
        EditEvenLength->setObjectName("EditEvenLength");
        EditEvenLength->setGeometry(QRect(290, 240, 101, 22));
        EditEvenLength->setMaximum(200000000);
        label_40 = new QLabel(frame_2);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(10, 270, 271, 21));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setFrameShadow(QFrame::Sunken);
        label_40->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxPartialSwingAngle = new QDoubleSpinBox(frame_2);
        doubleSpinBoxPartialSwingAngle->setObjectName("doubleSpinBoxPartialSwingAngle");
        doubleSpinBoxPartialSwingAngle->setGeometry(QRect(290, 270, 62, 22));
        doubleSpinBoxPartialSwingAngle->setMaximum(360.000000000000000);
        EditOKWidthDiffereceH = new QDoubleSpinBox(frame_2);
        EditOKWidthDiffereceH->setObjectName("EditOKWidthDiffereceH");
        EditOKWidthDiffereceH->setGeometry(QRect(289, 180, 71, 22));
        EditOKWidthDiffereceH->setMaximum(360.000000000000000);
        EditOKWidthDiffereceL = new QDoubleSpinBox(frame_2);
        EditOKWidthDiffereceL->setObjectName("EditOKWidthDiffereceL");
        EditOKWidthDiffereceL->setGeometry(QRect(290, 160, 71, 22));
        EditOKWidthDiffereceL->setMaximum(360.000000000000000);
        pushButton = new QPushButton(EditLibraryDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(600, 810, 101, 31));
        pushButton->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon1);
        ButtonLibDelete = new QPushButton(EditLibraryDialog);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(340, 770, 111, 31));
        ButtonLibDelete->setFont(font1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon2);
        ButtonLibSaveNew = new QPushButton(EditLibraryDialog);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(460, 770, 131, 31));
        ButtonLibSaveNew->setFont(font1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon3);
        framePickLayer = new QFrame(EditLibraryDialog);
        framePickLayer->setObjectName("framePickLayer");
        framePickLayer->setGeometry(QRect(280, 70, 381, 28));
        framePickLayer->setFrameShape(QFrame::NoFrame);
        framePickLayer->setFrameShadow(QFrame::Plain);
        tableWidgetLibList = new QTableWidget(EditLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 220, 251, 341));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_8 = new QLabel(EditLibraryDialog);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(280, 50, 381, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setTextFormat(Qt::AutoText);
        label_8->setAlignment(Qt::AlignCenter);
        frameGenLayer = new QFrame(EditLibraryDialog);
        frameGenLayer->setObjectName("frameGenLayer");
        frameGenLayer->setGeometry(QRect(280, 120, 381, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);
        EditLibID = new QLineEdit(EditLibraryDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(330, 10, 81, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        ButtonLibNew = new QPushButton(EditLibraryDialog);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(200, 770, 131, 31));
        ButtonLibNew->setFont(font1);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon4);
        frameLibFolder = new QFrame(EditLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 251, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        label_9 = new QLabel(EditLibraryDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(280, 100, 381, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignCenter);
        frame = new QFrame(EditLibraryDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(280, 140, 431, 311));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        frame_4 = new QFrame(frame);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 100, 331, 121));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Sunken);
        EditMinBlockSize = new QSpinBox(frame_4);
        EditMinBlockSize->setObjectName("EditMinBlockSize");
        EditMinBlockSize->setGeometry(QRect(220, 4, 81, 22));
        EditMinBlockSize->setMaximum(1000000);
        label_11 = new QLabel(frame_4);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(42, 26, 168, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxBlockSize = new QSpinBox(frame_4);
        EditMaxBlockSize->setObjectName("EditMaxBlockSize");
        EditMaxBlockSize->setGeometry(QRect(220, 26, 81, 22));
        EditMaxBlockSize->setMaximum(1000000);
        label_12 = new QLabel(frame_4);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(42, 4, 168, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinBlockDots = new QSpinBox(frame_4);
        EditMinBlockDots->setObjectName("EditMinBlockDots");
        EditMinBlockDots->setGeometry(QRect(220, 50, 101, 22));
        EditMinBlockDots->setMaximum(2000000000);
        label_13 = new QLabel(frame_4);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(42, 50, 168, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxBlockDots = new QSpinBox(frame_4);
        EditMaxBlockDots->setObjectName("EditMaxBlockDots");
        EditMaxBlockDots->setGeometry(QRect(220, 70, 101, 22));
        EditMaxBlockDots->setMinimum(-1);
        EditMaxBlockDots->setMaximum(2000000000);
        EditMaxBlockDots->setValue(2000000000);
        label_14 = new QLabel(frame_4);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(42, 70, 168, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_15 = new QLabel(frame_4);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(42, 96, 168, 21));
        label_15->setFrameShape(QFrame::Panel);
        label_15->setFrameShadow(QFrame::Sunken);
        label_15->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLimitBlockSize = new QSpinBox(frame_4);
        EditLimitBlockSize->setObjectName("EditLimitBlockSize");
        EditLimitBlockSize->setGeometry(QRect(220, 96, 61, 22));
        EditLimitBlockSize->setMaximum(99999);
        label_32 = new QLabel(frame_4);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(0, 0, 31, 121));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Raised);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_32->setIndent(1);
        frame_3 = new QFrame(frame);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 40, 331, 51));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frame_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(42, 4, 168, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupL = new QSpinBox(frame_3);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(220, 4, 61, 22));
        EditPickupL->setMaximum(255);
        label_10 = new QLabel(frame_3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(42, 26, 168, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupH = new QSpinBox(frame_3);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(220, 26, 61, 22));
        EditPickupH->setMaximum(255);
        label_31 = new QLabel(frame_3);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(0, 0, 31, 51));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Raised);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_31->setIndent(1);
        label_34 = new QLabel(frame);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(0, 0, 381, 21));
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Sunken);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_5 = new QFrame(EditLibraryDialog);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(290, 370, 411, 81));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Sunken);
        EditNoiseSize = new QSpinBox(frame_5);
        EditNoiseSize->setObjectName("EditNoiseSize");
        EditNoiseSize->setGeometry(QRect(310, 10, 84, 21));
        QFont font2;
        font2.setPointSize(9);
        EditNoiseSize->setFont(font2);
        label_17 = new QLabel(frame_5);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(40, 50, 261, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPriority = new QSpinBox(frame_5);
        EditPriority->setObjectName("EditPriority");
        EditPriority->setGeometry(QRect(310, 50, 84, 21));
        EditPriority->setFont(font2);
        label_36 = new QLabel(frame_5);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(0, 0, 31, 81));
        label_36->setFrameShape(QFrame::Panel);
        label_36->setFrameShadow(QFrame::Raised);
        label_36->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_36->setIndent(1);
        label_48 = new QLabel(frame_5);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(40, 30, 261, 21));
        label_48->setFrameShape(QFrame::Panel);
        label_48->setFrameShadow(QFrame::Sunken);
        label_48->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_49 = new QLabel(frame_5);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(40, 10, 261, 21));
        label_49->setFrameShape(QFrame::Panel);
        label_49->setFrameShadow(QFrame::Sunken);
        label_49->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNoiseSizePinHole = new QSpinBox(frame_5);
        EditNoiseSizePinHole->setObjectName("EditNoiseSizePinHole");
        EditNoiseSizePinHole->setGeometry(QRect(310, 30, 84, 21));
        EditNoiseSizePinHole->setFont(font2);

        retranslateUi(EditLibraryDialog);

        QMetaObject::connectSlotsByName(EditLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *EditLibraryDialog)
    {
        EditLibraryDialog->setWindowTitle(QCoreApplication::translate("EditLibraryDialog", "Edit Library", nullptr));
        label_4->setText(QCoreApplication::translate("EditLibraryDialog", "\345\220\215\347\247\260", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditLibraryDialog", "Update", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditLibraryDialog", "Library Name", nullptr));
        label_30->setText(QCoreApplication::translate("EditLibraryDialog", "Angle (0-180)", nullptr));
        label_33->setText(QCoreApplication::translate("EditLibraryDialog", "Transit wdth", nullptr));
        label_38->setText(QCoreApplication::translate("EditLibraryDialog", "Brightness difference Dark", nullptr));
        checkBoxExcludeDynamicMask->setText(QCoreApplication::translate("EditLibraryDialog", "Exclude dynamic mask", nullptr));
        label_35->setText(QCoreApplication::translate("EditLibraryDialog", "\346\244\234\346\237\273\343\203\221\343\203\251\343\203\241\343\203\274\343\202\277", nullptr));
        label_39->setText(QCoreApplication::translate("EditLibraryDialog", "Brightness difference Light", nullptr));
        checkBoxCircleMode->setText(QCoreApplication::translate("EditLibraryDialog", "Circle", nullptr));
        checkBoxUseAbsolute->setText(QCoreApplication::translate("EditLibraryDialog", "Absolute brightness", nullptr));
        label_37->setText(QCoreApplication::translate("EditLibraryDialog", "Even Length", nullptr));
        label_40->setText(QCoreApplication::translate("EditLibraryDialog", "Swing angle range", nullptr));
        pushButton->setText(QCoreApplication::translate("EditLibraryDialog", "Close", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditLibraryDialog", "Delete", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditLibraryDialog", "Save New", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditLibraryDialog", "Name", nullptr));
        label_8->setText(QCoreApplication::translate("EditLibraryDialog", "\346\212\275\345\207\272\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditLibraryDialog", "12345", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditLibraryDialog", "Clear new", nullptr));
        label_9->setText(QCoreApplication::translate("EditLibraryDialog", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        label_11->setText(QCoreApplication::translate("EditLibraryDialog", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_12->setText(QCoreApplication::translate("EditLibraryDialog", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_13->setText(QCoreApplication::translate("EditLibraryDialog", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_14->setText(QCoreApplication::translate("EditLibraryDialog", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_15->setText(QCoreApplication::translate("EditLibraryDialog", "\351\231\220\347\225\214\343\202\265\343\202\244\343\202\272", nullptr));
        label_32->setText(QCoreApplication::translate("EditLibraryDialog", "\343\202\265\n"
"\343\202\244\n"
"\343\202\272", nullptr));
        label_7->setText(QCoreApplication::translate("EditLibraryDialog", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
        label_10->setText(QCoreApplication::translate("EditLibraryDialog", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
        label_31->setText(QCoreApplication::translate("EditLibraryDialog", "\350\274\235\n"
"\345\272\246", nullptr));
        label_34->setText(QCoreApplication::translate("EditLibraryDialog", "\347\224\237\346\210\220\343\203\221\343\203\251\343\203\241\343\203\274\343\202\277", nullptr));
        label_17->setText(QCoreApplication::translate("EditLibraryDialog", "\345\204\252\345\205\210\345\272\246", nullptr));
        label_36->setText(QCoreApplication::translate("EditLibraryDialog", "\347\224\237\n"
"\346\210\220", nullptr));
        label_48->setText(QCoreApplication::translate("EditLibraryDialog", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272\343\200\200\343\203\224\343\203\263\343\203\233\343\203\274\343\203\253\345\211\212\351\231\244", nullptr));
        label_49->setText(QCoreApplication::translate("EditLibraryDialog", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272 \345\255\244\347\253\213\347\202\271\345\211\212\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLibraryDialog: public Ui_EditLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLIBRARYDIALOG_H
