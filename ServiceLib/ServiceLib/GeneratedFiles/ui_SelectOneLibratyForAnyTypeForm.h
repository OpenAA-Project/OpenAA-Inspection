/********************************************************************************
** Form generated from reading UI file 'SelectOneLibratyForAnyTypeForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTONELIBRATYFORANYTYPEFORM_H
#define UI_SELECTONELIBRATYFORANYTYPEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectOneLibratyForAnyTypeForm
{
public:
    QComboBox *comboBLibType;
    QPushButton *pushButtonOK;
    QTableWidget *tableWidgetLibList;
    QFrame *frameLibFolder;
    QPushButton *pushButtonCancel;
    QFrame *frame;
    QLineEdit *lineEditLibName;
    QLabel *label;
    QSpinBox *spinBoxLibID;
    QLabel *label_3;
    QLabel *label_2;

    void setupUi(QWidget *SelectOneLibratyForAnyTypeForm)
    {
        if (SelectOneLibratyForAnyTypeForm->objectName().isEmpty())
            SelectOneLibratyForAnyTypeForm->setObjectName("SelectOneLibratyForAnyTypeForm");
        SelectOneLibratyForAnyTypeForm->resize(428, 411);
        comboBLibType = new QComboBox(SelectOneLibratyForAnyTypeForm);
        comboBLibType->setObjectName("comboBLibType");
        comboBLibType->setGeometry(QRect(10, 10, 201, 22));
        pushButtonOK = new QPushButton(SelectOneLibratyForAnyTypeForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(220, 360, 91, 41));
        tableWidgetLibList = new QTableWidget(SelectOneLibratyForAnyTypeForm);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 190, 201, 211));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolder = new QFrame(SelectOneLibratyForAnyTypeForm);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 30, 201, 161));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        pushButtonCancel = new QPushButton(SelectOneLibratyForAnyTypeForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(330, 360, 91, 41));
        frame = new QFrame(SelectOneLibratyForAnyTypeForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(220, 210, 201, 131));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        lineEditLibName = new QLineEdit(frame);
        lineEditLibName->setObjectName("lineEditLibName");
        lineEditLibName->setGeometry(QRect(10, 90, 181, 31));
        QPalette palette;
        QBrush brush(QColor(85, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        QBrush brush2(QColor(240, 240, 240, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush2);
        lineEditLibName->setPalette(palette);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 201, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxLibID = new QSpinBox(frame);
        spinBoxLibID->setObjectName("spinBoxLibID");
        spinBoxLibID->setGeometry(QRect(90, 30, 101, 31));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush2);
        spinBoxLibID->setPalette(palette1);
        spinBoxLibID->setReadOnly(true);
        spinBoxLibID->setButtonSymbols(QAbstractSpinBox::NoButtons);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 181, 20));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 30, 81, 20));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(SelectOneLibratyForAnyTypeForm);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SelectOneLibratyForAnyTypeForm);
    } // setupUi

    void retranslateUi(QWidget *SelectOneLibratyForAnyTypeForm)
    {
        SelectOneLibratyForAnyTypeForm->setWindowTitle(QCoreApplication::translate("SelectOneLibratyForAnyTypeForm", "Form", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectOneLibratyForAnyTypeForm", "OK", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectOneLibratyForAnyTypeForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectOneLibratyForAnyTypeForm", "\345\220\215\345\211\215", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectOneLibratyForAnyTypeForm", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("SelectOneLibratyForAnyTypeForm", "Selected", nullptr));
        label_3->setText(QCoreApplication::translate("SelectOneLibratyForAnyTypeForm", "Library name", nullptr));
        label_2->setText(QCoreApplication::translate("SelectOneLibratyForAnyTypeForm", "LibID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectOneLibratyForAnyTypeForm: public Ui_SelectOneLibratyForAnyTypeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTONELIBRATYFORANYTYPEFORM_H
