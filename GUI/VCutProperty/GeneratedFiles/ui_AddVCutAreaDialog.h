/********************************************************************************
** Form generated from reading UI file 'AddVCutAreaDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDVCUTAREADIALOG_H
#define UI_ADDVCUTAREADIALOG_H

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

class Ui_AddVCutAreaDialogClass
{
public:
    QFrame *frame;
    QLineEdit *EditLibName;
    QLabel *label_12;
    QSpinBox *EditThresholdLength;
    QLabel *label_10;
    QLabel *label_4;
    QLineEdit *EditLibID;
    QLabel *label_11;
    QSpinBox *EditThresholdShift;
    QDoubleSpinBox *EditThresholdLevel;
    QFrame *frameLibFolder;
    QTableWidget *tableWidgetLibList;
    QPushButton *pushButtonGenerateLib;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *AddVCutAreaDialogClass)
    {
        if (AddVCutAreaDialogClass->objectName().isEmpty())
            AddVCutAreaDialogClass->setObjectName("AddVCutAreaDialogClass");
        AddVCutAreaDialogClass->resize(399, 370);
        frame = new QFrame(AddVCutAreaDialogClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 180, 381, 121));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        EditLibName = new QLineEdit(frame);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 10, 211, 31));
        QFont font;
        font.setPointSize(12);
        EditLibName->setFont(font);
        label_12 = new QLabel(frame);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 90, 251, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditThresholdLength = new QSpinBox(frame);
        EditThresholdLength->setObjectName("EditThresholdLength");
        EditThresholdLength->setGeometry(QRect(270, 90, 81, 22));
        EditThresholdLength->setMaximum(1000000);
        label_10 = new QLabel(frame);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 50, 251, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 10, 51, 31));
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(frame);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 10, 81, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        label_11 = new QLabel(frame);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 70, 251, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditThresholdShift = new QSpinBox(frame);
        EditThresholdShift->setObjectName("EditThresholdShift");
        EditThresholdShift->setGeometry(QRect(270, 70, 81, 22));
        EditThresholdShift->setMaximum(1000000);
        EditThresholdLevel = new QDoubleSpinBox(frame);
        EditThresholdLevel->setObjectName("EditThresholdLevel");
        EditThresholdLevel->setGeometry(QRect(270, 50, 101, 24));
        EditThresholdLevel->setDecimals(3);
        EditThresholdLevel->setMaximum(99999999.000000000000000);
        frameLibFolder = new QFrame(AddVCutAreaDialogClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 161));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        tableWidgetLibList = new QTableWidget(AddVCutAreaDialogClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 20, 181, 151));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonGenerateLib = new QPushButton(AddVCutAreaDialogClass);
        pushButtonGenerateLib->setObjectName("pushButtonGenerateLib");
        pushButtonGenerateLib->setGeometry(QRect(10, 310, 171, 51));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cut.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonGenerateLib->setIcon(icon);
        pushButtonCancel = new QPushButton(AddVCutAreaDialogClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(220, 310, 171, 51));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(AddVCutAreaDialogClass);

        QMetaObject::connectSlotsByName(AddVCutAreaDialogClass);
    } // setupUi

    void retranslateUi(QDialog *AddVCutAreaDialogClass)
    {
        AddVCutAreaDialogClass->setWindowTitle(QCoreApplication::translate("AddVCutAreaDialogClass", "AddVCutAreaDialog", nullptr));
        EditLibName->setText(QCoreApplication::translate("AddVCutAreaDialogClass", "Library Name", nullptr));
        label_12->setText(QCoreApplication::translate("AddVCutAreaDialogClass", "V\343\202\253\343\203\203\343\203\210\347\204\241\343\201\227\343\201\256\350\250\261\345\256\271\351\225\267\343\201\225", nullptr));
        label_10->setText(QCoreApplication::translate("AddVCutAreaDialogClass", "\346\212\275\345\207\272\343\203\254\343\203\231\343\203\253", nullptr));
        label_4->setText(QCoreApplication::translate("AddVCutAreaDialogClass", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("AddVCutAreaDialogClass", "12345", nullptr));
        label_11->setText(QCoreApplication::translate("AddVCutAreaDialogClass", "\344\275\215\347\275\256\343\201\232\343\202\214\350\250\261\345\256\271\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AddVCutAreaDialogClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AddVCutAreaDialogClass", "Name", nullptr));
        pushButtonGenerateLib->setText(QCoreApplication::translate("AddVCutAreaDialogClass", "V\343\202\253\343\203\203\343\203\210\343\202\250\343\203\252\343\202\242\343\202\222\344\275\234\346\210\220", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AddVCutAreaDialogClass", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddVCutAreaDialogClass: public Ui_AddVCutAreaDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDVCUTAREADIALOG_H
