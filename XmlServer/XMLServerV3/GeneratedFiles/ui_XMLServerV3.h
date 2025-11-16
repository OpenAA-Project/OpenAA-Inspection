/********************************************************************************
** Form generated from reading UI file 'XMLServerV3.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XMLSERVERV3_H
#define UI_XMLSERVERV3_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XMLServerV3Class
{
public:
    QWidget *centralWidget;
    QTableWidget *tableWidgetTable;
    QTableWidget *tableWidgetClient;
    QLabel *label;
    QLabel *label_2;
    QTableWidget *tableWidgetCommand;
    QLabel *label_3;
    QPushButton *pushButtonSetting;
    QPushButton *pushButtonWriteOut;
    QCheckBox *checkBoxShowAll;
    QProgressBar *progressBar;

    void setupUi(QMainWindow *XMLServerV3Class)
    {
        if (XMLServerV3Class->objectName().isEmpty())
            XMLServerV3Class->setObjectName(QString::fromUtf8("XMLServerV3Class"));
        XMLServerV3Class->resize(579, 703);
        centralWidget = new QWidget(XMLServerV3Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tableWidgetTable = new QTableWidget(centralWidget);
        if (tableWidgetTable->columnCount() < 1)
            tableWidgetTable->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidgetTable->setObjectName(QString::fromUtf8("tableWidgetTable"));
        tableWidgetTable->setGeometry(QRect(10, 30, 561, 141));
        tableWidgetTable->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetClient = new QTableWidget(centralWidget);
        if (tableWidgetClient->columnCount() < 5)
            tableWidgetClient->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetClient->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetClient->setHorizontalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetClient->setHorizontalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetClient->setHorizontalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetClient->setHorizontalHeaderItem(4, __qtablewidgetitem5);
        tableWidgetClient->setObjectName(QString::fromUtf8("tableWidgetClient"));
        tableWidgetClient->setGeometry(QRect(10, 200, 561, 192));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 561, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 180, 561, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        tableWidgetCommand = new QTableWidget(centralWidget);
        if (tableWidgetCommand->columnCount() < 5)
            tableWidgetCommand->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetCommand->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetCommand->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetCommand->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetCommand->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetCommand->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        tableWidgetCommand->setObjectName(QString::fromUtf8("tableWidgetCommand"));
        tableWidgetCommand->setGeometry(QRect(10, 420, 561, 192));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 400, 561, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        pushButtonSetting = new QPushButton(centralWidget);
        pushButtonSetting->setObjectName(QString::fromUtf8("pushButtonSetting"));
        pushButtonSetting->setGeometry(QRect(10, 660, 75, 23));
        pushButtonWriteOut = new QPushButton(centralWidget);
        pushButtonWriteOut->setObjectName(QString::fromUtf8("pushButtonWriteOut"));
        pushButtonWriteOut->setGeometry(QRect(110, 660, 75, 23));
        checkBoxShowAll = new QCheckBox(centralWidget);
        checkBoxShowAll->setObjectName(QString::fromUtf8("checkBoxShowAll"));
        checkBoxShowAll->setGeometry(QRect(20, 400, 76, 17));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 620, 561, 23));
        progressBar->setValue(24);
        progressBar->setTextVisible(false);
        XMLServerV3Class->setCentralWidget(centralWidget);

        retranslateUi(XMLServerV3Class);
        QObject::connect(pushButtonSetting, SIGNAL(clicked()), XMLServerV3Class, SLOT(slotSetting()));
        QObject::connect(pushButtonWriteOut, SIGNAL(clicked()), XMLServerV3Class, SLOT(slotWriteOut()));

        QMetaObject::connectSlotsByName(XMLServerV3Class);
    } // setupUi

    void retranslateUi(QMainWindow *XMLServerV3Class)
    {
        XMLServerV3Class->setWindowTitle(QCoreApplication::translate("XMLServerV3Class", "XMLServerV3", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("XMLServerV3Class", "TableName", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetClient->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("XMLServerV3Class", "Client-ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetClient->horizontalHeaderItem(1);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("XMLServerV3Class", "Client-IP", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetClient->horizontalHeaderItem(2);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("XMLServerV3Class", "OpHandle", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetClient->horizontalHeaderItem(3);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("XMLServerV3Class", "Access time", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetClient->horizontalHeaderItem(4);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("XMLServerV3Class", "Queued", nullptr));
        label->setText(QCoreApplication::translate("XMLServerV3Class", "XML Table data", nullptr));
        label_2->setText(QCoreApplication::translate("XMLServerV3Class", "Client", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetCommand->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("XMLServerV3Class", "Access Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetCommand->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("XMLServerV3Class", "XML-ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetCommand->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("XMLServerV3Class", "OpeHandle", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetCommand->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("XMLServerV3Class", "Command", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetCommand->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("XMLServerV3Class", "Milisec", nullptr));
        label_3->setText(QCoreApplication::translate("XMLServerV3Class", "Command", nullptr));
        pushButtonSetting->setText(QCoreApplication::translate("XMLServerV3Class", "Setting", nullptr));
        pushButtonWriteOut->setText(QCoreApplication::translate("XMLServerV3Class", "WriteOut", nullptr));
        checkBoxShowAll->setText(QCoreApplication::translate("XMLServerV3Class", "Show all", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XMLServerV3Class: public Ui_XMLServerV3Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XMLSERVERV3_H
