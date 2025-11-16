/********************************************************************************
** Form generated from reading UI file 'EditScanPhaseNumber.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITSCANPHASENUMBER_H
#define UI_EDITSCANPHASENUMBER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditScanPhaseNumber
{
public:
    QFrame *frameGrid;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label;
    QSpinBox *spinBoxScanNumberInPhaseDimNumb;

    void setupUi(QWidget *EditScanPhaseNumber)
    {
        if (EditScanPhaseNumber->objectName().isEmpty())
            EditScanPhaseNumber->setObjectName("EditScanPhaseNumber");
        EditScanPhaseNumber->resize(210, 326);
        frameGrid = new QFrame(EditScanPhaseNumber);
        frameGrid->setObjectName("frameGrid");
        frameGrid->setGeometry(QRect(10, 10, 191, 211));
        frameGrid->setFrameShape(QFrame::StyledPanel);
        frameGrid->setFrameShadow(QFrame::Sunken);
        pushButtonOK = new QPushButton(EditScanPhaseNumber);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 290, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(EditScanPhaseNumber);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 290, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        label = new QLabel(EditScanPhaseNumber);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 230, 191, 18));
        spinBoxScanNumberInPhaseDimNumb = new QSpinBox(EditScanPhaseNumber);
        spinBoxScanNumberInPhaseDimNumb->setObjectName("spinBoxScanNumberInPhaseDimNumb");
        spinBoxScanNumberInPhaseDimNumb->setGeometry(QRect(90, 250, 81, 24));

        retranslateUi(EditScanPhaseNumber);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(EditScanPhaseNumber);
    } // setupUi

    void retranslateUi(QWidget *EditScanPhaseNumber)
    {
        EditScanPhaseNumber->setWindowTitle(QCoreApplication::translate("EditScanPhaseNumber", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditScanPhaseNumber", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditScanPhaseNumber", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("EditScanPhaseNumber", "ScanNumberInPhase", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditScanPhaseNumber: public Ui_EditScanPhaseNumber {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITSCANPHASENUMBER_H
