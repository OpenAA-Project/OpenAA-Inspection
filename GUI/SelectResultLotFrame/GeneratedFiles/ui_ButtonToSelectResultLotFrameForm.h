/********************************************************************************
** Form generated from reading UI file 'ButtonToSelectResultLotFrameForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONTOSELECTRESULTLOTFRAMEFORM_H
#define UI_BUTTONTOSELECTRESULTLOTFRAMEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ButtonToSelectResultLotFrameForm
{
public:
    QPushButton *pushButton;

    void setupUi(GUIFormBase *ButtonToSelectResultLotFrameForm)
    {
        if (ButtonToSelectResultLotFrameForm->objectName().isEmpty())
            ButtonToSelectResultLotFrameForm->setObjectName("ButtonToSelectResultLotFrameForm");
        ButtonToSelectResultLotFrameForm->resize(142, 46);
        pushButton = new QPushButton(ButtonToSelectResultLotFrameForm);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 0, 141, 47));

        retranslateUi(ButtonToSelectResultLotFrameForm);

        QMetaObject::connectSlotsByName(ButtonToSelectResultLotFrameForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ButtonToSelectResultLotFrameForm)
    {
        ButtonToSelectResultLotFrameForm->setWindowTitle(QCoreApplication::translate("ButtonToSelectResultLotFrameForm", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("ButtonToSelectResultLotFrameForm", "Select Lot frame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonToSelectResultLotFrameForm: public Ui_ButtonToSelectResultLotFrameForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONTOSELECTRESULTLOTFRAMEFORM_H
