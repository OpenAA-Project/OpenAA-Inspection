/********************************************************************************
** Form generated from reading UI file 'ZoomMechanicalPanelForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZOOMMECHANICALPANELFORM_H
#define UI_ZOOMMECHANICALPANELFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ZoomMechanicalPanelForm
{
public:
    QSlider *verticalSlider;
    QFrame *frame;
    QPushButton *pushButtonSetValue;
    QDoubleSpinBox *doubleSpinBoxValue;
    QLabel *label;

    void setupUi(GUIFormBase *ZoomMechanicalPanelForm)
    {
        if (ZoomMechanicalPanelForm->objectName().isEmpty())
            ZoomMechanicalPanelForm->setObjectName(QString::fromUtf8("ZoomMechanicalPanelForm"));
        ZoomMechanicalPanelForm->resize(87, 267);
        verticalSlider = new QSlider(ZoomMechanicalPanelForm);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setGeometry(QRect(30, 0, 22, 181));
        verticalSlider->setMaximum(100);
        verticalSlider->setOrientation(Qt::Vertical);
        frame = new QFrame(ZoomMechanicalPanelForm);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 190, 81, 71));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonSetValue = new QPushButton(frame);
        pushButtonSetValue->setObjectName(QString::fromUtf8("pushButtonSetValue"));
        pushButtonSetValue->setGeometry(QRect(20, 40, 61, 28));
        doubleSpinBoxValue = new QDoubleSpinBox(frame);
        doubleSpinBoxValue->setObjectName(QString::fromUtf8("doubleSpinBoxValue"));
        doubleSpinBoxValue->setGeometry(QRect(20, 10, 62, 22));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 10, 21, 21));
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(ZoomMechanicalPanelForm);

        QMetaObject::connectSlotsByName(ZoomMechanicalPanelForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ZoomMechanicalPanelForm)
    {
        ZoomMechanicalPanelForm->setWindowTitle(QCoreApplication::translate("ZoomMechanicalPanelForm", "Form", nullptr));
        pushButtonSetValue->setText(QCoreApplication::translate("ZoomMechanicalPanelForm", "Set", nullptr));
        label->setText(QCoreApplication::translate("ZoomMechanicalPanelForm", "X", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ZoomMechanicalPanelForm: public Ui_ZoomMechanicalPanelForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZOOMMECHANICALPANELFORM_H
