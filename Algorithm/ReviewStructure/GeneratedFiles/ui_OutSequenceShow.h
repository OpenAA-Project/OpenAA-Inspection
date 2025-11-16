/********************************************************************************
** Form generated from reading UI file 'OutSequenceShow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTSEQUENCESHOW_H
#define UI_OUTSEQUENCESHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OutSequenceShow
{
public:
    QLabel *MessageLabel;

    void setupUi(QWidget *OutSequenceShow)
    {
        if (OutSequenceShow->objectName().isEmpty())
            OutSequenceShow->setObjectName("OutSequenceShow");
        OutSequenceShow->resize(542, 106);
        MessageLabel = new QLabel(OutSequenceShow);
        MessageLabel->setObjectName("MessageLabel");
        MessageLabel->setGeometry(QRect(30, 20, 471, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        MessageLabel->setFont(font);

        retranslateUi(OutSequenceShow);

        QMetaObject::connectSlotsByName(OutSequenceShow);
    } // setupUi

    void retranslateUi(QWidget *OutSequenceShow)
    {
        OutSequenceShow->setWindowTitle(QCoreApplication::translate("OutSequenceShow", "Form", nullptr));
        MessageLabel->setText(QCoreApplication::translate("OutSequenceShow", "MessageLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OutSequenceShow: public Ui_OutSequenceShow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTSEQUENCESHOW_H
