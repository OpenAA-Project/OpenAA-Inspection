/********************************************************************************
** Form generated from reading UI file 'AddRouteDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDROUTEDIALOG_H
#define UI_ADDROUTEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_AddRouteDialog
{
public:
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonCancel;
    QLabel *label_2;
    QLineEdit *lineEditPath;
    QLabel *label_3;
    QSpinBox *spinBoxPriority;
    QLabel *label_4;
    QLineEdit *lineEditNetworkPath;
    QLineEdit *lineEditDFSFilterDLLFileName;
    QLabel *label_5;
    QPushButton *pushButtonSearchDLL;
    QLineEdit *lineEditDFSFilterParameter;
    QLabel *label_6;

    void setupUi(QDialog *AddRouteDialog)
    {
        if (AddRouteDialog->objectName().isEmpty())
            AddRouteDialog->setObjectName("AddRouteDialog");
        AddRouteDialog->resize(434, 291);
        pushButtonAdd = new QPushButton(AddRouteDialog);
        pushButtonAdd->setObjectName("pushButtonAdd");
        pushButtonAdd->setGeometry(QRect(70, 250, 93, 28));
        pushButtonCancel = new QPushButton(AddRouteDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(270, 250, 93, 28));
        label_2 = new QLabel(AddRouteDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 401, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        lineEditPath = new QLineEdit(AddRouteDialog);
        lineEditPath->setObjectName("lineEditPath");
        lineEditPath->setGeometry(QRect(10, 30, 401, 21));
        label_3 = new QLabel(AddRouteDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 60, 121, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        spinBoxPriority = new QSpinBox(AddRouteDialog);
        spinBoxPriority->setObjectName("spinBoxPriority");
        spinBoxPriority->setGeometry(QRect(140, 60, 101, 22));
        label_4 = new QLabel(AddRouteDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 90, 401, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        lineEditNetworkPath = new QLineEdit(AddRouteDialog);
        lineEditNetworkPath->setObjectName("lineEditNetworkPath");
        lineEditNetworkPath->setGeometry(QRect(10, 110, 401, 21));
        lineEditDFSFilterDLLFileName = new QLineEdit(AddRouteDialog);
        lineEditDFSFilterDLLFileName->setObjectName("lineEditDFSFilterDLLFileName");
        lineEditDFSFilterDLLFileName->setGeometry(QRect(10, 160, 371, 21));
        label_5 = new QLabel(AddRouteDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 140, 401, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        pushButtonSearchDLL = new QPushButton(AddRouteDialog);
        pushButtonSearchDLL->setObjectName("pushButtonSearchDLL");
        pushButtonSearchDLL->setGeometry(QRect(380, 160, 31, 21));
        lineEditDFSFilterParameter = new QLineEdit(AddRouteDialog);
        lineEditDFSFilterParameter->setObjectName("lineEditDFSFilterParameter");
        lineEditDFSFilterParameter->setGeometry(QRect(10, 210, 401, 21));
        label_6 = new QLabel(AddRouteDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 190, 401, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);

        retranslateUi(AddRouteDialog);

        QMetaObject::connectSlotsByName(AddRouteDialog);
    } // setupUi

    void retranslateUi(QDialog *AddRouteDialog)
    {
        AddRouteDialog->setWindowTitle(QCoreApplication::translate("AddRouteDialog", "DFS provider", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("AddRouteDialog", "Add", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AddRouteDialog", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("AddRouteDialog", "Local path", nullptr));
        label_3->setText(QCoreApplication::translate("AddRouteDialog", "Priority", nullptr));
        label_4->setText(QCoreApplication::translate("AddRouteDialog", "Network path (ex. \\192.168.0.100DataXXX)", nullptr));
        label_5->setText(QCoreApplication::translate("AddRouteDialog", "DFS Filter DLL (Local path)", nullptr));
        pushButtonSearchDLL->setText(QCoreApplication::translate("AddRouteDialog", "...", nullptr));
        label_6->setText(QCoreApplication::translate("AddRouteDialog", "DFS filter parameter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddRouteDialog: public Ui_AddRouteDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDROUTEDIALOG_H
