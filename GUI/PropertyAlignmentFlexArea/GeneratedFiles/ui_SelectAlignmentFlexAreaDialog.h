/********************************************************************************
** Form generated from reading UI file 'SelectAlignmentFlexAreaDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTALIGNMENTFLEXAREADIALOG_H
#define UI_SELECTALIGNMENTFLEXAREADIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectAlignmentFlexAreaDialog
{
public:
    QPushButton *ButtonCancel;
    QTableWidget *tableWidgetLibList;
    QLineEdit *EditLibID;
    QLineEdit *EditItemName;
    QLabel *label;
    QFrame *frameLibFolder;
    QPushButton *ButtonOK;
    QLineEdit *EditLibName;
    QFrame *frameGenLayer;
    QFrame *frame_26;
    QLabel *label_87;
    QSpinBox *spinBoxSearchDot;
    QLabel *label_20;
    QLabel *label_3;
    QSpinBox *spinBoxGlobalSearchDot;
    QCheckBox *checkBoxKeepBW;
    QLabel *label_9;
    QLabel *labelCautionForOrigin;

    void setupUi(QDialog *SelectAlignmentFlexAreaDialog)
    {
        if (SelectAlignmentFlexAreaDialog->objectName().isEmpty())
            SelectAlignmentFlexAreaDialog->setObjectName("SelectAlignmentFlexAreaDialog");
        SelectAlignmentFlexAreaDialog->resize(418, 465);
        ButtonCancel = new QPushButton(SelectAlignmentFlexAreaDialog);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(260, 420, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon);
        tableWidgetLibList = new QTableWidget(SelectAlignmentFlexAreaDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(200, 10, 201, 141));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        EditLibID = new QLineEdit(SelectAlignmentFlexAreaDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(30, 190, 51, 21));
        EditLibID->setReadOnly(true);
        EditItemName = new QLineEdit(SelectAlignmentFlexAreaDialog);
        EditItemName->setObjectName("EditItemName");
        EditItemName->setGeometry(QRect(80, 160, 321, 21));
        EditItemName->setReadOnly(false);
        label = new QLabel(SelectAlignmentFlexAreaDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 160, 81, 21));
        frameLibFolder = new QFrame(SelectAlignmentFlexAreaDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(0, 10, 191, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonOK = new QPushButton(SelectAlignmentFlexAreaDialog);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(80, 420, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon1);
        EditLibName = new QLineEdit(SelectAlignmentFlexAreaDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(80, 190, 321, 21));
        EditLibName->setReadOnly(true);
        frameGenLayer = new QFrame(SelectAlignmentFlexAreaDialog);
        frameGenLayer->setObjectName("frameGenLayer");
        frameGenLayer->setGeometry(QRect(20, 250, 381, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);
        frame_26 = new QFrame(SelectAlignmentFlexAreaDialog);
        frame_26->setObjectName("frame_26");
        frame_26->setGeometry(QRect(20, 280, 381, 101));
        frame_26->setFrameShape(QFrame::StyledPanel);
        frame_26->setFrameShadow(QFrame::Sunken);
        label_87 = new QLabel(frame_26);
        label_87->setObjectName("label_87");
        label_87->setGeometry(QRect(0, 0, 31, 101));
        label_87->setFrameShape(QFrame::Panel);
        label_87->setFrameShadow(QFrame::Raised);
        label_87->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_87->setIndent(1);
        spinBoxSearchDot = new QSpinBox(frame_26);
        spinBoxSearchDot->setObjectName("spinBoxSearchDot");
        spinBoxSearchDot->setGeometry(QRect(290, 40, 81, 20));
        spinBoxSearchDot->setMinimum(0);
        spinBoxSearchDot->setMaximum(9999);
        label_20 = new QLabel(frame_26);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(40, 40, 241, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        label_20->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(frame_26);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 10, 241, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        spinBoxGlobalSearchDot = new QSpinBox(frame_26);
        spinBoxGlobalSearchDot->setObjectName("spinBoxGlobalSearchDot");
        spinBoxGlobalSearchDot->setGeometry(QRect(290, 10, 81, 22));
        spinBoxGlobalSearchDot->setMaximum(999999);
        checkBoxKeepBW = new QCheckBox(frame_26);
        checkBoxKeepBW->setObjectName("checkBoxKeepBW");
        checkBoxKeepBW->setGeometry(QRect(40, 70, 291, 22));
        label_9 = new QLabel(SelectAlignmentFlexAreaDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 230, 381, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignCenter);
        labelCautionForOrigin = new QLabel(SelectAlignmentFlexAreaDialog);
        labelCautionForOrigin->setObjectName("labelCautionForOrigin");
        labelCautionForOrigin->setGeometry(QRect(30, 390, 341, 20));

        retranslateUi(SelectAlignmentFlexAreaDialog);

        ButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SelectAlignmentFlexAreaDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectAlignmentFlexAreaDialog)
    {
        SelectAlignmentFlexAreaDialog->setWindowTitle(QCoreApplication::translate("SelectAlignmentFlexAreaDialog", "Select library", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SelectAlignmentFlexAreaDialog", "Cancel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectAlignmentFlexAreaDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectAlignmentFlexAreaDialog", "Name", nullptr));
        label->setText(QCoreApplication::translate("SelectAlignmentFlexAreaDialog", "Item name", nullptr));
        ButtonOK->setText(QCoreApplication::translate("SelectAlignmentFlexAreaDialog", "OK", nullptr));
        label_87->setText(QCoreApplication::translate("SelectAlignmentFlexAreaDialog", "<html><head/><body><p>\345\256\237</p><p>\350\241\214</p></body></html>", nullptr));
        label_20->setText(QCoreApplication::translate("SelectAlignmentFlexAreaDialog", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        label_3->setText(QCoreApplication::translate("SelectAlignmentFlexAreaDialog", "\345\272\203\345\237\237\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        checkBoxKeepBW->setText(QCoreApplication::translate("SelectAlignmentFlexAreaDialog", "Keep Block/White", nullptr));
        label_9->setText(QCoreApplication::translate("SelectAlignmentFlexAreaDialog", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        labelCautionForOrigin->setText(QCoreApplication::translate("SelectAlignmentFlexAreaDialog", "Pickup/Generate from Master image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectAlignmentFlexAreaDialog: public Ui_SelectAlignmentFlexAreaDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTALIGNMENTFLEXAREADIALOG_H
