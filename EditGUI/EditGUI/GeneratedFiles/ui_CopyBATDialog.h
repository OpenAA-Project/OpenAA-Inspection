/********************************************************************************
** Form generated from reading UI file 'CopyBATDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYBATDIALOG_H
#define UI_COPYBATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_CopyBATDialog
{
public:
    QLabel *label;
    QLineEdit *lineEditBATFile;
    QPushButton *pushButtonSelectBATFile;
    QLabel *label_2;
    QLineEdit *lineEditGUI;
    QLabel *label_3;
    QLineEdit *lineEditAlgorithm;
    QLineEdit *lineEditPIOFile;
    QLabel *label_4;
    QLineEdit *lineEditCameraFile;
    QLabel *label_5;
    QLineEdit *lineEditSequenceFile;
    QLabel *label_6;
    QLineEdit *lineEditGeneralStockerFile;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEditFilter;
    QLineEdit *lineEditGlobalDat;
    QLabel *label_9;
    QPushButton *pushButtonSelectGlobalDat;
    QLineEdit *lineEditResultFile;
    QLabel *label_10;
    QLineEdit *lineEditLightFile;
    QLabel *label_11;
    QPushButton *pushButtonMakeBAT;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonSelecGUIFolder;
    QPushButton *pushButtonSelectAlgorithmFolder;
    QPushButton *pushButtonSelectPIOFile;
    QPushButton *pushButtonSelectCameraFile;
    QPushButton *pushButtonSelectLightFile;
    QPushButton *pushButtonSelectSequenceDLL;
    QPushButton *pushButtonSelectGeneralStockers;
    QPushButton *pushButtonSelectFilterPath;
    QPushButton *pushButtonSelectResultDLL;
    QPushButton *pushButtonSaveSetting;
    QPushButton *pushButtonLoadSetting;
    QTableWidget *tableWidgetAdditional;
    QLabel *label_12;
    QPushButton *pushButtonPlus;
    QPushButton *pushButtonMinus;
    QCheckBox *checkBoxInspectionPlayer;
    QCheckBox *checkBoxInspectionEditor;
    QCheckBox *checkBoxRepairGUIMain;

    void setupUi(QDialog *CopyBATDialog)
    {
        if (CopyBATDialog->objectName().isEmpty())
            CopyBATDialog->setObjectName("CopyBATDialog");
        CopyBATDialog->resize(570, 824);
        label = new QLabel(CopyBATDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 520, 391, 21));
        lineEditBATFile = new QLineEdit(CopyBATDialog);
        lineEditBATFile->setObjectName("lineEditBATFile");
        lineEditBATFile->setGeometry(QRect(20, 540, 401, 31));
        pushButtonSelectBATFile = new QPushButton(CopyBATDialog);
        pushButtonSelectBATFile->setObjectName("pushButtonSelectBATFile");
        pushButtonSelectBATFile->setGeometry(QRect(430, 540, 41, 31));
        label_2 = new QLabel(CopyBATDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 70, 91, 31));
        lineEditGUI = new QLineEdit(CopyBATDialog);
        lineEditGUI->setObjectName("lineEditGUI");
        lineEditGUI->setGeometry(QRect(130, 70, 291, 31));
        label_3 = new QLabel(CopyBATDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 110, 111, 31));
        lineEditAlgorithm = new QLineEdit(CopyBATDialog);
        lineEditAlgorithm->setObjectName("lineEditAlgorithm");
        lineEditAlgorithm->setGeometry(QRect(130, 110, 291, 31));
        lineEditPIOFile = new QLineEdit(CopyBATDialog);
        lineEditPIOFile->setObjectName("lineEditPIOFile");
        lineEditPIOFile->setGeometry(QRect(130, 150, 381, 31));
        label_4 = new QLabel(CopyBATDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 150, 61, 31));
        lineEditCameraFile = new QLineEdit(CopyBATDialog);
        lineEditCameraFile->setObjectName("lineEditCameraFile");
        lineEditCameraFile->setGeometry(QRect(130, 190, 381, 31));
        label_5 = new QLabel(CopyBATDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 190, 71, 31));
        lineEditSequenceFile = new QLineEdit(CopyBATDialog);
        lineEditSequenceFile->setObjectName("lineEditSequenceFile");
        lineEditSequenceFile->setGeometry(QRect(130, 270, 381, 31));
        label_6 = new QLabel(CopyBATDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 270, 111, 31));
        lineEditGeneralStockerFile = new QLineEdit(CopyBATDialog);
        lineEditGeneralStockerFile->setObjectName("lineEditGeneralStockerFile");
        lineEditGeneralStockerFile->setGeometry(QRect(130, 310, 381, 31));
        label_7 = new QLabel(CopyBATDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 310, 121, 31));
        label_8 = new QLabel(CopyBATDialog);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(30, 350, 91, 31));
        lineEditFilter = new QLineEdit(CopyBATDialog);
        lineEditFilter->setObjectName("lineEditFilter");
        lineEditFilter->setGeometry(QRect(130, 350, 281, 31));
        lineEditGlobalDat = new QLineEdit(CopyBATDialog);
        lineEditGlobalDat->setObjectName("lineEditGlobalDat");
        lineEditGlobalDat->setGeometry(QRect(20, 20, 401, 31));
        label_9 = new QLabel(CopyBATDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 0, 391, 21));
        pushButtonSelectGlobalDat = new QPushButton(CopyBATDialog);
        pushButtonSelectGlobalDat->setObjectName("pushButtonSelectGlobalDat");
        pushButtonSelectGlobalDat->setGeometry(QRect(430, 20, 41, 31));
        lineEditResultFile = new QLineEdit(CopyBATDialog);
        lineEditResultFile->setObjectName("lineEditResultFile");
        lineEditResultFile->setGeometry(QRect(130, 390, 381, 31));
        label_10 = new QLabel(CopyBATDialog);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(30, 390, 91, 31));
        lineEditLightFile = new QLineEdit(CopyBATDialog);
        lineEditLightFile->setObjectName("lineEditLightFile");
        lineEditLightFile->setGeometry(QRect(130, 230, 381, 31));
        label_11 = new QLabel(CopyBATDialog);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(20, 230, 71, 31));
        pushButtonMakeBAT = new QPushButton(CopyBATDialog);
        pushButtonMakeBAT->setObjectName("pushButtonMakeBAT");
        pushButtonMakeBAT->setGeometry(QRect(110, 760, 112, 34));
        pushButtonCancel = new QPushButton(CopyBATDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(310, 760, 112, 34));
        pushButtonSelecGUIFolder = new QPushButton(CopyBATDialog);
        pushButtonSelecGUIFolder->setObjectName("pushButtonSelecGUIFolder");
        pushButtonSelecGUIFolder->setGeometry(QRect(430, 70, 41, 31));
        pushButtonSelectAlgorithmFolder = new QPushButton(CopyBATDialog);
        pushButtonSelectAlgorithmFolder->setObjectName("pushButtonSelectAlgorithmFolder");
        pushButtonSelectAlgorithmFolder->setGeometry(QRect(430, 110, 41, 31));
        pushButtonSelectPIOFile = new QPushButton(CopyBATDialog);
        pushButtonSelectPIOFile->setObjectName("pushButtonSelectPIOFile");
        pushButtonSelectPIOFile->setGeometry(QRect(520, 150, 41, 31));
        pushButtonSelectCameraFile = new QPushButton(CopyBATDialog);
        pushButtonSelectCameraFile->setObjectName("pushButtonSelectCameraFile");
        pushButtonSelectCameraFile->setGeometry(QRect(520, 190, 41, 31));
        pushButtonSelectLightFile = new QPushButton(CopyBATDialog);
        pushButtonSelectLightFile->setObjectName("pushButtonSelectLightFile");
        pushButtonSelectLightFile->setGeometry(QRect(520, 230, 41, 31));
        pushButtonSelectSequenceDLL = new QPushButton(CopyBATDialog);
        pushButtonSelectSequenceDLL->setObjectName("pushButtonSelectSequenceDLL");
        pushButtonSelectSequenceDLL->setGeometry(QRect(520, 270, 41, 31));
        pushButtonSelectGeneralStockers = new QPushButton(CopyBATDialog);
        pushButtonSelectGeneralStockers->setObjectName("pushButtonSelectGeneralStockers");
        pushButtonSelectGeneralStockers->setGeometry(QRect(520, 310, 41, 31));
        pushButtonSelectFilterPath = new QPushButton(CopyBATDialog);
        pushButtonSelectFilterPath->setObjectName("pushButtonSelectFilterPath");
        pushButtonSelectFilterPath->setGeometry(QRect(420, 350, 41, 31));
        pushButtonSelectResultDLL = new QPushButton(CopyBATDialog);
        pushButtonSelectResultDLL->setObjectName("pushButtonSelectResultDLL");
        pushButtonSelectResultDLL->setGeometry(QRect(520, 390, 41, 31));
        pushButtonSaveSetting = new QPushButton(CopyBATDialog);
        pushButtonSaveSetting->setObjectName("pushButtonSaveSetting");
        pushButtonSaveSetting->setGeometry(QRect(460, 760, 101, 23));
        pushButtonLoadSetting = new QPushButton(CopyBATDialog);
        pushButtonLoadSetting->setObjectName("pushButtonLoadSetting");
        pushButtonLoadSetting->setGeometry(QRect(460, 790, 101, 23));
        tableWidgetAdditional = new QTableWidget(CopyBATDialog);
        if (tableWidgetAdditional->columnCount() < 2)
            tableWidgetAdditional->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetAdditional->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetAdditional->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetAdditional->setObjectName("tableWidgetAdditional");
        tableWidgetAdditional->setGeometry(QRect(20, 610, 451, 131));
        tableWidgetAdditional->setSelectionMode(QAbstractItemView::SingleSelection);
        label_12 = new QLabel(CopyBATDialog);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(20, 580, 451, 31));
        pushButtonPlus = new QPushButton(CopyBATDialog);
        pushButtonPlus->setObjectName("pushButtonPlus");
        pushButtonPlus->setGeometry(QRect(481, 610, 81, 34));
        pushButtonMinus = new QPushButton(CopyBATDialog);
        pushButtonMinus->setObjectName("pushButtonMinus");
        pushButtonMinus->setGeometry(QRect(480, 650, 81, 34));
        checkBoxInspectionPlayer = new QCheckBox(CopyBATDialog);
        checkBoxInspectionPlayer->setObjectName("checkBoxInspectionPlayer");
        checkBoxInspectionPlayer->setGeometry(QRect(30, 430, 321, 22));
        checkBoxInspectionEditor = new QCheckBox(CopyBATDialog);
        checkBoxInspectionEditor->setObjectName("checkBoxInspectionEditor");
        checkBoxInspectionEditor->setGeometry(QRect(30, 460, 321, 22));
        checkBoxRepairGUIMain = new QCheckBox(CopyBATDialog);
        checkBoxRepairGUIMain->setObjectName("checkBoxRepairGUIMain");
        checkBoxRepairGUIMain->setGeometry(QRect(30, 490, 321, 22));

        retranslateUi(CopyBATDialog);

        QMetaObject::connectSlotsByName(CopyBATDialog);
    } // setupUi

    void retranslateUi(QDialog *CopyBATDialog)
    {
        CopyBATDialog->setWindowTitle(QCoreApplication::translate("CopyBATDialog", "MakeBAT", nullptr));
        label->setText(QCoreApplication::translate("CopyBATDialog", "BAT\343\203\225\343\202\241\343\202\244\343\203\253\345\220\215", nullptr));
        lineEditBATFile->setText(QCoreApplication::translate("CopyBATDialog", "CopyAll.bat", nullptr));
        pushButtonSelectBATFile->setText(QCoreApplication::translate("CopyBATDialog", "...", nullptr));
        label_2->setText(QCoreApplication::translate("CopyBATDialog", "GUI path", nullptr));
        label_3->setText(QCoreApplication::translate("CopyBATDialog", "Algorithm path", nullptr));
        label_4->setText(QCoreApplication::translate("CopyBATDialog", "PIO", nullptr));
        label_5->setText(QCoreApplication::translate("CopyBATDialog", "Cameral", nullptr));
        label_6->setText(QCoreApplication::translate("CopyBATDialog", "SequenceDLL", nullptr));
        label_7->setText(QCoreApplication::translate("CopyBATDialog", "GeneralStocker", nullptr));
        label_8->setText(QCoreApplication::translate("CopyBATDialog", "Filter path", nullptr));
        label_9->setText(QCoreApplication::translate("CopyBATDialog", "Global.dat\343\203\225\343\202\241\343\202\244\343\203\253", nullptr));
        pushButtonSelectGlobalDat->setText(QCoreApplication::translate("CopyBATDialog", "...", nullptr));
        label_10->setText(QCoreApplication::translate("CopyBATDialog", "ResultDLL", nullptr));
        label_11->setText(QCoreApplication::translate("CopyBATDialog", "LightDLL", nullptr));
        pushButtonMakeBAT->setText(QCoreApplication::translate("CopyBATDialog", "Bat\347\224\237\346\210\220", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CopyBATDialog", "Cancel", nullptr));
        pushButtonSelecGUIFolder->setText(QCoreApplication::translate("CopyBATDialog", "...", nullptr));
        pushButtonSelectAlgorithmFolder->setText(QCoreApplication::translate("CopyBATDialog", "...", nullptr));
        pushButtonSelectPIOFile->setText(QCoreApplication::translate("CopyBATDialog", "...", nullptr));
        pushButtonSelectCameraFile->setText(QCoreApplication::translate("CopyBATDialog", "...", nullptr));
        pushButtonSelectLightFile->setText(QCoreApplication::translate("CopyBATDialog", "...", nullptr));
        pushButtonSelectSequenceDLL->setText(QCoreApplication::translate("CopyBATDialog", "...", nullptr));
        pushButtonSelectGeneralStockers->setText(QCoreApplication::translate("CopyBATDialog", "...", nullptr));
        pushButtonSelectFilterPath->setText(QCoreApplication::translate("CopyBATDialog", "...", nullptr));
        pushButtonSelectResultDLL->setText(QCoreApplication::translate("CopyBATDialog", "...", nullptr));
        pushButtonSaveSetting->setText(QCoreApplication::translate("CopyBATDialog", "Save setting", nullptr));
        pushButtonLoadSetting->setText(QCoreApplication::translate("CopyBATDialog", "Load setting", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetAdditional->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CopyBATDialog", "Source File", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetAdditional->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CopyBATDialog", "Destination", nullptr));
        label_12->setText(QCoreApplication::translate("CopyBATDialog", "\350\277\275\345\212\240\343\203\225\343\202\241\343\202\244\343\203\253", nullptr));
        pushButtonPlus->setText(QCoreApplication::translate("CopyBATDialog", "+", nullptr));
        pushButtonMinus->setText(QCoreApplication::translate("CopyBATDialog", "-", nullptr));
        checkBoxInspectionPlayer->setText(QCoreApplication::translate("CopyBATDialog", "InspectionPlayer", nullptr));
        checkBoxInspectionEditor->setText(QCoreApplication::translate("CopyBATDialog", "InspectionEditor", nullptr));
        checkBoxRepairGUIMain->setText(QCoreApplication::translate("CopyBATDialog", "RepairGUIMain", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CopyBATDialog: public Ui_CopyBATDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYBATDIALOG_H
