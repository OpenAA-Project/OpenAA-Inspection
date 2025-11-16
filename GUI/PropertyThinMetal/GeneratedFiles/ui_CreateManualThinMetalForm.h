/********************************************************************************
** Form generated from reading UI file 'CreateManualThinMetalForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEMANUALTHINMETALFORM_H
#define UI_CREATEMANUALTHINMETALFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateManualThinMetalForm
{
public:
    QFrame *frameLibFolder;
    QLineEdit *EditLibName;
    QPushButton *ButtonOK;
    QTableWidget *tableWidgetLibList;
    QPushButton *ButtonCancel;
    QLineEdit *EditLibID;
    QFrame *frame_6;
    QLabel *label_35;
    QLabel *label_20;
    QLabel *label_17;
    QSpinBox *EditOKDotH;
    QLabel *label_18;
    QSpinBox *EditBrightWidthL;
    QSpinBox *EditOKDotL;
    QSpinBox *EditBrightWidthH;
    QLabel *label_19;
    QLabel *label_29;
    QSpinBox *EditOKLengthL;
    QSpinBox *EditOKLengthH;
    QSpinBox *EditShrinkDot;
    QLabel *label_38;
    QLabel *label_51;
    QSpinBox *EditMaxNGDotL;
    QSpinBox *EditMaxNGDotH;
    QLabel *label_39;
    QSpinBox *EditEnlargeDot;
    QLabel *label;
    QLineEdit *EditItemName;

    void setupUi(QDialog *CreateManualThinMetalForm)
    {
        if (CreateManualThinMetalForm->objectName().isEmpty())
            CreateManualThinMetalForm->setObjectName("CreateManualThinMetalForm");
        CreateManualThinMetalForm->resize(424, 485);
        frameLibFolder = new QFrame(CreateManualThinMetalForm);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        EditLibName = new QLineEdit(CreateManualThinMetalForm);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(80, 200, 331, 21));
        EditLibName->setReadOnly(true);
        ButtonOK = new QPushButton(CreateManualThinMetalForm);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(40, 430, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        tableWidgetLibList = new QTableWidget(CreateManualThinMetalForm);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 201, 141));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonCancel = new QPushButton(CreateManualThinMetalForm);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(280, 430, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        EditLibID = new QLineEdit(CreateManualThinMetalForm);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(30, 200, 51, 21));
        EditLibID->setReadOnly(true);
        frame_6 = new QFrame(CreateManualThinMetalForm);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(30, 230, 381, 181));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Sunken);
        label_35 = new QLabel(frame_6);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(0, 0, 31, 181));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Raised);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_35->setIndent(1);
        label_20 = new QLabel(frame_6);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(280, 8, 81, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        label_20->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_17 = new QLabel(frame_6);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(60, 28, 121, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKDotH = new QSpinBox(frame_6);
        EditOKDotH->setObjectName("EditOKDotH");
        EditOKDotH->setGeometry(QRect(280, 48, 81, 22));
        EditOKDotH->setMaximum(99999999);
        label_18 = new QLabel(frame_6);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(60, 48, 121, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBrightWidthL = new QSpinBox(frame_6);
        EditBrightWidthL->setObjectName("EditBrightWidthL");
        EditBrightWidthL->setGeometry(QRect(190, 28, 81, 22));
        EditBrightWidthL->setMaximum(255);
        EditOKDotL = new QSpinBox(frame_6);
        EditOKDotL->setObjectName("EditOKDotL");
        EditOKDotL->setGeometry(QRect(190, 48, 81, 22));
        EditOKDotL->setMaximum(99999999);
        EditBrightWidthH = new QSpinBox(frame_6);
        EditBrightWidthH->setObjectName("EditBrightWidthH");
        EditBrightWidthH->setGeometry(QRect(280, 28, 81, 22));
        EditBrightWidthH->setMaximum(255);
        label_19 = new QLabel(frame_6);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(190, 8, 81, 21));
        label_19->setFrameShape(QFrame::Panel);
        label_19->setFrameShadow(QFrame::Sunken);
        label_19->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_29 = new QLabel(frame_6);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(60, 68, 121, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKLengthL = new QSpinBox(frame_6);
        EditOKLengthL->setObjectName("EditOKLengthL");
        EditOKLengthL->setGeometry(QRect(190, 68, 81, 22));
        EditOKLengthL->setMaximum(99999999);
        EditOKLengthH = new QSpinBox(frame_6);
        EditOKLengthH->setObjectName("EditOKLengthH");
        EditOKLengthH->setGeometry(QRect(280, 68, 81, 22));
        EditOKLengthH->setMaximum(99999999);
        EditShrinkDot = new QSpinBox(frame_6);
        EditShrinkDot->setObjectName("EditShrinkDot");
        EditShrinkDot->setGeometry(QRect(230, 130, 81, 22));
        EditShrinkDot->setMaximum(99999999);
        label_38 = new QLabel(frame_6);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(60, 128, 121, 21));
        label_38->setFrameShape(QFrame::Panel);
        label_38->setFrameShadow(QFrame::Sunken);
        label_38->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_51 = new QLabel(frame_6);
        label_51->setObjectName("label_51");
        label_51->setGeometry(QRect(60, 90, 121, 21));
        label_51->setFrameShape(QFrame::Panel);
        label_51->setFrameShadow(QFrame::Sunken);
        label_51->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxNGDotL = new QSpinBox(frame_6);
        EditMaxNGDotL->setObjectName("EditMaxNGDotL");
        EditMaxNGDotL->setGeometry(QRect(190, 90, 81, 22));
        EditMaxNGDotL->setMaximum(99999999);
        EditMaxNGDotH = new QSpinBox(frame_6);
        EditMaxNGDotH->setObjectName("EditMaxNGDotH");
        EditMaxNGDotH->setGeometry(QRect(280, 90, 81, 22));
        EditMaxNGDotH->setMaximum(99999999);
        label_39 = new QLabel(frame_6);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(60, 150, 121, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditEnlargeDot = new QSpinBox(frame_6);
        EditEnlargeDot->setObjectName("EditEnlargeDot");
        EditEnlargeDot->setGeometry(QRect(230, 150, 81, 22));
        EditEnlargeDot->setMaximum(99999999);
        label = new QLabel(CreateManualThinMetalForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 170, 81, 21));
        EditItemName = new QLineEdit(CreateManualThinMetalForm);
        EditItemName->setObjectName("EditItemName");
        EditItemName->setGeometry(QRect(90, 170, 321, 21));
        EditItemName->setReadOnly(false);

        retranslateUi(CreateManualThinMetalForm);

        ButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(CreateManualThinMetalForm);
    } // setupUi

    void retranslateUi(QDialog *CreateManualThinMetalForm)
    {
        CreateManualThinMetalForm->setWindowTitle(QCoreApplication::translate("CreateManualThinMetalForm", "Create Manual ThinMetal", nullptr));
        ButtonOK->setText(QCoreApplication::translate("CreateManualThinMetalForm", "OK", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CreateManualThinMetalForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CreateManualThinMetalForm", "Name", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("CreateManualThinMetalForm", "Cancel", nullptr));
        label_35->setText(QCoreApplication::translate("CreateManualThinMetalForm", "\346\244\234\346\237\273", nullptr));
        label_20->setText(QCoreApplication::translate("CreateManualThinMetalForm", "\346\230\216\345\201\264", nullptr));
        label_17->setText(QCoreApplication::translate("CreateManualThinMetalForm", "OK\350\274\235\345\272\246\347\257\204\345\233\262", nullptr));
        label_18->setText(QCoreApplication::translate("CreateManualThinMetalForm", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_19->setText(QCoreApplication::translate("CreateManualThinMetalForm", "\346\232\227\345\201\264", nullptr));
        label_29->setText(QCoreApplication::translate("CreateManualThinMetalForm", "\343\201\223\343\202\214\344\273\245\344\270\212\343\201\256\351\225\267\343\201\225\343\201\247\357\274\256\357\274\247", nullptr));
        label_38->setText(QCoreApplication::translate("CreateManualThinMetalForm", "\345\217\216\347\270\256\343\203\211\343\203\203\343\203\210", nullptr));
        label_51->setText(QCoreApplication::translate("CreateManualThinMetalForm", "\346\234\200\345\244\247NG\351\235\242\347\251\215", nullptr));
        label_39->setText(QCoreApplication::translate("CreateManualThinMetalForm", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210", nullptr));
        label->setText(QCoreApplication::translate("CreateManualThinMetalForm", "Item name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateManualThinMetalForm: public Ui_CreateManualThinMetalForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEMANUALTHINMETALFORM_H
