/********************************************************************************
** Form generated from reading UI file 'DisplayLibFolderForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYLIBFOLDERFORM_H
#define UI_DISPLAYLIBFOLDERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_DisplayLibFolderForm
{
public:
    QFrame *frame;
    QFrame *frameButtons;
    QPushButton *pushButtonSet;

    void setupUi(GUIFormBase *DisplayLibFolderForm)
    {
        if (DisplayLibFolderForm->objectName().isEmpty())
            DisplayLibFolderForm->setObjectName("DisplayLibFolderForm");
        DisplayLibFolderForm->resize(332, 399);
        frame = new QFrame(DisplayLibFolderForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 331, 361));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frameButtons = new QFrame(DisplayLibFolderForm);
        frameButtons->setObjectName("frameButtons");
        frameButtons->setGeometry(QRect(0, 360, 331, 41));
        frameButtons->setFrameShape(QFrame::StyledPanel);
        frameButtons->setFrameShadow(QFrame::Raised);
        pushButtonSet = new QPushButton(frameButtons);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(110, 0, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSet->setIcon(icon);

        retranslateUi(DisplayLibFolderForm);

        QMetaObject::connectSlotsByName(DisplayLibFolderForm);
    } // setupUi

    void retranslateUi(GUIFormBase *DisplayLibFolderForm)
    {
        DisplayLibFolderForm->setWindowTitle(QCoreApplication::translate("DisplayLibFolderForm", "Display LibFolder", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("DisplayLibFolderForm", "SET", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DisplayLibFolderForm: public Ui_DisplayLibFolderForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYLIBFOLDERFORM_H
