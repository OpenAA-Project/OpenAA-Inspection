/********************************************************************************
** Form generated from reading UI file 'EasyPropertyDentMeasureForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EASYPROPERTYDENTMEASUREFORM_H
#define UI_EASYPROPERTYDENTMEASUREFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_EasyPropertyDentMeasureForm
{
public:
    QToolButton *toolButtonAutoGenerate;
    QPushButton *PushButtonSaveBladePos;
    QPushButton *PushButtonLoadBladePos;
    QPushButton *PushButtonAddLine;
    QPushButton *PushButtonRemoveLine;
    QToolButton *toolButtonGetCorrentValues;
    QToolButton *toolButtonSetCorrentValues;
    QPushButton *PushButtonManualCreateArea;
    QToolButton *toolButtonGetCorrentValuesTarget;
    QToolButton *toolButtonSetName;
    QToolButton *toolButtonGenFilmUpper;
    QToolButton *toolButtonGenFilmLower;
    QLabel *label;
    QPushButton *pushButtonSetUpper;
    QPushButton *pushButtonSetLower;
    QFrame *frame;
    QToolButton *toolButtonFilm;
    QToolButton *toolButtonBlade;
    QStackedWidget *stackedWidget;
    QWidget *Blade;
    QTableWidget *tableWidgetBladePos;
    QWidget *Film;
    QTableWidget *tableWidgetFilmPos;
    QPushButton *PushButtonGenerateFilmPos;

    void setupUi(GUIFormBase *EasyPropertyDentMeasureForm)
    {
        if (EasyPropertyDentMeasureForm->objectName().isEmpty())
            EasyPropertyDentMeasureForm->setObjectName("EasyPropertyDentMeasureForm");
        EasyPropertyDentMeasureForm->resize(960, 951);
        toolButtonAutoGenerate = new QToolButton(EasyPropertyDentMeasureForm);
        toolButtonAutoGenerate->setObjectName("toolButtonAutoGenerate");
        toolButtonAutoGenerate->setGeometry(QRect(10, 10, 461, 81));
        QFont font;
        font.setPointSize(24);
        toolButtonAutoGenerate->setFont(font);
        toolButtonAutoGenerate->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(220, 254, 220, 255), stop:1 rgba(120, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonAutoGenerate->setCheckable(false);
        toolButtonAutoGenerate->setChecked(false);
        PushButtonSaveBladePos = new QPushButton(EasyPropertyDentMeasureForm);
        PushButtonSaveBladePos->setObjectName("PushButtonSaveBladePos");
        PushButtonSaveBladePos->setGeometry(QRect(50, 620, 231, 61));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font1.setPointSize(16);
        font1.setBold(true);
        PushButtonSaveBladePos->setFont(font1);
        PushButtonSaveBladePos->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonSaveBladePos->setCheckable(true);
        PushButtonSaveBladePos->setAutoDefault(false);
        PushButtonSaveBladePos->setFlat(false);
        PushButtonLoadBladePos = new QPushButton(EasyPropertyDentMeasureForm);
        PushButtonLoadBladePos->setObjectName("PushButtonLoadBladePos");
        PushButtonLoadBladePos->setGeometry(QRect(660, 620, 241, 61));
        PushButtonLoadBladePos->setFont(font1);
        PushButtonLoadBladePos->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonLoadBladePos->setCheckable(true);
        PushButtonLoadBladePos->setAutoDefault(false);
        PushButtonLoadBladePos->setFlat(false);
        PushButtonAddLine = new QPushButton(EasyPropertyDentMeasureForm);
        PushButtonAddLine->setObjectName("PushButtonAddLine");
        PushButtonAddLine->setGeometry(QRect(610, 110, 111, 61));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font2.setPointSize(28);
        font2.setBold(true);
        PushButtonAddLine->setFont(font2);
        PushButtonAddLine->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonAddLine->setCheckable(true);
        PushButtonAddLine->setAutoDefault(false);
        PushButtonAddLine->setFlat(false);
        PushButtonRemoveLine = new QPushButton(EasyPropertyDentMeasureForm);
        PushButtonRemoveLine->setObjectName("PushButtonRemoveLine");
        PushButtonRemoveLine->setGeometry(QRect(740, 110, 111, 61));
        PushButtonRemoveLine->setFont(font2);
        PushButtonRemoveLine->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonRemoveLine->setCheckable(true);
        PushButtonRemoveLine->setAutoDefault(false);
        PushButtonRemoveLine->setFlat(false);
        toolButtonGetCorrentValues = new QToolButton(EasyPropertyDentMeasureForm);
        toolButtonGetCorrentValues->setObjectName("toolButtonGetCorrentValues");
        toolButtonGetCorrentValues->setGeometry(QRect(460, 690, 461, 81));
        QFont font3;
        font3.setPointSize(20);
        font3.setBold(true);
        toolButtonGetCorrentValues->setFont(font3);
        toolButtonGetCorrentValues->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonGetCorrentValues->setCheckable(true);
        toolButtonGetCorrentValues->setAutoExclusive(true);
        toolButtonSetCorrentValues = new QToolButton(EasyPropertyDentMeasureForm);
        toolButtonSetCorrentValues->setObjectName("toolButtonSetCorrentValues");
        toolButtonSetCorrentValues->setGeometry(QRect(40, 690, 301, 81));
        QFont font4;
        font4.setPointSize(20);
        toolButtonSetCorrentValues->setFont(font4);
        toolButtonSetCorrentValues->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonSetCorrentValues->setCheckable(true);
        toolButtonSetCorrentValues->setAutoExclusive(true);
        PushButtonManualCreateArea = new QPushButton(EasyPropertyDentMeasureForm);
        PushButtonManualCreateArea->setObjectName("PushButtonManualCreateArea");
        PushButtonManualCreateArea->setGeometry(QRect(530, 10, 391, 91));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font5.setPointSize(24);
        PushButtonManualCreateArea->setFont(font5);
        PushButtonManualCreateArea->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonManualCreateArea->setCheckable(true);
        PushButtonManualCreateArea->setAutoExclusive(false);
        PushButtonManualCreateArea->setAutoDefault(false);
        PushButtonManualCreateArea->setFlat(false);
        toolButtonGetCorrentValuesTarget = new QToolButton(EasyPropertyDentMeasureForm);
        toolButtonGetCorrentValuesTarget->setObjectName("toolButtonGetCorrentValuesTarget");
        toolButtonGetCorrentValuesTarget->setGeometry(QRect(460, 780, 461, 81));
        toolButtonGetCorrentValuesTarget->setFont(font3);
        toolButtonGetCorrentValuesTarget->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonGetCorrentValuesTarget->setCheckable(true);
        toolButtonGetCorrentValuesTarget->setAutoExclusive(true);
        toolButtonSetName = new QToolButton(EasyPropertyDentMeasureForm);
        toolButtonSetName->setObjectName("toolButtonSetName");
        toolButtonSetName->setGeometry(QRect(10, 100, 461, 81));
        toolButtonSetName->setFont(font);
        toolButtonSetName->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonSetName->setCheckable(true);
        toolButtonSetName->setChecked(true);
        toolButtonGenFilmUpper = new QToolButton(EasyPropertyDentMeasureForm);
        toolButtonGenFilmUpper->setObjectName("toolButtonGenFilmUpper");
        toolButtonGenFilmUpper->setGeometry(QRect(10, 810, 211, 71));
        toolButtonGenFilmUpper->setCheckable(true);
        toolButtonGenFilmLower = new QToolButton(EasyPropertyDentMeasureForm);
        toolButtonGenFilmLower->setObjectName("toolButtonGenFilmLower");
        toolButtonGenFilmLower->setGeometry(QRect(230, 810, 211, 71));
        toolButtonGenFilmLower->setCheckable(true);
        label = new QLabel(EasyPropertyDentMeasureForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 780, 431, 31));
        label->setAlignment(Qt::AlignCenter);
        pushButtonSetUpper = new QPushButton(EasyPropertyDentMeasureForm);
        pushButtonSetUpper->setObjectName("pushButtonSetUpper");
        pushButtonSetUpper->setGeometry(QRect(10, 890, 211, 41));
        pushButtonSetLower = new QPushButton(EasyPropertyDentMeasureForm);
        pushButtonSetLower->setObjectName("pushButtonSetLower");
        pushButtonSetLower->setGeometry(QRect(230, 890, 211, 41));
        frame = new QFrame(EasyPropertyDentMeasureForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 190, 731, 61));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonFilm = new QToolButton(frame);
        toolButtonFilm->setObjectName("toolButtonFilm");
        toolButtonFilm->setGeometry(QRect(330, 0, 311, 51));
        toolButtonFilm->setFont(font);
        toolButtonFilm->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(220, 220, 220, 255), stop:1 rgba(120, 120, 120, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 255, 255), stop:1 rgba(0, 141, 255, 255));\n"
"}"));
        toolButtonFilm->setCheckable(true);
        toolButtonFilm->setChecked(false);
        toolButtonFilm->setAutoExclusive(true);
        toolButtonBlade = new QToolButton(frame);
        toolButtonBlade->setObjectName("toolButtonBlade");
        toolButtonBlade->setGeometry(QRect(10, 0, 311, 51));
        toolButtonBlade->setFont(font);
        toolButtonBlade->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(220, 220, 220, 255), stop:1 rgba(120, 120, 120, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 255, 255), stop:1 rgba(0, 141, 255, 255));\n"
"}"));
        toolButtonBlade->setCheckable(true);
        toolButtonBlade->setChecked(true);
        toolButtonBlade->setAutoExclusive(true);
        stackedWidget = new QStackedWidget(EasyPropertyDentMeasureForm);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 250, 961, 371));
        Blade = new QWidget();
        Blade->setObjectName("Blade");
        tableWidgetBladePos = new QTableWidget(Blade);
        if (tableWidgetBladePos->columnCount() < 11)
            tableWidgetBladePos->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        if (tableWidgetBladePos->rowCount() < 1)
            tableWidgetBladePos->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetBladePos->setVerticalHeaderItem(0, __qtablewidgetitem11);
        tableWidgetBladePos->setObjectName("tableWidgetBladePos");
        tableWidgetBladePos->setGeometry(QRect(10, 0, 941, 361));
        QFont font6;
        font6.setPointSize(11);
        tableWidgetBladePos->setFont(font6);
        tableWidgetBladePos->verticalHeader()->setMinimumSectionSize(45);
        tableWidgetBladePos->verticalHeader()->setDefaultSectionSize(45);
        stackedWidget->addWidget(Blade);
        Film = new QWidget();
        Film->setObjectName("Film");
        tableWidgetFilmPos = new QTableWidget(Film);
        if (tableWidgetFilmPos->columnCount() < 11)
            tableWidgetFilmPos->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidgetFilmPos->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidgetFilmPos->setHorizontalHeaderItem(1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidgetFilmPos->setHorizontalHeaderItem(2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidgetFilmPos->setHorizontalHeaderItem(3, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidgetFilmPos->setHorizontalHeaderItem(4, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidgetFilmPos->setHorizontalHeaderItem(5, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidgetFilmPos->setHorizontalHeaderItem(6, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidgetFilmPos->setHorizontalHeaderItem(7, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidgetFilmPos->setHorizontalHeaderItem(8, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidgetFilmPos->setHorizontalHeaderItem(9, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidgetFilmPos->setHorizontalHeaderItem(10, __qtablewidgetitem22);
        if (tableWidgetFilmPos->rowCount() < 1)
            tableWidgetFilmPos->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidgetFilmPos->setVerticalHeaderItem(0, __qtablewidgetitem23);
        tableWidgetFilmPos->setObjectName("tableWidgetFilmPos");
        tableWidgetFilmPos->setGeometry(QRect(10, 60, 941, 301));
        tableWidgetFilmPos->setFont(font6);
        tableWidgetFilmPos->verticalHeader()->setMinimumSectionSize(45);
        tableWidgetFilmPos->verticalHeader()->setDefaultSectionSize(45);
        PushButtonGenerateFilmPos = new QPushButton(Film);
        PushButtonGenerateFilmPos->setObjectName("PushButtonGenerateFilmPos");
        PushButtonGenerateFilmPos->setGeometry(QRect(670, 0, 261, 51));
        PushButtonGenerateFilmPos->setFont(font1);
        PushButtonGenerateFilmPos->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonGenerateFilmPos->setCheckable(true);
        PushButtonGenerateFilmPos->setAutoDefault(false);
        PushButtonGenerateFilmPos->setFlat(false);
        stackedWidget->addWidget(Film);

        retranslateUi(EasyPropertyDentMeasureForm);

        PushButtonSaveBladePos->setDefault(false);
        PushButtonLoadBladePos->setDefault(false);
        PushButtonAddLine->setDefault(false);
        PushButtonRemoveLine->setDefault(false);
        PushButtonManualCreateArea->setDefault(false);
        stackedWidget->setCurrentIndex(0);
        PushButtonGenerateFilmPos->setDefault(false);


        QMetaObject::connectSlotsByName(EasyPropertyDentMeasureForm);
    } // setupUi

    void retranslateUi(GUIFormBase *EasyPropertyDentMeasureForm)
    {
        EasyPropertyDentMeasureForm->setWindowTitle(QCoreApplication::translate("EasyPropertyDentMeasureForm", "Form", nullptr));
        toolButtonAutoGenerate->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\346\244\234\346\237\273\351\240\230\345\237\237\343\201\256\347\224\237\346\210\220", nullptr));
        PushButtonSaveBladePos->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\350\250\210\346\270\254\344\275\215\347\275\256\343\201\256\344\277\235\345\255\230", nullptr));
        PushButtonLoadBladePos->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\350\250\210\346\270\254\344\275\215\347\275\256\343\201\256\350\252\255\350\276\274", nullptr));
        PushButtonAddLine->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "+", nullptr));
        PushButtonRemoveLine->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "-", nullptr));
        toolButtonGetCorrentValues->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217\343\201\256\350\250\210\346\270\254\345\200\244", nullptr));
        toolButtonSetCorrentValues->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\345\237\272\346\272\226\345\200\244\343\201\256\345\217\215\346\230\240", nullptr));
        PushButtonManualCreateArea->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\346\270\254\351\225\267\343\201\256\351\240\230\345\237\237\343\202\222\346\217\217\347\224\273", nullptr));
        toolButtonGetCorrentValuesTarget->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\347\217\276\345\234\250\343\201\256\346\244\234\346\237\273\347\224\273\345\203\217\343\201\256\350\250\210\346\270\254\345\200\244", nullptr));
        toolButtonSetName->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\350\250\210\346\270\254\345\220\215\347\247\260\357\274\217\350\250\210\346\270\254\347\250\256\351\241\236", nullptr));
        toolButtonGenFilmUpper->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\344\270\212\345\201\264\343\203\225\343\202\243\343\203\253\343\203\240\351\225\267\343\201\225\346\244\234\346\237\273", nullptr));
        toolButtonGenFilmLower->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\344\270\213\345\201\264\343\203\225\343\202\243\343\203\253\343\203\240\351\225\267\343\201\225\346\244\234\346\237\273", nullptr));
        label->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\343\203\234\343\202\277\343\203\263\343\202\222\346\212\274\343\201\227\344\270\213\343\201\222\343\200\201\345\220\204\344\270\212\344\270\213\343\201\256\345\210\203\343\201\256\347\253\257\343\202\222\343\202\257\343\203\252\343\203\203\343\202\257\343\201\227\343\201\246\343\201\217\343\201\240\343\201\225\343\201\204", nullptr));
        pushButtonSetUpper->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\350\207\252\345\213\225\343\201\256\350\250\255\345\256\232", nullptr));
        pushButtonSetLower->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\350\207\252\345\213\225\343\201\256\350\250\255\345\256\232", nullptr));
        toolButtonFilm->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\343\203\225\343\202\243\343\203\253\343\203\240\350\250\210\346\270\254", nullptr));
        toolButtonBlade->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\345\210\203\343\201\256\350\250\210\346\270\254", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetBladePos->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\345\240\264\346\211\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetBladePos->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\345\267\246\343\201\213\343\202\211\343\201\256\350\267\235\351\233\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetBladePos->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\344\270\212\343\201\213\343\202\211\343\201\256\350\267\235\351\233\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetBladePos->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\345\217\263\343\201\213\343\202\211\343\201\256\350\267\235\351\233\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetBladePos->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\344\270\213\343\201\213\343\202\211\343\201\256\350\267\235\351\233\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetBladePos->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\344\270\213\351\231\220\345\200\244", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetBladePos->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\344\270\212\351\231\220\345\200\244", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetBladePos->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\350\250\210\346\270\254\347\267\232\343\201\256\351\225\267\343\201\225", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetBladePos->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\343\203\235\343\202\244\343\203\263\343\203\210\357\274\221", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetBladePos->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\343\203\235\343\202\244\343\203\263\343\203\210\357\274\222", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetBladePos->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\346\270\254\345\256\232\345\200\244", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetBladePos->verticalHeaderItem(0);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\346\226\260\343\201\227\343\201\204\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetFilmPos->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\345\240\264\346\211\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidgetFilmPos->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\345\267\246\343\201\213\343\202\211\343\201\256\350\267\235\351\233\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidgetFilmPos->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\344\270\212\343\201\213\343\202\211\343\201\256\350\267\235\351\233\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidgetFilmPos->horizontalHeaderItem(3);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\345\217\263\343\201\213\343\202\211\343\201\256\350\267\235\351\233\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidgetFilmPos->horizontalHeaderItem(4);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\344\270\213\343\201\213\343\202\211\343\201\256\350\267\235\351\233\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidgetFilmPos->horizontalHeaderItem(5);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\344\270\213\351\231\220\345\200\244", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidgetFilmPos->horizontalHeaderItem(6);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\344\270\212\351\231\220\345\200\244", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidgetFilmPos->horizontalHeaderItem(7);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\350\250\210\346\270\254\347\267\232\343\201\256\351\225\267\343\201\225", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidgetFilmPos->horizontalHeaderItem(8);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\343\203\225\343\202\243\343\203\253\343\203\240\347\253\257", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidgetFilmPos->horizontalHeaderItem(9);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\343\203\235\343\202\244\343\203\263\343\203\210\357\274\222", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidgetFilmPos->horizontalHeaderItem(10);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\346\270\254\345\256\232\345\200\244", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidgetFilmPos->verticalHeaderItem(0);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\346\226\260\343\201\227\343\201\204\350\241\214", nullptr));
        PushButtonGenerateFilmPos->setText(QCoreApplication::translate("EasyPropertyDentMeasureForm", "\343\203\225\343\202\243\343\203\253\343\203\240\350\250\210\346\270\254\343\201\256\343\201\277\347\224\237\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EasyPropertyDentMeasureForm: public Ui_EasyPropertyDentMeasureForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EASYPROPERTYDENTMEASUREFORM_H
