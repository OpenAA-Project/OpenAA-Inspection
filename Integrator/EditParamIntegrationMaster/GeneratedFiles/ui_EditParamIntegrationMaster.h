/********************************************************************************
** Form generated from reading UI file 'EditParamIntegrationMaster.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITPARAMINTEGRATIONMASTER_H
#define UI_EDITPARAMINTEGRATIONMASTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditParamIntegrationMasterClass
{
public:
    QWidget *centralWidget;
    QPushButton *SaveButton;
    QPushButton *UpdateDefaultButton;
    QPushButton *LoadButton;
    QPushButton *CancelButton;
    QLineEdit *lineEditFileName;
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *General;
    QFrame *frameGlobalParam;
    QWidget *Slave;
    QListWidget *listWidgetSlaveList;
    QPushButton *pushButtonSlaveListPlus;
    QLabel *label_2;
    QPushButton *pushButtonSlaveListMinus;
    QFrame *frame;
    QLabel *label_3;
    QSpinBox *spinBoxMachineCode;
    QLabel *label_4;
    QLineEdit *lineEditSlaveAddress;
    QLabel *label_5;
    QLineEdit *lineEditSharedFolder;
    QPushButton *pushButtonShooseSharedFolder;
    QPushButton *pushButtonImagePathPlus;
    QPushButton *pushButtonImagePathMinus;
    QLabel *label_7;
    QSpinBox *spinBoxMinAdditionalSec;
    QLabel *label_8;
    QSpinBox *spinBoxMaxAdditionalSec;
    QTableWidget *tableWidgetImageFolders;
    QLabel *label_9;
    QSpinBox *spinBoxOffsetXForSync;
    QSpinBox *spinBoxOffsetYForSync;
    QLabel *label_10;
    QLabel *label_11;
    QCheckBox *checkBoxDependent;
    QCheckBox *checkBoxSlaveIsInMaster;

    void setupUi(QMainWindow *EditParamIntegrationMasterClass)
    {
        if (EditParamIntegrationMasterClass->objectName().isEmpty())
            EditParamIntegrationMasterClass->setObjectName("EditParamIntegrationMasterClass");
        EditParamIntegrationMasterClass->resize(637, 618);
        centralWidget = new QWidget(EditParamIntegrationMasterClass);
        centralWidget->setObjectName("centralWidget");
        SaveButton = new QPushButton(centralWidget);
        SaveButton->setObjectName("SaveButton");
        SaveButton->setGeometry(QRect(20, 580, 101, 31));
        UpdateDefaultButton = new QPushButton(centralWidget);
        UpdateDefaultButton->setObjectName("UpdateDefaultButton");
        UpdateDefaultButton->setGeometry(QRect(150, 580, 101, 31));
        LoadButton = new QPushButton(centralWidget);
        LoadButton->setObjectName("LoadButton");
        LoadButton->setGeometry(QRect(290, 580, 91, 31));
        CancelButton = new QPushButton(centralWidget);
        CancelButton->setObjectName("CancelButton");
        CancelButton->setGeometry(QRect(530, 580, 101, 31));
        lineEditFileName = new QLineEdit(centralWidget);
        lineEditFileName->setObjectName("lineEditFileName");
        lineEditFileName->setGeometry(QRect(80, 0, 541, 20));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 71, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(10, 30, 611, 541));
        General = new QWidget();
        General->setObjectName("General");
        frameGlobalParam = new QFrame(General);
        frameGlobalParam->setObjectName("frameGlobalParam");
        frameGlobalParam->setGeometry(QRect(0, 0, 611, 431));
        frameGlobalParam->setFrameShape(QFrame::StyledPanel);
        frameGlobalParam->setFrameShadow(QFrame::Sunken);
        tabWidget->addTab(General, QString());
        Slave = new QWidget();
        Slave->setObjectName("Slave");
        listWidgetSlaveList = new QListWidget(Slave);
        listWidgetSlaveList->setObjectName("listWidgetSlaveList");
        listWidgetSlaveList->setGeometry(QRect(10, 30, 111, 421));
        listWidgetSlaveList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSlaveListPlus = new QPushButton(Slave);
        pushButtonSlaveListPlus->setObjectName("pushButtonSlaveListPlus");
        pushButtonSlaveListPlus->setGeometry(QRect(10, 460, 51, 34));
        label_2 = new QLabel(Slave);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 111, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        pushButtonSlaveListMinus = new QPushButton(Slave);
        pushButtonSlaveListMinus->setObjectName("pushButtonSlaveListMinus");
        pushButtonSlaveListMinus->setGeometry(QRect(70, 460, 51, 34));
        frame = new QFrame(Slave);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(140, 10, 461, 491));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 231, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        spinBoxMachineCode = new QSpinBox(frame);
        spinBoxMachineCode->setObjectName("spinBoxMachineCode");
        spinBoxMachineCode->setGeometry(QRect(250, 10, 81, 24));
        spinBoxMachineCode->setMaximum(99999);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 70, 231, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        lineEditSlaveAddress = new QLineEdit(frame);
        lineEditSlaveAddress->setObjectName("lineEditSlaveAddress");
        lineEditSlaveAddress->setGeometry(QRect(250, 70, 201, 24));
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 100, 121, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        lineEditSharedFolder = new QLineEdit(frame);
        lineEditSharedFolder->setObjectName("lineEditSharedFolder");
        lineEditSharedFolder->setGeometry(QRect(140, 100, 291, 24));
        pushButtonShooseSharedFolder = new QPushButton(frame);
        pushButtonShooseSharedFolder->setObjectName("pushButtonShooseSharedFolder");
        pushButtonShooseSharedFolder->setGeometry(QRect(430, 100, 24, 26));
        pushButtonImagePathPlus = new QPushButton(frame);
        pushButtonImagePathPlus->setObjectName("pushButtonImagePathPlus");
        pushButtonImagePathPlus->setGeometry(QRect(340, 450, 51, 34));
        pushButtonImagePathMinus = new QPushButton(frame);
        pushButtonImagePathMinus->setObjectName("pushButtonImagePathMinus");
        pushButtonImagePathMinus->setGeometry(QRect(400, 450, 51, 34));
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 130, 231, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        spinBoxMinAdditionalSec = new QSpinBox(frame);
        spinBoxMinAdditionalSec->setObjectName("spinBoxMinAdditionalSec");
        spinBoxMinAdditionalSec->setGeometry(QRect(250, 130, 81, 24));
        spinBoxMinAdditionalSec->setMaximum(99999999);
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 154, 231, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter);
        spinBoxMaxAdditionalSec = new QSpinBox(frame);
        spinBoxMaxAdditionalSec->setObjectName("spinBoxMaxAdditionalSec");
        spinBoxMaxAdditionalSec->setGeometry(QRect(250, 154, 81, 24));
        spinBoxMaxAdditionalSec->setMaximum(99999999);
        tableWidgetImageFolders = new QTableWidget(frame);
        if (tableWidgetImageFolders->columnCount() < 1)
            tableWidgetImageFolders->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetImageFolders->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidgetImageFolders->setObjectName("tableWidgetImageFolders");
        tableWidgetImageFolders->setGeometry(QRect(10, 230, 441, 211));
        label_9 = new QLabel(frame);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 190, 231, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter);
        spinBoxOffsetXForSync = new QSpinBox(frame);
        spinBoxOffsetXForSync->setObjectName("spinBoxOffsetXForSync");
        spinBoxOffsetXForSync->setGeometry(QRect(270, 190, 71, 24));
        spinBoxOffsetXForSync->setMaximum(99999999);
        spinBoxOffsetYForSync = new QSpinBox(frame);
        spinBoxOffsetYForSync->setObjectName("spinBoxOffsetYForSync");
        spinBoxOffsetYForSync->setGeometry(QRect(370, 190, 81, 24));
        spinBoxOffsetYForSync->setMaximum(99999999);
        label_10 = new QLabel(frame);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(250, 190, 16, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter);
        label_11 = new QLabel(frame);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(350, 190, 16, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter);
        checkBoxDependent = new QCheckBox(frame);
        checkBoxDependent->setObjectName("checkBoxDependent");
        checkBoxDependent->setGeometry(QRect(250, 40, 161, 22));
        checkBoxSlaveIsInMaster = new QCheckBox(frame);
        checkBoxSlaveIsInMaster->setObjectName("checkBoxSlaveIsInMaster");
        checkBoxSlaveIsInMaster->setGeometry(QRect(10, 40, 171, 22));
        tabWidget->addTab(Slave, QString());
        EditParamIntegrationMasterClass->setCentralWidget(centralWidget);

        retranslateUi(EditParamIntegrationMasterClass);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(EditParamIntegrationMasterClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditParamIntegrationMasterClass)
    {
        EditParamIntegrationMasterClass->setWindowTitle(QCoreApplication::translate("EditParamIntegrationMasterClass", "EditParamIntegrationMaster", nullptr));
        SaveButton->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "Save", nullptr));
        UpdateDefaultButton->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "Overwrite", nullptr));
        LoadButton->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "Load", nullptr));
        CancelButton->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "Close", nullptr));
        label->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "File Name", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(General), QCoreApplication::translate("EditParamIntegrationMasterClass", "General", nullptr));
        pushButtonSlaveListPlus->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "+", nullptr));
        label_2->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "Slave", nullptr));
        pushButtonSlaveListMinus->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "-", nullptr));
        label_3->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "Slave machine code", nullptr));
        label_4->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "Slave IP address (host name)", nullptr));
        label_5->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "Shared folder", nullptr));
        pushButtonShooseSharedFolder->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "...", nullptr));
        pushButtonImagePathPlus->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "+", nullptr));
        pushButtonImagePathMinus->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "-", nullptr));
        label_7->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "Minimum additional second", nullptr));
        label_8->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "Maximum additional second", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetImageFolders->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "ImagePath", nullptr));
        label_9->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "Offset for sync", nullptr));
        label_10->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "X", nullptr));
        label_11->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "Y", nullptr));
        checkBoxDependent->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "Dependent", nullptr));
        checkBoxSlaveIsInMaster->setText(QCoreApplication::translate("EditParamIntegrationMasterClass", "Slave is In Master", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Slave), QCoreApplication::translate("EditParamIntegrationMasterClass", "Slave", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditParamIntegrationMasterClass: public Ui_EditParamIntegrationMasterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITPARAMINTEGRATIONMASTER_H
