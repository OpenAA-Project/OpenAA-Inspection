/********************************************************************************
** Form generated from reading UI file 'FilterInPhaseForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERINPHASEFORM_H
#define UI_FILTERINPHASEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FilterInPhaseForm
{
public:
    QListWidget *listWidgetFilterInstance;
    QLabel *label;
    QListWidget *listWidgetFilterbank;
    QLabel *label_2;
    QPushButton *pushButtonReturn;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonGet;

    void setupUi(QDialog *FilterInPhaseForm)
    {
        if (FilterInPhaseForm->objectName().isEmpty())
            FilterInPhaseForm->setObjectName("FilterInPhaseForm");
        FilterInPhaseForm->resize(479, 282);
        listWidgetFilterInstance = new QListWidget(FilterInPhaseForm);
        listWidgetFilterInstance->setObjectName("listWidgetFilterInstance");
        listWidgetFilterInstance->setGeometry(QRect(270, 30, 201, 191));
        label = new QLabel(FilterInPhaseForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 201, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetFilterbank = new QListWidget(FilterInPhaseForm);
        listWidgetFilterbank->setObjectName("listWidgetFilterbank");
        listWidgetFilterbank->setGeometry(QRect(10, 30, 201, 191));
        label_2 = new QLabel(FilterInPhaseForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(270, 10, 201, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonReturn = new QPushButton(FilterInPhaseForm);
        pushButtonReturn->setObjectName("pushButtonReturn");
        pushButtonReturn->setGeometry(QRect(220, 130, 41, 31));
        pushButtonOK = new QPushButton(FilterInPhaseForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(190, 240, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonGet = new QPushButton(FilterInPhaseForm);
        pushButtonGet->setObjectName("pushButtonGet");
        pushButtonGet->setGeometry(QRect(220, 70, 41, 31));

        retranslateUi(FilterInPhaseForm);

        QMetaObject::connectSlotsByName(FilterInPhaseForm);
    } // setupUi

    void retranslateUi(QDialog *FilterInPhaseForm)
    {
        FilterInPhaseForm->setWindowTitle(QCoreApplication::translate("FilterInPhaseForm", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("FilterInPhaseForm", "Filter bank", nullptr));
        label_2->setText(QCoreApplication::translate("FilterInPhaseForm", "Filter Instance", nullptr));
        pushButtonReturn->setText(QCoreApplication::translate("FilterInPhaseForm", "<=", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("FilterInPhaseForm", "OK", nullptr));
        pushButtonGet->setText(QCoreApplication::translate("FilterInPhaseForm", "=>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilterInPhaseForm: public Ui_FilterInPhaseForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERINPHASEFORM_H
