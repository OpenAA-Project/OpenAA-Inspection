/********************************************************************************
** Form generated from reading UI file 'TransFileServer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSFILESERVER_H
#define UI_TRANSFILESERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TransFileServerClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QSpinBox *spinBoxTransPort;
    QLabel *label_2;
    QLineEdit *lineEditCachePath;
    QProgressBar *progressBar;

    void setupUi(QMainWindow *TransFileServerClass)
    {
        if (TransFileServerClass->objectName().isEmpty())
            TransFileServerClass->setObjectName("TransFileServerClass");
        TransFileServerClass->resize(380, 104);
        centralWidget = new QWidget(TransFileServerClass);
        centralWidget->setObjectName("centralWidget");
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 71, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        spinBoxTransPort = new QSpinBox(centralWidget);
        spinBoxTransPort->setObjectName("spinBoxTransPort");
        spinBoxTransPort->setGeometry(QRect(10, 30, 71, 22));
        spinBoxTransPort->setMaximum(65535);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(90, 10, 281, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        lineEditCachePath = new QLineEdit(centralWidget);
        lineEditCachePath->setObjectName("lineEditCachePath");
        lineEditCachePath->setGeometry(QRect(90, 30, 281, 20));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(10, 70, 361, 23));
        progressBar->setValue(24);
        TransFileServerClass->setCentralWidget(centralWidget);

        retranslateUi(TransFileServerClass);

        QMetaObject::connectSlotsByName(TransFileServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *TransFileServerClass)
    {
        TransFileServerClass->setWindowTitle(QCoreApplication::translate("TransFileServerClass", "TransFileServer", nullptr));
        label->setText(QCoreApplication::translate("TransFileServerClass", "Port", nullptr));
        label_2->setText(QCoreApplication::translate("TransFileServerClass", "Cache path", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TransFileServerClass: public Ui_TransFileServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSFILESERVER_H
