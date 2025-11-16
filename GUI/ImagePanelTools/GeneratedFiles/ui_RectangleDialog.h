/********************************************************************************
** Form generated from reading UI file 'RectangleDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECTANGLEDIALOG_H
#define UI_RECTANGLEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_RectangleDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBoxX1;
    QSpinBox *spinBoxY1;
    QSpinBox *spinBoxX2;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *spinBoxY2;
    QLabel *label_6;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *RectangleDialog)
    {
        if (RectangleDialog->objectName().isEmpty())
            RectangleDialog->setObjectName("RectangleDialog");
        RectangleDialog->resize(202, 262);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RectangleDialog->sizePolicy().hasHeightForWidth());
        RectangleDialog->setSizePolicy(sizePolicy);
        label = new QLabel(RectangleDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(RectangleDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 40, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(RectangleDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 40, 71, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        spinBoxX1 = new QSpinBox(RectangleDialog);
        spinBoxX1->setObjectName("spinBoxX1");
        spinBoxX1->setGeometry(QRect(20, 60, 71, 22));
        spinBoxX1->setMinimum(-99999999);
        spinBoxX1->setMaximum(99999999);
        spinBoxY1 = new QSpinBox(RectangleDialog);
        spinBoxY1->setObjectName("spinBoxY1");
        spinBoxY1->setGeometry(QRect(110, 60, 71, 22));
        spinBoxY1->setMinimum(-99999999);
        spinBoxY1->setMaximum(99999999);
        spinBoxX2 = new QSpinBox(RectangleDialog);
        spinBoxX2->setObjectName("spinBoxX2");
        spinBoxX2->setGeometry(QRect(20, 150, 71, 22));
        spinBoxX2->setMinimum(-99999999);
        spinBoxX2->setMaximum(99999999);
        label_4 = new QLabel(RectangleDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 100, 181, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(RectangleDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 130, 71, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        spinBoxY2 = new QSpinBox(RectangleDialog);
        spinBoxY2->setObjectName("spinBoxY2");
        spinBoxY2->setGeometry(QRect(110, 150, 71, 22));
        spinBoxY2->setMinimum(-99999999);
        spinBoxY2->setMaximum(99999999);
        label_6 = new QLabel(RectangleDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(110, 130, 71, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(RectangleDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 200, 91, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(RectangleDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 200, 81, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(RectangleDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(RectangleDialog);
    } // setupUi

    void retranslateUi(QDialog *RectangleDialog)
    {
        RectangleDialog->setWindowTitle(QCoreApplication::translate("RectangleDialog", "Rectangle", nullptr));
        label->setText(QCoreApplication::translate("RectangleDialog", "\345\267\246\344\270\212", nullptr));
        label_2->setText(QCoreApplication::translate("RectangleDialog", "X", nullptr));
        label_3->setText(QCoreApplication::translate("RectangleDialog", "Y", nullptr));
        label_4->setText(QCoreApplication::translate("RectangleDialog", "\345\217\263\344\270\213", nullptr));
        label_5->setText(QCoreApplication::translate("RectangleDialog", "X", nullptr));
        label_6->setText(QCoreApplication::translate("RectangleDialog", "Y", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("RectangleDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("RectangleDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RectangleDialog: public Ui_RectangleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECTANGLEDIALOG_H
