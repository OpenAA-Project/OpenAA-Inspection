/********************************************************************************
** Form generated from reading UI file 'EditPartDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITPARTDIALOG_H
#define UI_EDITPARTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditPartDialog
{
public:
    QLineEdit *lineEditAreaName;
    QFrame *frame_26;
    QLabel *label_87;
    QSpinBox *EditSearchAngle;
    QLabel *label_20;
    QLabel *label_4;
    QSpinBox *spinBoxSearchArea;
    QTableWidget *tableWidgetLibList;
    QFrame *frameLibFolder;
    QLabel *label_5;
    QLineEdit *EditLibName;
    QLineEdit *EditLibID;
    QPushButton *ButtonCancel;
    QPushButton *ButtonOK;
    QPushButton *ButtonDelete;

    void setupUi(QDialog *EditPartDialog)
    {
        if (EditPartDialog->objectName().isEmpty())
            EditPartDialog->setObjectName("EditPartDialog");
        EditPartDialog->resize(426, 356);
        lineEditAreaName = new QLineEdit(EditPartDialog);
        lineEditAreaName->setObjectName("lineEditAreaName");
        lineEditAreaName->setGeometry(QRect(100, 160, 311, 24));
        frame_26 = new QFrame(EditPartDialog);
        frame_26->setObjectName("frame_26");
        frame_26->setGeometry(QRect(30, 220, 381, 71));
        frame_26->setFrameShape(QFrame::StyledPanel);
        frame_26->setFrameShadow(QFrame::Sunken);
        label_87 = new QLabel(frame_26);
        label_87->setObjectName("label_87");
        label_87->setGeometry(QRect(0, 0, 31, 71));
        label_87->setFrameShape(QFrame::Panel);
        label_87->setFrameShadow(QFrame::Raised);
        label_87->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_87->setIndent(1);
        EditSearchAngle = new QSpinBox(frame_26);
        EditSearchAngle->setObjectName("EditSearchAngle");
        EditSearchAngle->setGeometry(QRect(290, 40, 81, 20));
        EditSearchAngle->setMinimum(-255);
        EditSearchAngle->setMaximum(255);
        label_20 = new QLabel(frame_26);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(40, 40, 241, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        label_20->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(frame_26);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 10, 241, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        spinBoxSearchArea = new QSpinBox(frame_26);
        spinBoxSearchArea->setObjectName("spinBoxSearchArea");
        spinBoxSearchArea->setGeometry(QRect(290, 10, 81, 22));
        spinBoxSearchArea->setMaximum(999999);
        tableWidgetLibList = new QTableWidget(EditPartDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 201, 141));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolder = new QFrame(EditPartDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(EditPartDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 160, 81, 21));
        EditLibName = new QLineEdit(EditPartDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(90, 190, 321, 21));
        EditLibName->setReadOnly(true);
        EditLibID = new QLineEdit(EditPartDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(40, 190, 51, 21));
        EditLibID->setReadOnly(true);
        ButtonCancel = new QPushButton(EditPartDialog);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(300, 310, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon);
        ButtonOK = new QPushButton(EditPartDialog);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(160, 310, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon1);
        ButtonDelete = new QPushButton(EditPartDialog);
        ButtonDelete->setObjectName("ButtonDelete");
        ButtonDelete->setGeometry(QRect(20, 310, 101, 31));
        ButtonDelete->setIcon(icon1);
        ButtonDelete->setAutoDefault(false);

        retranslateUi(EditPartDialog);

        ButtonOK->setDefault(true);
        ButtonDelete->setDefault(false);


        QMetaObject::connectSlotsByName(EditPartDialog);
    } // setupUi

    void retranslateUi(QDialog *EditPartDialog)
    {
        EditPartDialog->setWindowTitle(QCoreApplication::translate("EditPartDialog", "Dialog", nullptr));
        label_87->setText(QCoreApplication::translate("EditPartDialog", "<html><head/><body><p>\345\256\237</p><p>\350\241\214</p></body></html>", nullptr));
        label_20->setText(QCoreApplication::translate("EditPartDialog", "\346\216\242\347\264\242\350\247\222\345\272\246\343\200\200\302\261", nullptr));
        label_4->setText(QCoreApplication::translate("EditPartDialog", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\343\200\200\302\261", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditPartDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditPartDialog", "Name", nullptr));
        label_5->setText(QCoreApplication::translate("EditPartDialog", "\351\203\250\345\223\201\345\220\215", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("EditPartDialog", "Cancel", nullptr));
        ButtonOK->setText(QCoreApplication::translate("EditPartDialog", "OK", nullptr));
        ButtonDelete->setText(QCoreApplication::translate("EditPartDialog", "\345\211\212\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditPartDialog: public Ui_EditPartDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITPARTDIALOG_H
