/********************************************************************************
** Form generated from reading UI file 'CommDialogForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMDIALOGFORM_H
#define UI_COMMDIALOGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CommDialogForm
{
public:
    QLineEdit *lineEditFileName;
    QFrame *frameFormComm;
    QLabel *label;
    QPushButton *pushButtonSaveNew;
    QPushButton *pushButtonFileName;
    QPushButton *pushButtonLoad;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *CommDialogForm)
    {
        if (CommDialogForm->objectName().isEmpty())
            CommDialogForm->setObjectName("CommDialogForm");
        CommDialogForm->resize(506, 629);
        lineEditFileName = new QLineEdit(CommDialogForm);
        lineEditFileName->setObjectName("lineEditFileName");
        lineEditFileName->setGeometry(QRect(10, 30, 421, 21));
        frameFormComm = new QFrame(CommDialogForm);
        frameFormComm->setObjectName("frameFormComm");
        frameFormComm->setGeometry(QRect(10, 100, 484, 484));
        frameFormComm->setFrameShape(QFrame::Panel);
        frameFormComm->setFrameShadow(QFrame::Sunken);
        label = new QLabel(CommDialogForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 481, 16));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSaveNew = new QPushButton(CommDialogForm);
        pushButtonSaveNew->setObjectName("pushButtonSaveNew");
        pushButtonSaveNew->setGeometry(QRect(200, 590, 121, 31));
        pushButtonFileName = new QPushButton(CommDialogForm);
        pushButtonFileName->setObjectName("pushButtonFileName");
        pushButtonFileName->setGeometry(QRect(440, 30, 51, 23));
        pushButtonLoad = new QPushButton(CommDialogForm);
        pushButtonLoad->setObjectName("pushButtonLoad");
        pushButtonLoad->setGeometry(QRect(180, 60, 171, 31));
        pushButtonUpdate = new QPushButton(CommDialogForm);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(10, 590, 121, 31));
        pushButtonClose = new QPushButton(CommDialogForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(370, 590, 121, 31));

        retranslateUi(CommDialogForm);

        pushButtonClose->setDefault(true);


        QMetaObject::connectSlotsByName(CommDialogForm);
    } // setupUi

    void retranslateUi(QDialog *CommDialogForm)
    {
        CommDialogForm->setWindowTitle(QCoreApplication::translate("CommDialogForm", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("CommDialogForm", "Loaded file name", nullptr));
        pushButtonSaveNew->setText(QCoreApplication::translate("CommDialogForm", "Save new", nullptr));
        pushButtonFileName->setText(QCoreApplication::translate("CommDialogForm", "...", nullptr));
        pushButtonLoad->setText(QCoreApplication::translate("CommDialogForm", "Load", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("CommDialogForm", "Update", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("CommDialogForm", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CommDialogForm: public Ui_CommDialogForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMDIALOGFORM_H
