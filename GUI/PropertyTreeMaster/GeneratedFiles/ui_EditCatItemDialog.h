/********************************************************************************
** Form generated from reading UI file 'EditCatItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITCATITEMDIALOG_H
#define UI_EDITCATITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditCatItemDialog
{
public:
    QLabel *label;
    QLineEdit *lineEditCatName;
    QLabel *label_2;
    QLineEdit *lineEditCatID;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_7;
    QFrame *frame_3;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QSpinBox *spinBoxSearchID;
    QPushButton *pushButtonStartSearchByID;
    QLabel *label_5;
    QFrame *frame_2;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEditSearchName;
    QPushButton *pushButtonStartSearchByName;
    QLabel *label_3;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_10;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_8;
    QScrollArea *scrollAreaMachine;
    QWidget *scrollAreaWidgetContents_3;
    QSpacerItem *horizontalSpacer_9;
    QWidget *layoutWidget_3;
    QGridLayout *gridLayout_7;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_7;
    QLabel *labelTopView;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_2;
    QFrame *frameGrid;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonDelete;
    QFrame *frame;
    QGridLayout *gridLayout;
    QFrame *frameCategory;
    QLineEdit *lineEditState;
    QTableWidget *tableWidgetDst;
    QPushButton *pushButtonNew;
    QPushButton *pushButtonAdd;

    void setupUi(QDialog *EditCatItemDialog)
    {
        if (EditCatItemDialog->objectName().isEmpty())
            EditCatItemDialog->setObjectName("EditCatItemDialog");
        EditCatItemDialog->resize(1134, 774);
        label = new QLabel(EditCatItemDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(350, 640, 321, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        lineEditCatName = new QLineEdit(EditCatItemDialog);
        lineEditCatName->setObjectName("lineEditCatName");
        lineEditCatName->setGeometry(QRect(350, 660, 321, 41));
        QFont font;
        font.setPointSize(15);
        lineEditCatName->setFont(font);
        label_2 = new QLabel(EditCatItemDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(250, 640, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        lineEditCatID = new QLineEdit(EditCatItemDialog);
        lineEditCatID->setObjectName("lineEditCatID");
        lineEditCatID->setGeometry(QRect(250, 660, 71, 41));
        lineEditCatID->setFont(font);
        lineEditCatID->setAlignment(Qt::AlignCenter);
        lineEditCatID->setReadOnly(true);
        layoutWidget = new QWidget(EditCatItemDialog);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(50, 340, 601, 55));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget);
        horizontalLayout_7->setSpacing(4);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        frame_3 = new QFrame(layoutWidget);
        frame_3->setObjectName("frame_3");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy);
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        gridLayout_6 = new QGridLayout(frame_3);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(4, 4, 4, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(4);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        spinBoxSearchID = new QSpinBox(frame_3);
        spinBoxSearchID->setObjectName("spinBoxSearchID");
        spinBoxSearchID->setMaximum(99999999);

        horizontalLayout_5->addWidget(spinBoxSearchID);

        pushButtonStartSearchByID = new QPushButton(frame_3);
        pushButtonStartSearchByID->setObjectName("pushButtonStartSearchByID");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonStartSearchByID->setIcon(icon);

        horizontalLayout_5->addWidget(pushButtonStartSearchByID);


        gridLayout_6->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_5, 0, 0, 1, 1);


        horizontalLayout_7->addWidget(frame_3);

        frame_2 = new QFrame(layoutWidget);
        frame_2->setObjectName("frame_2");
        sizePolicy1.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy1);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        gridLayout_5 = new QGridLayout(frame_2);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(4, 4, 4, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(4);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        lineEditSearchName = new QLineEdit(frame_2);
        lineEditSearchName->setObjectName("lineEditSearchName");

        horizontalLayout_4->addWidget(lineEditSearchName);

        pushButtonStartSearchByName = new QPushButton(frame_2);
        pushButtonStartSearchByName->setObjectName("pushButtonStartSearchByName");
        pushButtonStartSearchByName->setIcon(icon);

        horizontalLayout_4->addWidget(pushButtonStartSearchByName);


        gridLayout_5->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_3, 0, 0, 1, 1);


        horizontalLayout_7->addWidget(frame_2);

        layoutWidget_2 = new QWidget(EditCatItemDialog);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(220, 110, 242, 221));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_6->setSpacing(4);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_10);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_8 = new QLabel(layoutWidget_2);
        label_8->setObjectName("label_8");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy2);
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_3->addWidget(label_8);

        scrollAreaMachine = new QScrollArea(layoutWidget_2);
        scrollAreaMachine->setObjectName("scrollAreaMachine");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(scrollAreaMachine->sizePolicy().hasHeightForWidth());
        scrollAreaMachine->setSizePolicy(sizePolicy3);
        scrollAreaMachine->setMinimumSize(QSize(150, 0));
        scrollAreaMachine->setMaximumSize(QSize(150, 200000));
        scrollAreaMachine->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollAreaMachine->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName("scrollAreaWidgetContents_3");
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 148, 195));
        scrollAreaMachine->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_3->addWidget(scrollAreaMachine);


        horizontalLayout_6->addLayout(verticalLayout_3);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);

        layoutWidget_3 = new QWidget(EditCatItemDialog);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(380, 30, 347, 347));
        gridLayout_7 = new QGridLayout(layoutWidget_3);
        gridLayout_7->setSpacing(4);
        gridLayout_7->setObjectName("gridLayout_7");
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_7->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_7, 1, 0, 1, 1);

        labelTopView = new QLabel(layoutWidget_3);
        labelTopView->setObjectName("labelTopView");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(labelTopView->sizePolicy().hasHeightForWidth());
        labelTopView->setSizePolicy(sizePolicy4);
        labelTopView->setMinimumSize(QSize(257, 257));
        labelTopView->setMaximumSize(QSize(257, 257));
        labelTopView->setFrameShape(QFrame::Panel);
        labelTopView->setFrameShadow(QFrame::Sunken);

        gridLayout_7->addWidget(labelTopView, 1, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_8, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_7->addItem(verticalSpacer_2, 2, 1, 1, 1);

        frameGrid = new QFrame(EditCatItemDialog);
        frameGrid->setObjectName("frameGrid");
        frameGrid->setGeometry(QRect(50, 400, 601, 211));
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(frameGrid->sizePolicy().hasHeightForWidth());
        frameGrid->setSizePolicy(sizePolicy5);
        frameGrid->setMinimumSize(QSize(0, 200));
        frameGrid->setFrameShape(QFrame::StyledPanel);
        frameGrid->setFrameShadow(QFrame::Sunken);
        pushButtonOK = new QPushButton(EditCatItemDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(370, 720, 121, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        pushButtonCancel = new QPushButton(EditCatItemDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(520, 720, 111, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon2);
        pushButtonDelete = new QPushButton(EditCatItemDialog);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(980, 660, 111, 41));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDelete->setIcon(icon3);
        frame = new QFrame(EditCatItemDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 10, 250, 326));
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy6);
        frame->setMinimumSize(QSize(250, 0));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName("gridLayout");
        frameCategory = new QFrame(frame);
        frameCategory->setObjectName("frameCategory");
        sizePolicy6.setHeightForWidth(frameCategory->sizePolicy().hasHeightForWidth());
        frameCategory->setSizePolicy(sizePolicy6);
        frameCategory->setFrameShape(QFrame::StyledPanel);
        frameCategory->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frameCategory, 0, 0, 1, 1);

        lineEditState = new QLineEdit(EditCatItemDialog);
        lineEditState->setObjectName("lineEditState");
        lineEditState->setGeometry(QRect(50, 610, 400, 20));
        sizePolicy.setHeightForWidth(lineEditState->sizePolicy().hasHeightForWidth());
        lineEditState->setSizePolicy(sizePolicy);
        lineEditState->setMinimumSize(QSize(400, 0));
        lineEditState->setMaximumSize(QSize(16777215, 16777215));
        lineEditState->setReadOnly(true);
        tableWidgetDst = new QTableWidget(EditCatItemDialog);
        if (tableWidgetDst->columnCount() < 5)
            tableWidgetDst->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetDst->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetDst->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetDst->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetDst->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetDst->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetDst->setObjectName("tableWidgetDst");
        tableWidgetDst->setGeometry(QRect(700, 20, 421, 621));
        tableWidgetDst->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetDst->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonNew = new QPushButton(EditCatItemDialog);
        pushButtonNew->setObjectName("pushButtonNew");
        pushButtonNew->setGeometry(QRect(700, 660, 101, 41));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Green.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonNew->setIcon(icon4);
        pushButtonAdd = new QPushButton(EditCatItemDialog);
        pushButtonAdd->setObjectName("pushButtonAdd");
        pushButtonAdd->setGeometry(QRect(820, 660, 101, 41));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAdd->setIcon(icon5);

        retranslateUi(EditCatItemDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(EditCatItemDialog);
    } // setupUi

    void retranslateUi(QDialog *EditCatItemDialog)
    {
        EditCatItemDialog->setWindowTitle(QCoreApplication::translate("EditCatItemDialog", "Edit CatItem", nullptr));
        label->setText(QCoreApplication::translate("EditCatItemDialog", "Cat Name", nullptr));
        lineEditCatName->setText(QString());
        label_2->setText(QCoreApplication::translate("EditCatItemDialog", "Cat ID", nullptr));
        lineEditCatID->setText(QString());
        pushButtonStartSearchByID->setText(QCoreApplication::translate("EditCatItemDialog", "\346\244\234\347\264\242", nullptr));
        label_5->setText(QCoreApplication::translate("EditCatItemDialog", "ID\346\244\234\347\264\242", nullptr));
        pushButtonStartSearchByName->setText(QCoreApplication::translate("EditCatItemDialog", "\346\244\234\347\264\242", nullptr));
        label_3->setText(QCoreApplication::translate("EditCatItemDialog", "\345\220\215\347\247\260\346\244\234\347\264\242", nullptr));
        label_8->setText(QCoreApplication::translate("EditCatItemDialog", "Machine", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditCatItemDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditCatItemDialog", "Cancel", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("EditCatItemDialog", "Delete", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetDst->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditCatItemDialog", "CatID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetDst->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditCatItemDialog", "CatName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetDst->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EditCatItemDialog", "MasterCode", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetDst->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("EditCatItemDialog", "MasterName", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetDst->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("EditCatItemDialog", "Alert", nullptr));
        pushButtonNew->setText(QCoreApplication::translate("EditCatItemDialog", "New", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("EditCatItemDialog", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditCatItemDialog: public Ui_EditCatItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITCATITEMDIALOG_H
