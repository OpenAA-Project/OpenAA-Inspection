/********************************************************************************
** Form generated from reading UI file 'InputMirror.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTMIRROR_H
#define UI_INPUTMIRROR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputMirror
{
public:
    QPushButton *pushButtonYMirror;
    QPushButton *pushButtonXMirror;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *InputMirror)
    {
        if (InputMirror->objectName().isEmpty())
            InputMirror->setObjectName("InputMirror");
        InputMirror->resize(154, 103);
        pushButtonYMirror = new QPushButton(InputMirror);
        pushButtonYMirror->setObjectName("pushButtonYMirror");
        pushButtonYMirror->setGeometry(QRect(10, 40, 131, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Mirror.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonYMirror->setIcon(icon);
        pushButtonXMirror = new QPushButton(InputMirror);
        pushButtonXMirror->setObjectName("pushButtonXMirror");
        pushButtonXMirror->setGeometry(QRect(10, 10, 131, 23));
        pushButtonXMirror->setIcon(icon);
        pushButtonCancel = new QPushButton(InputMirror);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(10, 70, 131, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(InputMirror);

        QMetaObject::connectSlotsByName(InputMirror);
    } // setupUi

    void retranslateUi(QDialog *InputMirror)
    {
        InputMirror->setWindowTitle(QCoreApplication::translate("InputMirror", "Dialog", nullptr));
        pushButtonYMirror->setText(QCoreApplication::translate("InputMirror", "Y axis mirror", nullptr));
        pushButtonXMirror->setText(QCoreApplication::translate("InputMirror", "X axis mirror", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputMirror", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputMirror: public Ui_InputMirror {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTMIRROR_H
