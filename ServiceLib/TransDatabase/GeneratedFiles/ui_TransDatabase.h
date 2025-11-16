/********************************************************************************
** Form generated from reading UI file 'TransDatabase.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSDATABASE_H
#define UI_TRANSDATABASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TransDatabaseClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLineEdit *lineEditAccessPort;

    void setupUi(QMainWindow *TransDatabaseClass)
    {
        if (TransDatabaseClass->objectName().isEmpty())
            TransDatabaseClass->setObjectName("TransDatabaseClass");
        TransDatabaseClass->resize(130, 23);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TransDatabaseClass->sizePolicy().hasHeightForWidth());
        TransDatabaseClass->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(TransDatabaseClass);
        centralWidget->setObjectName("centralWidget");
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 46, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        lineEditAccessPort = new QLineEdit(centralWidget);
        lineEditAccessPort->setObjectName("lineEditAccessPort");
        lineEditAccessPort->setGeometry(QRect(60, 0, 61, 20));
        TransDatabaseClass->setCentralWidget(centralWidget);

        retranslateUi(TransDatabaseClass);

        QMetaObject::connectSlotsByName(TransDatabaseClass);
    } // setupUi

    void retranslateUi(QMainWindow *TransDatabaseClass)
    {
        TransDatabaseClass->setWindowTitle(QCoreApplication::translate("TransDatabaseClass", "TransDatabase", nullptr));
        label->setText(QCoreApplication::translate("TransDatabaseClass", "Port", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TransDatabaseClass: public Ui_TransDatabaseClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSDATABASE_H
