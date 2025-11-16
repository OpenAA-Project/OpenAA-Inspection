/********************************************************************************
** Form generated from reading UI file 'EndlessLineDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENDLESSLINEDIALOG_H
#define UI_ENDLESSLINEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EndlessLineDialog
{
public:
    QSpinBox *spinBoxX;
    QLabel *label_4;
    QLabel *label;
    QPushButton *pushButtonCancel;
    QLabel *label_2;
    QSpinBox *spinBoxY;
    QLabel *label_3;
    QPushButton *pushButtonOK;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox;

    void setupUi(QDialog *EndlessLineDialog)
    {
        if (EndlessLineDialog->objectName().isEmpty())
            EndlessLineDialog->setObjectName("EndlessLineDialog");
        EndlessLineDialog->resize(201, 235);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EndlessLineDialog->sizePolicy().hasHeightForWidth());
        EndlessLineDialog->setSizePolicy(sizePolicy);
        spinBoxX = new QSpinBox(EndlessLineDialog);
        spinBoxX->setObjectName("spinBoxX");
        spinBoxX->setGeometry(QRect(20, 60, 71, 22));
        spinBoxX->setMinimum(-99999999);
        spinBoxX->setMaximum(99999999);
        label_4 = new QLabel(EndlessLineDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 100, 181, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label = new QLabel(EndlessLineDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        pushButtonCancel = new QPushButton(EndlessLineDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 180, 81, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        label_2 = new QLabel(EndlessLineDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 40, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        spinBoxY = new QSpinBox(EndlessLineDialog);
        spinBoxY->setObjectName("spinBoxY");
        spinBoxY->setGeometry(QRect(110, 60, 71, 22));
        spinBoxY->setMinimum(-99999999);
        spinBoxY->setMaximum(99999999);
        label_3 = new QLabel(EndlessLineDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 40, 71, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(EndlessLineDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 180, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        label_5 = new QLabel(EndlessLineDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 130, 71, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        doubleSpinBox = new QDoubleSpinBox(EndlessLineDialog);
        doubleSpinBox->setObjectName("doubleSpinBox");
        doubleSpinBox->setGeometry(QRect(90, 130, 71, 22));
        doubleSpinBox->setMaximum(360.000000000000000);

        retranslateUi(EndlessLineDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(EndlessLineDialog);
    } // setupUi

    void retranslateUi(QDialog *EndlessLineDialog)
    {
        EndlessLineDialog->setWindowTitle(QCoreApplication::translate("EndlessLineDialog", "Endless line", nullptr));
        label_4->setText(QCoreApplication::translate("EndlessLineDialog", "\350\247\222\345\272\246\357\274\210\345\272\246\357\274\211", nullptr));
        label->setText(QCoreApplication::translate("EndlessLineDialog", "\351\200\232\351\201\216\347\202\271", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EndlessLineDialog", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("EndlessLineDialog", "X", nullptr));
        label_3->setText(QCoreApplication::translate("EndlessLineDialog", "Y", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EndlessLineDialog", "OK", nullptr));
        label_5->setText(QCoreApplication::translate("EndlessLineDialog", "\316\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EndlessLineDialog: public Ui_EndlessLineDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENDLESSLINEDIALOG_H
