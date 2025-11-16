/********************************************************************************
** Form generated from reading UI file 'ShowSizePanelSeqForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWSIZEPANELSEQFORM_H
#define UI_SHOWSIZEPANELSEQFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowSizePanelSeqForm
{
public:
    QFrame *frame_4;
    QLabel *label_13;
    QLabel *label_14;
    QDoubleSpinBox *doubleSpinBoxWidth;
    QLabel *label_16;
    QDoubleSpinBox *doubleSpinBoxLength;
    QLabel *label_17;
    QDoubleSpinBox *doubleSpinBoxHeight;
    QPushButton *pushButtonChange;

    void setupUi(GUIFormBase *ShowSizePanelSeqForm)
    {
        if (ShowSizePanelSeqForm->objectName().isEmpty())
            ShowSizePanelSeqForm->setObjectName(QString::fromUtf8("ShowSizePanelSeqForm"));
        ShowSizePanelSeqForm->resize(238, 157);
        frame_4 = new QFrame(ShowSizePanelSeqForm);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(0, 0, 231, 111));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        label_13 = new QLabel(frame_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(0, 0, 231, 16));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter);
        label_14 = new QLabel(frame_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 52, 121, 16));
        doubleSpinBoxWidth = new QDoubleSpinBox(frame_4);
        doubleSpinBoxWidth->setObjectName(QString::fromUtf8("doubleSpinBoxWidth"));
        doubleSpinBoxWidth->setGeometry(QRect(140, 54, 81, 22));
        doubleSpinBoxWidth->setMinimum(10.000000000000000);
        doubleSpinBoxWidth->setMaximum(250.000000000000000);
        label_16 = new QLabel(frame_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 28, 121, 16));
        doubleSpinBoxLength = new QDoubleSpinBox(frame_4);
        doubleSpinBoxLength->setObjectName(QString::fromUtf8("doubleSpinBoxLength"));
        doubleSpinBoxLength->setGeometry(QRect(140, 30, 81, 22));
        doubleSpinBoxLength->setMinimum(10.000000000000000);
        doubleSpinBoxLength->setMaximum(350.000000000000000);
        label_17 = new QLabel(frame_4);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 76, 121, 16));
        doubleSpinBoxHeight = new QDoubleSpinBox(frame_4);
        doubleSpinBoxHeight->setObjectName(QString::fromUtf8("doubleSpinBoxHeight"));
        doubleSpinBoxHeight->setGeometry(QRect(140, 78, 81, 22));
        doubleSpinBoxHeight->setMinimum(-10.000000000000000);
        doubleSpinBoxHeight->setMaximum(50.000000000000000);
        pushButtonChange = new QPushButton(ShowSizePanelSeqForm);
        pushButtonChange->setObjectName(QString::fromUtf8("pushButtonChange"));
        pushButtonChange->setGeometry(QRect(140, 120, 81, 28));

        retranslateUi(ShowSizePanelSeqForm);

        QMetaObject::connectSlotsByName(ShowSizePanelSeqForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowSizePanelSeqForm)
    {
        ShowSizePanelSeqForm->setWindowTitle(QCoreApplication::translate("ShowSizePanelSeqForm", "Form", nullptr));
        label_13->setText(QCoreApplication::translate("ShowSizePanelSeqForm", "Size information", nullptr));
        label_14->setText(QCoreApplication::translate("ShowSizePanelSeqForm", "Width (mm)", nullptr));
        label_16->setText(QCoreApplication::translate("ShowSizePanelSeqForm", "Length (mm)", nullptr));
        label_17->setText(QCoreApplication::translate("ShowSizePanelSeqForm", "Thickness (mm)", nullptr));
        pushButtonChange->setText(QCoreApplication::translate("ShowSizePanelSeqForm", "Change", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowSizePanelSeqForm: public Ui_ShowSizePanelSeqForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWSIZEPANELSEQFORM_H
