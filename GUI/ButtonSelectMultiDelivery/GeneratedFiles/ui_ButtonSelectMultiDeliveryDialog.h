/********************************************************************************
** Form generated from reading UI file 'ButtonSelectMultiDeliveryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONSELECTMULTIDELIVERYDIALOG_H
#define UI_BUTTONSELECTMULTIDELIVERYDIALOG_H

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

class Ui_ButtonSelectMultiDeliveryDialog
{
public:
    QLineEdit *EditName;
    QPushButton *ButtonCreate;
    QLabel *label_3;
    QLineEdit *EditID;
    QPushButton *ButtonCancel;
    QLabel *label_2;
    QLabel *label_4;
    QLineEdit *EditRemark;
    QLabel *label;
    QTableWidget *tableWidgetLot;
    QPushButton *ButtonSelect;

    void setupUi(QDialog *ButtonSelectMultiDeliveryDialog)
    {
        if (ButtonSelectMultiDeliveryDialog->objectName().isEmpty())
            ButtonSelectMultiDeliveryDialog->setObjectName("ButtonSelectMultiDeliveryDialog");
        ButtonSelectMultiDeliveryDialog->resize(532, 392);
        EditName = new QLineEdit(ButtonSelectMultiDeliveryDialog);
        EditName->setObjectName("EditName");
        EditName->setGeometry(QRect(150, 30, 171, 21));
        ButtonCreate = new QPushButton(ButtonSelectMultiDeliveryDialog);
        ButtonCreate->setObjectName("ButtonCreate");
        ButtonCreate->setGeometry(QRect(230, 60, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Make.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCreate->setIcon(icon);
        label_3 = new QLabel(ButtonSelectMultiDeliveryDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(320, 10, 201, 16));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditID = new QLineEdit(ButtonSelectMultiDeliveryDialog);
        EditID->setObjectName("EditID");
        EditID->setGeometry(QRect(10, 30, 141, 21));
        ButtonCancel = new QPushButton(ButtonSelectMultiDeliveryDialog);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(440, 60, 81, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        label_2 = new QLabel(ButtonSelectMultiDeliveryDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(150, 10, 171, 16));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(ButtonSelectMultiDeliveryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 60, 211, 16));
        EditRemark = new QLineEdit(ButtonSelectMultiDeliveryDialog);
        EditRemark->setObjectName("EditRemark");
        EditRemark->setGeometry(QRect(320, 30, 201, 21));
        label = new QLabel(ButtonSelectMultiDeliveryDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 141, 16));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetLot = new QTableWidget(ButtonSelectMultiDeliveryDialog);
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
        tableWidgetLot->setGeometry(QRect(10, 100, 511, 281));
        tableWidgetLot->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLot->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonSelect = new QPushButton(ButtonSelectMultiDeliveryDialog);
        ButtonSelect->setObjectName("ButtonSelect");
        ButtonSelect->setGeometry(QRect(330, 60, 81, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonSelect->setIcon(icon2);

        retranslateUi(ButtonSelectMultiDeliveryDialog);

        QMetaObject::connectSlotsByName(ButtonSelectMultiDeliveryDialog);
    } // setupUi

    void retranslateUi(QDialog *ButtonSelectMultiDeliveryDialog)
    {
        ButtonSelectMultiDeliveryDialog->setWindowTitle(QCoreApplication::translate("ButtonSelectMultiDeliveryDialog", "Select MultiDelivery", nullptr));
        ButtonCreate->setText(QCoreApplication::translate("ButtonSelectMultiDeliveryDialog", "Create new", nullptr));
        label_3->setText(QCoreApplication::translate("ButtonSelectMultiDeliveryDialog", "Remark", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("ButtonSelectMultiDeliveryDialog", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("ButtonSelectMultiDeliveryDialog", "Name", nullptr));
        label_4->setText(QCoreApplication::translate("ButtonSelectMultiDeliveryDialog", "ID\343\201\257\344\275\225\343\202\202\345\205\245\343\202\214\343\201\252\343\201\221\343\202\214\343\201\260\346\227\245\346\231\202\343\201\214\350\207\252\345\213\225\347\232\204\343\201\253\345\205\245\343\202\213", nullptr));
        label->setText(QCoreApplication::translate("ButtonSelectMultiDeliveryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLot->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ButtonSelectMultiDeliveryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLot->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ButtonSelectMultiDeliveryDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLot->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ButtonSelectMultiDeliveryDialog", "Day Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLot->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ButtonSelectMultiDeliveryDialog", "Remark", nullptr));
        ButtonSelect->setText(QCoreApplication::translate("ButtonSelectMultiDeliveryDialog", "Select", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonSelectMultiDeliveryDialog: public Ui_ButtonSelectMultiDeliveryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONSELECTMULTIDELIVERYDIALOG_H
