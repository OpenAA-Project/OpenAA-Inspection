/********************************************************************************
** Form generated from reading UI file 'LineDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEDIALOG_H
#define UI_LINEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_LineDialog
{
public:
    QSpinBox *spinBoxX1;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_6;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxX2;
    QSpinBox *spinBoxY2;
    QLabel *label_2;
    QSpinBox *spinBoxY1;
    QLabel *label_3;
    QPushButton *pushButtonOK;
    QLabel *label_5;

    void setupUi(QDialog *LineDialog)
    {
        if (LineDialog->objectName().isEmpty())
            LineDialog->setObjectName("LineDialog");
        LineDialog->resize(200, 254);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LineDialog->sizePolicy().hasHeightForWidth());
        LineDialog->setSizePolicy(sizePolicy);
        spinBoxX1 = new QSpinBox(LineDialog);
        spinBoxX1->setObjectName("spinBoxX1");
        spinBoxX1->setGeometry(QRect(20, 60, 71, 22));
        sizePolicy.setHeightForWidth(spinBoxX1->sizePolicy().hasHeightForWidth());
        spinBoxX1->setSizePolicy(sizePolicy);
        spinBoxX1->setMinimum(-99999999);
        spinBoxX1->setMaximum(99999999);
        label_4 = new QLabel(LineDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 100, 181, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label = new QLabel(LineDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(LineDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(110, 130, 71, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        pushButtonCancel = new QPushButton(LineDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 200, 81, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        spinBoxX2 = new QSpinBox(LineDialog);
        spinBoxX2->setObjectName("spinBoxX2");
        spinBoxX2->setGeometry(QRect(20, 150, 71, 22));
        spinBoxX2->setMinimum(-99999999);
        spinBoxX2->setMaximum(99999999);
        spinBoxY2 = new QSpinBox(LineDialog);
        spinBoxY2->setObjectName("spinBoxY2");
        spinBoxY2->setGeometry(QRect(110, 150, 71, 22));
        spinBoxY2->setMinimum(-99999999);
        spinBoxY2->setMaximum(99999999);
        label_2 = new QLabel(LineDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 40, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        spinBoxY1 = new QSpinBox(LineDialog);
        spinBoxY1->setObjectName("spinBoxY1");
        spinBoxY1->setGeometry(QRect(110, 60, 71, 22));
        spinBoxY1->setMinimum(-99999999);
        spinBoxY1->setMaximum(99999999);
        label_3 = new QLabel(LineDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 40, 71, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(LineDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 200, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        label_5 = new QLabel(LineDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 130, 71, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);

        retranslateUi(LineDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(LineDialog);
    } // setupUi

    void retranslateUi(QDialog *LineDialog)
    {
        LineDialog->setWindowTitle(QCoreApplication::translate("LineDialog", "Line", nullptr));
        label_4->setText(QCoreApplication::translate("LineDialog", "\347\265\202\347\202\271", nullptr));
        label->setText(QCoreApplication::translate("LineDialog", "\345\247\213\347\202\271", nullptr));
        label_6->setText(QCoreApplication::translate("LineDialog", "Y", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("LineDialog", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("LineDialog", "X", nullptr));
        label_3->setText(QCoreApplication::translate("LineDialog", "Y", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("LineDialog", "OK", nullptr));
        label_5->setText(QCoreApplication::translate("LineDialog", "X", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LineDialog: public Ui_LineDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEDIALOG_H
