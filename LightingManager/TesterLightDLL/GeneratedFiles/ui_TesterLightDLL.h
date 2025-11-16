/********************************************************************************
** Form generated from reading UI file 'TesterLightDLL.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTERLIGHTDLL_H
#define UI_TESTERLIGHTDLL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TesterLightDLLClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonLoadDLL;
    QListWidget *listWidgetLightDLL;
    QToolButton *toolButtonOnOff;
    QPushButton *pushButtonSetting;
    QPushButton *pushButtonSaveToDefault;
    QPushButton *pushButtonSaveAs;
    QPushButton *pushButtonLoadFromDefault;
    QPushButton *pushButtonLoadAs;
    QLineEdit *lineEditLightParamStr;
    QLabel *label;

    void setupUi(QMainWindow *TesterLightDLLClass)
    {
        if (TesterLightDLLClass->objectName().isEmpty())
            TesterLightDLLClass->setObjectName("TesterLightDLLClass");
        TesterLightDLLClass->resize(775, 346);
        centralWidget = new QWidget(TesterLightDLLClass);
        centralWidget->setObjectName("centralWidget");
        pushButtonLoadDLL = new QPushButton(centralWidget);
        pushButtonLoadDLL->setObjectName("pushButtonLoadDLL");
        pushButtonLoadDLL->setGeometry(QRect(470, 50, 131, 41));
        listWidgetLightDLL = new QListWidget(centralWidget);
        listWidgetLightDLL->setObjectName("listWidgetLightDLL");
        listWidgetLightDLL->setGeometry(QRect(10, 50, 441, 281));
        toolButtonOnOff = new QToolButton(centralWidget);
        toolButtonOnOff->setObjectName("toolButtonOnOff");
        toolButtonOnOff->setGeometry(QRect(470, 130, 131, 41));
        toolButtonOnOff->setCheckable(true);
        toolButtonOnOff->setChecked(true);
        pushButtonSetting = new QPushButton(centralWidget);
        pushButtonSetting->setObjectName("pushButtonSetting");
        pushButtonSetting->setGeometry(QRect(470, 190, 131, 41));
        pushButtonSaveToDefault = new QPushButton(centralWidget);
        pushButtonSaveToDefault->setObjectName("pushButtonSaveToDefault");
        pushButtonSaveToDefault->setGeometry(QRect(470, 260, 131, 31));
        pushButtonSaveAs = new QPushButton(centralWidget);
        pushButtonSaveAs->setObjectName("pushButtonSaveAs");
        pushButtonSaveAs->setGeometry(QRect(470, 300, 131, 31));
        pushButtonLoadFromDefault = new QPushButton(centralWidget);
        pushButtonLoadFromDefault->setObjectName("pushButtonLoadFromDefault");
        pushButtonLoadFromDefault->setGeometry(QRect(620, 260, 131, 31));
        pushButtonLoadAs = new QPushButton(centralWidget);
        pushButtonLoadAs->setObjectName("pushButtonLoadAs");
        pushButtonLoadAs->setGeometry(QRect(620, 300, 131, 31));
        lineEditLightParamStr = new QLineEdit(centralWidget);
        lineEditLightParamStr->setObjectName("lineEditLightParamStr");
        lineEditLightParamStr->setGeometry(QRect(130, 10, 321, 21));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 101, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        TesterLightDLLClass->setCentralWidget(centralWidget);

        retranslateUi(TesterLightDLLClass);

        QMetaObject::connectSlotsByName(TesterLightDLLClass);
    } // setupUi

    void retranslateUi(QMainWindow *TesterLightDLLClass)
    {
        TesterLightDLLClass->setWindowTitle(QCoreApplication::translate("TesterLightDLLClass", "TesterLightDLL", nullptr));
        pushButtonLoadDLL->setText(QCoreApplication::translate("TesterLightDLLClass", "-> Load DLL", nullptr));
        toolButtonOnOff->setText(QCoreApplication::translate("TesterLightDLLClass", "ON", nullptr));
        pushButtonSetting->setText(QCoreApplication::translate("TesterLightDLLClass", "Setting", nullptr));
        pushButtonSaveToDefault->setText(QCoreApplication::translate("TesterLightDLLClass", "Save to default", nullptr));
        pushButtonSaveAs->setText(QCoreApplication::translate("TesterLightDLLClass", "Save...", nullptr));
        pushButtonLoadFromDefault->setText(QCoreApplication::translate("TesterLightDLLClass", "Load from default", nullptr));
        pushButtonLoadAs->setText(QCoreApplication::translate("TesterLightDLLClass", "Load...", nullptr));
        label->setText(QCoreApplication::translate("TesterLightDLLClass", "Initial Parameter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TesterLightDLLClass: public Ui_TesterLightDLLClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTERLIGHTDLL_H
