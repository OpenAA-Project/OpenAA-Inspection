/********************************************************************************
** Form generated from reading UI file 'SelectLotForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLOTFORM_H
#define UI_SELECTLOTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectLotForm
{
public:
    QLabel *label_4;
    QLabel *label;
    QLineEdit *EditName;
    QLineEdit *EditRemark;
    QPushButton *ButtonCreate;
    QLineEdit *EditID;
    QPushButton *ButtonCancel;
    QTableWidget *tableWidgetLot;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *ButtonSelect;

    void setupUi(QWidget *SelectLotForm)
    {
        if (SelectLotForm->objectName().isEmpty())
            SelectLotForm->setObjectName("SelectLotForm");
        SelectLotForm->resize(529, 422);
        label_4 = new QLabel(SelectLotForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 60, 511, 16));
        label = new QLabel(SelectLotForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 141, 16));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditName = new QLineEdit(SelectLotForm);
        EditName->setObjectName("EditName");
        EditName->setGeometry(QRect(150, 30, 171, 21));
        EditRemark = new QLineEdit(SelectLotForm);
        EditRemark->setObjectName("EditRemark");
        EditRemark->setGeometry(QRect(320, 30, 201, 21));
        ButtonCreate = new QPushButton(SelectLotForm);
        ButtonCreate->setObjectName("ButtonCreate");
        ButtonCreate->setGeometry(QRect(170, 90, 131, 31));
        EditID = new QLineEdit(SelectLotForm);
        EditID->setObjectName("EditID");
        EditID->setGeometry(QRect(10, 30, 141, 21));
        ButtonCancel = new QPushButton(SelectLotForm);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(430, 90, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon);
        tableWidgetLot = new QTableWidget(SelectLotForm);
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
        tableWidgetLot->setGeometry(QRect(10, 130, 511, 281));
        tableWidgetLot->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLot->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_2 = new QLabel(SelectLotForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(150, 10, 171, 16));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(SelectLotForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(320, 10, 201, 16));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonSelect = new QPushButton(SelectLotForm);
        ButtonSelect->setObjectName("ButtonSelect");
        ButtonSelect->setGeometry(QRect(310, 90, 111, 31));

        retranslateUi(SelectLotForm);

        QMetaObject::connectSlotsByName(SelectLotForm);
    } // setupUi

    void retranslateUi(QWidget *SelectLotForm)
    {
        SelectLotForm->setWindowTitle(QCoreApplication::translate("SelectLotForm", "Form", nullptr));
        label_4->setText(QCoreApplication::translate("SelectLotForm", "ID\343\201\257\344\275\225\343\202\202\345\205\245\343\202\214\343\201\252\343\201\221\343\202\214\343\201\260\346\227\245\346\231\202\343\201\214\350\207\252\345\213\225\347\232\204\343\201\253\345\205\245\343\202\213", nullptr));
        label->setText(QCoreApplication::translate("SelectLotForm", "ID", nullptr));
        ButtonCreate->setText(QCoreApplication::translate("SelectLotForm", "Create new", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SelectLotForm", "Cancel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLot->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectLotForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLot->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectLotForm", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLot->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectLotForm", "Day Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLot->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectLotForm", "Remark", nullptr));
        label_2->setText(QCoreApplication::translate("SelectLotForm", "Name", nullptr));
        label_3->setText(QCoreApplication::translate("SelectLotForm", "Remark", nullptr));
        ButtonSelect->setText(QCoreApplication::translate("SelectLotForm", "Select", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLotForm: public Ui_SelectLotForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLOTFORM_H
