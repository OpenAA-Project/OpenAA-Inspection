/********************************************************************************
** Form generated from reading UI file 'haspcereal_1.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HASPCEREAL_1_H
#define UI_HASPCEREAL_1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HaspCereal_1Class
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pbYES;
    QPushButton *pbNO;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *HaspCereal_1Class)
    {
        if (HaspCereal_1Class->objectName().isEmpty())
            HaspCereal_1Class->setObjectName("HaspCereal_1Class");
        HaspCereal_1Class->resize(198, 130);
        centralWidget = new QWidget(HaspCereal_1Class);
        centralWidget->setObjectName("centralWidget");
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 181, 41));
        pbYES = new QPushButton(centralWidget);
        pbYES->setObjectName("pbYES");
        pbYES->setGeometry(QRect(10, 60, 71, 21));
        pbNO = new QPushButton(centralWidget);
        pbNO->setObjectName("pbNO");
        pbNO->setGeometry(QRect(110, 60, 71, 21));
        HaspCereal_1Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(HaspCereal_1Class);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 198, 20));
        HaspCereal_1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(HaspCereal_1Class);
        mainToolBar->setObjectName("mainToolBar");
        mainToolBar->setOrientation(Qt::Horizontal);
        HaspCereal_1Class->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(HaspCereal_1Class);
        statusBar->setObjectName("statusBar");
        statusBar->setGeometry(QRect(0, 112, 198, 18));
        HaspCereal_1Class->setStatusBar(statusBar);

        retranslateUi(HaspCereal_1Class);

        QMetaObject::connectSlotsByName(HaspCereal_1Class);
    } // setupUi

    void retranslateUi(QMainWindow *HaspCereal_1Class)
    {
        HaspCereal_1Class->setWindowTitle(QCoreApplication::translate("HaspCereal_1Class", "HaspCereal_1", nullptr));
        label->setText(QCoreApplication::translate("HaspCereal_1Class", "Is the preparation for HASP good?", nullptr));
        pbYES->setText(QCoreApplication::translate("HaspCereal_1Class", "YES", nullptr));
        pbNO->setText(QCoreApplication::translate("HaspCereal_1Class", "NO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HaspCereal_1Class: public Ui_HaspCereal_1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HASPCEREAL_1_H
