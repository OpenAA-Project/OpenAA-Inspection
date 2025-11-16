/********************************************************************************
** Form generated from reading UI file 'PropertyPieceDefForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYPIECEDEFFORM_H
#define UI_PROPERTYPIECEDEFFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyPieceDefForm
{
public:
    QFrame *frame;
    QLabel *label;
    QLabel *label_4;
    QTableWidget *tableWidgetResult;
    QPushButton *pushButtonCopyByFoundItems;
    QLabel *label_3;
    QLabel *label_2;
    QPushButton *pushButtonStartSearch;
    QFrame *frame_2;
    QPushButton *pushButtonMatchClosed;

    void setupUi(GUIFormBase *PropertyPieceDefForm)
    {
        if (PropertyPieceDefForm->objectName().isEmpty())
            PropertyPieceDefForm->setObjectName("PropertyPieceDefForm");
        PropertyPieceDefForm->resize(400, 700);
        frame = new QFrame(PropertyPieceDefForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 381, 421));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 191, 16));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 330, 161, 16));
        tableWidgetResult = new QTableWidget(frame);
        if (tableWidgetResult->columnCount() < 3)
            tableWidgetResult->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetResult->setObjectName("tableWidgetResult");
        tableWidgetResult->setGeometry(QRect(30, 110, 331, 211));
        tableWidgetResult->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetResult->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonCopyByFoundItems = new QPushButton(frame);
        pushButtonCopyByFoundItems->setObjectName("pushButtonCopyByFoundItems");
        pushButtonCopyByFoundItems->setGeometry(QRect(60, 360, 261, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Copy.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCopyByFoundItems->setIcon(icon);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 90, 151, 16));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 30, 151, 16));
        pushButtonStartSearch = new QPushButton(frame);
        pushButtonStartSearch->setObjectName("pushButtonStartSearch");
        pushButtonStartSearch->setGeometry(QRect(120, 50, 151, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonStartSearch->setIcon(icon1);
        frame_2 = new QFrame(PropertyPieceDefForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 440, 381, 211));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        pushButtonMatchClosed = new QPushButton(frame_2);
        pushButtonMatchClosed->setObjectName("pushButtonMatchClosed");
        pushButtonMatchClosed->setGeometry(QRect(60, 20, 261, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonMatchClosed->setIcon(icon2);

        retranslateUi(PropertyPieceDefForm);

        QMetaObject::connectSlotsByName(PropertyPieceDefForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyPieceDefForm)
    {
        PropertyPieceDefForm->setWindowTitle(QCoreApplication::translate("PropertyPieceDefForm", "Property PieceDef", nullptr));
        label->setText(QCoreApplication::translate("PropertyPieceDefForm", "\357\274\221\357\274\232\346\216\242\347\264\242\345\205\203\343\201\256\343\202\242\343\202\244\343\203\206\343\203\240\343\202\222\351\201\270\346\212\236", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyPieceDefForm", "\357\274\224\357\274\232\347\265\220\346\236\234\345\207\246\347\220\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetResult->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyPieceDefForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetResult->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyPieceDefForm", "Location", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetResult->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyPieceDefForm", "Matching", nullptr));
        pushButtonCopyByFoundItems->setText(QCoreApplication::translate("PropertyPieceDefForm", "\343\202\242\343\202\244\343\203\206\343\203\240\343\202\222\343\202\263\343\203\224\343\203\274", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyPieceDefForm", "\357\274\223\357\274\232\346\216\242\347\264\242\347\265\220\346\236\234", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyPieceDefForm", "\357\274\222\357\274\232\346\216\242\347\264\242\351\226\213\345\247\213", nullptr));
        pushButtonStartSearch->setText(QCoreApplication::translate("PropertyPieceDefForm", "\346\216\242\347\264\242\351\226\213\345\247\213", nullptr));
        pushButtonMatchClosed->setText(QCoreApplication::translate("PropertyPieceDefForm", "\351\201\270\346\212\236\351\240\230\345\237\237\343\202\222\350\277\221\345\202\215\343\201\247\343\203\236\343\203\203\343\203\201\343\203\263\343\202\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyPieceDefForm: public Ui_PropertyPieceDefForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYPIECEDEFFORM_H
