/********************************************************************************
** Form generated from reading UI file 'SettingDeleteDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDELETEDIALOG_H
#define UI_SETTINGDELETEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingDeleteDialog
{
public:
    QPushButton *pushButtonOK;
    QLabel *label_8;
    QSpinBox *spinBoxCheckingHour;
    QSpinBox *spinBoxCheckingMinute;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_2;
    QCheckBox *checkBoxImagePrioritySpace;
    QSpinBox *spinBoxImageKeepingSpace;
    QSpinBox *spinBoxImageKeepingMonths;
    QLabel *label_5;
    QFrame *frame;
    QCheckBox *checkBoxImageKeepMonths;
    QCheckBox *checkBoxImageKeepDays;
    QSpinBox *spinBoxImageKeepingDays;
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
    QLabel *label_3;

    void setupUi(QDialog *SettingDeleteDialog)
    {
        if (SettingDeleteDialog->objectName().isEmpty())
            SettingDeleteDialog->setObjectName("SettingDeleteDialog");
        SettingDeleteDialog->resize(540, 346);
        pushButtonOK = new QPushButton(SettingDeleteDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(390, 300, 112, 34));
        label_8 = new QLabel(SettingDeleteDialog);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 280, 241, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        spinBoxCheckingHour = new QSpinBox(SettingDeleteDialog);
        spinBoxCheckingHour->setObjectName("spinBoxCheckingHour");
        spinBoxCheckingHour->setGeometry(QRect(0, 310, 54, 24));
        spinBoxCheckingHour->setMaximum(23);
        spinBoxCheckingMinute = new QSpinBox(SettingDeleteDialog);
        spinBoxCheckingMinute->setObjectName("spinBoxCheckingMinute");
        spinBoxCheckingMinute->setGeometry(QRect(110, 310, 54, 24));
        spinBoxCheckingMinute->setMaximum(59);
        label_9 = new QLabel(SettingDeleteDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(60, 310, 41, 21));
        label_10 = new QLabel(SettingDeleteDialog);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(170, 310, 61, 21));
        label = new QLabel(SettingDeleteDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(280, 10, 211, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(SettingDeleteDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(410, 180, 71, 20));
        label_2 = new QLabel(SettingDeleteDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(410, 40, 71, 20));
        checkBoxImagePrioritySpace = new QCheckBox(SettingDeleteDialog);
        checkBoxImagePrioritySpace->setObjectName("checkBoxImagePrioritySpace");
        checkBoxImagePrioritySpace->setGeometry(QRect(330, 150, 151, 22));
        spinBoxImageKeepingSpace = new QSpinBox(SettingDeleteDialog);
        spinBoxImageKeepingSpace->setObjectName("spinBoxImageKeepingSpace");
        spinBoxImageKeepingSpace->setGeometry(QRect(300, 180, 101, 24));
        spinBoxImageKeepingSpace->setMaximum(99999999);
        spinBoxImageKeepingMonths = new QSpinBox(SettingDeleteDialog);
        spinBoxImageKeepingMonths->setObjectName("spinBoxImageKeepingMonths");
        spinBoxImageKeepingMonths->setGeometry(QRect(323, 70, 81, 24));
        spinBoxImageKeepingMonths->setMaximum(99999999);
        label_5 = new QLabel(SettingDeleteDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(410, 70, 71, 20));
        frame = new QFrame(SettingDeleteDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(280, 40, 41, 51));
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
        spinBoxImageKeepingDays = new QSpinBox(SettingDeleteDialog);
        spinBoxImageKeepingDays->setObjectName("spinBoxImageKeepingDays");
        spinBoxImageKeepingDays->setGeometry(QRect(323, 40, 81, 24));
        spinBoxImageKeepingDays->setMaximum(99999999);
        tabWidget_2 = new QTabWidget(SettingDeleteDialog);
        tabWidget_2->setObjectName("tabWidget_2");
        tabWidget_2->setGeometry(QRect(0, 10, 271, 251));
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
        label_3 = new QLabel(SettingDeleteDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(280, 120, 211, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);

        retranslateUi(SettingDeleteDialog);

        tabWidget_2->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SettingDeleteDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDeleteDialog)
    {
        SettingDeleteDialog->setWindowTitle(QCoreApplication::translate("SettingDeleteDialog", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDeleteDialog", "OK", nullptr));
        label_8->setText(QCoreApplication::translate("SettingDeleteDialog", "Checking time (Every day)", nullptr));
        label_9->setText(QCoreApplication::translate("SettingDeleteDialog", "Hour", nullptr));
        label_10->setText(QCoreApplication::translate("SettingDeleteDialog", "Minute", nullptr));
        label->setText(QCoreApplication::translate("SettingDeleteDialog", "Keeping term", nullptr));
        label_4->setText(QCoreApplication::translate("SettingDeleteDialog", "GB", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDeleteDialog", "days", nullptr));
        checkBoxImagePrioritySpace->setText(QCoreApplication::translate("SettingDeleteDialog", "Priority space", nullptr));
        label_5->setText(QCoreApplication::translate("SettingDeleteDialog", "Month", nullptr));
        checkBoxImageKeepMonths->setText(QString());
        checkBoxImageKeepDays->setText(QString());
        label_6->setText(QCoreApplication::translate("SettingDeleteDialog", "Image file name with path", nullptr));
        pushButtonImageSubLine->setText(QCoreApplication::translate("SettingDeleteDialog", "-", nullptr));
        pushButtonImageAddFileName->setText(QCoreApplication::translate("SettingDeleteDialog", "+", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_2), QCoreApplication::translate("SettingDeleteDialog", "File", nullptr));
        pushButtonImageSubFolder->setText(QCoreApplication::translate("SettingDeleteDialog", "-", nullptr));
        pushButtonImageAddFolderName->setText(QCoreApplication::translate("SettingDeleteDialog", "+", nullptr));
        label_7->setText(QCoreApplication::translate("SettingDeleteDialog", "Folder name list", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QCoreApplication::translate("SettingDeleteDialog", "Folder", nullptr));
        label_3->setText(QCoreApplication::translate("SettingDeleteDialog", "Keeping remaining space", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDeleteDialog: public Ui_SettingDeleteDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDELETEDIALOG_H
