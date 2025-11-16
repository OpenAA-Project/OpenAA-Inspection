/********************************************************************************
** Form generated from reading UI file 'IntegrationRunningTrendForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONRUNNINGTRENDFORM_H
#define UI_INTEGRATIONRUNNINGTRENDFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_IntegrationRunningTrendForm
{
public:
    QFrame *frame;
    QComboBox *comboBoxSpan;
    QLabel *labelNG;
    QLabel *labelOK;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QWidget *page_2;
    QLabel *label_2;
    QWidget *page_3;
    QLabel *label_3;
    QFrame *frameScaleY;

    void setupUi(GUIFormBase *IntegrationRunningTrendForm)
    {
        if (IntegrationRunningTrendForm->objectName().isEmpty())
            IntegrationRunningTrendForm->setObjectName("IntegrationRunningTrendForm");
        IntegrationRunningTrendForm->resize(668, 172);
        frame = new QFrame(IntegrationRunningTrendForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 661, 41));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        comboBoxSpan = new QComboBox(frame);
        comboBoxSpan->addItem(QString());
        comboBoxSpan->addItem(QString());
        comboBoxSpan->addItem(QString());
        comboBoxSpan->setObjectName("comboBoxSpan");
        comboBoxSpan->setGeometry(QRect(10, 3, 81, 31));
        QFont font;
        font.setPointSize(12);
        comboBoxSpan->setFont(font);
        labelNG = new QLabel(frame);
        labelNG->setObjectName("labelNG");
        labelNG->setGeometry(QRect(160, 10, 41, 18));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        labelNG->setPalette(palette);
        labelNG->setAutoFillBackground(true);
        labelNG->setAlignment(Qt::AlignCenter);
        labelOK = new QLabel(frame);
        labelOK->setObjectName("labelOK");
        labelOK->setGeometry(QRect(220, 10, 41, 18));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        QBrush brush2(QColor(0, 255, 0, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush2);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush2);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush2);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush2);
        labelOK->setPalette(palette1);
        labelOK->setAutoFillBackground(true);
        labelOK->setAlignment(Qt::AlignCenter);
        stackedWidget = new QStackedWidget(frame);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(290, 0, 361, 41));
        page = new QWidget();
        page->setObjectName("page");
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 291, 18));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        label_2 = new QLabel(page_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 311, 18));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        label_3 = new QLabel(page_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 301, 18));
        stackedWidget->addWidget(page_3);
        frameScaleY = new QFrame(IntegrationRunningTrendForm);
        frameScaleY->setObjectName("frameScaleY");
        frameScaleY->setGeometry(QRect(0, 40, 61, 131));
        frameScaleY->setFrameShape(QFrame::StyledPanel);
        frameScaleY->setFrameShadow(QFrame::Raised);

        retranslateUi(IntegrationRunningTrendForm);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(IntegrationRunningTrendForm);
    } // setupUi

    void retranslateUi(GUIFormBase *IntegrationRunningTrendForm)
    {
        IntegrationRunningTrendForm->setWindowTitle(QCoreApplication::translate("IntegrationRunningTrendForm", "Form", nullptr));
        comboBoxSpan->setItemText(0, QCoreApplication::translate("IntegrationRunningTrendForm", "\346\231\202\351\226\223", nullptr));
        comboBoxSpan->setItemText(1, QCoreApplication::translate("IntegrationRunningTrendForm", "\346\227\245", nullptr));
        comboBoxSpan->setItemText(2, QCoreApplication::translate("IntegrationRunningTrendForm", "\346\234\210", nullptr));

        labelNG->setText(QCoreApplication::translate("IntegrationRunningTrendForm", "NG", nullptr));
        labelOK->setText(QCoreApplication::translate("IntegrationRunningTrendForm", "OK", nullptr));
        label->setText(QCoreApplication::translate("IntegrationRunningTrendForm", "\347\270\246\350\273\270\343\201\2571\345\210\206\345\275\223\343\201\237\343\202\212\343\201\256\346\244\234\346\237\273\346\225\260", nullptr));
        label_2->setText(QCoreApplication::translate("IntegrationRunningTrendForm", "\347\270\246\350\273\270\343\201\2571\346\231\202\351\226\223\345\275\223\343\201\237\343\202\212\343\201\256\346\244\234\346\237\273\346\225\260", nullptr));
        label_3->setText(QCoreApplication::translate("IntegrationRunningTrendForm", "\347\270\246\350\273\270\343\201\2571\346\227\245\345\275\223\343\201\237\343\202\212\343\201\256\346\244\234\346\237\273\346\225\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationRunningTrendForm: public Ui_IntegrationRunningTrendForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONRUNNINGTRENDFORM_H
