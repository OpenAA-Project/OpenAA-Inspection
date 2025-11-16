/********************************************************************************
** Form generated from reading UI file 'CopyLibraryForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYLIBRARYFORM_H
#define UI_COPYLIBRARYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_CopyLibraryFormClass
{
public:
    QFrame *frame;
    QLabel *label;
    QFrame *frameFolderSrc;
    QTableWidget *tableWidgetLibListSrc;
    QFrame *frame_2;
    QLabel *label_2;
    QFrame *frameFolderDst;
    QTableWidget *tableWidgetLibListDst;
    QPushButton *pushButtonCopy;
    QPushButton *pushButtonClose;
    QLabel *label_3;
    QPushButton *pushButtonAll;

    void setupUi(QDialog *CopyLibraryFormClass)
    {
        if (CopyLibraryFormClass->objectName().isEmpty())
            CopyLibraryFormClass->setObjectName("CopyLibraryFormClass");
        CopyLibraryFormClass->resize(621, 488);
        frame = new QFrame(CopyLibraryFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 261, 431));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 261, 16));
        QPalette palette;
        QBrush brush(QColor(0, 0, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        label->setPalette(palette);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameFolderSrc = new QFrame(frame);
        frameFolderSrc->setObjectName("frameFolderSrc");
        frameFolderSrc->setGeometry(QRect(10, 20, 241, 181));
        frameFolderSrc->setFrameShape(QFrame::NoFrame);
        frameFolderSrc->setFrameShadow(QFrame::Raised);
        tableWidgetLibListSrc = new QTableWidget(frame);
        if (tableWidgetLibListSrc->columnCount() < 2)
            tableWidgetLibListSrc->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibListSrc->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibListSrc->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibListSrc->setObjectName("tableWidgetLibListSrc");
        tableWidgetLibListSrc->setGeometry(QRect(10, 210, 241, 201));
        tableWidgetLibListSrc->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibListSrc->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame_2 = new QFrame(CopyLibraryFormClass);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(350, 10, 261, 431));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 261, 16));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::NoRole, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::NoRole, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::NoRole, brush);
        label_2->setPalette(palette1);
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameFolderDst = new QFrame(frame_2);
        frameFolderDst->setObjectName("frameFolderDst");
        frameFolderDst->setGeometry(QRect(10, 20, 241, 181));
        frameFolderDst->setFrameShape(QFrame::NoFrame);
        frameFolderDst->setFrameShadow(QFrame::Raised);
        tableWidgetLibListDst = new QTableWidget(frame_2);
        if (tableWidgetLibListDst->columnCount() < 2)
            tableWidgetLibListDst->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLibListDst->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibListDst->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetLibListDst->setObjectName("tableWidgetLibListDst");
        tableWidgetLibListDst->setGeometry(QRect(10, 210, 241, 201));
        tableWidgetLibListDst->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibListDst->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonCopy = new QPushButton(CopyLibraryFormClass);
        pushButtonCopy->setObjectName("pushButtonCopy");
        pushButtonCopy->setGeometry(QRect(270, 210, 81, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/CopyOne.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCopy->setIcon(icon);
        pushButtonClose = new QPushButton(CopyLibraryFormClass);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(510, 450, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon1);
        label_3 = new QLabel(CopyLibraryFormClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(280, 190, 45, 12));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonAll = new QPushButton(CopyLibraryFormClass);
        pushButtonAll->setObjectName("pushButtonAll");
        pushButtonAll->setGeometry(QRect(270, 290, 81, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Copy.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAll->setIcon(icon2);

        retranslateUi(CopyLibraryFormClass);

        QMetaObject::connectSlotsByName(CopyLibraryFormClass);
    } // setupUi

    void retranslateUi(QDialog *CopyLibraryFormClass)
    {
        CopyLibraryFormClass->setWindowTitle(QCoreApplication::translate("CopyLibraryFormClass", "CopyLibraryForm", nullptr));
        label->setText(QCoreApplication::translate("CopyLibraryFormClass", "\343\202\263\343\203\224\343\203\274\345\205\203", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibListSrc->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CopyLibraryFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibListSrc->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CopyLibraryFormClass", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("CopyLibraryFormClass", "\343\202\263\343\203\224\343\203\274\345\205\210", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibListDst->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CopyLibraryFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibListDst->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("CopyLibraryFormClass", "Name", nullptr));
        pushButtonCopy->setText(QCoreApplication::translate("CopyLibraryFormClass", "Copy 1", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("CopyLibraryFormClass", "Close", nullptr));
        label_3->setText(QCoreApplication::translate("CopyLibraryFormClass", "=>", nullptr));
        pushButtonAll->setText(QCoreApplication::translate("CopyLibraryFormClass", "Copy all", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CopyLibraryFormClass: public Ui_CopyLibraryFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYLIBRARYFORM_H
