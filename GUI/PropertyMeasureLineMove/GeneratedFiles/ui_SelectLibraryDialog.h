/********************************************************************************
** Form generated from reading UI file 'SelectLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLIBRARYDIALOG_H
#define UI_SELECTLIBRARYDIALOG_H

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

class Ui_SelectLibraryDialog
{
public:
    QFrame *frame_2;
    QLabel *label_92;
    QSpinBox *EditSearchDot;
    QLabel *label_93;
    QLabel *label_94;
    QDoubleSpinBox *doubleSpinBoxThresholdM;
    QDoubleSpinBox *doubleSpinBoxThresholdP;
    QSpinBox *EditEdgeWidth;
    QLabel *label_95;
    QFrame *frameLibFolder;
    QLineEdit *EditLibID;
    QLabel *label_4;
    QLineEdit *EditLibName;
    QTableWidget *tableWidgetLibList;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonCancel;
    QLineEdit *EditItemName;
    QLabel *label_5;

    void setupUi(QDialog *SelectLibraryDialog)
    {
        if (SelectLibraryDialog->objectName().isEmpty())
            SelectLibraryDialog->setObjectName("SelectLibraryDialog");
        SelectLibraryDialog->resize(430, 540);
        frame_2 = new QFrame(SelectLibraryDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 270, 411, 131));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_92 = new QLabel(frame_2);
        label_92->setObjectName("label_92");
        label_92->setGeometry(QRect(50, 10, 201, 21));
        label_92->setFrameShape(QFrame::Panel);
        label_92->setFrameShadow(QFrame::Sunken);
        label_92->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSearchDot = new QSpinBox(frame_2);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(260, 10, 81, 22));
        EditSearchDot->setReadOnly(true);
        EditSearchDot->setMaximum(255);
        label_93 = new QLabel(frame_2);
        label_93->setObjectName("label_93");
        label_93->setGeometry(QRect(50, 40, 201, 21));
        label_93->setFrameShape(QFrame::Panel);
        label_93->setFrameShadow(QFrame::Sunken);
        label_93->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_94 = new QLabel(frame_2);
        label_94->setObjectName("label_94");
        label_94->setGeometry(QRect(50, 70, 201, 21));
        label_94->setFrameShape(QFrame::Panel);
        label_94->setFrameShadow(QFrame::Sunken);
        label_94->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxThresholdM = new QDoubleSpinBox(frame_2);
        doubleSpinBoxThresholdM->setObjectName("doubleSpinBoxThresholdM");
        doubleSpinBoxThresholdM->setGeometry(QRect(260, 40, 81, 22));
        doubleSpinBoxThresholdM->setReadOnly(true);
        doubleSpinBoxThresholdP = new QDoubleSpinBox(frame_2);
        doubleSpinBoxThresholdP->setObjectName("doubleSpinBoxThresholdP");
        doubleSpinBoxThresholdP->setGeometry(QRect(260, 70, 81, 22));
        doubleSpinBoxThresholdP->setReadOnly(true);
        EditEdgeWidth = new QSpinBox(frame_2);
        EditEdgeWidth->setObjectName("EditEdgeWidth");
        EditEdgeWidth->setGeometry(QRect(260, 100, 81, 22));
        EditEdgeWidth->setMaximum(255);
        label_95 = new QLabel(frame_2);
        label_95->setObjectName("label_95");
        label_95->setGeometry(QRect(50, 100, 201, 21));
        label_95->setFrameShape(QFrame::Panel);
        label_95->setFrameShadow(QFrame::Sunken);
        label_95->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameLibFolder = new QFrame(SelectLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 201, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        EditLibID = new QLineEdit(SelectLibraryDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 230, 81, 31));
        QFont font;
        font.setPointSize(12);
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        label_4 = new QLabel(SelectLibraryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 230, 51, 31));
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibName = new QLineEdit(SelectLibraryDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 230, 281, 31));
        EditLibName->setFont(font);
        EditLibName->setReadOnly(true);
        tableWidgetLibList = new QTableWidget(SelectLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(220, 10, 201, 201));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelect = new QPushButton(SelectLibraryDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(50, 480, 121, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSelect->setIcon(icon);
        pushButtonCancel = new QPushButton(SelectLibraryDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(260, 480, 121, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        EditItemName = new QLineEdit(SelectLibraryDialog);
        EditItemName->setObjectName("EditItemName");
        EditItemName->setGeometry(QRect(140, 420, 281, 31));
        EditItemName->setFont(font);
        EditItemName->setReadOnly(true);
        label_5 = new QLabel(SelectLibraryDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 420, 121, 31));
        label_5->setFont(font);
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(SelectLibraryDialog);

        pushButtonSelect->setDefault(true);


        QMetaObject::connectSlotsByName(SelectLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectLibraryDialog)
    {
        SelectLibraryDialog->setWindowTitle(QCoreApplication::translate("SelectLibraryDialog", "Select Library", nullptr));
        label_92->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        label_93->setText(QCoreApplication::translate("SelectLibraryDialog", "\344\270\213\351\231\220\343\201\227\343\201\215\343\201\204\345\200\244\357\274\210\346\234\200\345\260\217\357\274\220\357\274\211", nullptr));
        label_94->setText(QCoreApplication::translate("SelectLibraryDialog", "\344\270\212\351\231\220\343\201\227\343\201\215\343\201\204\345\200\244\357\274\210\346\234\200\345\260\217\357\274\220\357\274\211", nullptr));
        label_95->setText(QCoreApplication::translate("SelectLibraryDialog", "\350\274\252\351\203\255\345\271\205", nullptr));
        EditLibID->setText(QCoreApplication::translate("SelectLibraryDialog", "12345", nullptr));
        label_4->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\220\215\347\247\260", nullptr));
        EditLibName->setText(QCoreApplication::translate("SelectLibraryDialog", "Library Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectLibraryDialog", "Name", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectLibraryDialog", "Select", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectLibraryDialog", "Cancel", nullptr));
        EditItemName->setText(QString());
        label_5->setText(QCoreApplication::translate("SelectLibraryDialog", "Item Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibraryDialog: public Ui_SelectLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBRARYDIALOG_H
