/********************************************************************************
** Form generated from reading UI file 'DistinguishPixForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTINGUISHPIXFORM_H
#define UI_DISTINGUISHPIXFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_DistinguishPixForm
{
public:
    QLabel *label;
    QLineEdit *lineEditFolderName;
    QPushButton *pushButtonSearchFolder;
    QListWidget *listWidget;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonNG1;
    QPushButton *pushButtonSaveList;
    QPushButton *pushButtonLoadList;
    QPushButton *pushButtonClearList;
    QPushButton *pushButtonScanFolder;
    QPushButton *pushButtonNG2;
    QPushButton *pushButtonNG3;
    QPushButton *pushButtonNG4;
    QPushButton *pushButtonOKForNone;
    QPushButton *pushButtonReleaseOne;

    void setupUi(GUIFormBase *DistinguishPixForm)
    {
        if (DistinguishPixForm->objectName().isEmpty())
            DistinguishPixForm->setObjectName("DistinguishPixForm");
        DistinguishPixForm->resize(398, 595);
        label = new QLabel(DistinguishPixForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 51, 16));
        lineEditFolderName = new QLineEdit(DistinguishPixForm);
        lineEditFolderName->setObjectName("lineEditFolderName");
        lineEditFolderName->setGeometry(QRect(70, 10, 291, 21));
        pushButtonSearchFolder = new QPushButton(DistinguishPixForm);
        pushButtonSearchFolder->setObjectName("pushButtonSearchFolder");
        pushButtonSearchFolder->setGeometry(QRect(360, 10, 31, 21));
        listWidget = new QListWidget(DistinguishPixForm);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(10, 40, 281, 541));
        pushButtonOK = new QPushButton(DistinguishPixForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(300, 120, 93, 28));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonNG1 = new QPushButton(DistinguishPixForm);
        pushButtonNG1->setObjectName("pushButtonNG1");
        pushButtonNG1->setGeometry(QRect(300, 160, 93, 28));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/NG.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonNG1->setIcon(icon1);
        pushButtonSaveList = new QPushButton(DistinguishPixForm);
        pushButtonSaveList->setObjectName("pushButtonSaveList");
        pushButtonSaveList->setGeometry(QRect(300, 460, 93, 28));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSaveList->setIcon(icon2);
        pushButtonLoadList = new QPushButton(DistinguishPixForm);
        pushButtonLoadList->setObjectName("pushButtonLoadList");
        pushButtonLoadList->setGeometry(QRect(300, 500, 93, 28));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Load.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonLoadList->setIcon(icon3);
        pushButtonClearList = new QPushButton(DistinguishPixForm);
        pushButtonClearList->setObjectName("pushButtonClearList");
        pushButtonClearList->setGeometry(QRect(300, 550, 93, 28));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClearList->setIcon(icon4);
        pushButtonScanFolder = new QPushButton(DistinguishPixForm);
        pushButtonScanFolder->setObjectName("pushButtonScanFolder");
        pushButtonScanFolder->setGeometry(QRect(300, 40, 93, 28));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Folder.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonScanFolder->setIcon(icon5);
        pushButtonNG2 = new QPushButton(DistinguishPixForm);
        pushButtonNG2->setObjectName("pushButtonNG2");
        pushButtonNG2->setGeometry(QRect(300, 190, 93, 28));
        pushButtonNG2->setIcon(icon1);
        pushButtonNG3 = new QPushButton(DistinguishPixForm);
        pushButtonNG3->setObjectName("pushButtonNG3");
        pushButtonNG3->setGeometry(QRect(300, 220, 93, 28));
        pushButtonNG3->setIcon(icon1);
        pushButtonNG4 = new QPushButton(DistinguishPixForm);
        pushButtonNG4->setObjectName("pushButtonNG4");
        pushButtonNG4->setGeometry(QRect(300, 250, 93, 28));
        pushButtonNG4->setIcon(icon1);
        pushButtonOKForNone = new QPushButton(DistinguishPixForm);
        pushButtonOKForNone->setObjectName("pushButtonOKForNone");
        pushButtonOKForNone->setGeometry(QRect(300, 390, 93, 28));
        pushButtonOKForNone->setIcon(icon);
        pushButtonReleaseOne = new QPushButton(DistinguishPixForm);
        pushButtonReleaseOne->setObjectName("pushButtonReleaseOne");
        pushButtonReleaseOne->setGeometry(QRect(300, 300, 93, 28));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Qtres/Release.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonReleaseOne->setIcon(icon6);

        retranslateUi(DistinguishPixForm);

        QMetaObject::connectSlotsByName(DistinguishPixForm);
    } // setupUi

    void retranslateUi(GUIFormBase *DistinguishPixForm)
    {
        DistinguishPixForm->setWindowTitle(QCoreApplication::translate("DistinguishPixForm", "Distinguish Pix", nullptr));
        label->setText(QCoreApplication::translate("DistinguishPixForm", "Folder", nullptr));
        pushButtonSearchFolder->setText(QCoreApplication::translate("DistinguishPixForm", "...", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("DistinguishPixForm", "OK", nullptr));
        pushButtonNG1->setText(QCoreApplication::translate("DistinguishPixForm", "NG 1", nullptr));
        pushButtonSaveList->setText(QCoreApplication::translate("DistinguishPixForm", "Save list", nullptr));
        pushButtonLoadList->setText(QCoreApplication::translate("DistinguishPixForm", "Load list", nullptr));
        pushButtonClearList->setText(QCoreApplication::translate("DistinguishPixForm", "Clear list", nullptr));
        pushButtonScanFolder->setText(QCoreApplication::translate("DistinguishPixForm", "Scan folder", nullptr));
        pushButtonNG2->setText(QCoreApplication::translate("DistinguishPixForm", "NG 2", nullptr));
        pushButtonNG3->setText(QCoreApplication::translate("DistinguishPixForm", "NG 3", nullptr));
        pushButtonNG4->setText(QCoreApplication::translate("DistinguishPixForm", "NG 4", nullptr));
        pushButtonOKForNone->setText(QCoreApplication::translate("DistinguishPixForm", "OK for none", nullptr));
        pushButtonReleaseOne->setText(QCoreApplication::translate("DistinguishPixForm", "Release one", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DistinguishPixForm: public Ui_DistinguishPixForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTINGUISHPIXFORM_H
