/********************************************************************************
** Form generated from reading UI file 'SampleUI.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAMPLEUI_H
#define UI_SAMPLEUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SampleUIClass
{
public:
    QPushButton *pushButton;
    QRadioButton *radioButton;
    QCheckBox *checkBox;
    QComboBox *comboBox;
    QLabel *label;

    void setupUi(QWidget *SampleUIClass)
    {
        if (SampleUIClass->objectName().isEmpty())
            SampleUIClass->setObjectName("SampleUIClass");
        SampleUIClass->resize(400, 300);
        pushButton = new QPushButton(SampleUIClass);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(40, 30, 101, 23));
        radioButton = new QRadioButton(SampleUIClass);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(40, 60, 85, 18));
        checkBox = new QCheckBox(SampleUIClass);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(40, 90, 101, 18));
        comboBox = new QComboBox(SampleUIClass);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(40, 120, 69, 22));
        label = new QLabel(SampleUIClass);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 160, 101, 16));

        retranslateUi(SampleUIClass);

        QMetaObject::connectSlotsByName(SampleUIClass);
    } // setupUi

    void retranslateUi(QWidget *SampleUIClass)
    {
        SampleUIClass->setWindowTitle(QCoreApplication::translate("SampleUIClass", "SampleUI", nullptr));
        pushButton->setText(QCoreApplication::translate("SampleUIClass", "Sample Button", nullptr));
        radioButton->setText(QCoreApplication::translate("SampleUIClass", "Button Text", nullptr));
        checkBox->setText(QCoreApplication::translate("SampleUIClass", "CheckBox Text", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("SampleUIClass", "Text 0", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("SampleUIClass", "Text 1", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("SampleUIClass", "Text 2", nullptr));

        label->setText(QCoreApplication::translate("SampleUIClass", "Label text", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SampleUIClass: public Ui_SampleUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAMPLEUI_H
