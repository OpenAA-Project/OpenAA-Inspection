/********************************************************************************
** Form generated from reading UI file 'SelectColorSample.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTCOLORSAMPLE_H
#define UI_SELECTCOLORSAMPLE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectColorSample
{
public:
    QTableWidget *tableWidget;
    QFrame *frame;
    QLabel *label;
    QLineEdit *lineEditName;
    QPushButton *pushButtonSaveNew;
    QPushButton *pushButtonUpdate;
    QLineEdit *lineEditAutocount;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonDelete;

    void setupUi(QWidget *SelectColorSample)
    {
        if (SelectColorSample->objectName().isEmpty())
            SelectColorSample->setObjectName("SelectColorSample");
        SelectColorSample->resize(201, 440);
        tableWidget = new QTableWidget(SelectColorSample);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 200, 181, 192));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(SelectColorSample);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 181, 101));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 181, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditName = new QLineEdit(frame);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(60, 30, 111, 20));
        pushButtonSaveNew = new QPushButton(frame);
        pushButtonSaveNew->setObjectName("pushButtonSaveNew");
        pushButtonSaveNew->setGeometry(QRect(90, 60, 81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSaveNew->setIcon(icon);
        pushButtonUpdate = new QPushButton(frame);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(10, 60, 75, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon1);
        lineEditAutocount = new QLineEdit(frame);
        lineEditAutocount->setObjectName("lineEditAutocount");
        lineEditAutocount->setGeometry(QRect(10, 30, 51, 20));
        pushButtonSelect = new QPushButton(SelectColorSample);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(100, 400, 91, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSelect->setIcon(icon2);
        pushButtonDelete = new QPushButton(SelectColorSample);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(10, 400, 81, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDelete->setIcon(icon3);

        retranslateUi(SelectColorSample);

        QMetaObject::connectSlotsByName(SelectColorSample);
    } // setupUi

    void retranslateUi(QWidget *SelectColorSample)
    {
        SelectColorSample->setWindowTitle(QCoreApplication::translate("SelectColorSample", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectColorSample", "Count", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectColorSample", "Name", nullptr));
        label->setText(QCoreApplication::translate("SelectColorSample", "Save / Update", nullptr));
        lineEditName->setText(QCoreApplication::translate("SelectColorSample", "XXX", nullptr));
        pushButtonSaveNew->setText(QCoreApplication::translate("SelectColorSample", "Save new", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("SelectColorSample", "Update", nullptr));
        lineEditAutocount->setText(QCoreApplication::translate("SelectColorSample", "123", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectColorSample", "Select", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("SelectColorSample", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectColorSample: public Ui_SelectColorSample {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTCOLORSAMPLE_H
