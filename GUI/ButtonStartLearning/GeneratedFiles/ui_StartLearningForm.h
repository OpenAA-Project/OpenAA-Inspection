/********************************************************************************
** Form generated from reading UI file 'StartLearningForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTLEARNINGFORM_H
#define UI_STARTLEARNINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_StartLearningFormClass
{
public:
    QPushButton *pushButtonStart;
    QComboBox *comboBoxLearningType;
    QListWidget *listWidgetFiles;
    QPushButton *pushButton;
    QProgressBar *progressBar;
    QPushButton *pushButtonClear;

    void setupUi(GUIFormBase *StartLearningFormClass)
    {
        if (StartLearningFormClass->objectName().isEmpty())
            StartLearningFormClass->setObjectName("StartLearningFormClass");
        StartLearningFormClass->resize(200, 325);
        pushButtonStart = new QPushButton(StartLearningFormClass);
        pushButtonStart->setObjectName("pushButtonStart");
        pushButtonStart->setGeometry(QRect(10, 240, 181, 51));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Start.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonStart->setIcon(icon);
        comboBoxLearningType = new QComboBox(StartLearningFormClass);
        comboBoxLearningType->addItem(QString());
        comboBoxLearningType->addItem(QString());
        comboBoxLearningType->addItem(QString());
        comboBoxLearningType->setObjectName("comboBoxLearningType");
        comboBoxLearningType->setGeometry(QRect(10, 220, 181, 22));
        listWidgetFiles = new QListWidget(StartLearningFormClass);
        listWidgetFiles->setObjectName("listWidgetFiles");
        listWidgetFiles->setGeometry(QRect(10, 41, 181, 161));
        pushButton = new QPushButton(StartLearningFormClass);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 0, 75, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Load.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon1);
        progressBar = new QProgressBar(StartLearningFormClass);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(10, 300, 181, 23));
        progressBar->setValue(24);
        pushButtonClear = new QPushButton(StartLearningFormClass);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(110, 0, 75, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClear->setIcon(icon2);

        retranslateUi(StartLearningFormClass);

        QMetaObject::connectSlotsByName(StartLearningFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *StartLearningFormClass)
    {
        StartLearningFormClass->setWindowTitle(QCoreApplication::translate("StartLearningFormClass", "StartLearningForm", nullptr));
        pushButtonStart->setText(QCoreApplication::translate("StartLearningFormClass", "Start Learning", nullptr));
        comboBoxLearningType->setItemText(0, QCoreApplication::translate("StartLearningFormClass", "Standard", nullptr));
        comboBoxLearningType->setItemText(1, QCoreApplication::translate("StartLearningFormClass", "Quick", nullptr));
        comboBoxLearningType->setItemText(2, QCoreApplication::translate("StartLearningFormClass", "Complete", nullptr));

        pushButton->setText(QCoreApplication::translate("StartLearningFormClass", "Files", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("StartLearningFormClass", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartLearningFormClass: public Ui_StartLearningFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTLEARNINGFORM_H
