/********************************************************************************
** Form generated from reading UI file 'SelectMovePastePage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTMOVEPASTEPAGE_H
#define UI_SELECTMOVEPASTEPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectMovePastePage
{
public:
    QPushButton *pushButton;
    QLabel *label_3;
    QFrame *frameBase;
    QFrame *frame;
    QLabel *label;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QPushButton *pushButton_2;

    void setupUi(QDialog *SelectMovePastePage)
    {
        if (SelectMovePastePage->objectName().isEmpty())
            SelectMovePastePage->setObjectName("SelectMovePastePage");
        SelectMovePastePage->resize(281, 225);
        pushButton = new QPushButton(SelectMovePastePage);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(30, 180, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon);
        label_3 = new QLabel(SelectMovePastePage);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 281, 20));
        label_3->setAlignment(Qt::AlignCenter);
        frameBase = new QFrame(SelectMovePastePage);
        frameBase->setObjectName("frameBase");
        frameBase->setGeometry(QRect(10, 20, 261, 151));
        frameBase->setFrameShape(QFrame::StyledPanel);
        frameBase->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(frameBase);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 241, 41));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 51, 16));
        checkBox = new QCheckBox(frame);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(80, 10, 61, 18));
        checkBox->setChecked(true);
        checkBox_2 = new QCheckBox(frame);
        checkBox_2->setObjectName("checkBox_2");
        checkBox_2->setGeometry(QRect(160, 10, 61, 18));
        checkBox_2->setChecked(true);
        pushButton_2 = new QPushButton(SelectMovePastePage);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(170, 180, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_2->setIcon(icon1);

        retranslateUi(SelectMovePastePage);

        pushButton->setDefault(true);


        QMetaObject::connectSlotsByName(SelectMovePastePage);
    } // setupUi

    void retranslateUi(QDialog *SelectMovePastePage)
    {
        SelectMovePastePage->setWindowTitle(QCoreApplication::translate("SelectMovePastePage", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("SelectMovePastePage", "OK", nullptr));
        label_3->setText(QCoreApplication::translate("SelectMovePastePage", "\343\203\232\343\203\274\343\202\270\345\242\203\347\225\214\343\201\256Move/Paste \343\203\232\343\203\274\343\202\270\351\201\270\346\212\236", nullptr));
        label->setText(QCoreApplication::translate("SelectMovePastePage", "Page", nullptr));
        checkBox->setText(QCoreApplication::translate("SelectMovePastePage", "Page 0", nullptr));
        checkBox_2->setText(QCoreApplication::translate("SelectMovePastePage", "Page 1", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SelectMovePastePage", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectMovePastePage: public Ui_SelectMovePastePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTMOVEPASTEPAGE_H
