/********************************************************************************
** Form generated from reading UI file 'PropertyAreaShaderForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYAREASHADERFORM_H
#define UI_PROPERTYAREASHADERFORM_H

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
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyAreaShaderFormClass
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QPushButton *ButtonPickupTest;
    QPushButton *pushButtonSetFromAll;
    QPushButton *pushButtonEditLibrary;
    QTableWidget *tableWidgetGeneratedLibList;
    QPushButton *ButtonGenerateLibs;
    QPushButton *pushButtonGetBackAll;
    QPushButton *ButtonPickupClearTest;
    QPushButton *pushButtonGetBack;
    QPushButton *pushButtonSetFrom;
    QLabel *label_31;
    QLabel *label_30;
    QPushButton *pushButtonEditLibFolder;
    QLabel *labelLibFolderName;
    QFrame *frame_3;
    QLabel *label_35;
    QSpinBox *EditMinSize;
    QLabel *label_29;
    QSpinBox *EditPriority;
    QSpinBox *EditMaxSize;
    QSpinBox *EditMaxDot;
    QSpinBox *EditMinDot;
    QLabel *label_26;
    QLabel *label_28;
    QSpinBox *EditShrinkDot;
    QLabel *label_27;
    QLabel *label_36;
    QPushButton *ButtonLibSave;
    QLabel *label_7;
    QLineEdit *EditLibName;
    QLabel *label_8;
    QLineEdit *EditLibID;
    QPushButton *pushButton;
    QTableWidget *tableWidgetLibList;
    QWidget *tab;
    QTableWidget *tableWidgetAreaShader;
    QFrame *frame;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBoxSigma;
    QDoubleSpinBox *doubleSpinBoxAverage;
    QSpinBox *spinBoxCellSize;
    QLabel *label;
    QLabel *label_3;
    QCheckBox *checkBoxFixed;
    QDoubleSpinBox *doubleSpinBoxAdoptRate;
    QLabel *label_5;
    QLabel *label_2;

    void setupUi(GUIFormBase *PropertyAreaShaderFormClass)
    {
        if (PropertyAreaShaderFormClass->objectName().isEmpty())
            PropertyAreaShaderFormClass->setObjectName("PropertyAreaShaderFormClass");
        PropertyAreaShaderFormClass->resize(399, 700);
        tabWidget = new QTabWidget(PropertyAreaShaderFormClass);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 10, 401, 691));
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        ButtonPickupTest = new QPushButton(tab_2);
        ButtonPickupTest->setObjectName("ButtonPickupTest");
        ButtonPickupTest->setGeometry(QRect(10, 234, 181, 41));
        QFont font;
        font.setPointSize(11);
        ButtonPickupTest->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Extract.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupTest->setIcon(icon);
        pushButtonSetFromAll = new QPushButton(tab_2);
        pushButtonSetFromAll->setObjectName("pushButtonSetFromAll");
        pushButtonSetFromAll->setGeometry(QRect(180, 170, 39, 23));
        pushButtonEditLibrary = new QPushButton(tab_2);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(230, 200, 161, 31));
        QFont font1;
        font1.setPointSize(12);
        pushButtonEditLibrary->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon1);
        tableWidgetGeneratedLibList = new QTableWidget(tab_2);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetGeneratedLibList->setObjectName("tableWidgetGeneratedLibList");
        tableWidgetGeneratedLibList->setGeometry(QRect(230, 70, 161, 121));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonGenerateLibs = new QPushButton(tab_2);
        ButtonGenerateLibs->setObjectName("ButtonGenerateLibs");
        ButtonGenerateLibs->setGeometry(QRect(200, 240, 191, 71));
        ButtonGenerateLibs->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonGenerateLibs->setIcon(icon2);
        pushButtonGetBackAll = new QPushButton(tab_2);
        pushButtonGetBackAll->setObjectName("pushButtonGetBackAll");
        pushButtonGetBackAll->setGeometry(QRect(180, 200, 39, 23));
        ButtonPickupClearTest = new QPushButton(tab_2);
        ButtonPickupClearTest->setObjectName("ButtonPickupClearTest");
        ButtonPickupClearTest->setGeometry(QRect(10, 280, 181, 31));
        ButtonPickupClearTest->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupClearTest->setIcon(icon3);
        pushButtonGetBack = new QPushButton(tab_2);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(180, 120, 39, 23));
        pushButtonSetFrom = new QPushButton(tab_2);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(180, 90, 39, 23));
        label_31 = new QLabel(tab_2);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(230, 50, 161, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_30 = new QLabel(tab_2);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 50, 161, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonEditLibFolder = new QPushButton(tab_2);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(20, 10, 101, 31));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon4);
        labelLibFolderName = new QLabel(tab_2);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(140, 10, 241, 31));
        QFont font2;
        font2.setPointSize(16);
        labelLibFolderName->setFont(font2);
        frame_3 = new QFrame(tab_2);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 330, 381, 221));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_35 = new QLabel(frame_3);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(200, 60, 81, 21));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Sunken);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinSize = new QSpinBox(frame_3);
        EditMinSize->setObjectName("EditMinSize");
        EditMinSize->setGeometry(QRect(280, 60, 71, 22));
        EditMinSize->setMaximum(999999);
        label_29 = new QLabel(frame_3);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(30, 140, 131, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPriority = new QSpinBox(frame_3);
        EditPriority->setObjectName("EditPriority");
        EditPriority->setGeometry(QRect(160, 140, 61, 22));
        EditPriority->setMaximum(255);
        EditMaxSize = new QSpinBox(frame_3);
        EditMaxSize->setObjectName("EditMaxSize");
        EditMaxSize->setGeometry(QRect(280, 80, 71, 22));
        EditMaxSize->setMaximum(999999);
        EditMaxDot = new QSpinBox(frame_3);
        EditMaxDot->setObjectName("EditMaxDot");
        EditMaxDot->setGeometry(QRect(110, 80, 71, 22));
        EditMaxDot->setMaximum(99999999);
        EditMinDot = new QSpinBox(frame_3);
        EditMinDot->setObjectName("EditMinDot");
        EditMinDot->setGeometry(QRect(110, 60, 71, 22));
        EditMinDot->setMaximum(999999);
        label_26 = new QLabel(frame_3);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(30, 110, 131, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_28 = new QLabel(frame_3);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(30, 80, 81, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditShrinkDot = new QSpinBox(frame_3);
        EditShrinkDot->setObjectName("EditShrinkDot");
        EditShrinkDot->setGeometry(QRect(160, 110, 61, 22));
        EditShrinkDot->setMaximum(255);
        label_27 = new QLabel(frame_3);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(30, 60, 81, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_36 = new QLabel(frame_3);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(200, 80, 81, 21));
        label_36->setFrameShape(QFrame::Panel);
        label_36->setFrameShadow(QFrame::Sunken);
        label_36->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibSave = new QPushButton(frame_3);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(10, 170, 361, 41));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon5);
        label_7 = new QLabel(frame_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 0, 381, 21));
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibName = new QLineEdit(frame_3);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 20, 231, 21));
        EditLibName->setFont(font1);
        label_8 = new QLabel(frame_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 20, 51, 21));
        label_8->setFont(font1);
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(frame_3);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 20, 81, 21));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        pushButton = new QPushButton(frame_3);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(300, 680, 71, 31));
        pushButton->setFont(font);
        tableWidgetLibList = new QTableWidget(tab_2);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 70, 161, 161));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        tableWidgetAreaShader = new QTableWidget(tab);
        if (tableWidgetAreaShader->columnCount() < 3)
            tableWidgetAreaShader->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetAreaShader->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetAreaShader->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetAreaShader->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        tableWidgetAreaShader->setObjectName("tableWidgetAreaShader");
        tableWidgetAreaShader->setGeometry(QRect(10, 10, 381, 421));
        tableWidgetAreaShader->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAreaShader->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(tab);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 450, 381, 181));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(41, 150, 81, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxSigma = new QDoubleSpinBox(frame);
        doubleSpinBoxSigma->setObjectName("doubleSpinBoxSigma");
        doubleSpinBoxSigma->setGeometry(QRect(130, 150, 81, 22));
        doubleSpinBoxSigma->setMaximum(1000.000000000000000);
        doubleSpinBoxAverage = new QDoubleSpinBox(frame);
        doubleSpinBoxAverage->setObjectName("doubleSpinBoxAverage");
        doubleSpinBoxAverage->setGeometry(QRect(130, 120, 81, 22));
        doubleSpinBoxAverage->setMaximum(256.000000000000000);
        spinBoxCellSize = new QSpinBox(frame);
        spinBoxCellSize->setObjectName("spinBoxCellSize");
        spinBoxCellSize->setGeometry(QRect(129, 30, 81, 22));
        spinBoxCellSize->setMaximum(999999);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(38, 30, 81, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 381, 21));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxFixed = new QCheckBox(frame);
        checkBoxFixed->setObjectName("checkBoxFixed");
        checkBoxFixed->setGeometry(QRect(39, 100, 191, 17));
        doubleSpinBoxAdoptRate = new QDoubleSpinBox(frame);
        doubleSpinBoxAdoptRate->setObjectName("doubleSpinBoxAdoptRate");
        doubleSpinBoxAdoptRate->setGeometry(QRect(129, 60, 81, 22));
        doubleSpinBoxAdoptRate->setMaximum(100.000000000000000);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(40, 120, 81, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(39, 60, 81, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidget->addTab(tab, QString());

        retranslateUi(PropertyAreaShaderFormClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PropertyAreaShaderFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyAreaShaderFormClass)
    {
        PropertyAreaShaderFormClass->setWindowTitle(QCoreApplication::translate("PropertyAreaShaderFormClass", "PropertyAreaShaderForm", nullptr));
        ButtonPickupTest->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\345\215\230\344\270\200\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\343\201\256\346\212\275\345\207\272", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "=>>", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "Name", nullptr));
        ButtonGenerateLibs->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\344\270\212\343\201\256\345\205\250\343\201\246\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\347\224\237\346\210\220", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "<<=", nullptr));
        ButtonPickupClearTest->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\346\212\275\345\207\272\343\201\256\343\202\257\343\203\252\343\202\242", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "<=", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "=>", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\357\274\270\357\274\270\357\274\270", nullptr));
        label_35->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\346\234\200\345\260\217\351\225\267\343\201\225", nullptr));
        label_29->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\347\224\237\346\210\220\346\231\202\343\201\256\345\204\252\345\205\210\345\272\246", nullptr));
        label_26->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\345\207\246\347\220\206\351\240\230\345\237\237\343\201\270\343\201\256\345\217\216\347\270\256\351\207\217", nullptr));
        label_28->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\346\234\200\345\244\247\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_27->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\346\234\200\345\260\217\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_36->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\346\234\200\345\244\247\351\225\267\343\201\225", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\343\203\207\343\203\274\343\202\277\343\203\231\343\203\274\343\202\271\343\201\270\343\201\256\346\233\264\346\226\260", nullptr));
        label_7->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\227\343\203\255\343\203\221\343\203\206\343\202\243", nullptr));
        EditLibName->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "Library Name", nullptr));
        label_8->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "12345", nullptr));
        pushButton->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "Name", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("PropertyAreaShaderFormClass", "Generate", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetAreaShader->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetAreaShader->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetAreaShader->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "Position", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\345\233\272\345\256\232\345\201\217\345\267\256", nullptr));
        label->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\345\207\246\347\220\206\343\202\265\343\202\244\343\202\272", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\343\202\257\343\203\252\343\203\203\343\202\257\343\201\227\343\201\237\343\203\252\343\202\271\343\203\210\343\201\256\346\203\205\345\240\261", nullptr));
        checkBoxFixed->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\345\233\272\345\256\232\345\200\244", nullptr));
        label_5->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\345\233\272\345\256\232\345\271\263\345\235\207\345\200\244", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyAreaShaderFormClass", "\346\216\241\347\224\250\347\216\207", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("PropertyAreaShaderFormClass", "Items", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyAreaShaderFormClass: public Ui_PropertyAreaShaderFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYAREASHADERFORM_H
