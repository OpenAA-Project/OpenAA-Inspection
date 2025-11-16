/********************************************************************************
** Form generated from reading UI file 'Process3DHistgramForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESS3DHISTGRAMFORM_H
#define UI_PROCESS3DHISTGRAMFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Process3DHistgramForm
{
public:
    QFrame *frame_16;
    QLabel *label_62;
    QLabel *label_64;
    QLabel *label_67;
    QDoubleSpinBox *doubleSpinBoxSmallFlatness;
    QSpinBox *spinBoxSmallAreaSize;
    QFrame *frame_15;
    QLabel *label_58;
    QLabel *label_59;
    QLabel *label_63;
    QDoubleSpinBox *doubleSpinBoxLargeTilt;
    QDoubleSpinBox *doubleSpinBoxLargeFlatness;
    QFrame *frame_2;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_30;
    QDoubleSpinBox *doubleSpinBoxBaseCycleDot;
    QDoubleSpinBox *doubleSpinBoxHeightPerShift;
    QPushButton *ButtonSaveToLibrary;
    QPushButton *ButtonClose;
    QStackedWidget *stackedWidgetParts;
    QWidget *page;
    QWidget *page_3;
    QPushButton *ButtonRelrectSaveParts;
    QWidget *page_2;
    QPushButton *ButtonLoadFromLibrary;
    QPushButton *ButtonReflectAllBlocks;
    QFrame *frame;
    QLabel *label_31;
    QLabel *label;
    QLabel *label_2;
    QLabel *labelResultSmallFlatness;
    QLabel *labelResultLargeTile;
    QPushButton *ButtonCalc;
    QLabel *labelResultLargeTileUnit;
    QLabel *labelResultSmallFlatnessUnit;
    QLabel *labelUnitName_1;
    QLabel *labelUnitName_3;
    QLabel *labelResultLargeFlatnessUnit;
    QLabel *labelUnitName_2;
    QLabel *label_3;
    QLabel *labelResultLargeFlatness;
    QFrame *frame_SimImage;
    QPushButton *pushButtonChangeLib;
    QPushButton *pushButtonTransmitItemNameAll;
    QLineEdit *EditLibName;
    QLabel *label_5;
    QLineEdit *EditItemName;
    QLabel *label_9;
    QLabel *label_4;
    QLineEdit *EditLibID;
    QFrame *frameLayer;
    QPushButton *ButtonRelrectOnlyBlock;
    QToolButton *toolButtonSimShowBlock;
    QToolButton *toolButtonSimShowBright;

    void setupUi(QWidget *Process3DHistgramForm)
    {
        if (Process3DHistgramForm->objectName().isEmpty())
            Process3DHistgramForm->setObjectName("Process3DHistgramForm");
        Process3DHistgramForm->resize(1031, 711);
        frame_16 = new QFrame(Process3DHistgramForm);
        frame_16->setObjectName("frame_16");
        frame_16->setGeometry(QRect(400, 610, 361, 91));
        frame_16->setFrameShape(QFrame::StyledPanel);
        frame_16->setFrameShadow(QFrame::Sunken);
        label_62 = new QLabel(frame_16);
        label_62->setObjectName("label_62");
        label_62->setGeometry(QRect(40, 40, 191, 21));
        label_62->setFrameShape(QFrame::Panel);
        label_62->setFrameShadow(QFrame::Sunken);
        label_62->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_64 = new QLabel(frame_16);
        label_64->setObjectName("label_64");
        label_64->setGeometry(QRect(40, 10, 191, 21));
        label_64->setFrameShape(QFrame::Panel);
        label_64->setFrameShadow(QFrame::Sunken);
        label_64->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_67 = new QLabel(frame_16);
        label_67->setObjectName("label_67");
        label_67->setGeometry(QRect(0, 0, 31, 91));
        label_67->setFrameShape(QFrame::Panel);
        label_67->setFrameShadow(QFrame::Raised);
        label_67->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_67->setIndent(1);
        doubleSpinBoxSmallFlatness = new QDoubleSpinBox(frame_16);
        doubleSpinBoxSmallFlatness->setObjectName("doubleSpinBoxSmallFlatness");
        doubleSpinBoxSmallFlatness->setGeometry(QRect(240, 10, 111, 24));
        doubleSpinBoxSmallFlatness->setDecimals(3);
        doubleSpinBoxSmallFlatness->setMaximum(99999999.000000000000000);
        spinBoxSmallAreaSize = new QSpinBox(frame_16);
        spinBoxSmallAreaSize->setObjectName("spinBoxSmallAreaSize");
        spinBoxSmallAreaSize->setGeometry(QRect(240, 40, 111, 24));
        spinBoxSmallAreaSize->setMaximum(99999999);
        frame_15 = new QFrame(Process3DHistgramForm);
        frame_15->setObjectName("frame_15");
        frame_15->setGeometry(QRect(400, 530, 361, 71));
        frame_15->setFrameShape(QFrame::StyledPanel);
        frame_15->setFrameShadow(QFrame::Sunken);
        label_58 = new QLabel(frame_15);
        label_58->setObjectName("label_58");
        label_58->setGeometry(QRect(40, 40, 191, 21));
        label_58->setFrameShape(QFrame::Panel);
        label_58->setFrameShadow(QFrame::Sunken);
        label_58->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_59 = new QLabel(frame_15);
        label_59->setObjectName("label_59");
        label_59->setGeometry(QRect(40, 10, 191, 21));
        label_59->setFrameShape(QFrame::Panel);
        label_59->setFrameShadow(QFrame::Sunken);
        label_59->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_63 = new QLabel(frame_15);
        label_63->setObjectName("label_63");
        label_63->setGeometry(QRect(0, 0, 31, 71));
        label_63->setFrameShape(QFrame::Panel);
        label_63->setFrameShadow(QFrame::Raised);
        label_63->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_63->setIndent(1);
        doubleSpinBoxLargeTilt = new QDoubleSpinBox(frame_15);
        doubleSpinBoxLargeTilt->setObjectName("doubleSpinBoxLargeTilt");
        doubleSpinBoxLargeTilt->setGeometry(QRect(240, 10, 111, 24));
        doubleSpinBoxLargeTilt->setDecimals(3);
        doubleSpinBoxLargeTilt->setMaximum(99999999.000000000000000);
        doubleSpinBoxLargeFlatness = new QDoubleSpinBox(frame_15);
        doubleSpinBoxLargeFlatness->setObjectName("doubleSpinBoxLargeFlatness");
        doubleSpinBoxLargeFlatness->setGeometry(QRect(240, 40, 111, 24));
        doubleSpinBoxLargeFlatness->setDecimals(3);
        doubleSpinBoxLargeFlatness->setMaximum(99999999.000000000000000);
        frame_2 = new QFrame(Process3DHistgramForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(400, 450, 361, 71));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(40, 10, 191, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(40, 40, 191, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_30 = new QLabel(frame_2);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(0, 0, 31, 71));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Raised);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_30->setIndent(1);
        doubleSpinBoxBaseCycleDot = new QDoubleSpinBox(frame_2);
        doubleSpinBoxBaseCycleDot->setObjectName("doubleSpinBoxBaseCycleDot");
        doubleSpinBoxBaseCycleDot->setGeometry(QRect(240, 10, 111, 24));
        doubleSpinBoxBaseCycleDot->setDecimals(3);
        doubleSpinBoxBaseCycleDot->setMaximum(99999999.000000000000000);
        doubleSpinBoxHeightPerShift = new QDoubleSpinBox(frame_2);
        doubleSpinBoxHeightPerShift->setObjectName("doubleSpinBoxHeightPerShift");
        doubleSpinBoxHeightPerShift->setGeometry(QRect(240, 40, 111, 24));
        doubleSpinBoxHeightPerShift->setDecimals(3);
        doubleSpinBoxHeightPerShift->setMaximum(99999999.000000000000000);
        ButtonSaveToLibrary = new QPushButton(Process3DHistgramForm);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(10, 620, 171, 41));
        ButtonSaveToLibrary->setAcceptDrops(true);
        ButtonClose = new QPushButton(Process3DHistgramForm);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(190, 660, 201, 41));
        stackedWidgetParts = new QStackedWidget(Process3DHistgramForm);
        stackedWidgetParts->setObjectName("stackedWidgetParts");
        stackedWidgetParts->setGeometry(QRect(10, 580, 181, 41));
        page = new QWidget();
        page->setObjectName("page");
        stackedWidgetParts->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        ButtonRelrectSaveParts = new QPushButton(page_3);
        ButtonRelrectSaveParts->setObjectName("ButtonRelrectSaveParts");
        ButtonRelrectSaveParts->setGeometry(QRect(0, 0, 171, 41));
        stackedWidgetParts->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidgetParts->addWidget(page_2);
        ButtonLoadFromLibrary = new QPushButton(Process3DHistgramForm);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(190, 620, 201, 41));
        ButtonLoadFromLibrary->setAcceptDrops(true);
        ButtonReflectAllBlocks = new QPushButton(Process3DHistgramForm);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(190, 580, 201, 41));
        ButtonReflectAllBlocks->setAcceptDrops(true);
        frame = new QFrame(Process3DHistgramForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(770, 460, 241, 221));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_31 = new QLabel(frame);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(0, 0, 241, 21));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 131, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 130, 131, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelResultSmallFlatness = new QLabel(frame);
        labelResultSmallFlatness->setObjectName("labelResultSmallFlatness");
        labelResultSmallFlatness->setGeometry(QRect(150, 130, 81, 21));
        labelResultSmallFlatness->setFrameShape(QFrame::Panel);
        labelResultSmallFlatness->setFrameShadow(QFrame::Sunken);
        labelResultSmallFlatness->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelResultLargeTile = new QLabel(frame);
        labelResultLargeTile->setObjectName("labelResultLargeTile");
        labelResultLargeTile->setGeometry(QRect(150, 30, 81, 21));
        labelResultLargeTile->setFrameShape(QFrame::Panel);
        labelResultLargeTile->setFrameShadow(QFrame::Sunken);
        labelResultLargeTile->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonCalc = new QPushButton(frame);
        ButtonCalc->setObjectName("ButtonCalc");
        ButtonCalc->setGeometry(QRect(40, 180, 161, 31));
        ButtonCalc->setAcceptDrops(true);
        labelResultLargeTileUnit = new QLabel(frame);
        labelResultLargeTileUnit->setObjectName("labelResultLargeTileUnit");
        labelResultLargeTileUnit->setGeometry(QRect(150, 50, 81, 21));
        QPalette palette;
        QBrush brush(QColor(255, 255, 127, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(255, 170, 0, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        labelResultLargeTileUnit->setPalette(palette);
        labelResultLargeTileUnit->setAutoFillBackground(true);
        labelResultLargeTileUnit->setFrameShape(QFrame::Panel);
        labelResultLargeTileUnit->setFrameShadow(QFrame::Sunken);
        labelResultLargeTileUnit->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelResultSmallFlatnessUnit = new QLabel(frame);
        labelResultSmallFlatnessUnit->setObjectName("labelResultSmallFlatnessUnit");
        labelResultSmallFlatnessUnit->setGeometry(QRect(150, 150, 81, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        labelResultSmallFlatnessUnit->setPalette(palette1);
        labelResultSmallFlatnessUnit->setAutoFillBackground(true);
        labelResultSmallFlatnessUnit->setFrameShape(QFrame::Panel);
        labelResultSmallFlatnessUnit->setFrameShadow(QFrame::Sunken);
        labelResultSmallFlatnessUnit->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelUnitName_1 = new QLabel(frame);
        labelUnitName_1->setObjectName("labelUnitName_1");
        labelUnitName_1->setGeometry(QRect(10, 50, 131, 20));
        labelUnitName_1->setFrameShape(QFrame::NoFrame);
        labelUnitName_1->setFrameShadow(QFrame::Sunken);
        labelUnitName_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelUnitName_3 = new QLabel(frame);
        labelUnitName_3->setObjectName("labelUnitName_3");
        labelUnitName_3->setGeometry(QRect(10, 150, 131, 20));
        labelUnitName_3->setFrameShape(QFrame::NoFrame);
        labelUnitName_3->setFrameShadow(QFrame::Sunken);
        labelUnitName_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelResultLargeFlatnessUnit = new QLabel(frame);
        labelResultLargeFlatnessUnit->setObjectName("labelResultLargeFlatnessUnit");
        labelResultLargeFlatnessUnit->setGeometry(QRect(150, 100, 81, 21));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        labelResultLargeFlatnessUnit->setPalette(palette2);
        labelResultLargeFlatnessUnit->setAutoFillBackground(true);
        labelResultLargeFlatnessUnit->setFrameShape(QFrame::Panel);
        labelResultLargeFlatnessUnit->setFrameShadow(QFrame::Sunken);
        labelResultLargeFlatnessUnit->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelUnitName_2 = new QLabel(frame);
        labelUnitName_2->setObjectName("labelUnitName_2");
        labelUnitName_2->setGeometry(QRect(10, 100, 131, 20));
        labelUnitName_2->setFrameShape(QFrame::NoFrame);
        labelUnitName_2->setFrameShadow(QFrame::Sunken);
        labelUnitName_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 80, 131, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelResultLargeFlatness = new QLabel(frame);
        labelResultLargeFlatness->setObjectName("labelResultLargeFlatness");
        labelResultLargeFlatness->setGeometry(QRect(150, 80, 81, 21));
        labelResultLargeFlatness->setFrameShape(QFrame::Panel);
        labelResultLargeFlatness->setFrameShadow(QFrame::Sunken);
        labelResultLargeFlatness->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_SimImage = new QFrame(Process3DHistgramForm);
        frame_SimImage->setObjectName("frame_SimImage");
        frame_SimImage->setGeometry(QRect(160, 10, 861, 431));
        frame_SimImage->setFrameShape(QFrame::StyledPanel);
        frame_SimImage->setFrameShadow(QFrame::Raised);
        pushButtonChangeLib = new QPushButton(Process3DHistgramForm);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(220, 540, 31, 23));
        pushButtonTransmitItemNameAll = new QPushButton(Process3DHistgramForm);
        pushButtonTransmitItemNameAll->setObjectName("pushButtonTransmitItemNameAll");
        pushButtonTransmitItemNameAll->setGeometry(QRect(340, 490, 51, 23));
        EditLibName = new QLineEdit(Process3DHistgramForm);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(70, 540, 151, 21));
        EditLibName->setReadOnly(true);
        label_5 = new QLabel(Process3DHistgramForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(70, 520, 151, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditItemName = new QLineEdit(Process3DHistgramForm);
        EditItemName->setObjectName("EditItemName");
        EditItemName->setGeometry(QRect(150, 490, 191, 21));
        EditItemName->setReadOnly(false);
        label_9 = new QLabel(Process3DHistgramForm);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 490, 141, 20));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(Process3DHistgramForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 520, 62, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(Process3DHistgramForm);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(10, 540, 61, 21));
        EditLibID->setReadOnly(true);
        frameLayer = new QFrame(Process3DHistgramForm);
        frameLayer->setObjectName("frameLayer");
        frameLayer->setGeometry(QRect(20, 450, 171, 41));
        frameLayer->setFrameShape(QFrame::NoFrame);
        frameLayer->setFrameShadow(QFrame::Plain);
        ButtonRelrectOnlyBlock = new QPushButton(Process3DHistgramForm);
        ButtonRelrectOnlyBlock->setObjectName("ButtonRelrectOnlyBlock");
        ButtonRelrectOnlyBlock->setGeometry(QRect(10, 580, 171, 41));
        ButtonRelrectOnlyBlock->setAcceptDrops(true);
        toolButtonSimShowBlock = new QToolButton(Process3DHistgramForm);
        toolButtonSimShowBlock->setObjectName("toolButtonSimShowBlock");
        toolButtonSimShowBlock->setGeometry(QRect(10, 10, 141, 41));
        toolButtonSimShowBlock->setCheckable(true);
        toolButtonSimShowBlock->setChecked(true);
        toolButtonSimShowBright = new QToolButton(Process3DHistgramForm);
        toolButtonSimShowBright->setObjectName("toolButtonSimShowBright");
        toolButtonSimShowBright->setGeometry(QRect(10, 60, 141, 41));
        toolButtonSimShowBright->setCheckable(true);
        toolButtonSimShowBright->setChecked(true);

        retranslateUi(Process3DHistgramForm);

        stackedWidgetParts->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Process3DHistgramForm);
    } // setupUi

    void retranslateUi(QWidget *Process3DHistgramForm)
    {
        Process3DHistgramForm->setWindowTitle(QCoreApplication::translate("Process3DHistgramForm", "Form", nullptr));
        label_62->setText(QCoreApplication::translate("Process3DHistgramForm", "Regular size", nullptr));
        label_64->setText(QCoreApplication::translate("Process3DHistgramForm", "Flatness", nullptr));
        label_67->setText(QCoreApplication::translate("Process3DHistgramForm", "<html><head/><body><p>\345\260\217</p><p>\351\240\230</p><p>\345\237\237</p></body></html>", nullptr));
        label_58->setText(QCoreApplication::translate("Process3DHistgramForm", "Flatness", nullptr));
        label_59->setText(QCoreApplication::translate("Process3DHistgramForm", "Tilt from horizon", nullptr));
        label_63->setText(QCoreApplication::translate("Process3DHistgramForm", "<html><head/><body><p>\345\272\203</p><p>\345\237\237</p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("Process3DHistgramForm", "Base cycle dot", nullptr));
        label_8->setText(QCoreApplication::translate("Process3DHistgramForm", "Height per shift", nullptr));
        label_30->setText(QCoreApplication::translate("Process3DHistgramForm", "<html><head/><body><p>\350\250\255</p><p>\345\256\232</p></body></html>", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("Process3DHistgramForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        ButtonClose->setText(QCoreApplication::translate("Process3DHistgramForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonRelrectSaveParts->setText(QCoreApplication::translate("Process3DHistgramForm", "\351\203\250\345\223\201\344\277\235\345\255\230", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("Process3DHistgramForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("Process3DHistgramForm", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\351\240\230\345\237\237\343\201\253\345\217\215\346\230\240", nullptr));
        label_31->setText(QCoreApplication::translate("Process3DHistgramForm", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\345\210\244\345\256\232\347\265\220\346\236\234", nullptr));
        label->setText(QCoreApplication::translate("Process3DHistgramForm", "\345\272\203\345\237\237\357\274\215Tilt", nullptr));
        label_2->setText(QCoreApplication::translate("Process3DHistgramForm", "\345\260\217\351\240\230\345\237\237", nullptr));
        labelResultSmallFlatness->setText(QCoreApplication::translate("Process3DHistgramForm", "123", nullptr));
        labelResultLargeTile->setText(QCoreApplication::translate("Process3DHistgramForm", "123", nullptr));
        ButtonCalc->setText(QCoreApplication::translate("Process3DHistgramForm", "\350\250\210\347\256\227", nullptr));
        labelResultLargeTileUnit->setText(QCoreApplication::translate("Process3DHistgramForm", "123", nullptr));
        labelResultSmallFlatnessUnit->setText(QCoreApplication::translate("Process3DHistgramForm", "123", nullptr));
        labelUnitName_1->setText(QCoreApplication::translate("Process3DHistgramForm", "mm", nullptr));
        labelUnitName_3->setText(QCoreApplication::translate("Process3DHistgramForm", "mm", nullptr));
        labelResultLargeFlatnessUnit->setText(QCoreApplication::translate("Process3DHistgramForm", "123", nullptr));
        labelUnitName_2->setText(QCoreApplication::translate("Process3DHistgramForm", "mm", nullptr));
        label_3->setText(QCoreApplication::translate("Process3DHistgramForm", "\345\272\203\345\237\237\357\274\215Flatness", nullptr));
        labelResultLargeFlatness->setText(QCoreApplication::translate("Process3DHistgramForm", "123", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("Process3DHistgramForm", "...", nullptr));
        pushButtonTransmitItemNameAll->setText(QCoreApplication::translate("Process3DHistgramForm", "To all", nullptr));
        EditLibName->setText(QCoreApplication::translate("Process3DHistgramForm", "XXX", nullptr));
        label_5->setText(QCoreApplication::translate("Process3DHistgramForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        EditItemName->setText(QCoreApplication::translate("Process3DHistgramForm", "XXX", nullptr));
        label_9->setText(QCoreApplication::translate("Process3DHistgramForm", "Item name", nullptr));
        label_4->setText(QCoreApplication::translate("Process3DHistgramForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        EditLibID->setText(QCoreApplication::translate("Process3DHistgramForm", "12345", nullptr));
        ButtonRelrectOnlyBlock->setText(QCoreApplication::translate("Process3DHistgramForm", "\343\201\223\343\201\256\351\240\230\345\237\237\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        toolButtonSimShowBlock->setText(QCoreApplication::translate("Process3DHistgramForm", "Block", nullptr));
        toolButtonSimShowBright->setText(QCoreApplication::translate("Process3DHistgramForm", "\350\274\235\345\272\246NG", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Process3DHistgramForm: public Ui_Process3DHistgramForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESS3DHISTGRAMFORM_H
