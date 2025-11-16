/********************************************************************************
** Form generated from reading UI file 'MakeAlgorithmUpperDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAKEALGORITHMUPPERDIALOG_H
#define UI_MAKEALGORITHMUPPERDIALOG_H

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

class Ui_MakeAlgorithmUpperDialog
{
public:
    QFrame *frame_4;
    QTableWidget *tableWidgetCrossedLayer;
    QLabel *label_8;
    QFrame *frame;
    QFrame *frame_2;
    QLabel *label_3;
    QComboBox *comboBoxLibTypeSelect;
    QTableWidget *tableWidgetLibListSelect;
    QFrame *frameLibFolderSelect;
    QPushButton *pushButtonSelectButton;
    QFrame *frame_3;
    QLabel *label_4;
    QTableWidget *tableWidgetSelected;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *MakeAlgorithmUpperDialog)
    {
        if (MakeAlgorithmUpperDialog->objectName().isEmpty())
            MakeAlgorithmUpperDialog->setObjectName("MakeAlgorithmUpperDialog");
        MakeAlgorithmUpperDialog->resize(1289, 610);
        frame_4 = new QFrame(MakeAlgorithmUpperDialog);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 10, 561, 541));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        tableWidgetCrossedLayer = new QTableWidget(frame_4);
        if (tableWidgetCrossedLayer->columnCount() < 5)
            tableWidgetCrossedLayer->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetCrossedLayer->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetCrossedLayer->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetCrossedLayer->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetCrossedLayer->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetCrossedLayer->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetCrossedLayer->setObjectName("tableWidgetCrossedLayer");
        tableWidgetCrossedLayer->setGeometry(QRect(0, 20, 551, 511));
        tableWidgetCrossedLayer->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetCrossedLayer->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_8 = new QLabel(frame_4);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 0, 551, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(MakeAlgorithmUpperDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(580, 10, 701, 541));
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
        tableWidgetLibListSelect = new QTableWidget(frame_2);
        if (tableWidgetLibListSelect->columnCount() < 2)
            tableWidgetLibListSelect->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetLibListSelect->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetLibListSelect->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        tableWidgetLibListSelect->setObjectName("tableWidgetLibListSelect");
        tableWidgetLibListSelect->setGeometry(QRect(10, 210, 241, 301));
        tableWidgetLibListSelect->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibListSelect->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolderSelect = new QFrame(frame_2);
        frameLibFolderSelect->setObjectName("frameLibFolderSelect");
        frameLibFolderSelect->setGeometry(QRect(10, 60, 241, 141));
        frameLibFolderSelect->setFrameShape(QFrame::StyledPanel);
        frameLibFolderSelect->setFrameShadow(QFrame::Sunken);
        pushButtonSelectButton = new QPushButton(frame);
        pushButtonSelectButton->setObjectName("pushButtonSelectButton");
        pushButtonSelectButton->setGeometry(QRect(280, 190, 51, 31));
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
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetSelected->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetSelected->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetSelected->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        tableWidgetSelected->setObjectName("tableWidgetSelected");
        tableWidgetSelected->setGeometry(QRect(10, 30, 331, 421));
        tableWidgetSelected->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetSelected->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonUpdate = new QPushButton(frame);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(480, 490, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon);
        pushButtonClose = new QPushButton(MakeAlgorithmUpperDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(1170, 560, 111, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon1);

        retranslateUi(MakeAlgorithmUpperDialog);

        QMetaObject::connectSlotsByName(MakeAlgorithmUpperDialog);
    } // setupUi

    void retranslateUi(QDialog *MakeAlgorithmUpperDialog)
    {
        MakeAlgorithmUpperDialog->setWindowTitle(QCoreApplication::translate("MakeAlgorithmUpperDialog", "Make algorithm upper items", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetCrossedLayer->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MakeAlgorithmUpperDialog", "L/C", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetCrossedLayer->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MakeAlgorithmUpperDialog", "Generation", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetCrossedLayer->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MakeAlgorithmUpperDialog", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetCrossedLayer->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MakeAlgorithmUpperDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetCrossedLayer->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MakeAlgorithmUpperDialog", "Lib", nullptr));
        label_8->setText(QCoreApplication::translate("MakeAlgorithmUpperDialog", "Upper layer/composite", nullptr));
        label_3->setText(QCoreApplication::translate("MakeAlgorithmUpperDialog", "Select library - source", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetLibListSelect->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MakeAlgorithmUpperDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetLibListSelect->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MakeAlgorithmUpperDialog", "Name", nullptr));
        pushButtonSelectButton->setText(QCoreApplication::translate("MakeAlgorithmUpperDialog", "=>", nullptr));
        label_4->setText(QCoreApplication::translate("MakeAlgorithmUpperDialog", "Selected", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetSelected->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MakeAlgorithmUpperDialog", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetSelected->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MakeAlgorithmUpperDialog", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetSelected->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MakeAlgorithmUpperDialog", "Library Name", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("MakeAlgorithmUpperDialog", "Update", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("MakeAlgorithmUpperDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MakeAlgorithmUpperDialog: public Ui_MakeAlgorithmUpperDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAKEALGORITHMUPPERDIALOG_H
