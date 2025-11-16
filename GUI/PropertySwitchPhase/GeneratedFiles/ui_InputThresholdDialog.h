/********************************************************************************
** Form generated from reading UI file 'InputThresholdDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTTHRESHOLDDIALOG_H
#define UI_INPUTTHRESHOLDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_InputThresholdDialog
{
public:
    QLabel *label;
    QSpinBox *spinBoxSearchDot;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *InputThresholdDialog)
    {
        if (InputThresholdDialog->objectName().isEmpty())
            InputThresholdDialog->setObjectName("InputThresholdDialog");
        InputThresholdDialog->resize(208, 122);
        label = new QLabel(InputThresholdDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 101, 21));
        spinBoxSearchDot = new QSpinBox(InputThresholdDialog);
        spinBoxSearchDot->setObjectName("spinBoxSearchDot");
        spinBoxSearchDot->setGeometry(QRect(30, 30, 111, 24));
        spinBoxSearchDot->setMaximum(999999);
        pushButtonOK = new QPushButton(InputThresholdDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 70, 91, 34));
        pushButtonCancel = new QPushButton(InputThresholdDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 70, 91, 34));

        retranslateUi(InputThresholdDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(InputThresholdDialog);
    } // setupUi

    void retranslateUi(QDialog *InputThresholdDialog)
    {
        InputThresholdDialog->setWindowTitle(QCoreApplication::translate("InputThresholdDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("InputThresholdDialog", "\346\216\242\347\264\242\347\257\204\345\233\262", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputThresholdDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputThresholdDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputThresholdDialog: public Ui_InputThresholdDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTTHRESHOLDDIALOG_H
