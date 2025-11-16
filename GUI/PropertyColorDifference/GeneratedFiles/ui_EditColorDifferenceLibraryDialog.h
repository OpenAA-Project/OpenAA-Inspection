/********************************************************************************
** Form generated from reading UI file 'EditColorDifferenceLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITCOLORDIFFERENCELIBRARYDIALOG_H
#define UI_EDITCOLORDIFFERENCELIBRARYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditColorDifferenceLibraryDialog
{
public:
    QPushButton *ButtonLibSaveNew;
    QFrame *frameLibFolder;
    QLabel *label_4;
    QPushButton *pushButton;
    QPushButton *ButtonLibDelete;
    QPushButton *ButtonLibSave;
    QTableWidget *tableWidgetLibList;
    QLineEdit *EditLibName;
    QPushButton *ButtonLibNew;
    QLineEdit *EditLibID;
    QFrame *frame;
    QToolButton *toolButtonItem;
    QToolButton *toolButtonReference;
    QTabWidget *tabWidget;
    QWidget *tab;
    QDoubleSpinBox *doubleSpinBoxGenDeltaE;
    QLabel *label_61;
    QLabel *label_60;
    QSpinBox *spinBoxMaxLength;
    QLabel *label_62;
    QSpinBox *spinBoxGenBlockResolution;
    QLabel *label_63;
    QSpinBox *spinBoxGenMinArea;
    QLabel *label_64;
    QSpinBox *spinBoxGenMaxArea;
    QDoubleSpinBox *doubleSpinBoxGenMaxVariable;
    QLabel *label_65;
    QDoubleSpinBox *doubleSpinBoxGenMaxBrightDifference;
    QLabel *label_66;
    QLabel *label_67;
    QSpinBox *spinBoxGenSurroundMergin;
    QWidget *tab_2;
    QFrame *frame_4;
    QLabel *label_33;
    QLabel *label_49;
    QDoubleSpinBox *doubleSpinBoxAdoptedRate;
    QDoubleSpinBox *doubleSpinBoxTHDeltaE;
    QLabel *label_52;
    QLabel *label_56;
    QComboBox *comboBoxJudgeMethod;
    QFrame *frame_5;
    QLabel *label_34;
    QLabel *label_50;
    QDoubleSpinBox *doubleSpinBoxdH;
    QDoubleSpinBox *doubleSpinBoxdSL;
    QLabel *label_51;
    QDoubleSpinBox *doubleSpinBoxdSH;
    QLabel *label_53;
    QDoubleSpinBox *doubleSpinBoxdVL;
    QLabel *label_54;
    QDoubleSpinBox *doubleSpinBoxdVH;
    QLabel *label_55;
    QLabel *label_57;
    QCheckBox *checkBoxAdaptAlignment;

    void setupUi(QDialog *EditColorDifferenceLibraryDialog)
    {
        if (EditColorDifferenceLibraryDialog->objectName().isEmpty())
            EditColorDifferenceLibraryDialog->setObjectName("EditColorDifferenceLibraryDialog");
        EditColorDifferenceLibraryDialog->resize(693, 586);
        ButtonLibSaveNew = new QPushButton(EditColorDifferenceLibraryDialog);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(460, 500, 111, 31));
        QFont font;
        font.setPointSize(11);
        ButtonLibSaveNew->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon);
        frameLibFolder = new QFrame(EditColorDifferenceLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 221, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(EditColorDifferenceLibraryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(250, 10, 51, 31));
        QFont font1;
        font1.setPointSize(12);
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButton = new QPushButton(EditColorDifferenceLibraryDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(580, 540, 101, 31));
        pushButton->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon1);
        ButtonLibDelete = new QPushButton(EditColorDifferenceLibraryDialog);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(350, 500, 101, 31));
        ButtonLibDelete->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon2);
        ButtonLibSave = new QPushButton(EditColorDifferenceLibraryDialog);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(580, 500, 101, 31));
        ButtonLibSave->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon3);
        tableWidgetLibList = new QTableWidget(EditColorDifferenceLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 220, 221, 191));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        EditLibName = new QLineEdit(EditColorDifferenceLibraryDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(380, 10, 291, 31));
        EditLibName->setFont(font1);
        ButtonLibNew = new QPushButton(EditColorDifferenceLibraryDialog);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(230, 500, 111, 31));
        ButtonLibNew->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon4);
        EditLibID = new QLineEdit(EditColorDifferenceLibraryDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(300, 10, 81, 31));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        frame = new QFrame(EditColorDifferenceLibraryDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(260, 430, 411, 61));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonItem = new QToolButton(frame);
        toolButtonItem->setObjectName("toolButtonItem");
        toolButtonItem->setGeometry(QRect(0, 10, 161, 41));
        toolButtonItem->setCheckable(true);
        toolButtonItem->setChecked(true);
        toolButtonItem->setAutoExclusive(true);
        toolButtonReference = new QToolButton(frame);
        toolButtonReference->setObjectName("toolButtonReference");
        toolButtonReference->setGeometry(QRect(170, 10, 161, 41));
        toolButtonReference->setCheckable(true);
        toolButtonReference->setAutoExclusive(true);
        tabWidget = new QTabWidget(EditColorDifferenceLibraryDialog);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(240, 60, 441, 361));
        tab = new QWidget();
        tab->setObjectName("tab");
        doubleSpinBoxGenDeltaE = new QDoubleSpinBox(tab);
        doubleSpinBoxGenDeltaE->setObjectName("doubleSpinBoxGenDeltaE");
        doubleSpinBoxGenDeltaE->setGeometry(QRect(270, 10, 101, 24));
        QFont font2;
        font2.setPointSize(9);
        doubleSpinBoxGenDeltaE->setFont(font2);
        doubleSpinBoxGenDeltaE->setDecimals(3);
        doubleSpinBoxGenDeltaE->setMaximum(100.000000000000000);
        label_61 = new QLabel(tab);
        label_61->setObjectName("label_61");
        label_61->setGeometry(QRect(20, 40, 241, 24));
        label_61->setFont(font2);
        label_61->setFrameShape(QFrame::Panel);
        label_61->setFrameShadow(QFrame::Sunken);
        label_61->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_60 = new QLabel(tab);
        label_60->setObjectName("label_60");
        label_60->setGeometry(QRect(20, 10, 241, 24));
        label_60->setFrameShape(QFrame::Panel);
        label_60->setFrameShadow(QFrame::Sunken);
        label_60->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxMaxLength = new QSpinBox(tab);
        spinBoxMaxLength->setObjectName("spinBoxMaxLength");
        spinBoxMaxLength->setGeometry(QRect(270, 40, 101, 24));
        spinBoxMaxLength->setMaximum(99999999);
        label_62 = new QLabel(tab);
        label_62->setObjectName("label_62");
        label_62->setGeometry(QRect(20, 80, 241, 24));
        label_62->setFont(font2);
        label_62->setFrameShape(QFrame::Panel);
        label_62->setFrameShadow(QFrame::Sunken);
        label_62->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxGenBlockResolution = new QSpinBox(tab);
        spinBoxGenBlockResolution->setObjectName("spinBoxGenBlockResolution");
        spinBoxGenBlockResolution->setGeometry(QRect(270, 80, 101, 24));
        spinBoxGenBlockResolution->setMaximum(99999999);
        label_63 = new QLabel(tab);
        label_63->setObjectName("label_63");
        label_63->setGeometry(QRect(20, 110, 241, 24));
        label_63->setFont(font2);
        label_63->setFrameShape(QFrame::Panel);
        label_63->setFrameShadow(QFrame::Sunken);
        label_63->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxGenMinArea = new QSpinBox(tab);
        spinBoxGenMinArea->setObjectName("spinBoxGenMinArea");
        spinBoxGenMinArea->setGeometry(QRect(270, 110, 101, 24));
        spinBoxGenMinArea->setMaximum(99999999);
        label_64 = new QLabel(tab);
        label_64->setObjectName("label_64");
        label_64->setGeometry(QRect(20, 140, 241, 24));
        label_64->setFont(font2);
        label_64->setFrameShape(QFrame::Panel);
        label_64->setFrameShadow(QFrame::Sunken);
        label_64->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxGenMaxArea = new QSpinBox(tab);
        spinBoxGenMaxArea->setObjectName("spinBoxGenMaxArea");
        spinBoxGenMaxArea->setGeometry(QRect(270, 140, 101, 24));
        spinBoxGenMaxArea->setMaximum(999999999);
        doubleSpinBoxGenMaxVariable = new QDoubleSpinBox(tab);
        doubleSpinBoxGenMaxVariable->setObjectName("doubleSpinBoxGenMaxVariable");
        doubleSpinBoxGenMaxVariable->setGeometry(QRect(270, 170, 101, 24));
        doubleSpinBoxGenMaxVariable->setFont(font2);
        doubleSpinBoxGenMaxVariable->setDecimals(3);
        doubleSpinBoxGenMaxVariable->setMaximum(200.000000000000000);
        label_65 = new QLabel(tab);
        label_65->setObjectName("label_65");
        label_65->setGeometry(QRect(20, 170, 241, 24));
        label_65->setFrameShape(QFrame::Panel);
        label_65->setFrameShadow(QFrame::Sunken);
        label_65->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxGenMaxBrightDifference = new QDoubleSpinBox(tab);
        doubleSpinBoxGenMaxBrightDifference->setObjectName("doubleSpinBoxGenMaxBrightDifference");
        doubleSpinBoxGenMaxBrightDifference->setGeometry(QRect(270, 200, 101, 24));
        doubleSpinBoxGenMaxBrightDifference->setFont(font2);
        doubleSpinBoxGenMaxBrightDifference->setDecimals(3);
        doubleSpinBoxGenMaxBrightDifference->setMaximum(200.000000000000000);
        label_66 = new QLabel(tab);
        label_66->setObjectName("label_66");
        label_66->setGeometry(QRect(20, 200, 241, 24));
        label_66->setFrameShape(QFrame::Panel);
        label_66->setFrameShadow(QFrame::Sunken);
        label_66->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_67 = new QLabel(tab);
        label_67->setObjectName("label_67");
        label_67->setGeometry(QRect(20, 230, 241, 24));
        label_67->setFont(font2);
        label_67->setFrameShape(QFrame::Panel);
        label_67->setFrameShadow(QFrame::Sunken);
        label_67->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxGenSurroundMergin = new QSpinBox(tab);
        spinBoxGenSurroundMergin->setObjectName("spinBoxGenSurroundMergin");
        spinBoxGenSurroundMergin->setGeometry(QRect(270, 230, 101, 24));
        spinBoxGenSurroundMergin->setMaximum(999999999);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        frame_4 = new QFrame(tab_2);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 10, 411, 111));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Sunken);
        label_33 = new QLabel(frame_4);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(0, 0, 31, 111));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Raised);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_33->setIndent(1);
        label_49 = new QLabel(frame_4);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(50, 10, 241, 24));
        label_49->setFrameShape(QFrame::Panel);
        label_49->setFrameShadow(QFrame::Sunken);
        label_49->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxAdoptedRate = new QDoubleSpinBox(frame_4);
        doubleSpinBoxAdoptedRate->setObjectName("doubleSpinBoxAdoptedRate");
        doubleSpinBoxAdoptedRate->setGeometry(QRect(300, 10, 101, 24));
        doubleSpinBoxAdoptedRate->setMaximum(100.000000000000000);
        doubleSpinBoxTHDeltaE = new QDoubleSpinBox(frame_4);
        doubleSpinBoxTHDeltaE->setObjectName("doubleSpinBoxTHDeltaE");
        doubleSpinBoxTHDeltaE->setGeometry(QRect(300, 70, 101, 24));
        doubleSpinBoxTHDeltaE->setFont(font2);
        doubleSpinBoxTHDeltaE->setDecimals(3);
        doubleSpinBoxTHDeltaE->setMaximum(100.000000000000000);
        label_52 = new QLabel(frame_4);
        label_52->setObjectName("label_52");
        label_52->setGeometry(QRect(50, 70, 241, 24));
        label_52->setFont(font2);
        label_52->setFrameShape(QFrame::Panel);
        label_52->setFrameShadow(QFrame::Sunken);
        label_52->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_56 = new QLabel(frame_4);
        label_56->setObjectName("label_56");
        label_56->setGeometry(QRect(50, 40, 111, 24));
        label_56->setFont(font2);
        label_56->setFrameShape(QFrame::Panel);
        label_56->setFrameShadow(QFrame::Sunken);
        label_56->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        comboBoxJudgeMethod = new QComboBox(frame_4);
        comboBoxJudgeMethod->addItem(QString());
        comboBoxJudgeMethod->addItem(QString());
        comboBoxJudgeMethod->addItem(QString());
        comboBoxJudgeMethod->setObjectName("comboBoxJudgeMethod");
        comboBoxJudgeMethod->setGeometry(QRect(170, 40, 231, 24));
        frame_5 = new QFrame(tab_2);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 130, 411, 161));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Sunken);
        label_34 = new QLabel(frame_5);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(0, 0, 31, 161));
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Raised);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_34->setIndent(1);
        label_50 = new QLabel(frame_5);
        label_50->setObjectName("label_50");
        label_50->setGeometry(QRect(50, 10, 241, 24));
        label_50->setFrameShape(QFrame::Panel);
        label_50->setFrameShadow(QFrame::Sunken);
        label_50->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxdH = new QDoubleSpinBox(frame_5);
        doubleSpinBoxdH->setObjectName("doubleSpinBoxdH");
        doubleSpinBoxdH->setGeometry(QRect(300, 10, 101, 24));
        doubleSpinBoxdH->setMaximum(100.000000000000000);
        doubleSpinBoxdSL = new QDoubleSpinBox(frame_5);
        doubleSpinBoxdSL->setObjectName("doubleSpinBoxdSL");
        doubleSpinBoxdSL->setGeometry(QRect(300, 40, 101, 24));
        doubleSpinBoxdSL->setMaximum(100.000000000000000);
        label_51 = new QLabel(frame_5);
        label_51->setObjectName("label_51");
        label_51->setGeometry(QRect(50, 40, 241, 24));
        label_51->setFrameShape(QFrame::Panel);
        label_51->setFrameShadow(QFrame::Sunken);
        label_51->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxdSH = new QDoubleSpinBox(frame_5);
        doubleSpinBoxdSH->setObjectName("doubleSpinBoxdSH");
        doubleSpinBoxdSH->setGeometry(QRect(300, 70, 101, 24));
        doubleSpinBoxdSH->setMaximum(100.000000000000000);
        label_53 = new QLabel(frame_5);
        label_53->setObjectName("label_53");
        label_53->setGeometry(QRect(50, 70, 241, 24));
        label_53->setFrameShape(QFrame::Panel);
        label_53->setFrameShadow(QFrame::Sunken);
        label_53->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxdVL = new QDoubleSpinBox(frame_5);
        doubleSpinBoxdVL->setObjectName("doubleSpinBoxdVL");
        doubleSpinBoxdVL->setGeometry(QRect(300, 100, 101, 24));
        doubleSpinBoxdVL->setMaximum(100.000000000000000);
        label_54 = new QLabel(frame_5);
        label_54->setObjectName("label_54");
        label_54->setGeometry(QRect(50, 100, 241, 24));
        label_54->setFrameShape(QFrame::Panel);
        label_54->setFrameShadow(QFrame::Sunken);
        label_54->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxdVH = new QDoubleSpinBox(frame_5);
        doubleSpinBoxdVH->setObjectName("doubleSpinBoxdVH");
        doubleSpinBoxdVH->setGeometry(QRect(300, 130, 101, 24));
        doubleSpinBoxdVH->setMaximum(100.000000000000000);
        label_55 = new QLabel(frame_5);
        label_55->setObjectName("label_55");
        label_55->setGeometry(QRect(50, 130, 241, 24));
        label_55->setFrameShape(QFrame::Panel);
        label_55->setFrameShadow(QFrame::Sunken);
        label_55->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_57 = new QLabel(tab_2);
        label_57->setObjectName("label_57");
        label_57->setGeometry(QRect(60, 300, 241, 24));
        label_57->setFont(font2);
        label_57->setFrameShape(QFrame::Panel);
        label_57->setFrameShadow(QFrame::Sunken);
        label_57->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxAdaptAlignment = new QCheckBox(tab_2);
        checkBoxAdaptAlignment->setObjectName("checkBoxAdaptAlignment");
        checkBoxAdaptAlignment->setGeometry(QRect(310, 300, 71, 21));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(EditColorDifferenceLibraryDialog);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(EditColorDifferenceLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *EditColorDifferenceLibraryDialog)
    {
        EditColorDifferenceLibraryDialog->setWindowTitle(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "Dialog", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "Save New", nullptr));
        label_4->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\345\220\215\347\247\260", nullptr));
        pushButton->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "Delete", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "Update", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "Name", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "Library Name", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "Clear new", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "12345", nullptr));
        toolButtonItem->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\351\200\232\345\270\270\350\211\262\350\252\277\351\240\230\345\237\237", nullptr));
        toolButtonReference->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\345\217\202\347\205\247\351\240\230\345\237\237", nullptr));
        label_61->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272\357\274\210\351\225\267\343\201\225\357\274\211", nullptr));
        label_60->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\351\240\230\345\237\237\347\224\237\346\210\220\343\201\256\316\224E\347\257\204\345\233\262", nullptr));
        label_62->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\345\210\206\350\247\243\347\237\251\345\275\242\343\201\256\343\201\256\351\225\267\343\201\225", nullptr));
        label_63->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_64->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_65->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\345\220\214\344\270\200\345\214\226\343\201\247\343\201\215\343\202\213\343\201\260\343\202\211\343\201\244\343\201\215\346\234\200\345\244\247\345\200\244", nullptr));
        label_66->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\345\220\214\344\270\200\345\214\226\343\201\247\343\201\215\343\202\213\350\274\235\345\272\246\345\267\256\346\234\200\345\244\247\345\200\244", nullptr));
        label_67->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\345\217\216\347\270\256\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\347\224\237\346\210\220", nullptr));
        label_33->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "<html><head/><body><p>\346\244\234</p><p>\346\237\273</p></body></html>", nullptr));
        label_49->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\346\216\241\347\224\250\347\216\207(%)", nullptr));
        label_52->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\316\224E\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        label_56->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\345\210\244\345\256\232\346\226\271\346\263\225", nullptr));
        comboBoxJudgeMethod->setItemText(0, QCoreApplication::translate("EditColorDifferenceLibraryDialog", "OK/NG\343\202\222\344\275\277\343\201\206", nullptr));
        comboBoxJudgeMethod->setItemText(1, QCoreApplication::translate("EditColorDifferenceLibraryDialog", "DeltaE\343\201\247\345\210\244\345\256\232", nullptr));
        comboBoxJudgeMethod->setItemText(2, QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\346\265\201\345\213\225\343\202\265\343\203\263\343\203\227\343\203\253\343\201\247HSV\345\210\244\345\256\232", nullptr));

        label_34->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "<html><head/><body><p>H</p><p>S</p><p>V</p></body></html>", nullptr));
        label_50->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "H\343\201\256\350\250\261\345\256\271\345\267\256\347\225\260", nullptr));
        label_51->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "S\343\201\256\344\270\255\345\277\203\345\201\264\343\201\256\350\250\261\345\256\271\345\267\256\347\225\260", nullptr));
        label_53->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "S\343\201\256\345\244\226\345\201\264\343\201\256\350\250\261\345\256\271\345\267\256\347\225\260", nullptr));
        label_54->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "V\343\201\256\346\232\227\345\201\264\343\201\256\350\250\261\345\256\271\345\267\256\347\225\260", nullptr));
        label_55->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "V\343\201\256\346\230\216\345\201\264\343\201\256\350\250\261\345\256\271\345\267\256\347\225\260", nullptr));
        label_57->setText(QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\344\275\215\347\275\256\345\220\210\343\202\217\343\201\233\343\201\247\347\247\273\345\213\225\343\201\231\343\202\213", nullptr));
        checkBoxAdaptAlignment->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("EditColorDifferenceLibraryDialog", "\346\244\234\346\237\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditColorDifferenceLibraryDialog: public Ui_EditColorDifferenceLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITCOLORDIFFERENCELIBRARYDIALOG_H
