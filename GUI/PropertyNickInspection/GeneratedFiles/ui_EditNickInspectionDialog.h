/********************************************************************************
** Form generated from reading UI file 'EditNickInspectionDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITNICKINSPECTIONDIALOG_H
#define UI_EDITNICKINSPECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditNickInspectionDialog
{
public:
    QTableWidget *tableWidgetLibList;
    QPushButton *ButtonLibSaveNew;
    QPushButton *ButtonLibNew;
    QPushButton *ButtonLibSave;
    QPushButton *pushButtonClose;
    QFrame *frameLibFolder;
    QPushButton *ButtonLibDelete;
    QFrame *frame_2;
    QLabel *label_3;
    QComboBox *comboBoxLibTypeSelect;
    QFrame *frameLibFolderSelect;
    QTableWidget *tableWidgetLibListSelect;
    QPushButton *pushButtonSelectButton;
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
    QLabel *label_9;
    QFrame *frameGenLayer;
    QLabel *label_10;
    QFrame *framePickLayer;
    QLineEdit *EditLibID;
    QLineEdit *EditLibName;
    QLabel *label_7;

    void setupUi(QDialog *EditNickInspectionDialog)
    {
        if (EditNickInspectionDialog->objectName().isEmpty())
            EditNickInspectionDialog->setObjectName("EditNickInspectionDialog");
        EditNickInspectionDialog->resize(1011, 636);
        tableWidgetLibList = new QTableWidget(EditNickInspectionDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 230, 231, 301));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonLibSaveNew = new QPushButton(EditNickInspectionDialog);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(500, 590, 131, 31));
        QFont font;
        font.setPointSize(11);
        ButtonLibSaveNew->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon);
        ButtonLibNew = new QPushButton(EditNickInspectionDialog);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(250, 590, 131, 31));
        ButtonLibNew->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon1);
        ButtonLibSave = new QPushButton(EditNickInspectionDialog);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(640, 590, 121, 31));
        ButtonLibSave->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon2);
        pushButtonClose = new QPushButton(EditNickInspectionDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(900, 590, 101, 31));
        pushButtonClose->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon3);
        frameLibFolder = new QFrame(EditNickInspectionDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 231, 211));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonLibDelete = new QPushButton(EditNickInspectionDialog);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(390, 590, 101, 31));
        ButtonLibDelete->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon4);
        frame_2 = new QFrame(EditNickInspectionDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(250, 50, 271, 521));
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
        comboBoxLibTypeSelect->setGeometry(QRect(10, 30, 251, 22));
        frameLibFolderSelect = new QFrame(frame_2);
        frameLibFolderSelect->setObjectName("frameLibFolderSelect");
        frameLibFolderSelect->setGeometry(QRect(10, 60, 251, 141));
        frameLibFolderSelect->setFrameShape(QFrame::StyledPanel);
        frameLibFolderSelect->setFrameShadow(QFrame::Sunken);
        tableWidgetLibListSelect = new QTableWidget(frame_2);
        if (tableWidgetLibListSelect->columnCount() < 2)
            tableWidgetLibListSelect->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLibListSelect->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibListSelect->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetLibListSelect->setObjectName("tableWidgetLibListSelect");
        tableWidgetLibListSelect->setGeometry(QRect(10, 210, 251, 301));
        tableWidgetLibListSelect->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibListSelect->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelectButton = new QPushButton(EditNickInspectionDialog);
        pushButtonSelectButton->setObjectName("pushButtonSelectButton");
        pushButtonSelectButton->setGeometry(QRect(530, 230, 51, 41));
        frame_3 = new QFrame(EditNickInspectionDialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(590, 50, 391, 241));
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
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetSelected->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetSelected->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetSelected->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        tableWidgetSelected->setObjectName("tableWidgetSelected");
        tableWidgetSelected->setGeometry(QRect(10, 30, 371, 201));
        tableWidgetSelected->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetSelected->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(EditNickInspectionDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(760, 410, 161, 161));
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
        frame_4 = new QFrame(EditNickInspectionDialog);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(590, 410, 161, 161));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        spinBoxLimitSize = new QSpinBox(frame_4);
        spinBoxLimitSize->setObjectName("spinBoxLimitSize");
        spinBoxLimitSize->setGeometry(QRect(10, 50, 131, 24));
        spinBoxLimitSize->setMinimum(1);
        spinBoxLimitSize->setMaximum(99999);
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
        label_9 = new QLabel(EditNickInspectionDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(590, 350, 351, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignCenter);
        frameGenLayer = new QFrame(EditNickInspectionDialog);
        frameGenLayer->setObjectName("frameGenLayer");
        frameGenLayer->setGeometry(QRect(590, 370, 351, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);
        label_10 = new QLabel(EditNickInspectionDialog);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(590, 300, 351, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setTextFormat(Qt::AutoText);
        label_10->setAlignment(Qt::AlignCenter);
        framePickLayer = new QFrame(EditNickInspectionDialog);
        framePickLayer->setObjectName("framePickLayer");
        framePickLayer->setGeometry(QRect(590, 320, 351, 28));
        framePickLayer->setFrameShape(QFrame::NoFrame);
        framePickLayer->setFrameShadow(QFrame::Plain);
        EditLibID = new QLineEdit(EditNickInspectionDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(300, 10, 81, 31));
        QFont font1;
        font1.setPointSize(12);
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        EditLibName = new QLineEdit(EditNickInspectionDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(380, 10, 601, 31));
        EditLibName->setFont(font1);
        label_7 = new QLabel(EditNickInspectionDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(250, 10, 51, 31));
        label_7->setFont(font1);
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(EditNickInspectionDialog);

        QMetaObject::connectSlotsByName(EditNickInspectionDialog);
    } // setupUi

    void retranslateUi(QDialog *EditNickInspectionDialog)
    {
        EditNickInspectionDialog->setWindowTitle(QCoreApplication::translate("EditNickInspectionDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditNickInspectionDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditNickInspectionDialog", "Name", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditNickInspectionDialog", "Save New", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditNickInspectionDialog", "Clear new", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditNickInspectionDialog", "Update", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditNickInspectionDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditNickInspectionDialog", "Delete", nullptr));
        label_3->setText(QCoreApplication::translate("EditNickInspectionDialog", "Select library - source", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibListSelect->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EditNickInspectionDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibListSelect->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("EditNickInspectionDialog", "Name", nullptr));
        pushButtonSelectButton->setText(QCoreApplication::translate("EditNickInspectionDialog", "=>", nullptr));
        label_4->setText(QCoreApplication::translate("EditNickInspectionDialog", "Selected", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetSelected->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("EditNickInspectionDialog", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetSelected->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("EditNickInspectionDialog", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetSelected->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("EditNickInspectionDialog", "Library Name", nullptr));
        label->setText(QCoreApplication::translate("EditNickInspectionDialog", "NG Percentage", nullptr));
        label_2->setText(QCoreApplication::translate("EditNickInspectionDialog", "Refer Brightness", nullptr));
        checkBoxEnableWhite->setText(QCoreApplication::translate("EditNickInspectionDialog", "Enable white", nullptr));
        label_5->setText(QCoreApplication::translate("EditNickInspectionDialog", "Jdge", nullptr));
        label_6->setText(QCoreApplication::translate("EditNickInspectionDialog", "Limit size", nullptr));
        label_8->setText(QCoreApplication::translate("EditNickInspectionDialog", "Generation", nullptr));
        label_9->setText(QCoreApplication::translate("EditNickInspectionDialog", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        label_10->setText(QCoreApplication::translate("EditNickInspectionDialog", "\346\212\275\345\207\272\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditNickInspectionDialog", "12345", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditNickInspectionDialog", "Library Name", nullptr));
        label_7->setText(QCoreApplication::translate("EditNickInspectionDialog", "\345\220\215\347\247\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditNickInspectionDialog: public Ui_EditNickInspectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITNICKINSPECTIONDIALOG_H
