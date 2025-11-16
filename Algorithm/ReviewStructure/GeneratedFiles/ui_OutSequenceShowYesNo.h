/********************************************************************************
** Form generated from reading UI file 'OutSequenceShowYesNo.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTSEQUENCESHOWYESNO_H
#define UI_OUTSEQUENCESHOWYESNO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OutSequenceShowYesNo
{
public:
    QLabel *MessageLabel;
    QPushButton *NoButton;
    QPushButton *YesButton;

    void setupUi(QWidget *OutSequenceShowYesNo)
    {
        if (OutSequenceShowYesNo->objectName().isEmpty())
            OutSequenceShowYesNo->setObjectName("OutSequenceShowYesNo");
        OutSequenceShowYesNo->resize(490, 129);
        MessageLabel = new QLabel(OutSequenceShowYesNo);
        MessageLabel->setObjectName("MessageLabel");
        MessageLabel->setGeometry(QRect(12, 12, 471, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        MessageLabel->setFont(font);
        NoButton = new QPushButton(OutSequenceShowYesNo);
        NoButton->setObjectName("NoButton");
        NoButton->setGeometry(QRect(290, 80, 89, 33));
        YesButton = new QPushButton(OutSequenceShowYesNo);
        YesButton->setObjectName("YesButton");
        YesButton->setGeometry(QRect(98, 80, 89, 33));

        retranslateUi(OutSequenceShowYesNo);

        YesButton->setDefault(true);


        QMetaObject::connectSlotsByName(OutSequenceShowYesNo);
    } // setupUi

    void retranslateUi(QWidget *OutSequenceShowYesNo)
    {
        OutSequenceShowYesNo->setWindowTitle(QCoreApplication::translate("OutSequenceShowYesNo", "Form", nullptr));
        MessageLabel->setText(QCoreApplication::translate("OutSequenceShowYesNo", "MessageLabel", nullptr));
        NoButton->setText(QCoreApplication::translate("OutSequenceShowYesNo", "NO", nullptr));
        YesButton->setText(QCoreApplication::translate("OutSequenceShowYesNo", "YES", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OutSequenceShowYesNo: public Ui_OutSequenceShowYesNo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTSEQUENCESHOWYESNO_H
