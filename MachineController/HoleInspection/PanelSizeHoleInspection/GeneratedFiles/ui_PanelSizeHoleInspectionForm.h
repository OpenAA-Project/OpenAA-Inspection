/********************************************************************************
** Form generated from reading UI file 'PanelSizeHoleInspectionForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANELSIZEHOLEINSPECTIONFORM_H
#define UI_PANELSIZEHOLEINSPECTIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PanelSizeHoleInspectionForm
{
public:
    QPushButton *pushButtonSet;
    QDoubleSpinBox *doubleSpinBoxX;
    QLabel *label_ScanCount;
    QDoubleSpinBox *doubleSpinBoxY;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_LineCount;
    QComboBox *comboBoxLength;

    void setupUi(GUIFormBase *PanelSizeHoleInspectionForm)
    {
        if (PanelSizeHoleInspectionForm->objectName().isEmpty())
            PanelSizeHoleInspectionForm->setObjectName(QString::fromUtf8("PanelSizeHoleInspectionForm"));
        PanelSizeHoleInspectionForm->resize(489, 56);
        pushButtonSet = new QPushButton(PanelSizeHoleInspectionForm);
        pushButtonSet->setObjectName(QString::fromUtf8("pushButtonSet"));
        pushButtonSet->setGeometry(QRect(220, 10, 71, 41));
        doubleSpinBoxX = new QDoubleSpinBox(PanelSizeHoleInspectionForm);
        doubleSpinBoxX->setObjectName(QString::fromUtf8("doubleSpinBoxX"));
        doubleSpinBoxX->setGeometry(QRect(120, 0, 81, 22));
        QFont font;
        font.setPointSize(12);
        doubleSpinBoxX->setFont(font);
        doubleSpinBoxX->setMaximum(999.990000000000009);
        label_ScanCount = new QLabel(PanelSizeHoleInspectionForm);
        label_ScanCount->setObjectName(QString::fromUtf8("label_ScanCount"));
        label_ScanCount->setGeometry(QRect(420, 30, 61, 21));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        label_ScanCount->setPalette(palette);
        QFont font1;
        font1.setPointSize(10);
        label_ScanCount->setFont(font1);
        label_ScanCount->setAutoFillBackground(true);
        label_ScanCount->setFrameShape(QFrame::Panel);
        label_ScanCount->setFrameShadow(QFrame::Sunken);
        doubleSpinBoxY = new QDoubleSpinBox(PanelSizeHoleInspectionForm);
        doubleSpinBoxY->setObjectName(QString::fromUtf8("doubleSpinBoxY"));
        doubleSpinBoxY->setGeometry(QRect(120, 30, 81, 22));
        doubleSpinBoxY->setFont(font);
        doubleSpinBoxY->setMaximum(9999.989999999999782);
        label_5 = new QLabel(PanelSizeHoleInspectionForm);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(300, 10, 111, 21));
        label_5->setFont(font1);
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(PanelSizeHoleInspectionForm);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(300, 30, 111, 21));
        label_6->setFont(font1);
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(PanelSizeHoleInspectionForm);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(0, 30, 111, 21));
        label_7->setFont(font1);
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_8 = new QLabel(PanelSizeHoleInspectionForm);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(0, 0, 111, 21));
        label_8->setFont(font1);
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_LineCount = new QLabel(PanelSizeHoleInspectionForm);
        label_LineCount->setObjectName(QString::fromUtf8("label_LineCount"));
        label_LineCount->setGeometry(QRect(420, 10, 61, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Button, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        label_LineCount->setPalette(palette1);
        label_LineCount->setFont(font1);
        label_LineCount->setAutoFillBackground(true);
        label_LineCount->setFrameShape(QFrame::Panel);
        label_LineCount->setFrameShadow(QFrame::Sunken);
        comboBoxLength = new QComboBox(PanelSizeHoleInspectionForm);
        comboBoxLength->addItem(QString());
        comboBoxLength->addItem(QString());
        comboBoxLength->addItem(QString());
        comboBoxLength->addItem(QString());
        comboBoxLength->addItem(QString());
        comboBoxLength->addItem(QString());
        comboBoxLength->addItem(QString());
        comboBoxLength->addItem(QString());
        comboBoxLength->setObjectName(QString::fromUtf8("comboBoxLength"));
        comboBoxLength->setGeometry(QRect(120, 30, 92, 24));

        retranslateUi(PanelSizeHoleInspectionForm);

        QMetaObject::connectSlotsByName(PanelSizeHoleInspectionForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PanelSizeHoleInspectionForm)
    {
        PanelSizeHoleInspectionForm->setWindowTitle(QCoreApplication::translate("PanelSizeHoleInspectionForm", "Form", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("PanelSizeHoleInspectionForm", "Set", nullptr));
        label_ScanCount->setText(QCoreApplication::translate("PanelSizeHoleInspectionForm", "12345", nullptr));
        label_5->setText(QCoreApplication::translate("PanelSizeHoleInspectionForm", "LineCount", nullptr));
        label_6->setText(QCoreApplication::translate("PanelSizeHoleInspectionForm", "ScanCount", nullptr));
        label_7->setText(QCoreApplication::translate("PanelSizeHoleInspectionForm", "Length(Y size)", nullptr));
        label_8->setText(QCoreApplication::translate("PanelSizeHoleInspectionForm", "Width(X size)", nullptr));
        label_LineCount->setText(QCoreApplication::translate("PanelSizeHoleInspectionForm", "12345", nullptr));
        comboBoxLength->setItemText(0, QCoreApplication::translate("PanelSizeHoleInspectionForm", "80.0mm", nullptr));
        comboBoxLength->setItemText(1, QCoreApplication::translate("PanelSizeHoleInspectionForm", "160.0mm", nullptr));
        comboBoxLength->setItemText(2, QCoreApplication::translate("PanelSizeHoleInspectionForm", "240.0mm", nullptr));
        comboBoxLength->setItemText(3, QCoreApplication::translate("PanelSizeHoleInspectionForm", "320.0mm", nullptr));
        comboBoxLength->setItemText(4, QCoreApplication::translate("PanelSizeHoleInspectionForm", "400.0mm", nullptr));
        comboBoxLength->setItemText(5, QCoreApplication::translate("PanelSizeHoleInspectionForm", "480.0mm", nullptr));
        comboBoxLength->setItemText(6, QCoreApplication::translate("PanelSizeHoleInspectionForm", "560.0mm", nullptr));
        comboBoxLength->setItemText(7, QCoreApplication::translate("PanelSizeHoleInspectionForm", "620.0mm", nullptr));

    } // retranslateUi

};

namespace Ui {
    class PanelSizeHoleInspectionForm: public Ui_PanelSizeHoleInspectionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANELSIZEHOLEINSPECTIONFORM_H
