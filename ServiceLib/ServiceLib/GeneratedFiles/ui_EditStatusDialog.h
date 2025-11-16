/********************************************************************************
** Form generated from reading UI file 'EditStatusDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITSTATUSDIALOG_H
#define UI_EDITSTATUSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_EditStatusDialog
{
public:
    QTableWidget *tableWidgetGUI;
    QLabel *label;
    QLabel *label_2;
    QListWidget *listWidgetMode;
    QLabel *label_3;
    QFrame *frame;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonLoadHTML;
    QPushButton *pushButtonClear;
    QTextEdit *plainTextEditComment;
    QLabel *label_4;
    QPushButton *pushButtonLoadToolTipHTML;
    QPushButton *pushButtonToolTipClear;
    QTextEdit *textEditToolTip;
    QCheckBox *checkBoxEnableToolTip;

    void setupUi(QDialog *EditStatusDialog)
    {
        if (EditStatusDialog->objectName().isEmpty())
            EditStatusDialog->setObjectName("EditStatusDialog");
        EditStatusDialog->resize(450, 631);
        tableWidgetGUI = new QTableWidget(EditStatusDialog);
        if (tableWidgetGUI->columnCount() < 3)
            tableWidgetGUI->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetGUI->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetGUI->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetGUI->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetGUI->setObjectName("tableWidgetGUI");
        tableWidgetGUI->setGeometry(QRect(11, 20, 431, 71));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        tableWidgetGUI->setPalette(palette);
        tableWidgetGUI->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetGUI->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(EditStatusDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 431, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(EditStatusDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 100, 431, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetMode = new QListWidget(EditStatusDialog);
        listWidgetMode->setObjectName("listWidgetMode");
        listWidgetMode->setGeometry(QRect(10, 120, 431, 161));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        listWidgetMode->setPalette(palette1);
        label_3 = new QLabel(EditStatusDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 440, 431, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame = new QFrame(EditStatusDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 530, 451, 101));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonCancel = new QPushButton(frame);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(360, 50, 75, 34));
        pushButtonUpdate = new QPushButton(frame);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(234, 50, 121, 34));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon);
        pushButtonLoadHTML = new QPushButton(frame);
        pushButtonLoadHTML->setObjectName("pushButtonLoadHTML");
        pushButtonLoadHTML->setGeometry(QRect(20, 10, 112, 34));
        pushButtonClear = new QPushButton(frame);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(150, 10, 81, 34));
        plainTextEditComment = new QTextEdit(EditStatusDialog);
        plainTextEditComment->setObjectName("plainTextEditComment");
        plainTextEditComment->setGeometry(QRect(10, 460, 431, 71));
        label_4 = new QLabel(EditStatusDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(140, 290, 301, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonLoadToolTipHTML = new QPushButton(EditStatusDialog);
        pushButtonLoadToolTipHTML->setObjectName("pushButtonLoadToolTipHTML");
        pushButtonLoadToolTipHTML->setGeometry(QRect(20, 380, 112, 34));
        pushButtonToolTipClear = new QPushButton(EditStatusDialog);
        pushButtonToolTipClear->setObjectName("pushButtonToolTipClear");
        pushButtonToolTipClear->setGeometry(QRect(150, 380, 81, 34));
        textEditToolTip = new QTextEdit(EditStatusDialog);
        textEditToolTip->setObjectName("textEditToolTip");
        textEditToolTip->setGeometry(QRect(10, 310, 431, 61));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        textEditToolTip->setPalette(palette2);
        textEditToolTip->setAutoFillBackground(true);
        checkBoxEnableToolTip = new QCheckBox(EditStatusDialog);
        checkBoxEnableToolTip->setObjectName("checkBoxEnableToolTip");
        checkBoxEnableToolTip->setGeometry(QRect(20, 288, 108, 22));

        retranslateUi(EditStatusDialog);

        pushButtonUpdate->setDefault(true);


        QMetaObject::connectSlotsByName(EditStatusDialog);
    } // setupUi

    void retranslateUi(QDialog *EditStatusDialog)
    {
        EditStatusDialog->setWindowTitle(QCoreApplication::translate("EditStatusDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetGUI->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditStatusDialog", "DLLRoot", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetGUI->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditStatusDialog", "DLLName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetGUI->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EditStatusDialog", "InstName", nullptr));
        label->setText(QCoreApplication::translate("EditStatusDialog", "Where", nullptr));
        label_2->setText(QCoreApplication::translate("EditStatusDialog", "Mode", nullptr));
        label_3->setText(QCoreApplication::translate("EditStatusDialog", "Comment", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditStatusDialog", "Cancel", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("EditStatusDialog", "Update", nullptr));
        pushButtonLoadHTML->setText(QCoreApplication::translate("EditStatusDialog", "Load HTML", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("EditStatusDialog", "Clear", nullptr));
        label_4->setText(QCoreApplication::translate("EditStatusDialog", "ToolTip", nullptr));
        pushButtonLoadToolTipHTML->setText(QCoreApplication::translate("EditStatusDialog", "Load HTML", nullptr));
        pushButtonToolTipClear->setText(QCoreApplication::translate("EditStatusDialog", "Clear", nullptr));
        checkBoxEnableToolTip->setText(QCoreApplication::translate("EditStatusDialog", "Show", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditStatusDialog: public Ui_EditStatusDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITSTATUSDIALOG_H
