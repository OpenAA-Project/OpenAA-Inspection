/********************************************************************************
** Form generated from reading UI file 'PropertyARArrangeForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYARARRANGEFORM_H
#define UI_PROPERTYARARRANGEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyARArrangeFormClass
{
public:
    QTableWidget *tableWidgetRegistration;
    QLabel *label;
    QTableWidget *tableWidgetArrange;
    QLabel *label_2;
    QPushButton *pushButtonUpdate;
    QLabel *labelThumnail;

    void setupUi(GUIFormBase *PropertyARArrangeFormClass)
    {
        if (PropertyARArrangeFormClass->objectName().isEmpty())
            PropertyARArrangeFormClass->setObjectName("PropertyARArrangeFormClass");
        PropertyARArrangeFormClass->resize(373, 700);
        tableWidgetRegistration = new QTableWidget(PropertyARArrangeFormClass);
        if (tableWidgetRegistration->columnCount() < 3)
            tableWidgetRegistration->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetRegistration->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetRegistration->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetRegistration->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetRegistration->setObjectName("tableWidgetRegistration");
        tableWidgetRegistration->setGeometry(QRect(10, 320, 261, 181));
        tableWidgetRegistration->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetRegistration->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(PropertyARArrangeFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 300, 261, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetArrange = new QTableWidget(PropertyARArrangeFormClass);
        if (tableWidgetArrange->columnCount() < 3)
            tableWidgetArrange->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetArrange->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetArrange->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetArrange->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        tableWidgetArrange->setObjectName("tableWidgetArrange");
        tableWidgetArrange->setGeometry(QRect(10, 530, 351, 161));
        tableWidgetArrange->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetArrange->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_2 = new QLabel(PropertyARArrangeFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 510, 351, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonUpdate = new QPushButton(PropertyARArrangeFormClass);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(280, 320, 81, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon);
        labelThumnail = new QLabel(PropertyARArrangeFormClass);
        labelThumnail->setObjectName("labelThumnail");
        labelThumnail->setGeometry(QRect(10, 10, 351, 271));

        retranslateUi(PropertyARArrangeFormClass);

        QMetaObject::connectSlotsByName(PropertyARArrangeFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyARArrangeFormClass)
    {
        PropertyARArrangeFormClass->setWindowTitle(QCoreApplication::translate("PropertyARArrangeFormClass", "PropertyARArrangeForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetRegistration->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyARArrangeFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetRegistration->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyARArrangeFormClass", "Date/Tme", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetRegistration->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyARArrangeFormClass", "Position", nullptr));
        label->setText(QCoreApplication::translate("PropertyARArrangeFormClass", "Additional Registation", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetArrange->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyARArrangeFormClass", "ItemID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetArrange->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyARArrangeFormClass", "Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetArrange->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyARArrangeFormClass", "OK/NG", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyARArrangeFormClass", "Arrangement", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("PropertyARArrangeFormClass", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyARArrangeFormClass: public Ui_PropertyARArrangeFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYARARRANGEFORM_H
