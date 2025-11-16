/********************************************************************************
** Form generated from reading UI file 'ShowResultSmallLotForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWRESULTSMALLLOTFORM_H
#define UI_SHOWRESULTSMALLLOTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowResultSmallLotForm
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditLotID;
    QLineEdit *lineEditLotName;
    QLineEdit *lineEditSubLot;
    QPushButton *pushButtonChange;
    QLabel *label_4;
    QLineEdit *lineEditNGCount;

    void setupUi(GUIFormBase *ShowResultSmallLotForm)
    {
        if (ShowResultSmallLotForm->objectName().isEmpty())
            ShowResultSmallLotForm->setObjectName("ShowResultSmallLotForm");
        ShowResultSmallLotForm->resize(276, 81);
        label = new QLabel(ShowResultSmallLotForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 81, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(ShowResultSmallLotForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 20, 81, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(ShowResultSmallLotForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 40, 81, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        lineEditLotID = new QLineEdit(ShowResultSmallLotForm);
        lineEditLotID->setObjectName("lineEditLotID");
        lineEditLotID->setGeometry(QRect(100, 0, 171, 20));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(212, 208, 200, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditLotID->setPalette(palette);
        QFont font;
        font.setPointSize(12);
        lineEditLotID->setFont(font);
        lineEditLotID->setReadOnly(true);
        lineEditLotName = new QLineEdit(ShowResultSmallLotForm);
        lineEditLotName->setObjectName("lineEditLotName");
        lineEditLotName->setGeometry(QRect(100, 20, 171, 20));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditLotName->setPalette(palette1);
        lineEditLotName->setFont(font);
        lineEditLotName->setReadOnly(true);
        lineEditSubLot = new QLineEdit(ShowResultSmallLotForm);
        lineEditSubLot->setObjectName("lineEditSubLot");
        lineEditSubLot->setGeometry(QRect(100, 40, 71, 20));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditSubLot->setPalette(palette2);
        lineEditSubLot->setFont(font);
        lineEditSubLot->setReadOnly(true);
        pushButtonChange = new QPushButton(ShowResultSmallLotForm);
        pushButtonChange->setObjectName("pushButtonChange");
        pushButtonChange->setGeometry(QRect(200, 50, 71, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Change.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonChange->setIcon(icon);
        label_4 = new QLabel(ShowResultSmallLotForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 60, 81, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        lineEditNGCount = new QLineEdit(ShowResultSmallLotForm);
        lineEditNGCount->setObjectName("lineEditNGCount");
        lineEditNGCount->setGeometry(QRect(100, 60, 71, 20));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditNGCount->setPalette(palette3);
        lineEditNGCount->setFont(font);
        lineEditNGCount->setReadOnly(true);

        retranslateUi(ShowResultSmallLotForm);

        QMetaObject::connectSlotsByName(ShowResultSmallLotForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowResultSmallLotForm)
    {
        ShowResultSmallLotForm->setWindowTitle(QCoreApplication::translate("ShowResultSmallLotForm", "Show Result SmallLot", nullptr));
        label->setText(QCoreApplication::translate("ShowResultSmallLotForm", "Lot ID", nullptr));
        label_2->setText(QCoreApplication::translate("ShowResultSmallLotForm", "Lot Name", nullptr));
        label_3->setText(QCoreApplication::translate("ShowResultSmallLotForm", "Sub-Lot ID", nullptr));
        pushButtonChange->setText(QCoreApplication::translate("ShowResultSmallLotForm", "Change", nullptr));
        label_4->setText(QCoreApplication::translate("ShowResultSmallLotForm", "NG count", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowResultSmallLotForm: public Ui_ShowResultSmallLotForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWRESULTSMALLLOTFORM_H
