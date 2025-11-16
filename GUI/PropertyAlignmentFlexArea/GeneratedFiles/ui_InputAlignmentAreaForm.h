/********************************************************************************
** Form generated from reading UI file 'InputAlignmentAreaForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTALIGNMENTAREAFORM_H
#define UI_INPUTALIGNMENTAREAFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_InputAlignmentAreaFormClass
{
public:
    QLabel *label;
    QLineEdit *EditAreaName;
    QLabel *label_4;
    QFrame *frameLibrary;
    QPushButton *ButtonOK;
    QPushButton *ButtonCancel;
    QPushButton *ButtonDelete;
    QGroupBox *groupBox;
    QRadioButton *radioButtonPriorityHigh;
    QRadioButton *radioButtonPriorityMiddle;
    QRadioButton *radioButtonPriorityLow;
    QRadioButton *radioButtonPriorityLGlobal;
    QLabel *label_5;
    QFrame *frame;
    QTableWidget *tableWidgetLibListGen;
    QPushButton *pushButtonToGenList;
    QTableWidget *tableWidgetLibList;
    QFrame *frameLibFolder;
    QPushButton *pushButtonFromGenList;
    QLabel *label_6;

    void setupUi(QDialog *InputAlignmentAreaFormClass)
    {
        if (InputAlignmentAreaFormClass->objectName().isEmpty())
            InputAlignmentAreaFormClass->setObjectName("InputAlignmentAreaFormClass");
        InputAlignmentAreaFormClass->resize(946, 611);
        label = new QLabel(InputAlignmentAreaFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 261, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditAreaName = new QLineEdit(InputAlignmentAreaFormClass);
        EditAreaName->setObjectName("EditAreaName");
        EditAreaName->setGeometry(QRect(20, 30, 261, 21));
        label_4 = new QLabel(InputAlignmentAreaFormClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 60, 451, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameLibrary = new QFrame(InputAlignmentAreaFormClass);
        frameLibrary->setObjectName("frameLibrary");
        frameLibrary->setGeometry(QRect(20, 80, 451, 361));
        frameLibrary->setFrameShape(QFrame::StyledPanel);
        frameLibrary->setFrameShadow(QFrame::Sunken);
        ButtonOK = new QPushButton(InputAlignmentAreaFormClass);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(300, 570, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        ButtonCancel = new QPushButton(InputAlignmentAreaFormClass);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(560, 570, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        ButtonDelete = new QPushButton(InputAlignmentAreaFormClass);
        ButtonDelete->setObjectName("ButtonDelete");
        ButtonDelete->setEnabled(false);
        ButtonDelete->setGeometry(QRect(430, 570, 101, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonDelete->setIcon(icon2);
        groupBox = new QGroupBox(InputAlignmentAreaFormClass);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(240, 450, 681, 111));
        radioButtonPriorityHigh = new QRadioButton(groupBox);
        radioButtonPriorityHigh->setObjectName("radioButtonPriorityHigh");
        radioButtonPriorityHigh->setGeometry(QRect(20, 40, 631, 17));
        radioButtonPriorityHigh->setChecked(false);
        radioButtonPriorityMiddle = new QRadioButton(groupBox);
        radioButtonPriorityMiddle->setObjectName("radioButtonPriorityMiddle");
        radioButtonPriorityMiddle->setGeometry(QRect(20, 60, 641, 17));
        radioButtonPriorityMiddle->setChecked(true);
        radioButtonPriorityLow = new QRadioButton(groupBox);
        radioButtonPriorityLow->setObjectName("radioButtonPriorityLow");
        radioButtonPriorityLow->setGeometry(QRect(20, 80, 651, 17));
        radioButtonPriorityLow->setChecked(false);
        radioButtonPriorityLGlobal = new QRadioButton(groupBox);
        radioButtonPriorityLGlobal->setObjectName("radioButtonPriorityLGlobal");
        radioButtonPriorityLGlobal->setGeometry(QRect(20, 20, 621, 17));
        radioButtonPriorityLGlobal->setChecked(false);
        label_5 = new QLabel(InputAlignmentAreaFormClass);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(480, 60, 451, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame = new QFrame(InputAlignmentAreaFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(480, 80, 451, 371));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        tableWidgetLibListGen = new QTableWidget(frame);
        if (tableWidgetLibListGen->columnCount() < 2)
            tableWidgetLibListGen->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibListGen->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibListGen->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibListGen->setObjectName("tableWidgetLibListGen");
        tableWidgetLibListGen->setGeometry(QRect(250, 160, 191, 201));
        tableWidgetLibListGen->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibListGen->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonToGenList = new QPushButton(frame);
        pushButtonToGenList->setObjectName("pushButtonToGenList");
        pushButtonToGenList->setGeometry(QRect(210, 220, 31, 34));
        tableWidgetLibList = new QTableWidget(frame);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 160, 191, 201));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolder = new QFrame(frame);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 151));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        pushButtonFromGenList = new QPushButton(frame);
        pushButtonFromGenList->setObjectName("pushButtonFromGenList");
        pushButtonFromGenList->setGeometry(QRect(210, 270, 31, 34));
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(250, 140, 191, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(InputAlignmentAreaFormClass);

        ButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(InputAlignmentAreaFormClass);
    } // setupUi

    void retranslateUi(QDialog *InputAlignmentAreaFormClass)
    {
        InputAlignmentAreaFormClass->setWindowTitle(QCoreApplication::translate("InputAlignmentAreaFormClass", "Input Alignment Area", nullptr));
        label->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "\343\202\250\343\203\252\343\202\242\345\220\215\347\247\260", nullptr));
        label_4->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\224\343\201\250\343\201\256\343\202\242\343\203\251\343\202\244\343\203\263\343\203\241\343\203\263\343\203\210", nullptr));
        ButtonOK->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "OK", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "Cancel", nullptr));
        ButtonDelete->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "Delete", nullptr));
        groupBox->setTitle(QCoreApplication::translate("InputAlignmentAreaFormClass", "Priority", nullptr));
        radioButtonPriorityHigh->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "High( Exp. BGA, special part)", nullptr));
        radioButtonPriorityMiddle->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "Middle (General)", nullptr));
        radioButtonPriorityLow->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "Low (Only parts fitting)", nullptr));
        radioButtonPriorityLGlobal->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "Global alignment (Only for other alignment)", nullptr));
        label_5->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "\343\202\242\343\202\244\343\203\206\343\203\240\347\224\237\346\210\220\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibListGen->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibListGen->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "Name", nullptr));
        pushButtonToGenList->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "->", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "Name", nullptr));
        pushButtonFromGenList->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "<-", nullptr));
        label_6->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "\347\224\237\346\210\220\343\201\231\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputAlignmentAreaFormClass: public Ui_InputAlignmentAreaFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTALIGNMENTAREAFORM_H
