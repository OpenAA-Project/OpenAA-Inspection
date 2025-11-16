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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditLibrary
{
public:
    QFrame *frameLibFolder;
    QFrame *frame;
    QLabel *label_37;
    QSpinBox *EditPickupL;
    QLabel *label_35;
    QSpinBox *EditMinSize;
    QLabel *label_34;
    QLabel *label_29;
    QSpinBox *EditPriority;
    QSpinBox *EditStepDot;
    QSpinBox *EditMaxSize;
    QSpinBox *EditMaxDot;
    QSpinBox *EditMinDot;
    QSpinBox *EditSearchBlockWidth;
    QLabel *label_26;
    QLabel *label_28;
    QLabel *label_31;
    QSpinBox *EditShrinkDot;
    QLabel *label_27;
    QLabel *label_36;
    QLabel *label_32;
    QSpinBox *EditPickupH;
    QLabel *label_39;
    QSpinBox *EditLimitDot;
    QCheckBox *checkBoxGenerateOverlap;
    QLabel *label_4;
    QPushButton *ButtonLibDelete;
    QFrame *frame_2;
    QSpinBox *EditSelfSearch;
    QLabel *label_30;
    QDoubleSpinBox *doubleSpinBoxEmphasizeRate;
    QLabel *label_33;
    QSpinBox *EditMaxLineWidth;
    QLabel *label_38;
    QCheckBox *checkBoxExcludeDynamicMask;
    QDoubleSpinBox *doubleSpinBoxStartAngle;
    QLabel *label_40;
    QDoubleSpinBox *doubleSpinBoxEndAngle;
    QLabel *label_41;
    QLabel *label;
    QCheckBox *checkBoxFixedAngle;
    QPushButton *ButtonLibSave;
    QPushButton *ButtonLibNew;
    QLineEdit *EditLibName;
    QPushButton *ButtonLibSaveNew;
    QPushButton *pushButton;
    QLineEdit *EditLibID;
    QTableWidget *tableWidgetLibList;
    QLabel *label_8;
    QFrame *framePickLayer;
    QLabel *label_9;
    QFrame *frameGenLayer;
    QFrame *frameSourceLayer;
    QLabel *label_10;

    void setupUi(QDialog *EditLibrary)
    {
        if (EditLibrary->objectName().isEmpty())
            EditLibrary->setObjectName("EditLibrary");
        EditLibrary->resize(431, 818);
        frameLibFolder = new QFrame(EditLibrary);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 201, 191));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(EditLibrary);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 400, 411, 191));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_37 = new QLabel(frame);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(10, 114, 251, 21));
        label_37->setFrameShape(QFrame::Panel);
        label_37->setFrameShadow(QFrame::Sunken);
        label_37->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupL = new QSpinBox(frame);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(220, 24, 61, 22));
        EditPickupL->setMaximum(255);
        label_35 = new QLabel(frame);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(220, 50, 101, 21));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Sunken);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinSize = new QSpinBox(frame);
        EditMinSize->setObjectName("EditMinSize");
        EditMinSize->setGeometry(QRect(320, 50, 71, 22));
        EditMinSize->setMaximum(999999);
        label_34 = new QLabel(frame);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(200, 140, 141, 21));
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Sunken);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
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
        EditStepDot = new QSpinBox(frame);
        EditStepDot->setObjectName("EditStepDot");
        EditStepDot->setGeometry(QRect(340, 140, 61, 22));
        EditStepDot->setMaximum(255);
        EditMaxSize = new QSpinBox(frame);
        EditMaxSize->setObjectName("EditMaxSize");
        EditMaxSize->setGeometry(QRect(320, 70, 71, 22));
        EditMaxSize->setMaximum(999999);
        EditMaxDot = new QSpinBox(frame);
        EditMaxDot->setObjectName("EditMaxDot");
        EditMaxDot->setGeometry(QRect(140, 70, 71, 22));
        EditMaxDot->setMaximum(99999999);
        EditMinDot = new QSpinBox(frame);
        EditMinDot->setObjectName("EditMinDot");
        EditMinDot->setGeometry(QRect(140, 50, 71, 22));
        EditMinDot->setMaximum(999999);
        EditSearchBlockWidth = new QSpinBox(frame);
        EditSearchBlockWidth->setObjectName("EditSearchBlockWidth");
        EditSearchBlockWidth->setGeometry(QRect(260, 114, 61, 22));
        EditSearchBlockWidth->setMaximum(255);
        label_26 = new QLabel(frame);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(10, 94, 251, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_28 = new QLabel(frame);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(40, 70, 101, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_31 = new QLabel(frame);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(10, 4, 211, 21));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditShrinkDot = new QSpinBox(frame);
        EditShrinkDot->setObjectName("EditShrinkDot");
        EditShrinkDot->setGeometry(QRect(260, 94, 61, 22));
        EditShrinkDot->setMinimum(-255);
        EditShrinkDot->setMaximum(255);
        label_27 = new QLabel(frame);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(40, 50, 101, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_36 = new QLabel(frame);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(220, 70, 101, 21));
        label_36->setFrameShape(QFrame::Panel);
        label_36->setFrameShadow(QFrame::Sunken);
        label_36->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_32 = new QLabel(frame);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(10, 24, 211, 21));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupH = new QSpinBox(frame);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(220, 4, 61, 22));
        EditPickupH->setMaximum(255);
        label_39 = new QLabel(frame);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(10, 160, 121, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLimitDot = new QSpinBox(frame);
        EditLimitDot->setObjectName("EditLimitDot");
        EditLimitDot->setGeometry(QRect(130, 160, 61, 22));
        EditLimitDot->setMaximum(99999);
        checkBoxGenerateOverlap = new QCheckBox(frame);
        checkBoxGenerateOverlap->setObjectName("checkBoxGenerateOverlap");
        checkBoxGenerateOverlap->setGeometry(QRect(200, 160, 201, 17));
        label_4 = new QLabel(EditLibrary);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 210, 51, 31));
        QFont font;
        font.setPointSize(12);
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibDelete = new QPushButton(EditLibrary);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(120, 740, 91, 31));
        QFont font1;
        font1.setPointSize(11);
        ButtonLibDelete->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon);
        frame_2 = new QFrame(EditLibrary);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 590, 411, 141));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        EditSelfSearch = new QSpinBox(frame_2);
        EditSelfSearch->setObjectName("EditSelfSearch");
        EditSelfSearch->setGeometry(QRect(350, 24, 51, 22));
        EditSelfSearch->setMaximum(255);
        label_30 = new QLabel(frame_2);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 4, 121, 21));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxEmphasizeRate = new QDoubleSpinBox(frame_2);
        doubleSpinBoxEmphasizeRate->setObjectName("doubleSpinBoxEmphasizeRate");
        doubleSpinBoxEmphasizeRate->setGeometry(QRect(130, 4, 62, 22));
        doubleSpinBoxEmphasizeRate->setDecimals(4);
        doubleSpinBoxEmphasizeRate->setMinimum(-99.989999999999995);
        label_33 = new QLabel(frame_2);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(10, 24, 121, 21));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Sunken);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxLineWidth = new QSpinBox(frame_2);
        EditMaxLineWidth->setObjectName("EditMaxLineWidth");
        EditMaxLineWidth->setGeometry(QRect(130, 24, 61, 22));
        EditMaxLineWidth->setMaximum(255);
        label_38 = new QLabel(frame_2);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(200, 24, 151, 21));
        label_38->setFrameShape(QFrame::Panel);
        label_38->setFrameShadow(QFrame::Sunken);
        label_38->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxExcludeDynamicMask = new QCheckBox(frame_2);
        checkBoxExcludeDynamicMask->setObjectName("checkBoxExcludeDynamicMask");
        checkBoxExcludeDynamicMask->setGeometry(QRect(20, 50, 261, 17));
        doubleSpinBoxStartAngle = new QDoubleSpinBox(frame_2);
        doubleSpinBoxStartAngle->setObjectName("doubleSpinBoxStartAngle");
        doubleSpinBoxStartAngle->setGeometry(QRect(130, 90, 62, 22));
        doubleSpinBoxStartAngle->setDecimals(4);
        doubleSpinBoxStartAngle->setMinimum(-360.000000000000000);
        doubleSpinBoxStartAngle->setMaximum(360.000000000000000);
        label_40 = new QLabel(frame_2);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(10, 90, 121, 21));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setFrameShadow(QFrame::Sunken);
        label_40->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxEndAngle = new QDoubleSpinBox(frame_2);
        doubleSpinBoxEndAngle->setObjectName("doubleSpinBoxEndAngle");
        doubleSpinBoxEndAngle->setGeometry(QRect(340, 90, 62, 22));
        doubleSpinBoxEndAngle->setDecimals(4);
        doubleSpinBoxEndAngle->setMinimum(-360.000000000000000);
        doubleSpinBoxEndAngle->setMaximum(360.000000000000000);
        label_41 = new QLabel(frame_2);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(220, 90, 121, 21));
        label_41->setFrameShape(QFrame::Panel);
        label_41->setFrameShadow(QFrame::Sunken);
        label_41->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(frame_2);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 120, 281, 16));
        checkBoxFixedAngle = new QCheckBox(frame_2);
        checkBoxFixedAngle->setObjectName("checkBoxFixedAngle");
        checkBoxFixedAngle->setGeometry(QRect(20, 70, 261, 17));
        ButtonLibSave = new QPushButton(EditLibrary);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(330, 740, 91, 31));
        ButtonLibSave->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon1);
        ButtonLibNew = new QPushButton(EditLibrary);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(10, 740, 101, 31));
        ButtonLibNew->setFont(font1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon2);
        EditLibName = new QLineEdit(EditLibrary);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 210, 281, 31));
        EditLibName->setFont(font);
        ButtonLibSaveNew = new QPushButton(EditLibrary);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(220, 740, 101, 31));
        ButtonLibSaveNew->setFont(font1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon3);
        pushButton = new QPushButton(EditLibrary);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(330, 780, 91, 31));
        pushButton->setFont(font1);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon4);
        EditLibID = new QLineEdit(EditLibrary);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 210, 81, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        tableWidgetLibList = new QTableWidget(EditLibrary);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(220, 10, 201, 191));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_8 = new QLabel(EditLibrary);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 250, 411, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setTextFormat(Qt::AutoText);
        label_8->setAlignment(Qt::AlignCenter);
        framePickLayer = new QFrame(EditLibrary);
        framePickLayer->setObjectName("framePickLayer");
        framePickLayer->setGeometry(QRect(10, 270, 411, 28));
        framePickLayer->setFrameShape(QFrame::NoFrame);
        framePickLayer->setFrameShadow(QFrame::Plain);
        label_9 = new QLabel(EditLibrary);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 350, 411, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignCenter);
        frameGenLayer = new QFrame(EditLibrary);
        frameGenLayer->setObjectName("frameGenLayer");
        frameGenLayer->setGeometry(QRect(10, 370, 411, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);
        frameSourceLayer = new QFrame(EditLibrary);
        frameSourceLayer->setObjectName("frameSourceLayer");
        frameSourceLayer->setGeometry(QRect(10, 320, 411, 28));
        frameSourceLayer->setFrameShape(QFrame::NoFrame);
        frameSourceLayer->setFrameShadow(QFrame::Plain);
        label_10 = new QLabel(EditLibrary);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 300, 411, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setTextFormat(Qt::AutoText);
        label_10->setAlignment(Qt::AlignCenter);

        retranslateUi(EditLibrary);

        QMetaObject::connectSlotsByName(EditLibrary);
    } // setupUi

    void retranslateUi(QDialog *EditLibrary)
    {
        EditLibrary->setWindowTitle(QCoreApplication::translate("EditLibrary", "Edit Library", nullptr));
        label_37->setText(QCoreApplication::translate("EditLibrary", "\346\216\242\347\264\242\351\240\230\345\237\237\345\271\205", nullptr));
        label_35->setText(QCoreApplication::translate("EditLibrary", "\346\234\200\345\260\217\351\225\267\343\201\225", nullptr));
        label_34->setText(QCoreApplication::translate("EditLibrary", "\345\210\206\345\211\262\347\265\202\347\253\257\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_29->setText(QCoreApplication::translate("EditLibrary", "\347\224\237\346\210\220\346\231\202\343\201\256\345\204\252\345\205\210\345\272\246", nullptr));
        label_26->setText(QCoreApplication::translate("EditLibrary", "\345\207\246\347\220\206\351\240\230\345\237\237\343\201\270\343\201\256\345\217\216\347\270\256\351\207\217", nullptr));
        label_28->setText(QCoreApplication::translate("EditLibrary", "\346\234\200\345\244\247\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_31->setText(QCoreApplication::translate("EditLibrary", "\346\212\275\345\207\272\344\270\212\351\231\220\350\274\235\345\272\246", nullptr));
        label_27->setText(QCoreApplication::translate("EditLibrary", "\346\234\200\345\260\217\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_36->setText(QCoreApplication::translate("EditLibrary", "\346\234\200\345\244\247\351\225\267\343\201\225", nullptr));
        label_32->setText(QCoreApplication::translate("EditLibrary", "\346\212\275\345\207\272\344\270\213\351\231\220\350\274\235\345\272\246", nullptr));
        label_39->setText(QCoreApplication::translate("EditLibrary", "\351\231\220\347\225\214\343\202\265\343\202\244\343\202\272", nullptr));
        checkBoxGenerateOverlap->setText(QCoreApplication::translate("EditLibrary", "\351\207\215\350\244\207\347\224\237\346\210\220", nullptr));
        label_4->setText(QCoreApplication::translate("EditLibrary", "\345\220\215\347\247\260", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditLibrary", "Delete", nullptr));
        label_30->setText(QCoreApplication::translate("EditLibrary", "\345\274\267\350\252\277\344\277\202\346\225\260", nullptr));
        label_33->setText(QCoreApplication::translate("EditLibrary", "\347\267\232\345\271\205", nullptr));
        label_38->setText(QCoreApplication::translate("EditLibrary", "\346\216\242\347\264\242\350\267\235\351\233\242", nullptr));
        checkBoxExcludeDynamicMask->setText(QCoreApplication::translate("EditLibrary", "\345\213\225\347\232\204\343\203\236\343\202\271\343\202\257\351\240\230\345\237\237\343\202\222\346\216\222\351\231\244", nullptr));
        label_40->setText(QCoreApplication::translate("EditLibrary", "\351\226\213\345\247\213\350\247\222", nullptr));
        label_41->setText(QCoreApplication::translate("EditLibrary", "\347\265\202\344\272\206\350\247\222", nullptr));
        label->setText(QCoreApplication::translate("EditLibrary", "Angle is -360.0 -> 360.0 degree", nullptr));
        checkBoxFixedAngle->setText(QCoreApplication::translate("EditLibrary", "\345\233\272\345\256\232\350\247\222", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditLibrary", "Update", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditLibrary", "Clear new", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditLibrary", "Library Name", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditLibrary", "Save New", nullptr));
        pushButton->setText(QCoreApplication::translate("EditLibrary", "\351\226\211\343\201\230\343\202\213", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditLibrary", "12345", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditLibrary", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditLibrary", "Name", nullptr));
        label_8->setText(QCoreApplication::translate("EditLibrary", "\346\212\275\345\207\272\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        label_9->setText(QCoreApplication::translate("EditLibrary", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        label_10->setText(QCoreApplication::translate("EditLibrary", "\344\275\234\347\224\250\345\205\203\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLibrary: public Ui_EditLibrary {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLIBRARY_H
