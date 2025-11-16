/********************************************************************************
** Form generated from reading UI file 'ConfirmForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIRMFORM_H
#define UI_CONFIRMFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfirmForm
{
public:
    QLabel *labelShouldOK;
    QLabel *labelShouldNG;
    QScrollArea *scrollAreaShouldOK;
    QWidget *scrollAreaWidgetContents;
    QScrollArea *scrollAreaShouldNG;
    QWidget *scrollAreaWidgetContents_2;

    void setupUi(QWidget *ConfirmForm)
    {
        if (ConfirmForm->objectName().isEmpty())
            ConfirmForm->setObjectName("ConfirmForm");
        ConfirmForm->resize(840, 638);
        labelShouldOK = new QLabel(ConfirmForm);
        labelShouldOK->setObjectName("labelShouldOK");
        labelShouldOK->setGeometry(QRect(0, 0, 841, 31));
        QPalette palette;
        QBrush brush(QColor(0, 255, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        labelShouldOK->setPalette(palette);
        labelShouldOK->setAutoFillBackground(true);
        labelShouldOK->setFrameShape(QFrame::Panel);
        labelShouldOK->setFrameShadow(QFrame::Sunken);
        labelShouldOK->setAlignment(Qt::AlignCenter);
        labelShouldNG = new QLabel(ConfirmForm);
        labelShouldNG->setObjectName("labelShouldNG");
        labelShouldNG->setGeometry(QRect(0, 320, 841, 31));
        QPalette palette1;
        QBrush brush2(QColor(255, 0, 0, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush2);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush2);
        labelShouldNG->setPalette(palette1);
        labelShouldNG->setAutoFillBackground(true);
        labelShouldNG->setFrameShape(QFrame::Panel);
        labelShouldNG->setFrameShadow(QFrame::Sunken);
        labelShouldNG->setAlignment(Qt::AlignCenter);
        scrollAreaShouldOK = new QScrollArea(ConfirmForm);
        scrollAreaShouldOK->setObjectName("scrollAreaShouldOK");
        scrollAreaShouldOK->setGeometry(QRect(0, 30, 841, 281));
        scrollAreaShouldOK->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollAreaShouldOK->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        scrollAreaShouldOK->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 829, 279));
        scrollAreaShouldOK->setWidget(scrollAreaWidgetContents);
        scrollAreaShouldNG = new QScrollArea(ConfirmForm);
        scrollAreaShouldNG->setObjectName("scrollAreaShouldNG");
        scrollAreaShouldNG->setGeometry(QRect(0, 350, 841, 281));
        scrollAreaShouldNG->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollAreaShouldNG->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        scrollAreaShouldNG->setWidgetResizable(false);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 829, 279));
        scrollAreaShouldNG->setWidget(scrollAreaWidgetContents_2);

        retranslateUi(ConfirmForm);

        QMetaObject::connectSlotsByName(ConfirmForm);
    } // setupUi

    void retranslateUi(QWidget *ConfirmForm)
    {
        ConfirmForm->setWindowTitle(QCoreApplication::translate("ConfirmForm", "Confirm panel", nullptr));
        labelShouldOK->setText(QCoreApplication::translate("ConfirmForm", "OK\345\210\244\345\256\232\343\201\231\343\202\213\343\201\271\343\201\215", nullptr));
        labelShouldNG->setText(QCoreApplication::translate("ConfirmForm", "NG\345\210\244\345\256\232\343\201\231\343\202\213\343\201\271\343\201\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfirmForm: public Ui_ConfirmForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIRMFORM_H
