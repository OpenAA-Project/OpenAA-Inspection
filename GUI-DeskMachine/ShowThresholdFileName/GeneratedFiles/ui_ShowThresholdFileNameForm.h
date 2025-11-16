/********************************************************************************
** Form generated from reading UI file 'ShowThresholdFileNameForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWTHRESHOLDFILENAMEFORM_H
#define UI_SHOWTHRESHOLDFILENAMEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout;
    QLabel *labelHeadThresholdFileName;
    QLabel *labelThresholdFileName;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(289, 41);
        gridLayout = new QGridLayout(Form);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelHeadThresholdFileName = new QLabel(Form);
        labelHeadThresholdFileName->setObjectName(QString::fromUtf8("labelHeadThresholdFileName"));
        labelHeadThresholdFileName->setFrameShape(QFrame::Panel);
        labelHeadThresholdFileName->setFrameShadow(QFrame::Sunken);
        labelHeadThresholdFileName->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelHeadThresholdFileName, 0, 0, 1, 1);

        labelThresholdFileName = new QLabel(Form);
        labelThresholdFileName->setObjectName(QString::fromUtf8("labelThresholdFileName"));
        labelThresholdFileName->setFrameShape(QFrame::Panel);
        labelThresholdFileName->setFrameShadow(QFrame::Sunken);
        labelThresholdFileName->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(labelThresholdFileName, 0, 1, 1, 1);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        labelHeadThresholdFileName->setText(QCoreApplication::translate("Form", "Threshold File Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWTHRESHOLDFILENAMEFORM_H
