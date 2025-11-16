/********************************************************************************
** Form generated from reading UI file 'BootupLogoForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOTUPLOGOFORM_H
#define UI_BOOTUPLOGOFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BootupLogoFormClass
{
public:
    QLabel *label;

    void setupUi(QWidget *BootupLogoFormClass)
    {
        if (BootupLogoFormClass->objectName().isEmpty())
            BootupLogoFormClass->setObjectName("BootupLogoFormClass");
        BootupLogoFormClass->resize(400, 100);
        label = new QLabel(BootupLogoFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 381, 81));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(30);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(BootupLogoFormClass);

        QMetaObject::connectSlotsByName(BootupLogoFormClass);
    } // setupUi

    void retranslateUi(QWidget *BootupLogoFormClass)
    {
        BootupLogoFormClass->setWindowTitle(QCoreApplication::translate("BootupLogoFormClass", "Booting...", nullptr));
        label->setText(QCoreApplication::translate("BootupLogoFormClass", "\350\265\267\345\213\225\344\270\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BootupLogoFormClass: public Ui_BootupLogoFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOTUPLOGOFORM_H
