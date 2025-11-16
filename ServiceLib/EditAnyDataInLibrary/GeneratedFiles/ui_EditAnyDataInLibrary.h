/********************************************************************************
** Form generated from reading UI file 'EditAnyDataInLibrary.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITANYDATAINLIBRARY_H
#define UI_EDITANYDATAINLIBRARY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditAnyDataInLibraryClass
{
public:
    QWidget *centralWidget;
    QTableWidget *tableWidgetLibList;
    QFrame *frameLibFolder;
    QTableWidget *tableWidgetAnyData;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QFrame *frame_2;
    QLabel *label_7;
    QPushButton *pushButtonColor;
    QSpinBox *spinBoxNextJumpMilisec;
    QLabel *label_8;
    QLabel *label_9;
    QSpinBox *spinBoxPriority;
    QComboBox *comboBoxNGShape;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *lineEditDataName;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonSpecifiedData;
    QPushButton *pushButtonCreateNew;
    QPushButton *pushButtonDelete;
    QCheckBox *checkBoxBlink;
    QLabel *label_13;
    QLineEdit *lineEditTypeUniqueCode;
    QLabel *label_14;
    QLineEdit *lineEditTypeCode;
    QFrame *frame_3;
    QLabel *label_12;
    QPushButton *pushButtonCopyToCB;
    QPushButton *pushButtonPasteFromCB;
    QPushButton *pushButtonClose;
    QTableWidget *tableWidgetLibType;

    void setupUi(QMainWindow *EditAnyDataInLibraryClass)
    {
        if (EditAnyDataInLibraryClass->objectName().isEmpty())
            EditAnyDataInLibraryClass->setObjectName("EditAnyDataInLibraryClass");
        EditAnyDataInLibraryClass->resize(754, 732);
        centralWidget = new QWidget(EditAnyDataInLibraryClass);
        centralWidget->setObjectName("centralWidget");
        tableWidgetLibList = new QTableWidget(centralWidget);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(290, 210, 221, 221));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolder = new QFrame(centralWidget);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(40, 210, 241, 221));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        tableWidgetAnyData = new QTableWidget(centralWidget);
        if (tableWidgetAnyData->columnCount() < 2)
            tableWidgetAnyData->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetAnyData->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetAnyData->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetAnyData->setObjectName("tableWidgetAnyData");
        tableWidgetAnyData->setGeometry(QRect(520, 210, 221, 221));
        tableWidgetAnyData->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAnyData->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 10, 241, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 190, 471, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(520, 190, 211, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 30, 21, 151));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        QBrush brush1(QColor(0, 255, 127, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        QBrush brush2(QColor(106, 104, 100, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush2);
        QBrush brush3(QColor(212, 208, 200, 255));
        brush3.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        label_4->setPalette(palette);
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 210, 21, 221));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush2);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        label_5->setPalette(palette1);
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 450, 21, 191));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush2);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        label_6->setPalette(palette2);
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(40, 440, 351, 281));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 0, 351, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonColor = new QPushButton(frame_2);
        pushButtonColor->setObjectName("pushButtonColor");
        pushButtonColor->setGeometry(QRect(20, 120, 75, 23));
        spinBoxNextJumpMilisec = new QSpinBox(frame_2);
        spinBoxNextJumpMilisec->setObjectName("spinBoxNextJumpMilisec");
        spinBoxNextJumpMilisec->setGeometry(QRect(260, 180, 81, 22));
        spinBoxNextJumpMilisec->setMaximum(9999999);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 180, 231, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_9 = new QLabel(frame_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 210, 231, 20));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxPriority = new QSpinBox(frame_2);
        spinBoxPriority->setObjectName("spinBoxPriority");
        spinBoxPriority->setGeometry(QRect(260, 210, 81, 22));
        spinBoxPriority->setMaximum(9999999);
        comboBoxNGShape = new QComboBox(frame_2);
        comboBoxNGShape->addItem(QString());
        comboBoxNGShape->addItem(QString());
        comboBoxNGShape->addItem(QString());
        comboBoxNGShape->addItem(QString());
        comboBoxNGShape->addItem(QString());
        comboBoxNGShape->addItem(QString());
        comboBoxNGShape->addItem(QString());
        comboBoxNGShape->addItem(QString());
        comboBoxNGShape->addItem(QString());
        comboBoxNGShape->setObjectName("comboBoxNGShape");
        comboBoxNGShape->setGeometry(QRect(180, 120, 161, 22));
        label_10 = new QLabel(frame_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(120, 120, 61, 20));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_11 = new QLabel(frame_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(20, 90, 101, 20));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditDataName = new QLineEdit(frame_2);
        lineEditDataName->setObjectName("lineEditDataName");
        lineEditDataName->setGeometry(QRect(130, 90, 211, 20));
        pushButtonUpdate = new QPushButton(frame_2);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(100, 240, 61, 31));
        pushButtonSpecifiedData = new QPushButton(frame_2);
        pushButtonSpecifiedData->setObjectName("pushButtonSpecifiedData");
        pushButtonSpecifiedData->setGeometry(QRect(240, 240, 101, 31));
        pushButtonCreateNew = new QPushButton(frame_2);
        pushButtonCreateNew->setObjectName("pushButtonCreateNew");
        pushButtonCreateNew->setGeometry(QRect(20, 240, 71, 31));
        pushButtonDelete = new QPushButton(frame_2);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(170, 240, 61, 31));
        checkBoxBlink = new QCheckBox(frame_2);
        checkBoxBlink->setObjectName("checkBoxBlink");
        checkBoxBlink->setGeometry(QRect(120, 150, 76, 18));
        label_13 = new QLabel(frame_2);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(20, 30, 101, 20));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditTypeUniqueCode = new QLineEdit(frame_2);
        lineEditTypeUniqueCode->setObjectName("lineEditTypeUniqueCode");
        lineEditTypeUniqueCode->setGeometry(QRect(130, 30, 71, 20));
        QPalette palette3;
        QBrush brush4(QColor(85, 255, 255, 255));
        brush4.setStyle(Qt::BrushStyle::SolidPattern);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush4);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush4);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        lineEditTypeUniqueCode->setPalette(palette3);
        lineEditTypeUniqueCode->setReadOnly(true);
        label_14 = new QLabel(frame_2);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(20, 50, 101, 20));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditTypeCode = new QLineEdit(frame_2);
        lineEditTypeCode->setObjectName("lineEditTypeCode");
        lineEditTypeCode->setGeometry(QRect(130, 50, 71, 20));
        QPalette palette4;
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush4);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush4);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        lineEditTypeCode->setPalette(palette4);
        lineEditTypeCode->setReadOnly(true);
        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(390, 440, 251, 281));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_12 = new QLabel(frame_3);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(0, 0, 251, 20));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonCopyToCB = new QPushButton(frame_3);
        pushButtonCopyToCB->setObjectName("pushButtonCopyToCB");
        pushButtonCopyToCB->setGeometry(QRect(10, 60, 231, 31));
        pushButtonPasteFromCB = new QPushButton(frame_3);
        pushButtonPasteFromCB->setObjectName("pushButtonPasteFromCB");
        pushButtonPasteFromCB->setGeometry(QRect(10, 100, 231, 31));
        pushButtonClose = new QPushButton(centralWidget);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(650, 660, 91, 61));
        tableWidgetLibType = new QTableWidget(centralWidget);
        if (tableWidgetLibType->columnCount() < 2)
            tableWidgetLibType->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetLibType->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetLibType->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        tableWidgetLibType->setObjectName("tableWidgetLibType");
        tableWidgetLibType->setGeometry(QRect(40, 30, 241, 151));
        tableWidgetLibType->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibType->setSelectionBehavior(QAbstractItemView::SelectRows);
        EditAnyDataInLibraryClass->setCentralWidget(centralWidget);

        retranslateUi(EditAnyDataInLibraryClass);

        QMetaObject::connectSlotsByName(EditAnyDataInLibraryClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditAnyDataInLibraryClass)
    {
        EditAnyDataInLibraryClass->setWindowTitle(QCoreApplication::translate("EditAnyDataInLibraryClass", "EditAnyDataInLibrary", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetAnyData->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "NG Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetAnyData->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Name", nullptr));
        label->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Library type", nullptr));
        label_2->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Select Library", nullptr));
        label_3->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "AnyData in library", nullptr));
        label_4->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "1", nullptr));
        label_5->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "2", nullptr));
        label_6->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "3", nullptr));
        label_7->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Common setting", nullptr));
        pushButtonColor->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Color", nullptr));
        label_8->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Waiting milisec to next step", nullptr));
        label_9->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Priority", nullptr));
        comboBoxNGShape->setItemText(0, QCoreApplication::translate("EditAnyDataInLibraryClass", "Circle", nullptr));
        comboBoxNGShape->setItemText(1, QCoreApplication::translate("EditAnyDataInLibraryClass", "Filled circle", nullptr));
        comboBoxNGShape->setItemText(2, QCoreApplication::translate("EditAnyDataInLibraryClass", "Rectangle", nullptr));
        comboBoxNGShape->setItemText(3, QCoreApplication::translate("EditAnyDataInLibraryClass", "Filled Rectangle", nullptr));
        comboBoxNGShape->setItemText(4, QCoreApplication::translate("EditAnyDataInLibraryClass", "X", nullptr));
        comboBoxNGShape->setItemText(5, QCoreApplication::translate("EditAnyDataInLibraryClass", "Star", nullptr));
        comboBoxNGShape->setItemText(6, QCoreApplication::translate("EditAnyDataInLibraryClass", "Filled Star", nullptr));
        comboBoxNGShape->setItemText(7, QCoreApplication::translate("EditAnyDataInLibraryClass", "Cross(+)", nullptr));
        comboBoxNGShape->setItemText(8, QCoreApplication::translate("EditAnyDataInLibraryClass", "Sharp(#)", nullptr));

        label_10->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "NG shape", nullptr));
        label_11->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Name", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Update", nullptr));
        pushButtonSpecifiedData->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Specified data", nullptr));
        pushButtonCreateNew->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Create new", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Delete", nullptr));
        checkBoxBlink->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Blink", nullptr));
        label_13->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Type Unique Code", nullptr));
        label_14->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "TypeCode", nullptr));
        label_12->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Operation", nullptr));
        pushButtonCopyToCB->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "=> Copy common setting to clipboard", nullptr));
        pushButtonPasteFromCB->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "<= Paste common setting from clipboard", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "Close", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetLibType->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "TypeID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetLibType->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("EditAnyDataInLibraryClass", "LibName", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditAnyDataInLibraryClass: public Ui_EditAnyDataInLibraryClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITANYDATAINLIBRARY_H
