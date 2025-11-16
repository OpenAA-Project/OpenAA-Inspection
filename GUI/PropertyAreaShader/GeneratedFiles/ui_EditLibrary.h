/********************************************************************************
** Form generated from reading UI file 'EditLibrary.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLIBRARY_H
#define UI_EDITLIBRARY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
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

class Ui_EditLibrary
{
public:
    QPushButton *ButtonLibSave;
    QLabel *label_4;
    QPushButton *ButtonLibDelete;
    QLineEdit *EditLibName;
    QTableWidget *tableWidgetLibList;
    QFrame *frameLibFolder;
    QPushButton *ButtonLibSaveNew;
    QPushButton *ButtonLibNew;
    QPushButton *pushButton;
    QLineEdit *EditLibID;
    QFrame *frame;
    QSpinBox *EditPickupL;
    QLabel *label_35;
    QSpinBox *EditMinSize;
    QLabel *label_29;
    QSpinBox *EditPriority;
    QSpinBox *EditMaxSize;
    QSpinBox *EditMaxDot;
    QSpinBox *EditMinDot;
    QLabel *label_26;
    QLabel *label_28;
    QLabel *label_31;
    QSpinBox *EditShrinkDot;
    QLabel *label_27;
    QLabel *label_36;
    QLabel *label_32;
    QSpinBox *EditPickupH;
    QCheckBox *checkBoxGenerateOverlap;
    QFrame *frame_2;
    QSpinBox *spinBoxCellSize;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxAverage;
    QLabel *label_6;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBoxAdoptRate;
    QCheckBox *checkBoxFixed;
    QLabel *label_5;
    QLabel *label;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBoxSigma;
    QGroupBox *groupBox;
    QRadioButton *radioButtonPreProcess;
    QRadioButton *radioButtonPostProcess;
    QLabel *label_8;
    QFrame *framePickLayer;
    QLabel *label_9;
    QFrame *frameGenLayer;

    void setupUi(QDialog *EditLibrary)
    {
        if (EditLibrary->objectName().isEmpty())
            EditLibrary->setObjectName("EditLibrary");
        EditLibrary->resize(398, 769);
        ButtonLibSave = new QPushButton(EditLibrary);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(300, 700, 81, 31));
        QFont font;
        font.setPointSize(11);
        ButtonLibSave->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon);
        label_4 = new QLabel(EditLibrary);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 230, 51, 31));
        QFont font1;
        font1.setPointSize(12);
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibDelete = new QPushButton(EditLibrary);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(110, 700, 81, 31));
        ButtonLibDelete->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon1);
        EditLibName = new QLineEdit(EditLibrary);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 230, 241, 31));
        EditLibName->setFont(font1);
        tableWidgetLibList = new QTableWidget(EditLibrary);
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
        frameLibFolder = new QFrame(EditLibrary);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 201, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonLibSaveNew = new QPushButton(EditLibrary);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(200, 700, 91, 31));
        ButtonLibSaveNew->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon2);
        ButtonLibNew = new QPushButton(EditLibrary);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(10, 700, 91, 31));
        ButtonLibNew->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon3);
        pushButton = new QPushButton(EditLibrary);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(300, 730, 81, 31));
        pushButton->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon4);
        EditLibID = new QLineEdit(EditLibrary);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 230, 81, 31));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        frame = new QFrame(EditLibrary);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 370, 371, 171));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        EditPickupL = new QSpinBox(frame);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(130, 30, 61, 22));
        EditPickupL->setMaximum(255);
        label_35 = new QLabel(frame);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(210, 60, 81, 21));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Sunken);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinSize = new QSpinBox(frame);
        EditMinSize->setObjectName("EditMinSize");
        EditMinSize->setGeometry(QRect(290, 60, 71, 22));
        EditMinSize->setMaximum(999999);
        label_29 = new QLabel(frame);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(10, 140, 121, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPriority = new QSpinBox(frame);
        EditPriority->setObjectName("EditPriority");
        EditPriority->setGeometry(QRect(130, 140, 61, 22));
        EditPriority->setMaximum(255);
        EditMaxSize = new QSpinBox(frame);
        EditMaxSize->setObjectName("EditMaxSize");
        EditMaxSize->setGeometry(QRect(290, 80, 71, 22));
        EditMaxSize->setMaximum(999999);
        EditMaxDot = new QSpinBox(frame);
        EditMaxDot->setObjectName("EditMaxDot");
        EditMaxDot->setGeometry(QRect(120, 80, 71, 22));
        EditMaxDot->setMaximum(99999999);
        EditMinDot = new QSpinBox(frame);
        EditMinDot->setObjectName("EditMinDot");
        EditMinDot->setGeometry(QRect(120, 60, 71, 22));
        EditMinDot->setMaximum(999999);
        label_26 = new QLabel(frame);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(40, 110, 131, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_28 = new QLabel(frame);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(40, 80, 81, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_31 = new QLabel(frame);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(10, 10, 121, 21));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditShrinkDot = new QSpinBox(frame);
        EditShrinkDot->setObjectName("EditShrinkDot");
        EditShrinkDot->setGeometry(QRect(170, 110, 61, 22));
        EditShrinkDot->setMaximum(255);
        label_27 = new QLabel(frame);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(40, 60, 81, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_36 = new QLabel(frame);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(210, 80, 81, 21));
        label_36->setFrameShape(QFrame::Panel);
        label_36->setFrameShadow(QFrame::Sunken);
        label_36->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_32 = new QLabel(frame);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(10, 30, 121, 21));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupH = new QSpinBox(frame);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(130, 10, 61, 22));
        EditPickupH->setMaximum(255);
        checkBoxGenerateOverlap = new QCheckBox(frame);
        checkBoxGenerateOverlap->setObjectName("checkBoxGenerateOverlap");
        checkBoxGenerateOverlap->setGeometry(QRect(210, 140, 151, 17));
        frame_2 = new QFrame(EditLibrary);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 550, 371, 141));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        spinBoxCellSize = new QSpinBox(frame_2);
        spinBoxCellSize->setObjectName("spinBoxCellSize");
        spinBoxCellSize->setGeometry(QRect(90, 10, 61, 22));
        spinBoxCellSize->setMaximum(999999);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(200, 10, 81, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxAverage = new QDoubleSpinBox(frame_2);
        doubleSpinBoxAverage->setObjectName("doubleSpinBoxAverage");
        doubleSpinBoxAverage->setGeometry(QRect(99, 70, 81, 22));
        doubleSpinBoxAverage->setMaximum(256.000000000000000);
        label_6 = new QLabel(frame_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(100, 30, 211, 31));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(341, 10, 20, 20));
        doubleSpinBoxAdoptRate = new QDoubleSpinBox(frame_2);
        doubleSpinBoxAdoptRate->setObjectName("doubleSpinBoxAdoptRate");
        doubleSpinBoxAdoptRate->setGeometry(QRect(280, 10, 61, 22));
        doubleSpinBoxAdoptRate->setMaximum(100.000000000000000);
        checkBoxFixed = new QCheckBox(frame_2);
        checkBoxFixed->setObjectName("checkBoxFixed");
        checkBoxFixed->setGeometry(QRect(10, 40, 101, 17));
        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(9, 70, 81, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(frame_2);
        label->setObjectName("label");
        label->setGeometry(QRect(9, 10, 81, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 100, 81, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxSigma = new QDoubleSpinBox(frame_2);
        doubleSpinBoxSigma->setObjectName("doubleSpinBoxSigma");
        doubleSpinBoxSigma->setGeometry(QRect(99, 100, 81, 22));
        doubleSpinBoxSigma->setMaximum(1000.000000000000000);
        groupBox = new QGroupBox(frame_2);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(199, 70, 161, 61));
        radioButtonPreProcess = new QRadioButton(groupBox);
        radioButtonPreProcess->setObjectName("radioButtonPreProcess");
        radioButtonPreProcess->setGeometry(QRect(10, 10, 141, 17));
        radioButtonPreProcess->setChecked(true);
        radioButtonPostProcess = new QRadioButton(groupBox);
        radioButtonPostProcess->setObjectName("radioButtonPostProcess");
        radioButtonPostProcess->setGeometry(QRect(10, 30, 141, 17));
        label_8 = new QLabel(EditLibrary);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 270, 371, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setTextFormat(Qt::AutoText);
        label_8->setAlignment(Qt::AlignCenter);
        framePickLayer = new QFrame(EditLibrary);
        framePickLayer->setObjectName("framePickLayer");
        framePickLayer->setGeometry(QRect(10, 290, 371, 28));
        framePickLayer->setFrameShape(QFrame::NoFrame);
        framePickLayer->setFrameShadow(QFrame::Plain);
        label_9 = new QLabel(EditLibrary);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 320, 371, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignCenter);
        frameGenLayer = new QFrame(EditLibrary);
        frameGenLayer->setObjectName("frameGenLayer");
        frameGenLayer->setGeometry(QRect(10, 340, 371, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);

        retranslateUi(EditLibrary);

        QMetaObject::connectSlotsByName(EditLibrary);
    } // setupUi

    void retranslateUi(QDialog *EditLibrary)
    {
        EditLibrary->setWindowTitle(QCoreApplication::translate("EditLibrary", "EditLibrary", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditLibrary", "Update", nullptr));
        label_4->setText(QCoreApplication::translate("EditLibrary", "\345\220\215\347\247\260", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditLibrary", "Delete", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditLibrary", "Library Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditLibrary", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditLibrary", "Name", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditLibrary", "Save New", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditLibrary", "Clear new", nullptr));
        pushButton->setText(QCoreApplication::translate("EditLibrary", "\351\226\211\343\201\230\343\202\213", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditLibrary", "12345", nullptr));
        label_35->setText(QCoreApplication::translate("EditLibrary", "\346\234\200\345\260\217\351\225\267\343\201\225", nullptr));
        label_29->setText(QCoreApplication::translate("EditLibrary", "\347\224\237\346\210\220\346\231\202\343\201\256\345\204\252\345\205\210\345\272\246", nullptr));
        label_26->setText(QCoreApplication::translate("EditLibrary", "\345\207\246\347\220\206\351\240\230\345\237\237\343\201\270\343\201\256\345\217\216\347\270\256\351\207\217", nullptr));
        label_28->setText(QCoreApplication::translate("EditLibrary", "\346\234\200\345\244\247\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_31->setText(QCoreApplication::translate("EditLibrary", "\346\212\275\345\207\272\344\270\212\351\231\220\350\274\235\345\272\246", nullptr));
        label_27->setText(QCoreApplication::translate("EditLibrary", "\346\234\200\345\260\217\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_36->setText(QCoreApplication::translate("EditLibrary", "\346\234\200\345\244\247\351\225\267\343\201\225", nullptr));
        label_32->setText(QCoreApplication::translate("EditLibrary", "\346\212\275\345\207\272\344\270\213\351\231\220\350\274\235\345\272\246", nullptr));
        checkBoxGenerateOverlap->setText(QCoreApplication::translate("EditLibrary", "\351\207\215\350\244\207\347\224\237\346\210\220", nullptr));
        label_2->setText(QCoreApplication::translate("EditLibrary", "\346\216\241\347\224\250\347\216\207", nullptr));
        label_6->setText(QCoreApplication::translate("EditLibrary", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS UI Gothic'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\343\203\201\343\202\247\343\203\203\343\202\257\343\201\227\343\201\252\343\201\221\343\202\214\343\201\260\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217\343\201\256\345\271\263\345\235\207\350\274\235\345\272\246\343\200\201</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">\346\250\231\346\272\226\345\201\217\345\267\256\343\201\253\344\270\200\350\207\264\343\201\231\343\202\213\343\202\210\343\201"
                        "\206\343\201\252\345\244\211\346\217\233\343\201\253\343\201\252\343\202\213</p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("EditLibrary", "%", nullptr));
        checkBoxFixed->setText(QCoreApplication::translate("EditLibrary", "\345\233\272\345\256\232\345\200\244", nullptr));
        label_5->setText(QCoreApplication::translate("EditLibrary", "\345\233\272\345\256\232\345\271\263\345\235\207\345\200\244", nullptr));
        label->setText(QCoreApplication::translate("EditLibrary", "\345\207\246\347\220\206\343\202\265\343\202\244\343\202\272", nullptr));
        label_7->setText(QCoreApplication::translate("EditLibrary", "\345\233\272\345\256\232\345\201\217\345\267\256", nullptr));
        groupBox->setTitle(QString());
        radioButtonPreProcess->setText(QCoreApplication::translate("EditLibrary", "\346\244\234\346\237\273\345\207\246\347\220\206\347\224\250", nullptr));
        radioButtonPostProcess->setText(QCoreApplication::translate("EditLibrary", "\350\241\250\347\244\272\347\224\250", nullptr));
        label_8->setText(QCoreApplication::translate("EditLibrary", "\346\212\275\345\207\272\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        label_9->setText(QCoreApplication::translate("EditLibrary", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLibrary: public Ui_EditLibrary {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLIBRARY_H
