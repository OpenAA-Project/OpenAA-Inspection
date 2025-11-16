/********************************************************************************
** Form generated from reading UI file 'MasterCategoryInputForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MASTERCATEGORYINPUTFORM_H
#define UI_MASTERCATEGORYINPUTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MasterCategoryInputForm
{
public:
    QLabel *label;
    QPushButton *ButtonOK;
    QLabel *label_2;
    QLineEdit *EditRemark;
    QPushButton *ButtonCancel;
    QLineEdit *EditFolderName;

    void setupUi(QDialog *MasterCategoryInputForm)
    {
        if (MasterCategoryInputForm->objectName().isEmpty())
            MasterCategoryInputForm->setObjectName("MasterCategoryInputForm");
        MasterCategoryInputForm->resize(341, 110);
        label = new QLabel(MasterCategoryInputForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 151, 16));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        ButtonOK = new QPushButton(MasterCategoryInputForm);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(20, 70, 121, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        label_2 = new QLabel(MasterCategoryInputForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(180, 10, 151, 16));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        EditRemark = new QLineEdit(MasterCategoryInputForm);
        EditRemark->setObjectName("EditRemark");
        EditRemark->setGeometry(QRect(180, 30, 151, 21));
        ButtonCancel = new QPushButton(MasterCategoryInputForm);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(190, 70, 121, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        EditFolderName = new QLineEdit(MasterCategoryInputForm);
        EditFolderName->setObjectName("EditFolderName");
        EditFolderName->setGeometry(QRect(10, 30, 151, 21));

        retranslateUi(MasterCategoryInputForm);

        ButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(MasterCategoryInputForm);
    } // setupUi

    void retranslateUi(QDialog *MasterCategoryInputForm)
    {
        MasterCategoryInputForm->setWindowTitle(QCoreApplication::translate("MasterCategoryInputForm", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("MasterCategoryInputForm", "FolderName", nullptr));
        ButtonOK->setText(QCoreApplication::translate("MasterCategoryInputForm", "OK", nullptr));
        label_2->setText(QCoreApplication::translate("MasterCategoryInputForm", "Remark", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("MasterCategoryInputForm", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MasterCategoryInputForm: public Ui_MasterCategoryInputForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASTERCATEGORYINPUTFORM_H
