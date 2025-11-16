/********************************************************************************
** Form generated from reading UI file 'haspchosaku_2.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HASPCHOSAKU_2_H
#define UI_HASPCHOSAKU_2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HaspChosaku_2Class
{
public:
    QWidget *centralWidget;
    QDateEdit *dateEdit;
    QLineEdit *lineEdit;
    QPushButton *pbEND;
    QPushButton *pbOK;
    QLabel *lCopyright;
    QLabel *lUsable;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *HaspChosaku_2Class)
    {
        if (HaspChosaku_2Class->objectName().isEmpty())
            HaspChosaku_2Class->setObjectName("HaspChosaku_2Class");
        HaspChosaku_2Class->resize(212, 189);
        centralWidget = new QWidget(HaspChosaku_2Class);
        centralWidget->setObjectName("centralWidget");
        dateEdit = new QDateEdit(centralWidget);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(60, 80, 110, 22));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(60, 30, 113, 20));
        lineEdit->setMaxLength(8);
        pbEND = new QPushButton(centralWidget);
        pbEND->setObjectName("pbEND");
        pbEND->setGeometry(QRect(120, 120, 75, 23));
        pbOK = new QPushButton(centralWidget);
        pbOK->setObjectName("pbOK");
        pbOK->setGeometry(QRect(20, 120, 75, 23));
        lCopyright = new QLabel(centralWidget);
        lCopyright->setObjectName("lCopyright");
        lCopyright->setGeometry(QRect(10, 10, 191, 16));
        lUsable = new QLabel(centralWidget);
        lUsable->setObjectName("lUsable");
        lUsable->setGeometry(QRect(10, 60, 181, 16));
        HaspChosaku_2Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(HaspChosaku_2Class);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 212, 20));
        HaspChosaku_2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(HaspChosaku_2Class);
        mainToolBar->setObjectName("mainToolBar");
        mainToolBar->setOrientation(Qt::Horizontal);
        HaspChosaku_2Class->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(HaspChosaku_2Class);
        statusBar->setObjectName("statusBar");
        statusBar->setGeometry(QRect(0, 171, 212, 18));
        HaspChosaku_2Class->setStatusBar(statusBar);

        retranslateUi(HaspChosaku_2Class);

        QMetaObject::connectSlotsByName(HaspChosaku_2Class);
    } // setupUi

    void retranslateUi(QMainWindow *HaspChosaku_2Class)
    {
        HaspChosaku_2Class->setWindowTitle(QCoreApplication::translate("HaspChosaku_2Class", "HaspChosaku_2", nullptr));
        pbEND->setText(QCoreApplication::translate("HaspChosaku_2Class", "END", nullptr));
        pbOK->setText(QCoreApplication::translate("HaspChosaku_2Class", "OK", nullptr));
        lCopyright->setText(QCoreApplication::translate("HaspChosaku_2Class", "\350\221\227\344\275\234\346\250\251\350\252\215\350\250\274\347\225\252\345\217\267(8\346\241\201)", nullptr));
        lUsable->setText(QCoreApplication::translate("HaspChosaku_2Class", "\344\275\277\347\224\250\346\234\237\351\231\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HaspChosaku_2Class: public Ui_HaspChosaku_2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HASPCHOSAKU_2_H
