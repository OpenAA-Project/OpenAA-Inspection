/********************************************************************************
** Form generated from reading UI file 'AllocationLibByColorDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALLOCATIONLIBBYCOLORDIALOG_H
#define UI_ALLOCATIONLIBBYCOLORDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_AllocationLibByColorDialog
{
public:
    QFrame *frame;
    QFrame *frame_2;
    QLabel *label_3;
    QComboBox *comboBoxLibTypeSelect;
    QFrame *frameLibFolderSelect;
    QTableWidget *tableWidgetLibListSelect;
    QPushButton *pushButtonSelectButton;
    QFrame *frame_3;
    QLabel *label_4;
    QTableWidget *tableWidgetSelected;
    QPushButton *pushButtonUpdate;
    QFrame *frame_4;
    QLabel *label;
    QPushButton *pushButtonAddColor;
    QTableWidget *tableWidget;
    QPushButton *pushButtonSubColor;
    QPushButton *pushButtonFromDXFData;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *AllocationLibByColorDialog)
    {
        if (AllocationLibByColorDialog->objectName().isEmpty())
            AllocationLibByColorDialog->setObjectName("AllocationLibByColorDialog");
        AllocationLibByColorDialog->resize(958, 609);
        frame = new QFrame(AllocationLibByColorDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(220, 10, 731, 541));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 10, 271, 521));
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
        comboBoxLibTypeSelect->setGeometry(QRect(10, 30, 251, 22));
        frameLibFolderSelect = new QFrame(frame_2);
        frameLibFolderSelect->setObjectName("frameLibFolderSelect");
        frameLibFolderSelect->setGeometry(QRect(10, 60, 251, 141));
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
        tableWidgetLibListSelect->setGeometry(QRect(10, 210, 251, 301));
        tableWidgetLibListSelect->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibListSelect->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelectButton = new QPushButton(frame);
        pushButtonSelectButton->setObjectName("pushButtonSelectButton");
        pushButtonSelectButton->setGeometry(QRect(290, 190, 51, 41));
        frame_3 = new QFrame(frame);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(350, 10, 371, 461));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 0, 351, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        tableWidgetSelected = new QTableWidget(frame_3);
        if (tableWidgetSelected->columnCount() < 3)
            tableWidgetSelected->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetSelected->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetSelected->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetSelected->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        tableWidgetSelected->setObjectName("tableWidgetSelected");
        tableWidgetSelected->setGeometry(QRect(10, 30, 351, 421));
        tableWidgetSelected->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetSelected->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonUpdate = new QPushButton(frame);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(410, 480, 201, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon);
        frame_4 = new QFrame(AllocationLibByColorDialog);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(0, 10, 211, 541));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame_4);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 161, 18));
        label->setAlignment(Qt::AlignCenter);
        pushButtonAddColor = new QPushButton(frame_4);
        pushButtonAddColor->setObjectName("pushButtonAddColor");
        pushButtonAddColor->setGeometry(QRect(40, 450, 121, 34));
        tableWidget = new QTableWidget(frame_4);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 30, 191, 351));
        pushButtonSubColor = new QPushButton(frame_4);
        pushButtonSubColor->setObjectName("pushButtonSubColor");
        pushButtonSubColor->setGeometry(QRect(40, 490, 121, 34));
        pushButtonFromDXFData = new QPushButton(frame_4);
        pushButtonFromDXFData->setObjectName("pushButtonFromDXFData");
        pushButtonFromDXFData->setGeometry(QRect(30, 390, 141, 51));
        pushButtonCancel = new QPushButton(AllocationLibByColorDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(800, 560, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        pushButtonOK = new QPushButton(AllocationLibByColorDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(650, 560, 141, 41));
        pushButtonOK->setIcon(icon);

        retranslateUi(AllocationLibByColorDialog);

        pushButtonUpdate->setDefault(false);
        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(AllocationLibByColorDialog);
    } // setupUi

    void retranslateUi(QDialog *AllocationLibByColorDialog)
    {
        AllocationLibByColorDialog->setWindowTitle(QCoreApplication::translate("AllocationLibByColorDialog", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("AllocationLibByColorDialog", "Select library - source", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibListSelect->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AllocationLibByColorDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibListSelect->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AllocationLibByColorDialog", "Name", nullptr));
        pushButtonSelectButton->setText(QCoreApplication::translate("AllocationLibByColorDialog", "=>", nullptr));
        label_4->setText(QCoreApplication::translate("AllocationLibByColorDialog", "Selected", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetSelected->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("AllocationLibByColorDialog", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetSelected->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("AllocationLibByColorDialog", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetSelected->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("AllocationLibByColorDialog", "Library Name", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("AllocationLibByColorDialog", "Update", nullptr));
        label->setText(QCoreApplication::translate("AllocationLibByColorDialog", "Color", nullptr));
        pushButtonAddColor->setText(QCoreApplication::translate("AllocationLibByColorDialog", "Add color", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("AllocationLibByColorDialog", "Color", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("AllocationLibByColorDialog", "Item", nullptr));
        pushButtonSubColor->setText(QCoreApplication::translate("AllocationLibByColorDialog", "Sub color", nullptr));
        pushButtonFromDXFData->setText(QCoreApplication::translate("AllocationLibByColorDialog", "From DXF data", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AllocationLibByColorDialog", "Cancel", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AllocationLibByColorDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AllocationLibByColorDialog: public Ui_AllocationLibByColorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALLOCATIONLIBBYCOLORDIALOG_H
