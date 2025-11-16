/********************************************************************************
** Form generated from reading UI file 'PropertySavePartialImageForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYSAVEPARTIALIMAGEFORM_H
#define UI_PROPERTYSAVEPARTIALIMAGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PropertySavePartialImageForm
{
public:
    QFrame *frame;
    QToolButton *toolButtonArea;
    QToolButton *toolButtonImage;
    QTableWidget *tableWidget;

    void setupUi(QWidget *PropertySavePartialImageForm)
    {
        if (PropertySavePartialImageForm->objectName().isEmpty())
            PropertySavePartialImageForm->setObjectName(QString::fromUtf8("PropertySavePartialImageForm"));
        PropertySavePartialImageForm->resize(400, 300);
        frame = new QFrame(PropertySavePartialImageForm);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(40, 10, 331, 51));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonArea = new QToolButton(frame);
        toolButtonArea->setObjectName(QString::fromUtf8("toolButtonArea"));
        toolButtonArea->setGeometry(QRect(10, 10, 121, 31));
        toolButtonArea->setCheckable(true);
        toolButtonArea->setChecked(false);
        toolButtonArea->setAutoExclusive(true);
        toolButtonArea->setAutoRaise(false);
        toolButtonImage = new QToolButton(frame);
        toolButtonImage->setObjectName(QString::fromUtf8("toolButtonImage"));
        toolButtonImage->setGeometry(QRect(180, 10, 141, 31));
        toolButtonImage->setCheckable(true);
        toolButtonImage->setChecked(true);
        toolButtonImage->setAutoExclusive(true);
        toolButtonImage->setAutoRaise(false);
        tableWidget = new QTableWidget(PropertySavePartialImageForm);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 70, 381, 192));

        retranslateUi(PropertySavePartialImageForm);

        QMetaObject::connectSlotsByName(PropertySavePartialImageForm);
    } // setupUi

    void retranslateUi(QWidget *PropertySavePartialImageForm)
    {
        PropertySavePartialImageForm->setWindowTitle(QCoreApplication::translate("PropertySavePartialImageForm", "Form", nullptr));
        toolButtonArea->setText(QCoreApplication::translate("PropertySavePartialImageForm", "Area", nullptr));
        toolButtonImage->setText(QCoreApplication::translate("PropertySavePartialImageForm", "Image", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertySavePartialImageForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertySavePartialImageForm", "Location", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertySavePartialImageForm", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertySavePartialImageForm: public Ui_PropertySavePartialImageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYSAVEPARTIALIMAGEFORM_H
