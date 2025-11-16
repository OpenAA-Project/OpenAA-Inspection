/********************************************************************************
** Form generated from reading UI file 'EditZoomDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITZOOMDIALOG_H
#define UI_EDITZOOMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditZoomDialog
{
public:
    QLabel *label;
    QPushButton *pushButtonCancel;
    QDoubleSpinBox *doubleSpinBoxXZoomDir;
    QLabel *label_2;
    QPushButton *pushButtonOK;
    QDoubleSpinBox *doubleSpinBoxYZoomDir;

    void setupUi(QDialog *EditZoomDialog)
    {
        if (EditZoomDialog->objectName().isEmpty())
            EditZoomDialog->setObjectName("EditZoomDialog");
        EditZoomDialog->resize(211, 113);
        label = new QLabel(EditZoomDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 94, 16));
        pushButtonCancel = new QPushButton(EditZoomDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 60, 91, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        doubleSpinBoxXZoomDir = new QDoubleSpinBox(EditZoomDialog);
        doubleSpinBoxXZoomDir->setObjectName("doubleSpinBoxXZoomDir");
        doubleSpinBoxXZoomDir->setGeometry(QRect(10, 30, 91, 21));
        doubleSpinBoxXZoomDir->setDecimals(3);
        doubleSpinBoxXZoomDir->setMinimum(0.000000000000000);
        doubleSpinBoxXZoomDir->setMaximum(99999999.000000000000000);
        doubleSpinBoxXZoomDir->setValue(1.000000000000000);
        label_2 = new QLabel(EditZoomDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 10, 94, 16));
        pushButtonOK = new QPushButton(EditZoomDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 60, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        doubleSpinBoxYZoomDir = new QDoubleSpinBox(EditZoomDialog);
        doubleSpinBoxYZoomDir->setObjectName("doubleSpinBoxYZoomDir");
        doubleSpinBoxYZoomDir->setGeometry(QRect(110, 30, 91, 21));
        doubleSpinBoxYZoomDir->setDecimals(3);
        doubleSpinBoxYZoomDir->setMinimum(0.000000000000000);
        doubleSpinBoxYZoomDir->setMaximum(99999999.000000000000000);
        doubleSpinBoxYZoomDir->setValue(1.000000000000000);

        retranslateUi(EditZoomDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(EditZoomDialog);
    } // setupUi

    void retranslateUi(QDialog *EditZoomDialog)
    {
        EditZoomDialog->setWindowTitle(QCoreApplication::translate("EditZoomDialog", "Zoom gerber", nullptr));
        label->setText(QCoreApplication::translate("EditZoomDialog", "X zoom rate", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditZoomDialog", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("EditZoomDialog", "Y zoom rate", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditZoomDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditZoomDialog: public Ui_EditZoomDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITZOOMDIALOG_H
