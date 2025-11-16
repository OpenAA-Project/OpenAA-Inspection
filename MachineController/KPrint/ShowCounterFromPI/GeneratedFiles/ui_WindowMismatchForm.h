/********************************************************************************
** Form generated from reading UI file 'WindowMismatchForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWMISMATCHFORM_H
#define UI_WINDOWMISMATCHFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowMismatchForm
{
public:
    QLabel *label;
    QPushButton *pushButtonOK;

    void setupUi(QWidget *WindowMismatchForm)
    {
        if (WindowMismatchForm->objectName().isEmpty())
            WindowMismatchForm->setObjectName("WindowMismatchForm");
        WindowMismatchForm->resize(421, 94);
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        WindowMismatchForm->setPalette(palette);
        label = new QLabel(WindowMismatchForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 401, 41));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        label->setFont(font);
        label->setAutoFillBackground(true);
        label->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(WindowMismatchForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(170, 67, 80, 21));

        retranslateUi(WindowMismatchForm);

        QMetaObject::connectSlotsByName(WindowMismatchForm);
    } // setupUi

    void retranslateUi(QWidget *WindowMismatchForm)
    {
        WindowMismatchForm->setWindowTitle(QCoreApplication::translate("WindowMismatchForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("WindowMismatchForm", "\343\203\257\343\203\274\343\202\257\343\201\232\343\202\214\347\231\272\347\224\237", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("WindowMismatchForm", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowMismatchForm: public Ui_WindowMismatchForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWMISMATCHFORM_H
