/********************************************************************************
** Form generated from reading UI file 'LibFolderInputForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIBFOLDERINPUTFORM_H
#define UI_LIBFOLDERINPUTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LibFolderInputForm
{
public:
    QLineEdit *EditFolderName;
    QPushButton *ButtonCancel;
    QPushButton *ButtonOK;
    QLabel *label;

    void setupUi(QDialog *LibFolderInputForm)
    {
        if (LibFolderInputForm->objectName().isEmpty())
            LibFolderInputForm->setObjectName("LibFolderInputForm");
        LibFolderInputForm->resize(269, 100);
        EditFolderName = new QLineEdit(LibFolderInputForm);
        EditFolderName->setObjectName("EditFolderName");
        EditFolderName->setGeometry(QRect(30, 30, 211, 21));
        EditFolderName->setMaxLength(32);
        ButtonCancel = new QPushButton(LibFolderInputForm);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(140, 60, 121, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon);
        ButtonOK = new QPushButton(LibFolderInputForm);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(10, 60, 121, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon1);
        label = new QLabel(LibFolderInputForm);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 10, 211, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);

        retranslateUi(LibFolderInputForm);

        ButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(LibFolderInputForm);
    } // setupUi

    void retranslateUi(QDialog *LibFolderInputForm)
    {
        LibFolderInputForm->setWindowTitle(QCoreApplication::translate("LibFolderInputForm", "Dialog", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("LibFolderInputForm", "Cancel", nullptr));
        ButtonOK->setText(QCoreApplication::translate("LibFolderInputForm", "OK", nullptr));
        label->setText(QCoreApplication::translate("LibFolderInputForm", "FolderName", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LibFolderInputForm: public Ui_LibFolderInputForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIBFOLDERINPUTFORM_H
