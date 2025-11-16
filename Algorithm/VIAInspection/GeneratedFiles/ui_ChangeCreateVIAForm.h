/********************************************************************************
** Form generated from reading UI file 'ChangeCreateVIAForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGECREATEVIAFORM_H
#define UI_CHANGECREATEVIAFORM_H

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

class Ui_ChangeCreateVIAForm
{
public:
    QFrame *frame;
    QLabel *label;
    QFrame *frameLibFolder;
    QTableWidget *tableWidgetLibList;
    QFrame *frame_5;
    QLabel *label_4;
    QLineEdit *EditLibID;
    QLineEdit *EditLibName;
    QLabel *label_3;
    QPushButton *ButtonOK;
    QPushButton *ButtonCancel;
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
    QLabel *label_32;
    QSpinBox *EditOKLengthL;
    QSpinBox *EditOKLengthH;
    QSpinBox *EditShrinkDot;
    QLabel *label_41;
    QLabel *label_51;
    QSpinBox *EditMaxNGDotL;
    QSpinBox *EditMaxNGDotH;
    QLabel *label_42;
    QSpinBox *EditEnlargeDot;

    void setupUi(QDialog *ChangeCreateVIAForm)
    {
        if (ChangeCreateVIAForm->objectName().isEmpty())
            ChangeCreateVIAForm->setObjectName("ChangeCreateVIAForm");
        ChangeCreateVIAForm->resize(412, 477);
        frame = new QFrame(ChangeCreateVIAForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 391, 461));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 381, 21));
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameLibFolder = new QFrame(frame);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 20, 191, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        tableWidgetLibList = new QTableWidget(frame);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 20, 171, 141));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame_5 = new QFrame(frame);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 170, 371, 281));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame_5);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 20, 51, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(frame_5);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 20, 81, 21));
        EditLibID->setReadOnly(true);
        EditLibName = new QLineEdit(frame_5);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 20, 211, 21));
        label_3 = new QLabel(frame_5);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 351, 21));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonOK = new QPushButton(frame_5);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(10, 240, 75, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        ButtonCancel = new QPushButton(frame_5);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(280, 240, 81, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        frame_6 = new QFrame(frame_5);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(10, 40, 351, 181));
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
        label_20->setGeometry(QRect(260, 10, 81, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        label_20->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_17 = new QLabel(frame_6);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(40, 30, 121, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKDotH = new QSpinBox(frame_6);
        EditOKDotH->setObjectName("EditOKDotH");
        EditOKDotH->setGeometry(QRect(260, 50, 81, 22));
        EditOKDotH->setMaximum(99999999);
        label_18 = new QLabel(frame_6);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(40, 50, 121, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBrightWidthL = new QSpinBox(frame_6);
        EditBrightWidthL->setObjectName("EditBrightWidthL");
        EditBrightWidthL->setGeometry(QRect(170, 30, 81, 22));
        EditBrightWidthL->setMaximum(255);
        EditOKDotL = new QSpinBox(frame_6);
        EditOKDotL->setObjectName("EditOKDotL");
        EditOKDotL->setGeometry(QRect(170, 50, 81, 22));
        EditOKDotL->setMaximum(99999999);
        EditBrightWidthH = new QSpinBox(frame_6);
        EditBrightWidthH->setObjectName("EditBrightWidthH");
        EditBrightWidthH->setGeometry(QRect(260, 30, 81, 22));
        EditBrightWidthH->setMaximum(255);
        label_19 = new QLabel(frame_6);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(170, 10, 81, 21));
        label_19->setFrameShape(QFrame::Panel);
        label_19->setFrameShadow(QFrame::Sunken);
        label_19->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_32 = new QLabel(frame_6);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(40, 70, 121, 21));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKLengthL = new QSpinBox(frame_6);
        EditOKLengthL->setObjectName("EditOKLengthL");
        EditOKLengthL->setGeometry(QRect(170, 70, 81, 22));
        EditOKLengthL->setMaximum(99999999);
        EditOKLengthH = new QSpinBox(frame_6);
        EditOKLengthH->setObjectName("EditOKLengthH");
        EditOKLengthH->setGeometry(QRect(260, 70, 81, 22));
        EditOKLengthH->setMaximum(99999999);
        EditShrinkDot = new QSpinBox(frame_6);
        EditShrinkDot->setObjectName("EditShrinkDot");
        EditShrinkDot->setGeometry(QRect(210, 132, 81, 22));
        EditShrinkDot->setMaximum(99999999);
        label_41 = new QLabel(frame_6);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(40, 130, 121, 21));
        label_41->setFrameShape(QFrame::Panel);
        label_41->setFrameShadow(QFrame::Sunken);
        label_41->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_51 = new QLabel(frame_6);
        label_51->setObjectName("label_51");
        label_51->setGeometry(QRect(40, 92, 121, 21));
        label_51->setFrameShape(QFrame::Panel);
        label_51->setFrameShadow(QFrame::Sunken);
        label_51->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxNGDotL = new QSpinBox(frame_6);
        EditMaxNGDotL->setObjectName("EditMaxNGDotL");
        EditMaxNGDotL->setGeometry(QRect(170, 92, 81, 22));
        EditMaxNGDotL->setMaximum(99999999);
        EditMaxNGDotH = new QSpinBox(frame_6);
        EditMaxNGDotH->setObjectName("EditMaxNGDotH");
        EditMaxNGDotH->setGeometry(QRect(260, 92, 81, 22));
        EditMaxNGDotH->setMaximum(99999999);
        label_42 = new QLabel(frame_6);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(40, 152, 121, 21));
        label_42->setFrameShape(QFrame::Panel);
        label_42->setFrameShadow(QFrame::Sunken);
        label_42->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditEnlargeDot = new QSpinBox(frame_6);
        EditEnlargeDot->setObjectName("EditEnlargeDot");
        EditEnlargeDot->setGeometry(QRect(210, 152, 81, 22));
        EditEnlargeDot->setMaximum(99999999);

        retranslateUi(ChangeCreateVIAForm);

        QMetaObject::connectSlotsByName(ChangeCreateVIAForm);
    } // setupUi

    void retranslateUi(QDialog *ChangeCreateVIAForm)
    {
        ChangeCreateVIAForm->setWindowTitle(QCoreApplication::translate("ChangeCreateVIAForm", "CreateVIA", nullptr));
        label->setText(QCoreApplication::translate("ChangeCreateVIAForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ChangeCreateVIAForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ChangeCreateVIAForm", "Name", nullptr));
        label_4->setText(QCoreApplication::translate("ChangeCreateVIAForm", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("ChangeCreateVIAForm", "12345", nullptr));
        EditLibName->setText(QCoreApplication::translate("ChangeCreateVIAForm", "Library Name", nullptr));
        label_3->setText(QCoreApplication::translate("ChangeCreateVIAForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\227\343\203\255\343\203\221\343\203\206\343\202\243", nullptr));
        ButtonOK->setText(QCoreApplication::translate("ChangeCreateVIAForm", "OK", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("ChangeCreateVIAForm", "Cancel", nullptr));
        label_35->setText(QCoreApplication::translate("ChangeCreateVIAForm", "\346\244\234\346\237\273", nullptr));
        label_20->setText(QCoreApplication::translate("ChangeCreateVIAForm", "\346\230\216\345\201\264", nullptr));
        label_17->setText(QCoreApplication::translate("ChangeCreateVIAForm", "OK\350\274\235\345\272\246\347\257\204\345\233\262", nullptr));
        label_18->setText(QCoreApplication::translate("ChangeCreateVIAForm", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_19->setText(QCoreApplication::translate("ChangeCreateVIAForm", "\346\232\227\345\201\264", nullptr));
        label_32->setText(QCoreApplication::translate("ChangeCreateVIAForm", "\343\201\223\343\202\214\344\273\245\344\270\212\343\201\256\351\225\267\343\201\225\343\201\247\357\274\256\357\274\247", nullptr));
        label_41->setText(QCoreApplication::translate("ChangeCreateVIAForm", "\345\217\216\347\270\256\343\203\211\343\203\203\343\203\210", nullptr));
        label_51->setText(QCoreApplication::translate("ChangeCreateVIAForm", "\346\234\200\345\244\247NG\351\235\242\347\251\215", nullptr));
        label_42->setText(QCoreApplication::translate("ChangeCreateVIAForm", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeCreateVIAForm: public Ui_ChangeCreateVIAForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGECREATEVIAFORM_H
