/********************************************************************************
** Form generated from reading UI file 'CheckDLLForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKDLLFORM_H
#define UI_CHECKDLLFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CheckDLLFormClass
{
public:
    QLabel *label;
    QLineEdit *lineEditRoot;
    QLabel *label_2;
    QLineEdit *lineEditName;
    QLabel *label_3;
    QLineEdit *lineEditOrganization;
    QLabel *label_4;
    QLineEdit *lineEditVersion;
    QLabel *label_6;
    QLineEdit *lineEditDLLType;
    QListWidget *listWidgetExportFunc;
    QLabel *label_7;
    QPushButton *pushButtonOK;
    QLineEdit *lineEditExplain;
    QLabel *label_5;
    QLineEdit *lineEditCopyright;
    QLabel *label_8;
    QLabel *label_9;
    QTableWidget *tableWidgetMacro;
    QPushButton *pushButtonSetting;
    QPushButton *pushButtonTest;
    QFrame *frame;
    QToolBox *toolBox;
    QWidget *GUI;
    QListWidget *listWidgetGUI;
    QWidget *Algorithm;
    QListWidget *listWidgetAlgorithm;
    QWidget *ResultDLL;
    QListWidget *listWidgetResultDLL;
    QWidget *Filter;
    QListWidget *listWidgetFilter;
    QWidget *Camera;
    QListWidget *listWidgetCamera;
    QWidget *PIO;
    QListWidget *listWidgetPIO;
    QWidget *SequenceDLL;
    QListWidget *listWidgetSequenceDLL;
    QWidget *LightDLL;
    QListWidget *listWidgetLightDLL;
    QWidget *ExecuteVisualizer;
    QListWidget *listWidgetExecuteVisualizer;
    QLineEdit *lineEditLibType;
    QLabel *label_10;
    QLabel *label_11;
    QListWidget *listWidgetRelatedAlgorithm;

    void setupUi(QWidget *CheckDLLFormClass)
    {
        if (CheckDLLFormClass->objectName().isEmpty())
            CheckDLLFormClass->setObjectName("CheckDLLFormClass");
        CheckDLLFormClass->resize(631, 758);
        label = new QLabel(CheckDLLFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(400, 10, 71, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditRoot = new QLineEdit(CheckDLLFormClass);
        lineEditRoot->setObjectName("lineEditRoot");
        lineEditRoot->setGeometry(QRect(480, 10, 141, 20));
        lineEditRoot->setReadOnly(true);
        label_2 = new QLabel(CheckDLLFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(400, 40, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditName = new QLineEdit(CheckDLLFormClass);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(480, 40, 141, 20));
        lineEditName->setReadOnly(true);
        label_3 = new QLabel(CheckDLLFormClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(400, 70, 71, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditOrganization = new QLineEdit(CheckDLLFormClass);
        lineEditOrganization->setObjectName("lineEditOrganization");
        lineEditOrganization->setGeometry(QRect(480, 70, 141, 20));
        lineEditOrganization->setReadOnly(true);
        label_4 = new QLabel(CheckDLLFormClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(400, 100, 71, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditVersion = new QLineEdit(CheckDLLFormClass);
        lineEditVersion->setObjectName("lineEditVersion");
        lineEditVersion->setGeometry(QRect(480, 100, 141, 20));
        lineEditVersion->setReadOnly(true);
        label_6 = new QLabel(CheckDLLFormClass);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(400, 130, 71, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditDLLType = new QLineEdit(CheckDLLFormClass);
        lineEditDLLType->setObjectName("lineEditDLLType");
        lineEditDLLType->setGeometry(QRect(480, 130, 141, 20));
        lineEditDLLType->setReadOnly(true);
        listWidgetExportFunc = new QListWidget(CheckDLLFormClass);
        listWidgetExportFunc->setObjectName("listWidgetExportFunc");
        listWidgetExportFunc->setGeometry(QRect(400, 400, 221, 161));
        label_7 = new QLabel(CheckDLLFormClass);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(400, 380, 221, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonOK = new QPushButton(CheckDLLFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(170, 720, 111, 31));
        lineEditExplain = new QLineEdit(CheckDLLFormClass);
        lineEditExplain->setObjectName("lineEditExplain");
        lineEditExplain->setGeometry(QRect(480, 160, 141, 20));
        lineEditExplain->setReadOnly(true);
        label_5 = new QLabel(CheckDLLFormClass);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(400, 160, 71, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditCopyright = new QLineEdit(CheckDLLFormClass);
        lineEditCopyright->setObjectName("lineEditCopyright");
        lineEditCopyright->setGeometry(QRect(480, 190, 141, 20));
        lineEditCopyright->setReadOnly(true);
        label_8 = new QLabel(CheckDLLFormClass);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(400, 190, 71, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_9 = new QLabel(CheckDLLFormClass);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 570, 381, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetMacro = new QTableWidget(CheckDLLFormClass);
        if (tableWidgetMacro->columnCount() < 2)
            tableWidgetMacro->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetMacro->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetMacro->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetMacro->setObjectName("tableWidgetMacro");
        tableWidgetMacro->setGeometry(QRect(10, 590, 381, 121));
        pushButtonSetting = new QPushButton(CheckDLLFormClass);
        pushButtonSetting->setObjectName("pushButtonSetting");
        pushButtonSetting->setGeometry(QRect(420, 580, 191, 31));
        pushButtonTest = new QPushButton(CheckDLLFormClass);
        pushButtonTest->setObjectName("pushButtonTest");
        pushButtonTest->setEnabled(false);
        pushButtonTest->setGeometry(QRect(420, 620, 191, 31));
        frame = new QFrame(CheckDLLFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 381, 551));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        toolBox = new QToolBox(frame);
        toolBox->setObjectName("toolBox");
        toolBox->setGeometry(QRect(10, 10, 361, 531));
        GUI = new QWidget();
        GUI->setObjectName("GUI");
        GUI->setGeometry(QRect(0, 0, 361, 297));
        listWidgetGUI = new QListWidget(GUI);
        listWidgetGUI->setObjectName("listWidgetGUI");
        listWidgetGUI->setGeometry(QRect(10, 0, 341, 291));
        toolBox->addItem(GUI, QString::fromUtf8("GUI"));
        Algorithm = new QWidget();
        Algorithm->setObjectName("Algorithm");
        Algorithm->setGeometry(QRect(0, 0, 100, 30));
        listWidgetAlgorithm = new QListWidget(Algorithm);
        listWidgetAlgorithm->setObjectName("listWidgetAlgorithm");
        listWidgetAlgorithm->setGeometry(QRect(10, 0, 341, 291));
        toolBox->addItem(Algorithm, QString::fromUtf8("Algorithm"));
        ResultDLL = new QWidget();
        ResultDLL->setObjectName("ResultDLL");
        ResultDLL->setGeometry(QRect(0, 0, 100, 30));
        listWidgetResultDLL = new QListWidget(ResultDLL);
        listWidgetResultDLL->setObjectName("listWidgetResultDLL");
        listWidgetResultDLL->setGeometry(QRect(10, 0, 341, 291));
        toolBox->addItem(ResultDLL, QString::fromUtf8("ResultDLL"));
        Filter = new QWidget();
        Filter->setObjectName("Filter");
        Filter->setGeometry(QRect(0, 0, 100, 30));
        listWidgetFilter = new QListWidget(Filter);
        listWidgetFilter->setObjectName("listWidgetFilter");
        listWidgetFilter->setGeometry(QRect(10, 0, 341, 291));
        toolBox->addItem(Filter, QString::fromUtf8("Filter"));
        Camera = new QWidget();
        Camera->setObjectName("Camera");
        Camera->setGeometry(QRect(0, 0, 100, 30));
        listWidgetCamera = new QListWidget(Camera);
        listWidgetCamera->setObjectName("listWidgetCamera");
        listWidgetCamera->setGeometry(QRect(10, 0, 341, 291));
        toolBox->addItem(Camera, QString::fromUtf8("Camera"));
        PIO = new QWidget();
        PIO->setObjectName("PIO");
        PIO->setGeometry(QRect(0, 0, 100, 30));
        listWidgetPIO = new QListWidget(PIO);
        listWidgetPIO->setObjectName("listWidgetPIO");
        listWidgetPIO->setGeometry(QRect(10, 0, 341, 291));
        toolBox->addItem(PIO, QString::fromUtf8("PIO"));
        SequenceDLL = new QWidget();
        SequenceDLL->setObjectName("SequenceDLL");
        SequenceDLL->setGeometry(QRect(0, 0, 100, 30));
        listWidgetSequenceDLL = new QListWidget(SequenceDLL);
        listWidgetSequenceDLL->setObjectName("listWidgetSequenceDLL");
        listWidgetSequenceDLL->setGeometry(QRect(10, 0, 341, 291));
        toolBox->addItem(SequenceDLL, QString::fromUtf8("SequenceDLL"));
        LightDLL = new QWidget();
        LightDLL->setObjectName("LightDLL");
        LightDLL->setGeometry(QRect(0, 0, 100, 30));
        listWidgetLightDLL = new QListWidget(LightDLL);
        listWidgetLightDLL->setObjectName("listWidgetLightDLL");
        listWidgetLightDLL->setGeometry(QRect(10, 0, 341, 291));
        toolBox->addItem(LightDLL, QString::fromUtf8("LightDLL"));
        ExecuteVisualizer = new QWidget();
        ExecuteVisualizer->setObjectName("ExecuteVisualizer");
        ExecuteVisualizer->setGeometry(QRect(0, 0, 100, 30));
        listWidgetExecuteVisualizer = new QListWidget(ExecuteVisualizer);
        listWidgetExecuteVisualizer->setObjectName("listWidgetExecuteVisualizer");
        listWidgetExecuteVisualizer->setGeometry(QRect(10, 0, 341, 291));
        toolBox->addItem(ExecuteVisualizer, QString::fromUtf8("ExecuteVisualizer"));
        lineEditLibType = new QLineEdit(CheckDLLFormClass);
        lineEditLibType->setObjectName("lineEditLibType");
        lineEditLibType->setGeometry(QRect(480, 220, 141, 20));
        lineEditLibType->setReadOnly(true);
        label_10 = new QLabel(CheckDLLFormClass);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(400, 220, 71, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_11 = new QLabel(CheckDLLFormClass);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(400, 250, 221, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetRelatedAlgorithm = new QListWidget(CheckDLLFormClass);
        listWidgetRelatedAlgorithm->setObjectName("listWidgetRelatedAlgorithm");
        listWidgetRelatedAlgorithm->setGeometry(QRect(400, 270, 221, 91));

        retranslateUi(CheckDLLFormClass);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CheckDLLFormClass);
    } // setupUi

    void retranslateUi(QWidget *CheckDLLFormClass)
    {
        CheckDLLFormClass->setWindowTitle(QCoreApplication::translate("CheckDLLFormClass", "CheckDLLForm", nullptr));
        label->setText(QCoreApplication::translate("CheckDLLFormClass", "Root", nullptr));
        label_2->setText(QCoreApplication::translate("CheckDLLFormClass", "Name", nullptr));
        label_3->setText(QCoreApplication::translate("CheckDLLFormClass", "Organization", nullptr));
        label_4->setText(QCoreApplication::translate("CheckDLLFormClass", "Version", nullptr));
        label_6->setText(QCoreApplication::translate("CheckDLLFormClass", "DLL Type", nullptr));
        label_7->setText(QCoreApplication::translate("CheckDLLFormClass", "Export function", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("CheckDLLFormClass", "Close", nullptr));
        label_5->setText(QCoreApplication::translate("CheckDLLFormClass", "Explain", nullptr));
        label_8->setText(QCoreApplication::translate("CheckDLLFormClass", "Copyright", nullptr));
        label_9->setText(QCoreApplication::translate("CheckDLLFormClass", "Macro", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetMacro->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CheckDLLFormClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetMacro->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CheckDLLFormClass", "Explain", nullptr));
        pushButtonSetting->setText(QCoreApplication::translate("CheckDLLFormClass", "Setting", nullptr));
        pushButtonTest->setText(QCoreApplication::translate("CheckDLLFormClass", "Test function", nullptr));
        toolBox->setItemText(toolBox->indexOf(GUI), QCoreApplication::translate("CheckDLLFormClass", "GUI", nullptr));
        toolBox->setItemText(toolBox->indexOf(Algorithm), QCoreApplication::translate("CheckDLLFormClass", "Algorithm", nullptr));
        toolBox->setItemText(toolBox->indexOf(ResultDLL), QCoreApplication::translate("CheckDLLFormClass", "ResultDLL", nullptr));
        toolBox->setItemText(toolBox->indexOf(Filter), QCoreApplication::translate("CheckDLLFormClass", "Filter", nullptr));
        toolBox->setItemText(toolBox->indexOf(Camera), QCoreApplication::translate("CheckDLLFormClass", "Camera", nullptr));
        toolBox->setItemText(toolBox->indexOf(PIO), QCoreApplication::translate("CheckDLLFormClass", "PIO", nullptr));
        toolBox->setItemText(toolBox->indexOf(SequenceDLL), QCoreApplication::translate("CheckDLLFormClass", "SequenceDLL", nullptr));
        toolBox->setItemText(toolBox->indexOf(LightDLL), QCoreApplication::translate("CheckDLLFormClass", "LightDLL", nullptr));
        toolBox->setItemText(toolBox->indexOf(ExecuteVisualizer), QCoreApplication::translate("CheckDLLFormClass", "ExecuteVisualizer", nullptr));
        label_10->setText(QCoreApplication::translate("CheckDLLFormClass", "LibType", nullptr));
        label_11->setText(QCoreApplication::translate("CheckDLLFormClass", "Related Algorithm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CheckDLLFormClass: public Ui_CheckDLLFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKDLLFORM_H
