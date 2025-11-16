/********************************************************************************
** Form generated from reading UI file 'SelectCreateNew.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTCREATENEW_H
#define UI_SELECTCREATENEW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectCreateNewClass
{
public:
    QPushButton *pushButtonCreateNew;
    QPushButton *pushButtonGetColorMap;

    void setupUi(QDialog *SelectCreateNewClass)
    {
        if (SelectCreateNewClass->objectName().isEmpty())
            SelectCreateNewClass->setObjectName("SelectCreateNewClass");
        SelectCreateNewClass->resize(311, 70);
        pushButtonCreateNew = new QPushButton(SelectCreateNewClass);
        pushButtonCreateNew->setObjectName("pushButtonCreateNew");
        pushButtonCreateNew->setGeometry(QRect(10, 10, 141, 51));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Area.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCreateNew->setIcon(icon);
        pushButtonGetColorMap = new QPushButton(SelectCreateNewClass);
        pushButtonGetColorMap->setObjectName("pushButtonGetColorMap");
        pushButtonGetColorMap->setGeometry(QRect(160, 10, 141, 51));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Color.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonGetColorMap->setIcon(icon1);

        retranslateUi(SelectCreateNewClass);

        QMetaObject::connectSlotsByName(SelectCreateNewClass);
    } // setupUi

    void retranslateUi(QDialog *SelectCreateNewClass)
    {
        SelectCreateNewClass->setWindowTitle(QCoreApplication::translate("SelectCreateNewClass", "SelectCreateNew", nullptr));
        pushButtonCreateNew->setText(QCoreApplication::translate("SelectCreateNewClass", "\351\240\230\345\237\237\343\201\256\346\226\260\350\246\217\344\275\234\346\210\220", nullptr));
        pushButtonGetColorMap->setText(QCoreApplication::translate("SelectCreateNewClass", "\343\202\253\343\203\251\342\200\225\343\203\236\343\203\203\343\203\227\345\217\226\345\276\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectCreateNewClass: public Ui_SelectCreateNewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTCREATENEW_H
