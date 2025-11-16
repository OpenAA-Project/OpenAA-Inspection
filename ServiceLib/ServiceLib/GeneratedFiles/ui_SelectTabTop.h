/********************************************************************************
** Form generated from reading UI file 'SelectTabTop.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTTABTOP_H
#define UI_SELECTTABTOP_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectTabTop
{
public:
    QComboBox *comboBTabSheet;
    QComboBox *comboBTabPage;
    QPushButton *CancelButton;
    QLabel *label_4;
    QLabel *label_3;
    QPushButton *OKButton;

    void setupUi(QDialog *SelectTabTop)
    {
        if (SelectTabTop->objectName().isEmpty())
            SelectTabTop->setObjectName("SelectTabTop");
        SelectTabTop->resize(201, 176);
        comboBTabSheet = new QComboBox(SelectTabTop);
        comboBTabSheet->setObjectName("comboBTabSheet");
        comboBTabSheet->setGeometry(QRect(10, 30, 181, 22));
        comboBTabPage = new QComboBox(SelectTabTop);
        comboBTabPage->setObjectName("comboBTabPage");
        comboBTabPage->setGeometry(QRect(10, 90, 181, 22));
        CancelButton = new QPushButton(SelectTabTop);
        CancelButton->setObjectName("CancelButton");
        CancelButton->setGeometry(QRect(100, 130, 81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        CancelButton->setIcon(icon);
        label_4 = new QLabel(SelectTabTop);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 70, 151, 16));
        label_3 = new QLabel(SelectTabTop);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 10, 151, 16));
        OKButton = new QPushButton(SelectTabTop);
        OKButton->setObjectName("OKButton");
        OKButton->setGeometry(QRect(10, 130, 81, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        OKButton->setIcon(icon1);

        retranslateUi(SelectTabTop);

        QMetaObject::connectSlotsByName(SelectTabTop);
    } // setupUi

    void retranslateUi(QDialog *SelectTabTop)
    {
        SelectTabTop->setWindowTitle(QCoreApplication::translate("SelectTabTop", "Dialog", nullptr));
        CancelButton->setText(QCoreApplication::translate("SelectTabTop", "Cancel", nullptr));
        label_4->setText(QCoreApplication::translate("SelectTabTop", "Tab Page", nullptr));
        label_3->setText(QCoreApplication::translate("SelectTabTop", "TabSheet", nullptr));
        OKButton->setText(QCoreApplication::translate("SelectTabTop", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectTabTop: public Ui_SelectTabTop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTTABTOP_H
