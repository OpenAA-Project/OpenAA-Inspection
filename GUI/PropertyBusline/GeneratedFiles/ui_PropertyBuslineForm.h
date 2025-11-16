/********************************************************************************
** Form generated from reading UI file 'PropertyBuslineForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYBUSLINEFORM_H
#define UI_PROPERTYBUSLINEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyBuslineForm
{
public:
    QFrame *frame;
    QToolButton *toolButtonGenerate;
    QLabel *label_32;
    QToolButton *toolButtonTest;
    QToolButton *toolButtonTestOpen;
    QToolButton *toolButtonTestShort;
    QFrame *frame_2;
    QLabel *label_31;
    QPushButton *pushButtonSetFromAll;
    QPushButton *pushButtonEditLibrary;
    QTableWidget *tableWidgetGeneratedLibList;
    QPushButton *pushButtonGetBackAll;
    QPushButton *pushButtonGetBack;
    QLabel *labelLibFolderName;
    QTableWidget *tableWidgetLibList;
    QPushButton *pushButtonEditLibFolder;
    QLabel *label_30;
    QPushButton *pushButtonSetFrom;
    QFrame *frame_3;
    QSpinBox *EditMinWidth;
    QLabel *label_27;
    QPushButton *ButtonLibSave;
    QLabel *label_3;
    QLineEdit *EditLibName;
    QLabel *label_4;
    QLineEdit *EditLibID;
    QSpinBox *EditBinarizedLength;
    QLabel *label_41;
    QLabel *label_40;
    QSpinBox *EditReferredBrightness;
    QCheckBox *checkBoxDarkside;
    QLabel *label_42;
    QSpinBox *EditSearchDotToMaster;
    QCheckBox *checkBoxCompareToMaster;
    QLabel *label_28;
    QSpinBox *EditMinGap;
    QCheckBox *checkBoxAutoBinarize;
    QCheckBox *checkBoxReduceNoise;
    QLabel *label_44;
    QLabel *label_43;
    QDoubleSpinBox *doubleSpinBox;
    QLineEdit *lineEditMinArea;
    QLineEdit *lineEditMaxArea;
    QLabel *label_29;
    QSpinBox *EditMinSize;
    QPushButton *pushButtonGenerateFotTest;
    QFrame *frame_4;
    QLabel *label_5;
    QTableWidget *tableWidgetItemList;
    QPushButton *pushButtonTest;
    QPushButton *pushButtonClear;

    void setupUi(GUIFormBase *PropertyBuslineForm)
    {
        if (PropertyBuslineForm->objectName().isEmpty())
            PropertyBuslineForm->setObjectName("PropertyBuslineForm");
        PropertyBuslineForm->resize(400, 830);
        frame = new QFrame(PropertyBuslineForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 381, 61));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        toolButtonGenerate = new QToolButton(frame);
        toolButtonGenerate->setObjectName("toolButtonGenerate");
        toolButtonGenerate->setGeometry(QRect(10, 24, 151, 31));
        toolButtonGenerate->setCheckable(true);
        toolButtonGenerate->setChecked(true);
        toolButtonGenerate->setAutoExclusive(true);
        label_32 = new QLabel(frame);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(0, 0, 381, 20));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        toolButtonTest = new QToolButton(frame);
        toolButtonTest->setObjectName("toolButtonTest");
        toolButtonTest->setGeometry(QRect(170, 24, 101, 31));
        toolButtonTest->setCheckable(true);
        toolButtonTest->setChecked(false);
        toolButtonTest->setAutoExclusive(true);
        toolButtonTestOpen = new QToolButton(frame);
        toolButtonTestOpen->setObjectName("toolButtonTestOpen");
        toolButtonTestOpen->setGeometry(QRect(270, 24, 51, 31));
        toolButtonTestOpen->setCheckable(true);
        toolButtonTestOpen->setChecked(false);
        toolButtonTestOpen->setAutoExclusive(true);
        toolButtonTestShort = new QToolButton(frame);
        toolButtonTestShort->setObjectName("toolButtonTestShort");
        toolButtonTestShort->setGeometry(QRect(320, 24, 51, 31));
        toolButtonTestShort->setCheckable(true);
        toolButtonTestShort->setChecked(false);
        toolButtonTestShort->setAutoExclusive(true);
        frame_2 = new QFrame(PropertyBuslineForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 76, 381, 241));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_31 = new QLabel(frame_2);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(220, 40, 151, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSetFromAll = new QPushButton(frame_2);
        pushButtonSetFromAll->setObjectName("pushButtonSetFromAll");
        pushButtonSetFromAll->setGeometry(QRect(170, 170, 39, 23));
        pushButtonEditLibrary = new QPushButton(frame_2);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(220, 190, 151, 41));
        QFont font;
        font.setPointSize(12);
        pushButtonEditLibrary->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon);
        tableWidgetGeneratedLibList = new QTableWidget(frame_2);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetGeneratedLibList->setObjectName("tableWidgetGeneratedLibList");
        tableWidgetGeneratedLibList->setGeometry(QRect(220, 60, 151, 121));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonGetBackAll = new QPushButton(frame_2);
        pushButtonGetBackAll->setObjectName("pushButtonGetBackAll");
        pushButtonGetBackAll->setGeometry(QRect(170, 200, 39, 23));
        pushButtonGetBack = new QPushButton(frame_2);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(170, 120, 39, 23));
        labelLibFolderName = new QLabel(frame_2);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(120, 4, 251, 31));
        QFont font1;
        font1.setPointSize(16);
        labelLibFolderName->setFont(font1);
        tableWidgetLibList = new QTableWidget(frame_2);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 60, 151, 171));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonEditLibFolder = new QPushButton(frame_2);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(10, 4, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon1);
        label_30 = new QLabel(frame_2);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 40, 151, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSetFrom = new QPushButton(frame_2);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(170, 90, 39, 23));
        frame_3 = new QFrame(PropertyBuslineForm);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 320, 381, 341));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        EditMinWidth = new QSpinBox(frame_3);
        EditMinWidth->setObjectName("EditMinWidth");
        EditMinWidth->setGeometry(QRect(260, 48, 91, 22));
        EditMinWidth->setMaximum(999999);
        label_27 = new QLabel(frame_3);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(10, 48, 248, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibSave = new QPushButton(frame_3);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(10, 306, 361, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon2);
        label_3 = new QLabel(frame_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 381, 21));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibName = new QLineEdit(frame_3);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 20, 231, 21));
        EditLibName->setFont(font);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 20, 51, 21));
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(frame_3);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 20, 81, 21));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        EditBinarizedLength = new QSpinBox(frame_3);
        EditBinarizedLength->setObjectName("EditBinarizedLength");
        EditBinarizedLength->setGeometry(QRect(200, 240, 71, 22));
        EditBinarizedLength->setMaximum(99999);
        label_41 = new QLabel(frame_3);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(10, 260, 191, 21));
        label_41->setFrameShape(QFrame::Panel);
        label_41->setFrameShadow(QFrame::Sunken);
        label_41->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_40 = new QLabel(frame_3);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(10, 240, 191, 21));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setFrameShadow(QFrame::Sunken);
        label_40->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditReferredBrightness = new QSpinBox(frame_3);
        EditReferredBrightness->setObjectName("EditReferredBrightness");
        EditReferredBrightness->setGeometry(QRect(200, 260, 71, 22));
        EditReferredBrightness->setMaximum(99999);
        checkBoxDarkside = new QCheckBox(frame_3);
        checkBoxDarkside->setObjectName("checkBoxDarkside");
        checkBoxDarkside->setGeometry(QRect(10, 180, 351, 17));
        label_42 = new QLabel(frame_3);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(10, 280, 191, 21));
        label_42->setFrameShape(QFrame::Panel);
        label_42->setFrameShadow(QFrame::Sunken);
        label_42->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSearchDotToMaster = new QSpinBox(frame_3);
        EditSearchDotToMaster->setObjectName("EditSearchDotToMaster");
        EditSearchDotToMaster->setGeometry(QRect(200, 280, 71, 22));
        EditSearchDotToMaster->setMaximum(99999);
        checkBoxCompareToMaster = new QCheckBox(frame_3);
        checkBoxCompareToMaster->setObjectName("checkBoxCompareToMaster");
        checkBoxCompareToMaster->setGeometry(QRect(10, 200, 351, 17));
        label_28 = new QLabel(frame_3);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(10, 70, 248, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinGap = new QSpinBox(frame_3);
        EditMinGap->setObjectName("EditMinGap");
        EditMinGap->setGeometry(QRect(260, 70, 91, 22));
        EditMinGap->setMaximum(999999);
        checkBoxAutoBinarize = new QCheckBox(frame_3);
        checkBoxAutoBinarize->setObjectName("checkBoxAutoBinarize");
        checkBoxAutoBinarize->setGeometry(QRect(280, 260, 91, 20));
        checkBoxReduceNoise = new QCheckBox(frame_3);
        checkBoxReduceNoise->setObjectName("checkBoxReduceNoise");
        checkBoxReduceNoise->setGeometry(QRect(10, 220, 361, 17));
        label_44 = new QLabel(frame_3);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(10, 122, 248, 21));
        label_44->setFrameShape(QFrame::Panel);
        label_44->setFrameShadow(QFrame::Sunken);
        label_44->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_43 = new QLabel(frame_3);
        label_43->setObjectName("label_43");
        label_43->setGeometry(QRect(10, 100, 248, 21));
        label_43->setFrameShape(QFrame::Panel);
        label_43->setFrameShadow(QFrame::Sunken);
        label_43->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBox = new QDoubleSpinBox(frame_3);
        doubleSpinBox->setObjectName("doubleSpinBox");
        doubleSpinBox->setGeometry(QRect(260, 190, 62, 24));
        doubleSpinBox->setDecimals(0);
        doubleSpinBox->setMaximum(1000000000.000000000000000);
        lineEditMinArea = new QLineEdit(frame_3);
        lineEditMinArea->setObjectName("lineEditMinArea");
        lineEditMinArea->setGeometry(QRect(260, 100, 113, 24));
        lineEditMaxArea = new QLineEdit(frame_3);
        lineEditMaxArea->setObjectName("lineEditMaxArea");
        lineEditMaxArea->setGeometry(QRect(260, 120, 113, 24));
        label_29 = new QLabel(frame_3);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(12, 150, 241, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinSize = new QSpinBox(frame_3);
        EditMinSize->setObjectName("EditMinSize");
        EditMinSize->setGeometry(QRect(260, 150, 91, 22));
        EditMinSize->setMaximum(999999);
        pushButtonGenerateFotTest = new QPushButton(PropertyBuslineForm);
        pushButtonGenerateFotTest->setObjectName("pushButtonGenerateFotTest");
        pushButtonGenerateFotTest->setGeometry(QRect(10, 666, 161, 41));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonGenerateFotTest->setIcon(icon3);
        frame_4 = new QFrame(PropertyBuslineForm);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 710, 381, 121));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(frame_4);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 0, 381, 21));
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetItemList = new QTableWidget(frame_4);
        if (tableWidgetItemList->columnCount() < 4)
            tableWidgetItemList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        tableWidgetItemList->setObjectName("tableWidgetItemList");
        tableWidgetItemList->setGeometry(QRect(10, 24, 361, 91));
        tableWidgetItemList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetItemList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonTest = new QPushButton(PropertyBuslineForm);
        pushButtonTest->setObjectName("pushButtonTest");
        pushButtonTest->setGeometry(QRect(180, 666, 141, 41));
        pushButtonTest->setIcon(icon3);
        pushButtonClear = new QPushButton(PropertyBuslineForm);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(330, 666, 61, 41));

        retranslateUi(PropertyBuslineForm);

        QMetaObject::connectSlotsByName(PropertyBuslineForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyBuslineForm)
    {
        PropertyBuslineForm->setWindowTitle(QCoreApplication::translate("PropertyBuslineForm", "Property Busline", nullptr));
        toolButtonGenerate->setText(QCoreApplication::translate("PropertyBuslineForm", "\343\203\220\343\202\271\343\203\251\343\202\244\343\203\263\343\202\250\343\203\252\343\202\242\350\250\255\345\256\232", nullptr));
        label_32->setText(QCoreApplication::translate("PropertyBuslineForm", "\346\217\217\347\224\273", nullptr));
        toolButtonTest->setText(QCoreApplication::translate("PropertyBuslineForm", "\343\203\206\343\202\271\343\203\210\350\241\250\347\244\272", nullptr));
        toolButtonTestOpen->setText(QCoreApplication::translate("PropertyBuslineForm", "Open", nullptr));
        toolButtonTestShort->setText(QCoreApplication::translate("PropertyBuslineForm", "Short", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyBuslineForm", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyBuslineForm", "=>>", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyBuslineForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyBuslineForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyBuslineForm", "Name", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyBuslineForm", "<<=", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyBuslineForm", "<=", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyBuslineForm", "\357\274\270\357\274\270\357\274\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyBuslineForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyBuslineForm", "Name", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyBuslineForm", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyBuslineForm", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyBuslineForm", "=>", nullptr));
        label_27->setText(QCoreApplication::translate("PropertyBuslineForm", "\346\234\200\345\260\217\343\203\251\343\202\244\343\203\263\345\271\205", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("PropertyBuslineForm", "\343\203\207\343\203\274\343\202\277\343\203\231\343\203\274\343\202\271\343\201\270\343\201\256\346\233\264\346\226\260", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyBuslineForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\227\343\203\255\343\203\221\343\203\206\343\202\243", nullptr));
        EditLibName->setText(QCoreApplication::translate("PropertyBuslineForm", "Library Name", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyBuslineForm", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("PropertyBuslineForm", "12345", nullptr));
        label_41->setText(QCoreApplication::translate("PropertyBuslineForm", "\357\274\222\345\200\244\345\214\226\345\217\202\347\205\247\350\274\235\345\272\246\345\200\244", nullptr));
        label_40->setText(QCoreApplication::translate("PropertyBuslineForm", "\351\203\250\345\210\206\347\232\204\357\274\222\345\200\244\345\214\226\343\201\256\343\202\265\343\202\244\343\202\272", nullptr));
        checkBoxDarkside->setText(QCoreApplication::translate("PropertyBuslineForm", "\346\232\227\345\201\264", nullptr));
        label_42->setText(QCoreApplication::translate("PropertyBuslineForm", "\343\203\236\343\202\271\343\202\277\343\203\274\343\201\250\343\201\256\346\257\224\350\274\203\346\231\202\343\201\256\346\216\242\347\264\242\347\257\204\345\233\262", nullptr));
        checkBoxCompareToMaster->setText(QCoreApplication::translate("PropertyBuslineForm", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217\343\201\250\343\201\256\346\257\224\350\274\203", nullptr));
        label_28->setText(QCoreApplication::translate("PropertyBuslineForm", "\346\234\200\345\260\217\351\226\223\351\232\224", nullptr));
        checkBoxAutoBinarize->setText(QCoreApplication::translate("PropertyBuslineForm", "\350\207\252\345\213\225", nullptr));
        checkBoxReduceNoise->setText(QCoreApplication::translate("PropertyBuslineForm", "\343\203\216\343\202\244\343\202\272\345\211\212\351\231\244", nullptr));
        label_44->setText(QCoreApplication::translate("PropertyBuslineForm", "\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_43->setText(QCoreApplication::translate("PropertyBuslineForm", "\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_29->setText(QCoreApplication::translate("PropertyBuslineForm", "\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        pushButtonGenerateFotTest->setText(QCoreApplication::translate("PropertyBuslineForm", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217\343\201\247\343\201\256\347\224\237\346\210\220", nullptr));
        label_5->setText(QCoreApplication::translate("PropertyBuslineForm", "\347\224\237\346\210\220\343\201\225\343\202\214\343\201\237Busline\343\202\250\343\203\252\343\202\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetItemList->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyBuslineForm", "ItemID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetItemList->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyBuslineForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetItemList->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyBuslineForm", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetItemList->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyBuslineForm", "Location", nullptr));
        pushButtonTest->setText(QCoreApplication::translate("PropertyBuslineForm", "\346\244\234\346\237\273\347\224\273\345\203\217\343\201\247\344\273\256\346\212\275\345\207\272", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("PropertyBuslineForm", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyBuslineForm: public Ui_PropertyBuslineForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYBUSLINEFORM_H
