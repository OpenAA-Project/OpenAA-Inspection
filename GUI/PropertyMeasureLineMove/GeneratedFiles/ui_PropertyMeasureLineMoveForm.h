/********************************************************************************
** Form generated from reading UI file 'PropertyMeasureLineMoveForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYMEASURELINEMOVEFORM_H
#define UI_PROPERTYMEASURELINEMOVEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyMeasureLineMoveFormClass
{
public:
    QFrame *frame_2;
    QToolButton *toolButtonModeLine;
    QToolButton *toolButtonModeArc;
    QToolButton *toolButtonModeDistance;
    QToolButton *toolButtonModeMark;
    QToolButton *toolButtonModeRxLine;
    QFrame *frame_3;
    QLabel *label_30;
    QLabel *labelLibFolderName;
    QPushButton *pushButtonEditLibFolder;
    QTableWidget *tableWidgetLibList;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTableWidget *tableWidgetLineMoveList;
    QCheckBox *checkBoxSelect1;
    QCheckBox *checkBoxSelect2;
    QWidget *tab_2;
    QFrame *frame;
    QLabel *label_92;
    QSpinBox *EditSearchDot;
    QLabel *label_18;
    QLineEdit *EditLibID;
    QLineEdit *EditLibName;
    QPushButton *pushButtonCreateNew;
    QPushButton *pushButtonUpdate;
    QDoubleSpinBox *doubleSpinBoxThresholdP;
    QDoubleSpinBox *doubleSpinBoxThresholdM;
    QLabel *label_94;
    QLabel *label_93;
    QSpinBox *EditEdgeWidth;
    QLabel *label_95;
    QTableWidget *tableWidgetAlign;
    QPushButton *pushButtonEditLibrary;
    QPushButton *pushButtonExecuteAlign;
    QPushButton *pushButtonLoadCSV;
    QToolButton *toolButtonAlign;

    void setupUi(GUIFormBase *PropertyMeasureLineMoveFormClass)
    {
        if (PropertyMeasureLineMoveFormClass->objectName().isEmpty())
            PropertyMeasureLineMoveFormClass->setObjectName("PropertyMeasureLineMoveFormClass");
        PropertyMeasureLineMoveFormClass->resize(402, 700);
        frame_2 = new QFrame(PropertyMeasureLineMoveFormClass);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(4, 10, 391, 81));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        toolButtonModeLine = new QToolButton(frame_2);
        toolButtonModeLine->setObjectName("toolButtonModeLine");
        toolButtonModeLine->setGeometry(QRect(10, 10, 111, 31));
        toolButtonModeLine->setCheckable(true);
        toolButtonModeLine->setChecked(true);
        toolButtonModeLine->setAutoExclusive(true);
        toolButtonModeArc = new QToolButton(frame_2);
        toolButtonModeArc->setObjectName("toolButtonModeArc");
        toolButtonModeArc->setGeometry(QRect(260, 10, 111, 31));
        toolButtonModeArc->setCheckable(true);
        toolButtonModeArc->setAutoExclusive(true);
        toolButtonModeDistance = new QToolButton(frame_2);
        toolButtonModeDistance->setObjectName("toolButtonModeDistance");
        toolButtonModeDistance->setGeometry(QRect(140, 44, 111, 31));
        toolButtonModeDistance->setCheckable(true);
        toolButtonModeDistance->setAutoExclusive(true);
        toolButtonModeMark = new QToolButton(frame_2);
        toolButtonModeMark->setObjectName("toolButtonModeMark");
        toolButtonModeMark->setGeometry(QRect(10, 44, 111, 31));
        toolButtonModeMark->setCheckable(true);
        toolButtonModeMark->setChecked(false);
        toolButtonModeMark->setAutoExclusive(true);
        toolButtonModeRxLine = new QToolButton(frame_2);
        toolButtonModeRxLine->setObjectName("toolButtonModeRxLine");
        toolButtonModeRxLine->setGeometry(QRect(140, 10, 111, 31));
        toolButtonModeRxLine->setCheckable(true);
        toolButtonModeRxLine->setChecked(false);
        toolButtonModeRxLine->setAutoExclusive(true);
        frame_3 = new QFrame(PropertyMeasureLineMoveFormClass);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 100, 391, 591));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_30 = new QLabel(frame_3);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 50, 361, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelLibFolderName = new QLabel(frame_3);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(140, 10, 231, 31));
        QFont font;
        font.setPointSize(16);
        labelLibFolderName->setFont(font);
        pushButtonEditLibFolder = new QPushButton(frame_3);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(20, 10, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon);
        tableWidgetLibList = new QTableWidget(frame_3);
        if (tableWidgetLibList->columnCount() < 5)
            tableWidgetLibList->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 70, 361, 141));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tabWidget = new QTabWidget(frame_3);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(10, 220, 371, 366));
        tab = new QWidget();
        tab->setObjectName("tab");
        tableWidgetLineMoveList = new QTableWidget(tab);
        if (tableWidgetLineMoveList->columnCount() < 4)
            tableWidgetLineMoveList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetLineMoveList->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetLineMoveList->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetLineMoveList->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetLineMoveList->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        tableWidgetLineMoveList->setObjectName("tableWidgetLineMoveList");
        tableWidgetLineMoveList->setGeometry(QRect(0, 0, 361, 301));
        tableWidgetLineMoveList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidgetLineMoveList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLineMoveList->setSelectionBehavior(QAbstractItemView::SelectRows);
        checkBoxSelect1 = new QCheckBox(tab);
        checkBoxSelect1->setObjectName("checkBoxSelect1");
        checkBoxSelect1->setGeometry(QRect(70, 310, 70, 21));
        checkBoxSelect2 = new QCheckBox(tab);
        checkBoxSelect2->setObjectName("checkBoxSelect2");
        checkBoxSelect2->setGeometry(QRect(190, 310, 70, 21));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        frame = new QFrame(tab_2);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 0, 351, 201));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_92 = new QLabel(frame);
        label_92->setObjectName("label_92");
        label_92->setGeometry(QRect(40, 50, 201, 21));
        label_92->setFrameShape(QFrame::Panel);
        label_92->setFrameShadow(QFrame::Sunken);
        label_92->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSearchDot = new QSpinBox(frame);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(250, 50, 81, 22));
        EditSearchDot->setMaximum(255);
        label_18 = new QLabel(frame);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(10, 10, 61, 31));
        QFont font1;
        font1.setPointSize(12);
        label_18->setFont(font1);
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(frame);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(70, 10, 61, 31));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        EditLibName = new QLineEdit(frame);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(130, 10, 201, 31));
        EditLibName->setFont(font1);
        pushButtonCreateNew = new QPushButton(frame);
        pushButtonCreateNew->setObjectName("pushButtonCreateNew");
        pushButtonCreateNew->setGeometry(QRect(80, 160, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Make.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCreateNew->setIcon(icon1);
        pushButtonUpdate = new QPushButton(frame);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(200, 160, 91, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon2);
        doubleSpinBoxThresholdP = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdP->setObjectName("doubleSpinBoxThresholdP");
        doubleSpinBoxThresholdP->setGeometry(QRect(250, 100, 81, 22));
        doubleSpinBoxThresholdM = new QDoubleSpinBox(frame);
        doubleSpinBoxThresholdM->setObjectName("doubleSpinBoxThresholdM");
        doubleSpinBoxThresholdM->setGeometry(QRect(250, 80, 81, 22));
        label_94 = new QLabel(frame);
        label_94->setObjectName("label_94");
        label_94->setGeometry(QRect(40, 100, 201, 21));
        label_94->setFrameShape(QFrame::Panel);
        label_94->setFrameShadow(QFrame::Sunken);
        label_94->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_93 = new QLabel(frame);
        label_93->setObjectName("label_93");
        label_93->setGeometry(QRect(40, 80, 201, 21));
        label_93->setFrameShape(QFrame::Panel);
        label_93->setFrameShadow(QFrame::Sunken);
        label_93->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditEdgeWidth = new QSpinBox(frame);
        EditEdgeWidth->setObjectName("EditEdgeWidth");
        EditEdgeWidth->setGeometry(QRect(250, 130, 81, 22));
        EditEdgeWidth->setMaximum(255);
        label_95 = new QLabel(frame);
        label_95->setObjectName("label_95");
        label_95->setGeometry(QRect(40, 130, 201, 21));
        label_95->setFrameShape(QFrame::Panel);
        label_95->setFrameShadow(QFrame::Sunken);
        label_95->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetAlign = new QTableWidget(tab_2);
        if (tableWidgetAlign->columnCount() < 2)
            tableWidgetAlign->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetAlign->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetAlign->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        if (tableWidgetAlign->rowCount() < 3)
            tableWidgetAlign->setRowCount(3);
        tableWidgetAlign->setObjectName("tableWidgetAlign");
        tableWidgetAlign->setGeometry(QRect(130, 210, 231, 121));
        tableWidgetAlign->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetAlign->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetAlign->setSelectionMode(QAbstractItemView::SingleSelection);
        pushButtonEditLibrary = new QPushButton(tab_2);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(10, 210, 111, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon3);
        pushButtonExecuteAlign = new QPushButton(tab_2);
        pushButtonExecuteAlign->setObjectName("pushButtonExecuteAlign");
        pushButtonExecuteAlign->setGeometry(QRect(10, 300, 111, 31));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Align.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonExecuteAlign->setIcon(icon4);
        pushButtonLoadCSV = new QPushButton(tab_2);
        pushButtonLoadCSV->setObjectName("pushButtonLoadCSV");
        pushButtonLoadCSV->setGeometry(QRect(10, 240, 111, 31));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Load.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonLoadCSV->setIcon(icon5);
        toolButtonAlign = new QToolButton(tab_2);
        toolButtonAlign->setObjectName("toolButtonAlign");
        toolButtonAlign->setGeometry(QRect(10, 270, 111, 31));
        toolButtonAlign->setCheckable(true);
        toolButtonAlign->setChecked(false);
        toolButtonAlign->setAutoExclusive(true);
        tabWidget->addTab(tab_2, QString());

        retranslateUi(PropertyMeasureLineMoveFormClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PropertyMeasureLineMoveFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyMeasureLineMoveFormClass)
    {
        PropertyMeasureLineMoveFormClass->setWindowTitle(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "PropertyMeasureLineMoveForm", nullptr));
        toolButtonModeLine->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Line", nullptr));
        toolButtonModeArc->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Arc", nullptr));
        toolButtonModeDistance->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Distance", nullptr));
        toolButtonModeMark->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Mark", nullptr));
        toolButtonModeRxLine->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Rx Line", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "\357\274\270\357\274\270\357\274\270", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Search", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "ThrM", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetLibList->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "ThrP", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetLineMoveList->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetLineMoveList->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetLineMoveList->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetLineMoveList->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Search", nullptr));
        checkBoxSelect1->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "\357\274\221\351\201\270\346\212\236", nullptr));
        checkBoxSelect2->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "\357\274\222\351\201\270\346\212\236", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "\347\267\232\343\203\252\343\202\271\343\203\210", nullptr));
        label_92->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        label_18->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "12345", nullptr));
        EditLibName->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Library Name", nullptr));
        pushButtonCreateNew->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Create new", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Update", nullptr));
        label_94->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "\344\270\212\351\231\220\343\201\227\343\201\215\343\201\204\345\200\244\357\274\210\346\234\200\345\260\217\357\274\220\357\274\211", nullptr));
        label_93->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "\344\270\213\351\231\220\343\201\227\343\201\215\343\201\204\345\200\244\357\274\210\346\234\200\345\260\217\357\274\220\357\274\211", nullptr));
        label_95->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "\350\274\252\351\203\255\345\271\205", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetAlign->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Image", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetAlign->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Item", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Edit library", nullptr));
        pushButtonExecuteAlign->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Execute Align", nullptr));
        pushButtonLoadCSV->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Load CSV", nullptr));
        toolButtonAlign->setText(QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "Align", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("PropertyMeasureLineMoveFormClass", "\350\251\263\347\264\260\346\203\205\345\240\261", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyMeasureLineMoveFormClass: public Ui_PropertyMeasureLineMoveFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYMEASURELINEMOVEFORM_H
