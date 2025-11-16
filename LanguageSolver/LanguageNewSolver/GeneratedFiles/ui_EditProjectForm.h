/********************************************************************************
** Form generated from reading UI file 'EditProjectForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITPROJECTFORM_H
#define UI_EDITPROJECTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditProjectForm
{
public:
    QLineEdit *EditFolderReference;
    QPushButton *pushButtonFolderReference;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *EditProjectName;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *EditProjectForm)
    {
        if (EditProjectForm->objectName().isEmpty())
            EditProjectForm->setObjectName("EditProjectForm");
        EditProjectForm->resize(496, 171);
        EditFolderReference = new QLineEdit(EditProjectForm);
        EditFolderReference->setObjectName("EditFolderReference");
        EditFolderReference->setGeometry(QRect(10, 30, 371, 20));
        pushButtonFolderReference = new QPushButton(EditProjectForm);
        pushButtonFolderReference->setObjectName("pushButtonFolderReference");
        pushButtonFolderReference->setGeometry(QRect(390, 30, 81, 23));
        label_5 = new QLabel(EditProjectForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 10, 371, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(EditProjectForm);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 70, 191, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditProjectName = new QLineEdit(EditProjectForm);
        EditProjectName->setObjectName("EditProjectName");
        EditProjectName->setGeometry(QRect(10, 90, 191, 20));
        pushButtonOK = new QPushButton(EditProjectForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 130, 101, 31));
        pushButtonDelete = new QPushButton(EditProjectForm);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(180, 130, 101, 31));
        pushButtonCancel = new QPushButton(EditProjectForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(350, 130, 101, 31));

        retranslateUi(EditProjectForm);

        QMetaObject::connectSlotsByName(EditProjectForm);
    } // setupUi

    void retranslateUi(QDialog *EditProjectForm)
    {
        EditProjectForm->setWindowTitle(QCoreApplication::translate("EditProjectForm", "Dialog", nullptr));
        pushButtonFolderReference->setText(QCoreApplication::translate("EditProjectForm", "...", nullptr));
        label_5->setText(QCoreApplication::translate("EditProjectForm", "Folder reference", nullptr));
        label_6->setText(QCoreApplication::translate("EditProjectForm", "Project Name", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditProjectForm", "OK", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("EditProjectForm", "Delete", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditProjectForm", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditProjectForm: public Ui_EditProjectForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITPROJECTFORM_H
