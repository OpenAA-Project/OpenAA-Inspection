/********************************************************************************
** Form generated from reading UI file 'EditAlgorithmList.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITALGORITHMLIST_H
#define UI_EDITALGORITHMLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditAlgorithmListClass
{
public:
    QPushButton *pushButtonSave;
    QPushButton *pushButtonCancel;
    QFrame *frame;

    void setupUi(QWidget *EditAlgorithmListClass)
    {
        if (EditAlgorithmListClass->objectName().isEmpty())
            EditAlgorithmListClass->setObjectName("EditAlgorithmListClass");
        EditAlgorithmListClass->resize(1000, 400);
        pushButtonSave = new QPushButton(EditAlgorithmListClass);
        pushButtonSave->setObjectName("pushButtonSave");
        pushButtonSave->setGeometry(QRect(300, 360, 75, 31));
        pushButtonCancel = new QPushButton(EditAlgorithmListClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(540, 360, 75, 31));
        frame = new QFrame(EditAlgorithmListClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 1001, 351));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        retranslateUi(EditAlgorithmListClass);

        QMetaObject::connectSlotsByName(EditAlgorithmListClass);
    } // setupUi

    void retranslateUi(QWidget *EditAlgorithmListClass)
    {
        EditAlgorithmListClass->setWindowTitle(QCoreApplication::translate("EditAlgorithmListClass", "EditAlgorithmList", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("EditAlgorithmListClass", "Save & close", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditAlgorithmListClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditAlgorithmListClass: public Ui_EditAlgorithmListClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITALGORITHMLIST_H
