/********************************************************************************
** Form generated from reading UI file 'SettingParamDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGPARAMDIALOG_H
#define UI_SETTINGPARAMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingParamDialogClass
{
public:
    QTabWidget *tabWidgetAllParam;
    QWidget *tabGeneral;
    QWidget *tabComm;
    QWidget *tabCamStrategy;
    QWidget *tabResult;
    QTabWidget *tabWidgetResult;
    QWidget *tab;
    QWidget *tabAlgorithm;
    QTabWidget *tabWidgetAlgorithm;
    QWidget *tab_2;
    QWidget *tabOutlineOffset;
    QPushButton *ButtonOutlineOffset;
    QWidget *tabGUI;
    QWidget *Direction;
    QWidget *tab_4;
    QFrame *frameScanPhase;
    QWidget *tab_3;
    QPushButton *pushButtonRowImageTable;
    QPushButton *pushButtonLoadImageTable;
    QFrame *frameBottom;
    QPushButton *ButtonCancel;
    QPushButton *ButtonOK;
    QPushButton *pushButtonEachPage;

    void setupUi(QDialog *SettingParamDialogClass)
    {
        if (SettingParamDialogClass->objectName().isEmpty())
            SettingParamDialogClass->setObjectName("SettingParamDialogClass");
        SettingParamDialogClass->resize(642, 483);
        tabWidgetAllParam = new QTabWidget(SettingParamDialogClass);
        tabWidgetAllParam->setObjectName("tabWidgetAllParam");
        tabWidgetAllParam->setGeometry(QRect(0, 0, 641, 421));
        tabGeneral = new QWidget();
        tabGeneral->setObjectName("tabGeneral");
        tabWidgetAllParam->addTab(tabGeneral, QString());
        tabComm = new QWidget();
        tabComm->setObjectName("tabComm");
        tabWidgetAllParam->addTab(tabComm, QString());
        tabCamStrategy = new QWidget();
        tabCamStrategy->setObjectName("tabCamStrategy");
        tabWidgetAllParam->addTab(tabCamStrategy, QString());
        tabResult = new QWidget();
        tabResult->setObjectName("tabResult");
        tabWidgetResult = new QTabWidget(tabResult);
        tabWidgetResult->setObjectName("tabWidgetResult");
        tabWidgetResult->setGeometry(QRect(10, 10, 611, 371));
        tab = new QWidget();
        tab->setObjectName("tab");
        tabWidgetResult->addTab(tab, QString());
        tabWidgetAllParam->addTab(tabResult, QString());
        tabAlgorithm = new QWidget();
        tabAlgorithm->setObjectName("tabAlgorithm");
        tabWidgetAlgorithm = new QTabWidget(tabAlgorithm);
        tabWidgetAlgorithm->setObjectName("tabWidgetAlgorithm");
        tabWidgetAlgorithm->setGeometry(QRect(10, 10, 611, 381));
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabWidgetAlgorithm->addTab(tab_2, QString());
        tabWidgetAllParam->addTab(tabAlgorithm, QString());
        tabOutlineOffset = new QWidget();
        tabOutlineOffset->setObjectName("tabOutlineOffset");
        ButtonOutlineOffset = new QPushButton(tabOutlineOffset);
        ButtonOutlineOffset->setObjectName("ButtonOutlineOffset");
        ButtonOutlineOffset->setGeometry(QRect(480, 340, 131, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOutlineOffset->setIcon(icon);
        tabWidgetAllParam->addTab(tabOutlineOffset, QString());
        tabGUI = new QWidget();
        tabGUI->setObjectName("tabGUI");
        tabWidgetAllParam->addTab(tabGUI, QString());
        Direction = new QWidget();
        Direction->setObjectName("Direction");
        tabWidgetAllParam->addTab(Direction, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        frameScanPhase = new QFrame(tab_4);
        frameScanPhase->setObjectName("frameScanPhase");
        frameScanPhase->setGeometry(QRect(10, 10, 491, 371));
        frameScanPhase->setFrameShape(QFrame::NoFrame);
        frameScanPhase->setFrameShadow(QFrame::Raised);
        tabWidgetAllParam->addTab(tab_4, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        pushButtonRowImageTable = new QPushButton(tab_3);
        pushButtonRowImageTable->setObjectName("pushButtonRowImageTable");
        pushButtonRowImageTable->setGeometry(QRect(40, 20, 201, 34));
        pushButtonLoadImageTable = new QPushButton(tab_3);
        pushButtonLoadImageTable->setObjectName("pushButtonLoadImageTable");
        pushButtonLoadImageTable->setGeometry(QRect(40, 60, 201, 34));
        tabWidgetAllParam->addTab(tab_3, QString());
        frameBottom = new QFrame(SettingParamDialogClass);
        frameBottom->setObjectName("frameBottom");
        frameBottom->setGeometry(QRect(0, 420, 641, 61));
        frameBottom->setFrameShape(QFrame::StyledPanel);
        frameBottom->setFrameShadow(QFrame::Raised);
        ButtonCancel = new QPushButton(frameBottom);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(440, 10, 131, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        ButtonOK = new QPushButton(frameBottom);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(220, 10, 131, 41));
        ButtonOK->setIcon(icon);
        pushButtonEachPage = new QPushButton(frameBottom);
        pushButtonEachPage->setObjectName("pushButtonEachPage");
        pushButtonEachPage->setGeometry(QRect(20, 10, 111, 41));

        retranslateUi(SettingParamDialogClass);

        tabWidgetAllParam->setCurrentIndex(0);
        tabWidgetResult->setCurrentIndex(0);
        tabWidgetAlgorithm->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingParamDialogClass);
    } // setupUi

    void retranslateUi(QDialog *SettingParamDialogClass)
    {
        SettingParamDialogClass->setWindowTitle(QCoreApplication::translate("SettingParamDialogClass", "SettingParamDialog", nullptr));
        tabWidgetAllParam->setTabText(tabWidgetAllParam->indexOf(tabGeneral), QCoreApplication::translate("SettingParamDialogClass", "General Param", nullptr));
        tabWidgetAllParam->setTabText(tabWidgetAllParam->indexOf(tabComm), QCoreApplication::translate("SettingParamDialogClass", "Comm", nullptr));
        tabWidgetAllParam->setTabText(tabWidgetAllParam->indexOf(tabCamStrategy), QCoreApplication::translate("SettingParamDialogClass", "Cam Strategy", nullptr));
        tabWidgetResult->setTabText(tabWidgetResult->indexOf(tab), QCoreApplication::translate("SettingParamDialogClass", "Result", nullptr));
        tabWidgetAllParam->setTabText(tabWidgetAllParam->indexOf(tabResult), QCoreApplication::translate("SettingParamDialogClass", "Result", nullptr));
        tabWidgetAlgorithm->setTabText(tabWidgetAlgorithm->indexOf(tab_2), QCoreApplication::translate("SettingParamDialogClass", "\343\203\232\343\203\274\343\202\270", nullptr));
        tabWidgetAllParam->setTabText(tabWidgetAllParam->indexOf(tabAlgorithm), QCoreApplication::translate("SettingParamDialogClass", "Algorithm", nullptr));
        ButtonOutlineOffset->setText(QCoreApplication::translate("SettingParamDialogClass", "Save", nullptr));
        tabWidgetAllParam->setTabText(tabWidgetAllParam->indexOf(tabOutlineOffset), QCoreApplication::translate("SettingParamDialogClass", "OutlineOffset", nullptr));
        tabWidgetAllParam->setTabText(tabWidgetAllParam->indexOf(tabGUI), QCoreApplication::translate("SettingParamDialogClass", "GUI", nullptr));
        tabWidgetAllParam->setTabText(tabWidgetAllParam->indexOf(Direction), QCoreApplication::translate("SettingParamDialogClass", "Direction", nullptr));
        tabWidgetAllParam->setTabText(tabWidgetAllParam->indexOf(tab_4), QCoreApplication::translate("SettingParamDialogClass", "Scan phase", nullptr));
        pushButtonRowImageTable->setText(QCoreApplication::translate("SettingParamDialogClass", "Row image", nullptr));
        pushButtonLoadImageTable->setText(QCoreApplication::translate("SettingParamDialogClass", "Load image table", nullptr));
        tabWidgetAllParam->setTabText(tabWidgetAllParam->indexOf(tab_3), QCoreApplication::translate("SettingParamDialogClass", "Image table", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SettingParamDialogClass", "Cancel", nullptr));
        ButtonOK->setText(QCoreApplication::translate("SettingParamDialogClass", "OK  Save", nullptr));
        pushButtonEachPage->setText(QCoreApplication::translate("SettingParamDialogClass", "Each page", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingParamDialogClass: public Ui_SettingParamDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGPARAMDIALOG_H
