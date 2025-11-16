/********************************************************************************
** Form generated from reading UI file 'CameraSharer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERASHARER_H
#define UI_CAMERASHARER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraSharerClass
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QPushButton *pushButtonSetting;
    QLabel *label;
    QSpinBox *spinBoxCameraNo;
    QPushButton *pushButtonSelect;

    void setupUi(QMainWindow *CameraSharerClass)
    {
        if (CameraSharerClass->objectName().isEmpty())
            CameraSharerClass->setObjectName("CameraSharerClass");
        CameraSharerClass->resize(678, 84);
        centralWidget = new QWidget(CameraSharerClass);
        centralWidget->setObjectName("centralWidget");
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 571, 80));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonSetting = new QPushButton(centralWidget);
        pushButtonSetting->setObjectName("pushButtonSetting");
        pushButtonSetting->setGeometry(QRect(580, 50, 61, 31));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(590, 0, 81, 16));
        spinBoxCameraNo = new QSpinBox(centralWidget);
        spinBoxCameraNo->setObjectName("spinBoxCameraNo");
        spinBoxCameraNo->setGeometry(QRect(590, 20, 71, 22));
        pushButtonSelect = new QPushButton(centralWidget);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(640, 50, 31, 31));
        CameraSharerClass->setCentralWidget(centralWidget);

        retranslateUi(CameraSharerClass);

        QMetaObject::connectSlotsByName(CameraSharerClass);
    } // setupUi

    void retranslateUi(QMainWindow *CameraSharerClass)
    {
        CameraSharerClass->setWindowTitle(QCoreApplication::translate("CameraSharerClass", "CameraSharer", nullptr));
        pushButtonSetting->setText(QCoreApplication::translate("CameraSharerClass", "Setting", nullptr));
        label->setText(QCoreApplication::translate("CameraSharerClass", "Camera No", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("CameraSharerClass", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraSharerClass: public Ui_CameraSharerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERASHARER_H
