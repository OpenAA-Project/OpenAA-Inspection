/********************************************************************************
** Form generated from reading UI file 'Maintainer.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINTAINER_H
#define UI_MAINTAINER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MaintainerClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonSettingDelete;
    QPushButton *pushButtonSettingBackup;
    QPushButton *pushButtonSetting;
    QProgressBar *progressBar;
    QListWidget *listWidget;
    QLabel *labelAction;
    QLabel *labelPath;
    QPushButton *pushButtonExecuteNow;

    void setupUi(QMainWindow *MaintainerClass)
    {
        if (MaintainerClass->objectName().isEmpty())
            MaintainerClass->setObjectName("MaintainerClass");
        MaintainerClass->resize(547, 259);
        centralWidget = new QWidget(MaintainerClass);
        centralWidget->setObjectName("centralWidget");
        pushButtonSettingDelete = new QPushButton(centralWidget);
        pushButtonSettingDelete->setObjectName("pushButtonSettingDelete");
        pushButtonSettingDelete->setGeometry(QRect(10, 10, 151, 34));
        pushButtonSettingBackup = new QPushButton(centralWidget);
        pushButtonSettingBackup->setObjectName("pushButtonSettingBackup");
        pushButtonSettingBackup->setGeometry(QRect(10, 50, 151, 34));
        pushButtonSetting = new QPushButton(centralWidget);
        pushButtonSetting->setObjectName("pushButtonSetting");
        pushButtonSetting->setGeometry(QRect(10, 90, 151, 34));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(10, 230, 161, 23));
        progressBar->setValue(24);
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(180, 10, 361, 241));
        labelAction = new QLabel(centralWidget);
        labelAction->setObjectName("labelAction");
        labelAction->setGeometry(QRect(10, 190, 151, 16));
        labelPath = new QLabel(centralWidget);
        labelPath->setObjectName("labelPath");
        labelPath->setGeometry(QRect(10, 210, 151, 16));
        pushButtonExecuteNow = new QPushButton(centralWidget);
        pushButtonExecuteNow->setObjectName("pushButtonExecuteNow");
        pushButtonExecuteNow->setGeometry(QRect(10, 140, 151, 34));
        MaintainerClass->setCentralWidget(centralWidget);

        retranslateUi(MaintainerClass);

        QMetaObject::connectSlotsByName(MaintainerClass);
    } // setupUi

    void retranslateUi(QMainWindow *MaintainerClass)
    {
        MaintainerClass->setWindowTitle(QCoreApplication::translate("MaintainerClass", "Maintainer", nullptr));
        pushButtonSettingDelete->setText(QCoreApplication::translate("MaintainerClass", "\345\211\212\351\231\244\350\250\255\345\256\232", nullptr));
        pushButtonSettingBackup->setText(QCoreApplication::translate("MaintainerClass", "\343\203\220\343\203\203\343\202\257\343\202\242\343\203\203\343\203\227\350\250\255\345\256\232", nullptr));
        pushButtonSetting->setText(QCoreApplication::translate("MaintainerClass", "\343\203\255\343\202\260\350\250\255\345\256\232", nullptr));
        labelAction->setText(QCoreApplication::translate("MaintainerClass", "Action", nullptr));
        labelPath->setText(QCoreApplication::translate("MaintainerClass", "Path", nullptr));
        pushButtonExecuteNow->setText(QCoreApplication::translate("MaintainerClass", "\344\273\212\345\256\237\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MaintainerClass: public Ui_MaintainerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINTAINER_H
