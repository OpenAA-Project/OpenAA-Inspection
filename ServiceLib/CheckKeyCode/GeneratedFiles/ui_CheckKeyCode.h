/********************************************************************************
** Form generated from reading UI file 'CheckKeyCode.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKKEYCODE_H
#define UI_CHECKKEYCODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CheckKeyCodeClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLineEdit *lineEditDec;
    QLineEdit *lineEditHex;
    QLabel *label_2;
    QLineEdit *lineEditBin;
    QLabel *label_3;

    void setupUi(QMainWindow *CheckKeyCodeClass)
    {
        if (CheckKeyCodeClass->objectName().isEmpty())
            CheckKeyCodeClass->setObjectName("CheckKeyCodeClass");
        CheckKeyCodeClass->resize(395, 140);
        centralWidget = new QWidget(CheckKeyCodeClass);
        centralWidget->setObjectName("centralWidget");
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 91, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        lineEditDec = new QLineEdit(centralWidget);
        lineEditDec->setObjectName("lineEditDec");
        lineEditDec->setGeometry(QRect(10, 30, 91, 21));
        lineEditDec->setReadOnly(true);
        lineEditHex = new QLineEdit(centralWidget);
        lineEditHex->setObjectName("lineEditHex");
        lineEditHex->setGeometry(QRect(110, 30, 91, 21));
        lineEditHex->setReadOnly(true);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 10, 91, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        lineEditBin = new QLineEdit(centralWidget);
        lineEditBin->setObjectName("lineEditBin");
        lineEditBin->setGeometry(QRect(10, 90, 371, 21));
        lineEditBin->setReadOnly(true);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 371, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        CheckKeyCodeClass->setCentralWidget(centralWidget);

        retranslateUi(CheckKeyCodeClass);

        QMetaObject::connectSlotsByName(CheckKeyCodeClass);
    } // setupUi

    void retranslateUi(QMainWindow *CheckKeyCodeClass)
    {
        CheckKeyCodeClass->setWindowTitle(QCoreApplication::translate("CheckKeyCodeClass", "CheckKeyCode", nullptr));
        label->setText(QCoreApplication::translate("CheckKeyCodeClass", "DEC", nullptr));
        label_2->setText(QCoreApplication::translate("CheckKeyCodeClass", "Hex", nullptr));
        label_3->setText(QCoreApplication::translate("CheckKeyCodeClass", "Bin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CheckKeyCodeClass: public Ui_CheckKeyCodeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKKEYCODE_H
