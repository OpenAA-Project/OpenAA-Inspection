/********************************************************************************
** Form generated from reading UI file 'GraphTrendKidaForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHTRENDKIDAFORM_H
#define UI_GRAPHTRENDKIDAFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_GraphTrendKidaForm
{
public:
    QListWidget *listWidget;
    QPushButton *pushButtonShowLog;

    void setupUi(GUIFormBase *GraphTrendKidaForm)
    {
        if (GraphTrendKidaForm->objectName().isEmpty())
            GraphTrendKidaForm->setObjectName("GraphTrendKidaForm");
        GraphTrendKidaForm->resize(661, 220);
        listWidget = new QListWidget(GraphTrendKidaForm);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 0, 71, 181));
        QFont font;
        font.setPointSize(12);
        listWidget->setFont(font);
        listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonShowLog = new QPushButton(GraphTrendKidaForm);
        pushButtonShowLog->setObjectName("pushButtonShowLog");
        pushButtonShowLog->setGeometry(QRect(0, 180, 71, 41));

        retranslateUi(GraphTrendKidaForm);

        QMetaObject::connectSlotsByName(GraphTrendKidaForm);
    } // setupUi

    void retranslateUi(GUIFormBase *GraphTrendKidaForm)
    {
        GraphTrendKidaForm->setWindowTitle(QCoreApplication::translate("GraphTrendKidaForm", "Form", nullptr));
        pushButtonShowLog->setText(QCoreApplication::translate("GraphTrendKidaForm", "\343\203\255\343\202\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GraphTrendKidaForm: public Ui_GraphTrendKidaForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHTRENDKIDAFORM_H
