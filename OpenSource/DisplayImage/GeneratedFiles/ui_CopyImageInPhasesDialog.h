/********************************************************************************
** Form generated from reading UI file 'CopyImageInPhasesDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYIMAGEINPHASESDIALOG_H
#define UI_COPYIMAGEINPHASESDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CopyImageInPhasesDialog
{
public:
    QListWidget *listWidgetSourcePhase;
    QListWidget *listWidgetDestPhase;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButtonCopy;
    QPushButton *pushButtonCancel;
    QCheckBox *checkBoxTarget;
    QCheckBox *checkBoxMaster;

    void setupUi(QDialog *CopyImageInPhasesDialog)
    {
        if (CopyImageInPhasesDialog->objectName().isEmpty())
            CopyImageInPhasesDialog->setObjectName("CopyImageInPhasesDialog");
        CopyImageInPhasesDialog->resize(252, 247);
        listWidgetSourcePhase = new QListWidget(CopyImageInPhasesDialog);
        listWidgetSourcePhase->setObjectName("listWidgetSourcePhase");
        listWidgetSourcePhase->setGeometry(QRect(10, 80, 81, 111));
        listWidgetSourcePhase->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidgetDestPhase = new QListWidget(CopyImageInPhasesDialog);
        listWidgetDestPhase->setObjectName("listWidgetDestPhase");
        listWidgetDestPhase->setGeometry(QRect(160, 80, 81, 111));
        listWidgetDestPhase->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(CopyImageInPhasesDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 60, 81, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(CopyImageInPhasesDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 60, 81, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        pushButtonCopy = new QPushButton(CopyImageInPhasesDialog);
        pushButtonCopy->setObjectName("pushButtonCopy");
        pushButtonCopy->setGeometry(QRect(100, 90, 51, 41));
        pushButtonCancel = new QPushButton(CopyImageInPhasesDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(90, 200, 81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        checkBoxTarget = new QCheckBox(CopyImageInPhasesDialog);
        checkBoxTarget->setObjectName("checkBoxTarget");
        checkBoxTarget->setGeometry(QRect(110, 30, 141, 18));
        checkBoxTarget->setChecked(true);
        checkBoxMaster = new QCheckBox(CopyImageInPhasesDialog);
        checkBoxMaster->setObjectName("checkBoxMaster");
        checkBoxMaster->setGeometry(QRect(110, 10, 131, 18));
        checkBoxMaster->setChecked(true);

        retranslateUi(CopyImageInPhasesDialog);

        QMetaObject::connectSlotsByName(CopyImageInPhasesDialog);
    } // setupUi

    void retranslateUi(QDialog *CopyImageInPhasesDialog)
    {
        CopyImageInPhasesDialog->setWindowTitle(QCoreApplication::translate("CopyImageInPhasesDialog", "Cppy image between phases", nullptr));
        label->setText(QCoreApplication::translate("CopyImageInPhasesDialog", "Source", nullptr));
        label_2->setText(QCoreApplication::translate("CopyImageInPhasesDialog", "Destination", nullptr));
        pushButtonCopy->setText(QCoreApplication::translate("CopyImageInPhasesDialog", "=>", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CopyImageInPhasesDialog", "Cancel", nullptr));
        checkBoxTarget->setText(QCoreApplication::translate("CopyImageInPhasesDialog", "\346\244\234\346\237\273\347\224\273\345\203\217", nullptr));
        checkBoxMaster->setText(QCoreApplication::translate("CopyImageInPhasesDialog", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CopyImageInPhasesDialog: public Ui_CopyImageInPhasesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYIMAGEINPHASESDIALOG_H
