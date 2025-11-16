/********************************************************************************
** Form generated from reading UI file 'EditLibraryMono.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLIBRARYMONO_H
#define UI_EDITLIBRARYMONO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditLibraryMonoClass
{
public:
    QLabel *label_4;
    QLabel *label_23;
    QLabel *label_24;
    QSpinBox *EditFringeWidth;
    QLabel *label_29;
    QPushButton *ButtonLibDelete;
    QFrame *frameLibFolder;
    QPushButton *ButtonLibSaveNew;
    QLabel *label_28;
    QLabel *label_30;
    QSpinBox *EditPicoShift;
    QSpinBox *EditNoiseShrink;
    QSpinBox *EditExpandForPickup;
    QDoubleSpinBox *doubleSpinBoxAdptedMatchingRate;
    QLabel *label_27;
    QTableWidget *tableWidgetLibList;
    QDoubleSpinBox *doubleSpinBoxCompletelyMatchingRate;
    QLabel *label_25;
    QLineEdit *EditLibName;
    QSpinBox *EditPriority;
    QSpinBox *EditMinDot;
    QPushButton *pushButton;
    QPushButton *ButtonLibNew;
    QLabel *label_22;
    QPushButton *ButtonLibSave;
    QCheckBox *checkBoxStartupExecute;
    QLabel *label_26;
    QLineEdit *EditLibID;
    QSpinBox *EditPickupExpansion;
    QSpinBox *EditPickupH;
    QLabel *label_31;
    QLabel *label_32;
    QSpinBox *EditPickupL;

    void setupUi(QDialog *EditLibraryMonoClass)
    {
        if (EditLibraryMonoClass->objectName().isEmpty())
            EditLibraryMonoClass->setObjectName("EditLibraryMonoClass");
        EditLibraryMonoClass->resize(436, 667);
        label_4 = new QLabel(EditLibraryMonoClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 230, 51, 31));
        QFont font;
        font.setPointSize(12);
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_23 = new QLabel(EditLibraryMonoClass);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(10, 400, 161, 21));
        label_23->setFrameShape(QFrame::Panel);
        label_23->setFrameShadow(QFrame::Sunken);
        label_23->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_24 = new QLabel(EditLibraryMonoClass);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(10, 430, 161, 21));
        label_24->setFrameShape(QFrame::Panel);
        label_24->setFrameShadow(QFrame::Sunken);
        label_24->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditFringeWidth = new QSpinBox(EditLibraryMonoClass);
        EditFringeWidth->setObjectName("EditFringeWidth");
        EditFringeWidth->setGeometry(QRect(370, 380, 61, 22));
        EditFringeWidth->setMaximum(255);
        label_29 = new QLabel(EditLibraryMonoClass);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(10, 520, 161, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibDelete = new QPushButton(EditLibraryMonoClass);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(10, 620, 141, 31));
        QFont font1;
        font1.setPointSize(11);
        ButtonLibDelete->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon);
        frameLibFolder = new QFrame(EditLibraryMonoClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 201, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonLibSaveNew = new QPushButton(EditLibraryMonoClass);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(160, 580, 141, 31));
        ButtonLibSaveNew->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon1);
        label_28 = new QLabel(EditLibraryMonoClass);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(250, 380, 121, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_30 = new QLabel(EditLibraryMonoClass);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 550, 161, 21));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPicoShift = new QSpinBox(EditLibraryMonoClass);
        EditPicoShift->setObjectName("EditPicoShift");
        EditPicoShift->setGeometry(QRect(170, 340, 61, 22));
        EditPicoShift->setMaximum(255);
        EditNoiseShrink = new QSpinBox(EditLibraryMonoClass);
        EditNoiseShrink->setObjectName("EditNoiseShrink");
        EditNoiseShrink->setGeometry(QRect(170, 460, 61, 22));
        EditNoiseShrink->setMaximum(255);
        EditExpandForPickup = new QSpinBox(EditLibraryMonoClass);
        EditExpandForPickup->setObjectName("EditExpandForPickup");
        EditExpandForPickup->setGeometry(QRect(170, 490, 61, 22));
        EditExpandForPickup->setMaximum(255);
        doubleSpinBoxAdptedMatchingRate = new QDoubleSpinBox(EditLibraryMonoClass);
        doubleSpinBoxAdptedMatchingRate->setObjectName("doubleSpinBoxAdptedMatchingRate");
        doubleSpinBoxAdptedMatchingRate->setGeometry(QRect(170, 520, 62, 22));
        doubleSpinBoxAdptedMatchingRate->setDecimals(4);
        label_27 = new QLabel(EditLibraryMonoClass);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(250, 340, 111, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetLibList = new QTableWidget(EditLibraryMonoClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(220, 10, 211, 201));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        doubleSpinBoxCompletelyMatchingRate = new QDoubleSpinBox(EditLibraryMonoClass);
        doubleSpinBoxCompletelyMatchingRate->setObjectName("doubleSpinBoxCompletelyMatchingRate");
        doubleSpinBoxCompletelyMatchingRate->setGeometry(QRect(170, 550, 62, 22));
        doubleSpinBoxCompletelyMatchingRate->setDecimals(4);
        label_25 = new QLabel(EditLibraryMonoClass);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(10, 460, 161, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibName = new QLineEdit(EditLibraryMonoClass);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 230, 281, 31));
        EditLibName->setFont(font);
        EditPriority = new QSpinBox(EditLibraryMonoClass);
        EditPriority->setObjectName("EditPriority");
        EditPriority->setGeometry(QRect(170, 400, 61, 22));
        EditPriority->setMaximum(255);
        EditMinDot = new QSpinBox(EditLibraryMonoClass);
        EditMinDot->setObjectName("EditMinDot");
        EditMinDot->setGeometry(QRect(360, 340, 71, 22));
        EditMinDot->setMaximum(255);
        pushButton = new QPushButton(EditLibraryMonoClass);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(310, 620, 111, 31));
        pushButton->setFont(font1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon2);
        ButtonLibNew = new QPushButton(EditLibraryMonoClass);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(10, 580, 141, 31));
        ButtonLibNew->setFont(font1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon3);
        label_22 = new QLabel(EditLibraryMonoClass);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(10, 340, 161, 21));
        label_22->setFrameShape(QFrame::Panel);
        label_22->setFrameShadow(QFrame::Sunken);
        label_22->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibSave = new QPushButton(EditLibraryMonoClass);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(310, 580, 111, 31));
        ButtonLibSave->setFont(font1);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon4);
        checkBoxStartupExecute = new QCheckBox(EditLibraryMonoClass);
        checkBoxStartupExecute->setObjectName("checkBoxStartupExecute");
        checkBoxStartupExecute->setGeometry(QRect(20, 370, 211, 20));
        label_26 = new QLabel(EditLibraryMonoClass);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(10, 490, 161, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(EditLibraryMonoClass);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 230, 81, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        EditPickupExpansion = new QSpinBox(EditLibraryMonoClass);
        EditPickupExpansion->setObjectName("EditPickupExpansion");
        EditPickupExpansion->setGeometry(QRect(170, 430, 61, 22));
        EditPickupExpansion->setMaximum(255);
        EditPickupH = new QSpinBox(EditLibraryMonoClass);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(170, 280, 61, 22));
        EditPickupH->setMaximum(255);
        label_31 = new QLabel(EditLibraryMonoClass);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(10, 280, 161, 21));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_32 = new QLabel(EditLibraryMonoClass);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(10, 310, 161, 21));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupL = new QSpinBox(EditLibraryMonoClass);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(170, 310, 61, 22));
        EditPickupL->setMaximum(255);

        retranslateUi(EditLibraryMonoClass);

        QMetaObject::connectSlotsByName(EditLibraryMonoClass);
    } // setupUi

    void retranslateUi(QDialog *EditLibraryMonoClass)
    {
        EditLibraryMonoClass->setWindowTitle(QCoreApplication::translate("EditLibraryMonoClass", "EditLibraryMono", nullptr));
        label_4->setText(QCoreApplication::translate("EditLibraryMonoClass", "\345\220\215\347\247\260", nullptr));
        label_23->setText(QCoreApplication::translate("EditLibraryMonoClass", "\345\204\252\345\205\210\345\272\246\347\225\252\345\217\267", nullptr));
        label_24->setText(QCoreApplication::translate("EditLibraryMonoClass", "\351\201\267\347\247\273\345\271\205", nullptr));
        label_29->setText(QCoreApplication::translate("EditLibraryMonoClass", "\346\216\241\347\224\250\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditLibraryMonoClass", "Delete", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditLibraryMonoClass", "Save New", nullptr));
        label_28->setText(QCoreApplication::translate("EditLibraryMonoClass", "\345\221\250\347\270\201\343\203\211\343\203\203\343\203\210\345\271\205", nullptr));
        label_30->setText(QCoreApplication::translate("EditLibraryMonoClass", "\346\234\200\347\265\202\346\261\272\345\256\232\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        label_27->setText(QCoreApplication::translate("EditLibraryMonoClass", "\346\234\200\345\260\217\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditLibraryMonoClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditLibraryMonoClass", "Name", nullptr));
        label_25->setText(QCoreApplication::translate("EditLibraryMonoClass", "\347\224\237\346\210\220\346\231\202\343\203\216\343\202\244\343\202\272\351\231\244\345\216\273\343\203\211\343\203\203\343\203\210", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditLibraryMonoClass", "Library Name", nullptr));
        pushButton->setText(QCoreApplication::translate("EditLibraryMonoClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditLibraryMonoClass", "Clear new", nullptr));
        label_22->setText(QCoreApplication::translate("EditLibraryMonoClass", "\350\251\263\347\264\260\351\240\230\345\237\237\343\202\267\343\203\225\343\203\210\351\207\217", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditLibraryMonoClass", "Update", nullptr));
        checkBoxStartupExecute->setText(QCoreApplication::translate("EditLibraryMonoClass", "\343\203\207\343\203\225\343\202\251\343\203\253\343\203\210\343\201\247\345\256\237\350\241\214", nullptr));
        label_26->setText(QCoreApplication::translate("EditLibraryMonoClass", "\346\212\275\345\207\272\351\240\230\345\237\237\343\201\256\350\206\250\345\274\265\351\207\217", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditLibraryMonoClass", "12345", nullptr));
        label_31->setText(QCoreApplication::translate("EditLibraryMonoClass", "\346\212\275\345\207\272\344\270\212\351\231\220\350\274\235\345\272\246", nullptr));
        label_32->setText(QCoreApplication::translate("EditLibraryMonoClass", "\346\212\275\345\207\272\344\270\213\351\231\220\350\274\235\345\272\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLibraryMonoClass: public Ui_EditLibraryMonoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLIBRARYMONO_H
