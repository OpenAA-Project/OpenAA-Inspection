/********************************************************************************
** Form generated from reading UI file 'PropertyMatchingAlignmentForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYMATCHINGALIGNMENTFORM_H
#define UI_PROPERTYMATCHINGALIGNMENTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyMatchingAlignmentFormClass
{
public:
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxCoverRate;
    QDoubleSpinBox *doubleSpinBoxPickUpVar;
    QPushButton *pushButtonCreateSpecified;
    QTableWidget *tableWidget;
    QToolButton *toolButtonSpecified;
    QLabel *label_3;
    QSpinBox *spinBoxBlockSize;

    void setupUi(GUIFormBase *PropertyMatchingAlignmentFormClass)
    {
        if (PropertyMatchingAlignmentFormClass->objectName().isEmpty())
            PropertyMatchingAlignmentFormClass->setObjectName("PropertyMatchingAlignmentFormClass");
        PropertyMatchingAlignmentFormClass->resize(400, 489);
        label = new QLabel(PropertyMatchingAlignmentFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 20, 111, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(PropertyMatchingAlignmentFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 70, 111, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxCoverRate = new QDoubleSpinBox(PropertyMatchingAlignmentFormClass);
        doubleSpinBoxCoverRate->setObjectName("doubleSpinBoxCoverRate");
        doubleSpinBoxCoverRate->setGeometry(QRect(70, 40, 91, 22));
        doubleSpinBoxCoverRate->setMaximum(100.000000000000000);
        doubleSpinBoxPickUpVar = new QDoubleSpinBox(PropertyMatchingAlignmentFormClass);
        doubleSpinBoxPickUpVar->setObjectName("doubleSpinBoxPickUpVar");
        doubleSpinBoxPickUpVar->setGeometry(QRect(70, 90, 91, 22));
        doubleSpinBoxPickUpVar->setMaximum(100000000.000000000000000);
        pushButtonCreateSpecified = new QPushButton(PropertyMatchingAlignmentFormClass);
        pushButtonCreateSpecified->setObjectName("pushButtonCreateSpecified");
        pushButtonCreateSpecified->setGeometry(QRect(10, 130, 221, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Make.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCreateSpecified->setIcon(icon);
        tableWidget = new QTableWidget(PropertyMatchingAlignmentFormClass);
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
        tableWidget->setGeometry(QRect(10, 200, 381, 281));
        toolButtonSpecified = new QToolButton(PropertyMatchingAlignmentFormClass);
        toolButtonSpecified->setObjectName("toolButtonSpecified");
        toolButtonSpecified->setGeometry(QRect(240, 130, 121, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Area.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonSpecified->setIcon(icon1);
        toolButtonSpecified->setCheckable(true);
        toolButtonSpecified->setChecked(false);
        toolButtonSpecified->setAutoExclusive(true);
        toolButtonSpecified->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        label_3 = new QLabel(PropertyMatchingAlignmentFormClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(220, 20, 111, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxBlockSize = new QSpinBox(PropertyMatchingAlignmentFormClass);
        spinBoxBlockSize->setObjectName("spinBoxBlockSize");
        spinBoxBlockSize->setGeometry(QRect(220, 40, 111, 22));
        spinBoxBlockSize->setMaximum(99999999);

        retranslateUi(PropertyMatchingAlignmentFormClass);

        QMetaObject::connectSlotsByName(PropertyMatchingAlignmentFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyMatchingAlignmentFormClass)
    {
        PropertyMatchingAlignmentFormClass->setWindowTitle(QCoreApplication::translate("PropertyMatchingAlignmentFormClass", "PropertyMatchingAlignmentForm", nullptr));
        label->setText(QCoreApplication::translate("PropertyMatchingAlignmentFormClass", "\347\211\271\345\276\264\351\235\242\347\251\215\346\257\224\347\216\207", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyMatchingAlignmentFormClass", "\347\211\271\345\276\264\345\210\206\346\225\243\344\270\213\351\231\220", nullptr));
        pushButtonCreateSpecified->setText(QCoreApplication::translate("PropertyMatchingAlignmentFormClass", "\351\201\270\346\212\236\343\202\242\343\202\244\343\203\206\343\203\240\343\201\256\347\211\271\345\276\264\351\240\230\345\237\237\343\202\222\344\275\234\346\210\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyMatchingAlignmentFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyMatchingAlignmentFormClass", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyMatchingAlignmentFormClass", "ItemID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyMatchingAlignmentFormClass", "Area", nullptr));
        toolButtonSpecified->setText(QCoreApplication::translate("PropertyMatchingAlignmentFormClass", "\347\211\271\345\276\264\351\240\230\345\237\237\343\201\256\350\241\250\347\244\272", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyMatchingAlignmentFormClass", "\343\203\226\343\203\255\343\203\203\343\202\257\343\202\265\343\202\244\343\202\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyMatchingAlignmentFormClass: public Ui_PropertyMatchingAlignmentFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYMATCHINGALIGNMENTFORM_H
