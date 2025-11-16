/********************************************************************************
** Form generated from reading UI file 'SetLineWidthDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETLINEWIDTHDIALOG_H
#define UI_SETLINEWIDTHDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SetLineWidthDialog
{
public:
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxLineWidth;
    QLabel *label_2;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *SetLineWidthDialog)
    {
        if (SetLineWidthDialog->objectName().isEmpty())
            SetLineWidthDialog->setObjectName("SetLineWidthDialog");
        SetLineWidthDialog->resize(219, 134);
        pushButtonCancel = new QPushButton(SetLineWidthDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 80, 81, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        spinBoxLineWidth = new QSpinBox(SetLineWidthDialog);
        spinBoxLineWidth->setObjectName("spinBoxLineWidth");
        spinBoxLineWidth->setGeometry(QRect(20, 40, 111, 31));
        spinBoxLineWidth->setMinimum(0);
        spinBoxLineWidth->setMaximum(99999999);
        label_2 = new QLabel(SetLineWidthDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 10, 111, 31));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(SetLineWidthDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 80, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);

        retranslateUi(SetLineWidthDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SetLineWidthDialog);
    } // setupUi

    void retranslateUi(QDialog *SetLineWidthDialog)
    {
        SetLineWidthDialog->setWindowTitle(QCoreApplication::translate("SetLineWidthDialog", "Set Line width", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SetLineWidthDialog", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("SetLineWidthDialog", "\347\267\232\343\201\256\345\271\205", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SetLineWidthDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetLineWidthDialog: public Ui_SetLineWidthDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETLINEWIDTHDIALOG_H
