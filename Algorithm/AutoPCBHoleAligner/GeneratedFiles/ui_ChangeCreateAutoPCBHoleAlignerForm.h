/********************************************************************************
** Form generated from reading UI file 'ChangeCreateAutoPCBHoleAlignerForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGECREATEAUTOPCBHOLEALIGNERFORM_H
#define UI_CHANGECREATEAUTOPCBHOLEALIGNERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangeCreateAutoPCBHoleAlignerFormClass
{
public:
    QFrame *frame;
    QLabel *label;
    QFrame *frameLibFolder;
    QTableWidget *tableWidgetLibList;
    QFrame *frame_5;
    QLabel *label_4;
    QLineEdit *EditLibID;
    QLineEdit *EditLibName;
    QLabel *label_3;
    QPushButton *ButtonOK;
    QPushButton *ButtonCancel;
    QFrame *frame_2;
    QCheckBox *checkBoxCheckOutside;
    QCheckBox *checkBoxStartupExecute;
    QSpinBox *EditThresholdDiff;
    QLabel *label_24;
    QLabel *label_23;
    QLabel *label_27;
    QSpinBox *EditMaxSearch;
    QLabel *label_25;
    QSpinBox *EditFringeDot;
    QLabel *label_22;
    QLabel *label_28;
    QSpinBox *EditMaxDiameter;
    QSpinBox *EditExpandForPickup;
    QSpinBox *EditMinDiameter;

    void setupUi(QDialog *ChangeCreateAutoPCBHoleAlignerFormClass)
    {
        if (ChangeCreateAutoPCBHoleAlignerFormClass->objectName().isEmpty())
            ChangeCreateAutoPCBHoleAlignerFormClass->setObjectName("ChangeCreateAutoPCBHoleAlignerFormClass");
        ChangeCreateAutoPCBHoleAlignerFormClass->resize(496, 446);
        frame = new QFrame(ChangeCreateAutoPCBHoleAlignerFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 491, 441));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 491, 21));
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameLibFolder = new QFrame(frame);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 20, 221, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        tableWidgetLibList = new QTableWidget(frame);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(240, 20, 241, 141));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame_5 = new QFrame(frame);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 170, 471, 261));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame_5);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 20, 61, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(frame_5);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(70, 20, 81, 21));
        EditLibID->setReadOnly(true);
        EditLibName = new QLineEdit(frame_5);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(150, 20, 311, 21));
        label_3 = new QLabel(frame_5);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 471, 21));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonOK = new QPushButton(frame_5);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(10, 220, 75, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        ButtonCancel = new QPushButton(frame_5);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(380, 220, 81, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        frame_2 = new QFrame(frame_5);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 50, 451, 161));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        checkBoxCheckOutside = new QCheckBox(frame_2);
        checkBoxCheckOutside->setObjectName("checkBoxCheckOutside");
        checkBoxCheckOutside->setGeometry(QRect(240, 70, 211, 20));
        checkBoxStartupExecute = new QCheckBox(frame_2);
        checkBoxStartupExecute->setObjectName("checkBoxStartupExecute");
        checkBoxStartupExecute->setGeometry(QRect(30, 40, 131, 18));
        EditThresholdDiff = new QSpinBox(frame_2);
        EditThresholdDiff->setObjectName("EditThresholdDiff");
        EditThresholdDiff->setGeometry(QRect(380, 40, 61, 22));
        EditThresholdDiff->setMaximum(255);
        label_24 = new QLabel(frame_2);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(10, 100, 151, 21));
        label_24->setFrameShape(QFrame::Panel);
        label_24->setFrameShadow(QFrame::Sunken);
        label_24->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_23 = new QLabel(frame_2);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(10, 70, 151, 21));
        label_23->setFrameShape(QFrame::Panel);
        label_23->setFrameShadow(QFrame::Sunken);
        label_23->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_27 = new QLabel(frame_2);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(230, 10, 151, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxSearch = new QSpinBox(frame_2);
        EditMaxSearch->setObjectName("EditMaxSearch");
        EditMaxSearch->setGeometry(QRect(380, 10, 61, 22));
        EditMaxSearch->setMaximum(255);
        label_25 = new QLabel(frame_2);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(10, 130, 151, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditFringeDot = new QSpinBox(frame_2);
        EditFringeDot->setObjectName("EditFringeDot");
        EditFringeDot->setGeometry(QRect(160, 130, 61, 22));
        EditFringeDot->setMaximum(255);
        label_22 = new QLabel(frame_2);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(10, 10, 151, 21));
        label_22->setFrameShape(QFrame::Panel);
        label_22->setFrameShadow(QFrame::Sunken);
        label_22->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_28 = new QLabel(frame_2);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(230, 40, 151, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxDiameter = new QSpinBox(frame_2);
        EditMaxDiameter->setObjectName("EditMaxDiameter");
        EditMaxDiameter->setGeometry(QRect(160, 100, 61, 22));
        EditMaxDiameter->setMaximum(255);
        EditExpandForPickup = new QSpinBox(frame_2);
        EditExpandForPickup->setObjectName("EditExpandForPickup");
        EditExpandForPickup->setGeometry(QRect(160, 10, 61, 22));
        EditExpandForPickup->setMaximum(255);
        EditMinDiameter = new QSpinBox(frame_2);
        EditMinDiameter->setObjectName("EditMinDiameter");
        EditMinDiameter->setGeometry(QRect(160, 70, 61, 22));
        EditMinDiameter->setMaximum(255);

        retranslateUi(ChangeCreateAutoPCBHoleAlignerFormClass);

        QMetaObject::connectSlotsByName(ChangeCreateAutoPCBHoleAlignerFormClass);
    } // setupUi

    void retranslateUi(QDialog *ChangeCreateAutoPCBHoleAlignerFormClass)
    {
        ChangeCreateAutoPCBHoleAlignerFormClass->setWindowTitle(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "ChangeCreateAutoPCBHoleAlignerForm", nullptr));
        label->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "Name", nullptr));
        label_4->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "12345", nullptr));
        EditLibName->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "Library Name", nullptr));
        label_3->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\227\343\203\255\343\203\221\343\203\206\343\202\243", nullptr));
        ButtonOK->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "OK", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "Cancel", nullptr));
        checkBoxCheckOutside->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "\346\230\216\343\202\213\343\201\204\351\240\230\345\237\237\343\201\253\345\233\262\343\201\276\343\202\214\343\201\246\343\201\204\343\202\213\343\201\213\343\201\256\345\210\244\345\256\232", nullptr));
        checkBoxStartupExecute->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "\343\203\207\343\203\225\343\202\251\343\203\253\343\203\210\343\201\247\345\256\237\350\241\214", nullptr));
        label_24->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "\346\234\200\345\244\247\347\233\264\345\276\204\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_23->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "\346\234\200\345\260\217\347\233\264\345\276\204\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_27->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "\345\221\250\345\233\262\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_25->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "\345\221\250\347\270\201\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_22->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "\347\251\264\351\240\230\345\237\237\350\206\250\345\274\265\351\207\217", nullptr));
        label_28->setText(QCoreApplication::translate("ChangeCreateAutoPCBHoleAlignerFormClass", "\350\274\235\345\272\246\345\244\211\345\214\226\351\226\276\345\200\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeCreateAutoPCBHoleAlignerFormClass: public Ui_ChangeCreateAutoPCBHoleAlignerFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGECREATEAUTOPCBHOLEALIGNERFORM_H
