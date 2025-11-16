/********************************************************************************
** Form generated from reading UI file 'PasswordDropper.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWORDDROPPER_H
#define UI_PASSWORDDROPPER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PasswordDropper
{
public:
    QPushButton *pushButtonLoad;
    QListWidget *listWidgetControl;
    QPushButton *pushButtonSetDropFilter;
    QPushButton *pushButtonSaveDefault;
    QListWidget *listWidgetPassword;
    QPushButton *pushButtonCreatePassword;
    QPushButton *pushButtonCreateClass;
    QPushButton *pushButtonDeleteControl;
    QLabel *label_3;
    QListWidget *listWidgetClass;
    QPushButton *pushButtonDeletPassword;
    QPushButton *pushButtonDeleteClass;
    QPushButton *pushButtonModifyPassword;
    QPushButton *pushButtonModifyClass;
    QPushButton *pushButtonLoadDefault;
    QLabel *label;
    QLabel *label_4;
    QSpinBox *spinBoxExpiredTime;
    QLabel *labelDrag;
    QLabel *label_2;
    QPushButton *pushButtonSave;

    void setupUi(QWidget *PasswordDropper)
    {
        if (PasswordDropper->objectName().isEmpty())
            PasswordDropper->setObjectName("PasswordDropper");
        PasswordDropper->resize(653, 393);
        pushButtonLoad = new QPushButton(PasswordDropper);
        pushButtonLoad->setObjectName("pushButtonLoad");
        pushButtonLoad->setGeometry(QRect(410, 310, 91, 31));
        listWidgetControl = new QListWidget(PasswordDropper);
        listWidgetControl->setObjectName("listWidgetControl");
        listWidgetControl->setGeometry(QRect(340, 80, 301, 192));
        pushButtonSetDropFilter = new QPushButton(PasswordDropper);
        pushButtonSetDropFilter->setObjectName("pushButtonSetDropFilter");
        pushButtonSetDropFilter->setGeometry(QRect(20, 10, 141, 31));
        pushButtonSetDropFilter->setCheckable(true);
        pushButtonSaveDefault = new QPushButton(PasswordDropper);
        pushButtonSaveDefault->setObjectName("pushButtonSaveDefault");
        pushButtonSaveDefault->setGeometry(QRect(510, 350, 111, 31));
        listWidgetPassword = new QListWidget(PasswordDropper);
        listWidgetPassword->setObjectName("listWidgetPassword");
        listWidgetPassword->setGeometry(QRect(180, 80, 151, 192));
        pushButtonCreatePassword = new QPushButton(PasswordDropper);
        pushButtonCreatePassword->setObjectName("pushButtonCreatePassword");
        pushButtonCreatePassword->setGeometry(QRect(180, 280, 75, 23));
        pushButtonCreateClass = new QPushButton(PasswordDropper);
        pushButtonCreateClass->setObjectName("pushButtonCreateClass");
        pushButtonCreateClass->setGeometry(QRect(10, 280, 75, 23));
        pushButtonDeleteControl = new QPushButton(PasswordDropper);
        pushButtonDeleteControl->setObjectName("pushButtonDeleteControl");
        pushButtonDeleteControl->setGeometry(QRect(410, 280, 91, 23));
        label_3 = new QLabel(PasswordDropper);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(180, 60, 151, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetClass = new QListWidget(PasswordDropper);
        listWidgetClass->setObjectName("listWidgetClass");
        listWidgetClass->setGeometry(QRect(10, 80, 161, 192));
        pushButtonDeletPassword = new QPushButton(PasswordDropper);
        pushButtonDeletPassword->setObjectName("pushButtonDeletPassword");
        pushButtonDeletPassword->setGeometry(QRect(260, 280, 75, 23));
        pushButtonDeleteClass = new QPushButton(PasswordDropper);
        pushButtonDeleteClass->setObjectName("pushButtonDeleteClass");
        pushButtonDeleteClass->setGeometry(QRect(90, 280, 75, 23));
        pushButtonModifyPassword = new QPushButton(PasswordDropper);
        pushButtonModifyPassword->setObjectName("pushButtonModifyPassword");
        pushButtonModifyPassword->setGeometry(QRect(180, 310, 75, 23));
        pushButtonModifyClass = new QPushButton(PasswordDropper);
        pushButtonModifyClass->setObjectName("pushButtonModifyClass");
        pushButtonModifyClass->setGeometry(QRect(10, 310, 75, 23));
        pushButtonLoadDefault = new QPushButton(PasswordDropper);
        pushButtonLoadDefault->setObjectName("pushButtonLoadDefault");
        pushButtonLoadDefault->setGeometry(QRect(510, 310, 111, 31));
        label = new QLabel(PasswordDropper);
        label->setObjectName("label");
        label->setGeometry(QRect(210, 20, 131, 16));
        label_4 = new QLabel(PasswordDropper);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(340, 60, 301, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxExpiredTime = new QSpinBox(PasswordDropper);
        spinBoxExpiredTime->setObjectName("spinBoxExpiredTime");
        spinBoxExpiredTime->setGeometry(QRect(350, 20, 101, 22));
        spinBoxExpiredTime->setMaximum(99999999);
        labelDrag = new QLabel(PasswordDropper);
        labelDrag->setObjectName("labelDrag");
        labelDrag->setGeometry(QRect(530, 10, 61, 41));
        labelDrag->setFrameShape(QFrame::Panel);
        labelDrag->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(PasswordDropper);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(9, 60, 161, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSave = new QPushButton(PasswordDropper);
        pushButtonSave->setObjectName("pushButtonSave");
        pushButtonSave->setGeometry(QRect(410, 350, 91, 31));

        retranslateUi(PasswordDropper);

        QMetaObject::connectSlotsByName(PasswordDropper);
    } // setupUi

    void retranslateUi(QWidget *PasswordDropper)
    {
        PasswordDropper->setWindowTitle(QCoreApplication::translate("PasswordDropper", "Form", nullptr));
        pushButtonLoad->setText(QCoreApplication::translate("PasswordDropper", "Load", nullptr));
        pushButtonSetDropFilter->setText(QCoreApplication::translate("PasswordDropper", "Set Drop filter", nullptr));
        pushButtonSaveDefault->setText(QCoreApplication::translate("PasswordDropper", "Save default", nullptr));
        pushButtonCreatePassword->setText(QCoreApplication::translate("PasswordDropper", "New", nullptr));
        pushButtonCreateClass->setText(QCoreApplication::translate("PasswordDropper", "New", nullptr));
        pushButtonDeleteControl->setText(QCoreApplication::translate("PasswordDropper", "Delete", nullptr));
        label_3->setText(QCoreApplication::translate("PasswordDropper", "Password", nullptr));
        pushButtonDeletPassword->setText(QCoreApplication::translate("PasswordDropper", "Delete", nullptr));
        pushButtonDeleteClass->setText(QCoreApplication::translate("PasswordDropper", "Delete", nullptr));
        pushButtonModifyPassword->setText(QCoreApplication::translate("PasswordDropper", "Modify", nullptr));
        pushButtonModifyClass->setText(QCoreApplication::translate("PasswordDropper", "Modify", nullptr));
        pushButtonLoadDefault->setText(QCoreApplication::translate("PasswordDropper", "Load default", nullptr));
        label->setText(QCoreApplication::translate("PasswordDropper", "Expired time (sec)", nullptr));
        label_4->setText(QCoreApplication::translate("PasswordDropper", "Control", nullptr));
        labelDrag->setText(QCoreApplication::translate("PasswordDropper", "Drag", nullptr));
        label_2->setText(QCoreApplication::translate("PasswordDropper", "Class", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("PasswordDropper", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PasswordDropper: public Ui_PasswordDropper {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWORDDROPPER_H
