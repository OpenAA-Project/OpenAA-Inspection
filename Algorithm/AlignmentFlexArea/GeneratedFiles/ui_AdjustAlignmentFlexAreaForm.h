/********************************************************************************
** Form generated from reading UI file 'AdjustAlignmentFlexAreaForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADJUSTALIGNMENTFLEXAREAFORM_H
#define UI_ADJUSTALIGNMENTFLEXAREAFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdjustAlignmentFlexAreaForm
{
public:
    QPushButton *pushButtonClose;
    QPushButton *pushButtonHistogramX;
    QSpinBox *spinBoxSearchDot;
    QPushButton *pushButtonSetAll;
    QLabel *label_2;
    QLabel *labelUnitName;
    QDoubleSpinBox *doubleSpinBoxSearchDotUnit;
    QLabel *label;
    QPushButton *pushButtonSetOne;
    QPushButton *pushButtonHistogramY;
    QLabel *label_3;
    QSpinBox *spinBoxGlobalSearchDot;
    QDoubleSpinBox *doubleSpinBoxGlobalSearchDotUnit;
    QLabel *labelUnitName_2;
    QCheckBox *checkBoxKeepBW;
    QLabel *label_23;
    QSpinBox *EditSmallSearch;
    QLabel *label_22;
    QDoubleSpinBox *doubleSpinBoxCloserRate;
    QPushButton *pushButtonSaveLibrary;
    QPushButton *pushButtonLoadLibrary;
    QDoubleSpinBox *doubleSpinBoxSmallSearchUnit;
    QLabel *labelUnitName_3;

    void setupUi(QWidget *AdjustAlignmentFlexAreaForm)
    {
        if (AdjustAlignmentFlexAreaForm->objectName().isEmpty())
            AdjustAlignmentFlexAreaForm->setObjectName("AdjustAlignmentFlexAreaForm");
        AdjustAlignmentFlexAreaForm->resize(317, 383);
        pushButtonClose = new QPushButton(AdjustAlignmentFlexAreaForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(230, 340, 75, 31));
        pushButtonHistogramX = new QPushButton(AdjustAlignmentFlexAreaForm);
        pushButtonHistogramX->setObjectName("pushButtonHistogramX");
        pushButtonHistogramX->setGeometry(QRect(10, 260, 141, 31));
        spinBoxSearchDot = new QSpinBox(AdjustAlignmentFlexAreaForm);
        spinBoxSearchDot->setObjectName("spinBoxSearchDot");
        spinBoxSearchDot->setGeometry(QRect(10, 81, 91, 22));
        spinBoxSearchDot->setMaximum(999999);
        pushButtonSetAll = new QPushButton(AdjustAlignmentFlexAreaForm);
        pushButtonSetAll->setObjectName("pushButtonSetAll");
        pushButtonSetAll->setGeometry(QRect(160, 220, 141, 31));
        label_2 = new QLabel(AdjustAlignmentFlexAreaForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(120, 60, 111, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        labelUnitName = new QLabel(AdjustAlignmentFlexAreaForm);
        labelUnitName->setObjectName("labelUnitName");
        labelUnitName->setGeometry(QRect(240, 80, 51, 21));
        labelUnitName->setFrameShape(QFrame::NoFrame);
        labelUnitName->setFrameShadow(QFrame::Plain);
        doubleSpinBoxSearchDotUnit = new QDoubleSpinBox(AdjustAlignmentFlexAreaForm);
        doubleSpinBoxSearchDotUnit->setObjectName("doubleSpinBoxSearchDotUnit");
        doubleSpinBoxSearchDotUnit->setGeometry(QRect(120, 81, 111, 22));
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
        label = new QLabel(AdjustAlignmentFlexAreaForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 60, 101, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        pushButtonSetOne = new QPushButton(AdjustAlignmentFlexAreaForm);
        pushButtonSetOne->setObjectName("pushButtonSetOne");
        pushButtonSetOne->setGeometry(QRect(10, 220, 141, 31));
        pushButtonHistogramY = new QPushButton(AdjustAlignmentFlexAreaForm);
        pushButtonHistogramY->setObjectName("pushButtonHistogramY");
        pushButtonHistogramY->setGeometry(QRect(160, 260, 141, 31));
        label_3 = new QLabel(AdjustAlignmentFlexAreaForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 221, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        spinBoxGlobalSearchDot = new QSpinBox(AdjustAlignmentFlexAreaForm);
        spinBoxGlobalSearchDot->setObjectName("spinBoxGlobalSearchDot");
        spinBoxGlobalSearchDot->setGeometry(QRect(10, 31, 91, 22));
        spinBoxGlobalSearchDot->setMaximum(999999);
        doubleSpinBoxGlobalSearchDotUnit = new QDoubleSpinBox(AdjustAlignmentFlexAreaForm);
        doubleSpinBoxGlobalSearchDotUnit->setObjectName("doubleSpinBoxGlobalSearchDotUnit");
        doubleSpinBoxGlobalSearchDotUnit->setGeometry(QRect(120, 31, 111, 22));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxGlobalSearchDotUnit->setPalette(palette1);
        doubleSpinBoxGlobalSearchDotUnit->setMaximum(99999999.000000000000000);
        labelUnitName_2 = new QLabel(AdjustAlignmentFlexAreaForm);
        labelUnitName_2->setObjectName("labelUnitName_2");
        labelUnitName_2->setGeometry(QRect(240, 30, 51, 21));
        labelUnitName_2->setFrameShape(QFrame::NoFrame);
        labelUnitName_2->setFrameShadow(QFrame::Plain);
        checkBoxKeepBW = new QCheckBox(AdjustAlignmentFlexAreaForm);
        checkBoxKeepBW->setObjectName("checkBoxKeepBW");
        checkBoxKeepBW->setGeometry(QRect(20, 190, 291, 22));
        label_23 = new QLabel(AdjustAlignmentFlexAreaForm);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(10, 110, 221, 21));
        label_23->setFrameShape(QFrame::Panel);
        label_23->setFrameShadow(QFrame::Sunken);
        label_23->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSmallSearch = new QSpinBox(AdjustAlignmentFlexAreaForm);
        EditSmallSearch->setObjectName("EditSmallSearch");
        EditSmallSearch->setGeometry(QRect(10, 130, 91, 22));
        EditSmallSearch->setMinimum(0);
        EditSmallSearch->setMaximum(99999999);
        label_22 = new QLabel(AdjustAlignmentFlexAreaForm);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(10, 160, 201, 21));
        label_22->setFrameShape(QFrame::Panel);
        label_22->setFrameShadow(QFrame::Sunken);
        label_22->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxCloserRate = new QDoubleSpinBox(AdjustAlignmentFlexAreaForm);
        doubleSpinBoxCloserRate->setObjectName("doubleSpinBoxCloserRate");
        doubleSpinBoxCloserRate->setGeometry(QRect(220, 160, 81, 24));
        doubleSpinBoxCloserRate->setDecimals(3);
        doubleSpinBoxCloserRate->setMaximum(1.000000000000000);
        pushButtonSaveLibrary = new QPushButton(AdjustAlignmentFlexAreaForm);
        pushButtonSaveLibrary->setObjectName("pushButtonSaveLibrary");
        pushButtonSaveLibrary->setGeometry(QRect(10, 300, 141, 31));
        pushButtonLoadLibrary = new QPushButton(AdjustAlignmentFlexAreaForm);
        pushButtonLoadLibrary->setObjectName("pushButtonLoadLibrary");
        pushButtonLoadLibrary->setGeometry(QRect(160, 300, 141, 31));
        doubleSpinBoxSmallSearchUnit = new QDoubleSpinBox(AdjustAlignmentFlexAreaForm);
        doubleSpinBoxSmallSearchUnit->setObjectName("doubleSpinBoxSmallSearchUnit");
        doubleSpinBoxSmallSearchUnit->setGeometry(QRect(120, 130, 111, 22));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxSmallSearchUnit->setPalette(palette2);
        doubleSpinBoxSmallSearchUnit->setMaximum(99999999.000000000000000);
        labelUnitName_3 = new QLabel(AdjustAlignmentFlexAreaForm);
        labelUnitName_3->setObjectName("labelUnitName_3");
        labelUnitName_3->setGeometry(QRect(240, 130, 51, 21));
        labelUnitName_3->setFrameShape(QFrame::NoFrame);
        labelUnitName_3->setFrameShadow(QFrame::Plain);

        retranslateUi(AdjustAlignmentFlexAreaForm);

        pushButtonClose->setDefault(true);


        QMetaObject::connectSlotsByName(AdjustAlignmentFlexAreaForm);
    } // setupUi

    void retranslateUi(QWidget *AdjustAlignmentFlexAreaForm)
    {
        AdjustAlignmentFlexAreaForm->setWindowTitle(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "Form", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "Close", nullptr));
        pushButtonHistogramX->setText(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "Histogram-X", nullptr));
        pushButtonSetAll->setText(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "Set to all points", nullptr));
        label_2->setText(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "Search length", nullptr));
        labelUnitName->setText(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "mm", nullptr));
        label->setText(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "Search dot", nullptr));
        pushButtonSetOne->setText(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "Set in this point", nullptr));
        pushButtonHistogramY->setText(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "Histogram-Y", nullptr));
        label_3->setText(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "Global search", nullptr));
        labelUnitName_2->setText(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "mm", nullptr));
        checkBoxKeepBW->setText(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "Keep Block/White", nullptr));
        label_23->setText(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "Small search dot", nullptr));
        label_22->setText(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "Closer rate", nullptr));
        pushButtonSaveLibrary->setText(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "Save to library", nullptr));
        pushButtonLoadLibrary->setText(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "Load from library", nullptr));
        labelUnitName_3->setText(QCoreApplication::translate("AdjustAlignmentFlexAreaForm", "mm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdjustAlignmentFlexAreaForm: public Ui_AdjustAlignmentFlexAreaForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADJUSTALIGNMENTFLEXAREAFORM_H
