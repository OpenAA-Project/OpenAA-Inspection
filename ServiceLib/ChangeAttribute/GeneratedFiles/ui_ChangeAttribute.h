/********************************************************************************
** Form generated from reading UI file 'ChangeAttribute.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEATTRIBUTE_H
#define UI_CHANGEATTRIBUTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangeAttributeClass
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEditGUIFileName;
    QPushButton *pushButtonSelectGUI;
    QLabel *label;
    QPushButton *pushButtonSelectSequence;
    QLineEdit *lineEditSequenceFile;
    QLabel *label_2;
    QPushButton *pushButtonSelectFilter;
    QLineEdit *lineEditFilterFile;
    QLabel *label_3;
    QPushButton *pushButtonSendGUI;
    QLabel *label_4;
    QTableWidget *tableWidget;
    QPushButton *pushButtonSendSequence;
    QPushButton *pushButtonSendFilter;

    void setupUi(QMainWindow *ChangeAttributeClass)
    {
        if (ChangeAttributeClass->objectName().isEmpty())
            ChangeAttributeClass->setObjectName("ChangeAttributeClass");
        ChangeAttributeClass->resize(535, 387);
        centralWidget = new QWidget(ChangeAttributeClass);
        centralWidget->setObjectName("centralWidget");
        lineEditGUIFileName = new QLineEdit(centralWidget);
        lineEditGUIFileName->setObjectName("lineEditGUIFileName");
        lineEditGUIFileName->setGeometry(QRect(10, 210, 311, 28));
        pushButtonSelectGUI = new QPushButton(centralWidget);
        pushButtonSelectGUI->setObjectName("pushButtonSelectGUI");
        pushButtonSelectGUI->setGeometry(QRect(320, 210, 41, 28));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 190, 481, 21));
        pushButtonSelectSequence = new QPushButton(centralWidget);
        pushButtonSelectSequence->setObjectName("pushButtonSelectSequence");
        pushButtonSelectSequence->setGeometry(QRect(320, 270, 41, 28));
        lineEditSequenceFile = new QLineEdit(centralWidget);
        lineEditSequenceFile->setObjectName("lineEditSequenceFile");
        lineEditSequenceFile->setGeometry(QRect(10, 270, 311, 28));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 250, 481, 21));
        pushButtonSelectFilter = new QPushButton(centralWidget);
        pushButtonSelectFilter->setObjectName("pushButtonSelectFilter");
        pushButtonSelectFilter->setGeometry(QRect(320, 330, 41, 28));
        lineEditFilterFile = new QLineEdit(centralWidget);
        lineEditFilterFile->setObjectName("lineEditFilterFile");
        lineEditFilterFile->setGeometry(QRect(10, 330, 311, 28));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 310, 481, 21));
        pushButtonSendGUI = new QPushButton(centralWidget);
        pushButtonSendGUI->setObjectName("pushButtonSendGUI");
        pushButtonSendGUI->setGeometry(QRect(400, 210, 93, 28));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 10, 481, 21));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 30, 511, 141));
        pushButtonSendSequence = new QPushButton(centralWidget);
        pushButtonSendSequence->setObjectName("pushButtonSendSequence");
        pushButtonSendSequence->setGeometry(QRect(400, 270, 93, 28));
        pushButtonSendFilter = new QPushButton(centralWidget);
        pushButtonSendFilter->setObjectName("pushButtonSendFilter");
        pushButtonSendFilter->setGeometry(QRect(400, 330, 93, 28));
        ChangeAttributeClass->setCentralWidget(centralWidget);

        retranslateUi(ChangeAttributeClass);

        QMetaObject::connectSlotsByName(ChangeAttributeClass);
    } // setupUi

    void retranslateUi(QMainWindow *ChangeAttributeClass)
    {
        ChangeAttributeClass->setWindowTitle(QCoreApplication::translate("ChangeAttributeClass", "ChangeAttribute", nullptr));
        pushButtonSelectGUI->setText(QCoreApplication::translate("ChangeAttributeClass", "...", nullptr));
        label->setText(QCoreApplication::translate("ChangeAttributeClass", "GUI file", nullptr));
        pushButtonSelectSequence->setText(QCoreApplication::translate("ChangeAttributeClass", "...", nullptr));
        label_2->setText(QCoreApplication::translate("ChangeAttributeClass", "Sequence file", nullptr));
        pushButtonSelectFilter->setText(QCoreApplication::translate("ChangeAttributeClass", "...", nullptr));
        label_3->setText(QCoreApplication::translate("ChangeAttributeClass", "Filter file", nullptr));
        pushButtonSendGUI->setText(QCoreApplication::translate("ChangeAttributeClass", "Send", nullptr));
        label_4->setText(QCoreApplication::translate("ChangeAttributeClass", "Choose Program", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ChangeAttributeClass", "PID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ChangeAttributeClass", "Process name", nullptr));
        pushButtonSendSequence->setText(QCoreApplication::translate("ChangeAttributeClass", "Send", nullptr));
        pushButtonSendFilter->setText(QCoreApplication::translate("ChangeAttributeClass", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeAttributeClass: public Ui_ChangeAttributeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEATTRIBUTE_H
