/********************************************************************************
** Form generated from reading UI file 'OutlineOffsetForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTLINEOFFSETFORM_H
#define UI_OUTLINEOFFSETFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OutlineOffsetForm
{
public:
    QPushButton *ButtonCancel;
    QPushButton *ButtonOK;

    void setupUi(QWidget *OutlineOffsetForm)
    {
        if (OutlineOffsetForm->objectName().isEmpty())
            OutlineOffsetForm->setObjectName("OutlineOffsetForm");
        OutlineOffsetForm->resize(708, 577);
        ButtonCancel = new QPushButton(OutlineOffsetForm);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(490, 520, 131, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon);
        ButtonOK = new QPushButton(OutlineOffsetForm);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(80, 520, 131, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon1);

        retranslateUi(OutlineOffsetForm);

        QMetaObject::connectSlotsByName(OutlineOffsetForm);
    } // setupUi

    void retranslateUi(QWidget *OutlineOffsetForm)
    {
        OutlineOffsetForm->setWindowTitle(QCoreApplication::translate("OutlineOffsetForm", "Form", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("OutlineOffsetForm", "Cancel", nullptr));
        ButtonOK->setText(QCoreApplication::translate("OutlineOffsetForm", "OK  Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OutlineOffsetForm: public Ui_OutlineOffsetForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTLINEOFFSETFORM_H
