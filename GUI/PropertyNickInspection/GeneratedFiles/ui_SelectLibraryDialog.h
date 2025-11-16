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
    QTableWidget *tableWidgetLibList;
    QFrame *frameLibFolder;
    QFrame *frame_3;
    QLabel *label_4;
    QTableWidget *tableWidgetSelected;
    QFrame *frame;
    QSpinBox *spinBoxNGPercentage;
    QLabel *label;
    QLabel *label_2;
    QCheckBox *checkBoxEnableWhite;
    QSpinBox *spinBoxRefBrightness;
    QLabel *label_5;
    QFrame *frame_4;
    QSpinBox *spinBoxLimitSize;
    QLabel *label_6;
    QLabel *label_8;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonCancel;
    QLineEdit *EditLibName;
    QLineEdit *EditLibID;
    QLabel *label_7;

    void setupUi(QDialog *SelectLibraryDialog)
    {
        if (SelectLibraryDialog->objectName().isEmpty())
            SelectLibraryDialog->setObjectName("SelectLibraryDialog");
        SelectLibraryDialog->resize(539, 696);
        tableWidgetLibList = new QTableWidget(SelectLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(240, 10, 291, 201));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolder = new QFrame(SelectLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 221, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        frame_3 = new QFrame(SelectLibraryDialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 270, 351, 351));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 0, 351, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        tableWidgetSelected = new QTableWidget(frame_3);
        if (tableWidgetSelected->columnCount() < 3)
            tableWidgetSelected->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetSelected->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetSelected->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetSelected->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        tableWidgetSelected->setObjectName("tableWidgetSelected");
        tableWidgetSelected->setGeometry(QRect(10, 30, 331, 311));
        tableWidgetSelected->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetSelected->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(SelectLibraryDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(370, 440, 161, 161));
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
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 0, 161, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        frame_4 = new QFrame(SelectLibraryDialog);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(370, 270, 161, 161));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        spinBoxLimitSize = new QSpinBox(frame_4);
        spinBoxLimitSize->setObjectName("spinBoxLimitSize");
        spinBoxLimitSize->setGeometry(QRect(10, 50, 131, 24));
        spinBoxLimitSize->setMinimum(1);
        spinBoxLimitSize->setMaximum(100);
        label_6 = new QLabel(frame_4);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 27, 131, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_8 = new QLabel(frame_4);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 0, 161, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter);
        pushButtonSelect = new QPushButton(SelectLibraryDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(110, 640, 121, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSelect->setIcon(icon);
        pushButtonCancel = new QPushButton(SelectLibraryDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(320, 640, 121, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        EditLibName = new QLineEdit(SelectLibraryDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(130, 240, 401, 31));
        QFont font;
        font.setPointSize(12);
        EditLibName->setFont(font);
        EditLibID = new QLineEdit(SelectLibraryDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 240, 71, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        label_7 = new QLabel(SelectLibraryDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 240, 51, 31));
        label_7->setFont(font);
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(SelectLibraryDialog);

        pushButtonSelect->setDefault(true);


        QMetaObject::connectSlotsByName(SelectLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectLibraryDialog)
    {
        SelectLibraryDialog->setWindowTitle(QCoreApplication::translate("SelectLibraryDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectLibraryDialog", "Name", nullptr));
        label_4->setText(QCoreApplication::translate("SelectLibraryDialog", "Selected", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetSelected->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectLibraryDialog", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetSelected->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectLibraryDialog", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetSelected->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SelectLibraryDialog", "Library Name", nullptr));
        label->setText(QCoreApplication::translate("SelectLibraryDialog", "NG Percentage", nullptr));
        label_2->setText(QCoreApplication::translate("SelectLibraryDialog", "Refer Brightness", nullptr));
        checkBoxEnableWhite->setText(QCoreApplication::translate("SelectLibraryDialog", "Enable white", nullptr));
        label_5->setText(QCoreApplication::translate("SelectLibraryDialog", "Jdge", nullptr));
        label_6->setText(QCoreApplication::translate("SelectLibraryDialog", "Limit size", nullptr));
        label_8->setText(QCoreApplication::translate("SelectLibraryDialog", "Generation", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectLibraryDialog", "Select", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectLibraryDialog", "Cancel", nullptr));
        EditLibName->setText(QCoreApplication::translate("SelectLibraryDialog", "Library Name", nullptr));
        EditLibID->setText(QCoreApplication::translate("SelectLibraryDialog", "12345", nullptr));
        label_7->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\220\215\347\247\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibraryDialog: public Ui_SelectLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBRARYDIALOG_H
