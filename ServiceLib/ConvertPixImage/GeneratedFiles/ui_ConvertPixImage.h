/********************************************************************************
** Form generated from reading UI file 'ConvertPixImage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONVERTPIXIMAGE_H
#define UI_CONVERTPIXIMAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConvertPixImageClass
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QTableWidget *tableWidgetPixFile;
    QPushButton *pushButtonAddPixFile;
    QPushButton *pushButtonAddPixFolder;
    QLabel *label;
    QPushButton *pushButtonDeleteList;
    QFrame *frame_2;
    QLabel *label_2;
    QLineEdit *lineEditOutputPath;
    QPushButton *pushButtonFindPath;
    QPushButton *pushButtonExecuteConvert;
    QComboBox *comboBoxExtension;
    QPushButton *pushButtonClose;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ConvertPixImageClass)
    {
        if (ConvertPixImageClass->objectName().isEmpty())
            ConvertPixImageClass->setObjectName("ConvertPixImageClass");
        ConvertPixImageClass->resize(968, 744);
        centralWidget = new QWidget(ConvertPixImageClass);
        centralWidget->setObjectName("centralWidget");
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 951, 571));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        tableWidgetPixFile = new QTableWidget(frame);
        if (tableWidgetPixFile->columnCount() < 2)
            tableWidgetPixFile->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetPixFile->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetPixFile->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetPixFile->setObjectName("tableWidgetPixFile");
        tableWidgetPixFile->setGeometry(QRect(10, 80, 931, 481));
        tableWidgetPixFile->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetPixFile->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonAddPixFile = new QPushButton(frame);
        pushButtonAddPixFile->setObjectName("pushButtonAddPixFile");
        pushButtonAddPixFile->setGeometry(QRect(20, 30, 161, 41));
        pushButtonAddPixFolder = new QPushButton(frame);
        pushButtonAddPixFolder->setObjectName("pushButtonAddPixFolder");
        pushButtonAddPixFolder->setGeometry(QRect(200, 30, 161, 41));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 951, 21));
        label->setAlignment(Qt::AlignCenter);
        pushButtonDeleteList = new QPushButton(frame);
        pushButtonDeleteList->setObjectName("pushButtonDeleteList");
        pushButtonDeleteList->setGeometry(QRect(680, 37, 201, 31));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 590, 951, 71));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 951, 21));
        label_2->setAlignment(Qt::AlignCenter);
        lineEditOutputPath = new QLineEdit(frame_2);
        lineEditOutputPath->setObjectName("lineEditOutputPath");
        lineEditOutputPath->setGeometry(QRect(10, 30, 881, 31));
        pushButtonFindPath = new QPushButton(frame_2);
        pushButtonFindPath->setObjectName("pushButtonFindPath");
        pushButtonFindPath->setGeometry(QRect(902, 30, 41, 28));
        pushButtonExecuteConvert = new QPushButton(centralWidget);
        pushButtonExecuteConvert->setObjectName("pushButtonExecuteConvert");
        pushButtonExecuteConvert->setGeometry(QRect(400, 670, 191, 41));
        comboBoxExtension = new QComboBox(centralWidget);
        comboBoxExtension->addItem(QString());
        comboBoxExtension->addItem(QString());
        comboBoxExtension->addItem(QString());
        comboBoxExtension->setObjectName("comboBoxExtension");
        comboBoxExtension->setGeometry(QRect(620, 680, 80, 22));
        pushButtonClose = new QPushButton(centralWidget);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(860, 670, 93, 41));
        ConvertPixImageClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ConvertPixImageClass);
        statusBar->setObjectName("statusBar");
        ConvertPixImageClass->setStatusBar(statusBar);

        retranslateUi(ConvertPixImageClass);

        QMetaObject::connectSlotsByName(ConvertPixImageClass);
    } // setupUi

    void retranslateUi(QMainWindow *ConvertPixImageClass)
    {
        ConvertPixImageClass->setWindowTitle(QCoreApplication::translate("ConvertPixImageClass", "ConvertPixImage", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetPixFile->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ConvertPixImageClass", "Path", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetPixFile->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ConvertPixImageClass", "FileName", nullptr));
        pushButtonAddPixFile->setText(QCoreApplication::translate("ConvertPixImageClass", "+ Add file", nullptr));
        pushButtonAddPixFolder->setText(QCoreApplication::translate("ConvertPixImageClass", "+ Add files in folder", nullptr));
        label->setText(QCoreApplication::translate("ConvertPixImageClass", "PIX file", nullptr));
        pushButtonDeleteList->setText(QCoreApplication::translate("ConvertPixImageClass", "- Delete selected lists", nullptr));
        label_2->setText(QCoreApplication::translate("ConvertPixImageClass", "Output Image path", nullptr));
        pushButtonFindPath->setText(QCoreApplication::translate("ConvertPixImageClass", "...", nullptr));
        pushButtonExecuteConvert->setText(QCoreApplication::translate("ConvertPixImageClass", "Execute convert", nullptr));
        comboBoxExtension->setItemText(0, QCoreApplication::translate("ConvertPixImageClass", "PNG", nullptr));
        comboBoxExtension->setItemText(1, QCoreApplication::translate("ConvertPixImageClass", "BMP", nullptr));
        comboBoxExtension->setItemText(2, QCoreApplication::translate("ConvertPixImageClass", "JPG", nullptr));

        pushButtonClose->setText(QCoreApplication::translate("ConvertPixImageClass", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConvertPixImageClass: public Ui_ConvertPixImageClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONVERTPIXIMAGE_H
