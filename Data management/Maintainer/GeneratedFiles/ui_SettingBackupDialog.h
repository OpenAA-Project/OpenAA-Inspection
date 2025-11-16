/********************************************************************************
** Form generated from reading UI file 'SettingBackupDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGBACKUPDIALOG_H
#define UI_SETTINGBACKUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingBackupDialog
{
public:
    QLabel *label_9;
    QSpinBox *spinBoxCheckingHour;
    QLabel *label_10;
    QPushButton *pushButtonOK;
    QLabel *label_8;
    QSpinBox *spinBoxCheckingMinute;
    QLabel *label_3;
    QSpinBox *spinBoxImageKeepingSpace;
    QTabWidget *tabWidget_2;
    QWidget *tab_2;
    QLabel *label_6;
    QListWidget *listWidgetImageFileNames;
    QPushButton *pushButtonImageSubLine;
    QPushButton *pushButtonImageAddFileName;
    QWidget *tab_3;
    QListWidget *listWidgetImageFolderNames;
    QPushButton *pushButtonImageSubFolder;
    QPushButton *pushButtonImageAddFolderName;
    QLabel *label_7;
    QFrame *frame;
    QCheckBox *checkBoxImageKeepMonths;
    QCheckBox *checkBoxImageKeepDays;
    QSpinBox *spinBoxImageKeepingMonths;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxImageKeepingDays;
    QCheckBox *checkBoxImagePrioritySpace;
    QLabel *label_5;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *lineEditDestinationPath;
    QPushButton *pushButtonSelectDestinationPath;

    void setupUi(QDialog *SettingBackupDialog)
    {
        if (SettingBackupDialog->objectName().isEmpty())
            SettingBackupDialog->setObjectName("SettingBackupDialog");
        SettingBackupDialog->resize(539, 444);
        label_9 = new QLabel(SettingBackupDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(70, 410, 41, 21));
        spinBoxCheckingHour = new QSpinBox(SettingBackupDialog);
        spinBoxCheckingHour->setObjectName("spinBoxCheckingHour");
        spinBoxCheckingHour->setGeometry(QRect(10, 410, 54, 24));
        spinBoxCheckingHour->setMaximum(23);
        label_10 = new QLabel(SettingBackupDialog);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(180, 410, 61, 21));
        pushButtonOK = new QPushButton(SettingBackupDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(400, 400, 112, 34));
        label_8 = new QLabel(SettingBackupDialog);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 380, 241, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        spinBoxCheckingMinute = new QSpinBox(SettingBackupDialog);
        spinBoxCheckingMinute->setObjectName("spinBoxCheckingMinute");
        spinBoxCheckingMinute->setGeometry(QRect(120, 410, 54, 24));
        spinBoxCheckingMinute->setMaximum(59);
        label_3 = new QLabel(SettingBackupDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(310, 140, 211, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        spinBoxImageKeepingSpace = new QSpinBox(SettingBackupDialog);
        spinBoxImageKeepingSpace->setObjectName("spinBoxImageKeepingSpace");
        spinBoxImageKeepingSpace->setGeometry(QRect(330, 200, 101, 24));
        spinBoxImageKeepingSpace->setMaximum(99999999);
        tabWidget_2 = new QTabWidget(SettingBackupDialog);
        tabWidget_2->setObjectName("tabWidget_2");
        tabWidget_2->setGeometry(QRect(30, 30, 271, 251));
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        label_6 = new QLabel(tab_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 10, 251, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        listWidgetImageFileNames = new QListWidget(tab_2);
        listWidgetImageFileNames->setObjectName("listWidgetImageFileNames");
        listWidgetImageFileNames->setGeometry(QRect(0, 30, 251, 141));
        pushButtonImageSubLine = new QPushButton(tab_2);
        pushButtonImageSubLine->setObjectName("pushButtonImageSubLine");
        pushButtonImageSubLine->setGeometry(QRect(180, 180, 61, 34));
        pushButtonImageAddFileName = new QPushButton(tab_2);
        pushButtonImageAddFileName->setObjectName("pushButtonImageAddFileName");
        pushButtonImageAddFileName->setGeometry(QRect(10, 180, 61, 34));
        tabWidget_2->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        listWidgetImageFolderNames = new QListWidget(tab_3);
        listWidgetImageFolderNames->setObjectName("listWidgetImageFolderNames");
        listWidgetImageFolderNames->setGeometry(QRect(0, 30, 251, 141));
        pushButtonImageSubFolder = new QPushButton(tab_3);
        pushButtonImageSubFolder->setObjectName("pushButtonImageSubFolder");
        pushButtonImageSubFolder->setGeometry(QRect(180, 180, 61, 34));
        pushButtonImageAddFolderName = new QPushButton(tab_3);
        pushButtonImageAddFolderName->setObjectName("pushButtonImageAddFolderName");
        pushButtonImageAddFolderName->setGeometry(QRect(10, 180, 61, 34));
        label_7 = new QLabel(tab_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 10, 251, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        tabWidget_2->addTab(tab_3, QString());
        frame = new QFrame(SettingBackupDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(310, 60, 41, 51));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        checkBoxImageKeepMonths = new QCheckBox(frame);
        checkBoxImageKeepMonths->setObjectName("checkBoxImageKeepMonths");
        checkBoxImageKeepMonths->setGeometry(QRect(10, 30, 31, 22));
        checkBoxImageKeepMonths->setChecked(false);
        checkBoxImageKeepMonths->setAutoExclusive(true);
        checkBoxImageKeepDays = new QCheckBox(frame);
        checkBoxImageKeepDays->setObjectName("checkBoxImageKeepDays");
        checkBoxImageKeepDays->setGeometry(QRect(10, 0, 31, 22));
        checkBoxImageKeepDays->setChecked(true);
        checkBoxImageKeepDays->setAutoExclusive(true);
        spinBoxImageKeepingMonths = new QSpinBox(SettingBackupDialog);
        spinBoxImageKeepingMonths->setObjectName("spinBoxImageKeepingMonths");
        spinBoxImageKeepingMonths->setGeometry(QRect(353, 90, 81, 24));
        spinBoxImageKeepingMonths->setMaximum(99999999);
        label_4 = new QLabel(SettingBackupDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(430, 190, 71, 20));
        label = new QLabel(SettingBackupDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(310, 30, 211, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(SettingBackupDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(440, 60, 71, 20));
        spinBoxImageKeepingDays = new QSpinBox(SettingBackupDialog);
        spinBoxImageKeepingDays->setObjectName("spinBoxImageKeepingDays");
        spinBoxImageKeepingDays->setGeometry(QRect(353, 60, 81, 24));
        spinBoxImageKeepingDays->setMaximum(99999999);
        checkBoxImagePrioritySpace = new QCheckBox(SettingBackupDialog);
        checkBoxImagePrioritySpace->setObjectName("checkBoxImagePrioritySpace");
        checkBoxImagePrioritySpace->setGeometry(QRect(360, 170, 151, 22));
        label_5 = new QLabel(SettingBackupDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(440, 90, 71, 20));
        label_11 = new QLabel(SettingBackupDialog);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(0, 0, 531, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_12 = new QLabel(SettingBackupDialog);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(0, 290, 531, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        lineEditDestinationPath = new QLineEdit(SettingBackupDialog);
        lineEditDestinationPath->setObjectName("lineEditDestinationPath");
        lineEditDestinationPath->setGeometry(QRect(40, 310, 461, 21));
        pushButtonSelectDestinationPath = new QPushButton(SettingBackupDialog);
        pushButtonSelectDestinationPath->setObjectName("pushButtonSelectDestinationPath");
        pushButtonSelectDestinationPath->setGeometry(QRect(500, 310, 31, 23));

        retranslateUi(SettingBackupDialog);

        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingBackupDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingBackupDialog)
    {
        SettingBackupDialog->setWindowTitle(QCoreApplication::translate("SettingBackupDialog", "Dialog", nullptr));
        label_9->setText(QCoreApplication::translate("SettingBackupDialog", "Hour", nullptr));
        label_10->setText(QCoreApplication::translate("SettingBackupDialog", "Minute", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingBackupDialog", "OK", nullptr));
        label_8->setText(QCoreApplication::translate("SettingBackupDialog", "Checking time (Every day)", nullptr));
        label_3->setText(QCoreApplication::translate("SettingBackupDialog", "Keeping remaining space", nullptr));
        label_6->setText(QCoreApplication::translate("SettingBackupDialog", "Image file name with path", nullptr));
        pushButtonImageSubLine->setText(QCoreApplication::translate("SettingBackupDialog", "-", nullptr));
        pushButtonImageAddFileName->setText(QCoreApplication::translate("SettingBackupDialog", "+", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_2), QCoreApplication::translate("SettingBackupDialog", "File", nullptr));
        pushButtonImageSubFolder->setText(QCoreApplication::translate("SettingBackupDialog", "-", nullptr));
        pushButtonImageAddFolderName->setText(QCoreApplication::translate("SettingBackupDialog", "+", nullptr));
        label_7->setText(QCoreApplication::translate("SettingBackupDialog", "Folder name list", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QCoreApplication::translate("SettingBackupDialog", "Folder", nullptr));
        checkBoxImageKeepMonths->setText(QString());
        checkBoxImageKeepDays->setText(QString());
        label_4->setText(QCoreApplication::translate("SettingBackupDialog", "GB", nullptr));
        label->setText(QCoreApplication::translate("SettingBackupDialog", "Keeping term", nullptr));
        label_2->setText(QCoreApplication::translate("SettingBackupDialog", "days", nullptr));
        checkBoxImagePrioritySpace->setText(QCoreApplication::translate("SettingBackupDialog", "Priority space", nullptr));
        label_5->setText(QCoreApplication::translate("SettingBackupDialog", "Month", nullptr));
        label_11->setText(QCoreApplication::translate("SettingBackupDialog", "Source", nullptr));
        label_12->setText(QCoreApplication::translate("SettingBackupDialog", "Destination", nullptr));
        pushButtonSelectDestinationPath->setText(QCoreApplication::translate("SettingBackupDialog", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingBackupDialog: public Ui_SettingBackupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGBACKUPDIALOG_H
