/********************************************************************************
** Form generated from reading UI file 'ManageByLot.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGEBYLOT_H
#define UI_MANAGEBYLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManageByLot
{
public:
    QGridLayout *gridLayout_4;
    QFrame *frame;
    QGridLayout *gridLayout;
    QFrame *frameCategory;
    QGridLayout *gridLayout_7;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_7;
    QLabel *labelTopView;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_2;
    QFrame *frameGrid;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonClose;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_7;
    QTableWidget *tableWidgetInspection;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButtonDeleteLines;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QCheckBox *cbShowInspectFirstEndTime;
    QCheckBox *cbShowInspectionCount;
    QTableWidget *tableWidgetLot;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_5;
    QGridLayout *gridLayout_2;
    QPushButton *pushButtonDeleteLot;
    QPushButton *pushButtonDeleteAll;
    QPushButton *pushButtonBackup;
    QPushButton *pushButtonRestore;
    QPushButton *pushButtonBackupOnly;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEditState;
    QSpacerItem *horizontalSpacer_6;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_7;
    QFrame *frame_3;
    QGridLayout *gridLayout_6;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_5;
    QSpinBox *spinBoxSearchID;
    QPushButton *pushButtonStartSearchByID;
    QFrame *frame_2;
    QGridLayout *gridLayout_5;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEditSearchName;
    QPushButton *pushButtonStartSearchByName;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_10;
    QVBoxLayout *verticalLayout;
    QLabel *label_6;
    QScrollArea *scrollAreaMachine;
    QWidget *scrollAreaWidgetContents;
    QSpacerItem *horizontalSpacer_9;

    void setupUi(QDialog *ManageByLot)
    {
        if (ManageByLot->objectName().isEmpty())
            ManageByLot->setObjectName("ManageByLot");
        ManageByLot->resize(1191, 971);
        gridLayout_4 = new QGridLayout(ManageByLot);
        gridLayout_4->setObjectName("gridLayout_4");
        frame = new QFrame(ManageByLot);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(450, 0));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName("gridLayout");
        frameCategory = new QFrame(frame);
        frameCategory->setObjectName("frameCategory");
        sizePolicy.setHeightForWidth(frameCategory->sizePolicy().hasHeightForWidth());
        frameCategory->setSizePolicy(sizePolicy);
        frameCategory->setFrameShape(QFrame::StyledPanel);
        frameCategory->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frameCategory, 0, 0, 1, 1);


        gridLayout_4->addWidget(frame, 0, 0, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(4);
        gridLayout_7->setObjectName("gridLayout_7");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_7->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_7, 1, 0, 1, 1);

        labelTopView = new QLabel(ManageByLot);
        labelTopView->setObjectName("labelTopView");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelTopView->sizePolicy().hasHeightForWidth());
        labelTopView->setSizePolicy(sizePolicy1);
        labelTopView->setMinimumSize(QSize(257, 257));
        labelTopView->setMaximumSize(QSize(257, 257));
        labelTopView->setFrameShape(QFrame::Panel);
        labelTopView->setFrameShadow(QFrame::Sunken);

        gridLayout_7->addWidget(labelTopView, 1, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_8, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_7->addItem(verticalSpacer_2, 2, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_7, 0, 2, 2, 1);

        frameGrid = new QFrame(ManageByLot);
        frameGrid->setObjectName("frameGrid");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frameGrid->sizePolicy().hasHeightForWidth());
        frameGrid->setSizePolicy(sizePolicy2);
        frameGrid->setMinimumSize(QSize(0, 200));
        frameGrid->setFrameShape(QFrame::StyledPanel);
        frameGrid->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(frameGrid, 2, 0, 1, 3);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(208, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButtonClose = new QPushButton(ManageByLot);
        pushButtonClose->setObjectName("pushButtonClose");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButtonClose->sizePolicy().hasHeightForWidth());
        pushButtonClose->setSizePolicy(sizePolicy3);
        pushButtonClose->setMinimumSize(QSize(80, 40));
        pushButtonClose->setAutoRepeat(false);

        horizontalLayout_2->addWidget(pushButtonClose);


        gridLayout_3->addLayout(horizontalLayout_2, 1, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_7 = new QLabel(ManageByLot);
        label_7->setObjectName("label_7");
        label_7->setMaximumSize(QSize(16777215, 16777215));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(label_7);

        tableWidgetInspection = new QTableWidget(ManageByLot);
        if (tableWidgetInspection->columnCount() < 3)
            tableWidgetInspection->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetInspection->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetInspection->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetInspection->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetInspection->setObjectName("tableWidgetInspection");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(tableWidgetInspection->sizePolicy().hasHeightForWidth());
        tableWidgetInspection->setSizePolicy(sizePolicy4);
        tableWidgetInspection->setMinimumSize(QSize(350, 0));
        tableWidgetInspection->setMaximumSize(QSize(16777215, 16777215));
        tableWidgetInspection->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableWidgetInspection->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetInspection->setTextElideMode(Qt::ElideMiddle);
        tableWidgetInspection->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_2->addWidget(tableWidgetInspection);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        pushButtonDeleteLines = new QPushButton(ManageByLot);
        pushButtonDeleteLines->setObjectName("pushButtonDeleteLines");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pushButtonDeleteLines->sizePolicy().hasHeightForWidth());
        pushButtonDeleteLines->setSizePolicy(sizePolicy5);
        pushButtonDeleteLines->setMinimumSize(QSize(200, 40));

        horizontalLayout_8->addWidget(pushButtonDeleteLines);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_8);


        gridLayout_3->addLayout(verticalLayout_2, 0, 1, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_4 = new QLabel(ManageByLot);
        label_4->setObjectName("label_4");
        sizePolicy5.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy5);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_3->addWidget(label_4);

        cbShowInspectFirstEndTime = new QCheckBox(ManageByLot);
        cbShowInspectFirstEndTime->setObjectName("cbShowInspectFirstEndTime");

        verticalLayout_3->addWidget(cbShowInspectFirstEndTime);

        cbShowInspectionCount = new QCheckBox(ManageByLot);
        cbShowInspectionCount->setObjectName("cbShowInspectionCount");

        verticalLayout_3->addWidget(cbShowInspectionCount);

        tableWidgetLot = new QTableWidget(ManageByLot);
        if (tableWidgetLot->columnCount() < 5)
            tableWidgetLot->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLot->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetLot->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetLot->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetLot->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetLot->setHorizontalHeaderItem(4, __qtablewidgetitem7);
        tableWidgetLot->setObjectName("tableWidgetLot");
        sizePolicy.setHeightForWidth(tableWidgetLot->sizePolicy().hasHeightForWidth());
        tableWidgetLot->setSizePolicy(sizePolicy);
        tableWidgetLot->setMinimumSize(QSize(0, 0));
        tableWidgetLot->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableWidgetLot->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetLot->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidgetLot->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_3->addWidget(tableWidgetLot);

        verticalLayout_3->setStretch(3, 2);

        verticalLayout_5->addLayout(verticalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        pushButtonDeleteLot = new QPushButton(ManageByLot);
        pushButtonDeleteLot->setObjectName("pushButtonDeleteLot");
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(pushButtonDeleteLot->sizePolicy().hasHeightForWidth());
        pushButtonDeleteLot->setSizePolicy(sizePolicy6);
        pushButtonDeleteLot->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(pushButtonDeleteLot, 0, 1, 1, 1);

        pushButtonDeleteAll = new QPushButton(ManageByLot);
        pushButtonDeleteAll->setObjectName("pushButtonDeleteAll");
        sizePolicy6.setHeightForWidth(pushButtonDeleteAll->sizePolicy().hasHeightForWidth());
        pushButtonDeleteAll->setSizePolicy(sizePolicy6);
        pushButtonDeleteAll->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(pushButtonDeleteAll, 0, 2, 1, 1);

        pushButtonBackup = new QPushButton(ManageByLot);
        pushButtonBackup->setObjectName("pushButtonBackup");
        sizePolicy6.setHeightForWidth(pushButtonBackup->sizePolicy().hasHeightForWidth());
        pushButtonBackup->setSizePolicy(sizePolicy6);
        pushButtonBackup->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(pushButtonBackup, 1, 1, 1, 1);

        pushButtonRestore = new QPushButton(ManageByLot);
        pushButtonRestore->setObjectName("pushButtonRestore");
        sizePolicy6.setHeightForWidth(pushButtonRestore->sizePolicy().hasHeightForWidth());
        pushButtonRestore->setSizePolicy(sizePolicy6);
        pushButtonRestore->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(pushButtonRestore, 1, 2, 1, 1);

        pushButtonBackupOnly = new QPushButton(ManageByLot);
        pushButtonBackupOnly->setObjectName("pushButtonBackupOnly");
        pushButtonBackupOnly->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(pushButtonBackupOnly, 1, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout_5->addLayout(horizontalLayout);


        gridLayout_3->addLayout(verticalLayout_5, 0, 0, 2, 1);

        gridLayout_3->setColumnStretch(0, 1);
        gridLayout_3->setColumnStretch(1, 1);

        gridLayout_4->addLayout(gridLayout_3, 4, 0, 1, 3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        lineEditState = new QLineEdit(ManageByLot);
        lineEditState->setObjectName("lineEditState");
        QSizePolicy sizePolicy7(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(lineEditState->sizePolicy().hasHeightForWidth());
        lineEditState->setSizePolicy(sizePolicy7);
        lineEditState->setMinimumSize(QSize(400, 0));
        lineEditState->setMaximumSize(QSize(16777215, 16777215));
        lineEditState->setReadOnly(true);

        horizontalLayout_3->addWidget(lineEditState);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        progressBar = new QProgressBar(ManageByLot);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(0);

        horizontalLayout_3->addWidget(progressBar);


        gridLayout_4->addLayout(horizontalLayout_3, 3, 0, 1, 3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(4);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        frame_3 = new QFrame(ManageByLot);
        frame_3->setObjectName("frame_3");
        sizePolicy7.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy7);
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        gridLayout_6 = new QGridLayout(frame_3);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(4, 4, 4, 0);
        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        QSizePolicy sizePolicy8(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy8);
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


        horizontalLayout_7->addWidget(frame_3);

        frame_2 = new QFrame(ManageByLot);
        frame_2->setObjectName("frame_2");
        sizePolicy8.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy8);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        gridLayout_5 = new QGridLayout(frame_2);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(4, 4, 4, 0);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        sizePolicy8.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy8);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_3, 0, 0, 1, 1);

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


        horizontalLayout_7->addWidget(frame_2);


        gridLayout_4->addLayout(horizontalLayout_7, 1, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(4);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_10);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_6 = new QLabel(ManageByLot);
        label_6->setObjectName("label_6");
        QSizePolicy sizePolicy9(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy9);
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(label_6);

        scrollAreaMachine = new QScrollArea(ManageByLot);
        scrollAreaMachine->setObjectName("scrollAreaMachine");
        QSizePolicy sizePolicy10(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(scrollAreaMachine->sizePolicy().hasHeightForWidth());
        scrollAreaMachine->setSizePolicy(sizePolicy10);
        scrollAreaMachine->setMinimumSize(QSize(150, 0));
        scrollAreaMachine->setMaximumSize(QSize(150, 200000));
        scrollAreaMachine->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollAreaMachine->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollAreaMachine->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 146, 320));
        scrollAreaMachine->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollAreaMachine);


        horizontalLayout_6->addLayout(verticalLayout);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);


        gridLayout_4->addLayout(horizontalLayout_6, 0, 1, 2, 1);


        retranslateUi(ManageByLot);

        QMetaObject::connectSlotsByName(ManageByLot);
    } // setupUi

    void retranslateUi(QDialog *ManageByLot)
    {
        ManageByLot->setWindowTitle(QCoreApplication::translate("ManageByLot", "ResultDataManagement by Lot", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ManageByLot", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_7->setText(QCoreApplication::translate("ManageByLot", "\346\244\234\346\237\273\343\203\207\343\203\274\343\202\277", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetInspection->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ManageByLot", "\346\244\234\346\237\273ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetInspection->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ManageByLot", "\346\227\245\346\231\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetInspection->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ManageByLot", "\346\244\234\346\237\273\347\265\220\346\236\234", nullptr));
        pushButtonDeleteLines->setText(QCoreApplication::translate("ManageByLot", "\351\201\270\346\212\236\350\241\214\343\201\256\345\211\212\351\231\244", nullptr));
        label_4->setText(QCoreApplication::translate("ManageByLot", "\346\244\234\346\237\273\343\203\255\343\203\203\343\203\210", nullptr));
        cbShowInspectFirstEndTime->setText(QCoreApplication::translate("ManageByLot", "\345\210\235\345\233\236\343\201\250\346\234\200\347\265\202\343\201\256\346\244\234\346\237\273\346\231\202\345\210\273\343\202\222\350\241\250\347\244\272\343\201\231\343\202\213", nullptr));
        cbShowInspectionCount->setText(QCoreApplication::translate("ManageByLot", "Show Inspection Count", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLot->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ManageByLot", "\343\203\255\343\203\203\343\203\210\343\203\225\343\202\241\343\202\244\343\203\253\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetLot->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ManageByLot", "\343\203\255\343\203\203\343\203\210\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetLot->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ManageByLot", "\345\210\235\345\233\236\346\244\234\346\237\273\346\231\202\345\210\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetLot->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ManageByLot", "\346\234\200\347\265\202\346\244\234\346\237\273\346\231\202\345\210\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetLot->horizontalHeaderItem(4);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("ManageByLot", "\346\244\234\346\237\273\345\233\236\346\225\260", nullptr));
        pushButtonDeleteLot->setText(QCoreApplication::translate("ManageByLot", "\351\201\270\346\212\236\343\203\255\343\203\203\343\203\210\343\201\256\345\211\212\351\231\244", nullptr));
        pushButtonDeleteAll->setText(QCoreApplication::translate("ManageByLot", "\345\205\250\345\211\212\351\231\244", nullptr));
        pushButtonBackup->setText(QCoreApplication::translate("ManageByLot", "\351\201\270\346\212\236\343\203\255\343\203\203\343\203\210\343\201\256\343\203\225\343\202\241\343\202\244\343\203\253\343\201\270\343\203\220\343\203\203\343\202\257\343\202\242\343\203\203\343\203\227\357\274\217\345\211\212\351\231\244", nullptr));
        pushButtonRestore->setText(QCoreApplication::translate("ManageByLot", "\343\203\220\343\203\203\343\202\257\343\202\242\343\203\203\343\203\227\343\203\225\343\202\241\343\202\244\343\203\253\343\201\213\343\202\211\343\203\252\343\202\271\343\203\210\343\202\242", nullptr));
        pushButtonBackupOnly->setText(QCoreApplication::translate("ManageByLot", "Only Backup", nullptr));
        label_5->setText(QCoreApplication::translate("ManageByLot", "ID\346\244\234\347\264\242", nullptr));
        pushButtonStartSearchByID->setText(QCoreApplication::translate("ManageByLot", "\346\244\234\347\264\242", nullptr));
        label_3->setText(QCoreApplication::translate("ManageByLot", "\345\220\215\347\247\260\346\244\234\347\264\242", nullptr));
        pushButtonStartSearchByName->setText(QCoreApplication::translate("ManageByLot", "\346\244\234\347\264\242", nullptr));
        label_6->setText(QCoreApplication::translate("ManageByLot", "Machine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManageByLot: public Ui_ManageByLot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGEBYLOT_H
