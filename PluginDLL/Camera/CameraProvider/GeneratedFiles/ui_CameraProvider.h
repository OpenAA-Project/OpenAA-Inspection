/********************************************************************************
** Form generated from reading UI file 'CameraProvider.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAPROVIDER_H
#define UI_CAMERAPROVIDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraProviderClass
{
public:
    QWidget *centralWidget;
    QTableWidget *tableWidget;
    QProgressBar *progressBar;

    void setupUi(QMainWindow *CameraProviderClass)
    {
        if (CameraProviderClass->objectName().isEmpty())
            CameraProviderClass->setObjectName("CameraProviderClass");
        CameraProviderClass->resize(439, 229);
        centralWidget = new QWidget(CameraProviderClass);
        centralWidget->setObjectName("centralWidget");
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 421, 171));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(10, 190, 421, 23));
        progressBar->setMaximum(1000);
        progressBar->setValue(24);
        CameraProviderClass->setCentralWidget(centralWidget);

        retranslateUi(CameraProviderClass);

        QMetaObject::connectSlotsByName(CameraProviderClass);
    } // setupUi

    void retranslateUi(QMainWindow *CameraProviderClass)
    {
        CameraProviderClass->setWindowTitle(QCoreApplication::translate("CameraProviderClass", "CameraProvider", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CameraProviderClass", "CameraNo", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CameraProviderClass", "DLL file name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraProviderClass: public Ui_CameraProviderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAPROVIDER_H
