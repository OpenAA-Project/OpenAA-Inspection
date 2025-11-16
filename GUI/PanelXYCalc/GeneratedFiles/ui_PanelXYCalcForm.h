/********************************************************************************
** Form generated from reading UI file 'PanelXYCalcForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANELXYCALCFORM_H
#define UI_PANELXYCALCFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PanelXYCalcForm
{
public:
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxX;
    QPushButton *pushButtonSet;
    QDoubleSpinBox *doubleSpinBoxY;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_ScanCount;
    QLabel *label_LineCount;

    void setupUi(GUIFormBase *PanelXYCalcForm)
    {
        if (PanelXYCalcForm->objectName().isEmpty())
            PanelXYCalcForm->setObjectName("PanelXYCalcForm");
        PanelXYCalcForm->resize(499, 44);
        label = new QLabel(PanelXYCalcForm);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 111, 21));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(PanelXYCalcForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 20, 111, 21));
        label_2->setFont(font);
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        doubleSpinBoxX = new QDoubleSpinBox(PanelXYCalcForm);
        doubleSpinBoxX->setObjectName("doubleSpinBoxX");
        doubleSpinBoxX->setGeometry(QRect(120, 0, 81, 22));
        QFont font1;
        font1.setPointSize(12);
        doubleSpinBoxX->setFont(font1);
        doubleSpinBoxX->setMaximum(999.990000000000009);
        pushButtonSet = new QPushButton(PanelXYCalcForm);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(200, 0, 71, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSet->setIcon(icon);
        doubleSpinBoxY = new QDoubleSpinBox(PanelXYCalcForm);
        doubleSpinBoxY->setObjectName("doubleSpinBoxY");
        doubleSpinBoxY->setGeometry(QRect(120, 20, 81, 22));
        doubleSpinBoxY->setFont(font1);
        doubleSpinBoxY->setMaximum(9999.989999999999782);
        label_3 = new QLabel(PanelXYCalcForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(300, 0, 111, 21));
        label_3->setFont(font);
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(PanelXYCalcForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(300, 20, 111, 21));
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_ScanCount = new QLabel(PanelXYCalcForm);
        label_ScanCount->setObjectName("label_ScanCount");
        label_ScanCount->setGeometry(QRect(420, 20, 61, 21));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::BrightText, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::BrightText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::BrightText, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        label_ScanCount->setPalette(palette);
        label_ScanCount->setFont(font);
        label_ScanCount->setAutoFillBackground(true);
        label_ScanCount->setFrameShape(QFrame::Panel);
        label_ScanCount->setFrameShadow(QFrame::Sunken);
        label_LineCount = new QLabel(PanelXYCalcForm);
        label_LineCount->setObjectName("label_LineCount");
        label_LineCount->setGeometry(QRect(420, 0, 61, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::BrightText, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::BrightText, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::BrightText, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        label_LineCount->setPalette(palette1);
        label_LineCount->setFont(font);
        label_LineCount->setAutoFillBackground(true);
        label_LineCount->setFrameShape(QFrame::Panel);
        label_LineCount->setFrameShadow(QFrame::Sunken);

        retranslateUi(PanelXYCalcForm);

        QMetaObject::connectSlotsByName(PanelXYCalcForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PanelXYCalcForm)
    {
        PanelXYCalcForm->setWindowTitle(QCoreApplication::translate("PanelXYCalcForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("PanelXYCalcForm", "Width(X size)", nullptr));
        label_2->setText(QCoreApplication::translate("PanelXYCalcForm", "Length(Y size)", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("PanelXYCalcForm", "Set", nullptr));
        label_3->setText(QCoreApplication::translate("PanelXYCalcForm", "LineCount", nullptr));
        label_4->setText(QCoreApplication::translate("PanelXYCalcForm", "ScanCount", nullptr));
        label_ScanCount->setText(QCoreApplication::translate("PanelXYCalcForm", "12345", nullptr));
        label_LineCount->setText(QCoreApplication::translate("PanelXYCalcForm", "12345", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PanelXYCalcForm: public Ui_PanelXYCalcForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANELXYCALCFORM_H
