/********************************************************************************
** Form generated from reading UI file 'haspwrite_3.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HASPWRITE_3_H
#define UI_HASPWRITE_3_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HaspWrite_3Class
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLabel *tUsableyears;
    QLabel *tCpyright;
    QPushButton *pbEND;
    QLabel *lCopyright;
    QLabel *lUsableyears;
    QPushButton *pbFILEOPEN;
    QPushButton *pbDELETE;
    QPushButton *pbINSERT;
    QLabel *tCerealNo;
    QLabel *lCerealNo;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *HaspWrite_3Class)
    {
        if (HaspWrite_3Class->objectName().isEmpty())
            HaspWrite_3Class->setObjectName("HaspWrite_3Class");
        HaspWrite_3Class->resize(430, 211);
        centralWidget = new QWidget(HaspWrite_3Class);
        centralWidget->setObjectName("centralWidget");
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(440, 390, 75, 23));
        tUsableyears = new QLabel(centralWidget);
        tUsableyears->setObjectName("tUsableyears");
        tUsableyears->setGeometry(QRect(10, 40, 101, 16));
        tCpyright = new QLabel(centralWidget);
        tCpyright->setObjectName("tCpyright");
        tCpyright->setGeometry(QRect(10, 10, 101, 16));
        pbEND = new QPushButton(centralWidget);
        pbEND->setObjectName("pbEND");
        pbEND->setGeometry(QRect(320, 140, 75, 23));
        lCopyright = new QLabel(centralWidget);
        lCopyright->setObjectName("lCopyright");
        lCopyright->setGeometry(QRect(110, 10, 81, 16));
        lUsableyears = new QLabel(centralWidget);
        lUsableyears->setObjectName("lUsableyears");
        lUsableyears->setGeometry(QRect(110, 40, 81, 16));
        pbFILEOPEN = new QPushButton(centralWidget);
        pbFILEOPEN->setObjectName("pbFILEOPEN");
        pbFILEOPEN->setGeometry(QRect(20, 140, 75, 23));
        pbDELETE = new QPushButton(centralWidget);
        pbDELETE->setObjectName("pbDELETE");
        pbDELETE->setGeometry(QRect(220, 140, 75, 23));
        pbINSERT = new QPushButton(centralWidget);
        pbINSERT->setObjectName("pbINSERT");
        pbINSERT->setGeometry(QRect(120, 140, 75, 23));
        tCerealNo = new QLabel(centralWidget);
        tCerealNo->setObjectName("tCerealNo");
        tCerealNo->setGeometry(QRect(10, 70, 101, 16));
        lCerealNo = new QLabel(centralWidget);
        lCerealNo->setObjectName("lCerealNo");
        lCerealNo->setGeometry(QRect(110, 70, 81, 20));
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(200, 10, 221, 101));
        tableWidget->setFrameShape(QFrame::StyledPanel);
        tableWidget->setFrameShadow(QFrame::Sunken);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        HaspWrite_3Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(HaspWrite_3Class);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 430, 20));
        HaspWrite_3Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(HaspWrite_3Class);
        mainToolBar->setObjectName("mainToolBar");
        mainToolBar->setOrientation(Qt::Horizontal);
        HaspWrite_3Class->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(HaspWrite_3Class);
        statusBar->setObjectName("statusBar");
        statusBar->setGeometry(QRect(0, 193, 430, 18));
        HaspWrite_3Class->setStatusBar(statusBar);

        retranslateUi(HaspWrite_3Class);

        QMetaObject::connectSlotsByName(HaspWrite_3Class);
    } // setupUi

    void retranslateUi(QMainWindow *HaspWrite_3Class)
    {
        HaspWrite_3Class->setWindowTitle(QCoreApplication::translate("HaspWrite_3Class", "HaspWrite_3", nullptr));
        pushButton->setText(QCoreApplication::translate("HaspWrite_3Class", "1:FileOut", nullptr));
        tUsableyears->setText(QCoreApplication::translate("HaspWrite_3Class", "\344\275\277\347\224\250\346\234\237\351\226\223", nullptr));
        tCpyright->setText(QCoreApplication::translate("HaspWrite_3Class", "\350\221\227\344\275\234\346\250\251\350\252\215\350\250\274\347\225\252\345\217\267", nullptr));
        pbEND->setText(QCoreApplication::translate("HaspWrite_3Class", "END", nullptr));
        pbFILEOPEN->setText(QCoreApplication::translate("HaspWrite_3Class", "FILE OPEN", nullptr));
        pbDELETE->setText(QCoreApplication::translate("HaspWrite_3Class", "DELETE", nullptr));
        pbINSERT->setText(QCoreApplication::translate("HaspWrite_3Class", "INSERT", nullptr));
        tCerealNo->setText(QCoreApplication::translate("HaspWrite_3Class", "\343\202\267\343\203\252\343\202\242\343\203\253No", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HaspWrite_3Class: public Ui_HaspWrite_3Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HASPWRITE_3_H
