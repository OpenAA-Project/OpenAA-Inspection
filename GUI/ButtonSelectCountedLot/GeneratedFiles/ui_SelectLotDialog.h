/********************************************************************************
** Form generated from reading UI file 'SelectLotDialog.ui'
**
** Created: Mon Feb 20 05:07:00 2017
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLOTDIALOG_H
#define UI_SELECTLOTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SelectLotDialog
{
public:
    QFrame *frame;
    QFrame *frame_2;
    QLabel *label;
    QSpinBox *spinBoxLotCountNumber;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *SelectLotDialog)
    {
        if (SelectLotDialog->objectName().isEmpty())
            SelectLotDialog->setObjectName(QString::fromUtf8("SelectLotDialog"));
        SelectLotDialog->resize(549, 450);
        frame = new QFrame(SelectLotDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 50, 550, 400));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(SelectLotDialog);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(0, 0, 551, 51));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 91, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        spinBoxLotCountNumber = new QSpinBox(frame_2);
        spinBoxLotCountNumber->setObjectName(QString::fromUtf8("spinBoxLotCountNumber"));
        spinBoxLotCountNumber->setGeometry(QRect(120, 10, 71, 22));
        spinBoxLotCountNumber->setMaximum(99999999);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(210, 10, 331, 16));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(210, 30, 331, 16));

        retranslateUi(SelectLotDialog);

        QMetaObject::connectSlotsByName(SelectLotDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectLotDialog)
    {
        SelectLotDialog->setWindowTitle(QApplication::translate("SelectLotDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SelectLotDialog", "Lot count", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SelectLotDialog", "0 : unlimited", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SelectLotDialog", "[*] : Set number for count from 1", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SelectLotDialog: public Ui_SelectLotDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLOTDIALOG_H
