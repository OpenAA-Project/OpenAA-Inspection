/********************************************************************************
** Form generated from reading UI file 'Arc2Dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARC2DIALOG_H
#define UI_ARC2DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Arc2Dialog
{
public:
    QLabel *label_5;
    QLabel *label_7;
    QSpinBox *spinBoxRx;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_9;
    QLabel *label_6;
    QSpinBox *spinBoxRy;
    QDoubleSpinBox *doubleSpinBoxStartS;
    QLabel *label;
    QLabel *label_3;
    QPushButton *pushButtonOK;
    QDoubleSpinBox *doubleSpinBoxEndS;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxCy;
    QSpinBox *spinBoxCx;
    QLabel *label_8;

    void setupUi(QDialog *Arc2Dialog)
    {
        if (Arc2Dialog->objectName().isEmpty())
            Arc2Dialog->setObjectName("Arc2Dialog");
        Arc2Dialog->resize(200, 333);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Arc2Dialog->sizePolicy().hasHeightForWidth());
        Arc2Dialog->setSizePolicy(sizePolicy);
        label_5 = new QLabel(Arc2Dialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 130, 71, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(Arc2Dialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 190, 181, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        spinBoxRx = new QSpinBox(Arc2Dialog);
        spinBoxRx->setObjectName("spinBoxRx");
        spinBoxRx->setGeometry(QRect(20, 150, 71, 22));
        spinBoxRx->setMinimum(-99999999);
        spinBoxRx->setMaximum(99999999);
        label_2 = new QLabel(Arc2Dialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 40, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(Arc2Dialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 100, 181, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(Arc2Dialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(110, 220, 71, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(Arc2Dialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(110, 130, 71, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        spinBoxRy = new QSpinBox(Arc2Dialog);
        spinBoxRy->setObjectName("spinBoxRy");
        spinBoxRy->setGeometry(QRect(110, 150, 71, 22));
        spinBoxRy->setMinimum(-99999999);
        spinBoxRy->setMaximum(99999999);
        doubleSpinBoxStartS = new QDoubleSpinBox(Arc2Dialog);
        doubleSpinBoxStartS->setObjectName("doubleSpinBoxStartS");
        doubleSpinBoxStartS->setGeometry(QRect(20, 240, 71, 22));
        doubleSpinBoxStartS->setMaximum(360.000000000000000);
        label = new QLabel(Arc2Dialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(Arc2Dialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 40, 71, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(Arc2Dialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 280, 91, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        doubleSpinBoxEndS = new QDoubleSpinBox(Arc2Dialog);
        doubleSpinBoxEndS->setObjectName("doubleSpinBoxEndS");
        doubleSpinBoxEndS->setGeometry(QRect(110, 240, 71, 22));
        doubleSpinBoxEndS->setMaximum(360.000000000000000);
        pushButtonCancel = new QPushButton(Arc2Dialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 280, 81, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        spinBoxCy = new QSpinBox(Arc2Dialog);
        spinBoxCy->setObjectName("spinBoxCy");
        spinBoxCy->setGeometry(QRect(110, 60, 71, 22));
        spinBoxCy->setMinimum(-99999999);
        spinBoxCy->setMaximum(99999999);
        spinBoxCx = new QSpinBox(Arc2Dialog);
        spinBoxCx->setObjectName("spinBoxCx");
        spinBoxCx->setGeometry(QRect(20, 60, 71, 22));
        spinBoxCx->setMinimum(-99999999);
        spinBoxCx->setMaximum(99999999);
        label_8 = new QLabel(Arc2Dialog);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 220, 71, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter);

        retranslateUi(Arc2Dialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(Arc2Dialog);
    } // setupUi

    void retranslateUi(QDialog *Arc2Dialog)
    {
        Arc2Dialog->setWindowTitle(QCoreApplication::translate("Arc2Dialog", "Arc", nullptr));
        label_5->setText(QCoreApplication::translate("Arc2Dialog", "Rx", nullptr));
        label_7->setText(QCoreApplication::translate("Arc2Dialog", "\345\247\213\347\202\271\343\200\201\347\265\202\347\202\271\343\200\200\350\247\222\345\272\246\357\274\210\345\272\246\357\274\211", nullptr));
        label_2->setText(QCoreApplication::translate("Arc2Dialog", "X", nullptr));
        label_4->setText(QCoreApplication::translate("Arc2Dialog", "\345\215\212\345\276\204", nullptr));
        label_9->setText(QCoreApplication::translate("Arc2Dialog", "\345\247\213\347\202\271\350\247\222\345\272\246", nullptr));
        label_6->setText(QCoreApplication::translate("Arc2Dialog", "Ry", nullptr));
        label->setText(QCoreApplication::translate("Arc2Dialog", "\344\270\255\345\277\203", nullptr));
        label_3->setText(QCoreApplication::translate("Arc2Dialog", "Y", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("Arc2Dialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("Arc2Dialog", "Cancel", nullptr));
        label_8->setText(QCoreApplication::translate("Arc2Dialog", "\345\247\213\347\202\271\350\247\222\345\272\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Arc2Dialog: public Ui_Arc2Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARC2DIALOG_H
