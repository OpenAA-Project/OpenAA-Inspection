/********************************************************************************
** Form generated from reading UI file 'RingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RINGDIALOG_H
#define UI_RINGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_RingDialog
{
public:
    QSpinBox *spinBoxCx;
    QLabel *label_6;
    QPushButton *pushButtonCancel;
    QLabel *label_2;
    QLabel *label;
    QSpinBox *spinBoxCy;
    QPushButton *pushButtonOK;
    QSpinBox *spinBoxRx1;
    QLabel *label_5;
    QSpinBox *spinBoxRy1;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_7;
    QSpinBox *spinBoxRx2;
    QLabel *label_8;
    QSpinBox *spinBoxRy2;
    QLabel *label_9;

    void setupUi(QDialog *RingDialog)
    {
        if (RingDialog->objectName().isEmpty())
            RingDialog->setObjectName("RingDialog");
        RingDialog->resize(201, 337);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RingDialog->sizePolicy().hasHeightForWidth());
        RingDialog->setSizePolicy(sizePolicy);
        spinBoxCx = new QSpinBox(RingDialog);
        spinBoxCx->setObjectName("spinBoxCx");
        spinBoxCx->setGeometry(QRect(20, 60, 71, 22));
        spinBoxCx->setMinimum(-99999999);
        spinBoxCx->setMaximum(99999999);
        label_6 = new QLabel(RingDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(110, 130, 71, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        pushButtonCancel = new QPushButton(RingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 280, 81, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        label_2 = new QLabel(RingDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 40, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label = new QLabel(RingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        spinBoxCy = new QSpinBox(RingDialog);
        spinBoxCy->setObjectName("spinBoxCy");
        spinBoxCy->setGeometry(QRect(110, 60, 71, 22));
        spinBoxCy->setMinimum(-99999999);
        spinBoxCy->setMaximum(99999999);
        pushButtonOK = new QPushButton(RingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 280, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        spinBoxRx1 = new QSpinBox(RingDialog);
        spinBoxRx1->setObjectName("spinBoxRx1");
        spinBoxRx1->setGeometry(QRect(20, 150, 71, 22));
        spinBoxRx1->setMinimum(-99999999);
        spinBoxRx1->setMaximum(99999999);
        label_5 = new QLabel(RingDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 130, 71, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        spinBoxRy1 = new QSpinBox(RingDialog);
        spinBoxRy1->setObjectName("spinBoxRy1");
        spinBoxRy1->setGeometry(QRect(110, 150, 71, 22));
        spinBoxRy1->setMinimum(-99999999);
        spinBoxRy1->setMaximum(99999999);
        label_4 = new QLabel(RingDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 100, 181, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(RingDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 40, 71, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(RingDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 220, 71, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        spinBoxRx2 = new QSpinBox(RingDialog);
        spinBoxRx2->setObjectName("spinBoxRx2");
        spinBoxRx2->setGeometry(QRect(20, 240, 71, 22));
        spinBoxRx2->setMinimum(-99999999);
        spinBoxRx2->setMaximum(99999999);
        label_8 = new QLabel(RingDialog);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 190, 181, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter);
        spinBoxRy2 = new QSpinBox(RingDialog);
        spinBoxRy2->setObjectName("spinBoxRy2");
        spinBoxRy2->setGeometry(QRect(110, 240, 71, 22));
        spinBoxRy2->setMinimum(-99999999);
        spinBoxRy2->setMaximum(99999999);
        label_9 = new QLabel(RingDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(110, 220, 71, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter);

        retranslateUi(RingDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(RingDialog);
    } // setupUi

    void retranslateUi(QDialog *RingDialog)
    {
        RingDialog->setWindowTitle(QCoreApplication::translate("RingDialog", "Ring", nullptr));
        label_6->setText(QCoreApplication::translate("RingDialog", "Ry", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("RingDialog", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("RingDialog", "X", nullptr));
        label->setText(QCoreApplication::translate("RingDialog", "\344\270\255\345\277\203", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("RingDialog", "OK", nullptr));
        label_5->setText(QCoreApplication::translate("RingDialog", "Rx", nullptr));
        label_4->setText(QCoreApplication::translate("RingDialog", "\345\206\205\345\201\264\345\215\212\345\276\204", nullptr));
        label_3->setText(QCoreApplication::translate("RingDialog", "Y", nullptr));
        label_7->setText(QCoreApplication::translate("RingDialog", "Rx", nullptr));
        label_8->setText(QCoreApplication::translate("RingDialog", "\345\244\226\345\201\264\345\215\212\345\276\204", nullptr));
        label_9->setText(QCoreApplication::translate("RingDialog", "Ry", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RingDialog: public Ui_RingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RINGDIALOG_H
