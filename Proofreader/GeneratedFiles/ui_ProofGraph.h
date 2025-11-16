/********************************************************************************
** Form generated from reading UI file 'ProofGraph.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROOFGRAPH_H
#define UI_PROOFGRAPH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProofGraphClass
{
public:
    QGridLayout *gridLayout;
    QDockWidget *dwShowGraph;
    QWidget *dockWidgetContents;
    QHBoxLayout *hboxLayout;
    QGridLayout *gridLayout1;
    QLabel *label;
    QDoubleSpinBox *dsbAverageY;
    QLabel *label_2;
    QDoubleSpinBox *dsbCalibration;
    QPushButton *pbSave;
    QSpacerItem *spacerItem;
    QPushButton *pbClose;

    void setupUi(QDialog *ProofGraphClass)
    {
        if (ProofGraphClass->objectName().isEmpty())
            ProofGraphClass->setObjectName("ProofGraphClass");
        ProofGraphClass->resize(769, 662);
        gridLayout = new QGridLayout(ProofGraphClass);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setVerticalSpacing(6);
        gridLayout->setContentsMargins(9, 9, 9, 9);
        dwShowGraph = new QDockWidget(ProofGraphClass);
        dwShowGraph->setObjectName("dwShowGraph");
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        dwShowGraph->setWidget(dockWidgetContents);

        gridLayout->addWidget(dwShowGraph, 0, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName("hboxLayout");
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout1 = new QGridLayout();
        gridLayout1->setObjectName("gridLayout1");
        gridLayout1->setHorizontalSpacing(6);
        gridLayout1->setVerticalSpacing(6);
        gridLayout1->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(ProofGraphClass);
        label->setObjectName("label");

        gridLayout1->addWidget(label, 0, 0, 1, 1);

        dsbAverageY = new QDoubleSpinBox(ProofGraphClass);
        dsbAverageY->setObjectName("dsbAverageY");
        dsbAverageY->setReadOnly(true);
        dsbAverageY->setDecimals(5);
        dsbAverageY->setMaximum(99999.999989999996615);

        gridLayout1->addWidget(dsbAverageY, 0, 1, 1, 1);

        label_2 = new QLabel(ProofGraphClass);
        label_2->setObjectName("label_2");

        gridLayout1->addWidget(label_2, 1, 0, 1, 1);

        dsbCalibration = new QDoubleSpinBox(ProofGraphClass);
        dsbCalibration->setObjectName("dsbCalibration");
        dsbCalibration->setDecimals(5);
        dsbCalibration->setMaximum(99999.999989999996615);

        gridLayout1->addWidget(dsbCalibration, 1, 1, 1, 1);


        hboxLayout->addLayout(gridLayout1);

        pbSave = new QPushButton(ProofGraphClass);
        pbSave->setObjectName("pbSave");
        pbSave->setMinimumSize(QSize(0, 51));

        hboxLayout->addWidget(pbSave);

        spacerItem = new QSpacerItem(331, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem);

        pbClose = new QPushButton(ProofGraphClass);
        pbClose->setObjectName("pbClose");
        pbClose->setMinimumSize(QSize(0, 51));

        hboxLayout->addWidget(pbClose);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);


        retranslateUi(ProofGraphClass);

        QMetaObject::connectSlotsByName(ProofGraphClass);
    } // setupUi

    void retranslateUi(QDialog *ProofGraphClass)
    {
        ProofGraphClass->setWindowTitle(QCoreApplication::translate("ProofGraphClass", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ProofGraphClass", "Average of Y", nullptr));
        label_2->setText(QCoreApplication::translate("ProofGraphClass", "Calibration value", nullptr));
        pbSave->setText(QCoreApplication::translate("ProofGraphClass", "Save", nullptr));
        pbClose->setText(QCoreApplication::translate("ProofGraphClass", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProofGraphClass: public Ui_ProofGraphClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROOFGRAPH_H
