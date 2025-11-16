/********************************************************************************
** Form generated from reading UI file 'ListboxGUITimeForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTBOXGUITIMEFORM_H
#define UI_LISTBOXGUITIMEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ListboxGUITimeFormClass
{
public:
    QTableWidget *tableWidget;
    QFrame *frame;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButtonUpdate;

    void setupUi(GUIFormBase *ListboxGUITimeFormClass)
    {
        if (ListboxGUITimeFormClass->objectName().isEmpty())
            ListboxGUITimeFormClass->setObjectName("ListboxGUITimeFormClass");
        ListboxGUITimeFormClass->resize(611, 413);
        tableWidget = new QTableWidget(ListboxGUITimeFormClass);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 611, 381));
        frame = new QFrame(ListboxGUITimeFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 380, 421, 31));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(190, 0, 121, 16));
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(320, 0, 71, 21));
        lineEdit->setReadOnly(true);
        pushButtonUpdate = new QPushButton(frame);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(30, 0, 151, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon);

        retranslateUi(ListboxGUITimeFormClass);

        QMetaObject::connectSlotsByName(ListboxGUITimeFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ListboxGUITimeFormClass)
    {
        ListboxGUITimeFormClass->setWindowTitle(QCoreApplication::translate("ListboxGUITimeFormClass", "ListboxGUITimeForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ListboxGUITimeFormClass", "DLLRoot", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ListboxGUITimeFormClass", "DLLName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ListboxGUITimeFormClass", "InstName", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ListboxGUITimeFormClass", "STime", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ListboxGUITimeFormClass", "RTime", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ListboxGUITimeFormClass", "CTime", nullptr));
        label->setText(QCoreApplication::translate("ListboxGUITimeFormClass", "Total time", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("ListboxGUITimeFormClass", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListboxGUITimeFormClass: public Ui_ListboxGUITimeFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTBOXGUITIMEFORM_H
