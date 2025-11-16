/********************************************************************************
** Form generated from reading UI file 'InputPageAndItemNameDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTPAGEANDITEMNAMEDIALOG_H
#define UI_INPUTPAGEANDITEMNAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputPageAndItemNameDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBoxPage;
    QLineEdit *lineEditItemName;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *InputPageAndItemNameDialog)
    {
        if (InputPageAndItemNameDialog->objectName().isEmpty())
            InputPageAndItemNameDialog->setObjectName("InputPageAndItemNameDialog");
        InputPageAndItemNameDialog->resize(379, 136);
        label = new QLabel(InputPageAndItemNameDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 81, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(InputPageAndItemNameDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 40, 81, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        comboBoxPage = new QComboBox(InputPageAndItemNameDialog);
        comboBoxPage->setObjectName("comboBoxPage");
        comboBoxPage->setGeometry(QRect(100, 10, 80, 22));
        lineEditItemName = new QLineEdit(InputPageAndItemNameDialog);
        lineEditItemName->setObjectName("lineEditItemName");
        lineEditItemName->setGeometry(QRect(100, 40, 271, 21));
        pushButtonOK = new QPushButton(InputPageAndItemNameDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 80, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(InputPageAndItemNameDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(240, 80, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(InputPageAndItemNameDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(InputPageAndItemNameDialog);
    } // setupUi

    void retranslateUi(QDialog *InputPageAndItemNameDialog)
    {
        InputPageAndItemNameDialog->setWindowTitle(QCoreApplication::translate("InputPageAndItemNameDialog", "Input Page and ItemName", nullptr));
        label->setText(QCoreApplication::translate("InputPageAndItemNameDialog", "Page", nullptr));
        label_2->setText(QCoreApplication::translate("InputPageAndItemNameDialog", "Item name", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputPageAndItemNameDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputPageAndItemNameDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputPageAndItemNameDialog: public Ui_InputPageAndItemNameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTPAGEANDITEMNAMEDIALOG_H
