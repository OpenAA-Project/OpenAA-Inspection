/********************************************************************************
** Form generated from reading UI file 'PanelOffsetVRSForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANELOFFSETVRSFORM_H
#define UI_PANELOFFSETVRSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PanelOffsetVRSForm
{
public:
    QPushButton *pushButtonSet;
    QFrame *frame_4;
    QLabel *label_13;
    QLabel *label_14;
    QDoubleSpinBox *doubleSpinBoxFrontY;
    QLabel *label_16;
    QDoubleSpinBox *doubleSpinBoxFrontX;
    QFrame *frame_5;
    QLabel *label_15;
    QLabel *label_17;
    QDoubleSpinBox *doubleSpinBoxBackY;
    QLabel *label_18;
    QDoubleSpinBox *doubleSpinBoxBackX;

    void setupUi(GUIFormBase *PanelOffsetVRSForm)
    {
        if (PanelOffsetVRSForm->objectName().isEmpty())
            PanelOffsetVRSForm->setObjectName(QString::fromUtf8("PanelOffsetVRSForm"));
        PanelOffsetVRSForm->resize(336, 122);
        pushButtonSet = new QPushButton(PanelOffsetVRSForm);
        pushButtonSet->setObjectName(QString::fromUtf8("pushButtonSet"));
        pushButtonSet->setGeometry(QRect(250, 90, 81, 28));
        frame_4 = new QFrame(PanelOffsetVRSForm);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(0, 0, 161, 81));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        label_13 = new QLabel(frame_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(0, 0, 161, 16));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter);
        label_14 = new QLabel(frame_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 47, 51, 21));
        doubleSpinBoxFrontY = new QDoubleSpinBox(frame_4);
        doubleSpinBoxFrontY->setObjectName(QString::fromUtf8("doubleSpinBoxFrontY"));
        doubleSpinBoxFrontY->setGeometry(QRect(70, 44, 81, 22));
        doubleSpinBoxFrontY->setMinimum(-99999999.000000000000000);
        doubleSpinBoxFrontY->setMaximum(99999999.000000000000000);
        label_16 = new QLabel(frame_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 23, 51, 21));
        doubleSpinBoxFrontX = new QDoubleSpinBox(frame_4);
        doubleSpinBoxFrontX->setObjectName(QString::fromUtf8("doubleSpinBoxFrontX"));
        doubleSpinBoxFrontX->setGeometry(QRect(70, 20, 81, 22));
        doubleSpinBoxFrontX->setMinimum(-99999999.000000000000000);
        doubleSpinBoxFrontX->setMaximum(99999999.000000000000000);
        frame_5 = new QFrame(PanelOffsetVRSForm);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setGeometry(QRect(170, 0, 161, 81));
        frame_5->setFrameShape(QFrame::Panel);
        frame_5->setFrameShadow(QFrame::Sunken);
        label_15 = new QLabel(frame_5);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(0, 0, 161, 16));
        label_15->setFrameShape(QFrame::Panel);
        label_15->setFrameShadow(QFrame::Sunken);
        label_15->setAlignment(Qt::AlignCenter);
        label_17 = new QLabel(frame_5);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 47, 51, 21));
        doubleSpinBoxBackY = new QDoubleSpinBox(frame_5);
        doubleSpinBoxBackY->setObjectName(QString::fromUtf8("doubleSpinBoxBackY"));
        doubleSpinBoxBackY->setGeometry(QRect(70, 44, 81, 22));
        doubleSpinBoxBackY->setMinimum(-99999999.000000000000000);
        doubleSpinBoxBackY->setMaximum(99999999.000000000000000);
        label_18 = new QLabel(frame_5);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(10, 23, 51, 21));
        doubleSpinBoxBackX = new QDoubleSpinBox(frame_5);
        doubleSpinBoxBackX->setObjectName(QString::fromUtf8("doubleSpinBoxBackX"));
        doubleSpinBoxBackX->setGeometry(QRect(70, 20, 81, 22));
        doubleSpinBoxBackX->setMinimum(-99999999.000000000000000);
        doubleSpinBoxBackX->setMaximum(99999999.000000000000000);

        retranslateUi(PanelOffsetVRSForm);

        QMetaObject::connectSlotsByName(PanelOffsetVRSForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PanelOffsetVRSForm)
    {
        PanelOffsetVRSForm->setWindowTitle(QCoreApplication::translate("PanelOffsetVRSForm", "Form", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("PanelOffsetVRSForm", "Set", nullptr));
        label_13->setText(QCoreApplication::translate("PanelOffsetVRSForm", "Front", nullptr));
        label_14->setText(QCoreApplication::translate("PanelOffsetVRSForm", "Y (mm)", nullptr));
        label_16->setText(QCoreApplication::translate("PanelOffsetVRSForm", "X(mm)", nullptr));
        label_15->setText(QCoreApplication::translate("PanelOffsetVRSForm", "Back", nullptr));
        label_17->setText(QCoreApplication::translate("PanelOffsetVRSForm", "Y (mm)", nullptr));
        label_18->setText(QCoreApplication::translate("PanelOffsetVRSForm", "X(mm)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PanelOffsetVRSForm: public Ui_PanelOffsetVRSForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANELOFFSETVRSFORM_H
