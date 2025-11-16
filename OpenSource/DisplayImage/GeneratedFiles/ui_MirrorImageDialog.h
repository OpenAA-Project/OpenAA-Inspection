/********************************************************************************
** Form generated from reading UI file 'MirrorImageDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MIRRORIMAGEDIALOG_H
#define UI_MIRRORIMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_MirrorImageDialog
{
public:
    QCheckBox *checkBoxMaster;
    QCheckBox *checkBoxTarget;
    QLabel *label_2;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonGo;
    QGroupBox *groupBox;
    QRadioButton *radioButtonXMirror;
    QRadioButton *radioButtonYMirror;
    QLabel *label_3;

    void setupUi(QDialog *MirrorImageDialog)
    {
        if (MirrorImageDialog->objectName().isEmpty())
            MirrorImageDialog->setObjectName("MirrorImageDialog");
        MirrorImageDialog->resize(241, 259);
        checkBoxMaster = new QCheckBox(MirrorImageDialog);
        checkBoxMaster->setObjectName("checkBoxMaster");
        checkBoxMaster->setGeometry(QRect(70, 10, 131, 18));
        checkBoxMaster->setChecked(true);
        checkBoxTarget = new QCheckBox(MirrorImageDialog);
        checkBoxTarget->setObjectName("checkBoxTarget");
        checkBoxTarget->setGeometry(QRect(70, 40, 141, 18));
        checkBoxTarget->setChecked(true);
        label_2 = new QLabel(MirrorImageDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 170, 191, 20));
        label_2->setAlignment(Qt::AlignCenter);
        pushButtonCancel = new QPushButton(MirrorImageDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 220, 81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonGo = new QPushButton(MirrorImageDialog);
        pushButtonGo->setObjectName("pushButtonGo");
        pushButtonGo->setGeometry(QRect(30, 220, 81, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonGo->setIcon(icon1);
        groupBox = new QGroupBox(MirrorImageDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 70, 201, 80));
        radioButtonXMirror = new QRadioButton(groupBox);
        radioButtonXMirror->setObjectName("radioButtonXMirror");
        radioButtonXMirror->setGeometry(QRect(20, 10, 171, 22));
        radioButtonXMirror->setChecked(true);
        radioButtonYMirror = new QRadioButton(groupBox);
        radioButtonYMirror->setObjectName("radioButtonYMirror");
        radioButtonYMirror->setGeometry(QRect(20, 40, 171, 22));
        label_3 = new QLabel(MirrorImageDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 190, 191, 20));
        label_3->setAlignment(Qt::AlignCenter);

        retranslateUi(MirrorImageDialog);

        QMetaObject::connectSlotsByName(MirrorImageDialog);
    } // setupUi

    void retranslateUi(QDialog *MirrorImageDialog)
    {
        MirrorImageDialog->setWindowTitle(QCoreApplication::translate("MirrorImageDialog", "X/Y mirror", nullptr));
        checkBoxMaster->setText(QCoreApplication::translate("MirrorImageDialog", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217", nullptr));
        checkBoxTarget->setText(QCoreApplication::translate("MirrorImageDialog", "\346\244\234\346\237\273\347\224\273\345\203\217", nullptr));
        label_2->setText(QCoreApplication::translate("MirrorImageDialog", "\346\234\254\345\221\275\344\273\244\343\201\257UNDO\343\201\247\343\201\215\343\201\276\343\201\233\343\202\223", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("MirrorImageDialog", "Cancel", nullptr));
        pushButtonGo->setText(QCoreApplication::translate("MirrorImageDialog", "Go", nullptr));
        groupBox->setTitle(QString());
        radioButtonXMirror->setText(QCoreApplication::translate("MirrorImageDialog", "X\357\274\210\346\250\252\357\274\211\345\217\215\350\273\242", nullptr));
        radioButtonYMirror->setText(QCoreApplication::translate("MirrorImageDialog", "Y\357\274\210\347\270\246\357\274\211\345\217\215\350\273\242", nullptr));
        label_3->setText(QCoreApplication::translate("MirrorImageDialog", "\343\203\232\343\203\274\343\202\270\345\206\205\343\201\247\343\201\256\345\217\215\350\273\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MirrorImageDialog: public Ui_MirrorImageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MIRRORIMAGEDIALOG_H
