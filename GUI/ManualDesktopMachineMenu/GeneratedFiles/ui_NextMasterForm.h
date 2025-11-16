/********************************************************************************
** Form generated from reading UI file 'NextMasterForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEXTMASTERFORM_H
#define UI_NEXTMASTERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NextMasterFormClass
{
public:
    QLabel *label;
    QPushButton *pushButtonStartNext;
    QPushButton *pushButtonFinish;

    void setupUi(QDialog *NextMasterFormClass)
    {
        if (NextMasterFormClass->objectName().isEmpty())
            NextMasterFormClass->setObjectName("NextMasterFormClass");
        NextMasterFormClass->resize(348, 146);
        label = new QLabel(NextMasterFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 331, 31));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonStartNext = new QPushButton(NextMasterFormClass);
        pushButtonStartNext->setObjectName("pushButtonStartNext");
        pushButtonStartNext->setGeometry(QRect(40, 90, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Start.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonStartNext->setIcon(icon);
        pushButtonFinish = new QPushButton(NextMasterFormClass);
        pushButtonFinish->setObjectName("pushButtonFinish");
        pushButtonFinish->setGeometry(QRect(210, 90, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonFinish->setIcon(icon1);

        retranslateUi(NextMasterFormClass);

        pushButtonStartNext->setDefault(true);


        QMetaObject::connectSlotsByName(NextMasterFormClass);
    } // setupUi

    void retranslateUi(QDialog *NextMasterFormClass)
    {
        NextMasterFormClass->setWindowTitle(QCoreApplication::translate("NextMasterFormClass", "NextMasterForm", nullptr));
        label->setText(QCoreApplication::translate("NextMasterFormClass", "\346\254\241\343\201\256\343\203\236\343\202\271\343\202\277\343\203\274\345\237\272\346\235\277\343\202\222\343\202\273\343\203\203\343\203\210\343\201\227\343\201\246\343\201\217\343\201\240\343\201\225\343\201\204", nullptr));
        pushButtonStartNext->setText(QCoreApplication::translate("NextMasterFormClass", "\350\252\255\343\201\277\350\276\274\343\201\277\351\226\213\345\247\213", nullptr));
        pushButtonFinish->setText(QCoreApplication::translate("NextMasterFormClass", "\347\231\273\351\214\262\347\265\202\344\272\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NextMasterFormClass: public Ui_NextMasterFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEXTMASTERFORM_H
