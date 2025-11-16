/********************************************************************************
** Form generated from reading UI file 'xmlserver.ui'
**
** Created: Mon Oct 1 16:13:18 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XMLSERVER_H
#define UI_XMLSERVER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_XmlServerClass
{
public:
    QLabel *label_3;
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *statusLabel;
    QLabel *lTime;
    QTableWidget *tableWidget;
    QTableWidget *SaveWidget;
    QPushButton *SaveB;
    QPushButton *CreateB;
    QPushButton *CutB;
    QPushButton *ENDB;

    void setupUi(QWidget *XmlServerClass)
    {
        if (XmlServerClass->objectName().isEmpty())
            XmlServerClass->setObjectName(QString::fromUtf8("XmlServerClass"));
        XmlServerClass->setWindowModality(Qt::NonModal);
        XmlServerClass->resize(467, 509);
        XmlServerClass->setAutoFillBackground(true);
        label_3 = new QLabel(XmlServerClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(270, 10, 91, 20));
        label_2 = new QLabel(XmlServerClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(340, 30, 50, 21));
        pushButton = new QPushButton(XmlServerClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(400, 10, 41, 23));
        statusLabel = new QLabel(XmlServerClass);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(20, 10, 231, 41));
        lTime = new QLabel(XmlServerClass);
        lTime->setObjectName(QString::fromUtf8("lTime"));
        lTime->setGeometry(QRect(270, 30, 50, 16));
        tableWidget = new QTableWidget(XmlServerClass);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(20, 210, 431, 261));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setColumnCount(4);
        SaveWidget = new QTableWidget(XmlServerClass);
        if (SaveWidget->columnCount() < 2)
            SaveWidget->setColumnCount(2);
        SaveWidget->setObjectName(QString::fromUtf8("SaveWidget"));
        SaveWidget->setGeometry(QRect(20, 70, 371, 111));
        SaveWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        SaveWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        SaveWidget->setColumnCount(2);
        SaveB = new QPushButton(XmlServerClass);
        SaveB->setObjectName(QString::fromUtf8("SaveB"));
        SaveB->setGeometry(QRect(400, 80, 41, 23));
        CreateB = new QPushButton(XmlServerClass);
        CreateB->setObjectName(QString::fromUtf8("CreateB"));
        CreateB->setGeometry(QRect(400, 150, 41, 23));
        CutB = new QPushButton(XmlServerClass);
        CutB->setObjectName(QString::fromUtf8("CutB"));
        CutB->setGeometry(QRect(370, 480, 75, 23));
        ENDB = new QPushButton(XmlServerClass);
        ENDB->setObjectName(QString::fromUtf8("ENDB"));
        ENDB->setGeometry(QRect(20, 480, 75, 23));

        retranslateUi(XmlServerClass);

        QMetaObject::connectSlotsByName(XmlServerClass);
    } // setupUi

    void retranslateUi(QWidget *XmlServerClass)
    {
        XmlServerClass->setWindowTitle(QApplication::translate("XmlServerClass", "XmlServer", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("XmlServerClass", "ConnectTimeOut", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("XmlServerClass", "(hour)", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("XmlServerClass", "Set", 0, QApplication::UnicodeUTF8));
        statusLabel->setText(QApplication::translate("XmlServerClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        SaveB->setText(QApplication::translate("XmlServerClass", "Save", 0, QApplication::UnicodeUTF8));
        CreateB->setText(QApplication::translate("XmlServerClass", "Create", 0, QApplication::UnicodeUTF8));
        CutB->setText(QApplication::translate("XmlServerClass", "disconnect", 0, QApplication::UnicodeUTF8));
        ENDB->setText(QApplication::translate("XmlServerClass", "END", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class XmlServerClass: public Ui_XmlServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XMLSERVER_H
