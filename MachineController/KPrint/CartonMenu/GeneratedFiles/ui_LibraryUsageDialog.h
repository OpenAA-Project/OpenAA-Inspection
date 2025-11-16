/********************************************************************************
** Form generated from reading UI file 'LibraryUsageDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIBRARYUSAGEDIALOG_H
#define UI_LIBRARYUSAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_LibraryUsageDialog
{
public:
    QLabel *label;
    QLineEdit *lineEditUsageName;
    QFrame *frame_2;
    QLabel *label_3;
    QComboBox *comboBoxLibTypeSelect;
    QTableWidget *tableWidgetLibListSelect;
    QFrame *frameLibFolderSelect;
    QTableWidget *tableWidgetLibListUsage;
    QPushButton *pushButtonPickup;
    QPushButton *pushButtonPushBack;
    QFrame *frame;
    QToolButton *toolButtonSide1;
    QToolButton *toolButtonSide2;
    QToolButton *toolButtonSide3;
    QToolButton *toolButtonSide4;
    QTableWidget *tableWidget;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonCancel;
    QGroupBox *groupBox;
    QRadioButton *radioButtonPriorityGlobal;
    QRadioButton *radioButtonPriorityMiddle;
    QCheckBox *checkBoxDefault;

    void setupUi(QDialog *LibraryUsageDialog)
    {
        if (LibraryUsageDialog->objectName().isEmpty())
            LibraryUsageDialog->setObjectName("LibraryUsageDialog");
        LibraryUsageDialog->resize(1074, 566);
        label = new QLabel(LibraryUsageDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(248, 50, 61, 24));
        label->setAlignment(Qt::AlignCenter);
        lineEditUsageName = new QLineEdit(LibraryUsageDialog);
        lineEditUsageName->setObjectName("lineEditUsageName");
        lineEditUsageName->setGeometry(QRect(310, 50, 191, 24));
        frame_2 = new QFrame(LibraryUsageDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(258, 80, 671, 431));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 261, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        comboBoxLibTypeSelect = new QComboBox(frame_2);
        comboBoxLibTypeSelect->setObjectName("comboBoxLibTypeSelect");
        comboBoxLibTypeSelect->setGeometry(QRect(10, 30, 241, 22));
        tableWidgetLibListSelect = new QTableWidget(frame_2);
        if (tableWidgetLibListSelect->columnCount() < 2)
            tableWidgetLibListSelect->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibListSelect->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibListSelect->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibListSelect->setObjectName("tableWidgetLibListSelect");
        tableWidgetLibListSelect->setGeometry(QRect(10, 240, 241, 181));
        tableWidgetLibListSelect->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibListSelect->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolderSelect = new QFrame(frame_2);
        frameLibFolderSelect->setObjectName("frameLibFolderSelect");
        frameLibFolderSelect->setGeometry(QRect(10, 60, 241, 171));
        frameLibFolderSelect->setFrameShape(QFrame::StyledPanel);
        frameLibFolderSelect->setFrameShadow(QFrame::Sunken);
        tableWidgetLibListUsage = new QTableWidget(frame_2);
        if (tableWidgetLibListUsage->columnCount() < 3)
            tableWidgetLibListUsage->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLibListUsage->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibListUsage->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetLibListUsage->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        tableWidgetLibListUsage->setObjectName("tableWidgetLibListUsage");
        tableWidgetLibListUsage->setGeometry(QRect(300, 240, 361, 181));
        tableWidgetLibListUsage->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibListUsage->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonPickup = new QPushButton(frame_2);
        pushButtonPickup->setObjectName("pushButtonPickup");
        pushButtonPickup->setGeometry(QRect(260, 280, 31, 41));
        pushButtonPushBack = new QPushButton(frame_2);
        pushButtonPushBack->setObjectName("pushButtonPushBack");
        pushButtonPushBack->setGeometry(QRect(260, 340, 31, 41));
        frame = new QFrame(LibraryUsageDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 661, 41));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonSide1 = new QToolButton(frame);
        toolButtonSide1->setObjectName("toolButtonSide1");
        toolButtonSide1->setGeometry(QRect(10, 10, 101, 31));
        toolButtonSide1->setCheckable(true);
        toolButtonSide1->setChecked(true);
        toolButtonSide1->setAutoExclusive(true);
        toolButtonSide2 = new QToolButton(frame);
        toolButtonSide2->setObjectName("toolButtonSide2");
        toolButtonSide2->setGeometry(QRect(120, 10, 101, 31));
        toolButtonSide2->setCheckable(true);
        toolButtonSide2->setAutoExclusive(true);
        toolButtonSide3 = new QToolButton(frame);
        toolButtonSide3->setObjectName("toolButtonSide3");
        toolButtonSide3->setGeometry(QRect(230, 10, 101, 31));
        toolButtonSide3->setCheckable(true);
        toolButtonSide3->setAutoExclusive(true);
        toolButtonSide4 = new QToolButton(frame);
        toolButtonSide4->setObjectName("toolButtonSide4");
        toolButtonSide4->setGeometry(QRect(340, 10, 101, 31));
        toolButtonSide4->setCheckable(true);
        toolButtonSide4->setAutoExclusive(true);
        tableWidget = new QTableWidget(LibraryUsageDialog);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 50, 241, 461));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonDelete = new QPushButton(LibraryUsageDialog);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(140, 520, 112, 34));
        pushButtonUpdate = new QPushButton(LibraryUsageDialog);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(950, 300, 112, 34));
        pushButtonAdd = new QPushButton(LibraryUsageDialog);
        pushButtonAdd->setObjectName("pushButtonAdd");
        pushButtonAdd->setGeometry(QRect(950, 350, 112, 34));
        pushButtonCancel = new QPushButton(LibraryUsageDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(830, 520, 112, 34));
        groupBox = new QGroupBox(LibraryUsageDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(940, 80, 121, 111));
        radioButtonPriorityGlobal = new QRadioButton(groupBox);
        radioButtonPriorityGlobal->setObjectName("radioButtonPriorityGlobal");
        radioButtonPriorityGlobal->setGeometry(QRect(10, 30, 101, 22));
        radioButtonPriorityGlobal->setChecked(true);
        radioButtonPriorityMiddle = new QRadioButton(groupBox);
        radioButtonPriorityMiddle->setObjectName("radioButtonPriorityMiddle");
        radioButtonPriorityMiddle->setGeometry(QRect(10, 60, 101, 22));
        checkBoxDefault = new QCheckBox(LibraryUsageDialog);
        checkBoxDefault->setObjectName("checkBoxDefault");
        checkBoxDefault->setGeometry(QRect(940, 200, 108, 31));

        retranslateUi(LibraryUsageDialog);

        QMetaObject::connectSlotsByName(LibraryUsageDialog);
    } // setupUi

    void retranslateUi(QDialog *LibraryUsageDialog)
    {
        LibraryUsageDialog->setWindowTitle(QCoreApplication::translate("LibraryUsageDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("LibraryUsageDialog", "\345\220\215\347\247\260", nullptr));
        label_3->setText(QCoreApplication::translate("LibraryUsageDialog", "Select library - source", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibListSelect->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("LibraryUsageDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibListSelect->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("LibraryUsageDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibListUsage->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("LibraryUsageDialog", "Algorithm", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibListUsage->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("LibraryUsageDialog", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetLibListUsage->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("LibraryUsageDialog", "Name", nullptr));
        pushButtonPickup->setText(QCoreApplication::translate("LibraryUsageDialog", "=>", nullptr));
        pushButtonPushBack->setText(QCoreApplication::translate("LibraryUsageDialog", "<=", nullptr));
        toolButtonSide1->setText(QCoreApplication::translate("LibraryUsageDialog", "Top", nullptr));
        toolButtonSide2->setText(QCoreApplication::translate("LibraryUsageDialog", "Bottom", nullptr));
        toolButtonSide3->setText(QCoreApplication::translate("LibraryUsageDialog", "Mono", nullptr));
        toolButtonSide4->setText(QCoreApplication::translate("LibraryUsageDialog", "Mono", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("LibraryUsageDialog", "\345\220\215\347\247\260", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("LibraryUsageDialog", "Delete", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("LibraryUsageDialog", "Update", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("LibraryUsageDialog", "Add", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("LibraryUsageDialog", "Cancel", nullptr));
        groupBox->setTitle(QCoreApplication::translate("LibraryUsageDialog", "\343\202\242\343\203\251\343\202\244\343\203\263\343\203\241\343\203\263\343\203\210", nullptr));
        radioButtonPriorityGlobal->setText(QCoreApplication::translate("LibraryUsageDialog", "\345\244\226\345\275\242", nullptr));
        radioButtonPriorityMiddle->setText(QCoreApplication::translate("LibraryUsageDialog", "\343\203\221\343\202\277\343\203\274\343\203\263", nullptr));
        checkBoxDefault->setText(QCoreApplication::translate("LibraryUsageDialog", "\345\210\235\346\234\237\344\275\277\347\224\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LibraryUsageDialog: public Ui_LibraryUsageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIBRARYUSAGEDIALOG_H
