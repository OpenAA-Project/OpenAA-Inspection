/********************************************************************************
** Form generated from reading UI file 'LearningServer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEARNINGSERVER_H
#define UI_LEARNINGSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LearningServerClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QTableView *tableViewRegisteredData;
    QTableWidget *tableWidgetLibrary;
    QFrame *frameBottom;
    QPushButton *pushButtonExecute;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonSetting;
    QTableWidget *tableWidgetConnection;
    QLabel *label_10;
    QPushButton *pushButtonSaveImage;
    QPushButton *pushButtonBackup;
    QPushButton *pushButtonRestore;
    QPushButton *pushButtonUpdate;
    QLabel *label_11;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFrame *frame;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEditXSize;
    QLineEdit *lineEditYSize;
    QLabel *label_5;
    QLineEdit *lineEditLayer;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_MasterImage;
    QLabel *label_TargetImage;
    QLineEdit *lineEditMasterID;
    QLabel *label_8;
    QLineEdit *lineEditMasterName;
    QLabel *label_9;
    QFrame *frameColorButton;
    QWidget *tab_2;
    QTableWidget *tableWidgetExecuter;
    QLabel *label_12;
    QTableWidget *tableWidgetAlgorithmThreshold;
    QProgressBar *progressBar;
    QTableWidget *tableWidgetThresholdProperty;

    void setupUi(QMainWindow *LearningServerClass)
    {
        if (LearningServerClass->objectName().isEmpty())
            LearningServerClass->setObjectName("LearningServerClass");
        LearningServerClass->resize(1349, 700);
        centralWidget = new QWidget(LearningServerClass);
        centralWidget->setObjectName("centralWidget");
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 410, 501, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 501, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableViewRegisteredData = new QTableView(centralWidget);
        tableViewRegisteredData->setObjectName("tableViewRegisteredData");
        tableViewRegisteredData->setGeometry(QRect(10, 30, 501, 351));
        tableViewRegisteredData->setSelectionMode(QAbstractItemView::SingleSelection);
        tableViewRegisteredData->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetLibrary = new QTableWidget(centralWidget);
        if (tableWidgetLibrary->columnCount() < 4)
            tableWidgetLibrary->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibrary->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibrary->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLibrary->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibrary->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetLibrary->setObjectName("tableWidgetLibrary");
        tableWidgetLibrary->setGeometry(QRect(10, 430, 501, 131));
        tableWidgetLibrary->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibrary->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameBottom = new QFrame(centralWidget);
        frameBottom->setObjectName("frameBottom");
        frameBottom->setGeometry(QRect(0, 570, 1351, 131));
        frameBottom->setFrameShape(QFrame::StyledPanel);
        frameBottom->setFrameShadow(QFrame::Raised);
        pushButtonExecute = new QPushButton(frameBottom);
        pushButtonExecute->setObjectName("pushButtonExecute");
        pushButtonExecute->setGeometry(QRect(190, 10, 141, 41));
        pushButtonExecute->setCheckable(true);
        pushButtonClose = new QPushButton(frameBottom);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(1180, 40, 111, 71));
        pushButtonSetting = new QPushButton(frameBottom);
        pushButtonSetting->setObjectName("pushButtonSetting");
        pushButtonSetting->setGeometry(QRect(10, 10, 141, 41));
        tableWidgetConnection = new QTableWidget(frameBottom);
        if (tableWidgetConnection->columnCount() < 2)
            tableWidgetConnection->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetConnection->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetConnection->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        tableWidgetConnection->setObjectName("tableWidgetConnection");
        tableWidgetConnection->setGeometry(QRect(520, 30, 501, 91));
        label_10 = new QLabel(frameBottom);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(520, 10, 501, 20));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSaveImage = new QPushButton(frameBottom);
        pushButtonSaveImage->setObjectName("pushButtonSaveImage");
        pushButtonSaveImage->setGeometry(QRect(390, 10, 121, 41));
        pushButtonBackup = new QPushButton(frameBottom);
        pushButtonBackup->setObjectName("pushButtonBackup");
        pushButtonBackup->setGeometry(QRect(220, 70, 141, 41));
        pushButtonRestore = new QPushButton(frameBottom);
        pushButtonRestore->setObjectName("pushButtonRestore");
        pushButtonRestore->setGeometry(QRect(370, 70, 141, 41));
        pushButtonUpdate = new QPushButton(frameBottom);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(10, 70, 141, 41));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(60, 380, 431, 21));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(510, 10, 831, 551));
        tab = new QWidget();
        tab->setObjectName("tab");
        frame = new QFrame(tab);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 811, 521));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 61, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(80, 10, 61, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditXSize = new QLineEdit(frame);
        lineEditXSize->setObjectName("lineEditXSize");
        lineEditXSize->setGeometry(QRect(10, 30, 61, 20));
        lineEditYSize = new QLineEdit(frame);
        lineEditYSize->setObjectName("lineEditYSize");
        lineEditYSize->setGeometry(QRect(80, 30, 61, 20));
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(150, 10, 61, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditLayer = new QLineEdit(frame);
        lineEditLayer->setObjectName("lineEditLayer");
        lineEditLayer->setGeometry(QRect(150, 30, 61, 20));
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 100, 381, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(400, 100, 381, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_MasterImage = new QLabel(frame);
        label_MasterImage->setObjectName("label_MasterImage");
        label_MasterImage->setGeometry(QRect(10, 120, 381, 371));
        label_TargetImage = new QLabel(frame);
        label_TargetImage->setObjectName("label_TargetImage");
        label_TargetImage->setGeometry(QRect(400, 120, 381, 371));
        lineEditMasterID = new QLineEdit(frame);
        lineEditMasterID->setObjectName("lineEditMasterID");
        lineEditMasterID->setGeometry(QRect(220, 30, 61, 20));
        lineEditMasterID->setReadOnly(true);
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(220, 10, 61, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditMasterName = new QLineEdit(frame);
        lineEditMasterName->setObjectName("lineEditMasterName");
        lineEditMasterName->setGeometry(QRect(290, 30, 421, 20));
        lineEditMasterName->setReadOnly(true);
        label_9 = new QLabel(frame);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(290, 10, 421, 20));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameColorButton = new QFrame(frame);
        frameColorButton->setObjectName("frameColorButton");
        frameColorButton->setGeometry(QRect(10, 60, 381, 31));
        frameColorButton->setFrameShape(QFrame::StyledPanel);
        frameColorButton->setFrameShadow(QFrame::Raised);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tableWidgetExecuter = new QTableWidget(tab_2);
        if (tableWidgetExecuter->columnCount() < 5)
            tableWidgetExecuter->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetExecuter->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetExecuter->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetExecuter->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetExecuter->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetExecuter->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        tableWidgetExecuter->setObjectName("tableWidgetExecuter");
        tableWidgetExecuter->setGeometry(QRect(10, 10, 421, 511));
        tableWidgetExecuter->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetExecuter->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_12 = new QLabel(tab_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(440, 10, 381, 20));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetAlgorithmThreshold = new QTableWidget(tab_2);
        if (tableWidgetAlgorithmThreshold->columnCount() < 5)
            tableWidgetAlgorithmThreshold->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetAlgorithmThreshold->setHorizontalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidgetAlgorithmThreshold->setHorizontalHeaderItem(1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidgetAlgorithmThreshold->setHorizontalHeaderItem(2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidgetAlgorithmThreshold->setHorizontalHeaderItem(3, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidgetAlgorithmThreshold->setHorizontalHeaderItem(4, __qtablewidgetitem15);
        tableWidgetAlgorithmThreshold->setObjectName("tableWidgetAlgorithmThreshold");
        tableWidgetAlgorithmThreshold->setGeometry(QRect(440, 30, 381, 151));
        tableWidgetAlgorithmThreshold->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAlgorithmThreshold->setSelectionBehavior(QAbstractItemView::SelectRows);
        progressBar = new QProgressBar(tab_2);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(440, 500, 381, 23));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        tableWidgetThresholdProperty = new QTableWidget(tab_2);
        if (tableWidgetThresholdProperty->columnCount() < 2)
            tableWidgetThresholdProperty->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidgetThresholdProperty->setHorizontalHeaderItem(0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidgetThresholdProperty->setHorizontalHeaderItem(1, __qtablewidgetitem17);
        tableWidgetThresholdProperty->setObjectName("tableWidgetThresholdProperty");
        tableWidgetThresholdProperty->setGeometry(QRect(440, 190, 381, 301));
        tabWidget->addTab(tab_2, QString());
        LearningServerClass->setCentralWidget(centralWidget);

        retranslateUi(LearningServerClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LearningServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *LearningServerClass)
    {
        LearningServerClass->setWindowTitle(QCoreApplication::translate("LearningServerClass", "LearningServer", nullptr));
        label->setText(QCoreApplication::translate("LearningServerClass", "Library", nullptr));
        label_2->setText(QCoreApplication::translate("LearningServerClass", "Registered data", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibrary->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("LearningServerClass", "LibType", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibrary->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("LearningServerClass", "LibTypeName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibrary->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("LearningServerClass", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibrary->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("LearningServerClass", "Lib Name", nullptr));
        pushButtonExecute->setText(QCoreApplication::translate("LearningServerClass", "\345\256\237\350\241\214\350\252\277\346\225\264", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("LearningServerClass", "Close", nullptr));
        pushButtonSetting->setText(QCoreApplication::translate("LearningServerClass", "Setting", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetConnection->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("LearningServerClass", "IP address", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetConnection->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("LearningServerClass", "Command", nullptr));
        label_10->setText(QCoreApplication::translate("LearningServerClass", "Connection", nullptr));
        pushButtonSaveImage->setText(QCoreApplication::translate("LearningServerClass", "\347\224\273\345\203\217\345\207\272\345\212\233", nullptr));
        pushButtonBackup->setText(QCoreApplication::translate("LearningServerClass", "Save to backup", nullptr));
        pushButtonRestore->setText(QCoreApplication::translate("LearningServerClass", "Restore", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("LearningServerClass", "\350\241\250\347\244\272\346\233\264\346\226\260", nullptr));
        label_11->setText(QCoreApplication::translate("LearningServerClass", "Type : 1=OK , 2=NG", nullptr));
        label_3->setText(QCoreApplication::translate("LearningServerClass", "XSize", nullptr));
        label_4->setText(QCoreApplication::translate("LearningServerClass", "YSize", nullptr));
        label_5->setText(QCoreApplication::translate("LearningServerClass", "Layer", nullptr));
        label_6->setText(QCoreApplication::translate("LearningServerClass", "Master Image", nullptr));
        label_7->setText(QCoreApplication::translate("LearningServerClass", "Target Image", nullptr));
        label_MasterImage->setText(QString());
        label_TargetImage->setText(QString());
        label_8->setText(QCoreApplication::translate("LearningServerClass", "MasterID", nullptr));
        label_9->setText(QCoreApplication::translate("LearningServerClass", "Master name", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("LearningServerClass", "\347\231\273\351\214\262\346\203\205\345\240\261\347\242\272\350\252\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetExecuter->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("LearningServerClass", "LearningID", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetExecuter->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("LearningServerClass", "UpdateTime", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetExecuter->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("LearningServerClass", "OK/NG", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetExecuter->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("LearningServerClass", "Priority", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetExecuter->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("LearningServerClass", "Result", nullptr));
        label_12->setText(QCoreApplication::translate("LearningServerClass", "Library", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetAlgorithmThreshold->horizontalHeaderItem(0);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("LearningServerClass", "LibType", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetAlgorithmThreshold->horizontalHeaderItem(1);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("LearningServerClass", "LibTypeName", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidgetAlgorithmThreshold->horizontalHeaderItem(2);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("LearningServerClass", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidgetAlgorithmThreshold->horizontalHeaderItem(3);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("LearningServerClass", "Lib Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidgetAlgorithmThreshold->horizontalHeaderItem(4);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("LearningServerClass", "\350\251\225\344\276\241\345\200\244", nullptr));
        progressBar->setFormat(QCoreApplication::translate("LearningServerClass", "%p", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidgetThresholdProperty->horizontalHeaderItem(0);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("LearningServerClass", "\350\250\255\345\256\232\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidgetThresholdProperty->horizontalHeaderItem(1);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("LearningServerClass", "\350\250\255\345\256\232\345\200\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("LearningServerClass", "\345\256\237\350\241\214\347\212\266\346\263\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LearningServerClass: public Ui_LearningServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEARNINGSERVER_H
