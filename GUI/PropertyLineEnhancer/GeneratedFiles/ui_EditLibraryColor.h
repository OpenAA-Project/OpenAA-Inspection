/********************************************************************************
** Form generated from reading UI file 'EditLibraryColor.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLIBRARYCOLOR_H
#define UI_EDITLIBRARYCOLOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditLibraryColorClass
{
public:
    QPushButton *pushButton;
    QFrame *frame_2;
    QSpinBox *EditSelfSearch;
    QLabel *label_30;
    QDoubleSpinBox *doubleSpinBoxEmphasizeRate;
    QLabel *label_33;
    QSpinBox *EditMaxLineWidth;
    QLabel *label_38;
    QFrame *frame;
    QLabel *label_37;
    QLabel *label_35;
    QSpinBox *EditMinSize;
    QLabel *label_34;
    QLabel *label_29;
    QSpinBox *EditPriority;
    QSpinBox *EditStepDot;
    QSpinBox *EditMaxSize;
    QSpinBox *EditMaxDot;
    QSpinBox *EditMinDot;
    QSpinBox *EditSearchBlockWidth;
    QLabel *label_26;
    QLabel *label_28;
    QSpinBox *EditShrinkDot;
    QLabel *label_27;
    QLabel *label_36;
    QLabel *label_39;
    QSpinBox *EditLimitDot;
    QFrame *frameLibFolder;
    QPushButton *ButtonLibSaveNew;
    QLabel *label_4;
    QTableWidget *tableWidgetLibList;
    QLineEdit *EditLibName;
    QPushButton *ButtonLibNew;
    QPushButton *ButtonLibDelete;
    QPushButton *ButtonLibSave;
    QLineEdit *EditLibID;
    QPushButton *pushButtonAddAllColor;
    QFrame *frameThreshold;
    QLabel *label_8;
    QListWidget *listWidgetEliminatedColor;
    QTabWidget *tabWidget;
    QWidget *tab_7;
    QFrame *frameColorSample;
    QPushButton *pushButtonEliminateColor;
    QPushButton *pushButtonAddColor;
    QWidget *tab_8;
    QFrame *framePicked_3;
    QLabel *label_44;
    QPushButton *pushButtonSubPickupColor;
    QPushButton *pushButtonAddPickupColor;
    QSpinBox *spinBoxMerginAddPickupColor;
    QSpinBox *spinBoxMerginSubPickupColor;
    QLabel *label_45;
    QFrame *framePickupColor;
    QWidget *tab_9;
    QFrame *frameShowColorSmples;
    QPushButton *pushButtonAddColorArea;
    QPushButton *pushButtonEliminateColorArea;
    QLabel *label_7;
    QListWidget *listWidgetBaseColor;

    void setupUi(QDialog *EditLibraryColorClass)
    {
        if (EditLibraryColorClass->objectName().isEmpty())
            EditLibraryColorClass->setObjectName("EditLibraryColorClass");
        EditLibraryColorClass->resize(851, 821);
        pushButton = new QPushButton(EditLibraryColorClass);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(310, 780, 71, 31));
        QFont font;
        font.setPointSize(11);
        pushButton->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon);
        frame_2 = new QFrame(EditLibraryColorClass);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 670, 381, 71));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        EditSelfSearch = new QSpinBox(frame_2);
        EditSelfSearch->setObjectName("EditSelfSearch");
        EditSelfSearch->setGeometry(QRect(320, 40, 51, 22));
        EditSelfSearch->setMaximum(255);
        label_30 = new QLabel(frame_2);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 10, 121, 21));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxEmphasizeRate = new QDoubleSpinBox(frame_2);
        doubleSpinBoxEmphasizeRate->setObjectName("doubleSpinBoxEmphasizeRate");
        doubleSpinBoxEmphasizeRate->setGeometry(QRect(130, 10, 62, 22));
        doubleSpinBoxEmphasizeRate->setDecimals(4);
        doubleSpinBoxEmphasizeRate->setMinimum(-99.989999999999995);
        label_33 = new QLabel(frame_2);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(10, 40, 121, 21));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Sunken);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxLineWidth = new QSpinBox(frame_2);
        EditMaxLineWidth->setObjectName("EditMaxLineWidth");
        EditMaxLineWidth->setGeometry(QRect(130, 40, 61, 22));
        EditMaxLineWidth->setMaximum(255);
        label_38 = new QLabel(frame_2);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(210, 40, 111, 21));
        label_38->setFrameShape(QFrame::Panel);
        label_38->setFrameShadow(QFrame::Sunken);
        label_38->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame = new QFrame(EditLibraryColorClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 490, 381, 171));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_37 = new QLabel(frame);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(40, 80, 131, 21));
        label_37->setFrameShape(QFrame::Panel);
        label_37->setFrameShadow(QFrame::Sunken);
        label_37->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_35 = new QLabel(frame);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(210, 10, 81, 21));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Sunken);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinSize = new QSpinBox(frame);
        EditMinSize->setObjectName("EditMinSize");
        EditMinSize->setGeometry(QRect(290, 10, 71, 22));
        EditMinSize->setMaximum(999999);
        label_34 = new QLabel(frame);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(200, 110, 111, 21));
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Sunken);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_29 = new QLabel(frame);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(10, 110, 121, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPriority = new QSpinBox(frame);
        EditPriority->setObjectName("EditPriority");
        EditPriority->setGeometry(QRect(130, 110, 61, 22));
        EditPriority->setMaximum(255);
        EditStepDot = new QSpinBox(frame);
        EditStepDot->setObjectName("EditStepDot");
        EditStepDot->setGeometry(QRect(310, 110, 61, 22));
        EditStepDot->setMaximum(255);
        EditMaxSize = new QSpinBox(frame);
        EditMaxSize->setObjectName("EditMaxSize");
        EditMaxSize->setGeometry(QRect(290, 30, 71, 22));
        EditMaxSize->setMaximum(999999);
        EditMaxDot = new QSpinBox(frame);
        EditMaxDot->setObjectName("EditMaxDot");
        EditMaxDot->setGeometry(QRect(120, 30, 71, 22));
        EditMaxDot->setMaximum(99999999);
        EditMinDot = new QSpinBox(frame);
        EditMinDot->setObjectName("EditMinDot");
        EditMinDot->setGeometry(QRect(120, 10, 71, 22));
        EditMinDot->setMaximum(999999);
        EditSearchBlockWidth = new QSpinBox(frame);
        EditSearchBlockWidth->setObjectName("EditSearchBlockWidth");
        EditSearchBlockWidth->setGeometry(QRect(170, 80, 61, 22));
        EditSearchBlockWidth->setMaximum(255);
        label_26 = new QLabel(frame);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(40, 60, 131, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_28 = new QLabel(frame);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(40, 30, 81, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditShrinkDot = new QSpinBox(frame);
        EditShrinkDot->setObjectName("EditShrinkDot");
        EditShrinkDot->setGeometry(QRect(170, 60, 61, 22));
        EditShrinkDot->setMaximum(255);
        label_27 = new QLabel(frame);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(40, 10, 81, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_36 = new QLabel(frame);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(210, 30, 81, 21));
        label_36->setFrameShape(QFrame::Panel);
        label_36->setFrameShadow(QFrame::Sunken);
        label_36->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_39 = new QLabel(frame);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(10, 140, 121, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLimitDot = new QSpinBox(frame);
        EditLimitDot->setObjectName("EditLimitDot");
        EditLimitDot->setGeometry(QRect(130, 140, 61, 22));
        EditLimitDot->setMaximum(99999);
        frameLibFolder = new QFrame(EditLibraryColorClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 201, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonLibSaveNew = new QPushButton(EditLibraryColorClass);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(210, 750, 91, 31));
        ButtonLibSaveNew->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon1);
        label_4 = new QLabel(EditLibraryColorClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(400, 130, 51, 31));
        QFont font1;
        font1.setPointSize(12);
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetLibList = new QTableWidget(EditLibraryColorClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(220, 10, 171, 201));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        EditLibName = new QLineEdit(EditLibraryColorClass);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(530, 130, 211, 31));
        EditLibName->setFont(font1);
        ButtonLibNew = new QPushButton(EditLibraryColorClass);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(20, 750, 91, 31));
        ButtonLibNew->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon2);
        ButtonLibDelete = new QPushButton(EditLibraryColorClass);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(120, 750, 81, 31));
        ButtonLibDelete->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon3);
        ButtonLibSave = new QPushButton(EditLibraryColorClass);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(310, 750, 71, 31));
        ButtonLibSave->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon4);
        EditLibID = new QLineEdit(EditLibraryColorClass);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(450, 130, 81, 31));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        pushButtonAddAllColor = new QPushButton(EditLibraryColorClass);
        pushButtonAddAllColor->setObjectName("pushButtonAddAllColor");
        pushButtonAddAllColor->setGeometry(QRect(320, 320, 71, 41));
        frameThreshold = new QFrame(EditLibraryColorClass);
        frameThreshold->setObjectName("frameThreshold");
        frameThreshold->setGeometry(QRect(40, 230, 271, 251));
        frameThreshold->setFrameShape(QFrame::StyledPanel);
        frameThreshold->setFrameShadow(QFrame::Raised);
        label_8 = new QLabel(EditLibraryColorClass);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(320, 390, 61, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetEliminatedColor = new QListWidget(EditLibraryColorClass);
        listWidgetEliminatedColor->setObjectName("listWidgetEliminatedColor");
        listWidgetEliminatedColor->setGeometry(QRect(320, 410, 61, 61));
        tabWidget = new QTabWidget(EditLibraryColorClass);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(400, 180, 441, 551));
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        frameColorSample = new QFrame(tab_7);
        frameColorSample->setObjectName("frameColorSample");
        frameColorSample->setGeometry(QRect(10, 10, 205, 511));
        frameColorSample->setFrameShape(QFrame::StyledPanel);
        frameColorSample->setFrameShadow(QFrame::Sunken);
        pushButtonEliminateColor = new QPushButton(frameColorSample);
        pushButtonEliminateColor->setObjectName("pushButtonEliminateColor");
        pushButtonEliminateColor->setGeometry(QRect(20, 480, 161, 25));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/ColorDelete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEliminateColor->setIcon(icon5);
        pushButtonAddColor = new QPushButton(frameColorSample);
        pushButtonAddColor->setObjectName("pushButtonAddColor");
        pushButtonAddColor->setGeometry(QRect(20, 450, 161, 25));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Qtres/ColorAdd.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAddColor->setIcon(icon6);
        tabWidget->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        framePicked_3 = new QFrame(tab_8);
        framePicked_3->setObjectName("framePicked_3");
        framePicked_3->setGeometry(QRect(10, 10, 191, 111));
        framePicked_3->setFrameShape(QFrame::StyledPanel);
        framePicked_3->setFrameShadow(QFrame::Sunken);
        label_44 = new QLabel(framePicked_3);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(0, 0, 191, 21));
        label_44->setFrameShape(QFrame::Panel);
        label_44->setFrameShadow(QFrame::Sunken);
        label_44->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSubPickupColor = new QPushButton(framePicked_3);
        pushButtonSubPickupColor->setObjectName("pushButtonSubPickupColor");
        pushButtonSubPickupColor->setGeometry(QRect(40, 80, 75, 23));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Qtres/Color.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSubPickupColor->setIcon(icon7);
        pushButtonAddPickupColor = new QPushButton(framePicked_3);
        pushButtonAddPickupColor->setObjectName("pushButtonAddPickupColor");
        pushButtonAddPickupColor->setGeometry(QRect(40, 50, 75, 23));
        pushButtonAddPickupColor->setIcon(icon6);
        spinBoxMerginAddPickupColor = new QSpinBox(framePicked_3);
        spinBoxMerginAddPickupColor->setObjectName("spinBoxMerginAddPickupColor");
        spinBoxMerginAddPickupColor->setGeometry(QRect(120, 50, 61, 22));
        spinBoxMerginAddPickupColor->setValue(10);
        spinBoxMerginSubPickupColor = new QSpinBox(framePicked_3);
        spinBoxMerginSubPickupColor->setObjectName("spinBoxMerginSubPickupColor");
        spinBoxMerginSubPickupColor->setGeometry(QRect(120, 80, 61, 22));
        spinBoxMerginSubPickupColor->setValue(10);
        label_45 = new QLabel(framePicked_3);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(120, 30, 64, 21));
        label_45->setFrameShape(QFrame::Panel);
        label_45->setFrameShadow(QFrame::Sunken);
        label_45->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        framePickupColor = new QFrame(framePicked_3);
        framePickupColor->setObjectName("framePickupColor");
        framePickupColor->setGeometry(QRect(10, 30, 21, 71));
        framePickupColor->setFrameShape(QFrame::NoFrame);
        framePickupColor->setFrameShadow(QFrame::Plain);
        tabWidget->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName("tab_9");
        frameShowColorSmples = new QFrame(tab_9);
        frameShowColorSmples->setObjectName("frameShowColorSmples");
        frameShowColorSmples->setGeometry(QRect(10, 10, 415, 355));
        frameShowColorSmples->setFrameShape(QFrame::NoFrame);
        frameShowColorSmples->setFrameShadow(QFrame::Plain);
        pushButtonAddColorArea = new QPushButton(tab_9);
        pushButtonAddColorArea->setObjectName("pushButtonAddColorArea");
        pushButtonAddColorArea->setGeometry(QRect(60, 370, 161, 25));
        pushButtonAddColorArea->setIcon(icon6);
        pushButtonEliminateColorArea = new QPushButton(tab_9);
        pushButtonEliminateColorArea->setObjectName("pushButtonEliminateColorArea");
        pushButtonEliminateColorArea->setGeometry(QRect(60, 400, 161, 25));
        pushButtonEliminateColorArea->setIcon(icon5);
        tabWidget->addTab(tab_9, QString());
        label_7 = new QLabel(EditLibraryColorClass);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(320, 230, 61, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetBaseColor = new QListWidget(EditLibraryColorClass);
        listWidgetBaseColor->setObjectName("listWidgetBaseColor");
        listWidgetBaseColor->setGeometry(QRect(320, 250, 61, 61));

        retranslateUi(EditLibraryColorClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditLibraryColorClass);
    } // setupUi

    void retranslateUi(QDialog *EditLibraryColorClass)
    {
        EditLibraryColorClass->setWindowTitle(QCoreApplication::translate("EditLibraryColorClass", "EditLibraryColor", nullptr));
        pushButton->setText(QCoreApplication::translate("EditLibraryColorClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_30->setText(QCoreApplication::translate("EditLibraryColorClass", "\345\274\267\350\252\277\344\277\202\346\225\260", nullptr));
        label_33->setText(QCoreApplication::translate("EditLibraryColorClass", "\347\267\232\345\271\205", nullptr));
        label_38->setText(QCoreApplication::translate("EditLibraryColorClass", "\346\216\242\347\264\242\350\267\235\351\233\242", nullptr));
        label_37->setText(QCoreApplication::translate("EditLibraryColorClass", "\346\216\242\347\264\242\351\240\230\345\237\237\345\271\205", nullptr));
        label_35->setText(QCoreApplication::translate("EditLibraryColorClass", "\346\234\200\345\260\217\351\225\267\343\201\225", nullptr));
        label_34->setText(QCoreApplication::translate("EditLibraryColorClass", "\345\210\206\345\211\262\347\265\202\347\253\257\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_29->setText(QCoreApplication::translate("EditLibraryColorClass", "\347\224\237\346\210\220\346\231\202\343\201\256\345\204\252\345\205\210\345\272\246", nullptr));
        label_26->setText(QCoreApplication::translate("EditLibraryColorClass", "\345\207\246\347\220\206\351\240\230\345\237\237\343\201\270\343\201\256\345\217\216\347\270\256\351\207\217", nullptr));
        label_28->setText(QCoreApplication::translate("EditLibraryColorClass", "\346\234\200\345\244\247\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_27->setText(QCoreApplication::translate("EditLibraryColorClass", "\346\234\200\345\260\217\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_36->setText(QCoreApplication::translate("EditLibraryColorClass", "\346\234\200\345\244\247\351\225\267\343\201\225", nullptr));
        label_39->setText(QCoreApplication::translate("EditLibraryColorClass", "\351\231\220\347\225\214\343\202\265\343\202\244\343\202\272", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditLibraryColorClass", "Save New", nullptr));
        label_4->setText(QCoreApplication::translate("EditLibraryColorClass", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditLibraryColorClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditLibraryColorClass", "Name", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditLibraryColorClass", "Library Name", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditLibraryColorClass", "Clear new", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditLibraryColorClass", "Delete", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditLibraryColorClass", "Update", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditLibraryColorClass", "12345", nullptr));
        pushButtonAddAllColor->setText(QCoreApplication::translate("EditLibraryColorClass", "<<\345\205\250\350\211\262\350\277\275\345\212\240", nullptr));
        label_8->setText(QCoreApplication::translate("EditLibraryColorClass", "\351\231\244\345\244\226\350\211\262", nullptr));
        pushButtonEliminateColor->setText(QCoreApplication::translate("EditLibraryColorClass", "Eliminate color", nullptr));
        pushButtonAddColor->setText(QCoreApplication::translate("EditLibraryColorClass", "Add Color", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QCoreApplication::translate("EditLibraryColorClass", "\350\211\262\347\231\273\351\214\262\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        label_44->setText(QCoreApplication::translate("EditLibraryColorClass", "\343\203\224\343\203\203\343\202\257\343\202\242\343\203\203\343\203\227\350\211\262\343\201\256\350\277\275\345\212\240\343\203\273\351\231\244\345\244\226", nullptr));
        pushButtonSubPickupColor->setText(QCoreApplication::translate("EditLibraryColorClass", "Sub =>", nullptr));
        pushButtonAddPickupColor->setText(QCoreApplication::translate("EditLibraryColorClass", "Add =>", nullptr));
        label_45->setText(QCoreApplication::translate("EditLibraryColorClass", "\343\203\236\343\203\274\343\202\270\343\203\263\350\274\235\345\272\246", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_8), QCoreApplication::translate("EditLibraryColorClass", "\343\203\224\343\202\257\343\202\273\343\203\253\346\212\275\345\207\272\350\211\262", nullptr));
        pushButtonAddColorArea->setText(QCoreApplication::translate("EditLibraryColorClass", "Add Color", nullptr));
        pushButtonEliminateColorArea->setText(QCoreApplication::translate("EditLibraryColorClass", "Eliminate color", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_9), QCoreApplication::translate("EditLibraryColorClass", "\351\240\230\345\237\237\346\212\275\345\207\272\350\211\262", nullptr));
        label_7->setText(QCoreApplication::translate("EditLibraryColorClass", "\350\277\275\345\212\240\350\211\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLibraryColorClass: public Ui_EditLibraryColorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLIBRARYCOLOR_H
