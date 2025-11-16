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
    QTableWidget *tableWidgetLibList;
    QFrame *frameLibFolder;
    QFrame *frame;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxDiaPrecision;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxPosPrecision;
    QLabel *label_3;
    QSpinBox *spinBoxNoiseSize;
    QLabel *label_92;
    QSpinBox *EditSearchDot;
    QSpinBox *spinBoxBandWidth;
    QLabel *label_5;
    QLineEdit *EditLibName;
    QLabel *label_4;
    QLineEdit *EditLibID;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonSelect;

    void setupUi(QDialog *SelectLibraryDialog)
    {
        if (SelectLibraryDialog->objectName().isEmpty())
            SelectLibraryDialog->setObjectName("SelectLibraryDialog");
        SelectLibraryDialog->resize(470, 477);
        tableWidgetLibList = new QTableWidget(SelectLibraryDialog);
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
        frameLibFolder = new QFrame(SelectLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 221, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(SelectLibraryDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(80, 270, 331, 131));
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
        doubleSpinBoxDiaPrecision->setReadOnly(true);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 30, 181, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxPosPrecision = new QDoubleSpinBox(frame);
        doubleSpinBoxPosPrecision->setObjectName("doubleSpinBoxPosPrecision");
        doubleSpinBoxPosPrecision->setGeometry(QRect(210, 30, 81, 22));
        doubleSpinBoxPosPrecision->setReadOnly(true);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 50, 181, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxNoiseSize = new QSpinBox(frame);
        spinBoxNoiseSize->setObjectName("spinBoxNoiseSize");
        spinBoxNoiseSize->setGeometry(QRect(210, 50, 81, 22));
        spinBoxNoiseSize->setReadOnly(true);
        label_92 = new QLabel(frame);
        label_92->setObjectName("label_92");
        label_92->setGeometry(QRect(20, 100, 181, 21));
        label_92->setFrameShape(QFrame::Panel);
        label_92->setFrameShadow(QFrame::Sunken);
        label_92->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSearchDot = new QSpinBox(frame);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(210, 100, 81, 22));
        EditSearchDot->setReadOnly(true);
        EditSearchDot->setMaximum(100);
        spinBoxBandWidth = new QSpinBox(frame);
        spinBoxBandWidth->setObjectName("spinBoxBandWidth");
        spinBoxBandWidth->setGeometry(QRect(210, 70, 81, 22));
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 70, 181, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibName = new QLineEdit(SelectLibraryDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(130, 230, 331, 31));
        QFont font;
        font.setPointSize(12);
        EditLibName->setFont(font);
        label_4 = new QLabel(SelectLibraryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 230, 51, 31));
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(SelectLibraryDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 230, 71, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        pushButtonCancel = new QPushButton(SelectLibraryDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(280, 420, 121, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonSelect = new QPushButton(SelectLibraryDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(70, 420, 121, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSelect->setIcon(icon1);

        retranslateUi(SelectLibraryDialog);

        pushButtonSelect->setDefault(true);


        QMetaObject::connectSlotsByName(SelectLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectLibraryDialog)
    {
        SelectLibraryDialog->setWindowTitle(QCoreApplication::translate("SelectLibraryDialog", "Select Library", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectLibraryDialog", "Name", nullptr));
        label->setText(QCoreApplication::translate("SelectLibraryDialog", "\347\251\264\345\276\204\347\262\276\345\272\246", nullptr));
        label_2->setText(QCoreApplication::translate("SelectLibraryDialog", "\344\275\215\347\275\256\347\262\276\345\272\246", nullptr));
        label_3->setText(QCoreApplication::translate("SelectLibraryDialog", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272", nullptr));
        label_92->setText(QCoreApplication::translate("SelectLibraryDialog", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        label_5->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\270\257\345\271\205", nullptr));
        EditLibName->setText(QCoreApplication::translate("SelectLibraryDialog", "Library Name", nullptr));
        label_4->setText(QCoreApplication::translate("SelectLibraryDialog", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("SelectLibraryDialog", "12345", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectLibraryDialog", "Cancel", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectLibraryDialog", "Select", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibraryDialog: public Ui_SelectLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBRARYDIALOG_H
