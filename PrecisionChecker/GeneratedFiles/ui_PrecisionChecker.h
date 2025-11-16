/********************************************************************************
** Form generated from reading UI file 'PrecisionChecker.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRECISIONCHECKER_H
#define UI_PRECISIONCHECKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrecisionCheckerClass
{
public:
    QWidget *centralWidget;
    QFrame *frameImagePanel;
    QPushButton *pushButtonLoadImage;
    QComboBox *comboBoxPage;
    QCheckBox *chkViewBit;
    QCheckBox *chkFlexArea;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *btnHistgram;
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QSpinBox *txtX_2;
    QSpinBox *txtY_2;
    QWidget *layoutWidget1;
    QHBoxLayout *hboxLayout1;
    QSpinBox *txtX_1;
    QSpinBox *txtY_1;
    QPushButton *pushButton_7;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PrecisionCheckerClass)
    {
        if (PrecisionCheckerClass->objectName().isEmpty())
            PrecisionCheckerClass->setObjectName("PrecisionCheckerClass");
        PrecisionCheckerClass->resize(1101, 968);
        centralWidget = new QWidget(PrecisionCheckerClass);
        centralWidget->setObjectName("centralWidget");
        frameImagePanel = new QFrame(centralWidget);
        frameImagePanel->setObjectName("frameImagePanel");
        frameImagePanel->setGeometry(QRect(10, 10, 961, 901));
        frameImagePanel->setFrameShape(QFrame::StyledPanel);
        frameImagePanel->setFrameShadow(QFrame::Raised);
        pushButtonLoadImage = new QPushButton(centralWidget);
        pushButtonLoadImage->setObjectName("pushButtonLoadImage");
        pushButtonLoadImage->setGeometry(QRect(980, 50, 101, 41));
        comboBoxPage = new QComboBox(centralWidget);
        comboBoxPage->addItem(QString());
        comboBoxPage->setObjectName("comboBoxPage");
        comboBoxPage->setGeometry(QRect(990, 10, 101, 22));
        chkViewBit = new QCheckBox(centralWidget);
        chkViewBit->setObjectName("chkViewBit");
        chkViewBit->setGeometry(QRect(990, 110, 111, 18));
        chkFlexArea = new QCheckBox(centralWidget);
        chkFlexArea->setObjectName("chkFlexArea");
        chkFlexArea->setGeometry(QRect(990, 140, 101, 18));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(980, 180, 75, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(980, 620, 75, 23));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(980, 370, 75, 23));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(980, 340, 75, 23));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(980, 400, 75, 23));
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(980, 310, 75, 23));
        btnHistgram = new QPushButton(centralWidget);
        btnHistgram->setObjectName("btnHistgram");
        btnHistgram->setGeometry(QRect(980, 590, 75, 23));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(980, 560, 120, 22));
        hboxLayout = new QHBoxLayout(layoutWidget);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName("hboxLayout");
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        txtX_2 = new QSpinBox(layoutWidget);
        txtX_2->setObjectName("txtX_2");
        txtX_2->setMaximum(20000);

        hboxLayout->addWidget(txtX_2);

        txtY_2 = new QSpinBox(layoutWidget);
        txtY_2->setObjectName("txtY_2");
        txtY_2->setMaximum(20000);

        hboxLayout->addWidget(txtY_2);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(980, 530, 120, 22));
        hboxLayout1 = new QHBoxLayout(layoutWidget1);
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(11, 11, 11, 11);
        hboxLayout1->setObjectName("hboxLayout1");
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        txtX_1 = new QSpinBox(layoutWidget1);
        txtX_1->setObjectName("txtX_1");
        txtX_1->setMaximum(20000);

        hboxLayout1->addWidget(txtX_1);

        txtY_1 = new QSpinBox(layoutWidget1);
        txtY_1->setObjectName("txtY_1");
        txtY_1->setMaximum(20000);

        hboxLayout1->addWidget(txtY_1);

        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(980, 210, 75, 23));
        PrecisionCheckerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PrecisionCheckerClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1101, 18));
        PrecisionCheckerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PrecisionCheckerClass);
        mainToolBar->setObjectName("mainToolBar");
        PrecisionCheckerClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PrecisionCheckerClass);
        statusBar->setObjectName("statusBar");
        PrecisionCheckerClass->setStatusBar(statusBar);

        retranslateUi(PrecisionCheckerClass);

        comboBoxPage->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PrecisionCheckerClass);
    } // setupUi

    void retranslateUi(QMainWindow *PrecisionCheckerClass)
    {
        PrecisionCheckerClass->setWindowTitle(QCoreApplication::translate("PrecisionCheckerClass", "PrecisionChecker", nullptr));
        pushButtonLoadImage->setText(QCoreApplication::translate("PrecisionCheckerClass", "Load Image", nullptr));
        comboBoxPage->setItemText(0, QCoreApplication::translate("PrecisionCheckerClass", "Page 0", nullptr));

        chkViewBit->setText(QCoreApplication::translate("PrecisionCheckerClass", "ViewThreshHold", nullptr));
        chkFlexArea->setText(QCoreApplication::translate("PrecisionCheckerClass", "ViewFlexArea", nullptr));
        pushButton->setText(QCoreApplication::translate("PrecisionCheckerClass", "Param", nullptr));
        pushButton_2->setText(QCoreApplication::translate("PrecisionCheckerClass", "grp1", nullptr));
        pushButton_3->setText(QCoreApplication::translate("PrecisionCheckerClass", "Resolution", nullptr));
        pushButton_4->setText(QCoreApplication::translate("PrecisionCheckerClass", "Brightness", nullptr));
        pushButton_5->setText(QCoreApplication::translate("PrecisionCheckerClass", "Angle", nullptr));
        pushButton_6->setText(QCoreApplication::translate("PrecisionCheckerClass", "Focus", nullptr));
        btnHistgram->setText(QCoreApplication::translate("PrecisionCheckerClass", "Histgram", nullptr));
        pushButton_7->setText(QCoreApplication::translate("PrecisionCheckerClass", "ReScan", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PrecisionCheckerClass: public Ui_PrecisionCheckerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRECISIONCHECKER_H
