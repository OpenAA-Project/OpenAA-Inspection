/********************************************************************************
** Form generated from reading UI file 'VirtualPIOClient.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIRTUALPIOCLIENT_H
#define UI_VIRTUALPIOCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VirtualPIOClientClass
{
public:
    QWidget *centralWidget;
    QTableWidget *tableWidget;
    QTableWidget *tableWidgetPortBitsIn;
    QTableWidget *tableWidgetPortBitsOut;
    QLabel *label;
    QLabel *label_2;
    QProgressBar *progressBar;

    void setupUi(QMainWindow *VirtualPIOClientClass)
    {
        if (VirtualPIOClientClass->objectName().isEmpty())
            VirtualPIOClientClass->setObjectName("VirtualPIOClientClass");
        VirtualPIOClientClass->resize(433, 488);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(VirtualPIOClientClass->sizePolicy().hasHeightForWidth());
        VirtualPIOClientClass->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        VirtualPIOClientClass->setPalette(palette);
        centralWidget = new QWidget(VirtualPIOClientClass);
        centralWidget->setObjectName("centralWidget");
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 256, 71));
        tableWidgetPortBitsIn = new QTableWidget(centralWidget);
        if (tableWidgetPortBitsIn->columnCount() < 3)
            tableWidgetPortBitsIn->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetPortBitsIn->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetPortBitsIn->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetPortBitsIn->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        tableWidgetPortBitsIn->setObjectName("tableWidgetPortBitsIn");
        tableWidgetPortBitsIn->setGeometry(QRect(0, 100, 211, 351));
        tableWidgetPortBitsOut = new QTableWidget(centralWidget);
        if (tableWidgetPortBitsOut->columnCount() < 3)
            tableWidgetPortBitsOut->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetPortBitsOut->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetPortBitsOut->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetPortBitsOut->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        tableWidgetPortBitsOut->setObjectName("tableWidgetPortBitsOut");
        tableWidgetPortBitsOut->setGeometry(QRect(220, 100, 211, 351));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 80, 56, 12));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(240, 80, 56, 12));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(10, 460, 411, 23));
        progressBar->setValue(24);
        progressBar->setTextVisible(false);
        VirtualPIOClientClass->setCentralWidget(centralWidget);

        retranslateUi(VirtualPIOClientClass);

        QMetaObject::connectSlotsByName(VirtualPIOClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *VirtualPIOClientClass)
    {
        VirtualPIOClientClass->setWindowTitle(QCoreApplication::translate("VirtualPIOClientClass", "VirtualPIOClient", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("VirtualPIOClientClass", "Server Host IP", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("VirtualPIOClientClass", "Port", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetPortBitsIn->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("VirtualPIOClientClass", "No", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetPortBitsIn->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("VirtualPIOClientClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetPortBitsIn->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("VirtualPIOClientClass", "Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetPortBitsOut->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("VirtualPIOClientClass", "No", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetPortBitsOut->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("VirtualPIOClientClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetPortBitsOut->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("VirtualPIOClientClass", "Data", nullptr));
        label->setText(QCoreApplication::translate("VirtualPIOClientClass", "Input", nullptr));
        label_2->setText(QCoreApplication::translate("VirtualPIOClientClass", "Output", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VirtualPIOClientClass: public Ui_VirtualPIOClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIRTUALPIOCLIENT_H
