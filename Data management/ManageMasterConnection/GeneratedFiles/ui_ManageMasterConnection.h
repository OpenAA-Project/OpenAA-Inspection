/********************************************************************************
** Form generated from reading UI file 'ManageMasterConnection.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGEMASTERCONNECTION_H
#define UI_MANAGEMASTERCONNECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManageMasterConnectionClass
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QTableView *tableView;
    QLineEdit *EditRemark;
    QFrame *frameCategory;
    QLabel *labelTopView;
    QLineEdit *EditMasterCode;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label;
    QLineEdit *EditMasterName;
    QLabel *label_3;
    QFrame *frame_2;
    QLabel *label_5;
    QTableView *tableViewConnection;
    QTableView *tableViewContents;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *pushButtonCreateNew;
    QPushButton *pushButtonDeleteConnection;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonAddMaster;
    QLineEdit *lineEditHost;
    QLineEdit *lineEditDatabaseFile;
    QLabel *label_8;
    QLabel *label_9;

    void setupUi(QMainWindow *ManageMasterConnectionClass)
    {
        if (ManageMasterConnectionClass->objectName().isEmpty())
            ManageMasterConnectionClass->setObjectName("ManageMasterConnectionClass");
        ManageMasterConnectionClass->resize(1108, 681);
        centralWidget = new QWidget(ManageMasterConnectionClass);
        centralWidget->setObjectName("centralWidget");
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 50, 641, 581));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        tableView = new QTableView(frame);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(10, 380, 611, 192));
        EditRemark = new QLineEdit(frame);
        EditRemark->setObjectName("EditRemark");
        EditRemark->setGeometry(QRect(340, 350, 281, 21));
        frameCategory = new QFrame(frame);
        frameCategory->setObjectName("frameCategory");
        frameCategory->setGeometry(QRect(0, 20, 361, 251));
        frameCategory->setFrameShape(QFrame::StyledPanel);
        frameCategory->setFrameShadow(QFrame::Raised);
        labelTopView = new QLabel(frame);
        labelTopView->setObjectName("labelTopView");
        labelTopView->setGeometry(QRect(370, 20, 257, 257));
        labelTopView->setFrameShape(QFrame::Panel);
        labelTopView->setFrameShadow(QFrame::Sunken);
        EditMasterCode = new QLineEdit(frame);
        EditMasterCode->setObjectName("EditMasterCode");
        EditMasterCode->setGeometry(QRect(10, 300, 81, 21));
        EditMasterCode->setReadOnly(true);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(340, 330, 281, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 280, 81, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 330, 321, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        EditMasterName = new QLineEdit(frame);
        EditMasterName->setObjectName("EditMasterName");
        EditMasterName->setGeometry(QRect(10, 350, 321, 21));
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(-1, 0, 641, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(720, 50, 381, 581));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 0, 381, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableViewConnection = new QTableView(frame_2);
        tableViewConnection->setObjectName("tableViewConnection");
        tableViewConnection->setGeometry(QRect(10, 50, 361, 192));
        tableViewContents = new QTableView(frame_2);
        tableViewContents->setObjectName("tableViewContents");
        tableViewContents->setGeometry(QRect(10, 361, 361, 171));
        label_6 = new QLabel(frame_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 30, 361, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 340, 361, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonCreateNew = new QPushButton(frame_2);
        pushButtonCreateNew->setObjectName("pushButtonCreateNew");
        pushButtonCreateNew->setGeometry(QRect(20, 250, 101, 31));
        pushButtonDeleteConnection = new QPushButton(frame_2);
        pushButtonDeleteConnection->setObjectName("pushButtonDeleteConnection");
        pushButtonDeleteConnection->setGeometry(QRect(140, 250, 101, 31));
        pushButtonClose = new QPushButton(centralWidget);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(920, 640, 121, 31));
        pushButtonAddMaster = new QPushButton(centralWidget);
        pushButtonAddMaster->setObjectName("pushButtonAddMaster");
        pushButtonAddMaster->setGeometry(QRect(660, 250, 51, 41));
        lineEditHost = new QLineEdit(centralWidget);
        lineEditHost->setObjectName("lineEditHost");
        lineEditHost->setGeometry(QRect(10, 20, 191, 20));
        lineEditDatabaseFile = new QLineEdit(centralWidget);
        lineEditDatabaseFile->setObjectName("lineEditDatabaseFile");
        lineEditDatabaseFile->setGeometry(QRect(210, 20, 441, 20));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 0, 191, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(210, 0, 441, 20));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        ManageMasterConnectionClass->setCentralWidget(centralWidget);

        retranslateUi(ManageMasterConnectionClass);

        QMetaObject::connectSlotsByName(ManageMasterConnectionClass);
    } // setupUi

    void retranslateUi(QMainWindow *ManageMasterConnectionClass)
    {
        ManageMasterConnectionClass->setWindowTitle(QCoreApplication::translate("ManageMasterConnectionClass", "Manage Master Connection", nullptr));
        label_2->setText(QCoreApplication::translate("ManageMasterConnectionClass", "Remark", nullptr));
        label_4->setText(QCoreApplication::translate("ManageMasterConnectionClass", "Master Code", nullptr));
        label->setText(QCoreApplication::translate("ManageMasterConnectionClass", "Master Name", nullptr));
        label_3->setText(QCoreApplication::translate("ManageMasterConnectionClass", "Master Data", nullptr));
        label_5->setText(QCoreApplication::translate("ManageMasterConnectionClass", "Connection", nullptr));
        label_6->setText(QCoreApplication::translate("ManageMasterConnectionClass", "Connection Data", nullptr));
        label_7->setText(QCoreApplication::translate("ManageMasterConnectionClass", "Content Data", nullptr));
        pushButtonCreateNew->setText(QCoreApplication::translate("ManageMasterConnectionClass", "Create new", nullptr));
        pushButtonDeleteConnection->setText(QCoreApplication::translate("ManageMasterConnectionClass", "Delete", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ManageMasterConnectionClass", "Close", nullptr));
        pushButtonAddMaster->setText(QCoreApplication::translate("ManageMasterConnectionClass", "=>", nullptr));
        label_8->setText(QCoreApplication::translate("ManageMasterConnectionClass", "host", nullptr));
        label_9->setText(QCoreApplication::translate("ManageMasterConnectionClass", "database file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManageMasterConnectionClass: public Ui_ManageMasterConnectionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGEMASTERCONNECTION_H
