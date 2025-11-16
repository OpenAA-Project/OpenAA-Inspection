/********************************************************************************
** Form generated from reading UI file 'MakeMasterReport.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAKEMASTERREPORT_H
#define UI_MAKEMASTERREPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MakeMasterReportClass
{
public:
    QWidget *centralWidget;
    QFrame *frameDatabase;
    QPushButton *pushButtonOpenDatabase;
    QLabel *label;
    QLineEdit *lineEditDBFileName;
    QLabel *label_2;
    QSpinBox *spinBoxPortNo;
    QLineEdit *lineEditHostName;
    QLabel *label_3;
    QPushButton *pushButtonClose;
    QFrame *frameMasterData;
    QFrame *frame_3;
    QGridLayout *gridLayout_6;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_5;
    QSpinBox *spinBoxSearchID;
    QPushButton *pushButtonStartSearchByID;
    QLabel *labelTopView;
    QFrame *frameGrid;
    QLineEdit *lineEditState;
    QFrame *frame;
    QGridLayout *gridLayout;
    QFrame *frameCategory;
    QFrame *frame_2;
    QGridLayout *gridLayout_5;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEditSearchName;
    QPushButton *pushButtonStartSearchByName;
    QTableWidget *tableWidgetAlgorithm;
    QLabel *label_6;
    QPushButton *pushButtonSelect;

    void setupUi(QMainWindow *MakeMasterReportClass)
    {
        if (MakeMasterReportClass->objectName().isEmpty())
            MakeMasterReportClass->setObjectName("MakeMasterReportClass");
        MakeMasterReportClass->resize(1224, 828);
        centralWidget = new QWidget(MakeMasterReportClass);
        centralWidget->setObjectName("centralWidget");
        frameDatabase = new QFrame(centralWidget);
        frameDatabase->setObjectName("frameDatabase");
        frameDatabase->setGeometry(QRect(20, 10, 821, 81));
        frameDatabase->setFrameShape(QFrame::StyledPanel);
        frameDatabase->setFrameShadow(QFrame::Sunken);
        pushButtonOpenDatabase = new QPushButton(frameDatabase);
        pushButtonOpenDatabase->setObjectName("pushButtonOpenDatabase");
        pushButtonOpenDatabase->setGeometry(QRect(640, 10, 161, 61));
        label = new QLabel(frameDatabase);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        lineEditDBFileName = new QLineEdit(frameDatabase);
        lineEditDBFileName->setObjectName("lineEditDBFileName");
        lineEditDBFileName->setGeometry(QRect(200, 50, 421, 20));
        label_2 = new QLabel(frameDatabase);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 50, 181, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        spinBoxPortNo = new QSpinBox(frameDatabase);
        spinBoxPortNo->setObjectName("spinBoxPortNo");
        spinBoxPortNo->setGeometry(QRect(200, 30, 91, 22));
        spinBoxPortNo->setMaximum(65536);
        spinBoxPortNo->setValue(3051);
        lineEditHostName = new QLineEdit(frameDatabase);
        lineEditHostName->setObjectName("lineEditHostName");
        lineEditHostName->setGeometry(QRect(200, 10, 421, 20));
        label_3 = new QLabel(frameDatabase);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 30, 181, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        pushButtonClose = new QPushButton(centralWidget);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(970, 20, 141, 61));
        frameMasterData = new QFrame(centralWidget);
        frameMasterData->setObjectName("frameMasterData");
        frameMasterData->setGeometry(QRect(20, 100, 1191, 681));
        frameMasterData->setFrameShape(QFrame::StyledPanel);
        frameMasterData->setFrameShadow(QFrame::Sunken);
        frame_3 = new QFrame(frameMasterData);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(40, 340, 181, 51));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy);
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        gridLayout_6 = new QGridLayout(frame_3);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(4, 4, 4, 0);
        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_5, 0, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(4);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        spinBoxSearchID = new QSpinBox(frame_3);
        spinBoxSearchID->setObjectName("spinBoxSearchID");
        spinBoxSearchID->setMaximum(99999999);

        horizontalLayout_5->addWidget(spinBoxSearchID);

        pushButtonStartSearchByID = new QPushButton(frame_3);
        pushButtonStartSearchByID->setObjectName("pushButtonStartSearchByID");

        horizontalLayout_5->addWidget(pushButtonStartSearchByID);


        gridLayout_6->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        labelTopView = new QLabel(frameMasterData);
        labelTopView->setObjectName("labelTopView");
        labelTopView->setGeometry(QRect(470, 70, 257, 257));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelTopView->sizePolicy().hasHeightForWidth());
        labelTopView->setSizePolicy(sizePolicy2);
        labelTopView->setMinimumSize(QSize(257, 257));
        labelTopView->setMaximumSize(QSize(257, 257));
        labelTopView->setFrameShape(QFrame::Panel);
        labelTopView->setFrameShadow(QFrame::Sunken);
        frameGrid = new QFrame(frameMasterData);
        frameGrid->setObjectName("frameGrid");
        frameGrid->setGeometry(QRect(10, 400, 1173, 271));
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(frameGrid->sizePolicy().hasHeightForWidth());
        frameGrid->setSizePolicy(sizePolicy3);
        frameGrid->setMinimumSize(QSize(0, 200));
        frameGrid->setFrameShape(QFrame::StyledPanel);
        frameGrid->setFrameShadow(QFrame::Sunken);
        lineEditState = new QLineEdit(frameMasterData);
        lineEditState->setObjectName("lineEditState");
        lineEditState->setGeometry(QRect(760, 370, 400, 20));
        sizePolicy.setHeightForWidth(lineEditState->sizePolicy().hasHeightForWidth());
        lineEditState->setSizePolicy(sizePolicy);
        lineEditState->setMinimumSize(QSize(400, 0));
        lineEditState->setMaximumSize(QSize(16777215, 16777215));
        lineEditState->setReadOnly(true);
        frame = new QFrame(frameMasterData);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 450, 326));
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy4);
        frame->setMinimumSize(QSize(450, 0));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        frameCategory = new QFrame(frame);
        frameCategory->setObjectName("frameCategory");
        sizePolicy4.setHeightForWidth(frameCategory->sizePolicy().hasHeightForWidth());
        frameCategory->setSizePolicy(sizePolicy4);
        frameCategory->setFrameShape(QFrame::StyledPanel);
        frameCategory->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frameCategory, 0, 0, 1, 1);

        frame_2 = new QFrame(frameMasterData);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(220, 340, 499, 51));
        sizePolicy1.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy1);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        gridLayout_5 = new QGridLayout(frame_2);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(4, 4, 4, 0);
        label_4 = new QLabel(frame_2);
        label_4->setObjectName("label_4");
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_4, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(4);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        lineEditSearchName = new QLineEdit(frame_2);
        lineEditSearchName->setObjectName("lineEditSearchName");

        horizontalLayout_4->addWidget(lineEditSearchName);

        pushButtonStartSearchByName = new QPushButton(frame_2);
        pushButtonStartSearchByName->setObjectName("pushButtonStartSearchByName");

        horizontalLayout_4->addWidget(pushButtonStartSearchByName);


        gridLayout_5->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        tableWidgetAlgorithm = new QTableWidget(frameMasterData);
        if (tableWidgetAlgorithm->columnCount() < 3)
            tableWidgetAlgorithm->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetAlgorithm->setObjectName("tableWidgetAlgorithm");
        tableWidgetAlgorithm->setGeometry(QRect(740, 40, 431, 291));
        tableWidgetAlgorithm->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAlgorithm->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_6 = new QLabel(frameMasterData);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(740, 20, 431, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        pushButtonSelect = new QPushButton(centralWidget);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(590, 790, 121, 31));
        MakeMasterReportClass->setCentralWidget(centralWidget);

        retranslateUi(MakeMasterReportClass);

        QMetaObject::connectSlotsByName(MakeMasterReportClass);
    } // setupUi

    void retranslateUi(QMainWindow *MakeMasterReportClass)
    {
        MakeMasterReportClass->setWindowTitle(QCoreApplication::translate("MakeMasterReportClass", "MakeMasterReport", nullptr));
        pushButtonOpenDatabase->setText(QCoreApplication::translate("MakeMasterReportClass", "Open database", nullptr));
        label->setText(QCoreApplication::translate("MakeMasterReportClass", "Host name or IP address", nullptr));
        label_2->setText(QCoreApplication::translate("MakeMasterReportClass", "File path and name", nullptr));
        label_3->setText(QCoreApplication::translate("MakeMasterReportClass", "Port number", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("MakeMasterReportClass", "Close", nullptr));
        label_5->setText(QCoreApplication::translate("MakeMasterReportClass", "ID\346\244\234\347\264\242", nullptr));
        pushButtonStartSearchByID->setText(QCoreApplication::translate("MakeMasterReportClass", "\346\244\234\347\264\242", nullptr));
        label_4->setText(QCoreApplication::translate("MakeMasterReportClass", "\345\220\215\347\247\260\346\244\234\347\264\242", nullptr));
        pushButtonStartSearchByName->setText(QCoreApplication::translate("MakeMasterReportClass", "\346\244\234\347\264\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetAlgorithm->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MakeMasterReportClass", "Root", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetAlgorithm->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MakeMasterReportClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetAlgorithm->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MakeMasterReportClass", "Explain", nullptr));
        label_6->setText(QCoreApplication::translate("MakeMasterReportClass", "Loaded algorithm", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("MakeMasterReportClass", "Select", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MakeMasterReportClass: public Ui_MakeMasterReportClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAKEMASTERREPORT_H
