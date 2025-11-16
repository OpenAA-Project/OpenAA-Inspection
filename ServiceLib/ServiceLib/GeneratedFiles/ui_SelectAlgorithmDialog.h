/********************************************************************************
** Form generated from reading UI file 'SelectAlgorithmDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTALGORITHMDIALOG_H
#define UI_SELECTALGORITHMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectAlgorithmDialog
{
public:
    QTableWidget *tableWidgetAlgorithm;
    QFrame *frame;
    QPushButton *pushButtonAll;
    QPushButton *pushButtonSelectOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectAlgorithmDialog)
    {
        if (SelectAlgorithmDialog->objectName().isEmpty())
            SelectAlgorithmDialog->setObjectName("SelectAlgorithmDialog");
        SelectAlgorithmDialog->resize(491, 313);
        tableWidgetAlgorithm = new QTableWidget(SelectAlgorithmDialog);
        if (tableWidgetAlgorithm->columnCount() < 3)
            tableWidgetAlgorithm->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetAlgorithm->setObjectName("tableWidgetAlgorithm");
        tableWidgetAlgorithm->setGeometry(QRect(10, 10, 471, 251));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidgetAlgorithm->sizePolicy().hasHeightForWidth());
        tableWidgetAlgorithm->setSizePolicy(sizePolicy);
        tableWidgetAlgorithm->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableWidgetAlgorithm->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectItems);
        frame = new QFrame(SelectAlgorithmDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 260, 481, 51));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        pushButtonAll = new QPushButton(frame);
        pushButtonAll->setObjectName("pushButtonAll");
        pushButtonAll->setGeometry(QRect(10, 10, 80, 31));
        pushButtonSelectOK = new QPushButton(frame);
        pushButtonSelectOK->setObjectName("pushButtonSelectOK");
        pushButtonSelectOK->setGeometry(QRect(130, 10, 151, 31));
        pushButtonCancel = new QPushButton(frame);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(360, 10, 111, 31));

        retranslateUi(SelectAlgorithmDialog);

        pushButtonSelectOK->setDefault(true);


        QMetaObject::connectSlotsByName(SelectAlgorithmDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectAlgorithmDialog)
    {
        SelectAlgorithmDialog->setWindowTitle(QCoreApplication::translate("SelectAlgorithmDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetAlgorithm->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectAlgorithmDialog", "C", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetAlgorithm->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectAlgorithmDialog", "DLLRoot", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetAlgorithm->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectAlgorithmDialog", "DLLName", nullptr));
        pushButtonAll->setText(QCoreApplication::translate("SelectAlgorithmDialog", "All", nullptr));
        pushButtonSelectOK->setText(QCoreApplication::translate("SelectAlgorithmDialog", "\351\201\270\346\212\236\346\261\272\345\256\232", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectAlgorithmDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectAlgorithmDialog: public Ui_SelectAlgorithmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTALGORITHMDIALOG_H
