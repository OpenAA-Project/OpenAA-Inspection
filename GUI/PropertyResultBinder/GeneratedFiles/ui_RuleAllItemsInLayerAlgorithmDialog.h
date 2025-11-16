/********************************************************************************
** Form generated from reading UI file 'RuleAllItemsInLayerAlgorithmDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULEALLITEMSINLAYERALGORITHMDIALOG_H
#define UI_RULEALLITEMSINLAYERALGORITHMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_RuleAllItemsInLayerAlgorithmDialog
{
public:
    QSpinBox *spinBoxPage;
    QPushButton *pushButtonCancel;
    QLabel *label_4;
    QFrame *frame;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEditName;
    QLineEdit *lineEditRemark;
    QCheckBox *checkBoxConclusion;
    QPushButton *pushButtonOK;
    QLabel *label_3;
    QComboBox *comboBoxLibTypeSelect;
    QLabel *label_5;
    QSpinBox *spinBoxLayer;
    QPushButton *pushButtonDelete;

    void setupUi(QDialog *RuleAllItemsInLayerAlgorithmDialog)
    {
        if (RuleAllItemsInLayerAlgorithmDialog->objectName().isEmpty())
            RuleAllItemsInLayerAlgorithmDialog->setObjectName("RuleAllItemsInLayerAlgorithmDialog");
        RuleAllItemsInLayerAlgorithmDialog->resize(284, 306);
        spinBoxPage = new QSpinBox(RuleAllItemsInLayerAlgorithmDialog);
        spinBoxPage->setObjectName("spinBoxPage");
        spinBoxPage->setGeometry(QRect(190, 70, 61, 22));
        pushButtonCancel = new QPushButton(RuleAllItemsInLayerAlgorithmDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(190, 250, 81, 41));
        QFont font;
        font.setPointSize(10);
        pushButtonCancel->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        label_4 = new QLabel(RuleAllItemsInLayerAlgorithmDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 70, 171, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        frame = new QFrame(RuleAllItemsInLayerAlgorithmDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 140, 261, 101));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 10, 61, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 40, 61, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        lineEditName = new QLineEdit(frame);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(80, 10, 171, 21));
        lineEditRemark = new QLineEdit(frame);
        lineEditRemark->setObjectName("lineEditRemark");
        lineEditRemark->setGeometry(QRect(80, 40, 171, 21));
        checkBoxConclusion = new QCheckBox(frame);
        checkBoxConclusion->setObjectName("checkBoxConclusion");
        checkBoxConclusion->setGeometry(QRect(10, 70, 231, 19));
        pushButtonOK = new QPushButton(RuleAllItemsInLayerAlgorithmDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 250, 81, 41));
        pushButtonOK->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        label_3 = new QLabel(RuleAllItemsInLayerAlgorithmDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 261, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        comboBoxLibTypeSelect = new QComboBox(RuleAllItemsInLayerAlgorithmDialog);
        comboBoxLibTypeSelect->setObjectName("comboBoxLibTypeSelect");
        comboBoxLibTypeSelect->setGeometry(QRect(10, 30, 261, 22));
        label_5 = new QLabel(RuleAllItemsInLayerAlgorithmDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 100, 171, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        spinBoxLayer = new QSpinBox(RuleAllItemsInLayerAlgorithmDialog);
        spinBoxLayer->setObjectName("spinBoxLayer");
        spinBoxLayer->setGeometry(QRect(190, 100, 61, 22));
        pushButtonDelete = new QPushButton(RuleAllItemsInLayerAlgorithmDialog);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(100, 250, 81, 41));
        pushButtonDelete->setFont(font);
        pushButtonDelete->setIcon(icon1);
        pushButtonDelete->setAutoDefault(false);

        retranslateUi(RuleAllItemsInLayerAlgorithmDialog);

        pushButtonOK->setDefault(true);
        pushButtonDelete->setDefault(false);


        QMetaObject::connectSlotsByName(RuleAllItemsInLayerAlgorithmDialog);
    } // setupUi

    void retranslateUi(QDialog *RuleAllItemsInLayerAlgorithmDialog)
    {
        RuleAllItemsInLayerAlgorithmDialog->setWindowTitle(QCoreApplication::translate("RuleAllItemsInLayerAlgorithmDialog", "Rule all Items in Layer Algorithm", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("RuleAllItemsInLayerAlgorithmDialog", "Cancel", nullptr));
        label_4->setText(QCoreApplication::translate("RuleAllItemsInLayerAlgorithmDialog", "Page", nullptr));
        label_6->setText(QCoreApplication::translate("RuleAllItemsInLayerAlgorithmDialog", "Name", nullptr));
        label_7->setText(QCoreApplication::translate("RuleAllItemsInLayerAlgorithmDialog", "Remark", nullptr));
        checkBoxConclusion->setText(QCoreApplication::translate("RuleAllItemsInLayerAlgorithmDialog", "Conclusion", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("RuleAllItemsInLayerAlgorithmDialog", "OK", nullptr));
        label_3->setText(QCoreApplication::translate("RuleAllItemsInLayerAlgorithmDialog", "Select library - source", nullptr));
        label_5->setText(QCoreApplication::translate("RuleAllItemsInLayerAlgorithmDialog", "Layer", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("RuleAllItemsInLayerAlgorithmDialog", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RuleAllItemsInLayerAlgorithmDialog: public Ui_RuleAllItemsInLayerAlgorithmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULEALLITEMSINLAYERALGORITHMDIALOG_H
