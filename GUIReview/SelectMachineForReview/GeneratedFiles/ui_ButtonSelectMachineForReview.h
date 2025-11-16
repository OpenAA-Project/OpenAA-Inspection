/********************************************************************************
** Form generated from reading UI file 'ButtonSelectMachineForReview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONSELECTMACHINEFORREVIEW_H
#define UI_BUTTONSELECTMACHINEFORREVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ButtonSelectMachineForReview
{
public:
    QPushButton *pushButton;

    void setupUi(GUIFormBase *ButtonSelectMachineForReview)
    {
        if (ButtonSelectMachineForReview->objectName().isEmpty())
            ButtonSelectMachineForReview->setObjectName(QString::fromUtf8("ButtonSelectMachineForReview"));
        ButtonSelectMachineForReview->resize(101, 39);
        pushButton = new QPushButton(ButtonSelectMachineForReview);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 0, 101, 41));

        retranslateUi(ButtonSelectMachineForReview);

        QMetaObject::connectSlotsByName(ButtonSelectMachineForReview);
    } // setupUi

    void retranslateUi(GUIFormBase *ButtonSelectMachineForReview)
    {
        ButtonSelectMachineForReview->setWindowTitle(QCoreApplication::translate("ButtonSelectMachineForReview", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("ButtonSelectMachineForReview", "Select machine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonSelectMachineForReview: public Ui_ButtonSelectMachineForReview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONSELECTMACHINEFORREVIEW_H
