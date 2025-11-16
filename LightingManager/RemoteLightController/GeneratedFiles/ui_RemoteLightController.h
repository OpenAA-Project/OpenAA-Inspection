/********************************************************************************
** Form generated from reading UI file 'RemoteLightController.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOTELIGHTCONTROLLER_H
#define UI_REMOTELIGHTCONTROLLER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RemoteLightControllerClass
{
public:
    QWidget *centralWidget;
    QFrame *frameButtons;
    QFrame *frameController;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonSetting;
    QPushButton *pushButtonSaveAll;
    QPushButton *pushButtonLoadAll;
    QToolButton *toolButtonOnOff;
    QPushButton *pushButtonUpdate;
    QTableWidget *tableWidgetLight;
    QToolButton *toolButtonManagementMode;
    QFrame *frameOperation;
    QLineEdit *lineEditRemark;
    QLabel *label_2;
    QLineEdit *lineEditID;
    QLabel *label;
    QLineEdit *lineEditName;
    QLabel *label_3;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonUpdate_2;
    QPushButton *pushButtonCreateNew;
    QLabel *label_4;

    void setupUi(QMainWindow *RemoteLightControllerClass)
    {
        if (RemoteLightControllerClass->objectName().isEmpty())
            RemoteLightControllerClass->setObjectName("RemoteLightControllerClass");
        RemoteLightControllerClass->resize(731, 496);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RemoteLightControllerClass->sizePolicy().hasHeightForWidth());
        RemoteLightControllerClass->setSizePolicy(sizePolicy);
        RemoteLightControllerClass->setMinimumSize(QSize(731, 0));
        RemoteLightControllerClass->setMaximumSize(QSize(731, 16777215));
        centralWidget = new QWidget(RemoteLightControllerClass);
        centralWidget->setObjectName("centralWidget");
        frameButtons = new QFrame(centralWidget);
        frameButtons->setObjectName("frameButtons");
        frameButtons->setGeometry(QRect(480, 50, 251, 331));
        frameButtons->setFrameShape(QFrame::StyledPanel);
        frameButtons->setFrameShadow(QFrame::Raised);
        frameController = new QFrame(centralWidget);
        frameController->setObjectName("frameController");
        frameController->setGeometry(QRect(480, 380, 251, 111));
        frameController->setFrameShape(QFrame::StyledPanel);
        frameController->setFrameShadow(QFrame::Raised);
        pushButtonClose = new QPushButton(frameController);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(160, 50, 81, 48));
        pushButtonSetting = new QPushButton(frameController);
        pushButtonSetting->setObjectName("pushButtonSetting");
        pushButtonSetting->setGeometry(QRect(160, 10, 81, 31));
        pushButtonSaveAll = new QPushButton(frameController);
        pushButtonSaveAll->setObjectName("pushButtonSaveAll");
        pushButtonSaveAll->setGeometry(QRect(300, 70, 81, 28));
        pushButtonLoadAll = new QPushButton(frameController);
        pushButtonLoadAll->setObjectName("pushButtonLoadAll");
        pushButtonLoadAll->setGeometry(QRect(300, 10, 81, 28));
        toolButtonOnOff = new QToolButton(frameController);
        toolButtonOnOff->setObjectName("toolButtonOnOff");
        toolButtonOnOff->setGeometry(QRect(10, 20, 141, 61));
        toolButtonOnOff->setCheckable(true);
        toolButtonOnOff->setChecked(true);
        pushButtonUpdate = new QPushButton(frameController);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(300, 40, 81, 28));
        tableWidgetLight = new QTableWidget(centralWidget);
        if (tableWidgetLight->columnCount() < 3)
            tableWidgetLight->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLight->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLight->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLight->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetLight->setObjectName("tableWidgetLight");
        tableWidgetLight->setGeometry(QRect(0, 0, 471, 291));
        tableWidgetLight->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLight->setSelectionBehavior(QAbstractItemView::SelectRows);
        toolButtonManagementMode = new QToolButton(centralWidget);
        toolButtonManagementMode->setObjectName("toolButtonManagementMode");
        toolButtonManagementMode->setGeometry(QRect(480, 10, 241, 31));
        toolButtonManagementMode->setCheckable(true);
        frameOperation = new QFrame(centralWidget);
        frameOperation->setObjectName("frameOperation");
        frameOperation->setGeometry(QRect(0, 340, 471, 151));
        frameOperation->setFrameShape(QFrame::StyledPanel);
        frameOperation->setFrameShadow(QFrame::Raised);
        lineEditRemark = new QLineEdit(frameOperation);
        lineEditRemark->setObjectName("lineEditRemark");
        lineEditRemark->setGeometry(QRect(230, 80, 231, 20));
        label_2 = new QLabel(frameOperation);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 60, 211, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        lineEditID = new QLineEdit(frameOperation);
        lineEditID->setObjectName("lineEditID");
        lineEditID->setGeometry(QRect(10, 30, 91, 20));
        label = new QLabel(frameOperation);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 91, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        lineEditName = new QLineEdit(frameOperation);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(10, 80, 211, 20));
        label_3 = new QLabel(frameOperation);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(230, 60, 231, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        pushButtonDelete = new QPushButton(frameOperation);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(350, 110, 111, 31));
        pushButtonUpdate_2 = new QPushButton(frameOperation);
        pushButtonUpdate_2->setObjectName("pushButtonUpdate_2");
        pushButtonUpdate_2->setGeometry(QRect(170, 110, 141, 31));
        pushButtonCreateNew = new QPushButton(frameOperation);
        pushButtonCreateNew->setObjectName("pushButtonCreateNew");
        pushButtonCreateNew->setGeometry(QRect(10, 110, 121, 31));
        label_4 = new QLabel(frameOperation);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(120, 30, 341, 16));
        RemoteLightControllerClass->setCentralWidget(centralWidget);

        retranslateUi(RemoteLightControllerClass);

        QMetaObject::connectSlotsByName(RemoteLightControllerClass);
    } // setupUi

    void retranslateUi(QMainWindow *RemoteLightControllerClass)
    {
        RemoteLightControllerClass->setWindowTitle(QCoreApplication::translate("RemoteLightControllerClass", "RemoteLightController", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("RemoteLightControllerClass", "Close", nullptr));
        pushButtonSetting->setText(QCoreApplication::translate("RemoteLightControllerClass", "Setting", nullptr));
        pushButtonSaveAll->setText(QCoreApplication::translate("RemoteLightControllerClass", "Save all", nullptr));
        pushButtonLoadAll->setText(QCoreApplication::translate("RemoteLightControllerClass", "Load all", nullptr));
        toolButtonOnOff->setText(QCoreApplication::translate("RemoteLightControllerClass", "ON/OFF", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("RemoteLightControllerClass", "Update", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLight->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("RemoteLightControllerClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLight->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("RemoteLightControllerClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLight->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("RemoteLightControllerClass", "Remark", nullptr));
        toolButtonManagementMode->setText(QCoreApplication::translate("RemoteLightControllerClass", "Management mode", nullptr));
        label_2->setText(QCoreApplication::translate("RemoteLightControllerClass", "Name", nullptr));
        label->setText(QCoreApplication::translate("RemoteLightControllerClass", "ID", nullptr));
        label_3->setText(QCoreApplication::translate("RemoteLightControllerClass", "Remark", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("RemoteLightControllerClass", "Delete", nullptr));
        pushButtonUpdate_2->setText(QCoreApplication::translate("RemoteLightControllerClass", "Update", nullptr));
        pushButtonCreateNew->setText(QCoreApplication::translate("RemoteLightControllerClass", "Create new", nullptr));
        label_4->setText(QCoreApplication::translate("RemoteLightControllerClass", "Input unique ID number manually when you create new", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RemoteLightControllerClass: public Ui_RemoteLightControllerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOTELIGHTCONTROLLER_H
