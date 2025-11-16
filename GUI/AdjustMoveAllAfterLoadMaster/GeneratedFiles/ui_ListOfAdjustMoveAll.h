/********************************************************************************
** Form generated from reading UI file 'ListOfAdjustMoveAll.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTOFADJUSTMOVEALL_H
#define UI_LISTOFADJUSTMOVEALL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ListOfAdjustMoveAll
{
public:
    QTableWidget *tableWidgetXY;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonLoad;
    QLabel *label;
    QSpinBox *spinBoxMasterCode;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *ListOfAdjustMoveAll)
    {
        if (ListOfAdjustMoveAll->objectName().isEmpty())
            ListOfAdjustMoveAll->setObjectName("ListOfAdjustMoveAll");
        ListOfAdjustMoveAll->resize(251, 326);
        tableWidgetXY = new QTableWidget(ListOfAdjustMoveAll);
        if (tableWidgetXY->columnCount() < 2)
            tableWidgetXY->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetXY->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetXY->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetXY->setObjectName("tableWidgetXY");
        tableWidgetXY->setGeometry(QRect(10, 91, 231, 141));
        pushButtonSave = new QPushButton(ListOfAdjustMoveAll);
        pushButtonSave->setObjectName("pushButtonSave");
        pushButtonSave->setGeometry(QRect(30, 240, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSave->setIcon(icon);
        pushButtonClose = new QPushButton(ListOfAdjustMoveAll);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(130, 280, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon1);
        pushButtonLoad = new QPushButton(ListOfAdjustMoveAll);
        pushButtonLoad->setObjectName("pushButtonLoad");
        pushButtonLoad->setGeometry(QRect(130, 240, 91, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Load.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonLoad->setIcon(icon2);
        label = new QLabel(ListOfAdjustMoveAll);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 61, 16));
        spinBoxMasterCode = new QSpinBox(ListOfAdjustMoveAll);
        spinBoxMasterCode->setObjectName("spinBoxMasterCode");
        spinBoxMasterCode->setGeometry(QRect(80, 10, 101, 22));
        spinBoxMasterCode->setMinimum(-1);
        spinBoxMasterCode->setMaximum(999999);
        label_2 = new QLabel(ListOfAdjustMoveAll);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 40, 191, 16));
        label_3 = new QLabel(ListOfAdjustMoveAll);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 231, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);

        retranslateUi(ListOfAdjustMoveAll);

        pushButtonClose->setDefault(true);


        QMetaObject::connectSlotsByName(ListOfAdjustMoveAll);
    } // setupUi

    void retranslateUi(QDialog *ListOfAdjustMoveAll)
    {
        ListOfAdjustMoveAll->setWindowTitle(QCoreApplication::translate("ListOfAdjustMoveAll", "List of Adjust move all", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetXY->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ListOfAdjustMoveAll", "Dx", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetXY->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ListOfAdjustMoveAll", "Dy", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("ListOfAdjustMoveAll", "Save", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ListOfAdjustMoveAll", "Close", nullptr));
        pushButtonLoad->setText(QCoreApplication::translate("ListOfAdjustMoveAll", "Load", nullptr));
        label->setText(QCoreApplication::translate("ListOfAdjustMoveAll", "MasterCode", nullptr));
        label_2->setText(QCoreApplication::translate("ListOfAdjustMoveAll", "If -1 is set, (Dx,Dy) is general shift", nullptr));
        label_3->setText(QCoreApplication::translate("ListOfAdjustMoveAll", "Shift value  (Plus is right, down)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListOfAdjustMoveAll: public Ui_ListOfAdjustMoveAll {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTOFADJUSTMOVEALL_H
