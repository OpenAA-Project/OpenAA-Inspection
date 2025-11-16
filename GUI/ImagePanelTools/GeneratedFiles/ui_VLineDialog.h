/********************************************************************************
** Form generated from reading UI file 'VLineDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VLINEDIALOG_H
#define UI_VLINEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_VLineDialog
{
public:
    QLabel *label_4;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxX1;
    QPushButton *pushButtonOK;
    QLabel *label_5;
    QLabel *label;
    QSpinBox *spinBoxLen;
    QSpinBox *spinBoxY1;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *VLineDialog)
    {
        if (VLineDialog->objectName().isEmpty())
            VLineDialog->setObjectName("VLineDialog");
        VLineDialog->resize(201, 223);
        label_4 = new QLabel(VLineDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 100, 181, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        pushButtonCancel = new QPushButton(VLineDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 170, 81, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        spinBoxX1 = new QSpinBox(VLineDialog);
        spinBoxX1->setObjectName("spinBoxX1");
        spinBoxX1->setGeometry(QRect(20, 60, 71, 22));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spinBoxX1->sizePolicy().hasHeightForWidth());
        spinBoxX1->setSizePolicy(sizePolicy);
        spinBoxX1->setMinimum(-99999999);
        spinBoxX1->setMaximum(99999999);
        pushButtonOK = new QPushButton(VLineDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 170, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        label_5 = new QLabel(VLineDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 130, 91, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        label = new QLabel(VLineDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        spinBoxLen = new QSpinBox(VLineDialog);
        spinBoxLen->setObjectName("spinBoxLen");
        spinBoxLen->setGeometry(QRect(110, 130, 71, 22));
        spinBoxLen->setMinimum(-99999999);
        spinBoxLen->setMaximum(99999999);
        spinBoxY1 = new QSpinBox(VLineDialog);
        spinBoxY1->setObjectName("spinBoxY1");
        spinBoxY1->setGeometry(QRect(110, 60, 71, 22));
        spinBoxY1->setMinimum(-99999999);
        spinBoxY1->setMaximum(99999999);
        label_2 = new QLabel(VLineDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 40, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(VLineDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 40, 71, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);

        retranslateUi(VLineDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(VLineDialog);
    } // setupUi

    void retranslateUi(QDialog *VLineDialog)
    {
        VLineDialog->setWindowTitle(QCoreApplication::translate("VLineDialog", "VLine", nullptr));
        label_4->setText(QCoreApplication::translate("VLineDialog", "\347\265\202\347\202\271", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("VLineDialog", "Cancel", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("VLineDialog", "OK", nullptr));
        label_5->setText(QCoreApplication::translate("VLineDialog", "\344\270\213\346\226\271\345\220\221\343\201\256\351\225\267\343\201\225", nullptr));
        label->setText(QCoreApplication::translate("VLineDialog", "\345\247\213\347\202\271", nullptr));
        label_2->setText(QCoreApplication::translate("VLineDialog", "X", nullptr));
        label_3->setText(QCoreApplication::translate("VLineDialog", "Y", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VLineDialog: public Ui_VLineDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VLINEDIALOG_H
