/********************************************************************************
** Form generated from reading UI file 'TrueColorChangeShiftForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRUECOLORCHANGESHIFTFORM_H
#define UI_TRUECOLORCHANGESHIFTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrueColorChangeShiftFormClass
{
public:
    QPushButton *pushButton;
    QSpinBox *spinBoxXDir;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxYDir;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *TrueColorChangeShiftFormClass)
    {
        if (TrueColorChangeShiftFormClass->objectName().isEmpty())
            TrueColorChangeShiftFormClass->setObjectName("TrueColorChangeShiftFormClass");
        TrueColorChangeShiftFormClass->resize(266, 170);
        pushButton = new QPushButton(TrueColorChangeShiftFormClass);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(40, 102, 75, 31));
        spinBoxXDir = new QSpinBox(TrueColorChangeShiftFormClass);
        spinBoxXDir->setObjectName("spinBoxXDir");
        spinBoxXDir->setGeometry(QRect(40, 60, 81, 22));
        spinBoxXDir->setMinimum(-999);
        spinBoxXDir->setMaximum(999);
        pushButtonCancel = new QPushButton(TrueColorChangeShiftFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(150, 102, 75, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/fireworks_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        spinBoxYDir = new QSpinBox(TrueColorChangeShiftFormClass);
        spinBoxYDir->setObjectName("spinBoxYDir");
        spinBoxYDir->setGeometry(QRect(140, 60, 81, 22));
        spinBoxYDir->setMinimum(-999);
        spinBoxYDir->setMaximum(999);
        label = new QLabel(TrueColorChangeShiftFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 40, 81, 16));
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(TrueColorChangeShiftFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 40, 81, 16));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(TrueColorChangeShiftFormClass);

        QMetaObject::connectSlotsByName(TrueColorChangeShiftFormClass);
    } // setupUi

    void retranslateUi(QWidget *TrueColorChangeShiftFormClass)
    {
        TrueColorChangeShiftFormClass->setWindowTitle(QCoreApplication::translate("TrueColorChangeShiftFormClass", "TrueColorChangeShiftForm", nullptr));
        pushButton->setText(QCoreApplication::translate("TrueColorChangeShiftFormClass", "Set", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("TrueColorChangeShiftFormClass", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("TrueColorChangeShiftFormClass", "X\347\247\273\345\213\225\351\207\217", nullptr));
        label_2->setText(QCoreApplication::translate("TrueColorChangeShiftFormClass", "Y\347\247\273\345\213\225\351\207\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrueColorChangeShiftFormClass: public Ui_TrueColorChangeShiftFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRUECOLORCHANGESHIFTFORM_H
