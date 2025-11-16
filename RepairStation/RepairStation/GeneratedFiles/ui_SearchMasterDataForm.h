/********************************************************************************
** Form generated from reading UI file 'SearchMasterDataForm.ui'
**
** Created: Mon Aug 20 16:22:46 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHMASTERDATAFORM_H
#define UI_SEARCHMASTERDATAFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>
#include <QtGui/QTreeWidget>
#include "passwordpushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_SearchMasterDataFormClass
{
public:
    QFrame *frame;
    QTreeWidget *trMasterList;
    QLineEdit *leMasterID;
    PasswordPushButton *pbCancel;
    PasswordPushButton *pbReadMasterData;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *leMasterRemark;
    QLineEdit *leMasterName;
    QLabel *label_3;
    QLabel *lbMasterImage;
    QFrame *frame_3;
    QLabel *label_4;
    QSpinBox *sbSearchByMasterID;
    PasswordPushButton *pbSearchByMasterID;
    QFrame *frame_4;
    PasswordPushButton *pbSearchByMasterName;
    QLabel *label_5;
    QLineEdit *leSearchByMasterName;
    QTableWidget *twMasterList;

    void setupUi(QDialog *SearchMasterDataFormClass)
    {
        if (SearchMasterDataFormClass->objectName().isEmpty())
            SearchMasterDataFormClass->setObjectName(QString::fromUtf8("SearchMasterDataFormClass"));
        SearchMasterDataFormClass->resize(879, 619);
        frame = new QFrame(SearchMasterDataFormClass);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 861, 301));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        trMasterList = new QTreeWidget(frame);
        trMasterList->setObjectName(QString::fromUtf8("trMasterList"));
        trMasterList->setGeometry(QRect(10, 10, 351, 281));
        leMasterID = new QLineEdit(frame);
        leMasterID->setObjectName(QString::fromUtf8("leMasterID"));
        leMasterID->setGeometry(QRect(370, 44, 71, 25));
        leMasterID->setReadOnly(true);
        pbCancel = new PasswordPushButton(frame);
        pbCancel->setObjectName(QString::fromUtf8("pbCancel"));
        pbCancel->setGeometry(QRect(490, 230, 91, 51));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbCancel->setIcon(icon);
        pbReadMasterData = new PasswordPushButton(frame);
        pbReadMasterData->setObjectName(QString::fromUtf8("pbReadMasterData"));
        pbReadMasterData->setGeometry(QRect(370, 230, 91, 51));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(370, 20, 71, 25));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(370, 80, 211, 25));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        leMasterRemark = new QLineEdit(frame);
        leMasterRemark->setObjectName(QString::fromUtf8("leMasterRemark"));
        leMasterRemark->setGeometry(QRect(370, 164, 211, 25));
        leMasterRemark->setReadOnly(true);
        leMasterName = new QLineEdit(frame);
        leMasterName->setObjectName(QString::fromUtf8("leMasterName"));
        leMasterName->setGeometry(QRect(370, 104, 211, 25));
        leMasterName->setReadOnly(true);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(370, 140, 211, 25));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        lbMasterImage = new QLabel(frame);
        lbMasterImage->setObjectName(QString::fromUtf8("lbMasterImage"));
        lbMasterImage->setGeometry(QRect(590, 10, 261, 281));
        lbMasterImage->setFrameShape(QFrame::Panel);
        lbMasterImage->setFrameShadow(QFrame::Sunken);
        frame_3 = new QFrame(SearchMasterDataFormClass);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(10, 320, 261, 51));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 18, 61, 16));
        QFont font;
        font.setPointSize(10);
        label_4->setFont(font);
        sbSearchByMasterID = new QSpinBox(frame_3);
        sbSearchByMasterID->setObjectName(QString::fromUtf8("sbSearchByMasterID"));
        sbSearchByMasterID->setGeometry(QRect(80, 15, 71, 22));
        sbSearchByMasterID->setMaximum(9999);
        pbSearchByMasterID = new PasswordPushButton(frame_3);
        pbSearchByMasterID->setObjectName(QString::fromUtf8("pbSearchByMasterID"));
        pbSearchByMasterID->setGeometry(QRect(170, 12, 77, 31));
        frame_4 = new QFrame(SearchMasterDataFormClass);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(290, 320, 581, 51));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Sunken);
        pbSearchByMasterName = new PasswordPushButton(frame_4);
        pbSearchByMasterName->setObjectName(QString::fromUtf8("pbSearchByMasterName"));
        pbSearchByMasterName->setGeometry(QRect(490, 10, 77, 31));
        label_5 = new QLabel(frame_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 20, 135, 16));
        label_5->setFont(font);
        leSearchByMasterName = new QLineEdit(frame_4);
        leSearchByMasterName->setObjectName(QString::fromUtf8("leSearchByMasterName"));
        leSearchByMasterName->setGeometry(QRect(160, 14, 311, 25));
        twMasterList = new QTableWidget(SearchMasterDataFormClass);
        twMasterList->setObjectName(QString::fromUtf8("twMasterList"));
        twMasterList->setGeometry(QRect(10, 380, 861, 231));

        retranslateUi(SearchMasterDataFormClass);

        QMetaObject::connectSlotsByName(SearchMasterDataFormClass);
    } // setupUi

    void retranslateUi(QDialog *SearchMasterDataFormClass)
    {
        SearchMasterDataFormClass->setWindowTitle(QApplication::translate("SearchMasterDataFormClass", "\343\203\236\343\202\271\343\202\277\343\203\274\346\244\234\347\264\242\347\224\273\351\235\242", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = trMasterList->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("SearchMasterDataFormClass", "1", 0, QApplication::UnicodeUTF8));
        pbCancel->setText(QApplication::translate("SearchMasterDataFormClass", "Cancel", 0, QApplication::UnicodeUTF8));
        pbReadMasterData->setText(QApplication::translate("SearchMasterDataFormClass", "Read", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SearchMasterDataFormClass", "Master ID", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SearchMasterDataFormClass", "Master Name", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SearchMasterDataFormClass", "Remark", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SearchMasterDataFormClass", "Master ID", 0, QApplication::UnicodeUTF8));
        pbSearchByMasterID->setText(QApplication::translate("SearchMasterDataFormClass", "Search", 0, QApplication::UnicodeUTF8));
        pbSearchByMasterName->setText(QApplication::translate("SearchMasterDataFormClass", "Search", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SearchMasterDataFormClass", "Master Name", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SearchMasterDataFormClass: public Ui_SearchMasterDataFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHMASTERDATAFORM_H
