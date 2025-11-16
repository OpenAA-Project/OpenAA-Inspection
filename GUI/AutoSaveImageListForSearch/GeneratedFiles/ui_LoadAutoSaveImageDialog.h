/********************************************************************************
** Form generated from reading UI file 'LoadAutoSaveImageDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADAUTOSAVEIMAGEDIALOG_H
#define UI_LOADAUTOSAVEIMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadAutoSaveImageDialog
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QFrame *frame;
    QFrame *frame_2;
    QLabel *label;
    QCheckBox *checkBoxAllDrives;
    QComboBox *comboBoxSelectDrive;
    QTableWidget *tableWidgetFound;
    QFrame *frame_3;
    QDateTimeEdit *dateTimeEditFrom;
    QDateTimeEdit *dateTimeEditTo;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButtonStartSearch;

    void setupUi(QDialog *LoadAutoSaveImageDialog)
    {
        if (LoadAutoSaveImageDialog->objectName().isEmpty())
            LoadAutoSaveImageDialog->setObjectName("LoadAutoSaveImageDialog");
        LoadAutoSaveImageDialog->resize(350, 624);
        pushButtonOK = new QPushButton(LoadAutoSaveImageDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 570, 111, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Load.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(LoadAutoSaveImageDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(220, 570, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        frame = new QFrame(LoadAutoSaveImageDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 331, 541));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 10, 311, 81));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame_2);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 311, 21));
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxAllDrives = new QCheckBox(frame_2);
        checkBoxAllDrives->setObjectName("checkBoxAllDrives");
        checkBoxAllDrives->setGeometry(QRect(10, 20, 221, 18));
        comboBoxSelectDrive = new QComboBox(frame_2);
        comboBoxSelectDrive->addItem(QString());
        comboBoxSelectDrive->setObjectName("comboBoxSelectDrive");
        comboBoxSelectDrive->setGeometry(QRect(10, 50, 111, 22));
        tableWidgetFound = new QTableWidget(frame);
        if (tableWidgetFound->columnCount() < 2)
            tableWidgetFound->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetFound->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetFound->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetFound->setObjectName("tableWidgetFound");
        tableWidgetFound->setGeometry(QRect(10, 180, 311, 351));
        tableWidgetFound->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetFound->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame_3 = new QFrame(frame);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 100, 211, 71));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        dateTimeEditFrom = new QDateTimeEdit(frame_3);
        dateTimeEditFrom->setObjectName("dateTimeEditFrom");
        dateTimeEditFrom->setGeometry(QRect(60, 10, 141, 22));
        dateTimeEditFrom->setCalendarPopup(true);
        dateTimeEditTo = new QDateTimeEdit(frame_3);
        dateTimeEditTo->setObjectName("dateTimeEditTo");
        dateTimeEditTo->setGeometry(QRect(60, 40, 141, 22));
        label_2 = new QLabel(frame_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 51, 21));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(frame_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 40, 51, 21));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonStartSearch = new QPushButton(frame);
        pushButtonStartSearch->setObjectName("pushButtonStartSearch");
        pushButtonStartSearch->setGeometry(QRect(230, 110, 91, 51));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonStartSearch->setIcon(icon2);

        retranslateUi(LoadAutoSaveImageDialog);

        pushButtonStartSearch->setDefault(true);


        QMetaObject::connectSlotsByName(LoadAutoSaveImageDialog);
    } // setupUi

    void retranslateUi(QDialog *LoadAutoSaveImageDialog)
    {
        LoadAutoSaveImageDialog->setWindowTitle(QCoreApplication::translate("LoadAutoSaveImageDialog", "Load AutoSaveImage", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("LoadAutoSaveImageDialog", "Load", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("LoadAutoSaveImageDialog", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("LoadAutoSaveImageDialog", "Drive", nullptr));
        checkBoxAllDrives->setText(QCoreApplication::translate("LoadAutoSaveImageDialog", "All drives", nullptr));
        comboBoxSelectDrive->setItemText(0, QCoreApplication::translate("LoadAutoSaveImageDialog", "D Drive (D:\\)", nullptr));

        QTableWidgetItem *___qtablewidgetitem = tableWidgetFound->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("LoadAutoSaveImageDialog", "Date/Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetFound->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("LoadAutoSaveImageDialog", "MasterID", nullptr));
        label_2->setText(QCoreApplication::translate("LoadAutoSaveImageDialog", "From", nullptr));
        label_3->setText(QCoreApplication::translate("LoadAutoSaveImageDialog", "To", nullptr));
        pushButtonStartSearch->setText(QCoreApplication::translate("LoadAutoSaveImageDialog", "Start search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoadAutoSaveImageDialog: public Ui_LoadAutoSaveImageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADAUTOSAVEIMAGEDIALOG_H
