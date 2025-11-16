/********************************************************************************
** Form generated from reading UI file 'ChangeShiftForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGESHIFTFORM_H
#define UI_CHANGESHIFTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangeShiftFormClass
{
public:
    QPushButton *pushButton;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxXDir;
    QSpinBox *spinBoxYDir;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *ChangeShiftFormClass)
    {
        if (ChangeShiftFormClass->objectName().isEmpty())
            ChangeShiftFormClass->setObjectName("ChangeShiftFormClass");
        ChangeShiftFormClass->resize(223, 135);
        pushButton = new QPushButton(ChangeShiftFormClass);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 82, 75, 31));
        pushButtonCancel = new QPushButton(ChangeShiftFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(130, 82, 75, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/fireworks_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        spinBoxXDir = new QSpinBox(ChangeShiftFormClass);
        spinBoxXDir->setObjectName("spinBoxXDir");
        spinBoxXDir->setGeometry(QRect(20, 40, 81, 22));
        spinBoxXDir->setMinimum(-99);
        spinBoxYDir = new QSpinBox(ChangeShiftFormClass);
        spinBoxYDir->setObjectName("spinBoxYDir");
        spinBoxYDir->setGeometry(QRect(120, 40, 81, 22));
        spinBoxYDir->setMinimum(-999);
        spinBoxYDir->setMaximum(999);
        label = new QLabel(ChangeShiftFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 81, 16));
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(ChangeShiftFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(120, 20, 81, 16));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(ChangeShiftFormClass);

        QMetaObject::connectSlotsByName(ChangeShiftFormClass);
    } // setupUi

    void retranslateUi(QWidget *ChangeShiftFormClass)
    {
        ChangeShiftFormClass->setWindowTitle(QCoreApplication::translate("ChangeShiftFormClass", "ChangeShiftForm", nullptr));
        pushButton->setText(QCoreApplication::translate("ChangeShiftFormClass", "Set", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("ChangeShiftFormClass", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("ChangeShiftFormClass", "X\347\247\273\345\213\225\351\207\217", nullptr));
        label_2->setText(QCoreApplication::translate("ChangeShiftFormClass", "Y\347\247\273\345\213\225\351\207\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeShiftFormClass: public Ui_ChangeShiftFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGESHIFTFORM_H
