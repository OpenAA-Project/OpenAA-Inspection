/********************************************************************************
** Form generated from reading UI file 'MessageForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEFORM_H
#define UI_MESSAGEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MessageForm
{
public:
    QLabel *label;
    QPushButton *pushButtonClose;

    void setupUi(QWidget *MessageForm)
    {
        if (MessageForm->objectName().isEmpty())
            MessageForm->setObjectName("MessageForm");
        MessageForm->resize(400, 300);
        QPalette palette;
        QBrush brush(QColor(170, 170, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        MessageForm->setPalette(palette);
        label = new QLabel(MessageForm);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 90, 341, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);
        pushButtonClose = new QPushButton(MessageForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(160, 240, 93, 28));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon);

        retranslateUi(MessageForm);

        pushButtonClose->setDefault(true);


        QMetaObject::connectSlotsByName(MessageForm);
    } // setupUi

    void retranslateUi(QWidget *MessageForm)
    {
        MessageForm->setWindowTitle(QCoreApplication::translate("MessageForm", "Message", nullptr));
        label->setText(QCoreApplication::translate("MessageForm", "TextLabel", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("MessageForm", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MessageForm: public Ui_MessageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEFORM_H
