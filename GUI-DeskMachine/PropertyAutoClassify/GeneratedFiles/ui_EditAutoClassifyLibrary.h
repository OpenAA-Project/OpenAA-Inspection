/********************************************************************************
** Form generated from reading UI file 'EditAutoClassifyLibrary.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITAUTOCLASSIFYLIBRARY_H
#define UI_EDITAUTOCLASSIFYLIBRARY_H

#include <QtCore/QVariant>
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

class Ui_EditAutoClassifyLibraryClass
{
public:
    QTableWidget *tableWidgetLibList;
    QFrame *frameLibFolder;
    QLabel *label_4;
    QLineEdit *EditLibName;
    QPushButton *ButtonLibDelete;
    QPushButton *pushButton;
    QPushButton *ButtonLibSaveNew;
    QPushButton *ButtonLibSave;
    QLineEdit *EditLibID;
    QPushButton *ButtonLibNew;
    QFrame *frame_4;
    QLabel *label_14;
    QSpinBox *EditSpaceToOutline;
    QLabel *label_15;
    QSpinBox *EditNoiseSize;
    QLabel *label_16;
    QSpinBox *EditPriority;
    QLabel *label_33;
    QFrame *frame_3;
    QSpinBox *EditMinBlockSize;
    QLabel *label_9;
    QSpinBox *EditMaxBlockSize;
    QLabel *label_10;
    QSpinBox *EditMinBlockDots;
    QLabel *label_12;
    QSpinBox *EditMaxBlockDots;
    QLabel *label_11;
    QLabel *label_13;
    QSpinBox *EditLimitBlockSize;
    QLabel *label_32;

    void setupUi(QDialog *EditAutoClassifyLibraryClass)
    {
        if (EditAutoClassifyLibraryClass->objectName().isEmpty())
            EditAutoClassifyLibraryClass->setObjectName(QString::fromUtf8("EditAutoClassifyLibraryClass"));
        EditAutoClassifyLibraryClass->resize(624, 556);
        tableWidgetLibList = new QTableWidget(EditAutoClassifyLibraryClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName(QString::fromUtf8("tableWidgetLibList"));
        tableWidgetLibList->setGeometry(QRect(10, 230, 221, 311));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolder = new QFrame(EditAutoClassifyLibraryClass);
        frameLibFolder->setObjectName(QString::fromUtf8("frameLibFolder"));
        frameLibFolder->setGeometry(QRect(10, 10, 221, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(EditAutoClassifyLibraryClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(240, 10, 51, 31));
        QFont font;
        font.setPointSize(12);
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibName = new QLineEdit(EditAutoClassifyLibraryClass);
        EditLibName->setObjectName(QString::fromUtf8("EditLibName"));
        EditLibName->setGeometry(QRect(370, 10, 211, 31));
        EditLibName->setFont(font);
        ButtonLibDelete = new QPushButton(EditAutoClassifyLibraryClass);
        ButtonLibDelete->setObjectName(QString::fromUtf8("ButtonLibDelete"));
        ButtonLibDelete->setGeometry(QRect(330, 300, 91, 31));
        QFont font1;
        font1.setPointSize(11);
        ButtonLibDelete->setFont(font1);
        pushButton = new QPushButton(EditAutoClassifyLibraryClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(530, 340, 81, 31));
        pushButton->setFont(font1);
        ButtonLibSaveNew = new QPushButton(EditAutoClassifyLibraryClass);
        ButtonLibSaveNew->setObjectName(QString::fromUtf8("ButtonLibSaveNew"));
        ButtonLibSaveNew->setGeometry(QRect(430, 300, 91, 31));
        ButtonLibSaveNew->setFont(font1);
        ButtonLibSave = new QPushButton(EditAutoClassifyLibraryClass);
        ButtonLibSave->setObjectName(QString::fromUtf8("ButtonLibSave"));
        ButtonLibSave->setGeometry(QRect(530, 300, 81, 31));
        ButtonLibSave->setFont(font1);
        EditLibID = new QLineEdit(EditAutoClassifyLibraryClass);
        EditLibID->setObjectName(QString::fromUtf8("EditLibID"));
        EditLibID->setGeometry(QRect(290, 10, 81, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        ButtonLibNew = new QPushButton(EditAutoClassifyLibraryClass);
        ButtonLibNew->setObjectName(QString::fromUtf8("ButtonLibNew"));
        ButtonLibNew->setGeometry(QRect(240, 300, 81, 31));
        ButtonLibNew->setFont(font1);
        frame_4 = new QFrame(EditAutoClassifyLibraryClass);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(240, 200, 371, 81));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Sunken);
        label_14 = new QLabel(frame_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(30, 10, 111, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSpaceToOutline = new QSpinBox(frame_4);
        EditSpaceToOutline->setObjectName(QString::fromUtf8("EditSpaceToOutline"));
        EditSpaceToOutline->setGeometry(QRect(160, 10, 61, 23));
        label_15 = new QLabel(frame_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(30, 30, 111, 21));
        label_15->setFrameShape(QFrame::Panel);
        label_15->setFrameShadow(QFrame::Sunken);
        label_15->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNoiseSize = new QSpinBox(frame_4);
        EditNoiseSize->setObjectName(QString::fromUtf8("EditNoiseSize"));
        EditNoiseSize->setGeometry(QRect(160, 30, 61, 23));
        QFont font2;
        font2.setPointSize(9);
        EditNoiseSize->setFont(font2);
        label_16 = new QLabel(frame_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(30, 50, 111, 21));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPriority = new QSpinBox(frame_4);
        EditPriority->setObjectName(QString::fromUtf8("EditPriority"));
        EditPriority->setGeometry(QRect(160, 50, 61, 23));
        EditPriority->setFont(font2);
        label_33 = new QLabel(frame_4);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(0, 0, 20, 81));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Raised);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_33->setIndent(1);
        frame_3 = new QFrame(EditAutoClassifyLibraryClass);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(240, 50, 371, 141));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        EditMinBlockSize = new QSpinBox(frame_3);
        EditMinBlockSize->setObjectName(QString::fromUtf8("EditMinBlockSize"));
        EditMinBlockSize->setGeometry(QRect(160, 10, 81, 22));
        EditMinBlockSize->setMaximum(1000000);
        label_9 = new QLabel(frame_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 30, 111, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxBlockSize = new QSpinBox(frame_3);
        EditMaxBlockSize->setObjectName(QString::fromUtf8("EditMaxBlockSize"));
        EditMaxBlockSize->setGeometry(QRect(160, 30, 81, 22));
        EditMaxBlockSize->setMaximum(1000000);
        label_10 = new QLabel(frame_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(30, 10, 111, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinBlockDots = new QSpinBox(frame_3);
        EditMinBlockDots->setObjectName(QString::fromUtf8("EditMinBlockDots"));
        EditMinBlockDots->setGeometry(QRect(160, 60, 101, 22));
        EditMinBlockDots->setMaximum(2000000000);
        label_12 = new QLabel(frame_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(30, 60, 111, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxBlockDots = new QSpinBox(frame_3);
        EditMaxBlockDots->setObjectName(QString::fromUtf8("EditMaxBlockDots"));
        EditMaxBlockDots->setGeometry(QRect(160, 80, 101, 22));
        EditMaxBlockDots->setMaximum(2000000000);
        EditMaxBlockDots->setValue(2000000000);
        label_11 = new QLabel(frame_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(30, 80, 111, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_13 = new QLabel(frame_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(30, 110, 111, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLimitBlockSize = new QSpinBox(frame_3);
        EditLimitBlockSize->setObjectName(QString::fromUtf8("EditLimitBlockSize"));
        EditLimitBlockSize->setGeometry(QRect(160, 110, 61, 22));
        EditLimitBlockSize->setMaximum(99999);
        label_32 = new QLabel(frame_3);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(0, 0, 20, 141));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Raised);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_32->setIndent(1);

        retranslateUi(EditAutoClassifyLibraryClass);

        QMetaObject::connectSlotsByName(EditAutoClassifyLibraryClass);
    } // setupUi

    void retranslateUi(QDialog *EditAutoClassifyLibraryClass)
    {
        EditAutoClassifyLibraryClass->setWindowTitle(QCoreApplication::translate("EditAutoClassifyLibraryClass", "EditAutoClassifyLibrary", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "Name", nullptr));
        label_4->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "\345\220\215\347\247\260", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "Library Name", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "Delete", nullptr));
        pushButton->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "Save New", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "Update", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "12345", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "Clear new", nullptr));
        label_14->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "\350\274\252\351\203\255\343\201\213\343\202\211\343\201\256\351\226\223\351\232\224", nullptr));
        label_15->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272", nullptr));
        label_16->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "\345\204\252\345\205\210\345\272\246", nullptr));
        label_33->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "\347\224\237\n"
"\346\210\220", nullptr));
        label_9->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_10->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_12->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_11->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_13->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "\351\231\220\347\225\214\343\202\265\343\202\244\343\202\272", nullptr));
        label_32->setText(QCoreApplication::translate("EditAutoClassifyLibraryClass", "\343\202\265\n"
"\343\202\244\n"
"\343\202\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditAutoClassifyLibraryClass: public Ui_EditAutoClassifyLibraryClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITAUTOCLASSIFYLIBRARY_H
