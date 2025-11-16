/********************************************************************************
** Form generated from reading UI file 'ProcessingForm.ui'
**
** Created: Mon Aug 20 16:22:46 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESSINGFORM_H
#define UI_PROCESSINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProcessingFormClass
{
public:
    QLabel *label;
    QProgressBar *pgbProcessing;

    void setupUi(QWidget *ProcessingFormClass)
    {
        if (ProcessingFormClass->objectName().isEmpty())
            ProcessingFormClass->setObjectName(QString::fromUtf8("ProcessingFormClass"));
        ProcessingFormClass->resize(439, 123);
        label = new QLabel(ProcessingFormClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 10, 291, 41));
        label->setMaximumSize(QSize(291, 41));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        pgbProcessing = new QProgressBar(ProcessingFormClass);
        pgbProcessing->setObjectName(QString::fromUtf8("pgbProcessing"));
        pgbProcessing->setWindowModality(Qt::NonModal);
        pgbProcessing->setGeometry(QRect(30, 70, 391, 31));
        pgbProcessing->setMinimumSize(QSize(391, 31));
        pgbProcessing->setValue(0);

        retranslateUi(ProcessingFormClass);

        QMetaObject::connectSlotsByName(ProcessingFormClass);
    } // setupUi

    void retranslateUi(QWidget *ProcessingFormClass)
    {
        ProcessingFormClass->setWindowTitle(QApplication::translate("ProcessingFormClass", "ProcessingForm", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ProcessingFormClass", "On Processing ...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProcessingFormClass: public Ui_ProcessingFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESSINGFORM_H
