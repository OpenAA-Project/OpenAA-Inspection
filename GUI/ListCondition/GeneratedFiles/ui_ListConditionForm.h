/********************************************************************************
** Form generated from reading UI file 'ListConditionForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTCONDITIONFORM_H
#define UI_LISTCONDITIONFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ListConditionForm
{
public:
    QListWidget *listWidgetConditions;
    QPushButton *pushButtonSave;
    QLineEdit *lineEditName;
    QLabel *label;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonUpdate;

    void setupUi(GUIFormBase *ListConditionForm)
    {
        if (ListConditionForm->objectName().isEmpty())
            ListConditionForm->setObjectName("ListConditionForm");
        ListConditionForm->resize(163, 187);
        listWidgetConditions = new QListWidget(ListConditionForm);
        listWidgetConditions->setObjectName("listWidgetConditions");
        listWidgetConditions->setGeometry(QRect(0, 50, 161, 111));
        pushButtonSave = new QPushButton(ListConditionForm);
        pushButtonSave->setObjectName("pushButtonSave");
        pushButtonSave->setGeometry(QRect(110, 20, 51, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSave->setIcon(icon);
        lineEditName = new QLineEdit(ListConditionForm);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(0, 20, 113, 20));
        label = new QLabel(ListConditionForm);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 161, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        pushButtonSelect = new QPushButton(ListConditionForm);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(0, 160, 61, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSelect->setIcon(icon1);
        pushButtonUpdate = new QPushButton(ListConditionForm);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(100, 160, 61, 23));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon2);

        retranslateUi(ListConditionForm);

        QMetaObject::connectSlotsByName(ListConditionForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ListConditionForm)
    {
        ListConditionForm->setWindowTitle(QCoreApplication::translate("ListConditionForm", "List condition", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("ListConditionForm", "Save", nullptr));
        label->setText(QCoreApplication::translate("ListConditionForm", "Condition", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("ListConditionForm", "Select", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("ListConditionForm", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListConditionForm: public Ui_ListConditionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTCONDITIONFORM_H
