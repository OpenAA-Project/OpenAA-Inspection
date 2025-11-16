/********************************************************************************
** Form generated from reading UI file 'ResultLotLoadForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTLOTLOADFORM_H
#define UI_RESULTLOTLOADFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ResultLotLoadClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QTableWidget *twResultTable;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_2;
    QLabel *lbResultText;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;

    void setupUi(QDialog *ResultLotLoadClass)
    {
        if (ResultLotLoadClass->objectName().isEmpty())
            ResultLotLoadClass->setObjectName(QString::fromUtf8("ResultLotLoadClass"));
        ResultLotLoadClass->resize(717, 378);
        gridLayout = new QGridLayout(ResultLotLoadClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label = new QLabel(ResultLotLoadClass);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(30);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        twResultTable = new QTableWidget(ResultLotLoadClass);
        if (twResultTable->columnCount() < 2)
            twResultTable->setColumnCount(2);
        QFont font1;
        font1.setPointSize(14);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem->setFont(font1);
        twResultTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem1->setFont(font1);
        twResultTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (twResultTable->rowCount() < 3)
            twResultTable->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem2->setFont(font1);
        twResultTable->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem3->setFont(font1);
        twResultTable->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem4->setFont(font1);
        twResultTable->setVerticalHeaderItem(2, __qtablewidgetitem4);
        twResultTable->setObjectName(QString::fromUtf8("twResultTable"));
        twResultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twResultTable->setAlternatingRowColors(false);
        twResultTable->setGridStyle(Qt::DashDotLine);
        twResultTable->setCornerButtonEnabled(false);
        twResultTable->horizontalHeader()->setStretchLastSection(true);
        twResultTable->verticalHeader()->setStretchLastSection(true);

        horizontalLayout_3->addWidget(twResultTable);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        horizontalLayout_3->setStretch(1, 1);

        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        label_2 = new QLabel(ResultLotLoadClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font2;
        font2.setPointSize(20);
        label_2->setFont(font2);

        horizontalLayout_4->addWidget(label_2);

        lbResultText = new QLabel(ResultLotLoadClass);
        lbResultText->setObjectName(QString::fromUtf8("lbResultText"));
        lbResultText->setFont(font2);

        horizontalLayout_4->addWidget(lbResultText);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(ResultLotLoadClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        gridLayout->setRowStretch(1, 1);

        retranslateUi(ResultLotLoadClass);
        QObject::connect(okButton, SIGNAL(clicked()), ResultLotLoadClass, SLOT(accept()));

        QMetaObject::connectSlotsByName(ResultLotLoadClass);
    } // setupUi

    void retranslateUi(QDialog *ResultLotLoadClass)
    {
        ResultLotLoadClass->setWindowTitle(QCoreApplication::translate("ResultLotLoadClass", "Result Lot Load Form", nullptr));
        label->setText(QCoreApplication::translate("ResultLotLoadClass", "Load Result", nullptr));
        QTableWidgetItem *___qtablewidgetitem = twResultTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ResultLotLoadClass", "Front", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = twResultTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ResultLotLoadClass", "Back", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = twResultTable->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ResultLotLoadClass", "NG Count", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = twResultTable->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ResultLotLoadClass", "OK Count", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = twResultTable->verticalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ResultLotLoadClass", "Count All", nullptr));
        label_2->setText(QCoreApplication::translate("ResultLotLoadClass", "Result...", nullptr));
        lbResultText->setText(QCoreApplication::translate("ResultLotLoadClass", "TextLabel", nullptr));
        okButton->setText(QCoreApplication::translate("ResultLotLoadClass", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResultLotLoadClass: public Ui_ResultLotLoadClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTLOTLOADFORM_H
