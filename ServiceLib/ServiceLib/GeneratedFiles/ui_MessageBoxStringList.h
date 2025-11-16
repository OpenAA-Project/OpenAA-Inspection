/********************************************************************************
** Form generated from reading UI file 'MessageBoxStringList.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEBOXSTRINGLIST_H
#define UI_MESSAGEBOXSTRINGLIST_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MessageBoxStringList
{
public:
    QListWidget *listWidgetMsg;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *MessageBoxStringList)
    {
        if (MessageBoxStringList->objectName().isEmpty())
            MessageBoxStringList->setObjectName("MessageBoxStringList");
        MessageBoxStringList->resize(483, 160);
        listWidgetMsg = new QListWidget(MessageBoxStringList);
        listWidgetMsg->setObjectName("listWidgetMsg");
        listWidgetMsg->setGeometry(QRect(10, 10, 461, 101));
        listWidgetMsg->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listWidgetMsg->setAlternatingRowColors(true);
        listWidgetMsg->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonOK = new QPushButton(MessageBoxStringList);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(190, 120, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);

        retranslateUi(MessageBoxStringList);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(MessageBoxStringList);
    } // setupUi

    void retranslateUi(QDialog *MessageBoxStringList)
    {
        MessageBoxStringList->setWindowTitle(QCoreApplication::translate("MessageBoxStringList", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("MessageBoxStringList", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MessageBoxStringList: public Ui_MessageBoxStringList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEBOXSTRINGLIST_H
