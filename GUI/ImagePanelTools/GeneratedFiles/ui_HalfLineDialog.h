/********************************************************************************
** Form generated from reading UI file 'HalfLineDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HALFLINEDIALOG_H
#define UI_HALFLINEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_HalfLineDialog
{
public:
    QLabel *label_4;
    QPushButton *pushButtonOK;
    QLabel *label_3;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox;
    QSpinBox *spinBoxX;
    QLabel *label_5;
    QLabel *label;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxY;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBoxLength;

    void setupUi(QDialog *HalfLineDialog)
    {
        if (HalfLineDialog->objectName().isEmpty())
            HalfLineDialog->setObjectName("HalfLineDialog");
        HalfLineDialog->resize(202, 300);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(HalfLineDialog->sizePolicy().hasHeightForWidth());
        HalfLineDialog->setSizePolicy(sizePolicy);
        label_4 = new QLabel(HalfLineDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 100, 181, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(HalfLineDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 240, 91, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        label_3 = new QLabel(HalfLineDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 40, 71, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(HalfLineDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 40, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        doubleSpinBox = new QDoubleSpinBox(HalfLineDialog);
        doubleSpinBox->setObjectName("doubleSpinBox");
        doubleSpinBox->setGeometry(QRect(90, 130, 71, 22));
        doubleSpinBox->setMaximum(360.000000000000000);
        spinBoxX = new QSpinBox(HalfLineDialog);
        spinBoxX->setObjectName("spinBoxX");
        spinBoxX->setGeometry(QRect(20, 60, 71, 22));
        spinBoxX->setMinimum(-99999999);
        spinBoxX->setMaximum(99999999);
        label_5 = new QLabel(HalfLineDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 130, 71, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        label = new QLabel(HalfLineDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        pushButtonCancel = new QPushButton(HalfLineDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 240, 81, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        spinBoxY = new QSpinBox(HalfLineDialog);
        spinBoxY->setObjectName("spinBoxY");
        spinBoxY->setGeometry(QRect(110, 60, 71, 22));
        spinBoxY->setMinimum(-99999999);
        spinBoxY->setMaximum(99999999);
        label_6 = new QLabel(HalfLineDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 170, 181, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        doubleSpinBoxLength = new QDoubleSpinBox(HalfLineDialog);
        doubleSpinBoxLength->setObjectName("doubleSpinBoxLength");
        doubleSpinBoxLength->setGeometry(QRect(70, 200, 71, 22));
        doubleSpinBoxLength->setMaximum(99999999.000000000000000);

        retranslateUi(HalfLineDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(HalfLineDialog);
    } // setupUi

    void retranslateUi(QDialog *HalfLineDialog)
    {
        HalfLineDialog->setWindowTitle(QCoreApplication::translate("HalfLineDialog", "HalfLine", nullptr));
        label_4->setText(QCoreApplication::translate("HalfLineDialog", "\350\247\222\345\272\246\357\274\210\345\272\246\357\274\211", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("HalfLineDialog", "OK", nullptr));
        label_3->setText(QCoreApplication::translate("HalfLineDialog", "Y", nullptr));
        label_2->setText(QCoreApplication::translate("HalfLineDialog", "X", nullptr));
        label_5->setText(QCoreApplication::translate("HalfLineDialog", "\316\270", nullptr));
        label->setText(QCoreApplication::translate("HalfLineDialog", "\351\200\232\351\201\216\347\202\271", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("HalfLineDialog", "Cancel", nullptr));
        label_6->setText(QCoreApplication::translate("HalfLineDialog", "\351\225\267\343\201\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HalfLineDialog: public Ui_HalfLineDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HALFLINEDIALOG_H
