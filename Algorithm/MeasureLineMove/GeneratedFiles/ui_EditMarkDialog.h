/********************************************************************************
** Form generated from reading UI file 'EditMarkDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITMARKDIALOG_H
#define UI_EDITMARKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditMarkDialog
{
public:
    QPushButton *ButtonLoadFromLibrary;
    QLabel *label_6;
    QPushButton *ButtonSaveToLibrary;
    QPushButton *ButtonRelrectOnlyBlock;
    QListWidget *listWidgetHistList;
    QFrame *frame;
    QLabel *label_92;
    QSpinBox *EditSearchDot;
    QLineEdit *EditName;
    QLabel *label_4;
    QLabel *label_94;
    QLabel *label_93;
    QDoubleSpinBox *doubleSpinBoxThresholdM;
    QDoubleSpinBox *doubleSpinBoxThresholdP;
    QDoubleSpinBox *doubleSpinBoxThresholdPLib;
    QDoubleSpinBox *doubleSpinBoxThresholdMLib;
    QSpinBox *EditSearchDotLib;
    QCheckBox *checkBoxEnable;
    QLabel *label_8;
    QLineEdit *EditItemID;
    QDoubleSpinBox *doubleSpinBoxSearchDot;
    QLabel *labelUnitName_4;
    QLabel *label_98;
    QDoubleSpinBox *doubleSpinBoxThresholdM_2;
    QDoubleSpinBox *doubleSpinBoxThresholdP_2;
    QLabel *labelUnitName_5;
    QLabel *labelUnitName_6;
    QLabel *label_99;
    QLabel *label_100;
    QComboBox *comboBoxUsedLayer;
    QPushButton *pushButtonChangeItemID;
    QPushButton *pushButtonChangeLib;
    QLabel *label_7;
    QPushButton *ButtonReflectAllBlocks;
    QLineEdit *EditLibID;
    QLabel *label_40;
    QFrame *frame_2;
    QPushButton *pushButtonTest;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *labelPosDiffX;
    QLabel *labelPosDiffY;
    QLabel *labelPosDiffYUnit;
    QLabel *labelPosDiffXUnit;
    QLabel *labelUnitName_7;
    QLabel *labelUnitName_8;
    QLineEdit *Edit_LibName;
    QPushButton *ButtonClose;

    void setupUi(QWidget *EditMarkDialog)
    {
        if (EditMarkDialog->objectName().isEmpty())
            EditMarkDialog->setObjectName("EditMarkDialog");
        EditMarkDialog->resize(670, 480);
        ButtonLoadFromLibrary = new QPushButton(EditMarkDialog);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(180, 410, 161, 41));
        label_6 = new QLabel(EditMarkDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 0, 62, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonSaveToLibrary = new QPushButton(EditMarkDialog);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(10, 410, 161, 41));
        ButtonRelrectOnlyBlock = new QPushButton(EditMarkDialog);
        ButtonRelrectOnlyBlock->setObjectName("ButtonRelrectOnlyBlock");
        ButtonRelrectOnlyBlock->setGeometry(QRect(10, 360, 161, 41));
        listWidgetHistList = new QListWidget(EditMarkDialog);
        listWidgetHistList->setObjectName("listWidgetHistList");
        listWidgetHistList->setGeometry(QRect(450, 230, 201, 71));
        frame = new QFrame(EditMarkDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 50, 411, 291));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_92 = new QLabel(frame);
        label_92->setObjectName("label_92");
        label_92->setGeometry(QRect(10, 130, 211, 21));
        label_92->setFrameShape(QFrame::Panel);
        label_92->setFrameShadow(QFrame::Sunken);
        label_92->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSearchDot = new QSpinBox(frame);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(230, 130, 91, 22));
        EditSearchDot->setReadOnly(false);
        EditSearchDot->setMaximum(10000);
        EditName = new QLineEdit(frame);
        EditName->setObjectName("EditName");
        EditName->setGeometry(QRect(180, 10, 211, 31));
        QFont font;
        font.setPointSize(12);
        EditName->setFont(font);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(100, 10, 81, 31));
        QFont font1;
        font1.setPointSize(9);
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_94 = new QLabel(frame);
        label_94->setObjectName("label_94");
        label_94->setGeometry(QRect(10, 230, 211, 21));
        label_94->setFrameShape(QFrame::Panel);
        label_94->setFrameShadow(QFrame::Sunken);
        label_94->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_93 = new QLabel(frame);
        label_93->setObjectName("label_93");
        label_93->setGeometry(QRect(10, 180, 211, 21));
        label_93->setFrameShape(QFrame::Panel);
        label_93->setFrameShadow(QFrame::Sunken);
        label_93->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxThresholdM = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdM->setObjectName("doubleSpinBoxThresholdM");
        doubleSpinBoxThresholdM->setGeometry(QRect(230, 180, 91, 22));
        doubleSpinBoxThresholdP = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdP->setObjectName("doubleSpinBoxThresholdP");
        doubleSpinBoxThresholdP->setGeometry(QRect(230, 230, 91, 22));
        doubleSpinBoxThresholdPLib = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdPLib->setObjectName("doubleSpinBoxThresholdPLib");
        doubleSpinBoxThresholdPLib->setGeometry(QRect(320, 230, 81, 22));
        QPalette palette;
        QBrush brush(QColor(255, 255, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(212, 208, 200, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxThresholdPLib->setPalette(palette);
        doubleSpinBoxThresholdPLib->setReadOnly(true);
        doubleSpinBoxThresholdMLib = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdMLib->setObjectName("doubleSpinBoxThresholdMLib");
        doubleSpinBoxThresholdMLib->setGeometry(QRect(320, 180, 81, 22));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxThresholdMLib->setPalette(palette1);
        doubleSpinBoxThresholdMLib->setReadOnly(true);
        EditSearchDotLib = new QSpinBox(frame);
        EditSearchDotLib->setObjectName("EditSearchDotLib");
        EditSearchDotLib->setGeometry(QRect(320, 130, 81, 22));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        EditSearchDotLib->setPalette(palette2);
        EditSearchDotLib->setReadOnly(true);
        EditSearchDotLib->setMaximum(100);
        checkBoxEnable = new QCheckBox(frame);
        checkBoxEnable->setObjectName("checkBoxEnable");
        checkBoxEnable->setGeometry(QRect(10, 100, 191, 21));
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 0, 62, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditItemID = new QLineEdit(frame);
        EditItemID->setObjectName("EditItemID");
        EditItemID->setGeometry(QRect(0, 20, 61, 21));
        EditItemID->setReadOnly(true);
        doubleSpinBoxSearchDot = new QDoubleSpinBox(frame);
        doubleSpinBoxSearchDot->setObjectName("doubleSpinBoxSearchDot");
        doubleSpinBoxSearchDot->setGeometry(QRect(230, 150, 91, 22));
        QPalette palette3;
        QBrush brush2(QColor(255, 170, 0, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        QBrush brush3(QColor(240, 240, 240, 255));
        brush3.setStyle(Qt::BrushStyle::SolidPattern);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        doubleSpinBoxSearchDot->setPalette(palette3);
        doubleSpinBoxSearchDot->setMaximum(9999999999.000000000000000);
        labelUnitName_4 = new QLabel(frame);
        labelUnitName_4->setObjectName("labelUnitName_4");
        labelUnitName_4->setGeometry(QRect(130, 150, 91, 20));
        labelUnitName_4->setFrameShape(QFrame::NoFrame);
        labelUnitName_4->setFrameShadow(QFrame::Sunken);
        labelUnitName_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_98 = new QLabel(frame);
        label_98->setObjectName("label_98");
        label_98->setGeometry(QRect(320, 110, 81, 21));
        label_98->setFrameShape(QFrame::Panel);
        label_98->setFrameShadow(QFrame::Sunken);
        label_98->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxThresholdM_2 = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdM_2->setObjectName("doubleSpinBoxThresholdM_2");
        doubleSpinBoxThresholdM_2->setGeometry(QRect(230, 200, 91, 22));
        QPalette palette4;
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        doubleSpinBoxThresholdM_2->setPalette(palette4);
        doubleSpinBoxThresholdM_2->setMaximum(9999999999.000000000000000);
        doubleSpinBoxThresholdP_2 = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdP_2->setObjectName("doubleSpinBoxThresholdP_2");
        doubleSpinBoxThresholdP_2->setGeometry(QRect(230, 250, 91, 22));
        QPalette palette5;
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette5.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        doubleSpinBoxThresholdP_2->setPalette(palette5);
        doubleSpinBoxThresholdP_2->setMaximum(9999999999.000000000000000);
        labelUnitName_5 = new QLabel(frame);
        labelUnitName_5->setObjectName("labelUnitName_5");
        labelUnitName_5->setGeometry(QRect(130, 200, 91, 20));
        labelUnitName_5->setFrameShape(QFrame::NoFrame);
        labelUnitName_5->setFrameShadow(QFrame::Sunken);
        labelUnitName_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelUnitName_6 = new QLabel(frame);
        labelUnitName_6->setObjectName("labelUnitName_6");
        labelUnitName_6->setGeometry(QRect(130, 250, 91, 20));
        labelUnitName_6->setFrameShape(QFrame::NoFrame);
        labelUnitName_6->setFrameShadow(QFrame::Sunken);
        labelUnitName_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_99 = new QLabel(frame);
        label_99->setObjectName("label_99");
        label_99->setGeometry(QRect(230, 110, 81, 21));
        label_99->setFrameShape(QFrame::Panel);
        label_99->setFrameShadow(QFrame::Sunken);
        label_99->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_100 = new QLabel(frame);
        label_100->setObjectName("label_100");
        label_100->setGeometry(QRect(10, 60, 211, 21));
        label_100->setFrameShape(QFrame::Panel);
        label_100->setFrameShadow(QFrame::Sunken);
        label_100->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        comboBoxUsedLayer = new QComboBox(frame);
        comboBoxUsedLayer->setObjectName("comboBoxUsedLayer");
        comboBoxUsedLayer->setGeometry(QRect(230, 60, 161, 22));
        pushButtonChangeItemID = new QPushButton(frame);
        pushButtonChangeItemID->setObjectName("pushButtonChangeItemID");
        pushButtonChangeItemID->setGeometry(QRect(60, 20, 31, 22));
        pushButtonChangeLib = new QPushButton(EditMarkDialog);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(310, 20, 31, 23));
        label_7 = new QLabel(EditMarkDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(70, 0, 241, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonReflectAllBlocks = new QPushButton(EditMarkDialog);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(180, 360, 161, 41));
        EditLibID = new QLineEdit(EditMarkDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(10, 20, 61, 21));
        EditLibID->setReadOnly(true);
        label_40 = new QLabel(EditMarkDialog);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(450, 210, 201, 21));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setFrameShadow(QFrame::Sunken);
        label_40->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_2 = new QFrame(EditMarkDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(430, 50, 231, 151));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        pushButtonTest = new QPushButton(frame_2);
        pushButtonTest->setObjectName("pushButtonTest");
        pushButtonTest->setGeometry(QRect(30, 10, 151, 31));
        label_10 = new QLabel(frame_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(20, 50, 121, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_11 = new QLabel(frame_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(20, 100, 121, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelPosDiffX = new QLabel(frame_2);
        labelPosDiffX->setObjectName("labelPosDiffX");
        labelPosDiffX->setGeometry(QRect(140, 50, 81, 21));
        labelPosDiffX->setFrameShape(QFrame::Panel);
        labelPosDiffX->setFrameShadow(QFrame::Sunken);
        labelPosDiffX->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelPosDiffY = new QLabel(frame_2);
        labelPosDiffY->setObjectName("labelPosDiffY");
        labelPosDiffY->setGeometry(QRect(140, 100, 81, 21));
        labelPosDiffY->setFrameShape(QFrame::Panel);
        labelPosDiffY->setFrameShadow(QFrame::Sunken);
        labelPosDiffY->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelPosDiffYUnit = new QLabel(frame_2);
        labelPosDiffYUnit->setObjectName("labelPosDiffYUnit");
        labelPosDiffYUnit->setGeometry(QRect(140, 120, 81, 21));
        QPalette palette6;
        QBrush brush4(QColor(255, 255, 255, 255));
        brush4.setStyle(Qt::BrushStyle::SolidPattern);
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush4);
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush2);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush4);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush2);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush2);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush2);
        labelPosDiffYUnit->setPalette(palette6);
        labelPosDiffYUnit->setAutoFillBackground(true);
        labelPosDiffYUnit->setFrameShape(QFrame::Panel);
        labelPosDiffYUnit->setFrameShadow(QFrame::Sunken);
        labelPosDiffYUnit->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelPosDiffXUnit = new QLabel(frame_2);
        labelPosDiffXUnit->setObjectName("labelPosDiffXUnit");
        labelPosDiffXUnit->setGeometry(QRect(140, 70, 81, 21));
        QPalette palette7;
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush4);
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush2);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush4);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush2);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush2);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush2);
        labelPosDiffXUnit->setPalette(palette7);
        labelPosDiffXUnit->setAutoFillBackground(true);
        labelPosDiffXUnit->setFrameShape(QFrame::Panel);
        labelPosDiffXUnit->setFrameShadow(QFrame::Sunken);
        labelPosDiffXUnit->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelUnitName_7 = new QLabel(frame_2);
        labelUnitName_7->setObjectName("labelUnitName_7");
        labelUnitName_7->setGeometry(QRect(40, 70, 91, 20));
        labelUnitName_7->setFrameShape(QFrame::NoFrame);
        labelUnitName_7->setFrameShadow(QFrame::Sunken);
        labelUnitName_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelUnitName_8 = new QLabel(frame_2);
        labelUnitName_8->setObjectName("labelUnitName_8");
        labelUnitName_8->setGeometry(QRect(40, 120, 91, 20));
        labelUnitName_8->setFrameShape(QFrame::NoFrame);
        labelUnitName_8->setFrameShadow(QFrame::Sunken);
        labelUnitName_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Edit_LibName = new QLineEdit(EditMarkDialog);
        Edit_LibName->setObjectName("Edit_LibName");
        Edit_LibName->setGeometry(QRect(70, 20, 241, 21));
        Edit_LibName->setReadOnly(true);
        ButtonClose = new QPushButton(EditMarkDialog);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(470, 410, 171, 41));

        retranslateUi(EditMarkDialog);

        QMetaObject::connectSlotsByName(EditMarkDialog);
    } // setupUi

    void retranslateUi(QWidget *EditMarkDialog)
    {
        EditMarkDialog->setWindowTitle(QCoreApplication::translate("EditMarkDialog", "Form", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("EditMarkDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        label_6->setText(QCoreApplication::translate("EditMarkDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("EditMarkDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        ButtonRelrectOnlyBlock->setText(QCoreApplication::translate("EditMarkDialog", "\343\201\223\343\201\256\347\267\232\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        label_92->setText(QCoreApplication::translate("EditMarkDialog", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        EditName->setText(QString());
        label_4->setText(QCoreApplication::translate("EditMarkDialog", "\345\200\213\345\210\245\345\220\215\347\247\260", nullptr));
        label_94->setText(QCoreApplication::translate("EditMarkDialog", "\343\202\272\343\203\254\343\200\200\344\270\212\351\231\220\343\201\227\343\201\215\343\201\204\345\200\244\357\274\210\346\234\200\345\260\217\357\274\220\357\274\211", nullptr));
        label_93->setText(QCoreApplication::translate("EditMarkDialog", "\343\202\272\343\203\254\343\200\200\344\270\213\351\231\220\343\201\227\343\201\215\343\201\204\345\200\244\357\274\210\346\234\200\345\260\217\357\274\220\357\274\211", nullptr));
        checkBoxEnable->setText(QCoreApplication::translate("EditMarkDialog", "Enable", nullptr));
        label_8->setText(QCoreApplication::translate("EditMarkDialog", "ItemID", nullptr));
        EditItemID->setText(QCoreApplication::translate("EditMarkDialog", "12345", nullptr));
        labelUnitName_4->setText(QCoreApplication::translate("EditMarkDialog", "mm", nullptr));
        label_98->setText(QCoreApplication::translate("EditMarkDialog", "Library", nullptr));
        labelUnitName_5->setText(QCoreApplication::translate("EditMarkDialog", "mm", nullptr));
        labelUnitName_6->setText(QCoreApplication::translate("EditMarkDialog", "mm", nullptr));
        label_99->setText(QCoreApplication::translate("EditMarkDialog", "Value", nullptr));
        label_100->setText(QCoreApplication::translate("EditMarkDialog", "Used layer", nullptr));
        pushButtonChangeItemID->setText(QCoreApplication::translate("EditMarkDialog", "...", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("EditMarkDialog", "...", nullptr));
        label_7->setText(QCoreApplication::translate("EditMarkDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("EditMarkDialog", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\347\267\232\343\201\253\345\217\215\346\230\240", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditMarkDialog", "12345", nullptr));
        label_40->setText(QCoreApplication::translate("EditMarkDialog", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\343\203\220\343\203\251\343\201\244\343\201\215\343\202\260\343\203\251\343\203\225", nullptr));
        pushButtonTest->setText(QCoreApplication::translate("EditMarkDialog", "Test", nullptr));
        label_10->setText(QCoreApplication::translate("EditMarkDialog", "\357\274\270\346\226\271\345\220\221\344\275\215\347\275\256\343\202\272\343\203\254", nullptr));
        label_11->setText(QCoreApplication::translate("EditMarkDialog", "\357\274\271\346\226\271\345\220\221\344\275\215\347\275\256\343\202\272\343\203\254", nullptr));
        labelPosDiffX->setText(QString());
        labelPosDiffY->setText(QString());
        labelPosDiffYUnit->setText(QString());
        labelPosDiffXUnit->setText(QString());
        labelUnitName_7->setText(QCoreApplication::translate("EditMarkDialog", "mm", nullptr));
        labelUnitName_8->setText(QCoreApplication::translate("EditMarkDialog", "mm", nullptr));
        Edit_LibName->setText(QCoreApplication::translate("EditMarkDialog", "XXX", nullptr));
        ButtonClose->setText(QCoreApplication::translate("EditMarkDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditMarkDialog: public Ui_EditMarkDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITMARKDIALOG_H
