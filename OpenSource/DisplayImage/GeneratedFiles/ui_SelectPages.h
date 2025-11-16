/********************************************************************************
** Form generated from reading UI file 'SelectPages.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTPAGES_H
#define UI_SELECTPAGES_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectPages
{
public:
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonAll;
    QListWidget *listWidgetSelect;
    QPushButton *pushButtonRelease;

    void setupUi(QDialog *SelectPages)
    {
        if (SelectPages->objectName().isEmpty())
            SelectPages->setObjectName("SelectPages");
        SelectPages->resize(222, 167);
        pushButtonSelect = new QPushButton(SelectPages);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(10, 130, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSelect->setIcon(icon);
        pushButtonAll = new QPushButton(SelectPages);
        pushButtonAll->setObjectName("pushButtonAll");
        pushButtonAll->setGeometry(QRect(120, 30, 91, 34));
        listWidgetSelect = new QListWidget(SelectPages);
        listWidgetSelect->setObjectName("listWidgetSelect");
        listWidgetSelect->setGeometry(QRect(10, 10, 101, 111));
        listWidgetSelect->setSelectionMode(QAbstractItemView::MultiSelection);
        listWidgetSelect->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonRelease = new QPushButton(SelectPages);
        pushButtonRelease->setObjectName("pushButtonRelease");
        pushButtonRelease->setGeometry(QRect(120, 80, 91, 34));

        retranslateUi(SelectPages);

        QMetaObject::connectSlotsByName(SelectPages);
    } // setupUi

    void retranslateUi(QDialog *SelectPages)
    {
        SelectPages->setWindowTitle(QCoreApplication::translate("SelectPages", "Dialog", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectPages", "Select", nullptr));
        pushButtonAll->setText(QCoreApplication::translate("SelectPages", "All", nullptr));
        pushButtonRelease->setText(QCoreApplication::translate("SelectPages", "Release", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectPages: public Ui_SelectPages {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTPAGES_H
