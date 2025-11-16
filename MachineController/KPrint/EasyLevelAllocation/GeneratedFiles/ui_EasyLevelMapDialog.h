/********************************************************************************
** Form generated from reading UI file 'EasyLevelMapDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EASYLEVELMAPDIALOG_H
#define UI_EASYLEVELMAPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EasyLevelMapDialog
{
public:
    QLabel *label_LevelNumber;
    QSlider *horizontalSliderLevel;
    QLabel *label;
    QLineEdit *lineEditLevelName;
    QLabel *label_3;
    QFrame *frame;
    QToolButton *toolButtonDotColorMatchLibPattern;
    QToolButton *toolButtonDotColorMatchLibFlat;
    QToolButton *toolButtonDotColorMatchCADLib;
    QToolButton *toolButtonDotColorMatchBladeLib;
    QToolButton *toolButtonDentLib;
    QFrame *frame_2;
    QStackedWidget *stackedWidget;
    QWidget *DotColorMatching;
    QPushButton *pushButtonSettingLibIDDotColorMatching;
    QFrame *frameLibFolderDotColorMatching;
    QTableWidget *tableWidgetLibListDotColorMatching;
    QWidget *page_2;
    QPushButton *pushButtonSettingLibIDDentInspection;
    QFrame *frameLibFolderDentInspection;
    QTableWidget *tableWidgetLibListDentInspection;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *EasyLevelMapDialog)
    {
        if (EasyLevelMapDialog->objectName().isEmpty())
            EasyLevelMapDialog->setObjectName("EasyLevelMapDialog");
        EasyLevelMapDialog->resize(745, 539);
        label_LevelNumber = new QLabel(EasyLevelMapDialog);
        label_LevelNumber->setObjectName("label_LevelNumber");
        label_LevelNumber->setGeometry(QRect(10, 60, 41, 31));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label_LevelNumber->setFont(font);
        label_LevelNumber->setAlignment(Qt::AlignCenter);
        horizontalSliderLevel = new QSlider(EasyLevelMapDialog);
        horizontalSliderLevel->setObjectName("horizontalSliderLevel");
        horizontalSliderLevel->setGeometry(QRect(60, 50, 531, 61));
        horizontalSliderLevel->setMaximum(5);
        horizontalSliderLevel->setPageStep(1);
        horizontalSliderLevel->setValue(3);
        horizontalSliderLevel->setOrientation(Qt::Horizontal);
        horizontalSliderLevel->setTickPosition(QSlider::TicksBelow);
        label = new QLabel(EasyLevelMapDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 741, 31));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        lineEditLevelName = new QLineEdit(EasyLevelMapDialog);
        lineEditLevelName->setObjectName("lineEditLevelName");
        lineEditLevelName->setGeometry(QRect(160, 140, 401, 31));
        label_3 = new QLabel(EasyLevelMapDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 140, 131, 31));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        frame = new QFrame(EasyLevelMapDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(20, 190, 231, 261));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonDotColorMatchLibPattern = new QToolButton(frame);
        toolButtonDotColorMatchLibPattern->setObjectName("toolButtonDotColorMatchLibPattern");
        toolButtonDotColorMatchLibPattern->setGeometry(QRect(0, 0, 221, 41));
        toolButtonDotColorMatchLibPattern->setCheckable(true);
        toolButtonDotColorMatchLibPattern->setChecked(true);
        toolButtonDotColorMatchLibPattern->setAutoExclusive(true);
        toolButtonDotColorMatchLibFlat = new QToolButton(frame);
        toolButtonDotColorMatchLibFlat->setObjectName("toolButtonDotColorMatchLibFlat");
        toolButtonDotColorMatchLibFlat->setGeometry(QRect(0, 50, 221, 41));
        toolButtonDotColorMatchLibFlat->setCheckable(true);
        toolButtonDotColorMatchLibFlat->setAutoExclusive(true);
        toolButtonDotColorMatchCADLib = new QToolButton(frame);
        toolButtonDotColorMatchCADLib->setObjectName("toolButtonDotColorMatchCADLib");
        toolButtonDotColorMatchCADLib->setGeometry(QRect(0, 100, 221, 41));
        toolButtonDotColorMatchCADLib->setCheckable(true);
        toolButtonDotColorMatchCADLib->setAutoExclusive(true);
        toolButtonDotColorMatchBladeLib = new QToolButton(frame);
        toolButtonDotColorMatchBladeLib->setObjectName("toolButtonDotColorMatchBladeLib");
        toolButtonDotColorMatchBladeLib->setGeometry(QRect(0, 150, 221, 41));
        toolButtonDotColorMatchBladeLib->setCheckable(true);
        toolButtonDotColorMatchBladeLib->setAutoExclusive(true);
        toolButtonDentLib = new QToolButton(frame);
        toolButtonDentLib->setObjectName("toolButtonDentLib");
        toolButtonDentLib->setGeometry(QRect(0, 200, 221, 41));
        toolButtonDentLib->setCheckable(true);
        toolButtonDentLib->setAutoExclusive(true);
        frame_2 = new QFrame(EasyLevelMapDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(270, 190, 461, 281));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        stackedWidget = new QStackedWidget(frame_2);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 10, 441, 261));
        DotColorMatching = new QWidget();
        DotColorMatching->setObjectName("DotColorMatching");
        pushButtonSettingLibIDDotColorMatching = new QPushButton(DotColorMatching);
        pushButtonSettingLibIDDotColorMatching->setObjectName("pushButtonSettingLibIDDotColorMatching");
        pushButtonSettingLibIDDotColorMatching->setGeometry(QRect(250, 220, 112, 34));
        frameLibFolderDotColorMatching = new QFrame(DotColorMatching);
        frameLibFolderDotColorMatching->setObjectName("frameLibFolderDotColorMatching");
        frameLibFolderDotColorMatching->setGeometry(QRect(0, 0, 191, 211));
        frameLibFolderDotColorMatching->setFrameShape(QFrame::StyledPanel);
        frameLibFolderDotColorMatching->setFrameShadow(QFrame::Sunken);
        tableWidgetLibListDotColorMatching = new QTableWidget(DotColorMatching);
        if (tableWidgetLibListDotColorMatching->columnCount() < 2)
            tableWidgetLibListDotColorMatching->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibListDotColorMatching->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibListDotColorMatching->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibListDotColorMatching->setObjectName("tableWidgetLibListDotColorMatching");
        tableWidgetLibListDotColorMatching->setGeometry(QRect(200, 0, 241, 211));
        tableWidgetLibListDotColorMatching->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibListDotColorMatching->setSelectionBehavior(QAbstractItemView::SelectRows);
        stackedWidget->addWidget(DotColorMatching);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        pushButtonSettingLibIDDentInspection = new QPushButton(page_2);
        pushButtonSettingLibIDDentInspection->setObjectName("pushButtonSettingLibIDDentInspection");
        pushButtonSettingLibIDDentInspection->setGeometry(QRect(250, 220, 112, 34));
        frameLibFolderDentInspection = new QFrame(page_2);
        frameLibFolderDentInspection->setObjectName("frameLibFolderDentInspection");
        frameLibFolderDentInspection->setGeometry(QRect(0, 0, 191, 211));
        frameLibFolderDentInspection->setFrameShape(QFrame::StyledPanel);
        frameLibFolderDentInspection->setFrameShadow(QFrame::Sunken);
        tableWidgetLibListDentInspection = new QTableWidget(page_2);
        if (tableWidgetLibListDentInspection->columnCount() < 2)
            tableWidgetLibListDentInspection->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLibListDentInspection->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibListDentInspection->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetLibListDentInspection->setObjectName("tableWidgetLibListDentInspection");
        tableWidgetLibListDentInspection->setGeometry(QRect(200, 0, 241, 211));
        tableWidgetLibListDentInspection->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibListDentInspection->setSelectionBehavior(QAbstractItemView::SelectRows);
        stackedWidget->addWidget(page_2);
        pushButtonOK = new QPushButton(EasyLevelMapDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(310, 480, 131, 41));

        retranslateUi(EasyLevelMapDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EasyLevelMapDialog);
    } // setupUi

    void retranslateUi(QDialog *EasyLevelMapDialog)
    {
        EasyLevelMapDialog->setWindowTitle(QCoreApplication::translate("EasyLevelMapDialog", "\347\260\241\346\230\223\343\201\227\343\201\215\343\201\204\345\200\244\350\250\255\345\256\232\343\201\256\345\211\262\343\202\212\345\275\223\343\201\246", nullptr));
        label_LevelNumber->setText(QCoreApplication::translate("EasyLevelMapDialog", "3", nullptr));
        label->setText(QCoreApplication::translate("EasyLevelMapDialog", "\347\260\241\346\230\223\350\250\255\345\256\232\343\201\256\345\237\272\346\272\226\350\250\255\345\256\232", nullptr));
        label_3->setText(QCoreApplication::translate("EasyLevelMapDialog", "\343\203\254\343\203\231\343\203\253\345\220\215\347\247\260", nullptr));
        toolButtonDotColorMatchLibPattern->setText(QCoreApplication::translate("EasyLevelMapDialog", "\345\215\260\345\210\267\351\235\242\343\200\200\346\244\234\346\237\273\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        toolButtonDotColorMatchLibFlat->setText(QCoreApplication::translate("EasyLevelMapDialog", "\347\204\241\345\234\260\351\235\242\343\200\200\346\244\234\346\237\273\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        toolButtonDotColorMatchCADLib->setText(QCoreApplication::translate("EasyLevelMapDialog", "CAD\343\201\256\346\244\234\346\237\273\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        toolButtonDotColorMatchBladeLib->setText(QCoreApplication::translate("EasyLevelMapDialog", "\345\210\203\343\201\256\346\244\234\346\237\273\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        toolButtonDentLib->setText(QCoreApplication::translate("EasyLevelMapDialog", "\345\210\203\350\241\250\351\235\242\343\201\256\346\244\234\346\237\273\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        pushButtonSettingLibIDDotColorMatching->setText(QCoreApplication::translate("EasyLevelMapDialog", "\350\250\255\345\256\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibListDotColorMatching->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EasyLevelMapDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibListDotColorMatching->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EasyLevelMapDialog", "Name", nullptr));
        pushButtonSettingLibIDDentInspection->setText(QCoreApplication::translate("EasyLevelMapDialog", "\350\250\255\345\256\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibListDentInspection->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EasyLevelMapDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibListDentInspection->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("EasyLevelMapDialog", "Name", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EasyLevelMapDialog", "OK Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EasyLevelMapDialog: public Ui_EasyLevelMapDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EASYLEVELMAPDIALOG_H
