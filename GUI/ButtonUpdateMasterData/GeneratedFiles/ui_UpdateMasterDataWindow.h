/********************************************************************************
** Form generated from reading UI file 'UpdateMasterDataWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEMASTERDATAWINDOW_H
#define UI_UPDATEMASTERDATAWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UpdateMasterDataWindowClass
{
public:
    QFrame *frame;
    QLabel *label_4;
    QLineEdit *EditMasterCode;
    QLineEdit *EditMasterName;
    QLabel *label_2;
    QLineEdit *EditRemark;
    QLabel *label;
    QFrame *frameCategory;
    QPushButton *ButtonUpdate;
    QPushButton *ButtonCancel;
    QFrame *frameGrid;

    void setupUi(QWidget *UpdateMasterDataWindowClass)
    {
        if (UpdateMasterDataWindowClass->objectName().isEmpty())
            UpdateMasterDataWindowClass->setObjectName("UpdateMasterDataWindowClass");
        UpdateMasterDataWindowClass->resize(646, 483);
        frame = new QFrame(UpdateMasterDataWindowClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(30, 40, 591, 221));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(380, 10, 81, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        EditMasterCode = new QLineEdit(frame);
        EditMasterCode->setObjectName("EditMasterCode");
        EditMasterCode->setGeometry(QRect(380, 30, 81, 21));
        EditMasterCode->setReadOnly(true);
        EditMasterName = new QLineEdit(frame);
        EditMasterName->setObjectName("EditMasterName");
        EditMasterName->setGeometry(QRect(380, 90, 201, 21));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(380, 120, 201, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        EditRemark = new QLineEdit(frame);
        EditRemark->setObjectName("EditRemark");
        EditRemark->setGeometry(QRect(380, 140, 201, 21));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(380, 70, 201, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        frameCategory = new QFrame(frame);
        frameCategory->setObjectName("frameCategory");
        frameCategory->setGeometry(QRect(10, 10, 361, 201));
        frameCategory->setFrameShape(QFrame::StyledPanel);
        frameCategory->setFrameShadow(QFrame::Raised);
        ButtonUpdate = new QPushButton(frame);
        ButtonUpdate->setObjectName("ButtonUpdate");
        ButtonUpdate->setGeometry(QRect(380, 180, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonUpdate->setIcon(icon);
        ButtonCancel = new QPushButton(frame);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(490, 180, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        frameGrid = new QFrame(UpdateMasterDataWindowClass);
        frameGrid->setObjectName("frameGrid");
        frameGrid->setGeometry(QRect(30, 270, 591, 181));
        frameGrid->setFrameShape(QFrame::StyledPanel);
        frameGrid->setFrameShadow(QFrame::Sunken);

        retranslateUi(UpdateMasterDataWindowClass);

        QMetaObject::connectSlotsByName(UpdateMasterDataWindowClass);
    } // setupUi

    void retranslateUi(QWidget *UpdateMasterDataWindowClass)
    {
        UpdateMasterDataWindowClass->setWindowTitle(QCoreApplication::translate("UpdateMasterDataWindowClass", "UpdateMasterDataWindow", nullptr));
        label_4->setText(QCoreApplication::translate("UpdateMasterDataWindowClass", "Master Code", nullptr));
        label_2->setText(QCoreApplication::translate("UpdateMasterDataWindowClass", "Remark", nullptr));
        label->setText(QCoreApplication::translate("UpdateMasterDataWindowClass", "Master Name", nullptr));
        ButtonUpdate->setText(QCoreApplication::translate("UpdateMasterDataWindowClass", "Update", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("UpdateMasterDataWindowClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UpdateMasterDataWindowClass: public Ui_UpdateMasterDataWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEMASTERDATAWINDOW_H
