/********************************************************************************
** Form generated from reading UI file 'EVDLLListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVDLLLISTFORM_H
#define UI_EVDLLLISTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EVDLLListForm
{
public:
    QTabWidget *tabWidgetDLLList;
    QWidget *tab;
    QWidget *tab_2;

    void setupUi(QWidget *EVDLLListForm)
    {
        if (EVDLLListForm->objectName().isEmpty())
            EVDLLListForm->setObjectName("EVDLLListForm");
        EVDLLListForm->resize(325, 566);
        tabWidgetDLLList = new QTabWidget(EVDLLListForm);
        tabWidgetDLLList->setObjectName("tabWidgetDLLList");
        tabWidgetDLLList->setGeometry(QRect(0, 0, 321, 531));
        tab = new QWidget();
        tab->setObjectName("tab");
        tabWidgetDLLList->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabWidgetDLLList->addTab(tab_2, QString());

        retranslateUi(EVDLLListForm);

        QMetaObject::connectSlotsByName(EVDLLListForm);
    } // setupUi

    void retranslateUi(QWidget *EVDLLListForm)
    {
        EVDLLListForm->setWindowTitle(QCoreApplication::translate("EVDLLListForm", "Form", nullptr));
        tabWidgetDLLList->setTabText(tabWidgetDLLList->indexOf(tab), QCoreApplication::translate("EVDLLListForm", "Tab 1", nullptr));
        tabWidgetDLLList->setTabText(tabWidgetDLLList->indexOf(tab_2), QCoreApplication::translate("EVDLLListForm", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EVDLLListForm: public Ui_EVDLLListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVDLLLISTFORM_H
