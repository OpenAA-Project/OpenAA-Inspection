/********************************************************************************
** Form generated from reading UI file 'InputCodeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTCODEDIALOG_H
#define UI_INPUTCODEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputCodeDialog
{
public:
    QLineEdit *lineEditBarcode;
    QLabel *label;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *InputCodeDialog)
    {
        if (InputCodeDialog->objectName().isEmpty())
            InputCodeDialog->setObjectName("InputCodeDialog");
        InputCodeDialog->resize(260, 99);
        lineEditBarcode = new QLineEdit(InputCodeDialog);
        lineEditBarcode->setObjectName("lineEditBarcode");
        lineEditBarcode->setGeometry(QRect(10, 30, 241, 20));
        label = new QLabel(InputCodeDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 241, 16));
        pushButtonOK = new QPushButton(InputCodeDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 60, 81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(InputCodeDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(160, 60, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(InputCodeDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(InputCodeDialog);
    } // setupUi

    void retranslateUi(QDialog *InputCodeDialog)
    {
        InputCodeDialog->setWindowTitle(QCoreApplication::translate("InputCodeDialog", "Input code", nullptr));
        label->setText(QCoreApplication::translate("InputCodeDialog", "\343\203\220\343\203\274\343\202\263\343\203\274\343\203\211\343\201\256\345\200\244\343\202\222\346\211\213\345\205\245\345\212\233\343\201\227\343\201\246\343\201\217\343\201\240\343\201\225\343\201\204", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputCodeDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputCodeDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputCodeDialog: public Ui_InputCodeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTCODEDIALOG_H
