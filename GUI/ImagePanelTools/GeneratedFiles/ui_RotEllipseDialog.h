/********************************************************************************
** Form generated from reading UI file 'RotEllipseDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROTELLIPSEDIALOG_H
#define UI_ROTELLIPSEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_RotEllipseDialog
{
public:
    QSpinBox *spinBoxCx;
    QLabel *label_6;
    QPushButton *pushButtonCancel;
    QLabel *label_2;
    QLabel *label;
    QSpinBox *spinBoxCy;
    QPushButton *pushButtonOK;
    QSpinBox *spinBoxRx;
    QLabel *label_5;
    QSpinBox *spinBoxRy;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBoxS;
    QLabel *label_8;

    void setupUi(QDialog *RotEllipseDialog)
    {
        if (RotEllipseDialog->objectName().isEmpty())
            RotEllipseDialog->setObjectName("RotEllipseDialog");
        RotEllipseDialog->resize(204, 317);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RotEllipseDialog->sizePolicy().hasHeightForWidth());
        RotEllipseDialog->setSizePolicy(sizePolicy);
        spinBoxCx = new QSpinBox(RotEllipseDialog);
        spinBoxCx->setObjectName("spinBoxCx");
        spinBoxCx->setGeometry(QRect(20, 60, 71, 22));
        spinBoxCx->setMinimum(-99999999);
        spinBoxCx->setMaximum(99999999);
        label_6 = new QLabel(RotEllipseDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(110, 130, 71, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        pushButtonCancel = new QPushButton(RotEllipseDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 260, 81, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        label_2 = new QLabel(RotEllipseDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 40, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label = new QLabel(RotEllipseDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        spinBoxCy = new QSpinBox(RotEllipseDialog);
        spinBoxCy->setObjectName("spinBoxCy");
        spinBoxCy->setGeometry(QRect(110, 60, 71, 22));
        spinBoxCy->setMinimum(-99999999);
        spinBoxCy->setMaximum(99999999);
        pushButtonOK = new QPushButton(RotEllipseDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 260, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        spinBoxRx = new QSpinBox(RotEllipseDialog);
        spinBoxRx->setObjectName("spinBoxRx");
        spinBoxRx->setGeometry(QRect(20, 150, 71, 22));
        spinBoxRx->setMinimum(-99999999);
        spinBoxRx->setMaximum(99999999);
        label_5 = new QLabel(RotEllipseDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 130, 71, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        spinBoxRy = new QSpinBox(RotEllipseDialog);
        spinBoxRy->setObjectName("spinBoxRy");
        spinBoxRy->setGeometry(QRect(110, 150, 71, 22));
        spinBoxRy->setMinimum(-99999999);
        spinBoxRy->setMaximum(99999999);
        label_4 = new QLabel(RotEllipseDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 100, 181, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(RotEllipseDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 40, 71, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(RotEllipseDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 190, 181, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        doubleSpinBoxS = new QDoubleSpinBox(RotEllipseDialog);
        doubleSpinBoxS->setObjectName("doubleSpinBoxS");
        doubleSpinBoxS->setGeometry(QRect(90, 220, 71, 22));
        doubleSpinBoxS->setMaximum(360.000000000000000);
        label_8 = new QLabel(RotEllipseDialog);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 220, 71, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter);

        retranslateUi(RotEllipseDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(RotEllipseDialog);
    } // setupUi

    void retranslateUi(QDialog *RotEllipseDialog)
    {
        RotEllipseDialog->setWindowTitle(QCoreApplication::translate("RotEllipseDialog", "RotEllipse", nullptr));
        label_6->setText(QCoreApplication::translate("RotEllipseDialog", "Ry", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("RotEllipseDialog", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("RotEllipseDialog", "X", nullptr));
        label->setText(QCoreApplication::translate("RotEllipseDialog", "\344\270\255\345\277\203", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("RotEllipseDialog", "OK", nullptr));
        label_5->setText(QCoreApplication::translate("RotEllipseDialog", "Rx", nullptr));
        label_4->setText(QCoreApplication::translate("RotEllipseDialog", "\345\215\212\345\276\204", nullptr));
        label_3->setText(QCoreApplication::translate("RotEllipseDialog", "Y", nullptr));
        label_7->setText(QCoreApplication::translate("RotEllipseDialog", "\350\247\222\345\272\246\357\274\210\345\272\246\357\274\211", nullptr));
        label_8->setText(QCoreApplication::translate("RotEllipseDialog", "\316\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RotEllipseDialog: public Ui_RotEllipseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROTELLIPSEDIALOG_H
