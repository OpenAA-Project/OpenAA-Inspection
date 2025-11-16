/********************************************************************************
** Form generated from reading UI file 'Messager.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGER_H
#define UI_MESSAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MessagerClass
{
public:
    QWidget *centralWidget;
    QTableWidget *tableWidget;
    QTableWidget *tableWidgetGeneral;
    QPushButton *pushButtonSequence;
    QPushButton *pushButtonClose;

    void setupUi(QMainWindow *MessagerClass)
    {
        if (MessagerClass->objectName().isEmpty())
            MessagerClass->setObjectName("MessagerClass");
        MessagerClass->resize(411, 263);
        centralWidget = new QWidget(MessagerClass);
        centralWidget->setObjectName("centralWidget");
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 110, 411, 131));
        tableWidgetGeneral = new QTableWidget(centralWidget);
        if (tableWidgetGeneral->columnCount() < 2)
            tableWidgetGeneral->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetGeneral->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetGeneral->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        tableWidgetGeneral->setObjectName("tableWidgetGeneral");
        tableWidgetGeneral->setGeometry(QRect(0, 0, 411, 111));
        pushButtonSequence = new QPushButton(centralWidget);
        pushButtonSequence->setObjectName("pushButtonSequence");
        pushButtonSequence->setGeometry(QRect(10, 240, 75, 23));
        pushButtonClose = new QPushButton(centralWidget);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(330, 240, 75, 23));
        MessagerClass->setCentralWidget(centralWidget);

        retranslateUi(MessagerClass);

        QMetaObject::connectSlotsByName(MessagerClass);
    } // setupUi

    void retranslateUi(QMainWindow *MessagerClass)
    {
        MessagerClass->setWindowTitle(QCoreApplication::translate("MessagerClass", "Messager", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MessagerClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MessagerClass", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MessagerClass", "Message", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetGeneral->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MessagerClass", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetGeneral->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MessagerClass", "Message", nullptr));
        pushButtonSequence->setText(QCoreApplication::translate("MessagerClass", "Sequence", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("MessagerClass", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MessagerClass: public Ui_MessagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGER_H
