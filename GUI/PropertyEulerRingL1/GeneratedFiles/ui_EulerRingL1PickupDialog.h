/********************************************************************************
** Form generated from reading UI file 'EulerRingL1PickupDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EULERRINGL1PICKUPDIALOG_H
#define UI_EULERRINGL1PICKUPDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EulerRingL1PickupDialog
{
public:
    QSpinBox *EditPickupL;
    QLabel *label_7;
    QPushButton *ButtonReflect;
    QPushButton *ButtonClose;
    QSpinBox *EditPickupH;
    QLabel *label_8;
    QFrame *frameLineGraph;

    void setupUi(QDialog *EulerRingL1PickupDialog)
    {
        if (EulerRingL1PickupDialog->objectName().isEmpty())
            EulerRingL1PickupDialog->setObjectName("EulerRingL1PickupDialog");
        EulerRingL1PickupDialog->resize(729, 527);
        EditPickupL = new QSpinBox(EulerRingL1PickupDialog);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(190, 460, 61, 22));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(192, 192, 192, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        EditPickupL->setPalette(palette);
        EditPickupL->setMaximum(255);
        label_7 = new QLabel(EulerRingL1PickupDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(70, 460, 111, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonReflect = new QPushButton(EulerRingL1PickupDialog);
        ButtonReflect->setObjectName("ButtonReflect");
        ButtonReflect->setGeometry(QRect(530, 430, 171, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Reflection.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonReflect->setIcon(icon);
        ButtonClose = new QPushButton(EulerRingL1PickupDialog);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(530, 480, 171, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonClose->setIcon(icon1);
        EditPickupH = new QSpinBox(EulerRingL1PickupDialog);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(190, 490, 61, 22));
        EditPickupH->setMaximum(255);
        label_8 = new QLabel(EulerRingL1PickupDialog);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(70, 490, 111, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameLineGraph = new QFrame(EulerRingL1PickupDialog);
        frameLineGraph->setObjectName("frameLineGraph");
        frameLineGraph->setGeometry(QRect(10, 10, 711, 381));
        frameLineGraph->setFrameShape(QFrame::NoFrame);
        frameLineGraph->setFrameShadow(QFrame::Plain);

        retranslateUi(EulerRingL1PickupDialog);

        QMetaObject::connectSlotsByName(EulerRingL1PickupDialog);
    } // setupUi

    void retranslateUi(QDialog *EulerRingL1PickupDialog)
    {
        EulerRingL1PickupDialog->setWindowTitle(QCoreApplication::translate("EulerRingL1PickupDialog", "EulerRingL1 Pickup", nullptr));
        label_7->setText(QCoreApplication::translate("EulerRingL1PickupDialog", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
        ButtonReflect->setText(QCoreApplication::translate("EulerRingL1PickupDialog", "\345\217\215\346\230\240", nullptr));
        ButtonClose->setText(QCoreApplication::translate("EulerRingL1PickupDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_8->setText(QCoreApplication::translate("EulerRingL1PickupDialog", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EulerRingL1PickupDialog: public Ui_EulerRingL1PickupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EULERRINGL1PICKUPDIALOG_H
