/********************************************************************************
** Form generated from reading UI file 'InputStringList.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTSTRINGLIST_H
#define UI_INPUTSTRINGLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputStringListClass
{
public:
    QFrame *frame;
    QPushButton *pushButtonDeleteCurrentLine;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonAddLine;

    void setupUi(QDialog *InputStringListClass)
    {
        if (InputStringListClass->objectName().isEmpty())
            InputStringListClass->setObjectName("InputStringListClass");
        InputStringListClass->resize(391, 371);
        frame = new QFrame(InputStringListClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 320, 391, 51));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonDeleteCurrentLine = new QPushButton(frame);
        pushButtonDeleteCurrentLine->setObjectName("pushButtonDeleteCurrentLine");
        pushButtonDeleteCurrentLine->setGeometry(QRect(20, 10, 131, 31));
        pushButtonOK = new QPushButton(frame);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(280, 10, 101, 31));
        pushButtonAddLine = new QPushButton(frame);
        pushButtonAddLine->setObjectName("pushButtonAddLine");
        pushButtonAddLine->setGeometry(QRect(160, 10, 91, 31));

        retranslateUi(InputStringListClass);

        QMetaObject::connectSlotsByName(InputStringListClass);
    } // setupUi

    void retranslateUi(QDialog *InputStringListClass)
    {
        InputStringListClass->setWindowTitle(QCoreApplication::translate("InputStringListClass", "InputStringList", nullptr));
        pushButtonDeleteCurrentLine->setText(QCoreApplication::translate("InputStringListClass", "Delete current line", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputStringListClass", "OK", nullptr));
        pushButtonAddLine->setText(QCoreApplication::translate("InputStringListClass", "+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputStringListClass: public Ui_InputStringListClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTSTRINGLIST_H
