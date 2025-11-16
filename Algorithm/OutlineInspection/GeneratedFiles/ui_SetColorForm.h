/********************************************************************************
** Form generated from reading UI file 'SetColorForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETCOLORFORM_H
#define UI_SETCOLORFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetColorFormClass
{
public:
    QFrame *frameRegistPanel;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QFrame *frameColorPanel;

    void setupUi(QDialog *SetColorFormClass)
    {
        if (SetColorFormClass->objectName().isEmpty())
            SetColorFormClass->setObjectName("SetColorFormClass");
        SetColorFormClass->resize(652, 462);
        frameRegistPanel = new QFrame(SetColorFormClass);
        frameRegistPanel->setObjectName("frameRegistPanel");
        frameRegistPanel->setGeometry(QRect(440, 10, 204, 444));
        frameRegistPanel->setFrameShape(QFrame::StyledPanel);
        frameRegistPanel->setFrameShadow(QFrame::Raised);
        pushButtonOK = new QPushButton(SetColorFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(60, 420, 111, 31));
        pushButtonCancel = new QPushButton(SetColorFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(280, 420, 111, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        frameColorPanel = new QFrame(SetColorFormClass);
        frameColorPanel->setObjectName("frameColorPanel");
        frameColorPanel->setGeometry(QRect(10, 10, 420, 356));
        frameColorPanel->setFrameShape(QFrame::StyledPanel);
        frameColorPanel->setFrameShadow(QFrame::Raised);

        retranslateUi(SetColorFormClass);

        QMetaObject::connectSlotsByName(SetColorFormClass);
    } // setupUi

    void retranslateUi(QDialog *SetColorFormClass)
    {
        SetColorFormClass->setWindowTitle(QCoreApplication::translate("SetColorFormClass", "SetColorForm", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SetColorFormClass", "\350\250\255\345\256\232", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SetColorFormClass", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetColorFormClass: public Ui_SetColorFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETCOLORFORM_H
