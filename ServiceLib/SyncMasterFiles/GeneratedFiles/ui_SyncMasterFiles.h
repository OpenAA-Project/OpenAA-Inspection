/********************************************************************************
** Form generated from reading UI file 'SyncMasterFiles.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNCMASTERFILES_H
#define UI_SYNCMASTERFILES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SyncMasterFilesClass
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QListWidget *listWidgetSource;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEditSource;
    QLineEdit *lineEditDestination;
    QListWidget *listWidgetExcluded;
    QLabel *label_6;
    QPushButton *pushButtonAddExcluded;
    QPushButton *pushButtonDelExcluded;
    QLabel *label_3;
    QLabel *label_4;
    QProgressBar *progressBar;
    QLabel *label_5;
    QListWidget *listWidgetAddition;
    QListWidget *listWidgetUpdate;
    QListWidget *listWidgetRemove;

    void setupUi(QMainWindow *SyncMasterFilesClass)
    {
        if (SyncMasterFilesClass->objectName().isEmpty())
            SyncMasterFilesClass->setObjectName("SyncMasterFilesClass");
        SyncMasterFilesClass->resize(743, 505);
        centralWidget = new QWidget(SyncMasterFilesClass);
        centralWidget->setObjectName("centralWidget");
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 391, 461));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        listWidgetSource = new QListWidget(frame);
        listWidgetSource->setObjectName("listWidgetSource");
        listWidgetSource->setGeometry(QRect(10, 30, 371, 291));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 46, 13));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 330, 81, 16));
        lineEditSource = new QLineEdit(frame);
        lineEditSource->setObjectName("lineEditSource");
        lineEditSource->setGeometry(QRect(90, 10, 291, 20));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(212, 208, 200, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditSource->setPalette(palette);
        lineEditSource->setReadOnly(true);
        lineEditDestination = new QLineEdit(frame);
        lineEditDestination->setObjectName("lineEditDestination");
        lineEditDestination->setGeometry(QRect(90, 330, 291, 20));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditDestination->setPalette(palette1);
        lineEditDestination->setReadOnly(true);
        listWidgetExcluded = new QListWidget(frame);
        new QListWidgetItem(listWidgetExcluded);
        listWidgetExcluded->setObjectName("listWidgetExcluded");
        listWidgetExcluded->setGeometry(QRect(90, 360, 281, 91));
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 360, 71, 16));
        pushButtonAddExcluded = new QPushButton(frame);
        pushButtonAddExcluded->setObjectName("pushButtonAddExcluded");
        pushButtonAddExcluded->setGeometry(QRect(20, 390, 51, 23));
        pushButtonDelExcluded = new QPushButton(frame);
        pushButtonDelExcluded->setObjectName("pushButtonDelExcluded");
        pushButtonDelExcluded->setGeometry(QRect(20, 420, 51, 23));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(530, 10, 46, 13));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(530, 320, 46, 13));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(10, 480, 721, 23));
        progressBar->setValue(24);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(530, 170, 46, 13));
        listWidgetAddition = new QListWidget(centralWidget);
        listWidgetAddition->setObjectName("listWidgetAddition");
        listWidgetAddition->setGeometry(QRect(410, 30, 321, 121));
        listWidgetUpdate = new QListWidget(centralWidget);
        listWidgetUpdate->setObjectName("listWidgetUpdate");
        listWidgetUpdate->setGeometry(QRect(410, 190, 321, 121));
        listWidgetRemove = new QListWidget(centralWidget);
        listWidgetRemove->setObjectName("listWidgetRemove");
        listWidgetRemove->setGeometry(QRect(410, 340, 321, 121));
        SyncMasterFilesClass->setCentralWidget(centralWidget);

        retranslateUi(SyncMasterFilesClass);

        QMetaObject::connectSlotsByName(SyncMasterFilesClass);
    } // setupUi

    void retranslateUi(QMainWindow *SyncMasterFilesClass)
    {
        SyncMasterFilesClass->setWindowTitle(QCoreApplication::translate("SyncMasterFilesClass", "SyncMasterFiles", nullptr));
        label->setText(QCoreApplication::translate("SyncMasterFilesClass", "Source", nullptr));
        label_2->setText(QCoreApplication::translate("SyncMasterFilesClass", "Operated folder", nullptr));

        const bool __sortingEnabled = listWidgetExcluded->isSortingEnabled();
        listWidgetExcluded->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidgetExcluded->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("SyncMasterFilesClass", "REGULUS64-2.FDB", nullptr));
        listWidgetExcluded->setSortingEnabled(__sortingEnabled);

        label_6->setText(QCoreApplication::translate("SyncMasterFilesClass", "Excluded files", nullptr));
        pushButtonAddExcluded->setText(QCoreApplication::translate("SyncMasterFilesClass", "+", nullptr));
        pushButtonDelExcluded->setText(QCoreApplication::translate("SyncMasterFilesClass", "-", nullptr));
        label_3->setText(QCoreApplication::translate("SyncMasterFilesClass", "Addition", nullptr));
        label_4->setText(QCoreApplication::translate("SyncMasterFilesClass", "Remove", nullptr));
        label_5->setText(QCoreApplication::translate("SyncMasterFilesClass", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SyncMasterFilesClass: public Ui_SyncMasterFilesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNCMASTERFILES_H
