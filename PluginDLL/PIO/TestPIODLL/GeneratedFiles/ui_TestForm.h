/********************************************************************************
** Form generated from reading UI file 'TestForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTFORM_H
#define UI_TESTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestForm
{
public:
    QFrame *frameOutput;
    QCheckBox *checkBoxOutput0;
    QFrame *frameInput;
    QToolButton *toolButtonInputEnabledBit0;
    QCheckBox *checkBoxInputBit0;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *TestForm)
    {
        if (TestForm->objectName().isEmpty())
            TestForm->setObjectName("TestForm");
        TestForm->resize(321, 542);
        frameOutput = new QFrame(TestForm);
        frameOutput->setObjectName("frameOutput");
        frameOutput->setGeometry(QRect(190, 30, 121, 501));
        frameOutput->setFrameShape(QFrame::StyledPanel);
        frameOutput->setFrameShadow(QFrame::Sunken);
        checkBoxOutput0 = new QCheckBox(frameOutput);
        checkBoxOutput0->setObjectName("checkBoxOutput0");
        checkBoxOutput0->setGeometry(QRect(15, 10, 101, 20));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(212, 208, 200, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        checkBoxOutput0->setPalette(palette);
        frameInput = new QFrame(TestForm);
        frameInput->setObjectName("frameInput");
        frameInput->setGeometry(QRect(10, 30, 171, 501));
        frameInput->setFrameShape(QFrame::StyledPanel);
        frameInput->setFrameShadow(QFrame::Sunken);
        toolButtonInputEnabledBit0 = new QToolButton(frameInput);
        toolButtonInputEnabledBit0->setObjectName("toolButtonInputEnabledBit0");
        toolButtonInputEnabledBit0->setGeometry(QRect(10, 10, 41, 21));
        toolButtonInputEnabledBit0->setCheckable(true);
        toolButtonInputEnabledBit0->setChecked(false);
        checkBoxInputBit0 = new QCheckBox(frameInput);
        checkBoxInputBit0->setObjectName("checkBoxInputBit0");
        checkBoxInputBit0->setGeometry(QRect(60, 10, 101, 21));
        label = new QLabel(TestForm);
        label->setObjectName("label");
        label->setGeometry(QRect(190, 10, 121, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(TestForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 171, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(TestForm);

        QMetaObject::connectSlotsByName(TestForm);
    } // setupUi

    void retranslateUi(QWidget *TestForm)
    {
        TestForm->setWindowTitle(QCoreApplication::translate("TestForm", "Form", nullptr));
        checkBoxOutput0->setText(QCoreApplication::translate("TestForm", "Bit0", nullptr));
        toolButtonInputEnabledBit0->setText(QCoreApplication::translate("TestForm", "0", nullptr));
        checkBoxInputBit0->setText(QCoreApplication::translate("TestForm", "Bit0", nullptr));
        label->setText(QCoreApplication::translate("TestForm", "Output", nullptr));
        label_2->setText(QCoreApplication::translate("TestForm", "Input", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestForm: public Ui_TestForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTFORM_H
