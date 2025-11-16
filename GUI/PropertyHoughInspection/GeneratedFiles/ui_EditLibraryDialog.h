/********************************************************************************
** Form generated from reading UI file 'EditLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLIBRARYDIALOG_H
#define UI_EDITLIBRARYDIALOG_H

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

class Ui_EditLibraryDialog
{
public:
    QLabel *label_4;
    QTableWidget *tableWidgetLibList;
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
    QDoubleSpinBox *EditMaxNGWidth;
    QLabel *label_45;
    QLabel *label_46;
    QSpinBox *EditMinAverageContinuous;
    QCheckBox *checkBoxDynamicBinarize;
    QPushButton *pushButton;
    QPushButton *ButtonLibSaveNew;
    QFrame *frameLibFolder;
    QLineEdit *EditLibName;
    QPushButton *ButtonLibNew;
    QLineEdit *EditLibID;
    QPushButton *ButtonLibSave;
    QPushButton *ButtonLibDelete;

    void setupUi(QDialog *EditLibraryDialog)
    {
        if (EditLibraryDialog->objectName().isEmpty())
            EditLibraryDialog->setObjectName("EditLibraryDialog");
        EditLibraryDialog->resize(413, 740);
        label_4 = new QLabel(EditLibraryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 230, 51, 31));
        QFont font;
        font.setPointSize(12);
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetLibList = new QTableWidget(EditLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(220, 10, 171, 201));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(EditLibraryDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 270, 391, 381));
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
        label_41->setGeometry(QRect(110, 270, 131, 21));
        label_41->setFrameShape(QFrame::Panel);
        label_41->setFrameShadow(QFrame::Sunken);
        label_41->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupL = new QSpinBox(frame);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(250, 270, 71, 22));
        EditPickupL->setMaximum(1000000);
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
        EditPickupH->setGeometry(QRect(250, 300, 71, 22));
        EditPickupH->setMaximum(1000000);
        label_42 = new QLabel(frame);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(110, 300, 131, 21));
        label_42->setFrameShape(QFrame::Panel);
        label_42->setFrameShadow(QFrame::Sunken);
        label_42->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxRemoveDynamicMask = new QCheckBox(frame);
        checkBoxRemoveDynamicMask->setObjectName("checkBoxRemoveDynamicMask");
        checkBoxRemoveDynamicMask->setGeometry(QRect(160, 240, 161, 22));
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
        label_16->setGeometry(QRect(40, 190, 191, 21));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxLineCount = new QSpinBox(frame);
        EditMaxLineCount->setObjectName("EditMaxLineCount");
        EditMaxLineCount->setGeometry(QRect(240, 190, 81, 22));
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
        EditMaxNGWidth = new QDoubleSpinBox(frame);
        EditMaxNGWidth->setObjectName("EditMaxNGWidth");
        EditMaxNGWidth->setGeometry(QRect(240, 170, 81, 22));
        EditMaxNGWidth->setMaximum(99999999.000000000000000);
        label_45 = new QLabel(frame);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(40, 170, 191, 21));
        label_45->setFrameShape(QFrame::Panel);
        label_45->setFrameShadow(QFrame::Sunken);
        label_45->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_46 = new QLabel(frame);
        label_46->setObjectName("label_46");
        label_46->setGeometry(QRect(40, 210, 191, 21));
        label_46->setFrameShape(QFrame::Panel);
        label_46->setFrameShadow(QFrame::Sunken);
        label_46->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinAverageContinuous = new QSpinBox(frame);
        EditMinAverageContinuous->setObjectName("EditMinAverageContinuous");
        EditMinAverageContinuous->setGeometry(QRect(240, 210, 81, 22));
        EditMinAverageContinuous->setMaximum(999999999);
        checkBoxDynamicBinarize = new QCheckBox(frame);
        checkBoxDynamicBinarize->setObjectName("checkBoxDynamicBinarize");
        checkBoxDynamicBinarize->setGeometry(QRect(160, 330, 161, 22));
        pushButton = new QPushButton(EditLibraryDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(320, 700, 81, 31));
        QFont font1;
        font1.setPointSize(11);
        pushButton->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon);
        ButtonLibSaveNew = new QPushButton(EditLibraryDialog);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(210, 660, 101, 31));
        ButtonLibSaveNew->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon1);
        frameLibFolder = new QFrame(EditLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 201, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        EditLibName = new QLineEdit(EditLibraryDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 230, 251, 31));
        EditLibName->setFont(font);
        ButtonLibNew = new QPushButton(EditLibraryDialog);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(10, 660, 101, 31));
        ButtonLibNew->setFont(font1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon2);
        EditLibID = new QLineEdit(EditLibraryDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 230, 81, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        ButtonLibSave = new QPushButton(EditLibraryDialog);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(320, 660, 81, 31));
        ButtonLibSave->setFont(font1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon3);
        ButtonLibDelete = new QPushButton(EditLibraryDialog);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(120, 660, 81, 31));
        ButtonLibDelete->setFont(font1);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon4);

        retranslateUi(EditLibraryDialog);

        QMetaObject::connectSlotsByName(EditLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *EditLibraryDialog)
    {
        EditLibraryDialog->setWindowTitle(QCoreApplication::translate("EditLibraryDialog", "Edit Library", nullptr));
        label_4->setText(QCoreApplication::translate("EditLibraryDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditLibraryDialog", "Name", nullptr));
        label_39->setText(QCoreApplication::translate("EditLibraryDialog", "Minimum pixels", nullptr));
        label_27->setText(QCoreApplication::translate("EditLibraryDialog", "Line width", nullptr));
        label_40->setText(QCoreApplication::translate("EditLibraryDialog", "Partial binarized size", nullptr));
        label_41->setText(QCoreApplication::translate("EditLibraryDialog", "Pickup Low", nullptr));
        label_28->setText(QCoreApplication::translate("EditLibraryDialog", "Maximum isolation", nullptr));
        label_43->setText(QCoreApplication::translate("EditLibraryDialog", "NG Length", nullptr));
        label_42->setText(QCoreApplication::translate("EditLibraryDialog", "Pickup High", nullptr));
        checkBoxRemoveDynamicMask->setText(QCoreApplication::translate("EditLibraryDialog", "DynamicMask", nullptr));
        label_29->setText(QCoreApplication::translate("EditLibraryDialog", "Reduced noise pixel area", nullptr));
        label_16->setText(QCoreApplication::translate("EditLibraryDialog", "Max line count", nullptr));
        label_44->setText(QCoreApplication::translate("EditLibraryDialog", "Min NG width", nullptr));
        label_45->setText(QCoreApplication::translate("EditLibraryDialog", "Max NG width", nullptr));
        label_46->setText(QCoreApplication::translate("EditLibraryDialog", "Continuous dots", nullptr));
        checkBoxDynamicBinarize->setText(QCoreApplication::translate("EditLibraryDialog", "DynamicBinarize", nullptr));
        pushButton->setText(QCoreApplication::translate("EditLibraryDialog", "Close", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditLibraryDialog", "Save New", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditLibraryDialog", "Library Name", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditLibraryDialog", "Clear new", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditLibraryDialog", "12345", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditLibraryDialog", "Update", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditLibraryDialog", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLibraryDialog: public Ui_EditLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLIBRARYDIALOG_H
