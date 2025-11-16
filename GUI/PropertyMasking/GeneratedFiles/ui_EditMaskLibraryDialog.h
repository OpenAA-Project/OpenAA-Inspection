/********************************************************************************
** Form generated from reading UI file 'EditMaskLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITMASKLIBRARYDIALOG_H
#define UI_EDITMASKLIBRARYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditMaskLibraryDialog
{
public:
    QTableWidget *tableWidgetLibList;
    QFrame *frame;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxLibID;
    QLineEdit *lineEditLibName;
    QGroupBox *groupBox;
    QRadioButton *radioButtonEffective;
    QRadioButton *radioButtonIneffective;
    QRadioButton *radioButtonLimitedEffective;
    QRadioButton *radioButtonLimitedIneffective;
    QPushButton *pushButtonSaveNew;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonColor;
    QFrame *frameLimited;
    QFrame *frame_3;
    QLabel *label_4;
    QTableWidget *tableWidgetSelected;
    QFrame *frame_2;
    QLabel *label_3;
    QComboBox *comboBoxLibTypeSelect;
    QTableWidget *tableWidgetLibListSelect;
    QFrame *frameLibFolderSelect;
    QPushButton *pushButtonSelectButton;
    QFrame *frameLibFolder;
    QPushButton *pushButtonClose;
    QLabel *label_5;

    void setupUi(QDialog *EditMaskLibraryDialog)
    {
        if (EditMaskLibraryDialog->objectName().isEmpty())
            EditMaskLibraryDialog->setObjectName("EditMaskLibraryDialog");
        EditMaskLibraryDialog->resize(946, 600);
        tableWidgetLibList = new QTableWidget(EditMaskLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 210, 231, 291));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(EditMaskLibraryDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(250, 10, 691, 541));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 71, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(90, 10, 401, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        spinBoxLibID = new QSpinBox(frame);
        spinBoxLibID->setObjectName("spinBoxLibID");
        spinBoxLibID->setGeometry(QRect(10, 30, 71, 22));
        spinBoxLibID->setReadOnly(true);
        spinBoxLibID->setMaximum(99999999);
        lineEditLibName = new QLineEdit(frame);
        lineEditLibName->setObjectName("lineEditLibName");
        lineEditLibName->setGeometry(QRect(90, 30, 401, 20));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 60, 481, 41));
        radioButtonEffective = new QRadioButton(groupBox);
        radioButtonEffective->setObjectName("radioButtonEffective");
        radioButtonEffective->setGeometry(QRect(10, 10, 71, 17));
        radioButtonEffective->setChecked(true);
        radioButtonIneffective = new QRadioButton(groupBox);
        radioButtonIneffective->setObjectName("radioButtonIneffective");
        radioButtonIneffective->setGeometry(QRect(100, 10, 81, 17));
        radioButtonLimitedEffective = new QRadioButton(groupBox);
        radioButtonLimitedEffective->setObjectName("radioButtonLimitedEffective");
        radioButtonLimitedEffective->setGeometry(QRect(210, 10, 111, 17));
        radioButtonLimitedIneffective = new QRadioButton(groupBox);
        radioButtonLimitedIneffective->setObjectName("radioButtonLimitedIneffective");
        radioButtonLimitedIneffective->setGeometry(QRect(340, 10, 121, 17));
        pushButtonSaveNew = new QPushButton(frame);
        pushButtonSaveNew->setObjectName("pushButtonSaveNew");
        pushButtonSaveNew->setGeometry(QRect(360, 500, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSaveNew->setIcon(icon);
        pushButtonUpdate = new QPushButton(frame);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(480, 500, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon1);
        pushButtonDelete = new QPushButton(frame);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(590, 500, 91, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDelete->setIcon(icon2);
        pushButtonColor = new QPushButton(frame);
        pushButtonColor->setObjectName("pushButtonColor");
        pushButtonColor->setGeometry(QRect(520, 60, 112, 34));
        frameLimited = new QFrame(frame);
        frameLimited->setObjectName("frameLimited");
        frameLimited->setGeometry(QRect(10, 110, 671, 371));
        frameLimited->setFrameShape(QFrame::StyledPanel);
        frameLimited->setFrameShadow(QFrame::Raised);
        frame_3 = new QFrame(frameLimited);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(340, 0, 331, 371));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 0, 331, 21));
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
        tableWidgetSelected->setGeometry(QRect(10, 30, 311, 331));
        tableWidgetSelected->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetSelected->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame_2 = new QFrame(frameLimited);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(0, 0, 261, 371));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 261, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        comboBoxLibTypeSelect = new QComboBox(frame_2);
        comboBoxLibTypeSelect->setObjectName("comboBoxLibTypeSelect");
        comboBoxLibTypeSelect->setGeometry(QRect(10, 30, 241, 22));
        tableWidgetLibListSelect = new QTableWidget(frame_2);
        if (tableWidgetLibListSelect->columnCount() < 2)
            tableWidgetLibListSelect->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetLibListSelect->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetLibListSelect->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        tableWidgetLibListSelect->setObjectName("tableWidgetLibListSelect");
        tableWidgetLibListSelect->setGeometry(QRect(10, 210, 241, 151));
        tableWidgetLibListSelect->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibListSelect->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolderSelect = new QFrame(frame_2);
        frameLibFolderSelect->setObjectName("frameLibFolderSelect");
        frameLibFolderSelect->setGeometry(QRect(10, 60, 241, 141));
        frameLibFolderSelect->setFrameShape(QFrame::StyledPanel);
        frameLibFolderSelect->setFrameShadow(QFrame::Sunken);
        pushButtonSelectButton = new QPushButton(frameLimited);
        pushButtonSelectButton->setObjectName("pushButtonSelectButton");
        pushButtonSelectButton->setGeometry(QRect(280, 180, 51, 31));
        frameLibFolder = new QFrame(EditMaskLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 231, 161));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        pushButtonClose = new QPushButton(EditMaskLibraryDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(840, 560, 91, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon3);
        label_5 = new QLabel(EditMaskLibraryDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 190, 231, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);

        retranslateUi(EditMaskLibraryDialog);

        QMetaObject::connectSlotsByName(EditMaskLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *EditMaskLibraryDialog)
    {
        EditMaskLibraryDialog->setWindowTitle(QCoreApplication::translate("EditMaskLibraryDialog", "Edit Mask Library", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditMaskLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Library name", nullptr));
        label->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Library ID", nullptr));
        label_2->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Library name", nullptr));
        groupBox->setTitle(QString());
        radioButtonEffective->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Effective", nullptr));
        radioButtonIneffective->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Ineffective", nullptr));
        radioButtonLimitedEffective->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Limited effective", nullptr));
        radioButtonLimitedIneffective->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Limited ineffective", nullptr));
        pushButtonSaveNew->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Save new", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Update", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Delete", nullptr));
        pushButtonColor->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Color", nullptr));
        label_4->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Selected", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetSelected->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetSelected->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("EditMaskLibraryDialog", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetSelected->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Library Name", nullptr));
        label_3->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Select library - source", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetLibListSelect->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("EditMaskLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetLibListSelect->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Name", nullptr));
        pushButtonSelectButton->setText(QCoreApplication::translate("EditMaskLibraryDialog", "=>", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Close", nullptr));
        label_5->setText(QCoreApplication::translate("EditMaskLibraryDialog", "Mask library", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditMaskLibraryDialog: public Ui_EditMaskLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITMASKLIBRARYDIALOG_H
