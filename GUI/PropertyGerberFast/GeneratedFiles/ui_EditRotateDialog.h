/********************************************************************************
** Form generated from reading UI file 'EditRotateDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITROTATEDIALOG_H
#define UI_EDITROTATEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditRotateDialog
{
public:
    QLabel *label_3;
    QLabel *label;
    QPushButton *pushButtonCancel;
    QDoubleSpinBox *doubleSpinBoxAngle;
    QPushButton *pushButtonOK;
    QFrame *frame;
    QPushButton *pushButton180;
    QPushButton *pushButton90;
    QPushButton *pushButton270;

    void setupUi(QDialog *EditRotateDialog)
    {
        if (EditRotateDialog->objectName().isEmpty())
            EditRotateDialog->setObjectName("EditRotateDialog");
        EditRotateDialog->resize(322, 202);
        label_3 = new QLabel(EditRotateDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 60, 81, 16));
        label = new QLabel(EditRotateDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 141, 20));
        pushButtonCancel = new QPushButton(EditRotateDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(90, 150, 151, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        doubleSpinBoxAngle = new QDoubleSpinBox(EditRotateDialog);
        doubleSpinBoxAngle->setObjectName("doubleSpinBoxAngle");
        doubleSpinBoxAngle->setGeometry(QRect(40, 30, 91, 21));
        doubleSpinBoxAngle->setDecimals(3);
        doubleSpinBoxAngle->setMinimum(0.000000000000000);
        doubleSpinBoxAngle->setMaximum(360.000000000000000);
        pushButtonOK = new QPushButton(EditRotateDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 90, 141, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        frame = new QFrame(EditRotateDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(180, 10, 131, 131));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        pushButton180 = new QPushButton(frame);
        pushButton180->setObjectName("pushButton180");
        pushButton180->setGeometry(QRect(10, 50, 112, 34));
        pushButton90 = new QPushButton(frame);
        pushButton90->setObjectName("pushButton90");
        pushButton90->setGeometry(QRect(10, 10, 112, 34));
        pushButton270 = new QPushButton(frame);
        pushButton270->setObjectName("pushButton270");
        pushButton270->setGeometry(QRect(10, 90, 112, 34));

        retranslateUi(EditRotateDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(EditRotateDialog);
    } // setupUi

    void retranslateUi(QDialog *EditRotateDialog)
    {
        EditRotateDialog->setWindowTitle(QCoreApplication::translate("EditRotateDialog", "Rotate gerber", nullptr));
        label_3->setText(QCoreApplication::translate("EditRotateDialog", "Clock wise", nullptr));
        label->setText(QCoreApplication::translate("EditRotateDialog", "Rotated degree", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditRotateDialog", "Cancel", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditRotateDialog", "OK", nullptr));
        pushButton180->setText(QCoreApplication::translate("EditRotateDialog", "180 degree", nullptr));
        pushButton90->setText(QCoreApplication::translate("EditRotateDialog", "90 degree", nullptr));
        pushButton270->setText(QCoreApplication::translate("EditRotateDialog", "-90 degree", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditRotateDialog: public Ui_EditRotateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITROTATEDIALOG_H
