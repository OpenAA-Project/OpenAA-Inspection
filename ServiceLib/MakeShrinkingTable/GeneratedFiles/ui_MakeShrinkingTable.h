/********************************************************************************
** Form generated from reading UI file 'MakeShrinkingTable.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAKESHRINKINGTABLE_H
#define UI_MAKESHRINKINGTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MakeShrinkingTableClass
{
public:
    QWidget *centralWidget;
    QSpinBox *spinBoxNumb;
    QPushButton *pushButtonStart;
    QLineEdit *lineEditFileName;
    QLabel *label;

    void setupUi(QMainWindow *MakeShrinkingTableClass)
    {
        if (MakeShrinkingTableClass->objectName().isEmpty())
            MakeShrinkingTableClass->setObjectName("MakeShrinkingTableClass");
        MakeShrinkingTableClass->resize(410, 97);
        centralWidget = new QWidget(MakeShrinkingTableClass);
        centralWidget->setObjectName("centralWidget");
        spinBoxNumb = new QSpinBox(centralWidget);
        spinBoxNumb->setObjectName("spinBoxNumb");
        spinBoxNumb->setGeometry(QRect(40, 40, 71, 31));
        spinBoxNumb->setMaximum(9999);
        pushButtonStart = new QPushButton(centralWidget);
        pushButtonStart->setObjectName("pushButtonStart");
        pushButtonStart->setGeometry(QRect(140, 40, 91, 34));
        lineEditFileName = new QLineEdit(centralWidget);
        lineEditFileName->setObjectName("lineEditFileName");
        lineEditFileName->setGeometry(QRect(100, 10, 301, 24));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 91, 18));
        MakeShrinkingTableClass->setCentralWidget(centralWidget);

        retranslateUi(MakeShrinkingTableClass);

        QMetaObject::connectSlotsByName(MakeShrinkingTableClass);
    } // setupUi

    void retranslateUi(QMainWindow *MakeShrinkingTableClass)
    {
        MakeShrinkingTableClass->setWindowTitle(QCoreApplication::translate("MakeShrinkingTableClass", "MakeShrinkingTable", nullptr));
        pushButtonStart->setText(QCoreApplication::translate("MakeShrinkingTableClass", "Start", nullptr));
        lineEditFileName->setText(QCoreApplication::translate("MakeShrinkingTableClass", "ShrinkingTable.dat", nullptr));
        label->setText(QCoreApplication::translate("MakeShrinkingTableClass", "File name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MakeShrinkingTableClass: public Ui_MakeShrinkingTableClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAKESHRINKINGTABLE_H
