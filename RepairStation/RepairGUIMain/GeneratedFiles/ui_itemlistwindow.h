/********************************************************************************
** Form generated from reading UI file 'itemlistwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMLISTWINDOW_H
#define UI_ITEMLISTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTabWidget>
#include <QtGui/QToolButton>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_ItemListWindow
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QToolButton *toolButton;
    QLabel *label;

    void setupUi(QWidget *ItemListWindow)
    {
        if (ItemListWindow->objectName().isEmpty())
            ItemListWindow->setObjectName(QString::fromUtf8("ItemListWindow"));
        ItemListWindow->resize(354, 631);
        tabWidget = new QTabWidget(ItemListWindow);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 331, 611));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        toolButton = new QToolButton(tab);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(0, 0, 31, 31));
        toolButton->setIconSize(QSize(32, 32));
        toolButton->setCheckable(true);
        toolButton->setChecked(true);
        toolButton->setAutoExclusive(true);
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 0, 61, 31));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setWordWrap(true);
        tabWidget->addTab(tab, QString());

        retranslateUi(ItemListWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ItemListWindow);
    } // setupUi

    void retranslateUi(QWidget *ItemListWindow)
    {
        ItemListWindow->setWindowTitle(QApplication::translate("ItemListWindow", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ItemListWindow", "TextLabel 1111 2222", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QString());
    } // retranslateUi

};

namespace Ui {
    class ItemListWindow: public Ui_ItemListWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMLISTWINDOW_H
