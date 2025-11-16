/********************************************************************************
** Form generated from reading UI file 'MonoNGTypeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MONONGTYPEDIALOG_H
#define UI_MONONGTYPEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_MonoNGTypeDialog
{
public:
    QSpinBox *spinBoxMaxColor;
    QLabel *label;
    QLabel *label_6;
    QPushButton *pushButtonOK;
    QSpinBox *spinBoxMinRoundRate;
    QLabel *label_3;
    QLabel *label_2;
    QSpinBox *spinBoxMinSize;
    QSpinBox *spinBoxMinColor;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *spinBoxMaxSize;
    QSpinBox *spinBoxMaxRoundRate;

    void setupUi(QDialog *MonoNGTypeDialog)
    {
        if (MonoNGTypeDialog->objectName().isEmpty())
            MonoNGTypeDialog->setObjectName("MonoNGTypeDialog");
        MonoNGTypeDialog->resize(188, 222);
        spinBoxMaxColor = new QSpinBox(MonoNGTypeDialog);
        spinBoxMaxColor->setObjectName("spinBoxMaxColor");
        spinBoxMaxColor->setGeometry(QRect(100, 30, 81, 22));
        spinBoxMaxColor->setMaximum(999999);
        label = new QLabel(MonoNGTypeDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 60, 81, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(MonoNGTypeDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 10, 81, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonOK = new QPushButton(MonoNGTypeDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(50, 170, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        spinBoxMinRoundRate = new QSpinBox(MonoNGTypeDialog);
        spinBoxMinRoundRate->setObjectName("spinBoxMinRoundRate");
        spinBoxMinRoundRate->setGeometry(QRect(10, 130, 81, 22));
        spinBoxMinRoundRate->setMaximum(9999);
        label_3 = new QLabel(MonoNGTypeDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(100, 110, 81, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(MonoNGTypeDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(100, 60, 81, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxMinSize = new QSpinBox(MonoNGTypeDialog);
        spinBoxMinSize->setObjectName("spinBoxMinSize");
        spinBoxMinSize->setGeometry(QRect(10, 80, 81, 22));
        spinBoxMinSize->setMaximum(999999);
        spinBoxMinColor = new QSpinBox(MonoNGTypeDialog);
        spinBoxMinColor->setObjectName("spinBoxMinColor");
        spinBoxMinColor->setGeometry(QRect(10, 30, 81, 22));
        spinBoxMinColor->setMaximum(999999);
        label_4 = new QLabel(MonoNGTypeDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 110, 81, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(MonoNGTypeDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(100, 10, 81, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxMaxSize = new QSpinBox(MonoNGTypeDialog);
        spinBoxMaxSize->setObjectName("spinBoxMaxSize");
        spinBoxMaxSize->setGeometry(QRect(100, 80, 81, 22));
        spinBoxMaxSize->setMaximum(999999);
        spinBoxMaxRoundRate = new QSpinBox(MonoNGTypeDialog);
        spinBoxMaxRoundRate->setObjectName("spinBoxMaxRoundRate");
        spinBoxMaxRoundRate->setGeometry(QRect(100, 130, 81, 22));
        spinBoxMaxRoundRate->setMaximum(9999);

        retranslateUi(MonoNGTypeDialog);

        QMetaObject::connectSlotsByName(MonoNGTypeDialog);
    } // setupUi

    void retranslateUi(QDialog *MonoNGTypeDialog)
    {
        MonoNGTypeDialog->setWindowTitle(QCoreApplication::translate("MonoNGTypeDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("MonoNGTypeDialog", "\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_6->setText(QCoreApplication::translate("MonoNGTypeDialog", "\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("MonoNGTypeDialog", "OK", nullptr));
        label_3->setText(QCoreApplication::translate("MonoNGTypeDialog", "\346\234\200\345\244\247\345\206\206\345\275\242\347\216\207", nullptr));
        label_2->setText(QCoreApplication::translate("MonoNGTypeDialog", "\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_4->setText(QCoreApplication::translate("MonoNGTypeDialog", "\346\234\200\345\260\217\345\206\206\345\275\242\347\216\207", nullptr));
        label_5->setText(QCoreApplication::translate("MonoNGTypeDialog", "\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MonoNGTypeDialog: public Ui_MonoNGTypeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MONONGTYPEDIALOG_H
