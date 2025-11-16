/********************************************************************************
** Form generated from reading UI file 'ColorSelectBlockLibraryForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORSELECTBLOCKLIBRARYFORM_H
#define UI_COLORSELECTBLOCKLIBRARYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ColorSelectBlockLibraryFormClass
{
public:
    QFrame *frameLibFolder;
    QPushButton *ButtonSelect;
    QPushButton *ButtonCancel;
    QTableWidget *tableWidgetLibList;

    void setupUi(QDialog *ColorSelectBlockLibraryFormClass)
    {
        if (ColorSelectBlockLibraryFormClass->objectName().isEmpty())
            ColorSelectBlockLibraryFormClass->setObjectName("ColorSelectBlockLibraryFormClass");
        ColorSelectBlockLibraryFormClass->resize(413, 196);
        frameLibFolder = new QFrame(ColorSelectBlockLibraryFormClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonSelect = new QPushButton(ColorSelectBlockLibraryFormClass);
        ButtonSelect->setObjectName("ButtonSelect");
        ButtonSelect->setGeometry(QRect(210, 160, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonSelect->setIcon(icon);
        ButtonCancel = new QPushButton(ColorSelectBlockLibraryFormClass);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(320, 160, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        tableWidgetLibList = new QTableWidget(ColorSelectBlockLibraryFormClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 201, 141));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(ColorSelectBlockLibraryFormClass);

        QMetaObject::connectSlotsByName(ColorSelectBlockLibraryFormClass);
    } // setupUi

    void retranslateUi(QDialog *ColorSelectBlockLibraryFormClass)
    {
        ColorSelectBlockLibraryFormClass->setWindowTitle(QCoreApplication::translate("ColorSelectBlockLibraryFormClass", "ColorSelectBlockLibraryForm", nullptr));
        ButtonSelect->setText(QCoreApplication::translate("ColorSelectBlockLibraryFormClass", "Select", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("ColorSelectBlockLibraryFormClass", "Cancel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ColorSelectBlockLibraryFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ColorSelectBlockLibraryFormClass", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ColorSelectBlockLibraryFormClass: public Ui_ColorSelectBlockLibraryFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORSELECTBLOCKLIBRARYFORM_H
