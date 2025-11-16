/********************************************************************************
** Form generated from reading UI file 'ButtonChangeServerForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONCHANGESERVERFORM_H
#define UI_BUTTONCHANGESERVERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ButtonChangeServerForm
{
public:
    QPushButton *pushButton;

    void setupUi(GUIFormBase *ButtonChangeServerForm)
    {
        if (ButtonChangeServerForm->objectName().isEmpty())
            ButtonChangeServerForm->setObjectName("ButtonChangeServerForm");
        ButtonChangeServerForm->resize(107, 35);
        pushButton = new QPushButton(ButtonChangeServerForm);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 0, 111, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Hole.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon);

        retranslateUi(ButtonChangeServerForm);

        QMetaObject::connectSlotsByName(ButtonChangeServerForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ButtonChangeServerForm)
    {
        ButtonChangeServerForm->setWindowTitle(QCoreApplication::translate("ButtonChangeServerForm", "Change server", nullptr));
        pushButton->setText(QCoreApplication::translate("ButtonChangeServerForm", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonChangeServerForm: public Ui_ButtonChangeServerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONCHANGESERVERFORM_H
