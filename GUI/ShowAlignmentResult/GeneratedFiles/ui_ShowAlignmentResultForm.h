/********************************************************************************
** Form generated from reading UI file 'ShowAlignmentResultForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWALIGNMENTRESULTFORM_H
#define UI_SHOWALIGNMENTRESULTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ShowAlignmentResultForm
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditResultDx;
    QLineEdit *lineEditResultDy;
    QLineEdit *lineEditResultAngle;

    void setupUi(GUIFormBase *ShowAlignmentResultForm)
    {
        if (ShowAlignmentResultForm->objectName().isEmpty())
            ShowAlignmentResultForm->setObjectName("ShowAlignmentResultForm");
        ShowAlignmentResultForm->resize(238, 45);
        label = new QLabel(ShowAlignmentResultForm);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 75, 18));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(ShowAlignmentResultForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(80, 0, 75, 18));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(ShowAlignmentResultForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(160, 0, 75, 18));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        lineEditResultDx = new QLineEdit(ShowAlignmentResultForm);
        lineEditResultDx->setObjectName("lineEditResultDx");
        lineEditResultDx->setGeometry(QRect(0, 20, 71, 24));
        QPalette palette;
        QBrush brush(QColor(85, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditResultDx->setPalette(palette);
        lineEditResultDx->setReadOnly(true);
        lineEditResultDy = new QLineEdit(ShowAlignmentResultForm);
        lineEditResultDy->setObjectName("lineEditResultDy");
        lineEditResultDy->setGeometry(QRect(80, 20, 71, 24));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditResultDy->setPalette(palette1);
        lineEditResultDy->setReadOnly(true);
        lineEditResultAngle = new QLineEdit(ShowAlignmentResultForm);
        lineEditResultAngle->setObjectName("lineEditResultAngle");
        lineEditResultAngle->setGeometry(QRect(160, 20, 71, 24));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditResultAngle->setPalette(palette2);
        lineEditResultAngle->setReadOnly(true);

        retranslateUi(ShowAlignmentResultForm);

        QMetaObject::connectSlotsByName(ShowAlignmentResultForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowAlignmentResultForm)
    {
        ShowAlignmentResultForm->setWindowTitle(QCoreApplication::translate("ShowAlignmentResultForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("ShowAlignmentResultForm", "Dx", nullptr));
        label_2->setText(QCoreApplication::translate("ShowAlignmentResultForm", "Dy", nullptr));
        label_3->setText(QCoreApplication::translate("ShowAlignmentResultForm", "Angle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowAlignmentResultForm: public Ui_ShowAlignmentResultForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWALIGNMENTRESULTFORM_H
