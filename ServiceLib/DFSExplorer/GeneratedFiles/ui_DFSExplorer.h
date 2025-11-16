/********************************************************************************
** Form generated from reading UI file 'DFSExplorer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DFSEXPLORER_H
#define UI_DFSEXPLORER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DFSExplorerClass
{
public:
    QWidget *centralWidget;
    QTreeWidget *treeWidgetFolders;
    QTableWidget *tableWidgetFiles;
    QFrame *frame;
    QPushButton *pushButtonAddFolder;
    QPushButton *pushButtonCopyTo;
    QPushButton *pushButtonCopyFrom;
    QPushButton *pushButtonRemove;
    QPushButton *pushButtonRemoveFolder;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DFSExplorerClass)
    {
        if (DFSExplorerClass->objectName().isEmpty())
            DFSExplorerClass->setObjectName("DFSExplorerClass");
        DFSExplorerClass->resize(1261, 1128);
        centralWidget = new QWidget(DFSExplorerClass);
        centralWidget->setObjectName("centralWidget");
        treeWidgetFolders = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidgetFolders->setHeaderItem(__qtreewidgetitem);
        treeWidgetFolders->setObjectName("treeWidgetFolders");
        treeWidgetFolders->setGeometry(QRect(0, 30, 371, 1041));
        tableWidgetFiles = new QTableWidget(centralWidget);
        if (tableWidgetFiles->columnCount() < 6)
            tableWidgetFiles->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetFiles->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetFiles->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetFiles->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetFiles->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetFiles->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetFiles->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidgetFiles->setObjectName("tableWidgetFiles");
        tableWidgetFiles->setGeometry(QRect(370, 30, 891, 1041));
        tableWidgetFiles->setDragDropMode(QAbstractItemView::DragDrop);
        tableWidgetFiles->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetFiles->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 1261, 31));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonAddFolder = new QPushButton(frame);
        pushButtonAddFolder->setObjectName("pushButtonAddFolder");
        pushButtonAddFolder->setGeometry(QRect(30, 0, 93, 28));
        pushButtonCopyTo = new QPushButton(frame);
        pushButtonCopyTo->setObjectName("pushButtonCopyTo");
        pushButtonCopyTo->setGeometry(QRect(380, 0, 93, 28));
        pushButtonCopyFrom = new QPushButton(frame);
        pushButtonCopyFrom->setObjectName("pushButtonCopyFrom");
        pushButtonCopyFrom->setGeometry(QRect(510, 0, 93, 28));
        pushButtonRemove = new QPushButton(frame);
        pushButtonRemove->setObjectName("pushButtonRemove");
        pushButtonRemove->setGeometry(QRect(630, 0, 93, 28));
        pushButtonRemoveFolder = new QPushButton(frame);
        pushButtonRemoveFolder->setObjectName("pushButtonRemoveFolder");
        pushButtonRemoveFolder->setGeometry(QRect(160, 0, 93, 28));
        DFSExplorerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DFSExplorerClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1261, 26));
        DFSExplorerClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(DFSExplorerClass);
        statusBar->setObjectName("statusBar");
        DFSExplorerClass->setStatusBar(statusBar);

        retranslateUi(DFSExplorerClass);

        QMetaObject::connectSlotsByName(DFSExplorerClass);
    } // setupUi

    void retranslateUi(QMainWindow *DFSExplorerClass)
    {
        DFSExplorerClass->setWindowTitle(QCoreApplication::translate("DFSExplorerClass", "DFSExplorer", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetFiles->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DFSExplorerClass", "File name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetFiles->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DFSExplorerClass", "Provider", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetFiles->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DFSExplorerClass", "Path", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetFiles->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("DFSExplorerClass", "Ext", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetFiles->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("DFSExplorerClass", "FileSize", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetFiles->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("DFSExplorerClass", "Updated", nullptr));
        pushButtonAddFolder->setText(QCoreApplication::translate("DFSExplorerClass", "Add folder", nullptr));
        pushButtonCopyTo->setText(QCoreApplication::translate("DFSExplorerClass", "CopyTo", nullptr));
        pushButtonCopyFrom->setText(QCoreApplication::translate("DFSExplorerClass", "CopyFrom", nullptr));
        pushButtonRemove->setText(QCoreApplication::translate("DFSExplorerClass", "Remove File", nullptr));
        pushButtonRemoveFolder->setText(QCoreApplication::translate("DFSExplorerClass", "Remove folder", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DFSExplorerClass: public Ui_DFSExplorerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DFSEXPLORER_H
