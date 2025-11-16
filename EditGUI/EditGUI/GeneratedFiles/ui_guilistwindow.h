/********************************************************************************
** Form generated from reading UI file 'guilistwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUILISTWINDOW_H
#define UI_GUILISTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GuiListWindow
{
public:

    void setupUi(QWidget *GuiListWindow)
    {
        if (GuiListWindow->objectName().isEmpty())
            GuiListWindow->setObjectName("GuiListWindow");
        GuiListWindow->resize(400, 655);

        retranslateUi(GuiListWindow);

        QMetaObject::connectSlotsByName(GuiListWindow);
    } // setupUi

    void retranslateUi(QWidget *GuiListWindow)
    {
        GuiListWindow->setWindowTitle(QCoreApplication::translate("GuiListWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GuiListWindow: public Ui_GuiListWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUILISTWINDOW_H
