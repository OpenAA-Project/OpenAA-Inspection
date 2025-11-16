/********************************************************************************
** Form generated from reading UI file 'PropertyHoughInspectionForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYHOUGHINSPECTIONFORM_H
#define UI_PROPERTYHOUGHINSPECTIONFORM_H

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

class Ui_PropertyHoughInspectionForm
{
public:
    QFrame *frame;
    QToolButton *toolButtonGenerate;
    QLabel *label_32;
    QToolButton *toolButtonTest;
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
    QPushButton *ButtonLibSave;
    QLabel *label_3;
    QLineEdit *EditLibName;
    QLabel *label_4;
    QLineEdit *EditLibID;
    QLabel *label_40;
    QSpinBox *EditMaxIsolation;
    QLabel *label_39;
    QSpinBox *EditPickupH;
    QLabel *label_27;
    QSpinBox *EditNGLength;
    QLabel *label_28;
    QLabel *label_43;
    QLabel *label_41;
    QSpinBox *EditBinarizedLength;
    QLabel *label_42;
    QSpinBox *EditZoneWidth;
    QSpinBox *EditMinPixels;
    QSpinBox *EditPickupL;
    QCheckBox *checkBoxRemoveDynamicMask;
    QLabel *label_29;
    QSpinBox *EditReducedSize;
    QLabel *label_16;
    QSpinBox *EditMaxLineCount;
    QLabel *label_44;
    QDoubleSpinBox *EditMinNGWidth;
    QLabel *label_45;
    QDoubleSpinBox *EditMaxNGWidth;
    QFrame *frame_4;
    QLabel *label_5;
    QTableWidget *tableWidgetItemList;

    void setupUi(GUIFormBase *PropertyHoughInspectionForm)
    {
        if (PropertyHoughInspectionForm->objectName().isEmpty())
            PropertyHoughInspectionForm->setObjectName("PropertyHoughInspectionForm");
        PropertyHoughInspectionForm->resize(400, 909);
        frame = new QFrame(PropertyHoughInspectionForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 381, 71));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        toolButtonGenerate = new QToolButton(frame);
        toolButtonGenerate->setObjectName("toolButtonGenerate");
        toolButtonGenerate->setGeometry(QRect(10, 30, 141, 31));
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
        toolButtonTest->setGeometry(QRect(180, 30, 141, 31));
        toolButtonTest->setCheckable(true);
        toolButtonTest->setChecked(false);
        toolButtonTest->setAutoExclusive(true);
        frame_2 = new QFrame(PropertyHoughInspectionForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 90, 381, 251));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_31 = new QLabel(frame_2);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(220, 50, 151, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSetFromAll = new QPushButton(frame_2);
        pushButtonSetFromAll->setObjectName("pushButtonSetFromAll");
        pushButtonSetFromAll->setGeometry(QRect(170, 170, 39, 23));
        pushButtonEditLibrary = new QPushButton(frame_2);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(220, 200, 151, 41));
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
        tableWidgetGeneratedLibList->setGeometry(QRect(220, 70, 151, 121));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonGetBackAll = new QPushButton(frame_2);
        pushButtonGetBackAll->setObjectName("pushButtonGetBackAll");
        pushButtonGetBackAll->setGeometry(QRect(170, 200, 39, 23));
        pushButtonGetBack = new QPushButton(frame_2);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(170, 120, 39, 23));
        labelLibFolderName = new QLabel(frame_2);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(120, 10, 251, 31));
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
        tableWidgetLibList->setGeometry(QRect(10, 70, 151, 171));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonEditLibFolder = new QPushButton(frame_2);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(10, 10, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon1);
        label_30 = new QLabel(frame_2);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 50, 151, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSetFrom = new QPushButton(frame_2);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(170, 90, 39, 23));
        frame_3 = new QFrame(PropertyHoughInspectionForm);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 350, 381, 361));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        ButtonLibSave = new QPushButton(frame_3);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(10, 320, 361, 31));
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
        label_40 = new QLabel(frame_3);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(60, 110, 191, 21));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setFrameShadow(QFrame::Sunken);
        label_40->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxIsolation = new QSpinBox(frame_3);
        EditMaxIsolation->setObjectName("EditMaxIsolation");
        EditMaxIsolation->setGeometry(QRect(260, 70, 71, 22));
        EditMaxIsolation->setMaximum(999999);
        label_39 = new QLabel(frame_3);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(60, 150, 191, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupH = new QSpinBox(frame_3);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(300, 260, 61, 22));
        EditPickupH->setMaximum(255);
        label_27 = new QLabel(frame_3);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(60, 50, 191, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNGLength = new QSpinBox(frame_3);
        EditNGLength->setObjectName("EditNGLength");
        EditNGLength->setGeometry(QRect(260, 170, 81, 22));
        EditNGLength->setMaximum(99999999);
        label_28 = new QLabel(frame_3);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(60, 70, 191, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_43 = new QLabel(frame_3);
        label_43->setObjectName("label_43");
        label_43->setGeometry(QRect(60, 170, 191, 21));
        label_43->setFrameShape(QFrame::Panel);
        label_43->setFrameShadow(QFrame::Sunken);
        label_43->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_41 = new QLabel(frame_3);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(10, 260, 101, 21));
        label_41->setFrameShape(QFrame::Panel);
        label_41->setFrameShadow(QFrame::Sunken);
        label_41->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBinarizedLength = new QSpinBox(frame_3);
        EditBinarizedLength->setObjectName("EditBinarizedLength");
        EditBinarizedLength->setGeometry(QRect(260, 110, 71, 22));
        EditBinarizedLength->setMaximum(9999999);
        label_42 = new QLabel(frame_3);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(200, 260, 101, 21));
        label_42->setFrameShape(QFrame::Panel);
        label_42->setFrameShadow(QFrame::Sunken);
        label_42->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditZoneWidth = new QSpinBox(frame_3);
        EditZoneWidth->setObjectName("EditZoneWidth");
        EditZoneWidth->setGeometry(QRect(260, 50, 71, 22));
        EditZoneWidth->setMaximum(999999);
        EditMinPixels = new QSpinBox(frame_3);
        EditMinPixels->setObjectName("EditMinPixels");
        EditMinPixels->setGeometry(QRect(260, 150, 81, 22));
        EditMinPixels->setMaximum(999999999);
        EditPickupL = new QSpinBox(frame_3);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(110, 260, 61, 22));
        EditPickupL->setMaximum(255);
        checkBoxRemoveDynamicMask = new QCheckBox(frame_3);
        checkBoxRemoveDynamicMask->setObjectName("checkBoxRemoveDynamicMask");
        checkBoxRemoveDynamicMask->setGeometry(QRect(200, 290, 161, 19));
        label_29 = new QLabel(frame_3);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(60, 90, 191, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditReducedSize = new QSpinBox(frame_3);
        EditReducedSize->setObjectName("EditReducedSize");
        EditReducedSize->setGeometry(QRect(260, 90, 71, 22));
        EditReducedSize->setMaximum(999999);
        label_16 = new QLabel(frame_3);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(60, 230, 191, 21));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxLineCount = new QSpinBox(frame_3);
        EditMaxLineCount->setObjectName("EditMaxLineCount");
        EditMaxLineCount->setGeometry(QRect(260, 230, 81, 22));
        EditMaxLineCount->setMaximum(999999999);
        label_44 = new QLabel(frame_3);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(60, 190, 191, 21));
        label_44->setFrameShape(QFrame::Panel);
        label_44->setFrameShadow(QFrame::Sunken);
        label_44->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinNGWidth = new QDoubleSpinBox(frame_3);
        EditMinNGWidth->setObjectName("EditMinNGWidth");
        EditMinNGWidth->setGeometry(QRect(260, 190, 81, 22));
        EditMinNGWidth->setMaximum(99999999.000000000000000);
        label_45 = new QLabel(frame_3);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(60, 210, 191, 21));
        label_45->setFrameShape(QFrame::Panel);
        label_45->setFrameShadow(QFrame::Sunken);
        label_45->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxNGWidth = new QDoubleSpinBox(frame_3);
        EditMaxNGWidth->setObjectName("EditMaxNGWidth");
        EditMaxNGWidth->setGeometry(QRect(260, 210, 81, 22));
        EditMaxNGWidth->setMaximum(99999999.000000000000000);
        frame_4 = new QFrame(PropertyHoughInspectionForm);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 730, 381, 171));
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
        tableWidgetItemList->setGeometry(QRect(10, 30, 361, 131));
        tableWidgetItemList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetItemList->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(PropertyHoughInspectionForm);

        QMetaObject::connectSlotsByName(PropertyHoughInspectionForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyHoughInspectionForm)
    {
        PropertyHoughInspectionForm->setWindowTitle(QCoreApplication::translate("PropertyHoughInspectionForm", "Property HoughInspection", nullptr));
        toolButtonGenerate->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Item area", nullptr));
        label_32->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Draw", nullptr));
        toolButtonTest->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Test view", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "=>>", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "EditLibrary", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Name", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "<<=", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "<=", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "\357\274\270\357\274\270\357\274\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Name", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Category", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "=>", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Update", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Property", nullptr));
        EditLibName->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Library Name", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Name", nullptr));
        EditLibID->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "12345", nullptr));
        label_40->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Partial binarized size", nullptr));
        label_39->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Minimum pixels", nullptr));
        label_27->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Line width", nullptr));
        label_28->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Maximum isolation", nullptr));
        label_43->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "NG Length", nullptr));
        label_41->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Pickup Low", nullptr));
        label_42->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Pickup High", nullptr));
        checkBoxRemoveDynamicMask->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "DynamicMask", nullptr));
        label_29->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Reduced noise pixel area", nullptr));
        label_16->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Max line count", nullptr));
        label_44->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Min NG width", nullptr));
        label_45->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Max NG width", nullptr));
        label_5->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Generated area", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetItemList->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "ItemID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetItemList->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetItemList->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetItemList->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyHoughInspectionForm", "Location", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyHoughInspectionForm: public Ui_PropertyHoughInspectionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYHOUGHINSPECTIONFORM_H
