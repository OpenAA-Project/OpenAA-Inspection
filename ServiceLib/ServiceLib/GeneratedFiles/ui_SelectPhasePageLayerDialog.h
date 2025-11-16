/********************************************************************************
** Form generated from reading UI file 'SelectPhasePageLayerDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTPHASEPAGELAYERDIALOG_H
#define UI_SELECTPHASEPAGELAYERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectPhasePageLayerDialog
{
public:
    QListWidget *listWidgetPhase1;
    QListWidget *listWidgetPage1;
    QLabel *labelLayer;
    QPushButton *pushButtonSelect1;
    QLabel *labelPage;
    QPushButton *pushButtonCancel1;
    QLabel *labelPhase;
    QListWidget *listWidgetLayer1;

    void setupUi(QDialog *SelectPhasePageLayerDialog)
    {
        if (SelectPhasePageLayerDialog->objectName().isEmpty())
            SelectPhasePageLayerDialog->setObjectName("SelectPhasePageLayerDialog");
        SelectPhasePageLayerDialog->resize(420, 255);
        listWidgetPhase1 = new QListWidget(SelectPhasePageLayerDialog);
        listWidgetPhase1->setObjectName("listWidgetPhase1");
        listWidgetPhase1->setGeometry(QRect(10, 30, 111, 171));
        listWidgetPhase1->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidgetPage1 = new QListWidget(SelectPhasePageLayerDialog);
        listWidgetPage1->setObjectName("listWidgetPage1");
        listWidgetPage1->setGeometry(QRect(130, 30, 111, 171));
        listWidgetPage1->setSelectionBehavior(QAbstractItemView::SelectRows);
        labelLayer = new QLabel(SelectPhasePageLayerDialog);
        labelLayer->setObjectName("labelLayer");
        labelLayer->setGeometry(QRect(260, 10, 91, 18));
        pushButtonSelect1 = new QPushButton(SelectPhasePageLayerDialog);
        pushButtonSelect1->setObjectName("pushButtonSelect1");
        pushButtonSelect1->setGeometry(QRect(70, 210, 112, 34));
        labelPage = new QLabel(SelectPhasePageLayerDialog);
        labelPage->setObjectName("labelPage");
        labelPage->setGeometry(QRect(140, 10, 91, 18));
        pushButtonCancel1 = new QPushButton(SelectPhasePageLayerDialog);
        pushButtonCancel1->setObjectName("pushButtonCancel1");
        pushButtonCancel1->setGeometry(QRect(190, 210, 112, 34));
        labelPhase = new QLabel(SelectPhasePageLayerDialog);
        labelPhase->setObjectName("labelPhase");
        labelPhase->setGeometry(QRect(20, 10, 91, 18));
        listWidgetLayer1 = new QListWidget(SelectPhasePageLayerDialog);
        listWidgetLayer1->setObjectName("listWidgetLayer1");
        listWidgetLayer1->setGeometry(QRect(250, 30, 161, 171));
        listWidgetLayer1->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(SelectPhasePageLayerDialog);

        pushButtonSelect1->setDefault(true);


        QMetaObject::connectSlotsByName(SelectPhasePageLayerDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectPhasePageLayerDialog)
    {
        SelectPhasePageLayerDialog->setWindowTitle(QCoreApplication::translate("SelectPhasePageLayerDialog", "Dialog", nullptr));
        labelLayer->setText(QCoreApplication::translate("SelectPhasePageLayerDialog", "Layer", nullptr));
        pushButtonSelect1->setText(QCoreApplication::translate("SelectPhasePageLayerDialog", "Select", nullptr));
        labelPage->setText(QCoreApplication::translate("SelectPhasePageLayerDialog", "Page", nullptr));
        pushButtonCancel1->setText(QCoreApplication::translate("SelectPhasePageLayerDialog", "Cancel", nullptr));
        labelPhase->setText(QCoreApplication::translate("SelectPhasePageLayerDialog", "Phase", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectPhasePageLayerDialog: public Ui_SelectPhasePageLayerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTPHASEPAGELAYERDIALOG_H
