/********************************************************************************
** Form generated from reading UI file 'LanguageSolver.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LANGUAGESOLVER_H
#define UI_LANGUAGESOLVER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LanguageSolverClass
{
public:
    QAction *actionLoad_source_CPP;
    QAction *actionLoad_UI_ui;
    QAction *actionSave_CSV;
    QAction *actionLoad_CSV;
    QAction *actionSave_resource_files;
    QAction *actionClose;
    QAction *actionReplace_CPP;
    QAction *actionCodec;
    QAction *actionLoad_resource_file;
    QAction *actionCodec_for_Languages;
    QAction *actionLoad_Project;
    QAction *actionSaveProject;
    QAction *actionOverwrite_Project;
    QWidget *centralWidget;
    QListWidget *listWidgetProject;
    QLabel *label;
    QLabel *label_2;
    QListWidget *listWidgetUI;
    QListWidget *listWidgetCPP;
    QLabel *label_3;
    QLineEdit *lineEditResourceFile;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEditCSVFile;
    QPushButton *pushButtonAddCPPFiles;
    QPushButton *pushButtonAddUIFiles;
    QPushButton *pushButtonSetResourceFile;
    QPushButton *pushButtonSetCSVFile;
    QPushButton *pushButtonAddProject;
    QLineEdit *lineEditProjectName;
    QPushButton *pushButtonUpdateProject;
    QPushButton *pushButtonDeleteProject;
    QPushButton *pushButtonDeleteCPPFiles;
    QPushButton *pushButtonDeleteUIFiles;
    QPushButton *pushButtonExecute;
    QLabel *label_6;
    QPushButton *pushButtonFolderReference;
    QLineEdit *EditFolderReference;
    QPushButton *pushButtonAutoResourceNaming;
    QPushButton *pushButtonAutoCSVNaming;
    QLineEdit *lineEditVarName;
    QLabel *label_7;
    QPushButton *pushButtonExecuteOne;
    QPushButton *pushButtonViewString;
    QPushButton *pushButtonViewUI;
    QPushButton *pushButtonAutoXLSXNaming;
    QLineEdit *lineEditXLSXFile;
    QLabel *label_8;
    QPushButton *pushButtonSetXLSXFile;
    QLineEdit *lineEditXLSXFolder;
    QLabel *label_9;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOption;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LanguageSolverClass)
    {
        if (LanguageSolverClass->objectName().isEmpty())
            LanguageSolverClass->setObjectName("LanguageSolverClass");
        LanguageSolverClass->resize(707, 737);
        actionLoad_source_CPP = new QAction(LanguageSolverClass);
        actionLoad_source_CPP->setObjectName("actionLoad_source_CPP");
        actionLoad_UI_ui = new QAction(LanguageSolverClass);
        actionLoad_UI_ui->setObjectName("actionLoad_UI_ui");
        actionSave_CSV = new QAction(LanguageSolverClass);
        actionSave_CSV->setObjectName("actionSave_CSV");
        actionLoad_CSV = new QAction(LanguageSolverClass);
        actionLoad_CSV->setObjectName("actionLoad_CSV");
        actionSave_resource_files = new QAction(LanguageSolverClass);
        actionSave_resource_files->setObjectName("actionSave_resource_files");
        actionClose = new QAction(LanguageSolverClass);
        actionClose->setObjectName("actionClose");
        actionReplace_CPP = new QAction(LanguageSolverClass);
        actionReplace_CPP->setObjectName("actionReplace_CPP");
        actionCodec = new QAction(LanguageSolverClass);
        actionCodec->setObjectName("actionCodec");
        actionLoad_resource_file = new QAction(LanguageSolverClass);
        actionLoad_resource_file->setObjectName("actionLoad_resource_file");
        actionCodec_for_Languages = new QAction(LanguageSolverClass);
        actionCodec_for_Languages->setObjectName("actionCodec_for_Languages");
        actionLoad_Project = new QAction(LanguageSolverClass);
        actionLoad_Project->setObjectName("actionLoad_Project");
        actionSaveProject = new QAction(LanguageSolverClass);
        actionSaveProject->setObjectName("actionSaveProject");
        actionOverwrite_Project = new QAction(LanguageSolverClass);
        actionOverwrite_Project->setObjectName("actionOverwrite_Project");
        centralWidget = new QWidget(LanguageSolverClass);
        centralWidget->setObjectName("centralWidget");
        listWidgetProject = new QListWidget(centralWidget);
        listWidgetProject->setObjectName("listWidgetProject");
        listWidgetProject->setGeometry(QRect(20, 132, 171, 251));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 112, 171, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(209, 292, 371, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetUI = new QListWidget(centralWidget);
        listWidgetUI->setObjectName("listWidgetUI");
        listWidgetUI->setGeometry(QRect(210, 312, 371, 111));
        listWidgetCPP = new QListWidget(centralWidget);
        listWidgetCPP->setObjectName("listWidgetCPP");
        listWidgetCPP->setGeometry(QRect(210, 162, 371, 121));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(210, 142, 371, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditResourceFile = new QLineEdit(centralWidget);
        lineEditResourceFile->setObjectName("lineEditResourceFile");
        lineEditResourceFile->setGeometry(QRect(210, 454, 371, 20));
        lineEditResourceFile->setReadOnly(false);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(210, 434, 371, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(210, 512, 371, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditCSVFile = new QLineEdit(centralWidget);
        lineEditCSVFile->setObjectName("lineEditCSVFile");
        lineEditCSVFile->setGeometry(QRect(210, 532, 371, 20));
        pushButtonAddCPPFiles = new QPushButton(centralWidget);
        pushButtonAddCPPFiles->setObjectName("pushButtonAddCPPFiles");
        pushButtonAddCPPFiles->setGeometry(QRect(600, 162, 81, 31));
        pushButtonAddUIFiles = new QPushButton(centralWidget);
        pushButtonAddUIFiles->setObjectName("pushButtonAddUIFiles");
        pushButtonAddUIFiles->setGeometry(QRect(600, 302, 81, 31));
        pushButtonSetResourceFile = new QPushButton(centralWidget);
        pushButtonSetResourceFile->setObjectName("pushButtonSetResourceFile");
        pushButtonSetResourceFile->setGeometry(QRect(600, 462, 81, 23));
        pushButtonSetCSVFile = new QPushButton(centralWidget);
        pushButtonSetCSVFile->setObjectName("pushButtonSetCSVFile");
        pushButtonSetCSVFile->setGeometry(QRect(600, 530, 81, 23));
        pushButtonAddProject = new QPushButton(centralWidget);
        pushButtonAddProject->setObjectName("pushButtonAddProject");
        pushButtonAddProject->setGeometry(QRect(20, 412, 75, 23));
        lineEditProjectName = new QLineEdit(centralWidget);
        lineEditProjectName->setObjectName("lineEditProjectName");
        lineEditProjectName->setGeometry(QRect(20, 382, 171, 20));
        pushButtonUpdateProject = new QPushButton(centralWidget);
        pushButtonUpdateProject->setObjectName("pushButtonUpdateProject");
        pushButtonUpdateProject->setGeometry(QRect(100, 412, 75, 23));
        pushButtonDeleteProject = new QPushButton(centralWidget);
        pushButtonDeleteProject->setObjectName("pushButtonDeleteProject");
        pushButtonDeleteProject->setGeometry(QRect(100, 442, 75, 23));
        pushButtonDeleteCPPFiles = new QPushButton(centralWidget);
        pushButtonDeleteCPPFiles->setObjectName("pushButtonDeleteCPPFiles");
        pushButtonDeleteCPPFiles->setGeometry(QRect(600, 202, 81, 31));
        pushButtonDeleteUIFiles = new QPushButton(centralWidget);
        pushButtonDeleteUIFiles->setObjectName("pushButtonDeleteUIFiles");
        pushButtonDeleteUIFiles->setGeometry(QRect(600, 342, 81, 31));
        pushButtonExecute = new QPushButton(centralWidget);
        pushButtonExecute->setObjectName("pushButtonExecute");
        pushButtonExecute->setGeometry(QRect(20, 582, 171, 91));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(210, 0, 278, 141));
        pushButtonFolderReference = new QPushButton(centralWidget);
        pushButtonFolderReference->setObjectName("pushButtonFolderReference");
        pushButtonFolderReference->setGeometry(QRect(20, 472, 151, 23));
        EditFolderReference = new QLineEdit(centralWidget);
        EditFolderReference->setObjectName("EditFolderReference");
        EditFolderReference->setGeometry(QRect(20, 502, 151, 20));
        pushButtonAutoResourceNaming = new QPushButton(centralWidget);
        pushButtonAutoResourceNaming->setObjectName("pushButtonAutoResourceNaming");
        pushButtonAutoResourceNaming->setGeometry(QRect(600, 434, 81, 23));
        pushButtonAutoCSVNaming = new QPushButton(centralWidget);
        pushButtonAutoCSVNaming->setObjectName("pushButtonAutoCSVNaming");
        pushButtonAutoCSVNaming->setGeometry(QRect(600, 502, 81, 23));
        lineEditVarName = new QLineEdit(centralWidget);
        lineEditVarName->setObjectName("lineEditVarName");
        lineEditVarName->setGeometry(QRect(20, 30, 101, 20));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 10, 101, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonExecuteOne = new QPushButton(centralWidget);
        pushButtonExecuteOne->setObjectName("pushButtonExecuteOne");
        pushButtonExecuteOne->setGeometry(QRect(20, 542, 171, 31));
        pushButtonViewString = new QPushButton(centralWidget);
        pushButtonViewString->setObjectName("pushButtonViewString");
        pushButtonViewString->setGeometry(QRect(600, 242, 81, 31));
        pushButtonViewUI = new QPushButton(centralWidget);
        pushButtonViewUI->setObjectName("pushButtonViewUI");
        pushButtonViewUI->setGeometry(QRect(600, 382, 81, 31));
        pushButtonAutoXLSXNaming = new QPushButton(centralWidget);
        pushButtonAutoXLSXNaming->setObjectName("pushButtonAutoXLSXNaming");
        pushButtonAutoXLSXNaming->setGeometry(QRect(600, 582, 81, 23));
        lineEditXLSXFile = new QLineEdit(centralWidget);
        lineEditXLSXFile->setObjectName("lineEditXLSXFile");
        lineEditXLSXFile->setGeometry(QRect(210, 612, 371, 20));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(210, 592, 371, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSetXLSXFile = new QPushButton(centralWidget);
        pushButtonSetXLSXFile->setObjectName("pushButtonSetXLSXFile");
        pushButtonSetXLSXFile->setGeometry(QRect(600, 610, 81, 23));
        lineEditXLSXFolder = new QLineEdit(centralWidget);
        lineEditXLSXFolder->setObjectName("lineEditXLSXFolder");
        lineEditXLSXFolder->setGeometry(QRect(20, 80, 171, 20));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 60, 171, 20));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        LanguageSolverClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LanguageSolverClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 707, 18));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        menuOption = new QMenu(menuBar);
        menuOption->setObjectName("menuOption");
        LanguageSolverClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LanguageSolverClass);
        mainToolBar->setObjectName("mainToolBar");
        LanguageSolverClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LanguageSolverClass);
        statusBar->setObjectName("statusBar");
        LanguageSolverClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuOption->menuAction());
        menuFile->addAction(actionLoad_source_CPP);
        menuFile->addAction(actionLoad_UI_ui);
        menuFile->addSeparator();
        menuFile->addAction(actionSave_CSV);
        menuFile->addAction(actionLoad_CSV);
        menuFile->addSeparator();
        menuFile->addAction(actionSave_resource_files);
        menuFile->addAction(actionLoad_resource_file);
        menuFile->addAction(actionReplace_CPP);
        menuFile->addSeparator();
        menuFile->addAction(actionSaveProject);
        menuFile->addAction(actionLoad_Project);
        menuFile->addAction(actionOverwrite_Project);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuOption->addAction(actionCodec);
        menuOption->addAction(actionCodec_for_Languages);

        retranslateUi(LanguageSolverClass);

        QMetaObject::connectSlotsByName(LanguageSolverClass);
    } // setupUi

    void retranslateUi(QMainWindow *LanguageSolverClass)
    {
        LanguageSolverClass->setWindowTitle(QCoreApplication::translate("LanguageSolverClass", "LanguageSolver", nullptr));
        actionLoad_source_CPP->setText(QCoreApplication::translate("LanguageSolverClass", "Load source(CPP)", nullptr));
        actionLoad_UI_ui->setText(QCoreApplication::translate("LanguageSolverClass", "Load UI(ui)", nullptr));
        actionSave_CSV->setText(QCoreApplication::translate("LanguageSolverClass", "Save CSV", nullptr));
        actionLoad_CSV->setText(QCoreApplication::translate("LanguageSolverClass", "Load CSV", nullptr));
        actionSave_resource_files->setText(QCoreApplication::translate("LanguageSolverClass", "Save resource file", nullptr));
        actionClose->setText(QCoreApplication::translate("LanguageSolverClass", "Exit", nullptr));
        actionReplace_CPP->setText(QCoreApplication::translate("LanguageSolverClass", "Replace CPP", nullptr));
        actionCodec->setText(QCoreApplication::translate("LanguageSolverClass", "Codec", nullptr));
        actionLoad_resource_file->setText(QCoreApplication::translate("LanguageSolverClass", "Load resource file", nullptr));
        actionCodec_for_Languages->setText(QCoreApplication::translate("LanguageSolverClass", "Codec for Languages", nullptr));
        actionLoad_Project->setText(QCoreApplication::translate("LanguageSolverClass", "Load Project", nullptr));
        actionSaveProject->setText(QCoreApplication::translate("LanguageSolverClass", "SaveProject", nullptr));
        actionOverwrite_Project->setText(QCoreApplication::translate("LanguageSolverClass", "Overwrite Project", nullptr));
        label->setText(QCoreApplication::translate("LanguageSolverClass", "Projects", nullptr));
        label_2->setText(QCoreApplication::translate("LanguageSolverClass", "UI Files", nullptr));
        label_3->setText(QCoreApplication::translate("LanguageSolverClass", "CPP Files", nullptr));
        label_4->setText(QCoreApplication::translate("LanguageSolverClass", "Resource file", nullptr));
        label_5->setText(QCoreApplication::translate("LanguageSolverClass", "CSV file", nullptr));
        pushButtonAddCPPFiles->setText(QCoreApplication::translate("LanguageSolverClass", "Add files", nullptr));
        pushButtonAddUIFiles->setText(QCoreApplication::translate("LanguageSolverClass", "Add files", nullptr));
        pushButtonSetResourceFile->setText(QCoreApplication::translate("LanguageSolverClass", "file", nullptr));
        pushButtonSetCSVFile->setText(QCoreApplication::translate("LanguageSolverClass", "file", nullptr));
        pushButtonAddProject->setText(QCoreApplication::translate("LanguageSolverClass", "Add", nullptr));
        pushButtonUpdateProject->setText(QCoreApplication::translate("LanguageSolverClass", "Update", nullptr));
        pushButtonDeleteProject->setText(QCoreApplication::translate("LanguageSolverClass", "Delete", nullptr));
        pushButtonDeleteCPPFiles->setText(QCoreApplication::translate("LanguageSolverClass", "Delete", nullptr));
        pushButtonDeleteUIFiles->setText(QCoreApplication::translate("LanguageSolverClass", "Delete", nullptr));
        pushButtonExecute->setText(QCoreApplication::translate("LanguageSolverClass", "Execute all", nullptr));
        label_6->setText(QCoreApplication::translate("LanguageSolverClass", "1:Load resource file if it exists\n"
"2:Load XLSX file if it exists. Otherwise CSV file is loaded\n"
"   When CSV is loaded, newer resource file may be loaded\n"
"3:Load UI file\n"
"4:Create bak file for CPP if CPP file is changed\n"
"5:Replace CPP file\n"
"6:Add include word in CPP\n"
"7:Save resource file\n"
"8:Save XLSX file\n"
"9:Save header file", nullptr));
        pushButtonFolderReference->setText(QCoreApplication::translate("LanguageSolverClass", "Folder reference", nullptr));
        pushButtonAutoResourceNaming->setText(QCoreApplication::translate("LanguageSolverClass", "Auto", nullptr));
        pushButtonAutoCSVNaming->setText(QCoreApplication::translate("LanguageSolverClass", "Auto", nullptr));
        lineEditVarName->setText(QCoreApplication::translate("LanguageSolverClass", "LangSolver", nullptr));
        label_7->setText(QCoreApplication::translate("LanguageSolverClass", "Variable Name", nullptr));
        pushButtonExecuteOne->setText(QCoreApplication::translate("LanguageSolverClass", "Execute 1 selected project", nullptr));
        pushButtonViewString->setText(QCoreApplication::translate("LanguageSolverClass", "View", nullptr));
        pushButtonViewUI->setText(QCoreApplication::translate("LanguageSolverClass", "View", nullptr));
        pushButtonAutoXLSXNaming->setText(QCoreApplication::translate("LanguageSolverClass", "Auto", nullptr));
        label_8->setText(QCoreApplication::translate("LanguageSolverClass", "XLSX file", nullptr));
        pushButtonSetXLSXFile->setText(QCoreApplication::translate("LanguageSolverClass", "file", nullptr));
        label_9->setText(QCoreApplication::translate("LanguageSolverClass", "XLSX Folder", nullptr));
        menuFile->setTitle(QCoreApplication::translate("LanguageSolverClass", "File", nullptr));
        menuOption->setTitle(QCoreApplication::translate("LanguageSolverClass", "Option", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LanguageSolverClass: public Ui_LanguageSolverClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LANGUAGESOLVER_H
