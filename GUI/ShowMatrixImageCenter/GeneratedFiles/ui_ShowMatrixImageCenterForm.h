/********************************************************************************
** Form generated from reading UI file 'ShowMatrixImageCenterForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWMATRIXIMAGECENTERFORM_H
#define UI_SHOWMATRIXIMAGECENTERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ShowMatrixImageCenterForm
{
public:
    QLabel *label;
    QSpinBox *spinBoxCenterX;
    QLabel *label_2;
    QSpinBox *spinBoxCenterY;

    void setupUi(GUIFormBase *ShowMatrixImageCenterForm)
    {
        if (ShowMatrixImageCenterForm->objectName().isEmpty())
            ShowMatrixImageCenterForm->setObjectName("ShowMatrixImageCenterForm");
        ShowMatrixImageCenterForm->resize(180, 40);
        label = new QLabel(ShowMatrixImageCenterForm);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 91, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        spinBoxCenterX = new QSpinBox(ShowMatrixImageCenterForm);
        spinBoxCenterX->setObjectName("spinBoxCenterX");
        spinBoxCenterX->setGeometry(QRect(90, 0, 91, 22));
        spinBoxCenterX->setMinimum(-99999999);
        spinBoxCenterX->setMaximum(99999999);
        label_2 = new QLabel(ShowMatrixImageCenterForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 20, 91, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        spinBoxCenterY = new QSpinBox(ShowMatrixImageCenterForm);
        spinBoxCenterY->setObjectName("spinBoxCenterY");
        spinBoxCenterY->setGeometry(QRect(90, 20, 91, 22));
        spinBoxCenterY->setMinimum(-99999999);
        spinBoxCenterY->setMaximum(99999999);

        retranslateUi(ShowMatrixImageCenterForm);

        QMetaObject::connectSlotsByName(ShowMatrixImageCenterForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowMatrixImageCenterForm)
    {
        ShowMatrixImageCenterForm->setWindowTitle(QCoreApplication::translate("ShowMatrixImageCenterForm", "Show Matrix Image Center", nullptr));
        label->setText(QCoreApplication::translate("ShowMatrixImageCenterForm", "Center-X", nullptr));
        label_2->setText(QCoreApplication::translate("ShowMatrixImageCenterForm", "Center-X", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowMatrixImageCenterForm: public Ui_ShowMatrixImageCenterForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWMATRIXIMAGECENTERFORM_H
