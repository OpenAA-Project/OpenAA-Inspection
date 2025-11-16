/********************************************************************************
** Form generated from reading UI file 'colorform.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORFORM_H
#define UI_COLORFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_colorFormClass
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButton;
    QComboBox *comboBox;
    QLineEdit *lineEdit;

    void setupUi(QDialog *colorFormClass)
    {
        if (colorFormClass->objectName().isEmpty())
            colorFormClass->setObjectName(QString::fromUtf8("colorFormClass"));
        colorFormClass->resize(418, 359);
        tableWidget = new QTableWidget(colorFormClass);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(40, 70, 281, 261));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        pushButton = new QPushButton(colorFormClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(330, 30, 75, 23));
        comboBox = new QComboBox(colorFormClass);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(40, 30, 151, 22));
        lineEdit = new QLineEdit(colorFormClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(210, 30, 113, 20));

        retranslateUi(colorFormClass);

        QMetaObject::connectSlotsByName(colorFormClass);
    } // setupUi

    void retranslateUi(QDialog *colorFormClass)
    {
        colorFormClass->setWindowTitle(QCoreApplication::translate("colorFormClass", "colorSetting", nullptr));
        pushButton->setText(QCoreApplication::translate("colorFormClass", "Set", nullptr));
    } // retranslateUi

};

namespace Ui {
    class colorFormClass: public Ui_colorFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORFORM_H
