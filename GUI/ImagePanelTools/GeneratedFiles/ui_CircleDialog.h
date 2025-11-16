/********************************************************************************
** Form generated from reading UI file 'CircleDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CIRCLEDIALOG_H
#define UI_CIRCLEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CircleDialog
{
public:
    QPushButton *pushButtonOK;
    QLabel *label_3;
    QLabel *label;
    QSpinBox *spinBoxR;
    QLabel *label_5;
    QSpinBox *spinBoxCx;
    QSpinBox *spinBoxCy;
    QLabel *label_4;
    QPushButton *pushButtonCancel;
    QLabel *label_2;

    void setupUi(QDialog *CircleDialog)
    {
        if (CircleDialog->objectName().isEmpty())
            CircleDialog->setObjectName("CircleDialog");
        CircleDialog->resize(199, 256);
        pushButtonOK = new QPushButton(CircleDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 200, 91, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        label_3 = new QLabel(CircleDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 40, 71, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        label = new QLabel(CircleDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        spinBoxR = new QSpinBox(CircleDialog);
        spinBoxR->setObjectName("spinBoxR");
        spinBoxR->setGeometry(QRect(70, 150, 71, 22));
        spinBoxR->setMinimum(-99999999);
        spinBoxR->setMaximum(99999999);
        label_5 = new QLabel(CircleDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(70, 130, 71, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        spinBoxCx = new QSpinBox(CircleDialog);
        spinBoxCx->setObjectName("spinBoxCx");
        spinBoxCx->setGeometry(QRect(20, 60, 71, 22));
        spinBoxCx->setMinimum(-99999999);
        spinBoxCx->setMaximum(99999999);
        spinBoxCy = new QSpinBox(CircleDialog);
        spinBoxCy->setObjectName("spinBoxCy");
        spinBoxCy->setGeometry(QRect(110, 60, 71, 22));
        spinBoxCy->setMinimum(-99999999);
        spinBoxCy->setMaximum(99999999);
        label_4 = new QLabel(CircleDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 100, 181, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        pushButtonCancel = new QPushButton(CircleDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 200, 81, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        label_2 = new QLabel(CircleDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 40, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(CircleDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(CircleDialog);
    } // setupUi

    void retranslateUi(QDialog *CircleDialog)
    {
        CircleDialog->setWindowTitle(QCoreApplication::translate("CircleDialog", "Circle", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("CircleDialog", "OK", nullptr));
        label_3->setText(QCoreApplication::translate("CircleDialog", "Y", nullptr));
        label->setText(QCoreApplication::translate("CircleDialog", "\344\270\255\345\277\203", nullptr));
        label_5->setText(QCoreApplication::translate("CircleDialog", "R", nullptr));
        label_4->setText(QCoreApplication::translate("CircleDialog", "\345\215\212\345\276\204", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CircleDialog", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("CircleDialog", "X", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CircleDialog: public Ui_CircleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CIRCLEDIALOG_H
