/********************************************************************************
** Form generated from reading UI file 'EditEachPageLocalDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITEACHPAGELOCALDIALOG_H
#define UI_EDITEACHPAGELOCALDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditEachPageLocalDialog
{
public:
    QFrame *frameEachPageLocal;
    QPushButton *ButtonOK;
    QLabel *label;
    QListWidget *listWidgetPageList;

    void setupUi(QDialog *EditEachPageLocalDialog)
    {
        if (EditEachPageLocalDialog->objectName().isEmpty())
            EditEachPageLocalDialog->setObjectName(QString::fromUtf8("EditEachPageLocalDialog"));
        EditEachPageLocalDialog->resize(630, 522);
        frameEachPageLocal = new QFrame(EditEachPageLocalDialog);
        frameEachPageLocal->setObjectName(QString::fromUtf8("frameEachPageLocal"));
        frameEachPageLocal->setGeometry(QRect(80, 12, 541, 461));
        frameEachPageLocal->setFrameShape(QFrame::StyledPanel);
        frameEachPageLocal->setFrameShadow(QFrame::Sunken);
        ButtonOK = new QPushButton(EditEachPageLocalDialog);
        ButtonOK->setObjectName(QString::fromUtf8("ButtonOK"));
        ButtonOK->setGeometry(QRect(330, 480, 101, 31));
        label = new QLabel(EditEachPageLocalDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 61, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        listWidgetPageList = new QListWidget(EditEachPageLocalDialog);
        listWidgetPageList->setObjectName(QString::fromUtf8("listWidgetPageList"));
        listWidgetPageList->setGeometry(QRect(10, 30, 61, 441));

        retranslateUi(EditEachPageLocalDialog);

        QMetaObject::connectSlotsByName(EditEachPageLocalDialog);
    } // setupUi

    void retranslateUi(QDialog *EditEachPageLocalDialog)
    {
        EditEachPageLocalDialog->setWindowTitle(QCoreApplication::translate("EditEachPageLocalDialog", "Dialog", nullptr));
        ButtonOK->setText(QCoreApplication::translate("EditEachPageLocalDialog", "OK", nullptr));
        label->setText(QCoreApplication::translate("EditEachPageLocalDialog", "Page", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditEachPageLocalDialog: public Ui_EditEachPageLocalDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITEACHPAGELOCALDIALOG_H
