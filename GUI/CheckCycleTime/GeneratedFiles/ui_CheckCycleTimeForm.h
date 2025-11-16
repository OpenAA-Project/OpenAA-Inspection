/********************************************************************************
** Form generated from reading UI file 'CheckCycleTimeForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKCYCLETIMEFORM_H
#define UI_CHECKCYCLETIMEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_CheckCycleTimeForm
{
public:
    QDoubleSpinBox *doubleSpinBoxSettingTime;
    QDoubleSpinBox *doubleSpinBoxCurrentCycleTime;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButtonSet;
    QDoubleSpinBox *doubleSpinBoxSettingError;
    QLabel *label_3;

    void setupUi(GUIFormBase *CheckCycleTimeForm)
    {
        if (CheckCycleTimeForm->objectName().isEmpty())
            CheckCycleTimeForm->setObjectName("CheckCycleTimeForm");
        CheckCycleTimeForm->resize(221, 65);
        doubleSpinBoxSettingTime = new QDoubleSpinBox(CheckCycleTimeForm);
        doubleSpinBoxSettingTime->setObjectName("doubleSpinBoxSettingTime");
        doubleSpinBoxSettingTime->setGeometry(QRect(90, 0, 62, 22));
        doubleSpinBoxCurrentCycleTime = new QDoubleSpinBox(CheckCycleTimeForm);
        doubleSpinBoxCurrentCycleTime->setObjectName("doubleSpinBoxCurrentCycleTime");
        doubleSpinBoxCurrentCycleTime->setGeometry(QRect(90, 20, 62, 22));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(212, 208, 200, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxCurrentCycleTime->setPalette(palette);
        doubleSpinBoxCurrentCycleTime->setReadOnly(true);
        label = new QLabel(CheckCycleTimeForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 71, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(CheckCycleTimeForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 20, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        pushButtonSet = new QPushButton(CheckCycleTimeForm);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(160, 10, 51, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSet->setIcon(icon);
        doubleSpinBoxSettingError = new QDoubleSpinBox(CheckCycleTimeForm);
        doubleSpinBoxSettingError->setObjectName("doubleSpinBoxSettingError");
        doubleSpinBoxSettingError->setGeometry(QRect(90, 40, 62, 22));
        label_3 = new QLabel(CheckCycleTimeForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 40, 71, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);

        retranslateUi(CheckCycleTimeForm);

        QMetaObject::connectSlotsByName(CheckCycleTimeForm);
    } // setupUi

    void retranslateUi(GUIFormBase *CheckCycleTimeForm)
    {
        CheckCycleTimeForm->setWindowTitle(QCoreApplication::translate("CheckCycleTimeForm", "Check CycleTime", nullptr));
        label->setText(QCoreApplication::translate("CheckCycleTimeForm", "SettingTime", nullptr));
        label_2->setText(QCoreApplication::translate("CheckCycleTimeForm", "CurrentCycle", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("CheckCycleTimeForm", "Set", nullptr));
        label_3->setText(QCoreApplication::translate("CheckCycleTimeForm", "Error time", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CheckCycleTimeForm: public Ui_CheckCycleTimeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKCYCLETIMEFORM_H
