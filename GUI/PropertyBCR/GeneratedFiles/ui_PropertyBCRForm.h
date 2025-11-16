/********************************************************************************
** Form generated from reading UI file 'PropertyBCRForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYBCRFORM_H
#define UI_PROPERTYBCRFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyBCRForm
{
public:
    QTableWidget *tableWidget;
    QLabel *label;
    QPushButton *pushButtonTest;
    QLabel *labelTestBCode;

    void setupUi(GUIFormBase *PropertyBCRForm)
    {
        if (PropertyBCRForm->objectName().isEmpty())
            PropertyBCRForm->setObjectName("PropertyBCRForm");
        PropertyBCRForm->resize(400, 567);
        tableWidget = new QTableWidget(PropertyBCRForm);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 40, 371, 192));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(PropertyBCRForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 371, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        pushButtonTest = new QPushButton(PropertyBCRForm);
        pushButtonTest->setObjectName("pushButtonTest");
        pushButtonTest->setGeometry(QRect(50, 250, 91, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Test.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonTest->setIcon(icon);
        labelTestBCode = new QLabel(PropertyBCRForm);
        labelTestBCode->setObjectName("labelTestBCode");
        labelTestBCode->setGeometry(QRect(50, 300, 311, 31));
        labelTestBCode->setFrameShape(QFrame::Panel);
        labelTestBCode->setFrameShadow(QFrame::Sunken);

        retranslateUi(PropertyBCRForm);

        QMetaObject::connectSlotsByName(PropertyBCRForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyBCRForm)
    {
        PropertyBCRForm->setWindowTitle(QCoreApplication::translate("PropertyBCRForm", "Property BCR", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyBCRForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyBCRForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyBCRForm", "Location", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyBCRForm", "Type", nullptr));
        label->setText(QCoreApplication::translate("PropertyBCRForm", "Barcode area", nullptr));
        pushButtonTest->setText(QCoreApplication::translate("PropertyBCRForm", "Test", nullptr));
        labelTestBCode->setText(QCoreApplication::translate("PropertyBCRForm", "XXXX-XXXX", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyBCRForm: public Ui_PropertyBCRForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYBCRFORM_H
