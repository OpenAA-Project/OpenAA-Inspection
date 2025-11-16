/********************************************************************************
** Form generated from reading UI file 'SelectLibraryWithTypeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLIBRARYWITHTYPEDIALOG_H
#define UI_SELECTLIBRARYWITHTYPEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectLibraryWithTypeDialog
{
public:
    QFrame *frame_2;
    QLabel *label_3;
    QComboBox *comboBoxLibTypeSelect;
    QFrame *frameLibFolderSelect;
    QTableWidget *tableWidgetLibListSelect;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectLibraryWithTypeDialog)
    {
        if (SelectLibraryWithTypeDialog->objectName().isEmpty())
            SelectLibraryWithTypeDialog->setObjectName("SelectLibraryWithTypeDialog");
        SelectLibraryWithTypeDialog->resize(351, 644);
        frame_2 = new QFrame(SelectLibraryWithTypeDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(0, 0, 351, 581));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 341, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        comboBoxLibTypeSelect = new QComboBox(frame_2);
        comboBoxLibTypeSelect->setObjectName("comboBoxLibTypeSelect");
        comboBoxLibTypeSelect->setGeometry(QRect(10, 30, 331, 22));
        frameLibFolderSelect = new QFrame(frame_2);
        frameLibFolderSelect->setObjectName("frameLibFolderSelect");
        frameLibFolderSelect->setGeometry(QRect(10, 60, 331, 201));
        frameLibFolderSelect->setFrameShape(QFrame::StyledPanel);
        frameLibFolderSelect->setFrameShadow(QFrame::Sunken);
        tableWidgetLibListSelect = new QTableWidget(frame_2);
        if (tableWidgetLibListSelect->columnCount() < 2)
            tableWidgetLibListSelect->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibListSelect->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibListSelect->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibListSelect->setObjectName("tableWidgetLibListSelect");
        tableWidgetLibListSelect->setGeometry(QRect(10, 270, 331, 301));
        tableWidgetLibListSelect->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibListSelect->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelect = new QPushButton(SelectLibraryWithTypeDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(10, 590, 131, 41));
        pushButtonCancel = new QPushButton(SelectLibraryWithTypeDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(210, 590, 131, 41));

        retranslateUi(SelectLibraryWithTypeDialog);

        pushButtonSelect->setDefault(true);


        QMetaObject::connectSlotsByName(SelectLibraryWithTypeDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectLibraryWithTypeDialog)
    {
        SelectLibraryWithTypeDialog->setWindowTitle(QCoreApplication::translate("SelectLibraryWithTypeDialog", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("SelectLibraryWithTypeDialog", "Select library - source", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibListSelect->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectLibraryWithTypeDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibListSelect->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectLibraryWithTypeDialog", "Name", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectLibraryWithTypeDialog", "Select", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectLibraryWithTypeDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibraryWithTypeDialog: public Ui_SelectLibraryWithTypeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBRARYWITHTYPEDIALOG_H
