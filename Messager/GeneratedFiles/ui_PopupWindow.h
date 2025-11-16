/********************************************************************************
** Form generated from reading UI file 'PopupWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POPUPWINDOW_H
#define UI_POPUPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PopupWindowClass
{
public:
    QLabel *label;

    void setupUi(QWidget *PopupWindowClass)
    {
        if (PopupWindowClass->objectName().isEmpty())
            PopupWindowClass->setObjectName("PopupWindowClass");
        PopupWindowClass->resize(450, 343);
        label = new QLabel(PopupWindowClass);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 130, 361, 101));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(20);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label->setWordWrap(true);

        retranslateUi(PopupWindowClass);

        QMetaObject::connectSlotsByName(PopupWindowClass);
    } // setupUi

    void retranslateUi(QWidget *PopupWindowClass)
    {
        PopupWindowClass->setWindowTitle(QCoreApplication::translate("PopupWindowClass", "PopupWindow", nullptr));
        label->setText(QCoreApplication::translate("PopupWindowClass", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PopupWindowClass: public Ui_PopupWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POPUPWINDOW_H
