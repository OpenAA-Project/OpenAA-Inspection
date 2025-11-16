/********************************************************************************
** Form generated from reading UI file 'PropertyPixelInspectionForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYPIXELINSPECTIONFORM_H
#define UI_PROPERTYPIXELINSPECTIONFORM_H

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
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyPixelInspectionFormClass
{
public:
    QTableWidget *tableWidgetLibList;
    QFrame *frameLibFolder;
    QFrame *frame_3;
    QPushButton *pbClearNew;
    QLineEdit *EditLibName;
    QPushButton *pbUpdate;
    QPushButton *pbDelete;
    QPushButton *pbSaveNew;
    QLabel *label_5;
    QLineEdit *EditLibID;
    QFrame *frame;
    QCheckBox *chbDetailSettingNarrow;
    QSpinBox *sbSearchDotTargetNarrow;
    QLineEdit *EditLibID_2;
    QSpinBox *sbSearchDotMasterNarrow;
    QLabel *label_19;
    QLabel *label_13;
    QLabel *label_10;
    QLabel *label_20;
    QLabel *label_22;
    QSpinBox *sbNGSizeNarrow;
    QDoubleSpinBox *dsbRelativeNGThresholdNarrow;
    QSpinBox *sbAbsoluteNGThresholdNarrow;
    QLabel *label_25;
    QFrame *frame_2;
    QLineEdit *EditLibID_3;
    QLabel *label_23;
    QSpinBox *sbSearchDotMasterBroad;
    QCheckBox *chbDetailSettingBroad;
    QLabel *label_24;
    QLabel *label_14;
    QLabel *label_11;
    QSpinBox *sbNGSizeBroad;
    QSpinBox *sbSearchDotTargetBroad;
    QLabel *label_21;
    QSpinBox *sbAbsoluteNGThresholdBroad;
    QLabel *label_26;
    QDoubleSpinBox *dsbRelativeNGThresholdBroad;
    QCheckBox *chbIsCalcPixelInterPoration;
    QLabel *label_27;

    void setupUi(GUIFormBase *PropertyPixelInspectionFormClass)
    {
        if (PropertyPixelInspectionFormClass->objectName().isEmpty())
            PropertyPixelInspectionFormClass->setObjectName("PropertyPixelInspectionFormClass");
        PropertyPixelInspectionFormClass->resize(401, 671);
        tableWidgetLibList = new QTableWidget(PropertyPixelInspectionFormClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 181, 161));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolder = new QFrame(PropertyPixelInspectionFormClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 161));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        frame_3 = new QFrame(PropertyPixelInspectionFormClass);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 180, 381, 461));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        pbClearNew = new QPushButton(frame_3);
        pbClearNew->setObjectName("pbClearNew");
        pbClearNew->setGeometry(QRect(10, 420, 91, 31));
        QFont font;
        font.setPointSize(11);
        pbClearNew->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbClearNew->setIcon(icon);
        EditLibName = new QLineEdit(frame_3);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 10, 231, 31));
        QFont font1;
        font1.setPointSize(12);
        EditLibName->setFont(font1);
        pbUpdate = new QPushButton(frame_3);
        pbUpdate->setObjectName("pbUpdate");
        pbUpdate->setGeometry(QRect(290, 420, 81, 31));
        pbUpdate->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbUpdate->setIcon(icon1);
        pbDelete = new QPushButton(frame_3);
        pbDelete->setObjectName("pbDelete");
        pbDelete->setGeometry(QRect(110, 420, 71, 31));
        pbDelete->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbDelete->setIcon(icon2);
        pbSaveNew = new QPushButton(frame_3);
        pbSaveNew->setObjectName("pbSaveNew");
        pbSaveNew->setGeometry(QRect(190, 420, 91, 31));
        pbSaveNew->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbSaveNew->setIcon(icon3);
        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 10, 51, 31));
        label_5->setFont(font1);
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(frame_3);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 10, 81, 31));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        frame = new QFrame(frame_3);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 50, 361, 161));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        chbDetailSettingNarrow = new QCheckBox(frame);
        chbDetailSettingNarrow->setObjectName("chbDetailSettingNarrow");
        chbDetailSettingNarrow->setGeometry(QRect(270, 30, 81, 20));
        sbSearchDotTargetNarrow = new QSpinBox(frame);
        sbSearchDotTargetNarrow->setObjectName("sbSearchDotTargetNarrow");
        sbSearchDotTargetNarrow->setGeometry(QRect(270, 70, 81, 22));
        sbSearchDotTargetNarrow->setValue(1);
        EditLibID_2 = new QLineEdit(frame);
        EditLibID_2->setObjectName("EditLibID_2");
        EditLibID_2->setGeometry(QRect(0, 0, 361, 21));
        EditLibID_2->setFont(font1);
        EditLibID_2->setAlignment(Qt::AlignCenter);
        EditLibID_2->setReadOnly(true);
        sbSearchDotMasterNarrow = new QSpinBox(frame);
        sbSearchDotMasterNarrow->setObjectName("sbSearchDotMasterNarrow");
        sbSearchDotMasterNarrow->setGeometry(QRect(270, 50, 81, 22));
        label_19 = new QLabel(frame);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(10, 30, 251, 21));
        label_19->setFrameShape(QFrame::Panel);
        label_19->setFrameShadow(QFrame::Sunken);
        label_19->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_13 = new QLabel(frame);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 50, 251, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_10 = new QLabel(frame);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 70, 251, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_20 = new QLabel(frame);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(10, 130, 251, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        label_20->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_22 = new QLabel(frame);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(10, 90, 251, 21));
        label_22->setFrameShape(QFrame::Panel);
        label_22->setFrameShadow(QFrame::Sunken);
        label_22->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        sbNGSizeNarrow = new QSpinBox(frame);
        sbNGSizeNarrow->setObjectName("sbNGSizeNarrow");
        sbNGSizeNarrow->setGeometry(QRect(270, 130, 81, 22));
        sbNGSizeNarrow->setMinimum(1);
        sbNGSizeNarrow->setMaximum(9999);
        sbNGSizeNarrow->setValue(4);
        dsbRelativeNGThresholdNarrow = new QDoubleSpinBox(frame);
        dsbRelativeNGThresholdNarrow->setObjectName("dsbRelativeNGThresholdNarrow");
        dsbRelativeNGThresholdNarrow->setGeometry(QRect(270, 90, 81, 22));
        dsbRelativeNGThresholdNarrow->setDecimals(1);
        dsbRelativeNGThresholdNarrow->setMinimum(-1.000000000000000);
        dsbRelativeNGThresholdNarrow->setMaximum(1.000000000000000);
        dsbRelativeNGThresholdNarrow->setSingleStep(0.100000000000000);
        sbAbsoluteNGThresholdNarrow = new QSpinBox(frame);
        sbAbsoluteNGThresholdNarrow->setObjectName("sbAbsoluteNGThresholdNarrow");
        sbAbsoluteNGThresholdNarrow->setGeometry(QRect(270, 110, 81, 22));
        sbAbsoluteNGThresholdNarrow->setMinimum(1);
        sbAbsoluteNGThresholdNarrow->setMaximum(255);
        sbAbsoluteNGThresholdNarrow->setValue(10);
        label_25 = new QLabel(frame);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(10, 110, 251, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_2 = new QFrame(frame_3);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 220, 361, 161));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        EditLibID_3 = new QLineEdit(frame_2);
        EditLibID_3->setObjectName("EditLibID_3");
        EditLibID_3->setGeometry(QRect(0, 0, 361, 21));
        EditLibID_3->setFont(font1);
        EditLibID_3->setAlignment(Qt::AlignCenter);
        EditLibID_3->setReadOnly(true);
        label_23 = new QLabel(frame_2);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(10, 130, 251, 21));
        label_23->setFrameShape(QFrame::Panel);
        label_23->setFrameShadow(QFrame::Sunken);
        label_23->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        sbSearchDotMasterBroad = new QSpinBox(frame_2);
        sbSearchDotMasterBroad->setObjectName("sbSearchDotMasterBroad");
        sbSearchDotMasterBroad->setGeometry(QRect(270, 50, 81, 22));
        chbDetailSettingBroad = new QCheckBox(frame_2);
        chbDetailSettingBroad->setObjectName("chbDetailSettingBroad");
        chbDetailSettingBroad->setGeometry(QRect(270, 30, 81, 20));
        label_24 = new QLabel(frame_2);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(10, 90, 251, 21));
        label_24->setFrameShape(QFrame::Panel);
        label_24->setFrameShadow(QFrame::Sunken);
        label_24->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_14 = new QLabel(frame_2);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 50, 251, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_11 = new QLabel(frame_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 70, 251, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        sbNGSizeBroad = new QSpinBox(frame_2);
        sbNGSizeBroad->setObjectName("sbNGSizeBroad");
        sbNGSizeBroad->setGeometry(QRect(270, 130, 81, 22));
        sbNGSizeBroad->setMinimum(1);
        sbNGSizeBroad->setMaximum(9999);
        sbNGSizeBroad->setValue(100);
        sbSearchDotTargetBroad = new QSpinBox(frame_2);
        sbSearchDotTargetBroad->setObjectName("sbSearchDotTargetBroad");
        sbSearchDotTargetBroad->setGeometry(QRect(270, 70, 81, 22));
        sbSearchDotTargetBroad->setValue(1);
        label_21 = new QLabel(frame_2);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(10, 30, 251, 21));
        label_21->setFrameShape(QFrame::Panel);
        label_21->setFrameShadow(QFrame::Sunken);
        label_21->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        sbAbsoluteNGThresholdBroad = new QSpinBox(frame_2);
        sbAbsoluteNGThresholdBroad->setObjectName("sbAbsoluteNGThresholdBroad");
        sbAbsoluteNGThresholdBroad->setGeometry(QRect(270, 110, 81, 22));
        sbAbsoluteNGThresholdBroad->setMinimum(1);
        sbAbsoluteNGThresholdBroad->setMaximum(255);
        sbAbsoluteNGThresholdBroad->setValue(10);
        label_26 = new QLabel(frame_2);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(10, 110, 251, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        dsbRelativeNGThresholdBroad = new QDoubleSpinBox(frame_2);
        dsbRelativeNGThresholdBroad->setObjectName("dsbRelativeNGThresholdBroad");
        dsbRelativeNGThresholdBroad->setGeometry(QRect(270, 90, 81, 22));
        dsbRelativeNGThresholdBroad->setDecimals(1);
        dsbRelativeNGThresholdBroad->setMinimum(-1.000000000000000);
        dsbRelativeNGThresholdBroad->setMaximum(1.000000000000000);
        dsbRelativeNGThresholdBroad->setSingleStep(0.100000000000000);
        chbIsCalcPixelInterPoration = new QCheckBox(frame_3);
        chbIsCalcPixelInterPoration->setObjectName("chbIsCalcPixelInterPoration");
        chbIsCalcPixelInterPoration->setGeometry(QRect(280, 390, 81, 20));
        label_27 = new QLabel(frame_3);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(10, 390, 261, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(PropertyPixelInspectionFormClass);

        QMetaObject::connectSlotsByName(PropertyPixelInspectionFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyPixelInspectionFormClass)
    {
        PropertyPixelInspectionFormClass->setWindowTitle(QCoreApplication::translate("PropertyPixelInspectionFormClass", "PropertyPixelInspectionForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "Name", nullptr));
        pbClearNew->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "Clear new", nullptr));
        EditLibName->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "Library Name", nullptr));
        pbUpdate->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "Update", nullptr));
        pbDelete->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "Delete", nullptr));
        pbSaveNew->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "Save New", nullptr));
        label_5->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "12345", nullptr));
        EditLibID_2->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "\347\213\255\345\237\237", nullptr));
        label_19->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "\346\244\234\346\237\273\346\234\211\345\212\271\343\203\201\343\202\247\343\203\203\343\202\257", nullptr));
        label_13->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "\351\226\276\345\200\244\344\275\234\346\210\220\346\231\202\343\201\256\345\221\250\345\233\262\345\214\205\346\213\254\343\203\211\343\203\203\343\203\210", nullptr));
        label_10->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "\346\244\234\346\237\273\346\231\202\343\201\256\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        label_20->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "\346\244\234\345\207\272\343\202\265\343\202\244\343\202\272\357\274\210\343\203\211\343\203\203\343\203\210\357\274\211", nullptr));
        label_22->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "\347\233\270\345\257\276\351\226\276\345\200\244", nullptr));
        label_25->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "\347\265\266\345\257\276\351\226\276\345\200\244", nullptr));
        EditLibID_3->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "\345\272\203\345\237\237", nullptr));
        label_23->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "\346\244\234\345\207\272\343\202\265\343\202\244\343\202\272\357\274\210\343\203\211\343\203\203\343\203\210\357\274\211", nullptr));
        label_24->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "\347\233\270\345\257\276\351\226\276\345\200\244", nullptr));
        label_14->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "\351\226\276\345\200\244\344\275\234\346\210\220\346\231\202\343\201\256\345\221\250\345\233\262\345\214\205\346\213\254\343\203\211\343\203\203\343\203\210", nullptr));
        label_11->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "\346\244\234\346\237\273\346\231\202\343\201\256\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        label_21->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "\346\244\234\346\237\273\346\234\211\345\212\271\343\203\201\343\202\247\343\203\203\343\202\257", nullptr));
        label_26->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "\347\265\266\345\257\276\351\226\276\345\200\244", nullptr));
        label_27->setText(QCoreApplication::translate("PropertyPixelInspectionFormClass", "\343\203\224\343\202\257\343\202\273\343\203\253\350\243\234\351\226\223\346\251\237\350\203\275\343\202\222\346\234\211\345\212\271\343\201\253\343\201\231\343\202\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyPixelInspectionFormClass: public Ui_PropertyPixelInspectionFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYPIXELINSPECTIONFORM_H
