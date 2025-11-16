/********************************************************************************
** Form generated from reading UI file 'LensWindowForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LENSWINDOWFORM_H
#define UI_LENSWINDOWFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LensWindowForm
{
public:

    void setupUi(QWidget *LensWindowForm)
    {
        if (LensWindowForm->objectName().isEmpty())
            LensWindowForm->setObjectName("LensWindowForm");
        LensWindowForm->resize(400, 300);
        LensWindowForm->setAutoFillBackground(true);

        retranslateUi(LensWindowForm);

        QMetaObject::connectSlotsByName(LensWindowForm);
    } // setupUi

    void retranslateUi(QWidget *LensWindowForm)
    {
        LensWindowForm->setWindowTitle(QCoreApplication::translate("LensWindowForm", "Lens", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LensWindowForm: public Ui_LensWindowForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LENSWINDOWFORM_H
