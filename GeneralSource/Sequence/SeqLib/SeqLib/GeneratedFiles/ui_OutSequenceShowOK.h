/********************************************************************************
** Form generated from reading UI file 'OutSequenceShowOK.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTSEQUENCESHOWOK_H
#define UI_OUTSEQUENCESHOWOK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OutSequenceShowOK
{
public:
    QPushButton *OKButton;
    QLabel *MessageLabel;

    void setupUi(QWidget *OutSequenceShowOK)
    {
        if (OutSequenceShowOK->objectName().isEmpty())
            OutSequenceShowOK->setObjectName("OutSequenceShowOK");
        OutSequenceShowOK->resize(489, 123);
        OKButton = new QPushButton(OutSequenceShowOK);
        OKButton->setObjectName("OKButton");
        OKButton->setGeometry(QRect(200, 80, 89, 33));
        MessageLabel = new QLabel(OutSequenceShowOK);
        MessageLabel->setObjectName("MessageLabel");
        MessageLabel->setGeometry(QRect(10, 12, 471, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        MessageLabel->setFont(font);

        retranslateUi(OutSequenceShowOK);

        OKButton->setDefault(true);


        QMetaObject::connectSlotsByName(OutSequenceShowOK);
    } // setupUi

    void retranslateUi(QWidget *OutSequenceShowOK)
    {
        OutSequenceShowOK->setWindowTitle(QCoreApplication::translate("OutSequenceShowOK", "Form", nullptr));
        OKButton->setText(QCoreApplication::translate("OutSequenceShowOK", "OK", nullptr));
        MessageLabel->setText(QCoreApplication::translate("OutSequenceShowOK", "MessageLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OutSequenceShowOK: public Ui_OutSequenceShowOK {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTSEQUENCESHOWOK_H
