/********************************************************************************
** Form generated from reading UI file 'ChildPanelForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHILDPANELFORM_H
#define UI_CHILDPANELFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChildPanelForm
{
public:
    QPushButton *pushButtonSetting;
    QFrame *frame;
    QToolButton *toolButtonLive;

    void setupUi(QWidget *ChildPanelForm)
    {
        if (ChildPanelForm->objectName().isEmpty())
            ChildPanelForm->setObjectName(QString::fromUtf8("ChildPanelForm"));
        ChildPanelForm->resize(433, 353);
        pushButtonSetting = new QPushButton(ChildPanelForm);
        pushButtonSetting->setObjectName(QString::fromUtf8("pushButtonSetting"));
        pushButtonSetting->setGeometry(QRect(0, 0, 75, 23));
        frame = new QFrame(ChildPanelForm);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 30, 431, 321));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        toolButtonLive = new QToolButton(ChildPanelForm);
        toolButtonLive->setObjectName(QString::fromUtf8("toolButtonLive"));
        toolButtonLive->setGeometry(QRect(80, 0, 71, 23));
        toolButtonLive->setCheckable(true);
        toolButtonLive->setChecked(true);

        retranslateUi(ChildPanelForm);

        QMetaObject::connectSlotsByName(ChildPanelForm);
    } // setupUi

    void retranslateUi(QWidget *ChildPanelForm)
    {
        ChildPanelForm->setWindowTitle(QCoreApplication::translate("ChildPanelForm", "Dialog", nullptr));
        pushButtonSetting->setText(QCoreApplication::translate("ChildPanelForm", "Setting", nullptr));
        toolButtonLive->setText(QCoreApplication::translate("ChildPanelForm", "Live", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChildPanelForm: public Ui_ChildPanelForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHILDPANELFORM_H
