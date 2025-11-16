/********************************************************************************
** Form generated from reading UI file 'GraphTrendColorDifferenceForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHTRENDCOLORDIFFERENCEFORM_H
#define UI_GRAPHTRENDCOLORDIFFERENCEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_GraphTrendColorDifferenceForm
{
public:
    QListWidget *listWidgetItemList;
    QPushButton *pushButtonLogOut;
    QWidget *widgetH;
    QWidget *widgetS;
    QWidget *widgetE;
    QComboBox *comboBoxXScale;
    QWidget *widgetV;
    QLabel *labelH;
    QLabel *labelS;
    QLabel *labelV;
    QLabel *labelE;

    void setupUi(GUIFormBase *GraphTrendColorDifferenceForm)
    {
        if (GraphTrendColorDifferenceForm->objectName().isEmpty())
            GraphTrendColorDifferenceForm->setObjectName("GraphTrendColorDifferenceForm");
        GraphTrendColorDifferenceForm->resize(1292, 293);
        listWidgetItemList = new QListWidget(GraphTrendColorDifferenceForm);
        listWidgetItemList->setObjectName("listWidgetItemList");
        listWidgetItemList->setGeometry(QRect(0, 30, 111, 231));
        listWidgetItemList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonLogOut = new QPushButton(GraphTrendColorDifferenceForm);
        pushButtonLogOut->setObjectName("pushButtonLogOut");
        pushButtonLogOut->setGeometry(QRect(0, 260, 112, 34));
        widgetH = new QWidget(GraphTrendColorDifferenceForm);
        widgetH->setObjectName("widgetH");
        widgetH->setGeometry(QRect(140, 0, 1151, 71));
        widgetS = new QWidget(GraphTrendColorDifferenceForm);
        widgetS->setObjectName("widgetS");
        widgetS->setGeometry(QRect(140, 70, 1151, 71));
        widgetE = new QWidget(GraphTrendColorDifferenceForm);
        widgetE->setObjectName("widgetE");
        widgetE->setGeometry(QRect(140, 210, 1151, 71));
        comboBoxXScale = new QComboBox(GraphTrendColorDifferenceForm);
        comboBoxXScale->addItem(QString());
        comboBoxXScale->addItem(QString());
        comboBoxXScale->addItem(QString());
        comboBoxXScale->setObjectName("comboBoxXScale");
        comboBoxXScale->setGeometry(QRect(0, 0, 111, 31));
        widgetV = new QWidget(GraphTrendColorDifferenceForm);
        widgetV->setObjectName("widgetV");
        widgetV->setGeometry(QRect(140, 140, 1151, 71));
        labelH = new QLabel(GraphTrendColorDifferenceForm);
        labelH->setObjectName("labelH");
        labelH->setGeometry(QRect(110, 0, 31, 71));
        labelH->setAlignment(Qt::AlignCenter);
        labelS = new QLabel(GraphTrendColorDifferenceForm);
        labelS->setObjectName("labelS");
        labelS->setGeometry(QRect(110, 70, 31, 71));
        labelS->setAlignment(Qt::AlignCenter);
        labelV = new QLabel(GraphTrendColorDifferenceForm);
        labelV->setObjectName("labelV");
        labelV->setGeometry(QRect(110, 140, 31, 71));
        labelV->setAlignment(Qt::AlignCenter);
        labelE = new QLabel(GraphTrendColorDifferenceForm);
        labelE->setObjectName("labelE");
        labelE->setGeometry(QRect(110, 210, 31, 81));
        labelE->setAlignment(Qt::AlignCenter);

        retranslateUi(GraphTrendColorDifferenceForm);

        QMetaObject::connectSlotsByName(GraphTrendColorDifferenceForm);
    } // setupUi

    void retranslateUi(GUIFormBase *GraphTrendColorDifferenceForm)
    {
        GraphTrendColorDifferenceForm->setWindowTitle(QCoreApplication::translate("GraphTrendColorDifferenceForm", "Form", nullptr));
        pushButtonLogOut->setText(QCoreApplication::translate("GraphTrendColorDifferenceForm", "\343\203\255\343\202\260", nullptr));
        comboBoxXScale->setItemText(0, QCoreApplication::translate("GraphTrendColorDifferenceForm", "\346\244\234\346\237\273\346\225\260", nullptr));
        comboBoxXScale->setItemText(1, QCoreApplication::translate("GraphTrendColorDifferenceForm", "100\346\244\234\346\237\273", nullptr));
        comboBoxXScale->setItemText(2, QCoreApplication::translate("GraphTrendColorDifferenceForm", "\345\210\206\346\257\216", nullptr));

        labelH->setText(QCoreApplication::translate("GraphTrendColorDifferenceForm", "H", nullptr));
        labelS->setText(QCoreApplication::translate("GraphTrendColorDifferenceForm", "S", nullptr));
        labelV->setText(QCoreApplication::translate("GraphTrendColorDifferenceForm", "V", nullptr));
        labelE->setText(QCoreApplication::translate("GraphTrendColorDifferenceForm", "\316\224E", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GraphTrendColorDifferenceForm: public Ui_GraphTrendColorDifferenceForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHTRENDCOLORDIFFERENCEFORM_H
