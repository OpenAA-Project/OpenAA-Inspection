/********************************************************************************
** Form generated from reading UI file 'MoveXYDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOVEXYDIALOG_H
#define UI_MOVEXYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MoveXYDialog
{
public:
    QLabel *label;
    QTableWidget *tableWidgetValues;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonSet;

    void setupUi(QWidget *MoveXYDialog)
    {
        if (MoveXYDialog->objectName().isEmpty())
            MoveXYDialog->setObjectName("MoveXYDialog");
        MoveXYDialog->resize(201, 262);
        label = new QLabel(MoveXYDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 201, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        tableWidgetValues = new QTableWidget(MoveXYDialog);
        if (tableWidgetValues->columnCount() < 3)
            tableWidgetValues->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetValues->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetValues->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetValues->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetValues->setObjectName("tableWidgetValues");
        tableWidgetValues->setGeometry(QRect(10, 30, 181, 121));
        pushButtonOK = new QPushButton(MoveXYDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 220, 75, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(MoveXYDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 220, 75, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        pushButtonSet = new QPushButton(MoveXYDialog);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(60, 162, 75, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSet->setIcon(icon2);

        retranslateUi(MoveXYDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(MoveXYDialog);
    } // setupUi

    void retranslateUi(QWidget *MoveXYDialog)
    {
        MoveXYDialog->setWindowTitle(QCoreApplication::translate("MoveXYDialog", "Move XY", nullptr));
        label->setText(QCoreApplication::translate("MoveXYDialog", "Shift value", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetValues->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MoveXYDialog", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetValues->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MoveXYDialog", "ShiftX", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetValues->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MoveXYDialog", "ShiftY", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("MoveXYDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("MoveXYDialog", "Cancel", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("MoveXYDialog", "Set", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MoveXYDialog: public Ui_MoveXYDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOVEXYDIALOG_H
