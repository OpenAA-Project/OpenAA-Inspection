/********************************************************************************
** Form generated from reading UI file 'OutSequenceInput.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTSEQUENCEINPUT_H
#define UI_OUTSEQUENCEINPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OutSequenceInput
{
public:
    QPushButton *TestButton;
    QPushButton *SeqButton;
    QLineEdit *EditInput;
    QLabel *MessageLabel;
    QPushButton *YesButton;
    QPushButton *NoButton;

    void setupUi(QWidget *OutSequenceInput)
    {
        if (OutSequenceInput->objectName().isEmpty())
            OutSequenceInput->setObjectName("OutSequenceInput");
        OutSequenceInput->resize(461, 182);
        TestButton = new QPushButton(OutSequenceInput);
        TestButton->setObjectName("TestButton");
        TestButton->setGeometry(QRect(430, 0, 31, 21));
        SeqButton = new QPushButton(OutSequenceInput);
        SeqButton->setObjectName("SeqButton");
        SeqButton->setGeometry(QRect(430, 20, 31, 21));
        EditInput = new QLineEdit(OutSequenceInput);
        EditInput->setObjectName("EditInput");
        EditInput->setGeometry(QRect(160, 100, 121, 20));
        MessageLabel = new QLabel(OutSequenceInput);
        MessageLabel->setObjectName("MessageLabel");
        MessageLabel->setGeometry(QRect(0, 20, 421, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        MessageLabel->setFont(font);
        YesButton = new QPushButton(OutSequenceInput);
        YesButton->setObjectName("YesButton");
        YesButton->setGeometry(QRect(80, 140, 89, 33));
        NoButton = new QPushButton(OutSequenceInput);
        NoButton->setObjectName("NoButton");
        NoButton->setGeometry(QRect(270, 140, 89, 33));

        retranslateUi(OutSequenceInput);

        QMetaObject::connectSlotsByName(OutSequenceInput);
    } // setupUi

    void retranslateUi(QWidget *OutSequenceInput)
    {
        OutSequenceInput->setWindowTitle(QCoreApplication::translate("OutSequenceInput", "Form", nullptr));
        TestButton->setText(QCoreApplication::translate("OutSequenceInput", "Test", nullptr));
        SeqButton->setText(QCoreApplication::translate("OutSequenceInput", "Seq", nullptr));
        MessageLabel->setText(QCoreApplication::translate("OutSequenceInput", "MessageLabel", nullptr));
        YesButton->setText(QCoreApplication::translate("OutSequenceInput", "YES", nullptr));
        NoButton->setText(QCoreApplication::translate("OutSequenceInput", "NO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OutSequenceInput: public Ui_OutSequenceInput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTSEQUENCEINPUT_H
