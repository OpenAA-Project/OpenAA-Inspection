/********************************************************************************
** Form generated from reading UI file 'EditLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLIBRARYDIALOG_H
#define UI_EDITLIBRARYDIALOG_H

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

class Ui_EditLibraryDialog
{
public:
    QLabel *label_4;
    QPushButton *ButtonLibDelete;
    QPushButton *ButtonLibNew;
    QFrame *frame;
    QCheckBox *checkBoxDarkside;
    QCheckBox *checkBoxCompareToMaster;
    QSpinBox *EditBinarizedLength;
    QLabel *label_40;
    QLabel *label_41;
    QSpinBox *EditReferredBrightness;
    QLabel *label_42;
    QSpinBox *EditSearchDotToMaster;
    QCheckBox *checkBoxAutoBinarize;
    QCheckBox *checkBoxReduceNoise;
    QTableWidget *tableWidgetLibList;
    QLineEdit *EditLibName;
    QPushButton *ButtonLibSaveNew;
    QLineEdit *EditLibID;
    QPushButton *ButtonLibSave;
    QFrame *frameLibFolder;
    QPushButton *pushButton;
    QLabel *label_8;
    QFrame *framePickLayer;
    QFrame *frameGenLayer;
    QLabel *label_9;
    QFrame *frame_2;
    QLabel *label_44;
    QLabel *label_27;
    QSpinBox *EditMinWidth;
    QLabel *label_28;
    QLabel *label_43;
    QSpinBox *EditMinGap;
    QSpinBox *EditWidthToIgnoreEdge;
    QLabel *label_45;
    QLabel *label_46;
    QSpinBox *EditOKNickRate;
    QSpinBox *EditOKShortRate;
    QLabel *label_47;
    QLineEdit *lineEditMaxArea;
    QLineEdit *lineEditMinArea;
    QLabel *label_29;
    QSpinBox *EditMinSize;
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
    QFrame *frame_4;
    QSpinBox *EditLimitDot;
    QLabel *label_39;
    QLineEdit *lineEditBlockMinArea;
    QLabel *label_55;
    QLineEdit *lineEditBlockMaxArea;
    QLabel *label_56;

    void setupUi(QDialog *EditLibraryDialog)
    {
        if (EditLibraryDialog->objectName().isEmpty())
            EditLibraryDialog->setObjectName("EditLibraryDialog");
        EditLibraryDialog->resize(853, 775);
        label_4 = new QLabel(EditLibraryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 230, 51, 31));
        QFont font;
        font.setPointSize(12);
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibDelete = new QPushButton(EditLibraryDialog);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(200, 730, 111, 31));
        QFont font1;
        font1.setPointSize(11);
        ButtonLibDelete->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon);
        ButtonLibNew = new QPushButton(EditLibraryDialog);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(10, 730, 181, 31));
        ButtonLibNew->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon1);
        frame = new QFrame(EditLibraryDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 470, 281, 211));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        checkBoxDarkside = new QCheckBox(frame);
        checkBoxDarkside->setObjectName("checkBoxDarkside");
        checkBoxDarkside->setGeometry(QRect(20, 10, 251, 17));
        checkBoxCompareToMaster = new QCheckBox(frame);
        checkBoxCompareToMaster->setObjectName("checkBoxCompareToMaster");
        checkBoxCompareToMaster->setGeometry(QRect(20, 30, 251, 17));
        EditBinarizedLength = new QSpinBox(frame);
        EditBinarizedLength->setObjectName("EditBinarizedLength");
        EditBinarizedLength->setGeometry(QRect(200, 80, 71, 22));
        EditBinarizedLength->setMaximum(99999);
        label_40 = new QLabel(frame);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(10, 80, 191, 21));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setFrameShadow(QFrame::Sunken);
        label_40->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_41 = new QLabel(frame);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(10, 110, 191, 21));
        label_41->setFrameShape(QFrame::Panel);
        label_41->setFrameShadow(QFrame::Sunken);
        label_41->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditReferredBrightness = new QSpinBox(frame);
        EditReferredBrightness->setObjectName("EditReferredBrightness");
        EditReferredBrightness->setGeometry(QRect(200, 110, 71, 22));
        EditReferredBrightness->setMaximum(99999);
        label_42 = new QLabel(frame);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(10, 170, 191, 21));
        label_42->setFrameShape(QFrame::Panel);
        label_42->setFrameShadow(QFrame::Sunken);
        label_42->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSearchDotToMaster = new QSpinBox(frame);
        EditSearchDotToMaster->setObjectName("EditSearchDotToMaster");
        EditSearchDotToMaster->setGeometry(QRect(200, 170, 71, 22));
        EditSearchDotToMaster->setMaximum(99999);
        checkBoxAutoBinarize = new QCheckBox(frame);
        checkBoxAutoBinarize->setObjectName("checkBoxAutoBinarize");
        checkBoxAutoBinarize->setGeometry(QRect(200, 140, 111, 20));
        checkBoxReduceNoise = new QCheckBox(frame);
        checkBoxReduceNoise->setObjectName("checkBoxReduceNoise");
        checkBoxReduceNoise->setGeometry(QRect(20, 50, 251, 17));
        tableWidgetLibList = new QTableWidget(EditLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(220, 10, 281, 201));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        EditLibName = new QLineEdit(EditLibraryDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 230, 361, 31));
        EditLibName->setFont(font);
        ButtonLibSaveNew = new QPushButton(EditLibraryDialog);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(320, 730, 191, 31));
        ButtonLibSaveNew->setFont(font1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon2);
        EditLibID = new QLineEdit(EditLibraryDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 230, 81, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        ButtonLibSave = new QPushButton(EditLibraryDialog);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(520, 730, 161, 31));
        ButtonLibSave->setFont(font1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon3);
        frameLibFolder = new QFrame(EditLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 201, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        pushButton = new QPushButton(EditLibraryDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(720, 730, 111, 31));
        pushButton->setFont(font1);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon4);
        label_8 = new QLabel(EditLibraryDialog);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 270, 491, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setTextFormat(Qt::AutoText);
        label_8->setAlignment(Qt::AlignCenter);
        framePickLayer = new QFrame(EditLibraryDialog);
        framePickLayer->setObjectName("framePickLayer");
        framePickLayer->setGeometry(QRect(10, 290, 491, 28));
        framePickLayer->setFrameShape(QFrame::NoFrame);
        framePickLayer->setFrameShadow(QFrame::Plain);
        frameGenLayer = new QFrame(EditLibraryDialog);
        frameGenLayer->setObjectName("frameGenLayer");
        frameGenLayer->setGeometry(QRect(10, 340, 491, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);
        label_9 = new QLabel(EditLibraryDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 320, 491, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignCenter);
        frame_2 = new QFrame(EditLibraryDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(300, 470, 361, 241));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_44 = new QLabel(frame_2);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(10, 78, 221, 21));
        label_44->setFrameShape(QFrame::Panel);
        label_44->setFrameShadow(QFrame::Sunken);
        label_44->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_27 = new QLabel(frame_2);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(10, 8, 241, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinWidth = new QSpinBox(frame_2);
        EditMinWidth->setObjectName("EditMinWidth");
        EditMinWidth->setGeometry(QRect(258, 8, 91, 22));
        EditMinWidth->setMaximum(999999);
        label_28 = new QLabel(frame_2);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(10, 30, 241, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_43 = new QLabel(frame_2);
        label_43->setObjectName("label_43");
        label_43->setGeometry(QRect(10, 56, 221, 21));
        label_43->setFrameShape(QFrame::Panel);
        label_43->setFrameShadow(QFrame::Sunken);
        label_43->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinGap = new QSpinBox(frame_2);
        EditMinGap->setObjectName("EditMinGap");
        EditMinGap->setGeometry(QRect(258, 30, 91, 22));
        EditMinGap->setMaximum(999999);
        EditWidthToIgnoreEdge = new QSpinBox(frame_2);
        EditWidthToIgnoreEdge->setObjectName("EditWidthToIgnoreEdge");
        EditWidthToIgnoreEdge->setGeometry(QRect(260, 140, 91, 22));
        EditWidthToIgnoreEdge->setMaximum(2147483647);
        label_45 = new QLabel(frame_2);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(12, 140, 241, 21));
        label_45->setFrameShape(QFrame::Panel);
        label_45->setFrameShadow(QFrame::Sunken);
        label_45->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_46 = new QLabel(frame_2);
        label_46->setObjectName("label_46");
        label_46->setGeometry(QRect(12, 180, 241, 21));
        label_46->setFrameShape(QFrame::Panel);
        label_46->setFrameShadow(QFrame::Sunken);
        label_46->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKNickRate = new QSpinBox(frame_2);
        EditOKNickRate->setObjectName("EditOKNickRate");
        EditOKNickRate->setGeometry(QRect(260, 180, 91, 22));
        EditOKNickRate->setMaximum(2147483647);
        EditOKShortRate = new QSpinBox(frame_2);
        EditOKShortRate->setObjectName("EditOKShortRate");
        EditOKShortRate->setGeometry(QRect(260, 210, 91, 22));
        EditOKShortRate->setMaximum(2147483647);
        label_47 = new QLabel(frame_2);
        label_47->setObjectName("label_47");
        label_47->setGeometry(QRect(12, 210, 241, 21));
        label_47->setFrameShape(QFrame::Panel);
        label_47->setFrameShadow(QFrame::Sunken);
        label_47->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditMaxArea = new QLineEdit(frame_2);
        lineEditMaxArea->setObjectName("lineEditMaxArea");
        lineEditMaxArea->setGeometry(QRect(240, 78, 113, 21));
        lineEditMinArea = new QLineEdit(frame_2);
        lineEditMinArea->setObjectName("lineEditMinArea");
        lineEditMinArea->setGeometry(QRect(240, 56, 113, 21));
        label_29 = new QLabel(frame_2);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(12, 110, 241, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinSize = new QSpinBox(frame_2);
        EditMinSize->setObjectName("EditMinSize");
        EditMinSize->setGeometry(QRect(260, 110, 91, 22));
        EditMinSize->setMaximum(999999);
        frame_3 = new QFrame(EditLibraryDialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(670, 470, 171, 211));
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
        frame_4 = new QFrame(EditLibraryDialog);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 370, 361, 91));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        EditLimitDot = new QSpinBox(frame_4);
        EditLimitDot->setObjectName("EditLimitDot");
        EditLimitDot->setGeometry(QRect(200, 10, 71, 22));
        EditLimitDot->setMaximum(99999);
        label_39 = new QLabel(frame_4);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(10, 10, 181, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditBlockMinArea = new QLineEdit(frame_4);
        lineEditBlockMinArea->setObjectName("lineEditBlockMinArea");
        lineEditBlockMinArea->setGeometry(QRect(240, 40, 113, 21));
        label_55 = new QLabel(frame_4);
        label_55->setObjectName("label_55");
        label_55->setGeometry(QRect(10, 62, 221, 21));
        label_55->setFrameShape(QFrame::Panel);
        label_55->setFrameShadow(QFrame::Sunken);
        label_55->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditBlockMaxArea = new QLineEdit(frame_4);
        lineEditBlockMaxArea->setObjectName("lineEditBlockMaxArea");
        lineEditBlockMaxArea->setGeometry(QRect(240, 62, 113, 21));
        label_56 = new QLabel(frame_4);
        label_56->setObjectName("label_56");
        label_56->setGeometry(QRect(10, 40, 221, 21));
        label_56->setFrameShape(QFrame::Panel);
        label_56->setFrameShadow(QFrame::Sunken);
        label_56->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(EditLibraryDialog);

        QMetaObject::connectSlotsByName(EditLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *EditLibraryDialog)
    {
        EditLibraryDialog->setWindowTitle(QCoreApplication::translate("EditLibraryDialog", "Library", nullptr));
        label_4->setText(QCoreApplication::translate("EditLibraryDialog", "\345\220\215\347\247\260", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditLibraryDialog", "Delete", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditLibraryDialog", "Clear new", nullptr));
        checkBoxDarkside->setText(QCoreApplication::translate("EditLibraryDialog", "\346\232\227\345\201\264", nullptr));
        checkBoxCompareToMaster->setText(QCoreApplication::translate("EditLibraryDialog", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217\343\201\250\343\201\256\346\257\224\350\274\203", nullptr));
        label_40->setText(QCoreApplication::translate("EditLibraryDialog", "\351\203\250\345\210\206\347\232\204\357\274\222\345\200\244\345\214\226\343\201\256\343\202\265\343\202\244\343\202\272", nullptr));
        label_41->setText(QCoreApplication::translate("EditLibraryDialog", "\357\274\222\345\200\244\345\214\226\345\217\202\347\205\247\350\274\235\345\272\246\345\200\244", nullptr));
        label_42->setText(QCoreApplication::translate("EditLibraryDialog", "\343\203\236\343\202\271\343\202\277\343\203\274\343\201\250\343\201\256\346\257\224\350\274\203\346\231\202\343\201\256\346\216\242\347\264\242\347\257\204\345\233\262", nullptr));
        checkBoxAutoBinarize->setText(QCoreApplication::translate("EditLibraryDialog", "\350\207\252\345\213\225", nullptr));
        checkBoxReduceNoise->setText(QCoreApplication::translate("EditLibraryDialog", "\343\203\216\343\202\244\343\202\272\345\211\212\351\231\244", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditLibraryDialog", "Name", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditLibraryDialog", "Library Name", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditLibraryDialog", "Save New", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditLibraryDialog", "12345", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditLibraryDialog", "Update", nullptr));
        pushButton->setText(QCoreApplication::translate("EditLibraryDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_8->setText(QCoreApplication::translate("EditLibraryDialog", "\346\212\275\345\207\272\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        label_9->setText(QCoreApplication::translate("EditLibraryDialog", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        label_44->setText(QCoreApplication::translate("EditLibraryDialog", "\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_27->setText(QCoreApplication::translate("EditLibraryDialog", "\346\234\200\345\260\217\343\203\251\343\202\244\343\203\263\345\271\205", nullptr));
        label_28->setText(QCoreApplication::translate("EditLibraryDialog", "\346\234\200\345\260\217\351\226\223\351\232\224", nullptr));
        label_43->setText(QCoreApplication::translate("EditLibraryDialog", "\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_45->setText(QCoreApplication::translate("EditLibraryDialog", "\350\274\252\351\203\255\347\204\241\350\246\226\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        label_46->setText(QCoreApplication::translate("EditLibraryDialog", "\346\254\240\343\201\221\345\210\244\345\256\232\343\201\256\345\244\247\343\201\215\343\201\225\357\274\210\357\274\220\357\275\236100\357\274\205\357\274\211", nullptr));
        label_47->setText(QCoreApplication::translate("EditLibraryDialog", "\347\252\201\345\207\272\345\210\244\345\256\232\343\201\256\345\244\247\343\201\215\343\201\225\357\274\210\357\274\220\357\275\236100\357\274\205\357\274\211", nullptr));
        label_29->setText(QCoreApplication::translate("EditLibraryDialog", "\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_48->setText(QCoreApplication::translate("EditLibraryDialog", "OK\345\210\244\345\256\232\343\201\256\350\274\235\345\272\246\345\271\205", nullptr));
        label_49->setText(QCoreApplication::translate("EditLibraryDialog", "\345\206\205\345\201\264", nullptr));
        label_51->setText(QCoreApplication::translate("EditLibraryDialog", "\346\232\227\345\201\264", nullptr));
        label_53->setText(QCoreApplication::translate("EditLibraryDialog", "\345\244\226\345\201\264", nullptr));
        label_54->setText(QCoreApplication::translate("EditLibraryDialog", "\346\232\227\345\201\264", nullptr));
        label_52->setText(QCoreApplication::translate("EditLibraryDialog", "\346\230\216\345\201\264", nullptr));
        label_50->setText(QCoreApplication::translate("EditLibraryDialog", "\346\230\216\345\201\264", nullptr));
        label_39->setText(QCoreApplication::translate("EditLibraryDialog", "\351\231\220\347\225\214\343\202\265\343\202\244\343\202\272", nullptr));
        label_55->setText(QCoreApplication::translate("EditLibraryDialog", "\347\224\237\346\210\220\346\231\202\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_56->setText(QCoreApplication::translate("EditLibraryDialog", "\347\224\237\346\210\220\346\231\202\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLibraryDialog: public Ui_EditLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLIBRARYDIALOG_H
