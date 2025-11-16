/********************************************************************************
** Form generated from reading UI file 'HistoryListErrorForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORYLISTERRORFORM_H
#define UI_HISTORYLISTERRORFORM_H

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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_HistoryListErrorClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableWidget *twBoardCount;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *twFrontError;
    QTableWidget *twBackError;

    void setupUi(QDialog *HistoryListErrorClass)
    {
        if (HistoryListErrorClass->objectName().isEmpty())
            HistoryListErrorClass->setObjectName(QString::fromUtf8("HistoryListErrorClass"));
        HistoryListErrorClass->resize(804, 410);
        gridLayout = new QGridLayout(HistoryListErrorClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(HistoryListErrorClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(HistoryListErrorClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        twBoardCount = new QTableWidget(HistoryListErrorClass);
        if (twBoardCount->columnCount() < 2)
            twBoardCount->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        twBoardCount->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        twBoardCount->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (twBoardCount->rowCount() < 3)
            twBoardCount->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        twBoardCount->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        twBoardCount->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        twBoardCount->setVerticalHeaderItem(2, __qtablewidgetitem4);
        twBoardCount->setObjectName(QString::fromUtf8("twBoardCount"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(twBoardCount->sizePolicy().hasHeightForWidth());
        twBoardCount->setSizePolicy(sizePolicy);
        twBoardCount->setContextMenuPolicy(Qt::NoContextMenu);
        twBoardCount->setAutoFillBackground(false);
        twBoardCount->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        twBoardCount->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        twBoardCount->setAutoScroll(false);
        twBoardCount->setTabKeyNavigation(false);
        twBoardCount->setProperty("showDropIndicator", QVariant(false));
        twBoardCount->setDragDropOverwriteMode(false);
        twBoardCount->setAlternatingRowColors(false);
        twBoardCount->setSelectionMode(QAbstractItemView::NoSelection);
        twBoardCount->setWordWrap(true);
        twBoardCount->setCornerButtonEnabled(true);
        twBoardCount->horizontalHeader()->setCascadingSectionResizes(false);
        twBoardCount->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        twBoardCount->horizontalHeader()->setStretchLastSection(false);
        twBoardCount->verticalHeader()->setCascadingSectionResizes(false);
        twBoardCount->verticalHeader()->setStretchLastSection(false);

        verticalLayout->addWidget(twBoardCount);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(HistoryListErrorClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        twFrontError = new QTableWidget(HistoryListErrorClass);
        if (twFrontError->columnCount() < 2)
            twFrontError->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        twFrontError->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        twFrontError->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        twFrontError->setObjectName(QString::fromUtf8("twFrontError"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(twFrontError->sizePolicy().hasHeightForWidth());
        twFrontError->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(twFrontError);

        twBackError = new QTableWidget(HistoryListErrorClass);
        if (twBackError->columnCount() < 2)
            twBackError->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        twBackError->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        twBackError->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        twBackError->setObjectName(QString::fromUtf8("twBackError"));
        sizePolicy2.setHeightForWidth(twBackError->sizePolicy().hasHeightForWidth());
        twBackError->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(twBackError);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_2, 0, 2, 1, 1);

        QWidget::setTabOrder(okButton, twBoardCount);
        QWidget::setTabOrder(twBoardCount, twFrontError);
        QWidget::setTabOrder(twFrontError, twBackError);

        retranslateUi(HistoryListErrorClass);
        QObject::connect(okButton, SIGNAL(clicked()), HistoryListErrorClass, SLOT(accept()));

        QMetaObject::connectSlotsByName(HistoryListErrorClass);
    } // setupUi

    void retranslateUi(QDialog *HistoryListErrorClass)
    {
        HistoryListErrorClass->setWindowTitle(QCoreApplication::translate("HistoryListErrorClass", "HistoryListErrorForm", nullptr));
        okButton->setText(QCoreApplication::translate("HistoryListErrorClass", "OK", nullptr));
        label->setText(QCoreApplication::translate("HistoryListErrorClass", "Board Count", nullptr));
        QTableWidgetItem *___qtablewidgetitem = twBoardCount->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("HistoryListErrorClass", "Front", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = twBoardCount->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("HistoryListErrorClass", "Back", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = twBoardCount->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("HistoryListErrorClass", "OK", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = twBoardCount->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("HistoryListErrorClass", "NG", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = twBoardCount->verticalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("HistoryListErrorClass", "Sum", nullptr));
        label_2->setText(QCoreApplication::translate("HistoryListErrorClass", "Inspect ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = twFrontError->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("HistoryListErrorClass", "Front ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = twFrontError->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("HistoryListErrorClass", "ErrorType", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = twBackError->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("HistoryListErrorClass", "Back ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = twBackError->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("HistoryListErrorClass", "ErrorType", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HistoryListErrorClass: public Ui_HistoryListErrorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORYLISTERRORFORM_H
