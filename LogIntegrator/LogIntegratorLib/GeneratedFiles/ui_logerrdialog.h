/********************************************************************************
** Form generated from reading UI file 'logerrdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGERRDIALOG_H
#define UI_LOGERRDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_LogErrDialogClass
{
public:
    QTableWidget *tableWidget_err;
    QPushButton *pushButton;
    QTableWidget *tableWidget_succ;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pbCancel;

    void setupUi(QDialog *LogErrDialogClass)
    {
        if (LogErrDialogClass->objectName().isEmpty())
            LogErrDialogClass->setObjectName(QString::fromUtf8("LogErrDialogClass"));
        LogErrDialogClass->setWindowModality(Qt::ApplicationModal);
        LogErrDialogClass->resize(806, 640);
        LogErrDialogClass->setModal(true);
        tableWidget_err = new QTableWidget(LogErrDialogClass);
        if (tableWidget_err->columnCount() < 7)
            tableWidget_err->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_err->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_err->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_err->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_err->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_err->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_err->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_err->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget_err->setObjectName(QString::fromUtf8("tableWidget_err"));
        tableWidget_err->setGeometry(QRect(10, 380, 781, 181));
        pushButton = new QPushButton(LogErrDialogClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(686, 582, 111, 41));
        tableWidget_succ = new QTableWidget(LogErrDialogClass);
        if (tableWidget_succ->columnCount() < 7)
            tableWidget_succ->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_succ->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_succ->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_succ->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_succ->setHorizontalHeaderItem(3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_succ->setHorizontalHeaderItem(4, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_succ->setHorizontalHeaderItem(5, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_succ->setHorizontalHeaderItem(6, __qtablewidgetitem13);
        tableWidget_succ->setObjectName(QString::fromUtf8("tableWidget_succ"));
        tableWidget_succ->setGeometry(QRect(10, 30, 781, 301));
        label = new QLabel(LogErrDialogClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 121, 16));
        label_2 = new QLabel(LogErrDialogClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 360, 121, 16));
        pbCancel = new QPushButton(LogErrDialogClass);
        pbCancel->setObjectName(QString::fromUtf8("pbCancel"));
        pbCancel->setGeometry(QRect(10, 580, 111, 41));
        QWidget::setTabOrder(pushButton, tableWidget_succ);
        QWidget::setTabOrder(tableWidget_succ, tableWidget_err);

        retranslateUi(LogErrDialogClass);

        QMetaObject::connectSlotsByName(LogErrDialogClass);
    } // setupUi

    void retranslateUi(QDialog *LogErrDialogClass)
    {
        LogErrDialogClass->setWindowTitle(QCoreApplication::translate("LogErrDialogClass", "\345\207\246\347\220\206\347\265\220\346\236\234\343\203\200\343\202\244\343\202\242\343\203\255\343\202\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_err->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("LogErrDialogClass", "\345\223\201\347\250\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_err->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("LogErrDialogClass", "\343\203\255\343\203\203\343\203\210\347\225\252\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_err->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("LogErrDialogClass", "\345\237\272\346\235\277\347\225\252\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_err->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("LogErrDialogClass", "\344\277\235\345\255\230\346\227\245\344\273\230", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_err->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("LogErrDialogClass", "\344\277\235\345\255\230\346\231\202\351\226\223", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_err->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("LogErrDialogClass", "\344\277\235\345\255\230HD\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_err->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("LogErrDialogClass", "\350\252\255\343\201\277\350\276\274\343\202\223\343\201\240\343\203\255\343\202\260\343\201\256\346\225\260", nullptr));
        pushButton->setText(QCoreApplication::translate("LogErrDialogClass", "\351\226\211\343\201\230\343\202\213(&C)", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_succ->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("LogErrDialogClass", "\345\223\201\347\250\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_succ->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("LogErrDialogClass", "\343\203\255\343\203\203\343\203\210\347\225\252\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_succ->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("LogErrDialogClass", "\345\237\272\346\235\277\347\225\252\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_succ->horizontalHeaderItem(3);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("LogErrDialogClass", "\344\277\235\345\255\230\346\227\245\344\273\230", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_succ->horizontalHeaderItem(4);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("LogErrDialogClass", "\344\277\235\345\255\230\346\231\202\345\210\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_succ->horizontalHeaderItem(5);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("LogErrDialogClass", "\344\277\235\345\255\230HD\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_succ->horizontalHeaderItem(6);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("LogErrDialogClass", "\350\252\255\343\201\277\350\276\274\343\202\223\343\201\240\343\203\255\343\202\260\343\201\256\346\225\260", nullptr));
        label->setText(QCoreApplication::translate("LogErrDialogClass", "\346\210\220\345\212\237\343\201\227\343\201\237\343\203\255\343\202\260\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("LogErrDialogClass", "\343\202\250\343\203\251\343\203\274\343\201\256\347\231\272\347\224\237\343\201\227\343\201\237\343\203\255\343\202\260\357\274\232", nullptr));
        pbCancel->setText(QCoreApplication::translate("LogErrDialogClass", "\343\201\223\343\201\223\343\201\247\345\207\246\347\220\206\343\202\222\344\270\255\346\255\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogErrDialogClass: public Ui_LogErrDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGERRDIALOG_H
