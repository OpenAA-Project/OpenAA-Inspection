/********************************************************************************
** Form generated from reading UI file 'SettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QListWidget *listWidgetLightDLL;
    QLabel *label;
    QListWidget *listWidgetRegisteredItemList;
    QFrame *frame;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditDLLFileName;
    QLineEdit *lineEditRegistredName;
    QLineEdit *lineEditIPAddress;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *spinBoxPortNumber;
    QLineEdit *lineEditInitialString;
    QLabel *label_6;
    QPushButton *pushButtonSaveNew;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(725, 491);
        listWidgetLightDLL = new QListWidget(SettingDialog);
        listWidgetLightDLL->setObjectName("listWidgetLightDLL");
        listWidgetLightDLL->setGeometry(QRect(10, 30, 701, 192));
        listWidgetLightDLL->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(SettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 111, 16));
        listWidgetRegisteredItemList = new QListWidget(SettingDialog);
        listWidgetRegisteredItemList->setObjectName("listWidgetRegisteredItemList");
        listWidgetRegisteredItemList->setGeometry(QRect(10, 241, 256, 201));
        frame = new QFrame(SettingDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(280, 240, 431, 201));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 40, 111, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 111, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        lineEditDLLFileName = new QLineEdit(frame);
        lineEditDLLFileName->setObjectName("lineEditDLLFileName");
        lineEditDLLFileName->setGeometry(QRect(130, 10, 291, 20));
        lineEditRegistredName = new QLineEdit(frame);
        lineEditRegistredName->setObjectName("lineEditRegistredName");
        lineEditRegistredName->setGeometry(QRect(130, 40, 291, 20));
        lineEditIPAddress = new QLineEdit(frame);
        lineEditIPAddress->setObjectName("lineEditIPAddress");
        lineEditIPAddress->setGeometry(QRect(130, 70, 131, 20));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 70, 111, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 90, 111, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        spinBoxPortNumber = new QSpinBox(frame);
        spinBoxPortNumber->setObjectName("spinBoxPortNumber");
        spinBoxPortNumber->setGeometry(QRect(130, 90, 91, 22));
        spinBoxPortNumber->setMaximum(65535);
        lineEditInitialString = new QLineEdit(frame);
        lineEditInitialString->setObjectName("lineEditInitialString");
        lineEditInitialString->setGeometry(QRect(130, 120, 291, 20));
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 120, 111, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        pushButtonSaveNew = new QPushButton(frame);
        pushButtonSaveNew->setObjectName("pushButtonSaveNew");
        pushButtonSaveNew->setGeometry(QRect(10, 160, 81, 31));
        pushButtonUpdate = new QPushButton(frame);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(120, 160, 81, 31));
        pushButtonDelete = new QPushButton(frame);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(340, 160, 81, 31));
        pushButtonClose = new QPushButton(SettingDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(320, 450, 101, 31));

        retranslateUi(SettingDialog);

        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Setting", nullptr));
        label->setText(QCoreApplication::translate("SettingDialog", "Select Light DLL", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "Name", nullptr));
        label_3->setText(QCoreApplication::translate("SettingDialog", "DLL file path & name", nullptr));
        label_4->setText(QCoreApplication::translate("SettingDialog", "IP Address / Executer", nullptr));
        label_5->setText(QCoreApplication::translate("SettingDialog", "Port number", nullptr));
        label_6->setText(QCoreApplication::translate("SettingDialog", "Initial string", nullptr));
        pushButtonSaveNew->setText(QCoreApplication::translate("SettingDialog", "Save new", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("SettingDialog", "Update", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("SettingDialog", "Delete", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SettingDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
