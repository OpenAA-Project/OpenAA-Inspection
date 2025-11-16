/********************************************************************************
** Form generated from reading UI file 'ProjectPropertyManager.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTPROPERTYMANAGER_H
#define UI_PROJECTPROPERTYMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectPropertyManagerClass
{
public:
    QWidget *centralWidget;
    QTableWidget *tableWidgetProjectList;
    QLineEdit *lineEditSolutionFileName;
    QLabel *label;
    QPushButton *pushButtonSearchSolutionFile;
    QPushButton *pushButtonLoadSolution;
    QTableWidget *tableWidgetType;
    QPushButton *pushButtonUpdateProject;
    QListWidget *listWidgetTagFolder;
    QTableWidget *tableWidgetProperty;
    QPushButton *pushButtonCopyToAll;
    QPushButton *pushButtonCopy1;
    QPushButton *pushButtonPaste1;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *ProjectPropertyManagerClass)
    {
        if (ProjectPropertyManagerClass->objectName().isEmpty())
            ProjectPropertyManagerClass->setObjectName("ProjectPropertyManagerClass");
        ProjectPropertyManagerClass->resize(1776, 1041);
        centralWidget = new QWidget(ProjectPropertyManagerClass);
        centralWidget->setObjectName("centralWidget");
        tableWidgetProjectList = new QTableWidget(centralWidget);
        if (tableWidgetProjectList->columnCount() < 3)
            tableWidgetProjectList->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetProjectList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetProjectList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetProjectList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetProjectList->setObjectName("tableWidgetProjectList");
        tableWidgetProjectList->setGeometry(QRect(10, 40, 1001, 861));
        tableWidgetProjectList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetProjectList->setSelectionBehavior(QAbstractItemView::SelectRows);
        lineEditSolutionFileName = new QLineEdit(centralWidget);
        lineEditSolutionFileName->setObjectName("lineEditSolutionFileName");
        lineEditSolutionFileName->setGeometry(QRect(140, 10, 441, 21));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 10, 91, 16));
        pushButtonSearchSolutionFile = new QPushButton(centralWidget);
        pushButtonSearchSolutionFile->setObjectName("pushButtonSearchSolutionFile");
        pushButtonSearchSolutionFile->setGeometry(QRect(90, 10, 41, 21));
        pushButtonLoadSolution = new QPushButton(centralWidget);
        pushButtonLoadSolution->setObjectName("pushButtonLoadSolution");
        pushButtonLoadSolution->setGeometry(QRect(590, 10, 93, 23));
        tableWidgetType = new QTableWidget(centralWidget);
        if (tableWidgetType->columnCount() < 2)
            tableWidgetType->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetType->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetType->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        tableWidgetType->setObjectName("tableWidgetType");
        tableWidgetType->setGeometry(QRect(1020, 40, 281, 192));
        tableWidgetType->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetType->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonUpdateProject = new QPushButton(centralWidget);
        pushButtonUpdateProject->setObjectName("pushButtonUpdateProject");
        pushButtonUpdateProject->setGeometry(QRect(732, 910, 261, 31));
        listWidgetTagFolder = new QListWidget(centralWidget);
        new QListWidgetItem(listWidgetTagFolder);
        new QListWidgetItem(listWidgetTagFolder);
        new QListWidgetItem(listWidgetTagFolder);
        listWidgetTagFolder->setObjectName("listWidgetTagFolder");
        listWidgetTagFolder->setGeometry(QRect(1310, 40, 211, 81));
        listWidgetTagFolder->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetProperty = new QTableWidget(centralWidget);
        if (tableWidgetProperty->columnCount() < 2)
            tableWidgetProperty->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetProperty->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetProperty->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        tableWidgetProperty->setObjectName("tableWidgetProperty");
        tableWidgetProperty->setGeometry(QRect(1020, 250, 741, 651));
        pushButtonCopyToAll = new QPushButton(centralWidget);
        pushButtonCopyToAll->setObjectName("pushButtonCopyToAll");
        pushButtonCopyToAll->setGeometry(QRect(1110, 910, 271, 31));
        pushButtonCopy1 = new QPushButton(centralWidget);
        pushButtonCopy1->setObjectName("pushButtonCopy1");
        pushButtonCopy1->setGeometry(QRect(1110, 950, 271, 31));
        pushButtonPaste1 = new QPushButton(centralWidget);
        pushButtonPaste1->setObjectName("pushButtonPaste1");
        pushButtonPaste1->setGeometry(QRect(730, 950, 261, 31));
        ProjectPropertyManagerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ProjectPropertyManagerClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1776, 26));
        ProjectPropertyManagerClass->setMenuBar(menuBar);

        retranslateUi(ProjectPropertyManagerClass);

        QMetaObject::connectSlotsByName(ProjectPropertyManagerClass);
    } // setupUi

    void retranslateUi(QMainWindow *ProjectPropertyManagerClass)
    {
        ProjectPropertyManagerClass->setWindowTitle(QCoreApplication::translate("ProjectPropertyManagerClass", "ProjectPropertyManager", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetProjectList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetProjectList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "Project file path", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetProjectList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "Project file name", nullptr));
        lineEditSolutionFileName->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "C:/Regulus64v3/ServiceLib/ServiceLib.sln", nullptr));
        label->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "Solution file", nullptr));
        pushButtonSearchSolutionFile->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "...", nullptr));
        pushButtonLoadSolution->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "Load", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetType->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetType->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "Build", nullptr));
        pushButtonUpdateProject->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "Overwrite Updated project", nullptr));

        const bool __sortingEnabled = listWidgetTagFolder->isSortingEnabled();
        listWidgetTagFolder->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidgetTagFolder->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "ClCompile", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidgetTagFolder->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "Link", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidgetTagFolder->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "BuildLog", nullptr));
        listWidgetTagFolder->setSortingEnabled(__sortingEnabled);

        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetProperty->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetProperty->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "Data", nullptr));
        pushButtonCopyToAll->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "Copy selected property to all projects", nullptr));
        pushButtonCopy1->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "Copy selected property item", nullptr));
        pushButtonPaste1->setText(QCoreApplication::translate("ProjectPropertyManagerClass", "Paste valye in same Type/Property tag", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectPropertyManagerClass: public Ui_ProjectPropertyManagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTPROPERTYMANAGER_H
