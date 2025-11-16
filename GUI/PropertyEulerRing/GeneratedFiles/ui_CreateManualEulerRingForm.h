/********************************************************************************
** Form generated from reading UI file 'CreateManualEulerRingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEMANUALEULERRINGFORM_H
#define UI_CREATEMANUALEULERRINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
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

class Ui_CreateManualEulerRingFormClass
{
public:
    QFrame *frameLibFolder;
    QLineEdit *EditLibName;
    QLineEdit *EditLibID;
    QLabel *label_4;
    QTableWidget *tableWidgetLibList;
    QFrame *frame_20;
    QLabel *label_74;
    QFrame *framePanel;
    QLabel *label_67;
    QSpinBox *EditMergin;
    QLabel *label_49;
    QSpinBox *EditExpandedDot;
    QFrame *frame_25;
    QLabel *label_90;
    QFrame *frame_27;
    QLabel *label_91;
    QSpinBox *EditAdjustBlack;
    QSpinBox *EditAdjustWhite;
    QLabel *label_92;
    QLabel *label_93;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *CreateManualEulerRingFormClass)
    {
        if (CreateManualEulerRingFormClass->objectName().isEmpty())
            CreateManualEulerRingFormClass->setObjectName("CreateManualEulerRingFormClass");
        CreateManualEulerRingFormClass->resize(580, 402);
        frameLibFolder = new QFrame(CreateManualEulerRingFormClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(0, 10, 191, 151));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        EditLibName = new QLineEdit(CreateManualEulerRingFormClass);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(330, 10, 211, 31));
        QFont font;
        font.setPointSize(12);
        EditLibName->setFont(font);
        EditLibID = new QLineEdit(CreateManualEulerRingFormClass);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(250, 10, 81, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        label_4 = new QLabel(CreateManualEulerRingFormClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(200, 10, 51, 31));
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetLibList = new QTableWidget(CreateManualEulerRingFormClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(0, 170, 191, 181));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame_20 = new QFrame(CreateManualEulerRingFormClass);
        frame_20->setObjectName("frame_20");
        frame_20->setGeometry(QRect(200, 50, 371, 141));
        frame_20->setFrameShape(QFrame::StyledPanel);
        frame_20->setFrameShadow(QFrame::Sunken);
        label_74 = new QLabel(frame_20);
        label_74->setObjectName("label_74");
        label_74->setGeometry(QRect(0, 0, 20, 141));
        label_74->setFrameShape(QFrame::Panel);
        label_74->setFrameShadow(QFrame::Raised);
        label_74->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_74->setIndent(1);
        framePanel = new QFrame(frame_20);
        framePanel->setObjectName("framePanel");
        framePanel->setGeometry(QRect(150, 10, 211, 121));
        framePanel->setFrameShape(QFrame::NoFrame);
        framePanel->setFrameShadow(QFrame::Raised);
        label_67 = new QLabel(frame_20);
        label_67->setObjectName("label_67");
        label_67->setGeometry(QRect(40, 10, 70, 21));
        label_67->setFrameShape(QFrame::Panel);
        label_67->setFrameShadow(QFrame::Sunken);
        label_67->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMergin = new QSpinBox(frame_20);
        EditMergin->setObjectName("EditMergin");
        EditMergin->setGeometry(QRect(50, 30, 61, 22));
        EditMergin->setMaximum(99999999);
        label_49 = new QLabel(frame_20);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(40, 60, 71, 21));
        label_49->setFrameShape(QFrame::Panel);
        label_49->setFrameShadow(QFrame::Sunken);
        label_49->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditExpandedDot = new QSpinBox(frame_20);
        EditExpandedDot->setObjectName("EditExpandedDot");
        EditExpandedDot->setGeometry(QRect(50, 80, 61, 22));
        EditExpandedDot->setMaximum(99999999);
        frame_25 = new QFrame(CreateManualEulerRingFormClass);
        frame_25->setObjectName("frame_25");
        frame_25->setGeometry(QRect(200, 200, 371, 71));
        frame_25->setFrameShape(QFrame::StyledPanel);
        frame_25->setFrameShadow(QFrame::Sunken);
        label_90 = new QLabel(frame_25);
        label_90->setObjectName("label_90");
        label_90->setGeometry(QRect(0, 0, 20, 71));
        label_90->setFrameShape(QFrame::Panel);
        label_90->setFrameShadow(QFrame::Raised);
        label_90->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_90->setIndent(1);
        frame_27 = new QFrame(frame_25);
        frame_27->setObjectName("frame_27");
        frame_27->setGeometry(QRect(10, 120, 371, 101));
        frame_27->setFrameShape(QFrame::StyledPanel);
        frame_27->setFrameShadow(QFrame::Sunken);
        label_91 = new QLabel(frame_27);
        label_91->setObjectName("label_91");
        label_91->setGeometry(QRect(0, 0, 20, 61));
        label_91->setFrameShape(QFrame::Panel);
        label_91->setFrameShadow(QFrame::Raised);
        label_91->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_91->setIndent(1);
        EditAdjustBlack = new QSpinBox(frame_25);
        EditAdjustBlack->setObjectName("EditAdjustBlack");
        EditAdjustBlack->setGeometry(QRect(240, 10, 81, 22));
        EditAdjustBlack->setMaximum(255);
        EditAdjustWhite = new QSpinBox(frame_25);
        EditAdjustWhite->setObjectName("EditAdjustWhite");
        EditAdjustWhite->setGeometry(QRect(240, 40, 81, 22));
        EditAdjustWhite->setMaximum(255);
        label_92 = new QLabel(frame_25);
        label_92->setObjectName("label_92");
        label_92->setGeometry(QRect(30, 40, 201, 21));
        label_92->setFrameShape(QFrame::Panel);
        label_92->setFrameShadow(QFrame::Sunken);
        label_92->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_93 = new QLabel(frame_25);
        label_93->setObjectName("label_93");
        label_93->setGeometry(QRect(30, 10, 201, 21));
        label_93->setFrameShape(QFrame::Panel);
        label_93->setFrameShadow(QFrame::Sunken);
        label_93->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonCancel = new QPushButton(CreateManualEulerRingFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(400, 360, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonOK = new QPushButton(CreateManualEulerRingFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(60, 360, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Make.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);

        retranslateUi(CreateManualEulerRingFormClass);

        QMetaObject::connectSlotsByName(CreateManualEulerRingFormClass);
    } // setupUi

    void retranslateUi(QDialog *CreateManualEulerRingFormClass)
    {
        CreateManualEulerRingFormClass->setWindowTitle(QCoreApplication::translate("CreateManualEulerRingFormClass", "CreateManualEulerRingForm", nullptr));
        EditLibName->setText(QCoreApplication::translate("CreateManualEulerRingFormClass", "Library Name", nullptr));
        EditLibID->setText(QCoreApplication::translate("CreateManualEulerRingFormClass", "12345", nullptr));
        label_4->setText(QCoreApplication::translate("CreateManualEulerRingFormClass", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CreateManualEulerRingFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CreateManualEulerRingFormClass", "Name", nullptr));
        label_74->setText(QCoreApplication::translate("CreateManualEulerRingFormClass", "\350\274\235\n"
"\345\272\246", nullptr));
        label_67->setText(QCoreApplication::translate("CreateManualEulerRingFormClass", "\350\274\235\345\272\246\343\203\236\343\203\274\343\202\270\343\203\263", nullptr));
        label_49->setText(QCoreApplication::translate("CreateManualEulerRingFormClass", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_90->setText(QCoreApplication::translate("CreateManualEulerRingFormClass", "\350\243\234\n"
"\346\255\243", nullptr));
        label_91->setText(QCoreApplication::translate("CreateManualEulerRingFormClass", "\350\274\235\n"
"\345\272\246", nullptr));
        label_92->setText(QCoreApplication::translate("CreateManualEulerRingFormClass", "\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_93->setText(QCoreApplication::translate("CreateManualEulerRingFormClass", "\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CreateManualEulerRingFormClass", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("CreateManualEulerRingFormClass", "\344\275\234\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateManualEulerRingFormClass: public Ui_CreateManualEulerRingFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEMANUALEULERRINGFORM_H
