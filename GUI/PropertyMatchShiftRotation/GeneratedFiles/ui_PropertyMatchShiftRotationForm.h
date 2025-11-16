/********************************************************************************
** Form generated from reading UI file 'PropertyMatchShiftRotationForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYMATCHSHIFTROTATIONFORM_H
#define UI_PROPERTYMATCHSHIFTROTATIONFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyMatchShiftRotationForm
{
public:
    QToolButton *toolButtonPart;
    QToolButton *toolButtonMark;
    QTableWidget *tableWidgetPartList;
    QLabel *label;
    QTableWidget *tableWidgetMarkList;
    QLabel *label_2;
    QLabel *labelLibFolderName;
    QPushButton *pushButtonEditLibFolder;
    QPushButton *pushButtonEditLibrary;
    QFrame *frame;
    QListWidget *listWidgetAngleList;
    QLabel *labelRotationImage;

    void setupUi(GUIFormBase *PropertyMatchShiftRotationForm)
    {
        if (PropertyMatchShiftRotationForm->objectName().isEmpty())
            PropertyMatchShiftRotationForm->setObjectName("PropertyMatchShiftRotationForm");
        PropertyMatchShiftRotationForm->resize(400, 700);
        toolButtonPart = new QToolButton(PropertyMatchShiftRotationForm);
        toolButtonPart->setObjectName("toolButtonPart");
        toolButtonPart->setGeometry(QRect(10, 10, 141, 31));
        toolButtonPart->setCheckable(true);
        toolButtonMark = new QToolButton(PropertyMatchShiftRotationForm);
        toolButtonMark->setObjectName("toolButtonMark");
        toolButtonMark->setGeometry(QRect(170, 10, 141, 31));
        toolButtonMark->setCheckable(true);
        tableWidgetPartList = new QTableWidget(PropertyMatchShiftRotationForm);
        if (tableWidgetPartList->columnCount() < 3)
            tableWidgetPartList->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetPartList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetPartList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetPartList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetPartList->setObjectName("tableWidgetPartList");
        tableWidgetPartList->setGeometry(QRect(10, 108, 381, 191));
        tableWidgetPartList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetPartList->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(PropertyMatchShiftRotationForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 86, 381, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        tableWidgetMarkList = new QTableWidget(PropertyMatchShiftRotationForm);
        if (tableWidgetMarkList->columnCount() < 2)
            tableWidgetMarkList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetMarkList->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetMarkList->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        tableWidgetMarkList->setObjectName("tableWidgetMarkList");
        tableWidgetMarkList->setGeometry(QRect(10, 330, 381, 191));
        tableWidgetMarkList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetMarkList->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_2 = new QLabel(PropertyMatchShiftRotationForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 308, 381, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        labelLibFolderName = new QLabel(PropertyMatchShiftRotationForm);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(120, 50, 241, 31));
        QFont font;
        font.setPointSize(16);
        labelLibFolderName->setFont(font);
        pushButtonEditLibFolder = new QPushButton(PropertyMatchShiftRotationForm);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(10, 50, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon);
        pushButtonEditLibrary = new QPushButton(PropertyMatchShiftRotationForm);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(10, 530, 112, 34));
        frame = new QFrame(PropertyMatchShiftRotationForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(130, 530, 261, 161));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        listWidgetAngleList = new QListWidget(frame);
        listWidgetAngleList->setObjectName("listWidgetAngleList");
        listWidgetAngleList->setGeometry(QRect(10, 10, 91, 141));
        labelRotationImage = new QLabel(frame);
        labelRotationImage->setObjectName("labelRotationImage");
        labelRotationImage->setGeometry(QRect(100, 10, 151, 141));

        retranslateUi(PropertyMatchShiftRotationForm);

        QMetaObject::connectSlotsByName(PropertyMatchShiftRotationForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyMatchShiftRotationForm)
    {
        PropertyMatchShiftRotationForm->setWindowTitle(QCoreApplication::translate("PropertyMatchShiftRotationForm", "Form", nullptr));
        toolButtonPart->setText(QCoreApplication::translate("PropertyMatchShiftRotationForm", "\351\203\250\345\223\201", nullptr));
        toolButtonMark->setText(QCoreApplication::translate("PropertyMatchShiftRotationForm", "\344\275\215\347\275\256\345\220\210\343\202\217\343\201\233\351\203\250\345\210\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetPartList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyMatchShiftRotationForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetPartList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyMatchShiftRotationForm", "AreaID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetPartList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyMatchShiftRotationForm", "AreaName", nullptr));
        label->setText(QCoreApplication::translate("PropertyMatchShiftRotationForm", "\351\203\250\345\223\201\351\240\230\345\237\237\343\203\252\343\202\271\343\203\210", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetMarkList->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyMatchShiftRotationForm", "ItemID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetMarkList->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyMatchShiftRotationForm", "Position", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyMatchShiftRotationForm", "\344\275\215\347\275\256\345\220\210\343\202\217\343\201\233\351\203\250\345\210\206\343\203\252\343\202\271\343\203\210", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyMatchShiftRotationForm", "\357\274\270\357\274\270\357\274\270", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyMatchShiftRotationForm", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyMatchShiftRotationForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        labelRotationImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PropertyMatchShiftRotationForm: public Ui_PropertyMatchShiftRotationForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYMATCHSHIFTROTATIONFORM_H
