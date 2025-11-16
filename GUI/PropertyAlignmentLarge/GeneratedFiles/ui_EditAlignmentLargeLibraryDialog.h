/********************************************************************************
** Form generated from reading UI file 'EditAlignmentLargeLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITALIGNMENTLARGELIBRARYDIALOG_H
#define UI_EDITALIGNMENTLARGELIBRARYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditAlignmentLargeLibraryDialog
{
public:
    QLabel *label_9;
    QPushButton *ButtonLibSave;
    QPushButton *pushButtonClose;
    QFrame *framePickLayer;
    QPushButton *ButtonLibDelete;
    QPushButton *ButtonLibNew;
    QLineEdit *EditLibName;
    QFrame *frameLibFolder;
    QLineEdit *EditLibID;
    QLabel *label_4;
    QPushButton *ButtonLibSaveNew;
    QTableWidget *tableWidgetLibList;
    QLabel *label_10;
    QFrame *frameGenLayer;
    QTabWidget *tabWidget;
    QWidget *tab;
    QCheckBox *checkBoxGenerateBitBuff;
    QCheckBox *checkBoxGenerateArea;
    QCheckBox *checkBoxGenerateMark;
    QGroupBox *groupBox;
    QRadioButton *radioButtonPriorityHigh;
    QRadioButton *radioButtonPriorityMiddle;
    QRadioButton *radioButtonPriorityLow;
    QRadioButton *radioButtonPriorityLGlobal;
    QLabel *label_13;
    QLabel *label_14;
    QSpinBox *spinBoxMinGenerationAreaDots;
    QSpinBox *spinBoxMinGenerationMarkDots;
    QWidget *tab_2;
    QLabel *label_12;
    QCheckBox *checkBoxJudgeWithBrDif;
    QSpinBox *spinBoxMaxCountHLine;
    QFrame *frame_2;
    QLabel *label_5;
    QLabel *label_7;
    QSpinBox *EditMoveDot2;
    QSpinBox *EditMoveDotY2;
    QLabel *label_8;
    QLabel *label_11;
    QCheckBox *checkBoxUsageGlobal;
    QFrame *frame;
    QLabel *label_3;
    QSpinBox *EditMoveDotY;
    QSpinBox *EditMoveDot;
    QLabel *label;
    QLabel *label_6;
    QSpinBox *spinBoxMaxCountVLine;

    void setupUi(QDialog *EditAlignmentLargeLibraryDialog)
    {
        if (EditAlignmentLargeLibraryDialog->objectName().isEmpty())
            EditAlignmentLargeLibraryDialog->setObjectName("EditAlignmentLargeLibraryDialog");
        EditAlignmentLargeLibraryDialog->resize(659, 584);
        label_9 = new QLabel(EditAlignmentLargeLibraryDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(210, 90, 431, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignCenter);
        ButtonLibSave = new QPushButton(EditAlignmentLargeLibraryDialog);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(510, 500, 121, 31));
        QFont font;
        font.setPointSize(11);
        ButtonLibSave->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon);
        pushButtonClose = new QPushButton(EditAlignmentLargeLibraryDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(510, 540, 121, 31));
        pushButtonClose->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon1);
        framePickLayer = new QFrame(EditAlignmentLargeLibraryDialog);
        framePickLayer->setObjectName("framePickLayer");
        framePickLayer->setGeometry(QRect(210, 60, 431, 28));
        framePickLayer->setFrameShape(QFrame::NoFrame);
        framePickLayer->setFrameShadow(QFrame::Plain);
        ButtonLibDelete = new QPushButton(EditAlignmentLargeLibraryDialog);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(220, 500, 131, 31));
        ButtonLibDelete->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon2);
        ButtonLibNew = new QPushButton(EditAlignmentLargeLibraryDialog);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(220, 460, 131, 31));
        ButtonLibNew->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon3);
        EditLibName = new QLineEdit(EditAlignmentLargeLibraryDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(340, 0, 301, 31));
        QFont font1;
        font1.setPointSize(12);
        EditLibName->setFont(font1);
        frameLibFolder = new QFrame(EditAlignmentLargeLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 151));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        EditLibID = new QLineEdit(EditAlignmentLargeLibraryDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(260, 0, 81, 31));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        label_4 = new QLabel(EditAlignmentLargeLibraryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(210, 0, 51, 31));
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibSaveNew = new QPushButton(EditAlignmentLargeLibraryDialog);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(360, 500, 141, 31));
        ButtonLibSaveNew->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon4);
        tableWidgetLibList = new QTableWidget(EditAlignmentLargeLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 170, 191, 291));
        tableWidgetLibList->setDragEnabled(true);
        tableWidgetLibList->setDragDropOverwriteMode(true);
        tableWidgetLibList->setDragDropMode(QAbstractItemView::DragOnly);
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_10 = new QLabel(EditAlignmentLargeLibraryDialog);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(210, 40, 431, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setTextFormat(Qt::AutoText);
        label_10->setAlignment(Qt::AlignCenter);
        frameGenLayer = new QFrame(EditAlignmentLargeLibraryDialog);
        frameGenLayer->setObjectName("frameGenLayer");
        frameGenLayer->setGeometry(QRect(210, 110, 431, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);
        tabWidget = new QTabWidget(EditAlignmentLargeLibraryDialog);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(210, 160, 441, 291));
        tab = new QWidget();
        tab->setObjectName("tab");
        checkBoxGenerateBitBuff = new QCheckBox(tab);
        checkBoxGenerateBitBuff->setObjectName("checkBoxGenerateBitBuff");
        checkBoxGenerateBitBuff->setGeometry(QRect(10, 54, 291, 21));
        checkBoxGenerateArea = new QCheckBox(tab);
        checkBoxGenerateArea->setObjectName("checkBoxGenerateArea");
        checkBoxGenerateArea->setGeometry(QRect(10, 10, 291, 21));
        checkBoxGenerateMark = new QCheckBox(tab);
        checkBoxGenerateMark->setObjectName("checkBoxGenerateMark");
        checkBoxGenerateMark->setGeometry(QRect(10, 32, 291, 21));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 80, 381, 111));
        radioButtonPriorityHigh = new QRadioButton(groupBox);
        radioButtonPriorityHigh->setObjectName("radioButtonPriorityHigh");
        radioButtonPriorityHigh->setGeometry(QRect(20, 40, 361, 17));
        radioButtonPriorityHigh->setChecked(false);
        radioButtonPriorityMiddle = new QRadioButton(groupBox);
        radioButtonPriorityMiddle->setObjectName("radioButtonPriorityMiddle");
        radioButtonPriorityMiddle->setGeometry(QRect(20, 60, 361, 17));
        radioButtonPriorityMiddle->setChecked(true);
        radioButtonPriorityLow = new QRadioButton(groupBox);
        radioButtonPriorityLow->setObjectName("radioButtonPriorityLow");
        radioButtonPriorityLow->setGeometry(QRect(20, 80, 361, 17));
        radioButtonPriorityLow->setChecked(false);
        radioButtonPriorityLGlobal = new QRadioButton(groupBox);
        radioButtonPriorityLGlobal->setObjectName("radioButtonPriorityLGlobal");
        radioButtonPriorityLGlobal->setGeometry(QRect(20, 20, 361, 17));
        radioButtonPriorityLGlobal->setChecked(false);
        label_13 = new QLabel(tab);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 200, 191, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setTextFormat(Qt::AutoText);
        label_13->setAlignment(Qt::AlignCenter);
        label_14 = new QLabel(tab);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 230, 191, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setTextFormat(Qt::AutoText);
        label_14->setAlignment(Qt::AlignCenter);
        spinBoxMinGenerationAreaDots = new QSpinBox(tab);
        spinBoxMinGenerationAreaDots->setObjectName("spinBoxMinGenerationAreaDots");
        spinBoxMinGenerationAreaDots->setGeometry(QRect(210, 200, 121, 24));
        spinBoxMinGenerationAreaDots->setMaximum(2000000000);
        spinBoxMinGenerationMarkDots = new QSpinBox(tab);
        spinBoxMinGenerationMarkDots->setObjectName("spinBoxMinGenerationMarkDots");
        spinBoxMinGenerationMarkDots->setGeometry(QRect(210, 230, 121, 24));
        spinBoxMinGenerationMarkDots->setMaximum(2000000000);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        label_12 = new QLabel(tab_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(240, 100, 191, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        checkBoxJudgeWithBrDif = new QCheckBox(tab_2);
        checkBoxJudgeWithBrDif->setObjectName("checkBoxJudgeWithBrDif");
        checkBoxJudgeWithBrDif->setGeometry(QRect(10, 162, 291, 21));
        spinBoxMaxCountHLine = new QSpinBox(tab_2);
        spinBoxMaxCountHLine->setObjectName("spinBoxMaxCountHLine");
        spinBoxMaxCountHLine->setGeometry(QRect(60, 124, 91, 22));
        spinBoxMaxCountHLine->setMinimum(-1);
        spinBoxMaxCountHLine->setMaximum(3);
        spinBoxMaxCountHLine->setValue(-1);
        frame_2 = new QFrame(tab_2);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(220, 12, 211, 71));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 20, 91, 16));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(110, 20, 91, 16));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMoveDot2 = new QSpinBox(frame_2);
        EditMoveDot2->setObjectName("EditMoveDot2");
        EditMoveDot2->setGeometry(QRect(10, 40, 91, 22));
        EditMoveDot2->setMaximum(99999);
        EditMoveDotY2 = new QSpinBox(frame_2);
        EditMoveDotY2->setObjectName("EditMoveDotY2");
        EditMoveDotY2->setGeometry(QRect(110, 40, 91, 22));
        EditMoveDotY2->setMaximum(99999);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 0, 211, 16));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_11 = new QLabel(tab_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(20, 102, 191, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        checkBoxUsageGlobal = new QCheckBox(tab_2);
        checkBoxUsageGlobal->setObjectName("checkBoxUsageGlobal");
        checkBoxUsageGlobal->setGeometry(QRect(10, 190, 121, 21));
        frame = new QFrame(tab_2);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 12, 211, 71));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 20, 91, 16));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMoveDotY = new QSpinBox(frame);
        EditMoveDotY->setObjectName("EditMoveDotY");
        EditMoveDotY->setGeometry(QRect(110, 40, 91, 22));
        EditMoveDotY->setMaximum(99999);
        EditMoveDot = new QSpinBox(frame);
        EditMoveDot->setObjectName("EditMoveDot");
        EditMoveDot->setGeometry(QRect(10, 40, 91, 22));
        EditMoveDot->setMaximum(99999);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 91, 16));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 0, 211, 16));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxMaxCountVLine = new QSpinBox(tab_2);
        spinBoxMaxCountVLine->setObjectName("spinBoxMaxCountVLine");
        spinBoxMaxCountVLine->setGeometry(QRect(290, 122, 91, 22));
        spinBoxMaxCountVLine->setMinimum(-1);
        spinBoxMaxCountVLine->setMaximum(3);
        spinBoxMaxCountVLine->setValue(-1);
        tabWidget->addTab(tab_2, QString());

        retranslateUi(EditAlignmentLargeLibraryDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditAlignmentLargeLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *EditAlignmentLargeLibraryDialog)
    {
        EditAlignmentLargeLibraryDialog->setWindowTitle(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Dialog", nullptr));
        label_9->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Update", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Delete", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Clear new", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Library Name", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "12345", nullptr));
        label_4->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "\345\220\215\347\247\260", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Save New", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Name", nullptr));
        label_10->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "\346\212\275\345\207\272\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        checkBoxGenerateBitBuff->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "GenerateBitBuff", nullptr));
        checkBoxGenerateArea->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "GenerateArea", nullptr));
        checkBoxGenerateMark->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "GenerateMark", nullptr));
        groupBox->setTitle(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Priority", nullptr));
        radioButtonPriorityHigh->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "High( Exp. BGA, special part)", nullptr));
        radioButtonPriorityMiddle->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Middle (General)", nullptr));
        radioButtonPriorityLow->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Low (Only parts fitting)", nullptr));
        radioButtonPriorityLGlobal->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Global alignment (Only for other alignment)", nullptr));
        label_13->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Min generation area", nullptr));
        label_14->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Min generation area", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "\347\224\237\346\210\220", nullptr));
        label_12->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Count of Horizontal line", nullptr));
        checkBoxJudgeWithBrDif->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Judge with brightness difference", nullptr));
        label_5->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "\346\216\242\347\264\242\350\267\235\351\233\242 X", nullptr));
        label_7->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "\346\216\242\347\264\242\350\267\235\351\233\242 Y", nullptr));
        label_8->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "\357\274\222\347\225\252\347\233\256\343\201\256\346\216\242\347\264\242", nullptr));
        label_11->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Count of Horizontal line", nullptr));
        checkBoxUsageGlobal->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "Global usage", nullptr));
        label_3->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "\346\216\242\347\264\242\350\267\235\351\233\242 Y", nullptr));
        label->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "\346\216\242\347\264\242\350\267\235\351\233\242 X", nullptr));
        label_6->setText(QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "\346\234\200\345\210\235\343\201\256\346\216\242\347\264\242", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("EditAlignmentLargeLibraryDialog", "\346\244\234\346\237\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditAlignmentLargeLibraryDialog: public Ui_EditAlignmentLargeLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITALIGNMENTLARGELIBRARYDIALOG_H
