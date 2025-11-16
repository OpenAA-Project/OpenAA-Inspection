/********************************************************************************
** Form generated from reading UI file 'SelectWorkerForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTWORKERFORM_H
#define UI_SELECTWORKERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectWorkerForm
{
public:
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *ButtonSelect;
    QTableView *MListView;
    QLineEdit *EditRemark;
    QLabel *label_3;
    QLineEdit *EditName;
    QLineEdit *EditWorkerID;
    QLineEdit *EditSection;

    void setupUi(QWidget *SelectWorkerForm)
    {
        if (SelectWorkerForm->objectName().isEmpty())
            SelectWorkerForm->setObjectName("SelectWorkerForm");
        SelectWorkerForm->resize(373, 411);
        label_4 = new QLabel(SelectWorkerForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 60, 351, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(SelectWorkerForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 110, 351, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonSelect = new QPushButton(SelectWorkerForm);
        ButtonSelect->setObjectName("ButtonSelect");
        ButtonSelect->setGeometry(QRect(130, 370, 111, 31));
        MListView = new QTableView(SelectWorkerForm);
        MListView->setObjectName("MListView");
        MListView->setGeometry(QRect(10, 170, 351, 191));
        MListView->setSelectionMode(QAbstractItemView::SingleSelection);
        MListView->setSelectionBehavior(QAbstractItemView::SelectRows);
        EditRemark = new QLineEdit(SelectWorkerForm);
        EditRemark->setObjectName("EditRemark");
        EditRemark->setGeometry(QRect(10, 130, 351, 21));
        EditRemark->setMaxLength(64);
        label_3 = new QLabel(SelectWorkerForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 351, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditName = new QLineEdit(SelectWorkerForm);
        EditName->setObjectName("EditName");
        EditName->setGeometry(QRect(100, 30, 261, 21));
        EditName->setMaxLength(64);
        EditWorkerID = new QLineEdit(SelectWorkerForm);
        EditWorkerID->setObjectName("EditWorkerID");
        EditWorkerID->setGeometry(QRect(10, 30, 81, 21));
        EditWorkerID->setReadOnly(true);
        EditSection = new QLineEdit(SelectWorkerForm);
        EditSection->setObjectName("EditSection");
        EditSection->setGeometry(QRect(10, 80, 351, 21));
        EditSection->setMaxLength(64);

        retranslateUi(SelectWorkerForm);

        QMetaObject::connectSlotsByName(SelectWorkerForm);
    } // setupUi

    void retranslateUi(QWidget *SelectWorkerForm)
    {
        SelectWorkerForm->setWindowTitle(QCoreApplication::translate("SelectWorkerForm", "Form", nullptr));
        label_4->setText(QCoreApplication::translate("SelectWorkerForm", "Section", nullptr));
        label_5->setText(QCoreApplication::translate("SelectWorkerForm", "Remark", nullptr));
        ButtonSelect->setText(QCoreApplication::translate("SelectWorkerForm", "Select", nullptr));
        label_3->setText(QCoreApplication::translate("SelectWorkerForm", "Saved folder", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectWorkerForm: public Ui_SelectWorkerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTWORKERFORM_H
