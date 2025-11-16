/********************************************************************************
** Form generated from reading UI file 'DisplayStatusForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYSTATUSFORM_H
#define UI_DISPLAYSTATUSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTextEdit>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_DisplayStatusFormClass
{
public:
    QTextEdit *textEditComment;

    void setupUi(GUIFormBase *DisplayStatusFormClass)
    {
        if (DisplayStatusFormClass->objectName().isEmpty())
            DisplayStatusFormClass->setObjectName("DisplayStatusFormClass");
        DisplayStatusFormClass->resize(386, 279);
        textEditComment = new QTextEdit(DisplayStatusFormClass);
        textEditComment->setObjectName("textEditComment");
        textEditComment->setGeometry(QRect(0, 0, 381, 31));
        textEditComment->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditComment->setUndoRedoEnabled(false);
        textEditComment->setReadOnly(true);

        retranslateUi(DisplayStatusFormClass);

        QMetaObject::connectSlotsByName(DisplayStatusFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *DisplayStatusFormClass)
    {
        DisplayStatusFormClass->setWindowTitle(QCoreApplication::translate("DisplayStatusFormClass", "DisplayStatusForm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DisplayStatusFormClass: public Ui_DisplayStatusFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYSTATUSFORM_H
