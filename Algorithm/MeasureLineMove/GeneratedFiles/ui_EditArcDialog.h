/********************************************************************************
** Form generated from reading UI file 'EditArcDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITARCDIALOG_H
#define UI_EDITARCDIALOG_H

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

class Ui_EditArcDialog
{
public:
    QLabel *label_40;
    QLabel *label_7;
    QPushButton *pushButtonChangeLib;
    QFrame *frame;
    QLabel *label_92;
    QSpinBox *EditSearchDot;
    QLineEdit *EditName;
    QLabel *label_4;
    QLabel *label_94;
    QLabel *label_93;
    QDoubleSpinBox *doubleSpinBoxThresholdM;
    QDoubleSpinBox *doubleSpinBoxThresholdP;
    QLabel *label_95;
    QSpinBox *EditEdgeWidth;
    QDoubleSpinBox *doubleSpinBoxThresholdMLib;
    QSpinBox *EditSearchDotLib;
    QDoubleSpinBox *doubleSpinBoxThresholdPLib;
    QSpinBox *EditEdgeWidthLib;
    QCheckBox *checkBoxEnable;
    QLabel *label_100;
    QComboBox *comboBoxUsedLayer;
    QPushButton *pushButtonChangeItemID;
    QLabel *label_8;
    QLineEdit *EditItemID;
    QLabel *label_6;
    QPushButton *ButtonSaveToLibrary;
    QPushButton *ButtonRelrectOnlyBlock;
    QLineEdit *Edit_LibName;
    QFrame *frame_2;
    QPushButton *pushButtonTest;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *labelPosDiffX;
    QLabel *labelPosDiffY;
    QLabel *label_12;
    QLabel *labelRadius;
    QLabel *labelDiffR;
    QLabel *label_13;
    QPushButton *ButtonReflectAllBlocks;
    QListWidget *listWidgetHistList;
    QPushButton *ButtonClose;
    QLineEdit *EditLibID;
    QPushButton *ButtonLoadFromLibrary;

    void setupUi(QWidget *EditArcDialog)
    {
        if (EditArcDialog->objectName().isEmpty())
            EditArcDialog->setObjectName("EditArcDialog");
        EditArcDialog->resize(585, 422);
        label_40 = new QLabel(EditArcDialog);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(360, 210, 201, 21));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setFrameShadow(QFrame::Sunken);
        label_40->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_7 = new QLabel(EditArcDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(70, 10, 241, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonChangeLib = new QPushButton(EditArcDialog);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(310, 30, 31, 23));
        frame = new QFrame(EditArcDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 60, 331, 251));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_92 = new QLabel(frame);
        label_92->setObjectName("label_92");
        label_92->setGeometry(QRect(10, 140, 171, 21));
        label_92->setFrameShape(QFrame::Panel);
        label_92->setFrameShadow(QFrame::Sunken);
        label_92->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSearchDot = new QSpinBox(frame);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(180, 140, 71, 22));
        EditSearchDot->setReadOnly(true);
        EditSearchDot->setMaximum(100);
        EditName = new QLineEdit(frame);
        EditName->setObjectName("EditName");
        EditName->setGeometry(QRect(90, 40, 211, 31));
        QFont font;
        font.setPointSize(12);
        EditName->setFont(font);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 40, 81, 31));
        QFont font1;
        font1.setPointSize(9);
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_94 = new QLabel(frame);
        label_94->setObjectName("label_94");
        label_94->setGeometry(QRect(10, 190, 171, 21));
        label_94->setFrameShape(QFrame::Panel);
        label_94->setFrameShadow(QFrame::Sunken);
        label_94->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_93 = new QLabel(frame);
        label_93->setObjectName("label_93");
        label_93->setGeometry(QRect(10, 170, 171, 21));
        label_93->setFrameShape(QFrame::Panel);
        label_93->setFrameShadow(QFrame::Sunken);
        label_93->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxThresholdM = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdM->setObjectName("doubleSpinBoxThresholdM");
        doubleSpinBoxThresholdM->setGeometry(QRect(180, 170, 71, 22));
        doubleSpinBoxThresholdP = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdP->setObjectName("doubleSpinBoxThresholdP");
        doubleSpinBoxThresholdP->setGeometry(QRect(180, 190, 71, 22));
        label_95 = new QLabel(frame);
        label_95->setObjectName("label_95");
        label_95->setGeometry(QRect(10, 220, 171, 21));
        label_95->setFrameShape(QFrame::Panel);
        label_95->setFrameShadow(QFrame::Sunken);
        label_95->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditEdgeWidth = new QSpinBox(frame);
        EditEdgeWidth->setObjectName("EditEdgeWidth");
        EditEdgeWidth->setGeometry(QRect(180, 220, 71, 22));
        EditEdgeWidth->setMaximum(255);
        doubleSpinBoxThresholdMLib = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdMLib->setObjectName("doubleSpinBoxThresholdMLib");
        doubleSpinBoxThresholdMLib->setGeometry(QRect(250, 170, 71, 22));
        QPalette palette;
        QBrush brush(QColor(255, 255, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(212, 208, 200, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxThresholdMLib->setPalette(palette);
        doubleSpinBoxThresholdMLib->setReadOnly(true);
        EditSearchDotLib = new QSpinBox(frame);
        EditSearchDotLib->setObjectName("EditSearchDotLib");
        EditSearchDotLib->setGeometry(QRect(250, 140, 71, 22));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        EditSearchDotLib->setPalette(palette1);
        EditSearchDotLib->setReadOnly(true);
        EditSearchDotLib->setMaximum(100);
        doubleSpinBoxThresholdPLib = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdPLib->setObjectName("doubleSpinBoxThresholdPLib");
        doubleSpinBoxThresholdPLib->setGeometry(QRect(250, 190, 71, 22));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxThresholdPLib->setPalette(palette2);
        doubleSpinBoxThresholdPLib->setReadOnly(true);
        EditEdgeWidthLib = new QSpinBox(frame);
        EditEdgeWidthLib->setObjectName("EditEdgeWidthLib");
        EditEdgeWidthLib->setGeometry(QRect(250, 220, 71, 22));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        EditEdgeWidthLib->setPalette(palette3);
        EditEdgeWidthLib->setReadOnly(true);
        EditEdgeWidthLib->setMaximum(255);
        checkBoxEnable = new QCheckBox(frame);
        checkBoxEnable->setObjectName("checkBoxEnable");
        checkBoxEnable->setGeometry(QRect(10, 110, 191, 21));
        label_100 = new QLabel(frame);
        label_100->setObjectName("label_100");
        label_100->setGeometry(QRect(10, 80, 171, 21));
        label_100->setFrameShape(QFrame::Panel);
        label_100->setFrameShadow(QFrame::Sunken);
        label_100->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        comboBoxUsedLayer = new QComboBox(frame);
        comboBoxUsedLayer->setObjectName("comboBoxUsedLayer");
        comboBoxUsedLayer->setGeometry(QRect(190, 80, 131, 22));
        pushButtonChangeItemID = new QPushButton(frame);
        pushButtonChangeItemID->setObjectName("pushButtonChangeItemID");
        pushButtonChangeItemID->setGeometry(QRect(150, 10, 31, 22));
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 10, 81, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditItemID = new QLineEdit(frame);
        EditItemID->setObjectName("EditItemID");
        EditItemID->setGeometry(QRect(90, 10, 61, 21));
        EditItemID->setReadOnly(true);
        label_6 = new QLabel(EditArcDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 10, 62, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonSaveToLibrary = new QPushButton(EditArcDialog);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(10, 370, 161, 41));
        ButtonRelrectOnlyBlock = new QPushButton(EditArcDialog);
        ButtonRelrectOnlyBlock->setObjectName("ButtonRelrectOnlyBlock");
        ButtonRelrectOnlyBlock->setGeometry(QRect(10, 320, 161, 41));
        Edit_LibName = new QLineEdit(EditArcDialog);
        Edit_LibName->setObjectName("Edit_LibName");
        Edit_LibName->setGeometry(QRect(70, 30, 241, 21));
        Edit_LibName->setReadOnly(true);
        frame_2 = new QFrame(EditArcDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(360, 50, 201, 141));
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
        label_11->setGeometry(QRect(20, 70, 121, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelPosDiffX = new QLabel(frame_2);
        labelPosDiffX->setObjectName("labelPosDiffX");
        labelPosDiffX->setGeometry(QRect(140, 50, 41, 21));
        labelPosDiffX->setFrameShape(QFrame::Panel);
        labelPosDiffX->setFrameShadow(QFrame::Sunken);
        labelPosDiffX->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelPosDiffY = new QLabel(frame_2);
        labelPosDiffY->setObjectName("labelPosDiffY");
        labelPosDiffY->setGeometry(QRect(140, 70, 41, 21));
        labelPosDiffY->setFrameShape(QFrame::Panel);
        labelPosDiffY->setFrameShadow(QFrame::Sunken);
        labelPosDiffY->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_12 = new QLabel(frame_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(20, 90, 121, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelRadius = new QLabel(frame_2);
        labelRadius->setObjectName("labelRadius");
        labelRadius->setGeometry(QRect(140, 90, 41, 21));
        labelRadius->setFrameShape(QFrame::Panel);
        labelRadius->setFrameShadow(QFrame::Sunken);
        labelRadius->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelDiffR = new QLabel(frame_2);
        labelDiffR->setObjectName("labelDiffR");
        labelDiffR->setGeometry(QRect(140, 110, 41, 21));
        labelDiffR->setFrameShape(QFrame::Panel);
        labelDiffR->setFrameShadow(QFrame::Sunken);
        labelDiffR->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_13 = new QLabel(frame_2);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(20, 110, 121, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonReflectAllBlocks = new QPushButton(EditArcDialog);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(180, 320, 161, 41));
        listWidgetHistList = new QListWidget(EditArcDialog);
        listWidgetHistList->setObjectName("listWidgetHistList");
        listWidgetHistList->setGeometry(QRect(360, 230, 201, 71));
        ButtonClose = new QPushButton(EditArcDialog);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(380, 350, 171, 41));
        EditLibID = new QLineEdit(EditArcDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(10, 30, 61, 21));
        EditLibID->setReadOnly(true);
        ButtonLoadFromLibrary = new QPushButton(EditArcDialog);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(180, 370, 161, 41));

        retranslateUi(EditArcDialog);

        QMetaObject::connectSlotsByName(EditArcDialog);
    } // setupUi

    void retranslateUi(QWidget *EditArcDialog)
    {
        EditArcDialog->setWindowTitle(QCoreApplication::translate("EditArcDialog", "Threshold MeasureLineMove ARC", nullptr));
        label_40->setText(QCoreApplication::translate("EditArcDialog", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\343\203\220\343\203\251\343\201\244\343\201\215\343\202\260\343\203\251\343\203\225", nullptr));
        label_7->setText(QCoreApplication::translate("EditArcDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("EditArcDialog", "...", nullptr));
        label_92->setText(QCoreApplication::translate("EditArcDialog", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        EditName->setText(QString());
        label_4->setText(QCoreApplication::translate("EditArcDialog", "\345\200\213\345\210\245\345\220\215\347\247\260", nullptr));
        label_94->setText(QCoreApplication::translate("EditArcDialog", "\345\276\204\345\244\211\345\213\225\343\200\200\344\270\212\351\231\220\343\201\227\343\201\215\343\201\204\345\200\244\357\274\210\346\234\200\345\260\217\357\274\220\357\274\211", nullptr));
        label_93->setText(QCoreApplication::translate("EditArcDialog", "\345\276\204\345\244\211\345\213\225\343\200\200\344\270\213\351\231\220\343\201\227\343\201\215\343\201\204\345\200\244\357\274\210\346\234\200\345\260\217\357\274\220\357\274\211", nullptr));
        label_95->setText(QCoreApplication::translate("EditArcDialog", "\350\274\252\351\203\255\345\271\205", nullptr));
        checkBoxEnable->setText(QCoreApplication::translate("EditArcDialog", "Enable", nullptr));
        label_100->setText(QCoreApplication::translate("EditArcDialog", "Used layer", nullptr));
        pushButtonChangeItemID->setText(QCoreApplication::translate("EditArcDialog", "...", nullptr));
        label_8->setText(QCoreApplication::translate("EditArcDialog", "ItemID", nullptr));
        EditItemID->setText(QCoreApplication::translate("EditArcDialog", "12345", nullptr));
        label_6->setText(QCoreApplication::translate("EditArcDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("EditArcDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        ButtonRelrectOnlyBlock->setText(QCoreApplication::translate("EditArcDialog", "\343\201\223\343\201\256\347\267\232\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        Edit_LibName->setText(QCoreApplication::translate("EditArcDialog", "XXX", nullptr));
        pushButtonTest->setText(QCoreApplication::translate("EditArcDialog", "Test", nullptr));
        label_10->setText(QCoreApplication::translate("EditArcDialog", "\344\270\255\345\277\203\343\200\200\357\274\270\346\226\271\345\220\221\343\202\272\343\203\254", nullptr));
        label_11->setText(QCoreApplication::translate("EditArcDialog", "\344\270\255\345\277\203\343\200\200\357\274\271\346\226\271\345\220\221\343\202\272\343\203\254", nullptr));
        labelPosDiffX->setText(QString());
        labelPosDiffY->setText(QString());
        label_12->setText(QCoreApplication::translate("EditArcDialog", "\350\250\210\346\270\254\343\201\227\343\201\237\345\276\204", nullptr));
        labelRadius->setText(QString());
        labelDiffR->setText(QString());
        label_13->setText(QCoreApplication::translate("EditArcDialog", "\345\276\204\345\244\211\345\213\225", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("EditArcDialog", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\347\267\232\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonClose->setText(QCoreApplication::translate("EditArcDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditArcDialog", "12345", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("EditArcDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditArcDialog: public Ui_EditArcDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITARCDIALOG_H
