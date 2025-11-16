/********************************************************************************
** Form generated from reading UI file 'InputAlignmentPointForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTALIGNMENTPOINTFORM_H
#define UI_INPUTALIGNMENTPOINTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_InputAlignmentPointFormClass
{
public:
    QPushButton *ButtonOK;
    QPushButton *ButtonCancel;
    QPushButton *ButtonDefault;
    QCheckBox *checkBoxUsageGlobal;
    QLabel *label_2;
    QSpinBox *EditGroupNumber;
    QFrame *frame;
    QLabel *label_3;
    QSpinBox *EditMoveDotY;
    QSpinBox *EditMoveDot;
    QLabel *label;
    QLabel *label_6;
    QFrame *frame_2;
    QLabel *label_5;
    QLabel *label_4;
    QSpinBox *EditMoveDot2;
    QSpinBox *EditMoveDotY2;
    QLabel *label_7;

    void setupUi(QDialog *InputAlignmentPointFormClass)
    {
        if (InputAlignmentPointFormClass->objectName().isEmpty())
            InputAlignmentPointFormClass->setObjectName(QString::fromUtf8("InputAlignmentPointFormClass"));
        InputAlignmentPointFormClass->resize(449, 165);
        ButtonOK = new QPushButton(InputAlignmentPointFormClass);
        ButtonOK->setObjectName(QString::fromUtf8("ButtonOK"));
        ButtonOK->setGeometry(QRect(70, 130, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonOK->setIcon(icon);
        ButtonCancel = new QPushButton(InputAlignmentPointFormClass);
        ButtonCancel->setObjectName(QString::fromUtf8("ButtonCancel"));
        ButtonCancel->setGeometry(QRect(270, 130, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonCancel->setIcon(icon1);
        ButtonDefault = new QPushButton(InputAlignmentPointFormClass);
        ButtonDefault->setObjectName(QString::fromUtf8("ButtonDefault"));
        ButtonDefault->setGeometry(QRect(170, 130, 91, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Default.png"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonDefault->setIcon(icon2);
        checkBoxUsageGlobal = new QCheckBox(InputAlignmentPointFormClass);
        checkBoxUsageGlobal->setObjectName(QString::fromUtf8("checkBoxUsageGlobal"));
        checkBoxUsageGlobal->setGeometry(QRect(100, 100, 121, 21));
        label_2 = new QLabel(InputAlignmentPointFormClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(230, 80, 81, 16));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditGroupNumber = new QSpinBox(InputAlignmentPointFormClass);
        EditGroupNumber->setObjectName(QString::fromUtf8("EditGroupNumber"));
        EditGroupNumber->setGeometry(QRect(230, 100, 81, 22));
        EditGroupNumber->setMaximum(99999);
        frame = new QFrame(InputAlignmentPointFormClass);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 0, 211, 71));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(110, 20, 91, 16));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMoveDotY = new QSpinBox(frame);
        EditMoveDotY->setObjectName(QString::fromUtf8("EditMoveDotY"));
        EditMoveDotY->setGeometry(QRect(110, 40, 91, 22));
        EditMoveDotY->setMaximum(99999);
        EditMoveDot = new QSpinBox(frame);
        EditMoveDot->setObjectName(QString::fromUtf8("EditMoveDot"));
        EditMoveDot->setGeometry(QRect(10, 40, 91, 22));
        EditMoveDot->setMaximum(99999);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 91, 16));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(0, 0, 211, 16));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_2 = new QFrame(InputAlignmentPointFormClass);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(230, 0, 211, 71));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(frame_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 20, 91, 16));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(frame_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(110, 20, 91, 16));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMoveDot2 = new QSpinBox(frame_2);
        EditMoveDot2->setObjectName(QString::fromUtf8("EditMoveDot2"));
        EditMoveDot2->setGeometry(QRect(10, 40, 91, 22));
        EditMoveDot2->setMaximum(99999);
        EditMoveDotY2 = new QSpinBox(frame_2);
        EditMoveDotY2->setObjectName(QString::fromUtf8("EditMoveDotY2"));
        EditMoveDotY2->setGeometry(QRect(110, 40, 91, 22));
        EditMoveDotY2->setMaximum(99999);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(0, 0, 211, 16));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(InputAlignmentPointFormClass);

        ButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(InputAlignmentPointFormClass);
    } // setupUi

    void retranslateUi(QDialog *InputAlignmentPointFormClass)
    {
        InputAlignmentPointFormClass->setWindowTitle(QCoreApplication::translate("InputAlignmentPointFormClass", "InputAlignmentPointForm", nullptr));
        ButtonOK->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "OK", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "Cancel", nullptr));
        ButtonDefault->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "Default", nullptr));
        checkBoxUsageGlobal->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "Global usage", nullptr));
        label_2->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "\343\202\260\343\203\253\343\203\274\343\203\227\347\225\252\345\217\267", nullptr));
        label_3->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "\346\216\242\347\264\242\350\267\235\351\233\242 Y", nullptr));
        label->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "\346\216\242\347\264\242\350\267\235\351\233\242 X", nullptr));
        label_6->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "\346\234\200\345\210\235\343\201\256\346\216\242\347\264\242", nullptr));
        label_5->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "\346\216\242\347\264\242\350\267\235\351\233\242 X", nullptr));
        label_4->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "\346\216\242\347\264\242\350\267\235\351\233\242 Y", nullptr));
        label_7->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "\357\274\222\347\225\252\347\233\256\343\201\256\346\216\242\347\264\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputAlignmentPointFormClass: public Ui_InputAlignmentPointFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTALIGNMENTPOINTFORM_H
