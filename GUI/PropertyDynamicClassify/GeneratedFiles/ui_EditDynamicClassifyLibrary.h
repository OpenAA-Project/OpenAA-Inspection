/********************************************************************************
** Form generated from reading UI file 'EditDynamicClassifyLibrary.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITDYNAMICCLASSIFYLIBRARY_H
#define UI_EDITDYNAMICCLASSIFYLIBRARY_H

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

class Ui_EditDynamicClassifyLibraryClass
{
public:
    QTableWidget *tableWidgetLibList;
    QFrame *frameLibFolder;
    QLineEdit *EditLibName;
    QFrame *frame_15;
    QSpinBox *EditMinBlockSize;
    QLabel *label_58;
    QSpinBox *EditMaxBlockSize;
    QLabel *label_59;
    QSpinBox *EditMinBlockDots;
    QLabel *label_60;
    QSpinBox *EditMaxBlockDots;
    QLabel *label_61;
    QLabel *label_63;
    QLineEdit *EditLibID;
    QFrame *frame_18;
    QLabel *label_68;
    QFrame *frameGenerate;
    QLabel *label_4;
    QFrame *frame_4;
    QSpinBox *EditVariableWidth;
    QSpinBox *EditNoiseSize;
    QLabel *label_16;
    QSpinBox *EditPriority;
    QLabel *label_33;
    QSpinBox *EditShrinkDot;
    QLabel *label_15;
    QLabel *label_17;
    QLabel *label_14;
    QPushButton *ButtonLibSaveNew;
    QPushButton *ButtonLibDelete;
    QPushButton *ButtonLibSave;
    QPushButton *pushButtonClose;
    QPushButton *ButtonLibNew;
    QFrame *frame_16;
    QLabel *label_67;
    QSpinBox *EditOutlineIWidth;
    QSpinBox *EditOverlapInEachArea;
    QLabel *label_64;
    QLabel *label_65;
    QSpinBox *EditOutlineTWidth;
    QLabel *label_66;
    QLabel *label_69;
    QSpinBox *EditOutlineOWidth;
    QFrame *frame_25;
    QLabel *label_86;
    QSpinBox *EditAdjustBlack;
    QSpinBox *EditAdjustWhite;
    QLabel *label_88;
    QLabel *label_89;
    QCheckBox *checkBoxStartupExecute;

    void setupUi(QDialog *EditDynamicClassifyLibraryClass)
    {
        if (EditDynamicClassifyLibraryClass->objectName().isEmpty())
            EditDynamicClassifyLibraryClass->setObjectName("EditDynamicClassifyLibraryClass");
        EditDynamicClassifyLibraryClass->resize(520, 718);
        tableWidgetLibList = new QTableWidget(EditDynamicClassifyLibraryClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 170, 191, 181));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolder = new QFrame(EditDynamicClassifyLibraryClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 151));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        EditLibName = new QLineEdit(EditDynamicClassifyLibraryClass);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(330, 10, 181, 31));
        QFont font;
        font.setPointSize(12);
        EditLibName->setFont(font);
        frame_15 = new QFrame(EditDynamicClassifyLibraryClass);
        frame_15->setObjectName("frame_15");
        frame_15->setGeometry(QRect(220, 190, 291, 111));
        frame_15->setFrameShape(QFrame::StyledPanel);
        frame_15->setFrameShadow(QFrame::Sunken);
        EditMinBlockSize = new QSpinBox(frame_15);
        EditMinBlockSize->setObjectName("EditMinBlockSize");
        EditMinBlockSize->setGeometry(QRect(180, 10, 81, 22));
        EditMinBlockSize->setMaximum(1000000);
        label_58 = new QLabel(frame_15);
        label_58->setObjectName("label_58");
        label_58->setGeometry(QRect(50, 30, 111, 21));
        label_58->setFrameShape(QFrame::Panel);
        label_58->setFrameShadow(QFrame::Sunken);
        label_58->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxBlockSize = new QSpinBox(frame_15);
        EditMaxBlockSize->setObjectName("EditMaxBlockSize");
        EditMaxBlockSize->setGeometry(QRect(180, 30, 81, 22));
        EditMaxBlockSize->setMaximum(1000000);
        label_59 = new QLabel(frame_15);
        label_59->setObjectName("label_59");
        label_59->setGeometry(QRect(50, 10, 111, 21));
        label_59->setFrameShape(QFrame::Panel);
        label_59->setFrameShadow(QFrame::Sunken);
        label_59->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinBlockDots = new QSpinBox(frame_15);
        EditMinBlockDots->setObjectName("EditMinBlockDots");
        EditMinBlockDots->setGeometry(QRect(180, 60, 101, 22));
        EditMinBlockDots->setMaximum(2000000000);
        label_60 = new QLabel(frame_15);
        label_60->setObjectName("label_60");
        label_60->setGeometry(QRect(50, 60, 111, 21));
        label_60->setFrameShape(QFrame::Panel);
        label_60->setFrameShadow(QFrame::Sunken);
        label_60->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxBlockDots = new QSpinBox(frame_15);
        EditMaxBlockDots->setObjectName("EditMaxBlockDots");
        EditMaxBlockDots->setGeometry(QRect(180, 80, 101, 22));
        EditMaxBlockDots->setMaximum(2000000000);
        EditMaxBlockDots->setValue(2000000000);
        label_61 = new QLabel(frame_15);
        label_61->setObjectName("label_61");
        label_61->setGeometry(QRect(50, 80, 111, 21));
        label_61->setFrameShape(QFrame::Panel);
        label_61->setFrameShadow(QFrame::Sunken);
        label_61->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_63 = new QLabel(frame_15);
        label_63->setObjectName("label_63");
        label_63->setGeometry(QRect(0, 0, 31, 111));
        label_63->setFrameShape(QFrame::Panel);
        label_63->setFrameShadow(QFrame::Raised);
        label_63->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_63->setIndent(1);
        EditLibID = new QLineEdit(EditDynamicClassifyLibraryClass);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(280, 10, 51, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        frame_18 = new QFrame(EditDynamicClassifyLibraryClass);
        frame_18->setObjectName("frame_18");
        frame_18->setGeometry(QRect(220, 50, 291, 131));
        frame_18->setFrameShape(QFrame::StyledPanel);
        frame_18->setFrameShadow(QFrame::Sunken);
        label_68 = new QLabel(frame_18);
        label_68->setObjectName("label_68");
        label_68->setGeometry(QRect(0, 0, 31, 131));
        label_68->setFrameShape(QFrame::Panel);
        label_68->setFrameShadow(QFrame::Raised);
        label_68->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_68->setIndent(1);
        frameGenerate = new QFrame(frame_18);
        frameGenerate->setObjectName("frameGenerate");
        frameGenerate->setGeometry(QRect(30, 0, 211, 131));
        frameGenerate->setFrameShape(QFrame::NoFrame);
        frameGenerate->setFrameShadow(QFrame::Raised);
        label_4 = new QLabel(EditDynamicClassifyLibraryClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(230, 10, 51, 31));
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_4 = new QFrame(EditDynamicClassifyLibraryClass);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(220, 310, 291, 101));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Sunken);
        EditVariableWidth = new QSpinBox(frame_4);
        EditVariableWidth->setObjectName("EditVariableWidth");
        EditVariableWidth->setGeometry(QRect(180, 10, 61, 23));
        EditNoiseSize = new QSpinBox(frame_4);
        EditNoiseSize->setObjectName("EditNoiseSize");
        EditNoiseSize->setGeometry(QRect(180, 30, 61, 23));
        QFont font1;
        font1.setPointSize(9);
        EditNoiseSize->setFont(font1);
        label_16 = new QLabel(frame_4);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(50, 70, 111, 21));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPriority = new QSpinBox(frame_4);
        EditPriority->setObjectName("EditPriority");
        EditPriority->setGeometry(QRect(180, 70, 61, 23));
        EditPriority->setFont(font1);
        label_33 = new QLabel(frame_4);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(0, 0, 31, 101));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Raised);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_33->setIndent(1);
        EditShrinkDot = new QSpinBox(frame_4);
        EditShrinkDot->setObjectName("EditShrinkDot");
        EditShrinkDot->setGeometry(QRect(180, 50, 61, 23));
        EditShrinkDot->setFont(font1);
        EditShrinkDot->setMinimum(-99);
        label_15 = new QLabel(frame_4);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(50, 30, 111, 21));
        label_15->setFrameShape(QFrame::Panel);
        label_15->setFrameShadow(QFrame::Sunken);
        label_15->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_17 = new QLabel(frame_4);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(50, 50, 111, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_14 = new QLabel(frame_4);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(50, 10, 111, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibSaveNew = new QPushButton(EditDynamicClassifyLibraryClass);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(330, 640, 91, 31));
        QFont font2;
        font2.setPointSize(11);
        ButtonLibSaveNew->setFont(font2);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon);
        ButtonLibDelete = new QPushButton(EditDynamicClassifyLibraryClass);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(240, 640, 81, 31));
        ButtonLibDelete->setFont(font2);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon1);
        ButtonLibSave = new QPushButton(EditDynamicClassifyLibraryClass);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(430, 640, 81, 31));
        ButtonLibSave->setFont(font2);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon2);
        pushButtonClose = new QPushButton(EditDynamicClassifyLibraryClass);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(430, 680, 81, 31));
        pushButtonClose->setFont(font2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon3);
        ButtonLibNew = new QPushButton(EditDynamicClassifyLibraryClass);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(140, 640, 91, 31));
        ButtonLibNew->setFont(font2);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon4);
        frame_16 = new QFrame(EditDynamicClassifyLibraryClass);
        frame_16->setObjectName("frame_16");
        frame_16->setGeometry(QRect(220, 420, 291, 101));
        frame_16->setFrameShape(QFrame::StyledPanel);
        frame_16->setFrameShadow(QFrame::Sunken);
        label_67 = new QLabel(frame_16);
        label_67->setObjectName("label_67");
        label_67->setGeometry(QRect(0, 0, 31, 101));
        label_67->setFrameShape(QFrame::Panel);
        label_67->setFrameShadow(QFrame::Raised);
        label_67->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_67->setIndent(1);
        EditOutlineIWidth = new QSpinBox(frame_16);
        EditOutlineIWidth->setObjectName("EditOutlineIWidth");
        EditOutlineIWidth->setGeometry(QRect(180, 10, 61, 22));
        EditOutlineIWidth->setMaximum(1000000);
        EditOverlapInEachArea = new QSpinBox(frame_16);
        EditOverlapInEachArea->setObjectName("EditOverlapInEachArea");
        EditOverlapInEachArea->setGeometry(QRect(180, 70, 61, 22));
        EditOverlapInEachArea->setMaximum(1000000);
        label_64 = new QLabel(frame_16);
        label_64->setObjectName("label_64");
        label_64->setGeometry(QRect(50, 70, 111, 21));
        label_64->setFrameShape(QFrame::Panel);
        label_64->setFrameShadow(QFrame::Sunken);
        label_64->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_65 = new QLabel(frame_16);
        label_65->setObjectName("label_65");
        label_65->setGeometry(QRect(50, 30, 111, 21));
        label_65->setFrameShape(QFrame::Panel);
        label_65->setFrameShadow(QFrame::Sunken);
        label_65->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOutlineTWidth = new QSpinBox(frame_16);
        EditOutlineTWidth->setObjectName("EditOutlineTWidth");
        EditOutlineTWidth->setGeometry(QRect(180, 30, 61, 22));
        EditOutlineTWidth->setMaximum(1000000);
        label_66 = new QLabel(frame_16);
        label_66->setObjectName("label_66");
        label_66->setGeometry(QRect(50, 10, 111, 21));
        label_66->setFrameShape(QFrame::Panel);
        label_66->setFrameShadow(QFrame::Sunken);
        label_66->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_69 = new QLabel(frame_16);
        label_69->setObjectName("label_69");
        label_69->setGeometry(QRect(50, 50, 111, 21));
        label_69->setFrameShape(QFrame::Panel);
        label_69->setFrameShadow(QFrame::Sunken);
        label_69->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOutlineOWidth = new QSpinBox(frame_16);
        EditOutlineOWidth->setObjectName("EditOutlineOWidth");
        EditOutlineOWidth->setGeometry(QRect(180, 50, 61, 22));
        EditOutlineOWidth->setMaximum(1000000);
        frame_25 = new QFrame(EditDynamicClassifyLibraryClass);
        frame_25->setObjectName("frame_25");
        frame_25->setGeometry(QRect(220, 530, 291, 61));
        frame_25->setFrameShape(QFrame::StyledPanel);
        frame_25->setFrameShadow(QFrame::Sunken);
        label_86 = new QLabel(frame_25);
        label_86->setObjectName("label_86");
        label_86->setGeometry(QRect(0, 0, 31, 61));
        label_86->setFrameShape(QFrame::Panel);
        label_86->setFrameShadow(QFrame::Raised);
        label_86->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_86->setIndent(1);
        EditAdjustBlack = new QSpinBox(frame_25);
        EditAdjustBlack->setObjectName("EditAdjustBlack");
        EditAdjustBlack->setGeometry(QRect(220, 10, 61, 22));
        EditAdjustBlack->setMaximum(255);
        EditAdjustWhite = new QSpinBox(frame_25);
        EditAdjustWhite->setObjectName("EditAdjustWhite");
        EditAdjustWhite->setGeometry(QRect(220, 30, 61, 22));
        EditAdjustWhite->setMaximum(255);
        label_88 = new QLabel(frame_25);
        label_88->setObjectName("label_88");
        label_88->setGeometry(QRect(40, 30, 181, 21));
        label_88->setFrameShape(QFrame::Panel);
        label_88->setFrameShadow(QFrame::Sunken);
        label_88->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_89 = new QLabel(frame_25);
        label_89->setObjectName("label_89");
        label_89->setGeometry(QRect(40, 10, 181, 21));
        label_89->setFrameShape(QFrame::Panel);
        label_89->setFrameShadow(QFrame::Sunken);
        label_89->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxStartupExecute = new QCheckBox(EditDynamicClassifyLibraryClass);
        checkBoxStartupExecute->setObjectName("checkBoxStartupExecute");
        checkBoxStartupExecute->setGeometry(QRect(300, 600, 211, 18));

        retranslateUi(EditDynamicClassifyLibraryClass);

        QMetaObject::connectSlotsByName(EditDynamicClassifyLibraryClass);
    } // setupUi

    void retranslateUi(QDialog *EditDynamicClassifyLibraryClass)
    {
        EditDynamicClassifyLibraryClass->setWindowTitle(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "EditDynamicClassifyLibrary", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "Name", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "Library Name", nullptr));
        label_58->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_59->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_60->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_61->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_63->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\343\202\265\n"
"\343\202\244\n"
"\343\202\272", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "12345", nullptr));
        label_68->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\350\274\235\n"
"\345\272\246", nullptr));
        label_4->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\345\220\215\347\247\260", nullptr));
        label_16->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\345\204\252\345\205\210\345\272\246", nullptr));
        label_33->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\347\224\237\n"
"\346\210\220", nullptr));
        label_15->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272", nullptr));
        label_17->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\347\270\256\345\260\217\351\207\217", nullptr));
        label_14->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\345\244\211\345\213\225\345\271\205", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "Save New", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "Delete", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "Update", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "Clear new", nullptr));
        label_67->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\347\224\237\n"
"\346\210\220\n"
"\345\271\205", nullptr));
        label_64->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\351\240\230\345\237\237\351\207\215\350\244\207\343\203\211\343\203\203\343\203\210", nullptr));
        label_65->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\350\274\252\351\203\255\357\274\215\351\201\267\347\247\273", nullptr));
        label_66->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\350\274\252\351\203\255\357\274\215\345\206\205\345\201\264", nullptr));
        label_69->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\350\274\252\351\203\255\357\274\215\345\244\226\345\201\264", nullptr));
        label_86->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\350\243\234\n"
"\346\255\243", nullptr));
        label_88->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_89->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        checkBoxStartupExecute->setText(QCoreApplication::translate("EditDynamicClassifyLibraryClass", "\343\203\207\343\203\225\343\202\251\343\203\253\343\203\210\343\201\247\345\256\237\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditDynamicClassifyLibraryClass: public Ui_EditDynamicClassifyLibraryClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITDYNAMICCLASSIFYLIBRARY_H
