/********************************************************************************
** Form generated from reading UI file 'NGTypeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NGTYPEDIALOG_H
#define UI_NGTYPEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_NGTypeDialogClass
{
public:
    QPushButton *pushButtonOK;
    QSpinBox *spinBoxMinSize;
    QSpinBox *spinBoxMinRoundRate;
    QSpinBox *spinBoxMaxSize;
    QSpinBox *spinBoxMaxRoundRate;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *spinBoxMaxColor;
    QSpinBox *spinBoxMinColor;
    QLabel *label_6;

    void setupUi(QDialog *NGTypeDialogClass)
    {
        if (NGTypeDialogClass->objectName().isEmpty())
            NGTypeDialogClass->setObjectName("NGTypeDialogClass");
        NGTypeDialogClass->resize(208, 221);
        pushButtonOK = new QPushButton(NGTypeDialogClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(50, 170, 111, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        spinBoxMinSize = new QSpinBox(NGTypeDialogClass);
        spinBoxMinSize->setObjectName("spinBoxMinSize");
        spinBoxMinSize->setGeometry(QRect(10, 80, 81, 22));
        spinBoxMinSize->setMaximum(999999);
        spinBoxMinRoundRate = new QSpinBox(NGTypeDialogClass);
        spinBoxMinRoundRate->setObjectName("spinBoxMinRoundRate");
        spinBoxMinRoundRate->setGeometry(QRect(10, 130, 81, 22));
        spinBoxMinRoundRate->setMaximum(9999);
        spinBoxMaxSize = new QSpinBox(NGTypeDialogClass);
        spinBoxMaxSize->setObjectName("spinBoxMaxSize");
        spinBoxMaxSize->setGeometry(QRect(110, 80, 81, 22));
        spinBoxMaxSize->setMaximum(999999);
        spinBoxMaxRoundRate = new QSpinBox(NGTypeDialogClass);
        spinBoxMaxRoundRate->setObjectName("spinBoxMaxRoundRate");
        spinBoxMaxRoundRate->setGeometry(QRect(110, 130, 81, 22));
        spinBoxMaxRoundRate->setMaximum(9999);
        label = new QLabel(NGTypeDialogClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 60, 91, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(NGTypeDialogClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 60, 91, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(NGTypeDialogClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 110, 91, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(NGTypeDialogClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 110, 91, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(NGTypeDialogClass);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(110, 10, 91, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxMaxColor = new QSpinBox(NGTypeDialogClass);
        spinBoxMaxColor->setObjectName("spinBoxMaxColor");
        spinBoxMaxColor->setGeometry(QRect(110, 30, 81, 22));
        spinBoxMaxColor->setMaximum(999999);
        spinBoxMinColor = new QSpinBox(NGTypeDialogClass);
        spinBoxMinColor->setObjectName("spinBoxMinColor");
        spinBoxMinColor->setGeometry(QRect(10, 30, 81, 22));
        spinBoxMinColor->setMaximum(999999);
        label_6 = new QLabel(NGTypeDialogClass);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 10, 91, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(NGTypeDialogClass);

        QMetaObject::connectSlotsByName(NGTypeDialogClass);
    } // setupUi

    void retranslateUi(QDialog *NGTypeDialogClass)
    {
        NGTypeDialogClass->setWindowTitle(QCoreApplication::translate("NGTypeDialogClass", "NGTypeDialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("NGTypeDialogClass", "OK", nullptr));
        label->setText(QCoreApplication::translate("NGTypeDialogClass", "\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_2->setText(QCoreApplication::translate("NGTypeDialogClass", "\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_3->setText(QCoreApplication::translate("NGTypeDialogClass", "\346\234\200\345\244\247\345\206\206\345\275\242\347\216\207", nullptr));
        label_4->setText(QCoreApplication::translate("NGTypeDialogClass", "\346\234\200\345\260\217\345\206\206\345\275\242\347\216\207", nullptr));
        label_5->setText(QCoreApplication::translate("NGTypeDialogClass", "\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
        label_6->setText(QCoreApplication::translate("NGTypeDialogClass", "\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NGTypeDialogClass: public Ui_NGTypeDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NGTYPEDIALOG_H
