/********************************************************************************
** Form generated from reading UI file 'itemlistwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMLISTWINDOW_H
#define UI_ITEMLISTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ItemListWindow
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QToolButton *toolButton;
    QLabel *label;

    void setupUi(GUIFormBase *ItemListWindow)
    {
        if (ItemListWindow->objectName().isEmpty())
            ItemListWindow->setObjectName("ItemListWindow");
        ItemListWindow->resize(354, 631);
        tabWidget = new QTabWidget(ItemListWindow);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(10, 10, 331, 611));
        tab = new QWidget();
        tab->setObjectName("tab");
        toolButton = new QToolButton(tab);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(0, 0, 31, 31));
        toolButton->setIconSize(QSize(32, 32));
        toolButton->setCheckable(true);
        toolButton->setChecked(true);
        toolButton->setAutoExclusive(true);
        label = new QLabel(tab);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 0, 61, 31));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setWordWrap(true);
        tabWidget->addTab(tab, QString());

        retranslateUi(ItemListWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ItemListWindow);
    } // setupUi

    void retranslateUi(GUIFormBase *ItemListWindow)
    {
        ItemListWindow->setWindowTitle(QCoreApplication::translate("ItemListWindow", "Form", nullptr));
        label->setText(QCoreApplication::translate("ItemListWindow", "TextLabel 1111 2222", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QString());
    } // retranslateUi

};

namespace Ui {
    class ItemListWindow: public Ui_ItemListWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMLISTWINDOW_H
