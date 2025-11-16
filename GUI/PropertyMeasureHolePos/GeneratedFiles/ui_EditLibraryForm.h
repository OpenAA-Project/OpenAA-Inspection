/********************************************************************************
** Form generated from reading UI file 'EditLibraryForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLIBRARYFORM_H
#define UI_EDITLIBRARYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditLibraryFormClass
{
public:
    QTableWidget *tableWidgetLibList;
    QPushButton *pushButton;
    QFrame *frameLibFolder;
    QFrame *frame_2;
    QFrame *frame;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxDiaPrecision;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxPosPrecision;
    QLabel *label_3;
    QSpinBox *spinBoxNoiseSize;
    QLabel *label_92;
    QSpinBox *EditSearchDot;
    QStackedWidget *stackedWidget;
    QWidget *Color;
    QFrame *frameNarrowPanel;
    QPushButton *pushButtonNColor;
    QWidget *Mono;
    QLabel *label_93;
    QSpinBox *EditPickupH;
    QLabel *label_94;
    QSpinBox *EditPickupL;
    QSpinBox *spinBoxBandWidth;
    QLabel *label_5;
    QComboBox *comboBoxCalcMode;
    QLabel *label_95;
    QLineEdit *EditLibName;
    QLabel *label_4;
    QLineEdit *EditLibID;
    QPushButton *ButtonLibSave;
    QPushButton *ButtonLibDelete;
    QPushButton *ButtonLibSaveNew;
    QPushButton *ButtonLibNew;

    void setupUi(QDialog *EditLibraryFormClass)
    {
        if (EditLibraryFormClass->objectName().isEmpty())
            EditLibraryFormClass->setObjectName("EditLibraryFormClass");
        EditLibraryFormClass->resize(473, 702);
        tableWidgetLibList = new QTableWidget(EditLibraryFormClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(240, 10, 221, 201));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButton = new QPushButton(EditLibraryFormClass);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(370, 660, 81, 31));
        QFont font;
        font.setPointSize(11);
        pushButton->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon);
        frameLibFolder = new QFrame(EditLibraryFormClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 221, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        frame_2 = new QFrame(EditLibraryFormClass);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(70, 220, 391, 421));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(frame_2);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(30, 50, 331, 321));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxDiaPrecision = new QDoubleSpinBox(frame);
        doubleSpinBoxDiaPrecision->setObjectName("doubleSpinBoxDiaPrecision");
        doubleSpinBoxDiaPrecision->setGeometry(QRect(210, 10, 81, 22));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 30, 181, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxPosPrecision = new QDoubleSpinBox(frame);
        doubleSpinBoxPosPrecision->setObjectName("doubleSpinBoxPosPrecision");
        doubleSpinBoxPosPrecision->setGeometry(QRect(210, 30, 81, 22));
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 50, 181, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxNoiseSize = new QSpinBox(frame);
        spinBoxNoiseSize->setObjectName("spinBoxNoiseSize");
        spinBoxNoiseSize->setGeometry(QRect(210, 50, 81, 22));
        label_92 = new QLabel(frame);
        label_92->setObjectName("label_92");
        label_92->setGeometry(QRect(20, 100, 181, 21));
        label_92->setFrameShape(QFrame::Panel);
        label_92->setFrameShadow(QFrame::Sunken);
        label_92->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSearchDot = new QSpinBox(frame);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(210, 100, 81, 22));
        EditSearchDot->setMaximum(100);
        stackedWidget = new QStackedWidget(frame);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 170, 311, 141));
        Color = new QWidget();
        Color->setObjectName("Color");
        frameNarrowPanel = new QFrame(Color);
        frameNarrowPanel->setObjectName("frameNarrowPanel");
        frameNarrowPanel->setGeometry(QRect(70, 0, 231, 131));
        frameNarrowPanel->setFrameShape(QFrame::NoFrame);
        frameNarrowPanel->setFrameShadow(QFrame::Raised);
        pushButtonNColor = new QPushButton(Color);
        pushButtonNColor->setObjectName("pushButtonNColor");
        pushButtonNColor->setGeometry(QRect(10, 20, 61, 25));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Color.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonNColor->setIcon(icon1);
        stackedWidget->addWidget(Color);
        Mono = new QWidget();
        Mono->setObjectName("Mono");
        label_93 = new QLabel(Mono);
        label_93->setObjectName("label_93");
        label_93->setGeometry(QRect(0, 10, 131, 21));
        label_93->setFrameShape(QFrame::Panel);
        label_93->setFrameShadow(QFrame::Sunken);
        label_93->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupH = new QSpinBox(Mono);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(210, 30, 81, 22));
        EditPickupH->setMaximum(100);
        label_94 = new QLabel(Mono);
        label_94->setObjectName("label_94");
        label_94->setGeometry(QRect(170, 10, 131, 21));
        label_94->setFrameShape(QFrame::Panel);
        label_94->setFrameShadow(QFrame::Sunken);
        label_94->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupL = new QSpinBox(Mono);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(40, 30, 81, 22));
        EditPickupL->setMaximum(100);
        stackedWidget->addWidget(Mono);
        spinBoxBandWidth = new QSpinBox(frame);
        spinBoxBandWidth->setObjectName("spinBoxBandWidth");
        spinBoxBandWidth->setGeometry(QRect(210, 70, 81, 22));
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 70, 181, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        comboBoxCalcMode = new QComboBox(frame);
        comboBoxCalcMode->addItem(QString());
        comboBoxCalcMode->addItem(QString());
        comboBoxCalcMode->setObjectName("comboBoxCalcMode");
        comboBoxCalcMode->setGeometry(QRect(210, 130, 81, 22));
        label_95 = new QLabel(frame);
        label_95->setObjectName("label_95");
        label_95->setGeometry(QRect(20, 130, 181, 21));
        label_95->setFrameShape(QFrame::Panel);
        label_95->setFrameShadow(QFrame::Sunken);
        label_95->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibName = new QLineEdit(frame_2);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(150, 10, 211, 31));
        QFont font1;
        font1.setPointSize(12);
        EditLibName->setFont(font1);
        label_4 = new QLabel(frame_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 10, 51, 31));
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(frame_2);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(80, 10, 71, 31));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        ButtonLibSave = new QPushButton(frame_2);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(300, 380, 81, 31));
        ButtonLibSave->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon2);
        ButtonLibDelete = new QPushButton(frame_2);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(110, 380, 81, 31));
        ButtonLibDelete->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon3);
        ButtonLibSaveNew = new QPushButton(frame_2);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(200, 380, 91, 31));
        ButtonLibSaveNew->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon4);
        ButtonLibNew = new QPushButton(frame_2);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(10, 380, 91, 31));
        ButtonLibNew->setFont(font);
        ButtonLibNew->setIcon(icon4);

        retranslateUi(EditLibraryFormClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditLibraryFormClass);
    } // setupUi

    void retranslateUi(QDialog *EditLibraryFormClass)
    {
        EditLibraryFormClass->setWindowTitle(QCoreApplication::translate("EditLibraryFormClass", "EditLibraryForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditLibraryFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditLibraryFormClass", "Name", nullptr));
        pushButton->setText(QCoreApplication::translate("EditLibraryFormClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        label->setText(QCoreApplication::translate("EditLibraryFormClass", "\347\251\264\345\276\204\347\262\276\345\272\246", nullptr));
        label_2->setText(QCoreApplication::translate("EditLibraryFormClass", "\344\275\215\347\275\256\347\262\276\345\272\246", nullptr));
        label_3->setText(QCoreApplication::translate("EditLibraryFormClass", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272", nullptr));
        label_92->setText(QCoreApplication::translate("EditLibraryFormClass", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        pushButtonNColor->setText(QCoreApplication::translate("EditLibraryFormClass", "Color", nullptr));
        label_93->setText(QCoreApplication::translate("EditLibraryFormClass", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
        label_94->setText(QCoreApplication::translate("EditLibraryFormClass", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
        label_5->setText(QCoreApplication::translate("EditLibraryFormClass", "\345\270\257\345\271\205", nullptr));
        comboBoxCalcMode->setItemText(0, QCoreApplication::translate("EditLibraryFormClass", "\351\253\230\351\200\237\350\250\210\346\270\254", nullptr));
        comboBoxCalcMode->setItemText(1, QCoreApplication::translate("EditLibraryFormClass", "\351\253\230\347\262\276\345\272\246", nullptr));

        label_95->setText(QCoreApplication::translate("EditLibraryFormClass", "\350\250\210\346\270\254\346\226\271\346\263\225", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditLibraryFormClass", "Library Name", nullptr));
        label_4->setText(QCoreApplication::translate("EditLibraryFormClass", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditLibraryFormClass", "12345", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditLibraryFormClass", "Update", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditLibraryFormClass", "Delete", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditLibraryFormClass", "Save New", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditLibraryFormClass", "Clear new", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLibraryFormClass: public Ui_EditLibraryFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLIBRARYFORM_H
