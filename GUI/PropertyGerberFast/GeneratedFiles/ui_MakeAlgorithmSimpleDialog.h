/********************************************************************************
** Form generated from reading UI file 'MakeAlgorithmSimpleDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAKEALGORITHMSIMPLEDIALOG_H
#define UI_MAKEALGORITHMSIMPLEDIALOG_H

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

class Ui_MakeAlgorithmSimpleDialog
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
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *MakeAlgorithmSimpleDialog)
    {
        if (MakeAlgorithmSimpleDialog->objectName().isEmpty())
            MakeAlgorithmSimpleDialog->setObjectName("MakeAlgorithmSimpleDialog");
        MakeAlgorithmSimpleDialog->resize(719, 562);
        frame = new QFrame(MakeAlgorithmSimpleDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 701, 541));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 10, 261, 521));
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
        frameLibFolderSelect = new QFrame(frame_2);
        frameLibFolderSelect->setObjectName("frameLibFolderSelect");
        frameLibFolderSelect->setGeometry(QRect(10, 60, 241, 141));
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
        tableWidgetLibListSelect->setGeometry(QRect(10, 210, 241, 301));
        tableWidgetLibListSelect->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibListSelect->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelectButton = new QPushButton(frame);
        pushButtonSelectButton->setObjectName("pushButtonSelectButton");
        pushButtonSelectButton->setGeometry(QRect(280, 190, 51, 41));
        frame_3 = new QFrame(frame);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(340, 10, 351, 461));
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
        tableWidgetSelected->setGeometry(QRect(10, 30, 331, 421));
        tableWidgetSelected->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetSelected->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonUpdate = new QPushButton(frame);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(340, 490, 201, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon);
        pushButtonCancel = new QPushButton(frame);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(590, 490, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(MakeAlgorithmSimpleDialog);

        pushButtonUpdate->setDefault(true);


        QMetaObject::connectSlotsByName(MakeAlgorithmSimpleDialog);
    } // setupUi

    void retranslateUi(QDialog *MakeAlgorithmSimpleDialog)
    {
        MakeAlgorithmSimpleDialog->setWindowTitle(QCoreApplication::translate("MakeAlgorithmSimpleDialog", "Make algorithm simple items", nullptr));
        label_3->setText(QCoreApplication::translate("MakeAlgorithmSimpleDialog", "Select library - source", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibListSelect->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MakeAlgorithmSimpleDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibListSelect->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MakeAlgorithmSimpleDialog", "Name", nullptr));
        pushButtonSelectButton->setText(QCoreApplication::translate("MakeAlgorithmSimpleDialog", "=>", nullptr));
        label_4->setText(QCoreApplication::translate("MakeAlgorithmSimpleDialog", "Selected", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetSelected->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MakeAlgorithmSimpleDialog", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetSelected->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MakeAlgorithmSimpleDialog", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetSelected->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MakeAlgorithmSimpleDialog", "Library Name", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("MakeAlgorithmSimpleDialog", "Update and close", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("MakeAlgorithmSimpleDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MakeAlgorithmSimpleDialog: public Ui_MakeAlgorithmSimpleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAKEALGORITHMSIMPLEDIALOG_H
