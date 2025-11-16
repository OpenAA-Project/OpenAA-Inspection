/********************************************************************************
** Form generated from reading UI file 'PropertyThinMetalForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYTHINMETALFORM_H
#define UI_PROPERTYTHINMETALFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyThinMetalForm
{
public:
    QToolButton *toolButtonCreateArea;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *pushButtonEditLibFolder;
    QLabel *labelLibFolderName;
    QTableWidget *tableWidgetLibList;
    QTableWidget *tableWidgetGeneratedLibList;
    QPushButton *pushButtonSetFrom;
    QPushButton *pushButtonGetBack;
    QFrame *frame_4;
    QLineEdit *EditLibName;
    QLabel *label_3;
    QLineEdit *EditLibID;
    QLabel *label_4;
    QPushButton *ButtonLibSave;
    QFrame *frame_6;
    QSpinBox *EditMinSize;
    QLabel *label_9;
    QSpinBox *EditMaxSize;
    QLabel *label_10;
    QSpinBox *EditMinDots;
    QLabel *label_12;
    QSpinBox *EditMaxDots;
    QLabel *label_11;
    QLabel *label_13;
    QSpinBox *EditLimitSize;
    QLabel *label_54;
    QTableWidget *tableWidgetItems;
    QLabel *label_30;
    QLabel *label_31;
    QPushButton *pushButtonGetBackAll;
    QPushButton *pushButtonSetFromAll;
    QPushButton *pushButtonEditLibrary;
    QWidget *page_2;
    QTableWidget *tableWidgetAreaInfo;
    QLabel *label_32;
    QToolButton *toolButtonLibrary;

    void setupUi(GUIFormBase *PropertyThinMetalForm)
    {
        if (PropertyThinMetalForm->objectName().isEmpty())
            PropertyThinMetalForm->setObjectName("PropertyThinMetalForm");
        PropertyThinMetalForm->resize(382, 723);
        toolButtonCreateArea = new QToolButton(PropertyThinMetalForm);
        toolButtonCreateArea->setObjectName("toolButtonCreateArea");
        toolButtonCreateArea->setGeometry(QRect(170, 10, 121, 31));
        toolButtonCreateArea->setCheckable(true);
        toolButtonCreateArea->setAutoExclusive(true);
        stackedWidget = new QStackedWidget(PropertyThinMetalForm);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(-10, 50, 401, 661));
        page = new QWidget();
        page->setObjectName("page");
        pushButtonEditLibFolder = new QPushButton(page);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(20, 0, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon);
        labelLibFolderName = new QLabel(page);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(140, 0, 241, 31));
        QFont font;
        font.setPointSize(16);
        labelLibFolderName->setFont(font);
        tableWidgetLibList = new QTableWidget(page);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 60, 161, 161));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetGeneratedLibList = new QTableWidget(page);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetGeneratedLibList->setObjectName("tableWidgetGeneratedLibList");
        tableWidgetGeneratedLibList->setGeometry(QRect(230, 60, 161, 161));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSetFrom = new QPushButton(page);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(180, 90, 39, 23));
        pushButtonGetBack = new QPushButton(page);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(180, 120, 39, 23));
        frame_4 = new QFrame(page);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 280, 381, 381));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Sunken);
        EditLibName = new QLineEdit(frame_4);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 20, 231, 21));
        QFont font1;
        font1.setPointSize(12);
        EditLibName->setFont(font1);
        label_3 = new QLabel(frame_4);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 381, 21));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(frame_4);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 20, 81, 21));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        label_4 = new QLabel(frame_4);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 20, 51, 21));
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibSave = new QPushButton(frame_4);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(10, 350, 361, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon1);
        frame_6 = new QFrame(frame_4);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(10, 50, 361, 111));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Sunken);
        EditMinSize = new QSpinBox(frame_6);
        EditMinSize->setObjectName("EditMinSize");
        EditMinSize->setGeometry(QRect(160, 10, 81, 22));
        EditMinSize->setMaximum(1000000);
        label_9 = new QLabel(frame_6);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(40, 30, 111, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxSize = new QSpinBox(frame_6);
        EditMaxSize->setObjectName("EditMaxSize");
        EditMaxSize->setGeometry(QRect(160, 30, 81, 22));
        EditMaxSize->setMaximum(1000000);
        label_10 = new QLabel(frame_6);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(40, 10, 111, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinDots = new QSpinBox(frame_6);
        EditMinDots->setObjectName("EditMinDots");
        EditMinDots->setGeometry(QRect(160, 60, 81, 22));
        EditMinDots->setMaximum(2000000000);
        label_12 = new QLabel(frame_6);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(40, 60, 111, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxDots = new QSpinBox(frame_6);
        EditMaxDots->setObjectName("EditMaxDots");
        EditMaxDots->setGeometry(QRect(160, 80, 81, 22));
        EditMaxDots->setMaximum(2000000000);
        EditMaxDots->setValue(2000000000);
        label_11 = new QLabel(frame_6);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(40, 80, 111, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_13 = new QLabel(frame_6);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(250, 60, 101, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLimitSize = new QSpinBox(frame_6);
        EditLimitSize->setObjectName("EditLimitSize");
        EditLimitSize->setGeometry(QRect(280, 80, 61, 22));
        EditLimitSize->setMaximum(99999);
        label_54 = new QLabel(frame_6);
        label_54->setObjectName("label_54");
        label_54->setGeometry(QRect(0, 0, 31, 111));
        label_54->setFrameShape(QFrame::Panel);
        label_54->setFrameShadow(QFrame::Raised);
        label_54->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_54->setIndent(1);
        tableWidgetItems = new QTableWidget(frame_4);
        if (tableWidgetItems->columnCount() < 4)
            tableWidgetItems->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        tableWidgetItems->setObjectName("tableWidgetItems");
        tableWidgetItems->setGeometry(QRect(10, 170, 361, 171));
        tableWidgetItems->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetItems->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_30 = new QLabel(page);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 40, 161, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_31 = new QLabel(page);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(230, 40, 161, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonGetBackAll = new QPushButton(page);
        pushButtonGetBackAll->setObjectName("pushButtonGetBackAll");
        pushButtonGetBackAll->setGeometry(QRect(180, 200, 39, 23));
        pushButtonSetFromAll = new QPushButton(page);
        pushButtonSetFromAll->setObjectName("pushButtonSetFromAll");
        pushButtonSetFromAll->setGeometry(QRect(180, 170, 39, 23));
        pushButtonEditLibrary = new QPushButton(page);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(140, 230, 131, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon2);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        tableWidgetAreaInfo = new QTableWidget(page_2);
        if (tableWidgetAreaInfo->columnCount() < 4)
            tableWidgetAreaInfo->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetAreaInfo->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetAreaInfo->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetAreaInfo->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetAreaInfo->setHorizontalHeaderItem(3, __qtablewidgetitem11);
        tableWidgetAreaInfo->setObjectName("tableWidgetAreaInfo");
        tableWidgetAreaInfo->setGeometry(QRect(10, 20, 381, 481));
        tableWidgetAreaInfo->setSelectionMode(QAbstractItemView::MultiSelection);
        label_32 = new QLabel(page_2);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(10, 0, 381, 21));
        label_32->setFont(font1);
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        stackedWidget->addWidget(page_2);
        toolButtonLibrary = new QToolButton(PropertyThinMetalForm);
        toolButtonLibrary->setObjectName("toolButtonLibrary");
        toolButtonLibrary->setGeometry(QRect(10, 10, 121, 31));
        toolButtonLibrary->setCheckable(true);
        toolButtonLibrary->setChecked(true);
        toolButtonLibrary->setAutoExclusive(true);

        retranslateUi(PropertyThinMetalForm);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PropertyThinMetalForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyThinMetalForm)
    {
        PropertyThinMetalForm->setWindowTitle(QCoreApplication::translate("PropertyThinMetalForm", "Property ThinMetal", nullptr));
        toolButtonCreateArea->setText(QCoreApplication::translate("PropertyThinMetalForm", "Create Block", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyThinMetalForm", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyThinMetalForm", "\357\274\270\357\274\270\357\274\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyThinMetalForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyThinMetalForm", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyThinMetalForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyThinMetalForm", "Name", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyThinMetalForm", "=>", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyThinMetalForm", "<=", nullptr));
        EditLibName->setText(QCoreApplication::translate("PropertyThinMetalForm", "Library Name", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyThinMetalForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\227\343\203\255\343\203\221\343\203\206\343\202\243", nullptr));
        EditLibID->setText(QCoreApplication::translate("PropertyThinMetalForm", "12345", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyThinMetalForm", "\345\220\215\347\247\260", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("PropertyThinMetalForm", "\343\203\207\343\203\274\343\202\277\343\203\231\343\203\274\343\202\271\343\201\270\343\201\256\346\233\264\346\226\260", nullptr));
        label_9->setText(QCoreApplication::translate("PropertyThinMetalForm", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_10->setText(QCoreApplication::translate("PropertyThinMetalForm", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_12->setText(QCoreApplication::translate("PropertyThinMetalForm", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_11->setText(QCoreApplication::translate("PropertyThinMetalForm", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_13->setText(QCoreApplication::translate("PropertyThinMetalForm", "\351\231\220\347\225\214\343\202\265\343\202\244\343\202\272", nullptr));
        label_54->setText(QCoreApplication::translate("PropertyThinMetalForm", "\343\202\265\n"
"\343\202\244\n"
"\343\202\272", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetItems->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyThinMetalForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetItems->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyThinMetalForm", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetItems->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyThinMetalForm", "Item", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetItems->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyThinMetalForm", "Library", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyThinMetalForm", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyThinMetalForm", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyThinMetalForm", "<<=", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyThinMetalForm", "=>>", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyThinMetalForm", "Edit library", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetAreaInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("PropertyThinMetalForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetAreaInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("PropertyThinMetalForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetAreaInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("PropertyThinMetalForm", "\343\203\226\343\203\255\343\203\203\343\202\257\347\267\217\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetAreaInfo->horizontalHeaderItem(3);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("PropertyThinMetalForm", "\343\203\254\343\202\244\343\203\244\343\203\274\357\274\221", nullptr));
        label_32->setText(QCoreApplication::translate("PropertyThinMetalForm", "\344\275\277\347\224\250\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\226\343\203\255\343\203\203\343\202\257\346\203\205\345\240\261", nullptr));
        toolButtonLibrary->setText(QCoreApplication::translate("PropertyThinMetalForm", "Library Test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyThinMetalForm: public Ui_PropertyThinMetalForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYTHINMETALFORM_H
