/********************************************************************************
** Form generated from reading UI file 'SelectResultLotFrameDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTRESULTLOTFRAMEDIALOG_H
#define UI_SELECTRESULTLOTFRAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectResultLotFrameDialog
{
public:
    QLineEdit *EditID;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *EditRemark;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *EditName;
    QPushButton *ButtonCreate;
    QPushButton *ButtonCancel;
    QToolBox *toolBox;
    QWidget *page;
    QTableWidget *tableWidgetGroup;
    QWidget *page_2;
    QTableWidget *tableWidgetLot;
    QLabel *label_5;
    QLabel *label_6;

    void setupUi(QDialog *SelectResultLotFrameDialog)
    {
        if (SelectResultLotFrameDialog->objectName().isEmpty())
            SelectResultLotFrameDialog->setObjectName("SelectResultLotFrameDialog");
        SelectResultLotFrameDialog->resize(575, 560);
        EditID = new QLineEdit(SelectResultLotFrameDialog);
        EditID->setObjectName("EditID");
        EditID->setGeometry(QRect(10, 30, 141, 21));
        label_2 = new QLabel(SelectResultLotFrameDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 10, 171, 16));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(SelectResultLotFrameDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 141, 16));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditRemark = new QLineEdit(SelectResultLotFrameDialog);
        EditRemark->setObjectName("EditRemark");
        EditRemark->setGeometry(QRect(340, 30, 201, 21));
        label_3 = new QLabel(SelectResultLotFrameDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(340, 10, 201, 16));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(SelectResultLotFrameDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 60, 511, 16));
        EditName = new QLineEdit(SelectResultLotFrameDialog);
        EditName->setObjectName("EditName");
        EditName->setGeometry(QRect(160, 30, 171, 21));
        ButtonCreate = new QPushButton(SelectResultLotFrameDialog);
        ButtonCreate->setObjectName("ButtonCreate");
        ButtonCreate->setGeometry(QRect(180, 130, 161, 31));
        ButtonCancel = new QPushButton(SelectResultLotFrameDialog);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(440, 130, 111, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon);
        toolBox = new QToolBox(SelectResultLotFrameDialog);
        toolBox->setObjectName("toolBox");
        toolBox->setGeometry(QRect(10, 180, 551, 371));
        page = new QWidget();
        page->setObjectName("page");
        page->setGeometry(QRect(0, 0, 551, 301));
        tableWidgetGroup = new QTableWidget(page);
        if (tableWidgetGroup->columnCount() < 2)
            tableWidgetGroup->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetGroup->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetGroup->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetGroup->setObjectName("tableWidgetGroup");
        tableWidgetGroup->setGeometry(QRect(10, 0, 531, 301));
        toolBox->addItem(page, QString::fromUtf8("Group definition"));
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        page_2->setGeometry(QRect(0, 0, 551, 301));
        tableWidgetLot = new QTableWidget(page_2);
        if (tableWidgetLot->columnCount() < 4)
            tableWidgetLot->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLot->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLot->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetLot->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetLot->setHorizontalHeaderItem(3, __qtablewidgetitem5);
        tableWidgetLot->setObjectName("tableWidgetLot");
        tableWidgetLot->setGeometry(QRect(0, 0, 541, 281));
        tableWidgetLot->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLot->setSelectionBehavior(QAbstractItemView::SelectRows);
        toolBox->addItem(page_2, QString::fromUtf8("History"));
        label_5 = new QLabel(SelectResultLotFrameDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 82, 511, 21));
        label_6 = new QLabel(SelectResultLotFrameDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 105, 511, 21));

        retranslateUi(SelectResultLotFrameDialog);

        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SelectResultLotFrameDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectResultLotFrameDialog)
    {
        SelectResultLotFrameDialog->setWindowTitle(QCoreApplication::translate("SelectResultLotFrameDialog", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("SelectResultLotFrameDialog", "Name", nullptr));
        label->setText(QCoreApplication::translate("SelectResultLotFrameDialog", "ID", nullptr));
        label_3->setText(QCoreApplication::translate("SelectResultLotFrameDialog", "Remark", nullptr));
        label_4->setText(QCoreApplication::translate("SelectResultLotFrameDialog", "ID\343\201\257\344\275\225\343\202\202\345\205\245\343\202\214\343\201\252\343\201\221\343\202\214\343\201\260\346\227\245\346\231\202\343\201\214\350\207\252\345\213\225\347\232\204\343\201\253\345\205\245\343\202\213", nullptr));
        ButtonCreate->setText(QCoreApplication::translate("SelectResultLotFrameDialog", "Create new", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SelectResultLotFrameDialog", "Cancel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetGroup->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectResultLotFrameDialog", "Group Number", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetGroup->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectResultLotFrameDialog", "Group Lot name", nullptr));
        toolBox->setItemText(toolBox->indexOf(page), QCoreApplication::translate("SelectResultLotFrameDialog", "Group definition", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLot->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectResultLotFrameDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLot->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectResultLotFrameDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetLot->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SelectResultLotFrameDialog", "Day Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetLot->horizontalHeaderItem(3);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SelectResultLotFrameDialog", "Remark", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_2), QCoreApplication::translate("SelectResultLotFrameDialog", "History", nullptr));
        label_5->setText(QCoreApplication::translate("SelectResultLotFrameDialog", "[G] : Group number ", nullptr));
        label_6->setText(QCoreApplication::translate("SelectResultLotFrameDialog", "[F] : Frame number ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectResultLotFrameDialog: public Ui_SelectResultLotFrameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTRESULTLOTFRAMEDIALOG_H
