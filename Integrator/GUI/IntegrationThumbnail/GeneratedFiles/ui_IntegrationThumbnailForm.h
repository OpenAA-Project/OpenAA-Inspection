/********************************************************************************
** Form generated from reading UI file 'IntegrationThumbnailForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONTHUMBNAILFORM_H
#define UI_INTEGRATIONTHUMBNAILFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_IntegrationThumbnailForm
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(GUIFormBase *IntegrationThumbnailForm)
    {
        if (IntegrationThumbnailForm->objectName().isEmpty())
            IntegrationThumbnailForm->setObjectName("IntegrationThumbnailForm");
        IntegrationThumbnailForm->resize(619, 341);
        scrollArea = new QScrollArea(IntegrationThumbnailForm);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 0, 621, 341));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 619, 339));
        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(IntegrationThumbnailForm);

        QMetaObject::connectSlotsByName(IntegrationThumbnailForm);
    } // setupUi

    void retranslateUi(GUIFormBase *IntegrationThumbnailForm)
    {
        IntegrationThumbnailForm->setWindowTitle(QCoreApplication::translate("IntegrationThumbnailForm", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationThumbnailForm: public Ui_IntegrationThumbnailForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONTHUMBNAILFORM_H
