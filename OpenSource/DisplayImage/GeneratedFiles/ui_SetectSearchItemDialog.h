/********************************************************************************
** Form generated from reading UI file 'SetectSearchItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETECTSEARCHITEMDIALOG_H
#define UI_SETECTSEARCHITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SetectSearchItemDialog
{
public:
    QPushButton *ButtonSelectAndView;
    QTableWidget *tableWidgetItems;
    QFrame *frame;
    QLineEdit *lineEditTopName;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxTopID;
    QPushButton *pushButtonSortByID;
    QPushButton *pushButtonSortByName;
    QPushButton *pushButtonSortByLibID;
    QPushButton *ButtonOnlyView;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SetectSearchItemDialog)
    {
        if (SetectSearchItemDialog->objectName().isEmpty())
            SetectSearchItemDialog->setObjectName("SetectSearchItemDialog");
        SetectSearchItemDialog->resize(740, 557);
        ButtonSelectAndView = new QPushButton(SetectSearchItemDialog);
        ButtonSelectAndView->setObjectName("ButtonSelectAndView");
        ButtonSelectAndView->setGeometry(QRect(30, 500, 171, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonSelectAndView->setIcon(icon);
        tableWidgetItems = new QTableWidget(SetectSearchItemDialog);
        if (tableWidgetItems->columnCount() < 6)
            tableWidgetItems->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidgetItems->setObjectName("tableWidgetItems");
        tableWidgetItems->setGeometry(QRect(10, 110, 721, 381));
        tableWidgetItems->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetItems->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(SetectSearchItemDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 0, 581, 101));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        lineEditTopName = new QLineEdit(frame);
        lineEditTopName->setObjectName("lineEditTopName");
        lineEditTopName->setGeometry(QRect(390, 30, 161, 21));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(390, 10, 161, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 10, 91, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        spinBoxTopID = new QSpinBox(frame);
        spinBoxTopID->setObjectName("spinBoxTopID");
        spinBoxTopID->setGeometry(QRect(20, 30, 91, 22));
        spinBoxTopID->setMaximum(999999999);
        pushButtonSortByID = new QPushButton(frame);
        pushButtonSortByID->setObjectName("pushButtonSortByID");
        pushButtonSortByID->setGeometry(QRect(190, 60, 161, 28));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/SortNumber.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSortByID->setIcon(icon1);
        pushButtonSortByName = new QPushButton(frame);
        pushButtonSortByName->setObjectName("pushButtonSortByName");
        pushButtonSortByName->setGeometry(QRect(390, 60, 161, 28));
        pushButtonSortByName->setIcon(icon1);
        pushButtonSortByLibID = new QPushButton(frame);
        pushButtonSortByLibID->setObjectName("pushButtonSortByLibID");
        pushButtonSortByLibID->setGeometry(QRect(20, 60, 161, 28));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/SortText.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSortByLibID->setIcon(icon2);
        ButtonOnlyView = new QPushButton(SetectSearchItemDialog);
        ButtonOnlyView->setObjectName("ButtonOnlyView");
        ButtonOnlyView->setGeometry(QRect(260, 500, 171, 41));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Display.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOnlyView->setIcon(icon3);
        pushButtonCancel = new QPushButton(SetectSearchItemDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(560, 500, 161, 41));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon4);

        retranslateUi(SetectSearchItemDialog);

        ButtonSelectAndView->setDefault(true);


        QMetaObject::connectSlotsByName(SetectSearchItemDialog);
    } // setupUi

    void retranslateUi(QDialog *SetectSearchItemDialog)
    {
        SetectSearchItemDialog->setWindowTitle(QCoreApplication::translate("SetectSearchItemDialog", "Select/View item", nullptr));
        ButtonSelectAndView->setText(QCoreApplication::translate("SetectSearchItemDialog", "Select and view", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetItems->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SetectSearchItemDialog", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetItems->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SetectSearchItemDialog", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetItems->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SetectSearchItemDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetItems->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SetectSearchItemDialog", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetItems->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SetectSearchItemDialog", "Library", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetItems->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SetectSearchItemDialog", "Name", nullptr));
        label->setText(QCoreApplication::translate("SetectSearchItemDialog", "By name", nullptr));
        label_2->setText(QCoreApplication::translate("SetectSearchItemDialog", "By ID", nullptr));
        pushButtonSortByID->setText(QCoreApplication::translate("SetectSearchItemDialog", "Sort and top", nullptr));
        pushButtonSortByName->setText(QCoreApplication::translate("SetectSearchItemDialog", "Sort and top", nullptr));
        pushButtonSortByLibID->setText(QCoreApplication::translate("SetectSearchItemDialog", "Sort by LibID", nullptr));
        ButtonOnlyView->setText(QCoreApplication::translate("SetectSearchItemDialog", "Only view", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SetectSearchItemDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetectSearchItemDialog: public Ui_SetectSearchItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETECTSEARCHITEMDIALOG_H
