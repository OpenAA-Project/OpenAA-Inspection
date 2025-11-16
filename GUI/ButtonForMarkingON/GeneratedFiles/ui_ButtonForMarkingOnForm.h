/********************************************************************************
** Form generated from reading UI file 'ButtonForMarkingOnForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONFORMARKINGONFORM_H
#define UI_BUTTONFORMARKINGONFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ButtonForMarkingOnForm
{
public:
    QToolButton *toolButton;

    void setupUi(GUIFormBase *ButtonForMarkingOnForm)
    {
        if (ButtonForMarkingOnForm->objectName().isEmpty())
            ButtonForMarkingOnForm->setObjectName("ButtonForMarkingOnForm");
        ButtonForMarkingOnForm->resize(100, 50);
        toolButton = new QToolButton(ButtonForMarkingOnForm);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(0, 0, 101, 51));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/ButtonForMarkingON.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButton->setIcon(icon);
        toolButton->setCheckable(true);
        toolButton->setChecked(false);
        toolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        retranslateUi(ButtonForMarkingOnForm);

        QMetaObject::connectSlotsByName(ButtonForMarkingOnForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ButtonForMarkingOnForm)
    {
        ButtonForMarkingOnForm->setWindowTitle(QCoreApplication::translate("ButtonForMarkingOnForm", "MarkingOn", nullptr));
        toolButton->setText(QCoreApplication::translate("ButtonForMarkingOnForm", "Marking ON", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonForMarkingOnForm: public Ui_ButtonForMarkingOnForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONFORMARKINGONFORM_H
