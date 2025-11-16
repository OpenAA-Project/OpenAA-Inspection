/********************************************************************************
** Form generated from reading UI file 'NewProjectForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROJECTFORM_H
#define UI_NEWPROJECTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NewProjectForm
{
public:
    QLineEdit *lineEditProjectName;
    QLabel *label;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonDelete;

    void setupUi(QDialog *NewProjectForm)
    {
        if (NewProjectForm->objectName().isEmpty())
            NewProjectForm->setObjectName("NewProjectForm");
        NewProjectForm->resize(400, 102);
        lineEditProjectName = new QLineEdit(NewProjectForm);
        lineEditProjectName->setObjectName("lineEditProjectName");
        lineEditProjectName->setGeometry(QRect(20, 30, 361, 20));
        label = new QLabel(NewProjectForm);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 361, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(NewProjectForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(60, 60, 81, 31));
        pushButtonCancel = new QPushButton(NewProjectForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(270, 60, 81, 31));
        pushButtonDelete = new QPushButton(NewProjectForm);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(170, 60, 81, 31));

        retranslateUi(NewProjectForm);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(NewProjectForm);
    } // setupUi

    void retranslateUi(QDialog *NewProjectForm)
    {
        NewProjectForm->setWindowTitle(QCoreApplication::translate("NewProjectForm", "Input Project name", nullptr));
        label->setText(QCoreApplication::translate("NewProjectForm", "Project Name", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("NewProjectForm", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("NewProjectForm", "Cancel", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("NewProjectForm", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewProjectForm: public Ui_NewProjectForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROJECTFORM_H
