/********************************************************************************
** Form generated from reading UI file 'EllipseDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ELLIPSEDIALOG_H
#define UI_ELLIPSEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EllipseDialog
{
public:
    QSpinBox *spinBoxCx;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_6;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxRx;
    QSpinBox *spinBoxRy;
    QLabel *label_2;
    QSpinBox *spinBoxCy;
    QLabel *label_3;
    QPushButton *pushButtonOK;
    QLabel *label_5;

    void setupUi(QDialog *EllipseDialog)
    {
        if (EllipseDialog->objectName().isEmpty())
            EllipseDialog->setObjectName("EllipseDialog");
        EllipseDialog->resize(200, 252);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EllipseDialog->sizePolicy().hasHeightForWidth());
        EllipseDialog->setSizePolicy(sizePolicy);
        spinBoxCx = new QSpinBox(EllipseDialog);
        spinBoxCx->setObjectName("spinBoxCx");
        spinBoxCx->setGeometry(QRect(20, 60, 71, 22));
        spinBoxCx->setMinimum(-99999999);
        spinBoxCx->setMaximum(99999999);
        label_4 = new QLabel(EllipseDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 100, 181, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label = new QLabel(EllipseDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(EllipseDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(110, 130, 71, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        pushButtonCancel = new QPushButton(EllipseDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 200, 81, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        spinBoxRx = new QSpinBox(EllipseDialog);
        spinBoxRx->setObjectName("spinBoxRx");
        spinBoxRx->setGeometry(QRect(20, 150, 71, 22));
        spinBoxRx->setMinimum(-99999999);
        spinBoxRx->setMaximum(99999999);
        spinBoxRy = new QSpinBox(EllipseDialog);
        spinBoxRy->setObjectName("spinBoxRy");
        spinBoxRy->setGeometry(QRect(110, 150, 71, 22));
        spinBoxRy->setMinimum(-99999999);
        spinBoxRy->setMaximum(99999999);
        label_2 = new QLabel(EllipseDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 40, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        spinBoxCy = new QSpinBox(EllipseDialog);
        spinBoxCy->setObjectName("spinBoxCy");
        spinBoxCy->setGeometry(QRect(110, 60, 71, 22));
        spinBoxCy->setMinimum(-99999999);
        spinBoxCy->setMaximum(99999999);
        label_3 = new QLabel(EllipseDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 40, 71, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(EllipseDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 200, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        label_5 = new QLabel(EllipseDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 130, 71, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);

        retranslateUi(EllipseDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(EllipseDialog);
    } // setupUi

    void retranslateUi(QDialog *EllipseDialog)
    {
        EllipseDialog->setWindowTitle(QCoreApplication::translate("EllipseDialog", "Ellipse", nullptr));
        label_4->setText(QCoreApplication::translate("EllipseDialog", "\345\215\212\345\276\204", nullptr));
        label->setText(QCoreApplication::translate("EllipseDialog", "\344\270\255\345\277\203", nullptr));
        label_6->setText(QCoreApplication::translate("EllipseDialog", "Ry", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EllipseDialog", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("EllipseDialog", "X", nullptr));
        label_3->setText(QCoreApplication::translate("EllipseDialog", "Y", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EllipseDialog", "OK", nullptr));
        label_5->setText(QCoreApplication::translate("EllipseDialog", "Rx", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EllipseDialog: public Ui_EllipseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ELLIPSEDIALOG_H
