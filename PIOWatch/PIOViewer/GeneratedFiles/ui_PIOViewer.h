/********************************************************************************
** Form generated from reading UI file 'PIOViewer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIOVIEWER_H
#define UI_PIOVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PIOViewerClass
{
public:
    QWidget *centralWidget;
    QPushButton *pbClose;
    QTableWidget *twIN;
    QTableWidget *twOUT;
    QComboBox *comboBoxPIODLL;
    QLabel *label;
    QPushButton *pushButtonOpenPIO;
    QPushButton *pushButtonShowSignal;
    QLineEdit *lineEditIODef;
    QLabel *label_2;
    QPushButton *pushButtonSelectIODefineFile;
    QCheckBox *chkEchoBack;
    QComboBox *comboBoxBoardNumber;
    QLabel *label_3;
    QPushButton *pushButtonSaveSignal;
    QPushButton *pushButtonLoadSignal;
    QPushButton *pushButtonClear;
    QLineEdit *lineEditParameter;
    QLabel *label_4;

    void setupUi(QMainWindow *PIOViewerClass)
    {
        if (PIOViewerClass->objectName().isEmpty())
            PIOViewerClass->setObjectName("PIOViewerClass");
        PIOViewerClass->resize(519, 859);
        centralWidget = new QWidget(PIOViewerClass);
        centralWidget->setObjectName("centralWidget");
        pbClose = new QPushButton(centralWidget);
        pbClose->setObjectName("pbClose");
        pbClose->setGeometry(QRect(410, 790, 101, 41));
        twIN = new QTableWidget(centralWidget);
        if (twIN->columnCount() < 1)
            twIN->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        twIN->setHorizontalHeaderItem(0, __qtablewidgetitem);
        twIN->setObjectName("twIN");
        twIN->setGeometry(QRect(10, 170, 251, 612));
        twIN->setSelectionMode(QAbstractItemView::SingleSelection);
        twIN->setSelectionBehavior(QAbstractItemView::SelectRows);
        twIN->setShowGrid(true);
        twIN->setColumnCount(1);
        twIN->verticalHeader()->setVisible(true);
        twOUT = new QTableWidget(centralWidget);
        twOUT->setObjectName("twOUT");
        twOUT->setGeometry(QRect(260, 170, 251, 612));
        twOUT->setSelectionMode(QAbstractItemView::SingleSelection);
        twOUT->setSelectionBehavior(QAbstractItemView::SelectRows);
        twOUT->setShowGrid(true);
        twOUT->setColumnCount(0);
        comboBoxPIODLL = new QComboBox(centralWidget);
        comboBoxPIODLL->setObjectName("comboBoxPIODLL");
        comboBoxPIODLL->setGeometry(QRect(130, 10, 381, 22));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 101, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        pushButtonOpenPIO = new QPushButton(centralWidget);
        pushButtonOpenPIO->setObjectName("pushButtonOpenPIO");
        pushButtonOpenPIO->setGeometry(QRect(230, 100, 121, 31));
        pushButtonShowSignal = new QPushButton(centralWidget);
        pushButtonShowSignal->setObjectName("pushButtonShowSignal");
        pushButtonShowSignal->setGeometry(QRect(410, 100, 101, 31));
        lineEditIODef = new QLineEdit(centralWidget);
        lineEditIODef->setObjectName("lineEditIODef");
        lineEditIODef->setGeometry(QRect(130, 40, 341, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 40, 101, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        pushButtonSelectIODefineFile = new QPushButton(centralWidget);
        pushButtonSelectIODefineFile->setObjectName("pushButtonSelectIODefineFile");
        pushButtonSelectIODefineFile->setGeometry(QRect(474, 40, 31, 23));
        chkEchoBack = new QCheckBox(centralWidget);
        chkEchoBack->setObjectName("chkEchoBack");
        chkEchoBack->setGeometry(QRect(20, 800, 81, 17));
        chkEchoBack->setChecked(true);
        comboBoxBoardNumber = new QComboBox(centralWidget);
        comboBoxBoardNumber->setObjectName("comboBoxBoardNumber");
        comboBoxBoardNumber->setGeometry(QRect(120, 140, 74, 22));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 140, 101, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        pushButtonSaveSignal = new QPushButton(centralWidget);
        pushButtonSaveSignal->setObjectName("pushButtonSaveSignal");
        pushButtonSaveSignal->setGeometry(QRect(170, 800, 91, 31));
        pushButtonLoadSignal = new QPushButton(centralWidget);
        pushButtonLoadSignal->setObjectName("pushButtonLoadSignal");
        pushButtonLoadSignal->setGeometry(QRect(270, 800, 91, 31));
        pushButtonClear = new QPushButton(centralWidget);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(410, 130, 101, 23));
        lineEditParameter = new QLineEdit(centralWidget);
        lineEditParameter->setObjectName("lineEditParameter");
        lineEditParameter->setGeometry(QRect(130, 70, 341, 21));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 70, 101, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        PIOViewerClass->setCentralWidget(centralWidget);

        retranslateUi(PIOViewerClass);

        QMetaObject::connectSlotsByName(PIOViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *PIOViewerClass)
    {
        PIOViewerClass->setWindowTitle(QCoreApplication::translate("PIOViewerClass", "PIOViewer", nullptr));
        pbClose->setText(QCoreApplication::translate("PIOViewerClass", "&Close", nullptr));
        QTableWidgetItem *___qtablewidgetitem = twIN->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PIOViewerClass", "Input bit", nullptr));
        label->setText(QCoreApplication::translate("PIOViewerClass", "Select DLL", nullptr));
        pushButtonOpenPIO->setText(QCoreApplication::translate("PIOViewerClass", "Open", nullptr));
        pushButtonShowSignal->setText(QCoreApplication::translate("PIOViewerClass", "Show signal", nullptr));
        lineEditIODef->setText(QCoreApplication::translate("PIOViewerClass", "IODef.dat", nullptr));
        label_2->setText(QCoreApplication::translate("PIOViewerClass", "IODefine", nullptr));
        pushButtonSelectIODefineFile->setText(QCoreApplication::translate("PIOViewerClass", "...", nullptr));
        chkEchoBack->setText(QCoreApplication::translate("PIOViewerClass", "Echo Back", nullptr));
        label_3->setText(QCoreApplication::translate("PIOViewerClass", "Board Number", nullptr));
        pushButtonSaveSignal->setText(QCoreApplication::translate("PIOViewerClass", "Save signal", nullptr));
        pushButtonLoadSignal->setText(QCoreApplication::translate("PIOViewerClass", "Load signal", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("PIOViewerClass", "Clear signals", nullptr));
        label_4->setText(QCoreApplication::translate("PIOViewerClass", "Parameter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PIOViewerClass: public Ui_PIOViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIOVIEWER_H
