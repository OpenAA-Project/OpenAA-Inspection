/********************************************************************************
** Form generated from reading UI file 'EditDistanceDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITDISTANCEDIALOG_H
#define UI_EDITDISTANCEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditDistanceDialog
{
public:
    QLabel *label_40;
    QFrame *frame;
    QLineEdit *EditName;
    QLabel *label_4;
    QLabel *label_94;
    QLabel *label_93;
    QDoubleSpinBox *doubleSpinBoxThresholdM;
    QDoubleSpinBox *doubleSpinBoxThresholdP;
    QDoubleSpinBox *doubleSpinBoxThresholdPLib;
    QDoubleSpinBox *doubleSpinBoxThresholdMLib;
    QCheckBox *checkBoxEnable;
    QLineEdit *EditItemID;
    QLabel *label_8;
    QDoubleSpinBox *doubleSpinBoxThresholdP_2;
    QDoubleSpinBox *doubleSpinBoxThresholdM_2;
    QLabel *labelUnitName_4;
    QLabel *label_98;
    QLabel *labelUnitName_5;
    QLabel *label_99;
    QCheckBox *checkBoxModeToSetInInitial;
    QDoubleSpinBox *doubleSpinBoxOKRangeInInitial;
    QLabel *label_96;
    QLabel *label_97;
    QComboBox *comboBoxOutputType;
    QPushButton *pushButtonChangeItemID;
    QPushButton *pushButtonChangeLib;
    QLabel *label_6;
    QLineEdit *EditLibID;
    QLineEdit *Edit_LibName;
    QPushButton *ButtonClose;
    QPushButton *ButtonRelrectOnlyBlock;
    QLabel *label_7;
    QPushButton *ButtonSaveToLibrary;
    QListWidget *listWidgetHistList;
    QPushButton *ButtonReflectAllBlocks;
    QPushButton *ButtonLoadFromLibrary;
    QFrame *frame_2;
    QPushButton *pushButtonTest;
    QLabel *label_12;
    QLabel *labelLength;
    QLabel *labelLengthUnit;
    QLabel *labelUnitName_6;
    QGroupBox *groupBoxTransfer;
    QLabel *label_95;
    QSpinBox *spinBoxTransferInfo;

    void setupUi(QWidget *EditDistanceDialog)
    {
        if (EditDistanceDialog->objectName().isEmpty())
            EditDistanceDialog->setObjectName("EditDistanceDialog");
        EditDistanceDialog->resize(672, 456);
        label_40 = new QLabel(EditDistanceDialog);
        label_40->setObjectName("label_40");
        label_40->setEnabled(false);
        label_40->setGeometry(QRect(420, 250, 201, 21));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setFrameShadow(QFrame::Sunken);
        label_40->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame = new QFrame(EditDistanceDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 60, 401, 281));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
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
        label_94->setGeometry(QRect(10, 140, 211, 21));
        label_94->setFrameShape(QFrame::Panel);
        label_94->setFrameShadow(QFrame::Sunken);
        label_94->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_93 = new QLabel(frame);
        label_93->setObjectName("label_93");
        label_93->setGeometry(QRect(10, 90, 211, 21));
        label_93->setFrameShape(QFrame::Panel);
        label_93->setFrameShadow(QFrame::Sunken);
        label_93->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxThresholdM = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdM->setObjectName("doubleSpinBoxThresholdM");
        doubleSpinBoxThresholdM->setGeometry(QRect(230, 90, 91, 22));
        doubleSpinBoxThresholdM->setMinimum(-99999999.000000000000000);
        doubleSpinBoxThresholdM->setMaximum(999999.989999999990687);
        doubleSpinBoxThresholdP = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdP->setObjectName("doubleSpinBoxThresholdP");
        doubleSpinBoxThresholdP->setGeometry(QRect(230, 140, 91, 22));
        doubleSpinBoxThresholdP->setMinimum(-99999999.000000000000000);
        doubleSpinBoxThresholdP->setMaximum(999999.989999999990687);
        doubleSpinBoxThresholdPLib = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdPLib->setObjectName("doubleSpinBoxThresholdPLib");
        doubleSpinBoxThresholdPLib->setGeometry(QRect(320, 140, 71, 22));
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
        doubleSpinBoxThresholdPLib->setMaximum(999999.989999999990687);
        doubleSpinBoxThresholdMLib = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdMLib->setObjectName("doubleSpinBoxThresholdMLib");
        doubleSpinBoxThresholdMLib->setGeometry(QRect(320, 90, 71, 22));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxThresholdMLib->setPalette(palette1);
        doubleSpinBoxThresholdMLib->setReadOnly(true);
        doubleSpinBoxThresholdMLib->setMaximum(999999.989999999990687);
        checkBoxEnable = new QCheckBox(frame);
        checkBoxEnable->setObjectName("checkBoxEnable");
        checkBoxEnable->setGeometry(QRect(20, 60, 191, 21));
        EditItemID = new QLineEdit(frame);
        EditItemID->setObjectName("EditItemID");
        EditItemID->setGeometry(QRect(0, 30, 61, 21));
        EditItemID->setReadOnly(true);
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 10, 62, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxThresholdP_2 = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdP_2->setObjectName("doubleSpinBoxThresholdP_2");
        doubleSpinBoxThresholdP_2->setGeometry(QRect(230, 160, 91, 22));
        QPalette palette2;
        QBrush brush2(QColor(255, 170, 0, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        QBrush brush3(QColor(240, 240, 240, 255));
        brush3.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        doubleSpinBoxThresholdP_2->setPalette(palette2);
        doubleSpinBoxThresholdP_2->setMaximum(9999999999.000000000000000);
        doubleSpinBoxThresholdM_2 = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdM_2->setObjectName("doubleSpinBoxThresholdM_2");
        doubleSpinBoxThresholdM_2->setGeometry(QRect(230, 110, 91, 22));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        doubleSpinBoxThresholdM_2->setPalette(palette3);
        doubleSpinBoxThresholdM_2->setMaximum(9999999999.000000000000000);
        labelUnitName_4 = new QLabel(frame);
        labelUnitName_4->setObjectName("labelUnitName_4");
        labelUnitName_4->setGeometry(QRect(130, 110, 91, 20));
        labelUnitName_4->setFrameShape(QFrame::NoFrame);
        labelUnitName_4->setFrameShadow(QFrame::Sunken);
        labelUnitName_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_98 = new QLabel(frame);
        label_98->setObjectName("label_98");
        label_98->setGeometry(QRect(320, 70, 81, 21));
        label_98->setFrameShape(QFrame::Panel);
        label_98->setFrameShadow(QFrame::Sunken);
        label_98->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelUnitName_5 = new QLabel(frame);
        labelUnitName_5->setObjectName("labelUnitName_5");
        labelUnitName_5->setGeometry(QRect(130, 160, 91, 20));
        labelUnitName_5->setFrameShape(QFrame::NoFrame);
        labelUnitName_5->setFrameShadow(QFrame::Sunken);
        labelUnitName_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_99 = new QLabel(frame);
        label_99->setObjectName("label_99");
        label_99->setGeometry(QRect(230, 70, 81, 21));
        label_99->setFrameShape(QFrame::Panel);
        label_99->setFrameShadow(QFrame::Sunken);
        label_99->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxModeToSetInInitial = new QCheckBox(frame);
        checkBoxModeToSetInInitial->setObjectName("checkBoxModeToSetInInitial");
        checkBoxModeToSetInInitial->setGeometry(QRect(20, 190, 251, 21));
        doubleSpinBoxOKRangeInInitial = new QDoubleSpinBox(frame);
        doubleSpinBoxOKRangeInInitial->setObjectName("doubleSpinBoxOKRangeInInitial");
        doubleSpinBoxOKRangeInInitial->setGeometry(QRect(320, 220, 71, 22));
        label_96 = new QLabel(frame);
        label_96->setObjectName("label_96");
        label_96->setGeometry(QRect(10, 220, 301, 21));
        label_96->setFrameShape(QFrame::Panel);
        label_96->setFrameShadow(QFrame::Sunken);
        label_96->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_97 = new QLabel(frame);
        label_97->setObjectName("label_97");
        label_97->setGeometry(QRect(10, 250, 111, 21));
        label_97->setFrameShape(QFrame::Panel);
        label_97->setFrameShadow(QFrame::Sunken);
        label_97->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        comboBoxOutputType = new QComboBox(frame);
        comboBoxOutputType->addItem(QString());
        comboBoxOutputType->addItem(QString());
        comboBoxOutputType->setObjectName("comboBoxOutputType");
        comboBoxOutputType->setGeometry(QRect(130, 250, 261, 24));
        pushButtonChangeItemID = new QPushButton(frame);
        pushButtonChangeItemID->setObjectName("pushButtonChangeItemID");
        pushButtonChangeItemID->setGeometry(QRect(60, 30, 31, 22));
        pushButtonChangeLib = new QPushButton(EditDistanceDialog);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(310, 30, 31, 23));
        label_6 = new QLabel(EditDistanceDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 10, 62, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(EditDistanceDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(10, 30, 61, 21));
        EditLibID->setReadOnly(true);
        Edit_LibName = new QLineEdit(EditDistanceDialog);
        Edit_LibName->setObjectName("Edit_LibName");
        Edit_LibName->setGeometry(QRect(70, 30, 241, 21));
        Edit_LibName->setReadOnly(true);
        ButtonClose = new QPushButton(EditDistanceDialog);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(350, 400, 171, 41));
        ButtonRelrectOnlyBlock = new QPushButton(EditDistanceDialog);
        ButtonRelrectOnlyBlock->setObjectName("ButtonRelrectOnlyBlock");
        ButtonRelrectOnlyBlock->setGeometry(QRect(10, 350, 161, 41));
        label_7 = new QLabel(EditDistanceDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(70, 10, 241, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonSaveToLibrary = new QPushButton(EditDistanceDialog);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(10, 400, 161, 41));
        listWidgetHistList = new QListWidget(EditDistanceDialog);
        listWidgetHistList->setObjectName("listWidgetHistList");
        listWidgetHistList->setEnabled(false);
        listWidgetHistList->setGeometry(QRect(420, 270, 201, 71));
        ButtonReflectAllBlocks = new QPushButton(EditDistanceDialog);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(180, 350, 161, 41));
        ButtonLoadFromLibrary = new QPushButton(EditDistanceDialog);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(180, 400, 161, 41));
        frame_2 = new QFrame(EditDistanceDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(420, 50, 231, 111));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        pushButtonTest = new QPushButton(frame_2);
        pushButtonTest->setObjectName("pushButtonTest");
        pushButtonTest->setGeometry(QRect(30, 10, 151, 31));
        label_12 = new QLabel(frame_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(20, 50, 101, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelLength = new QLabel(frame_2);
        labelLength->setObjectName("labelLength");
        labelLength->setGeometry(QRect(120, 50, 101, 21));
        labelLength->setFrameShape(QFrame::Panel);
        labelLength->setFrameShadow(QFrame::Sunken);
        labelLength->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelLengthUnit = new QLabel(frame_2);
        labelLengthUnit->setObjectName("labelLengthUnit");
        labelLengthUnit->setGeometry(QRect(120, 70, 101, 21));
        QPalette palette4;
        QBrush brush4(QColor(255, 255, 255, 255));
        brush4.setStyle(Qt::BrushStyle::SolidPattern);
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush4);
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush2);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush4);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush2);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush2);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush2);
        labelLengthUnit->setPalette(palette4);
        labelLengthUnit->setAutoFillBackground(true);
        labelLengthUnit->setFrameShape(QFrame::Panel);
        labelLengthUnit->setFrameShadow(QFrame::Sunken);
        labelLengthUnit->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelUnitName_6 = new QLabel(frame_2);
        labelUnitName_6->setObjectName("labelUnitName_6");
        labelUnitName_6->setGeometry(QRect(30, 70, 91, 20));
        labelUnitName_6->setFrameShape(QFrame::NoFrame);
        labelUnitName_6->setFrameShadow(QFrame::Sunken);
        labelUnitName_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        groupBoxTransfer = new QGroupBox(EditDistanceDialog);
        groupBoxTransfer->setObjectName("groupBoxTransfer");
        groupBoxTransfer->setGeometry(QRect(420, 170, 231, 61));
        groupBoxTransfer->setCheckable(true);
        label_95 = new QLabel(groupBoxTransfer);
        label_95->setObjectName("label_95");
        label_95->setGeometry(QRect(10, 30, 141, 21));
        label_95->setFrameShape(QFrame::Panel);
        label_95->setFrameShadow(QFrame::Sunken);
        label_95->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxTransferInfo = new QSpinBox(groupBoxTransfer);
        spinBoxTransferInfo->setObjectName("spinBoxTransferInfo");
        spinBoxTransferInfo->setGeometry(QRect(160, 30, 61, 22));
        spinBoxTransferInfo->setMinimum(-1);
        spinBoxTransferInfo->setMaximum(10000);

        retranslateUi(EditDistanceDialog);

        QMetaObject::connectSlotsByName(EditDistanceDialog);
    } // setupUi

    void retranslateUi(QWidget *EditDistanceDialog)
    {
        EditDistanceDialog->setWindowTitle(QCoreApplication::translate("EditDistanceDialog", "Threshold MeasureLineMove Distance", nullptr));
        label_40->setText(QCoreApplication::translate("EditDistanceDialog", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\343\203\220\343\203\251\343\201\244\343\201\215\343\202\260\343\203\251\343\203\225", nullptr));
        EditName->setText(QString());
        label_4->setText(QCoreApplication::translate("EditDistanceDialog", "\345\200\213\345\210\245\345\220\215\347\247\260", nullptr));
        label_94->setText(QCoreApplication::translate("EditDistanceDialog", "\351\225\267\343\201\225\345\244\211\345\213\225\343\200\200\344\270\212\351\231\220\343\201\227\343\201\215\343\201\204\345\200\244\357\274\210\346\234\200\345\260\217\357\274\220\357\274\211", nullptr));
        label_93->setText(QCoreApplication::translate("EditDistanceDialog", "\351\225\267\343\201\225\345\244\211\345\213\225\343\200\200\344\270\213\351\231\220\343\201\227\343\201\215\343\201\204\345\200\244\357\274\210\346\234\200\345\260\217\357\274\220\357\274\211", nullptr));
        checkBoxEnable->setText(QCoreApplication::translate("EditDistanceDialog", "Enable", nullptr));
        EditItemID->setText(QCoreApplication::translate("EditDistanceDialog", "12345", nullptr));
        label_8->setText(QCoreApplication::translate("EditDistanceDialog", "ItemID", nullptr));
        labelUnitName_4->setText(QCoreApplication::translate("EditDistanceDialog", "mm", nullptr));
        label_98->setText(QCoreApplication::translate("EditDistanceDialog", "Library", nullptr));
        labelUnitName_5->setText(QCoreApplication::translate("EditDistanceDialog", "mm", nullptr));
        label_99->setText(QCoreApplication::translate("EditDistanceDialog", "Value", nullptr));
        checkBoxModeToSetInInitial->setText(QCoreApplication::translate("EditDistanceDialog", "Update position and value in Initialization", nullptr));
        label_96->setText(QCoreApplication::translate("EditDistanceDialog", "\345\210\235\346\234\237\345\214\226\346\231\202\343\201\253OK\347\257\204\345\233\262\343\202\222\350\250\255\345\256\232\343\201\231\343\202\213\343\201\250\343\201\215\343\201\256OK\345\271\205(mm)", nullptr));
        label_97->setText(QCoreApplication::translate("EditDistanceDialog", "\345\207\272\345\212\233\343\202\277\343\202\244\343\203\227", nullptr));
        comboBoxOutputType->setItemText(0, QCoreApplication::translate("EditDistanceDialog", "\350\250\210\346\270\254\345\200\244\343\201\256\345\207\272\345\212\233", nullptr));
        comboBoxOutputType->setItemText(1, QCoreApplication::translate("EditDistanceDialog", "\343\201\227\343\201\215\343\201\204\345\200\244\344\270\255\345\244\256\345\200\244\343\201\250\343\201\256\345\267\256\345\210\206\345\207\272\345\212\233", nullptr));

        pushButtonChangeItemID->setText(QCoreApplication::translate("EditDistanceDialog", "...", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("EditDistanceDialog", "...", nullptr));
        label_6->setText(QCoreApplication::translate("EditDistanceDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditDistanceDialog", "12345", nullptr));
        Edit_LibName->setText(QCoreApplication::translate("EditDistanceDialog", "XXX", nullptr));
        ButtonClose->setText(QCoreApplication::translate("EditDistanceDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonRelrectOnlyBlock->setText(QCoreApplication::translate("EditDistanceDialog", "\343\201\223\343\201\256\347\267\232\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        label_7->setText(QCoreApplication::translate("EditDistanceDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("EditDistanceDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("EditDistanceDialog", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\347\267\232\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("EditDistanceDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        pushButtonTest->setText(QCoreApplication::translate("EditDistanceDialog", "Test", nullptr));
        label_12->setText(QCoreApplication::translate("EditDistanceDialog", "\350\250\210\346\270\254\345\200\244", nullptr));
        labelLength->setText(QString());
        labelLengthUnit->setText(QString());
        labelUnitName_6->setText(QCoreApplication::translate("EditDistanceDialog", "mm", nullptr));
        groupBoxTransfer->setTitle(QCoreApplication::translate("EditDistanceDialog", "\343\203\252\343\203\263\343\202\257\346\203\205\345\240\261", nullptr));
        label_95->setText(QCoreApplication::translate("EditDistanceDialog", "\351\200\201\344\277\241ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditDistanceDialog: public Ui_EditDistanceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITDISTANCEDIALOG_H
