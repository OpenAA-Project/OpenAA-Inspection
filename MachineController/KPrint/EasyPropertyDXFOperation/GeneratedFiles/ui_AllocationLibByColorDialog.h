/********************************************************************************
** Form generated from reading UI file 'AllocationLibByColorDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALLOCATIONLIBBYCOLORDIALOG_H
#define UI_ALLOCATIONLIBBYCOLORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_AllocationLibByColorDialog
{
public:
    QTableWidget *tableWidget;
    QFrame *frame_5;
    QSlider *horizontalSliderEasyThreshold;
    QLabel *labelK_8;
    QLabel *labelEasyNumber;
    QLabel *label_LevelName;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonFromDXF;
    QFrame *frame;
    QFrame *frameLibFolder;
    QLabel *labelK_10;
    QTableWidget *tableWidgetLibList;
    QLabel *label;
    QPushButton *pushButtonGetBackAll;
    QPushButton *pushButtonSetFrom;
    QTableWidget *tableWidgetGeneratedLibList;
    QLabel *label_31;
    QPushButton *pushButtonGetBack;
    QPushButton *pushButtonSetFromAll;

    void setupUi(QDialog *AllocationLibByColorDialog)
    {
        if (AllocationLibByColorDialog->objectName().isEmpty())
            AllocationLibByColorDialog->setObjectName("AllocationLibByColorDialog");
        AllocationLibByColorDialog->resize(701, 665);
        tableWidget = new QTableWidget(AllocationLibByColorDialog);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 140, 161, 421));
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->verticalHeader()->setMinimumSectionSize(30);
        tableWidget->verticalHeader()->setDefaultSectionSize(30);
        frame_5 = new QFrame(AllocationLibByColorDialog);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(0, 0, 691, 131));
        frame_5->setFrameShape(QFrame::Panel);
        frame_5->setFrameShadow(QFrame::Sunken);
        horizontalSliderEasyThreshold = new QSlider(frame_5);
        horizontalSliderEasyThreshold->setObjectName("horizontalSliderEasyThreshold");
        horizontalSliderEasyThreshold->setGeometry(QRect(80, 50, 541, 41));
        horizontalSliderEasyThreshold->setMinimum(0);
        horizontalSliderEasyThreshold->setMaximum(4);
        horizontalSliderEasyThreshold->setPageStep(1);
        horizontalSliderEasyThreshold->setValue(2);
        horizontalSliderEasyThreshold->setOrientation(Qt::Horizontal);
        horizontalSliderEasyThreshold->setTickPosition(QSlider::TicksBelow);
        labelK_8 = new QLabel(frame_5);
        labelK_8->setObjectName("labelK_8");
        labelK_8->setGeometry(QRect(0, 0, 401, 51));
        QFont font;
        font.setPointSize(18);
        labelK_8->setFont(font);
        labelK_8->setAlignment(Qt::AlignCenter);
        labelEasyNumber = new QLabel(frame_5);
        labelEasyNumber->setObjectName("labelEasyNumber");
        labelEasyNumber->setGeometry(QRect(10, 50, 61, 41));
        labelEasyNumber->setFont(font);
        labelEasyNumber->setAlignment(Qt::AlignCenter);
        label_LevelName = new QLabel(frame_5);
        label_LevelName->setObjectName("label_LevelName");
        label_LevelName->setGeometry(QRect(20, 90, 601, 41));
        QFont font1;
        font1.setPointSize(12);
        label_LevelName->setFont(font1);
        label_LevelName->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(AllocationLibByColorDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(270, 600, 161, 51));
        pushButtonFromDXF = new QPushButton(AllocationLibByColorDialog);
        pushButtonFromDXF->setObjectName("pushButtonFromDXF");
        pushButtonFromDXF->setGeometry(QRect(10, 600, 151, 51));
        frame = new QFrame(AllocationLibByColorDialog);
        frame->setObjectName("frame");
        frame->setEnabled(true);
        frame->setGeometry(QRect(170, 140, 521, 451));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        frameLibFolder = new QFrame(frame);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 30, 221, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        labelK_10 = new QLabel(frameLibFolder);
        labelK_10->setObjectName("labelK_10");
        labelK_10->setGeometry(QRect(0, -20, 601, 41));
        labelK_10->setFont(font1);
        labelK_10->setAlignment(Qt::AlignCenter);
        tableWidgetLibList = new QTableWidget(frame);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 240, 221, 201));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 541, 31));
        label->setAlignment(Qt::AlignCenter);
        pushButtonGetBackAll = new QPushButton(frame);
        pushButtonGetBackAll->setObjectName("pushButtonGetBackAll");
        pushButtonGetBackAll->setGeometry(QRect(240, 370, 39, 23));
        pushButtonSetFrom = new QPushButton(frame);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(240, 260, 39, 23));
        tableWidgetGeneratedLibList = new QTableWidget(frame);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        tableWidgetGeneratedLibList->setObjectName("tableWidgetGeneratedLibList");
        tableWidgetGeneratedLibList->setGeometry(QRect(290, 240, 221, 201));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_31 = new QLabel(frame);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(290, 220, 221, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonGetBack = new QPushButton(frame);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(240, 290, 39, 23));
        pushButtonSetFromAll = new QPushButton(frame);
        pushButtonSetFromAll->setObjectName("pushButtonSetFromAll");
        pushButtonSetFromAll->setGeometry(QRect(240, 340, 39, 23));

        retranslateUi(AllocationLibByColorDialog);

        QMetaObject::connectSlotsByName(AllocationLibByColorDialog);
    } // setupUi

    void retranslateUi(QDialog *AllocationLibByColorDialog)
    {
        AllocationLibByColorDialog->setWindowTitle(QCoreApplication::translate("AllocationLibByColorDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AllocationLibByColorDialog", "\350\211\262", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AllocationLibByColorDialog", "\345\211\262\343\202\212\345\275\223\343\201\246", nullptr));
        labelK_8->setText(QCoreApplication::translate("AllocationLibByColorDialog", "\347\260\241\346\230\223\350\250\255\345\256\232", nullptr));
        labelEasyNumber->setText(QCoreApplication::translate("AllocationLibByColorDialog", "NN", nullptr));
        label_LevelName->setText(QCoreApplication::translate("AllocationLibByColorDialog", "XXXX", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AllocationLibByColorDialog", "\347\231\273\351\214\262/\351\226\211\343\201\230\343\202\213", nullptr));
        pushButtonFromDXF->setText(QCoreApplication::translate("AllocationLibByColorDialog", "DXF\343\201\213\343\202\211\350\252\255\343\201\277\350\276\274\343\201\277", nullptr));
        labelK_10->setText(QCoreApplication::translate("AllocationLibByColorDialog", "XXXX", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("AllocationLibByColorDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("AllocationLibByColorDialog", "Name", nullptr));
        label->setText(QCoreApplication::translate("AllocationLibByColorDialog", "\345\211\262\343\202\212\345\275\223\343\201\246\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("AllocationLibByColorDialog", "<<=", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("AllocationLibByColorDialog", "=>", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("AllocationLibByColorDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("AllocationLibByColorDialog", "Name", nullptr));
        label_31->setText(QCoreApplication::translate("AllocationLibByColorDialog", "\345\211\262\343\202\212\345\275\223\343\201\246\343\202\211\343\202\214\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("AllocationLibByColorDialog", "<=", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("AllocationLibByColorDialog", "=>>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AllocationLibByColorDialog: public Ui_AllocationLibByColorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALLOCATIONLIBBYCOLORDIALOG_H
