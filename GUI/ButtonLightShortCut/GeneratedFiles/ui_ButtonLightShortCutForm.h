/********************************************************************************
** Form generated from reading UI file 'ButtonLightShortCutForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONLIGHTSHORTCUTFORM_H
#define UI_BUTTONLIGHTSHORTCUTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ButtonLightShortCutForm
{
public:

    void setupUi(GUIFormBase *ButtonLightShortCutForm)
    {
        if (ButtonLightShortCutForm->objectName().isEmpty())
            ButtonLightShortCutForm->setObjectName("ButtonLightShortCutForm");
        ButtonLightShortCutForm->resize(136, 50);

        retranslateUi(ButtonLightShortCutForm);

        QMetaObject::connectSlotsByName(ButtonLightShortCutForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ButtonLightShortCutForm)
    {
        ButtonLightShortCutForm->setWindowTitle(QCoreApplication::translate("ButtonLightShortCutForm", "LightShortCut", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonLightShortCutForm: public Ui_ButtonLightShortCutForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONLIGHTSHORTCUTFORM_H
