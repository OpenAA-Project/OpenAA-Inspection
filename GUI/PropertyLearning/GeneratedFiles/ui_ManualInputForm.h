/********************************************************************************
** Form generated from reading UI file 'ManualInputForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANUALINPUTFORM_H
#define UI_MANUALINPUTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_ManualInputFormClass
{
public:
    QToolButton *toolButtonMisNG;
    QToolButton *toolButtonNG;
    QSpinBox *spinBoxNGLevel;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *ManualInputFormClass)
    {
        if (ManualInputFormClass->objectName().isEmpty())
            ManualInputFormClass->setObjectName("ManualInputFormClass");
        ManualInputFormClass->resize(355, 173);
        toolButtonMisNG = new QToolButton(ManualInputFormClass);
        toolButtonMisNG->setObjectName("toolButtonMisNG");
        toolButtonMisNG->setGeometry(QRect(210, 10, 111, 31));
        toolButtonMisNG->setCheckable(true);
        toolButtonMisNG->setChecked(false);
        toolButtonMisNG->setAutoExclusive(true);
        toolButtonNG = new QToolButton(ManualInputFormClass);
        toolButtonNG->setObjectName("toolButtonNG");
        toolButtonNG->setGeometry(QRect(20, 10, 111, 31));
        toolButtonNG->setCheckable(true);
        toolButtonNG->setChecked(true);
        toolButtonNG->setAutoExclusive(true);
        toolButtonNG->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        spinBoxNGLevel = new QSpinBox(ManualInputFormClass);
        spinBoxNGLevel->setObjectName("spinBoxNGLevel");
        spinBoxNGLevel->setGeometry(QRect(20, 80, 111, 22));
        spinBoxNGLevel->setMaximum(255);
        label = new QLabel(ManualInputFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(29, 60, 71, 20));
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(ManualInputFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(180, 60, 155, 52));
        pushButtonOK = new QPushButton(ManualInputFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(40, 130, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(ManualInputFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(200, 130, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(ManualInputFormClass);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(ManualInputFormClass);
    } // setupUi

    void retranslateUi(QDialog *ManualInputFormClass)
    {
        ManualInputFormClass->setWindowTitle(QCoreApplication::translate("ManualInputFormClass", "ManualInputForm", nullptr));
        toolButtonMisNG->setText(QCoreApplication::translate("ManualInputFormClass", "\350\231\232\345\240\261\346\216\222\351\231\244", nullptr));
        toolButtonNG->setText(QCoreApplication::translate("ManualInputFormClass", "NG\347\231\272\345\240\261", nullptr));
        label->setText(QCoreApplication::translate("ManualInputFormClass", "NG\343\203\254\343\203\231\343\203\253", nullptr));
        label_2->setText(QCoreApplication::translate("ManualInputFormClass", "\347\265\266\345\257\276\346\244\234\345\207\272\343\201\227\343\201\252\343\201\221\343\202\214\343\201\260\343\201\252\343\202\211\343\201\252\343\201\204\357\274\256\357\274\247\n"
"\347\265\266\345\257\276\357\274\256\357\274\247\343\201\253\343\201\252\343\201\243\343\201\246\343\201\257\343\201\252\343\202\211\343\201\252\343\201\204\357\274\257\357\274\253\n"
"\343\201\223\343\202\214\343\202\211\343\201\256\346\231\202\343\200\201\357\274\220\n"
"\346\225\260\345\200\244\343\201\214\345\244\247\343\201\215\343\201\217\343\201\252\343\202\213\343\201\253\345\276\223\343\201\243\343\201\246\347\267\251\343\201\217\343\201\252\343\202\213", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("ManualInputFormClass", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("ManualInputFormClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManualInputFormClass: public Ui_ManualInputFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANUALINPUTFORM_H
