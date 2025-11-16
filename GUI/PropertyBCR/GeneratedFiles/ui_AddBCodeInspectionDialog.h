/********************************************************************************
** Form generated from reading UI file 'AddBCodeInspectionDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDBCODEINSPECTIONDIALOG_H
#define UI_ADDBCODEINSPECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddBCodeInspectionDialog
{
public:
    QDoubleSpinBox *doubleSpinBoxQuilityGrade;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonSet;
    QLabel *label;
    QComboBox *comboBoxCheckType;
    QStackedWidget *stackedWidget;
    QWidget *Read;
    QTableWidget *tableWidgetBarcodeType;
    QLabel *label_4;
    QTableWidget *tableWidgetBarcodeOrientation;
    QLabel *label_5;
    QCheckBox *checkBoxBarcodeIsOnlyDigit;
    QWidget *Quality;
    QPushButton *pushButtonSub;
    QPushButton *pushButtonSave;
    QLabel *label_2;
    QPushButton *pushButtonAdd;
    QTableWidget *tableWidgetGradeList;
    QPushButton *pushButtonLoad;
    QLabel *label_3;

    void setupUi(QDialog *AddBCodeInspectionDialog)
    {
        if (AddBCodeInspectionDialog->objectName().isEmpty())
            AddBCodeInspectionDialog->setObjectName("AddBCodeInspectionDialog");
        AddBCodeInspectionDialog->resize(493, 278);
        doubleSpinBoxQuilityGrade = new QDoubleSpinBox(AddBCodeInspectionDialog);
        doubleSpinBoxQuilityGrade->setObjectName("doubleSpinBoxQuilityGrade");
        doubleSpinBoxQuilityGrade->setGeometry(QRect(10, 70, 91, 31));
        doubleSpinBoxQuilityGrade->setDecimals(3);
        doubleSpinBoxQuilityGrade->setMaximum(9999.989999999999782);
        pushButtonClose = new QPushButton(AddBCodeInspectionDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(310, 230, 112, 34));
        pushButtonSet = new QPushButton(AddBCodeInspectionDialog);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(50, 230, 112, 34));
        label = new QLabel(AddBCodeInspectionDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 50, 101, 18));
        comboBoxCheckType = new QComboBox(AddBCodeInspectionDialog);
        comboBoxCheckType->addItem(QString());
        comboBoxCheckType->addItem(QString());
        comboBoxCheckType->addItem(QString());
        comboBoxCheckType->setObjectName("comboBoxCheckType");
        comboBoxCheckType->setGeometry(QRect(10, 10, 131, 24));
        stackedWidget = new QStackedWidget(AddBCodeInspectionDialog);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(150, 0, 341, 211));
        Read = new QWidget();
        Read->setObjectName("Read");
        tableWidgetBarcodeType = new QTableWidget(Read);
        if (tableWidgetBarcodeType->columnCount() < 1)
            tableWidgetBarcodeType->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetBarcodeType->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidgetBarcodeType->setObjectName("tableWidgetBarcodeType");
        tableWidgetBarcodeType->setGeometry(QRect(0, 30, 181, 181));
        tableWidgetBarcodeType->horizontalHeader()->setVisible(false);
        label_4 = new QLabel(Read);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 0, 181, 30));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        tableWidgetBarcodeOrientation = new QTableWidget(Read);
        if (tableWidgetBarcodeOrientation->columnCount() < 1)
            tableWidgetBarcodeOrientation->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetBarcodeOrientation->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        tableWidgetBarcodeOrientation->setObjectName("tableWidgetBarcodeOrientation");
        tableWidgetBarcodeOrientation->setGeometry(QRect(190, 20, 141, 131));
        tableWidgetBarcodeOrientation->horizontalHeader()->setVisible(false);
        label_5 = new QLabel(Read);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(190, 0, 141, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        checkBoxBarcodeIsOnlyDigit = new QCheckBox(Read);
        checkBoxBarcodeIsOnlyDigit->setObjectName("checkBoxBarcodeIsOnlyDigit");
        checkBoxBarcodeIsOnlyDigit->setGeometry(QRect(190, 160, 141, 18));
        stackedWidget->addWidget(Read);
        Quality = new QWidget();
        Quality->setObjectName("Quality");
        pushButtonSub = new QPushButton(Quality);
        pushButtonSub->setObjectName("pushButtonSub");
        pushButtonSub->setGeometry(QRect(290, 150, 41, 34));
        pushButtonSave = new QPushButton(Quality);
        pushButtonSave->setObjectName("pushButtonSave");
        pushButtonSave->setGeometry(QRect(240, 110, 91, 34));
        label_2 = new QLabel(Quality);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 231, 29));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        pushButtonAdd = new QPushButton(Quality);
        pushButtonAdd->setObjectName("pushButtonAdd");
        pushButtonAdd->setGeometry(QRect(240, 150, 41, 34));
        tableWidgetGradeList = new QTableWidget(Quality);
        if (tableWidgetGradeList->columnCount() < 2)
            tableWidgetGradeList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetGradeList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetGradeList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetGradeList->setObjectName("tableWidgetGradeList");
        tableWidgetGradeList->setGeometry(QRect(0, 30, 231, 171));
        pushButtonLoad = new QPushButton(Quality);
        pushButtonLoad->setObjectName("pushButtonLoad");
        pushButtonLoad->setGeometry(QRect(240, 70, 91, 34));
        label_3 = new QLabel(Quality);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(240, 30, 91, 29));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(Quality);

        retranslateUi(AddBCodeInspectionDialog);

        pushButtonSet->setDefault(true);
        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AddBCodeInspectionDialog);
    } // setupUi

    void retranslateUi(QDialog *AddBCodeInspectionDialog)
    {
        AddBCodeInspectionDialog->setWindowTitle(QCoreApplication::translate("AddBCodeInspectionDialog", "Dialog", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("AddBCodeInspectionDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("AddBCodeInspectionDialog", "\350\250\255\345\256\232", nullptr));
        label->setText(QCoreApplication::translate("AddBCodeInspectionDialog", "\345\223\201\350\263\252\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        comboBoxCheckType->setItemText(0, QCoreApplication::translate("AddBCodeInspectionDialog", "\350\252\255\343\201\277\345\217\226\343\202\212 2D", nullptr));
        comboBoxCheckType->setItemText(1, QCoreApplication::translate("AddBCodeInspectionDialog", "\345\223\201\350\263\252\343\203\201\343\202\247\343\203\203\343\202\257", nullptr));
        comboBoxCheckType->setItemText(2, QCoreApplication::translate("AddBCodeInspectionDialog", "\350\252\255\343\201\277\345\217\226\343\202\212 1D", nullptr));

        QTableWidgetItem *___qtablewidgetitem = tableWidgetBarcodeType->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AddBCodeInspectionDialog", "Code", nullptr));
        label_4->setText(QCoreApplication::translate("AddBCodeInspectionDialog", "\350\252\255\345\217\226\343\202\263\343\203\274\343\203\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetBarcodeOrientation->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AddBCodeInspectionDialog", "Code", nullptr));
        label_5->setText(QCoreApplication::translate("AddBCodeInspectionDialog", "\343\203\220\343\203\274\343\202\263\343\203\274\343\203\211\346\226\271\345\220\221", nullptr));
        checkBoxBarcodeIsOnlyDigit->setText(QCoreApplication::translate("AddBCodeInspectionDialog", "\346\225\260\345\200\244\343\201\256\343\201\277", nullptr));
        pushButtonSub->setText(QCoreApplication::translate("AddBCodeInspectionDialog", "-", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("AddBCodeInspectionDialog", "Save", nullptr));
        label_2->setText(QCoreApplication::translate("AddBCodeInspectionDialog", "\345\223\201\350\263\252\345\211\262\345\275\223\350\241\250", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("AddBCodeInspectionDialog", "+", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetGradeList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("AddBCodeInspectionDialog", "Grade", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetGradeList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("AddBCodeInspectionDialog", "\346\234\200\344\275\216\345\223\201\350\263\252\345\200\244", nullptr));
        pushButtonLoad->setText(QCoreApplication::translate("AddBCodeInspectionDialog", "Load", nullptr));
        label_3->setText(QCoreApplication::translate("AddBCodeInspectionDialog", "\345\217\202\350\200\203\343\203\207\343\203\274\343\202\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddBCodeInspectionDialog: public Ui_AddBCodeInspectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDBCODEINSPECTIONDIALOG_H
