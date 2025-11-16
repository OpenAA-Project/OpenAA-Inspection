/********************************************************************************
** Form generated from reading UI file 'PixelLibraryManager.ui'
**
** Created: Tue May 1 16:22:27 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIXELLIBRARYMANAGER_H
#define UI_PIXELLIBRARYMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_PixelLibraryManagerClass
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableWidget *twPixelLibraryList;
    QFrame *frame;
    QPushButton *pbSave;
    QPushButton *pbUpdate;
    QPushButton *pbLoad;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbAddRow;
    QPushButton *pbDeleteRow;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pbClose;

    void setupUi(QWidget *PixelLibraryManagerClass)
    {
        if (PixelLibraryManagerClass->objectName().isEmpty())
            PixelLibraryManagerClass->setObjectName(QString::fromUtf8("PixelLibraryManagerClass"));
        PixelLibraryManagerClass->resize(789, 419);
        gridLayout = new QGridLayout(PixelLibraryManagerClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(PixelLibraryManagerClass);
        label->setObjectName(QString::fromUtf8("label"));
        QPalette palette;
        QBrush brush(QColor(193, 193, 193, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("MS UI Gothic"));
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        label->setFont(font);
        label->setAutoFillBackground(true);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(label);

        twPixelLibraryList = new QTableWidget(PixelLibraryManagerClass);
        if (twPixelLibraryList->columnCount() < 5)
            twPixelLibraryList->setColumnCount(5);
        if (twPixelLibraryList->rowCount() < 3)
            twPixelLibraryList->setRowCount(3);
        twPixelLibraryList->setObjectName(QString::fromUtf8("twPixelLibraryList"));
        twPixelLibraryList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twPixelLibraryList->setSelectionMode(QAbstractItemView::SingleSelection);
        twPixelLibraryList->setSelectionBehavior(QAbstractItemView::SelectRows);
        twPixelLibraryList->setTextElideMode(Qt::ElideNone);
        twPixelLibraryList->setRowCount(3);
        twPixelLibraryList->setColumnCount(5);

        verticalLayout->addWidget(twPixelLibraryList);

        frame = new QFrame(PixelLibraryManagerClass);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 8);

        pbSave = new QPushButton(PixelLibraryManagerClass);
        pbSave->setObjectName(QString::fromUtf8("pbSave"));
        pbSave->setMinimumSize(QSize(111, 51));
        pbSave->setMaximumSize(QSize(111, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS UI Gothic"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        pbSave->setFont(font1);

        gridLayout->addWidget(pbSave, 1, 0, 1, 1);

        pbUpdate = new QPushButton(PixelLibraryManagerClass);
        pbUpdate->setObjectName(QString::fromUtf8("pbUpdate"));
        pbUpdate->setMinimumSize(QSize(111, 51));
        pbUpdate->setMaximumSize(QSize(111, 51));
        pbUpdate->setFont(font1);

        gridLayout->addWidget(pbUpdate, 1, 1, 1, 1);

        pbLoad = new QPushButton(PixelLibraryManagerClass);
        pbLoad->setObjectName(QString::fromUtf8("pbLoad"));
        pbLoad->setMinimumSize(QSize(111, 51));
        pbLoad->setMaximumSize(QSize(111, 51));
        pbLoad->setFont(font1);

        gridLayout->addWidget(pbLoad, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(29, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 3, 1, 1);

        pbAddRow = new QPushButton(PixelLibraryManagerClass);
        pbAddRow->setObjectName(QString::fromUtf8("pbAddRow"));
        pbAddRow->setMinimumSize(QSize(111, 51));
        pbAddRow->setMaximumSize(QSize(111, 51));
        pbAddRow->setFont(font1);

        gridLayout->addWidget(pbAddRow, 1, 4, 1, 1);

        pbDeleteRow = new QPushButton(PixelLibraryManagerClass);
        pbDeleteRow->setObjectName(QString::fromUtf8("pbDeleteRow"));
        pbDeleteRow->setMinimumSize(QSize(111, 51));
        pbDeleteRow->setMaximumSize(QSize(111, 51));
        pbDeleteRow->setFont(font1);

        gridLayout->addWidget(pbDeleteRow, 1, 5, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 6, 1, 1);

        pbClose = new QPushButton(PixelLibraryManagerClass);
        pbClose->setObjectName(QString::fromUtf8("pbClose"));
        pbClose->setMinimumSize(QSize(111, 51));
        pbClose->setMaximumSize(QSize(111, 51));
        pbClose->setFont(font1);

        gridLayout->addWidget(pbClose, 1, 7, 1, 1);


        retranslateUi(PixelLibraryManagerClass);

        QMetaObject::connectSlotsByName(PixelLibraryManagerClass);
    } // setupUi

    void retranslateUi(QWidget *PixelLibraryManagerClass)
    {
        PixelLibraryManagerClass->setWindowTitle(QApplication::translate("PixelLibraryManagerClass", "PixelLibraryManager", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PixelLibraryManagerClass", "\343\203\224\343\202\257\343\202\273\343\203\253\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\274\343\201\256\350\250\255\345\256\232", 0, QApplication::UnicodeUTF8));
        pbSave->setText(QApplication::translate("PixelLibraryManagerClass", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        pbUpdate->setText(QApplication::translate("PixelLibraryManagerClass", "\346\233\264\346\226\260", 0, QApplication::UnicodeUTF8));
        pbLoad->setText(QApplication::translate("PixelLibraryManagerClass", "\350\252\255\350\276\274", 0, QApplication::UnicodeUTF8));
        pbAddRow->setText(QApplication::translate("PixelLibraryManagerClass", "\350\241\214\350\277\275\345\212\240\357\274\210\357\274\213\357\274\211", 0, QApplication::UnicodeUTF8));
        pbDeleteRow->setText(QApplication::translate("PixelLibraryManagerClass", "\350\241\214\345\211\212\351\231\244\357\274\210\357\274\215\357\274\211", 0, QApplication::UnicodeUTF8));
        pbClose->setText(QApplication::translate("PixelLibraryManagerClass", "\351\226\211\343\201\230\343\202\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PixelLibraryManagerClass: public Ui_PixelLibraryManagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIXELLIBRARYMANAGER_H
