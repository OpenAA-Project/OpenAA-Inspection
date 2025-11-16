/********************************************************************************
** Form generated from reading UI file 'AlignmentFlexAreaImagePanelDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALIGNMENTFLEXAREAIMAGEPANELDIALOG_H
#define UI_ALIGNMENTFLEXAREAIMAGEPANELDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_AlignmentFlexAreaImagePanelDialog
{
public:
    QLabel *labelUnitName_2;
    QDoubleSpinBox *doubleSpinBoxGlobalSearchDotUnit;
    QLabel *label;
    QSpinBox *spinBoxGlobalSearchDot;
    QPushButton *pushButtonSetAll;
    QLabel *label_2;
    QLabel *labelUnitName;
    QSpinBox *spinBoxSearchDot;
    QDoubleSpinBox *doubleSpinBoxSearchDotUnit;
    QLabel *label_3;
    QPushButton *pushButtonSetOne;
    QCheckBox *checkBoxKeepBW;
    QPushButton *pushButtonClose;
    QLabel *label_4;
    QLineEdit *lineEditItemID;

    void setupUi(QDialog *AlignmentFlexAreaImagePanelDialog)
    {
        if (AlignmentFlexAreaImagePanelDialog->objectName().isEmpty())
            AlignmentFlexAreaImagePanelDialog->setObjectName("AlignmentFlexAreaImagePanelDialog");
        AlignmentFlexAreaImagePanelDialog->resize(332, 262);
        labelUnitName_2 = new QLabel(AlignmentFlexAreaImagePanelDialog);
        labelUnitName_2->setObjectName("labelUnitName_2");
        labelUnitName_2->setGeometry(QRect(240, 70, 51, 21));
        labelUnitName_2->setFrameShape(QFrame::NoFrame);
        labelUnitName_2->setFrameShadow(QFrame::Plain);
        doubleSpinBoxGlobalSearchDotUnit = new QDoubleSpinBox(AlignmentFlexAreaImagePanelDialog);
        doubleSpinBoxGlobalSearchDotUnit->setObjectName("doubleSpinBoxGlobalSearchDotUnit");
        doubleSpinBoxGlobalSearchDotUnit->setGeometry(QRect(120, 71, 111, 22));
        QPalette palette;
        QBrush brush(QColor(255, 170, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxGlobalSearchDotUnit->setPalette(palette);
        doubleSpinBoxGlobalSearchDotUnit->setMaximum(99999999.000000000000000);
        label = new QLabel(AlignmentFlexAreaImagePanelDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 100, 101, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        spinBoxGlobalSearchDot = new QSpinBox(AlignmentFlexAreaImagePanelDialog);
        spinBoxGlobalSearchDot->setObjectName("spinBoxGlobalSearchDot");
        spinBoxGlobalSearchDot->setGeometry(QRect(10, 71, 91, 22));
        spinBoxGlobalSearchDot->setMaximum(999999);
        pushButtonSetAll = new QPushButton(AlignmentFlexAreaImagePanelDialog);
        pushButtonSetAll->setObjectName("pushButtonSetAll");
        pushButtonSetAll->setGeometry(QRect(160, 180, 161, 31));
        label_2 = new QLabel(AlignmentFlexAreaImagePanelDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(120, 100, 111, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        labelUnitName = new QLabel(AlignmentFlexAreaImagePanelDialog);
        labelUnitName->setObjectName("labelUnitName");
        labelUnitName->setGeometry(QRect(240, 120, 51, 21));
        labelUnitName->setFrameShape(QFrame::NoFrame);
        labelUnitName->setFrameShadow(QFrame::Plain);
        spinBoxSearchDot = new QSpinBox(AlignmentFlexAreaImagePanelDialog);
        spinBoxSearchDot->setObjectName("spinBoxSearchDot");
        spinBoxSearchDot->setGeometry(QRect(10, 121, 91, 22));
        spinBoxSearchDot->setMaximum(999999);
        doubleSpinBoxSearchDotUnit = new QDoubleSpinBox(AlignmentFlexAreaImagePanelDialog);
        doubleSpinBoxSearchDotUnit->setObjectName("doubleSpinBoxSearchDotUnit");
        doubleSpinBoxSearchDotUnit->setGeometry(QRect(120, 121, 111, 22));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxSearchDotUnit->setPalette(palette1);
        doubleSpinBoxSearchDotUnit->setMaximum(99999999.000000000000000);
        label_3 = new QLabel(AlignmentFlexAreaImagePanelDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 50, 221, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        pushButtonSetOne = new QPushButton(AlignmentFlexAreaImagePanelDialog);
        pushButtonSetOne->setObjectName("pushButtonSetOne");
        pushButtonSetOne->setGeometry(QRect(10, 180, 141, 31));
        checkBoxKeepBW = new QCheckBox(AlignmentFlexAreaImagePanelDialog);
        checkBoxKeepBW->setObjectName("checkBoxKeepBW");
        checkBoxKeepBW->setGeometry(QRect(20, 150, 291, 22));
        pushButtonClose = new QPushButton(AlignmentFlexAreaImagePanelDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(200, 220, 121, 31));
        label_4 = new QLabel(AlignmentFlexAreaImagePanelDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 10, 41, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        lineEditItemID = new QLineEdit(AlignmentFlexAreaImagePanelDialog);
        lineEditItemID->setObjectName("lineEditItemID");
        lineEditItemID->setGeometry(QRect(60, 10, 81, 24));
        QPalette palette2;
        QBrush brush2(QColor(0, 255, 255, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditItemID->setPalette(palette2);
        lineEditItemID->setReadOnly(true);

        retranslateUi(AlignmentFlexAreaImagePanelDialog);

        pushButtonClose->setDefault(true);


        QMetaObject::connectSlotsByName(AlignmentFlexAreaImagePanelDialog);
    } // setupUi

    void retranslateUi(QDialog *AlignmentFlexAreaImagePanelDialog)
    {
        AlignmentFlexAreaImagePanelDialog->setWindowTitle(QCoreApplication::translate("AlignmentFlexAreaImagePanelDialog", "Dialog", nullptr));
        labelUnitName_2->setText(QCoreApplication::translate("AlignmentFlexAreaImagePanelDialog", "mm", nullptr));
        label->setText(QCoreApplication::translate("AlignmentFlexAreaImagePanelDialog", "Search dot", nullptr));
        pushButtonSetAll->setText(QCoreApplication::translate("AlignmentFlexAreaImagePanelDialog", "Set to all points", nullptr));
        label_2->setText(QCoreApplication::translate("AlignmentFlexAreaImagePanelDialog", "Search length", nullptr));
        labelUnitName->setText(QCoreApplication::translate("AlignmentFlexAreaImagePanelDialog", "mm", nullptr));
        label_3->setText(QCoreApplication::translate("AlignmentFlexAreaImagePanelDialog", "Global search", nullptr));
        pushButtonSetOne->setText(QCoreApplication::translate("AlignmentFlexAreaImagePanelDialog", "Set in this point", nullptr));
        checkBoxKeepBW->setText(QCoreApplication::translate("AlignmentFlexAreaImagePanelDialog", "Keep Block/White", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("AlignmentFlexAreaImagePanelDialog", "Close", nullptr));
        label_4->setText(QCoreApplication::translate("AlignmentFlexAreaImagePanelDialog", "ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AlignmentFlexAreaImagePanelDialog: public Ui_AlignmentFlexAreaImagePanelDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALIGNMENTFLEXAREAIMAGEPANELDIALOG_H
