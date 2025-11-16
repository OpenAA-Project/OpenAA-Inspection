/********************************************************************************
** Form generated from reading UI file 'MoveAllForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOVEALLFORM_H
#define UI_MOVEALLFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MoveAllFormClass
{
public:
    QCheckBox *checkBoxMoveMasterImage;
    QCheckBox *checkBoxMoveTargetImage;
    QSpinBox *spinBoxMoveX;
    QSpinBox *spinBoxMoveY;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QFrame *frame;
    QLabel *label_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QDialog *MoveAllFormClass)
    {
        if (MoveAllFormClass->objectName().isEmpty())
            MoveAllFormClass->setObjectName("MoveAllFormClass");
        MoveAllFormClass->resize(227, 310);
        checkBoxMoveMasterImage = new QCheckBox(MoveAllFormClass);
        checkBoxMoveMasterImage->setObjectName("checkBoxMoveMasterImage");
        checkBoxMoveMasterImage->setGeometry(QRect(40, 10, 181, 18));
        checkBoxMoveTargetImage = new QCheckBox(MoveAllFormClass);
        checkBoxMoveTargetImage->setObjectName("checkBoxMoveTargetImage");
        checkBoxMoveTargetImage->setGeometry(QRect(40, 40, 181, 18));
        spinBoxMoveX = new QSpinBox(MoveAllFormClass);
        spinBoxMoveX->setObjectName("spinBoxMoveX");
        spinBoxMoveX->setGeometry(QRect(160, 90, 61, 22));
        spinBoxMoveX->setMinimum(-999999);
        spinBoxMoveX->setMaximum(999999);
        spinBoxMoveY = new QSpinBox(MoveAllFormClass);
        spinBoxMoveY->setObjectName("spinBoxMoveY");
        spinBoxMoveY->setGeometry(QRect(160, 110, 61, 22));
        spinBoxMoveY->setMinimum(-999999);
        spinBoxMoveY->setMaximum(999999);
        label = new QLabel(MoveAllFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 70, 211, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(MoveAllFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 90, 151, 21));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(MoveAllFormClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 110, 151, 21));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonOK = new QPushButton(MoveAllFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 270, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Start.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(MoveAllFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 270, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        frame = new QFrame(MoveAllFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 140, 211, 41));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 10, 191, 16));
        scrollArea = new QScrollArea(MoveAllFormClass);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(20, 190, 191, 61));
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 189, 59));
        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(MoveAllFormClass);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(MoveAllFormClass);
    } // setupUi

    void retranslateUi(QDialog *MoveAllFormClass)
    {
        MoveAllFormClass->setWindowTitle(QCoreApplication::translate("MoveAllFormClass", "MoveAllForm", nullptr));
        checkBoxMoveMasterImage->setText(QCoreApplication::translate("MoveAllFormClass", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217\343\201\256\347\247\273\345\213\225", nullptr));
        checkBoxMoveTargetImage->setText(QCoreApplication::translate("MoveAllFormClass", "\346\244\234\346\237\273\347\224\273\345\203\217\343\201\256\347\247\273\345\213\225", nullptr));
        label->setText(QCoreApplication::translate("MoveAllFormClass", "\347\247\273\345\213\225\351\207\217", nullptr));
        label_2->setText(QCoreApplication::translate("MoveAllFormClass", "X : \346\250\252\346\226\271\345\220\221\343\200\200\345\217\263\347\247\273\345\213\225\343\201\214\343\203\227\343\203\251\343\202\271", nullptr));
        label_3->setText(QCoreApplication::translate("MoveAllFormClass", "Y : \347\270\246\346\226\271\345\220\221\343\200\200\344\270\213\347\247\273\345\213\225\343\201\214\343\203\227\343\203\251\343\202\271", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("MoveAllFormClass", "\345\256\237\350\241\214", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("MoveAllFormClass", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        label_4->setText(QCoreApplication::translate("MoveAllFormClass", "\343\203\232\343\203\274\343\202\270\345\242\203\347\225\214\343\202\222\350\266\205\343\201\210\343\202\213\351\203\250\345\210\206\343\201\257\347\240\264\346\243\204\343\201\225\343\202\214\343\201\276\343\201\231", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MoveAllFormClass: public Ui_MoveAllFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOVEALLFORM_H
