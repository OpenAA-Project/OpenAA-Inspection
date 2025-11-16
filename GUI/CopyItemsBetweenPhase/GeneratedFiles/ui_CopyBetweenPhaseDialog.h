/********************************************************************************
** Form generated from reading UI file 'CopyBetweenPhaseDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYBETWEENPHASEDIALOG_H
#define UI_COPYBETWEENPHASEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CopyBetweenPhaseDialog
{
public:
    QPushButton *pushButtonCancel;
    QCheckBox *checkBoxMaster;
    QLineEdit *lineEditAlgorithm;
    QListWidget *listWidgetDestPhase;
    QCheckBox *checkBoxTarget;
    QListWidget *listWidgetSourcePhase;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButtonCopy;
    QCheckBox *checkBoxAlgorithm;

    void setupUi(QDialog *CopyBetweenPhaseDialog)
    {
        if (CopyBetweenPhaseDialog->objectName().isEmpty())
            CopyBetweenPhaseDialog->setObjectName("CopyBetweenPhaseDialog");
        CopyBetweenPhaseDialog->resize(259, 286);
        pushButtonCancel = new QPushButton(CopyBetweenPhaseDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(90, 240, 81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        checkBoxMaster = new QCheckBox(CopyBetweenPhaseDialog);
        checkBoxMaster->setObjectName("checkBoxMaster");
        checkBoxMaster->setGeometry(QRect(10, 10, 201, 18));
        checkBoxMaster->setChecked(true);
        lineEditAlgorithm = new QLineEdit(CopyBetweenPhaseDialog);
        lineEditAlgorithm->setObjectName("lineEditAlgorithm");
        lineEditAlgorithm->setGeometry(QRect(30, 70, 211, 21));
        listWidgetDestPhase = new QListWidget(CopyBetweenPhaseDialog);
        listWidgetDestPhase->setObjectName("listWidgetDestPhase");
        listWidgetDestPhase->setGeometry(QRect(160, 120, 81, 111));
        listWidgetDestPhase->setSelectionBehavior(QAbstractItemView::SelectRows);
        checkBoxTarget = new QCheckBox(CopyBetweenPhaseDialog);
        checkBoxTarget->setObjectName("checkBoxTarget");
        checkBoxTarget->setGeometry(QRect(10, 30, 211, 18));
        checkBoxTarget->setChecked(true);
        listWidgetSourcePhase = new QListWidget(CopyBetweenPhaseDialog);
        listWidgetSourcePhase->setObjectName("listWidgetSourcePhase");
        listWidgetSourcePhase->setGeometry(QRect(10, 120, 81, 111));
        listWidgetSourcePhase->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(CopyBetweenPhaseDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 100, 81, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(CopyBetweenPhaseDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 100, 81, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        pushButtonCopy = new QPushButton(CopyBetweenPhaseDialog);
        pushButtonCopy->setObjectName("pushButtonCopy");
        pushButtonCopy->setGeometry(QRect(100, 130, 51, 41));
        checkBoxAlgorithm = new QCheckBox(CopyBetweenPhaseDialog);
        checkBoxAlgorithm->setObjectName("checkBoxAlgorithm");
        checkBoxAlgorithm->setGeometry(QRect(10, 50, 101, 18));
        checkBoxAlgorithm->setChecked(true);

        retranslateUi(CopyBetweenPhaseDialog);

        QMetaObject::connectSlotsByName(CopyBetweenPhaseDialog);
    } // setupUi

    void retranslateUi(QDialog *CopyBetweenPhaseDialog)
    {
        CopyBetweenPhaseDialog->setWindowTitle(QCoreApplication::translate("CopyBetweenPhaseDialog", "Copy between phases", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CopyBetweenPhaseDialog", "Cancel", nullptr));
        checkBoxMaster->setText(QCoreApplication::translate("CopyBetweenPhaseDialog", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217", nullptr));
        checkBoxTarget->setText(QCoreApplication::translate("CopyBetweenPhaseDialog", "\346\244\234\346\237\273\347\224\273\345\203\217", nullptr));
        label->setText(QCoreApplication::translate("CopyBetweenPhaseDialog", "Source", nullptr));
        label_2->setText(QCoreApplication::translate("CopyBetweenPhaseDialog", "Destination", nullptr));
        pushButtonCopy->setText(QCoreApplication::translate("CopyBetweenPhaseDialog", "=>", nullptr));
        checkBoxAlgorithm->setText(QCoreApplication::translate("CopyBetweenPhaseDialog", "Item data", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CopyBetweenPhaseDialog: public Ui_CopyBetweenPhaseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYBETWEENPHASEDIALOG_H
