/********************************************************************************
** Form generated from reading UI file 'ShowStrategicAllForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWSTRATEGICALLFORM_H
#define UI_SHOWSTRATEGICALLFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowStrategicAllForm
{
public:
    QLabel *label;
    QLineEdit *lineEditCurrentStrategicNumber;
    QPushButton *pushButtonShow;
    QLabel *label_2;
    QLineEdit *lineEditCurrentStrategicNumberForSeq;
    QLabel *label_3;
    QLineEdit *lineEditCurrentStrategicNumberForCalc;

    void setupUi(GUIFormBase *ShowStrategicAllForm)
    {
        if (ShowStrategicAllForm->objectName().isEmpty())
            ShowStrategicAllForm->setObjectName("ShowStrategicAllForm");
        ShowStrategicAllForm->resize(330, 76);
        label = new QLabel(ShowStrategicAllForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 171, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        lineEditCurrentStrategicNumber = new QLineEdit(ShowStrategicAllForm);
        lineEditCurrentStrategicNumber->setObjectName("lineEditCurrentStrategicNumber");
        lineEditCurrentStrategicNumber->setGeometry(QRect(180, 10, 71, 20));
        lineEditCurrentStrategicNumber->setReadOnly(true);
        pushButtonShow = new QPushButton(ShowStrategicAllForm);
        pushButtonShow->setObjectName("pushButtonShow");
        pushButtonShow->setGeometry(QRect(260, 20, 61, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Preview.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonShow->setIcon(icon);
        label_2 = new QLabel(ShowStrategicAllForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 30, 171, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        lineEditCurrentStrategicNumberForSeq = new QLineEdit(ShowStrategicAllForm);
        lineEditCurrentStrategicNumberForSeq->setObjectName("lineEditCurrentStrategicNumberForSeq");
        lineEditCurrentStrategicNumberForSeq->setGeometry(QRect(180, 30, 71, 20));
        lineEditCurrentStrategicNumberForSeq->setReadOnly(true);
        label_3 = new QLabel(ShowStrategicAllForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 50, 171, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        lineEditCurrentStrategicNumberForCalc = new QLineEdit(ShowStrategicAllForm);
        lineEditCurrentStrategicNumberForCalc->setObjectName("lineEditCurrentStrategicNumberForCalc");
        lineEditCurrentStrategicNumberForCalc->setGeometry(QRect(180, 50, 71, 20));
        lineEditCurrentStrategicNumberForCalc->setReadOnly(true);

        retranslateUi(ShowStrategicAllForm);

        QMetaObject::connectSlotsByName(ShowStrategicAllForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowStrategicAllForm)
    {
        ShowStrategicAllForm->setWindowTitle(QCoreApplication::translate("ShowStrategicAllForm", "Show Strategic all", nullptr));
        label->setText(QCoreApplication::translate("ShowStrategicAllForm", "CurrentStrategicNumber", nullptr));
        pushButtonShow->setText(QCoreApplication::translate("ShowStrategicAllForm", "Show", nullptr));
        label_2->setText(QCoreApplication::translate("ShowStrategicAllForm", "CurrentStrategicNumberForSeq", nullptr));
        label_3->setText(QCoreApplication::translate("ShowStrategicAllForm", "CurrentStrategicNumberForCalc", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowStrategicAllForm: public Ui_ShowStrategicAllForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWSTRATEGICALLFORM_H
