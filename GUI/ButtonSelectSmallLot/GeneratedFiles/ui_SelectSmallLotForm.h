/********************************************************************************
** Form generated from reading UI file 'SelectSmallLotForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTSMALLLOTFORM_H
#define UI_SELECTSMALLLOTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectSmallLotForm
{
public:
    QPushButton *ButtonSelect;
    QLineEdit *EditID;
    QLineEdit *EditName;
    QLineEdit *EditRemark;
    QPushButton *ButtonCreate;
    QLabel *label_3;
    QLabel *label;
    QPushButton *ButtonCancel;
    QLabel *label_2;
    QLabel *label_4;
    QTableWidget *tableWidgetLot;
    QPushButton *pushButtonIncrement;

    void setupUi(QDialog *SelectSmallLotForm)
    {
        if (SelectSmallLotForm->objectName().isEmpty())
            SelectSmallLotForm->setObjectName("SelectSmallLotForm");
        SelectSmallLotForm->resize(512, 419);
        ButtonSelect = new QPushButton(SelectSmallLotForm);
        ButtonSelect->setObjectName("ButtonSelect");
        ButtonSelect->setGeometry(QRect(300, 80, 101, 31));
        EditID = new QLineEdit(SelectSmallLotForm);
        EditID->setObjectName("EditID");
        EditID->setGeometry(QRect(0, 20, 141, 21));
        EditName = new QLineEdit(SelectSmallLotForm);
        EditName->setObjectName("EditName");
        EditName->setGeometry(QRect(140, 20, 171, 21));
        EditRemark = new QLineEdit(SelectSmallLotForm);
        EditRemark->setObjectName("EditRemark");
        EditRemark->setGeometry(QRect(310, 20, 201, 21));
        ButtonCreate = new QPushButton(SelectSmallLotForm);
        ButtonCreate->setObjectName("ButtonCreate");
        ButtonCreate->setGeometry(QRect(150, 80, 131, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Make.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCreate->setIcon(icon);
        label_3 = new QLabel(SelectSmallLotForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(310, 0, 201, 16));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(SelectSmallLotForm);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 141, 16));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonCancel = new QPushButton(SelectSmallLotForm);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(410, 80, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        label_2 = new QLabel(SelectSmallLotForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 0, 171, 16));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(SelectSmallLotForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 50, 401, 16));
        tableWidgetLot = new QTableWidget(SelectSmallLotForm);
        if (tableWidgetLot->columnCount() < 4)
            tableWidgetLot->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLot->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLot->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLot->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLot->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetLot->setObjectName("tableWidgetLot");
        tableWidgetLot->setGeometry(QRect(0, 120, 511, 291));
        tableWidgetLot->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLot->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonIncrement = new QPushButton(SelectSmallLotForm);
        pushButtonIncrement->setObjectName("pushButtonIncrement");
        pushButtonIncrement->setGeometry(QRect(300, 80, 101, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonIncrement->setIcon(icon2);

        retranslateUi(SelectSmallLotForm);

        QMetaObject::connectSlotsByName(SelectSmallLotForm);
    } // setupUi

    void retranslateUi(QDialog *SelectSmallLotForm)
    {
        SelectSmallLotForm->setWindowTitle(QCoreApplication::translate("SelectSmallLotForm", "Select SmallLot", nullptr));
        ButtonSelect->setText(QCoreApplication::translate("SelectSmallLotForm", "Select", nullptr));
        ButtonCreate->setText(QCoreApplication::translate("SelectSmallLotForm", "Create new", nullptr));
        label_3->setText(QCoreApplication::translate("SelectSmallLotForm", "Remark", nullptr));
        label->setText(QCoreApplication::translate("SelectSmallLotForm", "ID", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SelectSmallLotForm", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("SelectSmallLotForm", "Name", nullptr));
        label_4->setText(QCoreApplication::translate("SelectSmallLotForm", "ID\343\201\257\344\275\225\343\202\202\345\205\245\343\202\214\343\201\252\343\201\221\343\202\214\343\201\260\346\227\245\346\231\202\343\201\214\350\207\252\345\213\225\347\232\204\343\201\253\345\205\245\343\202\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLot->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectSmallLotForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLot->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectSmallLotForm", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLot->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectSmallLotForm", "Day Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLot->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectSmallLotForm", "Remark", nullptr));
        pushButtonIncrement->setText(QCoreApplication::translate("SelectSmallLotForm", "Increment", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectSmallLotForm: public Ui_SelectSmallLotForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTSMALLLOTFORM_H
