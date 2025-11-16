/********************************************************************************
** Form generated from reading UI file 'CreateClassForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATECLASSFORM_H
#define UI_CREATECLASSFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CreateClassForm
{
public:
    QLineEdit *lineEditName;
    QPushButton *pushButtonCancel;
    QLabel *label;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *CreateClassForm)
    {
        if (CreateClassForm->objectName().isEmpty())
            CreateClassForm->setObjectName("CreateClassForm");
        CreateClassForm->resize(343, 101);
        lineEditName = new QLineEdit(CreateClassForm);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(10, 30, 321, 20));
        pushButtonCancel = new QPushButton(CreateClassForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(220, 60, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        label = new QLabel(CreateClassForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 321, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonOK = new QPushButton(CreateClassForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(40, 60, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);

        retranslateUi(CreateClassForm);

        QMetaObject::connectSlotsByName(CreateClassForm);
    } // setupUi

    void retranslateUi(QDialog *CreateClassForm)
    {
        CreateClassForm->setWindowTitle(QCoreApplication::translate("CreateClassForm", "Dialog", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CreateClassForm", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("CreateClassForm", "Class Name", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("CreateClassForm", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateClassForm: public Ui_CreateClassForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATECLASSFORM_H
