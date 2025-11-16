/********************************************************************************
** Form generated from reading UI file 'PropertyAutoPCBHoleAlignerForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYAUTOPCBHOLEALIGNERFORM_H
#define UI_PROPERTYAUTOPCBHOLEALIGNERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_PropertyAutoPCBHoleAlignerForm
{
public:
    QTableWidget *tableWidgetGeneratedLibList;
    QLabel *labelLibFolderName;
    QPushButton *pushButtonGetBack;
    QPushButton *pushButtonSetFrom;
    QLabel *label_30;
    QFrame *frame;
    QLabel *label;
    QCheckBox *checkBoxShowHole;
    QCheckBox *checkBoxShowFringe;
    QPushButton *pushButtonEditLibFolder;
    QPushButton *pushButtonEditLibrary;
    QFrame *frame_2;
    QLabel *label_3;
    QTableWidget *tableWidgetAreaList;
    QLabel *label_31;
    QTableWidget *tableWidgetLibList;

    void setupUi(GUIFormBase *PropertyAutoPCBHoleAlignerForm)
    {
        if (PropertyAutoPCBHoleAlignerForm->objectName().isEmpty())
            PropertyAutoPCBHoleAlignerForm->setObjectName("PropertyAutoPCBHoleAlignerForm");
        PropertyAutoPCBHoleAlignerForm->resize(400, 700);
        tableWidgetGeneratedLibList = new QTableWidget(PropertyAutoPCBHoleAlignerForm);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetGeneratedLibList->setObjectName("tableWidgetGeneratedLibList");
        tableWidgetGeneratedLibList->setGeometry(QRect(230, 70, 161, 131));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        labelLibFolderName = new QLabel(PropertyAutoPCBHoleAlignerForm);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(150, 10, 241, 31));
        QFont font;
        font.setPointSize(16);
        labelLibFolderName->setFont(font);
        pushButtonGetBack = new QPushButton(PropertyAutoPCBHoleAlignerForm);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(180, 150, 39, 23));
        pushButtonSetFrom = new QPushButton(PropertyAutoPCBHoleAlignerForm);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(180, 110, 39, 23));
        label_30 = new QLabel(PropertyAutoPCBHoleAlignerForm);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 50, 161, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame = new QFrame(PropertyAutoPCBHoleAlignerForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 290, 381, 81));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 381, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxShowHole = new QCheckBox(frame);
        checkBoxShowHole->setObjectName("checkBoxShowHole");
        checkBoxShowHole->setGeometry(QRect(40, 26, 201, 22));
        checkBoxShowFringe = new QCheckBox(frame);
        checkBoxShowFringe->setObjectName("checkBoxShowFringe");
        checkBoxShowFringe->setGeometry(QRect(40, 50, 201, 22));
        pushButtonEditLibFolder = new QPushButton(PropertyAutoPCBHoleAlignerForm);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(10, 10, 131, 31));
        QFont font1;
        font1.setPointSize(12);
        pushButtonEditLibFolder->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon);
        pushButtonEditLibrary = new QPushButton(PropertyAutoPCBHoleAlignerForm);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(90, 210, 211, 31));
        pushButtonEditLibrary->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon1);
        frame_2 = new QFrame(PropertyAutoPCBHoleAlignerForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 380, 381, 191));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 381, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetAreaList = new QTableWidget(frame_2);
        if (tableWidgetAreaList->columnCount() < 4)
            tableWidgetAreaList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(3, __qtablewidgetitem5);
        tableWidgetAreaList->setObjectName("tableWidgetAreaList");
        tableWidgetAreaList->setGeometry(QRect(10, 30, 361, 151));
        tableWidgetAreaList->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetAreaList->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_31 = new QLabel(PropertyAutoPCBHoleAlignerForm);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(230, 50, 161, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetLibList = new QTableWidget(PropertyAutoPCBHoleAlignerForm);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 70, 161, 131));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(PropertyAutoPCBHoleAlignerForm);

        QMetaObject::connectSlotsByName(PropertyAutoPCBHoleAlignerForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyAutoPCBHoleAlignerForm)
    {
        PropertyAutoPCBHoleAlignerForm->setWindowTitle(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "Name", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "\357\274\270\357\274\270\357\274\270", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "<=", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "=>", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        label->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "\350\241\250\347\244\272", nullptr));
        checkBoxShowHole->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "\347\251\264\351\240\230\345\237\237\350\241\250\347\244\272", nullptr));
        checkBoxShowFringe->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "\345\221\250\347\270\201\351\240\230\345\237\237\350\241\250\347\244\272", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "Sheet\351\240\230\345\237\237\343\203\252\343\202\271\343\203\210", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetAreaList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetAreaList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "LibName", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetAreaList->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "MinD", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetAreaList->horizontalHeaderItem(3);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "MaxD", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyAutoPCBHoleAlignerForm", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyAutoPCBHoleAlignerForm: public Ui_PropertyAutoPCBHoleAlignerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYAUTOPCBHOLEALIGNERFORM_H
