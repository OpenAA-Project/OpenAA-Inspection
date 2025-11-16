/********************************************************************************
** Form generated from reading UI file 'PropertyLearningForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYLEARNINGFORM_H
#define UI_PROPERTYLEARNINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyLearningFormClass
{
public:
    QTableWidget *tableWidgetTrialList;
    QPushButton *pushButtonAddTrialFile;
    QPushButton *pushButtonDelTrialFile;
    QFrame *frame;
    QTableWidget *tableWidgetAreaList;
    QListWidget *listWidgetFileNamePerPage;
    QLabel *label;
    QPushButton *pushButtonLoadImage;

    void setupUi(GUIFormBase *PropertyLearningFormClass)
    {
        if (PropertyLearningFormClass->objectName().isEmpty())
            PropertyLearningFormClass->setObjectName("PropertyLearningFormClass");
        PropertyLearningFormClass->resize(400, 700);
        tableWidgetTrialList = new QTableWidget(PropertyLearningFormClass);
        if (tableWidgetTrialList->columnCount() < 2)
            tableWidgetTrialList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetTrialList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetTrialList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetTrialList->setObjectName("tableWidgetTrialList");
        tableWidgetTrialList->setGeometry(QRect(10, 20, 291, 192));
        tableWidgetTrialList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetTrialList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonAddTrialFile = new QPushButton(PropertyLearningFormClass);
        pushButtonAddTrialFile->setObjectName("pushButtonAddTrialFile");
        pushButtonAddTrialFile->setGeometry(QRect(310, 40, 81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAddTrialFile->setIcon(icon);
        pushButtonDelTrialFile = new QPushButton(PropertyLearningFormClass);
        pushButtonDelTrialFile->setObjectName("pushButtonDelTrialFile");
        pushButtonDelTrialFile->setGeometry(QRect(310, 90, 81, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDelTrialFile->setIcon(icon1);
        frame = new QFrame(PropertyLearningFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 270, 381, 311));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        tableWidgetAreaList = new QTableWidget(frame);
        if (tableWidgetAreaList->columnCount() < 4)
            tableWidgetAreaList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(3, __qtablewidgetitem5);
        tableWidgetAreaList->setObjectName("tableWidgetAreaList");
        tableWidgetAreaList->setGeometry(QRect(10, 120, 361, 181));
        tableWidgetAreaList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAreaList->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidgetFileNamePerPage = new QListWidget(frame);
        listWidgetFileNamePerPage->setObjectName("listWidgetFileNamePerPage");
        listWidgetFileNamePerPage->setGeometry(QRect(10, 30, 361, 81));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 361, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonLoadImage = new QPushButton(PropertyLearningFormClass);
        pushButtonLoadImage->setObjectName("pushButtonLoadImage");
        pushButtonLoadImage->setGeometry(QRect(310, 170, 81, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Load.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonLoadImage->setIcon(icon2);

        retranslateUi(PropertyLearningFormClass);

        QMetaObject::connectSlotsByName(PropertyLearningFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyLearningFormClass)
    {
        PropertyLearningFormClass->setWindowTitle(QCoreApplication::translate("PropertyLearningFormClass", "PropertyLearningForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetTrialList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyLearningFormClass", "\347\225\252\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetTrialList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyLearningFormClass", "Page0", nullptr));
        pushButtonAddTrialFile->setText(QCoreApplication::translate("PropertyLearningFormClass", "Add File", nullptr));
        pushButtonDelTrialFile->setText(QCoreApplication::translate("PropertyLearningFormClass", "Del File", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetAreaList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyLearningFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetAreaList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyLearningFormClass", "NG/OK", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetAreaList->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyLearningFormClass", "NGLevel", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetAreaList->horizontalHeaderItem(3);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyLearningFormClass", "Position", nullptr));
        label->setText(QCoreApplication::translate("PropertyLearningFormClass", "\350\241\250\347\244\272\344\270\255\343\201\256\343\203\225\343\202\241\343\202\244\343\203\253", nullptr));
        pushButtonLoadImage->setText(QCoreApplication::translate("PropertyLearningFormClass", "Load Image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyLearningFormClass: public Ui_PropertyLearningFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYLEARNINGFORM_H
