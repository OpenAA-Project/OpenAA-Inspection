/********************************************************************************
** Form generated from reading UI file 'MakeLockStarKey.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAKELOCKSTARKEY_H
#define UI_MAKELOCKSTARKEY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MakeLockStarKeyClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;

    void setupUi(QMainWindow *MakeLockStarKeyClass)
    {
        if (MakeLockStarKeyClass->objectName().isEmpty())
            MakeLockStarKeyClass->setObjectName("MakeLockStarKeyClass");
        MakeLockStarKeyClass->resize(305, 121);
        centralWidget = new QWidget(MakeLockStarKeyClass);
        centralWidget->setObjectName("centralWidget");
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 10, 191, 34));
        MakeLockStarKeyClass->setCentralWidget(centralWidget);

        retranslateUi(MakeLockStarKeyClass);

        QMetaObject::connectSlotsByName(MakeLockStarKeyClass);
    } // setupUi

    void retranslateUi(QMainWindow *MakeLockStarKeyClass)
    {
        MakeLockStarKeyClass->setWindowTitle(QCoreApplication::translate("MakeLockStarKeyClass", "MakeLockStarKey", nullptr));
        pushButton->setText(QCoreApplication::translate("MakeLockStarKeyClass", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MakeLockStarKeyClass: public Ui_MakeLockStarKeyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAKELOCKSTARKEY_H
