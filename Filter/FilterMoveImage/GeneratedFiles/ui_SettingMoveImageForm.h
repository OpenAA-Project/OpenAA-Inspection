/********************************************************************************
** Form generated from reading UI file 'SettingMoveImageForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGMOVEIMAGEFORM_H
#define UI_SETTINGMOVEIMAGEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingMoveImageForm
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxDx;
    QSpinBox *spinBoxDy;

    void setupUi(QDialog *SettingMoveImageForm)
    {
        if (SettingMoveImageForm->objectName().isEmpty())
            SettingMoveImageForm->setObjectName("SettingMoveImageForm");
        SettingMoveImageForm->resize(176, 99);
        pushButtonOK = new QPushButton(SettingMoveImageForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 60, 75, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(SettingMoveImageForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(90, 60, 75, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        label = new QLabel(SettingMoveImageForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 61, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(SettingMoveImageForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(100, 10, 61, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        spinBoxDx = new QSpinBox(SettingMoveImageForm);
        spinBoxDx->setObjectName("spinBoxDx");
        spinBoxDx->setGeometry(QRect(10, 30, 61, 22));
        spinBoxDx->setMinimum(-9999);
        spinBoxDx->setMaximum(9999);
        spinBoxDy = new QSpinBox(SettingMoveImageForm);
        spinBoxDy->setObjectName("spinBoxDy");
        spinBoxDy->setGeometry(QRect(100, 30, 61, 22));
        spinBoxDy->setMinimum(-9999);
        spinBoxDy->setMaximum(9999);

        retranslateUi(SettingMoveImageForm);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SettingMoveImageForm);
    } // setupUi

    void retranslateUi(QDialog *SettingMoveImageForm)
    {
        SettingMoveImageForm->setWindowTitle(QCoreApplication::translate("SettingMoveImageForm", "Setting Move-Image", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingMoveImageForm", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingMoveImageForm", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("SettingMoveImageForm", "X shift", nullptr));
        label_2->setText(QCoreApplication::translate("SettingMoveImageForm", "Y shift", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingMoveImageForm: public Ui_SettingMoveImageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGMOVEIMAGEFORM_H
