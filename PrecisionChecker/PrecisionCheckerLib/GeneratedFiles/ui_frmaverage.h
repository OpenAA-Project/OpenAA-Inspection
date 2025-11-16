/********************************************************************************
** Form generated from reading UI file 'frmaverage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMAVERAGE_H
#define UI_FRMAVERAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmAverageClass
{
public:
    QPushButton *btnExit;
    QFrame *frame;

    void setupUi(QWidget *frmAverageClass)
    {
        if (frmAverageClass->objectName().isEmpty())
            frmAverageClass->setObjectName("frmAverageClass");
        frmAverageClass->resize(603, 586);
        btnExit = new QPushButton(frmAverageClass);
        btnExit->setObjectName("btnExit");
        btnExit->setGeometry(QRect(510, 540, 75, 23));
        frame = new QFrame(frmAverageClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 581, 521));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        retranslateUi(frmAverageClass);

        QMetaObject::connectSlotsByName(frmAverageClass);
    } // setupUi

    void retranslateUi(QWidget *frmAverageClass)
    {
        frmAverageClass->setWindowTitle(QCoreApplication::translate("frmAverageClass", "frmAverage", nullptr));
        btnExit->setText(QCoreApplication::translate("frmAverageClass", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frmAverageClass: public Ui_frmAverageClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMAVERAGE_H
