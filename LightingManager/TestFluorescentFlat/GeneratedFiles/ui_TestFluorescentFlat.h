/********************************************************************************
** Form generated from reading UI file 'TestFluorescentFlat.ui'
**
** Created: Sun Jan 6 11:57:20 2013
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTFLUORESCENTFLAT_H
#define UI_TESTFLUORESCENTFLAT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>
#include <QtGui/QToolButton>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestFluorescentFlatClass
{
public:
    QWidget *centralWidget;
    QTableWidget *tableWidget;
    QPushButton *pushButtonOK;
    QSpinBox *spinBoxSetAll;
    QPushButton *pushButtonSetAll;
    QToolButton *toolButtonOnOff;

    void setupUi(QMainWindow *TestFluorescentFlatClass)
    {
        if (TestFluorescentFlatClass->objectName().isEmpty())
            TestFluorescentFlatClass->setObjectName(QString::fromUtf8("TestFluorescentFlatClass"));
        TestFluorescentFlatClass->resize(1173, 321);
        centralWidget = new QWidget(TestFluorescentFlatClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 30)
            tableWidget->setColumnCount(30);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(12, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(13, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(14, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(15, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(16, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(17, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(18, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(19, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(20, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(21, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(22, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(23, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(24, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(25, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(26, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(27, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(28, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(29, __qtablewidgetitem29);
        if (tableWidget->rowCount() < 7)
            tableWidget->setRowCount(7);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem36);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 1161, 261));
        pushButtonOK = new QPushButton(centralWidget);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(810, 270, 141, 41));
        spinBoxSetAll = new QSpinBox(centralWidget);
        spinBoxSetAll->setObjectName(QString::fromUtf8("spinBoxSetAll"));
        spinBoxSetAll->setGeometry(QRect(10, 270, 81, 22));
        spinBoxSetAll->setMaximum(2047);
        pushButtonSetAll = new QPushButton(centralWidget);
        pushButtonSetAll->setObjectName(QString::fromUtf8("pushButtonSetAll"));
        pushButtonSetAll->setGeometry(QRect(100, 270, 75, 23));
        toolButtonOnOff = new QToolButton(centralWidget);
        toolButtonOnOff->setObjectName(QString::fromUtf8("toolButtonOnOff"));
        toolButtonOnOff->setGeometry(QRect(250, 270, 121, 31));
        toolButtonOnOff->setCheckable(true);
        toolButtonOnOff->setChecked(false);
        TestFluorescentFlatClass->setCentralWidget(centralWidget);

        retranslateUi(TestFluorescentFlatClass);

        QMetaObject::connectSlotsByName(TestFluorescentFlatClass);
    } // setupUi

    void retranslateUi(QMainWindow *TestFluorescentFlatClass)
    {
        TestFluorescentFlatClass->setWindowTitle(QApplication::translate("TestFluorescentFlatClass", "TestFluorescentFlat", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\220", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\221", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\222", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\223", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\224", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\225", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\226", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\230", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\231", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\221\357\274\220", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\221\357\274\221", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->horizontalHeaderItem(12);
        ___qtablewidgetitem12->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\221\357\274\222", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->horizontalHeaderItem(13);
        ___qtablewidgetitem13->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\221\357\274\223", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->horizontalHeaderItem(14);
        ___qtablewidgetitem14->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\221\357\274\224", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->horizontalHeaderItem(15);
        ___qtablewidgetitem15->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\221\357\274\225", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->horizontalHeaderItem(16);
        ___qtablewidgetitem16->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\221\357\274\226", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->horizontalHeaderItem(17);
        ___qtablewidgetitem17->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\221\357\274\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->horizontalHeaderItem(18);
        ___qtablewidgetitem18->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\221\357\274\230", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->horizontalHeaderItem(19);
        ___qtablewidgetitem19->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\221\357\274\231", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->horizontalHeaderItem(20);
        ___qtablewidgetitem20->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\222\357\274\220", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->horizontalHeaderItem(21);
        ___qtablewidgetitem21->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\222\357\274\221", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->horizontalHeaderItem(22);
        ___qtablewidgetitem22->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\222\357\274\222", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->horizontalHeaderItem(23);
        ___qtablewidgetitem23->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\222\357\274\223", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->horizontalHeaderItem(24);
        ___qtablewidgetitem24->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\222\357\274\224", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->horizontalHeaderItem(25);
        ___qtablewidgetitem25->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\222\357\274\225", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->horizontalHeaderItem(26);
        ___qtablewidgetitem26->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\222\357\274\226", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget->horizontalHeaderItem(27);
        ___qtablewidgetitem27->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\222\357\274\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget->horizontalHeaderItem(28);
        ___qtablewidgetitem28->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\222\357\274\230", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget->horizontalHeaderItem(29);
        ___qtablewidgetitem29->setText(QApplication::translate("TestFluorescentFlatClass", "\357\274\222\357\274\231", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem30->setText(QApplication::translate("TestFluorescentFlatClass", "0", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem31->setText(QApplication::translate("TestFluorescentFlatClass", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem32->setText(QApplication::translate("TestFluorescentFlatClass", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem33->setText(QApplication::translate("TestFluorescentFlatClass", "3", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem34->setText(QApplication::translate("TestFluorescentFlatClass", "4", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem35->setText(QApplication::translate("TestFluorescentFlatClass", "5", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem36->setText(QApplication::translate("TestFluorescentFlatClass", "6", 0, QApplication::UnicodeUTF8));
        pushButtonOK->setText(QApplication::translate("TestFluorescentFlatClass", "Transfer", 0, QApplication::UnicodeUTF8));
        pushButtonSetAll->setText(QApplication::translate("TestFluorescentFlatClass", "Set All", 0, QApplication::UnicodeUTF8));
        toolButtonOnOff->setText(QApplication::translate("TestFluorescentFlatClass", "ON/OFF", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TestFluorescentFlatClass: public Ui_TestFluorescentFlatClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTFLUORESCENTFLAT_H
