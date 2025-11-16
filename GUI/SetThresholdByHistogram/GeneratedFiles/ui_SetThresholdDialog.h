/********************************************************************************
** Form generated from reading UI file 'SetThresholdDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTHRESHOLDDIALOG_H
#define UI_SETTHRESHOLDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SetThresholdDialog
{
public:
    QCheckBox *checkBoxModeOneWork;
    QCheckBox *checkBoxModeMultiWork;
    QTableWidget *tableWidgetAlgorithm;
    QPushButton *pushButtonSet;
    QDoubleSpinBox *doubleSpinBoxAdoptRate;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxSigmaMultiply;
    QLabel *label_2;
    QPushButton *pushButtonCancel;
    QTableWidget *tableWidgetHistogram;
    QCheckBox *checkBoxCheckAllAlgorithm;
    QCheckBox *checkBoxCheckAllHistogram;

    void setupUi(QDialog *SetThresholdDialog)
    {
        if (SetThresholdDialog->objectName().isEmpty())
            SetThresholdDialog->setObjectName("SetThresholdDialog");
        SetThresholdDialog->resize(660, 430);
        checkBoxModeOneWork = new QCheckBox(SetThresholdDialog);
        checkBoxModeOneWork->setObjectName("checkBoxModeOneWork");
        checkBoxModeOneWork->setGeometry(QRect(20, 20, 511, 22));
        checkBoxModeOneWork->setChecked(true);
        checkBoxModeMultiWork = new QCheckBox(SetThresholdDialog);
        checkBoxModeMultiWork->setObjectName("checkBoxModeMultiWork");
        checkBoxModeMultiWork->setGeometry(QRect(20, 50, 501, 22));
        checkBoxModeMultiWork->setChecked(true);
        tableWidgetAlgorithm = new QTableWidget(SetThresholdDialog);
        if (tableWidgetAlgorithm->columnCount() < 2)
            tableWidgetAlgorithm->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetAlgorithm->setObjectName("tableWidgetAlgorithm");
        tableWidgetAlgorithm->setGeometry(QRect(10, 110, 311, 192));
        pushButtonSet = new QPushButton(SetThresholdDialog);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(10, 380, 112, 34));
        doubleSpinBoxAdoptRate = new QDoubleSpinBox(SetThresholdDialog);
        doubleSpinBoxAdoptRate->setObjectName("doubleSpinBoxAdoptRate");
        doubleSpinBoxAdoptRate->setGeometry(QRect(40, 310, 81, 24));
        doubleSpinBoxAdoptRate->setMaximum(100.000000000000000);
        doubleSpinBoxAdoptRate->setValue(80.000000000000000);
        label = new QLabel(SetThresholdDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 310, 211, 21));
        doubleSpinBoxSigmaMultiply = new QDoubleSpinBox(SetThresholdDialog);
        doubleSpinBoxSigmaMultiply->setObjectName("doubleSpinBoxSigmaMultiply");
        doubleSpinBoxSigmaMultiply->setGeometry(QRect(40, 340, 81, 24));
        doubleSpinBoxSigmaMultiply->setMaximum(20.000000000000000);
        doubleSpinBoxSigmaMultiply->setSingleStep(1.000000000000000);
        doubleSpinBoxSigmaMultiply->setValue(6.000000000000000);
        label_2 = new QLabel(SetThresholdDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 340, 391, 21));
        pushButtonCancel = new QPushButton(SetThresholdDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(340, 370, 141, 51));
        tableWidgetHistogram = new QTableWidget(SetThresholdDialog);
        if (tableWidgetHistogram->columnCount() < 2)
            tableWidgetHistogram->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetHistogram->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetHistogram->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetHistogram->setObjectName("tableWidgetHistogram");
        tableWidgetHistogram->setGeometry(QRect(330, 110, 311, 192));
        checkBoxCheckAllAlgorithm = new QCheckBox(SetThresholdDialog);
        checkBoxCheckAllAlgorithm->setObjectName("checkBoxCheckAllAlgorithm");
        checkBoxCheckAllAlgorithm->setGeometry(QRect(40, 80, 108, 22));
        checkBoxCheckAllAlgorithm->setChecked(true);
        checkBoxCheckAllHistogram = new QCheckBox(SetThresholdDialog);
        checkBoxCheckAllHistogram->setObjectName("checkBoxCheckAllHistogram");
        checkBoxCheckAllHistogram->setGeometry(QRect(350, 80, 108, 22));
        checkBoxCheckAllHistogram->setChecked(true);

        retranslateUi(SetThresholdDialog);

        pushButtonCancel->setDefault(true);


        QMetaObject::connectSlotsByName(SetThresholdDialog);
    } // setupUi

    void retranslateUi(QDialog *SetThresholdDialog)
    {
        SetThresholdDialog->setWindowTitle(QCoreApplication::translate("SetThresholdDialog", "Set threshold", nullptr));
        checkBoxModeOneWork->setText(QCoreApplication::translate("SetThresholdDialog", "\345\220\214\344\270\200\343\203\257\343\203\274\343\202\257\345\206\205\343\201\247\343\201\256\343\203\222\343\202\271\343\203\210\343\202\260\343\203\251\343\203\240", nullptr));
        checkBoxModeMultiWork->setText(QCoreApplication::translate("SetThresholdDialog", "\350\244\207\346\225\260\343\203\257\343\203\274\343\202\257\343\201\247\343\201\256\345\220\214\344\270\200\345\200\213\346\211\200\343\203\222\343\202\271\343\203\210\343\202\260\343\203\251\343\203\240", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetAlgorithm->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SetThresholdDialog", "Use", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetAlgorithm->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SetThresholdDialog", "Algorithm", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("SetThresholdDialog", "\343\201\227\343\201\215\343\201\204\345\200\244\350\250\255\345\256\232", nullptr));
        label->setText(QCoreApplication::translate("SetThresholdDialog", "\346\216\241\347\224\250\347\216\207\357\274\210\357\274\205\357\274\211", nullptr));
        label_2->setText(QCoreApplication::translate("SetThresholdDialog", "\350\250\255\345\256\232\343\201\231\343\202\213\345\201\217\345\267\256\345\200\244\343\201\256\345\200\215\347\216\207", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SetThresholdDialog", "Close", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetHistogram->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SetThresholdDialog", "Use", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetHistogram->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SetThresholdDialog", "Histogram", nullptr));
        checkBoxCheckAllAlgorithm->setText(QCoreApplication::translate("SetThresholdDialog", "All", nullptr));
        checkBoxCheckAllHistogram->setText(QCoreApplication::translate("SetThresholdDialog", "All", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetThresholdDialog: public Ui_SetThresholdDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTHRESHOLDDIALOG_H
