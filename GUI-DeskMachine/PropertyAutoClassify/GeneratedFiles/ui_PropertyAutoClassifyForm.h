/********************************************************************************
** Form generated from reading UI file 'PropertyAutoClassifyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYAUTOCLASSIFYFORM_H
#define UI_PROPERTYAUTOCLASSIFYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyAutoClassifyFormClass
{
public:
    QLabel *label_30;
    QTableWidget *tableWidgetLibList;
    QPushButton *pushButtonEditLibrary;
    QPushButton *ButtonPickupTest;
    QPushButton *pushButtonEditLibFolder;
    QPushButton *pushButtonSetFromAll;
    QPushButton *pushButtonGetBack;
    QLabel *label_31;
    QPushButton *pushButtonSetFrom;
    QLabel *labelLibFolderName;
    QTableWidget *tableWidgetGeneratedLibList;
    QPushButton *ButtonGenerateLibs;
    QPushButton *pushButtonGetBackAll;
    QPushButton *ButtonPickupClearTest;
    QFrame *frame_4;
    QLabel *label_3;
    QSpinBox *EditNoiseSize;
    QSpinBox *EditSpaceToOutline;
    QLabel *label_16;
    QSpinBox *EditPriority;
    QLabel *label_14;
    QLabel *label_15;
    QPushButton *ButtonLibSave;
    QFrame *frame;
    QTableWidget *tableWidgetBlockInfo;
    QToolButton *toolButtonAreaMode;

    void setupUi(GUIFormBase *PropertyAutoClassifyFormClass)
    {
        if (PropertyAutoClassifyFormClass->objectName().isEmpty())
            PropertyAutoClassifyFormClass->setObjectName(QString::fromUtf8("PropertyAutoClassifyFormClass"));
        PropertyAutoClassifyFormClass->resize(402, 661);
        label_30 = new QLabel(PropertyAutoClassifyFormClass);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(10, 50, 161, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetLibList = new QTableWidget(PropertyAutoClassifyFormClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName(QString::fromUtf8("tableWidgetLibList"));
        tableWidgetLibList->setGeometry(QRect(10, 70, 161, 161));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonEditLibrary = new QPushButton(PropertyAutoClassifyFormClass);
        pushButtonEditLibrary->setObjectName(QString::fromUtf8("pushButtonEditLibrary"));
        pushButtonEditLibrary->setGeometry(QRect(230, 10, 161, 31));
        QFont font;
        font.setPointSize(12);
        pushButtonEditLibrary->setFont(font);
        ButtonPickupTest = new QPushButton(PropertyAutoClassifyFormClass);
        ButtonPickupTest->setObjectName(QString::fromUtf8("ButtonPickupTest"));
        ButtonPickupTest->setGeometry(QRect(10, 254, 191, 51));
        QFont font1;
        font1.setPointSize(11);
        ButtonPickupTest->setFont(font1);
        pushButtonEditLibFolder = new QPushButton(PropertyAutoClassifyFormClass);
        pushButtonEditLibFolder->setObjectName(QString::fromUtf8("pushButtonEditLibFolder"));
        pushButtonEditLibFolder->setGeometry(QRect(10, 10, 101, 31));
        pushButtonSetFromAll = new QPushButton(PropertyAutoClassifyFormClass);
        pushButtonSetFromAll->setObjectName(QString::fromUtf8("pushButtonSetFromAll"));
        pushButtonSetFromAll->setGeometry(QRect(180, 170, 39, 23));
        pushButtonGetBack = new QPushButton(PropertyAutoClassifyFormClass);
        pushButtonGetBack->setObjectName(QString::fromUtf8("pushButtonGetBack"));
        pushButtonGetBack->setGeometry(QRect(180, 120, 39, 23));
        label_31 = new QLabel(PropertyAutoClassifyFormClass);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(230, 50, 161, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSetFrom = new QPushButton(PropertyAutoClassifyFormClass);
        pushButtonSetFrom->setObjectName(QString::fromUtf8("pushButtonSetFrom"));
        pushButtonSetFrom->setGeometry(QRect(180, 90, 39, 23));
        labelLibFolderName = new QLabel(PropertyAutoClassifyFormClass);
        labelLibFolderName->setObjectName(QString::fromUtf8("labelLibFolderName"));
        labelLibFolderName->setGeometry(QRect(120, 10, 101, 31));
        QFont font2;
        font2.setPointSize(16);
        labelLibFolderName->setFont(font2);
        tableWidgetGeneratedLibList = new QTableWidget(PropertyAutoClassifyFormClass);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetGeneratedLibList->setObjectName(QString::fromUtf8("tableWidgetGeneratedLibList"));
        tableWidgetGeneratedLibList->setGeometry(QRect(230, 70, 161, 161));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonGenerateLibs = new QPushButton(PropertyAutoClassifyFormClass);
        ButtonGenerateLibs->setObjectName(QString::fromUtf8("ButtonGenerateLibs"));
        ButtonGenerateLibs->setGeometry(QRect(10, 360, 191, 71));
        ButtonGenerateLibs->setFont(font1);
        pushButtonGetBackAll = new QPushButton(PropertyAutoClassifyFormClass);
        pushButtonGetBackAll->setObjectName(QString::fromUtf8("pushButtonGetBackAll"));
        pushButtonGetBackAll->setGeometry(QRect(180, 200, 39, 23));
        ButtonPickupClearTest = new QPushButton(PropertyAutoClassifyFormClass);
        ButtonPickupClearTest->setObjectName(QString::fromUtf8("ButtonPickupClearTest"));
        ButtonPickupClearTest->setGeometry(QRect(10, 310, 191, 31));
        ButtonPickupClearTest->setFont(font1);
        frame_4 = new QFrame(PropertyAutoClassifyFormClass);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(210, 250, 181, 181));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 0, 181, 21));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNoiseSize = new QSpinBox(frame_4);
        EditNoiseSize->setObjectName(QString::fromUtf8("EditNoiseSize"));
        EditNoiseSize->setGeometry(QRect(110, 60, 61, 31));
        EditNoiseSize->setFont(font);
        EditSpaceToOutline = new QSpinBox(frame_4);
        EditSpaceToOutline->setObjectName(QString::fromUtf8("EditSpaceToOutline"));
        EditSpaceToOutline->setGeometry(QRect(110, 30, 61, 31));
        EditSpaceToOutline->setFont(font);
        label_16 = new QLabel(frame_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 90, 101, 31));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPriority = new QSpinBox(frame_4);
        EditPriority->setObjectName(QString::fromUtf8("EditPriority"));
        EditPriority->setGeometry(QRect(110, 90, 61, 31));
        EditPriority->setFont(font);
        label_14 = new QLabel(frame_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 30, 101, 31));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_15 = new QLabel(frame_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 60, 101, 31));
        label_15->setFrameShape(QFrame::Panel);
        label_15->setFrameShadow(QFrame::Sunken);
        label_15->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibSave = new QPushButton(frame_4);
        ButtonLibSave->setObjectName(QString::fromUtf8("ButtonLibSave"));
        ButtonLibSave->setGeometry(QRect(10, 130, 161, 41));
        frame = new QFrame(PropertyAutoClassifyFormClass);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 450, 381, 201));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        tableWidgetBlockInfo = new QTableWidget(frame);
        if (tableWidgetBlockInfo->columnCount() < 3)
            tableWidgetBlockInfo->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetBlockInfo->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetBlockInfo->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetBlockInfo->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        tableWidgetBlockInfo->setObjectName(QString::fromUtf8("tableWidgetBlockInfo"));
        tableWidgetBlockInfo->setGeometry(QRect(10, 60, 361, 131));
        tableWidgetBlockInfo->setSelectionMode(QAbstractItemView::MultiSelection);
        toolButtonAreaMode = new QToolButton(frame);
        toolButtonAreaMode->setObjectName(QString::fromUtf8("toolButtonAreaMode"));
        toolButtonAreaMode->setGeometry(QRect(10, 10, 361, 31));
        toolButtonAreaMode->setCheckable(true);
        toolButtonAreaMode->setAutoExclusive(true);

        retranslateUi(PropertyAutoClassifyFormClass);

        QMetaObject::connectSlotsByName(PropertyAutoClassifyFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyAutoClassifyFormClass)
    {
        PropertyAutoClassifyFormClass->setWindowTitle(QCoreApplication::translate("PropertyAutoClassifyFormClass", "PropertyAutoClassifyForm", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "Name", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        ButtonPickupTest->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "\345\215\230\344\270\200\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\343\201\256\346\212\275\345\207\272", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "=>>", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "<=", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "=>", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "\357\274\270\357\274\270\357\274\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "Name", nullptr));
        ButtonGenerateLibs->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "\344\270\212\343\201\256\345\205\250\343\201\246\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\347\224\237\346\210\220", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "<<=", nullptr));
        ButtonPickupClearTest->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "\346\212\275\345\207\272\343\201\256\343\202\257\343\203\252\343\202\242", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\227\343\203\255\343\203\221\343\203\206\343\202\243", nullptr));
        label_16->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "\345\204\252\345\205\210\345\272\246", nullptr));
        label_14->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "\350\274\252\351\203\255\343\201\213\343\202\211\343\201\256\351\226\223\351\232\224", nullptr));
        label_15->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "\343\203\207\343\203\274\343\202\277\343\203\231\343\203\274\343\202\271\343\201\270\343\201\256\346\233\264\346\226\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetBlockInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetBlockInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetBlockInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "\351\240\230\345\237\237\347\267\217\346\225\260", nullptr));
        toolButtonAreaMode->setText(QCoreApplication::translate("PropertyAutoClassifyFormClass", "\347\224\237\346\210\220\343\201\225\343\202\214\343\201\237\351\240\230\345\237\237\346\203\205\345\240\261", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyAutoClassifyFormClass: public Ui_PropertyAutoClassifyFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYAUTOCLASSIFYFORM_H
