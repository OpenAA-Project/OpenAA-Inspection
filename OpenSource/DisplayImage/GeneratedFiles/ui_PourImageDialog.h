/********************************************************************************
** Form generated from reading UI file 'PourImageDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POURIMAGEDIALOG_H
#define UI_POURIMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_PourImageDialog
{
public:
    QSpinBox *spinBoxExpand;
    QSpinBox *spinBoxPickup;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonGo;
    QLabel *label_2;
    QLabel *label;

    void setupUi(QDialog *PourImageDialog)
    {
        if (PourImageDialog->objectName().isEmpty())
            PourImageDialog->setObjectName("PourImageDialog");
        PourImageDialog->resize(220, 136);
        spinBoxExpand = new QSpinBox(PourImageDialog);
        spinBoxExpand->setObjectName("spinBoxExpand");
        spinBoxExpand->setGeometry(QRect(110, 40, 81, 31));
        spinBoxExpand->setMinimum(-999);
        spinBoxExpand->setMaximum(999);
        spinBoxPickup = new QSpinBox(PourImageDialog);
        spinBoxPickup->setObjectName("spinBoxPickup");
        spinBoxPickup->setGeometry(QRect(10, 40, 71, 31));
        spinBoxPickup->setMinimum(0);
        spinBoxPickup->setMaximum(255);
        pushButtonCancel = new QPushButton(PourImageDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(114, 90, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonGo = new QPushButton(PourImageDialog);
        pushButtonGo->setObjectName("pushButtonGo");
        pushButtonGo->setGeometry(QRect(10, 90, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonGo->setIcon(icon1);
        label_2 = new QLabel(PourImageDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(120, 5, 71, 31));
        label = new QLabel(PourImageDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 5, 71, 31));

        retranslateUi(PourImageDialog);

        pushButtonGo->setDefault(true);


        QMetaObject::connectSlotsByName(PourImageDialog);
    } // setupUi

    void retranslateUi(QDialog *PourImageDialog)
    {
        PourImageDialog->setWindowTitle(QCoreApplication::translate("PourImageDialog", "Pour", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("PourImageDialog", "Cancel", nullptr));
        pushButtonGo->setText(QCoreApplication::translate("PourImageDialog", "Go", nullptr));
        label_2->setText(QCoreApplication::translate("PourImageDialog", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210", nullptr));
        label->setText(QCoreApplication::translate("PourImageDialog", "\346\212\275\345\207\272\350\274\235\345\272\246\345\271\205", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PourImageDialog: public Ui_PourImageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POURIMAGEDIALOG_H
