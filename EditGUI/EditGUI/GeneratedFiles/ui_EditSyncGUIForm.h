/********************************************************************************
** Form generated from reading UI file 'EditSyncGUIForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITSYNCGUIFORM_H
#define UI_EDITSYNCGUIFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditSyncGUIForm
{
public:
    QPushButton *pushButtonDelLine;
    QPushButton *pushButtonAddLine;
    QPushButton *pushButtonSaveNew;
    QTableWidget *tableWidget;
    QPushButton *pushButtonClose;
    QLineEdit *lineEditFileName;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonFileName;
    QLabel *label;
    QPushButton *pushButtonLoad;

    void setupUi(QWidget *EditSyncGUIForm)
    {
        if (EditSyncGUIForm->objectName().isEmpty())
            EditSyncGUIForm->setObjectName("EditSyncGUIForm");
        EditSyncGUIForm->resize(403, 403);
        pushButtonDelLine = new QPushButton(EditSyncGUIForm);
        pushButtonDelLine->setObjectName("pushButtonDelLine");
        pushButtonDelLine->setGeometry(QRect(110, 300, 75, 31));
        pushButtonAddLine = new QPushButton(EditSyncGUIForm);
        pushButtonAddLine->setObjectName("pushButtonAddLine");
        pushButtonAddLine->setGeometry(QRect(20, 300, 75, 31));
        pushButtonSaveNew = new QPushButton(EditSyncGUIForm);
        pushButtonSaveNew->setObjectName("pushButtonSaveNew");
        pushButtonSaveNew->setGeometry(QRect(150, 350, 111, 41));
        tableWidget = new QTableWidget(EditSyncGUIForm);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 120, 381, 171));
        tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);
        pushButtonClose = new QPushButton(EditSyncGUIForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(280, 350, 111, 41));
        lineEditFileName = new QLineEdit(EditSyncGUIForm);
        lineEditFileName->setObjectName("lineEditFileName");
        lineEditFileName->setGeometry(QRect(10, 32, 321, 26));
        pushButtonUpdate = new QPushButton(EditSyncGUIForm);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(20, 350, 111, 41));
        pushButtonFileName = new QPushButton(EditSyncGUIForm);
        pushButtonFileName->setObjectName("pushButtonFileName");
        pushButtonFileName->setGeometry(QRect(330, 32, 61, 26));
        label = new QLabel(EditSyncGUIForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 381, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        pushButtonLoad = new QPushButton(EditSyncGUIForm);
        pushButtonLoad->setObjectName("pushButtonLoad");
        pushButtonLoad->setGeometry(QRect(140, 70, 111, 41));

        retranslateUi(EditSyncGUIForm);

        pushButtonClose->setDefault(true);


        QMetaObject::connectSlotsByName(EditSyncGUIForm);
    } // setupUi

    void retranslateUi(QWidget *EditSyncGUIForm)
    {
        EditSyncGUIForm->setWindowTitle(QCoreApplication::translate("EditSyncGUIForm", "Form", nullptr));
        pushButtonDelLine->setText(QCoreApplication::translate("EditSyncGUIForm", "-", nullptr));
        pushButtonAddLine->setText(QCoreApplication::translate("EditSyncGUIForm", "+", nullptr));
        pushButtonSaveNew->setText(QCoreApplication::translate("EditSyncGUIForm", "Save new file", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditSyncGUIForm", "IPAddress", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditSyncGUIForm", "Port", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditSyncGUIForm", "Close", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("EditSyncGUIForm", "Update file", nullptr));
        pushButtonFileName->setText(QCoreApplication::translate("EditSyncGUIForm", "...", nullptr));
        label->setText(QCoreApplication::translate("EditSyncGUIForm", "Sync GUI file name", nullptr));
        pushButtonLoad->setText(QCoreApplication::translate("EditSyncGUIForm", "Load file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditSyncGUIForm: public Ui_EditSyncGUIForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITSYNCGUIFORM_H
