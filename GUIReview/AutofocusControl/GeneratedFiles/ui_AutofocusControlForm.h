/********************************************************************************
** Form generated from reading UI file 'AutofocusControlForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOFOCUSCONTROLFORM_H
#define UI_AUTOFOCUSCONTROLFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_AutofocusControlForm
{
public:
    QTableWidget *tableWidget9Pos;
    QPushButton *pushButton8Points;
    QPushButton *pushButtonMeasureNow;
    QLineEdit *lineEditCurrentZ;
    QLineEdit *lineEditBaseAverageZ;
    QLineEdit *lineEditDepth;
    QLabel *label;
    QLineEdit *lineEditMicroscopeZ;
    QPushButton *pushButtonAutofocusNow;
    QPushButton *pushButtonAuto;
    QLabel *label_2;
    QLineEdit *lineEditDepthu;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_6;
    QToolButton *toolButtonGoMicroscope;

    void setupUi(GUIFormBase *AutofocusControlForm)
    {
        if (AutofocusControlForm->objectName().isEmpty())
            AutofocusControlForm->setObjectName(QString::fromUtf8("AutofocusControlForm"));
        AutofocusControlForm->resize(417, 279);
        tableWidget9Pos = new QTableWidget(AutofocusControlForm);
        if (tableWidget9Pos->columnCount() < 3)
            tableWidget9Pos->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget9Pos->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget9Pos->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget9Pos->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget9Pos->rowCount() < 8)
            tableWidget9Pos->setRowCount(8);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget9Pos->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget9Pos->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget9Pos->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget9Pos->setVerticalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget9Pos->setVerticalHeaderItem(4, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget9Pos->setVerticalHeaderItem(5, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget9Pos->setVerticalHeaderItem(6, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget9Pos->setVerticalHeaderItem(7, __qtablewidgetitem10);
        tableWidget9Pos->setObjectName(QString::fromUtf8("tableWidget9Pos"));
        tableWidget9Pos->setGeometry(QRect(0, 0, 191, 281));
        pushButton8Points = new QPushButton(AutofocusControlForm);
        pushButton8Points->setObjectName(QString::fromUtf8("pushButton8Points"));
        pushButton8Points->setGeometry(QRect(200, 160, 101, 41));
        pushButtonMeasureNow = new QPushButton(AutofocusControlForm);
        pushButtonMeasureNow->setObjectName(QString::fromUtf8("pushButtonMeasureNow"));
        pushButtonMeasureNow->setGeometry(QRect(200, 110, 101, 41));
        lineEditCurrentZ = new QLineEdit(AutofocusControlForm);
        lineEditCurrentZ->setObjectName(QString::fromUtf8("lineEditCurrentZ"));
        lineEditCurrentZ->setGeometry(QRect(310, 110, 61, 21));
        lineEditCurrentZ->setReadOnly(true);
        lineEditBaseAverageZ = new QLineEdit(AutofocusControlForm);
        lineEditBaseAverageZ->setObjectName(QString::fromUtf8("lineEditBaseAverageZ"));
        lineEditBaseAverageZ->setGeometry(QRect(310, 160, 61, 21));
        lineEditBaseAverageZ->setReadOnly(true);
        lineEditDepth = new QLineEdit(AutofocusControlForm);
        lineEditDepth->setObjectName(QString::fromUtf8("lineEditDepth"));
        lineEditDepth->setGeometry(QRect(310, 230, 61, 20));
        lineEditDepth->setReadOnly(true);
        label = new QLabel(AutofocusControlForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(320, 210, 61, 21));
        lineEditMicroscopeZ = new QLineEdit(AutofocusControlForm);
        lineEditMicroscopeZ->setObjectName(QString::fromUtf8("lineEditMicroscopeZ"));
        lineEditMicroscopeZ->setGeometry(QRect(310, 20, 61, 21));
        lineEditMicroscopeZ->setReadOnly(true);
        pushButtonAutofocusNow = new QPushButton(AutofocusControlForm);
        pushButtonAutofocusNow->setObjectName(QString::fromUtf8("pushButtonAutofocusNow"));
        pushButtonAutofocusNow->setGeometry(QRect(200, 60, 101, 41));
        pushButtonAuto = new QPushButton(AutofocusControlForm);
        pushButtonAuto->setObjectName(QString::fromUtf8("pushButtonAuto"));
        pushButtonAuto->setGeometry(QRect(200, 210, 101, 61));
        label_2 = new QLabel(AutofocusControlForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(380, 20, 31, 20));
        lineEditDepthu = new QLineEdit(AutofocusControlForm);
        lineEditDepthu->setObjectName(QString::fromUtf8("lineEditDepthu"));
        lineEditDepthu->setGeometry(QRect(310, 250, 71, 20));
        lineEditDepthu->setReadOnly(true);
        label_5 = new QLabel(AutofocusControlForm);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(390, 250, 21, 16));
        label_3 = new QLabel(AutofocusControlForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(380, 110, 31, 20));
        label_4 = new QLabel(AutofocusControlForm);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(380, 160, 31, 20));
        label_6 = new QLabel(AutofocusControlForm);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(380, 230, 31, 20));
        toolButtonGoMicroscope = new QToolButton(AutofocusControlForm);
        toolButtonGoMicroscope->setObjectName(QString::fromUtf8("toolButtonGoMicroscope"));
        toolButtonGoMicroscope->setGeometry(QRect(200, 10, 101, 41));
        toolButtonGoMicroscope->setCheckable(true);
        toolButtonGoMicroscope->setChecked(false);

        retranslateUi(AutofocusControlForm);

        QMetaObject::connectSlotsByName(AutofocusControlForm);
    } // setupUi

    void retranslateUi(GUIFormBase *AutofocusControlForm)
    {
        AutofocusControlForm->setWindowTitle(QCoreApplication::translate("AutofocusControlForm", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget9Pos->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AutofocusControlForm", "dX", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget9Pos->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AutofocusControlForm", "dY", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget9Pos->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("AutofocusControlForm", "Z", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget9Pos->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("AutofocusControlForm", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget9Pos->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("AutofocusControlForm", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget9Pos->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("AutofocusControlForm", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget9Pos->verticalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("AutofocusControlForm", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget9Pos->verticalHeaderItem(4);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("AutofocusControlForm", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget9Pos->verticalHeaderItem(5);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("AutofocusControlForm", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget9Pos->verticalHeaderItem(6);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("AutofocusControlForm", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget9Pos->verticalHeaderItem(7);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("AutofocusControlForm", "8", nullptr));
        pushButton8Points->setText(QCoreApplication::translate("AutofocusControlForm", "Measure 8 points", nullptr));
        pushButtonMeasureNow->setText(QCoreApplication::translate("AutofocusControlForm", "Measure Now", nullptr));
        label->setText(QCoreApplication::translate("AutofocusControlForm", "Hole depth", nullptr));
        pushButtonAutofocusNow->setText(QCoreApplication::translate("AutofocusControlForm", "Autofocus now", nullptr));
        pushButtonAuto->setText(QCoreApplication::translate("AutofocusControlForm", "Auto (From hole)", nullptr));
        label_2->setText(QCoreApplication::translate("AutofocusControlForm", "pulse", nullptr));
        label_5->setText(QCoreApplication::translate("AutofocusControlForm", "um", nullptr));
        label_3->setText(QCoreApplication::translate("AutofocusControlForm", "pulse", nullptr));
        label_4->setText(QCoreApplication::translate("AutofocusControlForm", "pulse", nullptr));
        label_6->setText(QCoreApplication::translate("AutofocusControlForm", "pulse", nullptr));
        toolButtonGoMicroscope->setText(QCoreApplication::translate("AutofocusControlForm", "Go Microscope", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutofocusControlForm: public Ui_AutofocusControlForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOFOCUSCONTROLFORM_H
