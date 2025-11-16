/********************************************************************************
** Form generated from reading UI file 'ShowOperationalPanel.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWOPERATIONALPANEL_H
#define UI_SHOWOPERATIONALPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowOperationalPanel
{
public:
    QPushButton *ButtonLoadFromLibrary;
    QPushButton *ButtonReflectAllBlocks;
    QPushButton *ButtonSaveToLibrary;
    QPushButton *ButtonClose;
    QPushButton *ButtonRelrectOnlyBlock;
    QLineEdit *EditLibName;
    QLineEdit *EditLibID;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_39;
    QSpinBox *EditLimitDot;
    QLabel *label_6;
    QFrame *frame;
    QSpinBox *spinBoxNGPercentage;
    QLabel *label;
    QLabel *label_2;
    QCheckBox *checkBoxEnableWhite;
    QSpinBox *spinBoxRefBrightness;
    QLabel *label_7;
    QTableWidget *tableWidgetSelected;

    void setupUi(QWidget *ShowOperationalPanel)
    {
        if (ShowOperationalPanel->objectName().isEmpty())
            ShowOperationalPanel->setObjectName("ShowOperationalPanel");
        ShowOperationalPanel->resize(645, 415);
        ButtonLoadFromLibrary = new QPushButton(ShowOperationalPanel);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(290, 310, 261, 41));
        ButtonLoadFromLibrary->setAcceptDrops(true);
        ButtonReflectAllBlocks = new QPushButton(ShowOperationalPanel);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(290, 260, 321, 41));
        ButtonReflectAllBlocks->setAcceptDrops(true);
        ButtonSaveToLibrary = new QPushButton(ShowOperationalPanel);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(20, 310, 261, 41));
        ButtonSaveToLibrary->setAcceptDrops(true);
        ButtonClose = new QPushButton(ShowOperationalPanel);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(290, 360, 171, 41));
        ButtonRelrectOnlyBlock = new QPushButton(ShowOperationalPanel);
        ButtonRelrectOnlyBlock->setObjectName("ButtonRelrectOnlyBlock");
        ButtonRelrectOnlyBlock->setGeometry(QRect(10, 260, 271, 41));
        ButtonRelrectOnlyBlock->setAcceptDrops(true);
        EditLibName = new QLineEdit(ShowOperationalPanel);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(70, 30, 391, 21));
        EditLibName->setReadOnly(true);
        EditLibID = new QLineEdit(ShowOperationalPanel);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(10, 30, 61, 21));
        EditLibID->setReadOnly(true);
        label_4 = new QLabel(ShowOperationalPanel);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 10, 62, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(ShowOperationalPanel);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(70, 10, 391, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_39 = new QLabel(ShowOperationalPanel);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(420, 582, 191, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLimitDot = new QSpinBox(ShowOperationalPanel);
        EditLimitDot->setObjectName("EditLimitDot");
        EditLimitDot->setGeometry(QRect(610, 580, 71, 22));
        EditLimitDot->setMaximum(99999);
        label_6 = new QLabel(ShowOperationalPanel);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 60, 451, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame = new QFrame(ShowOperationalPanel);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(470, 90, 161, 161));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        spinBoxNGPercentage = new QSpinBox(frame);
        spinBoxNGPercentage->setObjectName("spinBoxNGPercentage");
        spinBoxNGPercentage->setGeometry(QRect(10, 50, 131, 24));
        spinBoxNGPercentage->setMinimum(1);
        spinBoxNGPercentage->setMaximum(100);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 27, 131, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 80, 131, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        checkBoxEnableWhite = new QCheckBox(frame);
        checkBoxEnableWhite->setObjectName("checkBoxEnableWhite");
        checkBoxEnableWhite->setGeometry(QRect(10, 130, 131, 22));
        spinBoxRefBrightness = new QSpinBox(frame);
        spinBoxRefBrightness->setObjectName("spinBoxRefBrightness");
        spinBoxRefBrightness->setGeometry(QRect(10, 100, 131, 24));
        spinBoxRefBrightness->setMaximum(255);
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 0, 161, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        tableWidgetSelected = new QTableWidget(ShowOperationalPanel);
        if (tableWidgetSelected->columnCount() < 4)
            tableWidgetSelected->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetSelected->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetSelected->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetSelected->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetSelected->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetSelected->setObjectName("tableWidgetSelected");
        tableWidgetSelected->setGeometry(QRect(10, 80, 451, 171));
        tableWidgetSelected->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetSelected->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(ShowOperationalPanel);

        QMetaObject::connectSlotsByName(ShowOperationalPanel);
    } // setupUi

    void retranslateUi(QWidget *ShowOperationalPanel)
    {
        ShowOperationalPanel->setWindowTitle(QCoreApplication::translate("ShowOperationalPanel", "Threshold BuslineInspection", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("ShowOperationalPanel", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("ShowOperationalPanel", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("ShowOperationalPanel", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        ButtonClose->setText(QCoreApplication::translate("ShowOperationalPanel", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonRelrectOnlyBlock->setText(QCoreApplication::translate("ShowOperationalPanel", "\343\201\223\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        EditLibName->setText(QCoreApplication::translate("ShowOperationalPanel", "XXX", nullptr));
        EditLibID->setText(QCoreApplication::translate("ShowOperationalPanel", "12345", nullptr));
        label_4->setText(QCoreApplication::translate("ShowOperationalPanel", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        label_5->setText(QCoreApplication::translate("ShowOperationalPanel", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        label_39->setText(QCoreApplication::translate("ShowOperationalPanel", "\351\231\220\347\225\214\343\202\265\343\202\244\343\202\272", nullptr));
        label_6->setText(QCoreApplication::translate("ShowOperationalPanel", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        label->setText(QCoreApplication::translate("ShowOperationalPanel", "NG Percentage", nullptr));
        label_2->setText(QCoreApplication::translate("ShowOperationalPanel", "Refer Brightness", nullptr));
        checkBoxEnableWhite->setText(QCoreApplication::translate("ShowOperationalPanel", "Enable white", nullptr));
        label_7->setText(QCoreApplication::translate("ShowOperationalPanel", "Jdge", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetSelected->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowOperationalPanel", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetSelected->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowOperationalPanel", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetSelected->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowOperationalPanel", "Library Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetSelected->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowOperationalPanel", "Result", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowOperationalPanel: public Ui_ShowOperationalPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWOPERATIONALPANEL_H
