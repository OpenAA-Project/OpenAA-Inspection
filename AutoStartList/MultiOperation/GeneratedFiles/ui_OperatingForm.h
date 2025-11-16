/********************************************************************************
** Form generated from reading UI file 'OperatingForm.ui'
**
** Created: Sat Jan 14 22:29:44 2017
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPERATINGFORM_H
#define UI_OPERATINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QMainWindow>
#include <QtGui/QProgressBar>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_OperatingForm
{
public:
    QWidget *centralwidget;
    QProgressBar *progressBar;

    void setupUi(QMainWindow *OperatingForm)
    {
        if (OperatingForm->objectName().isEmpty())
            OperatingForm->setObjectName(QString::fromUtf8("OperatingForm"));
        OperatingForm->resize(321, 44);
        centralwidget = new QWidget(OperatingForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 10, 301, 23));
        progressBar->setValue(24);
        OperatingForm->setCentralWidget(centralwidget);

        retranslateUi(OperatingForm);

        QMetaObject::connectSlotsByName(OperatingForm);
    } // setupUi

    void retranslateUi(QMainWindow *OperatingForm)
    {
        OperatingForm->setWindowTitle(QApplication::translate("OperatingForm", "MainWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OperatingForm: public Ui_OperatingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPERATINGFORM_H
