/********************************************************************************
** Form generated from reading UI file 'IntegrationOutputControlButtonForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONOUTPUTCONTROLBUTTONFORM_H
#define UI_INTEGRATIONOUTPUTCONTROLBUTTONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_IntegrationOutputControlButtonForm
{
public:
    QStackedWidget *stackedWidget;
    QWidget *_FreeForResult;
    QLabel *label_FreeForResult;
    QWidget *_Abs_OK;
    QLabel *label_Abs_OK;
    QWidget *_Abs_NG;
    QLabel *label_Abs_NG;
    QWidget *_Abs_Blade;
    QLabel *label_Abs_Blade;

    void setupUi(GUIFormBase *IntegrationOutputControlButtonForm)
    {
        if (IntegrationOutputControlButtonForm->objectName().isEmpty())
            IntegrationOutputControlButtonForm->setObjectName("IntegrationOutputControlButtonForm");
        IntegrationOutputControlButtonForm->resize(202, 87);
        stackedWidget = new QStackedWidget(IntegrationOutputControlButtonForm);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 171, 71));
        _FreeForResult = new QWidget();
        _FreeForResult->setObjectName("_FreeForResult");
        label_FreeForResult = new QLabel(_FreeForResult);
        label_FreeForResult->setObjectName("label_FreeForResult");
        label_FreeForResult->setGeometry(QRect(0, 0, 151, 61));
        QPalette palette;
        QBrush brush(QColor(0, 0, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(0, 255, 0, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_FreeForResult->setPalette(palette);
        QFont font;
        font.setPointSize(12);
        label_FreeForResult->setFont(font);
        label_FreeForResult->setAutoFillBackground(true);
        label_FreeForResult->setFrameShape(QFrame::Panel);
        label_FreeForResult->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(_FreeForResult);
        _Abs_OK = new QWidget();
        _Abs_OK->setObjectName("_Abs_OK");
        label_Abs_OK = new QLabel(_Abs_OK);
        label_Abs_OK->setObjectName("label_Abs_OK");
        label_Abs_OK->setGeometry(QRect(0, 0, 151, 61));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        QBrush brush2(QColor(255, 255, 0, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush2);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush2);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush2);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush2);
        label_Abs_OK->setPalette(palette1);
        label_Abs_OK->setFont(font);
        label_Abs_OK->setAutoFillBackground(true);
        label_Abs_OK->setFrameShape(QFrame::Panel);
        label_Abs_OK->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(_Abs_OK);
        _Abs_NG = new QWidget();
        _Abs_NG->setObjectName("_Abs_NG");
        label_Abs_NG = new QLabel(_Abs_NG);
        label_Abs_NG->setObjectName("label_Abs_NG");
        label_Abs_NG->setGeometry(QRect(0, 0, 151, 61));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        QBrush brush3(QColor(255, 0, 0, 255));
        brush3.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush3);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush3);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush3);
        label_Abs_NG->setPalette(palette2);
        label_Abs_NG->setFont(font);
        label_Abs_NG->setAutoFillBackground(true);
        label_Abs_NG->setFrameShape(QFrame::Panel);
        label_Abs_NG->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(_Abs_NG);
        _Abs_Blade = new QWidget();
        _Abs_Blade->setObjectName("_Abs_Blade");
        label_Abs_Blade = new QLabel(_Abs_Blade);
        label_Abs_Blade->setObjectName("label_Abs_Blade");
        label_Abs_Blade->setGeometry(QRect(0, 0, 151, 61));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush3);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush3);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush3);
        label_Abs_Blade->setPalette(palette3);
        label_Abs_Blade->setFont(font);
        label_Abs_Blade->setAutoFillBackground(true);
        label_Abs_Blade->setFrameShape(QFrame::Panel);
        label_Abs_Blade->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(_Abs_Blade);

        retranslateUi(IntegrationOutputControlButtonForm);

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(IntegrationOutputControlButtonForm);
    } // setupUi

    void retranslateUi(GUIFormBase *IntegrationOutputControlButtonForm)
    {
        IntegrationOutputControlButtonForm->setWindowTitle(QCoreApplication::translate("IntegrationOutputControlButtonForm", "Form", nullptr));
        label_FreeForResult->setText(QCoreApplication::translate("IntegrationOutputControlButtonForm", "\346\244\234\346\237\273", nullptr));
        label_Abs_OK->setText(QCoreApplication::translate("IntegrationOutputControlButtonForm", "OK\345\207\272\345\212\233", nullptr));
        label_Abs_NG->setText(QCoreApplication::translate("IntegrationOutputControlButtonForm", "NG\345\207\272\345\212\233", nullptr));
        label_Abs_Blade->setText(QCoreApplication::translate("IntegrationOutputControlButtonForm", "\345\210\203NG\345\207\272\345\212\233", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationOutputControlButtonForm: public Ui_IntegrationOutputControlButtonForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONOUTPUTCONTROLBUTTONFORM_H
