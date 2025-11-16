/********************************************************************************
** Form generated from reading UI file 'CreateNewRelation.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATENEWRELATION_H
#define UI_CREATENEWRELATION_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CreateNewRelationClass
{
public:
    QLineEdit *EditRemark;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *EditName;
    QLabel *label_3;
    QSpinBox *spinBoxRelationType;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *CreateNewRelationClass)
    {
        if (CreateNewRelationClass->objectName().isEmpty())
            CreateNewRelationClass->setObjectName("CreateNewRelationClass");
        CreateNewRelationClass->resize(632, 172);
        EditRemark = new QLineEdit(CreateNewRelationClass);
        EditRemark->setObjectName("EditRemark");
        EditRemark->setGeometry(QRect(340, 30, 281, 21));
        label_2 = new QLabel(CreateNewRelationClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(340, 10, 281, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label = new QLabel(CreateNewRelationClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 321, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        EditName = new QLineEdit(CreateNewRelationClass);
        EditName->setObjectName("EditName");
        EditName->setGeometry(QRect(10, 30, 321, 21));
        label_3 = new QLabel(CreateNewRelationClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 71, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        spinBoxRelationType = new QSpinBox(CreateNewRelationClass);
        spinBoxRelationType->setObjectName("spinBoxRelationType");
        spinBoxRelationType->setGeometry(QRect(10, 90, 71, 22));
        spinBoxRelationType->setMaximum(99999999);
        pushButtonOK = new QPushButton(CreateNewRelationClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(130, 130, 111, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ManageMasterConnection/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(CreateNewRelationClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(340, 130, 111, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ManageMasterConnection/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(CreateNewRelationClass);

        QMetaObject::connectSlotsByName(CreateNewRelationClass);
    } // setupUi

    void retranslateUi(QDialog *CreateNewRelationClass)
    {
        CreateNewRelationClass->setWindowTitle(QCoreApplication::translate("CreateNewRelationClass", "CreateNewRelation", nullptr));
        label_2->setText(QCoreApplication::translate("CreateNewRelationClass", "Remark", nullptr));
        label->setText(QCoreApplication::translate("CreateNewRelationClass", "Master Name", nullptr));
        label_3->setText(QCoreApplication::translate("CreateNewRelationClass", "TYPE Code", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("CreateNewRelationClass", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CreateNewRelationClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateNewRelationClass: public Ui_CreateNewRelationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATENEWRELATION_H
