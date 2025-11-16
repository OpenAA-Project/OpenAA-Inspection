/********************************************************************************
** Form generated from reading UI file 'SettingOneLayerForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGONELAYERFORM_H
#define UI_SETTINGONELAYERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingOneLayerFormClass
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label;
    QComboBox *comboBoxLayer;
    QLabel *label_2;
    QComboBox *comboBoxProcess;
    QLabel *label_3;
    QSpinBox *spinBoxParam;

    void setupUi(QDialog *SettingOneLayerFormClass)
    {
        if (SettingOneLayerFormClass->objectName().isEmpty())
            SettingOneLayerFormClass->setObjectName("SettingOneLayerFormClass");
        SettingOneLayerFormClass->resize(218, 227);
        pushButtonOK = new QPushButton(SettingOneLayerFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 190, 75, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(SettingOneLayerFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 190, 75, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        label = new QLabel(SettingOneLayerFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 20, 111, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        comboBoxLayer = new QComboBox(SettingOneLayerFormClass);
        comboBoxLayer->setObjectName("comboBoxLayer");
        comboBoxLayer->setGeometry(QRect(60, 40, 91, 22));
        label_2 = new QLabel(SettingOneLayerFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 70, 111, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        comboBoxProcess = new QComboBox(SettingOneLayerFormClass);
        comboBoxProcess->addItem(QString());
        comboBoxProcess->addItem(QString());
        comboBoxProcess->addItem(QString());
        comboBoxProcess->addItem(QString());
        comboBoxProcess->setObjectName("comboBoxProcess");
        comboBoxProcess->setGeometry(QRect(60, 90, 91, 22));
        label_3 = new QLabel(SettingOneLayerFormClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(50, 120, 111, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxParam = new QSpinBox(SettingOneLayerFormClass);
        spinBoxParam->setObjectName("spinBoxParam");
        spinBoxParam->setGeometry(QRect(70, 140, 71, 22));

        retranslateUi(SettingOneLayerFormClass);

        QMetaObject::connectSlotsByName(SettingOneLayerFormClass);
    } // setupUi

    void retranslateUi(QDialog *SettingOneLayerFormClass)
    {
        SettingOneLayerFormClass->setWindowTitle(QCoreApplication::translate("SettingOneLayerFormClass", "SettingOneLayerForm", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingOneLayerFormClass", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingOneLayerFormClass", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("SettingOneLayerFormClass", "Layer", nullptr));
        label_2->setText(QCoreApplication::translate("SettingOneLayerFormClass", "\345\207\246\347\220\206\346\226\271\346\263\225", nullptr));
        comboBoxProcess->setItemText(0, QCoreApplication::translate("SettingOneLayerFormClass", "\347\237\251\345\275\242\345\271\263\345\235\207\345\214\226", nullptr));
        comboBoxProcess->setItemText(1, QCoreApplication::translate("SettingOneLayerFormClass", "\346\250\252\345\271\263\345\235\207\345\214\226", nullptr));
        comboBoxProcess->setItemText(2, QCoreApplication::translate("SettingOneLayerFormClass", "\343\203\241\343\203\207\343\202\243\343\202\242\343\203\263\343\203\225\343\202\243\343\203\253\343\202\277", nullptr));
        comboBoxProcess->setItemText(3, QCoreApplication::translate("SettingOneLayerFormClass", "\347\237\251\345\275\242\345\212\240\351\207\215\345\271\263\345\235\207", nullptr));

        label_3->setText(QCoreApplication::translate("SettingOneLayerFormClass", "\351\240\230\345\237\237\343\203\211\343\203\203\343\203\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingOneLayerFormClass: public Ui_SettingOneLayerFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGONELAYERFORM_H
