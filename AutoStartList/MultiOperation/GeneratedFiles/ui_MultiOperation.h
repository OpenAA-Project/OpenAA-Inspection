/********************************************************************************
** Form generated from reading UI file 'MultiOperation.ui'
**
** Created: Sat Jan 14 22:29:43 2017
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTIOPERATION_H
#define UI_MULTIOPERATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_MultiOperationClass
{
public:
    QWidget *centralWidget;
    QTableWidget *tableWidget;
    QPushButton *pushButtonCreateNewConnect;
    QPushButton *pushButtonUpdateConnect;
    QPushButton *pushButtonDeleteConnect;
    QLabel *label_3;

    void setupUi(QMainWindow *MultiOperationClass)
    {
        if (MultiOperationClass->objectName().isEmpty())
            MultiOperationClass->setObjectName(QString::fromUtf8("MultiOperationClass"));
        MultiOperationClass->resize(563, 488);
        centralWidget = new QWidget(MultiOperationClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 30, 551, 411));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonCreateNewConnect = new QPushButton(centralWidget);
        pushButtonCreateNewConnect->setObjectName(QString::fromUtf8("pushButtonCreateNewConnect"));
        pushButtonCreateNewConnect->setGeometry(QRect(30, 450, 91, 23));
        pushButtonUpdateConnect = new QPushButton(centralWidget);
        pushButtonUpdateConnect->setObjectName(QString::fromUtf8("pushButtonUpdateConnect"));
        pushButtonUpdateConnect->setGeometry(QRect(130, 450, 91, 23));
        pushButtonDeleteConnect = new QPushButton(centralWidget);
        pushButtonDeleteConnect->setObjectName(QString::fromUtf8("pushButtonDeleteConnect"));
        pushButtonDeleteConnect->setGeometry(QRect(480, 450, 75, 23));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 10, 551, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        MultiOperationClass->setCentralWidget(centralWidget);

        retranslateUi(MultiOperationClass);

        QMetaObject::connectSlotsByName(MultiOperationClass);
    } // setupUi

    void retranslateUi(QMainWindow *MultiOperationClass)
    {
        MultiOperationClass->setWindowTitle(QApplication::translate("MultiOperationClass", "MultiOperation", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MultiOperationClass", "Name", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MultiOperationClass", "IPAddress", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MultiOperationClass", "LocalPath", 0, QApplication::UnicodeUTF8));
        pushButtonCreateNewConnect->setText(QApplication::translate("MultiOperationClass", "Create new", 0, QApplication::UnicodeUTF8));
        pushButtonUpdateConnect->setText(QApplication::translate("MultiOperationClass", "Update", 0, QApplication::UnicodeUTF8));
        pushButtonDeleteConnect->setText(QApplication::translate("MultiOperationClass", "Delete", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MultiOperationClass", "Connection ( Source/Destination )", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MultiOperationClass: public Ui_MultiOperationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTIOPERATION_H
