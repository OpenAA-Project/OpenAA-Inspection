/********************************************************************************
** Form generated from reading UI file 'AdjustAlignmentLargeForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADJUSTALIGNMENTLARGEFORM_H
#define UI_ADJUSTALIGNMENTLARGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdjustAlignmentLargeForm
{
public:
    QLabel *label;
    QSpinBox *spinBoxSearchDot;
    QPushButton *pushButtonHistogramX;
    QPushButton *pushButtonSetOne;
    QPushButton *pushButtonSetAll;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonHistogramY;
    QDoubleSpinBox *doubleSpinBoxSearchDotUnit;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *spinBoxSearchDotY;
    QDoubleSpinBox *doubleSpinBoxSearchDotUnitY;
    QLabel *label_5;
    QSpinBox *spinBoxMaxCountHLine;
    QLabel *label_6;
    QSpinBox *spinBoxMaxCountVLine;
    QCheckBox *checkBoxJudgeWithBrDif;
    QSpinBox *spinBoxSearchDot2Y;
    QDoubleSpinBox *doubleSpinBoxSearchDot2Unit;
    QDoubleSpinBox *doubleSpinBoxSearchDot2UnitY;
    QLabel *label_7;
    QSpinBox *spinBoxSearchDot2;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *labelUnitName1;
    QLabel *labelUnitName3;
    QLabel *labelUnitName2;
    QLabel *labelUnitName4;
    QLabel *label_40;
    QListWidget *listWidgetHistList;
    QCheckBox *checkBoxCharacterMode;
    QComboBox *comboBoxUseLayer;
    QLabel *label_13;
    QSpinBox *spinBoxThresholdColor;
    QLabel *labelSelectedLayer;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *labelThresholdColor;

    void setupUi(QWidget *AdjustAlignmentLargeForm)
    {
        if (AdjustAlignmentLargeForm->objectName().isEmpty())
            AdjustAlignmentLargeForm->setObjectName("AdjustAlignmentLargeForm");
        AdjustAlignmentLargeForm->resize(470, 499);
        label = new QLabel(AdjustAlignmentLargeForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 101, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        spinBoxSearchDot = new QSpinBox(AdjustAlignmentLargeForm);
        spinBoxSearchDot->setObjectName("spinBoxSearchDot");
        spinBoxSearchDot->setGeometry(QRect(10, 51, 101, 22));
        spinBoxSearchDot->setMaximum(999999);
        pushButtonHistogramX = new QPushButton(AdjustAlignmentLargeForm);
        pushButtonHistogramX->setObjectName("pushButtonHistogramX");
        pushButtonHistogramX->setGeometry(QRect(10, 410, 111, 31));
        pushButtonSetOne = new QPushButton(AdjustAlignmentLargeForm);
        pushButtonSetOne->setObjectName("pushButtonSetOne");
        pushButtonSetOne->setGeometry(QRect(10, 370, 131, 31));
        pushButtonSetAll = new QPushButton(AdjustAlignmentLargeForm);
        pushButtonSetAll->setObjectName("pushButtonSetAll");
        pushButtonSetAll->setGeometry(QRect(150, 370, 151, 31));
        pushButtonClose = new QPushButton(AdjustAlignmentLargeForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(380, 450, 75, 31));
        pushButtonHistogramY = new QPushButton(AdjustAlignmentLargeForm);
        pushButtonHistogramY->setObjectName("pushButtonHistogramY");
        pushButtonHistogramY->setGeometry(QRect(10, 450, 111, 31));
        doubleSpinBoxSearchDotUnit = new QDoubleSpinBox(AdjustAlignmentLargeForm);
        doubleSpinBoxSearchDotUnit->setObjectName("doubleSpinBoxSearchDotUnit");
        doubleSpinBoxSearchDotUnit->setGeometry(QRect(120, 51, 101, 22));
        QPalette palette;
        QBrush brush(QColor(255, 170, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxSearchDotUnit->setPalette(palette);
        doubleSpinBoxSearchDotUnit->setMaximum(99999999.000000000000000);
        label_2 = new QLabel(AdjustAlignmentLargeForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(120, 30, 61, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(AdjustAlignmentLargeForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(240, 29, 101, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(AdjustAlignmentLargeForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(350, 29, 61, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        spinBoxSearchDotY = new QSpinBox(AdjustAlignmentLargeForm);
        spinBoxSearchDotY->setObjectName("spinBoxSearchDotY");
        spinBoxSearchDotY->setGeometry(QRect(240, 50, 101, 22));
        spinBoxSearchDotY->setMaximum(999999);
        doubleSpinBoxSearchDotUnitY = new QDoubleSpinBox(AdjustAlignmentLargeForm);
        doubleSpinBoxSearchDotUnitY->setObjectName("doubleSpinBoxSearchDotUnitY");
        doubleSpinBoxSearchDotUnitY->setGeometry(QRect(350, 50, 101, 22));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxSearchDotUnitY->setPalette(palette1);
        doubleSpinBoxSearchDotUnitY->setMaximum(99999999.000000000000000);
        label_5 = new QLabel(AdjustAlignmentLargeForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 160, 141, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        spinBoxMaxCountHLine = new QSpinBox(AdjustAlignmentLargeForm);
        spinBoxMaxCountHLine->setObjectName("spinBoxMaxCountHLine");
        spinBoxMaxCountHLine->setGeometry(QRect(60, 180, 91, 22));
        spinBoxMaxCountHLine->setMinimum(-1);
        spinBoxMaxCountHLine->setMaximum(3);
        spinBoxMaxCountHLine->setValue(-1);
        label_6 = new QLabel(AdjustAlignmentLargeForm);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(160, 160, 141, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        spinBoxMaxCountVLine = new QSpinBox(AdjustAlignmentLargeForm);
        spinBoxMaxCountVLine->setObjectName("spinBoxMaxCountVLine");
        spinBoxMaxCountVLine->setGeometry(QRect(210, 180, 91, 22));
        spinBoxMaxCountVLine->setMinimum(-1);
        spinBoxMaxCountVLine->setMaximum(3);
        spinBoxMaxCountVLine->setValue(-1);
        checkBoxJudgeWithBrDif = new QCheckBox(AdjustAlignmentLargeForm);
        checkBoxJudgeWithBrDif->setObjectName("checkBoxJudgeWithBrDif");
        checkBoxJudgeWithBrDif->setGeometry(QRect(10, 210, 301, 31));
        spinBoxSearchDot2Y = new QSpinBox(AdjustAlignmentLargeForm);
        spinBoxSearchDot2Y->setObjectName("spinBoxSearchDot2Y");
        spinBoxSearchDot2Y->setGeometry(QRect(240, 121, 101, 22));
        spinBoxSearchDot2Y->setMaximum(999999);
        doubleSpinBoxSearchDot2Unit = new QDoubleSpinBox(AdjustAlignmentLargeForm);
        doubleSpinBoxSearchDot2Unit->setObjectName("doubleSpinBoxSearchDot2Unit");
        doubleSpinBoxSearchDot2Unit->setGeometry(QRect(120, 122, 101, 22));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxSearchDot2Unit->setPalette(palette2);
        doubleSpinBoxSearchDot2Unit->setMaximum(99999999.000000000000000);
        doubleSpinBoxSearchDot2UnitY = new QDoubleSpinBox(AdjustAlignmentLargeForm);
        doubleSpinBoxSearchDot2UnitY->setObjectName("doubleSpinBoxSearchDot2UnitY");
        doubleSpinBoxSearchDot2UnitY->setGeometry(QRect(350, 121, 101, 22));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxSearchDot2UnitY->setPalette(palette3);
        doubleSpinBoxSearchDot2UnitY->setMaximum(99999999.000000000000000);
        label_7 = new QLabel(AdjustAlignmentLargeForm);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 101, 101, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        spinBoxSearchDot2 = new QSpinBox(AdjustAlignmentLargeForm);
        spinBoxSearchDot2->setObjectName("spinBoxSearchDot2");
        spinBoxSearchDot2->setGeometry(QRect(10, 122, 101, 22));
        spinBoxSearchDot2->setMaximum(999999);
        label_8 = new QLabel(AdjustAlignmentLargeForm);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(350, 100, 61, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_9 = new QLabel(AdjustAlignmentLargeForm);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(120, 101, 61, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_10 = new QLabel(AdjustAlignmentLargeForm);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(240, 100, 101, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_11 = new QLabel(AdjustAlignmentLargeForm);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 10, 441, 20));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_12 = new QLabel(AdjustAlignmentLargeForm);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 80, 441, 20));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelUnitName1 = new QLabel(AdjustAlignmentLargeForm);
        labelUnitName1->setObjectName("labelUnitName1");
        labelUnitName1->setGeometry(QRect(180, 30, 41, 21));
        labelUnitName1->setFrameShape(QFrame::Panel);
        labelUnitName1->setFrameShadow(QFrame::Sunken);
        labelUnitName1->setAlignment(Qt::AlignCenter);
        labelUnitName3 = new QLabel(AdjustAlignmentLargeForm);
        labelUnitName3->setObjectName("labelUnitName3");
        labelUnitName3->setGeometry(QRect(180, 100, 41, 21));
        labelUnitName3->setFrameShape(QFrame::Panel);
        labelUnitName3->setFrameShadow(QFrame::Sunken);
        labelUnitName3->setAlignment(Qt::AlignCenter);
        labelUnitName2 = new QLabel(AdjustAlignmentLargeForm);
        labelUnitName2->setObjectName("labelUnitName2");
        labelUnitName2->setGeometry(QRect(410, 30, 41, 21));
        labelUnitName2->setFrameShape(QFrame::Panel);
        labelUnitName2->setFrameShadow(QFrame::Sunken);
        labelUnitName2->setAlignment(Qt::AlignCenter);
        labelUnitName4 = new QLabel(AdjustAlignmentLargeForm);
        labelUnitName4->setObjectName("labelUnitName4");
        labelUnitName4->setGeometry(QRect(410, 100, 41, 21));
        labelUnitName4->setFrameShape(QFrame::Panel);
        labelUnitName4->setFrameShadow(QFrame::Sunken);
        labelUnitName4->setAlignment(Qt::AlignCenter);
        label_40 = new QLabel(AdjustAlignmentLargeForm);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(310, 160, 151, 31));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setFrameShadow(QFrame::Sunken);
        label_40->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetHistList = new QListWidget(AdjustAlignmentLargeForm);
        listWidgetHistList->setObjectName("listWidgetHistList");
        listWidgetHistList->setGeometry(QRect(310, 190, 151, 81));
        checkBoxCharacterMode = new QCheckBox(AdjustAlignmentLargeForm);
        checkBoxCharacterMode->setObjectName("checkBoxCharacterMode");
        checkBoxCharacterMode->setGeometry(QRect(10, 240, 301, 31));
        comboBoxUseLayer = new QComboBox(AdjustAlignmentLargeForm);
        comboBoxUseLayer->setObjectName("comboBoxUseLayer");
        comboBoxUseLayer->setGeometry(QRect(170, 280, 121, 31));
        label_13 = new QLabel(AdjustAlignmentLargeForm);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 280, 161, 31));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxThresholdColor = new QSpinBox(AdjustAlignmentLargeForm);
        spinBoxThresholdColor->setObjectName("spinBoxThresholdColor");
        spinBoxThresholdColor->setGeometry(QRect(170, 320, 121, 31));
        spinBoxThresholdColor->setMinimum(-1);
        spinBoxThresholdColor->setMaximum(255);
        labelSelectedLayer = new QLabel(AdjustAlignmentLargeForm);
        labelSelectedLayer->setObjectName("labelSelectedLayer");
        labelSelectedLayer->setGeometry(QRect(410, 280, 51, 31));
        labelSelectedLayer->setFrameShape(QFrame::Panel);
        labelSelectedLayer->setFrameShadow(QFrame::Sunken);
        labelSelectedLayer->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_15 = new QLabel(AdjustAlignmentLargeForm);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 320, 161, 31));
        label_15->setFrameShape(QFrame::Panel);
        label_15->setFrameShadow(QFrame::Sunken);
        label_15->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_16 = new QLabel(AdjustAlignmentLargeForm);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(300, 320, 111, 31));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_17 = new QLabel(AdjustAlignmentLargeForm);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(300, 280, 111, 31));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelThresholdColor = new QLabel(AdjustAlignmentLargeForm);
        labelThresholdColor->setObjectName("labelThresholdColor");
        labelThresholdColor->setGeometry(QRect(410, 320, 51, 31));
        labelThresholdColor->setFrameShape(QFrame::Panel);
        labelThresholdColor->setFrameShadow(QFrame::Sunken);
        labelThresholdColor->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(AdjustAlignmentLargeForm);

        QMetaObject::connectSlotsByName(AdjustAlignmentLargeForm);
    } // setupUi

    void retranslateUi(QWidget *AdjustAlignmentLargeForm)
    {
        AdjustAlignmentLargeForm->setWindowTitle(QCoreApplication::translate("AdjustAlignmentLargeForm", "Adjust alignment", nullptr));
        label->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "X Search dot", nullptr));
        pushButtonHistogramX->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "Histogram-X", nullptr));
        pushButtonSetOne->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "Set in this point", nullptr));
        pushButtonSetAll->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "Set to all points", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "Close", nullptr));
        pushButtonHistogramY->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "Histogram-Y", nullptr));
        label_2->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "length", nullptr));
        label_3->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "Y Search dot", nullptr));
        label_4->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "length", nullptr));
        label_5->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "Count of Horizontal line", nullptr));
        label_6->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "Count of Horizontal line", nullptr));
        checkBoxJudgeWithBrDif->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "Judge with brightness difference", nullptr));
        label_7->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "X Search dot", nullptr));
        label_8->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "length", nullptr));
        label_9->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "length", nullptr));
        label_10->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "Y Search dot", nullptr));
        label_11->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "\346\234\200\345\210\235\343\201\256\346\216\242\347\264\242", nullptr));
        label_12->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "\357\274\222\347\225\252\347\233\256\343\201\256\346\216\242\347\264\242", nullptr));
        labelUnitName1->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "mm", nullptr));
        labelUnitName3->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "mm", nullptr));
        labelUnitName2->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "mm", nullptr));
        labelUnitName4->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "mm", nullptr));
        label_40->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\343\203\220\343\203\251\343\201\244\343\201\215\343\202\260\343\203\251\343\203\225", nullptr));
        checkBoxCharacterMode->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "Search in small characters", nullptr));
        label_13->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "\346\216\242\347\264\242\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        labelSelectedLayer->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "0", nullptr));
        label_15->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "\350\274\235\345\272\246\343\201\227\343\201\215\343\201\204\345\200\244 (-1:\350\207\252\345\213\225\350\250\255\345\256\232)", nullptr));
        label_16->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "\347\217\276\345\234\250\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        label_17->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "\347\217\276\345\234\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        labelThresholdColor->setText(QCoreApplication::translate("AdjustAlignmentLargeForm", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdjustAlignmentLargeForm: public Ui_AdjustAlignmentLargeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADJUSTALIGNMENTLARGEFORM_H
