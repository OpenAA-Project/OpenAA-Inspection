/********************************************************************************
** Form generated from reading UI file 'LanguageManager.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LANGUAGEMANAGER_H
#define UI_LANGUAGEMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LanguageManagerClass
{
public:
    QAction *actionLoad_solution;
    QAction *actionLanguage;
    QAction *actionDefault;
    QAction *actionNew_Project;
    QAction *actionSave_solution;
    QAction *actionNew_solution;
    QAction *actionClose;
    QAction *actionOverwrite_solution;
    QWidget *centralWidget;
    QTableWidget *tableWidgetProject;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButtonLoadExcel;
    QPushButton *pushButtonDeleteExcel;
    QTableWidget *tableWidgetExcelFiles;
    QLabel *label_3;
    QLineEdit *lineEditLNGFile;
    QPushButton *pushButtonLNGFile;
    QPushButton *pushButtonCompile;
    QPushButton *pushButtonBuildAll;
    QPushButton *pushButtonAddNewProject;
    QProgressBar *progressBarCompile;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSetting;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *LanguageManagerClass)
    {
        if (LanguageManagerClass->objectName().isEmpty())
            LanguageManagerClass->setObjectName("LanguageManagerClass");
        LanguageManagerClass->resize(1190, 623);
        actionLoad_solution = new QAction(LanguageManagerClass);
        actionLoad_solution->setObjectName("actionLoad_solution");
        actionLanguage = new QAction(LanguageManagerClass);
        actionLanguage->setObjectName("actionLanguage");
        actionDefault = new QAction(LanguageManagerClass);
        actionDefault->setObjectName("actionDefault");
        actionNew_Project = new QAction(LanguageManagerClass);
        actionNew_Project->setObjectName("actionNew_Project");
        actionSave_solution = new QAction(LanguageManagerClass);
        actionSave_solution->setObjectName("actionSave_solution");
        actionNew_solution = new QAction(LanguageManagerClass);
        actionNew_solution->setObjectName("actionNew_solution");
        actionClose = new QAction(LanguageManagerClass);
        actionClose->setObjectName("actionClose");
        actionOverwrite_solution = new QAction(LanguageManagerClass);
        actionOverwrite_solution->setObjectName("actionOverwrite_solution");
        centralWidget = new QWidget(LanguageManagerClass);
        centralWidget->setObjectName("centralWidget");
        tableWidgetProject = new QTableWidget(centralWidget);
        if (tableWidgetProject->columnCount() < 2)
            tableWidgetProject->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetProject->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetProject->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetProject->setObjectName("tableWidgetProject");
        tableWidgetProject->setGeometry(QRect(10, 30, 421, 471));
        tableWidgetProject->setDragEnabled(true);
        tableWidgetProject->setDragDropMode(QAbstractItemView::DragDrop);
        tableWidgetProject->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetProject->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 421, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(440, 10, 741, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        pushButtonLoadExcel = new QPushButton(centralWidget);
        pushButtonLoadExcel->setObjectName("pushButtonLoadExcel");
        pushButtonLoadExcel->setGeometry(QRect(630, 410, 171, 31));
        pushButtonDeleteExcel = new QPushButton(centralWidget);
        pushButtonDeleteExcel->setObjectName("pushButtonDeleteExcel");
        pushButtonDeleteExcel->setGeometry(QRect(820, 410, 171, 31));
        tableWidgetExcelFiles = new QTableWidget(centralWidget);
        if (tableWidgetExcelFiles->columnCount() < 2)
            tableWidgetExcelFiles->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetExcelFiles->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetExcelFiles->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetExcelFiles->setObjectName("tableWidgetExcelFiles");
        tableWidgetExcelFiles->setGeometry(QRect(440, 30, 741, 371));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(440, 460, 721, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        lineEditLNGFile = new QLineEdit(centralWidget);
        lineEditLNGFile->setObjectName("lineEditLNGFile");
        lineEditLNGFile->setGeometry(QRect(440, 480, 721, 31));
        pushButtonLNGFile = new QPushButton(centralWidget);
        pushButtonLNGFile->setObjectName("pushButtonLNGFile");
        pushButtonLNGFile->setGeometry(QRect(1160, 480, 20, 31));
        pushButtonCompile = new QPushButton(centralWidget);
        pushButtonCompile->setObjectName("pushButtonCompile");
        pushButtonCompile->setGeometry(QRect(530, 530, 141, 51));
        pushButtonBuildAll = new QPushButton(centralWidget);
        pushButtonBuildAll->setObjectName("pushButtonBuildAll");
        pushButtonBuildAll->setGeometry(QRect(80, 550, 131, 31));
        pushButtonAddNewProject = new QPushButton(centralWidget);
        pushButtonAddNewProject->setObjectName("pushButtonAddNewProject");
        pushButtonAddNewProject->setGeometry(QRect(80, 510, 131, 31));
        progressBarCompile = new QProgressBar(centralWidget);
        progressBarCompile->setObjectName("progressBarCompile");
        progressBarCompile->setGeometry(QRect(690, 530, 471, 23));
        progressBarCompile->setValue(24);
        LanguageManagerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LanguageManagerClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1190, 20));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        menuSetting = new QMenu(menuBar);
        menuSetting->setObjectName("menuSetting");
        LanguageManagerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LanguageManagerClass);
        mainToolBar->setObjectName("mainToolBar");
        LanguageManagerClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSetting->menuAction());
        menuFile->addAction(actionNew_solution);
        menuFile->addAction(actionLoad_solution);
        menuFile->addAction(actionSave_solution);
        menuFile->addAction(actionOverwrite_solution);
        menuFile->addSeparator();
        menuFile->addAction(actionNew_Project);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuSetting->addAction(actionLanguage);
        menuSetting->addAction(actionDefault);

        retranslateUi(LanguageManagerClass);

        QMetaObject::connectSlotsByName(LanguageManagerClass);
    } // setupUi

    void retranslateUi(QMainWindow *LanguageManagerClass)
    {
        LanguageManagerClass->setWindowTitle(QCoreApplication::translate("LanguageManagerClass", "LanguageManager", nullptr));
        actionLoad_solution->setText(QCoreApplication::translate("LanguageManagerClass", "Load solution", nullptr));
        actionLanguage->setText(QCoreApplication::translate("LanguageManagerClass", "Language", nullptr));
        actionDefault->setText(QCoreApplication::translate("LanguageManagerClass", "Default", nullptr));
        actionNew_Project->setText(QCoreApplication::translate("LanguageManagerClass", "New Project", nullptr));
        actionSave_solution->setText(QCoreApplication::translate("LanguageManagerClass", "Save solution", nullptr));
        actionNew_solution->setText(QCoreApplication::translate("LanguageManagerClass", "New solution", nullptr));
        actionClose->setText(QCoreApplication::translate("LanguageManagerClass", "Close", nullptr));
        actionOverwrite_solution->setText(QCoreApplication::translate("LanguageManagerClass", "Overwrite solution", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetProject->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("LanguageManagerClass", "Project", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetProject->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("LanguageManagerClass", "Lng-File", nullptr));
        label->setText(QCoreApplication::translate("LanguageManagerClass", "Project", nullptr));
        label_2->setText(QCoreApplication::translate("LanguageManagerClass", "EXCEL files", nullptr));
        pushButtonLoadExcel->setText(QCoreApplication::translate("LanguageManagerClass", "Load EXCEL file", nullptr));
        pushButtonDeleteExcel->setText(QCoreApplication::translate("LanguageManagerClass", "Delete from list", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetExcelFiles->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("LanguageManagerClass", "FileName", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetExcelFiles->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("LanguageManagerClass", "Path", nullptr));
        label_3->setText(QCoreApplication::translate("LanguageManagerClass", "Output LNG file and path", nullptr));
        pushButtonLNGFile->setText(QCoreApplication::translate("LanguageManagerClass", "...", nullptr));
        pushButtonCompile->setText(QCoreApplication::translate("LanguageManagerClass", "Compile", nullptr));
        pushButtonBuildAll->setText(QCoreApplication::translate("LanguageManagerClass", "Build all", nullptr));
        pushButtonAddNewProject->setText(QCoreApplication::translate("LanguageManagerClass", "Add new project", nullptr));
        menuFile->setTitle(QCoreApplication::translate("LanguageManagerClass", "File", nullptr));
        menuSetting->setTitle(QCoreApplication::translate("LanguageManagerClass", "Setting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LanguageManagerClass: public Ui_LanguageManagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LANGUAGEMANAGER_H
