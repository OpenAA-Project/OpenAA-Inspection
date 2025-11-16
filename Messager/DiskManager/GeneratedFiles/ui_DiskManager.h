/********************************************************************************
** Form generated from reading UI file 'DiskManager.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISKMANAGER_H
#define UI_DISKMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DiskManagerClass
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QLabel *label_2;
    QSpinBox *spinBoxYear;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *spinBoxMonth;
    QLabel *label_5;
    QSpinBox *spinBoxDay;
    QLabel *label_6;
    QSpinBox *spinBoxHour;
    QLabel *label_7;
    QSpinBox *spinBoxMinute;
    QLabel *label_8;
    QSpinBox *spinBoxSecond;
    QCheckBox *checkBoxExecuteDelete;
    QPushButton *pushButtonSaveSetting;
    QPushButton *pushButtonTransmitSetting;
    QCheckBox *checkBoxAutoMode;
    QFrame *frame_3;
    QLabel *label_11;
    QTableWidget *tableWidgetFileList;
    QTableWidget *tableWidgetSourceDrive;
    QLabel *label_10;

    void setupUi(QMainWindow *DiskManagerClass)
    {
        if (DiskManagerClass->objectName().isEmpty())
            DiskManagerClass->setObjectName("DiskManagerClass");
        DiskManagerClass->resize(831, 745);
        centralWidget = new QWidget(DiskManagerClass);
        centralWidget->setObjectName("centralWidget");
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(440, 30, 301, 241));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 40, 271, 21));
        spinBoxYear = new QSpinBox(frame);
        spinBoxYear->setObjectName("spinBoxYear");
        spinBoxYear->setGeometry(QRect(10, 70, 50, 22));
        spinBoxYear->setMinimum(2000);
        spinBoxYear->setMaximum(2099);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(70, 70, 21, 21));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(150, 70, 21, 21));
        spinBoxMonth = new QSpinBox(frame);
        spinBoxMonth->setObjectName("spinBoxMonth");
        spinBoxMonth->setGeometry(QRect(90, 70, 50, 22));
        spinBoxMonth->setMinimum(1);
        spinBoxMonth->setMaximum(12);
        spinBoxMonth->setValue(1);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(240, 70, 21, 21));
        spinBoxDay = new QSpinBox(frame);
        spinBoxDay->setObjectName("spinBoxDay");
        spinBoxDay->setGeometry(QRect(180, 70, 50, 22));
        spinBoxDay->setMinimum(1);
        spinBoxDay->setMaximum(31);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(70, 100, 21, 21));
        spinBoxHour = new QSpinBox(frame);
        spinBoxHour->setObjectName("spinBoxHour");
        spinBoxHour->setGeometry(QRect(10, 100, 51, 22));
        spinBoxHour->setMaximum(23);
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(150, 100, 21, 21));
        spinBoxMinute = new QSpinBox(frame);
        spinBoxMinute->setObjectName("spinBoxMinute");
        spinBoxMinute->setGeometry(QRect(90, 100, 50, 22));
        spinBoxMinute->setMaximum(59);
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(240, 100, 21, 21));
        spinBoxSecond = new QSpinBox(frame);
        spinBoxSecond->setObjectName("spinBoxSecond");
        spinBoxSecond->setGeometry(QRect(180, 100, 50, 22));
        spinBoxSecond->setMaximum(59);
        checkBoxExecuteDelete = new QCheckBox(frame);
        checkBoxExecuteDelete->setObjectName("checkBoxExecuteDelete");
        checkBoxExecuteDelete->setGeometry(QRect(10, 140, 251, 19));
        pushButtonSaveSetting = new QPushButton(frame);
        pushButtonSaveSetting->setObjectName("pushButtonSaveSetting");
        pushButtonSaveSetting->setGeometry(QRect(10, 180, 111, 31));
        pushButtonTransmitSetting = new QPushButton(frame);
        pushButtonTransmitSetting->setObjectName("pushButtonTransmitSetting");
        pushButtonTransmitSetting->setGeometry(QRect(150, 180, 111, 31));
        checkBoxAutoMode = new QCheckBox(frame);
        checkBoxAutoMode->setObjectName("checkBoxAutoMode");
        checkBoxAutoMode->setGeometry(QRect(10, 10, 161, 19));
        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 380, 811, 351));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_11 = new QLabel(frame_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(0, 0, 611, 20));
        label_11->setAlignment(Qt::AlignCenter);
        tableWidgetFileList = new QTableWidget(frame_3);
        if (tableWidgetFileList->columnCount() < 4)
            tableWidgetFileList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetFileList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetFileList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetFileList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetFileList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetFileList->setObjectName("tableWidgetFileList");
        tableWidgetFileList->setGeometry(QRect(10, 30, 791, 311));
        tableWidgetFileList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetFileList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetSourceDrive = new QTableWidget(centralWidget);
        if (tableWidgetSourceDrive->columnCount() < 3)
            tableWidgetSourceDrive->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetSourceDrive->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetSourceDrive->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetSourceDrive->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        tableWidgetSourceDrive->setObjectName("tableWidgetSourceDrive");
        tableWidgetSourceDrive->setGeometry(QRect(10, 40, 411, 321));
        tableWidgetSourceDrive->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetSourceDrive->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 20, 291, 21));
        DiskManagerClass->setCentralWidget(centralWidget);

        retranslateUi(DiskManagerClass);

        QMetaObject::connectSlotsByName(DiskManagerClass);
    } // setupUi

    void retranslateUi(QMainWindow *DiskManagerClass)
    {
        DiskManagerClass->setWindowTitle(QCoreApplication::translate("DiskManagerClass", "DiskManager", nullptr));
        label_2->setText(QCoreApplication::translate("DiskManagerClass", "\343\201\223\343\202\214\343\202\210\343\202\212\345\217\244\343\201\204\343\203\225\343\202\241\343\202\244\343\203\253\343\202\222\347\247\273\345\213\225\343\203\273\345\211\212\351\231\244", nullptr));
        label_3->setText(QCoreApplication::translate("DiskManagerClass", "\345\271\264", nullptr));
        label_4->setText(QCoreApplication::translate("DiskManagerClass", "\346\234\210", nullptr));
        label_5->setText(QCoreApplication::translate("DiskManagerClass", "\346\227\245", nullptr));
        label_6->setText(QCoreApplication::translate("DiskManagerClass", "\346\231\202", nullptr));
        label_7->setText(QCoreApplication::translate("DiskManagerClass", "\345\210\206", nullptr));
        label_8->setText(QCoreApplication::translate("DiskManagerClass", "\347\247\222", nullptr));
        checkBoxExecuteDelete->setText(QCoreApplication::translate("DiskManagerClass", "\345\211\212\351\231\244\343\202\222\345\256\237\350\241\214", nullptr));
        pushButtonSaveSetting->setText(QCoreApplication::translate("DiskManagerClass", "\350\250\255\345\256\232\344\277\235\345\255\230", nullptr));
        pushButtonTransmitSetting->setText(QCoreApplication::translate("DiskManagerClass", "\350\250\255\345\256\232\351\200\201\344\277\241", nullptr));
        checkBoxAutoMode->setText(QCoreApplication::translate("DiskManagerClass", "\350\207\252\345\213\225\350\273\242\351\200\201\343\203\273\345\211\212\351\231\244", nullptr));
        label_11->setText(QCoreApplication::translate("DiskManagerClass", "\346\211\213\345\213\225\343\201\247\343\201\256\346\223\215\344\275\234\357\274\210\343\203\252\343\202\271\343\203\210\343\202\222\343\203\200\343\203\226\343\203\253\343\202\257\343\203\252\343\203\203\343\202\257\357\274\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetFileList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DiskManagerClass", "\343\203\221\343\202\271", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetFileList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DiskManagerClass", "\343\203\225\343\202\241\343\202\244\343\203\253\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetFileList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DiskManagerClass", "\343\202\265\343\202\244\343\202\272", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetFileList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("DiskManagerClass", "\346\233\264\346\226\260\346\227\245\346\231\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetSourceDrive->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("DiskManagerClass", "PC", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetSourceDrive->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("DiskManagerClass", "Drive", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetSourceDrive->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("DiskManagerClass", "Free area", nullptr));
        label_10->setText(QCoreApplication::translate("DiskManagerClass", "\347\233\243\350\246\226\345\257\276\350\261\241Drive", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DiskManagerClass: public Ui_DiskManagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISKMANAGER_H
