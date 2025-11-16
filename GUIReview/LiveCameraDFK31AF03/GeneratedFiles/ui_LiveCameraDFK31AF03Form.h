/********************************************************************************
** Form generated from reading UI file 'LiveCameraDFK31AF03Form.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIVECAMERADFK31AF03FORM_H
#define UI_LIVECAMERADFK31AF03FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include "AreaCamera.h"

QT_BEGIN_NAMESPACE

class Ui_LiveCameraDFK31AF03Class
{
public:
    QGridLayout *gridLayout;
    AreaCamera *AreaCameraView;

    void setupUi(QWidget *LiveCameraDFK31AF03Class)
    {
        if (LiveCameraDFK31AF03Class->objectName().isEmpty())
            LiveCameraDFK31AF03Class->setObjectName(QString::fromUtf8("LiveCameraDFK31AF03Class"));
        LiveCameraDFK31AF03Class->resize(642, 488);
        gridLayout = new QGridLayout(LiveCameraDFK31AF03Class);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        AreaCameraView = new AreaCamera(LiveCameraDFK31AF03Class);
        AreaCameraView->setObjectName(QString::fromUtf8("AreaCameraView"));

        gridLayout->addWidget(AreaCameraView, 0, 0, 2, 1);

        gridLayout->setColumnStretch(0, 1);

        retranslateUi(LiveCameraDFK31AF03Class);

        QMetaObject::connectSlotsByName(LiveCameraDFK31AF03Class);
    } // setupUi

    void retranslateUi(QWidget *LiveCameraDFK31AF03Class)
    {
        LiveCameraDFK31AF03Class->setWindowTitle(QCoreApplication::translate("LiveCameraDFK31AF03Class", "LiveCameraDFK31AF03", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LiveCameraDFK31AF03Class: public Ui_LiveCameraDFK31AF03Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIVECAMERADFK31AF03FORM_H
