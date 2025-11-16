/********************************************************************************
** Form generated from reading UI file 'IntegrationStackNGThumbnailForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONSTACKNGTHUMBNAILFORM_H
#define UI_INTEGRATIONSTACKNGTHUMBNAILFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_IntegrationStackNGThumbnailForm
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(GUIFormBase *IntegrationStackNGThumbnailForm)
    {
        if (IntegrationStackNGThumbnailForm->objectName().isEmpty())
            IntegrationStackNGThumbnailForm->setObjectName("IntegrationStackNGThumbnailForm");
        IntegrationStackNGThumbnailForm->resize(766, 330);
        scrollArea = new QScrollArea(IntegrationStackNGThumbnailForm);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 0, 761, 321));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 759, 319));
        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(IntegrationStackNGThumbnailForm);

        QMetaObject::connectSlotsByName(IntegrationStackNGThumbnailForm);
    } // setupUi

    void retranslateUi(GUIFormBase *IntegrationStackNGThumbnailForm)
    {
        IntegrationStackNGThumbnailForm->setWindowTitle(QCoreApplication::translate("IntegrationStackNGThumbnailForm", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationStackNGThumbnailForm: public Ui_IntegrationStackNGThumbnailForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONSTACKNGTHUMBNAILFORM_H
