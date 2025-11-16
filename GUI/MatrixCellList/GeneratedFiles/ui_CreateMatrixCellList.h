/********************************************************************************
** Form generated from reading UI file 'CreateMatrixCellList.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEMATRIXCELLLIST_H
#define UI_CREATEMATRIXCELLLIST_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CreateMatrixCellListClass
{
public:
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxCellSizeX;
    QSpinBox *spinBoxCellSizeY;
    QSpinBox *spinBoxStartY;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *spinBoxStartX;
    QSpinBox *spinBoxEndY;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *spinBoxEndX;
    QComboBox *comboBox;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonColor;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *CreateMatrixCellListClass)
    {
        if (CreateMatrixCellListClass->objectName().isEmpty())
            CreateMatrixCellListClass->setObjectName("CreateMatrixCellListClass");
        CreateMatrixCellListClass->resize(211, 334);
        label = new QLabel(CreateMatrixCellListClass);
        label->setObjectName("label");
        label->setGeometry(QRect(19, 20, 81, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(CreateMatrixCellListClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 20, 81, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxCellSizeX = new QSpinBox(CreateMatrixCellListClass);
        spinBoxCellSizeX->setObjectName("spinBoxCellSizeX");
        spinBoxCellSizeX->setGeometry(QRect(20, 40, 81, 22));
        spinBoxCellSizeX->setMaximum(99999999);
        spinBoxCellSizeY = new QSpinBox(CreateMatrixCellListClass);
        spinBoxCellSizeY->setObjectName("spinBoxCellSizeY");
        spinBoxCellSizeY->setGeometry(QRect(110, 40, 81, 22));
        spinBoxCellSizeY->setMaximum(99999999);
        spinBoxStartY = new QSpinBox(CreateMatrixCellListClass);
        spinBoxStartY->setObjectName("spinBoxStartY");
        spinBoxStartY->setGeometry(QRect(110, 110, 81, 22));
        spinBoxStartY->setMaximum(99999999);
        label_3 = new QLabel(CreateMatrixCellListClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 90, 81, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(CreateMatrixCellListClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(19, 90, 81, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxStartX = new QSpinBox(CreateMatrixCellListClass);
        spinBoxStartX->setObjectName("spinBoxStartX");
        spinBoxStartX->setGeometry(QRect(20, 110, 81, 22));
        spinBoxStartX->setMaximum(99999999);
        spinBoxEndY = new QSpinBox(CreateMatrixCellListClass);
        spinBoxEndY->setObjectName("spinBoxEndY");
        spinBoxEndY->setGeometry(QRect(110, 160, 81, 22));
        spinBoxEndY->setMaximum(99999999);
        label_5 = new QLabel(CreateMatrixCellListClass);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(110, 140, 81, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(CreateMatrixCellListClass);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(19, 140, 81, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxEndX = new QSpinBox(CreateMatrixCellListClass);
        spinBoxEndX->setObjectName("spinBoxEndX");
        spinBoxEndX->setGeometry(QRect(20, 160, 81, 22));
        spinBoxEndX->setMaximum(99999999);
        comboBox = new QComboBox(CreateMatrixCellListClass);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(20, 210, 171, 22));
        pushButtonOK = new QPushButton(CreateMatrixCellListClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 250, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonColor = new QPushButton(CreateMatrixCellListClass);
        pushButtonColor->setObjectName("pushButtonColor");
        pushButtonColor->setGeometry(QRect(120, 250, 75, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Color.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonColor->setIcon(icon1);
        pushButtonClose = new QPushButton(CreateMatrixCellListClass);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(120, 290, 75, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon2);

        retranslateUi(CreateMatrixCellListClass);

        QMetaObject::connectSlotsByName(CreateMatrixCellListClass);
    } // setupUi

    void retranslateUi(QDialog *CreateMatrixCellListClass)
    {
        CreateMatrixCellListClass->setWindowTitle(QCoreApplication::translate("CreateMatrixCellListClass", "CreateMatrixCellList", nullptr));
        label->setText(QCoreApplication::translate("CreateMatrixCellListClass", "\350\246\226\351\207\216\343\202\265\343\202\244\343\202\272\357\274\270", nullptr));
        label_2->setText(QCoreApplication::translate("CreateMatrixCellListClass", "\350\246\226\351\207\216\343\202\265\343\202\244\343\202\272\357\274\271", nullptr));
        label_3->setText(QCoreApplication::translate("CreateMatrixCellListClass", "\351\226\213\345\247\213\345\272\247\346\250\231\357\274\271", nullptr));
        label_4->setText(QCoreApplication::translate("CreateMatrixCellListClass", "\351\226\213\345\247\213\345\272\247\346\250\231\357\274\270", nullptr));
        label_5->setText(QCoreApplication::translate("CreateMatrixCellListClass", "\347\265\202\344\272\206\345\272\247\346\250\231\357\274\271", nullptr));
        label_6->setText(QCoreApplication::translate("CreateMatrixCellListClass", "\347\265\202\344\272\206\345\272\247\346\250\231\357\274\270", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("CreateMatrixCellListClass", "\345\267\246\344\270\212\343\201\213\343\202\211\345\217\263\344\270\213\343\201\270\343\200\201\345\270\270\343\201\253\345\217\263\346\226\271\345\220\221", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("CreateMatrixCellListClass", "\345\267\246\344\270\212\343\201\213\343\202\211\345\217\263\344\270\213\343\201\270\343\200\201\347\266\231\347\266\232", nullptr));

        pushButtonOK->setText(QCoreApplication::translate("CreateMatrixCellListClass", "OK \347\224\237\346\210\220", nullptr));
        pushButtonColor->setText(QCoreApplication::translate("CreateMatrixCellListClass", "\350\211\262\350\250\255\345\256\232", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("CreateMatrixCellListClass", "\351\226\211\343\201\230\343\202\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateMatrixCellListClass: public Ui_CreateMatrixCellListClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEMATRIXCELLLIST_H
