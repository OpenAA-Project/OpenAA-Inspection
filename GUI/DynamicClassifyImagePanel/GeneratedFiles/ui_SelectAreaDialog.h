/********************************************************************************
** Form generated from reading UI file 'SelectAreaDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTAREADIALOG_H
#define UI_SELECTAREADIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SelectAreaDialogClass
{
public:
    QPushButton *pushButtonCopy;
    QPushButton *pushButtonCancel;
    QFrame *frame;
    QToolButton *toolButtonItemArea;
    QFrame *frame_2;
    QToolButton *toolButtonMaxZone;
    QToolButton *toolButtonCoreArea;
    QToolButton *toolButtonMinZone;
    QFrame *frame_3;
    QToolButton *toolButtonOutlineIArea;
    QToolButton *toolButtonOutlineTArea;
    QToolButton *toolButtonBareArea;
    QToolButton *toolButtonOutlineOArea;
    QToolButton *toolButtonInsideArea;

    void setupUi(QDialog *SelectAreaDialogClass)
    {
        if (SelectAreaDialogClass->objectName().isEmpty())
            SelectAreaDialogClass->setObjectName("SelectAreaDialogClass");
        SelectAreaDialogClass->resize(255, 305);
        pushButtonCopy = new QPushButton(SelectAreaDialogClass);
        pushButtonCopy->setObjectName("pushButtonCopy");
        pushButtonCopy->setGeometry(QRect(20, 240, 101, 41));
        pushButtonCancel = new QPushButton(SelectAreaDialogClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(130, 240, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        frame = new QFrame(SelectAreaDialogClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 231, 51));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        toolButtonItemArea = new QToolButton(frame);
        toolButtonItemArea->setObjectName("toolButtonItemArea");
        toolButtonItemArea->setGeometry(QRect(10, 10, 121, 31));
        toolButtonItemArea->setCheckable(true);
        toolButtonItemArea->setChecked(true);
        frame_2 = new QFrame(SelectAreaDialogClass);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 60, 231, 81));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        toolButtonMaxZone = new QToolButton(frame_2);
        toolButtonMaxZone->setObjectName("toolButtonMaxZone");
        toolButtonMaxZone->setGeometry(QRect(120, 10, 101, 31));
        toolButtonMaxZone->setCheckable(true);
        toolButtonCoreArea = new QToolButton(frame_2);
        toolButtonCoreArea->setObjectName("toolButtonCoreArea");
        toolButtonCoreArea->setGeometry(QRect(10, 10, 101, 31));
        toolButtonCoreArea->setCheckable(true);
        toolButtonCoreArea->setChecked(false);
        toolButtonMinZone = new QToolButton(frame_2);
        toolButtonMinZone->setObjectName("toolButtonMinZone");
        toolButtonMinZone->setGeometry(QRect(120, 40, 101, 31));
        toolButtonMinZone->setCheckable(true);
        frame_3 = new QFrame(SelectAreaDialogClass);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 150, 231, 81));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        toolButtonOutlineIArea = new QToolButton(frame_3);
        toolButtonOutlineIArea->setObjectName("toolButtonOutlineIArea");
        toolButtonOutlineIArea->setGeometry(QRect(10, 40, 71, 31));
        toolButtonOutlineIArea->setCheckable(true);
        toolButtonOutlineTArea = new QToolButton(frame_3);
        toolButtonOutlineTArea->setObjectName("toolButtonOutlineTArea");
        toolButtonOutlineTArea->setGeometry(QRect(80, 40, 71, 31));
        toolButtonOutlineTArea->setCheckable(true);
        toolButtonBareArea = new QToolButton(frame_3);
        toolButtonBareArea->setObjectName("toolButtonBareArea");
        toolButtonBareArea->setGeometry(QRect(10, 8, 71, 31));
        toolButtonBareArea->setCheckable(true);
        toolButtonOutlineOArea = new QToolButton(frame_3);
        toolButtonOutlineOArea->setObjectName("toolButtonOutlineOArea");
        toolButtonOutlineOArea->setGeometry(QRect(150, 40, 71, 31));
        toolButtonOutlineOArea->setCheckable(true);
        toolButtonInsideArea = new QToolButton(frame_3);
        toolButtonInsideArea->setObjectName("toolButtonInsideArea");
        toolButtonInsideArea->setGeometry(QRect(80, 8, 71, 31));
        toolButtonInsideArea->setCheckable(true);

        retranslateUi(SelectAreaDialogClass);

        QMetaObject::connectSlotsByName(SelectAreaDialogClass);
    } // setupUi

    void retranslateUi(QDialog *SelectAreaDialogClass)
    {
        SelectAreaDialogClass->setWindowTitle(QCoreApplication::translate("SelectAreaDialogClass", "SelectAreaDialog", nullptr));
        pushButtonCopy->setText(QCoreApplication::translate("SelectAreaDialogClass", "Execute copy", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectAreaDialogClass", "Cancel", nullptr));
        toolButtonItemArea->setText(QCoreApplication::translate("SelectAreaDialogClass", "ItemArea", nullptr));
        toolButtonMaxZone->setText(QCoreApplication::translate("SelectAreaDialogClass", "Max Zone", nullptr));
        toolButtonCoreArea->setText(QCoreApplication::translate("SelectAreaDialogClass", "Core", nullptr));
        toolButtonMinZone->setText(QCoreApplication::translate("SelectAreaDialogClass", "Min Zone", nullptr));
        toolButtonOutlineIArea->setText(QCoreApplication::translate("SelectAreaDialogClass", "Outline-I", nullptr));
        toolButtonOutlineTArea->setText(QCoreApplication::translate("SelectAreaDialogClass", "Outline-T", nullptr));
        toolButtonBareArea->setText(QCoreApplication::translate("SelectAreaDialogClass", "Bare", nullptr));
        toolButtonOutlineOArea->setText(QCoreApplication::translate("SelectAreaDialogClass", "Outline-O", nullptr));
        toolButtonInsideArea->setText(QCoreApplication::translate("SelectAreaDialogClass", "Inside", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectAreaDialogClass: public Ui_SelectAreaDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTAREADIALOG_H
