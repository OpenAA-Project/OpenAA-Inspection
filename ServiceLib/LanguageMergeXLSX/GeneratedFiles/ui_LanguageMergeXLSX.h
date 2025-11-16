/********************************************************************************
** Form generated from reading UI file 'LanguageMergeXLSX.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LANGUAGEMERGEXLSX_H
#define UI_LANGUAGEMERGEXLSX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LanguageMergeXLSXClass
{
public:
    QWidget *centralWidget;
    QTableWidget *tableWidget;
    QFrame *frame;
    QLabel *label;
    QLineEdit *lineEditDestFolder;
    QPushButton *pushButtonDestFolder;
    QListWidget *listWidgetDestFiles;
    QPushButton *pushButtonAddDest;
    QFrame *frame_2;
    QLabel *label_2;
    QLineEdit *lineEditSourceFolder;
    QPushButton *pushButtonSourceFolder;
    QListWidget *listWidgetSourceFiles;
    QPushButton *pushButtonAddSource;
    QPushButton *pushButtonConbine;
    QFrame *frame_3;
    QTableWidget *tableWidgetBindedFiles;
    QPushButton *pushButtonStartMerge;
    QProgressBar *progressBar;
    QLabel *label_3;

    void setupUi(QMainWindow *LanguageMergeXLSXClass)
    {
        if (LanguageMergeXLSXClass->objectName().isEmpty())
            LanguageMergeXLSXClass->setObjectName("LanguageMergeXLSXClass");
        LanguageMergeXLSXClass->resize(709, 740);
        centralWidget = new QWidget(LanguageMergeXLSXClass);
        centralWidget->setObjectName("centralWidget");
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
        tableWidget->setGeometry(QRect(80, 30, 531, 161));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 210, 311, 241));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 311, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        lineEditDestFolder = new QLineEdit(frame);
        lineEditDestFolder->setObjectName("lineEditDestFolder");
        lineEditDestFolder->setGeometry(QRect(10, 30, 261, 21));
        lineEditDestFolder->setReadOnly(true);
        pushButtonDestFolder = new QPushButton(frame);
        pushButtonDestFolder->setObjectName("pushButtonDestFolder");
        pushButtonDestFolder->setGeometry(QRect(280, 30, 21, 23));
        listWidgetDestFiles = new QListWidget(frame);
        listWidgetDestFiles->setObjectName("listWidgetDestFiles");
        listWidgetDestFiles->setGeometry(QRect(10, 60, 241, 171));
        listWidgetDestFiles->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonAddDest = new QPushButton(frame);
        pushButtonAddDest->setObjectName("pushButtonAddDest");
        pushButtonAddDest->setGeometry(QRect(260, 120, 41, 41));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(390, 220, 311, 241));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 311, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        lineEditSourceFolder = new QLineEdit(frame_2);
        lineEditSourceFolder->setObjectName("lineEditSourceFolder");
        lineEditSourceFolder->setGeometry(QRect(10, 30, 261, 21));
        lineEditSourceFolder->setReadOnly(true);
        pushButtonSourceFolder = new QPushButton(frame_2);
        pushButtonSourceFolder->setObjectName("pushButtonSourceFolder");
        pushButtonSourceFolder->setGeometry(QRect(280, 30, 21, 23));
        listWidgetSourceFiles = new QListWidget(frame_2);
        listWidgetSourceFiles->setObjectName("listWidgetSourceFiles");
        listWidgetSourceFiles->setGeometry(QRect(10, 60, 241, 171));
        listWidgetSourceFiles->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonAddSource = new QPushButton(frame_2);
        pushButtonAddSource->setObjectName("pushButtonAddSource");
        pushButtonAddSource->setGeometry(QRect(260, 120, 41, 41));
        pushButtonConbine = new QPushButton(centralWidget);
        pushButtonConbine->setObjectName("pushButtonConbine");
        pushButtonConbine->setGeometry(QRect(330, 300, 51, 51));
        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 460, 691, 261));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        tableWidgetBindedFiles = new QTableWidget(frame_3);
        if (tableWidgetBindedFiles->columnCount() < 3)
            tableWidgetBindedFiles->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetBindedFiles->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetBindedFiles->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetBindedFiles->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        tableWidgetBindedFiles->setObjectName("tableWidgetBindedFiles");
        tableWidgetBindedFiles->setGeometry(QRect(10, 10, 671, 201));
        tableWidgetBindedFiles->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonStartMerge = new QPushButton(frame_3);
        pushButtonStartMerge->setObjectName("pushButtonStartMerge");
        pushButtonStartMerge->setGeometry(QRect(20, 220, 191, 31));
        progressBar = new QProgressBar(frame_3);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(250, 220, 431, 23));
        progressBar->setValue(24);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 691, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        LanguageMergeXLSXClass->setCentralWidget(centralWidget);

        retranslateUi(LanguageMergeXLSXClass);

        QMetaObject::connectSlotsByName(LanguageMergeXLSXClass);
    } // setupUi

    void retranslateUi(QMainWindow *LanguageMergeXLSXClass)
    {
        LanguageMergeXLSXClass->setWindowTitle(QCoreApplication::translate("LanguageMergeXLSXClass", "LanguageMergeXLSX", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("LanguageMergeXLSXClass", "ColumnNo", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("LanguageMergeXLSXClass", "Language", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("LanguageMergeXLSXClass", "ExcelFont", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("LanguageMergeXLSXClass", "QtCodec", nullptr));
        label->setText(QCoreApplication::translate("LanguageMergeXLSXClass", "Destination", nullptr));
        pushButtonDestFolder->setText(QCoreApplication::translate("LanguageMergeXLSXClass", "...", nullptr));
        pushButtonAddDest->setText(QCoreApplication::translate("LanguageMergeXLSXClass", "Add", nullptr));
        label_2->setText(QCoreApplication::translate("LanguageMergeXLSXClass", "Source( These files are merged into destination files)", nullptr));
        pushButtonSourceFolder->setText(QCoreApplication::translate("LanguageMergeXLSXClass", "...", nullptr));
        pushButtonAddSource->setText(QCoreApplication::translate("LanguageMergeXLSXClass", "Add", nullptr));
        pushButtonConbine->setText(QCoreApplication::translate("LanguageMergeXLSXClass", "Conbine", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetBindedFiles->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("LanguageMergeXLSXClass", "Destination", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetBindedFiles->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("LanguageMergeXLSXClass", "Source", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetBindedFiles->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("LanguageMergeXLSXClass", "Result", nullptr));
        pushButtonStartMerge->setText(QCoreApplication::translate("LanguageMergeXLSXClass", "Start Merging", nullptr));
        label_3->setText(QCoreApplication::translate("LanguageMergeXLSXClass", "Select conbined language", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LanguageMergeXLSXClass: public Ui_LanguageMergeXLSXClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LANGUAGEMERGEXLSX_H
