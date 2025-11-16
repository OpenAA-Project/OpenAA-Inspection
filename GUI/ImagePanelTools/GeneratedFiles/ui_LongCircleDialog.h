/********************************************************************************
** Form generated from reading UI file 'LongCircleDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LONGCIRCLEDIALOG_H
#define UI_LONGCIRCLEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_LongCircleDialog
{
public:
    QSpinBox *spinBoxCx1;
    QLabel *label_3;
    QLabel *label_5;
    QSpinBox *spinBoxCy1;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxR;
    QSpinBox *spinBoxCx2;
    QSpinBox *spinBoxCy2;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;

    void setupUi(QDialog *LongCircleDialog)
    {
        if (LongCircleDialog->objectName().isEmpty())
            LongCircleDialog->setObjectName("LongCircleDialog");
        LongCircleDialog->resize(396, 255);
        spinBoxCx1 = new QSpinBox(LongCircleDialog);
        spinBoxCx1->setObjectName("spinBoxCx1");
        spinBoxCx1->setGeometry(QRect(20, 60, 71, 22));
        spinBoxCx1->setMinimum(-99999999);
        spinBoxCx1->setMaximum(99999999);
        label_3 = new QLabel(LongCircleDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 40, 71, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(LongCircleDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(70, 130, 71, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        spinBoxCy1 = new QSpinBox(LongCircleDialog);
        spinBoxCy1->setObjectName("spinBoxCy1");
        spinBoxCy1->setGeometry(QRect(110, 60, 71, 22));
        spinBoxCy1->setMinimum(-99999999);
        spinBoxCy1->setMaximum(99999999);
        label_2 = new QLabel(LongCircleDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 40, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(LongCircleDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 100, 181, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label = new QLabel(LongCircleDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(LongCircleDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 200, 91, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(LongCircleDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 200, 81, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        spinBoxR = new QSpinBox(LongCircleDialog);
        spinBoxR->setObjectName("spinBoxR");
        spinBoxR->setGeometry(QRect(70, 150, 71, 22));
        spinBoxR->setMinimum(-99999999);
        spinBoxR->setMaximum(99999999);
        spinBoxCx2 = new QSpinBox(LongCircleDialog);
        spinBoxCx2->setObjectName("spinBoxCx2");
        spinBoxCx2->setGeometry(QRect(220, 60, 71, 22));
        spinBoxCx2->setMinimum(-99999999);
        spinBoxCx2->setMaximum(99999999);
        spinBoxCy2 = new QSpinBox(LongCircleDialog);
        spinBoxCy2->setObjectName("spinBoxCy2");
        spinBoxCy2->setGeometry(QRect(310, 60, 71, 22));
        spinBoxCy2->setMinimum(-99999999);
        spinBoxCy2->setMaximum(99999999);
        label_6 = new QLabel(LongCircleDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(310, 40, 71, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(LongCircleDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(220, 40, 71, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(LongCircleDialog);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(210, 10, 181, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter);

        retranslateUi(LongCircleDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(LongCircleDialog);
    } // setupUi

    void retranslateUi(QDialog *LongCircleDialog)
    {
        LongCircleDialog->setWindowTitle(QCoreApplication::translate("LongCircleDialog", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("LongCircleDialog", "Y", nullptr));
        label_5->setText(QCoreApplication::translate("LongCircleDialog", "R", nullptr));
        label_2->setText(QCoreApplication::translate("LongCircleDialog", "X", nullptr));
        label_4->setText(QCoreApplication::translate("LongCircleDialog", "\345\215\212\345\276\204", nullptr));
        label->setText(QCoreApplication::translate("LongCircleDialog", "\344\270\255\345\277\2031", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("LongCircleDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("LongCircleDialog", "Cancel", nullptr));
        label_6->setText(QCoreApplication::translate("LongCircleDialog", "Y", nullptr));
        label_7->setText(QCoreApplication::translate("LongCircleDialog", "X", nullptr));
        label_8->setText(QCoreApplication::translate("LongCircleDialog", "\344\270\255\345\277\2032", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LongCircleDialog: public Ui_LongCircleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LONGCIRCLEDIALOG_H
