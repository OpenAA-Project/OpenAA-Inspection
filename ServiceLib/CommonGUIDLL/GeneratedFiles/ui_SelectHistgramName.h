/********************************************************************************
** Form generated from reading UI file 'SelectHistgramName.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTHISTGRAMNAME_H
#define UI_SELECTHISTGRAMNAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectHistgramName
{
public:
    QListWidget *listWidgetHistName;
    QPushButton *pushButtonSelect;

    void setupUi(QDialog *SelectHistgramName)
    {
        if (SelectHistgramName->objectName().isEmpty())
            SelectHistgramName->setObjectName("SelectHistgramName");
        SelectHistgramName->resize(257, 230);
        listWidgetHistName = new QListWidget(SelectHistgramName);
        listWidgetHistName->setObjectName("listWidgetHistName");
        listWidgetHistName->setGeometry(QRect(0, 0, 256, 192));
        pushButtonSelect = new QPushButton(SelectHistgramName);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(90, 192, 75, 31));

        retranslateUi(SelectHistgramName);

        QMetaObject::connectSlotsByName(SelectHistgramName);
    } // setupUi

    void retranslateUi(QDialog *SelectHistgramName)
    {
        SelectHistgramName->setWindowTitle(QCoreApplication::translate("SelectHistgramName", "Select histgram name", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectHistgramName", "Select", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectHistgramName: public Ui_SelectHistgramName {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTHISTGRAMNAME_H
