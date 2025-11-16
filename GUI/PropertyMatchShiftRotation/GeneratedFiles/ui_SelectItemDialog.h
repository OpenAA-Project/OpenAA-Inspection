/********************************************************************************
** Form generated from reading UI file 'SelectItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTITEMDIALOG_H
#define UI_SELECTITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectItemDialog
{
public:
    QLineEdit *EditItemName;
    QLineEdit *EditLibID;
    QPushButton *ButtonCancel;
    QLabel *label_9;
    QFrame *frameGenLayer;
    QLineEdit *EditLibName;
    QPushButton *ButtonOK;
    QLabel *label;
    QFrame *frameLibFolder;
    QTableWidget *tableWidgetLibList;
    QFrame *frame_26;
    QLabel *label_87;
    QLabel *label_3;
    QSpinBox *spinBoxSearchLittleInItem;
    QLabel *label_21;
    QDoubleSpinBox *doubleSpinBox;
    QPushButton *ButtonDelete;

    void setupUi(QDialog *SelectItemDialog)
    {
        if (SelectItemDialog->objectName().isEmpty())
            SelectItemDialog->setObjectName("SelectItemDialog");
        SelectItemDialog->resize(425, 420);
        EditItemName = new QLineEdit(SelectItemDialog);
        EditItemName->setObjectName("EditItemName");
        EditItemName->setGeometry(QRect(90, 160, 321, 21));
        EditItemName->setReadOnly(false);
        EditLibID = new QLineEdit(SelectItemDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(40, 190, 51, 21));
        EditLibID->setReadOnly(true);
        ButtonCancel = new QPushButton(SelectItemDialog);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(310, 370, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon);
        label_9 = new QLabel(SelectItemDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(30, 230, 381, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignCenter);
        frameGenLayer = new QFrame(SelectItemDialog);
        frameGenLayer->setObjectName("frameGenLayer");
        frameGenLayer->setGeometry(QRect(30, 250, 381, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);
        EditLibName = new QLineEdit(SelectItemDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(90, 190, 321, 21));
        EditLibName->setReadOnly(true);
        ButtonOK = new QPushButton(SelectItemDialog);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(160, 370, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon1);
        label = new QLabel(SelectItemDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 160, 81, 21));
        frameLibFolder = new QFrame(SelectItemDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        tableWidgetLibList = new QTableWidget(SelectItemDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 201, 141));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame_26 = new QFrame(SelectItemDialog);
        frame_26->setObjectName("frame_26");
        frame_26->setGeometry(QRect(30, 280, 381, 71));
        frame_26->setFrameShape(QFrame::StyledPanel);
        frame_26->setFrameShadow(QFrame::Sunken);
        label_87 = new QLabel(frame_26);
        label_87->setObjectName("label_87");
        label_87->setGeometry(QRect(0, 0, 31, 71));
        label_87->setFrameShape(QFrame::Panel);
        label_87->setFrameShadow(QFrame::Raised);
        label_87->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_87->setIndent(1);
        label_3 = new QLabel(frame_26);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 10, 241, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        spinBoxSearchLittleInItem = new QSpinBox(frame_26);
        spinBoxSearchLittleInItem->setObjectName("spinBoxSearchLittleInItem");
        spinBoxSearchLittleInItem->setGeometry(QRect(290, 10, 81, 22));
        spinBoxSearchLittleInItem->setMaximum(999999);
        label_21 = new QLabel(frame_26);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(40, 40, 241, 21));
        label_21->setFrameShape(QFrame::Panel);
        label_21->setFrameShadow(QFrame::Sunken);
        label_21->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBox = new QDoubleSpinBox(frame_26);
        doubleSpinBox->setObjectName("doubleSpinBox");
        doubleSpinBox->setGeometry(QRect(290, 40, 81, 24));
        doubleSpinBox->setMinimum(-1.000000000000000);
        doubleSpinBox->setMaximum(1.000000000000000);
        ButtonDelete = new QPushButton(SelectItemDialog);
        ButtonDelete->setObjectName("ButtonDelete");
        ButtonDelete->setGeometry(QRect(30, 370, 101, 31));
        ButtonDelete->setIcon(icon1);
        ButtonDelete->setAutoDefault(false);

        retranslateUi(SelectItemDialog);

        ButtonOK->setDefault(true);
        ButtonDelete->setDefault(false);


        QMetaObject::connectSlotsByName(SelectItemDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectItemDialog)
    {
        SelectItemDialog->setWindowTitle(QCoreApplication::translate("SelectItemDialog", "Dialog", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SelectItemDialog", "Cancel", nullptr));
        label_9->setText(QCoreApplication::translate("SelectItemDialog", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        ButtonOK->setText(QCoreApplication::translate("SelectItemDialog", "OK", nullptr));
        label->setText(QCoreApplication::translate("SelectItemDialog", "Item name", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectItemDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectItemDialog", "Name", nullptr));
        label_87->setText(QCoreApplication::translate("SelectItemDialog", "<html><head/><body><p>\345\256\237</p><p>\350\241\214</p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("SelectItemDialog", "\345\276\256\345\260\217\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\343\200\200\302\261", nullptr));
        label_21->setText(QCoreApplication::translate("SelectItemDialog", "\345\210\244\345\256\232\343\200\200\344\270\200\350\207\264\347\216\207", nullptr));
        ButtonDelete->setText(QCoreApplication::translate("SelectItemDialog", "\345\211\212\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectItemDialog: public Ui_SelectItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTITEMDIALOG_H
