/********************************************************************************
** Form generated from reading UI file 'ShowStatusComment.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWSTATUSCOMMENT_H
#define UI_SHOWSTATUSCOMMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowStatusCommentClass
{
public:
    QWidget *centralWidget;
    QTextEdit *textEdit;

    void setupUi(QMainWindow *ShowStatusCommentClass)
    {
        if (ShowStatusCommentClass->objectName().isEmpty())
            ShowStatusCommentClass->setObjectName("ShowStatusCommentClass");
        ShowStatusCommentClass->resize(348, 293);
        centralWidget = new QWidget(ShowStatusCommentClass);
        centralWidget->setObjectName("centralWidget");
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(0, 0, 341, 291));
        textEdit->setReadOnly(true);
        ShowStatusCommentClass->setCentralWidget(centralWidget);

        retranslateUi(ShowStatusCommentClass);

        QMetaObject::connectSlotsByName(ShowStatusCommentClass);
    } // setupUi

    void retranslateUi(QMainWindow *ShowStatusCommentClass)
    {
        ShowStatusCommentClass->setWindowTitle(QCoreApplication::translate("ShowStatusCommentClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowStatusCommentClass: public Ui_ShowStatusCommentClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWSTATUSCOMMENT_H
