/********************************************************************************
** Form generated from reading UI file 'FormMatrixPieceColor.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMMATRIXPIECECOLOR_H
#define UI_FORMMATRIXPIECECOLOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FormMatrixPieceColorClass
{
public:
    QListWidget *listWidget;
    QLabel *label;
    QPushButton *pushButtonColor;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *FormMatrixPieceColorClass)
    {
        if (FormMatrixPieceColorClass->objectName().isEmpty())
            FormMatrixPieceColorClass->setObjectName("FormMatrixPieceColorClass");
        FormMatrixPieceColorClass->resize(211, 300);
        listWidget = new QListWidget(FormMatrixPieceColorClass);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(10, 20, 81, 271));
        label = new QLabel(FormMatrixPieceColorClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 81, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonColor = new QPushButton(FormMatrixPieceColorClass);
        pushButtonColor->setObjectName("pushButtonColor");
        pushButtonColor->setGeometry(QRect(110, 20, 91, 51));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Color.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonColor->setIcon(icon);
        pushButtonOK = new QPushButton(FormMatrixPieceColorClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(110, 240, 91, 51));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);

        retranslateUi(FormMatrixPieceColorClass);

        QMetaObject::connectSlotsByName(FormMatrixPieceColorClass);
    } // setupUi

    void retranslateUi(QDialog *FormMatrixPieceColorClass)
    {
        FormMatrixPieceColorClass->setWindowTitle(QCoreApplication::translate("FormMatrixPieceColorClass", "FormMatrixPieceColor", nullptr));
        label->setText(QCoreApplication::translate("FormMatrixPieceColorClass", "Piece", nullptr));
        pushButtonColor->setText(QCoreApplication::translate("FormMatrixPieceColorClass", "Color", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("FormMatrixPieceColorClass", "\351\226\211\343\201\230\343\202\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormMatrixPieceColorClass: public Ui_FormMatrixPieceColorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMMATRIXPIECECOLOR_H
