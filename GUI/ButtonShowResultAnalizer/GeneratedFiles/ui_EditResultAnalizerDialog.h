/********************************************************************************
** Form generated from reading UI file 'EditResultAnalizerDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITRESULTANALIZERDIALOG_H
#define UI_EDITRESULTANALIZERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditResultAnalizerDialog
{
public:
    QLabel *label;
    QListWidget *listWidgetResultAnalizerDLL;
    QTableWidget *tableWidgetResultAnalizerItemBase;
    QLabel *label_2;
    QPushButton *pushButtonFromDLL;
    QPushButton *pushButtonToDLL;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonLoad;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonUpdateDefault;

    void setupUi(QDialog *EditResultAnalizerDialog)
    {
        if (EditResultAnalizerDialog->objectName().isEmpty())
            EditResultAnalizerDialog->setObjectName("EditResultAnalizerDialog");
        EditResultAnalizerDialog->resize(664, 313);
        label = new QLabel(EditResultAnalizerDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 261, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        listWidgetResultAnalizerDLL = new QListWidget(EditResultAnalizerDialog);
        listWidgetResultAnalizerDLL->setObjectName("listWidgetResultAnalizerDLL");
        listWidgetResultAnalizerDLL->setGeometry(QRect(10, 31, 261, 192));
        tableWidgetResultAnalizerItemBase = new QTableWidget(EditResultAnalizerDialog);
        if (tableWidgetResultAnalizerItemBase->columnCount() < 3)
            tableWidgetResultAnalizerItemBase->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetResultAnalizerItemBase->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetResultAnalizerItemBase->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetResultAnalizerItemBase->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetResultAnalizerItemBase->setObjectName("tableWidgetResultAnalizerItemBase");
        tableWidgetResultAnalizerItemBase->setGeometry(QRect(340, 31, 311, 192));
        label_2 = new QLabel(EditResultAnalizerDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(340, 10, 311, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        pushButtonFromDLL = new QPushButton(EditResultAnalizerDialog);
        pushButtonFromDLL->setObjectName("pushButtonFromDLL");
        pushButtonFromDLL->setGeometry(QRect(280, 60, 51, 34));
        pushButtonToDLL = new QPushButton(EditResultAnalizerDialog);
        pushButtonToDLL->setObjectName("pushButtonToDLL");
        pushButtonToDLL->setGeometry(QRect(280, 110, 51, 34));
        pushButtonSave = new QPushButton(EditResultAnalizerDialog);
        pushButtonSave->setObjectName("pushButtonSave");
        pushButtonSave->setGeometry(QRect(10, 230, 131, 34));
        pushButtonLoad = new QPushButton(EditResultAnalizerDialog);
        pushButtonLoad->setObjectName("pushButtonLoad");
        pushButtonLoad->setGeometry(QRect(150, 230, 121, 34));
        pushButtonOK = new QPushButton(EditResultAnalizerDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(540, 240, 112, 34));
        pushButtonUpdateDefault = new QPushButton(EditResultAnalizerDialog);
        pushButtonUpdateDefault->setObjectName("pushButtonUpdateDefault");
        pushButtonUpdateDefault->setGeometry(QRect(10, 270, 131, 34));

        retranslateUi(EditResultAnalizerDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(EditResultAnalizerDialog);
    } // setupUi

    void retranslateUi(QDialog *EditResultAnalizerDialog)
    {
        EditResultAnalizerDialog->setWindowTitle(QCoreApplication::translate("EditResultAnalizerDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("EditResultAnalizerDialog", "Result analizer", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetResultAnalizerItemBase->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditResultAnalizerDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetResultAnalizerItemBase->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditResultAnalizerDialog", "Comp name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetResultAnalizerItemBase->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EditResultAnalizerDialog", "Usage name", nullptr));
        label_2->setText(QCoreApplication::translate("EditResultAnalizerDialog", "Usage in master data", nullptr));
        pushButtonFromDLL->setText(QCoreApplication::translate("EditResultAnalizerDialog", "=>", nullptr));
        pushButtonToDLL->setText(QCoreApplication::translate("EditResultAnalizerDialog", "<=", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("EditResultAnalizerDialog", "Save", nullptr));
        pushButtonLoad->setText(QCoreApplication::translate("EditResultAnalizerDialog", "Load", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditResultAnalizerDialog", "OK", nullptr));
        pushButtonUpdateDefault->setText(QCoreApplication::translate("EditResultAnalizerDialog", "Update default", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditResultAnalizerDialog: public Ui_EditResultAnalizerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITRESULTANALIZERDIALOG_H
