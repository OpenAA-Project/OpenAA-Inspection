/********************************************************************************
** Form generated from reading UI file 'ColorFolderInputForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORFOLDERINPUTFORM_H
#define UI_COLORFOLDERINPUTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ColorFolderInputForm
{
public:
    QPushButton *ButtonOK;
    QPushButton *ButtonCancel;
    QLabel *label;
    QLineEdit *EditFolderName;

    void setupUi(QDialog *ColorFolderInputForm)
    {
        if (ColorFolderInputForm->objectName().isEmpty())
            ColorFolderInputForm->setObjectName("ColorFolderInputForm");
        ColorFolderInputForm->resize(268, 101);
        ButtonOK = new QPushButton(ColorFolderInputForm);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(10, 60, 121, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        ButtonCancel = new QPushButton(ColorFolderInputForm);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(140, 60, 121, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        label = new QLabel(ColorFolderInputForm);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 10, 151, 16));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        EditFolderName = new QLineEdit(ColorFolderInputForm);
        EditFolderName->setObjectName("EditFolderName");
        EditFolderName->setGeometry(QRect(60, 30, 151, 21));
        EditFolderName->setMaxLength(32);

        retranslateUi(ColorFolderInputForm);

        ButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(ColorFolderInputForm);
    } // setupUi

    void retranslateUi(QDialog *ColorFolderInputForm)
    {
        ColorFolderInputForm->setWindowTitle(QCoreApplication::translate("ColorFolderInputForm", "Dialog", nullptr));
        ButtonOK->setText(QCoreApplication::translate("ColorFolderInputForm", "OK", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("ColorFolderInputForm", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("ColorFolderInputForm", "FolderName", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ColorFolderInputForm: public Ui_ColorFolderInputForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORFOLDERINPUTFORM_H
