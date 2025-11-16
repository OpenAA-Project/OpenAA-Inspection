/********************************************************************************
** Form generated from reading UI file 'NGTypeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NGTYPEDIALOG_H
#define UI_NGTYPEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_NGTypeDialog
{
public:
    QLabel *label;
    QPushButton *pushButtonOK;
    QSpinBox *spinBoxMinRoundRate;
    QLabel *label_3;
    QLabel *label_2;
    QSpinBox *spinBoxMinSize;
    QLabel *label_4;
    QSpinBox *spinBoxMaxSize;
    QSpinBox *spinBoxMaxRoundRate;
    QFrame *frameThreshold;
    QLabel *label_33;
    QFrame *frameColorSample;
    QPushButton *pushButtonEliminateColor;
    QPushButton *pushButtonAddColor;
    QPushButton *pushButtonClear;

    void setupUi(QDialog *NGTypeDialog)
    {
        if (NGTypeDialog->objectName().isEmpty())
            NGTypeDialog->setObjectName("NGTypeDialog");
        NGTypeDialog->resize(489, 526);
        label = new QLabel(NGTypeDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 350, 81, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonOK = new QPushButton(NGTypeDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(80, 460, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        spinBoxMinRoundRate = new QSpinBox(NGTypeDialog);
        spinBoxMinRoundRate->setObjectName("spinBoxMinRoundRate");
        spinBoxMinRoundRate->setGeometry(QRect(40, 420, 81, 22));
        spinBoxMinRoundRate->setMaximum(9999);
        label_3 = new QLabel(NGTypeDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(130, 400, 81, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(NGTypeDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 350, 81, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxMinSize = new QSpinBox(NGTypeDialog);
        spinBoxMinSize->setObjectName("spinBoxMinSize");
        spinBoxMinSize->setGeometry(QRect(40, 370, 81, 22));
        spinBoxMinSize->setMaximum(999999);
        label_4 = new QLabel(NGTypeDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 400, 81, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxMaxSize = new QSpinBox(NGTypeDialog);
        spinBoxMaxSize->setObjectName("spinBoxMaxSize");
        spinBoxMaxSize->setGeometry(QRect(130, 370, 81, 22));
        spinBoxMaxSize->setMaximum(999999);
        spinBoxMaxRoundRate = new QSpinBox(NGTypeDialog);
        spinBoxMaxRoundRate->setObjectName("spinBoxMaxRoundRate");
        spinBoxMaxRoundRate->setGeometry(QRect(130, 420, 81, 22));
        spinBoxMaxRoundRate->setMaximum(9999);
        frameThreshold = new QFrame(NGTypeDialog);
        frameThreshold->setObjectName("frameThreshold");
        frameThreshold->setGeometry(QRect(10, 30, 251, 181));
        frameThreshold->setFrameShape(QFrame::StyledPanel);
        frameThreshold->setFrameShadow(QFrame::Sunken);
        label_33 = new QLabel(NGTypeDialog);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(10, 10, 251, 21));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Sunken);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameColorSample = new QFrame(NGTypeDialog);
        frameColorSample->setObjectName("frameColorSample");
        frameColorSample->setGeometry(QRect(270, 10, 205, 511));
        frameColorSample->setFrameShape(QFrame::StyledPanel);
        frameColorSample->setFrameShadow(QFrame::Sunken);
        pushButtonEliminateColor = new QPushButton(frameColorSample);
        pushButtonEliminateColor->setObjectName("pushButtonEliminateColor");
        pushButtonEliminateColor->setGeometry(QRect(20, 480, 161, 25));
        pushButtonAddColor = new QPushButton(frameColorSample);
        pushButtonAddColor->setObjectName("pushButtonAddColor");
        pushButtonAddColor->setGeometry(QRect(20, 450, 161, 25));
        pushButtonClear = new QPushButton(NGTypeDialog);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(90, 230, 91, 41));

        retranslateUi(NGTypeDialog);

        QMetaObject::connectSlotsByName(NGTypeDialog);
    } // setupUi

    void retranslateUi(QDialog *NGTypeDialog)
    {
        NGTypeDialog->setWindowTitle(QCoreApplication::translate("NGTypeDialog", "NGType", nullptr));
        label->setText(QCoreApplication::translate("NGTypeDialog", "\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("NGTypeDialog", "OK", nullptr));
        label_3->setText(QCoreApplication::translate("NGTypeDialog", "\346\234\200\345\244\247\345\206\206\345\275\242\347\216\207", nullptr));
        label_2->setText(QCoreApplication::translate("NGTypeDialog", "\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_4->setText(QCoreApplication::translate("NGTypeDialog", "\346\234\200\345\260\217\345\206\206\345\275\242\347\216\207", nullptr));
        label_33->setText(QCoreApplication::translate("NGTypeDialog", "\350\211\262\347\257\204\345\233\262", nullptr));
        pushButtonEliminateColor->setText(QCoreApplication::translate("NGTypeDialog", "Eliminate color", nullptr));
        pushButtonAddColor->setText(QCoreApplication::translate("NGTypeDialog", "Add Color", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("NGTypeDialog", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NGTypeDialog: public Ui_NGTypeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NGTYPEDIALOG_H
