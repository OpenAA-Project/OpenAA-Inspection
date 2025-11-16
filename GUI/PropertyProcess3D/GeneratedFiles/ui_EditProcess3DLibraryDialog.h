/********************************************************************************
** Form generated from reading UI file 'EditProcess3DLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITPROCESS3DLIBRARYDIALOG_H
#define UI_EDITPROCESS3DLIBRARYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
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

class Ui_EditProcess3DLibraryDialog
{
public:
    QPushButton *ButtonLibNew;
    QTableWidget *tableWidgetLibList;
    QPushButton *ButtonLibSaveNew;
    QPushButton *pushButtonClose;
    QLineEdit *EditLibID;
    QFrame *frameLibFolder;
    QPushButton *ButtonLibUpdate;
    QLabel *label_4;
    QFrame *frameGenLayer;
    QLabel *label_9;
    QPushButton *ButtonLibDelete;
    QLineEdit *EditLibName;
    QFrame *frame_2;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_30;
    QDoubleSpinBox *doubleSpinBoxBaseCycleDot;
    QDoubleSpinBox *doubleSpinBoxHeightPerShift;
    QLabel *label_65;
    QSpinBox *spinBoxVFilterLength;
    QFrame *frame_15;
    QLabel *label_58;
    QLabel *label_59;
    QLabel *label_63;
    QDoubleSpinBox *doubleSpinBoxLargeTilt;
    QDoubleSpinBox *doubleSpinBoxLargeFlatness;
    QFrame *frame_16;
    QLabel *label_62;
    QLabel *label_64;
    QLabel *label_67;
    QDoubleSpinBox *doubleSpinBoxSmallFlatness;
    QSpinBox *spinBoxSmallAreaSize;

    void setupUi(QDialog *EditProcess3DLibraryDialog)
    {
        if (EditProcess3DLibraryDialog->objectName().isEmpty())
            EditProcess3DLibraryDialog->setObjectName("EditProcess3DLibraryDialog");
        EditProcess3DLibraryDialog->resize(600, 709);
        ButtonLibNew = new QPushButton(EditProcess3DLibraryDialog);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(220, 630, 91, 31));
        QFont font;
        font.setPointSize(11);
        ButtonLibNew->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon);
        tableWidgetLibList = new QTableWidget(EditProcess3DLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 250, 191, 371));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonLibSaveNew = new QPushButton(EditProcess3DLibraryDialog);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(410, 630, 91, 31));
        ButtonLibSaveNew->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon1);
        pushButtonClose = new QPushButton(EditProcess3DLibraryDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(510, 670, 81, 31));
        pushButtonClose->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon2);
        EditLibID = new QLineEdit(EditProcess3DLibraryDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(270, 20, 81, 31));
        QFont font1;
        font1.setPointSize(12);
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        frameLibFolder = new QFrame(EditProcess3DLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 30, 191, 211));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonLibUpdate = new QPushButton(EditProcess3DLibraryDialog);
        ButtonLibUpdate->setObjectName("ButtonLibUpdate");
        ButtonLibUpdate->setGeometry(QRect(510, 630, 81, 31));
        ButtonLibUpdate->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibUpdate->setIcon(icon3);
        label_4 = new QLabel(EditProcess3DLibraryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(220, 20, 51, 31));
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameGenLayer = new QFrame(EditProcess3DLibraryDialog);
        frameGenLayer->setObjectName("frameGenLayer");
        frameGenLayer->setGeometry(QRect(210, 80, 381, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);
        label_9 = new QLabel(EditProcess3DLibraryDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(210, 60, 381, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignCenter);
        ButtonLibDelete = new QPushButton(EditProcess3DLibraryDialog);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(320, 630, 81, 31));
        ButtonLibDelete->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon4);
        EditLibName = new QLineEdit(EditProcess3DLibraryDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(350, 20, 211, 31));
        EditLibName->setFont(font1);
        frame_2 = new QFrame(EditProcess3DLibraryDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(210, 130, 371, 101));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(40, 10, 191, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(40, 40, 191, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_30 = new QLabel(frame_2);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(0, 0, 31, 101));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Raised);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_30->setIndent(1);
        doubleSpinBoxBaseCycleDot = new QDoubleSpinBox(frame_2);
        doubleSpinBoxBaseCycleDot->setObjectName("doubleSpinBoxBaseCycleDot");
        doubleSpinBoxBaseCycleDot->setGeometry(QRect(240, 10, 111, 24));
        doubleSpinBoxBaseCycleDot->setDecimals(3);
        doubleSpinBoxBaseCycleDot->setMaximum(99999999.000000000000000);
        doubleSpinBoxHeightPerShift = new QDoubleSpinBox(frame_2);
        doubleSpinBoxHeightPerShift->setObjectName("doubleSpinBoxHeightPerShift");
        doubleSpinBoxHeightPerShift->setGeometry(QRect(240, 40, 111, 24));
        doubleSpinBoxHeightPerShift->setDecimals(3);
        doubleSpinBoxHeightPerShift->setMaximum(99999999.000000000000000);
        label_65 = new QLabel(frame_2);
        label_65->setObjectName("label_65");
        label_65->setGeometry(QRect(40, 70, 191, 21));
        label_65->setFrameShape(QFrame::Panel);
        label_65->setFrameShadow(QFrame::Sunken);
        label_65->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxVFilterLength = new QSpinBox(frame_2);
        spinBoxVFilterLength->setObjectName("spinBoxVFilterLength");
        spinBoxVFilterLength->setGeometry(QRect(240, 70, 111, 24));
        spinBoxVFilterLength->setMaximum(99999999);
        frame_15 = new QFrame(EditProcess3DLibraryDialog);
        frame_15->setObjectName("frame_15");
        frame_15->setGeometry(QRect(210, 240, 371, 71));
        frame_15->setFrameShape(QFrame::StyledPanel);
        frame_15->setFrameShadow(QFrame::Sunken);
        label_58 = new QLabel(frame_15);
        label_58->setObjectName("label_58");
        label_58->setGeometry(QRect(40, 40, 191, 21));
        label_58->setFrameShape(QFrame::Panel);
        label_58->setFrameShadow(QFrame::Sunken);
        label_58->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_59 = new QLabel(frame_15);
        label_59->setObjectName("label_59");
        label_59->setGeometry(QRect(40, 10, 191, 21));
        label_59->setFrameShape(QFrame::Panel);
        label_59->setFrameShadow(QFrame::Sunken);
        label_59->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_63 = new QLabel(frame_15);
        label_63->setObjectName("label_63");
        label_63->setGeometry(QRect(0, 0, 31, 71));
        label_63->setFrameShape(QFrame::Panel);
        label_63->setFrameShadow(QFrame::Raised);
        label_63->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_63->setIndent(1);
        doubleSpinBoxLargeTilt = new QDoubleSpinBox(frame_15);
        doubleSpinBoxLargeTilt->setObjectName("doubleSpinBoxLargeTilt");
        doubleSpinBoxLargeTilt->setGeometry(QRect(240, 10, 111, 24));
        doubleSpinBoxLargeTilt->setDecimals(3);
        doubleSpinBoxLargeTilt->setMaximum(99999999.000000000000000);
        doubleSpinBoxLargeFlatness = new QDoubleSpinBox(frame_15);
        doubleSpinBoxLargeFlatness->setObjectName("doubleSpinBoxLargeFlatness");
        doubleSpinBoxLargeFlatness->setGeometry(QRect(240, 40, 111, 24));
        doubleSpinBoxLargeFlatness->setDecimals(3);
        doubleSpinBoxLargeFlatness->setMaximum(99999999.000000000000000);
        frame_16 = new QFrame(EditProcess3DLibraryDialog);
        frame_16->setObjectName("frame_16");
        frame_16->setGeometry(QRect(210, 320, 371, 91));
        frame_16->setFrameShape(QFrame::StyledPanel);
        frame_16->setFrameShadow(QFrame::Sunken);
        label_62 = new QLabel(frame_16);
        label_62->setObjectName("label_62");
        label_62->setGeometry(QRect(40, 40, 191, 21));
        label_62->setFrameShape(QFrame::Panel);
        label_62->setFrameShadow(QFrame::Sunken);
        label_62->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_64 = new QLabel(frame_16);
        label_64->setObjectName("label_64");
        label_64->setGeometry(QRect(40, 10, 191, 21));
        label_64->setFrameShape(QFrame::Panel);
        label_64->setFrameShadow(QFrame::Sunken);
        label_64->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_67 = new QLabel(frame_16);
        label_67->setObjectName("label_67");
        label_67->setGeometry(QRect(0, 0, 31, 91));
        label_67->setFrameShape(QFrame::Panel);
        label_67->setFrameShadow(QFrame::Raised);
        label_67->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_67->setIndent(1);
        doubleSpinBoxSmallFlatness = new QDoubleSpinBox(frame_16);
        doubleSpinBoxSmallFlatness->setObjectName("doubleSpinBoxSmallFlatness");
        doubleSpinBoxSmallFlatness->setGeometry(QRect(240, 10, 111, 24));
        doubleSpinBoxSmallFlatness->setDecimals(3);
        doubleSpinBoxSmallFlatness->setMaximum(99999999.000000000000000);
        spinBoxSmallAreaSize = new QSpinBox(frame_16);
        spinBoxSmallAreaSize->setObjectName("spinBoxSmallAreaSize");
        spinBoxSmallAreaSize->setGeometry(QRect(240, 40, 111, 24));
        spinBoxSmallAreaSize->setMaximum(99999999);

        retranslateUi(EditProcess3DLibraryDialog);

        QMetaObject::connectSlotsByName(EditProcess3DLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *EditProcess3DLibraryDialog)
    {
        EditProcess3DLibraryDialog->setWindowTitle(QCoreApplication::translate("EditProcess3DLibraryDialog", "Dialog", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "Clear new", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "Name", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "Save New", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "12345", nullptr));
        ButtonLibUpdate->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "Update", nullptr));
        label_4->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "\345\220\215\347\247\260", nullptr));
        label_9->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "Delete", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "Library Name", nullptr));
        label_7->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "Base cycle dot", nullptr));
        label_8->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "Height per shift", nullptr));
        label_30->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "<html><head/><body><p>\350\250\255</p><p>\345\256\232</p></body></html>", nullptr));
        label_65->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "Vertical filter length", nullptr));
        label_58->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "Flatness", nullptr));
        label_59->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "Tilt from horizon", nullptr));
        label_63->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "<html><head/><body><p>\345\272\203</p><p>\345\237\237</p></body></html>", nullptr));
        label_62->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "Regular size", nullptr));
        label_64->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "Flatness", nullptr));
        label_67->setText(QCoreApplication::translate("EditProcess3DLibraryDialog", "<html><head/><body><p>\345\260\217</p><p>\351\240\230</p><p>\345\237\237</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditProcess3DLibraryDialog: public Ui_EditProcess3DLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITPROCESS3DLIBRARYDIALOG_H
