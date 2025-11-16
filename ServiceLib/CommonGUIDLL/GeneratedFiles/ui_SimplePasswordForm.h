/********************************************************************************
** Form generated from reading UI file 'SimplePasswordForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLEPASSWORDFORM_H
#define UI_SIMPLEPASSWORDFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SimplePasswordForm
{
public:
    QPushButton *pushButtonOK;
    QLineEdit *lineEditPassword;
    QLabel *label;

    void setupUi(QDialog *SimplePasswordForm)
    {
        if (SimplePasswordForm->objectName().isEmpty())
            SimplePasswordForm->setObjectName("SimplePasswordForm");
        SimplePasswordForm->resize(247, 92);
        pushButtonOK = new QPushButton(SimplePasswordForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(80, 60, 75, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        lineEditPassword = new QLineEdit(SimplePasswordForm);
        lineEditPassword->setObjectName("lineEditPassword");
        lineEditPassword->setGeometry(QRect(10, 30, 231, 20));
        label = new QLabel(SimplePasswordForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 231, 20));
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(SimplePasswordForm);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SimplePasswordForm);
    } // setupUi

    void retranslateUi(QDialog *SimplePasswordForm)
    {
        SimplePasswordForm->setWindowTitle(QCoreApplication::translate("SimplePasswordForm", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SimplePasswordForm", "OK", nullptr));
        lineEditPassword->setText(QCoreApplication::translate("SimplePasswordForm", "XXXXXXXX", nullptr));
        label->setText(QCoreApplication::translate("SimplePasswordForm", "\343\203\221\343\202\271\343\203\257\343\203\274\343\203\211\343\202\222\345\205\245\345\212\233\343\201\227\343\201\246\343\201\217\343\201\240\343\201\225\343\201\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimplePasswordForm: public Ui_SimplePasswordForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLEPASSWORDFORM_H
