/********************************************************************************
** Form generated from reading UI file 'propertylist.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYLIST_H
#define UI_PROPERTYLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_PropertyList
{
public:
    QFrame *frame;
    QLabel *label;
    QLabel *label_2;
    QLabel *labelDLLName;
    QLabel *labelDLLRoot;
    QTableView *tableView;

    void setupUi(GUIFormBase *PropertyList)
    {
        if (PropertyList->objectName().isEmpty())
            PropertyList->setObjectName("PropertyList");
        PropertyList->resize(285, 497);
        frame = new QFrame(PropertyList);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 281, 41));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 71, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 20, 71, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelDLLName = new QLabel(frame);
        labelDLLName->setObjectName("labelDLLName");
        labelDLLName->setGeometry(QRect(70, 20, 191, 20));
        labelDLLName->setFrameShape(QFrame::Panel);
        labelDLLName->setFrameShadow(QFrame::Sunken);
        labelDLLName->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelDLLRoot = new QLabel(frame);
        labelDLLRoot->setObjectName("labelDLLRoot");
        labelDLLRoot->setGeometry(QRect(70, 0, 191, 20));
        labelDLLRoot->setFrameShape(QFrame::Panel);
        labelDLLRoot->setFrameShadow(QFrame::Sunken);
        labelDLLRoot->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableView = new QTableView(PropertyList);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(10, 50, 241, 341));

        retranslateUi(PropertyList);

        QMetaObject::connectSlotsByName(PropertyList);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyList)
    {
        PropertyList->setWindowTitle(QCoreApplication::translate("PropertyList", "Form", nullptr));
        label->setText(QCoreApplication::translate("PropertyList", "DLL Root", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyList", "DLL Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyList: public Ui_PropertyList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYLIST_H
