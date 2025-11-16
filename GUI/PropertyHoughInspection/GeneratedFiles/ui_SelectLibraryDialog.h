/********************************************************************************
** Form generated from reading UI file 'SelectLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLIBRARYDIALOG_H
#define UI_SELECTLIBRARYDIALOG_H

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

class Ui_SelectLibraryDialog
{
public:
    QPushButton *pushButtonSelect;
    QLabel *label_4;
    QTableWidget *tableWidgetLibList;
    QFrame *frameLibFolder;
    QLineEdit *EditLibName;
    QPushButton *pushButtonCancel;
    QLineEdit *EditLibID;
    QFrame *frame;
    QSpinBox *EditMinPixels;
    QLabel *label_39;
    QSpinBox *EditZoneWidth;
    QLabel *label_27;
    QSpinBox *EditBinarizedLength;
    QLabel *label_40;
    QLabel *label_41;
    QSpinBox *EditPickupL;
    QLabel *label_28;
    QSpinBox *EditMaxIsolation;
    QLabel *label_43;
    QSpinBox *EditNGLength;
    QSpinBox *EditPickupH;
    QLabel *label_42;
    QCheckBox *checkBoxRemoveDynamicMask;
    QLabel *label_29;
    QSpinBox *EditReducedSize;
    QLabel *label_16;
    QSpinBox *EditMaxLineCount;
    QLabel *label_44;
    QDoubleSpinBox *EditMinNGWidth;
    QLabel *label_45;
    QDoubleSpinBox *EditMaxNGWidth;

    void setupUi(QDialog *SelectLibraryDialog)
    {
        if (SelectLibraryDialog->objectName().isEmpty())
            SelectLibraryDialog->setObjectName("SelectLibraryDialog");
        SelectLibraryDialog->resize(472, 662);
        pushButtonSelect = new QPushButton(SelectLibraryDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(70, 610, 121, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSelect->setIcon(icon);
        label_4 = new QLabel(SelectLibraryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 230, 51, 31));
        QFont font;
        font.setPointSize(12);
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetLibList = new QTableWidget(SelectLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(240, 10, 221, 201));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolder = new QFrame(SelectLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 221, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        EditLibName = new QLineEdit(SelectLibraryDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(130, 230, 331, 31));
        EditLibName->setFont(font);
        pushButtonCancel = new QPushButton(SelectLibraryDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(280, 610, 121, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        EditLibID = new QLineEdit(SelectLibraryDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 230, 71, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        frame = new QFrame(SelectLibraryDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(40, 270, 381, 321));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        EditMinPixels = new QSpinBox(frame);
        EditMinPixels->setObjectName("EditMinPixels");
        EditMinPixels->setGeometry(QRect(240, 110, 81, 22));
        EditMinPixels->setMaximum(999999999);
        label_39 = new QLabel(frame);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(40, 110, 191, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditZoneWidth = new QSpinBox(frame);
        EditZoneWidth->setObjectName("EditZoneWidth");
        EditZoneWidth->setGeometry(QRect(240, 10, 71, 22));
        EditZoneWidth->setMaximum(999999);
        label_27 = new QLabel(frame);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(40, 10, 191, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBinarizedLength = new QSpinBox(frame);
        EditBinarizedLength->setObjectName("EditBinarizedLength");
        EditBinarizedLength->setGeometry(QRect(240, 70, 71, 22));
        EditBinarizedLength->setMaximum(9999999);
        label_40 = new QLabel(frame);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(40, 70, 191, 21));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setFrameShadow(QFrame::Sunken);
        label_40->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_41 = new QLabel(frame);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(130, 260, 101, 21));
        label_41->setFrameShape(QFrame::Panel);
        label_41->setFrameShadow(QFrame::Sunken);
        label_41->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupL = new QSpinBox(frame);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(240, 260, 71, 22));
        EditPickupL->setMaximum(255);
        label_28 = new QLabel(frame);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(40, 30, 191, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxIsolation = new QSpinBox(frame);
        EditMaxIsolation->setObjectName("EditMaxIsolation");
        EditMaxIsolation->setGeometry(QRect(240, 30, 71, 22));
        EditMaxIsolation->setMaximum(999999);
        label_43 = new QLabel(frame);
        label_43->setObjectName("label_43");
        label_43->setGeometry(QRect(40, 130, 191, 21));
        label_43->setFrameShape(QFrame::Panel);
        label_43->setFrameShadow(QFrame::Sunken);
        label_43->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNGLength = new QSpinBox(frame);
        EditNGLength->setObjectName("EditNGLength");
        EditNGLength->setGeometry(QRect(240, 130, 81, 22));
        EditNGLength->setMaximum(99999999);
        EditPickupH = new QSpinBox(frame);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(240, 290, 71, 22));
        EditPickupH->setMaximum(255);
        label_42 = new QLabel(frame);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(130, 290, 101, 21));
        label_42->setFrameShape(QFrame::Panel);
        label_42->setFrameShadow(QFrame::Sunken);
        label_42->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxRemoveDynamicMask = new QCheckBox(frame);
        checkBoxRemoveDynamicMask->setObjectName("checkBoxRemoveDynamicMask");
        checkBoxRemoveDynamicMask->setGeometry(QRect(190, 230, 161, 19));
        label_29 = new QLabel(frame);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(40, 50, 191, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditReducedSize = new QSpinBox(frame);
        EditReducedSize->setObjectName("EditReducedSize");
        EditReducedSize->setGeometry(QRect(240, 50, 71, 22));
        EditReducedSize->setMaximum(999999);
        label_16 = new QLabel(frame);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(40, 200, 191, 21));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxLineCount = new QSpinBox(frame);
        EditMaxLineCount->setObjectName("EditMaxLineCount");
        EditMaxLineCount->setGeometry(QRect(240, 200, 81, 22));
        EditMaxLineCount->setMaximum(999999999);
        label_44 = new QLabel(frame);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(40, 150, 191, 21));
        label_44->setFrameShape(QFrame::Panel);
        label_44->setFrameShadow(QFrame::Sunken);
        label_44->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinNGWidth = new QDoubleSpinBox(frame);
        EditMinNGWidth->setObjectName("EditMinNGWidth");
        EditMinNGWidth->setGeometry(QRect(240, 150, 81, 22));
        EditMinNGWidth->setMaximum(99999999.000000000000000);
        label_45 = new QLabel(frame);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(40, 170, 191, 21));
        label_45->setFrameShape(QFrame::Panel);
        label_45->setFrameShadow(QFrame::Sunken);
        label_45->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxNGWidth = new QDoubleSpinBox(frame);
        EditMaxNGWidth->setObjectName("EditMaxNGWidth");
        EditMaxNGWidth->setGeometry(QRect(240, 170, 81, 22));
        EditMaxNGWidth->setMaximum(99999999.000000000000000);

        retranslateUi(SelectLibraryDialog);

        pushButtonSelect->setDefault(true);


        QMetaObject::connectSlotsByName(SelectLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectLibraryDialog)
    {
        SelectLibraryDialog->setWindowTitle(QCoreApplication::translate("SelectLibraryDialog", "Select Library", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectLibraryDialog", "Select", nullptr));
        label_4->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectLibraryDialog", "Name", nullptr));
        EditLibName->setText(QCoreApplication::translate("SelectLibraryDialog", "Library Name", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectLibraryDialog", "Cancel", nullptr));
        EditLibID->setText(QCoreApplication::translate("SelectLibraryDialog", "12345", nullptr));
        label_39->setText(QCoreApplication::translate("SelectLibraryDialog", "Minimum pixels", nullptr));
        label_27->setText(QCoreApplication::translate("SelectLibraryDialog", "Line width", nullptr));
        label_40->setText(QCoreApplication::translate("SelectLibraryDialog", "Partial binarized size", nullptr));
        label_41->setText(QCoreApplication::translate("SelectLibraryDialog", "Pickup Low", nullptr));
        label_28->setText(QCoreApplication::translate("SelectLibraryDialog", "Maximum isolation", nullptr));
        label_43->setText(QCoreApplication::translate("SelectLibraryDialog", "NG Length", nullptr));
        label_42->setText(QCoreApplication::translate("SelectLibraryDialog", "Pickup High", nullptr));
        checkBoxRemoveDynamicMask->setText(QCoreApplication::translate("SelectLibraryDialog", "DynamicMask", nullptr));
        label_29->setText(QCoreApplication::translate("SelectLibraryDialog", "Reduced noise pixel area", nullptr));
        label_16->setText(QCoreApplication::translate("SelectLibraryDialog", "Max line count", nullptr));
        label_44->setText(QCoreApplication::translate("SelectLibraryDialog", "Min NG width", nullptr));
        label_45->setText(QCoreApplication::translate("SelectLibraryDialog", "Max NG width", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibraryDialog: public Ui_SelectLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBRARYDIALOG_H
