/********************************************************************************
** Form generated from reading UI file 'EditLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLIBRARYDIALOG_H
#define UI_EDITLIBRARYDIALOG_H

#include <QtCore/QVariant>
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
    QLabel *label_8;
    QFrame *framePickLayer;
    QLabel *label_9;
    QTableWidget *tableWidgetLibList;
    QPushButton *pushButton;
    QPushButton *ButtonLibSave;
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
    QPushButton *ButtonLibDelete;
    QLabel *label_4;
    QFrame *frameGenLayer;
    QPushButton *ButtonLibNew;
    QLineEdit *EditLibName;
    QLineEdit *EditLibID;
    QPushButton *ButtonLibSaveNew;
    QFrame *frameLibFolder;
    QFrame *frame_2;
    QSpinBox *EditSelfSearch;
    QLabel *label_30;
    QDoubleSpinBox *doubleSpinBoxEmphasizeRate;
    QLabel *label_33;
    QSpinBox *EditMaxLineWidth;
    QLabel *label_38;
    QCheckBox *checkBoxExcludeDynamicMask;

    void setupUi(QDialog *EditLibraryDialog)
    {
        if (EditLibraryDialog->objectName().isEmpty())
            EditLibraryDialog->setObjectName(QString::fromUtf8("EditLibraryDialog"));
        EditLibraryDialog->resize(402, 823);
        label_8 = new QLabel(EditLibraryDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 270, 381, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setTextFormat(Qt::AutoText);
        label_8->setAlignment(Qt::AlignCenter);
        framePickLayer = new QFrame(EditLibraryDialog);
        framePickLayer->setObjectName(QString::fromUtf8("framePickLayer"));
        framePickLayer->setGeometry(QRect(10, 290, 381, 28));
        framePickLayer->setFrameShape(QFrame::NoFrame);
        framePickLayer->setFrameShadow(QFrame::Plain);
        label_9 = new QLabel(EditLibraryDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 320, 381, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignCenter);
        tableWidgetLibList = new QTableWidget(EditLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName(QString::fromUtf8("tableWidgetLibList"));
        tableWidgetLibList->setGeometry(QRect(220, 10, 171, 201));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButton = new QPushButton(EditLibraryDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(300, 780, 71, 31));
        QFont font;
        font.setPointSize(11);
        pushButton->setFont(font);
        ButtonLibSave = new QPushButton(EditLibraryDialog);
        ButtonLibSave->setObjectName(QString::fromUtf8("ButtonLibSave"));
        ButtonLibSave->setGeometry(QRect(300, 750, 71, 31));
        ButtonLibSave->setFont(font);
        frame = new QFrame(EditLibraryDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 370, 381, 221));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_37 = new QLabel(frame);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setGeometry(QRect(40, 130, 131, 21));
        label_37->setFrameShape(QFrame::Panel);
        label_37->setFrameShadow(QFrame::Sunken);
        label_37->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupL = new QSpinBox(frame);
        EditPickupL->setObjectName(QString::fromUtf8("EditPickupL"));
        EditPickupL->setGeometry(QRect(130, 30, 61, 22));
        EditPickupL->setMaximum(255);
        label_35 = new QLabel(frame);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setGeometry(QRect(210, 60, 81, 21));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Sunken);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinSize = new QSpinBox(frame);
        EditMinSize->setObjectName(QString::fromUtf8("EditMinSize"));
        EditMinSize->setGeometry(QRect(290, 60, 71, 22));
        EditMinSize->setMaximum(999999);
        label_34 = new QLabel(frame);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(200, 160, 111, 21));
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Sunken);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_29 = new QLabel(frame);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(10, 160, 121, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPriority = new QSpinBox(frame);
        EditPriority->setObjectName(QString::fromUtf8("EditPriority"));
        EditPriority->setGeometry(QRect(130, 160, 61, 22));
        EditPriority->setMaximum(255);
        EditStepDot = new QSpinBox(frame);
        EditStepDot->setObjectName(QString::fromUtf8("EditStepDot"));
        EditStepDot->setGeometry(QRect(310, 160, 61, 22));
        EditStepDot->setMaximum(255);
        EditMaxSize = new QSpinBox(frame);
        EditMaxSize->setObjectName(QString::fromUtf8("EditMaxSize"));
        EditMaxSize->setGeometry(QRect(290, 80, 71, 22));
        EditMaxSize->setMaximum(999999);
        EditMaxDot = new QSpinBox(frame);
        EditMaxDot->setObjectName(QString::fromUtf8("EditMaxDot"));
        EditMaxDot->setGeometry(QRect(120, 80, 71, 22));
        EditMaxDot->setMaximum(99999999);
        EditMinDot = new QSpinBox(frame);
        EditMinDot->setObjectName(QString::fromUtf8("EditMinDot"));
        EditMinDot->setGeometry(QRect(120, 60, 71, 22));
        EditMinDot->setMaximum(999999);
        EditSearchBlockWidth = new QSpinBox(frame);
        EditSearchBlockWidth->setObjectName(QString::fromUtf8("EditSearchBlockWidth"));
        EditSearchBlockWidth->setGeometry(QRect(170, 130, 61, 22));
        EditSearchBlockWidth->setMaximum(255);
        label_26 = new QLabel(frame);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(40, 110, 131, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_28 = new QLabel(frame);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(40, 80, 81, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_31 = new QLabel(frame);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(10, 10, 121, 21));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditShrinkDot = new QSpinBox(frame);
        EditShrinkDot->setObjectName(QString::fromUtf8("EditShrinkDot"));
        EditShrinkDot->setGeometry(QRect(170, 110, 61, 22));
        EditShrinkDot->setMaximum(255);
        label_27 = new QLabel(frame);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(40, 60, 81, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_36 = new QLabel(frame);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setGeometry(QRect(210, 80, 81, 21));
        label_36->setFrameShape(QFrame::Panel);
        label_36->setFrameShadow(QFrame::Sunken);
        label_36->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_32 = new QLabel(frame);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(10, 30, 121, 21));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupH = new QSpinBox(frame);
        EditPickupH->setObjectName(QString::fromUtf8("EditPickupH"));
        EditPickupH->setGeometry(QRect(130, 10, 61, 22));
        EditPickupH->setMaximum(255);
        label_39 = new QLabel(frame);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setGeometry(QRect(10, 190, 121, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLimitDot = new QSpinBox(frame);
        EditLimitDot->setObjectName(QString::fromUtf8("EditLimitDot"));
        EditLimitDot->setGeometry(QRect(130, 190, 61, 22));
        EditLimitDot->setMaximum(99999);
        checkBoxGenerateOverlap = new QCheckBox(frame);
        checkBoxGenerateOverlap->setObjectName(QString::fromUtf8("checkBoxGenerateOverlap"));
        checkBoxGenerateOverlap->setGeometry(QRect(200, 190, 171, 17));
        ButtonLibDelete = new QPushButton(EditLibraryDialog);
        ButtonLibDelete->setObjectName(QString::fromUtf8("ButtonLibDelete"));
        ButtonLibDelete->setGeometry(QRect(120, 750, 81, 31));
        ButtonLibDelete->setFont(font);
        label_4 = new QLabel(EditLibraryDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 230, 51, 31));
        QFont font1;
        font1.setPointSize(12);
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameGenLayer = new QFrame(EditLibraryDialog);
        frameGenLayer->setObjectName(QString::fromUtf8("frameGenLayer"));
        frameGenLayer->setGeometry(QRect(10, 340, 381, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);
        ButtonLibNew = new QPushButton(EditLibraryDialog);
        ButtonLibNew->setObjectName(QString::fromUtf8("ButtonLibNew"));
        ButtonLibNew->setGeometry(QRect(30, 750, 81, 31));
        ButtonLibNew->setFont(font);
        EditLibName = new QLineEdit(EditLibraryDialog);
        EditLibName->setObjectName(QString::fromUtf8("EditLibName"));
        EditLibName->setGeometry(QRect(140, 230, 251, 31));
        EditLibName->setFont(font1);
        EditLibID = new QLineEdit(EditLibraryDialog);
        EditLibID->setObjectName(QString::fromUtf8("EditLibID"));
        EditLibID->setGeometry(QRect(60, 230, 81, 31));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        ButtonLibSaveNew = new QPushButton(EditLibraryDialog);
        ButtonLibSaveNew->setObjectName(QString::fromUtf8("ButtonLibSaveNew"));
        ButtonLibSaveNew->setGeometry(QRect(210, 750, 81, 31));
        ButtonLibSaveNew->setFont(font);
        frameLibFolder = new QFrame(EditLibraryDialog);
        frameLibFolder->setObjectName(QString::fromUtf8("frameLibFolder"));
        frameLibFolder->setGeometry(QRect(10, 10, 201, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        frame_2 = new QFrame(EditLibraryDialog);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(10, 600, 381, 111));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        EditSelfSearch = new QSpinBox(frame_2);
        EditSelfSearch->setObjectName(QString::fromUtf8("EditSelfSearch"));
        EditSelfSearch->setGeometry(QRect(320, 40, 51, 22));
        EditSelfSearch->setMaximum(255);
        label_30 = new QLabel(frame_2);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(10, 10, 121, 21));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxEmphasizeRate = new QDoubleSpinBox(frame_2);
        doubleSpinBoxEmphasizeRate->setObjectName(QString::fromUtf8("doubleSpinBoxEmphasizeRate"));
        doubleSpinBoxEmphasizeRate->setGeometry(QRect(130, 10, 62, 22));
        doubleSpinBoxEmphasizeRate->setDecimals(4);
        doubleSpinBoxEmphasizeRate->setMinimum(-99.989999999999995);
        label_33 = new QLabel(frame_2);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(10, 40, 121, 21));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Sunken);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxLineWidth = new QSpinBox(frame_2);
        EditMaxLineWidth->setObjectName(QString::fromUtf8("EditMaxLineWidth"));
        EditMaxLineWidth->setGeometry(QRect(130, 40, 61, 22));
        EditMaxLineWidth->setMaximum(255);
        label_38 = new QLabel(frame_2);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setGeometry(QRect(210, 40, 111, 21));
        label_38->setFrameShape(QFrame::Panel);
        label_38->setFrameShadow(QFrame::Sunken);
        label_38->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxExcludeDynamicMask = new QCheckBox(frame_2);
        checkBoxExcludeDynamicMask->setObjectName(QString::fromUtf8("checkBoxExcludeDynamicMask"));
        checkBoxExcludeDynamicMask->setGeometry(QRect(20, 70, 221, 17));

        retranslateUi(EditLibraryDialog);

        QMetaObject::connectSlotsByName(EditLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *EditLibraryDialog)
    {
        EditLibraryDialog->setWindowTitle(QCoreApplication::translate("EditLibraryDialog", "Edit Library", nullptr));
        label_8->setText(QCoreApplication::translate("EditLibraryDialog", "\346\212\275\345\207\272\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        label_9->setText(QCoreApplication::translate("EditLibraryDialog", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditLibraryDialog", "Name", nullptr));
        pushButton->setText(QCoreApplication::translate("EditLibraryDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditLibraryDialog", "Update", nullptr));
        label_37->setText(QCoreApplication::translate("EditLibraryDialog", "\346\216\242\347\264\242\351\240\230\345\237\237\345\271\205", nullptr));
        label_35->setText(QCoreApplication::translate("EditLibraryDialog", "\346\234\200\345\260\217\351\225\267\343\201\225", nullptr));
        label_34->setText(QCoreApplication::translate("EditLibraryDialog", "\345\210\206\345\211\262\347\265\202\347\253\257\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_29->setText(QCoreApplication::translate("EditLibraryDialog", "\347\224\237\346\210\220\346\231\202\343\201\256\345\204\252\345\205\210\345\272\246", nullptr));
        label_26->setText(QCoreApplication::translate("EditLibraryDialog", "\345\207\246\347\220\206\351\240\230\345\237\237\343\201\270\343\201\256\345\217\216\347\270\256\351\207\217", nullptr));
        label_28->setText(QCoreApplication::translate("EditLibraryDialog", "\346\234\200\345\244\247\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_31->setText(QCoreApplication::translate("EditLibraryDialog", "\346\212\275\345\207\272\344\270\212\351\231\220\350\274\235\345\272\246", nullptr));
        label_27->setText(QCoreApplication::translate("EditLibraryDialog", "\346\234\200\345\260\217\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_36->setText(QCoreApplication::translate("EditLibraryDialog", "\346\234\200\345\244\247\351\225\267\343\201\225", nullptr));
        label_32->setText(QCoreApplication::translate("EditLibraryDialog", "\346\212\275\345\207\272\344\270\213\351\231\220\350\274\235\345\272\246", nullptr));
        label_39->setText(QCoreApplication::translate("EditLibraryDialog", "\351\231\220\347\225\214\343\202\265\343\202\244\343\202\272", nullptr));
        checkBoxGenerateOverlap->setText(QCoreApplication::translate("EditLibraryDialog", "\351\207\215\350\244\207\347\224\237\346\210\220", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditLibraryDialog", "Delete", nullptr));
        label_4->setText(QCoreApplication::translate("EditLibraryDialog", "\345\220\215\347\247\260", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditLibraryDialog", "Clear new", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditLibraryDialog", "Library Name", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditLibraryDialog", "12345", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditLibraryDialog", "Save New", nullptr));
        label_30->setText(QCoreApplication::translate("EditLibraryDialog", "\345\274\267\350\252\277\344\277\202\346\225\260", nullptr));
        label_33->setText(QCoreApplication::translate("EditLibraryDialog", "\347\267\232\345\271\205", nullptr));
        label_38->setText(QCoreApplication::translate("EditLibraryDialog", "\346\216\242\347\264\242\350\267\235\351\233\242", nullptr));
        checkBoxExcludeDynamicMask->setText(QCoreApplication::translate("EditLibraryDialog", "\345\213\225\347\232\204\343\203\236\343\202\271\343\202\257\351\240\230\345\237\237\343\202\222\346\216\222\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLibraryDialog: public Ui_EditLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLIBRARYDIALOG_H
