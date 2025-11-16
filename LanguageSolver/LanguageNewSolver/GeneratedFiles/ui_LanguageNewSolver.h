/********************************************************************************
** Form generated from reading UI file 'LanguageNewSolver.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LANGUAGENEWSOLVER_H
#define UI_LANGUAGENEWSOLVER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LanguageNewSolverClass
{
public:
    QAction *actionNew_solution;
    QAction *actionLoad_solution;
    QAction *actionOverwrite_solution;
    QAction *actionSave_solution;
    QAction *actionClose;
    QAction *actionLoad_Codec_file;
    QWidget *centralWidget;
    QLabel *label_9;
    QLabel *label_7;
    QPushButton *pushButtonAddProject;
    QListWidget *listWidgetProject;
    QLineEdit *lineEditVarName;
    QPushButton *pushButtonExecuteOne;
    QLabel *label;
    QLineEdit *lineEditXLSXFolder;
    QPushButton *pushButtonExecute;
    QFrame *frame;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButtonAddCPPFiles;
    QPushButton *pushButtonSetResourceFile;
    QLineEdit *lineEditXLSXFile;
    QListWidget *listWidgetUI;
    QPushButton *pushButtonAutoXLSXNaming;
    QPushButton *pushButtonDeleteUIFiles;
    QPushButton *pushButtonSetXLSXFile;
    QLabel *label_8;
    QPushButton *pushButtonDeleteCPPFiles;
    QListWidget *listWidgetCPP;
    QPushButton *pushButtonAutoResourceNaming;
    QPushButton *pushButtonAddUIFiles;
    QLineEdit *lineEditResourceFile;
    QLineEdit *EditFolderReference;
    QPushButton *pushButtonFolderReference;
    QLabel *label_5;
    QTableWidget *tableWidget;
    QPushButton *pushButtonDeleteProject;
    QPushButton *pushButtonSort;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *LanguageNewSolverClass)
    {
        if (LanguageNewSolverClass->objectName().isEmpty())
            LanguageNewSolverClass->setObjectName("LanguageNewSolverClass");
        LanguageNewSolverClass->resize(1028, 710);
        actionNew_solution = new QAction(LanguageNewSolverClass);
        actionNew_solution->setObjectName("actionNew_solution");
        actionLoad_solution = new QAction(LanguageNewSolverClass);
        actionLoad_solution->setObjectName("actionLoad_solution");
        actionOverwrite_solution = new QAction(LanguageNewSolverClass);
        actionOverwrite_solution->setObjectName("actionOverwrite_solution");
        actionSave_solution = new QAction(LanguageNewSolverClass);
        actionSave_solution->setObjectName("actionSave_solution");
        actionClose = new QAction(LanguageNewSolverClass);
        actionClose->setObjectName("actionClose");
        actionLoad_Codec_file = new QAction(LanguageNewSolverClass);
        actionLoad_Codec_file->setObjectName("actionLoad_Codec_file");
        centralWidget = new QWidget(LanguageNewSolverClass);
        centralWidget->setObjectName("centralWidget");
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(11, 68, 341, 20));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(11, 18, 281, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonAddProject = new QPushButton(centralWidget);
        pushButtonAddProject->setObjectName("pushButtonAddProject");
        pushButtonAddProject->setGeometry(QRect(10, 540, 181, 31));
        listWidgetProject = new QListWidget(centralWidget);
        listWidgetProject->setObjectName("listWidgetProject");
        listWidgetProject->setGeometry(QRect(11, 140, 341, 391));
        lineEditVarName = new QLineEdit(centralWidget);
        lineEditVarName->setObjectName("lineEditVarName");
        lineEditVarName->setGeometry(QRect(11, 38, 281, 20));
        pushButtonExecuteOne = new QPushButton(centralWidget);
        pushButtonExecuteOne->setObjectName("pushButtonExecuteOne");
        pushButtonExecuteOne->setGeometry(QRect(10, 590, 341, 31));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(11, 120, 181, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditXLSXFolder = new QLineEdit(centralWidget);
        lineEditXLSXFolder->setObjectName("lineEditXLSXFolder");
        lineEditXLSXFolder->setGeometry(QRect(11, 88, 341, 20));
        pushButtonExecute = new QPushButton(centralWidget);
        pushButtonExecute->setObjectName("pushButtonExecute");
        pushButtonExecute->setGeometry(QRect(10, 630, 341, 41));
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(360, 180, 661, 471));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 220, 531, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 531, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 362, 531, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonAddCPPFiles = new QPushButton(frame);
        pushButtonAddCPPFiles->setObjectName("pushButtonAddCPPFiles");
        pushButtonAddCPPFiles->setGeometry(QRect(550, 92, 101, 31));
        pushButtonSetResourceFile = new QPushButton(frame);
        pushButtonSetResourceFile->setObjectName("pushButtonSetResourceFile");
        pushButtonSetResourceFile->setGeometry(QRect(551, 378, 101, 23));
        lineEditXLSXFile = new QLineEdit(frame);
        lineEditXLSXFile->setObjectName("lineEditXLSXFile");
        lineEditXLSXFile->setGeometry(QRect(10, 440, 531, 20));
        listWidgetUI = new QListWidget(frame);
        listWidgetUI->setObjectName("listWidgetUI");
        listWidgetUI->setGeometry(QRect(10, 240, 531, 111));
        pushButtonAutoXLSXNaming = new QPushButton(frame);
        pushButtonAutoXLSXNaming->setObjectName("pushButtonAutoXLSXNaming");
        pushButtonAutoXLSXNaming->setGeometry(QRect(550, 412, 101, 23));
        pushButtonDeleteUIFiles = new QPushButton(frame);
        pushButtonDeleteUIFiles->setObjectName("pushButtonDeleteUIFiles");
        pushButtonDeleteUIFiles->setGeometry(QRect(550, 272, 101, 31));
        pushButtonSetXLSXFile = new QPushButton(frame);
        pushButtonSetXLSXFile->setObjectName("pushButtonSetXLSXFile");
        pushButtonSetXLSXFile->setGeometry(QRect(550, 440, 101, 23));
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 420, 531, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonDeleteCPPFiles = new QPushButton(frame);
        pushButtonDeleteCPPFiles->setObjectName("pushButtonDeleteCPPFiles");
        pushButtonDeleteCPPFiles->setGeometry(QRect(550, 132, 101, 31));
        listWidgetCPP = new QListWidget(frame);
        listWidgetCPP->setObjectName("listWidgetCPP");
        listWidgetCPP->setGeometry(QRect(10, 90, 531, 121));
        pushButtonAutoResourceNaming = new QPushButton(frame);
        pushButtonAutoResourceNaming->setObjectName("pushButtonAutoResourceNaming");
        pushButtonAutoResourceNaming->setGeometry(QRect(551, 350, 101, 23));
        pushButtonAddUIFiles = new QPushButton(frame);
        pushButtonAddUIFiles->setObjectName("pushButtonAddUIFiles");
        pushButtonAddUIFiles->setGeometry(QRect(550, 232, 101, 31));
        lineEditResourceFile = new QLineEdit(frame);
        lineEditResourceFile->setObjectName("lineEditResourceFile");
        lineEditResourceFile->setGeometry(QRect(10, 382, 531, 20));
        lineEditResourceFile->setReadOnly(false);
        EditFolderReference = new QLineEdit(frame);
        EditFolderReference->setObjectName("EditFolderReference");
        EditFolderReference->setGeometry(QRect(10, 40, 531, 20));
        pushButtonFolderReference = new QPushButton(frame);
        pushButtonFolderReference->setObjectName("pushButtonFolderReference");
        pushButtonFolderReference->setGeometry(QRect(550, 42, 101, 23));
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 20, 531, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(360, 0, 661, 161));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonDeleteProject = new QPushButton(centralWidget);
        pushButtonDeleteProject->setObjectName("pushButtonDeleteProject");
        pushButtonDeleteProject->setGeometry(QRect(240, 540, 111, 31));
        pushButtonSort = new QPushButton(centralWidget);
        pushButtonSort->setObjectName("pushButtonSort");
        pushButtonSort->setGeometry(QRect(140, 120, 51, 21));
        LanguageNewSolverClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LanguageNewSolverClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1028, 20));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        LanguageNewSolverClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LanguageNewSolverClass);
        mainToolBar->setObjectName("mainToolBar");
        LanguageNewSolverClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew_solution);
        menuFile->addAction(actionLoad_solution);
        menuFile->addAction(actionOverwrite_solution);
        menuFile->addAction(actionSave_solution);
        menuFile->addSeparator();
        menuFile->addAction(actionLoad_Codec_file);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);

        retranslateUi(LanguageNewSolverClass);

        QMetaObject::connectSlotsByName(LanguageNewSolverClass);
    } // setupUi

    void retranslateUi(QMainWindow *LanguageNewSolverClass)
    {
        LanguageNewSolverClass->setWindowTitle(QCoreApplication::translate("LanguageNewSolverClass", "LanguageNewSolver", nullptr));
        actionNew_solution->setText(QCoreApplication::translate("LanguageNewSolverClass", "New solution", nullptr));
        actionLoad_solution->setText(QCoreApplication::translate("LanguageNewSolverClass", "Load solution", nullptr));
        actionOverwrite_solution->setText(QCoreApplication::translate("LanguageNewSolverClass", "Overwrite solution", nullptr));
        actionSave_solution->setText(QCoreApplication::translate("LanguageNewSolverClass", "Save solution", nullptr));
        actionClose->setText(QCoreApplication::translate("LanguageNewSolverClass", "Close", nullptr));
        actionLoad_Codec_file->setText(QCoreApplication::translate("LanguageNewSolverClass", "Load Codec file", nullptr));
        label_9->setText(QCoreApplication::translate("LanguageNewSolverClass", "XLSX Folder", nullptr));
        label_7->setText(QCoreApplication::translate("LanguageNewSolverClass", "Variable Name", nullptr));
        pushButtonAddProject->setText(QCoreApplication::translate("LanguageNewSolverClass", "Insert new", nullptr));
        lineEditVarName->setText(QCoreApplication::translate("LanguageNewSolverClass", "LangSolver", nullptr));
        pushButtonExecuteOne->setText(QCoreApplication::translate("LanguageNewSolverClass", "Execute 1 selected project", nullptr));
        label->setText(QCoreApplication::translate("LanguageNewSolverClass", "Projects", nullptr));
        pushButtonExecute->setText(QCoreApplication::translate("LanguageNewSolverClass", "Execute all", nullptr));
        label_2->setText(QCoreApplication::translate("LanguageNewSolverClass", "UI Files", nullptr));
        label_3->setText(QCoreApplication::translate("LanguageNewSolverClass", "CPP Files", nullptr));
        label_4->setText(QCoreApplication::translate("LanguageNewSolverClass", "Resource file", nullptr));
        pushButtonAddCPPFiles->setText(QCoreApplication::translate("LanguageNewSolverClass", "Add files", nullptr));
        pushButtonSetResourceFile->setText(QCoreApplication::translate("LanguageNewSolverClass", "file", nullptr));
        pushButtonAutoXLSXNaming->setText(QCoreApplication::translate("LanguageNewSolverClass", "Auto", nullptr));
        pushButtonDeleteUIFiles->setText(QCoreApplication::translate("LanguageNewSolverClass", "Delete", nullptr));
        pushButtonSetXLSXFile->setText(QCoreApplication::translate("LanguageNewSolverClass", "file", nullptr));
        label_8->setText(QCoreApplication::translate("LanguageNewSolverClass", "XLSX file", nullptr));
        pushButtonDeleteCPPFiles->setText(QCoreApplication::translate("LanguageNewSolverClass", "Delete", nullptr));
        pushButtonAutoResourceNaming->setText(QCoreApplication::translate("LanguageNewSolverClass", "Auto", nullptr));
        pushButtonAddUIFiles->setText(QCoreApplication::translate("LanguageNewSolverClass", "Add files", nullptr));
        pushButtonFolderReference->setText(QCoreApplication::translate("LanguageNewSolverClass", "...", nullptr));
        label_5->setText(QCoreApplication::translate("LanguageNewSolverClass", "Folder reference", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("LanguageNewSolverClass", "ColumnNo", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("LanguageNewSolverClass", "Language", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("LanguageNewSolverClass", "ExcelFont", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("LanguageNewSolverClass", "QtCodec", nullptr));
        pushButtonDeleteProject->setText(QCoreApplication::translate("LanguageNewSolverClass", "Delete", nullptr));
        pushButtonSort->setText(QCoreApplication::translate("LanguageNewSolverClass", "Sort", nullptr));
        menuFile->setTitle(QCoreApplication::translate("LanguageNewSolverClass", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LanguageNewSolverClass: public Ui_LanguageNewSolverClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LANGUAGENEWSOLVER_H
