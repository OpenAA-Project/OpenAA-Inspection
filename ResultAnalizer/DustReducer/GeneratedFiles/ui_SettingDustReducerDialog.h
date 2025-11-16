/********************************************************************************
** Form generated from reading UI file 'SettingDustReducerDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDUSTREDUCERDIALOG_H
#define UI_SETTINGDUSTREDUCERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingDustReducerDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *spinBoxVLayer;
    QLabel *label_6;
    QSpinBox *spinBoxBrightnessL;
    QSpinBox *spinBoxBrightnessH;
    QSpinBox *spinBoxMaxAreaDots;
    QSpinBox *spinBoxMaxLength;
    QDoubleSpinBox *doubleSpinBoxMaxV;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QTableWidget *tableWidgetResult;
    QLabel *label_7;
    QPushButton *pushButtonUpdateResult;

    void setupUi(QDialog *SettingDustReducerDialog)
    {
        if (SettingDustReducerDialog->objectName().isEmpty())
            SettingDustReducerDialog->setObjectName("SettingDustReducerDialog");
        SettingDustReducerDialog->resize(826, 249);
        label = new QLabel(SettingDustReducerDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 201, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(SettingDustReducerDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 40, 201, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(SettingDustReducerDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 201, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(SettingDustReducerDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 100, 201, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(SettingDustReducerDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 130, 201, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        spinBoxVLayer = new QSpinBox(SettingDustReducerDialog);
        spinBoxVLayer->setObjectName("spinBoxVLayer");
        spinBoxVLayer->setGeometry(QRect(220, 10, 101, 24));
        label_6 = new QLabel(SettingDustReducerDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 160, 201, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        spinBoxBrightnessL = new QSpinBox(SettingDustReducerDialog);
        spinBoxBrightnessL->setObjectName("spinBoxBrightnessL");
        spinBoxBrightnessL->setGeometry(QRect(220, 40, 101, 24));
        spinBoxBrightnessL->setMaximum(255);
        spinBoxBrightnessH = new QSpinBox(SettingDustReducerDialog);
        spinBoxBrightnessH->setObjectName("spinBoxBrightnessH");
        spinBoxBrightnessH->setGeometry(QRect(220, 70, 101, 24));
        spinBoxBrightnessH->setMaximum(255);
        spinBoxMaxAreaDots = new QSpinBox(SettingDustReducerDialog);
        spinBoxMaxAreaDots->setObjectName("spinBoxMaxAreaDots");
        spinBoxMaxAreaDots->setGeometry(QRect(220, 100, 101, 24));
        spinBoxMaxAreaDots->setMaximum(99999999);
        spinBoxMaxLength = new QSpinBox(SettingDustReducerDialog);
        spinBoxMaxLength->setObjectName("spinBoxMaxLength");
        spinBoxMaxLength->setGeometry(QRect(220, 130, 101, 24));
        spinBoxMaxLength->setMaximum(99999999);
        doubleSpinBoxMaxV = new QDoubleSpinBox(SettingDustReducerDialog);
        doubleSpinBoxMaxV->setObjectName("doubleSpinBoxMaxV");
        doubleSpinBoxMaxV->setGeometry(QRect(220, 160, 101, 24));
        doubleSpinBoxMaxV->setMaximum(1000.000000000000000);
        pushButtonOK = new QPushButton(SettingDustReducerDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 200, 112, 34));
        pushButtonCancel = new QPushButton(SettingDustReducerDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(200, 200, 112, 34));
        tableWidgetResult = new QTableWidget(SettingDustReducerDialog);
        if (tableWidgetResult->columnCount() < 8)
            tableWidgetResult->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableWidgetResult->setObjectName("tableWidgetResult");
        tableWidgetResult->setGeometry(QRect(340, 31, 481, 161));
        tableWidgetResult->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetResult->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetResult->setTextElideMode(Qt::ElideMiddle);
        label_7 = new QLabel(SettingDustReducerDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(340, 10, 481, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        pushButtonUpdateResult = new QPushButton(SettingDustReducerDialog);
        pushButtonUpdateResult->setObjectName("pushButtonUpdateResult");
        pushButtonUpdateResult->setGeometry(QRect(520, 200, 112, 34));

        retranslateUi(SettingDustReducerDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SettingDustReducerDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDustReducerDialog)
    {
        SettingDustReducerDialog->setWindowTitle(QCoreApplication::translate("SettingDustReducerDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SettingDustReducerDialog", "\350\251\225\344\276\241\343\201\231\343\202\213\347\224\273\345\203\217\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDustReducerDialog", "\343\201\224\343\201\277\343\201\256\344\270\213\351\231\220\350\274\235\345\272\246", nullptr));
        label_3->setText(QCoreApplication::translate("SettingDustReducerDialog", "\343\201\224\343\201\277\343\201\256\344\270\212\351\231\220\350\274\235\345\272\246", nullptr));
        label_4->setText(QCoreApplication::translate("SettingDustReducerDialog", "\343\201\224\343\201\277\343\201\256\351\235\242\347\251\215\357\274\210\343\203\211\343\203\203\343\203\210\346\225\260\357\274\211\343\201\256\344\270\212\351\231\220", nullptr));
        label_5->setText(QCoreApplication::translate("SettingDustReducerDialog", "\343\201\224\343\201\277\343\201\256\351\225\267\343\201\225\343\201\256\344\270\212\351\231\220", nullptr));
        label_6->setText(QCoreApplication::translate("SettingDustReducerDialog", "\345\221\250\345\233\262\343\201\256\350\274\235\345\272\246\345\201\217\345\267\256\345\200\244", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDustReducerDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingDustReducerDialog", "Cancel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetResult->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SettingDustReducerDialog", "Phase", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetResult->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SettingDustReducerDialog", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetResult->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SettingDustReducerDialog", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetResult->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SettingDustReducerDialog", "ItemID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetResult->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SettingDustReducerDialog", "PosNo", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetResult->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SettingDustReducerDialog", "\351\235\242\347\251\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetResult->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("SettingDustReducerDialog", "\351\225\267\343\201\225", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetResult->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("SettingDustReducerDialog", "\346\250\231\346\272\226\345\201\217\345\267\256", nullptr));
        label_7->setText(QCoreApplication::translate("SettingDustReducerDialog", "\345\207\246\347\220\206\347\265\220\346\236\234", nullptr));
        pushButtonUpdateResult->setText(QCoreApplication::translate("SettingDustReducerDialog", "\346\233\264\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDustReducerDialog: public Ui_SettingDustReducerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDUSTREDUCERDIALOG_H
