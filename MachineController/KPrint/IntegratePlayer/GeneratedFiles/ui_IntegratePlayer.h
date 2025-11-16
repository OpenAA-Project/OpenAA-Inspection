/********************************************************************************
** Form generated from reading UI file 'IntegratePlayer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATEPLAYER_H
#define UI_INTEGRATEPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IntegratePlayerClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonCheckIO;
    QSpinBox *spinBoxDelayCam1;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBoxDelayCam2;
    QLabel *label_4;
    QSpinBox *spinBoxTopOK;
    QLabel *label_5;
    QSpinBox *spinBoxTopNG;
    QLabel *label_6;
    QSpinBox *spinBoxBottomOK;
    QLabel *label_7;
    QSpinBox *spinBoxBottomNG;
    QLabel *label_8;

    void setupUi(QMainWindow *IntegratePlayerClass)
    {
        if (IntegratePlayerClass->objectName().isEmpty())
            IntegratePlayerClass->setObjectName(QString::fromUtf8("IntegratePlayerClass"));
        IntegratePlayerClass->resize(141, 141);
        centralWidget = new QWidget(IntegratePlayerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButtonCheckIO = new QPushButton(centralWidget);
        pushButtonCheckIO->setObjectName(QString::fromUtf8("pushButtonCheckIO"));
        pushButtonCheckIO->setGeometry(QRect(0, 0, 112, 34));
        spinBoxDelayCam1 = new QSpinBox(centralWidget);
        spinBoxDelayCam1->setObjectName(QString::fromUtf8("spinBoxDelayCam1"));
        spinBoxDelayCam1->setGeometry(QRect(40, 190, 71, 22));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 190, 21, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 190, 31, 21));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 220, 31, 21));
        spinBoxDelayCam2 = new QSpinBox(centralWidget);
        spinBoxDelayCam2->setObjectName(QString::fromUtf8("spinBoxDelayCam2"));
        spinBoxDelayCam2->setGeometry(QRect(40, 220, 71, 22));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(120, 220, 21, 21));
        spinBoxTopOK = new QSpinBox(centralWidget);
        spinBoxTopOK->setObjectName(QString::fromUtf8("spinBoxTopOK"));
        spinBoxTopOK->setGeometry(QRect(60, 40, 71, 22));
        spinBoxTopOK->setMaximum(99999999);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(0, 40, 51, 21));
        spinBoxTopNG = new QSpinBox(centralWidget);
        spinBoxTopNG->setObjectName(QString::fromUtf8("spinBoxTopNG"));
        spinBoxTopNG->setGeometry(QRect(60, 60, 71, 22));
        spinBoxTopNG->setMaximum(99999999);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(0, 60, 61, 21));
        spinBoxBottomOK = new QSpinBox(centralWidget);
        spinBoxBottomOK->setObjectName(QString::fromUtf8("spinBoxBottomOK"));
        spinBoxBottomOK->setGeometry(QRect(60, 90, 71, 22));
        spinBoxBottomOK->setMaximum(99999999);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(0, 90, 61, 21));
        spinBoxBottomNG = new QSpinBox(centralWidget);
        spinBoxBottomNG->setObjectName(QString::fromUtf8("spinBoxBottomNG"));
        spinBoxBottomNG->setGeometry(QRect(60, 110, 71, 22));
        spinBoxBottomNG->setMaximum(99999999);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(0, 110, 61, 21));
        IntegratePlayerClass->setCentralWidget(centralWidget);

        retranslateUi(IntegratePlayerClass);

        QMetaObject::connectSlotsByName(IntegratePlayerClass);
    } // setupUi

    void retranslateUi(QMainWindow *IntegratePlayerClass)
    {
        IntegratePlayerClass->setWindowTitle(QCoreApplication::translate("IntegratePlayerClass", "IntegratePlayer", nullptr));
        pushButtonCheckIO->setText(QCoreApplication::translate("IntegratePlayerClass", "I/O", nullptr));
        label->setText(QCoreApplication::translate("IntegratePlayerClass", "ms", nullptr));
        label_2->setText(QCoreApplication::translate("IntegratePlayerClass", "Cam1", nullptr));
        label_3->setText(QCoreApplication::translate("IntegratePlayerClass", "Cam2", nullptr));
        label_4->setText(QCoreApplication::translate("IntegratePlayerClass", "ms", nullptr));
        label_5->setText(QCoreApplication::translate("IntegratePlayerClass", "Cam1 OK", nullptr));
        label_6->setText(QCoreApplication::translate("IntegratePlayerClass", "Cam1 NG", nullptr));
        label_7->setText(QCoreApplication::translate("IntegratePlayerClass", "Cam2 OK", nullptr));
        label_8->setText(QCoreApplication::translate("IntegratePlayerClass", "Cam2 NG", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegratePlayerClass: public Ui_IntegratePlayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATEPLAYER_H
