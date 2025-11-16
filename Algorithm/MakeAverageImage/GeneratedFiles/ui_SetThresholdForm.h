/********************************************************************************
** Form generated from reading UI file 'SetThresholdForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTHRESHOLDFORM_H
#define UI_SETTHRESHOLDFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetThresholdForm
{
public:
    QPushButton *pushButtonClose;
    QLabel *label;
    QPushButton *pushButtonSetOne;
    QPushButton *pushButtonSetAll;
    QSpinBox *spinBoxSearchDot;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxSearchDotUnit;
    QLabel *labelUnitName;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBoxRotationDegree;
    QLabel *label_4;

    void setupUi(QWidget *SetThresholdForm)
    {
        if (SetThresholdForm->objectName().isEmpty())
            SetThresholdForm->setObjectName("SetThresholdForm");
        SetThresholdForm->resize(312, 210);
        pushButtonClose = new QPushButton(SetThresholdForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(230, 170, 75, 31));
        label = new QLabel(SetThresholdForm);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 10, 91, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        pushButtonSetOne = new QPushButton(SetThresholdForm);
        pushButtonSetOne->setObjectName("pushButtonSetOne");
        pushButtonSetOne->setGeometry(QRect(10, 130, 131, 31));
        pushButtonSetAll = new QPushButton(SetThresholdForm);
        pushButtonSetAll->setObjectName("pushButtonSetAll");
        pushButtonSetAll->setGeometry(QRect(150, 130, 151, 31));
        spinBoxSearchDot = new QSpinBox(SetThresholdForm);
        spinBoxSearchDot->setObjectName("spinBoxSearchDot");
        spinBoxSearchDot->setGeometry(QRect(0, 31, 91, 22));
        spinBoxSearchDot->setMaximum(999999);
        label_2 = new QLabel(SetThresholdForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 10, 111, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        doubleSpinBoxSearchDotUnit = new QDoubleSpinBox(SetThresholdForm);
        doubleSpinBoxSearchDotUnit->setObjectName("doubleSpinBoxSearchDotUnit");
        doubleSpinBoxSearchDotUnit->setGeometry(QRect(110, 31, 111, 22));
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
        labelUnitName = new QLabel(SetThresholdForm);
        labelUnitName->setObjectName("labelUnitName");
        labelUnitName->setGeometry(QRect(230, 30, 51, 21));
        labelUnitName->setFrameShape(QFrame::NoFrame);
        labelUnitName->setFrameShadow(QFrame::Plain);
        label_3 = new QLabel(SetThresholdForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 70, 121, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        doubleSpinBoxRotationDegree = new QDoubleSpinBox(SetThresholdForm);
        doubleSpinBoxRotationDegree->setObjectName("doubleSpinBoxRotationDegree");
        doubleSpinBoxRotationDegree->setGeometry(QRect(0, 90, 121, 24));
        doubleSpinBoxRotationDegree->setMaximum(90.000000000000000);
        label_4 = new QLabel(SetThresholdForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(130, 100, 75, 18));

        retranslateUi(SetThresholdForm);

        QMetaObject::connectSlotsByName(SetThresholdForm);
    } // setupUi

    void retranslateUi(QWidget *SetThresholdForm)
    {
        SetThresholdForm->setWindowTitle(QCoreApplication::translate("SetThresholdForm", "Form", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SetThresholdForm", "Close", nullptr));
        label->setText(QCoreApplication::translate("SetThresholdForm", "Search dot", nullptr));
        pushButtonSetOne->setText(QCoreApplication::translate("SetThresholdForm", "Set in this point", nullptr));
        pushButtonSetAll->setText(QCoreApplication::translate("SetThresholdForm", "Set to all points", nullptr));
        label_2->setText(QCoreApplication::translate("SetThresholdForm", "Search length", nullptr));
        labelUnitName->setText(QCoreApplication::translate("SetThresholdForm", "mm", nullptr));
        label_3->setText(QCoreApplication::translate("SetThresholdForm", "Rotation range", nullptr));
        label_4->setText(QCoreApplication::translate("SetThresholdForm", "Degree", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetThresholdForm: public Ui_SetThresholdForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTHRESHOLDFORM_H
