/********************************************************************************
** Form generated from reading UI file 'ColorChangeShiftForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORCHANGESHIFTFORM_H
#define UI_COLORCHANGESHIFTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ColorChangeShiftFormClass
{
public:
    QPushButton *pushButton;
    QSpinBox *spinBoxXDir;
    QLabel *label_2;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxYDir;
    QLabel *label;

    void setupUi(QWidget *ColorChangeShiftFormClass)
    {
        if (ColorChangeShiftFormClass->objectName().isEmpty())
            ColorChangeShiftFormClass->setObjectName("ColorChangeShiftFormClass");
        ColorChangeShiftFormClass->resize(242, 161);
        pushButton = new QPushButton(ColorChangeShiftFormClass);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(30, 92, 75, 31));
        spinBoxXDir = new QSpinBox(ColorChangeShiftFormClass);
        spinBoxXDir->setObjectName("spinBoxXDir");
        spinBoxXDir->setGeometry(QRect(30, 50, 81, 22));
        spinBoxXDir->setMinimum(-999);
        spinBoxXDir->setMaximum(999);
        label_2 = new QLabel(ColorChangeShiftFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 30, 81, 16));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonCancel = new QPushButton(ColorChangeShiftFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 92, 75, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        spinBoxYDir = new QSpinBox(ColorChangeShiftFormClass);
        spinBoxYDir->setObjectName("spinBoxYDir");
        spinBoxYDir->setGeometry(QRect(130, 50, 81, 22));
        spinBoxYDir->setMinimum(-999);
        spinBoxYDir->setMaximum(999);
        label = new QLabel(ColorChangeShiftFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 30, 81, 16));
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(ColorChangeShiftFormClass);

        QMetaObject::connectSlotsByName(ColorChangeShiftFormClass);
    } // setupUi

    void retranslateUi(QWidget *ColorChangeShiftFormClass)
    {
        ColorChangeShiftFormClass->setWindowTitle(QCoreApplication::translate("ColorChangeShiftFormClass", "ColorChangeShiftForm", nullptr));
        pushButton->setText(QCoreApplication::translate("ColorChangeShiftFormClass", "Set", nullptr));
        label_2->setText(QCoreApplication::translate("ColorChangeShiftFormClass", "Y\347\247\273\345\213\225\351\207\217", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("ColorChangeShiftFormClass", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("ColorChangeShiftFormClass", "X\347\247\273\345\213\225\351\207\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ColorChangeShiftFormClass: public Ui_ColorChangeShiftFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORCHANGESHIFTFORM_H
