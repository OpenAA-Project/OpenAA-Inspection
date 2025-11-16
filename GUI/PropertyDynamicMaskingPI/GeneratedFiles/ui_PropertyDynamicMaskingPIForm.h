/********************************************************************************
** Form generated from reading UI file 'PropertyDynamicMaskingPIForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYDYNAMICMASKINGPIFORM_H
#define UI_PROPERTYDYNAMICMASKINGPIFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyDynamicMaskingPIFormClass
{
public:
    QTableWidget *tableWidgetMaskingList;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label_5;
    QLabel *label_3;
    QSpinBox *spinBoxBlockWidth;
    QSpinBox *spinBoxDark;
    QSpinBox *spinBoxEnsmall;
    QSpinBox *spinBoxEnlarge;
    QSpinBox *spinBoxLight;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_8;
    QLabel *label_2;
    QSpinBox *spinBoxBlockHeight;
    QSpinBox *spinBoxMinSize;
    QLabel *label_15;
    QWidget *page_2;
    QLabel *label_9;
    QSpinBox *spinBoxDrawCol;
    QGroupBox *groupBox;
    QRadioButton *radioButtonPickupMask;
    QRadioButton *radioButtonDrawMask;
    QPushButton *pushButtonSet;

    void setupUi(GUIFormBase *PropertyDynamicMaskingPIFormClass)
    {
        if (PropertyDynamicMaskingPIFormClass->objectName().isEmpty())
            PropertyDynamicMaskingPIFormClass->setObjectName("PropertyDynamicMaskingPIFormClass");
        PropertyDynamicMaskingPIFormClass->resize(400, 700);
        tableWidgetMaskingList = new QTableWidget(PropertyDynamicMaskingPIFormClass);
        if (tableWidgetMaskingList->columnCount() < 5)
            tableWidgetMaskingList->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetMaskingList->setObjectName("tableWidgetMaskingList");
        tableWidgetMaskingList->setGeometry(QRect(10, 10, 381, 371));
        tableWidgetMaskingList->setSelectionBehavior(QAbstractItemView::SelectRows);
        stackedWidget = new QStackedWidget(PropertyDynamicMaskingPIFormClass);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(90, 440, 231, 211));
        page = new QWidget();
        page->setObjectName("page");
        label_5 = new QLabel(page);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(120, 0, 91, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(page);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(-10, 90, 101, 16));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxBlockWidth = new QSpinBox(page);
        spinBoxBlockWidth->setObjectName("spinBoxBlockWidth");
        spinBoxBlockWidth->setGeometry(QRect(150, 120, 61, 22));
        spinBoxBlockWidth->setMinimum(1);
        spinBoxBlockWidth->setMaximum(300);
        spinBoxDark = new QSpinBox(page);
        spinBoxDark->setObjectName("spinBoxDark");
        spinBoxDark->setGeometry(QRect(10, 20, 91, 22));
        spinBoxDark->setMaximum(255);
        spinBoxEnsmall = new QSpinBox(page);
        spinBoxEnsmall->setObjectName("spinBoxEnsmall");
        spinBoxEnsmall->setGeometry(QRect(150, 60, 61, 22));
        spinBoxEnlarge = new QSpinBox(page);
        spinBoxEnlarge->setObjectName("spinBoxEnlarge");
        spinBoxEnlarge->setGeometry(QRect(150, 90, 61, 22));
        spinBoxLight = new QSpinBox(page);
        spinBoxLight->setObjectName("spinBoxLight");
        spinBoxLight->setGeometry(QRect(120, 20, 91, 22));
        spinBoxLight->setMaximum(255);
        label_7 = new QLabel(page);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 120, 131, 16));
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(page);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 0, 91, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_8 = new QLabel(page);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 150, 131, 16));
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(-10, 60, 101, 16));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxBlockHeight = new QSpinBox(page);
        spinBoxBlockHeight->setObjectName("spinBoxBlockHeight");
        spinBoxBlockHeight->setGeometry(QRect(150, 150, 61, 22));
        spinBoxBlockHeight->setMinimum(1);
        spinBoxBlockHeight->setMaximum(300);
        spinBoxMinSize = new QSpinBox(page);
        spinBoxMinSize->setObjectName("spinBoxMinSize");
        spinBoxMinSize->setGeometry(QRect(130, 180, 81, 22));
        spinBoxMinSize->setMinimum(0);
        spinBoxMinSize->setMaximum(99999999);
        spinBoxMinSize->setValue(1);
        label_15 = new QLabel(page);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 180, 111, 16));
        label_15->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        label_9 = new QLabel(page_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(70, 30, 91, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxDrawCol = new QSpinBox(page_2);
        spinBoxDrawCol->setObjectName("spinBoxDrawCol");
        spinBoxDrawCol->setGeometry(QRect(70, 50, 91, 22));
        spinBoxDrawCol->setMaximum(255);
        stackedWidget->addWidget(page_2);
        groupBox = new QGroupBox(PropertyDynamicMaskingPIFormClass);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(90, 390, 241, 41));
        radioButtonPickupMask = new QRadioButton(groupBox);
        radioButtonPickupMask->setObjectName("radioButtonPickupMask");
        radioButtonPickupMask->setGeometry(QRect(10, 10, 101, 17));
        radioButtonPickupMask->setChecked(true);
        radioButtonDrawMask = new QRadioButton(groupBox);
        radioButtonDrawMask->setObjectName("radioButtonDrawMask");
        radioButtonDrawMask->setGeometry(QRect(130, 10, 101, 17));
        pushButtonSet = new QPushButton(PropertyDynamicMaskingPIFormClass);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(150, 657, 121, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSet->setIcon(icon);
        QWidget::setTabOrder(tableWidgetMaskingList, spinBoxDark);
        QWidget::setTabOrder(spinBoxDark, spinBoxLight);
        QWidget::setTabOrder(spinBoxLight, spinBoxEnsmall);
        QWidget::setTabOrder(spinBoxEnsmall, spinBoxEnlarge);
        QWidget::setTabOrder(spinBoxEnlarge, spinBoxBlockWidth);
        QWidget::setTabOrder(spinBoxBlockWidth, spinBoxBlockHeight);

        retranslateUi(PropertyDynamicMaskingPIFormClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PropertyDynamicMaskingPIFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyDynamicMaskingPIFormClass)
    {
        PropertyDynamicMaskingPIFormClass->setWindowTitle(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "PropertyDynamicMaskingPIForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetMaskingList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetMaskingList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "Mode", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetMaskingList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "Shrink", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetMaskingList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "Enlarge", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetMaskingList->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "Area", nullptr));
        label_5->setText(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "\346\230\216\345\201\264\350\274\235\345\272\246", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_7->setText(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "\345\207\246\347\220\206\343\203\226\343\203\255\343\203\203\343\202\257\343\201\256\346\250\252\343\201\256\343\202\265\343\202\244\343\202\272", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "\346\232\227\345\201\264\350\274\235\345\272\246", nullptr));
        label_8->setText(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "\345\207\246\347\220\206\343\203\226\343\203\255\343\203\203\343\202\257\343\201\256\347\270\246\343\201\256\343\202\265\343\202\244\343\202\272", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "\345\217\216\347\270\256\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_15->setText(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_9->setText(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "\346\217\217\347\224\273\350\274\235\345\272\246", nullptr));
        radioButtonPickupMask->setText(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "\346\212\275\345\207\272\343\203\236\343\202\271\343\202\257", nullptr));
        radioButtonDrawMask->setText(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "\346\217\217\347\224\273\343\203\236\343\202\271\343\202\257", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("PropertyDynamicMaskingPIFormClass", "Set", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyDynamicMaskingPIFormClass: public Ui_PropertyDynamicMaskingPIFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYDYNAMICMASKINGPIFORM_H
