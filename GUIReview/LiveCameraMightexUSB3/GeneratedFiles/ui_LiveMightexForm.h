/********************************************************************************
** Form generated from reading UI file 'LiveMightexForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIVEMIGHTEXFORM_H
#define UI_LIVEMIGHTEXFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_LiveMightexForm
{
public:
    QPushButton *pushButtonSetting;
    QToolButton *toolButtonLive;
    QFrame *frame;

    void setupUi(GUIFormBase *LiveMightexForm)
    {
        if (LiveMightexForm->objectName().isEmpty())
            LiveMightexForm->setObjectName(QString::fromUtf8("LiveMightexForm"));
        LiveMightexForm->resize(433, 352);
        pushButtonSetting = new QPushButton(LiveMightexForm);
        pushButtonSetting->setObjectName(QString::fromUtf8("pushButtonSetting"));
        pushButtonSetting->setGeometry(QRect(0, 0, 75, 23));
        toolButtonLive = new QToolButton(LiveMightexForm);
        toolButtonLive->setObjectName(QString::fromUtf8("toolButtonLive"));
        toolButtonLive->setGeometry(QRect(80, 0, 71, 23));
        toolButtonLive->setCheckable(true);
        toolButtonLive->setChecked(true);
        frame = new QFrame(LiveMightexForm);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 30, 431, 321));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);

        retranslateUi(LiveMightexForm);

        QMetaObject::connectSlotsByName(LiveMightexForm);
    } // setupUi

    void retranslateUi(GUIFormBase *LiveMightexForm)
    {
        LiveMightexForm->setWindowTitle(QCoreApplication::translate("LiveMightexForm", "Dialog", nullptr));
        pushButtonSetting->setText(QCoreApplication::translate("LiveMightexForm", "Setting", nullptr));
        toolButtonLive->setText(QCoreApplication::translate("LiveMightexForm", "Live", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LiveMightexForm: public Ui_LiveMightexForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIVEMIGHTEXFORM_H
