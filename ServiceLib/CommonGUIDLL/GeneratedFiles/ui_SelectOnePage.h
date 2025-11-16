/********************************************************************************
** Form generated from reading UI file 'SelectOnePage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTONEPAGE_H
#define UI_SELECTONEPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectOnePage
{
public:
    QListWidget *listWidgetPage;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *SelectOnePage)
    {
        if (SelectOnePage->objectName().isEmpty())
            SelectOnePage->setObjectName("SelectOnePage");
        SelectOnePage->resize(125, 215);
        listWidgetPage = new QListWidget(SelectOnePage);
        listWidgetPage->setObjectName("listWidgetPage");
        listWidgetPage->setGeometry(QRect(10, 10, 101, 161));
        listWidgetPage->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonOK = new QPushButton(SelectOnePage);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 180, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);

        retranslateUi(SelectOnePage);

        QMetaObject::connectSlotsByName(SelectOnePage);
    } // setupUi

    void retranslateUi(QDialog *SelectOnePage)
    {
        SelectOnePage->setWindowTitle(QCoreApplication::translate("SelectOnePage", "Select One Page", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectOnePage", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectOnePage: public Ui_SelectOnePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTONEPAGE_H
