/********************************************************************************
** Form generated from reading UI file 'ShareMasterDataForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHAREMASTERDATAFORM_H
#define UI_SHAREMASTERDATAFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShareMasterDataForm
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonOK;
    QComboBox *comboBoxMachineID;
    QLabel *label;
    QPushButton *pushButtonAddDestination;
    QPushButton *pushButtonDelDestination;

    void setupUi(QWidget *ShareMasterDataForm)
    {
        if (ShareMasterDataForm->objectName().isEmpty())
            ShareMasterDataForm->setObjectName("ShareMasterDataForm");
        ShareMasterDataForm->resize(423, 341);
        tableWidget = new QTableWidget(ShareMasterDataForm);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 40, 421, 261));
        pushButtonOK = new QPushButton(ShareMasterDataForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(160, 310, 81, 23));
        comboBoxMachineID = new QComboBox(ShareMasterDataForm);
        comboBoxMachineID->setObjectName("comboBoxMachineID");
        comboBoxMachineID->setGeometry(QRect(75, 10, 71, 22));
        label = new QLabel(ShareMasterDataForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 51, 21));
        pushButtonAddDestination = new QPushButton(ShareMasterDataForm);
        pushButtonAddDestination->setObjectName("pushButtonAddDestination");
        pushButtonAddDestination->setGeometry(QRect(160, 10, 75, 23));
        pushButtonDelDestination = new QPushButton(ShareMasterDataForm);
        pushButtonDelDestination->setObjectName("pushButtonDelDestination");
        pushButtonDelDestination->setGeometry(QRect(240, 10, 75, 23));

        retranslateUi(ShareMasterDataForm);

        QMetaObject::connectSlotsByName(ShareMasterDataForm);
    } // setupUi

    void retranslateUi(QWidget *ShareMasterDataForm)
    {
        ShareMasterDataForm->setWindowTitle(QCoreApplication::translate("ShareMasterDataForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShareMasterDataForm", "Source", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShareMasterDataForm", "Dx", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShareMasterDataForm", "Dy", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShareMasterDataForm", "MulColor", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("ShareMasterDataForm", "OK", nullptr));
        label->setText(QCoreApplication::translate("ShareMasterDataForm", "MachineID", nullptr));
        pushButtonAddDestination->setText(QCoreApplication::translate("ShareMasterDataForm", "Add", nullptr));
        pushButtonDelDestination->setText(QCoreApplication::translate("ShareMasterDataForm", "Del", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShareMasterDataForm: public Ui_ShareMasterDataForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHAREMASTERDATAFORM_H
