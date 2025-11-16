/********************************************************************************
** Form generated from reading UI file 'proofreader.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROOFREADER_H
#define UI_PROOFREADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProofreaderClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QToolButton *tbExpansion;
    QToolButton *tbWhole;
    QToolButton *tbRectangle;
    QComboBox *cbCamera;
    QCheckBox *chkReverse;
    QSpacerItem *spacerItem;
    QPushButton *pbLoadPixHalcon;
    QSpacerItem *spacerItem1;
    QVBoxLayout *vboxLayout;
    QPushButton *pbLoadMasterImage;
    QSpacerItem *spacerItem2;
    QSpinBox *sbThreshold;
    QPushButton *pbThreshold;
    QPushButton *pbLabelingX;
    QPushButton *pbLabelingY;
    QPushButton *pbSave;
    QPushButton *pbShowGraph;
    QPushButton *pbShowGraphFromCsv;
    QSpacerItem *spacerItem3;
    QPushButton *pbWhiteBalance;
    QSpacerItem *spacerItem4;
    QPushButton *pbClose;
    QDockWidget *dwMasterImage;
    QWidget *dockWidgetContents;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProofreaderClass)
    {
        if (ProofreaderClass->objectName().isEmpty())
            ProofreaderClass->setObjectName("ProofreaderClass");
        ProofreaderClass->resize(768, 778);
        centralWidget = new QWidget(ProofreaderClass);
        centralWidget->setObjectName("centralWidget");
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName("hboxLayout");
        tbExpansion = new QToolButton(centralWidget);
        tbExpansion->setObjectName("tbExpansion");
        tbExpansion->setMinimumSize(QSize(45, 41));

        hboxLayout->addWidget(tbExpansion);

        tbWhole = new QToolButton(centralWidget);
        tbWhole->setObjectName("tbWhole");
        tbWhole->setMinimumSize(QSize(45, 41));

        hboxLayout->addWidget(tbWhole);

        tbRectangle = new QToolButton(centralWidget);
        tbRectangle->setObjectName("tbRectangle");
        tbRectangle->setMinimumSize(QSize(45, 41));

        hboxLayout->addWidget(tbRectangle);

        cbCamera = new QComboBox(centralWidget);
        cbCamera->setObjectName("cbCamera");
        cbCamera->setMinimumSize(QSize(80, 0));

        hboxLayout->addWidget(cbCamera);

        chkReverse = new QCheckBox(centralWidget);
        chkReverse->setObjectName("chkReverse");

        hboxLayout->addWidget(chkReverse);

        spacerItem = new QSpacerItem(31, 41, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem);

        pbLoadPixHalcon = new QPushButton(centralWidget);
        pbLoadPixHalcon->setObjectName("pbLoadPixHalcon");
        pbLoadPixHalcon->setMinimumSize(QSize(101, 41));

        hboxLayout->addWidget(pbLoadPixHalcon);

        spacerItem1 = new QSpacerItem(31, 41, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem1);


        gridLayout->addLayout(hboxLayout, 0, 0, 1, 1);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName("vboxLayout");
        pbLoadMasterImage = new QPushButton(centralWidget);
        pbLoadMasterImage->setObjectName("pbLoadMasterImage");
        pbLoadMasterImage->setMinimumSize(QSize(101, 41));

        vboxLayout->addWidget(pbLoadMasterImage);

        spacerItem2 = new QSpacerItem(116, 61, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout->addItem(spacerItem2);

        sbThreshold = new QSpinBox(centralWidget);
        sbThreshold->setObjectName("sbThreshold");
        sbThreshold->setMaximum(255);

        vboxLayout->addWidget(sbThreshold);

        pbThreshold = new QPushButton(centralWidget);
        pbThreshold->setObjectName("pbThreshold");
        pbThreshold->setMinimumSize(QSize(101, 41));

        vboxLayout->addWidget(pbThreshold);

        pbLabelingX = new QPushButton(centralWidget);
        pbLabelingX->setObjectName("pbLabelingX");
        pbLabelingX->setMinimumSize(QSize(101, 41));

        vboxLayout->addWidget(pbLabelingX);

        pbLabelingY = new QPushButton(centralWidget);
        pbLabelingY->setObjectName("pbLabelingY");
        pbLabelingY->setMinimumSize(QSize(101, 41));

        vboxLayout->addWidget(pbLabelingY);

        pbSave = new QPushButton(centralWidget);
        pbSave->setObjectName("pbSave");
        pbSave->setMinimumSize(QSize(101, 41));

        vboxLayout->addWidget(pbSave);

        pbShowGraph = new QPushButton(centralWidget);
        pbShowGraph->setObjectName("pbShowGraph");
        pbShowGraph->setMinimumSize(QSize(101, 41));

        vboxLayout->addWidget(pbShowGraph);

        pbShowGraphFromCsv = new QPushButton(centralWidget);
        pbShowGraphFromCsv->setObjectName("pbShowGraphFromCsv");
        pbShowGraphFromCsv->setMinimumSize(QSize(101, 41));

        vboxLayout->addWidget(pbShowGraphFromCsv);

        spacerItem3 = new QSpacerItem(116, 51, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout->addItem(spacerItem3);

        pbWhiteBalance = new QPushButton(centralWidget);
        pbWhiteBalance->setObjectName("pbWhiteBalance");
        pbWhiteBalance->setMinimumSize(QSize(101, 41));

        vboxLayout->addWidget(pbWhiteBalance);

        spacerItem4 = new QSpacerItem(116, 51, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout->addItem(spacerItem4);

        pbClose = new QPushButton(centralWidget);
        pbClose->setObjectName("pbClose");
        pbClose->setMinimumSize(QSize(101, 41));

        vboxLayout->addWidget(pbClose);


        gridLayout->addLayout(vboxLayout, 0, 1, 2, 1);

        dwMasterImage = new QDockWidget(centralWidget);
        dwMasterImage->setObjectName("dwMasterImage");
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        dwMasterImage->setWidget(dockWidgetContents);

        gridLayout->addWidget(dwMasterImage, 1, 0, 1, 1);

        ProofreaderClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ProofreaderClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 768, 18));
        ProofreaderClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ProofreaderClass);
        mainToolBar->setObjectName("mainToolBar");
        mainToolBar->setOrientation(Qt::Horizontal);
        ProofreaderClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ProofreaderClass);
        statusBar->setObjectName("statusBar");
        ProofreaderClass->setStatusBar(statusBar);

        retranslateUi(ProofreaderClass);

        QMetaObject::connectSlotsByName(ProofreaderClass);
    } // setupUi

    void retranslateUi(QMainWindow *ProofreaderClass)
    {
        ProofreaderClass->setWindowTitle(QCoreApplication::translate("ProofreaderClass", "Proofreader", nullptr));
#if QT_CONFIG(tooltip)
        tbExpansion->setToolTip(QCoreApplication::translate("ProofreaderClass", "Expansion", nullptr));
#endif // QT_CONFIG(tooltip)
        tbExpansion->setText(QCoreApplication::translate("ProofreaderClass", "Exp", nullptr));
#if QT_CONFIG(tooltip)
        tbWhole->setToolTip(QCoreApplication::translate("ProofreaderClass", "Whole", nullptr));
#endif // QT_CONFIG(tooltip)
        tbWhole->setText(QCoreApplication::translate("ProofreaderClass", "Whole", nullptr));
#if QT_CONFIG(tooltip)
        tbRectangle->setToolTip(QCoreApplication::translate("ProofreaderClass", "Rectangle", nullptr));
#endif // QT_CONFIG(tooltip)
        tbRectangle->setText(QCoreApplication::translate("ProofreaderClass", "Rect", nullptr));
        chkReverse->setText(QCoreApplication::translate("ProofreaderClass", "White-Black Reverse", nullptr));
        pbLoadPixHalcon->setText(QCoreApplication::translate("ProofreaderClass", "Load PIX For HALCON", nullptr));
        pbLoadMasterImage->setText(QCoreApplication::translate("ProofreaderClass", "LoadMasterImage", nullptr));
        pbThreshold->setText(QCoreApplication::translate("ProofreaderClass", "Threshold", nullptr));
        pbLabelingX->setText(QCoreApplication::translate("ProofreaderClass", "Labeling X", nullptr));
        pbLabelingY->setText(QCoreApplication::translate("ProofreaderClass", "Labeling Y", nullptr));
        pbSave->setText(QCoreApplication::translate("ProofreaderClass", "Save", nullptr));
        pbShowGraph->setText(QCoreApplication::translate("ProofreaderClass", "ShowGraph", nullptr));
        pbShowGraphFromCsv->setText(QCoreApplication::translate("ProofreaderClass", "ShowGraph from csv", nullptr));
        pbWhiteBalance->setText(QCoreApplication::translate("ProofreaderClass", "White Balance", nullptr));
        pbClose->setText(QCoreApplication::translate("ProofreaderClass", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProofreaderClass: public Ui_ProofreaderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROOFREADER_H
