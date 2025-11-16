/********************************************************************************
** Form generated from reading UI file 'OutSequenceYesNo.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTSEQUENCEYESNO_H
#define UI_OUTSEQUENCEYESNO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OutSequenceYesNo
{
public:
    QPushButton *NoButton;
    QPushButton *YesButton;
    QPushButton *TestButton;
    QPushButton *SeqButton;
    QLabel *MessageLabel;

    void setupUi(QWidget *OutSequenceYesNo)
    {
        if (OutSequenceYesNo->objectName().isEmpty())
            OutSequenceYesNo->setObjectName("OutSequenceYesNo");
        OutSequenceYesNo->resize(494, 138);
        NoButton = new QPushButton(OutSequenceYesNo);
        NoButton->setObjectName("NoButton");
        NoButton->setGeometry(QRect(290, 90, 89, 33));
        YesButton = new QPushButton(OutSequenceYesNo);
        YesButton->setObjectName("YesButton");
        YesButton->setGeometry(QRect(98, 90, 89, 33));
        TestButton = new QPushButton(OutSequenceYesNo);
        TestButton->setObjectName("TestButton");
        TestButton->setGeometry(QRect(462, 2, 31, 21));
        SeqButton = new QPushButton(OutSequenceYesNo);
        SeqButton->setObjectName("SeqButton");
        SeqButton->setGeometry(QRect(462, 22, 31, 21));
        MessageLabel = new QLabel(OutSequenceYesNo);
        MessageLabel->setObjectName("MessageLabel");
        MessageLabel->setGeometry(QRect(12, 22, 441, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        MessageLabel->setFont(font);
        MessageLabel->setTextFormat(Qt::RichText);

        retranslateUi(OutSequenceYesNo);

        YesButton->setDefault(true);


        QMetaObject::connectSlotsByName(OutSequenceYesNo);
    } // setupUi

    void retranslateUi(QWidget *OutSequenceYesNo)
    {
        OutSequenceYesNo->setWindowTitle(QCoreApplication::translate("OutSequenceYesNo", "Form", nullptr));
        NoButton->setText(QCoreApplication::translate("OutSequenceYesNo", "NO", nullptr));
        YesButton->setText(QCoreApplication::translate("OutSequenceYesNo", "YES", nullptr));
        TestButton->setText(QCoreApplication::translate("OutSequenceYesNo", "Test", nullptr));
        SeqButton->setText(QCoreApplication::translate("OutSequenceYesNo", "Seq", nullptr));
        MessageLabel->setText(QCoreApplication::translate("OutSequenceYesNo", "MessageLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OutSequenceYesNo: public Ui_OutSequenceYesNo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTSEQUENCEYESNO_H
