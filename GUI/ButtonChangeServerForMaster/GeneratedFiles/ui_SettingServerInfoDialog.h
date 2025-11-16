/********************************************************************************
** Form generated from reading UI file 'SettingServerInfoDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSERVERINFODIALOG_H
#define UI_SETTINGSERVERINFODIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingServerInfoDialog
{
public:
    QLabel *label;
    QLineEdit *lineEditServerName;
    QLabel *label_2;
    QLineEdit *lineEditDBIPAddress;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEditImgePath;
    QListWidget *listWidgetServer;
    QPushButton *pushButtonCreateNew;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonClose;
    QLineEdit *lineEditDBFileName;
    QLabel *label_5;
    QSpinBox *spinBoxDBPort;

    void setupUi(QDialog *SettingServerInfoDialog)
    {
        if (SettingServerInfoDialog->objectName().isEmpty())
            SettingServerInfoDialog->setObjectName("SettingServerInfoDialog");
        SettingServerInfoDialog->resize(429, 352);
        label = new QLabel(SettingServerInfoDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(180, 10, 111, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        lineEditServerName = new QLineEdit(SettingServerInfoDialog);
        lineEditServerName->setObjectName("lineEditServerName");
        lineEditServerName->setGeometry(QRect(180, 30, 161, 20));
        label_2 = new QLabel(SettingServerInfoDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(180, 60, 111, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        lineEditDBIPAddress = new QLineEdit(SettingServerInfoDialog);
        lineEditDBIPAddress->setObjectName("lineEditDBIPAddress");
        lineEditDBIPAddress->setGeometry(QRect(180, 80, 161, 20));
        label_3 = new QLabel(SettingServerInfoDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(180, 110, 111, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(SettingServerInfoDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(180, 210, 111, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        lineEditImgePath = new QLineEdit(SettingServerInfoDialog);
        lineEditImgePath->setObjectName("lineEditImgePath");
        lineEditImgePath->setGeometry(QRect(180, 230, 161, 20));
        listWidgetServer = new QListWidget(SettingServerInfoDialog);
        listWidgetServer->setObjectName("listWidgetServer");
        listWidgetServer->setGeometry(QRect(10, 10, 151, 221));
        pushButtonCreateNew = new QPushButton(SettingServerInfoDialog);
        pushButtonCreateNew->setObjectName("pushButtonCreateNew");
        pushButtonCreateNew->setGeometry(QRect(180, 262, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Make.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCreateNew->setIcon(icon);
        pushButtonUpdate = new QPushButton(SettingServerInfoDialog);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(280, 262, 71, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon1);
        pushButtonDelete = new QPushButton(SettingServerInfoDialog);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(360, 262, 61, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDelete->setIcon(icon2);
        pushButtonClose = new QPushButton(SettingServerInfoDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(150, 310, 101, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon3);
        lineEditDBFileName = new QLineEdit(SettingServerInfoDialog);
        lineEditDBFileName->setObjectName("lineEditDBFileName");
        lineEditDBFileName->setGeometry(QRect(180, 180, 161, 20));
        label_5 = new QLabel(SettingServerInfoDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(180, 160, 111, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        spinBoxDBPort = new QSpinBox(SettingServerInfoDialog);
        spinBoxDBPort->setObjectName("spinBoxDBPort");
        spinBoxDBPort->setGeometry(QRect(180, 130, 71, 22));
        spinBoxDBPort->setMaximum(65535);

        retranslateUi(SettingServerInfoDialog);

        QMetaObject::connectSlotsByName(SettingServerInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingServerInfoDialog)
    {
        SettingServerInfoDialog->setWindowTitle(QCoreApplication::translate("SettingServerInfoDialog", "Setting Server-Info", nullptr));
        label->setText(QCoreApplication::translate("SettingServerInfoDialog", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("SettingServerInfoDialog", "Database IP / host", nullptr));
        label_3->setText(QCoreApplication::translate("SettingServerInfoDialog", "Database port", nullptr));
        label_4->setText(QCoreApplication::translate("SettingServerInfoDialog", "Master image path", nullptr));
        pushButtonCreateNew->setText(QCoreApplication::translate("SettingServerInfoDialog", "Create new", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("SettingServerInfoDialog", "Update", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("SettingServerInfoDialog", "Delete", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SettingServerInfoDialog", "Close", nullptr));
        label_5->setText(QCoreApplication::translate("SettingServerInfoDialog", "Database FileName", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingServerInfoDialog: public Ui_SettingServerInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSERVERINFODIALOG_H
