/********************************************************************************
** Form generated from reading UI file 'ShowResultForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWRESULTFORM_H
#define UI_SHOWRESULTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowResultForm
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEditResult;
    QSpinBox *spinBox;
    QPushButton *pushButtonSet;
    QPushButton *pushButtonClose;

    void setupUi(QWidget *ShowResultForm)
    {
        if (ShowResultForm->objectName().isEmpty())
            ShowResultForm->setObjectName("ShowResultForm");
        ShowResultForm->resize(233, 124);
        label = new QLabel(ShowResultForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 111, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(ShowResultForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 10, 91, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        lineEditResult = new QLineEdit(ShowResultForm);
        lineEditResult->setObjectName("lineEditResult");
        lineEditResult->setGeometry(QRect(10, 30, 111, 21));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditResult->setPalette(palette);
        lineEditResult->setReadOnly(true);
        spinBox = new QSpinBox(ShowResultForm);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(130, 30, 91, 22));
        spinBox->setMaximum(99999);
        pushButtonSet = new QPushButton(ShowResultForm);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(10, 70, 111, 41));
        pushButtonClose = new QPushButton(ShowResultForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(130, 70, 91, 41));

        retranslateUi(ShowResultForm);

        pushButtonClose->setDefault(true);


        QMetaObject::connectSlotsByName(ShowResultForm);
    } // setupUi

    void retranslateUi(QWidget *ShowResultForm)
    {
        ShowResultForm->setWindowTitle(QCoreApplication::translate("ShowResultForm", "Set CheckEveryday", nullptr));
        label->setText(QCoreApplication::translate("ShowResultForm", "Result", nullptr));
        label_2->setText(QCoreApplication::translate("ShowResultForm", "Register", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("ShowResultForm", "Set", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ShowResultForm", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowResultForm: public Ui_ShowResultForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWRESULTFORM_H
