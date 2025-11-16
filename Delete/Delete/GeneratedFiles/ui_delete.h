/********************************************************************************
** Form generated from reading UI file 'delete.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELETE_H
#define UI_DELETE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeleteClass
{
public:
    QPushButton *pushButton;
    QPushButton *pushButtonSource;
    QLabel *label;

    void setupUi(QWidget *DeleteClass)
    {
        if (DeleteClass->objectName().isEmpty())
            DeleteClass->setObjectName("DeleteClass");
        DeleteClass->resize(130, 226);
        DeleteClass->setMinimumSize(QSize(130, 226));
        DeleteClass->setMaximumSize(QSize(130, 226));
        DeleteClass->setContextMenuPolicy(Qt::ActionsContextMenu);
        DeleteClass->setAcceptDrops(true);
        DeleteClass->setAutoFillBackground(true);
        pushButton = new QPushButton(DeleteClass);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 10, 91, 23));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        pushButton->setFont(font);
        pushButtonSource = new QPushButton(DeleteClass);
        pushButtonSource->setObjectName("pushButtonSource");
        pushButtonSource->setGeometry(QRect(20, 50, 91, 23));
        pushButtonSource->setFont(font);
        label = new QLabel(DeleteClass);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 80, 81, 141));

        retranslateUi(DeleteClass);

        QMetaObject::connectSlotsByName(DeleteClass);
    } // setupUi

    void retranslateUi(QWidget *DeleteClass)
    {
        DeleteClass->setWindowTitle(QCoreApplication::translate("DeleteClass", "Delete", nullptr));
        pushButton->setText(QCoreApplication::translate("DeleteClass", "Delete All", nullptr));
        pushButtonSource->setText(QCoreApplication::translate("DeleteClass", "Delete Source", nullptr));
        label->setText(QCoreApplication::translate("DeleteClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Delete following</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">*.icproj</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">*.vcproj</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">*"
                        ".vcxproj</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">*.c</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">*.cpp</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">*.h</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">*.ui</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">*.qrc</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" "
                        "font-size:8pt;\">*.sln</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeleteClass: public Ui_DeleteClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETE_H
