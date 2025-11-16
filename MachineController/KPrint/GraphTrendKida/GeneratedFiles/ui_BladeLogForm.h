/********************************************************************************
** Form generated from reading UI file 'BladeLogForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLADELOGFORM_H
#define UI_BLADELOGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BladeLogForm
{
public:
    QTableWidget *tableWidget;
    QFrame *frame;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonExcel;

    void setupUi(QWidget *BladeLogForm)
    {
        if (BladeLogForm->objectName().isEmpty())
            BladeLogForm->setObjectName("BladeLogForm");
        BladeLogForm->resize(740, 569);
        tableWidget = new QTableWidget(BladeLogForm);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 741, 501));
        frame = new QFrame(BladeLogForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 500, 741, 71));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonClose = new QPushButton(frame);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(540, 10, 191, 51));
        pushButtonExcel = new QPushButton(frame);
        pushButtonExcel->setObjectName("pushButtonExcel");
        pushButtonExcel->setGeometry(QRect(10, 10, 191, 51));

        retranslateUi(BladeLogForm);

        QMetaObject::connectSlotsByName(BladeLogForm);
    } // setupUi

    void retranslateUi(QWidget *BladeLogForm)
    {
        BladeLogForm->setWindowTitle(QCoreApplication::translate("BladeLogForm", "\350\250\210\346\270\254\343\203\255\343\202\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("BladeLogForm", "\346\231\202\345\210\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("BladeLogForm", "\350\250\210\346\270\2541", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("BladeLogForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        pushButtonExcel->setText(QCoreApplication::translate("BladeLogForm", "EXCEL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BladeLogForm: public Ui_BladeLogForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLADELOGFORM_H
