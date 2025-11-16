/********************************************************************************
** Form generated from reading UI file 'CompressImageIndicatorForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPRESSIMAGEINDICATORFORM_H
#define UI_COMPRESSIMAGEINDICATORFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_CompressImageIndicatorForm
{
public:
    QProgressBar *progressBar;
    QLabel *label;

    void setupUi(GUIFormBase *CompressImageIndicatorForm)
    {
        if (CompressImageIndicatorForm->objectName().isEmpty())
            CompressImageIndicatorForm->setObjectName("CompressImageIndicatorForm");
        CompressImageIndicatorForm->resize(184, 56);
        progressBar = new QProgressBar(CompressImageIndicatorForm);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(10, 30, 171, 23));
        progressBar->setValue(24);
        label = new QLabel(CompressImageIndicatorForm);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 191, 16));
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(CompressImageIndicatorForm);

        QMetaObject::connectSlotsByName(CompressImageIndicatorForm);
    } // setupUi

    void retranslateUi(GUIFormBase *CompressImageIndicatorForm)
    {
        CompressImageIndicatorForm->setWindowTitle(QCoreApplication::translate("CompressImageIndicatorForm", "Compress Image Indicator", nullptr));
        label->setText(QCoreApplication::translate("CompressImageIndicatorForm", "Stock of compress image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CompressImageIndicatorForm: public Ui_CompressImageIndicatorForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPRESSIMAGEINDICATORFORM_H
