/********************************************************************************
** Form generated from reading UI file 'SelectThresholdLevelDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTTHRESHOLDLEVELDIALOG_H
#define UI_SELECTTHRESHOLDLEVELDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectThresholdLevelDialog
{
public:
    QTreeWidget *treeWidgetLevel;
    QFrame *frame;
    QLabel *label;
    QLineEdit *lineEditLevelName;
    QLineEdit *lineEditRemark;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBoxLevelValue;
    QLabel *label_4;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonClose;
    QLineEdit *lineEditParentName;
    QLabel *label_5;

    void setupUi(QDialog *SelectThresholdLevelDialog)
    {
        if (SelectThresholdLevelDialog->objectName().isEmpty())
            SelectThresholdLevelDialog->setObjectName("SelectThresholdLevelDialog");
        SelectThresholdLevelDialog->resize(523, 394);
        treeWidgetLevel = new QTreeWidget(SelectThresholdLevelDialog);
        treeWidgetLevel->setObjectName("treeWidgetLevel");
        treeWidgetLevel->setGeometry(QRect(0, 0, 521, 221));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeWidgetLevel->sizePolicy().hasHeightForWidth());
        treeWidgetLevel->setSizePolicy(sizePolicy);
        treeWidgetLevel->setAcceptDrops(true);
        frame = new QFrame(SelectThresholdLevelDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 220, 521, 171));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 40, 91, 24));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        lineEditLevelName = new QLineEdit(frame);
        lineEditLevelName->setObjectName("lineEditLevelName");
        lineEditLevelName->setGeometry(QRect(110, 40, 261, 24));
        lineEditLevelName->setMaxLength(60);
        lineEditRemark = new QLineEdit(frame);
        lineEditRemark->setObjectName("lineEditRemark");
        lineEditRemark->setGeometry(QRect(110, 70, 261, 24));
        lineEditRemark->setMaxLength(60);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 70, 91, 24));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 100, 91, 24));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        spinBoxLevelValue = new QSpinBox(frame);
        spinBoxLevelValue->setObjectName("spinBoxLevelValue");
        spinBoxLevelValue->setGeometry(QRect(110, 100, 71, 24));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(190, 100, 101, 24));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        pushButtonSelect = new QPushButton(frame);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(280, 130, 112, 34));
        pushButtonClose = new QPushButton(frame);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(400, 130, 112, 34));
        lineEditParentName = new QLineEdit(frame);
        lineEditParentName->setObjectName("lineEditParentName");
        lineEditParentName->setGeometry(QRect(110, 10, 261, 24));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditParentName->setPalette(palette);
        lineEditParentName->setAutoFillBackground(true);
        lineEditParentName->setMaxLength(60);
        lineEditParentName->setReadOnly(true);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 10, 91, 24));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);

        retranslateUi(SelectThresholdLevelDialog);

        QMetaObject::connectSlotsByName(SelectThresholdLevelDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectThresholdLevelDialog)
    {
        SelectThresholdLevelDialog->setWindowTitle(QCoreApplication::translate("SelectThresholdLevelDialog", "Dialog", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidgetLevel->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("SelectThresholdLevelDialog", "Level Name", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("SelectThresholdLevelDialog", "1", nullptr));
        label->setText(QCoreApplication::translate("SelectThresholdLevelDialog", "\343\203\254\343\203\231\343\203\253\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("SelectThresholdLevelDialog", "\345\202\231\350\200\203", nullptr));
        label_3->setText(QCoreApplication::translate("SelectThresholdLevelDialog", "\345\204\252\345\205\210\347\225\252\345\217\267", nullptr));
        label_4->setText(QCoreApplication::translate("SelectThresholdLevelDialog", "\357\274\220\357\275\236", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectThresholdLevelDialog", "\351\201\270\346\212\236", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SelectThresholdLevelDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_5->setText(QCoreApplication::translate("SelectThresholdLevelDialog", "\343\203\225\343\202\251\343\203\253\343\203\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectThresholdLevelDialog: public Ui_SelectThresholdLevelDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTTHRESHOLDLEVELDIALOG_H
