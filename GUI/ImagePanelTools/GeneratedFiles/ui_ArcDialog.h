/********************************************************************************
** Form generated from reading UI file 'ArcDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARCDIALOG_H
#define UI_ARCDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ArcDialog
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
    QLabel *label_8;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBoxStartS;
    QLabel *label_9;
    QDoubleSpinBox *doubleSpinBoxEndS;

    void setupUi(QDialog *ArcDialog)
    {
        if (ArcDialog->objectName().isEmpty())
            ArcDialog->setObjectName("ArcDialog");
        ArcDialog->resize(201, 338);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ArcDialog->sizePolicy().hasHeightForWidth());
        ArcDialog->setSizePolicy(sizePolicy);
        ArcDialog->setWindowOpacity(-2.000000000000000);
        spinBoxCx = new QSpinBox(ArcDialog);
        spinBoxCx->setObjectName("spinBoxCx");
        spinBoxCx->setGeometry(QRect(20, 60, 71, 22));
        spinBoxCx->setMinimum(-99999999);
        spinBoxCx->setMaximum(99999999);
        label_6 = new QLabel(ArcDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(110, 130, 71, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        pushButtonCancel = new QPushButton(ArcDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 280, 81, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        label_2 = new QLabel(ArcDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 40, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label = new QLabel(ArcDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        spinBoxCy = new QSpinBox(ArcDialog);
        spinBoxCy->setObjectName("spinBoxCy");
        spinBoxCy->setGeometry(QRect(110, 60, 71, 22));
        spinBoxCy->setMinimum(-99999999);
        spinBoxCy->setMaximum(99999999);
        pushButtonOK = new QPushButton(ArcDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 280, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        spinBoxRx = new QSpinBox(ArcDialog);
        spinBoxRx->setObjectName("spinBoxRx");
        spinBoxRx->setGeometry(QRect(20, 150, 71, 22));
        spinBoxRx->setMinimum(-99999999);
        spinBoxRx->setMaximum(99999999);
        label_5 = new QLabel(ArcDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 130, 71, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        spinBoxRy = new QSpinBox(ArcDialog);
        spinBoxRy->setObjectName("spinBoxRy");
        spinBoxRy->setGeometry(QRect(110, 150, 71, 22));
        spinBoxRy->setMinimum(-99999999);
        spinBoxRy->setMaximum(99999999);
        label_4 = new QLabel(ArcDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 100, 181, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(ArcDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 40, 71, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(ArcDialog);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 220, 71, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(ArcDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 190, 181, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        doubleSpinBoxStartS = new QDoubleSpinBox(ArcDialog);
        doubleSpinBoxStartS->setObjectName("doubleSpinBoxStartS");
        doubleSpinBoxStartS->setGeometry(QRect(20, 240, 71, 22));
        doubleSpinBoxStartS->setMaximum(360.000000000000000);
        label_9 = new QLabel(ArcDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(110, 220, 71, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter);
        doubleSpinBoxEndS = new QDoubleSpinBox(ArcDialog);
        doubleSpinBoxEndS->setObjectName("doubleSpinBoxEndS");
        doubleSpinBoxEndS->setGeometry(QRect(110, 240, 71, 22));
        doubleSpinBoxEndS->setMaximum(360.000000000000000);

        retranslateUi(ArcDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(ArcDialog);
    } // setupUi

    void retranslateUi(QDialog *ArcDialog)
    {
        ArcDialog->setWindowTitle(QCoreApplication::translate("ArcDialog", "Arc", nullptr));
        label_6->setText(QCoreApplication::translate("ArcDialog", "Ry", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("ArcDialog", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("ArcDialog", "X", nullptr));
        label->setText(QCoreApplication::translate("ArcDialog", "\344\270\255\345\277\203", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("ArcDialog", "OK", nullptr));
        label_5->setText(QCoreApplication::translate("ArcDialog", "Rx", nullptr));
        label_4->setText(QCoreApplication::translate("ArcDialog", "\345\215\212\345\276\204", nullptr));
        label_3->setText(QCoreApplication::translate("ArcDialog", "Y", nullptr));
        label_8->setText(QCoreApplication::translate("ArcDialog", "\345\247\213\347\202\271\350\247\222\345\272\246", nullptr));
        label_7->setText(QCoreApplication::translate("ArcDialog", "\345\247\213\347\202\271\343\200\201\347\265\202\347\202\271\343\200\200\350\247\222\345\272\246\357\274\210\345\272\246\357\274\211", nullptr));
        label_9->setText(QCoreApplication::translate("ArcDialog", "\345\247\213\347\202\271\350\247\222\345\272\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ArcDialog: public Ui_ArcDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARCDIALOG_H
