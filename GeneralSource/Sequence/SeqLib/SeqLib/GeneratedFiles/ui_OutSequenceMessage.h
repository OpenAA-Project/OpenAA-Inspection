/********************************************************************************
** Form generated from reading UI file 'OutSequenceMessage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTSEQUENCEMESSAGE_H
#define UI_OUTSEQUENCEMESSAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OutSequenceMessage
{
public:
    QPushButton *TestButton;
    QPushButton *SeqButton;
    QLabel *MessageLabel;
    QPushButton *OKButton;

    void setupUi(QWidget *OutSequenceMessage)
    {
        if (OutSequenceMessage->objectName().isEmpty())
            OutSequenceMessage->setObjectName("OutSequenceMessage");
        OutSequenceMessage->resize(489, 134);
        TestButton = new QPushButton(OutSequenceMessage);
        TestButton->setObjectName("TestButton");
        TestButton->setGeometry(QRect(460, 2, 31, 21));
        SeqButton = new QPushButton(OutSequenceMessage);
        SeqButton->setObjectName("SeqButton");
        SeqButton->setGeometry(QRect(460, 22, 31, 21));
        MessageLabel = new QLabel(OutSequenceMessage);
        MessageLabel->setObjectName("MessageLabel");
        MessageLabel->setGeometry(QRect(10, 22, 441, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        MessageLabel->setFont(font);
        OKButton = new QPushButton(OutSequenceMessage);
        OKButton->setObjectName("OKButton");
        OKButton->setGeometry(QRect(200, 90, 89, 33));

        retranslateUi(OutSequenceMessage);

        OKButton->setDefault(true);


        QMetaObject::connectSlotsByName(OutSequenceMessage);
    } // setupUi

    void retranslateUi(QWidget *OutSequenceMessage)
    {
        OutSequenceMessage->setWindowTitle(QCoreApplication::translate("OutSequenceMessage", "Form", nullptr));
        TestButton->setText(QCoreApplication::translate("OutSequenceMessage", "Test", nullptr));
        SeqButton->setText(QCoreApplication::translate("OutSequenceMessage", "Seq", nullptr));
        MessageLabel->setText(QCoreApplication::translate("OutSequenceMessage", "MessageLabel", nullptr));
        OKButton->setText(QCoreApplication::translate("OutSequenceMessage", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OutSequenceMessage: public Ui_OutSequenceMessage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTSEQUENCEMESSAGE_H
