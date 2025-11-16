/********************************************************************************
** Form generated from reading UI file 'CloseMessageForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOSEMESSAGEFORM_H
#define UI_CLOSEMESSAGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CloseMessageFormClass
{
public:
    QPushButton *pushButtonCloseAll;
    QPushButton *pushButtonCloseOne;
    QPushButton *pushButtonCalcen;
    QLabel *labelMessage;

    void setupUi(QDialog *CloseMessageFormClass)
    {
        if (CloseMessageFormClass->objectName().isEmpty())
            CloseMessageFormClass->setObjectName(QString::fromUtf8("CloseMessageFormClass"));
        CloseMessageFormClass->resize(266, 134);
        pushButtonCloseAll = new QPushButton(CloseMessageFormClass);
        pushButtonCloseAll->setObjectName(QString::fromUtf8("pushButtonCloseAll"));
        pushButtonCloseAll->setGeometry(QRect(20, 90, 75, 31));
        pushButtonCloseAll->setAutoDefault(true);
        pushButtonCloseOne = new QPushButton(CloseMessageFormClass);
        pushButtonCloseOne->setObjectName(QString::fromUtf8("pushButtonCloseOne"));
        pushButtonCloseOne->setGeometry(QRect(100, 90, 75, 31));
        pushButtonCalcen = new QPushButton(CloseMessageFormClass);
        pushButtonCalcen->setObjectName(QString::fromUtf8("pushButtonCalcen"));
        pushButtonCalcen->setGeometry(QRect(180, 90, 75, 31));
        labelMessage = new QLabel(CloseMessageFormClass);
        labelMessage->setObjectName(QString::fromUtf8("labelMessage"));
        labelMessage->setGeometry(QRect(19, 40, 241, 22));
        QFont font;
        font.setPointSize(16);
        labelMessage->setFont(font);
        labelMessage->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(CloseMessageFormClass);

        pushButtonCloseAll->setDefault(true);


        QMetaObject::connectSlotsByName(CloseMessageFormClass);
    } // setupUi

    void retranslateUi(QDialog *CloseMessageFormClass)
    {
        CloseMessageFormClass->setWindowTitle(QCoreApplication::translate("CloseMessageFormClass", "Close message", nullptr));
        pushButtonCloseAll->setText(QCoreApplication::translate("CloseMessageFormClass", "Close All", nullptr));
        pushButtonCloseOne->setText(QCoreApplication::translate("CloseMessageFormClass", "Close one", nullptr));
        pushButtonCalcen->setText(QCoreApplication::translate("CloseMessageFormClass", "Cancel", nullptr));
        labelMessage->setText(QCoreApplication::translate("CloseMessageFormClass", "\347\265\202\344\272\206\343\201\227\343\201\276\343\201\231\343\201\213\357\274\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CloseMessageFormClass: public Ui_CloseMessageFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOSEMESSAGEFORM_H
