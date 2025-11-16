/********************************************************************************
** Form generated from reading UI file 'PiecePropertyForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIECEPROPERTYFORM_H
#define UI_PIECEPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PiecePropertyFormClass
{
public:
    QFrame *frame_2;
    QToolButton *toolButtonArrange;
    QToolButton *toolButtonCutPiece;
    QFrame *frameAlgorithmBase;
    QToolButton *toolButtonArrange_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFrame *frame;
    QFrame *frameCategory;
    QFrame *frameGrid;
    QTableView *tableViewMList;
    QLabel *labelTopview;
    QPushButton *pushButtonExecuteAlignment;
    QPushButton *pushButtonUpdate;
    QTableWidget *tablePieceArrange;
    QFrame *frame_3;
    QSpinBox *spinBoxAutoCountX;
    QSpinBox *spinBoxAutoCountY;
    QToolButton *toolButtonStartMatrixArrange;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_7;
    QLabel *label_8;
    QWidget *tab_2;
    QFrame *frameGridAuto;
    QFrame *frameCategoryAuto;
    QLabel *labelTopviewAuto;
    QTableWidget *tableWidgetAutoCurrent;
    QPushButton *pushButtonAutoPopLoad;
    QPushButton *pushButtonPushBask;
    QLabel *label;
    QPushButton *pushButtonAutoExecute;
    QTableWidget *tableWidgetAutoResult;
    QLabel *label_2;
    QWidget *tab_3;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButtonStartAutoSearch;
    QTableWidget *tableWidgetAutoSearch;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButtonCopyByAutoSearch;

    void setupUi(GUIFormBase *PiecePropertyFormClass)
    {
        if (PiecePropertyFormClass->objectName().isEmpty())
            PiecePropertyFormClass->setObjectName("PiecePropertyFormClass");
        PiecePropertyFormClass->resize(400, 833);
        frame_2 = new QFrame(PiecePropertyFormClass);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 0, 381, 41));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        toolButtonArrange = new QToolButton(frame_2);
        toolButtonArrange->setObjectName("toolButtonArrange");
        toolButtonArrange->setGeometry(QRect(10, 10, 101, 21));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Arrange.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonArrange->setIcon(icon);
        toolButtonArrange->setCheckable(true);
        toolButtonArrange->setChecked(true);
        toolButtonArrange->setAutoExclusive(true);
        toolButtonArrange->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButtonCutPiece = new QToolButton(frame_2);
        toolButtonCutPiece->setObjectName("toolButtonCutPiece");
        toolButtonCutPiece->setGeometry(QRect(120, 10, 111, 21));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cut.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonCutPiece->setIcon(icon1);
        toolButtonCutPiece->setCheckable(true);
        toolButtonCutPiece->setAutoExclusive(true);
        toolButtonCutPiece->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        frameAlgorithmBase = new QFrame(PiecePropertyFormClass);
        frameAlgorithmBase->setObjectName("frameAlgorithmBase");
        frameAlgorithmBase->setGeometry(QRect(10, 46, 381, 51));
        frameAlgorithmBase->setFrameShape(QFrame::StyledPanel);
        frameAlgorithmBase->setFrameShadow(QFrame::Sunken);
        toolButtonArrange_2 = new QToolButton(frameAlgorithmBase);
        toolButtonArrange_2->setObjectName("toolButtonArrange_2");
        toolButtonArrange_2->setGeometry(QRect(10, 10, 101, 21));
        toolButtonArrange_2->setIcon(icon);
        toolButtonArrange_2->setCheckable(true);
        toolButtonArrange_2->setChecked(true);
        toolButtonArrange_2->setAutoExclusive(true);
        toolButtonArrange_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        tabWidget = new QTabWidget(PiecePropertyFormClass);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 100, 401, 731));
        tab = new QWidget();
        tab->setObjectName("tab");
        frame = new QFrame(tab);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 398, 341));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        frameCategory = new QFrame(frame);
        frameCategory->setObjectName("frameCategory");
        frameCategory->setGeometry(QRect(10, 5, 381, 141));
        frameCategory->setFrameShape(QFrame::StyledPanel);
        frameCategory->setFrameShadow(QFrame::Raised);
        frameGrid = new QFrame(frame);
        frameGrid->setObjectName("frameGrid");
        frameGrid->setGeometry(QRect(10, 150, 191, 181));
        frameGrid->setFrameShape(QFrame::StyledPanel);
        frameGrid->setFrameShadow(QFrame::Sunken);
        tableViewMList = new QTableView(frameGrid);
        tableViewMList->setObjectName("tableViewMList");
        tableViewMList->setGeometry(QRect(0, 0, 191, 181));
        tableViewMList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableViewMList->setSelectionBehavior(QAbstractItemView::SelectRows);
        labelTopview = new QLabel(frame);
        labelTopview->setObjectName("labelTopview");
        labelTopview->setGeometry(QRect(200, 150, 191, 181));
        labelTopview->setFrameShape(QFrame::Panel);
        labelTopview->setFrameShadow(QFrame::Sunken);
        pushButtonExecuteAlignment = new QPushButton(tab);
        pushButtonExecuteAlignment->setObjectName("pushButtonExecuteAlignment");
        pushButtonExecuteAlignment->setGeometry(QRect(10, 480, 291, 23));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonExecuteAlignment->setIcon(icon2);
        pushButtonUpdate = new QPushButton(tab);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(310, 480, 75, 23));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon3);
        tablePieceArrange = new QTableWidget(tab);
        if (tablePieceArrange->columnCount() < 6)
            tablePieceArrange->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tablePieceArrange->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tablePieceArrange->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tablePieceArrange->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tablePieceArrange->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tablePieceArrange->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tablePieceArrange->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tablePieceArrange->rowCount() < 1)
            tablePieceArrange->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tablePieceArrange->setVerticalHeaderItem(0, __qtablewidgetitem6);
        tablePieceArrange->setObjectName("tablePieceArrange");
        tablePieceArrange->setGeometry(QRect(0, 510, 391, 191));
        tablePieceArrange->setSelectionMode(QAbstractItemView::SingleSelection);
        tablePieceArrange->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame_3 = new QFrame(tab);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(0, 350, 391, 121));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        spinBoxAutoCountX = new QSpinBox(frame_3);
        spinBoxAutoCountX->setObjectName("spinBoxAutoCountX");
        spinBoxAutoCountX->setGeometry(QRect(190, 60, 71, 22));
        spinBoxAutoCountX->setMaximum(9999);
        spinBoxAutoCountY = new QSpinBox(frame_3);
        spinBoxAutoCountY->setObjectName("spinBoxAutoCountY");
        spinBoxAutoCountY->setGeometry(QRect(190, 90, 71, 22));
        spinBoxAutoCountY->setMaximum(9999);
        toolButtonStartMatrixArrange = new QToolButton(frame_3);
        toolButtonStartMatrixArrange->setObjectName("toolButtonStartMatrixArrange");
        toolButtonStartMatrixArrange->setGeometry(QRect(270, 60, 111, 51));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Start.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonStartMatrixArrange->setIcon(icon4);
        toolButtonStartMatrixArrange->setCheckable(true);
        toolButtonStartMatrixArrange->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        label_9 = new QLabel(frame_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 60, 171, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(frame_3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 90, 171, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(frame_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 0, 381, 16));
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(frame_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(30, 30, 291, 20));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        frameGridAuto = new QFrame(tab_2);
        frameGridAuto->setObjectName("frameGridAuto");
        frameGridAuto->setGeometry(QRect(10, 150, 191, 181));
        frameGridAuto->setFrameShape(QFrame::StyledPanel);
        frameGridAuto->setFrameShadow(QFrame::Sunken);
        frameCategoryAuto = new QFrame(tab_2);
        frameCategoryAuto->setObjectName("frameCategoryAuto");
        frameCategoryAuto->setGeometry(QRect(10, 10, 381, 131));
        frameCategoryAuto->setFrameShape(QFrame::StyledPanel);
        frameCategoryAuto->setFrameShadow(QFrame::Raised);
        labelTopviewAuto = new QLabel(tab_2);
        labelTopviewAuto->setObjectName("labelTopviewAuto");
        labelTopviewAuto->setGeometry(QRect(200, 150, 191, 181));
        labelTopviewAuto->setFrameShape(QFrame::Panel);
        labelTopviewAuto->setFrameShadow(QFrame::Sunken);
        tableWidgetAutoCurrent = new QTableWidget(tab_2);
        if (tableWidgetAutoCurrent->columnCount() < 2)
            tableWidgetAutoCurrent->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetAutoCurrent->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetAutoCurrent->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        tableWidgetAutoCurrent->setObjectName("tableWidgetAutoCurrent");
        tableWidgetAutoCurrent->setGeometry(QRect(10, 400, 191, 111));
        tableWidgetAutoCurrent->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAutoCurrent->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonAutoPopLoad = new QPushButton(tab_2);
        pushButtonAutoPopLoad->setObjectName("pushButtonAutoPopLoad");
        pushButtonAutoPopLoad->setGeometry(QRect(20, 340, 75, 31));
        pushButtonPushBask = new QPushButton(tab_2);
        pushButtonPushBask->setObjectName("pushButtonPushBask");
        pushButtonPushBask->setGeometry(QRect(110, 340, 75, 31));
        label = new QLabel(tab_2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 380, 191, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonAutoExecute = new QPushButton(tab_2);
        pushButtonAutoExecute->setObjectName("pushButtonAutoExecute");
        pushButtonAutoExecute->setGeometry(QRect(10, 520, 191, 51));
        pushButtonAutoExecute->setIcon(icon4);
        tableWidgetAutoResult = new QTableWidget(tab_2);
        if (tableWidgetAutoResult->columnCount() < 4)
            tableWidgetAutoResult->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetAutoResult->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetAutoResult->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetAutoResult->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidgetAutoResult->setHorizontalHeaderItem(3, __qtablewidgetitem12);
        tableWidgetAutoResult->setObjectName("tableWidgetAutoResult");
        tableWidgetAutoResult->setGeometry(QRect(210, 401, 181, 171));
        tableWidgetAutoResult->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAutoResult->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_2 = new QLabel(tab_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(210, 380, 181, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        label_3 = new QLabel(tab_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 20, 171, 16));
        label_4 = new QLabel(tab_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 50, 101, 16));
        pushButtonStartAutoSearch = new QPushButton(tab_3);
        pushButtonStartAutoSearch->setObjectName("pushButtonStartAutoSearch");
        pushButtonStartAutoSearch->setGeometry(QRect(80, 70, 181, 31));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonStartAutoSearch->setIcon(icon5);
        tableWidgetAutoSearch = new QTableWidget(tab_3);
        if (tableWidgetAutoSearch->columnCount() < 3)
            tableWidgetAutoSearch->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidgetAutoSearch->setHorizontalHeaderItem(0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidgetAutoSearch->setHorizontalHeaderItem(1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidgetAutoSearch->setHorizontalHeaderItem(2, __qtablewidgetitem15);
        tableWidgetAutoSearch->setObjectName("tableWidgetAutoSearch");
        tableWidgetAutoSearch->setGeometry(QRect(30, 140, 341, 231));
        tableWidgetAutoSearch->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAutoSearch->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_5 = new QLabel(tab_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(30, 110, 111, 16));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(30, 390, 50, 12));
        pushButtonCopyByAutoSearch = new QPushButton(tab_3);
        pushButtonCopyByAutoSearch->setObjectName("pushButtonCopyByAutoSearch");
        pushButtonCopyByAutoSearch->setGeometry(QRect(70, 410, 191, 31));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Qtres/Copy.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCopyByAutoSearch->setIcon(icon6);
        tabWidget->addTab(tab_3, QString());

        retranslateUi(PiecePropertyFormClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PiecePropertyFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PiecePropertyFormClass)
    {
        PiecePropertyFormClass->setWindowTitle(QCoreApplication::translate("PiecePropertyFormClass", "Piece Property", nullptr));
        toolButtonArrange->setText(QCoreApplication::translate("PiecePropertyFormClass", "Piece Arrange", nullptr));
        toolButtonCutPiece->setText(QCoreApplication::translate("PiecePropertyFormClass", "Cut Piece & Edit", nullptr));
        toolButtonArrange_2->setText(QCoreApplication::translate("PiecePropertyFormClass", "Piece Arrange", nullptr));
        pushButtonExecuteAlignment->setText(QCoreApplication::translate("PiecePropertyFormClass", "Execute alignment in selected items", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("PiecePropertyFormClass", "Update", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tablePieceArrange->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PiecePropertyFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tablePieceArrange->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PiecePropertyFormClass", "PieceID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tablePieceArrange->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PiecePropertyFormClass", "PieceLib", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tablePieceArrange->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PiecePropertyFormClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tablePieceArrange->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PiecePropertyFormClass", "Angle", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tablePieceArrange->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PiecePropertyFormClass", "Pos", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tablePieceArrange->verticalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PiecePropertyFormClass", "1", nullptr));
        toolButtonStartMatrixArrange->setText(QCoreApplication::translate("PiecePropertyFormClass", "Start arrange", nullptr));
        label_9->setText(QCoreApplication::translate("PiecePropertyFormClass", "Horizontal (X) count", nullptr));
        label_10->setText(QCoreApplication::translate("PiecePropertyFormClass", "Vertial (Y) count", nullptr));
        label_7->setText(QCoreApplication::translate("PiecePropertyFormClass", "Matrix arrangement", nullptr));
        label_8->setText(QCoreApplication::translate("PiecePropertyFormClass", "Select piece master before start", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("PiecePropertyFormClass", "Manual arrange", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetAutoCurrent->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PiecePropertyFormClass", "Code", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetAutoCurrent->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("PiecePropertyFormClass", "MasterName", nullptr));
        pushButtonAutoPopLoad->setText(QCoreApplication::translate("PiecePropertyFormClass", "\342\206\223", nullptr));
        pushButtonPushBask->setText(QCoreApplication::translate("PiecePropertyFormClass", "\342\206\221", nullptr));
        label->setText(QCoreApplication::translate("PiecePropertyFormClass", "\344\273\212\345\233\236\346\216\242\347\264\242\351\205\215\347\275\256\351\203\250\345\223\201", nullptr));
        pushButtonAutoExecute->setText(QCoreApplication::translate("PiecePropertyFormClass", "\351\205\215\347\275\256\345\256\237\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetAutoResult->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("PiecePropertyFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetAutoResult->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("PiecePropertyFormClass", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetAutoResult->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("PiecePropertyFormClass", "Code", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetAutoResult->horizontalHeaderItem(3);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("PiecePropertyFormClass", "Count", nullptr));
        label_2->setText(QCoreApplication::translate("PiecePropertyFormClass", "Arranemental result", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("PiecePropertyFormClass", "Lib->Automatic arrange", nullptr));
        label_3->setText(QCoreApplication::translate("PiecePropertyFormClass", "\357\274\221:\346\216\242\347\264\242\345\205\203\351\240\230\345\237\237\343\202\222\346\214\207\345\256\232", nullptr));
        label_4->setText(QCoreApplication::translate("PiecePropertyFormClass", "\357\274\222\357\274\232\346\216\242\347\264\242\351\226\213\345\247\213", nullptr));
        pushButtonStartAutoSearch->setText(QCoreApplication::translate("PiecePropertyFormClass", "Start search", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidgetAutoSearch->horizontalHeaderItem(0);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("PiecePropertyFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidgetAutoSearch->horizontalHeaderItem(1);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("PiecePropertyFormClass", "Location", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidgetAutoSearch->horizontalHeaderItem(2);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("PiecePropertyFormClass", "Matching", nullptr));
        label_5->setText(QCoreApplication::translate("PiecePropertyFormClass", "\357\274\223\357\274\232\346\216\242\347\264\242\347\265\220\346\236\234", nullptr));
        label_6->setText(QCoreApplication::translate("PiecePropertyFormClass", "\357\274\224\357\274\232\345\207\246\347\220\206", nullptr));
        pushButtonCopyByAutoSearch->setText(QCoreApplication::translate("PiecePropertyFormClass", "Copy item", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("PiecePropertyFormClass", "Automatic search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PiecePropertyFormClass: public Ui_PiecePropertyFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIECEPROPERTYFORM_H
