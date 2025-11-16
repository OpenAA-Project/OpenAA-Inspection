/********************************************************************************
** Form generated from reading UI file 'StartCloseOnce.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTCLOSEONCE_H
#define UI_STARTCLOSEONCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartCloseOnceClass
{
public:
    QWidget *centralWidget;
    QLabel *label;

    void setupUi(QMainWindow *StartCloseOnceClass)
    {
        if (StartCloseOnceClass->objectName().isEmpty())
            StartCloseOnceClass->setObjectName("StartCloseOnceClass");
        StartCloseOnceClass->resize(445, 73);
        centralWidget = new QWidget(StartCloseOnceClass);
        centralWidget->setObjectName("centralWidget");
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 20, 281, 31));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        StartCloseOnceClass->setCentralWidget(centralWidget);

        retranslateUi(StartCloseOnceClass);

        QMetaObject::connectSlotsByName(StartCloseOnceClass);
    } // setupUi

    void retranslateUi(QMainWindow *StartCloseOnceClass)
    {
        StartCloseOnceClass->setWindowTitle(QCoreApplication::translate("StartCloseOnceClass", "\343\203\241\343\203\203\343\202\273\343\203\274\343\202\270", nullptr));
        label->setText(QCoreApplication::translate("StartCloseOnceClass", "\343\201\227\343\201\260\343\202\211\343\201\217\343\201\212\345\276\205\343\201\241\343\201\217\343\201\240\343\201\225\343\201\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartCloseOnceClass: public Ui_StartCloseOnceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTCLOSEONCE_H
