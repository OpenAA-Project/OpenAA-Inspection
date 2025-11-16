/********************************************************************************
** Form generated from reading UI file 'PropertyProcess3DForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYPROCESS3DFORM_H
#define UI_PROPERTYPROCESS3DFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyProcess3DForm
{
public:
    QPushButton *pushButtonEditLibrary;
    QTableWidget *tableWidget;

    void setupUi(GUIFormBase *PropertyProcess3DForm)
    {
        if (PropertyProcess3DForm->objectName().isEmpty())
            PropertyProcess3DForm->setObjectName("PropertyProcess3DForm");
        PropertyProcess3DForm->resize(400, 700);
        pushButtonEditLibrary = new QPushButton(PropertyProcess3DForm);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(10, 10, 211, 31));
        QFont font;
        font.setPointSize(12);
        pushButtonEditLibrary->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon);
        tableWidget = new QTableWidget(PropertyProcess3DForm);
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
        tableWidget->setGeometry(QRect(10, 50, 381, 641));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(PropertyProcess3DForm);

        QMetaObject::connectSlotsByName(PropertyProcess3DForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyProcess3DForm)
    {
        PropertyProcess3DForm->setWindowTitle(QCoreApplication::translate("PropertyProcess3DForm", "Form", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyProcess3DForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyProcess3DForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyProcess3DForm", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyProcess3DForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyProcess3DForm", "ItemName", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyProcess3DForm: public Ui_PropertyProcess3DForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYPROCESS3DFORM_H
