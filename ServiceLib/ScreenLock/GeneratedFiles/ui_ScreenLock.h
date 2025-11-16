/********************************************************************************
** Form generated from reading UI file 'ScreenLock.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENLOCK_H
#define UI_SCREENLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScreenLockClass
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QLineEdit *lineEditPassword;
    QLabel *label;
    QPushButton *pushButtonOK;
    QLabel *LabelTitle;

    void setupUi(QMainWindow *ScreenLockClass)
    {
        if (ScreenLockClass->objectName().isEmpty())
            ScreenLockClass->setObjectName("ScreenLockClass");
        ScreenLockClass->resize(745, 659);
        centralWidget = new QWidget(ScreenLockClass);
        centralWidget->setObjectName("centralWidget");
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(220, 310, 281, 161));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        lineEditPassword = new QLineEdit(frame);
        lineEditPassword->setObjectName("lineEditPassword");
        lineEditPassword->setGeometry(QRect(50, 80, 191, 31));
        QFont font;
        font.setPointSize(12);
        lineEditPassword->setFont(font);
        lineEditPassword->setEchoMode(QLineEdit::Password);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 30, 211, 31));
        QFont font1;
        font1.setPointSize(14);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(frame);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(100, 120, 75, 31));
        pushButtonOK->setAutoDefault(true);
        LabelTitle = new QLabel(centralWidget);
        LabelTitle->setObjectName("LabelTitle");
        LabelTitle->setGeometry(QRect(240, 20, 381, 41));
        LabelTitle->setFont(font1);
        LabelTitle->setAlignment(Qt::AlignCenter);
        ScreenLockClass->setCentralWidget(centralWidget);

        retranslateUi(ScreenLockClass);

        QMetaObject::connectSlotsByName(ScreenLockClass);
    } // setupUi

    void retranslateUi(QMainWindow *ScreenLockClass)
    {
        ScreenLockClass->setWindowTitle(QCoreApplication::translate("ScreenLockClass", "ScreenLock", nullptr));
        label->setText(QCoreApplication::translate("ScreenLockClass", "Password", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("ScreenLockClass", "OK", nullptr));
        LabelTitle->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ScreenLockClass: public Ui_ScreenLockClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENLOCK_H
