/********************************************************************************
** Form generated from reading UI file 'SelectLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLIBRARYDIALOG_H
#define UI_SELECTLIBRARYDIALOG_H

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

class Ui_SelectLibraryDialog
{
public:
    QTableWidget *tableWidgetLibList;
    QPushButton *pushButtonSelect;
    QLabel *label_4;
    QFrame *frameLibFolder;
    QLineEdit *EditLibID;
    QPushButton *pushButtonCancel;
    QLineEdit *EditLibName;
    QFrame *frame;
    QSpinBox *EditMinWidth;
    QLabel *label_27;
    QCheckBox *checkBoxDarkside;
    QCheckBox *checkBoxCompareToMaster;
    QSpinBox *EditBinarizedLength;
    QLabel *label_40;
    QLabel *label_41;
    QSpinBox *EditReferredBrightness;
    QLabel *label_42;
    QSpinBox *EditSearchDotToMaster;
    QLabel *label_28;
    QSpinBox *EditMinGap;
    QCheckBox *checkBoxAutoBinarize;
    QCheckBox *checkBoxReduceNoise;
    QLabel *label_44;
    QLabel *label_43;
    QLineEdit *lineEditMinArea;
    QLineEdit *lineEditMaxArea;
    QSpinBox *EditMinSize;
    QLabel *label_29;
    QFrame *frame_3;
    QLabel *label_48;
    QLabel *label_49;
    QLabel *label_51;
    QSpinBox *EditBrightnessWidthInsideL;
    QLabel *label_53;
    QLabel *label_54;
    QSpinBox *EditBrightnessWidthOutsideL;
    QSpinBox *EditBrightnessWidthOutsideH;
    QSpinBox *EditBrightnessWidthInsideH;
    QLabel *label_52;
    QLabel *label_50;

    void setupUi(QDialog *SelectLibraryDialog)
    {
        if (SelectLibraryDialog->objectName().isEmpty())
            SelectLibraryDialog->setObjectName("SelectLibraryDialog");
        SelectLibraryDialog->resize(569, 595);
        tableWidgetLibList = new QTableWidget(SelectLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(240, 10, 291, 201));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelect = new QPushButton(SelectLibraryDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(120, 550, 121, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSelect->setIcon(icon);
        label_4 = new QLabel(SelectLibraryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 230, 51, 31));
        QFont font;
        font.setPointSize(12);
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameLibFolder = new QFrame(SelectLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 221, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        EditLibID = new QLineEdit(SelectLibraryDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 230, 71, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        pushButtonCancel = new QPushButton(SelectLibraryDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(330, 550, 121, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        EditLibName = new QLineEdit(SelectLibraryDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(130, 230, 431, 31));
        EditLibName->setFont(font);
        frame = new QFrame(SelectLibraryDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 260, 381, 281));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        EditMinWidth = new QSpinBox(frame);
        EditMinWidth->setObjectName("EditMinWidth");
        EditMinWidth->setGeometry(QRect(270, 10, 71, 22));
        EditMinWidth->setMaximum(999999);
        label_27 = new QLabel(frame);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(20, 10, 241, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxDarkside = new QCheckBox(frame);
        checkBoxDarkside->setObjectName("checkBoxDarkside");
        checkBoxDarkside->setGeometry(QRect(30, 142, 341, 17));
        checkBoxCompareToMaster = new QCheckBox(frame);
        checkBoxCompareToMaster->setObjectName("checkBoxCompareToMaster");
        checkBoxCompareToMaster->setGeometry(QRect(30, 162, 341, 17));
        EditBinarizedLength = new QSpinBox(frame);
        EditBinarizedLength->setObjectName("EditBinarizedLength");
        EditBinarizedLength->setGeometry(QRect(210, 206, 71, 22));
        EditBinarizedLength->setMaximum(99999);
        label_40 = new QLabel(frame);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(20, 206, 191, 21));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setFrameShadow(QFrame::Sunken);
        label_40->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_41 = new QLabel(frame);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(20, 230, 191, 21));
        label_41->setFrameShape(QFrame::Panel);
        label_41->setFrameShadow(QFrame::Sunken);
        label_41->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditReferredBrightness = new QSpinBox(frame);
        EditReferredBrightness->setObjectName("EditReferredBrightness");
        EditReferredBrightness->setGeometry(QRect(210, 230, 71, 22));
        EditReferredBrightness->setMaximum(99999);
        label_42 = new QLabel(frame);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(20, 252, 191, 21));
        label_42->setFrameShape(QFrame::Panel);
        label_42->setFrameShadow(QFrame::Sunken);
        label_42->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSearchDotToMaster = new QSpinBox(frame);
        EditSearchDotToMaster->setObjectName("EditSearchDotToMaster");
        EditSearchDotToMaster->setGeometry(QRect(210, 252, 71, 22));
        EditSearchDotToMaster->setMaximum(99999);
        label_28 = new QLabel(frame);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(20, 32, 241, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinGap = new QSpinBox(frame);
        EditMinGap->setObjectName("EditMinGap");
        EditMinGap->setGeometry(QRect(270, 32, 71, 22));
        EditMinGap->setMaximum(999999);
        checkBoxAutoBinarize = new QCheckBox(frame);
        checkBoxAutoBinarize->setObjectName("checkBoxAutoBinarize");
        checkBoxAutoBinarize->setGeometry(QRect(290, 230, 91, 20));
        checkBoxReduceNoise = new QCheckBox(frame);
        checkBoxReduceNoise->setObjectName("checkBoxReduceNoise");
        checkBoxReduceNoise->setGeometry(QRect(30, 182, 341, 17));
        label_44 = new QLabel(frame);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(20, 80, 221, 21));
        label_44->setFrameShape(QFrame::Panel);
        label_44->setFrameShadow(QFrame::Sunken);
        label_44->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_43 = new QLabel(frame);
        label_43->setObjectName("label_43");
        label_43->setGeometry(QRect(20, 58, 221, 21));
        label_43->setFrameShape(QFrame::Panel);
        label_43->setFrameShadow(QFrame::Sunken);
        label_43->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditMinArea = new QLineEdit(frame);
        lineEditMinArea->setObjectName("lineEditMinArea");
        lineEditMinArea->setGeometry(QRect(260, 58, 113, 21));
        lineEditMaxArea = new QLineEdit(frame);
        lineEditMaxArea->setObjectName("lineEditMaxArea");
        lineEditMaxArea->setGeometry(QRect(260, 80, 113, 21));
        EditMinSize = new QSpinBox(frame);
        EditMinSize->setObjectName("EditMinSize");
        EditMinSize->setGeometry(QRect(268, 110, 91, 22));
        EditMinSize->setMaximum(999999);
        label_29 = new QLabel(frame);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(20, 110, 241, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_3 = new QFrame(SelectLibraryDialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(390, 260, 171, 191));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_48 = new QLabel(frame_3);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(0, 0, 171, 21));
        label_48->setFrameShape(QFrame::Panel);
        label_48->setFrameShadow(QFrame::Sunken);
        label_48->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_49 = new QLabel(frame_3);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(10, 30, 151, 21));
        label_49->setFrameShape(QFrame::Panel);
        label_49->setFrameShadow(QFrame::Sunken);
        label_49->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_51 = new QLabel(frame_3);
        label_51->setObjectName("label_51");
        label_51->setGeometry(QRect(10, 50, 71, 21));
        label_51->setFrameShape(QFrame::Panel);
        label_51->setFrameShadow(QFrame::Sunken);
        label_51->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBrightnessWidthInsideL = new QSpinBox(frame_3);
        EditBrightnessWidthInsideL->setObjectName("EditBrightnessWidthInsideL");
        EditBrightnessWidthInsideL->setGeometry(QRect(10, 70, 71, 22));
        EditBrightnessWidthInsideL->setMinimum(-256);
        EditBrightnessWidthInsideL->setMaximum(256);
        label_53 = new QLabel(frame_3);
        label_53->setObjectName("label_53");
        label_53->setGeometry(QRect(10, 110, 151, 21));
        label_53->setFrameShape(QFrame::Panel);
        label_53->setFrameShadow(QFrame::Sunken);
        label_53->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_54 = new QLabel(frame_3);
        label_54->setObjectName("label_54");
        label_54->setGeometry(QRect(10, 130, 71, 21));
        label_54->setFrameShape(QFrame::Panel);
        label_54->setFrameShadow(QFrame::Sunken);
        label_54->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBrightnessWidthOutsideL = new QSpinBox(frame_3);
        EditBrightnessWidthOutsideL->setObjectName("EditBrightnessWidthOutsideL");
        EditBrightnessWidthOutsideL->setGeometry(QRect(10, 150, 71, 22));
        EditBrightnessWidthOutsideL->setMinimum(-256);
        EditBrightnessWidthOutsideL->setMaximum(256);
        EditBrightnessWidthOutsideH = new QSpinBox(frame_3);
        EditBrightnessWidthOutsideH->setObjectName("EditBrightnessWidthOutsideH");
        EditBrightnessWidthOutsideH->setGeometry(QRect(80, 150, 71, 22));
        EditBrightnessWidthOutsideH->setMinimum(-256);
        EditBrightnessWidthOutsideH->setMaximum(256);
        EditBrightnessWidthInsideH = new QSpinBox(frame_3);
        EditBrightnessWidthInsideH->setObjectName("EditBrightnessWidthInsideH");
        EditBrightnessWidthInsideH->setGeometry(QRect(80, 70, 71, 22));
        EditBrightnessWidthInsideH->setMinimum(-256);
        EditBrightnessWidthInsideH->setMaximum(256);
        label_52 = new QLabel(frame_3);
        label_52->setObjectName("label_52");
        label_52->setGeometry(QRect(80, 130, 71, 21));
        label_52->setFrameShape(QFrame::Panel);
        label_52->setFrameShadow(QFrame::Sunken);
        label_52->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_50 = new QLabel(frame_3);
        label_50->setObjectName("label_50");
        label_50->setGeometry(QRect(80, 50, 71, 21));
        label_50->setFrameShape(QFrame::Panel);
        label_50->setFrameShadow(QFrame::Sunken);
        label_50->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(SelectLibraryDialog);

        pushButtonSelect->setDefault(true);


        QMetaObject::connectSlotsByName(SelectLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectLibraryDialog)
    {
        SelectLibraryDialog->setWindowTitle(QCoreApplication::translate("SelectLibraryDialog", "Select Library", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectLibraryDialog", "Name", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectLibraryDialog", "Select", nullptr));
        label_4->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("SelectLibraryDialog", "12345", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectLibraryDialog", "Cancel", nullptr));
        EditLibName->setText(QCoreApplication::translate("SelectLibraryDialog", "Library Name", nullptr));
        label_27->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\234\200\345\260\217\343\203\251\343\202\244\343\203\263\345\271\205", nullptr));
        checkBoxDarkside->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\232\227\345\201\264", nullptr));
        checkBoxCompareToMaster->setText(QCoreApplication::translate("SelectLibraryDialog", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217\343\201\250\343\201\256\346\257\224\350\274\203", nullptr));
        label_40->setText(QCoreApplication::translate("SelectLibraryDialog", "\351\203\250\345\210\206\347\232\204\357\274\222\345\200\244\345\214\226\343\201\256\343\202\265\343\202\244\343\202\272", nullptr));
        label_41->setText(QCoreApplication::translate("SelectLibraryDialog", "\357\274\222\345\200\244\345\214\226\345\217\202\347\205\247\350\274\235\345\272\246\345\200\244", nullptr));
        label_42->setText(QCoreApplication::translate("SelectLibraryDialog", "\343\203\236\343\202\271\343\202\277\343\203\274\343\201\250\343\201\256\346\257\224\350\274\203\346\231\202\343\201\256\346\216\242\347\264\242\347\257\204\345\233\262", nullptr));
        label_28->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\234\200\345\260\217\351\226\223\351\232\224", nullptr));
        checkBoxAutoBinarize->setText(QCoreApplication::translate("SelectLibraryDialog", "\350\207\252\345\213\225", nullptr));
        checkBoxReduceNoise->setText(QCoreApplication::translate("SelectLibraryDialog", "\343\203\216\343\202\244\343\202\272\345\211\212\351\231\244", nullptr));
        label_44->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_43->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_29->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_48->setText(QCoreApplication::translate("SelectLibraryDialog", "OK\345\210\244\345\256\232\343\201\256\350\274\235\345\272\246\345\271\205", nullptr));
        label_49->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\206\205\345\201\264", nullptr));
        label_51->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\232\227\345\201\264", nullptr));
        label_53->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\244\226\345\201\264", nullptr));
        label_54->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\232\227\345\201\264", nullptr));
        label_52->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\230\216\345\201\264", nullptr));
        label_50->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\230\216\345\201\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibraryDialog: public Ui_SelectLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBRARYDIALOG_H
