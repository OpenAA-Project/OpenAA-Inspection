/********************************************************************************
** Form generated from reading UI file 'SetOKDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETOKDIALOG_H
#define UI_SETOKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetOKDialog
{
public:
    QPushButton *pushButtonBOKBright;
    QPushButton *pushButtonBOKSize;
    QPushButton *pushButtonNOKBright;
    QPushButton *pushButtonNOKSize;
    QPushButton *pushButtonOKSearch;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *SetOKDialog)
    {
        if (SetOKDialog->objectName().isEmpty())
            SetOKDialog->setObjectName("SetOKDialog");
        SetOKDialog->resize(265, 395);
        pushButtonBOKBright = new QPushButton(SetOKDialog);
        pushButtonBOKBright->setObjectName("pushButtonBOKBright");
        pushButtonBOKBright->setGeometry(QRect(20, 20, 221, 51));
        pushButtonBOKSize = new QPushButton(SetOKDialog);
        pushButtonBOKSize->setObjectName("pushButtonBOKSize");
        pushButtonBOKSize->setGeometry(QRect(20, 70, 221, 51));
        pushButtonNOKBright = new QPushButton(SetOKDialog);
        pushButtonNOKBright->setObjectName("pushButtonNOKBright");
        pushButtonNOKBright->setGeometry(QRect(20, 130, 221, 51));
        pushButtonNOKSize = new QPushButton(SetOKDialog);
        pushButtonNOKSize->setObjectName("pushButtonNOKSize");
        pushButtonNOKSize->setGeometry(QRect(20, 180, 221, 51));
        pushButtonOKSearch = new QPushButton(SetOKDialog);
        pushButtonOKSearch->setObjectName("pushButtonOKSearch");
        pushButtonOKSearch->setGeometry(QRect(20, 250, 221, 51));
        pushButtonClose = new QPushButton(SetOKDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(50, 330, 161, 41));

        retranslateUi(SetOKDialog);

        pushButtonClose->setDefault(true);


        QMetaObject::connectSlotsByName(SetOKDialog);
    } // setupUi

    void retranslateUi(QDialog *SetOKDialog)
    {
        SetOKDialog->setWindowTitle(QCoreApplication::translate("SetOKDialog", "OK\345\210\244\345\256\232", nullptr));
        pushButtonBOKBright->setText(QCoreApplication::translate("SetOKDialog", "\345\272\203\345\237\237\350\274\235\345\272\246\347\257\204\345\233\262\343\201\247OK\345\210\244\345\256\232", nullptr));
        pushButtonBOKSize->setText(QCoreApplication::translate("SetOKDialog", "\345\272\203\345\237\237\343\201\256NG\343\202\265\343\202\244\343\202\272\343\201\247OK\345\210\244\345\256\232", nullptr));
        pushButtonNOKBright->setText(QCoreApplication::translate("SetOKDialog", "\347\213\255\345\237\237\350\274\235\345\272\246\347\257\204\345\233\262\343\201\247OK\345\210\244\345\256\232", nullptr));
        pushButtonNOKSize->setText(QCoreApplication::translate("SetOKDialog", "\347\213\255\345\237\237\343\201\256NG\343\202\265\343\202\244\343\202\272\343\201\247OK\345\210\244\345\256\232", nullptr));
        pushButtonOKSearch->setText(QCoreApplication::translate("SetOKDialog", "\346\216\242\347\264\242\347\257\204\345\233\262\343\201\247OK\345\210\244\345\256\232", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SetOKDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetOKDialog: public Ui_SetOKDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETOKDIALOG_H
