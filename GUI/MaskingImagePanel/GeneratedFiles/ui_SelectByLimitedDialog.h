/********************************************************************************
** Form generated from reading UI file 'SelectByLimitedDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTBYLIMITEDDIALOG_H
#define UI_SELECTBYLIMITEDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectByLimitedDialog
{
public:
    QPushButton *ButtonCancel;
    QFrame *frameLibrary;
    QPushButton *ButtonSelectAll;
    QPushButton *ButtonSelectOneAtLeast;

    void setupUi(QDialog *SelectByLimitedDialog)
    {
        if (SelectByLimitedDialog->objectName().isEmpty())
            SelectByLimitedDialog->setObjectName("SelectByLimitedDialog");
        SelectByLimitedDialog->resize(432, 402);
        ButtonCancel = new QPushButton(SelectByLimitedDialog);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(330, 360, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon);
        frameLibrary = new QFrame(SelectByLimitedDialog);
        frameLibrary->setObjectName("frameLibrary");
        frameLibrary->setGeometry(QRect(0, -4, 431, 350));
        frameLibrary->setFrameShape(QFrame::StyledPanel);
        frameLibrary->setFrameShadow(QFrame::Sunken);
        ButtonSelectAll = new QPushButton(SelectByLimitedDialog);
        ButtonSelectAll->setObjectName("ButtonSelectAll");
        ButtonSelectAll->setGeometry(QRect(60, 360, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/SelectAll.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonSelectAll->setIcon(icon1);
        ButtonSelectOneAtLeast = new QPushButton(SelectByLimitedDialog);
        ButtonSelectOneAtLeast->setObjectName("ButtonSelectOneAtLeast");
        ButtonSelectOneAtLeast->setGeometry(QRect(180, 360, 121, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonSelectOneAtLeast->setIcon(icon2);

        retranslateUi(SelectByLimitedDialog);

        QMetaObject::connectSlotsByName(SelectByLimitedDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectByLimitedDialog)
    {
        SelectByLimitedDialog->setWindowTitle(QCoreApplication::translate("SelectByLimitedDialog", "Select by Limited", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SelectByLimitedDialog", "Cancel", nullptr));
        ButtonSelectAll->setText(QCoreApplication::translate("SelectByLimitedDialog", "Select all ", nullptr));
        ButtonSelectOneAtLeast->setText(QCoreApplication::translate("SelectByLimitedDialog", "Select one at least", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectByLimitedDialog: public Ui_SelectByLimitedDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTBYLIMITEDDIALOG_H
